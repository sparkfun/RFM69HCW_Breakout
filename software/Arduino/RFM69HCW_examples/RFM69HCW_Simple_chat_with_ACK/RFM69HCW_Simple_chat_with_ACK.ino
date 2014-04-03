/****************************************************************************** <filename>
RFM69HCW_Simple_chat_with_ACK
Mike Grusin, SparkFun Electronics
4/2/2014
https://github.com/sparkfun/RFM69_Breakout

This sketch will send and receive short text packets from one RFM69
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

//#define FREQUENCY   RF69_433MHZ
//#define FREQUENCY   RF69_868MHZ
#define FREQUENCY     RF69_915MHZ

#define IS_RFM69HW    true // Comment out if NOT using HW/HCW module

// CHANGE THE BELOW DEFINES TO YOUR NETWORK AND NODE IDs

#define MYNETWORK     100  // 0-255 ID number for the network (same for all nodes)
#define MYNODE          1  // 0-255 ID number for this node (unique to each node)
#define TONODE          2  // 0-255 Node you're sending messages to
                           // (Address 255 broadcasts to all nodes)

#define Promiscuous   true  // See all packets on this network?
                             // (Otherwise just ones addressed to you)
#define Encrypt       false  // Encrypt packets?
#define ENCRYPTKEY    "sampleEncryptKey" // Use the same 16 characters on each node

#define SERIAL_BAUD   9600 // Baud rate for terminal messages (not radio data)

// You can connect an LED between pins 9+ and 8- to get status blinks

#define LED           9  // Status LED + on pin 9 (ala Moteino)
#define GROUND        8  // Adjacent "ground" (digital low) pin for LED-

void setup()
{
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
  
  radio.promiscuous(Promiscuous); 

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
  Serial.print("To node: ");
  Serial.println(TONODE);
  Serial.print("Encryption: ");
  Serial.println(Encrypt ? "on" : "off");
  Serial.print("Promiscuous mode: ");
  Serial.println(Promiscuous ? "on" : "off");
  Serial.println();
}

void loop()
{
  static char buffer[MAX_DATA_LEN];
  static byte length = 0;
  byte i;
  
  // Check for any received packets
  
  if (radio.receiveDone())
  {
    Blink(LED,100);
    Serial.print("Received from node: ");
    Serial.print(radio.SENDERID, DEC);
    Serial.print(" to: ");
    Serial.print(radio.TARGETID, DEC);
    Serial.print(" RSSI: ");
    Serial.print(radio.RSSI);
    Serial.print(" data: \"");
    for (i = 0; i < radio.DATALEN; i++)
      Serial.print((char)radio.DATA[i]);
    Serial.print("\"");

    // If the sender requests an ACK, AND the packet is addressed
    // to us (in promiscuous mode you'll see all the packets),
    // reply with an ACKnowledge.

    if ((radio.ACK_REQUESTED)&&(radio.TARGETID == MYNODE))
    {
      radio.sendACK();
      Serial.println(" (ACK sent)");
    }
    else
      Serial.println(" (no ACK sent)");

  }

  // Gather serial characters and send if necessary
  
  if (Serial.available())
  {
    buffer[length] = Serial.read(); // Get the next typed char
      
    if (buffer[length] == 0x0D) // Is this char a carriage return?
    {
      // Got a carriage return, send the packet we've been storing

      Serial.print("Sending from node: ");
      Serial.print(MYNODE);
      Serial.print(" to: ");
      Serial.print(TONODE);
      Serial.print(" data: \"");
      for (byte i = 0; i < length; i++)
        Serial.print(buffer[i]);
      Serial.print("\"");

      Blink(LED,100);
      
      // Send the data. The function tells us whether the receiver
      // ACKnowledged the packet or not.
      // 3 = max retries, 30 = ms to wait for an ACK before
      // trying again or giving up.
      
      if (radio.sendWithRetry(TONODE, buffer, length, 3, 30)) // not "length+1" to ignore CR
        Serial.println(" (ACK received)");
      else
        Serial.println(" (no ACK received)");

      length = 0; // Reset buffer for next packet
    }
    else
    {
      // We didn't get a carriage return,
      // so keep adding to the packet

      if (length < MAX_DATA_LEN)
        length++;
    }
  }
}

void Blink(byte PIN, int DELAY_MS)
// Utility function to blink a LED for a given number of ms
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
