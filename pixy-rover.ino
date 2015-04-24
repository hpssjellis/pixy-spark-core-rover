// By Jeremy Ellis.
// Rover should move slowly unless several seconds no response from the pixy then it should stop.
// should move left or right based on where the object is.
// should stop if the object gets to big a width ie it is close.


#define FRAME_SKIP 25                // How many frames to skip. Lower numbers cause faster response

/* Globals -------------------------------------------------------------------*/
// Note my pololu big motor driver needs two digital and one analog PWM controls for the drive motor VNH5019
//   https://www.pololu.com/product/1451

int myForward          = D6;      // set or change these as needed
int myBackward         = D5;      // set or change these as needed
int myDriveMotor       = A0;    



// I am using the cheap pololu motor driver that only needs one digital and one analog pins for the turning motor DRV8835
//    https://www.pololu.com/product/2135    note: this can drive two motors but I needed the bigger driver for the 2.3 amp drivemotor

int myLeftRight        = D0;       // different motor driver does both left and right
int myTurnMotor        = A1;   //A4;  // this one must be changed since it is used by the Pixy along with A3,A4,A5

int myD7               = D7;      // to test if wifi is working
int myLast             = Time.now();   // for emergency motor stop after 4 s  no activity from the pixy







// Begin User Defined Defines
#define FRAME_SKIP 25                // How many frames to skip. Lower numbers cause faster response
// End User Defined Defines

//      #include "SPI.h"        // got rid of this since it would not compile
#include "Pixy.h"
#include "TPixy.h"


// Not sure how to flash new code so will not do this yet.
//SYSTEM_MODE(MANUAL);                // Set the system mode to manual. We don't need the cloud for this code


Pixy pixy;                          // Create our pixy object
int i = 0;                          // Create an int to count for frame skipping. Frame skipping is used to artificially slow down the pixy loop

// Setup - Runs Once @ Startup
void setup() {   
//    Spark.function("my-main", myMain);  
    pinMode(myDriveMotor, OUTPUT);
    pinMode(myForward, OUTPUT);
    pinMode(myBackward, OUTPUT);
    
    pinMode(myTurnMotor, OUTPUT);
    pinMode(myLeftRight, OUTPUT);

    pinMode(myD7, OUTPUT);    
  
    
    
    //Serial.begin(9600);             // Initalize the USB Serial port
   // pixy.init();                    // Initalize the pixy object
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
      
  
    //RGB.control(true);
    //RGB.color(0, 255, 255);  //cyan
    RGB.brightness(1);    // 1=very low light, 255 = max


    Serial.begin(9600);             // Initalize the USB Serial port
    pixy.init();                    // Initalize the pixy object
}

// Loop - Runs over and over
void loop(){ 
    
    
    
        RGB.brightness(1); 
    if (Time.now() >= myLast + 4){                // car may be out of control or wifi down or pixy down
          
         analogWrite(myDriveMotor,  0);           // shut both motors down
         analogWrite(myTurnMotor,   0);  
         RGB.brightness(100);                     // show that no processing lately
    }
    
    
    
    // Variable Creation 
    uint16_t blocks;                // Create an unsigned int to hold the number of found blocks
    char buf[50];                   // Create a buffer for printing over serial

    blocks = pixy.getBlocks();      // Do the pixy stuff. Grab the numbers of blocks the pixy finds
  
  // If we have some blocks increment the frame counter (i) and if enough frames have passed print out data about the found blocks to the serial port
  if (blocks) {
    myLast = Time.now();           // update time to see if car still in wifi control
    
    
    //  Deal with all the turning x = 0 - 319
  
    if (pixy.blocks[0].x < 150){   //object on the left so car should turn right
        digitalWrite(myLeftRight, 1);
        analogWrite(myTurnMotor,  250); 
    }  else {
        
       if (pixy.blocks[0].x > 190){   //object on the right so car should turn left 
         digitalWrite(myLeftRight, 0);
         analogWrite(myTurnMotor,  250); 
        
       }  else {   // object in the middle so just go straight
            analogWrite(myTurnMotor,  0);    
             
           }
  
    }  // end turning  main if
    
   
   // deal with the speed of the rover  width = 0 - 320
   
    if (pixy.blocks[0].width < 30){   //Object is very far away so go faster
   
        digitalWrite(myForward, 1);
        digitalWrite(myBackward, 0);
        analogWrite(myDriveMotor,  250);
   
    } else {    
        
        if (pixy.blocks[0].width > 70){   //Object is very wide so it is too close so stop
        
            analogWrite(myDriveMotor,  0);
        
        }   else {   // object a good distance away go a medium speed 0-250
                    digitalWrite(myForward, 1);
                    digitalWrite(myBackward, 0);
                    analogWrite(myDriveMotor,  100);
           }
        }
          
     
    
    
    
  } // end blocks
}   // end loop














