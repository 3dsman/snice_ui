// FilePicker.h: FilePicker dialog box.
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
// FilePicker.cpp
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

#ifndef _SNICE_FilePicker_H_
#define _SNICE_FilePicker_H_

#include "UI_dialog.h"

class W_fileSelector;
class W_menu;
class W_textbox;
class W_button;

class D_FilePicker : public UI_dialog
{
	
private:
	W_menu* pStartDir;
	W_fileSelector* pFileSelector;
	//colordisplay* pFileView;
	W_textbox* pSelectedFiles;
	W_button* pValid;
	W_button* pCancel;
	W_menu* pFileExt;
	int surfacex;
	int	surfacey;
	List selectedFileList;
	List extensions;
	char filesName[256];
	
	bool active;
public:

	//D_FilePicker();
/** the extension string is represented like that: "extDescription|*.ext;extDescription|*.ext|*.ext|*.ext|*.ext"*/
	D_FilePicker(int x, int y, char * name, char * exts);

	~D_FilePicker();

	virtual void Callback(UI_base * pCallObject, unsigned char callIndex );

	void SetSliders();
	
	void GetFilesNames(char* filename);

};

#endif // _SNICE_FilePicker_H_
