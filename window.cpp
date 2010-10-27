#include "Window.h"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "PolygonObject.h"
#include "wx/toolbar.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


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
  toolbar->AddTool(wxID_NEW, render, wxT("Render image"));
  toolbar->SetBackgroundColour( wxColour( 40, 40, 40 ) );
  Show( true );
  toolbar->AddTool(wxID_NEW, pause, wxT("Pause render"));
  toolbar->AddTool(wxID_NO, stop, wxT("Stop render"));
  toolbar->Realize();
  SetToolBar(toolbar);



  Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED,
  wxCommandEventHandler(Window::OnQuit));
  Connect(wxID_NEW, wxEVT_COMMAND_TOOL_CLICKED,
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
    Window *window = new Window(wxT("Renderer"),w,h,false);
    window->Show(true);


}

void Window::OnPaint(wxPaintEvent & event)
{
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;

  wxSize size = this->GetSize();



//vad gör detta?!?

  for (int i = 0; i<0; i++) {
      x = rand() % size.x + 1;
      y = rand() % size.y + 1;
      dc.DrawPoint(x,y);
  }

}

void Window::OnPaintRender(wxPaintEvent & event)
{
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;

  wxSize size = this->GetSize();

  wxColour col1, col2;
  col1.Set(100, 0, 0);
  col2.Set(0,100,0);

  Material m(0.5, 1, 0.5, 0.6, 0.4);
  Sphere p(0.5, Vec3f(0,0,-10.0), m);
  Vec3f hit;
//vad gör detta?!?
/*
  Vec3f v1 = Vec3f(150, 150, -100);
  Vec3f v2 = Vec3f(200, 150, -100);
  Vec3f v3 = Vec3f(150, 100, -100);
  PolygonObject p2(v1, v2, v3);
  */
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
            hit = a[k]->intersect(&r);
            if(!didHit)
            {
                if(hit.x == 0 && hit.y == 0 && hit.z == 0)
                    dc.SetPen(wxPen(col1, 1, wxSOLID));
                else
                {
                    col2.Set((r.color.x * 255), (r.color.x * 255), (r.color.x * 255));
                    dc.SetPen(wxPen(col2, 1, wxSOLID));
                    didHit = true;
                }
                dc.DrawPoint(j,i);
            }
        }
      }
  }
}
