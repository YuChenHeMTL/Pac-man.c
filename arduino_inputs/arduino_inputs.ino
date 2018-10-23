#define KEY_UP 38
#define KEY_DOWN 40
#define KEY_RIGHT 39
#define KEY_LEFT 37

#define PIN_UP 2
#define PIN_DOWN 3
#define PIN_RIGHT 4
#define PIN_LEFT 5

uint8_t buf[8] = { 0 }; 

int state = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_LEFT, INPUT);

  digitalWrite(PIN_UP, HIGH);
  digitalWrite(PIN_DOWN, HIGH);
  digitalWrite(PIN_RIGHT, HIGH);
  digitalWrite(PIN_LEFT, HIGH);

  delay(200);
}
void loop() 
{
  state = digitalRead(PIN_UP);
  if (state != 1) {
    buf[2] = KEY_UP;    // Up key
    Serial.write(buf, 8); 
    releaseKey();
  } 

  state = digitalRead(PIN_DOWN);
  if (state != 1) {
    buf[2] = KEY_DOWN;   // Down key
    Serial.write(buf, 8); 
    releaseKey();
  } 

  state = digitalRead(PIN_RIGHT);
  if (state != 1) {
    buf[2] = KEY_RIGHT;   // Right key
    Serial.write(buf, 8); 
    releaseKey();
  } 
  
  state = digitalRead(PIN_LEFT);
  if (state != 1) {
    buf[2] = KEY_LEFT;   // Left key
    Serial.write(buf, 8); 
    releaseKey();
  } 
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}
