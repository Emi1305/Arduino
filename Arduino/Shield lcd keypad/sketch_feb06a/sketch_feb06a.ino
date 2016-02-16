#include <DHT.h>
#include <LiquidCrystal.h>
#include <stdint.h>


#define botonDerecha(x) x<50
#define botonArriba(x) x<250
#define botonAbajo(x) x<450
#define botonIzquierda(x) x<650
#define botonSelect(x) x<850
#define leerTemperatura() map(analogRead(termometro), 0, 1023, 0, 500)
#define leerHumedadEnTierra() map(analogRead(sensorHumedadEnTierra), 0, 1023, 0, 4990)

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int const lcdKeys = A0;

int const termometro = A5;
int const sensorHumedad = A4;
int const sensorHumedadEnTierra = A3;

DHT dht(sensorHumedad, DHT11);

float temperatura;
float humedad;
float humedadEnTierra;

uint8_t funcionalidadElegida = 0;

unsigned long ultimaLectura = 0;
unsigned long delayLecturas = 500;

enum Boton{
  None,
  Arriba,
  Abajo,
  Izquierda,
  Derecha,
  Select
  
};

//@NAME:leerBotones
//@DESC: Indica que boton se presiono en el keypad
Boton leerBotones();

//@NAME:calcularTemperatura
//@DESC: Devuelve la temperatura medida por el termometro
float calcularTemperatura();

//@NAME: mostrarTemperatura
//@DESC: Muestra la temperatura en el display
void mostrarTemperatura();


//@NAME: mostrarHumedad
//@DESC: Muestra la humedad en el display
void mostrarHumedad();

//@NAME: mostrarHumedadEnTierra
//@DESC: Muestra la humedad de la tierra en el display
void mostrarHumedadEnTierra();

uint8_t const cantidadFuncionalidades = 3;

typedef void (*Funcionalidad)(void);

Funcionalidad funcionalidades[] = { mostrarTemperatura, mostrarHumedad, mostrarHumedadEnTierra };

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Ready");
//  Serial.begin(9600);
//  Serial.println("Fin setup");
  pinMode(termometro, INPUT);
  dht.begin();
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  Boton boton = leerBotones();
  if(boton != None) lcd.clear();
  
  if(boton == Derecha){
    ++funcionalidadElegida;
  }
  if(boton == Izquierda){
    --funcionalidadElegida;
  }
  funcionalidadElegida = funcionalidadElegida % cantidadFuncionalidades;
  Funcionalidad funcion = funcionalidades[funcionalidadElegida];
  funcion();
}

Boton leerBotones(){
  int key = analogRead(lcdKeys);
  if(botonDerecha(key)) return Derecha;
  if(botonArriba(key)) return Arriba;
  if(botonAbajo(key)) return Abajo;
  if(botonIzquierda(key)) return Izquierda;
  if(botonSelect(key)) return Select;
  return None;
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

void mostrarTemperatura(){
  temperatura = calcularTemperatura();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(0,1);
  lcd.print(temperatura);
}


float calcularHumedad(){
  if(millis()-ultimaLectura < delayLecturas){
    return humedad;
  }
  float hum = 0;
//  Serial.print("Temperaturas parciales: ");
  for(int i = 10; i; --i){
    hum += leerHumedad();
  }
  ultimaLectura = millis();
  return hum/10;
}



void mostrarHumedad(){
  //humedad = calcularHumedad();
  humedad = dht.readHumidity();
  lcd.setCursor(0,0);
  lcd.print("Humedad:");
  lcd.setCursor(0,1);
  lcd.print(humedad);
  lcd.setCursor(5,1);
  lcd.print("%");
}


float calcularHumedadEnTierra(){
  if(millis()-ultimaLectura < delayLecturas){
    return humedadEnTierra;
  }
  float hum = 0;
//  Serial.print("Temperaturas parciales: ");
  for(int i = 10; i; --i){
    hum += leerHumedadEnTierra();
  }
  ultimaLectura = millis();
  return hum/10;
}

void mostrarHumedadEnTierra(){
  humedadEnTierra = calcularHumedadEnTierra();
  lcd.setCursor(0,0);
  lcd.print("Hum. En Tierra:");
  lcd.setCursor(0,1);
  lcd.print(humedadEnTierra);
  lcd.setCursor(5,1);
  lcd.print("%");
}

