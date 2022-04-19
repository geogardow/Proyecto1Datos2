#include <iostream>
#include <fstream>
#include <string>
#include "image.h"
using namespace std;

image::image(){
}

void image::encodeImage(string path){
    ifstream image(path, ios::in | ios::binary);

    while(!image.eof())
    {
        ch = image.get();
        img.push_back(ch);
    }
    image.close();
}


void image::decodeImage(){
    ofstream image("temp.png", ios::out | ios::trunc);
    while (img.size() > 0)
    {
        ch = img.substr(0,1).c_str()[0];
        image.put(ch);
        img = img.substr(1);
    }
    image.clear();
}


