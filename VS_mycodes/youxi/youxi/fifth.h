#pragma once
#include"stdafx.h"
#include<stdlib.h>
#include"name.h"


void score(int tatalTime);
int getScore();

namespace youxi {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// fifth 摘要
	/// </summary>
	public ref class fifth : public System::Windows::Forms::Form
	{
	public:
		fifth(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~fifth()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(12, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(329, 38);
			this->label1->TabIndex = 8;
			this->label1->Text = L"仔细观察下面给出的数据，找出其中\r\n的规律，并在空白处填写相应数据";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label3->Location = System::Drawing::Point(55, 114);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 16);
			this->label3->TabIndex = 13;
			this->label3->Text = L"3，12，27，48，";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(189, 115);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(41, 21);
			this->textBox1->TabIndex = 16;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(130, 175);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 30);
			this->button1->TabIndex = 17;
			this->button1->Text = L"下一关";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &fifth::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &fifth::timer1_Tick);
			// 
			// fifth
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(350, 232);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Name = L"fifth";
			this->Text = L"第五关";
			this->Load += gcnew System::EventHandler(this, &fifth::fifth_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		int i;
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 double a;

				 //把文本转换成浮点型数据
				 a=Double::Parse(textBox1->Text);
				 if(a==75)
				 {
					 timer1->Stop();
			         score(i);
					
				 }
				 else {
					timer1->Stop();
					
				 }

				 name^f=gcnew name();
			     f->StartPosition=FormStartPosition::WindowsDefaultLocation; //设启动位置
			     f->TopMost=true; //置于顶层
			     f->Opacity=1;//设置透明度，设为了不透明
				 int n=getScore();
				 f->label5->Text=n.ToString();
			     f->Show();//装载显示窗口
				this->Visible=false;
			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 i++;
		 }
private: System::Void fifth_Load(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Start();
		 }
};
}
