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

//#include "snice.h"
//#include "prefs.h"
#include "../snice_UI.h"
//#include "viewports_array.h"
#include "widget/sub_menu.h"


/////////////////////////////////////////////
// Functions
/////////////////////////////////////////////

Option::Option(const string l, W_subMenu* submenu)
{
	//strncpy( label, l, 64 );
	//label[64] = '\0';
	label = l;

	optionSubMenu = submenu;
/*	if(optionSubMenu)
	{
		//l = new label(10,-4-20*optionnumber, 0, 1,"%*s >>", width/7-4, pCurrentOption->label);
		optionLabel = new W_label(5,-4, 0, 1,"%*s >>", 0, label);
	}
	// align files to the left
	else
	{*/
		optionLabel = new W_label(5,-4, 0, 1,"%s", label.c_str());
	/*}*/
}

Option::~Option()
{
    if (optionLabel) delete optionLabel;
}

W_subMenu::W_subMenu(int x, int y, int w, float red, float green, float blue)
	 :UI_widget(x, y, w, 10, red, green, blue)
{
	numberofoptions = 0;
	pSelectedOption = 0;
	onPickOption = 0;
}

W_subMenu::~W_subMenu()
{
	Flush();
	//pViewports->setIntercept(NULL);
}

void W_subMenu::AddOption(const string l, W_subMenu * optionsubMenu)
{
	int subMenumax = 64*font.charWidth+25;
	int stringSize = l.length()*font.charWidth;

	if (optionsubMenu)
	{
		stringSize += 10;//3* font.charWidth;
		//optionsubMenu->GetOption();
		optionsubMenu->SetPos(width,-20*numberofoptions);
		//optionsubMenu->parentMenu = this;
		AddChild(optionsubMenu);
	}

	options.Add((void*)new Option(l,optionsubMenu));

	pSelectedOption = (Option*)options.GetCurrentObjectPointer();
	if (pSelectedOption->optionSubMenu)
        pSelectedOption->optionSubMenu->SetVisible(false);

	numberofoptions++;

	// look how wide the label is and increase the subMenu width if necessary
	if (width < (int)(stringSize+25))
	{
		width = stringSize+25;

		if (width > subMenumax)
			width = subMenumax;

		Option* pCurrentOption;
		if (options.ToFirst())
			do
			{
				pCurrentOption = (Option*)options.GetCurrentObjectPointer();
				if (pCurrentOption->optionSubMenu)
					pCurrentOption->optionSubMenu->SetPosX(width);
			}while(options.ToNext());
	}

	height = 6+20*numberofoptions;

	//setLabel();
}

