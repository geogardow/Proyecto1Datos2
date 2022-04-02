#include <string>
//#include "interface.cpp"
#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "button.h"

Button::Button(int x, int y, int i, int j, wxPanel* panel){
        this->cardButton = new wxBitmapButton(panel, i*10+j, {gammasoft_64x64_xpm}, wxPoint(x, y));
        //this->cardButton->SetFocus();
    
}
