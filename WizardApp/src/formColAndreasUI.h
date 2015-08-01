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
#using <System.Windows.Forms.DLL>
#include "BuildManager.h"
#include "stdafx.h"
using namespace System::Windows::Forms;
namespace ColAndreasWizard {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for formColAndreasUI
	/// </summary>
	public ref class formColAndreasUI : public System::Windows::Forms::Form
	{
	public:
		formColAndreasUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~formColAndreasUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: bool Use_SAMP_MODELS = true;
	private: bool Use_CUSTOM_MODELS = false;
	private: System::Windows::Forms::Panel^  panelHeaderLogo;
	private: System::Windows::Forms::Panel^  panelLicense;
	private: System::Windows::Forms::Label^  labelLicense;
	private: System::Windows::Forms::Button^  buttonLicenseCancel;
	private: System::Windows::Forms::RadioButton^  radioButtonLicenseReject;
	private: System::Windows::Forms::RadioButton^  radioButtonLicenseAccept;
	private: System::Windows::Forms::Button^  buttonLicenseNext;
	private: System::Windows::Forms::RichTextBox^  richTextBoxLicense;
	private: System::Windows::Forms::Panel^  panelInstallDirectory;
	private: System::Windows::Forms::Button^  buttonInstallDirectoryBack;
	private: System::Windows::Forms::Button^  buttonInstallDirectoryCancel;
	private: System::Windows::Forms::Button^  buttonInstallDirectoryNext;
	private: System::Windows::Forms::Label^  labelInstallDirectory;
	private: System::Windows::Forms::Button^  buttonInstallDirectoryBrowse;
	private: System::Windows::Forms::TextBox^  textBoxInstallDirectory;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialogGTADirectory;
	private: System::Windows::Forms::Panel^  panelColAndreasOutputDirectory;
	private: System::Windows::Forms::Button^  buttonpanelColAndreasOutputDirectoryBack;
	private: System::Windows::Forms::Button^  buttonpanelColAndreasOutputDirectoryCancel;
	private: System::Windows::Forms::Button^  buttonpanelColAndreasOutputDirectoryNext;
	private: System::Windows::Forms::Label^  labelpanelColAndreasOutputDirectory;
	private: System::Windows::Forms::Button^  buttonpanelColAndreasOutputDirectoryBrowse;
	private: System::Windows::Forms::TextBox^  textBoxpanelColAndreasOutputDirectory;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialogColAndreas;
	private: System::Windows::Forms::Panel^  panelPreReview;
	private: System::Windows::Forms::Button^  buttonPreReviewBack;
	private: System::Windows::Forms::Button^  buttonPreReviewCancel;
	private: System::Windows::Forms::Button^  buttonPreReviewStart;
	private: System::Windows::Forms::CheckBox^  checkBoxPreReview_CustomObjects;
	private: System::Windows::Forms::CheckBox^  checkBoxPreReview_SAMPObjects;
	private: System::Windows::Forms::RichTextBox^  richTextBoxPreReview;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Panel^  panelColAndreasBuilder;
	private: System::Windows::Forms::Label^  labelColAndreasBuilder;


	private: System::Windows::Forms::RichTextBox^  richTextBoxColAndreasBuilder;
	private: System::Windows::Forms::ProgressBar^  progressBarColAndreasBuilder;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(formColAndreasUI::typeid));
			this->panelHeaderLogo = (gcnew System::Windows::Forms::Panel());
			this->panelLicense = (gcnew System::Windows::Forms::Panel());
			this->labelLicense = (gcnew System::Windows::Forms::Label());
			this->buttonLicenseCancel = (gcnew System::Windows::Forms::Button());
			this->radioButtonLicenseReject = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonLicenseAccept = (gcnew System::Windows::Forms::RadioButton());
			this->buttonLicenseNext = (gcnew System::Windows::Forms::Button());
			this->richTextBoxLicense = (gcnew System::Windows::Forms::RichTextBox());
			this->panelInstallDirectory = (gcnew System::Windows::Forms::Panel());
			this->buttonInstallDirectoryBack = (gcnew System::Windows::Forms::Button());
			this->buttonInstallDirectoryCancel = (gcnew System::Windows::Forms::Button());
			this->buttonInstallDirectoryNext = (gcnew System::Windows::Forms::Button());
			this->labelInstallDirectory = (gcnew System::Windows::Forms::Label());
			this->buttonInstallDirectoryBrowse = (gcnew System::Windows::Forms::Button());
			this->textBoxInstallDirectory = (gcnew System::Windows::Forms::TextBox());
			this->folderBrowserDialogGTADirectory = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->panelColAndreasOutputDirectory = (gcnew System::Windows::Forms::Panel());
			this->buttonpanelColAndreasOutputDirectoryBack = (gcnew System::Windows::Forms::Button());
			this->buttonpanelColAndreasOutputDirectoryCancel = (gcnew System::Windows::Forms::Button());
			this->buttonpanelColAndreasOutputDirectoryNext = (gcnew System::Windows::Forms::Button());
			this->labelpanelColAndreasOutputDirectory = (gcnew System::Windows::Forms::Label());
			this->buttonpanelColAndreasOutputDirectoryBrowse = (gcnew System::Windows::Forms::Button());
			this->textBoxpanelColAndreasOutputDirectory = (gcnew System::Windows::Forms::TextBox());
			this->saveFileDialogColAndreas = (gcnew System::Windows::Forms::SaveFileDialog());
			this->panelPreReview = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonPreReviewBack = (gcnew System::Windows::Forms::Button());
			this->buttonPreReviewCancel = (gcnew System::Windows::Forms::Button());
			this->buttonPreReviewStart = (gcnew System::Windows::Forms::Button());
			this->checkBoxPreReview_CustomObjects = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxPreReview_SAMPObjects = (gcnew System::Windows::Forms::CheckBox());
			this->richTextBoxPreReview = (gcnew System::Windows::Forms::RichTextBox());
			this->panelColAndreasBuilder = (gcnew System::Windows::Forms::Panel());
			this->labelColAndreasBuilder = (gcnew System::Windows::Forms::Label());
			this->richTextBoxColAndreasBuilder = (gcnew System::Windows::Forms::RichTextBox());
			this->progressBarColAndreasBuilder = (gcnew System::Windows::Forms::ProgressBar());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->panelLicense->SuspendLayout();
			this->panelInstallDirectory->SuspendLayout();
			this->panelColAndreasOutputDirectory->SuspendLayout();
			this->panelPreReview->SuspendLayout();
			this->panelColAndreasBuilder->SuspendLayout();
			this->SuspendLayout();
			// 
			// panelHeaderLogo
			// 
			this->panelHeaderLogo->BackColor = System::Drawing::Color::Transparent;
			this->panelHeaderLogo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panelHeaderLogo.BackgroundImage")));
			this->panelHeaderLogo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panelHeaderLogo->Location = System::Drawing::Point(7, 7);
			this->panelHeaderLogo->Name = L"panelHeaderLogo";
			this->panelHeaderLogo->Size = System::Drawing::Size(610, 80);
			this->panelHeaderLogo->TabIndex = 4;
			// 
			// panelLicense
			// 
			this->panelLicense->BackColor = System::Drawing::Color::Gainsboro;
			this->panelLicense->Controls->Add(this->labelLicense);
			this->panelLicense->Controls->Add(this->buttonLicenseCancel);
			this->panelLicense->Controls->Add(this->radioButtonLicenseReject);
			this->panelLicense->Controls->Add(this->radioButtonLicenseAccept);
			this->panelLicense->Controls->Add(this->buttonLicenseNext);
			this->panelLicense->Controls->Add(this->richTextBoxLicense);
			this->panelLicense->Location = System::Drawing::Point(7, 95);
			this->panelLicense->Name = L"panelLicense";
			this->panelLicense->Size = System::Drawing::Size(609, 341);
			this->panelLicense->TabIndex = 5;
			// 
			// labelLicense
			// 
			this->labelLicense->AutoSize = true;
			this->labelLicense->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelLicense->Location = System::Drawing::Point(6, 1);
			this->labelLicense->Name = L"labelLicense";
			this->labelLicense->Size = System::Drawing::Size(425, 32);
			this->labelLicense->TabIndex = 13;
			this->labelLicense->Text = L"Please read the following License Agreement. \r\nYou must accept the terms of this "
				L"agreement before using this software.";
			// 
			// buttonLicenseCancel
			// 
			this->buttonLicenseCancel->Location = System::Drawing::Point(534, 318);
			this->buttonLicenseCancel->Name = L"buttonLicenseCancel";
			this->buttonLicenseCancel->Size = System::Drawing::Size(75, 23);
			this->buttonLicenseCancel->TabIndex = 12;
			this->buttonLicenseCancel->Text = L"Cancel";
			this->buttonLicenseCancel->UseVisualStyleBackColor = true;
			this->buttonLicenseCancel->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonLicenseCancel_Click);
			// 
			// radioButtonLicenseReject
			// 
			this->radioButtonLicenseReject->AutoSize = true;
			this->radioButtonLicenseReject->Checked = true;
			this->radioButtonLicenseReject->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->radioButtonLicenseReject->Location = System::Drawing::Point(9, 317);
			this->radioButtonLicenseReject->Name = L"radioButtonLicenseReject";
			this->radioButtonLicenseReject->Size = System::Drawing::Size(202, 20);
			this->radioButtonLicenseReject->TabIndex = 11;
			this->radioButtonLicenseReject->TabStop = true;
			this->radioButtonLicenseReject->Text = L"I do not accept the agreement";
			this->radioButtonLicenseReject->UseVisualStyleBackColor = true;
			this->radioButtonLicenseReject->CheckedChanged += gcnew System::EventHandler(this, &formColAndreasUI::radioButtonLicenseReject_CheckedChanged);
			// 
			// radioButtonLicenseAccept
			// 
			this->radioButtonLicenseAccept->AutoSize = true;
			this->radioButtonLicenseAccept->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->radioButtonLicenseAccept->Location = System::Drawing::Point(9, 288);
			this->radioButtonLicenseAccept->Name = L"radioButtonLicenseAccept";
			this->radioButtonLicenseAccept->Size = System::Drawing::Size(162, 20);
			this->radioButtonLicenseAccept->TabIndex = 10;
			this->radioButtonLicenseAccept->Text = L"I accept the agreement";
			this->radioButtonLicenseAccept->UseVisualStyleBackColor = true;
			this->radioButtonLicenseAccept->CheckedChanged += gcnew System::EventHandler(this, &formColAndreasUI::radioButtonLicenseAccept_CheckedChanged);
			// 
			// buttonLicenseNext
			// 
			this->buttonLicenseNext->Enabled = false;
			this->buttonLicenseNext->Location = System::Drawing::Point(453, 318);
			this->buttonLicenseNext->Name = L"buttonLicenseNext";
			this->buttonLicenseNext->Size = System::Drawing::Size(75, 23);
			this->buttonLicenseNext->TabIndex = 9;
			this->buttonLicenseNext->Text = L"Next";
			this->buttonLicenseNext->UseVisualStyleBackColor = true;
			this->buttonLicenseNext->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonLicenseNext_Click);
			// 
			// richTextBoxLicense
			// 
			this->richTextBoxLicense->BackColor = System::Drawing::SystemColors::HighlightText;
			this->richTextBoxLicense->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBoxLicense->Location = System::Drawing::Point(9, 36);
			this->richTextBoxLicense->Name = L"richTextBoxLicense";
			this->richTextBoxLicense->ReadOnly = true;
			this->richTextBoxLicense->Size = System::Drawing::Size(580, 246);
			this->richTextBoxLicense->TabIndex = 8;
			this->richTextBoxLicense->Text = resources->GetString(L"richTextBoxLicense.Text");
			this->richTextBoxLicense->VScroll += gcnew System::EventHandler(this, &formColAndreasUI::richTextBoxLicense_VScroll);
			// 
			// panelInstallDirectory
			// 
			this->panelInstallDirectory->BackColor = System::Drawing::Color::Gainsboro;
			this->panelInstallDirectory->Controls->Add(this->buttonInstallDirectoryBack);
			this->panelInstallDirectory->Controls->Add(this->buttonInstallDirectoryCancel);
			this->panelInstallDirectory->Controls->Add(this->buttonInstallDirectoryNext);
			this->panelInstallDirectory->Controls->Add(this->labelInstallDirectory);
			this->panelInstallDirectory->Controls->Add(this->buttonInstallDirectoryBrowse);
			this->panelInstallDirectory->Controls->Add(this->textBoxInstallDirectory);
			this->panelInstallDirectory->Location = System::Drawing::Point(7, 95);
			this->panelInstallDirectory->Name = L"panelInstallDirectory";
			this->panelInstallDirectory->Size = System::Drawing::Size(609, 341);
			this->panelInstallDirectory->TabIndex = 14;
			this->panelInstallDirectory->Visible = false;
			// 
			// buttonInstallDirectoryBack
			// 
			this->buttonInstallDirectoryBack->Location = System::Drawing::Point(372, 318);
			this->buttonInstallDirectoryBack->Name = L"buttonInstallDirectoryBack";
			this->buttonInstallDirectoryBack->Size = System::Drawing::Size(75, 23);
			this->buttonInstallDirectoryBack->TabIndex = 17;
			this->buttonInstallDirectoryBack->Text = L"Back";
			this->buttonInstallDirectoryBack->UseVisualStyleBackColor = true;
			this->buttonInstallDirectoryBack->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonInstallDirectoryBack_Click);
			// 
			// buttonInstallDirectoryCancel
			// 
			this->buttonInstallDirectoryCancel->Location = System::Drawing::Point(534, 318);
			this->buttonInstallDirectoryCancel->Name = L"buttonInstallDirectoryCancel";
			this->buttonInstallDirectoryCancel->Size = System::Drawing::Size(75, 23);
			this->buttonInstallDirectoryCancel->TabIndex = 16;
			this->buttonInstallDirectoryCancel->Text = L"Cancel";
			this->buttonInstallDirectoryCancel->UseVisualStyleBackColor = true;
			this->buttonInstallDirectoryCancel->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonInstallDirectoryCancel_Click);
			// 
			// buttonInstallDirectoryNext
			// 
			this->buttonInstallDirectoryNext->Location = System::Drawing::Point(453, 318);
			this->buttonInstallDirectoryNext->Name = L"buttonInstallDirectoryNext";
			this->buttonInstallDirectoryNext->Size = System::Drawing::Size(75, 23);
			this->buttonInstallDirectoryNext->TabIndex = 15;
			this->buttonInstallDirectoryNext->Text = L"Next";
			this->buttonInstallDirectoryNext->UseVisualStyleBackColor = true;
			this->buttonInstallDirectoryNext->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonInstallDirectoryNext_Click);
			// 
			// labelInstallDirectory
			// 
			this->labelInstallDirectory->AutoSize = true;
			this->labelInstallDirectory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelInstallDirectory->Location = System::Drawing::Point(6, 103);
			this->labelInstallDirectory->Name = L"labelInstallDirectory";
			this->labelInstallDirectory->Size = System::Drawing::Size(282, 16);
			this->labelInstallDirectory->TabIndex = 14;
			this->labelInstallDirectory->Text = L"Select your GTA San Andreas install directory.";
			// 
			// buttonInstallDirectoryBrowse
			// 
			this->buttonInstallDirectoryBrowse->BackColor = System::Drawing::SystemColors::Control;
			this->buttonInstallDirectoryBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->buttonInstallDirectoryBrowse->Location = System::Drawing::Point(516, 120);
			this->buttonInstallDirectoryBrowse->Name = L"buttonInstallDirectoryBrowse";
			this->buttonInstallDirectoryBrowse->Size = System::Drawing::Size(76, 23);
			this->buttonInstallDirectoryBrowse->TabIndex = 13;
			this->buttonInstallDirectoryBrowse->Text = L"Browse..";
			this->buttonInstallDirectoryBrowse->UseVisualStyleBackColor = false;
			this->buttonInstallDirectoryBrowse->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonInstallDirectoryBrowse_Click);
			// 
			// textBoxInstallDirectory
			// 
			this->textBoxInstallDirectory->Location = System::Drawing::Point(9, 122);
			this->textBoxInstallDirectory->Name = L"textBoxInstallDirectory";
			this->textBoxInstallDirectory->ReadOnly = true;
			this->textBoxInstallDirectory->Size = System::Drawing::Size(498, 20);
			this->textBoxInstallDirectory->TabIndex = 12;
			// 
			// folderBrowserDialogGTADirectory
			// 
			this->folderBrowserDialogGTADirectory->Description = L"Select your GTA San Andreas root directory";
			this->folderBrowserDialogGTADirectory->RootFolder = System::Environment::SpecialFolder::MyComputer;
			this->folderBrowserDialogGTADirectory->ShowNewFolderButton = false;
			// 
			// panelColAndreasOutputDirectory
			// 
			this->panelColAndreasOutputDirectory->BackColor = System::Drawing::Color::Gainsboro;
			this->panelColAndreasOutputDirectory->Controls->Add(this->buttonpanelColAndreasOutputDirectoryBack);
			this->panelColAndreasOutputDirectory->Controls->Add(this->buttonpanelColAndreasOutputDirectoryCancel);
			this->panelColAndreasOutputDirectory->Controls->Add(this->buttonpanelColAndreasOutputDirectoryNext);
			this->panelColAndreasOutputDirectory->Controls->Add(this->labelpanelColAndreasOutputDirectory);
			this->panelColAndreasOutputDirectory->Controls->Add(this->buttonpanelColAndreasOutputDirectoryBrowse);
			this->panelColAndreasOutputDirectory->Controls->Add(this->textBoxpanelColAndreasOutputDirectory);
			this->panelColAndreasOutputDirectory->Location = System::Drawing::Point(7, 95);
			this->panelColAndreasOutputDirectory->Name = L"panelColAndreasOutputDirectory";
			this->panelColAndreasOutputDirectory->Size = System::Drawing::Size(609, 341);
			this->panelColAndreasOutputDirectory->TabIndex = 15;
			this->panelColAndreasOutputDirectory->Visible = false;
			// 
			// buttonpanelColAndreasOutputDirectoryBack
			// 
			this->buttonpanelColAndreasOutputDirectoryBack->Location = System::Drawing::Point(372, 318);
			this->buttonpanelColAndreasOutputDirectoryBack->Name = L"buttonpanelColAndreasOutputDirectoryBack";
			this->buttonpanelColAndreasOutputDirectoryBack->Size = System::Drawing::Size(75, 23);
			this->buttonpanelColAndreasOutputDirectoryBack->TabIndex = 17;
			this->buttonpanelColAndreasOutputDirectoryBack->Text = L"Back";
			this->buttonpanelColAndreasOutputDirectoryBack->UseVisualStyleBackColor = true;
			this->buttonpanelColAndreasOutputDirectoryBack->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonpanelColAndreasOutputDirectoryBack_Click);
			// 
			// buttonpanelColAndreasOutputDirectoryCancel
			// 
			this->buttonpanelColAndreasOutputDirectoryCancel->Location = System::Drawing::Point(534, 318);
			this->buttonpanelColAndreasOutputDirectoryCancel->Name = L"buttonpanelColAndreasOutputDirectoryCancel";
			this->buttonpanelColAndreasOutputDirectoryCancel->Size = System::Drawing::Size(75, 23);
			this->buttonpanelColAndreasOutputDirectoryCancel->TabIndex = 16;
			this->buttonpanelColAndreasOutputDirectoryCancel->Text = L"Cancel";
			this->buttonpanelColAndreasOutputDirectoryCancel->UseVisualStyleBackColor = true;
			this->buttonpanelColAndreasOutputDirectoryCancel->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonpanelColAndreasOutputDirectoryCancel_Click);
			// 
			// buttonpanelColAndreasOutputDirectoryNext
			// 
			this->buttonpanelColAndreasOutputDirectoryNext->Enabled = false;
			this->buttonpanelColAndreasOutputDirectoryNext->Location = System::Drawing::Point(453, 318);
			this->buttonpanelColAndreasOutputDirectoryNext->Name = L"buttonpanelColAndreasOutputDirectoryNext";
			this->buttonpanelColAndreasOutputDirectoryNext->Size = System::Drawing::Size(75, 23);
			this->buttonpanelColAndreasOutputDirectoryNext->TabIndex = 15;
			this->buttonpanelColAndreasOutputDirectoryNext->Text = L"Next";
			this->buttonpanelColAndreasOutputDirectoryNext->UseVisualStyleBackColor = true;
			this->buttonpanelColAndreasOutputDirectoryNext->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonpanelColAndreasOutputDirectoryNext_Click);
			// 
			// labelpanelColAndreasOutputDirectory
			// 
			this->labelpanelColAndreasOutputDirectory->AutoSize = true;
			this->labelpanelColAndreasOutputDirectory->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelpanelColAndreasOutputDirectory->Location = System::Drawing::Point(6, 103);
			this->labelpanelColAndreasOutputDirectory->Name = L"labelpanelColAndreasOutputDirectory";
			this->labelpanelColAndreasOutputDirectory->Size = System::Drawing::Size(272, 16);
			this->labelpanelColAndreasOutputDirectory->TabIndex = 14;
			this->labelpanelColAndreasOutputDirectory->Text = L"Select a location to save the ColAndreas file.";
			// 
			// buttonpanelColAndreasOutputDirectoryBrowse
			// 
			this->buttonpanelColAndreasOutputDirectoryBrowse->BackColor = System::Drawing::SystemColors::Control;
			this->buttonpanelColAndreasOutputDirectoryBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->buttonpanelColAndreasOutputDirectoryBrowse->Location = System::Drawing::Point(516, 120);
			this->buttonpanelColAndreasOutputDirectoryBrowse->Name = L"buttonpanelColAndreasOutputDirectoryBrowse";
			this->buttonpanelColAndreasOutputDirectoryBrowse->Size = System::Drawing::Size(76, 23);
			this->buttonpanelColAndreasOutputDirectoryBrowse->TabIndex = 13;
			this->buttonpanelColAndreasOutputDirectoryBrowse->Text = L"Browse..";
			this->buttonpanelColAndreasOutputDirectoryBrowse->UseVisualStyleBackColor = false;
			this->buttonpanelColAndreasOutputDirectoryBrowse->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonpanelColAndreasOutputDirectoryBrowse_Click);
			// 
			// textBoxpanelColAndreasOutputDirectory
			// 
			this->textBoxpanelColAndreasOutputDirectory->Location = System::Drawing::Point(9, 122);
			this->textBoxpanelColAndreasOutputDirectory->Name = L"textBoxpanelColAndreasOutputDirectory";
			this->textBoxpanelColAndreasOutputDirectory->ReadOnly = true;
			this->textBoxpanelColAndreasOutputDirectory->Size = System::Drawing::Size(498, 20);
			this->textBoxpanelColAndreasOutputDirectory->TabIndex = 12;
			// 
			// saveFileDialogColAndreas
			// 
			this->saveFileDialogColAndreas->CreatePrompt = true;
			this->saveFileDialogColAndreas->DefaultExt = L"cadb";
			this->saveFileDialogColAndreas->FileName = L"ColAndreas";
			this->saveFileDialogColAndreas->Filter = L"ColAndreas binary file|*.cadb";
			// 
			// panelPreReview
			// 
			this->panelPreReview->BackColor = System::Drawing::Color::Gainsboro;
			this->panelPreReview->Controls->Add(this->label1);
			this->panelPreReview->Controls->Add(this->buttonPreReviewBack);
			this->panelPreReview->Controls->Add(this->buttonPreReviewCancel);
			this->panelPreReview->Controls->Add(this->buttonPreReviewStart);
			this->panelPreReview->Controls->Add(this->checkBoxPreReview_CustomObjects);
			this->panelPreReview->Controls->Add(this->checkBoxPreReview_SAMPObjects);
			this->panelPreReview->Controls->Add(this->richTextBoxPreReview);
			this->panelPreReview->Location = System::Drawing::Point(7, 95);
			this->panelPreReview->Name = L"panelPreReview";
			this->panelPreReview->Size = System::Drawing::Size(609, 341);
			this->panelPreReview->TabIndex = 16;
			this->panelPreReview->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(113, 13);
			this->label1->TabIndex = 21;
			this->label1->Text = L"Review before starting";
			// 
			// buttonPreReviewBack
			// 
			this->buttonPreReviewBack->Location = System::Drawing::Point(372, 318);
			this->buttonPreReviewBack->Name = L"buttonPreReviewBack";
			this->buttonPreReviewBack->Size = System::Drawing::Size(75, 23);
			this->buttonPreReviewBack->TabIndex = 20;
			this->buttonPreReviewBack->Text = L"Back";
			this->buttonPreReviewBack->UseVisualStyleBackColor = true;
			this->buttonPreReviewBack->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonPreReviewBack_Click);
			// 
			// buttonPreReviewCancel
			// 
			this->buttonPreReviewCancel->Location = System::Drawing::Point(534, 318);
			this->buttonPreReviewCancel->Name = L"buttonPreReviewCancel";
			this->buttonPreReviewCancel->Size = System::Drawing::Size(75, 23);
			this->buttonPreReviewCancel->TabIndex = 19;
			this->buttonPreReviewCancel->Text = L"Cancel";
			this->buttonPreReviewCancel->UseVisualStyleBackColor = true;
			this->buttonPreReviewCancel->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonPreReviewCancel_Click);
			// 
			// buttonPreReviewStart
			// 
			this->buttonPreReviewStart->Location = System::Drawing::Point(453, 318);
			this->buttonPreReviewStart->Name = L"buttonPreReviewStart";
			this->buttonPreReviewStart->Size = System::Drawing::Size(75, 23);
			this->buttonPreReviewStart->TabIndex = 18;
			this->buttonPreReviewStart->Text = L"Start";
			this->buttonPreReviewStart->UseVisualStyleBackColor = true;
			this->buttonPreReviewStart->Click += gcnew System::EventHandler(this, &formColAndreasUI::buttonPreReviewStart_Click);
			// 
			// checkBoxPreReview_CustomObjects
			// 
			this->checkBoxPreReview_CustomObjects->AutoSize = true;
			this->checkBoxPreReview_CustomObjects->Location = System::Drawing::Point(9, 286);
			this->checkBoxPreReview_CustomObjects->Name = L"checkBoxPreReview_CustomObjects";
			this->checkBoxPreReview_CustomObjects->Size = System::Drawing::Size(233, 17);
			this->checkBoxPreReview_CustomObjects->TabIndex = 2;
			this->checkBoxPreReview_CustomObjects->Text = L"Include custom objects from CUSTOMS.img";
			this->checkBoxPreReview_CustomObjects->UseVisualStyleBackColor = true;
			this->checkBoxPreReview_CustomObjects->CheckedChanged += gcnew System::EventHandler(this, &formColAndreasUI::checkBoxPreReview_CustomObjects_CheckedChanged);
			// 
			// checkBoxPreReview_SAMPObjects
			// 
			this->checkBoxPreReview_SAMPObjects->AutoSize = true;
			this->checkBoxPreReview_SAMPObjects->Checked = true;
			this->checkBoxPreReview_SAMPObjects->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxPreReview_SAMPObjects->Location = System::Drawing::Point(9, 262);
			this->checkBoxPreReview_SAMPObjects->Name = L"checkBoxPreReview_SAMPObjects";
			this->checkBoxPreReview_SAMPObjects->Size = System::Drawing::Size(134, 17);
			this->checkBoxPreReview_SAMPObjects->TabIndex = 1;
			this->checkBoxPreReview_SAMPObjects->Text = L"Include SA-MP objects";
			this->checkBoxPreReview_SAMPObjects->UseVisualStyleBackColor = true;
			this->checkBoxPreReview_SAMPObjects->CheckedChanged += gcnew System::EventHandler(this, &formColAndreasUI::checkBoxPreReview_SAMPObjects_CheckedChanged);
			// 
			// richTextBoxPreReview
			// 
			this->richTextBoxPreReview->Location = System::Drawing::Point(9, 36);
			this->richTextBoxPreReview->Name = L"richTextBoxPreReview";
			this->richTextBoxPreReview->ReadOnly = true;
			this->richTextBoxPreReview->Size = System::Drawing::Size(583, 220);
			this->richTextBoxPreReview->TabIndex = 0;
			this->richTextBoxPreReview->Text = L"";
			// 
			// panelColAndreasBuilder
			// 
			this->panelColAndreasBuilder->BackColor = System::Drawing::Color::Gainsboro;
			this->panelColAndreasBuilder->Controls->Add(this->progressBarColAndreasBuilder);
			this->panelColAndreasBuilder->Controls->Add(this->labelColAndreasBuilder);
			this->panelColAndreasBuilder->Controls->Add(this->richTextBoxColAndreasBuilder);
			this->panelColAndreasBuilder->Location = System::Drawing::Point(7, 95);
			this->panelColAndreasBuilder->Name = L"panelColAndreasBuilder";
			this->panelColAndreasBuilder->Size = System::Drawing::Size(609, 341);
			this->panelColAndreasBuilder->TabIndex = 17;
			this->panelColAndreasBuilder->Visible = false;
			// 
			// labelColAndreasBuilder
			// 
			this->labelColAndreasBuilder->AutoSize = true;
			this->labelColAndreasBuilder->Location = System::Drawing::Point(15, 17);
			this->labelColAndreasBuilder->Name = L"labelColAndreasBuilder";
			this->labelColAndreasBuilder->Size = System::Drawing::Size(195, 13);
			this->labelColAndreasBuilder->TabIndex = 24;
			this->labelColAndreasBuilder->Text = L"Building ColAndreas database binary file";
			// 
			// richTextBoxColAndreasBuilder
			// 
			this->richTextBoxColAndreasBuilder->Location = System::Drawing::Point(15, 36);
			this->richTextBoxColAndreasBuilder->MaxLength = 0;
			this->richTextBoxColAndreasBuilder->Name = L"richTextBoxColAndreasBuilder";
			this->richTextBoxColAndreasBuilder->ReadOnly = true;
			this->richTextBoxColAndreasBuilder->Size = System::Drawing::Size(563, 204);
			this->richTextBoxColAndreasBuilder->TabIndex = 1;
			this->richTextBoxColAndreasBuilder->Text = L"";
			// 
			// progressBarColAndreasBuilder
			// 
			this->progressBarColAndreasBuilder->BackColor = System::Drawing::Color::Gainsboro;
			this->progressBarColAndreasBuilder->ForeColor = System::Drawing::Color::Maroon;
			this->progressBarColAndreasBuilder->Location = System::Drawing::Point(15, 280);
			this->progressBarColAndreasBuilder->Name = L"progressBarColAndreasBuilder";
			this->progressBarColAndreasBuilder->Size = System::Drawing::Size(577, 23);
			this->progressBarColAndreasBuilder->Step = 1;
			this->progressBarColAndreasBuilder->TabIndex = 0;
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &formColAndreasUI::backgroundWorker_DoWork);
			this->backgroundWorker->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &formColAndreasUI::backgroundWorker_ProgressChanged);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &formColAndreasUI::backgroundWorker_RunWorkerCompleted);
			// 
			// formColAndreasUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(624, 442);
			this->Controls->Add(this->panelHeaderLogo);
			this->Controls->Add(this->panelColAndreasBuilder);
			this->Controls->Add(this->panelPreReview);
			this->Controls->Add(this->panelColAndreasOutputDirectory);
			this->Controls->Add(this->panelInstallDirectory);
			this->Controls->Add(this->panelLicense);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->HelpButton = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(640, 480);
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"formColAndreasUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ColAndreas wizard v1.0.0";
			this->Load += gcnew System::EventHandler(this, &formColAndreasUI::formColAndreasUI_Load);
			this->panelLicense->ResumeLayout(false);
			this->panelLicense->PerformLayout();
			this->panelInstallDirectory->ResumeLayout(false);
			this->panelInstallDirectory->PerformLayout();
			this->panelColAndreasOutputDirectory->ResumeLayout(false);
			this->panelColAndreasOutputDirectory->PerformLayout();
			this->panelPreReview->ResumeLayout(false);
			this->panelPreReview->PerformLayout();
			this->panelColAndreasBuilder->ResumeLayout(false);
			this->panelColAndreasBuilder->PerformLayout();
			this->ResumeLayout(false);

		}


