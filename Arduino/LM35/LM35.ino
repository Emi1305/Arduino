void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = 0;
  for(int i = 10;i;i--);{
    temp += map(analogRead(A0), 0, 1023,0,4990);
  }
  temp = temp/10;
  Serial.println(temp);
  analogWrite(A1, (int)temp * 4);
  //Serial.print("Se envio: ");
  //Serial.println(map((int)temp,0,150,0,1023));
}
