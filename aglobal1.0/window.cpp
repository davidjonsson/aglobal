#include "Window.h"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "PolygonObject.h"
#include "wx/toolbar.h"
#include "wx/textctrl.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "wx/dcbuffer.h"
#include "wx/dcmemory.h"
#include "wx/image.h"
#include <wx/sizer.h>

  using namespace std;
//  ofstream lout ("LOG.txt" /*ios::trunc*/);
enum
{
    ID_RENDER,
    ID_PAUSE,
    ID_STOP,
    TEXT_LOG = 2, // declares an id which will be used to call our button;
};
Window::Window(const wxString& title,int w, int h, bool b)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(w, h))
{
  //ny
  SetBackgroundColour( wxColour( 100, 100, 100 ) );
  Show( true );
  if(b){
  wxImage::AddHandler( new wxPNGHandler );
  wxBitmap render(wxT("images/render4.png"), wxBITMAP_TYPE_PNG);
  wxBitmap pause(wxT("images/pause4.png"), wxBITMAP_TYPE_PNG);
  wxBitmap stop(wxT("images/stop4.png"), wxBITMAP_TYPE_PNG);
  wxToolBar *toolbar = CreateToolBar();
  toolbar->AddTool(ID_RENDER, render, wxT("Render image"));
  toolbar->SetBackgroundColour( wxColour( 40, 40, 40 ) );
  Show( true );
  toolbar->AddTool(ID_PAUSE, pause, wxT("Pause render"));
  toolbar->AddTool(ID_STOP, stop, wxT("Stop render"));
  toolbar->Realize();
  SetToolBar(toolbar);

   log = new wxTextCtrl(this, TEXT_LOG, _("====== LOG ====== \n"),
                      wxDefaultPosition, wxSize(200,100),
                      wxNO_BORDER | wxTE_MULTILINE | wxTE_READONLY);

    log->SetBackgroundColour( wxColour( 80, 80, 80 ) );


  string tmpLine;
  ifstream logFile ("LOG.txt");

  if (logFile.is_open())
  {
    while ( logFile.good() )
    {
      getline (logFile,tmpLine);
      wxString line(tmpLine.c_str(), wxConvUTF8);
      log->AppendText(line);
      log->AppendText(_("\n"));
    }
    logFile.close();
  }





 //Bäst om wxStreamToTextRedirector fungerade då skulle man bara behöva skriva cout.
// wxStreamToTextRedirector redirect(log);


// streambuf *sbOld = cout.rdbuf();
//  cout.rdbuf(log);
  // use cout as usual, the output appears in the text control
log->AppendText(_("Hello \n"));
//

 // cout.rdbuf(sbOld);

  Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
  wxCommandEventHandler(Window::OnQuit));
  Connect(ID_RENDER, wxEVT_COMMAND_TOOL_CLICKED,
            wxCommandEventHandler(Window::OnRender));
  Connect(wxEVT_PAINT, wxPaintEventHandler(Window::OnPaint));

  }
  else{
        Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
  wxCommandEventHandler(Window::OnQuit));
    Connect(wxEVT_PAINT, wxPaintEventHandler(Window::OnPaintRender));
  }


  //Connect(wxEVT_PAINT, wxPaintEventHandler(Window::OnPaint));
  srand(time(NULL));
  Centre();
}
void Window::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

void Window::OnRender(wxCommandEvent& event)
{

    int w = 1024, h = 768;
    windowRender = new Window(wxT("RenderWindow"),w,h,false);
    windowRender->Show(true);
    wxPaintDC(this);

}

void Window::OnPaint(wxPaintEvent & event)
{
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;
  wxSize size = this->GetSize();

}

void Window::OnPaintRender(wxPaintEvent & event)
{
           log = new wxTextCtrl(this, TEXT_LOG, _("====== LOG ====== \n"),
                      wxDefaultPosition, wxSize(200,200),
                      wxNO_BORDER | wxTE_MULTILINE | wxTE_READONLY);

    log->SetBackgroundColour( wxColour( 80, 80, 80 ) );
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;


  wxSize size = this->GetSize();
  wxBitmap bitmap(size.x, size.y);
  wxMemoryDC dc2image;
  dc2image.SelectObject(bitmap);

  wxColour col1, col2;
  col1.Set(100, 0, 0);
  col2.Set(0,100,0);

  Material m(0.5, 1, 0.5, 0.6, 0.4);
  Sphere p(0.5, Vec3f(0,0,-10.0), m);
  Vec3f hit;

  Sphere p2(0.5, Vec3f(1.5,0,-15.0), m);


  Shape* a[2];
  a[0] = &p;
  a[1] = &p2;



  for (int i = 0; i<size.y; i++)
  {
      for(int j = 0; j<size.x; j++)
      {
        x = rand() % size.x + 1;
        y = rand() % size.y + 1;
        float fovx = M_PI/4.0;
        float fovy = (((float)size.y)/((float)size.x))*fovx;
        float xCord = ((float)(2*j - size.x)/(float)size.x)*tan(fovx);
        float yCord = ((float)(2*i - size.y)/(float)size.y)*tan(fovy);
        Ray r(Vec3f(0, 0, 0), Vec3f(xCord,yCord,-1), Vec3f(0.5, 0.5, 0.5) );
        bool didHit = false;
        for(int k = 0; k < 2; k ++)
        {
            hit = a[k]->intersect(r);
            if(!didHit)
            {
                if(hit.x == 0 && hit.y == 0 && hit.z == 0)
                {
                    dc.SetPen(wxPen(col1, 1, wxSOLID));
                    dc2image.SetPen(wxPen(col1, 1, wxSOLID));
                }
                else
                {
                    col2.Set((r.color.x * 255), (r.color.x * 255), (r.color.x * 255));
                    dc.SetPen(wxPen(col2, 1, wxSOLID));
                    dc2image.SetPen(wxPen(col2, 1, wxSOLID));
                    printwx();

                    didHit = true;
                }

                dc.DrawPoint(j,i);
                dc2image.DrawPoint(j,i);
            }
        }
      }
  }

      // Converts the bitmap to an image
    wxImage image = bitmap.ConvertToImage();
    // Save the image to a jpeg.
    image.SetOption(wxIMAGE_OPTION_QUALITY, 85);
    image.SaveFile(wxT("renderedImage.png"), wxBITMAP_TYPE_PNG);
}
void printwx()
{
    float fl = 1.0;
     wxString posx;
     posx << fl << _(", ");

                  //  wxString pos = wxString::Format(wxT("%f"), xCord);
//    log->AppendText(_("hit \n"));
log.AppendText(_("s"));
    log->AppendText(posx + _("\n"));
}
