/*
 * Author: Zhe QU, Huijie LIN, Xuantang XIONG, Mohan
 * Date: 2016-02-07
 * Previous filename: TTN-Mapper-TTNEnschede-V1
 */

 //la consommation 1.5W = 0.3A*5.03V
 //la consommation résuite = 1.1w = 0.22*5v
#include <rn2xx3.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // TX, RX

//create an instance of the rn2xx3 library,
//giving the software serial as port to use
rn2xx3 myLora(mySerial);

// the setup routine runs once when you press reset:
void setup()
{
  //output LED pin
  pinMode(13, OUTPUT);
  led_on();
  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, INPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(57600); //serial port to computer
  mySerial.begin(9600); //serial port to radio
  Serial.println("Startup");

  initialize_radio();

  //transmit a startup message
  myLora.tx("TTN Mapper on TTN Enschede node");

  led_off();
  delay(2000);
  attachInterrupt(0, gestionINT0, RISING);
}

void initialize_radio()
{
  //reset rn2483
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();

  //Autobaud the rn2483 module to 9600. The default would otherwise be 57600.
  myLora.autobaud();

  //check communication with radio
  String hweui = myLora.hweui();
  while(hweui.length() != 16)
  {
    Serial.println("Communication with RN2xx3 unsuccessful. Power cycle the board.");
    Serial.println(hweui);
    delay(10000);
    hweui = myLora.hweui();
  }

  //print out the HWEUI so that we can register it via ttnctl
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.println("RN2xx3 firmware version:");
  Serial.println(myLora.sysver());

  //configure your keys and join the network
  Serial.println("Trying to join TTN");
  bool join_result = false;


  /*
   * ABP: initABP(String addr, String AppSKey, String NwkSKey);
   * Paste the example code from the TTN console here:
   */
  const char *devAddr = "260110AF";
  const char *nwkSKey = "AAC5129D9BF1ADC1189D3A56228AD870";
  const char *appSKey = "ECABFD6C270D637CB9E26EC93FF9CBE3";

  join_result = myLora.initABP(devAddr, appSKey, nwkSKey);

  /*
   * OTAA: initOTAA(String AppEUI, String AppKey);
   * If you are using OTAA, paste the example code from the TTN console here:
   */
 /* const char *appEui = "70B3D57ED0025B12";
  const char *appKey = "EDDFF9E19CE4420D93384AC0DF829530";
  const char *devEui = "0004A30B00E96FE4";
  join_result = myLora.initOTAA(appEui, appKey, devEui);*/


  while(!join_result)
  {
    Serial.println("Unable to join. Are your keys correct, and do you have TTN coverage?");
    delay(60000); //delay a minute before retry
    join_result = myLora.initABP(devAddr, appSKey, nwkSKey);
  }
  Serial.println("Successfully joined TTN");
  }

  float sensor_volt;
  float sensorValue;
  float RS_gas;
  float ratio;
  float previous_sensorValue = 0;
  float R0 = 13.3;
// the loop routine runs over and over again forever:
void loop()
{
    sensorValue = analogRead(0);
    sensor_volt = sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt;
    ratio = RS_gas/R0;
    Serial.print(ratio);
    Serial.print("sensorValue = ");
    Serial.print(sensorValue);
    Serial.print("\n");
    led_off();
    String gas = String(sensor_volt);
    if(abs(sensorValue-previous_sensorValue)>2){
      Serial.println("Send data to TTN");
      myLora.tx(gas);
      led_on();  
    }
    previous_sensorValue = sensorValue;
    if(ratio<5){
      digitalWrite(2,HIGH);
    }
    
    delay(2000);
}

void gestionINT0(){
  Serial.println("Warning!");
  for(int i=0;i<1000;i++){
    digitalWrite(9,HIGH);
    delay(1);
    digitalWrite(9,LOW);
  }
}


void led_on()
{
  digitalWrite(13, 1);
}

void led_off()
{
  digitalWrite(13, 0);
}

