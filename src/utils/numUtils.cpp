#include "utils/numUtils.hpp"

bool isStrDigit(std::string str){
    bool val;
    for(char c : str){
        val = std::isdigit(c);
        if(val == false)
            break;
    }
    return val;
}

bool isEnglishAlphabet(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) != 0;
}
