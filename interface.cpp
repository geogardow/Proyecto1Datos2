#include <wx/wxprec.h>
#include <wx/bmpbuttn.h>
#include "button.h"
#include "button.cpp"
#include "client.cpp"
#include "image.cpp"
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
    int randomStart;
    wxString name1;
    wxString name2;
    wxStaticText* labelP1 = new wxStaticText(panel, wxID_ANY, wxT("") ,wxPoint(900,900/3-384/2+175));
    wxStaticText* labelP2 = new wxStaticText(panel, wxID_ANY, wxT("") ,wxPoint(900,2*900/3-384/2+125));
    wxStaticText* points1;
    wxStaticText* points2;
    wxStaticBitmap* turn1 = new wxStaticBitmap(panel, wxID_ANY, {"check.png", wxBITMAP_TYPE_PNG}, {1000, 900/3-384/2+100}, {128, 64});
    wxStaticBitmap* turn2 = new wxStaticBitmap(panel, wxID_ANY, {"check.png", wxBITMAP_TYPE_PNG}, {1000, 2*900/3-384/2+50}, {128, 64});
    void updatePoints(int player, int points);
    void updateTurn(int player);

private:
       
    void OnClick(wxCommandEvent& event);

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
/**
 * @brief Construct a new Start:: Start object
 * 
 * @param title 
 * @param pos 
 * @param size 
 */
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
/**
 * @brief Saves the names of the players and then opens a frame
 * 
 * @param event 
 */
void Start::ClickStart(wxCommandEvent& event){

    if (this->textBoxP1->IsEmpty()==false && this->textBoxP2->IsEmpty()== false){
        this->player1 = this->textBoxP1->GetValue();
        this->player2 = this->textBoxP2->GetValue();
        MyFrame *frame = new MyFrame( "Memory Game", wxPoint(50, 50), wxSize(1200, 900));
        frame->labelP1->SetLabel(this->player1);
        frame->labelP2->SetLabel(this->player2);
        frame->name1 = this->player1;
        frame->name2 = this->player2;
        struct message starterPack;
        frame->updateTurn(frame->c.sendRequest(starterPack)->turn);
        frame->Show(true);
        frame->SetMinSize(wxSize(1200, 900));
        frame->SetMaxSize(wxSize(1200, 900));
        frame->CreateButtons();
        Close(true);
    }else{
        wxMessageBox("You must add a name");  
    }
}
/**
 * @brief Construct a new My Frame:: My Frame object
 * 
 * @param title 
 * @param pos 
 * @param size 
 */
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxStaticBitmap* player1Pic = new wxStaticBitmap(panel, wxID_ANY, {"inGame1.png", wxBITMAP_TYPE_PNG}, {900, 900/3-384/2+100}, {128, 64});
    wxStaticBitmap* player2Pic = new wxStaticBitmap(panel, wxID_ANY, {"inGame2.png", wxBITMAP_TYPE_PNG}, {900, 2*900/3-384/2+50}, {128, 64});
    points1 = new wxStaticText(panel, wxID_ANY, wxT("Points: 0"),wxPoint(900,900/3-384/2+200));
    points2 = new wxStaticText(panel, wxID_ANY, wxT("Points: 0"),wxPoint(900,2*900/3-384/2+150));

}
/**
 * @brief Controls what happens when you click a button of the button matrix
 * 
 * @param event 
 */
void MyFrame::OnClick(wxCommandEvent& event)
{
    wxBitmap star("assets/star.png", wxBITMAP_TYPE_PNG);
    int idPos = event.GetId();
    struct message request;
    request.ID = idPos;
    request.instruction = 0;
    struct message* answer;
    answer = c.sendRequest(request);
    interfaceImageMan.img = c.imageReceived;
    interfaceImageMan.decodeImage();
    int instruction = answer->instruction;
    int idPic = answer->picID;
    updatePoints(1, answer->pointsP1);
    updatePoints(2, answer->pointsP2);
    updateTurn(answer->turn);
    
    buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel({wxBitmap("temp.png", wxBITMAP_TYPE_PNG)});
    buttons[idPos/10][idPos%10]->cardButton->Enable(false);

    if (instruction == 0)
    {
        lastId = idPos;
    }
    else if (instruction == -1)
    {
        if (idPic == 1)
        {
            wxMessageBox("You're lucky today, you get an extra turn!");
        }
        else if (idPic == 2)
        {
            wxMessageBox("You're lucky today, you just doubled your points!");
        }
        else if (idPic == 3 && answer->switched == 1)
        {
            wxMessageBox("You are very lucky! You just exchanged points with your oponent!");
        }
        else if (idPic == 4)
        {
            wxMessageBox("Oh no, you got that one, your oponent loses one point!");
        }
        if (answer->HIT == 1)
        {
            wxMessageBox("You're very lucky! Both of the cards were loaded in memory! You got an extra point!");
        }
        
    } 
    else
    {
        wxMessageBox("Perdiste tu turno");
        buttons[lastId/10][lastId%10]->cardButton->SetBitmapLabel(star);
        buttons[idPos/10][idPos%10]->cardButton->SetBitmapLabel(star);
        buttons[lastId/10][lastId%10]->cardButton->Enable(true);
        buttons[idPos/10][idPos%10]->cardButton->Enable(true);
    }

    if (answer->winner == 1)
    {
        wxMessageBox("Felicidades el ganador es: "+this->name1);
        Close(true);
    }
    else if (answer->winner == 2)
    {
        wxMessageBox("Felicidades el ganador es: "+this->name2);
        Close(true);
    }
    else if (answer->winner == 3)
    {
        wxMessageBox("Oh no, hubo un empate");
        Close(true);
    }
}
/**
 * @brief Creates the matrix of buttons
 * 
 */
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
/**
 * @brief Updates the label of points
 * 
 * @param player 
 * @param points 
 */
void MyFrame::updatePoints(int player, int points){
    if(player == 1)
    {
        this->points1->SetLabel("Points: " + to_string(points));
    }
    else if(player == 2)
    {
        this->points2->SetLabel("Points: " + to_string(points));
    }
}
/**
 * @brief Updates the turn of the player
 * 
 * @param player 
 */
void MyFrame::updateTurn(int player){
    if(player == 1)
    {
        this->turn1->Show(true);
        this->turn2->Show(false);
    }
    else if(player == 2)
    {
        this->turn1->Show(false);
        this->turn2->Show(true);
    }
}