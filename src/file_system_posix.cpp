// fileSystemPosix.cpp: Function for file managment (input/output, browse).
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
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "mylist.h"
#include "file_system.h"

bool isDirectory(char * name){
	return (name[strlen(name)-1] == '/');
};

bool directoryExist(char * name){ return true;};
bool fileExist(char * name){return true;};

void rootsNames(List * rootsList){
	char* plinuxRoot = new char[2];  // Allocate memory for the array
  	strcpy(plinuxRoot, "/");
	rootsList->Add(plinuxRoot);
};

PathElement::PathElement(const char * name){

	if (strlen(name)<PATHMAXLENGTH)
	{
		strcpy(Path, name);
	}
	select = false;

};

PathElement::~PathElement(){};

void PathElement::GetName(char * name){
	unsigned int i = strlen(Path)-1;

	// Find the last "/" character in the chain
	while(( i >= 1) && ( Path[i-1] != '/')) { i -= 1;};

	// Copy the chain from the "/" character
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
		while( i && ( Path[i] != '/')) { i -= 1;};

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
	return (Path[strlen(Path)-1] == '/');
};


//**********************************************************
//********************    FILE INFO    *********************
//**********************************************************

FileInfo::FileInfo(const char * fileName)
		 :PathElement( fileName)
{
	file = true;
};

FileInfo::~FileInfo(){};

void FileInfo::GetExtension(const char * fileName, char * ext){};

bool FileInfo::FileExist(const char * name){return true;};

//**********************************************************
//*********************    DIR INFO    *********************
//**********************************************************

DirInfo::DirInfo(const char * dirName)
		:PathElement(dirName)
{
	file = false;
};

DirInfo::~DirInfo(){};

void DirInfo::BrowseDirectory(const char * exts, List * fileList)
{   
	struct dirent **namelist;
	struct stat infos;
    char catNamePath[PATHMAXLENGTH+EXTMAXLENGTH];
    
	strcpy(catNamePath,Path);
	if (strlen(catNamePath)>1)
	{
		catNamePath[strlen(catNamePath)-1] = 0;
	}
	if (fileList->ToFirst())
		do
		{
			delete (PathElement*)(fileList->GetCurrentObjectPointer());
			fileList->RemoveCurrent();
		}while (fileList->ToFirst());

    int n = scandir(catNamePath, &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir error");
    else {
    	int file = 0;
        while(file < n) {
        	strcpy(catNamePath,Path);
        	strcat(catNamePath,namelist[file]->d_name);
        	if ( 0 > lstat(catNamePath, &infos) )
        	{
            	printf("%s %s\n", "file stat problem : " , namelist[file]->d_name);
        	}else
	            if((S_ISDIR(infos.st_mode))&&(strcmp(namelist[file]->d_name,".")))
	            {
	            	strcpy(catNamePath,Path);
					strcat(catNamePath,namelist[file]->d_name);
					strcat(catNamePath,"/");
	            	fileList->Add(new DirInfo(catNamePath));
	            	//printf("%s %s\n", "repertoire: " , namelist[n]->d_name);
	            }
	        file++;
        }
        file = 0;
        while(file < n) {
        	strcpy(catNamePath,Path);
        	strcat(catNamePath,namelist[file]->d_name);
        	if ( 0 > lstat(catNamePath, &infos) )
        	{
            	printf("%s %s\n", "file stat problem : " , namelist[file]->d_name);
        	}else
        	if(S_ISREG(infos.st_mode)){
	        		
	        	// List Files
				char ext[EXTMAXLENGTH];
				char extsc[EXTMAXLENGTH];
				
				strcpy(extsc,exts);
	
				char * curPos= extsc;
				char * separator;
				if(strlen( extsc))
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
					
					if((strstr(namelist[file]->d_name,ext))||!(strcmp(ext,".*")))
					{
						strcpy(catNamePath,Path);
						strcat(catNamePath,namelist[file]->d_name);
						fileList->Add(new FileInfo(catNamePath));
						((FileInfo*)(fileList->GetCurrentObjectPointer()))->size = infos.st_size;
						((FileInfo*)(fileList->GetCurrentObjectPointer()))->cDate = infos.st_ctime;
						((FileInfo*)(fileList->GetCurrentObjectPointer()))->wDate = infos.st_mtime;
						((FileInfo*)(fileList->GetCurrentObjectPointer()))->aDate = infos.st_atime;
						separator = 0;
					}
					
					
					
				}while( separator);
        	}
	        file++;
        }
            /*
            if (S_ISREG(infos.st_mode))printf("%s %s\n", "regular: " , namelist[n]->d_name);
			if (S_ISDIR(infos.st_mode))printf("%s %s\n", "dir: " , namelist[n]->d_name);
			if (S_ISCHR(infos.st_mode))printf("%s %s\n", "chardev: " , namelist[n]->d_name);
            if (S_ISBLK(infos.st_mode))printf("%s %s\n", "block: " , namelist[n]->d_name);
			if (S_ISFIFO(infos.st_mode))printf("%s %s\n", "fifo: " , namelist[n]->d_name);
			if (S_ISLNK(infos.st_mode))printf("%s %s\n", "link: " , namelist[n]->d_name);
			if (S_ISSOCK(infos.st_mode))printf("%s %s\n", "sock: " , namelist[n]->d_name);
			*/
		file = n;
        while(file--) {
       		free(namelist[file]);
        }
        
        free(namelist);
    }
};

