#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#define PinDROITE_avant 6  // fait avancer le côté droit
#define PinDROITE_recule 7 // fait reculer le côté droit
#define PinGAUCHE_avant 8  // fait avancer le côté gauche
#define PinGAUCHE_recule 9 // fait reculer le côté gauche

#include "Arduino.h"

class Deplacement   /// Definition de ma classe Clignotement
{

private:
    unsigned long ;
    char etat;

public:
    void deplacement();                     ///Fonction pour se deplacer 
    void avant();                           ///Fonction pour avancer 
    void droite();                          ///Fonction pour aller à droite             
    void gauche();                          ///Fonction pour aller à gauche 
    void arriere();                         ///Fonction pour reculer 
    void stop_moteur();                     ///Fonction pour arreter les moteurs 
    void passerunobstacle();                ///Fonction pour passer un obstacle pas trop haut grâce au rocker bogie si trop haut alors contourner

};

#endif