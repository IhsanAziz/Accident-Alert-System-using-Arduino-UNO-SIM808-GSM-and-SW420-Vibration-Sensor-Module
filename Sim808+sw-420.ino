#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#define PHONE_NUMBER ""  //Put Your PhoneNumber Here to Get Alert message
//The content of messages sent
#define MESSAGE  "Accident Alert! your car ************ got into an accident! "

#define PIN_TX    10    
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX, PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,
int LED_Pin = 13;
int vibr_Pin = 3;

void setup() {
  pinMode(LED_Pin, OUTPUT);
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  Serial.begin(9600); //init serial 9600
  mySerial.begin(9600);
  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }
  Serial.println("Sim808 init success");

}
void loop() {
  long measurement = TP_init();
  delay(50);
  // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 97000) {
    digitalWrite(LED_Pin, HIGH);
    Serial.println("Start to send message ...");  

    //******** define phone number and text **********
    sim808.sendSMS(PHONE_NUMBER, MESSAGE);  // Sending Message 
  }
  else {
    digitalWrite(LED_Pin, LOW);
  }
}

long TP_init() {
  delay(10);
  long measurement = pulseIn (vibr_Pin, HIGH); //wait for the pin to get HIGH and returns measurement
  return measurement;
}
