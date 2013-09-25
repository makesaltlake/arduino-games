const int pinLED = 13;

const int pinLightGreen = 3;
const int pinLightBlue = 4;
const int pinLightRed = 5;

const int pinButtonL = 22;
const int pinButtonM = 21;
const int pinButtonR = 20;

int memorize[100];

void clear_memory() {
  for (int i = 0; i < 100; i++) {
    memorize[i] = 0;
  }
}

int get_pressed_button_id() {
  if (digitalRead(pinButtonL) == HIGH) return 1;
  if (digitalRead(pinButtonM) == HIGH) return 2;
  if (digitalRead(pinButtonR) == HIGH) return 3;
  return 0;
}

void on(int light_id) {
  switch(light_id) {
    case 0: off(); break;
    case 1: digitalWrite(pinLightGreen, HIGH); break;
    case 2: digitalWrite(pinLightBlue, HIGH); break;
    case 3: digitalWrite(pinLightRed, HIGH); break;
  }
}

void off() {
  digitalWrite(pinLightGreen, LOW);
  digitalWrite(pinLightBlue, LOW);
  digitalWrite(pinLightRed, LOW);
}

int random_light() {
  return 1 + random(3); // returns a number between 1 and 3
}

void flash_three_times() {
  off();
  for (int i = 0; i < 3; i++) {
    on(1); on(2); on(3);
    delay(200);
    off();
    delay(200);
  }
  delay(1000);
}

void setup() {
  randomSeed(analogRead(0));

  pinMode(pinLED, OUTPUT);

  pinMode(pinButtonL, INPUT);
  pinMode(pinButtonM, INPUT);
  pinMode(pinButtonR, INPUT);

  pinMode(pinLightGreen, OUTPUT);
  pinMode(pinLightBlue, OUTPUT);
  pinMode(pinLightRed, OUTPUT);
  
  clear_memory();
  
  digitalWrite(pinLED, HIGH);
  delay(500);
  digitalWrite(pinLED, LOW);
}

#define STATE_GENERATE 0
#define STATE_SHOW_LIGHTS 1
#define STATE_READ_BUTTONS 2
#define STATE_WAIT_BUTTON_RELEASE 3

int level_max_so_far = 0;
int level_current = 0;

int state = STATE_GENERATE;
int selected_light_id = 0;

void loop() {
  switch(state) {
    case STATE_GENERATE:
      // For each level, add one more random light to the list
      // of memorized lights:
      memorize[level_max_so_far] = random_light();
      level_max_so_far++;
      level_current = 0;
      state = STATE_SHOW_LIGHTS;
    
    case STATE_SHOW_LIGHTS:
      on(memorize[level_current]);
      delay(750);
      off();
      delay(500);
      
      level_current++;
      if (level_current == level_max_so_far) {
        level_current = 0;
        state = STATE_READ_BUTTONS;
      }
      break;
    
    case STATE_READ_BUTTONS:
      selected_light_id = get_pressed_button_id();
      if (selected_light_id != 0) { // at least one button is pressed
        // Show the corresponding LED to the button that was pressed
        off(); on(selected_light_id); delay(200);
        off(); delay(300);
        if (memorize[level_current] != selected_light_id) {
          // uh oh! they didn't press the right button
          flash_three_times();
          level_current = 0;
          state = STATE_SHOW_LIGHTS;
        } else {
          level_current++;
          if (level_current == level_max_so_far) {
            // Yay! they got the sequence so far
            level_current = 0;
            state = STATE_GENERATE;
          } else {
            state = STATE_WAIT_BUTTON_RELEASE;
          }
        }
      }
      break;

    case STATE_WAIT_BUTTON_RELEASE:
      // Wait for the button to be released
      off();
      delay(100);
      if (get_pressed_button_id() == 0) {
        state = STATE_READ_BUTTONS;
      }
  }  
}
