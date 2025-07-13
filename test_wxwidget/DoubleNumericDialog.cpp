#include "DoubleNumericDialog.h"



DoubleNumericDialog::DoubleNumericDialog(const wxString& title, const wxString& text1, const wxString& text2): wxDialog(nullptr,wxID_ANY,title,wxDefaultPosition,wxSize(250,230)){
	panel = new wxPanel(this, wxID_ANY);

	vbox = new wxBoxSizer(wxVERTICAL);
	hbox = new wxBoxSizer(wxHORIZONTAL);


	sct1 = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(55, 5), wxSize(100, 20),16384L,1);
	sct2 = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(55, sct1->GetSize().GetY()+20), wxSize(100, 20), 16384L, 1);
	stxt1 = new wxStaticText(panel, wxID_ANY, text1, wxPoint(25, 5), wxSize(100, 20));
	stxt2 = new wxStaticText(panel, wxID_ANY, text2, wxPoint(25, sct1->GetSize().GetY() + 20), wxSize(100, 20));

	okButton = new wxButton(this, wxID_OK, wxT("Ok"),wxDefaultPosition, wxSize(70, 30));
	closeButton = new wxButton(this, wxID_CANCEL, wxT("Close"),wxDefaultPosition, wxSize(70, 30));

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	vbox->Add(panel, 1);
	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	SetSizer(vbox);

	Centre();	
}


DoubleNumericDialog::~DoubleNumericDialog(){
	ShowModal();
	Destroy();
}

int DoubleNumericDialog::GetValueX(){
	return sct1->GetValue();
}

int DoubleNumericDialog::GetValueY(){
	return sct2->GetValue();
}
