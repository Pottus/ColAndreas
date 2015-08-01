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
#include "BuildManager.h"
#include <msclr\marshal.h>

// BuildManager constructor
BuildManager::BuildManager(std::string _GTAInstallDirectory, std::string _OutfileDirectroy, System::ComponentModel::BackgroundWorker ^ _backgroundWorkerPointer, bool _UsingSAMPObjects, bool _UsingCustomObjects)
{
	BuildManager::GTAInstallDirectory = _GTAInstallDirectory;
	BuildManager::OutfileDirectroy = _OutfileDirectroy;
	BuildManager::backgroundWorkerRefrence = _backgroundWorkerPointer;

	BuildManager::InitDirectoryNames();

	BuildManager::COLArrayVectorIndex = -1;
	BuildManager::IPLArrayVectorIndex = -1;
	BuildManager::Modelid_Modelname_VectorIndex = -1;

	UsingSAMPObjects = _UsingSAMPObjects;
	UsingCustomObjects = _UsingCustomObjects;

}
void BuildManager::InitDirectoryNames()
{
	BuildManager::ImageFileNames[0] = "\\models\\gta_int.img";
	BuildManager::ImageFileNames[1] = "\\models\\gta3.img";
	BuildManager::ImageFileNames[2] = "\\SAMP\\SAMPCOL.img";

	BuildManager::CollisionFileNames[0] = "\\models\\coll\\weapons.col";
	BuildManager::CollisionFileNames[1] = "\\models\\coll\\vehicles.col";
	//BuildManager::CollisionFileNames[2] = "\\models\\coll\\peds.col"; //Unusual file structure causing problems, file is unused in game.

	BuildManager::ItemPlacementFileNames[0] = "\\data\\maps\\country\\countn2.ipl";
	BuildManager::ItemPlacementFileNames[1] = "\\data\\maps\\country\\countrye.ipl";
	BuildManager::ItemPlacementFileNames[2] = "\\data\\maps\\country\\countryN.ipl";
	BuildManager::ItemPlacementFileNames[3] = "\\data\\maps\\country\\countryS.ipl";
	BuildManager::ItemPlacementFileNames[4] = "\\data\\maps\\country\\countryw.ipl";

	BuildManager::ItemPlacementFileNames[5] = "\\data\\maps\\interior\\gen_int1.ipl";
	BuildManager::ItemPlacementFileNames[6] = "\\data\\maps\\interior\\int_cont.ipl";
	BuildManager::ItemPlacementFileNames[7] = "\\data\\maps\\interior\\int_veg.ipl";
	BuildManager::ItemPlacementFileNames[8] = "\\data\\maps\\interior\\stadint.ipl";

	BuildManager::ItemPlacementFileNames[9] = "\\data\\maps\\LA\\LAe.ipl";
	BuildManager::ItemPlacementFileNames[10] = "\\data\\maps\\LA\\LAe2.ipl";
	BuildManager::ItemPlacementFileNames[11] = "\\data\\maps\\LA\\LAhills.ipl";
	BuildManager::ItemPlacementFileNames[12] = "\\data\\maps\\LA\\LAn.ipl";
	BuildManager::ItemPlacementFileNames[13] = "\\data\\maps\\LA\\LAn2.ipl";
	BuildManager::ItemPlacementFileNames[14] = "\\data\\maps\\LA\\LAs.ipl";
	BuildManager::ItemPlacementFileNames[15] = "\\data\\maps\\LA\\LAs2.ipl";
	BuildManager::ItemPlacementFileNames[16] = "\\data\\maps\\LA\\LAw.ipl";
	BuildManager::ItemPlacementFileNames[17] = "\\data\\maps\\LA\\LAw2.ipl";
	BuildManager::ItemPlacementFileNames[18] = "\\data\\maps\\LA\\LaWn.ipl";

	BuildManager::ItemPlacementFileNames[19] = "\\data\\maps\\leveldes\\levelmap.ipl";
	BuildManager::ItemPlacementFileNames[20] = "\\data\\maps\\leveldes\\seabed.ipl";

	BuildManager::ItemPlacementFileNames[21] = "\\data\\maps\\SF\\SFe.ipl";
	BuildManager::ItemPlacementFileNames[22] = "\\data\\maps\\SF\\SFn.ipl";
	BuildManager::ItemPlacementFileNames[23] = "\\data\\maps\\SF\\SFs.ipl";
	BuildManager::ItemPlacementFileNames[24] = "\\data\\maps\\SF\\SFSe.ipl";
	BuildManager::ItemPlacementFileNames[25] = "\\data\\maps\\SF\\SFw.ipl";

	BuildManager::ItemPlacementFileNames[26] = "\\data\\maps\\vegas\\vegasE.ipl";
	BuildManager::ItemPlacementFileNames[27] = "\\data\\maps\\vegas\\vegasN.ipl";
	BuildManager::ItemPlacementFileNames[28] = "\\data\\maps\\vegas\\vegasS.ipl";
	BuildManager::ItemPlacementFileNames[29] = "\\data\\maps\\vegas\\vegasW.ipl";
	BuildManager::ItemPlacementFileNames[30] = "\\data\\maps\\vegas\\vegaxref.ipl";

	BuildManager::ItemDefinitionFileNames[0] = "\\data\\maps\\country\\countn2.ide";
	BuildManager::ItemDefinitionFileNames[1] = "\\data\\maps\\country\\countrye.ide";
	BuildManager::ItemDefinitionFileNames[2] = "\\data\\maps\\country\\countryN.ide";
	BuildManager::ItemDefinitionFileNames[3] = "\\data\\maps\\country\\countryS.ide";
	BuildManager::ItemDefinitionFileNames[4] = "\\data\\maps\\country\\countryW.ide";
	BuildManager::ItemDefinitionFileNames[5] = "\\data\\maps\\country\\counxref.ide";

	BuildManager::ItemDefinitionFileNames[6] = "\\data\\maps\\generic\\barriers.ide";
	BuildManager::ItemDefinitionFileNames[7] = "\\data\\maps\\generic\\dynamic.ide";
	BuildManager::ItemDefinitionFileNames[8] = "\\data\\maps\\generic\\dynamic2.ide";
	BuildManager::ItemDefinitionFileNames[9] = "\\data\\maps\\generic\\multiobj.ide";
	BuildManager::ItemDefinitionFileNames[10] = "\\data\\maps\\generic\\procobj.ide";
	BuildManager::ItemDefinitionFileNames[11] = "\\data\\maps\\generic\\vegepart.ide";

	BuildManager::ItemDefinitionFileNames[12] = "\\data\\maps\\interior\\gen_int1.ide";
	BuildManager::ItemDefinitionFileNames[13] = "\\data\\maps\\interior\\gen_int2.ide";
	BuildManager::ItemDefinitionFileNames[14] = "\\data\\maps\\interior\\gen_int3.ide";
	BuildManager::ItemDefinitionFileNames[15] = "\\data\\maps\\interior\\gen_int4.ide";
	BuildManager::ItemDefinitionFileNames[16] = "\\data\\maps\\interior\\gen_int5.ide";
	BuildManager::ItemDefinitionFileNames[17] = "\\data\\maps\\interior\\gen_intb.ide";
	BuildManager::ItemDefinitionFileNames[18] = "\\data\\maps\\interior\\int_cont.ide";
	BuildManager::ItemDefinitionFileNames[19] = "\\data\\maps\\interior\\int_LA.ide";
	BuildManager::ItemDefinitionFileNames[20] = "\\data\\maps\\interior\\int_SF.ide";
	BuildManager::ItemDefinitionFileNames[21] = "\\data\\maps\\interior\\int_veg.ide";
	BuildManager::ItemDefinitionFileNames[22] = "\\data\\maps\\interior\\propext.ide";
	BuildManager::ItemDefinitionFileNames[23] = "\\data\\maps\\interior\\props.ide";
	BuildManager::ItemDefinitionFileNames[24] = "\\data\\maps\\interior\\props2.ide";
	BuildManager::ItemDefinitionFileNames[25] = "\\data\\maps\\interior\\savehous.ide";
	BuildManager::ItemDefinitionFileNames[26] = "\\data\\maps\\interior\\stadint.ide";

	BuildManager::ItemDefinitionFileNames[27] = "\\data\\maps\\LA\\LAe.ide";
	BuildManager::ItemDefinitionFileNames[28] = "\\data\\maps\\LA\\LAe2.ide";
	BuildManager::ItemDefinitionFileNames[29] = "\\data\\maps\\LA\\LAhills.ide";
	BuildManager::ItemDefinitionFileNames[30] = "\\data\\maps\\LA\\LAn.ide";
	BuildManager::ItemDefinitionFileNames[31] = "\\data\\maps\\LA\\LAn2.ide";
	BuildManager::ItemDefinitionFileNames[32] = "\\data\\maps\\LA\\LAs.ide";
	BuildManager::ItemDefinitionFileNames[33] = "\\data\\maps\\LA\\LAs2.ide";
	BuildManager::ItemDefinitionFileNames[34] = "\\data\\maps\\LA\\LAw.ide";
	BuildManager::ItemDefinitionFileNames[35] = "\\data\\maps\\LA\\LAw2.ide";
	BuildManager::ItemDefinitionFileNames[36] = "\\data\\maps\\LA\\LaWn.ide";
	BuildManager::ItemDefinitionFileNames[37] = "\\data\\maps\\LA\\LAxref.ide";

	BuildManager::ItemDefinitionFileNames[38] = "\\data\\maps\\leveldes\\leveldes.ide";
	BuildManager::ItemDefinitionFileNames[39] = "\\data\\maps\\leveldes\\levelmap.ide";
	BuildManager::ItemDefinitionFileNames[40] = "\\data\\maps\\leveldes\\levelxre.ide";
	BuildManager::ItemDefinitionFileNames[41] = "\\data\\maps\\leveldes\\seabed.ide";

	BuildManager::ItemDefinitionFileNames[42] = "\\data\\maps\\SF\\SFe.ide";
	BuildManager::ItemDefinitionFileNames[43] = "\\data\\maps\\SF\\SFn.ide";
	BuildManager::ItemDefinitionFileNames[44] = "\\data\\maps\\SF\\SFs.ide";
	BuildManager::ItemDefinitionFileNames[45] = "\\data\\maps\\SF\\SFSe.ide";
	BuildManager::ItemDefinitionFileNames[46] = "\\data\\maps\\SF\\SFw.ide";
	BuildManager::ItemDefinitionFileNames[47] = "\\data\\maps\\SF\\SFxref.ide";

	BuildManager::ItemDefinitionFileNames[48] = "\\data\\maps\\vegas\\vegasE.ide";
	BuildManager::ItemDefinitionFileNames[49] = "\\data\\maps\\vegas\\VegasN.ide";
	BuildManager::ItemDefinitionFileNames[50] = "\\data\\maps\\vegas\\VegasS.ide";
	BuildManager::ItemDefinitionFileNames[51] = "\\data\\maps\\vegas\\VegasW.ide";
	BuildManager::ItemDefinitionFileNames[52] = "\\data\\maps\\vegas\\vegaxref.ide";

	BuildManager::ItemDefinitionFileNames[53] = "\\data\\maps\\veh_mods\\veh_mods.ide";
}

