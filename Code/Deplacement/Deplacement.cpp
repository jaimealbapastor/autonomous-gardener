

void deplacement(){

    etat=(Serial1.read());
    
    if (etat=='H'){
        avant();
        Serial.println("Haut"); 
    }else if (etat=='B'){
        arriere();
        Serial.println("Bas"); 
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

void avant()
{

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);
    // Configuration de "marche avant" pour un moteur
    digitalWrite(borne3, HIGH); 
    digitalWrite(borne4, LOW);  

    // Configuration de "marche avant" pour le moteur
    digitalWrite(borne1, HIGH);
    digitalWrite(borne2, LOW);
}

void arriere()
{

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);
    // Puis on configure la "marche arrière"
    digitalWrite(borne3, LOW);
    digitalWrite(borne4, HIGH);
    // Puis on configure la "marche arrière"
    digitalWrite(borneIN1, LOW); 
    digitalWrite(borneIN2, HIGH);
}

void gauche()
{

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);

    digitalWrite(PinGAUCHE_avant, LOW);
    digitalWrite(PinGAUCHE_recule, HIGH);
    digitalWrite(PinDROITE_avant, HIGH);
    digitalWrite(PinDROITE_recule, LOW);
}

void droite()
{

    analogWrite(borne1, 200);
    analogWrite(borne2, 200);

    digitalWrite(PinGAUCHE_avant, HIGH);
    digitalWrite(PinGAUCHE_recule, LOW);
    digitalWrite(PinDROITE_avant, LOW);
    digitalWrite(PinDROITE_recule, HIGH);
}

void stop_moteur()
{
    analogWrite(borne1, 0);
    analogWrite(borne2, 0);
}

void passerunobstacle(){
    ///récuperer l'analyse d'obstacle avec classe au debut du programme
    /// si l'obstacle est surmontable: entre 1mm et 10 cm de haut
    ///alors on peut avancer avec précaution
    /// si l'inclinaison du robot est trop importante
    ///alors reculer et considerer cet obstacle comme insurmontable
    ///contourner l'obstacle

}