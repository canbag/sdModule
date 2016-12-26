

#include <sdModule.h>
 
#define PIN_SDPIN  10

int x = 0;

sdModule logging = sdModule(PIN_SDPIN);

void setup()
{
  Serial.begin(9600);
  Serial.println("started!");
  Serial.flush();
  
  logging.setTourLimit(100);
  logging.setFileSizeLimit(5);
  logging.setErrorPin(5);  
  logging.init();
  
  logging.addInfo("MISSION DATE","07.07.07 00:00");
  logging.addInfo("TEAM","ECOSPACE");
  logging.addInfo("PROJECT","HAB_001");
}
void loop() {
      x = x + 1;
      logging.add(String(x)+" is added!"); 
      //delay(1);               
}












