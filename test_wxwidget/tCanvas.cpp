#include "tCanvas.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(tCanvas, wxHVScrolledWindow)
EVT_PAINT(tCanvas::OnPaint)
EVT_LEFT_DOWN(tCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

tCanvas::tCanvas(wxWindow* parent, std::vector<wxColour> p) : wxHVScrolledWindow(parent, wxID_ANY){
	SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT);


	palette = p;
}


tCanvas::~tCanvas()
{
}

unsigned char * tCanvas::GetSprite()
{
	return c_sprite;
}

void tCanvas::UpdatePalette(std::vector<wxColour> p) {
	palette = p;
}

void tCanvas::SetPixelSize(int n){
	i_pixelSize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();
	Refresh();
}

void tCanvas::SetSpriteData(int rows, int columns, unsigned char * Sprite){
	c_sprite = Sprite;
	this->SetRowColumnCount(rows, columns);
}

void tCanvas::SetColor(int c){
	i_color = c;
}

wxCoord tCanvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(i_pixelSize);
}

wxCoord tCanvas::OnGetColumnWidth(size_t col) const
{
	return wxCoord(i_pixelSize);
}

void tCanvas::OnDraw(wxDC & dc){
	dc.Clear();

	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	wxPosition s = GetVisibleBegin();
	wxPosition e = GetVisibleEnd();

	pen.SetStyle(wxPENSTYLE_LAST_HATCH);
	pen.SetColour(wxColour(200, 200, 200));
	dc.SetPen(pen);

	if (i_pixelSize <= 4) {
		dc.SetPen(*wxTRANSPARENT_PEN);
	}

	for (int i = s.GetRow(); i < e.GetRow(); i++) {
		for (int j = s.GetCol(); j < e.GetCol(); j++) {
			int i_color = c_sprite[i*this->GetColumnCount() + j];
			brush.SetColour(palette[i_color]);
			brush.SetStyle(wxBRUSHSTYLE_SOLID);
			dc.SetBrush(brush);
			dc.DrawRectangle(j*i_pixelSize, i*i_pixelSize, i_pixelSize, i_pixelSize);
		}
	}


}

void tCanvas::OnPaint(wxPaintEvent & evt){
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

void tCanvas::OnMouseLeftDown(wxMouseEvent & evt){
	wxPosition s = GetVisibleBegin();
	c_sprite[(evt.GetY() / i_pixelSize + s.GetRow())*this->GetColumnCount() + (evt.GetX() / i_pixelSize + s.GetCol())] = i_color;
	this->Refresh(false);//Just refresh the modified part of the canvas not everything
	evt.Skip();
}
