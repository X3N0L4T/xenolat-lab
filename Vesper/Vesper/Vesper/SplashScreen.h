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
			this->Controls->Add(label);

			timer = gcnew Timer();
			timer->Interval = 16;
			timer->Tick += gcnew EventHandler(this, &SplashScreen::OnTick);
			timer->Start();

			phase = FADE_IN;
			targetY = 40;
		}

	private:
		Label^ label;
		Timer^ timer;
		Phase phase;
		int targetY;

		void OnTick(Object^ sender, EventArgs^ e) {
			label->Left = (this->ClientSize.Width - label->Width) / 2;

			if (phase == FADE_IN) {
				this->Opacity += 0.02;
				label->Top = (this->ClientSize.Height - label->Height) / 2;

				if (this->Opacity >= 1.0) {
					this->Opacity = 1.0;
					phase = MOVE_UP;
				}
			}
			else if (phase == MOVE_UP) {
				if (label->Top > targetY) {
					label->Top -= 4;
				} else {
					label->Top = targetY;
					phase = DONE;
					timer->Stop();
				}
			}
		}
	protected:
		~SplashScreen() {
			if (timer != nullptr) timer->Stop();
		}
	};
}