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
#include "../snice_UI.h"
//#include "viewports_array.h"
#include "widget/text_box.h"


W_textbox::W_textbox(int x, int y, int w, int h, string l, string c,bool num, bool integer, bool deci, bool contour, float red, float green, float blue)
		:UI_widget(x, y, w, h, r, g, b)
{

	initialWidth = w;
	number = num;
	decimal = deci;
    integ = integer;

	action = false;

    drawContour = contour;

	refName = l;

    prompt = l;
	//sprintf(prompt, "%s", l.c_str());
	//text = new W_label(posx + ( min(0,width -(strlen(prompt) * font.charWidth)))/2 , posy-2, width-6, 1, prompt);

	text = new W_label(0 , -1, width-6, 1, prompt);
	this->AddChild(text);
	//sprintf(contents, "%s", c.c_str());
	contents = c;
	SetLabel();

	onSetContent = 0;
}

W_textbox::~W_textbox()
{
    //UI_widget::~UI_widget();
	//delete text;
}

void W_textbox::SetLabel(string l)
{
		//delete text;
		//text = new W_label(posx + ( min(0,width -(strlen(l) * font.charWidth)))/2 , posy-2, width-6, 1, l);
		//text->SetPos(posx + ( min(0,width -(strlen(l) * font.charWidth)))/2 , posy-2);
		text->SetWidth(width-6);
		text->SetText(l);
}

void W_textbox::SetLabel()
{
    //char buttontext[256];
    string texte = contents;
	if (action) {
        width = max(initialWidth,(prompt.size() + contents.size() + 3) * font.charWidth);
        texte.insert(curPos,"|");
	};

	if (prompt.size())
        texte = prompt+": "+texte;
	   //sprintf(buttontext, "%s: %s", prompt.c_str(), contents.c_str());
	//else
	   //sprintf(buttontext, "%s", contents.c_str());

	//SetLabel(&buttontext[0]);
	SetLabel(texte);
}

void W_textbox::SetContent(const string c)
{
	//if (strlen(c) < 255)
	//{
	contents=c;
		//strcpy(contents,c);
    SetLabel();
	//}
}

char* W_textbox::GetContent()
{
	return &contents[0];
}

void W_textbox::SetWidth(int w)
{
    UI_base::SetWidth(w);
    initialWidth = width;
    SetLabel();
}

void W_textbox::OnSetContent(void (*function)(W_textbox* caller, string content))
{
    onSetContent = function;
}

