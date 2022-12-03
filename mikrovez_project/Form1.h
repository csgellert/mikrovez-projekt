#pragma once
#include <math.h>
#define PI 3.14159265358979323846
namespace WindowsForm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^ serialPort1;
	private: System::Windows::Forms::Timer^ timer1;







	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;

	private: System::Windows::Forms::Label^ label1;






	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 300;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 629);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Padding = System::Windows::Forms::Padding(1, 0, 19, 0);
			this->statusStrip1->Size = System::Drawing::Size(659, 26);
			this->statusStrip1->TabIndex = 7;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(151, 20);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 17);
			this->label1->TabIndex = 9;
			this->label1->Text = L"label1";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(659, 655);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->statusStrip1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	bool vezerlo_van = false;
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e)
	{
		array<System::String^>^ portnevek;
		
		int i;
		String^ s;
		Random^ randi = gcnew Random();
		this->Text = "uMogi-2 USB";
		portnevek = Ports::SerialPort::GetPortNames();
		i = 0;
		while (i < portnevek->Length && (!vezerlo_van))
		{
			if (!serialPort1->IsOpen)
			{
				serialPort1->PortName = portnevek[i];
				serialPort1->BaudRate = 9600;
				serialPort1->DataBits = 8;
				serialPort1->StopBits = Ports::StopBits::One;
				serialPort1->Parity = Ports::Parity::None;
				serialPort1->Handshake = Ports::Handshake::None;
				serialPort1->RtsEnable = true;
				serialPort1->DtrEnable = false;
				serialPort1->ReadTimeout = 200; // 0.2 s
				serialPort1->NewLine = "\r\n";
				serialPort1->Open();
				serialPort1->DiscardInBuffer();// usb !
				serialPort1->Write("?");
				try {
					s = serialPort1->ReadLine();
				}
				catch (...) {
					s = "Timeout";
					serialPort1->Close();
				}
				if (s == "uMogi-2") {
					toolStripStatusLabel1->Text = s + " on " +
						serialPort1->PortName;
					vezerlo_van = true;
				}
				else serialPort1->Close();
			}
			i++;
		}
		if (!vezerlo_van) {
			MessageBox::Show("No uMogi-2.", "Error", MessageBoxButtons::OK);
			Application::Exit();
		}
		 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
		 toll = gcnew System::Drawing::Pen(System::Drawing::Color::Black,1);
		 vastag = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2);
		 ecset = gcnew System::Drawing::SolidBrush(System::Drawing::SystemColors::Control);

	}
	Graphics^ fg;//form grafika
	Graphics^ fg2;//form grafika
	Pen^ toll;
	Pen^ vastag;
	System::Drawing::Font^ karakterkeszlet;
	System::Drawing::Brush^ ecset;
	int currant_rotation = 0;
	double ground_pos = 400;
	double fej_heigth = 30;
	double szar_length = 200;
	double alatet_h = 10;
	double furat = 50;
	double center_pos = 250;
	void animate_screw(int angle)
	{
		fg->Clear(System::Drawing::SystemColors::Control); //alap szín
		//fg->DrawImage(image, 0, 0, image->Size.Width, image->Size.Height
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(100,ground_pos , 300, 150));//felső test
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(100, ground_pos+150, 300, 200));//alsó test
		fg->DrawRectangle(toll, System::Drawing::Rectangle(center_pos - (int)(furat / 2), ground_pos+150, furat, -alatet_h-150+szar_length+30));//furat menet
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(center_pos  - 5 -(int)(furat / 2), ground_pos, furat + 10, 150));//furat
		fg->DrawLine(vastag,Point( center_pos - (int)(furat / 2), ground_pos + szar_length + 20),Point( center_pos + (int)(furat / 2), ground_pos + szar_length + 20));//belso menet vég
		Point point1 = Point(center_pos + 10 - (int)(furat / 2), ground_pos+szar_length+30);
		Point point2 = Point(center_pos, ground_pos + szar_length + 35);
		Point point3 = Point(center_pos - 10 + (int)(furat / 2), ground_pos + szar_length + 30);
		array<Point>^ curvePoints = { point1,point2,point3};
		fg->DrawPolygon(vastag, curvePoints);//háromszög
		rotate_screw(angle);
		vertical_movement(angle);
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(center_pos-65, ground_pos - 10, 130, 10));//alátét
		fg->FillRectangle(ecset, System::Drawing::Rectangle(center_pos-64, ground_pos - 10 + 1, 130 -2, 10-2));//alátét fill
	}
	void rotate_screw(int angle)
	{
		double angle_corr = (double)angle * 2*PI / 1023;
		double heigth_corr  = (double)angle * szar_length / 1023;
		double cp_x = center_pos;
		double cp_y = 100;
		double r = 50;
		double delta_phi = 2 * PI / 6;

		//fg->Clear(System::Drawing::SystemColors::Control); //alap szín
		Point point1 = Point(cp_x + r*cos(angle_corr), cp_y+r*sin(angle_corr));
		Point point2 = Point(cp_x + r * cos(angle_corr+delta_phi), cp_y + r * sin(angle_corr+delta_phi));
		Point point3 = Point(cp_x + r * cos(angle_corr+delta_phi*2), cp_y + r * sin(angle_corr+delta_phi*2));
		Point point4 = Point(cp_x + r * cos(angle_corr + delta_phi *3), cp_y + r * sin(angle_corr + delta_phi * 3));
		Point point5 = Point(cp_x + r * cos(angle_corr + delta_phi * 4), cp_y + r * sin(angle_corr + delta_phi * 4));
		Point point6 = Point(cp_x + r * cos(angle_corr + delta_phi * 5), cp_y + r * sin(angle_corr + delta_phi * 5));
		array<Point>^ curvePoints = { point1,point2,point3,point4,point5,point6};
		fg->DrawPolygon(vastag, curvePoints);
		double xc,yc;
		xc = r*sin(angle_corr); yc = r * cos(angle_corr); if (xc > 0 || fabs(yc)>r*cos(PI/6))					   { int tmp = (int)(cp_x + r * cos(angle_corr)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		xc = r*sin(angle_corr + delta_phi*1); yc = r * cos(angle_corr + delta_phi * 1); if (xc > 0 || fabs(yc) > r * cos(PI / 6)) { int tmp = (int)(cp_x + r * cos(angle_corr + delta_phi*1)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		xc = r*sin(angle_corr + delta_phi*2); yc = r * cos(angle_corr + delta_phi * 2); if (xc > 0 || fabs(yc) > r * cos(PI / 6)) { int tmp = (int)(cp_x + r * cos(angle_corr + delta_phi * 2)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		xc = r*sin(angle_corr + delta_phi*3); yc = r * cos(angle_corr + delta_phi * 3); if (xc > 0 || fabs(yc) > r * cos(PI / 6)) { int tmp = (int)(cp_x + r * cos(angle_corr + delta_phi * 3)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		xc = r*sin(angle_corr + delta_phi*4); yc = r * cos(angle_corr + delta_phi * 4); if (xc > 0 || fabs(yc) > r * cos(PI / 6)) { int tmp = (int)(cp_x + r * cos(angle_corr + delta_phi * 4)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		xc = r*sin(angle_corr + delta_phi*5); yc = r * cos(angle_corr + delta_phi * 5); if (xc > 0 || fabs(yc) > r * cos(PI / 6)) { int tmp = (int)(cp_x + r * cos(angle_corr+ delta_phi*5)); fg->DrawLine(vastag, Point(tmp, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr), Point(tmp, ground_pos - (szar_length + alatet_h) + (int)heigth_corr)); }
		double max_pos = -1000;
		double min_pos = 1000;
		int i;
		for (i = 0; i < 6; i++)
		{
			if (cp_x + r * cos(angle_corr + delta_phi * i) > max_pos)
			{
				max_pos = cp_x + r * cos(angle_corr + delta_phi * i);
			}
			if (cp_x + r * cos(angle_corr + delta_phi * i) < min_pos)
			{
				min_pos = cp_x + r * cos(angle_corr + delta_phi * i);
			}
		}
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(min_pos, ground_pos - (szar_length + fej_heigth + alatet_h) + (int)heigth_corr, max_pos - min_pos, fej_heigth));
		
		
	}
	void vertical_movement(int angle)
	{
		double angle_corr = (double)angle *szar_length/ 1023;
		//fg->DrawRectangle(toll, System::Drawing::Rectangle(200,ground_pos-(szar_length+fej_heigth+alatet_h)+(int)angle_corr,100,fej_heigth));//fej
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(center_pos-(int)(furat/2), ground_pos- (szar_length + alatet_h) + (int)angle_corr, furat, szar_length));//szár
		fg->FillRectangle(ecset, System::Drawing::Rectangle(center_pos - (int)(furat / 2)+1, ground_pos - (szar_length + alatet_h)+1 + (int)angle_corr, furat-2, szar_length-2));//erease inside of szár
		fg->DrawRectangle(toll, System::Drawing::Rectangle(center_pos+5 - (int)(furat / 2), ground_pos+10 - (szar_length + alatet_h) + (int)angle_corr, furat-10, szar_length+5-10));//szár menet
		fg->DrawLine(vastag, Point(center_pos - (int)(furat / 2), ground_pos + 10 - (szar_length + alatet_h) + (int)angle_corr),Point( center_pos - (int)(furat / 2) + furat, ground_pos + 10 - (szar_length + alatet_h) + (int)angle_corr));
		Point point1 = Point(center_pos - (int)(furat / 2),ground_pos -  alatet_h + (int)angle_corr);
		Point point2 = Point(center_pos +5- (int)(furat / 2), ground_pos - alatet_h +5+ (int)angle_corr);
		Point point3 = Point(center_pos -5+ (int)(furat / 2), ground_pos - alatet_h +5+ (int)angle_corr);
		Point point4 = Point(center_pos + (int)(furat / 2), ground_pos - alatet_h + (int)angle_corr);
		array<Point>^ curvePoints = { point1,point2,point3,point4};
		fg->DrawPolygon(vastag, curvePoints);//trapez
		double felsopont = (ground_pos + 5 - alatet_h + (int)angle_corr > ground_pos + 150) ? ground_pos + 5 - alatet_h + (int)angle_corr : ground_pos + 150;
		fg->DrawRectangle(vastag, System::Drawing::Rectangle(center_pos + 5 - (int)(furat / 2), felsopont, furat - 10, ground_pos-felsopont+ szar_length -alatet_h+40));//furat belso

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		String^ s;
		int i;
		if (vezerlo_van) {
			if (serialPort1->IsOpen)
			{
				serialPort1->Write("e");
				try {
					s = serialPort1->ReadLine();
				}
				catch (...) {
					timer1->Enabled = 0;
					s = "Timeout";
					serialPort1->Close();
					MessageBox::Show("No uMogi-2.", "Error", MessageBoxButtons::OK);
					Application::Exit();
				}
			}
			else
			{
				timer1->Enabled = 0;
				MessageBox::Show("No uMogi-2.", "Error", MessageBoxButtons::OK);
				Application::Exit();
			}
			label1->Text = s;
			//Console::WriteLine(L"%i",s);
			//s = "42";
			//s = label1->Text;
			if (abs(Convert::ToInt32(s) - currant_rotation) > 2)
			{
				currant_rotation = Convert::ToInt32(s);
				animate_screw(currant_rotation);
			}
		}
	}
	
private: System::Void Form1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	//paint: újra festi a formot
	fg = this->CreateGraphics();// grafika a formra
	//fg->Clear(System::Drawing::SystemColors::Control); //alap szín
}
private: System::Void Form1_Resize(System::Object^ sender, System::EventArgs^ e) {
	if (vezerlo_van) {
		animate_screw(currant_rotation);
	}
}
};
}