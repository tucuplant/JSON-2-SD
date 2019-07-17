
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
bool startDatalog = false;
int lum, hum, wl, temp;
String date, time, datalog="datalog.txt";

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

  if(SD.exists("datalog.txt"))
  SD.remove("datalog.txt");
 
// Borrar un fichero


  
}

void loop() {
	File dataFileWrite = SD.open("datalog.txt", FILE_WRITE);
	File dataFileRead = SD.open("datalog.txt", FILE_READ);

  // make a string for assembling the data to log:
  String dataString = "";
 
  // read three sensors and append to the string:
  if (startDatalog) {
	  //dataString = ",{";

	  if (dataFileRead.seek(dataFileRead.size() - 3) && dataFileRead.read() == 91) {
		  Serial.println("Primer objeto");
		  dataString = "{";
	  }
	  else if (dataFileRead.seek(dataFileRead.size() - 3) &&dataFileRead.read() == 125){
		  Serial.println("otro objeto");
		  dataString = ",{";
  }
	  

	  dataString += "\"date\":\"17/07/2019\"";
	  dataString += "}";
	 
		  
  }
  else {
	dataString= "{\"device\": \"tc-79368\",\"status\" : 200,\"dtl\" :0,\"data\" : [";
	dataString+= "]}";
	
	startDatalog = true;
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
 

  // if the file is available, write to it:
  if (dataFileWrite) {
	
    //dataFileWrite.println(dataString);
	dataFileWrite.seek(dataFileWrite.size() - 4);
	dataFileWrite.println(dataString);
    dataFileWrite.close();

  }
  // if the file isn't open, pop up an error:
  else {
    Serial.print("error opening ");
    Serial.println(datalog);
  }

  delay(2500);
}