void W_textbox::Draw()
{
    if(drawContour)
    {
        glTranslated(posx, posy, 0);
        // Black outlining
        /*glColor4f(0.3f,0.3f,0.3f,0.5f);
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
        glEnd();*/

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        // Fill
        // glColor4f(1.0f, 1.0f, 1.0f,0.6f);
        // glColor4f(0.64f, 0.59f, 0.53f,1.0f);
        glColor4f(0.75f, 0.75f, 0.75f,1.0f);
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

        // draw the border
        glColor4f(1.0f,1.0f,1.0f,0.7f);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures.slider.texID);				// Select Our Font Texture
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,1.0f);
            glVertex2d(0, 0);
            glTexCoord2f(0.25f,1.0f);
            glVertex2d(8, 0);
            glTexCoord2f(0.25,0.75f);
            glVertex2d(8, -8);
            glTexCoord2f(0.0f,0.75f);
            glVertex2d(0, -8);

            glTexCoord2f(0.49f,1.0f);
            glVertex2d(8, 0);
            glTexCoord2f(0.51f,1.0f);
            glVertex2d(width-8, 0);
            glTexCoord2f(0.51f,0.75f);
            glVertex2d(width-8, -8);
            glTexCoord2f(0.49f,0.75f);
            glVertex2d(8, -8);

            glTexCoord2f(0.75f,1.0f);
            glVertex2d(width-8, 0);
            glTexCoord2f(1.00f,1.0f);
            glVertex2d(width, 0);
            glTexCoord2f(1.00f,0.75f);
            glVertex2d(width, -8);
            glTexCoord2f(0.75f,0.75f);
            glVertex2d(width-8, -8);

            glTexCoord2f(0.75f,0.75f);
            glVertex2d(width-8, -8);
            glTexCoord2f(1.00f,0.75f);
            glVertex2d(width, -8);
            glTexCoord2f(1.00f,0.25f);
            glVertex2d(width, -height+8);
            glTexCoord2f(0.75f,0.25f);
            glVertex2d(width-8, -height+8);

            glTexCoord2f(0.75f,0.25f);
            glVertex2d(width-8, -height+8);
            glTexCoord2f(1.00f,0.25f);
            glVertex2d(width, -height+8);
            glTexCoord2f(1.00f,0.00f);
            glVertex2d(width, -height);
            glTexCoord2f(0.75f,0.00f);
            glVertex2d(width-8, -height);

            glTexCoord2f(0.25f,0.25f);
            glVertex2d(8, -height+8);
            glTexCoord2f(0.75f,0.25f);
            glVertex2d(width-8, -height+8);
            glTexCoord2f(0.75,0.00f);
            glVertex2d(width-8, -height);
            glTexCoord2f(0.25f,0.00f);
            glVertex2d(8, -height);

            glTexCoord2f(0.0f,0.25f);
            glVertex2d(0, -height+8);
            glTexCoord2f(0.25f,0.25f);
            glVertex2d(8, -height+8);
            glTexCoord2f(0.25f,0.00f);
            glVertex2d(8, -height);
            glTexCoord2f(0.0f,0.00f);
            glVertex2d(0, -height);

            glTexCoord2f(0.00f,0.75f);
            glVertex2d(0, -8);
            glTexCoord2f(0.25f,0.75f);
            glVertex2d(8, -8);
            glTexCoord2f(0.25f,0.25f);
            glVertex2d(8, -height+8);
            glTexCoord2f(0.00f,0.25f);
            glVertex2d(0, -height+8);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        // draw the cursor
        //glColor4f(0.9f,0.3f,0.1f,0.6f);
        //glBegin(GL_QUADS);
        //	glVertex2d(,);
        //	glVertex2d(,);
        //	glVertex2d(,);
        //	glVertex2d(,);
        //glEnd();
        glTranslated(-posx,-posy,0);
    }
	glColor4f(0.7f,0.7f,0.7f,0.4f);
	UI_widget::Draw();
}

UI_base* W_textbox::OnLButtonDown(int x, int y)
{
	if (Hittest(x,y))
	{
		pInterceptChild = this;
		return this;
	}
	return NULL;
}


UI_base* W_textbox::OnLButtonUp(int x, int y)
{
    if (pInterceptChild == this)
	{
       	if (Hittest(x,y))
    	{
            if (action)
            {
        		unsigned int position = (x - parentx - posx )/font.charWidth - (prompt.size() + 2);
        		position = min(max(position,0),contents.size());


        		//if the clic was after the cursor the clic is on the next character
        		if (position > curPos)
        			curPos = position-1 ;
        		else
        			curPos = position ;
        	}
        	else
        	{
                 // if the textbox were clicked
        		curPos = contents.size();
        		action = true;

        	}

        	SetLabel();
    		// we must intercept future commands (keyboard inputs)
            return this;
        }else
        {
            if (action)
            {

        		//if the chain is empty and must contain a number then write "0"
        		if ((number)&&(contents[0] == 0))
        			contents = "0";

        		// put the width at his initial size
        		width = initialWidth;
        		action = false;
    	        SetLabel();
    	        if(onSetContent) onSetContent(this, contents);
            }
    		//free the inteception pointers
            pInterceptChild = 0;
            return 0;
    	}
    }
    pInterceptChild = 0;
    return 0;

}

