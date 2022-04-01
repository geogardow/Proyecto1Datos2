#ifndef PROYECTO1DATOS2_BUTTON_H
#define PROYECTO1DATOS2_BUTTON_H
#include <string>
//#include "interface.cpp"
#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "gammasoft_64x64.xpm"

class Button {
private:
    int x, y, i, j;
    wxPanel* panel;
    wxBitmapButton* cardButton;

public:
    Button(int x, int y, int i, int j, wxPanel* panel);
    //void setPic();
    //void sendRequest();    
};


#endif //PROYECTO1DATOS2_BUTTON_H