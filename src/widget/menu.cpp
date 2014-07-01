// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
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
/*
#include "snice.h"
#include "prefs.h"

#include "viewports_array.h"
*/
#include "widget/sub_menu.h"
#include "widget/menu.h"

/////////////////////////////////////////////
// Functions
/////////////////////////////////////////////
/*
option::option(char* l, menu* submenu)
{
	strncpy( label, l, 64 );
	label[64] = '\0';
	//id = i;
	this->subMenu = submenu;
}*/

W_menu::W_menu(int x, int y, int w, int h, char *l, float red, float green, float blue)
	   :W_button(x, y, w, h, l)	
{
	childMenu = new W_subMenu(0,0,w,h);
	childMenu->SetVisible(false);
	AddChild(childMenu);
	childMenu->OnPickOption(pickOption));
	
}

W_menu::~W_menu()
{
	//pViewports->setIntercept( NULL);
}

void W_menu::pickOption(W_subMenu* caller, unsigned char option)
{
    SetOption(option);
};

void W_menu::SetLabel(char *l)
{
	
	char optionText[256];
		strcpy(optionText,l);
		strcat(optionText,": ");
		strcat(optionText,childMenu->GetString());
		text->SetText(l);
		//delete text;
		//text = new W_label(width/2-(strlen(optionText)*7)/2-4, -2, 0, 1, optionText);
}

void W_menu::AddOption(char *l, W_subMenu * optionsubMenu)
{
	childMenu->AddOption(l,optionsubMenu);
	SetLabel(refName);
}


UI_base* W_menu::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
		childMenu->SetVisible(true);
		//pViewports->setIntercept( childMenu);
	}

}

UI_base* W_menu::OnLButtonUp(int x, int y){}

void W_menu::Callback(UI_base * pCallObject, unsigned char callIndex )
{

	if ((childMenu == pCallObject) && (callIndex == 1))
	{
		SetLabel(refName);
	}
	if ((pParentUI_base)&&(childMenu == pCallObject))
	{
//		pParentUI_base->Callback(this,callIndex);
	}
}

char* W_menu::GetString()
{
	if (childMenu)
			return childMenu->GetString();
	printf("bug dans menu::getString()");
	return NULL;
}

int W_menu::GetOption()
{	
	if (childMenu)
		return childMenu->GetOption();
	return 0;
}

void W_menu::SetOption(int v)
{	
	if (childMenu)
	{
		childMenu->SetOption(v);
		SetLabel(refName);
	}
}


void W_menu::SetOption(char * text)
{	
	if (childMenu)
	{
		childMenu->SetOption(text);
		SetLabel(refName);
	}
}

void W_menu::Flush() // delete all options
{
	if (childMenu)
		childMenu->Flush();
}


void W_menu::LoadXML(TiXmlElement* element)
{
	const char * textElement = element->Attribute("Option");

	char option[256];
	// i look if there is no problem
	if ((textElement!=NULL)&&(strlen(textElement)<255)){
		strcpy(option, textElement);
		SetOption(option);
	};
}

void W_menu::SaveXML(TiXmlElement* element)
{
	
	//creation of the ColorBand xml flag
	TiXmlElement NodeMenu( refName );
	NodeMenu.SetAttribute ("Option", GetString());
	element->InsertEndChild( NodeMenu );
}

void W_menu::Set(char* order)
{
	printf("->%s=%s\n", refName, order);
	childMenu->Set(order);
	//SetOption(order);
	
};

