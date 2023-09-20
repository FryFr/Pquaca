#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <fstream> 

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    void OnSliderChange(wxCommandEvent& event);
    void OnStartButton(wxCommandEvent& event);
    void OnStopButton(wxCommandEvent& event);
    void OnResetButton(wxCommandEvent& event);
    void OnSaveConfig(wxCommandEvent& event);
    void OnLoadConfig(wxCommandEvent& event);
    void OnClearLog(wxCommandEvent& event);
    void OnApplyMode(wxCommandEvent& event);
    void OnUpdateView(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void LoadOBJFile(const std::string& filename); 

private:
    wxSlider* sliderBase;
    wxSlider* sliderHombro;
    wxSlider* sliderEslabon3;
    wxSlider* sliderEslabon4;
    wxSlider* sliderEslabon5;
    wxTextCtrl* textBase;
    wxTextCtrl* textHombro;
    wxTextCtrl* textEslabon3;
    wxTextCtrl* textEslabon4;
    wxTextCtrl* textEslabon5;
    wxTextCtrl* infoPanel;
    wxTextCtrl* logPanel;
    wxButton* startButton;
    wxButton* stopButton;
    wxButton* resetButton;
    wxButton* clearLogButton;
    wxButton* applyModeButton;
    wxButton* updateViewButton;
    wxChoice* modeChoice;
    wxPanel* graphicsPanel;
    wxMenuBar* menuBar;
    wxMenu* fileMenu;
    float base, hombro, eslabon3, eslabon4, eslabon5;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Brazo Robótico ");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 800))
{
    menuBar = new wxMenuBar();
    fileMenu = new wxMenu();
    fileMenu->Append(wxID_SAVE, "Guardar Configuración");
    fileMenu->Append(wxID_OPEN, "Cargar Configuración");
    menuBar->Append(fileMenu, "Archivo");
    SetMenuBar(menuBar);

    Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnSaveConfig));
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MyFrame::OnLoadConfig));

    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel* controlPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    controlPanel->SetBackgroundColour(wxColour(220, 220, 220));
    controlPanel->SetForegroundColour(wxColour(0, 0, 0));

    wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);

    sliderBase = new wxSlider(controlPanel, wxID_ANY, 0, -100, 100);
    sliderHombro = new wxSlider(controlPanel, wxID_ANY, 0, -100, 100);
    sliderEslabon3 = new wxSlider(controlPanel, wxID_ANY, 0, -100, 100);
    sliderEslabon4 = new wxSlider(controlPanel, wxID_ANY, 0, -100, 100);
    sliderEslabon5 = new wxSlider(controlPanel, wxID_ANY, 0, -100, 100);

    textBase = new wxTextCtrl(controlPanel, wxID_ANY, "0");
    textHombro = new wxTextCtrl(controlPanel, wxID_ANY, "0");
    textEslabon3 = new wxTextCtrl(controlPanel, wxID_ANY, "0");
    textEslabon4 = new wxTextCtrl(controlPanel, wxID_ANY, "0");
    textEslabon5 = new wxTextCtrl(controlPanel, wxID_ANY, "0");

    startButton = new wxButton(controlPanel, wxID_ANY, "Iniciar");
    startButton->SetBackgroundColour(wxColour(0, 0, 255));
    startButton->SetForegroundColour(wxColour(255, 255, 255));

    stopButton = new wxButton(controlPanel, wxID_ANY, "Detener");
    stopButton->SetBackgroundColour(wxColour(128, 128, 128));
    stopButton->SetForegroundColour(wxColour(255, 255, 255));

    resetButton = new wxButton(controlPanel, wxID_ANY, "Reiniciar");
    clearLogButton = new wxButton(controlPanel, wxID_ANY, "Limpiar Registro");
    applyModeButton = new wxButton(controlPanel, wxID_ANY, "Aplicar Modo");
    updateViewButton = new wxButton(controlPanel, wxID_ANY, "Actualizar Vista");

    infoPanel = new wxTextCtrl(controlPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    logPanel = new wxTextCtrl(controlPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);
    infoPanel->AppendText("Información en tiempo real:\n");
    logPanel->AppendText("Registro de eventos:\n");

    wxArrayString modes;
    modes.Add("Modo Manual");
    modes.Add("Modo Automático");
    modeChoice = new wxChoice(controlPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, modes);

    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Base:"), 0, wxALL, 5);
    controlSizer->Add(sliderBase, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(textBase, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Hombro:"), 0, wxALL, 5);
    controlSizer->Add(sliderHombro, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(textHombro, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Eslabon 3:"), 0, wxALL, 5);
    controlSizer->Add(sliderEslabon3, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(textEslabon3, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Eslabon 4:"), 0, wxALL, 5);
    controlSizer->Add(sliderEslabon4, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(textEslabon4, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Eslabon 5:"), 0, wxALL, 5);
    controlSizer->Add(sliderEslabon5, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(textEslabon5, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(startButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(stopButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(resetButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(clearLogButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(applyModeButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(updateViewButton, 0, wxALL | wxCENTER, 5);
    controlSizer->Add(new wxStaticText(controlPanel, wxID_ANY, "Modo de Operación:"), 0, wxALL, 5);
    controlSizer->Add(modeChoice, 0, wxALL | wxEXPAND, 5);
    controlSizer->Add(infoPanel, 1, wxALL | wxEXPAND, 5);
    controlSizer->Add(logPanel, 1, wxALL | wxEXPAND, 5);

    controlPanel->SetSizer(controlSizer);

    graphicsPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    graphicsPanel->SetBackgroundColour(wxColour(240, 240, 240));
    graphicsPanel->SetForegroundColour(wxColour(0, 0, 0));

    mainSizer->Add(controlPanel, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(graphicsPanel, 2, wxALL | wxEXPAND, 5);

    mainPanel->SetSizer(mainSizer);

    Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));
    Connect(wxEVT_COMMAND_SLIDER_UPDATED, wxCommandEventHandler(MyFrame::OnSliderChange));
    Connect(startButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnStartButton));
    Connect(stopButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnStopButton));
    Connect(resetButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnResetButton));
    Connect(clearLogButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnClearLog));
    Connect(applyModeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnApplyMode));
    Connect(updateViewButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnUpdateView));
}

void MyFrame::OnSliderChange(wxCommandEvent& event)
{
    base = sliderBase->GetValue();
    hombro = sliderHombro->GetValue();
    eslabon3 = sliderEslabon3->GetValue();
    eslabon4 = sliderEslabon4->GetValue();
    eslabon5 = sliderEslabon5->GetValue();

    textBase->SetValue(wxString::Format("%f", base));
    textHombro->SetValue(wxString::Format("%f", hombro));
    textEslabon3->SetValue(wxString::Format("%f", eslabon3));
    textEslabon4->SetValue(wxString::Format("%f", eslabon4));
    textEslabon5->SetValue(wxString::Format("%f", eslabon5));

    infoPanel->AppendText(wxString::Format("Movimiento: Base=%f, Hombro=%f, Eslabon3=%f, Eslabon4=%f, Eslabon5=%f\n", base, hombro, eslabon3, eslabon4, eslabon5));
    logPanel->AppendText(wxString::Format("Movimiento registrado: Base=%f, Hombro=%f, Eslabon3=%f, Eslabon4=%f, Eslabon5=%f\n", base, hombro, eslabon3, eslabon4, eslabon5));

    Refresh();
}

void MyFrame::OnStartButton(wxCommandEvent& event)
{
    infoPanel->AppendText("Brazo robótico iniciado.\n");
    logPanel->AppendText("Evento: Brazo robótico iniciado.\n");
}

void MyFrame::OnStopButton(wxCommandEvent& event)
{
    infoPanel->AppendText("Brazo robótico detenido.\n");
    logPanel->AppendText("Evento: Brazo robótico detenido.\n");
}

void MyFrame::OnResetButton(wxCommandEvent& event)
{
    infoPanel->AppendText("Valores reiniciados.\n");
    logPanel->AppendText("Evento: Valores reiniciados.\n");
    sliderBase->SetValue(0);
    sliderHombro->SetValue(0);
    sliderEslabon3->SetValue(0);
    sliderEslabon4->SetValue(0);
    sliderEslabon5->SetValue(0);
    OnSliderChange(event);
}

void MyFrame::OnSaveConfig(wxCommandEvent& event)
{
    logPanel->AppendText("Evento: Configuración guardada.\n");
}

void MyFrame::OnLoadConfig(wxCommandEvent& event)
{
    logPanel->AppendText("Evento: Configuración cargada.\n");
}

void MyFrame::OnClearLog(wxCommandEvent& event)
{
    logPanel->Clear();
    logPanel->AppendText("Registro de eventos:\n");
}

void MyFrame::OnApplyMode(wxCommandEvent& event)
{
    wxString mode = modeChoice->GetString(modeChoice->GetSelection());
    logPanel->AppendText("Evento: Modo de operación cambiado a " + mode + ".\n");
}

void MyFrame::OnUpdateView(wxCommandEvent& event)
{
    logPanel->AppendText("Evento: Vista 3D actualizada.\n");
}

void MyFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
}

void MyFrame::LoadOBJFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        logPanel->AppendText("Error: No se pudo abrir el archivo OBJ.\n");
        return;
    }
    
}




















