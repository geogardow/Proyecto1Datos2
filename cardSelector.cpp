#include <string>
#include "card.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include "cardSelector.h"


using namespace std;
fstream file;
struct empty
{
    int i, j, idPic, status;
};

card cardSelector::loadFromFile(int i, int j){
    file.open("cards.txt", ios::in | ios::out | ios::binary);
        file.seekg((i-1)*(4)*sizeof(empty)+(j-1)*sizeof(empty), ios::beg);
        char *buffer = (char*) malloc(sizeof(empty));
        file.read(buffer, sizeof(empty));
        empty* card = (empty*) buffer;
        card newCard = card(card->i,card->j, card->idPic, card->status);
        newCard.getImage(card->idPic);
        newCard.print();
        file.close();
        free(buffer);
        buffer = NULL;
        return newCard;
}

void cardSelector::loadToFile(int i, int j, int idPic, int status){
    empty card;
    card.i = i;
    card.j = j;
    card.idPic = idPic;
    card.status = status;
    file.open("cards.txt", ios::in | ios::out | ios::binary);
    file.seekg(((i-1)*(4)*sizeof(empty)+(j-1)*sizeof(empty)),ios::beg);
    file.write((char*)&card, sizeof(empty));
    file.close();    
}
card cardSelector::getCard(int i, int j){
    int flag = 1;

    for(int n = 0; n<10; n++){
        if (this->vectorCard[n].i == i && this->vectorCard[n].j == j){
            cout<<"Found object in vector: ";
            this->vectorCard[n].print();
            flag = 0;
            cout<<"return object ";
            this->vectorCard[n].print();
            return this->vectorCard[n];
        }
    }
    
    cout<<"value of flag "<<flag<<endl;
    if (flag == 1){
    cout<<"Did not find object in vector "<<endl;
    Card card = replace(i,j);
    return card;
    }
}

card cardSelector::replace(int i, int j){
    int n = rand()%10;
    cout<<"Delete position "<<n<<endl;
    cout<<"object deleted ";
    this->vectorCard[n].print();

    int old_i = this->vectorCard[n].i;
    int old_j = this->vectorCard[n].j;
    int old_type = this->vectorCard[n].idPic;
    int old_status = this->vectorCard[n].status;
    loadToFile(old_i, old_j, old_type, old_status);
    this->vectorCard.erase(this->vectorCard.begin()+n);

    card card = loadFromFile(i,j);
    this->vectorCard.push_back(card);
    cout<<"New object is: "<<endl;
    this->vectorCard[9].print();
    cout<<"New vector is: "<<endl;
    this->showVector();
    return card;

}
void cardSelector::createVector(){
    for(int i = 1 ; i <= 2; i++){
        for(int j = 1; j<=5; j++){
            this->vectorCard.push_back(loadFromFile(i,j));
        }
    }
}
void cardSelector::showVector(){
    for(int n = 0; n < 10; n++){
        this->vectorCard[n].print();
    }
}
void cardSelector::createFile(){
    int n = 1;
    for (int i = 1; i <= 6; i++){
        for (int j = 1; j<=5; j++){
            if (n > 3){
                n = 1;
                loadToFile(i,j,n,0);
                n+=1;
            }else{
                loadToFile(i,j,n,0);
                n+=1;
            } 
        }
    }  
}