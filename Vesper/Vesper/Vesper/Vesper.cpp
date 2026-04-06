#include "SplashScreen.h"
#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Vesper::SplashScreen^ splash = gcnew Vesper::SplashScreen();
	splash->ShowDialog();

	Application::Run(gcnew Vesper::MainWindow());
}