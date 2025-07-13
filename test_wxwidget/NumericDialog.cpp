#include "NumericDialog.h"



NumericDialog::NumericDialog(const wxString& title, const wxString& text): wxDialog(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(300,130)){
	panel = new wxPanel(this, wxID_ANY);

	vbox = new wxBoxSizer(wxVERTICAL);
	hbox = new wxBoxSizer(wxHORIZONTAL);

	sct = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(75, 5), wxSize(100, 20), 16384L, 0);
	stxt = new wxStaticText(panel, wxID_ANY, text, wxPoint(25, 5), wxSize(100, 20));

	okButton = new wxButton(this, wxID_OK, wxT("Ok"), wxDefaultPosition, wxSize(70, 30));
	closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxSize(70, 30));

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	vbox->Add(panel, 1);
	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	SetSizer(vbox);

	Centre();
}


NumericDialog::~NumericDialog(){
	ShowModal();
	Destroy();
}

int NumericDialog::GetIndex(){
	return sct->GetValue();
}
