/*
  Hand heater controller for ATtiny85.

  ATtiny85 board profile:
  Go into Preferences -> Additional Board Manager URLs
  Add:
  https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json

  Then go to Tools -> Board -> Board Manager, update, and add "attiny by David Mellis"

  Arduino IDE settings:
  Board: "ATtiny25/45/85"
  Processor: "ATtiny85"
  Clock: "Internal 8MHz"

  Programmer: USBasp
  Sketch -> Upload Using Programmer
*/
#define BUTTON       0
#define STATUS_LED   1
#define TEMP_SENSOR  2
#define HEATER       3
#define FAN          4

#define OFF 0
#define MID 1
#define FULL 2

byte heater_state = OFF;
byte last_button_state = 0;
uint16_t last_button_press = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(test_output, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(TEMP_SENSOR, INPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(FAN, OUTPUT);

  digitalWrite(STATUS_LED, LOW);
  digitalWrite(HEATER, LOW);
  digitalWrite(FAN, LOW);
}

// the loop function runs over and over again forever
void loop() {
  // Check if the button has just been pressed
  byte button_state = digitalRead(BUTTON);
  if((button_state == HIGH) && (last_button_state == LOW) && (millis() - last_button_press > 100))
  {
    // We've detected a button press. Change state.
    heater_state++;
    if(heater_state >=3) // If we've hit the end state, loop back to the start
    {
      heater_state = 0;
    }
    last_button_press = millis();
  }
  last_button_state = button_state;

  switch(heater_state){
    case 0:
      digitalWrite(STATUS_LED, LOW);
      digitalWrite(HEATER, LOW);
      digitalWrite(FAN, LOW);
      break;
    case 1:
      analogWrite(STATUS_LED, 100);
      digitalWrite(HEATER, HIGH);
      analogWrite(FAN, 175);
      break;
    case 2:
      digitalWrite(STATUS_LED, HIGH);
      digitalWrite(HEATER, HIGH);
      digitalWrite(FAN, HIGH);
      break;
  }
  
  /* digitalWrite(test_output, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(test_output, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  */
}
