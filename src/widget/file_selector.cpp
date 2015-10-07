// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
// www.funnyfarm.tv

// thanks to nehe stencil buffer tutorial http://nehe.gamedev.net/

// File modified by Tricoire Sebastien
// Date of creation : 2004 10 14
///
// File modified by
// Date of modification :

/* ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2002-2003 by Funny Farm.
 * www.funnyfarm.tv
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "../snice_UI.h"
#include "widget/file_selector.h"

W_fileSelector::W_fileSelector(int x, int y, int w, int h, int sx, int sy, string dir, string ext, float r, float g, float b)
             :W_slidedPanel(x, y, w, h, sx, sy, r, g, b)
{
	array = new W_array(0,0,sx,sy,2,30, 200,15);
    array->SetMargin(0,0,10,10);
	AddChild(array);
	array->OnClickCell(this, W_fileSelector::StatArrayClickCell);

	oneFile = false;

	directory = new DirInfo(dir);
    SetExtensions(ext);
}

W_fileSelector::~W_fileSelector(){

	if (directory)
	{
		delete directory;
	};
	while(!fileList.empty()) delete fileList.front(), fileList.pop_front();
	fileList.clear();

}

void W_fileSelector::StatArrayClickCell(UI_base * asker, W_array* caller, unsigned int x, unsigned int y)
{
	(dynamic_cast<W_fileSelector*> (asker))->ArrayClickCell(caller, x, y);
}

void W_fileSelector::ArrayClickCell( W_array* caller, unsigned int x, unsigned int y)
{
	if (fileList.size() > y)
	{
		std::list<PathElement*>::iterator iter = std::next(fileList.begin(), y);
		if (!shift||oneFile)
        {
            clearSelection();
        }
		selected.push_back(*iter);
        for (unsigned int i=0; i<array->getSizeX(); i++)
            array->SetCellColor(i,y,selColor);

		if(onChangeSelect) onChangeSelect(onChangeSelectAsker, this, selected);
	}
}

void W_fileSelector::clearSelection()
{
    selected.clear();

    Color color = {.r=0,.g=0,.b=0,.a=0};
    for (unsigned int i=0; i<array->getSizeX(); i++)
        for (unsigned int j=0; j<array->getSizeY(); j++)
            array->SetCellColor(i,j,color);
}

void W_fileSelector::ListDirectory(){	
    while(!fileList.empty()) delete fileList.front(), fileList.pop_front();
    fileList.clear();

	fileList = directory->BrowseDirectory(exts);

	std::list<PathElement*>::iterator it;
    array->ClearContent();
	array->Resize(2,fileList.size());
	unsigned int i =0;
	for (it=fileList.begin(); it!=fileList.end(); ++it)
	{
		string labelText = (*it)->GetName();
        W_label * label = new W_label(0, 0, 10, 0, labelText.c_str());
		
		DirInfo * dir = (dynamic_cast<DirInfo*> (*it));
		if (dir)
		{
            label->SetColor(0.5f,0.0f,0.0f);
            label->SetBold(true);
		}
        array->SetContent(0,i,label,true,true,true,true);
		
		FileInfo * file = (dynamic_cast<FileInfo*> (*it));
		if (file)
		{
			string labelText = file->formatdate(file->wDate);
            W_label * label = new W_label(0, 0, 10, 0, labelText.c_str());
            array->SetContent(1,i,label,true,true,true,true);
		}
		i++;
    }
    //array->setLineHeight(3,10);
	//array->SetWidth(500);
	/*
	array->setContentPos(0,0,0,0,0,0);
	array->setContentPos(0,1,1,0,0,0);
	array->setContentPos(0,2,1,1,0,0);
	array->setContentPos(0,3,0,1,0,0);
	array->setLineHeight(3, 35);
	array->setcollumnWidth(0, 150);*/
	
	SetPanelSurface(array->GetWidth(), array->GetHeight());
};

UI_base* W_fileSelector::OnKeyPressed(int key, int action){
	UI_base* intercept = W_slidedPanel::OnKeyPressed( key,  action);
	if ((!intercept)&&((key == SNICEUI_KEY_LEFT_SHIFT)||(key == SNICEUI_KEY_RIGHT_SHIFT)))
		shift = (action == SNICEUI_PRESS);
	return intercept;
};

std::list<PathElement*> W_fileSelector::GetSelectedList()
{
    return selected;
}

string W_fileSelector::GetCurrentDirectory(){
	return directory->GetFullName();
}

void W_fileSelector::SetCurrentDirectory(string dirName){
	if (directory)
		delete(directory);
	if ((directory = new DirInfo(dirName)))
	{
		ListDirectory();
	}
}

void W_fileSelector::SetExtensions(string extensions){
	
		string::size_type lastPos = 0;
	    string::size_type pos = extensions.find_first_of(";", lastPos);

		while (string::npos != pos || string::npos != lastPos)
		{
			// Found a token, add it to the vector.
			exts.push_back(extensions.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = extensions.find_first_not_of(";", pos);
			// Find next "non-delimiter"
			pos = extensions.find_first_of(";", lastPos);
		}

		ListDirectory();
}



void W_fileSelector::OnChangeSelect(UI_base * asker, std::function<void(UI_base * asker, W_fileSelector* caller, std::list<PathElement*> selection)> function)
{
	onChangeSelect = function;
	onChangeSelectAsker = asker;

}