/*
void W_subMenu::setLabel(char *l)
{
	delete text;
	text = new label(posx+width/2-(strlen(l)*CHARLENGTH)/2-4, posy-2, 0, 1, l);
}

void W_subMenu::setLabel()
{
	char buttontext[256];
//	if (numberofoptions)
//	{

		//char option[256];
		//strncpy(&option[0], pSelectedOption->label, 64); // width/8-strlen(name)-8);
		//sprintf(buttontext, "%s: %s", name, option);

		sprintf(buttontext, "%s: %s", name, getString());
//	}
//	else
//		sprintf(buttontext, "%s", name);
	setLabel(&buttontext[0]);
}
*/
void W_subMenu::Draw()
{
	if (visible)
	{
		// glLoadIdentity();
	//	glScaled(1/zoom,1/zoom,1);
		glTranslated(posx, posy, 0);

		// shadow
		//if (pPrefs->GetCute())
		//{
			glColor4f(0.7f,0.7f,0.7f,0.2f);

			glEnable(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, textures.shadow.texID);
			textures.shadow.BindTex();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			int shadowsize = 8;

			glBegin(GL_QUADS);
				glTexCoord2f(0.75f,0.0f);
				glVertex2d(width,-10);
				glTexCoord2f(1.0f,0.0f);
				glVertex2d(width+shadowsize,-10);
				glTexCoord2f(1.0f,0.25f);
				glVertex2d(width+shadowsize,-26);
				glTexCoord2f(0.75f, 0.25f);
				glVertex2d(width,-26);

				glTexCoord2f(0.75f,0.25f);
				glVertex2d(width, -26);
				glTexCoord2f(1.0f,0.25f);
				glVertex2d(width+shadowsize,-26);
				glTexCoord2f(1.0f,0.75f);
				glVertex2d(width+shadowsize, -height);
				glTexCoord2f(0.75f,0.75f);
				glVertex2d(width, -height);

				glTexCoord2f(0.75f,0.75f);
				glVertex2d(width, -height);
				glTexCoord2f(1.0f,0.75f);
				glVertex2d(width+shadowsize, -height);
				glTexCoord2f(1.0f,1.0f);
				glVertex2d(width+shadowsize, -height-shadowsize);
				glTexCoord2f(0.75f,1.0f);
				glVertex2d(width, -height-shadowsize);

				glTexCoord2f(0.75f,0.75f);
				glVertex2d(width, -height);
				glTexCoord2f(0.75f,1.0f);
				glVertex2d(width, -height-shadowsize);
				glTexCoord2f(0.25f,1.0f);
				glVertex2d(shadowsize,-height-shadowsize);
				glTexCoord2f(0.25f,0.75f);
				glVertex2d(shadowsize,-height);

				glTexCoord2f(0.25f,0.75f);
				glVertex2d(shadowsize,-height);
				glTexCoord2f(0.25f,1.0f);
				glVertex2d(shadowsize,-height-shadowsize);
				glTexCoord2f(0.0f,1.0f);
				glVertex2d(0,-height-shadowsize);
				glTexCoord2f(0.0f,0.75f);
				glVertex2d(0,-height);
			glEnd();

			// fill the last bit
			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.75f,0.75f);
				glVertex2d(width,-height);
				glTexCoord2f(0.70f,0.75f);
				glVertex2d(width-5,-height);
				glTexCoord2f(0.75f,0.70f);
				glVertex2d(width,-height+5);
			glEnd();
		//}

		glDisable(GL_TEXTURE_2D);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		// Black outlining
		glColor4f(0.3f,0.3f,0.3f,0.5f);
		glBegin(GL_POLYGON);
			glVertex2d(6, 0);
			glVertex2d(width-6, 0);
			glVertex2d(width-2, -1);
			glVertex2d(width-1, -3);
			glVertex2d(width, -6);
			glVertex2d(width, -height+6);
			glVertex2d(width-1, -height+2);
			glVertex2d(width-3, -height+1);
			glVertex2d(width-6, -height);
			glVertex2d(6, -height);
			glVertex2d(2, -height+1);
			glVertex2d(1, -height+3);
			glVertex2d(0, -height+6);
			glVertex2d(0, -6);
			glVertex2d(1, -2);
			glVertex2d(3, -1);
			glVertex2d(6, 0);
		glEnd();

		// Fill
		glColor4f(1.0f, 1.0f, 1.0f,0.6f);
		glBegin(GL_POLYGON);
			glVertex2d(6, -1);
			glVertex2d(width-6, -1);
			glVertex2d(width-2, -2);
			glVertex2d(width-1, -4);
			glVertex2d(width-1, -6);
			glVertex2d(width-1, -height+6);
			glVertex2d(width-2, -height+2);
			glVertex2d(width-4, -height+1);
			glVertex2d(width-6, -height+1);
			glVertex2d(6, -height+1);
			glVertex2d(2, -height+2);
			glVertex2d(1, -height+4);
			glVertex2d(1, -height+5);
			glVertex2d(1, -7);
			glVertex2d(2, -2);
			glVertex2d(4, -1);
			glVertex2d(6, 0);
		glEnd();

		// draw the options
		Option* pCurrentOption;

		if (options.ToFirst())
		do
		{
			pCurrentOption = (Option*)options.GetCurrentObjectPointer();

			glEnable(GL_BLEND);
			glBegin(GL_QUADS);

			if (pSelectedOption == pCurrentOption)
				glColor4f(0.4f,0.4f,0.4f,0.4f);
			else glColor4f(0.6f,0.6f,0.6f,0.6f);


			glVertex2d(4, -4);
			glVertex2d(width-4,-4);
			glVertex2d(width-4,-4-18);
			glVertex2d(4,-4-18);

			glEnd();
			if(pCurrentOption->optionSubMenu)
			{
                glColor4f(0.2f,0.2f,0.2f,0.6f);
                glBegin(GL_TRIANGLES);
                glVertex2d(width-12, -8);
			    glVertex2d(width-6,-13);
			    glVertex2d(width-12,-18);
                glEnd();
            }
			// remove for not anti aliased font
			glColor4f(0.9f,0.5f,0.5f,0.9f);

            pCurrentOption->optionLabel->Draw();

		    glTranslated(0,-20,0);
		}while(options.ToNext());

        glTranslated(0,20*numberofoptions,0);

        //bubble effect
        /*if (FastComputer)
		{
    		glEnable(GL_TEXTURE_2D);
    		glEnable(GL_BLEND);

    		glBindTexture(GL_TEXTURE_2D, textures.specular.texID);
    		glColor4f(1.0f,1.0f,1.0f,0.4f);
    		glBegin(GL_QUADS);
    			glTexCoord2f(0.0f,1.0f);
    			glVertex2d(0, 0);
    			glTexCoord2f(1.0f,1.0f);
    			glVertex2d(width,0);
    			glTexCoord2f(1.0f,0.0f);
    			glVertex2d(width,-height);
    			glTexCoord2f(0.0f,0.0f);
    			glVertex2d(0,-height);
    		glEnd();

    		glDisable(GL_TEXTURE_2D);
		}*/

		glTranslated(-posx,-posy,0);
		UI_widget::Draw();
	}
}
/*
void W_subMenu::DrawMenu()
{

}*/

