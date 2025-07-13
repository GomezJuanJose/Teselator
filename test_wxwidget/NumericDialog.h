#pragma once
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include <wx/spinctrl.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class NumericDialog : public wxDialog{
public:
	NumericDialog(const wxString& title, const wxString& text);
	~NumericDialog();

	int GetIndex();

private:
	wxPanel *panel;
	wxBoxSizer *vbox;
	wxBoxSizer *hbox;
	wxSpinCtrl* sct;
	wxStaticText* stxt;
	wxButton *okButton;
	wxButton *closeButton;
};