bool BuildManager::ReadColFile(const char fname[])
{
	std::ifstream file;
	char* data;
	std::streampos fsize = 0;
	unsigned int offset = 0;

	file.open(fname, std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{//Will error on 2 files because of the path's
		//cout << "(Failed to open) Error on file: " << fname << '\n';
		return false;
	}


	fsize = file.tellg();

	BuildManager::backgroundWorkerRefrence->ReportProgress(0, "fize = " + (uint32_t)fsize + "\n");
	data = new char[(uint32_t)fsize];

	file.seekg(0, std::ios::beg);
	file.read(data, fsize);
	file.close();

	while (offset < fsize && !strncmp(data + offset, "COL", 3))
	{
		uint32_t size = *(uint32_t*)(data + offset + 4);
		BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Size2 = " + (uint32_t)size + "\n");
		if (size > 0)
		{
			BuildManager::ColModel model = BuildManager::ReadColModel(data + offset);

			BuildManager::COLArray.push_back(model);
			BuildManager::COLArrayVectorIndex++;

			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Name of model = " + gcnew String(model.name.c_str()) + "\n\n");
			offset += 8 + size;
		}
		else
		{
			break;
		}
	}

	delete[] data;

	return true;
}

//much code can be skipped in here.
BuildManager::ColModel BuildManager::ReadColModel(char* data)
{
	char* data_start = data;
	bool v1 = false, v2 = false, v3 = false;
	BuildManager::ColModel model;

	// Get the version
	switch (*(data + 3))
	{
	case '3':
		v3 = true;
		break;
	case '2':
		v2 = true;
		break;
	case 'L':
		v1 = true;
		break;
	}
	data += 8;

	// Model name
	model.name = std::string(data);
	data += 22;

	// Model modelid
	model.modelid = *(int16_t*)data;

	data += 42;

	if (v1)
	{
		// Spheres
		model.num_spheres = *(uint32_t*)data;
		data += 4;
		model.spheres = new BuildManager::ColSphere[model.num_spheres];

		for (uint32_t i = 0; i < model.num_spheres; i++)
		{
			model.spheres[i].radius = *(float*)data;
			data += 4;

			model.spheres[i].center = *(BuildManager::Vertex*)data;
			data += 16;
		}

		// Unknown
		data += 4;

		// Boxes
		model.num_boxes = *(uint32_t*)data;
		data += 4;

		model.boxes = new BuildManager::ColBox[model.num_boxes];

		memcpy(model.boxes, data, model.num_boxes * sizeof(BuildManager::ColBox));
		data += model.num_boxes * sizeof(BuildManager::ColBox);

		// Vertices
		uint32_t num_vertices = *(uint32_t*)data;
		data += 4;

		BuildManager::Vertex* vertices = new BuildManager::Vertex[num_vertices];

		memcpy(vertices, data, num_vertices * sizeof(BuildManager::Vertex));
		data += num_vertices * sizeof(BuildManager::Vertex);

		// Faces
		model.num_faces = *(uint32_t*)data;
		data += 4;

		model.faces = new BuildManager::ColFace[model.num_faces];

		for (uint32_t i = 0; i < model.num_faces; i++)
		{
			uint32_t a_idx = *(uint32_t*)data;  data += 4;
			uint32_t b_idx = *(uint32_t*)data;  data += 4;
			uint32_t c_idx = *(uint32_t*)data;  data += 4;

			data += 4;

			model.faces[i].a = &vertices[a_idx];
			model.faces[i].b = &vertices[b_idx];
			model.faces[i].c = &vertices[c_idx];
		}
		delete[] vertices;
	}
	else
	{
		uint32_t offset_spheres = 0;
		uint32_t offset_boxes = 0;
		uint32_t offset_vertices = 0;
		uint32_t offset_faces = 0;

		model.num_spheres = *(uint16_t*)data;  data += 2;
		model.num_boxes = *(uint16_t*)data;  data += 2;
		model.num_faces = *(uint32_t*)data;

		data += 8;

		offset_spheres = *(uint32_t*)data;  data += 4;
		offset_boxes = *(uint32_t*)data;

		data += 8;

		offset_vertices = *(uint32_t*)data;  data += 4;
		offset_faces = *(uint32_t*)data;

		data += 8;

		if (v3)
		{
			data += 12;
		}

		// Spheres
		data = data_start + 4 + offset_spheres;
		model.spheres = new BuildManager::ColSphere[model.num_spheres];
		memcpy(model.spheres, data, model.num_spheres * sizeof(BuildManager::ColSphere));
		data += model.num_spheres * sizeof(BuildManager::ColSphere);

		// Boxes
		data = data_start + 4 + offset_boxes;
		model.boxes = new BuildManager::ColBox[model.num_boxes];
		memcpy(model.boxes, data, model.num_boxes * sizeof(BuildManager::ColBox));
		data += model.num_boxes * sizeof(BuildManager::ColBox);

		// Faces
		data = data_start + 4 + offset_faces;
		model.faces = new BuildManager::ColFace[model.num_faces];
		uint16_t* a_idx = new uint16_t[model.num_faces];
		uint16_t* b_idx = new uint16_t[model.num_faces];
		uint16_t* c_idx = new uint16_t[model.num_faces];

		int top_idx = 0;

		for (uint32_t i = 0; i < model.num_faces; i++)
		{
			a_idx[i] = *(uint16_t*)data;  data += 2;
			b_idx[i] = *(uint16_t*)data;  data += 2;
			c_idx[i] = *(uint16_t*)data;  data += 2;

			if (a_idx[i] > top_idx) top_idx = a_idx[i];
			if (b_idx[i] > top_idx) top_idx = b_idx[i];
			if (c_idx[i] > top_idx) top_idx = c_idx[i];

			data += 2;
		}

		// Vertices
		if (model.num_faces && top_idx)
		{
			uint32_t num_vertices = top_idx + 1;
			BuildManager::Vertex* vertices = new BuildManager::Vertex[num_vertices];
			data = data_start + 4 + offset_vertices;

			for (uint32_t i = 0; i < num_vertices; i++)
			{
				vertices[i].x = (*(int16_t*)data) / 128.0f;  data += 2;
				vertices[i].y = (*(int16_t*)data) / 128.0f;  data += 2;
				vertices[i].z = (*(int16_t*)data) / 128.0f;  data += 2;
			}

			for (uint32_t i = 0; i < model.num_faces; i++)
			{

				model.faces[i].a = &vertices[a_idx[i]];
				model.faces[i].b = &vertices[b_idx[i]];
				model.faces[i].c = &vertices[c_idx[i]];
			}

			delete[] vertices;
		}

		delete[] a_idx;
		delete[] b_idx;
		delete[] c_idx;
	}
	return model;
}


bool BuildManager::ExtractImageFiles()
{
	uint8_t Size = BuildManager::ImageFileNames.size();
	if (!UsingSAMPObjects && !UsingCustomObjects) Size--;

	for (uint8_t i = 0; i < Size; i++)
	{
		std::ifstream ImageFile;

		ImageFile.open(BuildManager::GTAInstallDirectory + BuildManager::ImageFileNames.at(i), std::ios::binary);

		if (ImageFile.is_open())
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Opened archive: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ImageFileNames.at(i)).c_str()) + "\n");

			ImageFile.seekg(0, std::ios::beg);

			char HeaderInfo[8];
			ImageFile.read(HeaderInfo, 8);//getting only the header info for now

			uint32_t FileIndex = 0;
			uint32_t EntryCount = 0;
			char Version[5];

			GetBytes(HeaderInfo, Version, FileIndex, 4);
			Version[4] = '\0';

			GetBytes(HeaderInfo, EntryCount, FileIndex, 4);

			uint32_t DirectorylistingSize = EntryCount * 32;

			char * Buffer = new char[DirectorylistingSize];
			ImageFile.read(Buffer, DirectorylistingSize);

			FileIndex = 0;

			uint32_t SectorOffset;
			uint16_t SectorSize;
			char Filename[24];

			for (uint32_t i = 0; i < EntryCount; i++)
			{
				GetBytes(Buffer, SectorOffset, FileIndex, 4);
				GetBytes(Buffer, SectorSize, FileIndex, 2);
				FileIndex += 2;

				GetBytes(Buffer, Filename, FileIndex, 24);

				std::string str(Filename);
				uint32_t DataArraySize = SectorSize * 2048;
				std::streampos NewOffset = SectorOffset * 2048;// + FileIndex;

				if (str.find(".col") != std::string::npos)
				{
					BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String(Filename) + "\n");

					ImageFile.seekg(NewOffset, ImageFile.beg);

					char* data = new char[DataArraySize];
					ImageFile.read(data, DataArraySize);

					//The whole col file is alligned to the 2048 byte block size
					uint32_t offset = 0;

					while (offset < NewOffset && !strncmp(data + offset, "COL", 3))
					{
						uint32_t size = *(uint32_t*)(data + offset + 4);

						if (size > 0)
						{
							BuildManager::ColModel model = ReadColModel(data + offset);

							BuildManager::COLArray.push_back(model);
							BuildManager::COLArrayVectorIndex++;

							offset += 8 + size;
						}
						else
						{
							break;
						}
					}

					//return the reader back to the current header position. 
					ImageFile.seekg(FileIndex, ImageFile.beg);
					delete[] data;
				}//end col
				else if (str.find(".ipl") != std::string::npos)
				{
					BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String(Filename) + "\n");

					ImageFile.seekg(NewOffset, ImageFile.beg);

					char* data = new char[DataArraySize];
					ImageFile.read(data, DataArraySize);

					ReadBinaryItemPlacmentData(data);

					//return the reader back to the current header position. 
					ImageFile.seekg(FileIndex, ImageFile.beg);
					delete[] data;
				}

			}
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "\n");
			delete[] Buffer;
		}
		else
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Failed to open archive: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ImageFileNames.at(i)).c_str()) + "\n");
			return false;
		}
	}
	return true;
}

