/****************************************************************************** <filename>
RFM69HCW_Reflect
Mike Grusin, SparkFun Electronics
https://github.com/sparkfun/RFM69_Breakout

This sketch will send test packets from one RFM69
module to another. It will automatically acknowledge ("ACK")
received messages, which shows the sender that the packet was
properly received.

Library requirements:

This sketch uses Felix Rusu's RFM69 library, available in this
distribution or at https://github.com/LowPowerLab/RFM69

To install the RFM69 library onto your system, see our tutorial at:
https://learn.sparkfun.com/tutorials/installing-an-arduino-library

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
range if the wires on both modules are as vertical as possible. For
extra range, you can solder a second, equal length of wire to one
of the adjacent ground pins, and point it in the opposite direction
of the antenna (dipole). Try to keep the wire in open air without
any metal nearby. The radio signal will pass through plastic boxes,
but don't try to operate the board + antenna within a metal box -
it won't work.

Software configuration:

This sketch will work out-of-the-box with the RFM69HCW/915MHz
Breakout Board. If you're using a different module or frequency,
modify the appropriate #defines at the top of the sketch.

All radio modules in your network should have the same network ID.
Each radio module should have a different ID. You can change these
by modifying the #defines for MYNETWORK (this network), MYNODE
(this node ID) and TONODE (the node you want to send messages to).
If you set TONODE to 255, that is a broadcast address which will
reach all the nodes on the network.

BE SURE TO SET "MYNODE" TO A DIFFERENT NUMBER FOR EACH NODE
IN YOUR NETWORK.

If you want to use encryption, set the Encryption #define to true,
and provide the same 16-character key to all your nodes.

If you set Promiscuous mode to true, you will receive all messages
sent on your network. If you set Promiscuous mode to false, you 
will only see messages addressed to MYNODE.

Using the code:

Once you've uploaded the code to your Arduino, open a Serial
Monitor window. Change the baud rate to 9600, and set the
"line ending" dropdown next to it to "Carriage return". You
should now be able to type short text messages into the bar
at the top of the Serial Monitor and press "Enter" or click "Send"
to send the message. Both sent and received messages will appear
in the Serial Monitor window.

Versions:

This sketch was tested with Arduino 1.0.5, RFM69HCW BOB version 1.0,
and Felix Rusu's RFM69 library as of 3/2014.

As this code is derived from Felix Rusu's example code,
it is distributed under the same license:

Creative Commons Attrib Share-Alike License
You are free to use/extend this library but please abide with the
CC-BY-SA license: http://creativecommons.org/licenses/by-sa/3.0/
******************************************************************************/

#include <RFM69.h>
#include <SPI.h>

RFM69 radio; // RFM69 library object

// Uncomment one of the below lines to define your module's frequency

#define FREQUENCY   RF69_433MHZ
//#define FREQUENCY   RF69_868MHZ
//#define FREQUENCY     RF69_915MHZ

#define IS_RFM69HW    true // Comment out if NOT using HW/HCW module

// CHANGE THE BELOW DEFINES TO YOUR NETWORK AND NODE IDs

#define MYNETWORK     100  // 0-255 ID number for the network (same for all nodes)
#define MYNODE          2  // 0-255 ID number for this node (unique to each node)

#define Encrypt       false  // Encrypt packets?
#define ENCRYPTKEY    "sampleEncryptKey" // Use the same 16 characters on each node

#define SERIAL_BAUD   9600 // Baud rate for terminal messages (not radio data)

// You can connect an LED between pins 9+ and 8- to get status blinks

#define LED           9  // Status LED + on pin 9 (ala Moteino)
#define GROUND        8  // Adjacent "ground" (digital low) pin for LED-

#define TIMEOUT 1000 // time delay between sends

void setup()
{
  int x;
  // Set up status LED
  
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  pinMode(GROUND,OUTPUT); // "Ground" pin next to LED pin for convenience
  digitalWrite(GROUND,LOW);
  
  // Set up serial port (to terminal, not to radio)
  
  Serial.begin(SERIAL_BAUD);
  Serial.println("Reboot");
  
  // Wait for radio to power up
  
  Blink(LED,100); // You could also use delay(100); 
  
  // Initialize radio module
  
  radio.initialize(FREQUENCY,MYNODE,MYNETWORK);

  // If module is HW/HCW set up for high-power mode
  
  if (IS_RFM69HW)
    radio.setHighPower();
  
  // Enable or disable promiscuous mode
  
//  radio.promiscuous(false); 

  // Enable or disable encryption
  
  if (Encrypt)
    radio.encrypt(ENCRYPTKEY); 
  else
    radio.encrypt(null);

  // print out configuration information
 
  Serial.println("RFM69 initialized!");
  Serial.print("Frequency: ");
  Serial.print(FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println("MHz");
  Serial.print("Network: ");
  Serial.println(MYNETWORK);
  Serial.print("My node: ");
  Serial.println(MYNODE);
  Serial.print("Encryption: ");
  Serial.println(Encrypt ? "on" : "off");
  Serial.println();
}

void loop()
{
  unsigned char from;
  static unsigned long nexttime = 0;

  // If we receive a packet, send it back to the source
  
  if (radio.receiveDone())
  {
    from = radio.SENDERID;
    
    if (radio.ACKRequested())
      radio.sendACK();

    Serial.print("Received message from node: ");
    Serial.print(from);
    Serial.print(" RSSI: ");
    Serial.println(radio.RSSI);
    Serial.println((char*)radio.DATA);

    Serial.print("Sending same message back to node: ");
    Serial.println(from);
    
    radio.send(from, (void*)radio.DATA, radio.DATALEN,false);

    Blink(LED,100);
  }
}

void Blink(byte PIN, int DELAY_MS)
// Utility function to blink a LED for a given number of ms
{
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}

