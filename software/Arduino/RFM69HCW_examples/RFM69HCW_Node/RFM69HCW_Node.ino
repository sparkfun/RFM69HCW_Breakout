/****************************************************************************** <filename>
RFM69HCW_Node
Mike Grusin, SparkFun Electronics>
3/17/2014
https://github.com/sparkfun/RFM69_Breakout

This sketch will send data packets filled with a test pattern
to another RFM69 module. You can use it with the "RFM69HCW_Gateway"
sketch to demonstrate sending and receiving packets between modules.

This sketch is a modified version of Felix Rusu's "Node" example
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
DIO0/'0'  D2                  D3 (requires modifying the library)

Note that you MUST attach an antenna to the board. This can be as
simple as a piece of wire cut to a specific length and soldered to
the ANT header. The length is dependent on the frequency of the 
module. For 915MHz the wire should be 3.07"/78mm long. For 434MHz
the wire should be 6.47"/164mm long.

ANTENNA TIPS: When operating the board, you will achieve the best
range if the wires on both ends are as vertical as possible. For
extra range, you can solder a second, equal length of wire to one
of the adjacent ground pins, and point it in the opposite direction
of the antenna (dipole). Try to keep the wire in open air without
any metal nearby. The radio signal will pass through plastic boxes,
but don't try to operate the board + antenna within a metal box -
it won't work.

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
#define NODEID        2    // ID number for this node (unique to each node)
#define GATEWAYID     1    // ID of destination node (gateway)

// Uncomment one of the below lines to define
// the frequency of your RFM69 module:

//#define FREQUENCY   RF69_433MHZ
//#define FREQUENCY   RF69_868MHZ
#define FREQUENCY     RF69_915MHZ

#define ENCRYPTKEY    "sampleEncryptKey" // Use the same 16 characters on each node
#define IS_RFM69HW    // Comment out if NOT using HW/HCW module
#define ACK_TIME      30 // Max # of ms to wait for an ack
#define SERIAL_BAUD   115200 // Baud rate for terminal messages (not radio data)

// You can connect an LED between pins 9 and 8 to get status blinks

#define LED           9  // Status LED+ on pin 9 (ala Moteino)
#define GROUND        8  // Adjacent "ground" (digital low) pin for LED-

RFM69 radio; // RFM69 library object

int TRANSMITPERIOD = 300; // Transmit a packet to the gateway this often (in ms)
char payload[] = "123 ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Test pattern
byte sendSize=0; // Start with 0-length packets, increase by one each time
boolean requestACK = false; // Don't request an ACKnowledge by default

void setup()
{
  // Set up status LED
  
  pinMode(LED,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  Blink(LED,100);
  
  // Set up serial port (to terminal, not to radio)
  
  Serial.begin(SERIAL_BAUD);
  Serial.println("reboot");
  
  delay(100); // wait for radio to power up
  
  radio.initialize(FREQUENCY,NODEID,NETWORKID);

  // If module is HW/HCW set up for high-power mode

#ifdef IS_RFM69HW
  radio.setHighPower();
#endif

  radio.encrypt(ENCRYPTKEY); // set up encryption

  // print out configuration information
 
  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
}

void loop()
{
  static long lastPeriod = -1;

  // You can send several 1-letter commands to the node:
  
  // '0' through '9' will change the interpacket delay
  // from 0 to 900 ms:

  if (Serial.available() > 0)
  {
    char input = Serial.read();
    if (input >= 48 && input <= 57) //[0,9]
    {
      TRANSMITPERIOD = 100 * (input-48);
      if (TRANSMITPERIOD == 0) TRANSMITPERIOD = 1000;
      Serial.print("\nChanging delay to ");
      Serial.print(TRANSMITPERIOD);
      Serial.println("ms\n");
    }
    
    if (input == 'r') // d = dump register values
      radio.readAllRegs();
    
    if (input == 'E') // E = enable encryption
      radio.encrypt(ENCRYPTKEY);
    
    if (input == 'e') // e = disable encryption
      radio.encrypt(null);
  }

  // Check for any received packets
  
  if (radio.receiveDone())
  {
    Serial.print('[');Serial.print(radio.SENDERID, DEC);Serial.print("] ");
    for (byte i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");Serial.print(radio.RSSI);Serial.print("]");

    if (radio.ACK_REQUESTED)
    {
      radio.sendACK();
      Serial.print(" - ACK sent");
      delay(10);

      // Blink when we have two-way communication with the gateway
      Blink(LED,5);
    }
    Serial.println();
  }
  
  // Wait until the next transmit period to send the next acket
  
  int currPeriod = millis()/TRANSMITPERIOD;

  if (currPeriod != lastPeriod)
  {
    lastPeriod=currPeriod;
    Serial.print("Sending[");
    Serial.print(sendSize);
    Serial.print("]: ");

    // Send increasingly large packets (to 32 characters)
    // then start over

    for(byte i = 0; i < sendSize; i++)
      Serial.print((char)payload[i]);

    if (radio.sendWithRetry(GATEWAYID, payload, sendSize))
     Serial.print(" ok!");
    else Serial.print(" nothing...");

    sendSize = (sendSize + 1) % 31;
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
