#pragma once
//#include "MainWindow.h"

namespace Vesper {
	
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	enum Phase { FADE_IN, HOLD, FADE_OUT, DONE };

	public ref class SplashScreen : public Form {
	public:
		SplashScreen() {
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->BackColor = Color::FromArgb(5, 5, 5);
			this-> Opacity = 0.0;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Size = Drawing::Size(800, 533);
			this->TopMost = true;

			//Load
			String^ basePath = AppDomain::CurrentDomain->BaseDirectory;
			String^ logoPath = System::IO::Path::Combine(basePath, "Assets\\vesper.png");

			logoBox = gcnew PictureBox();
			logoBox->Image = Image::FromFile(logoPath);
			logoBox->SizeMode = PictureBoxSizeMode::Zoom;
			logoBox->Size = Drawing::Size(800, 533);
			logoBox->BackColor = Color::Transparent;
			logoBox->Left = 0;
			logoBox->Top = 0;
			this->Controls->Add(logoBox);

			holdTicks = 0;
			phase = FADE_IN;

			timer = gcnew Timer();
			timer->Interval = 16;
			timer->Tick += gcnew EventHandler(this, &SplashScreen::OnTick);
			timer->Start();
		}

	private:
		PictureBox^ logoBox;
		Timer^ timer;
		Phase phase;
		int holdTicks;

		void OnTick(Object^ sender, EventArgs^ e) {
			if (phase == FADE_IN) {
				this->Opacity += 0.02;
				if (this->Opacity >= 1.0) {
					this->Opacity = 1.0;
					phase = HOLD;
				}
			}
			else if (phase == HOLD) {
				holdTicks++;
				//hold 1sec
				if (holdTicks >= 60) {
					phase = FADE_OUT;
				}
			}
			else if (phase == FADE_OUT) {
				this->Opacity -= 0.02;
				if (this->Opacity <= 0.0) {
					this->Opacity = 0.0;
					phase = DONE;
					timer->Stop();
					LaunchMainWindow();
				}
			}
		}

		void LaunchMainWindow() {
			//inWindow^ main = gcnew MainWindow();
			//in->Show();
			this->Close();
		}
	protected:
		~SplashScreen() {
			if (timer != nullptr) timer->Stop();
		}
	};
}