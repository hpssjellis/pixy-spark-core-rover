// By Jeremy Ellis

// Note: Watch the RGB LED at startup.
// If it quickly goes to breathing cyan, you have Wifi connectivity
// If it takes 20 seconds to go to breathing cyan, then you have no Wifi connectivity but the Pixy should still work

SYSTEM_MODE(SEMI_AUTOMATIC);  // so that connectivity is not blocking

int myConnect = 0;      // means neighter connected or disconnected yet



int myD7  = D7;      // to test if wifi is working


//      #include "SPI.h"        // got rid of this since it would not compile
#include "Pixy.h"
#include "TPixy.h"


// Not sure how to flash new code so will not do this yet.
//SYSTEM_MODE(MANUAL);                // Set the system mode to manual. We don't need the cloud for this code


Pixy pixy;                          // Create our pixy object

// Setup - Runs Once @ Startup
void setup() {   

    pinMode(myD7, OUTPUT); 
    Spark.connect();         //attempt to connect to Wifi

    delay(20000);   // wait 20 seconds at startup


   if (WiFi.ready()){   
        myConnect = 1;   // means wifi got connected
    } else {
        Spark.disconnect(); 
        WiFi.off();
        myConnect =2;   // means no wifi cloud connectivity
       // digitalWrite(D7,HIGH);     // D7 high says no wifi but spark working fine.
      }  
    
    
    RGB.brightness(1);    // 1=very low light, 255 = max

    Serial.begin(9600);             // Initalize the USB Serial port
    pixy.init();                    // Initalize the pixy object
}

// Loop - Runs over and over
void loop(){ 
    
    

    uint16_t    blocks;                       // Create an unsigned int to hold the number of found blocks
    char        buf[50];                      // Create a buffer for printing over serial
    int         myPixyInt, myWait, myWait2, i;

    blocks = pixy.getBlocks();      // Do the pixy stuff. Grab the numbers of blocks the pixy finds
  
  // If we have some blocks increment the frame counter (i) and if enough frames have passed print out data about the found blocks to the serial port
  if (blocks) {
 
 
 
 // for serial USB printing of the information every 25th loop
 
 /*
     i++;
    if (i%25==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (int j = 0; j < blocks; j++)
      {
        sprintf(buf, "\tblock %d:", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
        Serial.println();
      }
    }

 */
 
 
    myPixyInt = pixy.blocks[0].x;    // x location of the main object    0 - 320

   // myPixyInt = pixy.blocks[0].y;
   // myPixyInt = pixy.blocks[0].width;
   // myPixyInt = pixy.blocks[0].height;
   
   
   myWait = myPixyInt;
   // myWait = blocks * 3;  // if you want to see how many objects Pixy has detected x 3
   
   if (myPixyInt <= 10) {   
       digitalWrite(D7, LOW);     // If Pixy sees nothing D7 LED off
    }  
    
    
    if (myPixyInt > 10 && myPixyInt <= 100) {    // Object on the far left, blink really fast
        digitalWrite(D7, HIGH);                  
        delay(5);                                          
        digitalWrite(D7, LOW); 
        delay(5);
    }  
 
     
    if (myPixyInt > 100 && myPixyInt <= 200) {    // Object on near middle, blink slow
        digitalWrite(D7, HIGH);                  
        delay(100);                                          
        digitalWrite(D7, LOW); 
        delay(100);
    }  
 
      
    if (myPixyInt > 200 && myPixyInt <= 300) {    // Object on Right, blink really slow
        digitalWrite(D7, HIGH);                  
        delay(1000);                                          
        digitalWrite(D7, LOW); 
        delay(1000);
    }  
 
 
    if (myPixyInt > 300 ) {    // Object on far right, leave LED on
        digitalWrite(D7, HIGH);                  
    }  

    
   delay(5); // just for the heck of it slow things down a bit
  } // end blocks
}   // end loop














