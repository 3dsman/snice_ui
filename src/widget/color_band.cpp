// crafter interface library
// Funny Farm
// copyright � 2002 Wybren van Keulen
// www.funnyfarm.tv

// File modified by Tricoire Sebastien
// Date of creation : 2004 06 02
///
// File modified by Lionel Allorge
// Date of modification : 2004 06 02
//
// File modified by Tricoire Sebastien
// Date of creation : 2005 08 21
///

/* ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software{} you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation{} either version 2
 * of the License, or (at your option) any later version. The Blender
 * Foundation also sells licenses for use in proprietary software under
 * the Blender License.  See http://www.blender.org/BL/ for information
 * about this.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program{} if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2002-2003 by Funny Farm.
 * www.funnyfarm.tv
 *
 * ***** END GPL LICENSE BLOCK *****
 */

//#include "global.h"
#include "../snice_UI.h"
//#include "interpolation.h"
#include "widget/color_band.h"
#include <math.h>

W_colorBand::colorbandItem * W_colorBand::NewColorbandItem(float position, float red, float green, float blue, float alpha){
	W_colorBand::colorbandItem * tmp;
	tmp = new colorbandItem;
	tmp->pos = position;
	tmp->r = red;
	tmp->g = green;
	tmp->b = blue;
	tmp->a = alpha;
	return tmp;
}

W_colorBand::W_colorBand(int x, int y, int w, int h, string name)
		  :UI_widget(x, y, w, h)
{
	interpolation = 1;

	refName=name;

	draggingcolorbandItem = false;

	listofcolorbandItems.push_back(NewColorbandItem(0.0f,0.0f,0.0f,0.0f,1.0f));
	listofcolorbandItems.push_back(NewColorbandItem(1.0f,1.0f,1.0f,1.0f,1.0f));
	pActiveColorBandItem = *listofcolorbandItems.end();

}

W_colorBand::~W_colorBand()
{
	FlushColorNode();
}

bool W_colorBand::compareColorbandItemsPos (const colorbandItem* first, const colorbandItem* second)
{
  return ( first->pos < second->pos );
}

double W_colorBand::LinearInterpolate1D(double a, double b, double x) {
    return (b-a)*x+a;
  }

double W_colorBand::CosineInterpolate1D(double a, double b, double x) {
    double amp = (a-b)/2;
    return a-amp+amp*cos(PI*x);
  }

void W_colorBand::FlushColorNode()
{
	std::list<colorbandItem*>::iterator i = listofcolorbandItems.begin();
	while (i != listofcolorbandItems.end())
	{
			delete(*i);
			listofcolorbandItems.erase(i++);
	}
	pActiveColorBandItem=NULL;
	/*
	listofcolorbandItems.ToFirst();
	colorbandItem* pCurrentColourbandnode = (colorbandItem*) listofcolorbandItems.GetCurrentObjectPointer();

	while (pCurrentColourbandnode != NULL)
	{
		listofcolorbandItems.RemoveCurrent();
		delete pCurrentColourbandnode;


		pCurrentColourbandnode = (colorbandItem*)(listofcolorbandItems.GetCurrentObjectPointer());
	}*/
}

void W_colorBand::RemoveActiveColorNode()
{
	// go through the list until the active node is found and delete it
	if (listofcolorbandItems.size()>1)
	{
		listofcolorbandItems.remove(pActiveColorBandItem);
		delete(pActiveColorBandItem);
		pActiveColorBandItem = listofcolorbandItems.back();
		
	}
}

void W_colorBand::SortList()
{
	listofcolorbandItems.sort(compareColorbandItemsPos);
}

void W_colorBand::AddColorNode(float Pos, float Red, float Green, float Blue, float Alpha)
{
	if ((Red<=1)&&(Red>=0)&&(Green<=1)&&(Green>=0)&&(Blue<=1)&&(Blue>=0)&&(Alpha<=1)&&(Alpha>=0)&&(Pos<=1)&&(Pos>=0))
	{
		colorbandItem* tempnode = NewColorbandItem(Pos,Red,Green,Blue,Alpha);
		listofcolorbandItems.push_back( tempnode);
		SortList();
		pActiveColorBandItem = tempnode;
	}
}

