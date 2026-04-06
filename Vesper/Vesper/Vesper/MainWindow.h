#pragma once

namespace Vesper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MainWindow : public Form {
    public:
        MainWindow() {
            this->Text = L"Vesper";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackColor = Color::FromArgb(5, 5, 5);
            this->Size = Drawing::Size(1100, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            scrambleChars = L"!@#$%^&*01{}[]<>?/\\|~`ABCDEFabcdef";
            targetWord = L"Vesper";
            resolvedCount = 0;
            scrambleTick = 0;
            scrambleLimit = 8;
            looping = true;
            rng = gcnew Random();

            // Title label — top center
            titleLabel = gcnew Label();
            titleLabel->Text = targetWord;
            titleLabel->ForeColor = Color::FromArgb(0, 255, 65);
            titleLabel->Font = gcnew Drawing::Font("Courier New", 28, FontStyle::Bold);
            titleLabel->AutoSize = true;
            titleLabel->BackColor = Color::Transparent;
            titleLabel->Top = 14;
            this->Controls->Add(titleLabel);

            // Separator line under title
            separator = gcnew Panel();
            separator->BackColor = Color::FromArgb(0, 255, 65);
            separator->Size = Drawing::Size(1100, 1);
            separator->Top = 65;
            separator->Left = 0;
            this->Controls->Add(separator);

            // Scramble timer — slower tick for performance
            scrambleTimer = gcnew Timer();
            scrambleTimer->Interval = 50;
            scrambleTimer->Tick += gcnew EventHandler(this, &MainWindow::OnScrambleTick);
            scrambleTimer->Start();

            // Center title after form loads
            this->Shown += gcnew EventHandler(this, &MainWindow::OnShown);
        }

    private:
        Label^ titleLabel;
        Panel^ separator;
        Timer^ scrambleTimer;
        String^ targetWord;
        String^ scrambleChars;
        int     resolvedCount;
        int     scrambleTick;
        int     scrambleLimit;
        bool    looping;
        Random^ rng;

        wchar_t GetRandomChar() {
            return scrambleChars[rng->Next(scrambleChars->Length)];
        }

        String^ BuildScrambleText() {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();

            for (int i = 0; i < resolvedCount; i++) {
                sb->Append(targetWord[i]);
            }
            for (int i = resolvedCount; i < targetWord->Length; i++) {
                sb->Append(GetRandomChar());
            }

            return sb->ToString();
        }

        void OnScrambleTick(Object^ sender, EventArgs^ e) {
            titleLabel->Left = (this->ClientSize.Width - titleLabel->Width) / 2;
            scrambleTick++;
            titleLabel->Text = BuildScrambleText();

            if (scrambleTick >= scrambleLimit) {
                scrambleTick = 0;
                resolvedCount++;

                if (resolvedCount >= targetWord->Length) {
                    // Full word resolved — pause then restart loop
                    titleLabel->Text = targetWord;
                    resolvedCount = 0;
                }
            }
        }

        void OnShown(Object^ sender, EventArgs^ e) {
            titleLabel->Left = (this->ClientSize.Width - titleLabel->Width) / 2;
        }

    protected:
        ~MainWindow() {
            if (scrambleTimer != nullptr) scrambleTimer->Stop();
        }
    };
}