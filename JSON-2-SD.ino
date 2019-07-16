
/*
Circuit for mega del tucuplant: (depende de la placa usa un SPI u otro)
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 - 51
 ** MISO - pin 12 - 50
 ** CLK - pin 13 - 52 (SCK)
 ** CS - pin 4 - 53(for MKRZero SD: SDCARD_SS_PIN)
 */
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 53;

void setup() {
DynamicJsonDocument doc(2048);


  Serial.begin(9600);
  while (!Serial) {
    ; //Esto se hace para evitar fallos con USB nativo
  }


  Serial.println("Inicializando cortex prefrontal e hipocampo...");

  // Compribamos que hay tarjeta
  if (!SD.begin(chipSelect)) {
    Serial.println("Fallido, el cerebro no puede memorizar y va a suspender la oposicion");
    // Si no la hay lo dejamos haciendo el ganso en un bucle infinito
    while (1);
  }
  Serial.println("Puedo recordar...MATAR HUMANOS.");

  
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ",";
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
