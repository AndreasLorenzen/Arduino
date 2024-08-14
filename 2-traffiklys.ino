int potPin = A3;   // Potentiometer output connected to analog pin A3
int buttonPin = 2; // Button connected to digital pin 2

int redPin1 = 9;  // Red LED 1, connected to digital pin 11
int yelPin1 = 10;  // Yellow LED 1, connected to digital pin 10
int grnPin1 = 8;   // Green LED 1, connected to digital pin 9

int redPin2 = 3;   // Red LED 2, connected to digital pin 3
int yelPin2 = 5;   // Yellow LED 2, connected to digital pin 5
int grnPin2 = 6;   // Green LED 2, connected to digital pin 6

int currentLightSet = 0;   // Variable to track which light set is currently active (0 or 1)
int currentPhase = 0;      // Variable to track the current phase of the light sequence (0 to 4)
unsigned long phaseStartTime; // Time when the current phase started
const unsigned long phaseDuration = 2000; // Duration for each phase (2 seconds)
bool sequenceStarted = false; // Flag to indicate if the sequence has started

void setup() {
  pinMode(redPin1, OUTPUT);   // Set the LED pins as output
  pinMode(yelPin1, OUTPUT);
  pinMode(grnPin1, OUTPUT);

  pinMode(redPin2, OUTPUT);   // Set the additional LED pins as output
  pinMode(yelPin2, OUTPUT);
  pinMode(grnPin2, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with pull-up resistor

  // Turn off all LEDs initially
  allLedsOff();

  // Initial state: Both sets are red
  digitalWrite(redPin1, HIGH);
  digitalWrite(redPin2, HIGH);

  phaseStartTime = millis(); // Initialize the start time
}

void loop() {
  int buttonState = digitalRead(buttonPin); // Read the button state

  // Check if the button was pressed (LOW state)
  if (buttonState == LOW) {
    sequenceStarted = true; // Start the sequence
  }

  if (sequenceStarted) {
    unsigned long currentTime = millis(); // Current time

    // Check if it's time to change the phase
    if (currentTime - phaseStartTime >= phaseDuration) {
      phaseStartTime = currentTime; // Reset the phase start time

      // Update the phase
      currentPhase = (currentPhase + 1) % 5; // Move to the next phase (0 -> 1 -> 2 -> 3 -> 4 -> 0)

      // Turn off all LEDs in the current set
      if (currentLightSet == 0) {
        // Current set is set 1
        digitalWrite(redPin1, LOW);
        digitalWrite(yelPin1, LOW);
        digitalWrite(grnPin1, LOW);
      } else {
        // Current set is set 2
        digitalWrite(redPin2, LOW);
        digitalWrite(yelPin2, LOW);
        digitalWrite(grnPin2, LOW);
      }

      // Activate the next phase
      if (currentPhase == 0) {
        // Phase 0: Red
        if (currentLightSet == 0) {
          digitalWrite(redPin1, HIGH);
        } else {
          digitalWrite(redPin2, HIGH);
        }
      } else if (currentPhase == 1) {
        // Phase 1: Yellow
        if (currentLightSet == 0) {
          digitalWrite(yelPin1, HIGH);
        } else {
          digitalWrite(yelPin2, HIGH);
        }
      } else if (currentPhase == 2) {
        // Phase 2: Green
        if (currentLightSet == 0) {
          digitalWrite(grnPin1, HIGH);
        } else {
          digitalWrite(grnPin2, HIGH);
        }
      } else if (currentPhase == 3) {
        // Phase 3: Yellow again
        if (currentLightSet == 0) {
          digitalWrite(yelPin1, HIGH);
        } else {
          digitalWrite(yelPin2, HIGH);
        }
      } else if (currentPhase == 4) {
        // Phase 4: Red again
        if (currentLightSet == 0) {
          digitalWrite(redPin1, HIGH);
        } else {
          digitalWrite(redPin2, HIGH);
        }
      }

      // Switch to the other set after completing the sequence
      if (currentPhase == 4) {
        // Complete one cycle for the current light set
        if (currentLightSet == 0) {
          // Set 1 is done, now turn off all LEDs in set 1
          digitalWrite(redPin1, HIGH);
          digitalWrite(yelPin1, LOW);
          digitalWrite(grnPin1, LOW);
          // Set 2 should start its cycle
          currentLightSet = 1;
        } else {
          // Set 2 is done, now turn off all LEDs in set 2
          digitalWrite(redPin2, HIGH);
          digitalWrite(yelPin2, LOW);
          digitalWrite(grnPin2, LOW);
          // Set 1 should start its cycle
          currentLightSet = 0;
        }
        // Reset the phase and wait before starting the other set
        currentPhase = 0;
        delay(phaseDuration); // Wait before switching to the other set
      }
    }
  }
}

// Function to turn off all LEDs
void allLedsOff() {
  digitalWrite(redPin1, LOW);
  digitalWrite(yelPin1, LOW);
  digitalWrite(grnPin1, LOW);

  digitalWrite(redPin2, LOW);
  digitalWrite(yelPin2, LOW);
  digitalWrite(grnPin2, LOW);
}