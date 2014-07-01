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

#ifndef _SNICE_LIST_H_
#define _SNICE_LIST_H_

////////////////////////////////////////
// class listElement.
// Class for a node in a list
////////////////////////////////////////

	/**	\brief class for the elements of the list.*/
class ListElement
{
private:
	void* pObject;				/**<	\brief pointer to the corresponding object.*/
	ListElement* pNextElement;	/**<	\brief pointer to the next element of the list.*/
	ListElement* pPreviousElement;	/**<	\brief pointer to the previous element of the list.*/
	//int iObjectType;			// information for casting the void pointer to the appropriate type

public:
	/**	\brief constructor need pointer to the corresponding object.*/
	ListElement(void* pointer);
	

	/**	\brief to get pointer to the corresponding object.*/
	void* GetObjectPointer();

	/**	\brief to get pointer to the next element of the list.*/
	ListElement* GetNext();

	/**	\brief to get pointer to the previous element of the list.*/
	ListElement* GetPrevious();

	/**	\brief to set pointer to the next element of the list.*/
	void SetNext(ListElement* PointerToNext);

	/**	\brief to set pointer to the previous element of the list.*/
	void SetPrevious(ListElement* PointerToPrevious);
};

////////////////////////////////////////
// class list
// Class for a list
////////////////////////////////////////
/**	\brief class for the lists (list of nodes, of connexions,...).*/
class List
{
private:
	ListElement* pFirstElement;		/**<	\brief pointer to the first element of the list.*/
	ListElement* pLastElement;		/**<	\brief pointer to the last element of the list.*/
	ListElement* pCurrentElement;	/**<	\brief pointer to the current element of the list.*/
	ListElement* pStackElement;		/**<	\brief pointer to the stacked element.*/
	
public:

	List();
	
	~List();

	/**	\brief to add an object to the list.*/
	void Add(void* pointer);

	/**	\brief return true if the list is empty*/
	bool Empty();

	/**	\brief to remove the argument object from the list. (do not destroy the object)(return false if it fail)*/
	bool Remove(void * object);

	/**	\brief to remove current object from the list. (do not destroy the object)*/
	void RemoveCurrent();

	/**	\brief to remove all object from the list. (do not destroy the object)*/
	void Flush();

	/**	\brief to get the current object.*/
	void* GetCurrentObjectPointer();


	/**	\brief to go to the first object.
	
	make the first element curent and return true if there is one false else (if the list is empty)*/
	bool ToFirst();

	/**	\brief to go to the first object.
	
	make the first element curent and return true if there is one false else (if the list is empty)*/
	bool ToLast();
	/**	\brief to go to the next object.

	make the next element current and return true if it exist false else (if the node is the last one)*/
	bool ToNext();

	/**	\brief to go to the previous object.

	make the previous element current and return true if it exist false else (if the node is the first one)*/
	bool ToPrevious();

	/**	\brief find object in the list and set current object to it (return false if object is'nt in the list).*/
	bool Goto(void * object);

	/**	\brief set current to the posth object (return false if there is not).*/
	bool Goto(int pos);


	/**	\brief push the current element to the stack.

	the stack permit to push and pop position in the list*/
	void Push();

	/**	\brief pop the current element from the stack.

	the stack permit to push and pop position in the list*/
	void Pop();

	/**	\brief move object to the end of the list.
	
	if the object is'nt in the list do nothing*/
	void MoveToBack(void * pointer);

	/**	\brief return the nuber of objects in the list.*/
	int Count();
};

#endif //_SNICE_LIST_H_

// End of file list.h
