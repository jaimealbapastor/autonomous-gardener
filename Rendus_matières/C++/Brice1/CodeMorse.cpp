#include <iostream>
#include "Morse.h"
using namespace std;

int main(){
    char N;
    list L = []
    cout<<"mot";
    cin>>N;
    for(int i=0,i++){
        
    }

}

#include <iostream>
#include <string>
///#include "Morse.h"
using namespace std;

void textversmorse(){
    char text[36] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::string morse[36] = {".-","-...","-.-.","-..",".","..-","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

    std::string phrase;
    int input;
    
    std::cout << "Enter the Text You Wish to Translate into Morse Code.\n";
    std::getline(std::cin,phrase);
    
    cout << "Your Entered Text in Morse Code:\n";
 
    for (int i = 0; i<phrase.length(); ++i){
        for (int counter = 0; counter < 36; counter++){
            if (phrase.at(i) == text[counter]){
                cout << morse[counter];
                clignotement(morse[conteur]);
            }
        }
    }
}

int main(){
    
    textversmorse();
    
}

