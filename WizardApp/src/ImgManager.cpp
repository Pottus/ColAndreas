#include <algorithm>
#include <cstring>

#include <ImgManager.hpp>

ImgFile::ImgFile(std::string path)
{
	handle = new std::ifstream(path, std::ios::binary);
}

ImgFile::~ImgFile()
{
	delete handle;
}

bool ImgFile::Load()
{
	if(!handle || !handle->is_open()) return false;
	
	handle->read((char*) &header, sizeof(ImgHeader));
	
	if(!strncmp(header.validator, "VER2", 4))
	{
		ImgEntry thisEntry;
		
		for(int i = 0; i < header.entries; ++i)
		{
			handle->read((char*) &thisEntry, sizeof(ImgEntry));
			
			const char *fExtension = NULL;
			
			for(int e = 0; e < sizeof(thisEntry.name); ++e)
			{
				if(!thisEntry.name[e]) break;
				if(thisEntry.name[e] == '.') fExtension = thisEntry.name + e;
				
				thisEntry.name[e] = tolower(thisEntry.name[e]);
			}
			
			if(!fExtension || fExtension == thisEntry.name) continue;
			
			if(!strcmp(fExtension, ".col"))
			{
				COL.emplace_back(thisEntry);
			}
			else if(!strcmp(fExtension, ".ipl"))
			{
				IPL.emplace_back(thisEntry);
			}
		}
		
		return true;
	}
	
	return false;
}