#pragma endregion

		void UpdatePreReviewRichTextBox()
		{
			richTextBoxPreReview->Text = "Install direcrectory: \n"
				+ textBoxInstallDirectory->Text + "\n\n" + "Output directory: \n"
				+ textBoxpanelColAndreasOutputDirectory->Text + "\n\n";

			if (checkBoxPreReview_SAMPObjects->Checked == true)
				richTextBoxPreReview->Text += "Including SA-MP objects\n";
			else
				richTextBoxPreReview->Text += "Excluding SA-MP objects\n";

			if (checkBoxPreReview_CustomObjects->Checked == true)
				richTextBoxPreReview->Text += "Including custom objects from CUSTOM.img\n";
			else
				richTextBoxPreReview->Text += "Excluding custom objects from CUSTOM.img\n";
		}

		private: System::Void buttonLicenseNext_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (radioButtonLicenseAccept->Checked == true && radioButtonLicenseReject->Checked == false)
			{
				SCROLLINFO ScrollInformation;

				ZeroMemory(&ScrollInformation, sizeof(ScrollInformation));
				ScrollInformation.cbSize = sizeof(SCROLLINFO);
				ScrollInformation.fMask = SIF_ALL;

				GetScrollInfo(static_cast<HWND>(richTextBoxLicense->Handle.ToPointer()), SB_VERT, &ScrollInformation);

				if (((int)ScrollInformation.nMax - (UINT)ScrollInformation.nPage) - (int)ScrollInformation.nPos == 0)
				{
					panelLicense->Visible = false;
					panelInstallDirectory->Visible = true;
				}
			}
			else
			{
				MessageBox::Show("You must accept the license agreement to continue.", "", MessageBoxButtons::OK);
			}
		}
