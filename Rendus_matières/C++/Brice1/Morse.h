switch (letter)
    {
    case 'a':
        this->morse = ".-";
        break;
    case 'b':
        this->morse = "-...";
        break;
    case 'c':
        this->morse = "-.-.";
        break;
    case 'd':
        this->morse = "-..";
        break;
    case 'e':
        this->morse = ".";
        break;
    case 'f':
        this->morse = "..-.";
        break;
    case 'g':
        this->morse = "--.";
        break;
    case 'h':
        this->morse = "....";
        break;
    case 'i':
        this->morse = "..";
        break;
    case 'j':
        this->morse = ".---";
        break;
    case 'k':
        this->morse = "-.-";
        break;
    case 'l':
        this->morse = ".-..";
        break;
    case 'm':
        this->morse = "--";
        break;
    case 'n':
        this->morse = "-.";
        break;
    case 'o':
        this->morse = "---";
        break;
    case 'p':
        this->morse = ".--.";
        break;
    case 'q':
        this->morse = "--.-";
        break;
    case 'r':
        this->morse = ".-.";
        break;
    case 's':
        this->morse = "...";
        break;
    case 't':
        this->morse = "-";
        break;
    case 'u':
        this->morse = "..-";
        break;
    case 'v':
        this->morse = "...-";
        break;
    case 'w':
        this->morse = ".--";
        break;
    case 'x':
        this->morse = "-..-";
        break;
    case 'y':
        this->morse = "-.--";
        break;
    case 'z':
        this->morse = "--..";
        break;
    case '1':
        this->morse = ".----";
        break;
    case '2':
        this->morse = "..---";
        break;
    case '3':
        this->morse = "...--";
        break;
    case '4':
        this->morse = "....-";
        break;
    case '5':
        this->morse = ".....";
        break;
    case '6':
        this->morse = "-....";
        break;
    case '7':
        this->morse = "--...";


char text[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
std::string morse[36] = {".-","-...","-.-.","-..",".","..-","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};


void tiret(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    
}
 
void point(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    
}

void clignotement(std::string x){
    if (x=="."){
        point();
    
    }else if (x=="-"){
        tiret();
    }
}