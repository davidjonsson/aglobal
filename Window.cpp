#include "Window.h"
#include <stdlib.h>
#include "wx/dcbuffer.h"
#include "wx/dcmemory.h"
#include "wx/image.h"
#include <wx/sizer.h>
#include <ctime>
#include <wx/thread.h>
#include "wx/textctrl.h"

#define DIFFUSE 1
#define UNDEFINED 2
#define REFLECTIVE 3
#define TRANSMITIVE 4
#define GLASS 5
#define SIZEX 1024
#define SIZEY 768
#define SHAPESIZE 11
#define MAXANGLE 0.7431
#define NUM_SHADOW_RAYS 40
#define NUM_RAYS 5
#define ABSORB 1
#define TRANSMIT 2
#define REFLECT 3
#define DIFF 4
Shape* a[SHAPESIZE];




Vec3f getColor(Ray r);
Vec3f diffuseIndirect(Ray r, Vec3f color, Vec3f intersectNormal, Vec3f intersectPoint,Light L);
Vec3f traceRay(Ray ray, Light L);
Vec3f specular(float specSharpness,float specIntensity,Vec3f viewDir,Vec3f lightDir, Vec3f normal);
Vec3f diffuse(Light L,Vec3f color, Vec3f intersectPoint, Vec3f intersectNormal,int mtrlType);
Vec3f reflection(Ray ray,Vec3f intersectNormal,Vec3f intersectPoint, Light L, float wR);
Vec3f refraction(Ray ray, Vec3f intersectNormal, Vec3f intersectPoint, Light L, float wT);
int russianRoulette(Vec3f color, float wT,float wR);
wxTextCtrl *logg;
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
    /*
  wxPaintDC dc(this);

  wxCoord x = 0;
  wxCoord y = 0;

  wxSize size = this->GetSize();
  */
}

void Window::OnPaintRender(wxPaintEvent & event)
{
  wxPaintDC dc(this);
  logg = new wxTextCtrl(this, -1, _("====== LOG ====== \n"),
                      wxDefaultPosition, wxSize(400,200),
                      wxNO_BORDER | wxTE_MULTILINE | wxTE_READONLY);
  //save to image;
  wxSize size = this->GetSize();
  wxBitmap bitmap(size.x,size.y);

  wxMemoryDC dcImage;
  dcImage.SelectObject(bitmap);



  wxColour colour, col1, col2;

  col1.Set(100, 0, 0);
  col2.Set(0,100,0);
  Vec3f hit;

  Material mat (1,0,0,0,0);
 // Material mat(0.7,0.7,0.7,0,0);

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
  //mat = Material(1,1,1,0,0);
  mat = Material(124.0/255.0,252.0/255.0,0,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, 3, 0);
  PolygonObject p5(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p6(v1, v2, v3, mat);

//right wall
//mat = Material(0,0,1,0,0);
  mat = Material(0.7,0.7,0.7,0,0);
  v1 = Vec3f(wallSize, 3,-15);
  v2 = Vec3f(wallSize, 3, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p7(v1, v2, v3,mat);

  v1 = Vec3f(wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, 3, -15);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p8(v1, v2, v3,mat);

//left wall
 // mat = Material(0,1,1,0,0);
  mat = Material(0.7,0.7,0.7,0,0);
  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(-wallSize, 3, 0);
  PolygonObject p9(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, 3,-15);
  v2 = Vec3f(-wallSize, -wallSize, -15);
  v3 = Vec3f(-wallSize, -wallSize, 0);
  PolygonObject p10(v1, v2, v3, mat);

//tak
  mat = Material(0,1,1,0,0);
  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, -15);
  PolygonObject p11(v1, v2, v3,mat);

  v1 = Vec3f(-wallSize, -wallSize,-15);
  v2 = Vec3f(-wallSize, -wallSize, 0);
  v3 = Vec3f(wallSize, -wallSize, 0);
  PolygonObject p12(v1, v2, v3,mat);


  Material m(0, 0, 1, 0.8, 0);
  Material m2(0.5,0.5, 0.5, 0, 1);
  Material m3(0,0.698, 0.698, 0, 0);

  m3.setSpecular(1200,1000);
  m2.setSpecular(1200,1000);
  m.setSpecular(1200,1000);

  //Sphere p(1.5, Vec3f(4,-1,-11), m);
  //Sphere p2(1.5, Vec3f(2,-2001.5,-11), m2);
  //Sphere p13(1.5, Vec3f(0,1,-8), m3);

  Sphere p(1.5, Vec3f(4,1,-11), m);
  Sphere p2(1.5, Vec3f(0,1,-9), m2);
  Sphere p13(1, Vec3f(-3,1,-12), m3);


  Light L1(0, -8,-10,2.0f,2.0f);
  L1.setColor(Vec3f(255,255,255));
  L1.getMaterial().setType(6);
  //6 = LIGHT

/*
a[0] = &p3;
a[1] = &p4;
a[2] = &p5;
a[3] = &p6;
a[4] = &p7;
a[5] = &p8;
a[6] = &p9;
a[7] = &p10;
*/
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
 // a[11] = &L1;

  /*
a[11] = &p12;
a[12] = &p13;
*/
  srand(time(0));
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
            r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0),1);
            color = traceRay(r, L1);

