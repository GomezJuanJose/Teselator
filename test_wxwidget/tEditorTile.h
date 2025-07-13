#pragma once
#include <vector>
#include <fstream>
#include <exception>
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "tCanvas.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class tEditorTile : public wxMDIChildFrame
{
public:
	tEditorTile(wxMDIParentFrame* parent, wxString sName, std::vector<wxColour> p, int i);
	~tEditorTile();

	void UpdatePalette(std::vector<wxColour> p);
	void SetColor(int c);
	void SetIndex(int i);
	bool Export(wxString sFileName);
	bool New(int r, int c);

private:
	int i_row, i_col;

	int i_index;

	tCanvas* m_canvas = nullptr;
	wxStatusBar* m_statusBar = nullptr;
	wxSlider* m_zoomSlider = nullptr;

	std::vector<wxColour> pal;

	unsigned char *c_sprite = nullptr;

	void OnZoomChange(wxCommandEvent &evt);
	

	wxDECLARE_EVENT_TABLE();
};

