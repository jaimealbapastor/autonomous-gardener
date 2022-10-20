#ifndef STDINT_H
#define STDINT_H
#include <stdint.h>
#endif

#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H

class morseTranslator
{
private:
    const uint8_t morseLength = 6;
    const char blankSpace = '0';
    char dic[127][6];

    void addMorseToDic(char c, const char morse[]);

public:
    morseTranslator();
    ~morseTranslator();

    /**
     * @brief translates text into morse code
     * 
     * @param text the sentence to translate
     * @return char* containing the char list representing morse
     */
    char* translate(const char text[]);
    

};
#endif
