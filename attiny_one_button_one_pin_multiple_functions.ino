/*Using a Single Button, create mutliple options based on how long the button is pressed
 * Every time you press the button you add one to optionSelected
 * or optionInternalSelected add one.

http://www.technoblogy.com/show?LE0

 
 The circuit:
 * LED attached from pin 0 to ground through a 220 ohm resistor
 * LED attached from pin 1 to ground through a 220 ohm resistor
 * one side of momentary pushbutton attached to pin 2 (pull up in arduino/attiny85)
 * other side of momentary pushbutton attached to Ground (input pull up)
 
 * Note 1: In this circuit, when the button is pressed, Ground Voltage is what will be applied. 
 
 DEC 2014 by Scuba Steve
 Modified JAN 2015 by Michael James
 Both members of https://programmingelectronics.com
 Modified FEB 2022 by Raul Cobos for attiny85-arduino

 
 This code is in the public domain

 *********************************************************************************
 */


/////////Declare and Initialize Variables////////////////////////////

//We need to track how long the momentary pushbutton is held in order to add one to optionSelected or optionSelectedInternal
//This value will be recorded in seconds
float pressLength_milliSeconds = 0;

// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionInternal = 100;
int optionChange = 1000;        

//Count option selected;
int optionSelected;
int optionSelectedInternal;

//The Pin your button is attached to
int buttonPin = 2;

//Pin your LEDs are attached to
int ledPin_Option_1 = 0;
int ledPin_Option_2 = 1;

void setup(){

  // Initialize the pushbutton pin as an input pullup
  // Keep in mind, when pin 2 has ground voltage applied, we know the button is being pressed
  pinMode(buttonPin, INPUT_PULLUP);     

  //set the LEDs pins as outputs
  pinMode(ledPin_Option_1, OUTPUT); 
  pinMode(ledPin_Option_2, OUTPUT); 

  optionSelected=0;
  optionSelectedInternal=0;
                    

} // close setup


void loop() {

  //Record *roughly* the tenths of seconds the button in being held down
  while (digitalRead(buttonPin) == LOW ){ 
      delay(100);  //if you want more resolution, lower this number 
     pressLength_milliSeconds = pressLength_milliSeconds + 100;   
  }//close while


  //Different if-else conditions are triggered based on the length of the button press
  //Start with the longest time option first

  //OptionSelected - Execute the option selected if the button is held for the correct amount of time
  if (pressLength_milliSeconds >= optionChange){
      optionSelected=optionSelected + 1;
      // optionSelectedInternal=0; // You can reset optionSelectedInternal every time you change option
  } 
  //optionSelectedInternal - Execute the internal option if the button is held for the correct amount of time
  else if(pressLength_milliSeconds >= optionInternal){
      optionSelectedInternal= optionSelectedInternal + 1;
   }//close if options

  if(optionSelectedInternal>=5){//reset internal option
     optionSelectedInternal=0;
  }
  // Switch explication.
  // optionSelected make one function or another.
  // Always call "internalFunction()" you can choose what will do
  // last option must resert to 0 optionSelectec and optionSelectedInternal.
  // 
switch (optionSelected) {
  case 0:
    // statements
    break;
  case 1:
     digitalWrite(ledPin_Option_1, HIGH);  
     digitalWrite(ledPin_Option_2, LOW);  
     internalFunction();
    break;
  case 2:
       digitalWrite(ledPin_Option_1, LOW);
      digitalWrite(ledPin_Option_2, HIGH);  
      internalFunction();
    break;
  case 3:
     digitalWrite(ledPin_Option_1, HIGH);  
     digitalWrite(ledPin_Option_2, HIGH);  
     internalFunction();

  break;
  case 4 : //reset all
       optionSelected=0;
       optionSelectedInternal=0;
       digitalWrite(ledPin_Option_1, LOW);  
       digitalWrite(ledPin_Option_2, LOW);  

  default:
  break;
}
  //every time through the loop, we need to reset the pressLength_Seconds counter
  pressLength_milliSeconds = 0;

} // close void loop

void internalFunction(){
  switch (optionSelected) {
  case 0:
    // statements
    break;
  case 1:
     
     for (int i=0; i<optionSelectedInternal; i++) {
      digitalWrite(ledPin_Option_1, HIGH);
      delay(100);
      digitalWrite(ledPin_Option_1, LOW);
    delay(100);
    }
    delay(500);
       

    break;
  case 2:
       for (int i=0; i<optionSelectedInternal; i++) {
      digitalWrite(ledPin_Option_2, HIGH);
      delay(100);
      digitalWrite(ledPin_Option_2, LOW);
      delay(100);
    }
    delay(500);
    break;
  case 3:
     for (int i=0; i<optionSelectedInternal; i++) {
      digitalWrite(ledPin_Option_1, HIGH);
      delay(100);
      digitalWrite(ledPin_Option_2, LOW);
      delay(100);
      digitalWrite(ledPin_Option_2, HIGH);
      delay(100);
      digitalWrite(ledPin_Option_1, LOW);
      delay(100);
     }
     delay(500);
  break;
    

  default:
  break;
}


}
