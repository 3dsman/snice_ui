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
#include "widget/array.h"
#include <list>

#define colSize 300

class W_fileSelector : public W_slidedPanel
{
protected:

	std::list<PathElement*> fileList;
	std::list<PathElement*> selected;
	std::vector<string> exts;
	W_array* array = nullptr;
    DirInfo * directory = nullptr;

    //sel options
	bool oneFile;
	bool shift;
    Color selColor = {.r=0.1,.g=0.1,.b=0.1,.a=0.2};

    void clearSelection();
	void ListDirectory();
	
	virtual UI_base* OnKeyPressed(int key, int action);
	
	
	std::function<void(UI_base * asker, W_fileSelector* caller, std::list<PathElement*> selection)> onChangeSelect = NULL;
    UI_base * onChangeSelectAsker = NULL;

public:

	W_fileSelector(int x, int y, int w, int h,int sx, int sy, string dir, string ext, float red = defaultR*2.5, float green = defaultG*2.5, float blue = defaultB*2.5);

	~W_fileSelector();
	
    static void StatArrayClickCell(UI_base * asker, W_array* caller, unsigned int x, unsigned int y);
    void ArrayClickCell( W_array* caller, unsigned int x, unsigned int y);

    std::list<PathElement*> GetSelectedList();
	string GetCurrentDirectory();
	void SetCurrentDirectory(string dirName);
	void SetExtensions(string extensions);
	
	void OnChangeSelect(UI_base * asker, std::function<void(UI_base * asker, W_fileSelector* caller, std::list<PathElement*> selection)> function);

/*
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
