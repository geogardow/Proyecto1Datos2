#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#include "button.h"
#include "button.cpp"
#include "client.cpp"
//#include "cardSelector.cpp"
//#include "star.png"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxPanel* panel = new wxPanel(this);
    Button* buttons[8][8];
    void CreateButtons();
    client c = client();
    int lastId;

private:
       
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClick(wxCommandEvent& event);

};
enum
{
    ID_Hello = 1
};
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Memory Game", wxPoint(50, 50), wxSize(1200, 900));
    frame->Show(true);
    frame->SetMinSize(wxSize(1200, 900));
    frame->SetMaxSize(wxSize(1200, 900));
    frame->CreateButtons();

    //cardSelector *matrix = new cardSelector();
    //matrix->createFile();
    //matrix->createVector();
    //matrix->showVector();

    //cout<<"****************************************"<<endl;
    //matrix->loadFromFile(1,4);
    //matrix->loadFromFile(2,3);
    //cout<<"****************************************"<<endl;
    //matrix->getCard(2,3);
    //cout<<"****************************************"<<endl;
    //matrix->getCard(7,4);
    //cout<<"****************************************"<<endl;
    //delete matrix;

    return true;
}
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");


    //button2->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
      //  staticText2->SetLabel(wxString::Format("button2 clicked %d times", something));
      //});

    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Algoritmos y Estructuras de Datos 2");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Algoritmos y Estructuras de Datos 2");
}
void MyFrame::OnClick(wxCommandEvent& event)
{
    wxBitmap star("star2.png", wxBITMAP_TYPE_PNG);
    struct client::message request;    
    int idPos;
    idPos = event.GetId();
    struct client::message answer;
    request.ID=idPos;
    request.loadedPic= "";
    answer = c.sendRequest(request);
    int instruction;
    instruction = answer.ID;
    buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel({gammasoft_64x64_xpm}); //reemplazar {gammasoft_64x64_xpm} por wxBitmap(answer->loadedPic, wxBITMAP_TYPE_PNG)
     
    if (instruction == 0)
    {
        printf("CLIENT: Falta 1 carta de presionar \n");
        lastId = idPos;
    }
    else if (instruction == -1)
    {
        printf("CLIENT: Son iguales \n");
        //desabilitar las cartas
    } 
    else
    {
        printf("CLIENT: No son iguales \n");
        buttons[lastId/10][lastId%10]->cardButton->SetBitmapLabel(star);
        buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel(star);
    }
    

}
void MyFrame::CreateButtons()
{
    wxBitmap star("star2.png", wxBITMAP_TYPE_PNG);
    int x = 50;
    int y = 50;
    for(int i = 1; i < 9 ; i++){
        for (int j = 1; j < 9 ; j++){
            Button* cardButton = new Button(x,y,i,j,panel,star);
            buttons[i][j]=cardButton;
            Connect(i*10+j, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnClick));
            x = x + 90;
        }
        x = 50;
        y = y + 90;
    }
}

