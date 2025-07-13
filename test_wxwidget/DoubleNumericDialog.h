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

class DoubleNumericDialog : public wxDialog
{
public:
	DoubleNumericDialog(const wxString& title, const wxString& text1, const wxString& text2);
	~DoubleNumericDialog();

	int GetValueX();
	int GetValueY();

private:
	wxPanel *panel;
	wxBoxSizer *vbox;
	wxBoxSizer *hbox;
	wxSpinCtrl* sct1;
	wxSpinCtrl* sct2;
	wxStaticText* stxt1;
	wxStaticText* stxt2;
	wxButton *okButton;
	wxButton *closeButton;

	//void OnOk(wxCommandEvent &evt);

	//DECLARE_EVENT_TABLE()
};