private: System::Void richTextBoxLicense_VScroll(System::Object^  sender, System::EventArgs^  e) {

	SCROLLINFO ScrollInformation;

	ZeroMemory(&ScrollInformation, sizeof(ScrollInformation));
	ScrollInformation.cbSize = sizeof(SCROLLINFO);
	ScrollInformation.fMask = SIF_ALL;

	GetScrollInfo(static_cast<HWND>(richTextBoxLicense->Handle.ToPointer()), SB_VERT, &ScrollInformation);

	if (((int)ScrollInformation.nMax - (UINT)ScrollInformation.nPage) - (int)ScrollInformation.nPos == 0)
	{
		buttonLicenseNext->Enabled = true;
		//MessageBox::Show("You can procceed to the next page :)", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	else buttonLicenseNext->Enabled = false;
}
private: System::Void radioButtonLicenseAccept_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (radioButtonLicenseAccept->Checked == true)
	{
		radioButtonLicenseReject->Checked = false;
	}
}
private: System::Void radioButtonLicenseReject_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (radioButtonLicenseReject->Checked == true)
	{
		radioButtonLicenseAccept->Checked = false;
	}
}
private: System::Void buttonInstallDirectoryBack_Click(System::Object^  sender, System::EventArgs^  e) {

	panelLicense->Visible = true;
	panelInstallDirectory->Visible = false;
}
private: System::Void buttonInstallDirectoryCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void buttonLicenseCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void buttonInstallDirectoryBrowse_Click(System::Object^  sender, System::EventArgs^  e) {

	folderBrowserDialogGTADirectory->SelectedPath = textBoxInstallDirectory->Text;

	if (folderBrowserDialogGTADirectory->ShowDialog() == ::DialogResult::OK)
	{
		textBoxInstallDirectory->Text = folderBrowserDialogGTADirectory->SelectedPath;
	}
}
private: System::Void buttonInstallDirectoryNext_Click(System::Object^  sender, System::EventArgs^  e) {

	panelInstallDirectory->Visible = false;
	panelColAndreasOutputDirectory->Visible = true;
}

