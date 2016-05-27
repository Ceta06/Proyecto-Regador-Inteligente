  // Sensor de Humedad

  // Conectamos el sensor de la siguiente forma:
  // GND    -> GND
  // VCC    -> 5V
  // DAT    -> A0



  int PinValve1 = 27;//// select the input pin for the VALVULA 1
  int PinValve2 = 0;//// select the input pin for the VALVULA 2
  int PinB = 5; //// select the input pin for the BOMBA 
  int PinTemp = 40;// select the input pin for the Temperature
  int PinHum1 = 44;// select the input pin for the Sensor humedad 1
  int PinHum2= 48;// select the input pin for the Sensor humedad 1
  int PinLuz = 42; // select the input pin for the LDR
  int PinFLujo = 15; // select the input pin for the Flujo
  int led = 6;
  short int Available_options=5; //variable para establecer las opciones disponibles del arduino
  
  volatile int flow_frequency; // Measures flow sensor pulses
  unsigned int l_hour; // Calculated litres/hour
  unsigned char flowsensor = 2; // Sensor Input                           amarillo
  unsigned long currentTime;
  unsigned long cloopTime;
  String Dato="";
  void flow () // Interrupt function
  {
    flow_frequency++;
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void setup() {
    pinMode(PinValve1, OUTPUT);
    pinMode(PinValve2, OUTPUT);
    pinMode(PinB,OUTPUT);
    pinMode(led,OUTPUT);
    pinMode(flowsensor, INPUT);
    pinMode(PinTemp, INPUT);
    pinMode(PinHum1,INPUT);
    pinMode(PinHum2, INPUT);
    delay(2000);
    digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   // attachInterrupt(0, flow, RISING); // Setup Interrupt
   // sei(); // Enable interrupts
    currentTime = millis();
    cloopTime = currentTime;
                        //Estado Inicial de MEF (todo apagado)
    digitalWrite(PinB, LOW);
    digitalWrite(PinValve1, LOW);
    digitalWrite(PinValve2, LOW);
    digitalWrite(led, LOW);
    Serial1.begin(9600);
  }


  void Abre_Valvula(int pin) {
    digitalWrite(pin, HIGH);   // Aplicamos 5v al interruptor
  }
  void Cierra_Valvula(int pin) {
    digitalWrite(pin, LOW);   // Aplicamos 0v al interruptor
  }

  void Enciende_Bomba(int pin) {
    digitalWrite(pin, HIGH);   // Aplicamos 5v al interruptor
  }
  void Apaga_Bomba(int pin) {
    digitalWrite(pin, LOW);   // Aplicamos 0v al interruptor
  }

  String Intensidad_Luz(int pin) {
  //Serial.println("Welcome to TechPonder LDR Tutorial");
  int sensorValue = 0; // variable to store the value coming from the sensor
  sensorValue = analogRead(pin);
  // if (sensorValue < 880){ //4.29 volts 
  // }
  // delay 10ms to let the ADC recover:
  delay(1);
  // SendData(sensorValue);
  String thisString = String(sensorValue);
    return thisString;
}

String Intensidad_Temp(int pin) { //obtenemos el valor del ADC
  int tempC=0;
  tempC = analogRead(pin); 
  delay(1);
  String thisString = String(tempC);
    return thisString;
    }

float Flujo_Agua(int pin) {
  currentTime = millis();
    // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000))
  {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter

    }
    return l_hour;
  }


  String Humedad(int pin) {
    int Valor=0;
    //Serial.print("Sensor de Humedad valor:");
    Valor = analogRead(pin);
    // //Serial.print(Valor);
    // if (Valor <= 300);
    //   //Serial.println(" Encharcado");
    //   if ((Valor > 300) and (Valor <= 700));
    //     // Serial.println(" Humedo, no regar");
    //     if (Valor > 700);
    //       // Serial.println(" Seco, necesitas regar");
    // delay 10ms to let the ADC recover:
    delay(1);
    // Serial.println("Humedad");
    // Serial.print(Valor);
    String thisString = String(Valor);
    return thisString;
  }



  void blink(){
digitalWrite(led, HIGH);   // Aplicamos 5v al interruptor
delay (5);
digitalWrite(led, LOW);   // Aplicamos 5v al interruptor

}


int ReceiveData(){
  int incomingByte=0;
  blink(); 
 if (Serial.available() > 0) {             
  incomingByte=Serial.parseInt();      
  }
  Serial.flush();
  return incomingByte;
}


void SendData(String dato){
  Serial1.println(dato);//enviamos un byte
  blink();  
}

// int ReceiveData(){
//    while (Serial1.available() > 0) {
//     // look for the next valid integer in the incoming serial stream:
//     int data = Serial1.parseInt();
//     // look for the newline. That's the end of your
//     // sentence:
//     if (Serial1.read() == '\n') {
//     //Serial.println("DATO recibido:"); 
//      // Serial.println(red);
//      return data;
//     }
//   }
//   return 0;
// }

void AdministrarValvulas(){ //funcion para abrir y cerrar valvulas dependiento del valor recibido en el UART
  int option=0;

  option=ReceiveData();
  Serial.println(option);
  switch (option){
    case 1:
    Abre_Valvula(PinValve1);
    break;
    case 2:
    Cierra_Valvula(PinValve1);
    break;
    case 3:
    Abre_Valvula(PinValve2);
    break;
    case 4:
    Cierra_Valvula(PinValve2);
    break;
    default:
    AdministrarValvulas();
    break;
  }

  
}


  ////////////////////////////////main /////////////////////////////////
  void loop() {
 int var=0 ;                                                                                  ;
  var=ReceiveData();
  if (var<Available_options || var==0){
    switch (var) {
    case 1://Abre valvula 1
    AdministrarValvulas();
    break;
      case 2://'5'://Sensar Temperatura
      SendData(Humedad(PinHum1));
      break;
      case 3://'5'://Sensar Temperatura
      SendData(Humedad(PinHum2));
      break;
      case 4://'5'://Sensar Temperatura
      SendData(Intensidad_Luz(PinLuz));
      break;
      case 5://'5'://Sensar Temperatura
      SendData(Intensidad_Temp(PinTemp));
      break;
     // case 9://'5'://Sensar flujo
      //Flujo_Agua(PinFLujo);
      //break;
      default:
      break;
    }

  }else{
      SendData ("551"); //codigo 70 significa seleccion invalida
    }
    

//Solo se envian los datos solicitados
 }





