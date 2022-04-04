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
    std::vector<Card> vectorCard;
    
    public:
    Card getCard(int i, int j);
    Card replace(int i, int j);
    void createVector();
    void createFile();
    Card loadFromFile(int i, int j); // if there is not card in matrix get it from the csv or to create a matrix
    void loadToFile(int i, int j, int type, int status);
    void showVector();
    void shuffle();
};


#endif //PROYECTO1DATOS2_CARDSELECTOR_H