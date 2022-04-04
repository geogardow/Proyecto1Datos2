#include "card.h"
#include <string>

card::card(int i, int j, int idPic, int status){
    this->i = i;
    this->j = j;
    this->idPic = idPic;
    this->status = status;
}

void card::getImage(int idPic){
    switch (idPic)
    {
    case 1:
        this->img = "perro.png";
        break;
    case 2:
        this->img = "gato.png";
        break;
    case 3:
        this->img = "vaca.png";
        break;
    default:
        cout<<"Cannot find image"<<endl;
        break;
    }
}
void card::print(){
    std::cout<<this->idPic<<" "<<this->img<<" "<<this->status<<std::endl;
}