UI_base* W_textbox::OnMouseMove(int x, int y, int prevx, int prevy)
{
	if (pInterceptChild) return this;
	return 0;
}


UI_base* W_textbox::OnKeyPressed(int key)
{
    if (action)
    {
        switch (key)
    	{
    		case SNICEUI_KEY_BACKSPACE :
    				{
    					if (curPos>0)
    					{
    						contents.erase(curPos-1,1);
    						curPos--;
    					}
    					break;
    				}

    		case SNICEUI_KEY_DELETE :
    				{
    					if ((curPos + 1) < contents.size())
    					{
    						contents.erase(curPos,1);
    					}
    					break;
    				}

    		case SNICEUI_KEY_LEFT :
    				{
    					// move the cursor to the left
    					if (curPos>0)
    						curPos--;
    					break;
    				}

    		case SNICEUI_KEY_RIGHT :
    				{
    					// move the cursor to the right
    					if ((curPos + 1) < contents.size())
    						curPos++;
    					break;
    				}

    		case SNICEUI_KEY_ENTER :
    		case SNICEUI_KEY_KP_ENTER:
    			{
    				//if the chain is empty and must contain a number then write "0"
    				if ((number)&&(contents.size()==0))
    				   contents = "0";

    				// put the width at his initial size
    				width = initialWidth;
    				// disable the textbox edit mode
        			action = false;
        			//then set the label
    	            SetLabel();

    	            if(onSetContent) onSetContent(this, contents);

            		//free the inteception pointers
                    pInterceptChild = 0;
                    return 0;
        		}
    	}
    	//refresh the label
    	SetLabel();

        return this;
    }

	//if (pInterceptChild) return this;
	return UI_base::OnKeyPressed(key);

}

//void W_textbox::OnKeyPressedIntercept(int key)
//{
//	int pos = strlen(contents)-1;

//	if(key >= 65 && key <= 90)
//	{
		/*if ((keys[GLFW_KEY_LCTRL] || keys[GLFW_KEY_RCTRL]) && (key== 86))
		{
			//Et yop la fonction coller
			//paste function

			OpenClipboard (NULL) ;
			HGLOBAL hGlobal ;

			if (hGlobal = GetClipboardData (CF_TEXT))
			{

				char *  pGlobal ;
				char pText[255] ;

				pGlobal = (char*)GlobalLock (hGlobal) ;
				lstrcpy (&pText[0], pGlobal) ;
				if (((GlobalSize (hGlobal)) + strlen(contents))<250)
				{
					contents[pos] = '\0';
					strcat(contents,pText);
					strcat(contents,"|");
					pos = strlen(contents)-1;
					width = width + (GlobalSize (hGlobal))*7;
				}
			 }
			CloseClipboard () ;

		}
	}
*/
UI_base* W_textbox::OnCharPressed(int character)
{
	if((action)&&( character > 0 && character < 256 )&&
    (( character >= 48 && character <= 57 )||((character == '.')&&decimal)||((character == '-')&&integ)||(!number)))
		{

            contents.insert(curPos, 1, (char) character);
            curPos++;
			//dont forget to refresh the label
			SetLabel();
		}

	return UI_base::OnCharPressed(character);
}

void W_textbox::LoadXML(TiXmlElement* element)
{
	const char * textElement = element->Attribute("Text");

	// i look if there is no problem
	if ((textElement!=NULL)&&(strlen(textElement)<255)){
		contents = textElement;
		SetLabel();
	};
}

void W_textbox::SaveXML(TiXmlElement* element)
{
	//creation of the ColorBand xml flag
	TiXmlElement NodeTextBox( refName.c_str() );
	NodeTextBox.SetAttribute ("Text", GetContent());
	element->InsertEndChild( NodeTextBox );
}


void W_textbox::Set(char* order)
{
	printf("->%s=%s\n", refName.c_str(), order);
	SetContent(order);
	//if (pParentUI_base) pParentUI_base->Callback(this,1);
};

