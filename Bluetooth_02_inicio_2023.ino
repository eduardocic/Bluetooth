#include <SoftwareSerial.h>
 
// -------------------------------------------------------------
// Para configurar os parâmetros que fazem a comunicação com os 
// o módulo HC-05, eu primeiro preciso definir outros dois pinos
// a partir de onde eu irei fazer a transmissão e recepção dos 
// dados via bluetooth. 
//
// Em termos de conexão digital (segue bovinamente), faça:
//
//  POWER ---------- 5V;
//  GND   ---------- GND;
//  TXD   ---------- D2;
//  RXD   ---------- D3; 
// -------------------------------------------------------------
const int pinoRX  = 2; // pino DIGITAL 2, servindo como RX.
const int pinoTX  = 3; // pino DIGITAL 3, servindo como TX.

// Instanciando o bluetooth (podia ser qualquer nome).
SoftwareSerial bluetooth(pinoRX, pinoTX);

// String para receber os parâmetros do PWM.
String inString = "";
int pwm;


// -------------------------------------------------------------
//
//                             SETUP
//
// -------------------------------------------------------------
void setup(){
  // Inicializa o módulo seria (utilizada inicialmente para testes).
  Serial.begin(9600);

  // Um led para visualização de que os parâmetros de modo visual.
  pinMode(LED_BUILTIN, OUTPUT);

  // Inicialização da instância para o bluetooth
  bluetooth.begin(9600);

  // Para estabilização da rede.
  delay(100);
}
 


// -------------------------------------------------------------
//
//                             LOOP
//
// -------------------------------------------------------------
void loop(){

  // Enquanto houver dado disponível....
  // while( bluetooth.available() > 0 ){
  if( bluetooth.available() > 0 ){

    // Leia o dado que chegou
    int inChar = bluetooth.read();

    // Se o dado é um dígito, significa dizer que estamos entrando
    // na pegada da potência. 
    if ( isDigit(inChar) ) {
      inString += (char)inChar;
    }
    if ( inChar == '*' ){
      pwm  = inString.toInt();
      Serial.println(pwm);
      inString = "";
    }



    // Recebendo flags.
    if(inChar == 'a'){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("ON");
    }
    if(inChar == 'b'){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("OFF");
    }
  }
}