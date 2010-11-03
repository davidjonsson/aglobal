#include <wx/wx.h>
#include "wx/textctrl.h"
class Window : public wxFrame
{
    public:

        Window(const wxString& title,int w, int h,bool b);
         void OnQuit(wxCommandEvent& event);
         void OnPaint(wxPaintEvent & event);
         void OnPaintRender(wxPaintEvent & event);
         void OnRender(wxCommandEvent& event);
         void printwx();
         wxTextCtrl *log;
         Window *windowRender;

};
