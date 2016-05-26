
int incomingByte = 0;   // for incoming serial data
int pin = 13;

void setup(){
  Serial.begin(9600);
   pinMode(pin,OUTPUT);
}

void blink(){
digitalWrite(pin, HIGH);   // Aplicamos 5v al interruptor
delay (5);
digitalWrite(pin, LOW);   // Aplicamos 5v al interruptor
}

int prueba2(){

  switch (readSerial()){
    case 4:
    Serial.println("OK");
    break;
    default:
    //loop();//Serial.println("Invalido"); 
    break;
  }
 delay(2000);
}

void loop()
{
  prueba2();
  
}

int readSerial(){
  incomingByte=0;
 if (Serial.available() > 0) {             
  incomingByte=Serial.parseInt();      
  return incomingByte;
  }

  //Serial.flush();
}