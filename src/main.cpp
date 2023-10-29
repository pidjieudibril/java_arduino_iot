/*
  Titre      : lecture d'une temperature avec un TMP36
  Auteur     : Pidjieu dibril
  Date       : 14/10/2023
  Description: Démonstration de l'utilisation d'une broche analogue en entrée pour la lecture du TMP36
  Version    : 0.0.1
*/

#include <Arduino.h>


//#include <Arduino.h>
#define LED_BLEU 7
#define LED_ROUGE 6

//---------------------declaration des constantes------------------------------------ 

const int analogPin         = A1;       //Utilisation de la broche A1 pour lecture analogue(constante de base pour la lecture de lasortie du TMP36 a partir d'une broche digitale)
//constante pour obtenir une valeur de tension a partir du résultat du convertisseur analogique digitale CAD, de 0 à 1023 en 0 à 3.3V
const float pinBaseVoltage  = 3.3;      //Tension de base maximale pour la broche analogue du uC utilisé
const int pinAnalogMaxValue = 1023;     //Valeur maximale de la lecture de la broche analogue
//constante pour obtenir une mesure de température endegré Celcius a partir d'une valeur en V pour le TMP36
const float tensionDecalage = 500;      //tension de décalage pour le TMP36 en mV
const int msDelai           = 2000;     //nombre de milliseconde de délais(Variable de controle générales tel les délais, etc...)

//---------------------declaration des variables---------------------------------------

int analogValue        = 0;             //Variable pour contenir la valeur lue de la broche analogue(variable de base pour la lecture de la sortie du TMP36 a partir d'une broche digitale)
//variable pour obtenir une valeur de tension a partir du résultat du convertisseur analogique digitale CAD, de 0 à 1023 en 0 à 3.3V
float pinVoltage       = 0;             //Variable pour la transformation de la lecture analogue a une tension
//Variables pour obtenir une mesure de température endegré Celcius a partir d'une valeur en V pour le TMP36
float tmp36Temperature = 0;             //Varaiable pour contenir la temperature
int mVParDegreeCelcius = 10;            //Nombre de mV par degré Celcius
float statutChauffage = 0;
float statutClimatisation = 0;
float etatMaison = 25;


//-------------


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         //activation du port série pour affichage dans le moniteur série

  //// pinMode prend deux valeur la valeur de la broche et le mode de (sortir ou entree) de la broche
  pinMode(analogPin,INPUT);   //Pour une bonne lecture, la broche analogique doit être placé en mode entré explicitment
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(analogPin);                  // lecture de la broche analogue et sauvegarde de valeur
   /*
  Par défaut, sur le Arduino MKR1000, la lecture d'une broche analogue donneras une valeur de 0 a 1023.
  Nous pouvons alors utilisé la règle de 3 pour obtenir la tension lu par la broche analogue
  c'est-à-dire, sachant qu'une lecture de 1023 est égale a 3.3V, par regle de 3,
  la tension sera donnè par Tension = (lecture *3.3)/1023
  */
  pinVoltage = (analogValue*pinBaseVoltage)/pinAnalogMaxValue;     //Transfert de la lecture de la broche en tension
   /*
  Calcul de la temnpérature a partir de la tension de lecture en Volts
  1. transfert de la valeur de tension de Volts en mV en multipliant la tension obtenue en lecture par 1000
  2. Soustraction de 500 mV comme facteur de correction
  3. Le tout divisé par 10 mV par degré Celcius pour obtenir des degré Celcius
  */
  tmp36Temperature = (pinVoltage*1000 - tensionDecalage)/mVParDegreeCelcius;


    
  Serial.print("temp : t");
  
  Serial.println(tmp36Temperature);


                         // Envoie du message via le protocole MQTT 


  delay(msDelai);   //délai de sorte a ce qu'on puisse lire les valeurs et ralentir le uC
                    // Note: l'utilisation d'un délai est généralement une mauvaise pratique mais utilisable dans le cas de ce démo
}