private: System::Void buttonpanelColAndreasOutputDirectoryCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void buttonpanelColAndreasOutputDirectoryNext_Click(System::Object^  sender, System::EventArgs^  e) {

	//Load the PreReviewPage
	panelColAndreasOutputDirectory->Visible = false;
	panelPreReview->Visible = true;

	UpdatePreReviewRichTextBox();
}
private: System::Void buttonpanelColAndreasOutputDirectoryBack_Click(System::Object^  sender, System::EventArgs^  e) {

	panelColAndreasOutputDirectory->Visible = false;
	panelInstallDirectory->Visible = true;
}
private: System::Void buttonpanelColAndreasOutputDirectoryBrowse_Click(System::Object^  sender, System::EventArgs^  e) {

	saveFileDialogColAndreas->InitialDirectory = textBoxpanelColAndreasOutputDirectory->Text;
	if (saveFileDialogColAndreas->ShowDialog() == ::DialogResult::OK)
	{
		textBoxpanelColAndreasOutputDirectory->Text = saveFileDialogColAndreas->FileName;
		buttonpanelColAndreasOutputDirectoryNext->Enabled = true;
	}
}
private: System::Void formColAndreasUI_Load(System::Object^  sender, System::EventArgs^  e) {
	
	//MessageBox::Show("Loaded");
	/*
	Use the .NET framework to read the registry keys, these functions need recoding in .net

	String ^ GTAInstallDirectory;
	if (GetGTAInstallDirectoryFromRegistry(GTAInstallDirectory))
	{
		GTAInstallDirectory = PrepareGTAPathString(GTAInstallDirectory);
		textBoxInstallDirectory->Text = GTAInstallDirectory;
		folderBrowserDialogGTADirectory->SelectedPath = textBoxInstallDirectory->Text;
	}
	*/
}
private: System::Void buttonPreReviewBack_Click(System::Object^  sender, System::EventArgs^  e) {
	panelPreReview->Visible = false;
	panelColAndreasOutputDirectory->Visible = true;
}
private: System::Void checkBoxPreReview_SAMPObjects_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	UpdatePreReviewRichTextBox();

	if (checkBoxPreReview_SAMPObjects->Checked)
		Use_SAMP_MODELS = true;
	else
		Use_SAMP_MODELS = false;
}
private: System::Void checkBoxPreReview_CustomObjects_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	UpdatePreReviewRichTextBox();

	if (checkBoxPreReview_CustomObjects->Checked)
		Use_CUSTOM_MODELS = true;
	else
		Use_CUSTOM_MODELS = false;

}
private: System::Void buttonPreReviewCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void buttonPreReviewStart_Click(System::Object^  sender, System::EventArgs^  e) {
	panelPreReview->Visible = false;
	panelColAndreasBuilder->Visible = true;
	//This fires up ColAndreasBuilder
	backgroundWorker->RunWorkerAsync(); //Can use an object as a paramater if required.
}

