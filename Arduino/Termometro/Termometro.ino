#define leerTemperatura() map(analogRead(sensor), 0, 1023, 0, 4990)

int prendido = LOW;
int apagado = HIGH;
int digito[] = {A0,A1,A2,A3};
int segmento[] = {4,5,6,7,8,9,10,11};
int sensor = A5;
int temperatura;

unsigned long ultimaLectura = 0;
unsigned long delayLecturas = 500;

int c[7] = { LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW };
int numeros[][7] ={ {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, //0
                   {LOW, LOW, LOW, HIGH, LOW, LOW, HIGH}, //1
                   {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, LOW}, //2
                   {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}, //3
                   {HIGH, HIGH, LOW, HIGH, LOW, LOW, HIGH}, //4
                   {HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH}, //5
                   {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH}, //6
                   {LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH}, //7
                   {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, //8
                   {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH} }; //9

void setup() {
  for(int i = 0; i<4; i++)
    pinMode(digito[i], OUTPUT);
  for(int i = 0; i<8; i++)
    pinMode(segmento[i], OUTPUT);
  Serial.begin(9600);
  pinMode(sensor, INPUT);
}

void loop() {
  
  temperatura = calcularTemperatura();
//  Serial.print("Temperatura: ");
//  Serial.println(temperatura);
  delay(3);
  if (solicitaTemperatura()){
    Serial.println(temperatura);
  }
  for (int dig = 0; dig<4; dig++){
    imprimirNumero((((int)floor(temperatura/(pow(10,2-dig))))%10), dig);    
  }
}

void imprimirNumero(int num, int dig){
//  Serial.print("Digito: ");
//  Serial.print(dig);
//  Serial.print("Numero: ");
//  Serial.println(num);
  if(dig == 3){
    for(int i = 0; i<7; i++){
      digitalWrite(segmento[i], c[i]);  
    }
    digitalWrite(digito[dig], prendido);
    digitalWrite(digito[dig], apagado);
    return;
  }
  for(int i = 0; i<7; i++){
    digitalWrite(segmento[i], numeros[num][i]);
  }
  digitalWrite(segmento[7], dig == 1);
  digitalWrite(digito[dig], prendido);
  digitalWrite(digito[dig], apagado);
}

float calcularTemperatura(){
  if(millis()-ultimaLectura < delayLecturas){
    return temperatura;
  }
  float temp = 0;
//  Serial.print("Temperaturas parciales: ");
  for(int i = 10; i; --i){
    temp += leerTemperatura();
  }
  ultimaLectura = millis();
  return temp/10;
}

bool solicitaTemperatura(){
  
  if( int bytesRecibidos = Serial.available() > 0){
    char* buff = (char*)malloc(bytesRecibidos+1);
    for(int i=0;i<=bytesRecibidos;i++)
      buff[i] = Serial.read();
    return true;
  }
  return false;
}

