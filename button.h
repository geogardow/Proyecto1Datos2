#ifndef PROYECTO1DATOS2_BUTTON_H
#define PROYECTO1DATOS2_BUTTON_H
#include <string>
#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Button {
private:
    int x, y, i, j;
    wxPanel* panel;

public:
    Button(int x, int y, int i, int j, wxPanel* panel, wxBitmap star);
    wxBitmapButton* cardButton;
    //void setPic();
    //void sendRequest();    
};


#endif //PROYECTO1DATOS2_BUTTON_H