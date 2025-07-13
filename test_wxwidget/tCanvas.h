#pragma once
#include <vector>
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/vscroll.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class tCanvas : public wxHVScrolledWindow
{
public:
	tCanvas(wxWindow* parent, std::vector<wxColour> p);
	~tCanvas();

	unsigned char* GetSprite();
	void UpdatePalette(std::vector<wxColour> p);
	void SetPixelSize(int n);
	void SetSpriteData(int rows, int columns, unsigned char *Sprite);
	void SetColor(int c);
private:
	int i_pixelSize = 8;
	std::vector<wxColour> palette;
	int i_color = 0;
	unsigned char* c_sprite = nullptr;

	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent &evt);

	void OnMouseLeftDown(wxMouseEvent &evt);

	wxDECLARE_EVENT_TABLE();
};

