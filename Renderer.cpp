#include "Renderer.h"
#include "Window.h"

IMPLEMENT_APP(Renderer)

bool Renderer::OnInit()
{
    //int w = 640, h = 480;
    //Window *window = new Window(wxT("Renderer"),w,h,true);
    int w = 1024, h = 600;
    Window *window = new Window(wxT("Renderer"),w,h,false);
    window->Show(true);

    return true;
}
