/*
* This file is part of ColAndreas.
* Copyright(C) <2013>  <christopher michael james>
* computer_customs@hotmail.com
*
* ColAndreas is free software : you can redistribute it and / or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ColAndreas is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Special thanks:
*
* [uL]Slice, Writing the original collision reader function
*/

#pragma once

#ifdef WIN32
	#include <Windows.h>
#endif

#include <array>
#include <cstdio>
#include <fstream> 
#include <iostream>
#include <cctype>
#include <cstdint>
#include <algorithm>    // std::find
#include <string>
#include <vector>
#include <assert.h>
#include <array>

#include <ATree.hpp>

#define GetBytes(Source, Destination, Index, BytesToCopy) memcpy(&Destination, (Source + Index), BytesToCopy), Index+=BytesToCopy

class BuildManager
{
public:
	typedef struct
	{
		float x;
		float y;
		float z;
	} Vertex;

	typedef struct
	{
		BuildManager::Vertex center;
		float radius;
	} ColSphere;

	typedef struct
	{
		BuildManager::Vertex   min;
		BuildManager::Vertex   max;
	} ColBox;

	typedef struct
	{
		BuildManager::Vertex*  a;
		BuildManager::Vertex*  b;
		BuildManager::Vertex*  c;
	} ColFace;

	typedef struct
	{
		std::string name;
		uint16_t modelid;

		uint32_t num_spheres;
		uint32_t num_boxes;
		uint32_t num_faces;

		BuildManager::ColSphere* spheres;
		BuildManager::ColBox* boxes;
		BuildManager::ColFace* faces;

	} ColModel;

	typedef struct
	{
		float x;
		float y;
		float z;
		float w;
	} IPLRot;

	typedef struct
	{
		uint16_t modelid;

		BuildManager::Vertex Position;
		BuildManager::IPLRot Rotation;

		std::string Modelname;
	} IPLObject;

	typedef struct
	{
		uint16_t modelid;
		std::string ModelName;
		float DrawDist;
	} Modelid_Modelname_Struct;

private:
	uint8_t ERROR_CODE;//uint8_t
	std::string GTAInstallDirectory;
	std::string OutfileDirectory;

	std::vector<BuildManager::IPLObject> IPLArray;
	std::vector<BuildManager::ColModel> COLArray;
	ATree<int> modelnameLookup;
	std::map<int, std::string> modelidLookup;
	std::vector<BuildManager::Modelid_Modelname_Struct> Modelid_Modelname_Vector;

	std::vector<std::string> ImageFileNames;
	std::vector<std::string> CollisionFileNames;
	std::vector<std::string> ItemPlacementFileNames;
	std::vector<std::string> ItemDefinitionFileNames;

	bool ReadItemDefinitionFile(const char fname[]);
	bool ReadItemPlacementData(const char fname[]);
	void ReadBinaryItemPlacementData(char* RawIPLData);

	bool ReadColFile(const char fname[]);
	void InitDirectoryNames();

	bool UsingSAMPObjects;
	bool UsingCustomObjects;
	
public:
	BuildManager(std::string &GTADirectory, std::string &OutDirectory, bool SAMPObjects, bool CustomObjects);

	bool ExtractImageFiles();
	bool ExtractCollisionFiles();
	bool ExtractItemPlacementFiles();
	bool ExtractItemDefinitionFiles();
	void PrepareDatabaseStructures();

	bool WriteBinaryFile(const char fname[]);
};
