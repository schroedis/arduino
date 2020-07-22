const int delay_ms = 5;
#define D3 3 // PWM
#define TRIG 7
#define ECHO 4
#define OFFSET 64
#define STEP 32
#define VCONST 58.2
#define MAX_DIST 150.
#define MIN_DIST 10.

int i = 0;
long t_delta = 0;
double dist = 0;
long wait = 0;
char buffer[256] = "\0";
int intensity = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(D3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(115200);
  i = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  t_delta = pulseIn(ECHO, HIGH);
  dist = t_delta/VCONST;
    
  sprintf (buffer, "time: %6d", t_delta);
  Serial.print (buffer);
  sprintf (buffer, ";\t dist: %3d.%01d\n", int(dist), int((dist-int(dist))*10));
  Serial.print (buffer);

  if (dist < MAX_DIST) {
    if (dist < MIN_DIST) {
      analogWrite(D3, 255);
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      wait = 4*(dist-MIN_DIST);
      delay(max(0, wait-(t_delta/1000)));      
      //intensity = 127+int(128-128*(dist-MIN_DIST)/(MAX_DIST-MIN_DIST));
      //Serial.println(intensity);
      analogWrite(D3, intensity);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      analogWrite(D3, 0);
      digitalWrite(LED_BUILTIN, LOW); 
    }
  } else {
    analogWrite(D3, 0);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}
