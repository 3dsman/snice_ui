// file_picker.cpp: FilePicker dialog box.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// SNICE : Simple Nodal Image Compositing Environment
// SNICE is a image and video compositing software
// Copyright by Sebastien Tricoire (3dsman@free.fr) and Lionel Allorge (lionel.allorge@lunerouge.org)
///
// based on Crafter (Leaf) Library by Wybren van Keulen (www.funnyfarm.tv)
// based on GLFW Library (www.glfw.org)
// 
// file_picker.cpp
// This file is the FilePicker dialog box file
// File created by Tricoire Sebastien
// Date of creation : 2004 10 13
///
// File modified by 
// Date of modification : 
///
// Copyright (C) 2004 Sebastien Tricoire and Lionel Allorge.
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 as published by the Free Software Foundation;
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//////////////////////////////////////////////////

//#include "viewports_array.h"
#include "file_system.h"

#include "widget/label.h"
#include "widget/button.h"
#include "widget/text_box.h"
#include "widget/menu.h"
#include "widget/sub_menu.h"
#include "widget/file_selector.h"

#include "file_picker.h"

D_FilePicker::D_FilePicker(int x, int y, string name, string dir, std::list<string> exts)
			 :UI_dialog(x, y, 450, 290, name, false, false)
{

	r = 0.4f;
	g = 0.4f;
	b = 0.4f;

	strcpy(filesName,"");

	pStartDir = new W_menu(10, -30, 430, 20, "dir");
	AddChild(pStartDir);

	std::list<string> rootlist = rootsNames();
	
	for (std::list<string>::iterator iter=rootlist.begin(); iter!=rootlist.end(); iter++)
	{
		pStartDir->AddOption(*iter, 0);
	}
	string curDir = dir;
	if (dir == "")curDir = pStartDir->GetString();
		
	pStartDir->SetOption(0);

	pFileSelector = new W_fileSelector(10, -50, 430, 180,150,160,curDir, "*.*");
	AddChild(pFileSelector);
    pFileSelector->OnChangeSelect(this, D_FilePicker::StatFileSelectorSelect);
	
	pSelectedFiles = new W_textbox(10, -235, 300, 20, "File", curDir);
	AddChild(pSelectedFiles);
	pSelectedFiles->OnSetContent(this, D_FilePicker::StatTextboxChange);

	
	pValid = new W_button(320,-235, 120,20, "OK");
	AddChild(pValid);
	pValid->OnClick(this, D_FilePicker::StatButtonValid);

	pCancel = new W_button(320,-260, 120,20, "Cancel");
	AddChild(pCancel);
	pCancel->OnClick(this, D_FilePicker::StatButtonValid);
	
	
	pFileExt = new W_menu(10, -260, 300, 20, "File Type");
	AddChild(pFileExt);
	

	extensions = exts;
	for (std::list<string>::iterator iter=extensions.begin(); iter!=extensions.end(); iter++)
	{
		pFileExt->AddOption(*iter, 0);
	}
	pFileExt->OnPickOption(this,D_FilePicker::StatMenuChange);
	
	pFileExt->SetOption(0);
	
	std::list<string>::iterator iter=extensions.begin();
	pFileSelector->SetExtensions(*iter);
/*
	//set the good extension to the file selector
	if (extensions.ToFirst())
	{
		//find the substring of the extensions(after the | character)
		extString = (char *) extensions.GetCurrentObjectPointer();
		pdest = strchr(extString, '|' );
		//set the extension
		if (pdest)
			pFileSelector->SetExtensions(&extString[pdest - extString+1]);
	}*/
}



