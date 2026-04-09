#pragma once

namespace Vesper {
	namespace Modules {
		using namespace System;
		using namespace System::Windows::Forms;
		using namespace System::Drawing;

		public ref class Dashboard : public Panel {
		public:
			Dashboard(int width, int height) {
				this->Size = Drawing::Size(width, height);
				this->BackColor = Color::FromArgb(8, 8, 8);
				this->Location = Point(0, 0);

				BuildStatusBar();
				BuildWelcome();
			}

		private:
			void BuildStatusBar() {
				//Status
				Panel^ statusBar = gcnew Panel();
				statusBar->BackColor = Color::FromArgb(10, 10, 10);
				statusBar->Size = Drawing::Size(this->Width, 40);
				statusBar->Location = Point(0, 0);
				this->Controls->Add(statusBar);

				//indicator
				Panel^ dot = gcnew Panel();
				dot->BackColor = Color::FromArgb(0, 200, 80);
				dot->Size = Drawing::Size(8, 8);
				dot->Location = Point(20, 16);
				statusBar->Controls->Add(dot);

				//Text
				Label^ statusText = gcnew Label();
				statusText->Text = L"Modules Ready";
				statusText->ForeColor = Color::FromArgb(0, 200, 80);
				statusText->Font = gcnew Drawing::Font("Courier New", 9, FontStyle::Regular);
				statusText->AutoSize = true;
				statusText->Location = Point(36, 12);
				statusText->BackColor = Color::Transparent;
				statusBar->Controls->Add(statusText);

				//Bar bottom
				Panel^ border = gcnew Panel();
				border->BackColor = Color::FromArgb(30, 30, 30);
				border->Size = Drawing::Size(this->Width, 1);
				border->Location = Point(0, 39);
				statusBar->Controls->Add(border);
			}

			void BuildWelcome() {
				//Greet
				Label^ welcome = gcnew Label();
				welcome->Text = L"DASHBOARD";
				welcome->ForeColor = Color::FromArgb(180, 0, 0);
				welcome->Font = gcnew Drawing::Font("Courier New", 18, FontStyle::Bold);
				welcome->AutoSize = true;
				welcome->Location = Point(30, 60);
				welcome->BackColor = Color::Transparent;
				this->Controls->Add(welcome);

				//Sub
				Label^ sub = gcnew Label();
				sub->Text = L"Select a module.";
				sub->ForeColor = Color::FromArgb(100, 100, 100);
				sub->Font = gcnew Drawing::Font("Courier New", 10, FontStyle::Regular);
				sub->AutoSize = true;
				sub->Location = Point(30, 100);
				sub->BackColor = Color::Transparent;
				this->Controls->Add(sub);

				//Divider
				Panel^ divider = gcnew Panel();
				divider->BackColor = Color::FromArgb(30, 30, 30);
				divider->Size = Drawing::Size(this->Width - 60, 1);
				divider->Location = Point(30, 130);
				this->Controls->Add(divider);
			}
		};
}
}