//throws: invalid allocation size: 4294967295 error. I assume this is because these files are of version "COLL" / version 1
bool BuildManager::ExtractCollisionFiles()
{
	bool ReturnValue = true;
	for (uint8_t i = 0; i < BuildManager::CollisionFileNames.size(); i++)
	{

		if (BuildManager::ReadColFile((BuildManager::GTAInstallDirectory + BuildManager::CollisionFileNames.at(i)).c_str()))
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::CollisionFileNames.at(i)).c_str()) + "\n");
		else
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Failed to load: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::CollisionFileNames.at(i)).c_str()) + "\n");
			ReturnValue = false;
		}
	}
	return true;
}
void BuildManager::ReadBinaryItemPlacmentData(char* RawIPLData)
{
	uint32_t NumberofItemInstances, FileOffset;

	memcpy(&NumberofItemInstances, RawIPLData + 4, 4);
	memcpy(&FileOffset, RawIPLData + 28, 4);

	uint32_t TempModelid;

	for (uint32_t i = 0; i < NumberofItemInstances; i++)
	{
		BuildManager::IPLArray.push_back(BuildManager::IPLObject());
		BuildManager::IPLArrayVectorIndex++;

		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.x, FileOffset, 4);
		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.y, FileOffset, 4);
		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.z, FileOffset, 4);

		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.x, FileOffset, 4);
		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.y, FileOffset, 4);
		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.z, FileOffset, 4);
		GetBytes(RawIPLData, BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.w, FileOffset, 4);


		GetBytes(RawIPLData, TempModelid, FileOffset, 4);
		BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].modelid = static_cast<uint16_t>(TempModelid);

		FileOffset += 8; //Skip Interiorid, lodflag
	}
}
bool BuildManager::ReadItemPlacmentData(const char fname[])
{
	std::ifstream IPLFile;

	IPLFile.open(fname, std::ios::binary | std::ios::ate);

	if (IPLFile.is_open())
	{
		std::streampos fsize = 0;
		char* RawIPLData;

		IPLFile.seekg(0, IPLFile.end);
		fsize = IPLFile.tellg();
		RawIPLData = new char[(int)fsize];

		IPLFile.seekg(0, std::ios::beg);
		IPLFile.read(RawIPLData, fsize);
		IPLFile.close();

		int32_t FileOffset;

		char IPLString[5];
		memcpy(IPLString, RawIPLData, 4);

		IPLString[4] = '\0';

		if (strcmp(IPLString, "bnry\0") != 0)
		{
			FileOffset = 0;

			char TestSingleChar[2];
			TestSingleChar[0] = 0;

			std::vector<char> WholeLine;

			int DataBlockType = 0;
			while (FileOffset <fsize)//While not end of file.
			{
				memset(&TestSingleChar[0], 0, sizeof(TestSingleChar));
				memcpy(TestSingleChar, RawIPLData + FileOffset, 1);
				TestSingleChar[1] = 0; /* Add terminator */
				FileOffset++;

				WholeLine.push_back(TestSingleChar[0]);

				if (TestSingleChar[0] == '\n')
				{
					char* CurrentLine = new char[WholeLine.size() - 1];
					std::copy(WholeLine.begin(), WholeLine.end() - 2, CurrentLine); //Unsafe, recode required (do not disable this compiler warning)
					
					//for (std::vector<char>::iterator it = WholeLine.begin(); it != WholeLine.end()-2; ++it) {
						//CurrentLine += *it;
					//}

					CurrentLine[WholeLine.size() - 2] = '\0';



					if (strcmp(CurrentLine, "inst") == 0) DataBlockType = 1;
					else if (strcmp(CurrentLine, "end") == 0)
					{
						if (DataBlockType == 1) DataBlockType = 0;
					}
					else
					{
						if (DataBlockType == 1)
						{
							uint32_t LineOffset = 0;
							std::vector<char> CurrentValue;
							uint8_t CurrentDataValue = 1;

							BuildManager::IPLArray.push_back(BuildManager::IPLObject());
							BuildManager::IPLArrayVectorIndex++;

							while (LineOffset < WholeLine.size())
							{
								if (WholeLine[LineOffset] == ',' && WholeLine[LineOffset + 1] == ' ')
								{
									LineOffset++;
									char* TheValue = new char[CurrentValue.size() + 1];
									std::copy(CurrentValue.begin(), CurrentValue.end(), TheValue);
									TheValue[CurrentValue.size()] = '\0';
									std::string ValueSTR(TheValue);
									delete[] TheValue;
									switch (CurrentDataValue)
									{
									case 1:
									{
										int TempModelid = std::stoi(ValueSTR);
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].modelid = static_cast<uint16_t>(TempModelid);
										break;
									}
									case 2:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Modelname = ValueSTR;
										break;
									}
									case 4:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.x = stof(ValueSTR);
										break;
									}
									case 5:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.y = stof(ValueSTR);
										break;
									}
									case 6:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Position.z = stof(ValueSTR);
										break;
									}
									case 7:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.x = stof(ValueSTR);
										break;
									}
									case 8:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.y = stof(ValueSTR);
										break;
									}
									case 9:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.z = stof(ValueSTR);
										break;
									}
									case 10:
									{
										BuildManager::IPLArray[BuildManager::IPLArrayVectorIndex].Rotation.w = stof(ValueSTR);
										break;
									}
									}

									CurrentDataValue++;
									CurrentValue.clear();
								}
								else if (WholeLine[LineOffset + 1] == '\n' || WholeLine[LineOffset + 1] == '\r')
								{
									CurrentValue.push_back(WholeLine[LineOffset]);
									break;//Exit the while loop since we are done here.
								}
								else
								{
									CurrentValue.push_back(WholeLine[LineOffset]);
								}
								LineOffset++;
							}
						}
					}

					WholeLine.clear();
					delete[] CurrentLine;
				}
			}
		}
		delete[] RawIPLData;
		return true;
	}
	else return false;
}
bool BuildManager::ExtractItemPlacementFiles()
{
	bool ReturnValue = true;
	for (uint8_t i = 0; i < BuildManager::ItemPlacementFileNames.size(); i++)
	{
		if (BuildManager::ReadItemPlacmentData((BuildManager::GTAInstallDirectory + BuildManager::ItemPlacementFileNames.at(i)).c_str()))
			backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ItemPlacementFileNames.at(i)).c_str()) + "\n");
		else
		{
			backgroundWorkerRefrence->ReportProgress(0, "Failed to load: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ItemPlacementFileNames.at(i)).c_str()) + "\n");
			ReturnValue = false;
		}
	}
	return true;
}

