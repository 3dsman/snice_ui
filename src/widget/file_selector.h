// crafter interface library
// Funny Farm
// copyright © 2002 Wybren van Keulen
// www.funnyfarm.tv

// File modified by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02

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


#ifndef _SNICE_fileSelector_H_
#define _SNICE_fileSelector_H_

//#include "include/glfw.h"
#include "file_system.h"
#include "widget/slided_panel.h"
#include <list>

#define colSize 300

class W_fileSelector : public W_slidedPanel
{
private:

	std::list<PathElement> fileList;
	//List labelList;
	DirInfo * directory;
	GLuint displayList;
	bool oneFile;
	char ext[256];
	bool shift;

	void RefreshSelectedFilesText();
	//void GenDisplayList();
	//void listDirectory(char * dir, char * ext);
	void ListDirectory();
	virtual void PanelOnLButtonDown(int x, int y, int px, int py);
	virtual void PanelOnLButtonUp(int x, int y);
	virtual void PanelOnMouseMove(int x, int y, int prevx, int prevy);
	virtual void PanelOnKeyPressed(int key, int action);

	//virtual void PanelDraw();

public:

	W_fileSelector(int x, int y, int w, int h,int sx, int sy, string dir, string ext, float r = 0.8f, float g = 0.8f, float b = 0.8f);

	~W_fileSelector();

	void GetSelectedList(List * filenames);
	string GetCurrentDirectory();
	void SetCurrentDirectory(string dirName);
	void SetExtensions(char * extensions);

	
	
/*	void Draw();
	void setColor(float r, float g, float b);

	void getColor(float * r, float * g, float * b);
	
	bool hittest(int x, int y);
	void fileSelector::onLButtonDown(int x, int y, int px, int py);

	void fileSelector::onLButtonUp(int x, int y);

	void fileSelector::onMouseMove(int x, int y, int prevx, int prevy);
	
	void LoadXML(TiXmlElement* element);

	void SaveXML(TiXmlElement* element);*/

};

#endif // _SNICE_fileSelector_H_
