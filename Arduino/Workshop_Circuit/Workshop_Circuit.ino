#include "thermistor.h"

#define LED1 13
#define LED2 12
#define LED3 11
#define LDR A0 
#define NTC A1

/**********************************************************
                   Parametros Termistor
**********************************************************/
//aqui estao declaradas as caracteristicas do termistor
//para entender como funciona, consulta o Datasheet
THERMISTOR thermistor(NTC,
                      10000,
                      3950,
                      10000);
uint16_t temp; 


void setup() 
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(NTC, INPUT);

  //inicia comunicacao serial a 2400 bauds
  Serial.begin(2400);

  //acende o LED que indica o funcionamento do sistema
  digitalWrite(LED1, HIGH);
}

/**********************************************************
              SENSOR LDR
**********************************************************/
//Essa rotina identifica a presença de luz, 
//se certo nivel de luz nao eh detectado, um LED se acende para indicar 
void LightRead()
{
  int Read = analogRead(LDR);
  Serial.print("Read: ");
  Serial.println(Read);
  if (Read < 400) 
  {
    digitalWrite(LED2, HIGH);
  }
  else 
  {
    digitalWrite(LED2, LOW);
  }  
}

/**********************************************************
              SENSOR NTC
**********************************************************/
//Essa rotina le a temperatura 
//se certo valor for atingido ou supera, um LED se acende para indicar
void TemperatureRead() 
{
  temp = thermistor.read();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C");
  if ((int)temp > 315) 
  {
    digitalWrite(LED3, HIGH);
  }
  else
    digitalWrite(LED3, LOW);
}


void loop()
{
  LightRead();
  TemperatureRead();
  delay(200);
}