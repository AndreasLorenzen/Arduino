// Pin Definitions
const int buttonPinStart = 2;  // Start button pin
const int buttonPinReset = 11; // Reset button pin
const int redPin1 = 9;         // Red LED 1
const int yelPin1 = 10;        // Yellow LED 1
const int grnPin1 = 8;         // Green LED 1

const int redPin2 = 3;         // Red LED 2
const int yelPin2 = 5;         // Yellow LED 2
const int grnPin2 = 6;         // Green LED 2

// Timing Variables
const unsigned long phaseDuration = 2000;        // Duration for each phase (2 seconds)
const unsigned long shortPhaseDuration = 200;    // Shorter duration for the transition (0.5 seconds)

bool lightsOn = false;        // Variable to track the state of the lights (on or off)
bool lastButtonStateStart = HIGH;  // Variable to store the last button state for start button
bool lastButtonStateReset = HIGH;  // Variable to store the last button state for reset button
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeReset = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  // Configure LED pins as outputs
  pinMode(redPin1, OUTPUT);
  pinMode(yelPin1, OUTPUT);
  pinMode(grnPin1, OUTPUT);

  pinMode(redPin2, OUTPUT);
  pinMode(yelPin2, OUTPUT);
  pinMode(grnPin2, OUTPUT);

  // Configure button pins as inputs with pull-up resistors
  pinMode(buttonPinStart, INPUT_PULLUP);  // Start button
  pinMode(buttonPinReset, INPUT_PULLUP);  // Reset button

  // Initial state: All lights off except red
  resetProgram();  // Set initial state
}

void loop() {
  // Check buttons initially to handle any immediate button presses
  checkButtons();

  // Execute the light sequence if lights are on
  if (lightsOn) {
    // Light Set 1
    redLight1();          
    Checkwhilewaiting(phaseDuration);
    redYellowLight1();    
    Checkwhilewaiting(phaseDuration);
    greenLight1();        
    Checkwhilewaiting(phaseDuration);
    yellowLight1();       
    Checkwhilewaiting(phaseDuration);
    redLight1();          
    Checkwhilewaiting(shortPhaseDuration);

    // Light Set 2
    redLight2();          
    Checkwhilewaiting(phaseDuration);
    redYellowLight2();    
    Checkwhilewaiting(phaseDuration);
    greenLight2();        
    Checkwhilewaiting(phaseDuration);
    yellowLight2();       
    Checkwhilewaiting(phaseDuration);
    redLight2();          
    Checkwhilewaiting(shortPhaseDuration);
  } else {
    // If the lights are off, keep all LEDs off except red
    allLedsOffExceptRed();
  }
}

// Function to delay with button checks
void Checkwhilewaiting(unsigned long duration) {
  unsigned long startTime = millis();  // Record the start time
  while (millis() - startTime < duration) {
    // Check button states periodically

    checkButtons();
  }
}

// Function to check the state of buttons
void checkButtons() {
  int buttonStateStart = digitalRead(buttonPinStart);  // Read start button state
  int buttonStateReset = digitalRead(buttonPinReset);  // Read reset button state

  // Debounce logic for start button
  if (buttonStateStart == LOW && lastButtonStateStart == HIGH && (millis() - lastDebounceTimeStart) > debounceDelay) {
    lightsOn = !lightsOn;  // Toggle the lights on or off
    lastDebounceTimeStart = millis();  // Update debounce time
    Serial.print("Lights On: ");
    Serial.println(lightsOn);
  }
  lastButtonStateStart = buttonStateStart;  // Update last state of start button

  // Debounce logic for reset button
  if (buttonStateReset == LOW && lastButtonStateReset == HIGH && (millis() - lastDebounceTimeReset) > debounceDelay) {
    resetProgram();  // Call reset function to restore the original state
    lastDebounceTimeReset = millis();  // Update debounce time
    Serial.println("Program reset");
  }
  lastButtonStateReset = buttonStateReset;  // Update last state of reset button
}

// Functions to control LEDs for Light Set 1
void redLight1() {
  digitalWrite(redPin1, HIGH);  // Red on
  digitalWrite(yelPin1, LOW);   // Yellow off
  digitalWrite(grnPin1, LOW);   // Green off
}

void redYellowLight1() {
  digitalWrite(redPin1, HIGH);  // Red on
  digitalWrite(yelPin1, HIGH);  // Yellow on
  digitalWrite(grnPin1, LOW);   // Green off
}

void greenLight1() {
  digitalWrite(redPin1, LOW);   // Red off
  digitalWrite(yelPin1, LOW);   // Yellow off
  digitalWrite(grnPin1, HIGH);  // Green on
}

void yellowLight1() {
  digitalWrite(redPin1, LOW);   // Red off
  digitalWrite(yelPin1, HIGH);  // Yellow on
  digitalWrite(grnPin1, LOW);   // Green off
}

// Functions to control LEDs for Light Set 2
void redLight2() {
  digitalWrite(redPin2, HIGH);  // Red on
  digitalWrite(yelPin2, LOW);   // Yellow off
  digitalWrite(grnPin2, LOW);   // Green off
}

void redYellowLight2() {
  digitalWrite(redPin2, HIGH);  // Red on
  digitalWrite(yelPin2, HIGH);  // Yellow on
  digitalWrite(grnPin2, LOW);   // Green off
}

void greenLight2() {
  digitalWrite(redPin2, LOW);   // Red off
  digitalWrite(yelPin2, LOW);   // Yellow off
  digitalWrite(grnPin2, HIGH);  // Green on
}

void yellowLight2() {
  digitalWrite(redPin2, LOW);   // Red off
  digitalWrite(yelPin2, HIGH);  // Yellow on
  digitalWrite(grnPin2, LOW);   // Green off
}

// Function to turn off all LEDs except the red ones
void allLedsOffExceptRed() {
  digitalWrite(redPin1, HIGH);  // Red on
  digitalWrite(yelPin1, LOW);   // Yellow off
  digitalWrite(grnPin1, LOW);   // Green off

  digitalWrite(redPin2, HIGH);  // Red on
  digitalWrite(yelPin2, LOW);   // Yellow off
  digitalWrite(grnPin2, LOW);   // Green off
}

// Function to turn off all LEDs completely
void allLedsOff() {
  digitalWrite(redPin1, LOW);
  digitalWrite(yelPin1, LOW);
  digitalWrite(grnPin1, LOW);

  digitalWrite(redPin2, LOW);
  digitalWrite(yelPin2, LOW);
  digitalWrite(grnPin2, LOW);
}

// Function to reset the program to its original state
void resetProgram() {
  lightsOn = false;  // Turn off the light sequence
  allLedsOff();      // Turn off all LEDs
  digitalWrite(redPin1, HIGH);  // Only the red LEDs are on initially
  digitalWrite(redPin2, HIGH);
}
