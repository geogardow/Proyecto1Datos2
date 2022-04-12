#include <iostream>
#include <fstream>
#include <string>
#include "image.h"
using namespace std;

image::image(){
}

void image::encodeImage(std::string picture){
    ifstream image(picture, ios::in | ios::binary);

    while(!image.eof())
    {
        ch = image.get();
        img.push_back(ch);
    }
    image.close();
}


void image::decodeImage(){
    ofstream image("temp.png", ios::out | ios::trunc);

    cout<<img<<endl;
    while (img.size() > 0)
    {
        ch = img.substr(0,1).c_str()[0];
        image.put(ch);
        img = img.substr(1);
    }
    image.clear();
}