void W_colorBand::SetActiveColor(float Red,float Green,float Blue,float Alpha)
{
	if (pActiveColorBandItem)
	{
		pActiveColorBandItem->r = Red;
		pActiveColorBandItem->g = Green;
		pActiveColorBandItem->b = Blue;
		pActiveColorBandItem->a = Alpha;
	}
}

void W_colorBand::GetActiveColor(float* Red,float* Green,float* Blue,float* Alpha)
{
	if (pActiveColorBandItem)
	{
		*Red = pActiveColorBandItem->r;
		*Green = pActiveColorBandItem->g;
		*Blue = pActiveColorBandItem->b;
		*Alpha = pActiveColorBandItem->a;
	}
	else
	{
		*Red = 0;
		*Green = 0;
		*Blue = 0;
		*Alpha = 0;
	}
}

float W_colorBand::GetActiveColor(int RGBA)
{
	if (pActiveColorBandItem)
	{
		switch (RGBA)
		{
		case RED:
			return pActiveColorBandItem->r;
		case GREEN:
			return pActiveColorBandItem->g;
		case BLUE:
			return pActiveColorBandItem->b;
		case ALPHA:
			return pActiveColorBandItem->a;
		default:
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void W_colorBand::GetColorAt(float* Red,float* Green,float* Blue,float* Alpha, float pos)
{

	/*listofcolorbandItems.ToFirst();
	colorbandItem* pCurrentColourbandnode = (colorbandItem*) listofcolorbandItems.GetCurrentObjectPointer();

	listofcolorbandItems.ToNext();
	colorbandItem* pNextColourbandnode = (colorbandItem*) listofcolorbandItems.GetCurrentObjectPointer();
*/
	//******************************************  Remplissage du tableau *****************************************
	std::list<colorbandItem*>::iterator iter = listofcolorbandItems.begin();
	colorbandItem* pCurrentColourbandnode = (*iter++);
	colorbandItem* pNextColourbandnode = NULL;
	if (listofcolorbandItems.size()>1)
	{
		pNextColourbandnode = (*iter++);
		while ((iter != listofcolorbandItems.end())&&(((*iter)->pos) < pos))
		{
			pCurrentColourbandnode = pNextColourbandnode;
			pNextColourbandnode = (*iter++);
		}
	}
		if ((pNextColourbandnode))
		{
			// we calculate the relative position of the input position between the previous and next Colourbandnode
			float proportion;
			float NextRelative = ( pNextColourbandnode->pos - pCurrentColourbandnode->pos );
			float PosRelative = pos - ( pCurrentColourbandnode->pos );
			proportion = PosRelative / NextRelative;

			// choice of the interpolation
// TODO reactiver l'interpolation
			switch (interpolation)
			{
				case 1:
				{
					*Red = LinearInterpolate1D(pCurrentColourbandnode->r,pNextColourbandnode->r,proportion);
					*Green = LinearInterpolate1D(pCurrentColourbandnode->g,pNextColourbandnode->g,proportion);
					*Blue = LinearInterpolate1D(pCurrentColourbandnode->b,pNextColourbandnode->b,proportion);
					*Alpha = LinearInterpolate1D(pCurrentColourbandnode->a,pNextColourbandnode->a,proportion);
					break;
				};
				case 2:
				{
					*Red = CosineInterpolate1D(pCurrentColourbandnode->r,pNextColourbandnode->r,proportion);
					*Green = CosineInterpolate1D(pCurrentColourbandnode->g,pNextColourbandnode->g,proportion);
					*Blue = CosineInterpolate1D(pCurrentColourbandnode->b,pNextColourbandnode->b,proportion);
					*Alpha = CosineInterpolate1D(pCurrentColourbandnode->a,pNextColourbandnode->a,proportion);

					break;
				};
			}
		/*}else
		{
			*Red =  pNextColourbandnode->r;
			*Green = pNextColourbandnode->g;
			*Blue = pNextColourbandnode->b;
			*Alpha = pNextColourbandnode->a;
		}*/

	}else
	{
		*Red = pCurrentColourbandnode->r;
		*Green = pCurrentColourbandnode->g;
		*Blue = pCurrentColourbandnode->b;
		*Alpha = pCurrentColourbandnode->a;
	}


}

void W_colorBand::SetInterpolation(char i)
{
	if (i > 0) interpolation = i;
}

void W_colorBand::GetInterpolation(char i)
{
	i = interpolation;
}

void W_colorBand::SetHeight(int h)
{
	if (h > 0){
		height = h;
	}
}

void W_colorBand::SetWidth(int w)
{
	if (w > 0){
		width = w;
	}
}

void W_colorBand::SetPosX(int x)
{
	posx = x;
}

void W_colorBand::SetPosY(int y)
{
	posy = y;
}

void W_colorBand::Draw()
{
	// draw a stripe in the buttons to indicate the current value
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Draw the colourband
	// go through the list of colourband nodes, maybe sort the nodes
	// make a rectangle with vertex colours
	// make a triangle with stripe which represents the node

	glTranslated(posx,posy,0);


	bool bw = true;
	// first make a grid to show the alpha through
	for ( int loopx = 0; loopx < width-8; loopx+=10 )
	{
        bw = loopx%20;
		for ( int loopy = 0; loopy < height; loopy+=10 )
		{
			glBegin(GL_QUADS);
				glColor4f(bw ? 0.0f : 1.0f,bw ? 0.0f : 1.0f,bw ? 0.0f : 1.0f,1.0f);
				glVertex2d(loopx,-loopy);
				glVertex2d(min(width-8,loopx+10),-loopy);
				glVertex2d(min(width-8,loopx+10),-min(height,loopy+10));
				glVertex2d(loopx,-min(height,loopy+10));
			glEnd();

			bw = !bw;	// to get a checkerlike pattern
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// draw the colourband from 0.0 to 1.0
	std::list<colorbandItem*>::iterator iter = listofcolorbandItems.begin();
	colorbandItem* pCurrentColorbandItem = *iter;

	// first half of the first quad
	glBegin(GL_QUADS);
		glColor4f(pCurrentColorbandItem->r,pCurrentColorbandItem->g,pCurrentColorbandItem->b,pCurrentColorbandItem->a);
		glVertex2d(0,-height);
		glVertex2d(width-8,-height);

	while (iter != listofcolorbandItems.end())
	{
		pCurrentColorbandItem = *iter;
		// second half of the quad
			glColor4f(pCurrentColorbandItem->r,pCurrentColorbandItem->g,pCurrentColorbandItem->b,pCurrentColorbandItem->a);
			glVertex2d(width-8,-height*(1-pCurrentColorbandItem->pos));
			glVertex2d(0,-height*(1-pCurrentColorbandItem->pos));
		glEnd();

		// first half of the next quad
		glBegin(GL_QUADS);
			glColor4f(pCurrentColorbandItem->r,pCurrentColorbandItem->g,pCurrentColorbandItem->b,pCurrentColorbandItem->a);
			glVertex2d(0,-height*(1-pCurrentColorbandItem->pos));
			glVertex2d(width-8,-height*(1-pCurrentColorbandItem->pos));

		iter++;
	}
		// close the quad
		glVertex2d(width-8,0);
		glVertex2d(0,0);
	glEnd();

	// draw the border
	glColor4f(1.0f,1.0f,1.0f,0.7f);

	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textures.slider.texID);//textures[8].texID);
	textures.slider.BindTex();
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

	/*glBindTexture(GL_TEXTURE_2D, textures[10].texID);
	glColor4f(1.0f,1.0f,1.0f,0.6f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,1.0f);
		glVertex2d(0, 0);
		glTexCoord2f(1.0f,1.0f);
		glVertex2d(width, 0);
		glTexCoord2f(1.0f,0.0f);
		glVertex2d(width,-height);
		glTexCoord2f(0.0f,0.0f);
		glVertex2d(0, -height);
	glEnd();*/

	glDisable(GL_TEXTURE_2D);

	// draw the trianlge and stripe to indicate a node
	iter = listofcolorbandItems.begin();
	pCurrentColorbandItem = *iter;

	while (pCurrentColorbandItem != NULL)
	{
		if (pCurrentColorbandItem == pActiveColorBandItem)
			glColor4f(1.0f,1.0f,1.0f,0.8f);
		else
			glColor4f(0.0f,0.0f,0.0f,0.5f);

		glTranslated(0, -height+(pCurrentColorbandItem->pos/1.0f)*height, 0);
		glBegin(GL_QUADS);
			glVertex2d(0,1);
			glVertex2d(width-8,1);
			glVertex2d(width-8,-1);
			glVertex2d(0,-1);
		glEnd();

		glBegin(GL_TRIANGLES);
			glVertex2d(width-8,0);
			glVertex2d(width,3);
			glVertex2d(width,-3);
		glEnd();
		glTranslated(0, -(-height+(pCurrentColorbandItem->pos/1.0f)*height), 0);

		if (iter++ != listofcolorbandItems.end())
			pCurrentColorbandItem = *iter;
		else
			pCurrentColorbandItem = NULL;
	}

	glTranslated(-posx,-posy,0);

}

UI_base* W_colorBand::OnLButtonDown(int x, int y)
{

	if (Hittest(x,y))
	{
		colorbandItem* pCurrentColorbandItem;
		for(std::list<colorbandItem*>::iterator iter = listofcolorbandItems.begin(); iter != listofcolorbandItems.end(); iter ++)
			{
				pCurrentColorbandItem = *iter;

				if (y > posy - height+pCurrentColorbandItem->pos*height-4.0f && y < posy - height+pCurrentColorbandItem->pos*height+4.0f)
				{
					if (pActiveColorBandItem != pCurrentColorbandItem)
					{
						pActiveColorBandItem = pCurrentColorbandItem;
					}
					draggingcolorbandItem = true;
                    pInterceptChild = this;
                    return this;
				}
			}


		if (!draggingcolorbandItem)
		{
			float r,g,b,a;
			GetColorAt(&r,&g,&b,&a,(float)(y+height-posy)/(float)(height));
			colorbandItem* tempnode = NewColorbandItem((float)(y+height-posy)/(float)(height),r,g,b,a);

			listofcolorbandItems.push_back( tempnode);
			SortList();
			pActiveColorBandItem = tempnode;

			//if (pParentUI_base) pParentUI_base->Callback(this,2);

			draggingcolorbandItem = true;
            pInterceptChild = this;
            return this;

		}
	}
    pInterceptChild = 0;
    return 0;
}

UI_base* W_colorBand::OnLButtonUp(int x, int y)
{
    UI_widget::OnLButtonUp(x, y);
	draggingcolorbandItem = false;
	pInterceptChild = 0;
    return 0;
}

UI_base* W_colorBand::OnMouseMove(int x, int y, int prevx, int prevy)
{
	if(pInterceptChild == this)
        {
        if (draggingcolorbandItem)
        {
			pActiveColorBandItem->pos = max(min(1+float(y-posy)/float(height),1.0f),0.0f);

            if ((x > posx + width + 50)&&(listofcolorbandItems.size()>1))
            {
                RemoveActiveColorNode();
                draggingcolorbandItem=false;
            };

            SortList();
        }
		return this;
	}
    return 0;

}
/*
void W_colorBand::LoadXML(TiXmlElement* element)
{

	TiXmlElement* nodeElement = 0;

	FlushColorNode();
	for( nodeElement = element->FirstChildElement(); nodeElement; nodeElement = nodeElement->NextSiblingElement() )
	{

		if(strncmp(nodeElement->Value(),"ColorBar",9) == 0)
		{
			double r, g, b, a, pos;

			if ((nodeElement->QueryDoubleAttribute("Red",&r) != TIXML_NO_ATTRIBUTE)
				&& (nodeElement->QueryDoubleAttribute("Green",&g) != TIXML_NO_ATTRIBUTE)
				&& (nodeElement->QueryDoubleAttribute("Blue",&b) != TIXML_NO_ATTRIBUTE)
				&& (nodeElement->QueryDoubleAttribute("Alpha",&a) != TIXML_NO_ATTRIBUTE)
				&& (nodeElement->QueryDoubleAttribute("Pos",&pos) != TIXML_NO_ATTRIBUTE))
			{
				AddColorNode((float)pos, (float)r, (float)g, (float)b, (float)a);
			};
		}
	}
	const char * interpolationAttribute = element->Attribute("Interpolation");
	interpolation = 1;
	if (interpolationAttribute!=NULL){
		if(strncmp(interpolationAttribute,"linear",6) == 0){interpolation = 1;};
		if(strncmp(interpolationAttribute,"cosine",6) == 0){interpolation = 2;};
	}

}

void W_colorBand::SaveXML(TiXmlElement* element)
{
	char buf[256];


		//creation of the ColorBand xml flag
	TiXmlElement NodeColorBand( refName.c_str() );

	if (interpolation == 1)
		sprintf( buf, "linear" );

	if (interpolation == 2)
		sprintf( buf, "cosine" );

	NodeColorBand.SetAttribute( "Interpolation",  buf );
	//delete buf;



	listofcolorbandItems.ToFirst();
	colorbandItem* pCurrentColourbandnode = (colorbandItem*)(listofcolorbandItems.GetCurrentObjectPointer());
	while (pCurrentColourbandnode != NULL)
	{
			TiXmlElement colorBar( "ColorBar" );
			char buf[256];
			sprintf( buf, "%f", pCurrentColourbandnode->r );
			colorBar.SetAttribute( "Red", buf );
			sprintf( buf, "%f", pCurrentColourbandnode->g );
			colorBar.SetAttribute( "Green",  buf );
			sprintf( buf, "%f", pCurrentColourbandnode->b );
			colorBar.SetAttribute( "Blue",  buf );
			sprintf( buf, "%f", pCurrentColourbandnode->a );
			colorBar.SetAttribute( "Alpha",  buf );
			sprintf( buf, "%f", pCurrentColourbandnode->pos );
			colorBar.SetAttribute( "Pos",  buf );
			NodeColorBand.InsertEndChild( colorBar );
			//delete buf;
		if (listofcolorbandItems.ToNext() == true)
		{
			pCurrentColourbandnode = (colorbandItem*)(listofcolorbandItems.GetCurrentObjectPointer());
		}
		else
			pCurrentColourbandnode = NULL;
	}
	element->InsertEndChild( NodeColorBand );

}
void W_colorBand::Set(char* order)
{
 	printf("->%s", refName.c_str());
 	char value[256];
	int i=0;
 	for (i=0; i<256; ++i)
	    value[i]=0;
	char* separator = strchr(order,'=');
	if (separator)
	{
	 	int separatorPos = separator - order ;

	 	strncpy( value, order,separatorPos);
	 	char* end = order + separatorPos + 1;
	    printf (" %s=%s\n",value, end);
	    if (!strcmp(value, "interpolation"))
	    {
   		    if(strncmp(end,"linear",6) == 0){interpolation = 1;};
		    if(strncmp(end,"cosine",6) == 0){interpolation = 2;};
		}

		if(strncmp(value,"colorBar.",9) == 0)
		{
			if (listofcolorbandItems.Goto(atoi(value + 9)))
			{
			   	 pActiveColorBandItem = (colorbandItem*)(listofcolorbandItems.GetCurrentObjectPointer());
		         double r=g=b=0;
		         separator = strchr(end,',');
				 if (separator)
				 {
		 			 strncpy( value, end,separator - end);
		 			 value[separator-end] = 0;
		 			 r = atof(value);
		 			 end = separator+1;
			     };
			     separator = strchr(separator+1,',');
				 if (separator)
				 {
		 			 strncpy( value, end,separator - end);
		 			 g = atof(value);
		 			 b = atof(separator+1);
			     }

			   	 SetActiveColor(r/255,g/255,b/255,1);
			   	 //if (pParentUI_base) pParentUI_base->Callback(this,1);
	  		}else printf("!!!! this bar dont exist");
		};
	}
};*/