bool BuildManager::ExtractItemDefinitionFiles()
{
	bool ReturnValue = true;
	
	
	for (uint8_t i = 0; i < BuildManager::ItemDefinitionFileNames.size(); i++)
	{
		if (ReadItemDefinitionFile((BuildManager::GTAInstallDirectory + BuildManager::ItemDefinitionFileNames.at(i)).c_str()))
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ItemDefinitionFileNames.at(i)).c_str()) + "\n");
		else
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Failed to load: " + gcnew String((BuildManager::GTAInstallDirectory + BuildManager::ItemDefinitionFileNames.at(i)).c_str()) + "\n");
			ReturnValue = false;
		}
	}

	if(UsingSAMPObjects)
	{
		if (ReadItemDefinitionFile((BuildManager::GTAInstallDirectory + "\\SAMP\\SAMP.ide").c_str()))
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String((BuildManager::GTAInstallDirectory + "\\SAMP\\SAMP.ide").c_str()) + "\n");
		else
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Failed to load: " + gcnew String((BuildManager::GTAInstallDirectory + "\\SAMP\\SAMP.ide").c_str()) + "\n");
			ReturnValue = false;
		}
	}

	if(UsingCustomObjects)
	{
		if (ReadItemDefinitionFile((BuildManager::GTAInstallDirectory + "\\SAMP\\CUSTOM.ide").c_str()))
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Loaded: " + gcnew String((BuildManager::GTAInstallDirectory + "\\SAMP\\CUSTOM.ide").c_str()) + "\n");
		else
		{
			BuildManager::backgroundWorkerRefrence->ReportProgress(0, "Failed to load: " + gcnew String((BuildManager::GTAInstallDirectory + "\\SAMP\\CUSTOM.ide").c_str()) + "\n");
			ReturnValue = false;
		}
	}
	return ReturnValue;
}
bool BuildManager::ReadItemDefinitionFile(const char fname[])
{
	std::ifstream IDE_File;

	IDE_File.open(fname, std::ios::binary | std::ios::ate);

	if (IDE_File.is_open())
	{
		char* RawIDE_Data;
		std::streampos fsize = 0;

		IDE_File.seekg(0, IDE_File.end);
		fsize = IDE_File.tellg();

		RawIDE_Data = new char[(int)fsize];

		IDE_File.seekg(0, std::ios::beg);
		IDE_File.read(RawIDE_Data, fsize);
		IDE_File.close();

		uint32_t FileOffset = 0;

		char TestSingleChar[2];
		TestSingleChar[0] = 0;

		std::vector<char> WholeLine;

		int DataBlockType = 0;

		int LineCounter = 0;

		while (FileOffset <fsize)//While not end of file.
		{
			memset(&TestSingleChar[0], 0, sizeof(TestSingleChar));
			memcpy(TestSingleChar, RawIDE_Data + FileOffset, 1);
			TestSingleChar[1] = 0; /* Add terminator */
			FileOffset++;

			WholeLine.push_back(TestSingleChar[0]);
			LineCounter++;

			if (TestSingleChar[0] == '\n')
			{
				std::string CurrentLine(WholeLine.begin(), WholeLine.end() - 2);

				if (CurrentLine == "objs") DataBlockType = 1;
				else if (CurrentLine == "tobj") DataBlockType = 2;
				else if (CurrentLine == "anim") DataBlockType = 3;
				else if (CurrentLine == "weap") DataBlockType = 4;
				else if (CurrentLine == "end")
				{
					DataBlockType = 0;
				}
				else
				{
					if (DataBlockType == 1)
					{
						uint32_t LineOffset = 0;
						uint8_t CurrentDataValue = 0;
						uint16_t modelid;
						float DrawDist;
						std::string ModelName;
						std::vector<char> CurrentValue;
						bool IsArrayUpdatePermitted = true;
						while (LineOffset < WholeLine.size())
						{
							if (WholeLine[LineOffset] == '#')
							{//This is for default.dat support 
								IsArrayUpdatePermitted = false;
								break;
							}
							else if (WholeLine[LineOffset] == ',' && WholeLine[LineOffset + 1] == ' ')
							{
								LineOffset++;
								std::string ValueSTR(CurrentValue.begin(), CurrentValue.end());
								switch (CurrentDataValue)
								{
								case 0:
								{
									int TempModelid = std::stoi(ValueSTR);
									modelid = static_cast<uint16_t>(TempModelid);
									break;
								}
								case 1:
								{
									ModelName = ValueSTR;
									break;
								}
								case 3:
								{
									DrawDist = std::stof(ValueSTR);
									break;
								}
								}
								CurrentDataValue++;
								CurrentValue.clear();
							}
							else if (WholeLine[LineOffset + 1] == '\n' || WholeLine[LineOffset + 1] == '\r')
							{
								CurrentValue.push_back(WholeLine[LineOffset]);
								break;//Exit the while loop since we are done here.
							}
							else
								CurrentValue.push_back(WholeLine[LineOffset]);

							LineOffset++;
						}
						if (IsArrayUpdatePermitted)
						{
							BuildManager::Modelid_Modelname_Vector.push_back(BuildManager::Modelid_Modelname_Struct());
							BuildManager::Modelid_Modelname_VectorIndex++;

							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].modelid = modelid;
							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].ModelName = ModelName;
							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].DrawDist = DrawDist;
						}
					}
					else if (DataBlockType == 2)
					{
						uint32_t LineOffset = 0;
						uint8_t CurrentDataValue = 0;
						std::vector<char> CurrentValue;

						BuildManager::Modelid_Modelname_Vector.push_back(BuildManager::Modelid_Modelname_Struct());
						BuildManager::Modelid_Modelname_VectorIndex++;

						while (LineOffset < WholeLine.size())
						{
							if (WholeLine[LineOffset] == ',' && WholeLine[LineOffset + 1] == ' ')
							{
								LineOffset++;
								std::string ValueSTR(CurrentValue.begin(), CurrentValue.end());

								switch (CurrentDataValue)
								{
								case 0:
								{
									int TempModelid = std::stoi(ValueSTR);
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].modelid = static_cast<uint16_t>(TempModelid);
									break;
								}
								case 1:
								{
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].ModelName = ValueSTR;
									break;
								}
								case 3:
								{
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].DrawDist = std::stof(ValueSTR);
									break;
								}
								}
								CurrentDataValue++;
								CurrentValue.clear();
							}
							else if (WholeLine[LineOffset + 1] == '\n' || WholeLine[LineOffset + 1] == '\r')
							{
								CurrentValue.push_back(WholeLine[LineOffset]);
								break;//Exit the while loop since we are done here.
							}
							else
								CurrentValue.push_back(WholeLine[LineOffset]);

							LineOffset++;
						}
					}

					else if (DataBlockType == 3)
					{
						uint32_t LineOffset = 0;
						uint8_t CurrentDataValue = 0;

						std::vector<char> CurrentValue;

						BuildManager::Modelid_Modelname_Vector.push_back(BuildManager::Modelid_Modelname_Struct());
						BuildManager::Modelid_Modelname_VectorIndex++;

						while (LineOffset < WholeLine.size())
						{
							if (WholeLine[LineOffset] == ' ' && WholeLine[LineOffset + 1] == ',')
							{
								LineOffset++;
								std::string ValueSTR(CurrentValue.begin(), CurrentValue.end());

								switch (CurrentDataValue)
								{
								case 0:
								{
									int TempModelid = std::stoi(ValueSTR);
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].modelid = static_cast<uint16_t>(TempModelid);
									break;
								}
								case 1:
								{
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].ModelName = ValueSTR;
									break;
								}
								case 4:
								{
									BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].DrawDist = std::stof(ValueSTR);
									break;
								}
								}

								CurrentDataValue++;
								CurrentValue.clear();
							}
							else if (WholeLine[LineOffset + 1] == '\n' || WholeLine[LineOffset + 1] == '\r')
							{
								CurrentValue.push_back(WholeLine[LineOffset]);
								break;//Exit the while loop since we are done here.
							}
							else
								CurrentValue.push_back(WholeLine[LineOffset]);

							LineOffset++;
						}
					}
					else if (DataBlockType == 4)
					{
						if (WholeLine.size() < 3)
						{
							WholeLine.clear();
							LineCounter = 0;
							continue;
						}
						uint32_t LineOffset = 0;
						uint8_t CurrentDataValue = 0;
						uint16_t modelid;
						float DrawDist;
						std::string ModelName;
						std::vector<char> CurrentValue;
						bool IsArrayUpdatePermitted = true;

						int tempcount = 0;
						while (LineOffset < WholeLine.size())
						{
							if (WholeLine[LineOffset] == '#')//This is for default.dat support
							{
								IsArrayUpdatePermitted = false;
								break;
							}
							if (WholeLine[LineOffset] == ',' && WholeLine[LineOffset + 1] == ' ')
							{
								LineOffset++;
								std::string ValueSTR(CurrentValue.begin(), CurrentValue.end());
								switch (CurrentDataValue)
								{
								case 0:
								{
									int TempModelid = std::stoi(ValueSTR);
									modelid = static_cast<uint16_t>(TempModelid);
									break;
								}
								case 1:
								{
									ModelName = ValueSTR;
									break;
								}
								case 5:
								{
									DrawDist = std::stof(ValueSTR);
									break;
								}
								}

								CurrentDataValue++;
								CurrentValue.clear();
							}

							else if (WholeLine[LineOffset + 1] == '\n' || WholeLine[LineOffset + 1] == '\r')
							{
								if (WholeLine[LineOffset] == 13)
								{
									break;
								}
								CurrentValue.push_back(WholeLine[LineOffset]);
								break;//Exit the while loop since we are done here.
							}
							else
								CurrentValue.push_back(WholeLine[LineOffset]);

							LineOffset++;
						}
						if (IsArrayUpdatePermitted)
						{
							BuildManager::Modelid_Modelname_Vector.push_back(BuildManager::Modelid_Modelname_Struct());
							BuildManager::Modelid_Modelname_VectorIndex++;

							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].modelid = modelid;
							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].ModelName = ModelName;
							BuildManager::Modelid_Modelname_Vector[BuildManager::Modelid_Modelname_VectorIndex].DrawDist = DrawDist;
						}
					}
				}

				WholeLine.clear();
				LineCounter = 0;
			}
		}
		delete[] RawIDE_Data;
		return true;
	}
	else return false;
}

