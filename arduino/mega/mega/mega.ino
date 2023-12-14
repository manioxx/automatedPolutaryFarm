#include <DHT11.h>

DHT11 dht11(2);
const int IR = 3;
const int FLAME = 4;
const int BUZZER = 45;
char i;

// Pin configuration for L298N motor driver
const int fanIn1 = 8;   
const int fanIn2 = 7;   

const int lightIn1 = 6; 
const int lightIn2 = 5; 

const int eggIn1 = 9;  
const int eggIn2 = 10;   
const int eggena = 11;   

const int wasteIn1 = 13; 
const int wasteIn2 = 12; 
const int wasteena = 44;  
 
const int heaterIn1 = 40;  
const int heaterIn2 = 41;   

void setup() {  
  Serial.begin(9600);
  pinMode(FLAME, INPUT);
  pinMode(IR, INPUT);
  pinMode(13, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial3.begin(9600);

//fan
  pinMode(fanIn1, OUTPUT);
  pinMode(fanIn2, OUTPUT);
//light
  pinMode(lightIn1, OUTPUT);
  pinMode(lightIn2, OUTPUT);
//egg
  pinMode(eggIn1, OUTPUT);
  pinMode(eggIn2, OUTPUT);
//waste
  pinMode(wasteIn1, OUTPUT);
  pinMode(wasteIn2, OUTPUT);
  //heater
  pinMode(heaterIn1, OUTPUT);
  pinMode(heaterIn2, OUTPUT);

}

void loop() 
{
  sensorsRead();
  if(Serial3.available())
  {
    foodoff();
  }
  if (Serial.available() >= 7)
  {
    // Read the incoming  which is in the form auto eggs  fan food heater light waste
    String receivedString = Serial.readStringUntil('\n');  // assuming '\n' is used as the end marker
    // Convert the String to an array
    char myArray[7];
    // Extract each digit and convert it to an integer
    for (int i = 0; i < 7; i++) 
    {
      myArray[i] = receivedString.charAt(i) - '0';
    }
    // Print the array values
    Serial.print("Array: ");
    for (int j = 0; j < 7; j++) {
      Serial.print(myArray[j]);
      Serial.print(" ");
    }
    Serial.println();

    //egg
    egg(myArray[1]);
    //fan
    fan(myArray[2]);
    //food0.22
    food(myArray[3]);
    //heater
    heater(myArray[4]);
    //light
    light(myArray[5]);
    //waste
    waste(myArray[6]);
  }
}


void sensorsRead() 
{
  // Declare sensorsVal as a String
  String sensorsVal = "";

  // Attempt to read the temperature and humidity values from the DHT11 sensor.
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();
  delay(1200);
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT && humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) 
  {
    // Concatenate temperature and humidity to sensorsVal
    sensorsVal += String(temperature) + ',';
    sensorsVal += String(humidity) + ',';
  }

  // Read Flame and IR values
  int FlameValue = digitalRead(FLAME);
  int IrValue = digitalRead(IR);

  // Concatenate Flame and Ir values to sensorsVal
  sensorsVal += String(FlameValue) + ',';
  sensorsVal += String(IrValue);

  // Print sensorsVal to Serial Monitor
  Serial.println(sensorsVal);
  if(FlameValue ==1)
  {
    digitalWrite(BUZZER,HIGH);
  }
  else
  {
    digitalWrite(BUZZER,LOW);
  }

}

//egg
void egg(int i) 
{
  if (i == 1) 
  {
    Serial.println("Egg management ON");
    eggon();
  } 
  else 
  {
    Serial.println("Egg management OFF");
    eggoff();
  }
}
//waste
void waste(int i) 
{
  if (i == 1) 
  {
    Serial.println("Waste system ON");
    wasteon();
  } 
  else 
  {
    Serial.println("Waste system OFF");
    wasteoff();
  }
}
//fan
void fan(int i) 
{
  if (i == 1) 
  {
    Serial.println("Fan ON");
    fanon();
  }
  else 
  {
    Serial.println("Fan OFF");
    fanoff();
  }
}

//heater
void heater(int i)
 {
  if (i == 1)
  {
    Serial.println("Heater on ON");
    heateron();
  }
  else 
  {
    Serial.println("Heater OFF");
    heateroff();
  }
}

//light
void light(int i) 
{
  if (1 == i)
   {
    Serial.println("light ON");
    digitalWrite(13, HIGH);
    lighton();
  } 
  else 
  {
    Serial.println("light OFF");
    digitalWrite(13, LOW);
    lightoff();
  }
}

//food
void food(int i)
 {
  if (i == 1) 
  {
    foodon();
    Serial.println("food system ON");
  } 
  else 
  {
    foodoff();
    Serial.println("food system OFF");
  }
}

void fanon() 
{
  // Set fan motor direction clockwise
  digitalWrite(fanIn1, LOW);
  digitalWrite(fanIn2, HIGH);
}

void lighton()
 {
  // Set light motor direction clockwise (Note: Actual light brightness control may require additional circuitry)
  digitalWrite(lightIn1, HIGH);
  digitalWrite(lightIn2, LOW);
}

void fanoff() 
{
  // Stop the fan
  digitalWrite(fanIn1, LOW);
  digitalWrite(fanIn2, LOW);
}

void lightoff() 
{
  // Stop the light (Note: Actual light control may require additional circuitry)
  digitalWrite(lightIn1, LOW);
  digitalWrite(lightIn2, LOW);
}

void eggon() 
{
  // Set fan motor direction 
  analogWrite(eggena, 70);
  digitalWrite(eggIn1, HIGH);
  digitalWrite(eggIn2, LOW);
}

void wasteon() 
{
  // Set light motor direction clockwise (Note: Actual light brightness control may require additional circuitry)
  analogWrite(wasteena, 100);
  digitalWrite(wasteIn1, HIGH);
  digitalWrite(wasteIn2, LOW);
}

void eggoff() 
{
  // Stop the fan
  digitalWrite(eggIn1, LOW);
  digitalWrite(eggIn2, LOW);
}

void wasteoff() 
{
  // Stop the light (Note: Actual light control may require additional circuitry)
  digitalWrite(wasteIn1, LOW);
  digitalWrite(wasteIn2, LOW);
}
void foodon()
{
  Serial3.write('1');
}
void foodoff()
{
  
}
void heateron()
{
  digitalWrite(heaterIn1, HIGH);
  digitalWrite(heaterIn2, LOW);

}
void heateroff()
{
  digitalWrite(heaterIn1, LOW);
  digitalWrite(heaterIn2, LOW);

}
//"auto":"0","eggs":"0","fan":"0","food":"0","heater":"0","light":"0","waste":"0"

