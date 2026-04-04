#pragma once

namespace Vesper {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	enum Phase { FADE_IN, MOVE_UP, DONE };

	public ref class SplashScreen : public Form {
	public:
		SplashScreen() {
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->BackColor = Color::FromArgb(10, 10, 10);
			this->Opacity = 0.0;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Size = Drawing::Size(600, 400);
			this->TopMost = true;

			label = gcnew Label();
			label->Text = L"Vesper";
			label->ForeColor = Color::White;
			label->Font = gcnew Drawing::Font("Sego UI Light", 52, FontStyle::Regular);
			label->AutoSize = true;
			label->BackColor = Color::Transparent;
		}
	};
}