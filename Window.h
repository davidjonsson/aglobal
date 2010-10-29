#include <wx/wx.h>
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "PolygonObject.h"
#include "wx/toolbar.h"
#include "Light.h"
//#include "Scene.h"
#include "Vec3f.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <wx/wx.h>

class Window : public wxFrame
{
    public:
        Window(const wxString& title,int w, int h,bool b);
         void OnQuit(wxCommandEvent& event);
         void OnPaint(wxPaintEvent & event);
         void OnPaintRender(wxPaintEvent & event);
         void OnRender(wxCommandEvent& event);

        // Vec3f **pixelData;

};
