#include <wx/wx.h>

class Window : public wxFrame
{
    public:
        Window(const wxString& title);
         void OnQuit(wxCommandEvent& event);
         void Window::OnPaint(wxPaintEvent & event);

};
