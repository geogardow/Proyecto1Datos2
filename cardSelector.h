#ifndef PROYECTO1DATOS2_CARDSELECTOR_H
#define PROYECTO1DATOS2_CARDSELECTOR_H
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include "card.h"
#include "card.cpp"
#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



class cardSelector{
    private:
    std::vector<card> vectorCard;
    int cardsAvailable = 64;
    bool FLAG;

    public:
    cardSelector();
    void loadToFile(int i, int j, int type, int status);
    card loadFromFile(int i, int j);
    void createFile();
    void createVector(int size);
    card getCard(int i, int j);
    card replace(int i, int j);
    void deleteCard(int i, int j);
    void showVector();
    void shuffle();
    string choosePic(int idPic);

};


#endif //PROYECTO1DATOS2_CARDSELECTOR_H