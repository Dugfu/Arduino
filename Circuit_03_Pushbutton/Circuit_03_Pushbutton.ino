/*
  Détection de changement d'état d'un bouton poussoir
  (détection de front)

   La plupart du temps, il n'est pas nécessaire de connaître l'état d'un bouton poussoir
  à tout moment, mais seulement si l'état du bouton poussoir a été modifié. 
  Par exemple, on voudra savoir si un bouton poussoir est passé de l'état BAS à l'état HAUT. 
  Ceci est appelé détection de changement d'état, ou détection de front. 

 Cet exemple montre comment détecter quand un bouton poussoir change d'état. 

 Le montage : 
 * un bouton poussoir connecté entre la broche 2 et le +5V
 * une résistance de 10Kohms entre la broche 2 et le 0V (masse)
 * une LED entre la broche 13et la masse (intégrée à la carte Arduino)

  créé 27 Sep 2005
  modifié 30 Dec 2009
 par Tom Igoe

 Cet exemple est dans le domaine public. 
 Traduction française par X. HINAULT. 

 http://arduino.cc/en/Tutorial/ButtonStateChange

 */

// Les constantes ne changent pas durant le programme.
// Utilisée ici pour définir la numéro de la broche :

const int  buttonPin = 2;     // crée un identifiant pour la broche utilisée avec le bouton poussoir
const int ledPin = 13;       // crée un identifiant pour la broche utilisée avec la LED


// Les variables sont modifiées au cours du programme
int buttonPushCounter = 0;   // variable pour le comptage du nombre d'appuis sur le bouton poussoir
int buttonState = 0;         //Variable pour l'état actuel du bouton poussoir
int lastButtonState = 0;     // Variable pour l'état précédent du bouton poussoir
double speedTime = 1;
double speedCalc = 1000;

void setup() {
  // met la broche en entrée
  pinMode(buttonPin, INPUT);
 // met la broche en sortie
  pinMode(ledPin, OUTPUT);
  // initialise la communication série
  // Attention : utiliser la meme vitesse de communication pour le Terminal Série
  Serial.begin(9600);
}


void loop() {
  // lit l'état actuel du bouton poussoir et le mémorise dans la variable
  buttonState = digitalRead(buttonPin);

  // compare l'état actuel du bouton poussoir à l'état précédent mémorisé
  if (buttonState != lastButtonState) {
    // si l'état du bouton poussoir a changé et est HAUT, on incrémente la variable de comptage
    if (buttonState == HIGH) {
      // si l'état actuel du bouton est HAUT
      // il est passé de BAS  à HAUT
      // buttonPushCounter++;
      speedTime = speedTime/2;
      if (speedTime == 0.0078125000) {
        speedTime = 1;
      }
      // affiche les messages sur le PC
      Serial.println("APPUI"); 
      Serial.print("vitesse:  ");
      Serial.println(speedTime, DEC); // affiche la valeur au format décimal
    }
    else {
      // si le bouton courant est BAS
      // il est passé de HAUT à BAS :
      Serial.println("PAS D'APPUI");
    }

    //mémorise l'état courant du bouton poussoir
    //pour les prochains passages dans la boucle loop
    lastButtonState = buttonState;
  }

  // allume la LED tous les 4 appuis 
  // en utilisant la fonction modulo (symbole %)
  // qui fournit le reste de la division
  // par 4 de la variable de comptage
  // si le reste vaut 0, la variable de comptage
  // est un multiple de 4
  speedCalc = speedTime * 1000;
  digitalWrite(ledPin, HIGH);   // Turn on the LED
  delay(speedCalc);              // Wait for one second
  digitalWrite(ledPin, LOW);    // Turn off the LED  
  delay(speedCalc);  
}
