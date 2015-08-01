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
#include "formColAndreasUI.h"
#include "Splash.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	ColAndreasWizard::formColAndreasUI^ MainForm = gcnew ColAndreasWizard::formColAndreasUI();

	ColAndreasWizard::Splash^ Splash = gcnew ColAndreasWizard::Splash();

	Splash->ShowDialog();

	MainForm->ShowDialog();

	return 0;
}