#include "Renderer.h"
#include "Window.h"

IMPLEMENT_APP(Renderer)

bool Renderer::OnInit()
{
    Window *window = new Window(wxT("Renderer"));
    window->Show(true);

    return true;
}
