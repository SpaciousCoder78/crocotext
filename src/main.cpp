//including headers
//Made by spaciouscoder78
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/file.h>
#endif

//creating a app class
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//creating a frame class
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    //defining the frame contents
    void OnHello(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    wxTextCtrl *m_textArea;

    wxDECLARE_EVENT_TABLE();
};

//declaring our hello button 
enum
{
    ID_Hello = 1,

};

//assigning buttons
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_Hello, MyFrame::OnHello)
    EVT_MENU(wxID_SAVE, MyFrame::OnSave)
    EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()

//creating a main function using implement method
wxIMPLEMENT_APP(MyApp);

//initialising code
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("crocotext", wxPoint(50, 50), wxSize(1024, 768));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{   //appending contents into the frame
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_SAVE, "&Save...\tCtrl-S", "Save the current document");
    menuFile->Append(wxID_OPEN, "&Open...\tCtrl-O", "Open an existing document");
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to Crocotext");

    // create the text area and add it to the frame
    m_textArea = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    m_textArea->SetFont(wxFont(14, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    // layout the text area using a sizer
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_textArea, 1, wxEXPAND);
    SetSizer(sizer);
}

//save button event
void MyFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save file"), "", "", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user cancelled the dialog

    // save the current contents of the text area to the selected file
    wxString fileName = saveFileDialog.GetPath();
    if (!fileName.empty())
    {
        wxFile file(fileName, wxFile::write);
        if (file.IsOpened())
        {
            wxString contents = m_textArea->GetValue();
            file.Write(contents);
            file.Close();
        }
        else
        {
            wxMessageBox("Failed to save file", "Error", wxOK | wxICON_ERROR);
        }
    }
}

//open button event

void MyFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open file"), "", "", "Text files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user cancelled the dialog

    // load the selected file into the text area
    wxString fileName = openFileDialog.GetPath();
    if (!fileName.empty())
    {
        wxFile file(fileName, wxFile::read);
        if (file.IsOpened())
        {
            wxString contents;
            file.ReadAll(&contents);
            file.Close();
            m_textArea->SetValue(contents);
        }
        else
        {
            wxMessageBox("Failed to open file", "Error", wxOK | wxICON_ERROR);
        }
    }
}

//exit button event
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


//about button event
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Welcome to Crocotext", "About crocotext", wxOK | wxICON_INFORMATION);
}

//hello button event
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Welcome to crocotext");
}
