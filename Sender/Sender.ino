#include <SoftwareSerial.h>
#include <dht.h>

SoftwareSerial loraSerial(8,9); //TX, RX

dht DHT;

#define DHT11_PIN 7
#define M0 11
#define M1 10

unsigned long t1= millis();
unsigned long t2= 5000+millis();

const int i1= 2000;
const int i2= 2000;

const int capteur_D = 4;
const int capteur_A = A0;

int val_analogique;

void setup() {
pinMode(capteur_D, INPUT);
pinMode(capteur_A, INPUT);

 Serial.begin(9600);
 
 pinMode(M0, OUTPUT);
 pinMode(M1, OUTPUT);

 digitalWrite(M0, HIGH);
 digitalWrite(M1, HIGH);

 loraSerial.begin(9600);
 while (loraSerial.available() && loraSerial.read());

 uint8_t config_struct[6];
 config_struct[0] = 0xC0; //Store in internal flash
 config_struct[1] = 0x00; // Address High, set a different value on the receiving side
 config_struct[2] = 0x00; //Address Low
 config_struct[3] = 0x35; //8N1, 57600 Baud rate, 19.2 kbps Air data rate
 //   config_struct[4] = 0x17; //433 MHz
config_struct[4] = 0x00; //410 MHz
 config_struct[5] = 0x44; //Default Options

 loraSerial.write(config_struct,6);
 delay(2000);

 Serial.println("Config Complete");
 digitalWrite(M0, LOW);
 digitalWrite(M1, LOW);
 loraSerial.begin(57600);

}

void loop() {
unsigned long cu = millis();
if (cu-t1>i1)
{
rainSensor();
//    loraSerial.print("Analog value : ");
//    loraSerial.println(val_analogique);
//    loraSerial.println("");
Serial.println(cu-t1);
loraSerial.println(cu-t1);
    t1=cu;
}

if (cu-t2>=i2)
{
  DHT11();
//  loraSerial.print("Temperature = ");
//  loraSerial.print(DHT.temperature);
//  loraSerial.print("");
//  loraSerial.print("d");
//  loraSerial.print("Humidity = ");
//  loraSerial.print(DHT.humidity);
//  loraSerial.print("");
  loraSerial.println(cu-t2);
//  loraSerial.print("");
//  loraSerial.print("d");
//  loraSerial.println("");
Serial.println(cu-t2);
loraSerial.println(cu-t2);
  t2=cu;
  }
    char input = Serial.read();

 if(loraSerial.available() > 0){
    char input = loraSerial.read();
 }
}

void rainSensor(){
  if(digitalRead(capteur_D) == LOW) 
  {
    loraSerial.print(1);
    loraSerial.print("");
//    loraSerial.print("d"); 
    Serial.println(1); 
  }
else
  {
    loraSerial.print(0);
//    loraSerial.print("d");
    Serial.println(0);
  }
//val_analogique=analogRead(capteur_A); 
// Serial.print("Analog value : ");
// Serial.println(val_analogique); 
// Serial.println("");
  }

void DHT11()
{
int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Serial.println();

}
