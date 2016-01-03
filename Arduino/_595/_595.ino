int reset = 13;
int oe = 12;
int siguiente = 11;
int shift = 10;
int storage = 9;
int guardar = 4;
int mover = 3;
int entrada = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(reset, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(siguiente, OUTPUT);
  pinMode(shift, OUTPUT);
  pinMode(storage, OUTPUT);
  pinMode(guardar, INPUT);
  pinMode(mover, INPUT);
  pinMode(entrada, INPUT);
  digitalWrite(reset, HIGH);
  digitalWrite(oe, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(storage, digitalRead(guardar));
  digitalWrite(shift, digitalRead(mover));
  digitalWrite(siguiente, digitalRead(entrada)); 
}
