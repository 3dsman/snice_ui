// fileSystemWin.cpp: Function for file managment (input/output, browse).
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
// fileSystemWin.cpp
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

#include <windows.h>
#include <io.h>

#include "mylist.h"
#include "file_system.h"

bool isDirectory(char * name){
	return ( name[strlen( name) - 1] == '\\');
};

bool directoryExist(char * name){ return true;};
bool fileExist(char * name){return true;};

void rootsNames(List * rootsList){
	struct _finddata_t File;
	long hSearch;

	//get the names of the drives ("C:\NULLD:\NULLE:\NULLNULL")
	char buffer[1024];
	GetLogicalDriveStrings(1023,buffer);
	char name[128];
	char * drive;
	drive = buffer;
	while (drive[0]){
		strcpy(name,drive);
		strcat(name,"*.*");

		//test if the drive is readable
		hSearch = _findfirst(name, &File);
		if(hSearch != -1)
		{
			rootsList->Add(new char[PATHMAXLENGTH]);
			strcpy((char*) rootsList->GetCurrentObjectPointer(),drive);
			_findclose(hSearch);
		}
		drive = &(drive[strlen(drive)+1]);
	}	
};

PathElement::PathElement(char * name){

	if (strlen( name)<PATHMAXLENGTH)
	{
		strcpy(Path, name);
	}
	select = false;

};

PathElement::~PathElement(){};

void PathElement::GetName(char * name){
	unsigned int i = strlen(Path)-1;

	// Find the last "\" character in the chain
	while(( i >= 1) && ( Path[i-1] != '\\')) { i -= 1;};

	// Copy the chain from the "\" character
	strcpy( name, &( Path[ i ] ));
};

void PathElement::GetFullName(char * fullName){
	strcpy(fullName, Path);
}

void PathElement::GetDirectory(char * dirName)
{
		//start the scan at the second character fom the last (because directory path finish by \)
		unsigned int i = strlen(Path)-2;

		strcpy(dirName,Path);

		// Find the last "\" (0x5C) character in the chain
		while( i && ( Path[i] != '\\')) { i -= 1;};

		// set the end of the string just after the "\"
		strcpy( &( dirName[ i+1] ),"" );
}

void PathElement::GetClipingName(char * clipingName, unsigned int size)
{
	// Get the cliping name and verify if it is too long
	// if it is copy the ".." char at the size position

	GetName( clipingName);
	if (( strlen( clipingName)) > size){
		strcpy( &( clipingName[ size - 2]), "..");
	}
};

bool PathElement::IsSelected()
{
	return select;
};

void PathElement::Selected(bool selected)
{
	select = selected;
};

bool PathElement::IsDirectory()
{
	return (Path[strlen(Path)-1] == '\\');
};


//**********************************************************
//********************    FILE INFO    *********************
//**********************************************************

FileInfo::FileInfo(char *fileName)
		 :PathElement(fileName)
{
	file = true;
};

FileInfo::~FileInfo(){};

void FileInfo::GetExtension(char * fileName, char * ext){};

bool FileInfo::FileExist(char * name){return true;};

//**********************************************************
//*********************    DIR INFO    *********************
//**********************************************************

DirInfo::DirInfo(char * dirName)
		:PathElement(dirName)
{
	file = false;
};

DirInfo::~DirInfo(){};

void DirInfo::BrowseDirectory(char * exts, List * fileList)
{

	struct _finddata_t File;
	long hSearch;
	char catNameExt[PATHMAXLENGTH+EXTMAXLENGTH];
	char catNamePath[PATHMAXLENGTH+EXTMAXLENGTH];


	if (strlen(Path) + 1 + strlen(exts) <= PATHMAXLENGTH+EXTMAXLENGTH)
	{

		// delete the fileList content
		if (fileList->ToFirst())
		do
		{
			delete (PathElement*)( fileList->GetCurrentObjectPointer());
			fileList->RemoveCurrent();
		}while ( fileList->ToFirst());


		// List Directory
		strcpy(catNameExt,Path);
		strcat(catNameExt,"\\*.*");

		hSearch=_findfirst(catNameExt, &File);

		if(hSearch != -1)
		{
			do
			{
				// If it is a subdir then create a dirInfo element
				if((File.attrib & _A_SUBDIR) && (strcmp(File.name,".")))
				{
					strcpy(catNamePath,Path);
					strcat(catNamePath,File.name);
					strcat(catNamePath,"\\");
					
					fileList->Add(new DirInfo(catNamePath));		
				}
			}while(_findnext(hSearch, &File) == 0);

			_findclose(hSearch);
		}

		// List Files
		char ext[EXTMAXLENGTH];

		char * curPos= exts;
		char * separator;
		if(strlen( exts))
			do{
				// Find the next "|" character in the string
				separator = strchr(curPos,'|');
				
				// if there is one
				if (separator)
				{
					// copy to and add a null char at the end
					strncpy(ext,curPos,separator - curPos);
					ext[separator - curPos] = 0;

					//change the current position
					curPos = separator + 1;
				}else
				{
					//else just copy the string
					strcpy( ext, curPos);
				}


				strcpy(catNameExt,Path);
				strcat(catNameExt,"*");
				strcat(catNameExt,ext);
				
				hSearch=_findfirst(catNameExt, &File);

				if(hSearch != -1)
				{
					do
					{
						if(!(File.attrib & _A_SUBDIR))
						{
							strcpy(catNamePath,Path);
							strcat(catNamePath,File.name);

							fileList->Add(new FileInfo(catNamePath));
							((FileInfo*)(fileList->GetCurrentObjectPointer()))->size = File.size;
							((FileInfo*)(fileList->GetCurrentObjectPointer()))->cDate = File.time_create;
							((FileInfo*)(fileList->GetCurrentObjectPointer()))->wDate = File.time_write;
							((FileInfo*)(fileList->GetCurrentObjectPointer()))->aDate = File.time_access;

							/*
							strftime(a_time, sizeof(a_time), Format, localtime(&fileinfo.time_access));
							strftime(w_time, sizeof(a_time), Format, localtime(&fileinfo.time_write));
							strftime(c_time, sizeof(a_time), Format, localtime(&fileinfo.time_create));
							sprintf(sub, "%s\\%s", dir, fileinfo.name);
							printf("%s, %s, %s, %s, %d\n", sub, a_time, w_time, c_time, fileinfo.size);*/
						}
					}while(_findnext(hSearch, &File) == 0);

					_findclose(hSearch);
				}
			}while( separator);

	}
};