D_FilePicker::~D_FilePicker()
{
	/*
	if(extensions.ToFirst())
	do
	{
		delete (char*) extensions.GetCurrentObjectPointer();
		extensions.RemoveCurrent();
	}while(extensions.ToFirst());
	
	if(selectedFileList.ToFirst())
	do
	{
 if ((PathElement*)(selectedFileList.GetCurrentObjectPointer()))
	  	delete ((PathElement*)(selectedFileList.GetCurrentObjectPointer()));
		selectedFileList.RemoveCurrent();
	}while(selectedFileList.ToFirst());
	*/
}


	void D_FilePicker::StatButtonValid(UI_base * asker, W_button* caller)
	{
		(dynamic_cast<D_FilePicker*> (asker))->ButtonValid(caller);
	}
	
	void D_FilePicker::StatMenuChange(UI_base * asker, W_subMenu* caller, unsigned char option)
	{
		(dynamic_cast<D_FilePicker*> (asker))->MenuChange(caller, option);
	}
	
	void D_FilePicker::StatTextboxChange(UI_base * asker, W_textbox* caller, string content)
	{
		(dynamic_cast<D_FilePicker*> (asker))->TextboxChange(caller, content);
	}
	
    void D_FilePicker::StatFileSelectorSelect(UI_base * asker, W_fileSelector* caller, std::list<PathElement*> selection)
	{
        (dynamic_cast<D_FilePicker*> (asker))->FileSelectorSelect(caller, selection);
	}
	
    void D_FilePicker::ButtonValid( W_button* caller)
	{
		killMe = true;
        if(onValid) onValid(onValidAsker, this, pFileSelector->GetSelectedList(), caller==pValid);
    	pInterceptChild = 0;
	}
	
    void D_FilePicker::MenuChange( W_subMenu* caller, unsigned char option)
	{
        pFileExt->SetLabel("File Type");
		if (pFileSelector)
			pFileSelector->SetExtensions( caller->GetString());
	}
	
    void D_FilePicker::TextboxChange( W_textbox* caller, string content)
	{
		if (pFileSelector)
			pFileSelector->SetCurrentDirectory(content);
	}
	
    void D_FilePicker::FileSelectorSelect( W_fileSelector* caller, std::list<PathElement*> selection)
	{

        for (std::list<PathElement*>::iterator iter=selection.begin(); iter!=selection.end(); iter++)
        {

            std::cout<<(*iter)->GetName()<<" ";
        }
        std::cout<<std::endl;
	}
/*
void D_FilePicker::Callback(UI_base * pCallObject, unsigned char callIndex )
{
	
	//if the callback comme from the file extension menu
	if ((pCallObject == pFileExt)&&(callIndex == 1))
	{
		// search for the selected option
		
		if (extensions.ToFirst())
		{
			for (int i = pFileExt->GetOption()-1;i > 0; --i)
				extensions.ToNext();

			//find the substring of the extensions(after the | character)
			
			char * extString = (char *) extensions.GetCurrentObjectPointer();
			char * pdest = strchr(extString, '|' );

			//set the extension
			if( pdest )
			{
				pFileSelector->SetExtensions(&extString[pdest - extString+1]);}
		};
	}

		//if the callback comme from the file extension menu
	if ((pCallObject == pStartDir)&&(callIndex == 1))
	{
		pFileSelector->SetCurrentDirectory(pStartDir->GetString());
	}

	// if the callback is from the file selector
	if ((pCallObject == pFileSelector)&&(callIndex == 1)){

		//refresh the selected files list
		pFileSelector->GetSelectedList(&selectedFileList);

		//char filesName[256] = "";
		strcpy(filesName,"");
		char file[256] = "";

		
		if (selectedFileList.ToFirst())
		{
			do
			{

				(((PathElement*)(selectedFileList.GetCurrentObjectPointer()))->GetFullName(file));
				
				if ((strlen(filesName)+strlen(file))<255)
					strcat(filesName,file);

			}while ((selectedFileList.ToNext()) && (strcat(filesName,";")));
		}
		else
			pFileSelector->GetCurrentDirectory(filesName);

		
		//refresh the selectedFiles editbox
		pSelectedFiles->SetContent(filesName);
	}

	//if the callback comme from the selectedfiles textbox
	if ((pCallObject == pSelectedFiles)&&(callIndex == 1))
	{
		#ifdef _DEBUG
			printf("callback::pSelectedFiles -> 1\n");
		#endif
	}
	
	//if the callback comme from the valid button
	if ((pCallObject == pValid)&&(callIndex == 1))
	{
		pViewports->deletewhendone = this;
		visible= false;

		if (callbackNode)
		{
			callbackNode->Callback(this,1);
		}else
		{
		if (pParentUI_base)
			pParentUI_base->Callback(this,1);
		}		
	};
	
	//if the callback comme from the cancel button
	if ((pCallObject == pCancel)&&(callIndex == 1))
	{
		pViewports->deletewhendone = this;
		visible= false;
		if (callbackNode)
		{
			callbackNode->Callback(this,2);
		}else
		{
			if (pParentUI_base)
				pParentUI_base->Callback(this,2);
		}		
	};
};
*/
void D_FilePicker::GetFilesNames(char* filename){
	 strcpy(filename,pSelectedFiles->GetContent());
	 };

void D_FilePicker::OnValid(UI_base * asker, std::function<void(UI_base * asker, D_FilePicker* caller, std::list<PathElement*> selection, bool valid)> function)
{
    onValid = function;
    onValidAsker = asker;

}
