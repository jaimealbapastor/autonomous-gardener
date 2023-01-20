#include "Deplacement.hpp" ///Importation des fichiers

Deplacement dl;         ///abréviation pour pouvoir faire référence au classe lors d'appel de fonction


void setup(){

    /// Configuration de tous les pins de l'Arduino en sortie
    
    pinMode(borne1, OUTPUT);
    pinMode(borne2, OUTPUT);
    pinMode(borne3, OUTPUT);
    pinMode(borne4, OUTPUT);
    pinMode(borne5, OUTPUT);
    pinMode(borne6, OUTPUT);

    Serial.begin(9600);     /// Démarrage de la communication série
    Serial1.begin(9600);

    pinMode(PinGAUCHE_avant, OUTPUT);
    pinMode(PinGAUCHE_recule, OUTPUT);
    pinMode(PinDROITE_avant, OUTPUT);
    pinMode(PinDROITE_recule, OUTPUT);
}

void loop(){

}