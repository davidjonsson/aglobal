#include <wx/wx.h>

class Window : public wxFrame
{
    public:
        Window(const wxString& title,int w, int h,bool b);
         void OnQuit(wxCommandEvent& event);
         void OnPaint(wxPaintEvent & event);
         void OnPaintRender(wxPaintEvent & event);
         void OnRender(wxCommandEvent& event);

};
