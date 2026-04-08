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

			}
		};
}
}