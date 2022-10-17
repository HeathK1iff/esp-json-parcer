
#include <EspJsonParcer.h>

char* JSON_TEXT = "{\"device\":\"esp32\", \"sensors\":[{\"id\": \"temp\", \"value\": 10.4}, {\"id\": \"hum\", \"value\": 88}], alarm: 1}";

void printSensor0(EspJsonParcer *parcer){
  char bufId[50];
  if (parcer->getValue("sensors[0].id", bufId)){
         Serial.print("Id:");
         Serial.println(bufId);
         Serial.print("value:");
         Serial.println(parcer->getFloatValue("sensors[0].value"));
  }
}

void printSensor1(EspJsonParcer *parcer){
  char bufId[50];
  if (parcer->getValue("sensors[1].id", bufId)){
         Serial.print("Id:");
         Serial.println(bufId);
         Serial.print("value:");
         Serial.println(parcer->getFloatValue("sensors[1].value"));
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.println("Init");
  EspJsonParcer *parcer = new EspJsonParcer(JSON_TEXT);
  if (parcer->parce()){
      char bufDeviceName[50];
      if (parcer->getValue("device", bufDeviceName)){
         Serial.print("Device=");
         Serial.println(bufDeviceName);
      }
  
      printSensor0(parcer);
      printSensor1(parcer);

      Serial.print("Alarm=");
      Serial.println(parcer->getIntValue("alarm"));
  }
  delete parcer;
}

void loop()
{


}