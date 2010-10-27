#include "Renderer.h"
#include "Window.h"

IMPLEMENT_APP(Renderer)

bool Renderer::OnInit()
{
    int w = 640, h = 480;
    Window *window = new Window(wxT("Renderer"),w,h,true);
    window->Show(true);

    return true;
}
