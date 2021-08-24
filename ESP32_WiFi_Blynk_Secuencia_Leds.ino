/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  Note: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 ************************************************************

 Program para encender 4 led en secuencia acendente al apretar un boton,
 el boton no sera en fisico estara en la apicacion movil  Blynk, que nos 
 permite tener una interfaz desde nuesto dispositivo movil y con el
 cual podemos cominicarnos con el ESP32 y mandarle instrucciones; para
 este ejemplo tendrremos el boton en nuestro celular y al apretar el boton 
 de encendido comenzara la secuencia y si soltamos el boton parara la 
 secuencia.
 1000
 0100
 0010
 0001
 En este ejercicio se usara la placa ESP32-CAM y el programador FTD 
 para la pregramacion al ESP32.
 
 
 ************************************************************/

 

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"

//Declaracion de las librerias
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/*************VARIABLES PARA LA CONECCION************/
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6smBxcOndLUYJVSwK6S6t0S5o-S_u4RB";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "INFINITUM2F70_2.4";
char pass[] = "Y3bGsm526t";

/*************VARIABLES PARA LA SECUENCIA DE LEDS************/
int led[] = {12,13,14,15};                    //Pines con los LEDs en el orden que se desean encender
int ton[] = {1000,1000,1000,1000};            //Tiempo de encendido de cada led en milisegundos. {led1,led2,led3,led4,...}
int boton = 2;                                //Pin con el botón/pulsador
long tiempo;                                  //Donde guardaremos el tiempo para comparar
int lengthLED = (sizeof(led)/sizeof(int))-1;  //Sacamos la longitud del vector 'led'. Al devolver el valor en bytes, dividimos por el tamaño en bytes de un int y le restamos 1 para simplificar la lógica
int statusLedPin = 33;                        // Esta variable controla el led de status



void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode (statusLedPin, OUTPUT);     //Se configura el pin como salida

  
  for (int i=0;i<=lengthLED;i++){
    pinMode(led[i],OUTPUT);           //Configuramos los pines con led como salidas
  }
  pinMode(boton,INPUT);        //Configuramos el pin del boton como entrada
  digitalWrite (statusLedPin, HIGH);  // Se comienza con el led apagado

  conectarWifi();                     //Mandar a llamar la funcion para conectar el Wifi
  
}

void loop()
{
  //comenzamos la ejecucion de Blynk
  Blynk.run();

 
  if (digitalRead(boton)){                      //Se revisa el valor del boto, si es 1 entra al ciclo y comienxa a encender los led
    Serial.println("Se preciono el boton, valor");
    digitalWrite(led[0],HIGH);
    for (int i=0;i<=lengthLED;i++){
      tiempo=millis();                         //Guardamos el tiempo actual
      while (millis()-tiempo < ton[i]){        //Si el tiempo actual menos el tiempo guardado anteriomente no es mayor al tiempo de encendido del led actual, hacemos otra comprobacion
      if (!digitalRead(boton)){               //Si hemos soltado el boton
          Serial.println("Se apago el boton");
          for (int i=0;i<=lengthLED;i++){
            digitalWrite(led[i],LOW);          //Apagamos todos los LEDs
          }
          break;                               //Salimos del bucle for
        }
      }
      digitalWrite(led[i],LOW);                //Apagamos el LED actualmente encendido
      Serial.println("Apagando el led: ");
      Serial.println(led[i]);
      if (i!=lengthLED) {
        digitalWrite(led[i+1],HIGH);           //Encendemos el LED siguiente. El if evita que cojamos el valor lengthLED+1, 
        Serial.println("Encendemos el led: ");   //que no existe, ya que el vector es de longitud lengthLED
        Serial.println(led[i+1]);
      } 
    }
  }
 

}

 // Iniciar el WiFi
void conectarWifi(){
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  Blynk.begin(auth, ssid, pass);

}
