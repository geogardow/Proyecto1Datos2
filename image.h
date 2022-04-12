#ifndef PROYECTO1DATOS2_IMAGE_H
#define PROYECTO1DATOS2_IMAGE_H
#include <iostream>
#include <fstream>
#include <string>

class image
{
public:
    image();
    char ch;
    std::string img;
    void encodeImage(std::string picture);
    void decodeImage();
};
    
#endif //PROYECTO1DATOS2_IMAGE_H