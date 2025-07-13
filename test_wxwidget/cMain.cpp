#include "cMain.h"
#include "DoubleNumericDialog.h"
#include "NumericDialog.h"



wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuExport)
EVT_MENU(10003, cMain::OnMenuExit)
EVT_MENU(10004, cMain::OnNewColor)
EVT_MENU(10005, cMain::OnMenuIndex)
EVT_MENU(10006, cMain::OnMenuInfo)
EVT_MENU(10007, cMain::OnMenuHelp)
EVT_CLOSE(cMain::OnClose)
wxEND_EVENT_TABLE()

cMain::cMain() :wxMDIParentFrame(nullptr, wxID_ANY, "Teselator") {
	i_numColors = 0;
	i_defaultMemoryColor = 0;
	//Añade la barra del menu
	m_menuBar = new wxMenuBar();
	this->SetMenuBar(m_menuBar);

	//Añade un menu para operar con archivos
	wxMenu* m_menuArchivo = new wxMenu();
	m_menuArchivo->Append(10001, "New");
	m_menuArchivo->Append(10002, "Export");
	m_menuArchivo->Append(10003, "Exit");

	//Crea Añadir color
	wxMenu* m_menuHerramientas = new wxMenu();
	m_menuHerramientas->Append(10004, "Add color");
	m_menuHerramientas->Append(10005, "Change memory index");

	//Crea about
	wxMenu* m_menuInfo = new wxMenu();
	m_menuInfo->Append(10006, "About");
	m_menuInfo->Append(10007, "Help");

	//Añade el menu de archivos a la barra
	m_menuBar->Append(m_menuArchivo, "File");
	m_menuBar->Append(m_menuHerramientas, "Tools");
	m_menuBar->Append(m_menuInfo, "Information");

	//Add a toolbar for the palette
	m_toolsBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);
	palette.push_back(wxColour(0, 0, 0));
	wxButton* b = new wxButton(m_toolsBar, 10100 + i_numColors, "", wxDefaultPosition, wxSize(24, 24), 0);
	b->SetBackgroundColour(palette[i_numColors]);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColor), nullptr, this);
	m_toolsBar->AddControl(b);
	i_numColors++;

	m_toolsBar->Realize();

	//Helper
	help.UseConfig(wxConfig::Get());
	bool ret;
	help.SetTempDir(".");

	wxPathList pathlist;
	pathlist.Add("./helpfiles");
	pathlist.Add("../helpfiles");
	pathlist.Add("../../html/help/helpfiles");

	ret = help.AddBook(wxFileName(pathlist.FindValidPath("testing.hhp"), wxPATH_UNIX));
	if (!ret)
		wxMessageBox("Failed adding book helpfiles/testing.hhp");
	ret = help.AddBook(wxFileName(pathlist.FindValidPath("another.hhp"), wxPATH_UNIX));
	if (!ret)
		wxMessageBox(_("Failed adding book helpfiles/another.hhp"));
}

cMain::~cMain() {
}

void cMain::OnMenuNew(wxCommandEvent& evt) {
	int x, y;
	tEditorTile* w = new tEditorTile(this, "Sprite", palette, i_defaultMemoryColor);
	DoubleNumericDialog* sizeDialog = new DoubleNumericDialog("Sprite size in tiles (each tile is 8x8 pixels)", "Y", "X");
	sizeDialog->Show();
	if (sizeDialog->ShowModal() == wxID_OK) {
		w->New(sizeDialog->GetValueX() * 8, sizeDialog->GetValueY() * 8);
		w->Show();
	}
	evt.Skip();
}

void cMain::OnMenuExport(wxCommandEvent& evt) {
	if (GetActiveChild() != nullptr) {
		wxFileDialog dlg(this, "Export Tiles", "", "", ".txt Files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK) {
			((tEditorTile*)GetActiveChild())->Export(dlg.GetPath());
		}
	}
	evt.Skip();
}

void cMain::OnMenuExit(wxCommandEvent& evt) {
		evt.Skip();
		// Close the help frame; this will cause the config data to
		// get written.
		if (help.GetFrame()) // returns NULL if no help frame active
			help.GetFrame()->Close(true);
		// now we can safely delete the config pointer
		delete wxConfig::Set(NULL);
		Close(true);
}

void cMain::OnMenuInfo(wxCommandEvent& evt) {
	wxMessageDialog* dial = new wxMessageDialog(nullptr, "Developed by Juan José Gómez Simón.", "Info", wxOK);
	dial->ShowModal();
	evt.Skip();
}

void cMain::OnMenuHelp(wxCommandEvent& evt){
	help.Display("Test HELPFILE");
}

void cMain::OnMenuIndex(wxCommandEvent& evt) {
	NumericDialog* dial = new NumericDialog("Starting index to reserve memory", "Index");
	if (dial->ShowModal() == wxID_OK) {
		i_defaultMemoryColor = dial->GetIndex();

		for (wxWindowList::iterator it = this->GetChildren().begin(); it != this->GetChildren().end(); it++) {
			tEditorTile* et = dynamic_cast<tEditorTile*>(*it);
			if (et) {
				et->SetIndex(i_defaultMemoryColor);
			}
		}
	}
	evt.Skip();
}

void cMain::OnNewColor(wxCommandEvent& evt) {

	wxColourDialog dlg(this);

	if (dlg.ShowModal() == wxID_OK) {
		palette.push_back(dlg.GetColourData().GetColour());
		wxButton* b = new wxButton(m_toolsBar, 10100 + i_numColors, "", wxDefaultPosition, wxSize(24, 24), 0);
		b->SetBackgroundColour(palette[i_numColors]);
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColor), nullptr, this);
		m_toolsBar->AddControl(b);
		i_numColors++;
		m_toolsBar->Realize();

		for (wxWindowList::iterator it = this->GetChildren().begin(); it != this->GetChildren().end(); it++) {
			tEditorTile* et = dynamic_cast<tEditorTile*>(*it);
			if (et) {
				et->UpdatePalette(palette);
			}
		}
	}
	evt.Skip();
}

void cMain::OnClose(wxCloseEvent& event){
	// Close the help frame; this will cause the config data to
// get written.
	if (help.GetFrame()) // returns NULL if no help frame active
		help.GetFrame()->Close(true);
	// now we can safely delete the config pointer
	event.Skip();
	delete wxConfig::Set(NULL);
}

void cMain::OnSelectColor(wxCommandEvent& evt) {
	int i_color = evt.GetId() - 10100;
	if (GetActiveChild() != nullptr) {
		((tEditorTile*)GetActiveChild())->SetColor(i_color);
	}
}