/* xCord = (((float)(2* j) - size.x)/(float)size.x)*tan(fovx);
yCord = (((float)(2* i) - size.y)/(float)size.y)*tan(fovy);
r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0),1 );
color = traceRay(r, L1);

xCord = (((float)(2* (j+0.5)) - size.x)/(float)size.x)*tan(fovx);
yCord = (((float)(2* (i)) - size.y)/(float)size.y)*tan(fovy);
r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0),1 );
color2 = traceRay(r, L1);

xCord = (((float)(2* (j)) - size.x)/(float)size.x)*tan(fovx);
yCord = (((float)(2* (i+0.5)) - size.y)/(float)size.y)*tan(fovy);
r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0),1 );
color3 = traceRay(r, L1);

xCord = (((float)(2* (j+0.5)) - size.x)/(float)size.x)*tan(fovx);
yCord = (((float)(2* (i+0.5)) - size.y)/(float)size.y)*tan(fovy);
r = Ray(Vec3f(0,0, 0), Vec3f(xCord,yCord,-1), Vec3f(1, 0, 0),1 );
color4 = traceRay(r, L1);

color = Vec3f((color.x + color2.x + color3.x + color4.x)*0.25, (color.y + color2.y + color3.y + color4.y)*0.25, (color.z + color2.z + color3.z + color4.z)*0.25);
*/
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
                dcImage.SetPen(wxPen(col2, 1, wxSOLID));
                dc.DrawPoint(j,i);
                dcImage.DrawPoint(j,i);
            }
        }
    wxImage image = bitmap.ConvertToImage();

    wxImage::AddHandler( new wxPNGHandler );
    image.SetOption(wxIMAGE_OPTION_QUALITY, 90);
    image.SaveFile(wxT("render.png"), wxBITMAP_TYPE_PNG);

}

