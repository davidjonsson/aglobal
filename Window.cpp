#include "Window.h"
#include <stdlib.h>

#define SIZEX 1024
#define SIZEY 768
#define SHAPESIZE 7
#define MAXANGLE 0.7431
Shape* a[SHAPESIZE];

Vec3f traceRay(Ray r, int depth, Light L , bool refracted);

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

// pixelData = new Vec3f*[SIZEX];
  //for(int i = 0; i < SIZEX; i++)
  // pixelData[i] = new Vec3f[SIZEY];


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
// Scene s(SIZEX, SIZEY);
 // s.setupScene();
  // pixelData = s.renderScene();


    Window *window = new Window(wxT("Renderer"),1024,600,false);
    window->Show(true);


}

void Window::OnPaint(wxPaintEvent & event)
{
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;

  wxSize size = this->GetSize();




  for (int i = 0; i<0; i++) {
      x = rand() % size.x + 1;
      y = rand() % size.y + 1;
      dc.DrawPoint(x,y);
  }

}

void Window::OnPaintRender(wxPaintEvent & event)
{
  wxPaintDC dc(this);

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

  Material m(0, 0, 0.5, 0.1, 0);
  Material m2(0.5,0.5, 0.5, 0, 0);
  Material m3(0,0.698, 0.698, 0, 0);
  m3.setSpecular(100,1000);
  Sphere p(1, Vec3f(2,-1,-8), m);
  Material mat (0.5,0,0,0,0);

  int wallSize = 8;
 //bakre wall
  Vec3f v1 = Vec3f(-wallSize,3,-15);
  Vec3f v2 = Vec3f(wallSize, 3, -15);
  Vec3f v3 = Vec3f(-wallSize, -wallSize, -15);
  PolygonObject p3(v1, v2, v3, mat);

  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, -wallSize, -15);
  PolygonObject p4(v1, v2, v3, mat);

