/****************************************************************************** <filename>
RFM69HCW_Gateway
Mike Grusin, SparkFun Electronics>
3/17/2014
https://github.com/sparkfun/RFM69_Breakout

This sketch will receive packets sent by other RFM69 modules.
You can use it with the "RFM69HCW_Node" sketch to demonstrate
sending and receiving packets between modules.

This sketch is a modified version of Felix Rusu's "Gateway" example
sketch for his RFM69 library. It has had Moteino-specific hardware
references removed, and has been preset to work with SparkFun's
RFM69HCW/915MHz Breakout Board. (If you're using a different module
or frequency, see "Software configuration" below.)

Library requirements:

This sketch uses Felix Rusu's RFM69 library, available in this
distribution or at https://github.com/LowPowerLab/RFM69

To install the RFM69 library onto your system, see our tutorial at:
https://learn.sparkfun.com/tutorials/installing-an-arduino-library

Software configuration:

This sketch will work out-of-the-box with the RFM69HCW/915MHz
Breakout Board. If you're using a different module or frequency,
modify the appropriate #defines at the top of the sketch.

Hardware connections:

Note that the RFM69HCW breakout board is a 3.3V board.
The easiest way to use it is to connect it to a 3.3V Arduino.

You can connect it to a 5V Arduino if you power it from 3.3V,
and provide 5V to 3.3V level-shifting on the MOSI, SCK, NSS,
and DIO0 pins.

          328-based boards    32U4-based boards
MISO/'O'  D12                 ISP/MISO
MOSI/'I'  D11                 ISP/MOSI
SCK/'C'   D13                 ISP/SCK
NSS/'S'   D10                 D10
DIO0/'0'  D2                  D3

Versions:

This sketch was tested with Arduino 1.0.5, RFM69HCW BOB version 1.0,
and Felix Rusu's RFM69 library as of 3/2014.

As this code is derived from Felix Rusu's code, it is distributed
under the same license:

Creative Commons Attrib Share-Alike License
You are free to use/extend this library but please abide with the
CC-BY-SA license: http://creativecommons.org/licenses/by-sa/3.0/

******************************************************************************/

#include <RFM69.h>
#include <SPI.h>

#define NETWORKID     100  // ID number for the network (same for all nodes)
#define NODEID        1    // ID number for this node (unique to each node)

// Uncomment one of the below lines to define
// the frequency of your RFM69 module:

//#define FREQUENCY     RF69_433MHZ
//#define FREQUENCY     RF69_868MHZ
#define FREQUENCY     RF69_915MHZ

#define ENCRYPTKEY    "sampleEncryptKey" // Use the same 16 characters on each node
#define IS_RFM69HW    // Comment out if NOT using HW/HCW module
#define ACK_TIME      30 // Max # of ms to wait for an ack
#define SERIAL_BAUD   115200 // Baud rate for terminal messages (not radio data)

// You can connect an LED between pins 9 and 8 to get status blinks

#define LED           9  // Status LED+ on pin 9 (ala Moteino)
#define GROUND        8  // Adjacent "ground" (digital low) pin for LED-

RFM69 radio; // RFM69 library object

boolean promiscuousMode = false; // Don't sniff all packets by default

void setup()
{
  // Set up status LED

  pinMode(LED,OUTPUT);
  pinMode(GROUND,OUTPUT);
  digitalWrite(GROUND,LOW);
  Blink(LED,100);

  // Set up serial port (to terminal, not to radio)

  Serial.begin(SERIAL_BAUD);
  Serial.println("Gateway rebooted");
  
  delay(100); // wait for radio to power up
  
  radio.initialize(FREQUENCY,NODEID,NETWORKID);

  // If module is HW/HCW set up for high-power mode

#ifdef IS_RFM69HW
  radio.setHighPower();
#endif

  radio.encrypt(ENCRYPTKEY); // set up encryption

  radio.promiscuous(promiscuousMode); // enable/disable promiscuous mode

  // print out configuration information
  
  char buff[50];
  sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
}

void loop()
{
  static byte ackCount=0;

  // you can send several 1-letter commands to the gateway:

  if (Serial.available() > 0)
  {
    char input = Serial.read();
    
    if (input == 'r') // d = dump all register values
      radio.readAllRegs();
    
    if (input == 'E') // E = enable encryption
      radio.encrypt(ENCRYPTKEY);
    
    if (input == 'e') // e = disable encryption
      radio.encrypt(null);
    
    if (input == 'p') // p = toggle promiscuous mode
    {
      promiscuousMode = !promiscuousMode;
      radio.promiscuous(promiscuousMode);
      Serial.print("Promiscuous mode ");Serial.println(promiscuousMode ? "on" : "off");
    }
    
    if (input == 't') // t = print out module temperature
    {
      byte temperature =  radio.readTemperature(-1); // -1 = user cal factor, adjust for correct ambient
      byte fTemp = 1.8 * temperature + 32; // 9/5=1.8
      Serial.print( "Radio Temp is ");
      Serial.print(temperature);
      Serial.print("C, ");
      Serial.print(fTemp); //converting to F loses some resolution, obvious when C is on edge between 2 values (ie 26C=78F, 27C=80F)
      Serial.println('F');
    }
  }

  // Process received packets

  if (radio.receiveDone())
  {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");

    if (promiscuousMode)
    {
      Serial.print("to [");Serial.print(radio.TARGETID, DEC);Serial.print("] ");
    }

    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.RSSI);Serial.print("]");
    
    // When a node requests an ACK, respond to the ACK.

    if (radio.ACK_REQUESTED)
    {
      byte theNodeID = radio.SENDERID;
      radio.sendACK();
      Serial.print(" - ACK sent.");

      // Also for every third received packet, send a packet
      // requesting an ACK. This tests TX and RX on both the
      // NODE and the GATEWAY.

      if (ackCount++%3==0)
      {
        Serial.print(" Pinging node ");
        Serial.print(theNodeID);
        Serial.print(" - ACK...");
        delay(3); // Delay when sending right after reception
        if (radio.sendWithRetry(theNodeID, "ACK TEST", 8, 0))  // 0 = only 1 attempt, no retries
        {
          Serial.print("ok!");
          Blink(LED,3);
        }
        else Serial.print("nothing");
      }
    }
    Serial.println();
  }
}

void Blink(byte PIN, int DELAY_MS)
// Utility function to blink LED for a given number of ms
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