Vec3f traceRay(Ray ray, Light L){


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
            Vec3f returnColor, specColor, diffColor, reflColor, refrColor, diffIndirect;


            float wR = a[index]->getMaterial().wR, wT = a[index]->getMaterial().wT;
            Vec3f colorFromLight = L.color;

           float specSharpness = a[index]->getMaterial().specH;
           float specIntensity = a[index]->getMaterial().specI;
           Vec3f viewDir(ray.start-intersectPoint);
           Vec3f lightDir = L.position-intersectPoint;
           int mtrlType = a[index]->getMaterial().getType();

            //6 = LIGHT
           /*
           if(mtrlType == 6){
                return Vec3f(1,0,0);//a[index]->getMaterial().color;
           }
           */
           int rr = russianRoulette(ray.color,wT,wR);
           wxString foobar;
    if(rr != 1)
    {
        /*if(rr != 4)
        {
        foobar.Printf(wxT("%d "),rr);
        logg->AppendText(foobar);
        }*/
          if(specIntensity != 0)
           specColor = specular(specSharpness,specIntensity,viewDir,lightDir,intersectNormal);

           diffColor = diffuse(L, a[index]->getMaterial().color,intersectPoint, intersectNormal, mtrlType);

           if(wR > 0 && rr == 3)
           {
               // logg->AppendText(_("r->"));
                reflColor = reflection(ray, intersectNormal, intersectPoint, L ,wR);
           }
           if(wT > 0 && rr == 2)
           {
           // logg->AppendText(_("t->"));
           refrColor = refraction(ray, intersectNormal, intersectPoint, L, wT);
           }

            //diffuse indirect
            if(a[index]->getMaterial().getType() == DIFFUSE && rr == 4){
                //call for diffuse indirect lighting.
          //  logg->AppendText(_(" "));
                diffIndirect = diffuseIndirect(ray, a[index]->getMaterial().color, intersectNormal, intersectPoint, L);
            }
                // diffIndirect = diffuseIndirect(ray, a[index]->getMaterial().color, intersectNormal, intersectPoint, L);
                //fixa skalning korrekt sedan. 1-wR-wT duger inte..
                returnColor = (diffIndirect + specColor + diffColor * (1-wT - wR) + reflColor + refrColor);//+ diffColor * mtrlColor * (1-wR-wT);
                return returnColor;
            }
    }
    else
        return Vec3f(0,0,0);
}
//add a material parameter with which to select specular colo etc.
Vec3f specular(float specSharpness,float specIntensity,Vec3f viewDir,Vec3f lightDir, Vec3f normal){
    //H is the half vector caluclated from ligthDir and the normal. (Cheaper to calculate than V*R)

    Vec3f specColor(1,1,1),H;
    float dist = lightDir.lengthSquare();

    viewDir.normalize();
    lightDir.normalize();

    H = (lightDir + viewDir);
    H.normalize();
    //intensity of the reflective light
    float I = pow(normal.dot(H),specSharpness);
    specColor = (specColor*I*specIntensity)/dist;
    return specColor;
}

Vec3f diffuse(Light L,Vec3f color, Vec3f intersectPoint, Vec3f intersectNormal, int mtrlType){

                float BRDF = 0;

                switch(mtrlType){
                    case DIFFUSE :
                        BRDF =(color.x + color.y + color.z)/(3.0*M_PI);
                    break;

                }

                float y = L.position.y;
                Vec3f diffColor(0,0,0), mtrlColor = color;

//random values, range 0-0.99
            for(int N = 0; N < NUM_SHADOW_RAYS; N++){
                float x = ((float)(rand() % 100))/100;
                float z = ((float)(rand() % 100))/100;
//positive x to the right, positive z out towards us.
//L.position defined as left corner closest to viewer
                x = L.position.x + x * L.width;
                z = L.position.z - z * L.length;

                Vec3f pointToLight, normal, surfacePoint;
                pointToLight = Vec3f(x,y,z) - intersectPoint;
                float r2 = pointToLight.lengthSquare();
                pointToLight.normalize();

                surfacePoint = intersectPoint + pointToLight * 0.001;
                Ray shadowRay(surfacePoint, pointToLight, Vec3f(0,0,0),1);

                Vec3f colorFromLight = L.color;

                for(int j = 0; j < SHAPESIZE; j++){
                    Vec3f hitShadow = a[j]->intersect(&shadowRay, &normal);
                    if(!(hitShadow.x == 0 && hitShadow.y == 0 && hitShadow.z == 0)){
                                colorFromLight = Vec3f(0,0,0);
                                break;
                            }

                    }
                    if(colorFromLight.x != 0 && colorFromLight.y != 0 && colorFromLight.z != 0){
                    diffColor = diffColor + colorFromLight * color * (intersectNormal.dot(pointToLight) * L.normal.dot(pointToLight * (-1)))/ r2 ;
                    }
            }

    return diffColor * BRDF / (NUM_SHADOW_RAYS);
}

