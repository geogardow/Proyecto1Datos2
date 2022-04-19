#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#include "button.h"
#include "button.cpp"
#include "client.cpp"
#include "image.cpp"
#include <chrono>
#include <thread>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif



class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class Start : public wxFrame
{
public:
    Start(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxPanel* panel = new wxPanel(this);
    wxTextCtrl* textBoxP1;
    wxTextCtrl* textBoxP2;
    wxString player1;
    wxString player2;  
 
private:

    void ClickStart(wxCommandEvent& event);
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxPanel* panel = new wxPanel(this);
    Button* buttons[9][9];
    void CreateButtons();
    client c = client();
    image interfaceImageMan = image();
    int lastId;
    wxString name1;
    wxString name2;
    wxStaticText* labelP1 = new wxStaticText(panel, wxID_ANY, wxT("") ,wxPoint(900,900/3-384/2+175));
    wxStaticText* labelP2 = new wxStaticText(panel, wxID_ANY, wxT("") ,wxPoint(900,2*900/3-384/2+125));
    wxStaticText* points1;
    wxStaticText* points2;

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
    Start *frame = new Start( "Memory Game", wxPoint(50, 50), wxSize(1200, 900));
    frame->Show(true);
    frame->SetMinSize(wxSize(1200, 900));
    frame->SetMaxSize(wxSize(1200, 900));

    return true;
}
Start::Start(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxStaticBitmap* titlePic = new wxStaticBitmap(panel, wxID_ANY, {"title.png", wxBITMAP_TYPE_PNG}, {1200/2-512/2, 0}, {512, 256});
    wxStaticBitmap* player1Pic = new wxStaticBitmap(panel, wxID_ANY, {"start1.png", wxBITMAP_TYPE_PNG}, {1200/2-384/2, 900/3-384/2+100}, {384, 192});
    wxStaticBitmap* player2Pic = new wxStaticBitmap(panel, wxID_ANY, {"start2.png", wxBITMAP_TYPE_PNG}, {1200/2-384/2, 2*900/3-384/2+50}, {384, 192});
    this->textBoxP1 = new wxTextCtrl(panel, wxID_ANY, wxT(""),wxPoint(1200/2-45, 900/3-384/2+300));
    this->textBoxP2 = new wxTextCtrl(panel, wxID_ANY, wxT(""), wxPoint(1200/2-45, 2*900/3-384/2+250));
    wxButton *btn_start =new wxButton(panel,1, wxT("Start"), wxPoint(1200/2-40, 750));
    Connect(1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Start::ClickStart));
}

void Start::ClickStart(wxCommandEvent& event){

    if (this->textBoxP1->IsEmpty()==false && this->textBoxP2->IsEmpty()== false){
        this->player1 = this->textBoxP1->GetValue();
        this->player2 = this->textBoxP2->GetValue();
        MyFrame *frame = new MyFrame( "Memory Game", wxPoint(50, 50), wxSize(1200, 900));
        frame->labelP1->SetLabel(this->player1);
        frame->labelP2->SetLabel(this->player2);
        frame->name1 = this->player1;
        frame->name2 = this->player2;
        frame->Show(true);
        frame->SetMinSize(wxSize(1200, 900));
        frame->SetMaxSize(wxSize(1200, 900));
        frame->CreateButtons();
        Close(true);
    }else{
        wxMessageBox("You must add a name");  
    }
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxStaticBitmap* player1Pic = new wxStaticBitmap(panel, wxID_ANY, {"inGame1.png", wxBITMAP_TYPE_PNG}, {900, 900/3-384/2+100}, {128, 64});
    wxStaticBitmap* player2Pic = new wxStaticBitmap(panel, wxID_ANY, {"inGame2.png", wxBITMAP_TYPE_PNG}, {900, 2*900/3-384/2+50}, {128, 64});
    points1 = new wxStaticText(panel, wxID_ANY, wxT("0"),wxPoint(900,900/3-384/2+200));
    points2 = new wxStaticText(panel, wxID_ANY, wxT("0"),wxPoint(900,2*900/3-384/2+150));

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
    wxBitmap star("assets/star.png", wxBITMAP_TYPE_PNG);
    int idPos = event.GetId();
    client c = client();
    struct message request;
    request.ID = idPos;
    request.instruction = 0;
    struct message* answer;
    answer = c.sendRequest(request);
    interfaceImageMan.img = c.imageReceived;
    interfaceImageMan.decodeImage();
    int instruction = answer->instruction;
    
    buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel({wxBitmap("temp.png", wxBITMAP_TYPE_PNG)});
    buttons[idPos/10][idPos%10]->cardButton->Enable(false);

    if (instruction == 0)
    {
        printf("CLIENT: Falta 1 carta de presionar \n");
        lastId = idPos;
    }
    else if (instruction == -1)
    {
        printf("CLIENT: Son iguales \n");
    } 
    else
    {
        printf("CLIENT: No son iguales \n");
        wxMessageBox("Perdiste tu turno");
        buttons[lastId/10][lastId%10]->cardButton->SetBitmapLabel(star);
        buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel(star);
        buttons[lastId/10][lastId%10]->cardButton->Enable(true);
        buttons[idPos/10][idPos%10]->cardButton->Enable(true);
    }
}
void MyFrame::CreateButtons()
{
    wxBitmap star("assets/star.png", wxBITMAP_TYPE_PNG);
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