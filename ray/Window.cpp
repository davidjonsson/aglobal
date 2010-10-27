#include "Window.h"
#include "wx/toolbar.h"
#include <stdlib.h>
#include <time.h>
#include "Shape.h"
#include "Sphere.h"
#include "ray.h"
#include "Vec3f.h"
#include "Material.h"
#include "PolygonObject.h"


Window::Window(const wxString& title,int w, int h, bool b)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(w, h))
{

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

 // wxCoord x = 0;
 // wxCoord y = 0;

  wxSize size = this->GetSize();


//vad gör detta?!?
/*
  for (int i = 0; i<0; i++) {
      x = rand() % size.x + 1;
      y = rand() % size.y + 1;
      dc.DrawPoint(x,y);
  }
*/
}

void Window::OnPaintRender(wxPaintEvent & event)
{
  wxPaintDC dc(this);

//  wxCoord x = 0;
//  wxCoord y = 0;

  wxSize size = this->GetSize();

  int w = size.x;
  int h = size.y;
  Vec3f p1(200,200,-50);
  Vec3f p2(400,200,-50);
  Vec3f p3(200,400,-50);
  Material mat(0,0,1,1,1);
  Sphere s(50,Vec3f(w/2,h/2,-50),mat);
  PolygonObject p(p1,p2,p3);

  Shape* sArray[1];
  sArray[0] = &s;
  sArray[1] = &p;

  for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){

        for(int r = 0; r < 2; r++){
            Vec3f intersect = sArray[r]->intersect(Ray(Vec3f(i,j,1000),Vec3f(0,0,-1),Vec3f(1,1,1)));
            if(!(intersect.x == 0 && intersect.y == 0 && intersect.z == 0)){
                dc.DrawPoint(intersect.x,intersect.y);
            }

        }
      }
  }

//vad gör detta?!?
/*
  for (int i = 0; i<10000; i++) {
      x = rand() % size.x + 1;
      y = rand() % size.y + 1;
      dc.DrawPoint(x,y);
  }
  */
}
