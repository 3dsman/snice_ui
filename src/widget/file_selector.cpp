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

//#include "snice.h"
//#include "file_system.h"
#include "../snice_UI.h"
#include "widget/file_selector.h"



W_fileSelector::W_fileSelector(int x, int y, int w, int h, int sx, int sy, string dir, string ext, float r, float g, float b)
             :W_slidedPanel(x, y, w, h, sx, sy, r, g, b)
{
	array = new W_array(0,0,sx,sy,2,30, 200,15);
	childList.Add(array);
	//displayList=glGenLists(1);								// Creating Display List

	oneFile = false;

	if ((strlen(ext.c_str())) <= EXTMAXLENGTH)
		strcpy(this->ext,ext.c_str());
	else
		ext="";

	directory = new DirInfo(dir);

	ListDirectory();
	//listDirectory(dir, this->ext);
}

W_fileSelector::~W_fileSelector(){
	//glDeleteLists(displayList,1);

	if (directory)
	{
		delete directory;
	};
	/*
	if (labelList.ToFirst())
		do
		{
			delete (W_label*)(labelList.GetCurrentObjectPointer());
			labelList.RemoveCurrent();
		}while (labelList.ToFirst());
	*/
	if (fileList.size())
		fileList.clear();
		/*
		for (std::list<int>::iterator it = fifth.begin(); it != fifth.end(); it++)
		do
		{
			delete (PathElement*)(fileList.GetCurrentObjectPointer());
			fileList.RemoveCurrent();
		}while (fileList.ToFirst());*/	
}

void W_fileSelector::RefreshSelectedFilesText(){};
/*
void W_fileSelector::GenDisplayList(){

		glNewList(displayList,GL_COMPILE);		// Start Building A List
		
		//draw all the label

		if(labelList.ToFirst()&&fileList.ToFirst())
		{
			do
			{
				if (((PathElement*)(fileList.GetCurrentObjectPointer()))->IsDirectory()){
					((W_label*)(labelList.GetCurrentObjectPointer()))->SetColor(0.5f,0.0f,0.0f);
					//glColor4f(0.5f,0.0f,0.0f,0.6f);
				}else
					if (((PathElement*)(fileList.GetCurrentObjectPointer()))->IsSelected()){
						((W_label*)(labelList.GetCurrentObjectPointer()))->SetColor(0.0f,0.0f,1.0f);
						//glColor4f(0.0f,0.0f,1.0f,0.6f);
					}else
					{
						((W_label*)(labelList.GetCurrentObjectPointer()))->SetColor(0.0f,0.0f,0.0f);
						//glColor4f(0.0f,0.0f,0.0f,0.6f);
					}
				((W_label*)(labelList.GetCurrentObjectPointer()))->Draw();

			}while (labelList.ToNext()&&fileList.ToNext());
		}

		glEndList();							// Done Building The Display List
		 
};*/


//void fileSelector::listDirectory(char * dir, char * ext){
void W_fileSelector::ListDirectory(){	

	// delete the labelList content
/*
	if (childList.ToFirst())
		do
		{
			delete ((UI_base*)childList.GetCurrentObjectPointer());
			childList.RemoveCurrent();
			childList.ToNext();
		}while(childList.GetCurrentObjectPointer());

	int labelPosx = 6;
	int	labelPosy = -6;
*/

	fileList = directory->BrowseDirectory(ext);

	
	std::list<PathElement*>::iterator it;
	array->resize(2,fileList.size());
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
		array->setContent(0,i,label);
		
		FileInfo * file = (dynamic_cast<FileInfo*> (*it));
		if (file)
		{
			string labelText = file->formatdate(file->wDate);
			W_label * label = new W_label(0, 0, 10, 0, labelText.c_str());
			array->setContent(1,i,label);
		}
		i++;
	}
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

void W_fileSelector::PanelOnLButtonDown(int x, int y, int px, int py){
/*
	int pickedIndex;
	//pickedIndex = (x/colSize)*13 + ((-y-6)/13);
	pickedIndex = (x/colSize)*((surfacey-6)/13) + ((-y-6)/13);
	fileList.ToFirst();
	if ((!(shift))  || (oneFile))
	do{
		((PathElement*)(fileList.GetCurrentObjectPointer()))->Selected(false);

	}while (fileList.ToNext());

	//pickedIndex = (x/colSize)*13 + ((-y-6)/13);

	fileList.ToFirst();
	while (pickedIndex>0)
	{
		fileList.ToNext();
		pickedIndex -=1;

	};

	if (((PathElement*)(fileList.GetCurrentObjectPointer()))->IsDirectory())
	{
		char dirName[256];
		(((PathElement*)(fileList.GetCurrentObjectPointer()))->GetName(dirName));

		if (strcmp(dirName,"..\\")&&strcmp(dirName,"../"))
		{
			((PathElement*)(fileList.GetCurrentObjectPointer()))->GetFullName(dirName);
			SetCurrentDirectory(dirName);
			//listDirectory();
		}
		else
		{
			//directory->getParentDir(dirName);
			directory->GetDirectory(dirName);
			//strcpy(dirName,directory->getPath());
			SetCurrentDirectory(dirName);
			//listDirectory();
			//listDirectory(dirName, this->ext);
		}
		//if (pParentUI_base)
		//		pParentUI_base->Callback(this,1);
	}
	else
	{
		((PathElement*)(fileList.GetCurrentObjectPointer()))->Selected(true);
		//GenDisplayList();
		//if (pParentUI_base)
		//	pParentUI_base->Callback(this,1);
	}
*/
};


void W_fileSelector::PanelOnLButtonUp(int x, int y){};
	
void W_fileSelector::PanelOnMouseMove(int x, int y, int prevx, int prevy){};

void W_fileSelector::PanelOnKeyPressed(int key, int action){
	if ((key == SNICEUI_KEY_LEFT_SHIFT)||(key == SNICEUI_KEY_RIGHT_SHIFT))
		shift = (action == SNICEUI_PRESS);
	printf( "fileSelector::panelOnKeyPressed\n" );
};

void W_fileSelector::GetSelectedList(List * filenames){


	filenames->ToFirst();
	do
	{	
		delete (PathElement*)(filenames->GetCurrentObjectPointer());
		filenames->RemoveCurrent();
	}while (filenames->ToFirst());

	std::list<PathElement*>::iterator it;
	for (it=fileList.begin(); it!=fileList.end(); ++it)
	{
		if ((*it)->IsSelected()){
		
		    string name = (*it)->GetFullName();
			filenames->Add(new PathElement(name));
		};

	}

};

string W_fileSelector::GetCurrentDirectory(){
	return directory->GetFullName();
}

void W_fileSelector::SetCurrentDirectory(string dirName){
	free(directory);
	if (directory = new DirInfo(dirName))
	{
		ListDirectory();
	}
}

void W_fileSelector::SetExtensions(char * extensions){
	if ((strlen(extensions)) <= EXTMAXLENGTH)
	{
		strcpy(ext,extensions);
		ListDirectory();

	}
}
/*
void W_fileSelector::PanelDraw(){

	glCallList(displayList);

};*/
