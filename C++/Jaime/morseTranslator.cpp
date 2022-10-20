#include "morseTranslator.h"

void morseTranslator::addMorseToDic(char c, const char morse[])
{
    uint8_t length = sizeof(morse) / sizeof(char);
    uint8_t i = 0;
    while (i < morseLength)
    {
        if (i < length)
            dic[c][i] = morse[i];
        else
            dic[c][i] = blankSpace;
        i++;
    }
}

morseTranslator::morseTranslator()
{
    addMorseToDic('a', ".-");
    addMorseToDic('b', "-...");
    addMorseToDic('c', "-.-.");
    addMorseToDic('d', "-..");
    addMorseToDic('e', ".");
    addMorseToDic('f', "..-.");
    addMorseToDic('g', "--.");
    addMorseToDic('h', "....");
    addMorseToDic('i', "..");
    addMorseToDic('j', ".---");
    addMorseToDic('k', "-.-");
    addMorseToDic('l', ".-..");
    addMorseToDic('m', "--");
    addMorseToDic('n', "-.");
    addMorseToDic('o', "---");
    addMorseToDic('p', ".--.");
    addMorseToDic('q', "--.-");
    addMorseToDic('r', ".-.");
    addMorseToDic('s', "...");
    addMorseToDic('t', "-");
    addMorseToDic('u', "..-");
    addMorseToDic('v', "...-");
    addMorseToDic('w', ".--");
    addMorseToDic('x', "-..-");
    addMorseToDic('y', "-.--");
    addMorseToDic('z', "--..");
    addMorseToDic('A', ".-");
    addMorseToDic('B', "-...");
    addMorseToDic('C', "-.-.");
    addMorseToDic('D', "-..");
    addMorseToDic('E', ".");
    addMorseToDic('F', "..-.");
    addMorseToDic('G', "--.");
    addMorseToDic('H', "....");
    addMorseToDic('I', "..");
    addMorseToDic('J', ".---");
    addMorseToDic('K', "-.-");
    addMorseToDic('L', ".-..");
    addMorseToDic('M', "--");
    addMorseToDic('N', "-.");
    addMorseToDic('O', "---");
    addMorseToDic('P', ".--.");
    addMorseToDic('Q', "--.-");
    addMorseToDic('R', ".-.");
    addMorseToDic('S', "...");
    addMorseToDic('T', "-");
    addMorseToDic('U', "..-");
    addMorseToDic('V', "...-");
    addMorseToDic('W', ".--");
    addMorseToDic('X', "-..-");
    addMorseToDic('Y', "-.--");
    addMorseToDic('Z', "--..");
    addMorseToDic('1', ".----");
    addMorseToDic('2', "..---");
    addMorseToDic('3', "...--");
    addMorseToDic('4', "....-");
    addMorseToDic('5', ".....");
    addMorseToDic('6', "-....");
    addMorseToDic('7', "--...");
    addMorseToDic('8', "---..");
    addMorseToDic('9', "----.");
    addMorseToDic('0', "-----");
}

morseTranslator::~morseTranslator()
{
}

char *morseTranslator::translate(const char text[])
{
    uint8_t length = morseLength * sizeof(text) / sizeof(char);
    
}
