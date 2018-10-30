//steps to DFU arduino
//
//Reset Arduino with onboard pins
//Plug cycle the Arduino
//Flash Arduino-usbserial.hex bootloader with dfu-programmer (erase/flash/reset)
//Plug cycle the Arduino
//Flash firmware sketch using Arduino IDE
//Plug cycle the Arduino
//Flash Arduino-keyboard-0.3.hex bootloader with dfu-programmer (erase/flash/reset)
//Test and repeat

#define KEY_W 26
#define KEY_S 22
#define KEY_D 7
#define KEY_A 4

#define PIN_UP 4
#define PIN_DOWN 3
#define PIN_RIGHT 2
#define PIN_LEFT 5

uint8_t buf[8] = { 0 }; 

int state = 1;

void setup() {
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);

  //internal pull up (set the state to 1)
  digitalWrite(PIN_UP, HIGH);
  digitalWrite(PIN_DOWN, HIGH);
  digitalWrite(PIN_RIGHT, HIGH);
  digitalWrite(PIN_LEFT, HIGH);

  Serial.begin(9600);
  delay(200);
}
void loop() 
{
  state = digitalRead(PIN_UP);
  if (state != 1) {
    buf[2] = KEY_W;    // Up key
    delay(150);
    Serial.write(buf, 8); 
    releaseKey();
  } 

  state = digitalRead(PIN_DOWN);
  if (state != 1) {
    buf[2] = KEY_S;  //  Down key
    delay(150);
    Serial.write(buf, 8); 
    releaseKey();
  } 

  state = digitalRead(PIN_RIGHT);
  if (state != 1) {
    buf[2] = KEY_D; //   Right key
    delay(150);
    Serial.write(buf, 8); 
    releaseKey();
  } 
  
  state = digitalRead(PIN_LEFT);
  if (state != 1) {
    buf[2] = KEY_A;  //  Left key
    delay(150);
    Serial.write(buf, 8); 
    releaseKey();
  } 
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);  //Release key  
}