void BuildManager::PrepareDatabaseStructures()
{
	{
		uint32_t InnerArrayIterator = 0;

		bool ModelidMatch, ModelnameMatch, EntryFound;

		for (uint32_t i = 0; i <= BuildManager::Modelid_Modelname_VectorIndex; i++)
		{
			EntryFound = false;
			for (uint16_t j = 0; j <= BuildManager::COLArrayVectorIndex; j++)
			{
				if (BuildManager::Modelid_Modelname_Vector[i].ModelName == BuildManager::COLArray[j].name)
				{
					EntryFound = true;
					BuildManager::COLArray[j].modelid = BuildManager::Modelid_Modelname_Vector[i].modelid;
					break;
				}
			}

			if (!EntryFound)
			{
				BuildManager::Modelid_Modelname_Vector.erase(BuildManager::Modelid_Modelname_Vector.begin() + i);
				BuildManager::Modelid_Modelname_VectorIndex--;
				i--;
				continue;
			}

			//delete all the LOD entries we find here.
			std::string ModelnameTemp;
			for (unsigned int j = 0; j < BuildManager::Modelid_Modelname_Vector[i].ModelName.length(); ++j)
			{
				ModelnameTemp += toupper(BuildManager::Modelid_Modelname_Vector[i].ModelName.at(j));
			}
			std::size_t found = ModelnameTemp.find("LOD");
			if (found != std::string::npos)
			{
				//we found LOD, lets not continue PARENT loop for this iteration of i
				BuildManager::Modelid_Modelname_Vector.erase(BuildManager::Modelid_Modelname_Vector.begin() + i);
				BuildManager::Modelid_Modelname_VectorIndex--;
				i--;
				continue;
			}

			InnerArrayIterator = 0;

			while (InnerArrayIterator <= BuildManager::IPLArrayVectorIndex)
			{//This loop will break when any match occours. Not sure if this is good or bad.
				ModelidMatch = false, ModelnameMatch = false;

				if (BuildManager::Modelid_Modelname_Vector[i].modelid == BuildManager::IPLArray[InnerArrayIterator].modelid) ModelidMatch = true;
				if (BuildManager::Modelid_Modelname_Vector[i].ModelName.compare(BuildManager::IPLArray[InnerArrayIterator].Modelname) == 0) ModelnameMatch = true;

				if (ModelidMatch || ModelnameMatch) break;
				else InnerArrayIterator++;
			}
			if (ModelidMatch && !ModelnameMatch)
			{
				if (BuildManager::IPLArray[InnerArrayIterator].Modelname.empty())
				{
					if (!BuildManager::Modelid_Modelname_Vector[i].ModelName.empty())
					{
						BuildManager::IPLArray[InnerArrayIterator].Modelname = BuildManager::Modelid_Modelname_Vector[i].ModelName;
					}
				}
				else if (BuildManager::Modelid_Modelname_Vector[i].ModelName.empty())
				{
					if (!BuildManager::IPLArray[InnerArrayIterator].Modelname.empty())
					{
						BuildManager::Modelid_Modelname_Vector[i].ModelName = BuildManager::IPLArray[InnerArrayIterator].Modelname;
					}
				}
			}
			else if (!ModelidMatch && ModelnameMatch)
			{
				BuildManager::IPLArray[InnerArrayIterator].modelid = BuildManager::Modelid_Modelname_Vector[i].modelid;
			}
		}
	}

	//Alphasorting COL array
	std::sort(BuildManager::COLArray.begin(), BuildManager::COLArray.end(), [](BuildManager::ColModel const &a, BuildManager::ColModel const &b){ return a.modelid < b.modelid; });

	{
		uint16_t InnerArrayIterator = 0;

		bool ModelidMatch, ModelnameMatch;

		for (uint32_t i = 0; i <= BuildManager::IPLArrayVectorIndex; i++)
		{
			ModelidMatch = false, ModelnameMatch = false;
			InnerArrayIterator = 0;

			while (InnerArrayIterator <= BuildManager::COLArrayVectorIndex)
			{
				if (BuildManager::IPLArray[i].modelid == BuildManager::COLArray[InnerArrayIterator].modelid) ModelidMatch = true;
				if (BuildManager::IPLArray[i].Modelname.compare(BuildManager::COLArray[InnerArrayIterator].name) == 0) ModelnameMatch = true;

				if (ModelidMatch || ModelnameMatch) break;
				else InnerArrayIterator++;
			}

			if (!ModelidMatch && !ModelnameMatch)
			{
				//Remove from IPL array
				BuildManager::IPLArray.erase(BuildManager::IPLArray.begin() + i);
				BuildManager::IPLArrayVectorIndex--;
			}
			else if (ModelidMatch && !ModelnameMatch)
			{
				bool TriggerException = true;
				if (BuildManager::IPLArray[i].Modelname.empty())
				{
					if (!BuildManager::COLArray[InnerArrayIterator].name.empty())
					{
						BuildManager::IPLArray[i].Modelname = BuildManager::COLArray[InnerArrayIterator].name;
						TriggerException = false;
					}
				}
				else if (BuildManager::COLArray[InnerArrayIterator].name.empty())
				{
					if (!BuildManager::IPLArray[i].Modelname.empty())
					{
						BuildManager::COLArray[InnerArrayIterator].name = BuildManager::IPLArray[i].Modelname;
						TriggerException = false;
					}
				}

				if (TriggerException)
				{
					if (!BuildManager::COLArray[InnerArrayIterator].name.empty())
					{
						BuildManager::IPLArray[i].Modelname = BuildManager::COLArray[InnerArrayIterator].name;
					}
				}
			}
			else if (!ModelidMatch && ModelnameMatch)
			{
				BuildManager::IPLArray[i].modelid = BuildManager::COLArray[InnerArrayIterator].modelid;
			}
		}
	}
}

