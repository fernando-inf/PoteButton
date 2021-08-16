//Fuente Original: https://www.programmingelectronics.com/make-one-button-functionality-two-arduino/
//Adaptado por fernando-inf@hotmail.com
//Potenciometro en Pulsador Digital= Al apretar y soltar rápido el Valor de la Variable (Velocity) se incrementa.
                                   //Al apretar 500ms (o mas tiempo) y soltar, el Valor de la Variable decrece.


//#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();

float tiempo_inicial = 0;
int intervalo1 = 5;
int intervalo2 = 500;        
int Velocity = 0; //El valor inicial deberia obtenerse mediante MIDI Input (señal recibida del Software) al seleccionar un preset, en caso de aplicarlo se esa forma borrar "= 0".
const int VelocityMax = 3;
//const int Ch = 1; //Canal MIDI= 1

void PoteButton() 
              {
                  while (digitalRead (2)==LOW){ delay(50); tiempo_inicial = tiempo_inicial + 50;}
                
                  if (tiempo_inicial >= intervalo2)
                            {
                              Velocity--; if (Velocity < 0) Velocity = VelocityMax;
                              //MIDI.sendControlChange(51, Velocity, Ch); //(CC, Valor, Canal)
                              for (int i = 0; i <= 3; i++) {if (Velocity == i) {digitalWrite(i+3, HIGH);}  else {digitalWrite(i+3, LOW);}}
      
                            } 
                  else if(tiempo_inicial >= intervalo1)
                            {
                              Velocity++; if (Velocity > VelocityMax) Velocity = 0;
                              //MIDI.sendControlChange(51, Velocity, Ch);//(CC, Valor, Canal)
                              for (int i = 0; i <= 3; i++) {if (Velocity == i) {digitalWrite(i+3, HIGH);}  else {digitalWrite(i+3, LOW);}}
                            }      
                tiempo_inicial = 0;
              }

void setup() 
              {
                //MIDI.begin(MIDI_CHANNEL_OMNI);//MIDI_CHANNEL_OMNI= Lee los mensajes de todos los Canales, si esta vacio solo lee el Canal 1 en MIDI IN.
                //Serial.begin(115200); // Si conecta directo a MIDI - sin puerto serial: 31250
                pinMode(2, INPUT_PULLUP);//PIN DIGITAL D2 para Pulsador
                for (int i = 3; i <= 6; i++){pinMode(i,OUTPUT);}//PINES DIGITALES para LEDs: D3 a D6
                
              }

void loop() 
              {
                if(Velocity==0){digitalWrite(3, HIGH);}//Inicio
                PoteButton();
              }
