#include "Deplacement.hpp"

Deplacement::Deplacement(){};   ///Constructeur

void Deplacement::deplacement(){

    etat=(Serial.read());
    
    if (etat=='A'){
        avant();
        Serial.println("Avancer"); 
    }else if (etat=='R'){
        arriere();
        Serial.println("Reculer"); 
    }else if (etat=='G'){
        gauche();
        Serial.println("Gauche"); 
    }else if (etat=='D'){
        droite();
        Serial.println("Droite"); 
    }else if (etat=='S'){
        stop_moteur();
        Serial.println("Stop");
    }
}

void Deplacement::avant(){

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);
    // Configuration de "marche avant" pour un moteur
    digitalWrite(borne3, HIGH); 
    digitalWrite(borne4, LOW);  

    digitalWrite(borne1, HIGH);
    digitalWrite(borne2, LOW);
}

void Deplacement::arriere(){

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);
    // Puis on configure la "marche arrière"
    digitalWrite(borne3, LOW);
    digitalWrite(borne4, HIGH);
    // Puis on configure la "marche arrière"
    digitalWrite(borneIN1, LOW); 
    digitalWrite(borneIN2, HIGH);
}

void Deplacement::gauche(){

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);

    digitalWrite(PinGAUCHE_avant, LOW);
    digitalWrite(PinGAUCHE_recule, HIGH);
    digitalWrite(PinDROITE_avant, HIGH);
    digitalWrite(PinDROITE_recule, LOW);
}

void Deplacement::droite(){

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);

    digitalWrite(PinGAUCHE_avant, HIGH);
    digitalWrite(PinGAUCHE_recule, LOW);
    digitalWrite(PinDROITE_avant, LOW);
    digitalWrite(PinDROITE_recule, HIGH);
}

void Deplacement::stop_moteur(){

    analogWrite(borne1, 0);
    analogWrite(borne2, 0);
}

///en cours: 

void Deplacement::passerunobstacle(){

    ///récuperer l'analyse d'obstacle avec classe au debut du programme
    
    if (obstacle == 1){     /// si l'obstacle est surmontable: entre 1mm et 10 cm de haut
        avancer();          ///alors on peut avancer avec précaution
        if (robot >= 45){  /// si l'inclinaison du robot est trop importante: 45°
            arriere();
            obstacle = 0;   ///alors reculer et considerer cet obstacle comme insurmontable
        }
    }else{
        ///contourner l'obstacle soit droite soit gauche
    }


}