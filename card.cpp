#include "card.h"
#include <string>

card::card(int i, int j, int idPic, int status){
    this->i = i;
    this->j = j;
    this->idPic = idPic;
    this->status = status;
}

void card::print(){
    std::cout<<this->idPic<<" "<<this->img<<" "<<this->status<<std::endl;
}