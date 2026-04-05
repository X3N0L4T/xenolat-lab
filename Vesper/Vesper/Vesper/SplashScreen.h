#pragma once

namespace Vesper {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	enum Phase { FADE_IN, SCRAMBLE, MOVE_UP, DONE };

	public ref class SplashScreen : public Form {
	public:
		SplashScreen() {
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->BackColor = Color::FromArgb(10, 10, 10);
			this->Opacity = 0.0;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Size = Drawing::Size(700, 400);
			this->TopMost = true;

			scrambleChars = L"!@#$%^&*01{}[]<>?/\\|~'ABCDEFabcdef";
			targetWorld = L"Vesper";
			resolveCount = 0;
			scrambleTick = 0;
			scrambleLimit = 10;
			targetY = 40;
			rng = gcnew Random();

			label = gcnew Label();
			label->Text = BuildScrambleText();
			label->ForeColor = Color::FromArgb(255, 255, 255);
			label->Font = gcnew Drawing::Font("Courier New", 56, FontStyle::Bold);
			label->AutoSize = true;
			label->BackColor = Color::Transparent;
			this->Controls->Add(label);

			timer = gcnew Timer();
			timer->Interval = 16;
			timer->Tick += gcnew EventHandler(this, &SplashScreen::OnTick);
			timer->Start();

			phase = FADE_IN;
		}

	private:
		Label^ label;
		Timer^ timer;
		Phase phase;
		int targetY;
		String^ targetWorld;
		String^ scrambleChars;
		int resolveCount;
		int scrambleTick;
		int scrambleLimit;
		Random^ rng;

		wchar_t GetRandomChar() {
			return scrambleChars[rng->Next(scrambleChars->Length)];
		}

		String^ BuildScrambleText() {
			System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

			//resolve letters
			for (int i = 0; i < resolveCount; i++) {
				sb->Append(targetWorld[i]);
			}

			//remainig letters
			for (int i = resolveCount; i < targetWorld->Length; i++) {
				sb->Append(GetRandomChar());
			}

			return sb->ToString();
		}

		void OnTick(Object^ sender, EventArgs^ e) {
			label->Left = (this->ClientSize.Width - label->Width) / 2;

			if (phase == FADE_IN) {
				this->Opacity += 0.02;
				label->Text = BuildScrambleText();
				label->Top = (this->ClientSize.Height - label->Height) / 2;

				if (this->Opacity >= 1.0) {
					this->Opacity = 1.0;
					phase = SCRAMBLE;
				}
			}
			else if (phase == SCRAMBLE) {
				scrambleTick++;
				label->Text = BuildScrambleText();

				if (scrambleTick >= scrambleLimit) {
					scrambleTick = 0;
					resolveCount++;

					if (resolveCount >= targetWorld->Length) {
						label->Text = targetWorld;
						phase = MOVE_UP;
					}
				}
			}
			else if (phase == MOVE_UP) {
				if (label->Top > targetY) {
					label->Top -= 3;
				}
				else {
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