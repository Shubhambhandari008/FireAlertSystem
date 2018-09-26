#include<SoftwareSerial.h>
int Smoke=A0;
int PIR=7;
int Temp=A1;
int Moto1=5;
int Moto2=4;
int Buzzer=6;
int sensorThres = 200;

SoftwareSerial mySerial(2,3); 

void setup()
{
  mySerial.begin(9600);
  pinMode(Smoke,INPUT);
  pinMode(PIR,INPUT);
  pinMode(Temp,INPUT);
  pinMode(Moto1, OUTPUT);
  pinMode(Moto2,OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
  delay(100);
}

void loop()
{
  int Smokreadn=analogRead(Smoke);                //analog read Smoke
  
  float mv,cel;

         Serial.println("Smoke Percentage is= ");
         Serial.println(Smokreadn);
         delay(1000);

       if (Smokreadn> sensorThres)             // SMOKE SensorChecks if it has reached the threshold value
       {
         int Tmpreadn= analogRead(Temp);                 //temp analog read
           mv=(Tmpreadn/1024.0)*5000;
           cel=mv/10;
         Serial.println("TEMPRATURE in CELCUIS= ");
         Serial.println(cel);
         delay(1000);

            if (cel >45)
      {
        digitalWrite(Moto2,HIGH);
        digitalWrite(Moto1,LOW);
          delay(1000);
        digitalWrite(Buzzer,HIGH);
         delay(1000);
       int Pirreadn= digitalRead(PIR);                  //Digital read PIR
       if(Pirreadn==HIGH)
       {
               gsmsg();
             delay(1000);
        }
        else
       {
              gsmsg1();
          delay(1000);
        }
        
      } 
      
  } 
     else  if(Smokreadn<sensorThres && cel<40)
     { 
      
       delay(1000);
       digitalWrite(Buzzer,LOW);
          delay(100);
         digitalWrite(Moto1,LOW);
          delay(100);                       
        digitalWrite(Moto2,LOW);
          delay(100);
     }
          if (mySerial.available()>0)
    {
        Serial.write(mySerial.read());
     }
}
void gsmsg()
{
    mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
   delay(1000);  // Delay of 1000 milli seconds or 1 second
   mySerial.println("AT+CMGS=\"+919689689901\r"); // Replace x with mobile number
   delay(1000);
   mySerial.println("WARNING!!FIRE HUMAN DETECTED call \nAMBULANCE-108\n FIREBRIGADE-101");// The SMS text you want to send
   delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
   delay(1000);
}
void gsmsg1()
{
    mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
   delay(1000);  // Delay of 1000 milli seconds or 1 second
   mySerial.println("AT+CMGS=\"+919689689901\"\r"); // Replace x with mobile number
   delay(1000);
   mySerial.println("WARNING!!FIRE NO HUMANDETECTED call \n FIREBRIGADE-101");// The SMS text you want to send
   delay(1000);
   mySerial.println((char)26);// ASCII code of CTRL+Z
   delay(1000);
}
