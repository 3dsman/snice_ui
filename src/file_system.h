// fileSystem.h: Function for file managment (input/output, browse).
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
// fileSystem.h
// This file contains function for file managment (input/output, browse).
// File created by Tricoire Sebastien
// Date of creation : 2004 25 10
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

#ifndef _SNICE_FILESYSTEM_H_
#define _SNICE_FILESYSTEM_H_
#include <string>
#include "mylist.h"
#include <list>

using namespace std;

//#define PATHMAXLENGTH 2048	/**<	\brief Maximum length of a path*/
#define EXTMAXLENGTH 256	/**<	\brief Maximum length of the extensions*/

/**	\brief Return true if the name is those of a directoy.

	this function just look the end of the name to find \.
	It do not verify if directory exist.
*/
bool isDirectory(string name);


/**	\brief Return true if verify if the name directory exist.*/
bool directoryExist(string name);

/**	\brief Return true if verify if the name file exist.*/
bool fileExist(string name);

/**	\brief Get the roots manes (\ for linux and C:\, D:\,... for windows).*/
void rootsNames(std::list<string> rootsList);


/**	\brief Base class of file and directory path.*/

class PathElement
{
private:


protected:
	string Path;	/**<	\brief path name.*/
	bool select;	/**<	\brief true if the path is selected.*/
	bool file;		/**<	\brief true if it's a file (false for a directory).*/

public:

	PathElement(const string _name);

	virtual ~PathElement();

	/**	\brief to get the full name of the path.*/
	//virtual void getCompletteName(char * _completeName);
	virtual string GetFullName();

	/**	\brief to get the name of the last element of the path.
	
	exemple:
	- for the pathElement (type directory) "c:/this/is/my/path/" name = "path/".
	- for (type file) "c:/this/is/my/path/andTheFile.tga" name = "andTheFile.tga".
	*/
	string GetName();

	/**	\brief to get the name of the path only :-).
	
	exemple:
	- for the pathElement (type directory) "c:/this/is/my/path/" return "c:/this/is/my/".
	- for (type file) "c:/this/is/my/path/andTheFile.tga" return "c:/this/is/my/path/".
	*/
	//char * getPath();

	string GetDirectory();

	/**	\brief clip the "clipingName" name at the size (add ".." at the end).
	
	exemple:
	if the fullname of the path is "c:/thisFileHaveALongName.tga"

	char[16] filename	
	myPathElement->getClipingName(filename, 10);

	you get filename = "thisFile.."
	*/
	string GetClipingName( unsigned int size);

	/**	\brief return true if the pathElement is selected.*/
	bool IsSelected();

	/**	\brief set the select attribute.*/
	void Selected(bool selected);

	/**	\brief return true if the pathElement represent a directory.*/
	bool IsDirectory();

};

/**	\brief class for the files.*/
class FileInfo : public PathElement
{
private:

public:

	FileInfo(const string name);

	virtual ~FileInfo();

	/**	\brief to get file extension.*/
	void GetExtension(const string fileName, char * ext);

	/**	\brief test if the file exist.*/
	bool FileExist(const string name);
	
	int size;/**<	\brief file size.*/
	int cDate;/**<	\brief file creation date.*/
	int wDate;/**<	\brief last write date.*/
	int aDate;/**<	\brief last acces date.*/

};

/**	\brief class for the directory.*/
class DirInfo : public PathElement
{
private:


public:

	DirInfo(const string name);

	virtual ~DirInfo();

	/**	\brief to browse directory.*/
	std::list<PathElement> BrowseDirectory(const char * exts);

	/**	\brief to get parent directory.*/
	//void getParentDir(char * dirName);

};

#endif // _SNICE_FILESYSTEM_H_
