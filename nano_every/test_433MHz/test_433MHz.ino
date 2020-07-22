#define TIMESTEP_MS 0.25
//#define MAXN (int)(1000 / 2 / TIMESTEP_MS)
#define MAXN 2000 // ~.5s
#define MAXI 20 // -> 20*6.25µs ~= 0.125ms

int pin = 8;
int level = 0;
int i = 0;
int j = 0;
int first = 0;
int second = 0;
int toggle = 0;
short data[MAXN] = {0};


void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT);
  Serial.begin(57600);
  j = 0;
  toggle = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  first = 0;
  second = 0;
  for (i=0; i<MAXI; ++i) {
    level = digitalRead(pin);
    first += level;
    //delay(TIMESTEP_MS/256.);
  }
  for (i=0; i<MAXI; ++i) {
    level = digitalRead(pin);
    second += level;
    //delay(TIMESTEP_MS/256.);
  }
  //if ((2*first>MAXI) ^ (2*second>MAXI)) toggle++;
  if (abs(first-second) >= MAXI-3) {
    data[j] = 1;
    toggle++;
  } else {
    data[j] = 0;
  }
  
  //Serial.print(level);
  if (j+1 == MAXN) {
    //Serial.println(toggle);
    if (toggle > 80) {
      Serial.println(toggle);
      for (i=0; i<MAXN; ++i) Serial.print(data[i]);      
      Serial.println();
    }
    toggle = 0;
  }
  
  j = (j+1)%MAXN;
}
