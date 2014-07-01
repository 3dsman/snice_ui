// linked list class
// by Wybren van Keulen, WAVK
// copyright © 2002 Funny Farm
// www.funnyfarm.tv

// I got fed up with using standard linked list classes
// without understanding them completely,
// so I wrote my own from scratch
// with some extra options which are usefull for this
// particular application

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

#include "mylist.h"


ListElement::ListElement(void* pointer)
{
	pNextElement = 0;
	pPreviousElement = 0;
	pObject = pointer;
}
	


void* ListElement::GetObjectPointer()
{
	return pObject;
}



ListElement* ListElement::GetNext()
{
	return pNextElement;
}

ListElement* ListElement::GetPrevious()
{
	return pPreviousElement;
}

void ListElement::SetNext(ListElement* PointerToNext)
{
	pNextElement = PointerToNext;
}

void ListElement::SetPrevious(ListElement* PointerToPrevious)
{
	pPreviousElement = PointerToPrevious;
}



List::List()
{
	pFirstElement = 0;
	pCurrentElement = 0;
	pLastElement = 0;
	pStackElement = 0;
}

List::~List()
{
	while(pFirstElement)
	{
		pCurrentElement = pFirstElement;
		pFirstElement = pFirstElement->GetNext();
		delete pCurrentElement;

	}
}

void List::Add(void* pointer)
{
	ListElement* temp = new ListElement(pointer);
	if (pFirstElement == 0)
	{
		pFirstElement = temp;
		pCurrentElement = temp;
		pLastElement = temp;
		return;
	}
	

	if (pCurrentElement->GetNext())
	{
		temp->SetNext(pCurrentElement->GetNext());
		(pCurrentElement->GetNext())->SetPrevious(temp);
	}
	else pLastElement = temp;

	pCurrentElement->SetNext(temp);
	temp->SetPrevious(pCurrentElement);

	pCurrentElement = temp;
}



void* List::GetCurrentObjectPointer()
{
	if(pCurrentElement)
		return pCurrentElement->GetObjectPointer();

	return 0;
}

bool List::Empty()
{
	return (pFirstElement == 0);
}

bool List::Remove(void * object)
{
	if (Goto(object))
	{
		RemoveCurrent();
		return true;
	}
	return false;
}

void List::RemoveCurrent()
{
	// if there's nothing in the list
	if(pFirstElement == 0)
	{
		return;
	}
	

	if(pCurrentElement == pFirstElement)
	{
		pFirstElement = pCurrentElement->GetNext();
		if (pFirstElement)
			pFirstElement->SetPrevious(0);

		delete pCurrentElement;
		if (pCurrentElement == pLastElement) {pLastElement = 0;}
		pCurrentElement = pFirstElement;
		return;
	}
	
	(pCurrentElement->GetPrevious())->SetNext(pCurrentElement->GetNext());

	if(pCurrentElement != pLastElement)
	{
		(pCurrentElement->GetNext())->SetPrevious(pCurrentElement->GetPrevious());
	}else
	{
		pLastElement = pCurrentElement->GetPrevious();
	}

	ListElement* temp = pCurrentElement;
	pCurrentElement = pCurrentElement->GetPrevious();
	delete temp;
}

void List::Flush()
{
	ToFirst();
	while(pFirstElement)
	{
		pFirstElement = pCurrentElement->GetNext();
		delete pCurrentElement;
		pCurrentElement = pFirstElement;
	}
}

bool List::ToFirst()
{
	pCurrentElement = pFirstElement;
	if (pCurrentElement) return 1;

	return 0;
}

bool List::ToLast()
{
	pCurrentElement = pLastElement;
	if (pCurrentElement) return 1;

	return 0;
}


bool List::ToNext()
{
	if((pCurrentElement)&&(pCurrentElement->GetNext()))
	{
		//pPreviousElement = pCurrentElement;
		pCurrentElement = pCurrentElement->GetNext();
		return 1; // success
	}
	return 0; // failure, the end of the list
}

bool List::ToPrevious()
{
	if((pCurrentElement)&&(pCurrentElement->GetPrevious()))
	{
		pCurrentElement = pCurrentElement->GetPrevious();
		return 1; // success
	}
	return 0; // failure, the end of the list
}


bool List::Goto(void * object)
{
	if(ToFirst())
		do
		{
			if (pCurrentElement->GetObjectPointer() == object)
				return 1;
		
		}while (ToNext());
	return 0;
}


bool List::Goto(int pos)
{
    if(ToFirst())
		do
		{
	        --pos;
			if (pos <= 0)
				return 1;
		}while (ToNext());
	return 0;
}

void List::Push()
{
		pStackElement = pCurrentElement;
}

void List::Pop()
{
	if (pStackElement)
	{
		pCurrentElement = pStackElement;
		pStackElement = 0;
	}
}

void List::MoveToBack(void* pointer)
{
	ToFirst();

	// if there's no node at all or only one in the list
	if((!pCurrentElement)||(!pCurrentElement->GetNext()))
		return;

	ToFirst();
	do
	{
		if ( pointer == pCurrentElement->GetObjectPointer())
		{
			// if it's the already the last node
			if(pCurrentElement->GetNext() == 0)
				return;
			else
				RemoveCurrent();
		}
	}
	while (ToNext() != 0);
	
	Add(pointer);
}

int List::Count(){
	int nb = 0;

	ListElement* temp = pCurrentElement;

	ToFirst();
	if(pCurrentElement != 0)
		do
			nb = nb+1;
		while (ToNext() != 0);
	
	pCurrentElement = temp;

	return nb;
}