//floor
  mat = Material(0.5,0.5,0.5,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, 3, 0);
  PolygonObject p5(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p6(v1, v2, v3, mat);

//right wall
  mat = Material(0,0,0.5,0,0);
  v1 = Vec3f(wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p7(v1, v2, v3,mat);

  v1 = Vec3f(wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p8(v1, v2, v3,mat);

//left wall
  mat = Material(0,0.5,0.5,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p9(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, -15);
  v3 = Vec3f(-wallSize, -wallSize, 0);
  PolygonObject p10(v1, v2, v3, mat);

//tak
  mat = Material(0,0.5,0.5,0,0);
  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, -15);
  PolygonObject p11(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p12(v1, v2, v3,mat);

  Sphere p2(1.5, Vec3f(2,-1,-11), m2);
  Sphere p13(1, Vec3f(-2,-1,-8), m3);

  Light L1(0, -8,-8,1.0f,1.0f);
  L1.setColor(Vec3f(1,1,1));

    a[0] = &p;
    a[1] = &p5;
    a[2] = &p6;
    a[3] = &p2;
    a[4] = &p13;
    a[5] = &p7;
    a[6] = &p8;

/*
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
  a[10] = &p13;
*/
  /*
  a[11] = &p12;
  a[12] = &p13;
*/
  float fovx = M_PI/4.0;
  float fovy = (((float)size.y)/((float)size.x))*fovx*1.15;

  for (int i = 0; i<size.y; i++)
  {
        for(int j = 0; j<size.x; j++)
        {
            float xCord, yCord;
            Ray r;
            Vec3f color, color2, color3, color4;

            xCord = (((float)(2* j) - size.x)/(float)size.x)*tan(fovx);
            yCord = (((float)(2* i) - size.y)/(float)size.y)*tan(fovy);
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color = traceRay(r,3, L1, false);
  /*
            xCord = (((float)(2* j) - size.x)/(float)size.x)*tan(fovx);
            yCord = (((float)(2* i) - size.y)/(float)size.y)*tan(fovy);
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color = traceRay(r,3, L1, false);

            xCord = (((float)(2* (j+0.5)) - size.x)/(float)size.x)*tan(fovx);
            yCord = (((float)(2* (i)) - size.y)/(float)size.y)*tan(fovy);
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color2 = traceRay(r,3, L1, false);

            xCord = (((float)(2* (j)) - size.x)/(float)size.x)*tan(fovx);
            yCord = (((float)(2* (i+0.5)) - size.y)/(float)size.y)*tan(fovy);
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color3 = traceRay(r,3, L1, false);

            xCord = (((float)(2* (j+0.5)) - size.x)/(float)size.x)*tan(fovx);
            yCord = (((float)(2* (i+0.5)) - size.y)/(float)size.y)*tan(fovy);
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color4 = traceRay(r,3, L1, false);
*/
//Super sampling nedan, verkar fungera men suger kraft!!
/*
            xCord = ((float)(2*(j-0.5) - size.x)/(float)size.x)*tan(fovx);
            yCord = ((float)(2*(i+0.5) - size.y)/(float)size.y)*tan(fovy);
          r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color = traceRay(r,3, L1) * 0.25;

            xCord = ((float)(2*(j+0.5) - size.x)/(float)size.x)*tan(fovx);
            yCord = ((float)(2*(i+0.5) - size.y)/(float)size.y)*tan(fovy);

            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color = color + traceRay(r,3, L1) * 0.25;

            xCord = ((float)(2*(j-0.5) - size.x)/(float)size.x)*tan(fovx);
            yCord = ((float)(2*(i-0.5) - size.y)/(float)size.y)*tan(fovy);

            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color = color + traceRay(r,3, L1) * 0.25;

            xCord = ((float)(2*(j+0.5) - size.x)/(float)size.x)*tan(fovx);
            yCord = ((float)(2*(i-0.5) - size.y)/(float)size.y)*tan(fovy);

            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0) );
            color =color + traceRay(r,3, L1) * 0.25;
*/
          //  color = Vec3f((color.x + color2.x + color3.x + color4.x)*0.25, (color.y + color2.y + color3.y + color4.y)*0.25, (color.z + color2.z + color3.z + color4.z)*0.25);

                    if(color.x > 1.0 || color.y > 1.0 || color.z > 1.0){
                    float max = -5;
                    if(color.x > max)
                        max = color.x;
                    if(color.y > max)
                        max = color.y;
                    if(color.z > max)
                        max = color.z;

                    color = color * (1/max);

                 }

                col2.Set((color.x * 255), (color.y * 255), (color.z * 255));
                dc.SetPen(wxPen(col2, 1, wxSOLID));

                dc.DrawPoint(j,i);
            }
        }
}

Vec3f traceRay(Ray ray, int depth, Light L, bool refracted = false){


       Vec3f specColor;
        float length = 100000000;
        int index = -1;
        Vec3f hit,normal, intersectNormal, intersectPoint;

        for(int k = 0; k < SHAPESIZE; k++){

            hit = a[k]->intersect(&ray, &normal);

            if(!(hit.x == 0 && hit.y == 0 && hit.z == 0)){

                float currLength = (hit - ray.start).lengthSquare();

                if(currLength < length){

                    intersectNormal = normal;
                    intersectPoint = hit;
                    length = currLength;
                    index = k;
                }
            }
        }

        if(index != -1){


            intersectNormal.normalize();
            Vec3f returnColor;
            Vec3f specColor(1,1,1);

            float wR = a[index]->getMaterial().wR, wT = a[index]->getMaterial().wT;
            Vec3f colorFromLight = L.color;
//specular (Blinn-Phong)
           //H is the half vector caluclated from ligthDir and the normal. (Cheaper to calculate than V*R)
           Vec3f H;

           float specSharpness = a[index]->getMaterial().specH;
           float specIntensity = a[index]->getMaterial().specI;
           Vec3f viewDir(ray.start-intersectPoint);
           Vec3f lightDir = L.position-intersectPoint;

           float dist = lightDir.lengthSquare();

          viewDir.normalize();
           lightDir.normalize();

            H = (lightDir + viewDir);
            H.normalize();
            //intensity of the reflective light
           float I = pow(intersectNormal.dot(H),specSharpness);
           specColor = (specColor*I*specIntensity)/dist;

//reflective
            if(wR > 0 && depth > 0){
                Vec3f reflDirection;

                if(!refracted)
                    reflDirection = ray.direction - intersectNormal * (intersectNormal.dot(ray.direction)) * 2;
                else
                    reflDirection = ray.direction - (intersectNormal * (-1)) * (intersectNormal.dot(ray.direction)) * 2;

                intersectPoint = intersectPoint + reflDirection * 0.001;
                Ray reflRay(intersectPoint, reflDirection, Vec3f(0,0,0));
                if(refracted)
                    returnColor = returnColor + traceRay(reflRay, --depth, L, true) * wR;
                else
                    returnColor = returnColor + traceRay(reflRay, --depth, L, false) * wR;
            }

//refractive
            if(wT > 0 && depth > 0)
            {
                bool willTransmit = true;
                if(refracted)
                    willTransmit = ((intersectNormal * (-1)).dot(ray.direction) < MAXANGLE);
                else
                    willTransmit = (intersectNormal.dot(ray.direction) < MAXANGLE);

                if(willTransmit)
                {
                    Vec3f refrDirection;
                    float n;
                    intersectNormal.normalize();
                    ray.direction.normalize();
                    if(!refracted)
                    {
                        float cos1 = intersectNormal.dot((ray.direction * (-1)));
                        float c1 = (1/1.33);
                        float cos2 = sqrt(1 - c1*c1*(1-cos1*cos1));

                        if(cos1 >= 0)
                        {
                            refrDirection = ray.direction * c1 + intersectNormal * (c1*cos1 - cos2);
                        }
                        else
                        {
                            refrDirection = ray.direction * c1 + intersectNormal * (c1*cos1 + cos2);
                        }

                        refrDirection.normalize();
                        refrDirection = refrDirection - (refrDirection + intersectNormal * (intersectNormal.dot(intersectNormal))) * 2;

                   /* n = 1/a[index]->getMaterial().refrIndex;
                    float c1 = (intersectNormal * (-1)).dot(ray.direction);
                    float c2 = sqrt(1-((n*n)*(1-(c1*c1))));
                    refrDirection = ray.direction * n + intersectNormal * (n*c1-c2);
                    refrDirection.normalize();*/
                    }
                    else
                    {
                    /*intersectNormal = intersectNormal * (-1);
                    n = a[index]->getMaterial().refrIndex;
                    float c1 = (intersectNormal * (-1)).dot(ray.direction);
                    float c2 = sqrt(1-((n*n)*(1-(c1*c1))));
                    refrDirection = ray.direction * n + intersectNormal * (n*c1-c2);
                    refrDirection = refrDirection * (-1);*/
                        float cos1 = intersectNormal.dot((ray.direction * (-1)));
                        float c1 = (1.33);
                        float cos2 = sqrt(1 - c1*c1*(1-cos1*cos1));

                        if(cos1 >= 0)
                        {
                            refrDirection = ray.direction * c1 + intersectNormal * (c1*cos1 - cos2);
                        }
                        else
                        {
                            refrDirection = ray.direction * c1 + intersectNormal * (c1*cos1 + cos2);
                        }

                        refrDirection.normalize();
                        refrDirection = refrDirection - (refrDirection - intersectNormal * (intersectNormal.dot(intersectNormal))) * 2;
                    }

                    intersectPoint = intersectPoint + refrDirection * 0.01;
                    Ray refrRay(intersectPoint, refrDirection, Vec3f(0,0,0));


                    if(!refracted)
                        returnColor = returnColor + traceRay(refrRay, --depth, L, true) * wT;
                    else
                        returnColor = returnColor + traceRay(refrRay, --depth, L, false) * wT;
                }
            }

//direct lighting
//fix the weights here...  1 -wR - wT no good..
//uniform sampling --> p(y) = 1/area(Light)

                float area = L.length * L.width;
                int NUM_SHADOW_RAYS = 36;
                srand(NULL);
                float y = L.position.y;
                Vec3f diffColor(0,0,0), mtrlColor = a[index]->getMaterial().color;

//random values, range 0-0.99
            for(int N = 0; N < NUM_SHADOW_RAYS; N++){
                float x = ((float)(rand() % 100))/100;
                float z = ((float)(rand() % 100))/100;


//positive x to the right, positive z out towards us.
//L.position defined as left corner closest to viewer
                x  = L.position.x + x * L.width;
                z  = L.position.z - z * L.length;

                Vec3f pointToLight, normal, surfacePoint;
                pointToLight = Vec3f(x,y,z) - intersectPoint;
                float r2 = pointToLight.lengthSquare();
                pointToLight.normalize();
                surfacePoint = intersectPoint + pointToLight * 0.001;
                Ray shadowRay(surfacePoint, pointToLight, Vec3f(0,0,0));
                Vec3f colorFromLight = L.color;

                for(int j = 0; j < SHAPESIZE; j++){
                    Vec3f hitShadow = a[j]->intersect(&shadowRay, &normal);
                    if(!(hitShadow.x == 0 && hitShadow.y == 0 && hitShadow.z == 0)){
                                colorFromLight = Vec3f(0,0,0);
                                break;
                            }

                    }
                    if(colorFromLight.x != 0 && colorFromLight.y != 0 && colorFromLight.z != 0){
                    diffColor = diffColor + colorFromLight * (intersectNormal.dot(pointToLight) * L.normal.dot(pointToLight * (-1)) / (r2/5));
                    }
            }

                //fixa skalning korrekt sedan. 1-wR-wT duger inte..
                returnColor = returnColor + specColor+ diffColor * mtrlColor * (1-wR-wT);
                return returnColor;
            }
            else
               return Vec3f(0,0,0);


    }





