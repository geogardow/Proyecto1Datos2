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
#include "card.h"
#include <ctime>

using namespace std;
fstream file;
struct empty
{
    int i, j, idPic, status;
};

cardSelector::cardSelector(){
    createFile();
    createVector(cardsAvailable/3);
}

card cardSelector::loadFromFile(int i, int j){
    file.open("cards.txt", ios::in | ios::out | ios::binary);
    file.seekg((i-1)*(16)*sizeof(empty)+(j-1)*sizeof(empty), ios::beg);
    char *buffer = (char*) malloc(sizeof(empty));
    file.read(buffer, sizeof(empty));
    empty* emptyCard = (empty*) buffer;
    card newCard = card(emptyCard->i,emptyCard->j, emptyCard->idPic, emptyCard->status);
    file.close();
    free(buffer);
    buffer = NULL;
    return newCard;
}

void cardSelector::loadToFile(int i, int j, int idPic, int status){
    empty emptyCard;
    emptyCard.i = i;
    emptyCard.j = j;
    emptyCard.idPic = idPic;
    emptyCard.status = status;
    file.open("cards.txt", ios::in | ios::out | ios::binary);
    file.seekg(((i-1)*(16)*sizeof(empty)+(j-1)*sizeof(empty)),ios::beg);
    file.write((char*)&emptyCard, sizeof(empty));
    file.close();
}

card cardSelector::getCard(int i, int j){
    this->FLAG = false;
    int actualSize = this->vectorCard.size();
    for(int n = 0; n < actualSize; n++){
        if (this->vectorCard[n].i == i && this->vectorCard[n].j == j){
            this->FLAG = true; //Card found in vector
            return this->vectorCard[n];
        }
    }
    if (FLAG == false){ //Card is not found in vector
        card card = replace(i,j);
        return card;
    }
}

void cardSelector::createFile(){
    srand(time(0));
    FILE* toTest = fopen("toTest.csv", "a");
    vector<int> vect{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    int cardsLeft = this->cardsAvailable;
    int random;
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j<=8; j++){
            random = rand()%cardsLeft;
            int n = vect[random];
            loadToFile(i,j,n,0);
            fprintf(toTest, "%d, %d \n",i*10+j, n);
            vect.erase(vect.begin()+random);
            cardsLeft = cardsLeft - 1;
        }
    }
    fclose(toTest);  
}

void cardSelector::createVector(int size){
    srand(time(0));
    this->vectorCard.clear();
    cout<<"NEW VECTOR SIZE "<<size<<endl;
    std::vector<int> usedPairs;
    int m = 1;
    while (m <= size)
    {
        int i = rand() % 8 + 1;
        int j = rand() % 8 + 1;
        int pair = i*10+j; //Random pair to try with

        if (usedPairs.size() == 0) //Usedpairs vector size is zero
        {
            card temp = loadFromFile(i,j);
            if (temp.status != 1)
            { 
                usedPairs.push_back(pair);
                this->vectorCard.push_back(temp); //Adds the new card
                m++;
            } 
        } 
        else
        {
            int n = 0;
            bool canBeUsed = true;
            while (n != usedPairs.size()) //Usedpairs is not size zerp
            {
                if (usedPairs[n] == pair) //comparision of each of the used pairs with the tryout
                {
                    canBeUsed = false; //its already loaded
                    break;
                }
                n++; 
            }
            if (canBeUsed == true) //is not loaded
            {
                card temp = loadFromFile(i, j);
                if (temp.status != 1) //if its available it will load
                { 
                    usedPairs.push_back(pair);
                    this->vectorCard.push_back(temp);
                    m++;
                } 
            }
        }
    }
    
}

card cardSelector::replace(int i, int j){
    srand(time(0));
    if (this->vectorCard.size() > 0)
    {
        int n = rand() % this->vectorCard.size();
        int download_i = this->vectorCard[n].i;
        int download_j = this->vectorCard[n].j;
        int download_idPic = this->vectorCard[n].idPic;
        int download_status = this->vectorCard[n].status;
        loadToFile(download_i, download_j, download_idPic, download_status);
        this->vectorCard.erase(this->vectorCard.begin()+n);
    }
    
    card card = loadFromFile(i,j);
    this->vectorCard.push_back(card);
    return card;
}

void cardSelector::deleteCard(int i, int j){
    int leftCards = this->vectorCard.size();
        for(int n = 0; n < leftCards; n++){
            if (this->vectorCard[n].i == i && this->vectorCard[n].j == j){
                int download_i = this->vectorCard[n].i;
                int download_j = this->vectorCard[n].j;
                int download_idPic = this->vectorCard[n].idPic;
                int download_status = 1;
                loadToFile(download_i, download_j, download_idPic, download_status);
            }
        }
}

void cardSelector::shuffle(){
    this->cardsAvailable = this->cardsAvailable - 2;
    cout<<"\n CARDS AVAILABLE "<<this->cardsAvailable<<endl;
    cout<<"\n MATCHED, PROCEED TO SHUFFLE"<<endl;
    showVector();
    cout<<"\n VECTOR AFTER SHUFFLE"<<endl;
    createVector(this->cardsAvailable/3);
    showVector();
}

void cardSelector::showVector(){
    for(int n = 0; n < this->vectorCard.size(); n++){
        this->vectorCard[n].print();
    }
}

string cardSelector::choosePic(int idPic){
    switch (idPic)
    {
    case 1:
        return "assets/bonus.png";
    case 2:
        return "assets/double.png";
    case 3:
        return "assets/switch.png";
    case 4:
        return "assets/skull.png";
    case 5:
        return "assets/aguacate.png";
    case 6:
        return "assets/ajo.png";
    case 7:
        return "assets/arandano.png";
    case 8:
        return "assets/banano.png";
    case 9:
        return "assets/berenjena.png";
    case 10:
        return "assets/cebolla.png";
    case 11:
        return "assets/cereza.png";
    case 12:
        return "assets/chile.png";
    case 13:
        return "assets/cilantro.png";
    case 14:
        return "assets/fresa.png";
    case 15:
        return "assets/kiwi.png";
    case 16:
        return "assets/lechuga.png";
    case 17:
        return "assets/lima.png";
    case 18:
        return "assets/limon.png";
    case 19:
        return "assets/maiz.png";
    case 20:
        return "assets/manzana.png";
    case 21:
        return "assets/melocoton.png";
    case 22:
        return "assets/melon.png";
    case 23:
        return "assets/naranja.png";
    case 24:
        return "assets/pepino.png";
    case 25:
        return "assets/pera.png";
    case 26:
        return "assets/pina.png";
    case 27:
        return "assets/rabano.png";
    case 28:
        return "assets/remolacha.png";
    case 29:
        return "assets/sandia.png";
    case 30:
        return "assets/tomate.png";
    case 31:
        return "assets/uva.png";
    case 32:
        return "assets/zanahoria.png";
    default:
        cout<<"Error, ID desconocido"<<endl;
        return "";
    }
}