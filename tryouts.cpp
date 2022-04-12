#include <iostream>
#include <fstream>
#include <string>
#include "image.cpp"
using namespace std;

int main(){
    image* img = new image();
    //img->encodeImage("star2.png");
    img->decodeImage();
    return 0;
};