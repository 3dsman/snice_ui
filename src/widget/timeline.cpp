// crafter interface library
// copyright © 2004 Tricoire Sebastien

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
#include <math.h>

#include "snice.h"

#include "widget/text_box.h"
#include "widget/slider.h"

#include "widget/timeline.h"
 
W_timeline::W_timeline(int x, int y, int w, int h, char *l, float v, float f, float t, int p, float r, float g, float b)
		:UI_widget(x, y, w, h, r, g, b)
{
	pStartFrame = new W_textbox(x, 0, 55, 20, "S", _("0"), true);
	//pStartFrame->setParentUIbase(this);
	AddChild(pStartFrame);

	pEndFrame = new W_textbox(x + width - 55, 0, 55, 20, "E", _("500"), true);
	AddChild(pEndFrame);
	//pEndFrame->setParentUIbase(this);

	pSliderTimeline = new W_slider(x + 55,0,width - 110,20,l, v, f, t, p);
	AddChild(pSliderTimeline);
	//pSliderTimeline->setParentUIbase(this);

	action = false;

}

W_timeline::~W_timeline()
{
/*	delete pSliderTimeline;
	delete pStartFrame;
	delete pEndFrame;
	*/
}

void W_timeline::SetName(char *l)
{
	pSliderTimeline->SetName(l);
}

void W_timeline::SetLabel(char *l)
{
	pSliderTimeline->SetLabel(l);
	//delete text;
	//text = new label(posx+width/2-(strlen(l)*7)/2-4, posy-2, 0, 1, l);
}

void W_timeline::SetLabel()
{
	pSliderTimeline->SetLabel();
}

void W_timeline::SetWidth(int w)
{
	width = w;
	//setLabel();
	pEndFrame->SetPos(posx + width - 55, 0);
	//pSliderTimeline->SetPos(posx + 50,20);
	pSliderTimeline->SetWidth(width - 110);
}

void W_timeline::SetFrom(float f)
{
	if (f >= -10000)
	{
		if (pSliderTimeline->GetValue()<f)
			pSliderTimeline->SetValue(f);
		pSliderTimeline->SetFrom(f);
		char start[10];
		sprintf( start, "%i",(int) f );
		pStartFrame->SetContent(start);
	}
}

void W_timeline::SetTo(float t)
{
	if (t <= 10000)
	{
		if (pSliderTimeline->GetValue()>t)
			pSliderTimeline->SetValue(t);
		pSliderTimeline->SetTo(t);
		char end[10];
		sprintf( end, "%i",(int) t );
		pEndFrame->SetContent(end);
	}
}

float W_timeline::GetFrom()
{
	
	return pSliderTimeline->GetFrom();
}

float W_timeline::GetTo()
{
	return pSliderTimeline->GetTo();
}

void W_timeline::SetPrecision(int p)
{
	if ((p <= 5)&&(p >= 1))
	{
	pSliderTimeline->SetPrecision(p);
	//precision = p;
	}
}

void W_timeline::Draw()
{
	glTranslated(posx,posy,0);
	pSliderTimeline->Draw();
	pStartFrame->Draw();
	pEndFrame->Draw();
	glTranslated(-posx,-posy,0);
}

void W_timeline::Callback(UI_base * pCallObject, unsigned char callIndex )
{
	float temp;
	char text[256];

	if ((pCallObject == pStartFrame)&&(callIndex == 1)){
		temp = (float)(atoi(pStartFrame->GetContent()));
		if (temp > pSliderTimeline->GetTo())
		{
			temp = pSliderTimeline->GetTo();
			sprintf(text,"%i",(int)temp);
			pStartFrame->SetContent(text);
		}
		//pSliderTimeline->SetFrom((float)(atoi(pStartFrame->getContent())));
		SetFrom((float)(temp));
		return;
	}

	if ((pCallObject == pEndFrame)&&(callIndex == 1)){
		temp = (float)(atoi(pEndFrame->GetContent()));
		if (temp < pSliderTimeline->GetFrom())
		{
			temp = pSliderTimeline->GetFrom();
			sprintf(text,"%i",(int)temp);
			pEndFrame->SetContent(text);
		}
		SetTo(temp);
		//pSliderTimeline->SetTo(temp);
		return;
	}
}

float W_timeline::GetValue()
{
	return pSliderTimeline->GetValue();//value;
}

void W_timeline::SetValue(float v)
{
	pSliderTimeline->SetValue(v);
}
/*
void W_timeline::LoadXML(TiXmlElement* element)
{
	double frame, from, to;

	element->QueryDoubleAttribute("From",&from);
	SetFrom((float)from);
	//sprintf( pStartFrame->GetContent(), "%i",(int) from );
	//pStartFrame->SetLabel();


	element->QueryDoubleAttribute("To",&to);
	SetTo((float)to);
	//sprintf( pEndFrame->GetContent(), "%i",(int) to );
	//pEndFrame->SetLabel();

	element->QueryDoubleAttribute("Frame",&frame);
	SetValue((float)frame);
}

void W_timeline::SaveXML(TiXmlElement* element)
{
	TiXmlElement TimeLine( "TimeLine" );
	
	char buf[10];

	sprintf( buf, "%f", pSliderTimeline->GetFrom());
	TimeLine.SetAttribute ("From", buf);

	sprintf( buf, "%f", pSliderTimeline->GetTo() );
	TimeLine.SetAttribute ("To", buf);

	sprintf( buf, "%f", pSliderTimeline->GetValue() );
	TimeLine.SetAttribute ("Frame", buf);

	element->InsertEndChild( TimeLine );
}
*/

void W_timeline::Set(char* order)
{
	printf("->%s", refName);
 	char value[256];

 	for (int i=0; i<256; ++i)
	    value[i]=0;
	char* separator = strchr(order,'=');
	if (separator)
	{
	 	int separatorPos = separator - order ;
	 	
	 	strncpy( value, order,separatorPos);
	 	char* end = order + separatorPos + 1;
	    printf (" %s=%s\n",value, end);
	    if (!strcmp(value, "S"))
            SetFrom(atof(order + separatorPos + 1));
   	    if (!strcmp(value, "E"))
            SetTo(atof(order + separatorPos + 1));
   	    if (!strcmp(value, "Frame"))
            SetValue(atof(order + separatorPos + 1));
	    
		if (pParentUI_base) pParentUI_base->Callback(this,1);

	}
};

