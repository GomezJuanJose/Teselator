#include "tEditorTile.h"

wxBEGIN_EVENT_TABLE(tEditorTile, wxMDIChildFrame)
EVT_SLIDER(20001,tEditorTile::OnZoomChange)
wxEND_EVENT_TABLE()

tEditorTile::tEditorTile(wxMDIParentFrame* parent, wxString sName, std::vector<wxColour> p, int i) : wxMDIChildFrame(parent, wxID_ANY,sName){
	pal = p;
	m_canvas = new tCanvas(this,p);

	m_statusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_zoomSlider = new wxSlider(m_statusBar, 20001, 8, 1, 32);

	i_index = i;
}


tEditorTile::~tEditorTile()
{
}

void tEditorTile::SetColor(int c){
	m_canvas->SetColor(c);
}

void tEditorTile::SetIndex(int i){
	i_index = i;
}

void tEditorTile::UpdatePalette(std::vector<wxColour> p) {
	pal = p;
	m_canvas->UpdatePalette(p);
}

bool tEditorTile::Export(wxString sFileName)
{
	unsigned char* spr = m_canvas->GetSprite();
//	std::vector<std::string> tiles[];

	try {
		int col=i_col/8, row=i_row/8;
		std::ofstream myfile(sFileName.ToStdString());
		std::vector<std::string> tiles;
		tiles.clear();
		for (int i = 0; i < (row * col);i++) {
			tiles.push_back("\n u8 tesela"+ std::to_string(i) +"[64] ={\n");
		}

		int j = 0,group=1,minSubGroup=0,maxSubGroup= col -1;//indices to separate the pixel buffer and the string array in groups

		// Iterate 8 by 8 the vector(is the fixed size of a tile) and adds it to its corresponding string, after that detects if has reached the maximum of 64 * col_number(tiles) changes the maxs and mins of the strings
		for (int i = 0; i < (row * col * 64);i += 8) {
			if (i >= (col *8) *8*group) {
				minSubGroup = maxSubGroup+1;
				maxSubGroup += col;
				group++;
			}

			if (j < minSubGroup) {
				j = minSubGroup;
			}
			else if (j > maxSubGroup) {
				j = minSubGroup;
			}

			tiles[j] += std::to_string(spr[i]+ i_index) + ", " + std::to_string(spr[i + 1]+ i_index);
			tiles[j] += ", ";
			tiles[j] += std::to_string(spr[i + 2]+ i_index) + ", " + std::to_string(spr[i + 3]+ i_index);
			tiles[j] += ", ";
			tiles[j] += std::to_string(spr[i + 4]+ i_index) + ", " + std::to_string(spr[i + 5]+ i_index);
			tiles[j] += ", ";
			tiles[j] += std::to_string(spr[i + 6]+ i_index) + ", " + std::to_string(spr[i + 7]+ i_index);
			tiles[j] += ", \n";
			j++;

		}

		for (int i = 0; i < (row * col);i++) {
			myfile << tiles[i] + "};";
		}

		for (int i = 0;i < pal.size();i++) {
			myfile << "\nBG_PALETTE_SUB["+std::to_string(i+ i_index)+"]= RGB15("+ std::to_string(pal[i].Red()/8)+", "+ std::to_string(pal[i].Green()/8)+", "+ std::to_string(pal[i].Blue()/8) +");";
		}
		
		myfile.close();
	}
	catch (std::exception& ex) {
		wxMessageDialog *dial = new wxMessageDialog(nullptr,"Error, cannot export", "Error", wxOK | wxICON_ERROR);
		dial->ShowModal();
		return false;
	}
	return true;
}

bool tEditorTile::New(int r, int c)
{
	i_row = r;
	i_col = c;
	delete[] c_sprite;
	c_sprite = new unsigned char[r*c]{ 0 };
	m_canvas->SetSpriteData(r, c, c_sprite);
	return false;
}

void tEditorTile::OnZoomChange(wxCommandEvent & evt){
	m_statusBar->SetStatusText(wxString("Zoom: ") << m_zoomSlider->GetValue(), 1);
	m_canvas->SetPixelSize(m_zoomSlider->GetValue());
	evt.Skip();
}

