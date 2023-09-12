/*Source NPK tutorials 
https://www.youtube.com/watch?v=nGvaAZSIQaA
*/

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(35, 25);  // RX, TX

int SoilMoistValue, SoilMoistPercent, dataConduct, datapH, dataNitrogen, dataPhosphorus, dataPotassium;
float dataSoil, dataTemp;

void setup() {
  Serial.begin(9600);
  mySerial.begin(4800);
}

void loop() {
SensorRead();
    Serial.print("Soil Humidity: ");
    Serial.println(dataSoil);
    Serial.print("Soil Temperature: ");
    Serial.println(dataTemp);
    Serial.print("Soil Conductivity: ");
    Serial.println(dataConduct);
    Serial.print("Soil pH: ");
    Serial.println(datapH);
    Serial.print("Nitrogen: ");
    Serial.println(dataNitrogen);
    Serial.print("Phosphorus: ");
    Serial.println(dataPhosphorus);
    Serial.print("Potassium: ");
    Serial.println(dataPotassium);
    delay (2000);
}

void SensorRead(){
  byte queryData[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
  byte receivedData[19];

  mySerial.write(queryData, sizeof(queryData));  // Send the query data to the NPK sensor
  delay(1000);  // Wait for 1 second

  if (mySerial.available() >= sizeof(receivedData)) {  // Check if there are enough bytes available to read
    mySerial.readBytes(receivedData, sizeof(receivedData));  // Read the received data into the receivedData array

    // Parse and print the received data in decimal format
    unsigned int soilHumidity = (receivedData[3] << 8) | receivedData[4];
    unsigned int soilTemperature = (receivedData[5] << 8) | receivedData[6];
    unsigned int soilConductivity = (receivedData[7] << 8) | receivedData[8];
    unsigned int soilPH = (receivedData[9] << 8) | receivedData[10];
    unsigned int nitrogen = (receivedData[11] << 8) | receivedData[12];
    unsigned int phosphorus = (receivedData[13] << 8) | receivedData[14];
    unsigned int potassium = (receivedData[15] << 8) | receivedData[16];

// Perhitungan hasil kalibrasi sensor
    dataSoil = soilHumidity / 10.0;
    dataTemp = soilTemperature / 10.0;
    dataConduct = soilConductivity;
    datapH = soilPH / 10.0;
    dataNitrogen = nitrogen;
    dataPhosphorus = phosphorus / 2 ;
    dataPotassium = potassium; 

}
}