private: System::Void buttonColAndreasBuilderCancel_Click(System::Object^  sender, System::EventArgs^  e) {
	//ColAndreasBuilder Cancel Button
	backgroundWorker->CancelAsync();
}
private: System::Void backgroundWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

	//Need to destroy the thread before closing the application otherwise it will produce errors

	std::string InputDirectory;
	std::string OutputDirectory;

	MarshalString(textBoxInstallDirectory->Text, InputDirectory);
	MarshalString(textBoxpanelColAndreasOutputDirectory->Text, OutputDirectory);

	BuildManager TheBuildManager(InputDirectory, OutputDirectory, backgroundWorker, Use_SAMP_MODELS, Use_CUSTOM_MODELS);

	backgroundWorker->ReportProgress(1, "Processing image file archives\n");  //reporting progress
	TheBuildManager.ExtractImageFiles();
	backgroundWorker->ReportProgress(19, "Image file extraction complete\n\n");  //reporting progress

	TheBuildManager.ExtractCollisionFiles();

	backgroundWorker->ReportProgress(1, "Processing item placement files\n");
	TheBuildManager.ExtractItemPlacementFiles();
	backgroundWorker->ReportProgress(19, "Item placement extraction complete\n\n");  //reporting progress

	backgroundWorker->ReportProgress(1, "Processing item definition files\n");
	TheBuildManager.ExtractItemDefinitionFiles();
	backgroundWorker->ReportProgress(19, "Item definition extraction complete\n\n");

	backgroundWorker->ReportProgress(1, "Preparing database structures, this may take some time.\n");
	TheBuildManager.PrepareDatabaseStructures();
	backgroundWorker->ReportProgress(19, "Database structures succesfully prepared.\n\n");

	backgroundWorker->ReportProgress(1, "Writing the database file.\n");
	TheBuildManager.WriteBinaryFile(OutputDirectory.c_str());//Writes the database file
	backgroundWorker->ReportProgress(19, "Database file Written succesfully.\n\n");

}
private: System::Void backgroundWorker_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {
	//richTextBoxColAndreasBuilder->Text += "Progress Reported as " + e->ProgressPercentage + "\n";
	//richTextBoxColAndreasBuilder->Text += "Progress total is " + progressBarColAndreasBuilder->Value + "\n";
	progressBarColAndreasBuilder->Value += e->ProgressPercentage;  //rising the progressbar's value

	richTextBoxColAndreasBuilder->Text += e->UserState;
	richTextBoxColAndreasBuilder->SelectionStart = richTextBoxColAndreasBuilder->Text->Length;
	richTextBoxColAndreasBuilder->ScrollToCaret();
}
private: System::Void backgroundWorker_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	richTextBoxColAndreasBuilder->Text += "Worker thread completion Reported\n";
	progressBarColAndreasBuilder->Value = 0;   //reseting value

	if (e->Cancelled)    //Messages for the events
	{
		MessageBox::Show("You have cancelled background worker!!!");
	}
	else
	{
		MessageBox::Show("Database file created successfully.");
	}
}



	};
}
