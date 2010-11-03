#include <wx/wx.h>


class renderWindow : public wxFrame{

public:

         renderWindow(const wxString& title,int w, int h);
         void OnQuit(wxCommandEvent& event);
         void OnPaint(wxPaintEvent & event);
};
