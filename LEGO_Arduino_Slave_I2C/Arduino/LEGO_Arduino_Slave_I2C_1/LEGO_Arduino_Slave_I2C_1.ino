#include <Wire.h>

#define SLAVE_ADDRESS 0x0A

typedef union
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

const int nbytes = 4;
const int nreg = 6;
FLOATUNION_t Registers[nreg];

boolean answer = false;

void setup()
{
    Serial.begin(115200); // start serial for output
    Wire1.begin(SLAVE_ADDRESS);
    Wire1.onReceive(receiveData);
    Wire1.onRequest(sendData);
    Serial.println("Ready!");

    for (int i = 0; i < nreg; i++) Registers[i].number = i;
}

void loop(){}

void receiveData(int byteCount)
{
    while (Wire1.available() > 0)
      if(Wire1.read() == 0) answer = true;
}

// callback for sending data
void sendData()
{
  if(answer){
    for (int i = 0; i < nreg; i++) {
      for (int j = 0; j < nbytes; j++){
        Wire1.write(Registers[i].bytes[j]); 
      }  
      Registers[i].number += 0.01;
    }
    
    answer = false;
  }
}
