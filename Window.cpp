#include "Window.h"

#define SIZEX 1024
#define SIZEY 768

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

//  pixelData = new Vec3f*[SIZEX];
  //for(int i = 0; i < SIZEX; i++)
  //   pixelData[i] = new Vec3f[SIZEY];


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
//    Scene s(SIZEX, SIZEY);
 //   s.setupScene();
  //  pixelData = s.renderScene();


    Window *window = new Window(wxT("Renderer"),1024,600,false);
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

  wxColour colour, col1, col2;
/*
  for(int i = 0; i < SIZEX; i++)
  {
      for(int j = 0; i < SIZEY; j++)
      {
          colour.Set(pixelData[i][j].x, pixelData[i][j].y, pixelData[i][j].z);
          dc.DrawPoint(j,i);
      }
  }
*/



  col1.Set(100, 0, 0);
  col2.Set(0,100,0);
  Vec3f hit;

  Material m(0, 0.5, 0.5, 0.6, 0.4);
  Material m2(0.5, 0.5, 0.5, 0.6, 0.4);
  Sphere p(0.5, Vec3f(2,-1,-11.7), m);

  Material mat (0.5,0,0,0,0);


  int wallSize = 8;

  Vec3f v1 = Vec3f(-wallSize,3,-15);
  Vec3f v2 = Vec3f(wallSize, 3, -15);
  Vec3f v3 = Vec3f(-wallSize, -wallSize, -15);
  PolygonObject p3(v1, v2, v3, mat);

  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, -wallSize, -15);
  PolygonObject p4(v1, v2, v3, mat);

  mat = Material(0,0.5,0,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, 3, 0);
  PolygonObject p5(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p6(v1, v2, v3, mat);

  mat = Material(0,0,0.5,0,0);
  v1 = Vec3f(wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p7(v1, v2, v3,mat);

  v1 = Vec3f(wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p8(v1, v2, v3,mat);

  mat = Material(0.5,0.5,0.5,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p9(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, -15);
  v3 = Vec3f(-wallSize, -wallSize, 0);
  PolygonObject p10(v1, v2, v3, mat);

  mat = Material(0,0.5,0.5,0,0);
  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, -15);
  PolygonObject p11(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p12(v1, v2, v3,mat);

  Sphere p2(1, Vec3f(1,1,-12.0), m2);

  Light L1(0, -7.9,-8.5);
  L1.setColor(Vec3f(1,1,0.5));

  Shape* a[12];
  a[0] = &p;
  a[1] = &p2;
  a[2] = &p3;
  a[3] = &p4;
  a[4] = &p5;
  a[5] = &p6;
  a[6] = &p7;
  a[7] = &p8;
  a[8] = &p9;
  a[9] = &p10;
  a[10] = &p11;
  a[11] = &p12;
  float fovx = M_PI/4.0;
  float fovy = (((float)size.y)/((float)size.x))*fovx;

  for (int i = 0; i<size.y; i++)
  {
        for(int j = 0; j<size.x; j++)
        {

//måste bara göras för första
            float xCord = ((float)(2*j - size.x)/(float)size.x)*tan(fovx);
            float yCord = ((float)(2*i - size.y)/(float)size.y)*tan(fovy);

            Ray r(Vec3f(0, 0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
//rekursivt

/*
            float length = 1000000000;
            int index = -1;
            Vec3f normal, normalTmp, intersectTmp;
            for(int k = 0; k < 12; k++)
            {
                hit = a[k]->intersect(&r, &normal);

                if(!(hit.x == 0 && hit.y == 0 && hit.z == 0))
                {
                    float currLength = (hit - r.start).lengthSquare();
                    if(currLength < length)
                    {
                        normalTmp = normal;
                        intersectTmp = hit;
                        length = currLength;
                        index = k;
                    }
                }
            }
            if(index != -1)
            {

                Vec3f pointToLight = L1.position - intersectTmp;
                pointToLight.normalize();
                normalTmp.normalize();
                Vec3f colorFromLight;
                float diff = pointToLight.dot(normalTmp);
                if(diff > 0)
                {
                    bool occlusion = false;
                    //dc.SetPen(wxPen(wxColor(240,0,0), 1, wxSOLID));

                    //dc.DrawPoint(j,i);
                    colorFromLight = L1.color;// * pointToLight.dot(normalTmp);
                    Ray shadowRay(intersectTmp, pointToLight, Vec3f(0.5,0.5,0.5));
                    Vec3f tempNormal;
                    for(int k2 = 0; k2 < 12; k2++)
                    {
                        Vec3f hitShadow = a[k2]->intersect(&shadowRay, &tempNormal);
                        if(!(hitShadow.x == 0 && hitShadow.y == 0 && hitShadow.z == 0) && (hitShadow - intersectTmp).lengthSquare() < (L1.position - intersectTmp).lengthSquare() && k2 != index)
                            colorFromLight = Vec3f(0.0,0.0,0.0);
                    }
                }
                else
                    colorFromLight = Vec3f(0,0,0);


                Vec3f tempColor = colorFromLight* diff * a[index]->getMaterial().color;
                //if(tempColor.x > 1.0 || tempColor.y > 1.0 || tempColor.z > 1.0)
                 //   tempColor.normalize();
//                col2.Set((tempColor.x * 255), (tempColor.y * 255), (tempColor.z * 255));
                dc.SetPen(wxPen(col2, 1, wxSOLID));

                dc.DrawPoint(j,i);*/
            }
        }

    }



