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
#include "stdafx.h"

/*
Use the .NET framework to read the registry keys, these functions need recoding in .net

bool GetGTAInstallDirectoryFromRegistry(String ^ &OutString)
{
	HKEY key;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Rockstar Games\\GTA San Andreas\\Installation"), REG_OPTION_OPEN_LINK, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS)
	{
		DWORD BufferSize = 8192;

		PPERF_DATA_BLOCK PerfData = (PPERF_DATA_BLOCK)malloc(BufferSize);

		DWORD dwRet = RegQueryValueEx(key, TEXT("ExePath"), NULL, NULL, (LPBYTE)PerfData, &BufferSize);
		
		while (dwRet == ERROR_MORE_DATA)
		{
			BufferSize += 4096;
			PerfData = (PPERF_DATA_BLOCK)realloc(PerfData, BufferSize);
			dwRet = RegQueryValueEx(key, TEXT("ExePath"), NULL, NULL, (LPBYTE)PerfData, &BufferSize);
		}

		if (dwRet == ERROR_SUCCESS)
		{
			OutString = gcnew System::String((const wchar_t *)PerfData);
			return true;
		}

		RegCloseKey(key);
	}
	return false;
}

String^ PrepareGTAPathString(String ^ InString)
{
	
	// "C:\Program Files\Rockstar Games\GTA San Andreas\gta_sa.exe"

	// remove the first character
	// C:\Program Files\Rockstar Games\GTA San Andreas\gta_sa.exe"

	// remove the last 12 characters
	// C:\Program Files\Rockstar Games\GTA San Andreas

	// This logic should work regardless of which folder GTA San Andreas was installed too.


	std::string standardString;
	MarshalString(InString, standardString);

	standardString.erase(0, 1);
	standardString.erase(standardString.end() - 12, standardString.end());

	return gcnew System::String(standardString.c_str());
}
*/

// Source for MarshalString: https://msdn.microsoft.com/en-us/library/1b4az623.aspx 
void MarshalString(String ^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}