UI_base* W_subMenu::OnLButtonDown(int x, int y){return 0;}

UI_base* W_subMenu::OnLButtonUp(int x, int y)
{
    UI_widget::OnLButtonUp(x, y);
    if((pInterceptChild==this)&&(pSelectedOption)&&(!(pSelectedOption->optionSubMenu)))
	{
		if(onPickOption) onPickOption(this, GetOption());
	}
	pInterceptChild = 0;
	visible = false;
    return 0;
}

UI_base* W_subMenu::OnMouseMove(int x, int y, int prevx, int prevy)
{

    /*if ((pSelectedOption) && (pSelectedOption->optionSubMenu))
	{
		pSelectedOption->optionSubMenu->SetOption(0);
		pSelectedOption->optionSubMenu->SetVisible(true);

		if (((!Hittest(x,y)))&&(pSelectedOption->optionSubMenu->Hittest(x-posx,y-posy)))
		{
			//pViewports->setIntercept(pSelectedOption->optionSubMenu);
			return 0;
		}
	}*/

	/*if (!Hittest(x,y))
	{

		SetVisible(false);
		//pViewports->setIntercept(0);

		//if (pParentUI_base)pParentUI_base->Callback(this,2);
		return 0;
	}*/

	//setOption((parenty + posy -y -4) /20);
	if (!visible)return 0;

	if (Hittest(x,y))
    {
        SetOption((posy-y -4) /20);

    	pInterceptChild = this;
    }
    else
    {
        pInterceptChild = 0;
        UI_widget::OnMouseMove(x, y, prevx, prevy);
    }

    return this;
}

string W_subMenu::GetString()
{
	if (pSelectedOption)
	{
		if (pSelectedOption->optionSubMenu)
			return pSelectedOption->optionSubMenu->GetString();
		return pSelectedOption->label;
	}

	options.ToFirst();
	return ((Option*)(options.GetCurrentObjectPointer()))->label;
}

unsigned char W_subMenu::GetOption()
{
	unsigned char v = 1;
	if (options.ToFirst())
		do{
			if (pSelectedOption == (Option*)(options.GetCurrentObjectPointer()))
				return v;
			v++;
		}while(options.ToNext());

	return 0;
}

