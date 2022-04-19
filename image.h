#ifndef PROYECTO1DATOS2_IMAGE_H
#define PROYECTO1DATOS2_IMAGE_H
#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

class image
{
public:
    image();
    char ch;
    string img;
    void encodeImage(string path);
    void decodeImage();
};
    
#endif //PROYECTO1DATOS2_IMAGE_H