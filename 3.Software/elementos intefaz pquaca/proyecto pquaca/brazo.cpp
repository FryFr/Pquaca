#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>
#include <GL/glu.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxFrame* parent);
    void Render();
    void OnPaint(wxPaintEvent& event);

    wxGLContext* m_context;
};

MyGLCanvas::MyGLCanvas(wxFrame* parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr)
{
    m_context = new wxGLContext(this);
}

void MyGLCanvas::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Dibuja el brazo robótico
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0f, 0.2f, 0.2f);
    
    glPopMatrix();

    glTranslatef(0.5f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glScalef(1.0f, 0.2f, 0.2f);
    
    glPopMatrix();

    glFlush();
}

void MyGLCanvas::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    SetCurrent(*m_context);
    Render();
    SwapBuffers();
}



class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

    MyGLCanvas* glCanvas;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Brazo Robótico con OpenGL");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxPanel* mainPanel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    glCanvas = new MyGLCanvas(this);
    mainSizer->Add(glCanvas, 1, wxALL | wxEXPAND, 5);

    mainPanel->SetSizer(mainSizer);
}
