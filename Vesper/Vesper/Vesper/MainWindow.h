#pragma once
#include "Modules/Dashboard.h"

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
            this->Size = Drawing::Size(1350, 900);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            // Load icon
            String^ basePath = AppDomain::CurrentDomain->BaseDirectory;
            String^ icoPath = System::IO::Path::Combine(basePath, "Assets\\vesper.ico");
            this->Icon = gcnew System::Drawing::Icon(icoPath);

            BuildSidebar();
            BuildTopBar();
            BuildContentArea();
            LoadDashboard();
            BuildTrayIcon(icoPath);

            this->Shown += gcnew EventHandler(this, &MainWindow::OnShown);
            this->Resize += gcnew EventHandler(this, &MainWindow::OnResize);
            this->FormClosing += gcnew FormClosingEventHandler(this, &MainWindow::OnFormClosing);
        }

    private:
        // Sidebar controls
        // Sidebar scramble
        Panel^ sidebar;
        Label^ sidebarTitle;
        Panel^ topBar;
        Panel^ contentArea;
        TextBox^ searchBox;
        Button^ newTaskBtn;
        String^ scrambleChars;
        String^ targetWord;
        int     resolvedCount;
        int     scrambleTick;
        int     scrambleLimit;
        int     idleTick;
        bool    scrambling;
        Random^ rng;
        Timer^ scrambleTimer;
        Vesper::Modules::Dashboard^ dashboard;

        // Tray
        NotifyIcon^ trayIcon;
        System::Windows::Forms::ContextMenuStrip^ trayMenu;

        void BuildSidebar() {
            // Main sidebar panel
            sidebar = gcnew Panel();
            sidebar->BackColor = Color::FromArgb(12, 12, 12);
            sidebar->Size = Drawing::Size(240, 900);
            sidebar->Location = Point(0, 0);
            this->Controls->Add(sidebar);

            // Logo + title at top
            //String^ basePath = AppDomain::CurrentDomain->BaseDirectory;
            //String^ logoPath = System::IO::Path::Combine(basePath, "Assets\\vesper.png");

            //sidebarLogo = gcnew PictureBox();
            //sidebarLogo->Image = Image::FromFile(logoPath);
            //sidebarLogo->SizeMode = PictureBoxSizeMode::Zoom;
            //sidebarLogo->Size = Drawing::Size(40, 40);
            //sidebarLogo->Location = Point(14, 14);
            //sidebarLogo->BackColor = Color::Transparent;
            //sidebar->Controls->Add(sidebarLogo);

            sidebarTitle = gcnew Label();
            sidebarTitle->Text = L"VESPER";
            sidebarTitle->ForeColor = Color::White;
            sidebarTitle->Font = gcnew Drawing::Font("Courier New", 14, FontStyle::Bold);
            sidebarTitle->AutoSize = true;
            sidebarTitle->Location = Point(75, 22);
            sidebarTitle->BackColor = Color::Transparent;
            sidebar->Controls->Add(sidebarTitle);

            // Red line under logo area
            Panel^ topDivider = gcnew Panel();
            topDivider->BackColor = Color::FromArgb(180, 0, 0);
            topDivider->Size = Drawing::Size(240, 1);
            topDivider->Location = Point(0, 54);
            sidebar->Controls->Add(topDivider);

            // Nav items
            BuildNavButton(L"  Dashboard", 0, 90);
            BuildNavButton(L"  Reconnaissance", 1, 140);
            BuildNavButton(L"  Network", 2, 190);
            BuildNavButton(L"  Exploitation", 3, 240);
            BuildNavButton(L"  Post Exploitation", 4, 290);
            BuildNavButton(L"  Settings", 5, 340);

            // Bottom divider
            Panel^ botDivider = gcnew Panel();
            botDivider->BackColor = Color::FromArgb(180, 0, 0);
            botDivider->Size = Drawing::Size(240, 1);
            botDivider->Location = Point(0, 820);
            sidebar->Controls->Add(botDivider);

            // User label bottom
            // Sidebar scramble setup
            scrambleChars = L"!@#$%^&*01{}[]<>?/\\|~`ABCDEFabcdef";
            targetWord = L"VESPER";
            resolvedCount = 0;
            scrambleTick = 0;
            scrambleLimit = 8;
            idleTick = 0;
            scrambling = true;
            rng = gcnew Random();

            scrambleTimer = gcnew Timer();
            scrambleTimer->Interval = 50;
            scrambleTimer->Tick += gcnew EventHandler(this, &MainWindow::OnScrambleTick);
            scrambleTimer->Start();
        }

        void BuildContentArea() {
            contentArea = gcnew Panel();
            contentArea->BackColor = Color::FromArgb(8, 8, 8);
            contentArea->Size = Drawing::Size(1110, 845);
            contentArea->Location = Point(240, 55);
            this->Controls->Add(contentArea);
        }

        void BuildNavButton(String^ text, int index, int yPos) {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->ForeColor = Color::FromArgb(180, 180, 180);
            btn->Font = gcnew Drawing::Font("Courier New", 10, FontStyle::Regular);
            btn->Size = Drawing::Size(240, 42);
            btn->Location = Point(0, yPos);
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->BackColor = Color::Transparent;
            btn->TextAlign = ContentAlignment::MiddleLeft;
            btn->Tag = index;
            btn->Cursor = Cursors::Hand;
            sidebar->Controls->Add(btn);
        }

        void BuildTrayIcon(String^ icoPath) {
            trayIcon = gcnew NotifyIcon();
            trayIcon->Icon = gcnew System::Drawing::Icon(icoPath);
            trayIcon->Text = L"Vesper";
            trayIcon->Visible = true;

            trayMenu = gcnew System::Windows::Forms::ContextMenuStrip();
            trayMenu->Items->Add(L"Open", nullptr, gcnew EventHandler(this, &MainWindow::OnTrayOpen));
            trayMenu->Items->Add(L"-");
            trayMenu->Items->Add(L"Exit", nullptr, gcnew EventHandler(this, &MainWindow::OnTrayExit));
            trayIcon->ContextMenuStrip = trayMenu;
            trayIcon->DoubleClick += gcnew EventHandler(this, &MainWindow::OnTrayOpen);
        }

        void BuildTopBar() {
            topBar = gcnew Panel();
            topBar->BackColor = Color::FromArgb(12, 12, 12);
            topBar->Size = Drawing::Size(1110, 55);
            topBar->Location = Point(240, 0);
            this->Controls->Add(topBar);

            //Bottom
            Panel^ topBarBorder = gcnew Panel();
            topBarBorder->BackColor = Color::FromArgb(180, 0, 0);
            topBarBorder->Size = Drawing::Size(1110, 1);
            topBarBorder->Location = Point(0, 54);
            topBar->Controls->Add(topBarBorder);

            //Search
            searchBox = gcnew TextBox();
            searchBox->Text = L"Search...";
            searchBox->ForeColor = Color::FromArgb(120, 120, 120);
            searchBox->BackColor = Color::FromArgb(22, 22, 22);
            searchBox->Font = gcnew Drawing::Font("Courier New", 10, FontStyle::Regular);
            searchBox->Size = Drawing::Size(300, 30);
            searchBox->Location = Point(20, 12);
            searchBox->BorderStyle = BorderStyle::FixedSingle;
            searchBox->Enter += gcnew EventHandler(this, &MainWindow::OnSearchFocus);
            searchBox->Leave += gcnew EventHandler(this, &MainWindow::OnSearchUnFocus);
            topBar->Controls->Add(searchBox);

            //New task
            newTaskBtn = gcnew Button();
            newTaskBtn->Text = L"+ NEW TASK";
            newTaskBtn->ForeColor = Color::White;
            newTaskBtn->BackColor = Color::FromArgb(180, 0, 0);
            newTaskBtn->Font = gcnew Drawing::Font("Courier New", 9, FontStyle::Bold);
            newTaskBtn->Size = Drawing::Size(120, 32);
            newTaskBtn->Location = Point(970, 11);
            newTaskBtn->FlatStyle = FlatStyle::Flat;
            newTaskBtn->FlatAppearance->BorderSize = 0;
            newTaskBtn->Cursor = Cursors::Hand;
            topBar->Controls->Add(newTaskBtn);
        }

        void LoadDashboard() {
            dashboard = gcnew Vesper::Modules::Dashboard(
                contentArea->Width,
                contentArea->Height
            );
            contentArea->Controls->Add(dashboard);
        }

        void OnSearchFocus(Object^ sender, EventArgs^ e) {
            if (searchBox->Text == L"Search...") {
                searchBox->Text = L"";
                searchBox->ForeColor = Color::White;
            }
        }

        void OnSearchUnFocus(Object^ sender, EventArgs^ e) {
            if (searchBox->Text == L"") {
                searchBox->Text = L"Search...";
                searchBox->ForeColor = Color::FromArgb(120, 120, 120);
            }
        }

        void OnShown(Object^ sender, EventArgs^ e) {}

        void OnResize(Object^ sender, EventArgs^ e) {
            if (this->WindowState == FormWindowState::Minimized)
                this->Hide();
        }

        void OnFormClosing(Object^ sender, FormClosingEventArgs^ e) {
            if (e->CloseReason == CloseReason::UserClosing) {
                e->Cancel = true;
                this->Hide();
                trayIcon->ShowBalloonTip(1000, L"Vesper", L"Running in background.", ToolTipIcon::None);
            }
        }

        void OnTrayOpen(Object^ sender, EventArgs^ e) {
            this->Show();
            this->WindowState = FormWindowState::Normal;
            this->BringToFront();
        }

        void OnTrayExit(Object^ sender, EventArgs^ e) {
            trayIcon->Visible = false;
            Application::Exit();
        }

        wchar_t GetRandomChar() {
            return scrambleChars[rng->Next(scrambleChars->Length)];
        }

        String^ BuildScrambleText() {
            System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
            for (int i = 0; i < resolvedCount; i++)
                sb->Append(targetWord[i]);
            for (int i = resolvedCount; i < targetWord->Length; i++)
                sb->Append(GetRandomChar());
            return sb->ToString();
        }

        void OnScrambleTick(Object^ sender, EventArgs^ e) {
            if (scrambling) {
                scrambleTick++;
                sidebarTitle->Text = BuildScrambleText();

                if (scrambleTick >= scrambleLimit) {
                    scrambleTick = 0;
                    resolvedCount++;

                    if (resolvedCount >= targetWord->Length) {
                        sidebarTitle->Text = targetWord;
                        resolvedCount = 0;
                        scrambling = false;
                        idleTick = 0;
                    }
                }
            }
            else {
                // Wait 2 minutes before scrambling again
                idleTick++;
                if (idleTick >= 2400) {
                    scrambling = true;
                    idleTick = 0;
                }
            }
        }

    protected:
        ~MainWindow() {
            if (trayIcon != nullptr) trayIcon->Visible = false;
        }
    };
}