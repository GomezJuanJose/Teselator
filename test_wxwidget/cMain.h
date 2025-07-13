#pragma once

#include "wx/wx.h"
#include <vector>
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include <wx/colordlg.h>
#include "tEditorTile.h"

#include "wx/image.h"
#include "wx/html/helpfrm.h"
#include "wx/html/helpctrl.h"
#include "wx/filesys.h"
#include "wx/fs_zip.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "./sample.xpm"
#endif

class cMain : public wxMDIParentFrame {
public:
	cMain();
	~cMain();

private:
	int i_numColors;
	int i_defaultMemoryColor;
	std::vector<wxColour> palette;
	wxToolBar* m_toolsBar = nullptr;
	wxMenuBar* m_menuBar = nullptr;
	wxHtmlHelpController help = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuExport(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);
	void OnMenuInfo(wxCommandEvent& evt);
	void OnMenuHelp(wxCommandEvent& evt);
	void OnMenuIndex(wxCommandEvent& evt);
	void OnNewColor(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& event);


	void OnSelectColor(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

