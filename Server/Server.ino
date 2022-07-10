// (Send and Receive)

#define M0 11
#define M1 10

void setup() {
   Serial.begin(9600);
   pinMode(M0, OUTPUT);
   pinMode(M1, OUTPUT);

   //Set M0 and M1 to high for parameter setting
   digitalWrite(M0, HIGH);
   digitalWrite(M1, HIGH);

   Serial2.begin(9600);
   while (Serial2.available() && Serial2.read());

   //Send configuration commands to the module
   uint8_t config_struct[6];
   config_struct[0] = 0xC0; //Store in internal flash
   config_struct[1] = 0x00; // Address High, set a different value on the receiving side
   config_struct[2] = 0x00; //Address Low
   config_struct[3] = 0x35; //8N1, 57600 Baud rate, 19.2 kbps Air data rate
//   config_struct[4] = 0x17; //433 MHz
config_struct[4] = 0x00; //410 MHz
   config_struct[5] = 0x44; //Default Options

   Serial2.write(config_struct,6);
   delay(2000);

   Serial.println("Configuration Complete.");
   digitalWrite(M0, LOW);
   digitalWrite(M1, LOW);
   Serial2.begin(57600);

}

void loop() {
   if(Serial.available() > 0){
       char input = Serial.read();
      Serial2.print(input);
   }
   if(Serial2.available() > 0){
       char input = Serial2.read();
      Serial.print(input);
   }
}