Vec3f reflection(Ray ray,Vec3f intersectNormal,Vec3f intersectPoint, Light L, float wR)
{

    Vec3f reflDirection,returnColor;
    reflDirection = ray.direction - intersectNormal * (intersectNormal.dot(ray.direction)) * 2;
    intersectPoint = intersectPoint + reflDirection * 0.001;
    ray.weight *= wR;
    Ray reflRay(intersectPoint, reflDirection, Vec3f(0,0,0),ray.weight);
    return (returnColor + traceRay(reflRay, L) * reflRay.weight);
}

Vec3f refraction(Ray ray, Vec3f intersectNormal, Vec3f intersectPoint, Light L, float wT){

            bool isInside = false;
            float n1;
            float n2;
            intersectNormal.normalize();
            ray.direction.normalize();
            float normalDotDirection = intersectNormal.dot(ray.direction * (-1));
            if( normalDotDirection > 0){
             n1 = 1;
             n2 = 1.55; //glass
            }
            else{
            isInside = true;
            n1 = 1.55; //glass
            n2 = 1;
            }

            float n = n1/n2;

            float beta = sqrt(1 - n*n * (1 - normalDotDirection*normalDotDirection));
            Vec3f refrDir;

            if(!isInside)
                refrDir = ray.direction * n + intersectNormal * (n * normalDotDirection - beta);
            else
                refrDir = ray.direction * n + intersectNormal * (n * normalDotDirection + beta);

            refrDir.normalize();

            Vec3f refrPoint = intersectPoint + refrDir * 0.01;
            ray.weight *= wT;
            Ray refrRay(refrPoint, refrDir, Vec3f(0,0,0),ray.weight);

            return traceRay(refrRay,L)*refrRay.weight;
            }


Vec3f diffuseIndirect(Ray r, Vec3f color, Vec3f intersectNormal, Vec3f intersectPoint,Light L){

    //fixa absorbtion
    float reflectance = (color.x + color.y + color.z)/3.0;
    float BRDF = reflectance/M_PI;
    float random, theta, phi, probability;
    Vec3f returnColor;
    //russian roulette.

    random = rand() / ((float)RAND_MAX +1);
    if(random < (reflectance)){


    for(int i = 0; i < NUM_RAYS; i++)
    {
        float r1 = rand() / ((float)RAND_MAX + 1);
        phi = r1 * M_PI * 2.0;
        float r2 = rand() / ((float)RAND_MAX + 1);
        theta = acos(sqrt(r2));
       // theta = random * M_PI;
        float c = sqrt(1 - r2);
        probability = cos(theta) / M_PI;
        float x = cos(phi) * c;
        float y = sin(phi) * c;
        float z = sqrt(r2);

        Vec3f dir(x,y,z);
        Vec3f point = intersectPoint + dir * 0.01;
        Ray ray(point, dir, Vec3f(0,0,0),r.weight/NUM_RAYS);

       // returnColor =  returnColor  + getColor(ray);

        returnColor = returnColor + traceRay(ray, L) * (intersectNormal.dot(dir))/(probability);
        //returnColor = returnColor + traceRay(ray, L) * reflectance;///(probability);

    }
        return returnColor * (BRDF/(float)NUM_RAYS)/(1-reflectance);
    }
    else
        return Vec3f(0,0,0);

}


int russianRoulette(Vec3f color, float wT,float wR){
    float reflectiveness = (color.x + color.y + color.z)/3;



    if( 0 < wT+wR)
    {

             //float rr = rand() % 1000 / 1000.0;///(float)(RAND_MAX + 1);
             float rr2 = ((float)rand())/(float)(RAND_MAX + 1);

            // wxString Foobar;
             /*Foobar.Printf( wxT("RANDOMTAL =  %f \n wT,wR = %f,%f "), rr2,wT,wR);
             wxMessageBox(Foobar);*/

        if(wR > 0 && rr2 < wR)
        {
            //logg->AppendText(_("r->"));
             return REFLECT;//3
        }
        else if(wT > 0 && rr2 < wT)
        {

          //  logg->AppendText(_("t->"));
            return TRANSMIT;//2
        }
        else
        {
           // logg->AppendText(_("a.\n"));
            return ABSORB;//1
        }
    }
    else
    return DIFF;//4
}
