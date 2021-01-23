/*
 * Test Bluetooth avec le module HC05
 * 
 * LED en Pin 7 du Uno.
 * 
 * Le HC05 en TX=10 et RX=11
 * La Pin EN = 9
 * Pin STATE = Pas connectée. 
 * +5V et Masse.
 *  
 *  Ouvrir le terminal.
 *  
 *  Charger l'Apps : Bluetooth Terminal HC-05 de mightyIT sur votre smartphone.
 *  
 * Sur "Enter ASCII Command" tappez : on ou off, la Led s'allume ou s'eteints.
 * Le resultat apparait dans le terminal.
 * 
 */

#include <SoftwareSerial.h>   // librairie pour creer une nouvelle connexion serie max 9600 baud
#define PIN_LED 7             // Led sur le port 7.

SoftwareSerial BTSerial(10, 11); // BT-TX=10 et BT-RX=11

// Le S E T U P  :
// ==============
void setup()
  {
    Serial.begin(9600);                           // Moniteur série à 9600 Bauds.
    Serial.println("Commande en attente : ");
    BTSerial.begin(9600);                         // BT : HC-05 à 9600 Bauds.

    pinMode(PIN_LED, OUTPUT);                     // LED sur Port 7.
  }

// La B O U C L E  :
// ================
void loop()
  {
    String message;                               // Chaine : message
   
    // Boucle de lecture sur le BT :
    while (BTSerial.available())
      {
        
        // Lecture du message envoyé par le BT
        message = BTSerial.readString();

        // Ecriture du message dans le serial usb
        Serial.print("Etat de la LED = ");
        Serial.println(message);
      }
    
    // Boucle de lecture sur le serial usb
    while (Serial.available())
      {
        // Lecture du message envoyé par le serial usb
        message = Serial.readString();
        // Ecriture du message dans le BT
        Serial.print("Etat de la LED = ");
        BTSerial.print(message);
      }

    // si mon message est egal a "on"  ( + retour chariot et nouvelle ligne )
    if(message == "on\r\n")
      {
        digitalWrite(PIN_LED,HIGH); // led on
      }
    // Si non, le message est egal a "off"
    else if(message == "off\r\n")
      {
        digitalWrite(PIN_LED,LOW);  // led off
      }
  }
  
