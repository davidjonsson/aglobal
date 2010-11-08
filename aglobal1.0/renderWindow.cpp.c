#include "renderWindow.h"

renderWindow::renderWindow(const wxString& title,int w, int h)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(w, h))
{

  SetBackgroundColour( wxColour( 100, 100, 100 ) );
  Show( true );

  srand(time(NULL));
  Centre();

}

void renderWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

void renderWindow::OnRender(wxCommandEvent& event)
{
    wxCoord x = 0,y = 0;

    wxPaintDC dc(this);
    wxSize size = this->GetSize();

      for (int i = 0; i<1000; i++) {
      x = rand() % size.x + 1;
      y = rand() % size.y + 1;
      dc.DrawPoint(x,y);
  }
