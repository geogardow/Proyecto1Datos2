#include <string>
//#include "interface.cpp"
#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "button.h"
/**
 * @brief Construct a new Button:: Button object
 * 
 * @param x 
 * @param y 
 * @param i 
 * @param j 
 * @param panel 
 * @param star 
 */
Button::Button(int x, int y, int i, int j, wxPanel* panel, wxBitmap star){
        this->cardButton = new wxBitmapButton(panel, i*10+j, star, wxPoint(x, y), wxSize(80,80));
}