bool BuildManager::WriteBinaryFile(const char fname[])
{
	//Begin writing file
	std::ofstream ColAndreasBinaryfile;
	ColAndreasBinaryfile.open(fname, std::ios::out | std::ios::binary);
	if (ColAndreasBinaryfile.is_open())
	{
		//Filetype in header (standard binary file format) "Otherwise you could give it any old file and it would load it."
		char FileExtension[5] = "cadf";
		ColAndreasBinaryfile.write((char *)&FileExtension, 5);

		//Number of collision files
		ColAndreasBinaryfile.write((char *)&(BuildManager::COLArrayVectorIndex), 2);

		//Number of item placment entries
		ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArrayVectorIndex), 4);

		for (uint16_t i = 0; i < BuildManager::COLArrayVectorIndex + 1; i++)
		{
			//Modelid
			ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].modelid), 2);

			//number of collision spheres
			uint16_t SphereCount = static_cast<uint16_t> (BuildManager::COLArray[i].num_spheres);
			ColAndreasBinaryfile.write((char *)&SphereCount, 2);

			//number of collision boxes
			uint16_t BoxCount = static_cast<uint16_t> (BuildManager::COLArray[i].num_boxes);
			ColAndreasBinaryfile.write((char *)&BoxCount, 2);

			//number of collision faces
			uint16_t FaceCount = static_cast<uint16_t> (BuildManager::COLArray[i].num_faces);
			ColAndreasBinaryfile.write((char *)&FaceCount, 2);

			//Sphere data
			for (uint32_t j = 0; j < BuildManager::COLArray[i].num_spheres; j++) {
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].spheres[j].center.x), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].spheres[j].center.y), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].spheres[j].center.z), 4);

				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].spheres[j].radius), 4);
			}

			//Box data
			for (uint32_t j = 0; j < BuildManager::COLArray[i].num_boxes; j++)
			{
				//Convert the data to save CPU ticks, when the ColAndreas plugin loads
				float CenterX = (BuildManager::COLArray[i].boxes[j].min.x + BuildManager::COLArray[i].boxes[j].max.x) / 2;
				float CenterY = (BuildManager::COLArray[i].boxes[j].min.y + BuildManager::COLArray[i].boxes[j].max.y) / 2;
				float CenterZ = (BuildManager::COLArray[i].boxes[j].min.z + BuildManager::COLArray[i].boxes[j].max.z) / 2;

				float BoxsizeX = (BuildManager::COLArray[i].boxes[j].max.x - BuildManager::COLArray[i].boxes[j].min.x) / 2;
				float BoxsizeY = (BuildManager::COLArray[i].boxes[j].max.y - BuildManager::COLArray[i].boxes[j].min.y) / 2;
				float BoxsizeZ = (BuildManager::COLArray[i].boxes[j].max.z - BuildManager::COLArray[i].boxes[j].min.z) / 2;

				ColAndreasBinaryfile.write((char *)&CenterX, 4);
				ColAndreasBinaryfile.write((char *)&CenterY, 4);
				ColAndreasBinaryfile.write((char *)&CenterZ, 4);

				ColAndreasBinaryfile.write((char *)&BoxsizeX, 4);
				ColAndreasBinaryfile.write((char *)&BoxsizeY, 4);
				ColAndreasBinaryfile.write((char *)&BoxsizeZ, 4);
			}

			//Face data
			for (uint32_t j = 0; j < BuildManager::COLArray[i].num_faces; j++)
			{
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].a->x), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].a->y), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].a->z), 4);

				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].b->x), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].b->y), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].b->z), 4);

				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].c->x), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].c->y), 4);
				ColAndreasBinaryfile.write((char *)&(BuildManager::COLArray[i].faces[j].c->z), 4);
			}
		}

		//IPL modelid, x,y,z x,y,z,w
		for (uint32_t i = 0; i < BuildManager::IPLArrayVectorIndex + 1; i++)
		{
			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].modelid), 2);

			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Position.x), 4);
			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Position.y), 4);
			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Position.z), 4);

			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Rotation.x), 4);
			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Rotation.y), 4);
			ColAndreasBinaryfile.write((char *)&(BuildManager::IPLArray[i].Rotation.z), 4);

			float W_correction = BuildManager::IPLArray[i].Rotation.w * -1.0f;
			ColAndreasBinaryfile.write((char *)&W_correction, 4);
		}

		ColAndreasBinaryfile.close();
		return true;
	}
	return false;
}