bool W_subMenu::SetOption(int v)
{
	options.ToFirst();
	while(v>0){
		options.ToNext();
		v--;
	}
	Option* pNewOption = (Option*)(options.GetCurrentObjectPointer());
	if (pNewOption!=pSelectedOption)
	{
    	if (pSelectedOption->optionSubMenu)
    	{
        	pSelectedOption->optionSubMenu->SetVisible(false);
        }
        if (pNewOption->optionSubMenu)
    	{
    		pNewOption->optionSubMenu->SetOption(0);
    		pNewOption->optionSubMenu->SetVisible(true);
    	}
        pSelectedOption=pNewOption;
    }
	return true;
}


bool W_subMenu::SetOption(string text)
{
	options.ToFirst();
	do{
		//if (!strcmp(((Option*)(options.GetCurrentObjectPointer()))->label, text.c_str()))// || ((((option*)(options.GetCurrentObjectPointer()))->optionSubMenu)&&((( (option*)(options.GetCurrentObjectPointer()) )->optionSubMenu)->setOption(text))))
		if (((Option*)(options.GetCurrentObjectPointer()))->label == text.c_str())
		{
			pSelectedOption = (Option*)(options.GetCurrentObjectPointer());
			return true;
		}

	}while(options.ToNext());
	return false;
}

void W_subMenu::Flush() // delete all options
{
	options.ToFirst();
	Option* pCurrentOption = (Option*)options.GetCurrentObjectPointer();

	while (pCurrentOption != NULL)
	{
		if (pCurrentOption->optionSubMenu)
			pCurrentOption->optionSubMenu->Flush();
		delete pCurrentOption;
		options.RemoveCurrent();
		numberofoptions--;

		pCurrentOption = (Option*)(options.GetCurrentObjectPointer());
	}

	//width = width;
	//height = height;
}

void W_subMenu::OnPickOption(void (*function)(W_subMenu* caller, unsigned char option))
{
    onPickOption = function;
}

void W_subMenu::LoadXML(TiXmlElement* element)
{

	// TODO : Loading of optionsubMenu

	TiXmlElement* nodeElement = 0;

	Flush();
	for( nodeElement = element->FirstChildElement(); nodeElement; nodeElement = nodeElement->NextSiblingElement() )
	{

		if(strncmp(nodeElement->Value(),"Option",6) == 0)
		{
			//int idOption;
			const char * label = nodeElement->Attribute("Label");

			if (label)

			{
				if ((strlen(label)<255)){
					char text[256];
					strcpy(text,label);
					//AddOption(text,idOption);
					AddOption(text,0);

					//if (selectedOptionPos == 0) {pSelectedOption = (option*)(options.GetCurrentObjectPointer());};

				}

			};
		}
		if(strncmp(nodeElement->Value(),"Menu",4) == 0)
		{
			const char * label = nodeElement->Attribute("Label");
			W_subMenu * tmpSubMenu;
			tmpSubMenu = new W_subMenu(0,0,0,0);
			tmpSubMenu->LoadXML(nodeElement);

			AddOption(label,tmpSubMenu);
		}
	}

	int selectedOptionPos = 0;
	element->Attribute( "Selected", &selectedOptionPos );
	SetOption(selectedOptionPos);
}

void W_subMenu::SaveXML(TiXmlElement* element)
{

	int selectedOptionPos =0;

	options.ToFirst();
	Option* pCurrentOption = (Option*)options.GetCurrentObjectPointer();


	while (pCurrentOption != NULL)
	{

			TiXmlElement optionElement( "Option" );

			optionElement.SetAttribute( "Label", pCurrentOption->label.c_str() );
			//optionElement.SetAttribute( "id", pCurrentOption->id );

			element->InsertEndChild( optionElement );


			if (pSelectedOption == pCurrentOption)
				element->SetAttribute( "Selected", selectedOptionPos );
			selectedOptionPos++;

		if (options.ToNext() == true)
				pCurrentOption = (Option*)(options.GetCurrentObjectPointer());
			else
				pCurrentOption = NULL;
	}
}

void W_subMenu::Set(string order)
{
	printf("->%s=%s\n", refName.c_str(), order.c_str());
	SetOption(order);
	//if (pParentUI_base)pParentUI_base->Callback(this,1);
};

