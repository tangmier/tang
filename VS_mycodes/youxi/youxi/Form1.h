#pragma once
#include"stdafx.h"
#include"first.h"
#include<stdlib.h>
#include"second.h"
#include"third.h"
#include"forth.h"
#include"fifth.h"
#include"name.h"
#include"record.h"
#include"ranking.h"

using namespace System::Data::Odbc;
void setStartTime();
//void insert(List*&head,int num);
//struct List;

namespace youxi {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private: 

	private: System::ComponentModel::IContainer^  components;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"楷体", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(64, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(193, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"找规律填数字";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(9, 156);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 30);
			this->button1->TabIndex = 2;
			this->button1->Text = L"开始游戏";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button2->Location = System::Drawing::Point(89, 156);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 30);
			this->button2->TabIndex = 3;
			this->button2->Text = L"历史记录";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button3->Location = System::Drawing::Point(170, 156);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 30);
			this->button3->TabIndex = 4;
			this->button3->Text = L"总体排名";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button4->Location = System::Drawing::Point(252, 156);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 30);
			this->button4->TabIndex = 5;
			this->button4->Text = L"退出游戏";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(337, 211);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"主界面";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                first^f=gcnew first();
			     f->StartPosition=FormStartPosition::WindowsDefaultLocation; //设启动位置
			     f->TopMost=true; //置于顶层
			     f->Opacity=1;//设置透明度，设为了不透明
			     f->Show();//装载显示窗口
			 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 record^f=gcnew record();
			       f->StartPosition=FormStartPosition::WindowsDefaultLocation; //设启动位置
			       f->TopMost=true; //置于顶层
			       f->Opacity=1;//设置透明度，设为了不透明
				   String^con;
				   con="DSN=shuzi;UID=root;PWD=123456;";
				   String^sql="SELECT*FROM record order by score desc";
				   OdbcConnection^OdbcCon=gcnew OdbcConnection(con);
				   OdbcCon->Open();
				   OdbcCommand^Command=OdbcCon->CreateCommand();
				   Command->CommandText=sql;
				   OdbcDataReader^Reader=Command->ExecuteReader();
				   f->textBox1->Text="";
				   while(Reader->Read())
				   {
					   f->textBox1->Text+=Reader["name"];
					   f->textBox1->Text+="\t\t";
					   f->textBox1->Text+=Reader["score"];
					   f->textBox1->Text+="\r\n";
				   }
				   Reader->Close();
				   OdbcCon->Close();
				   f->Show();//装载显示窗口
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			     ranking^f=gcnew ranking();
			     f->StartPosition=FormStartPosition::WindowsDefaultLocation; //设启动位置
			     f->TopMost=true; //置于顶层
			     f->Opacity=1;//设置透明度，设为了不透明
			     f->Show();//装载显示窗口

				  String^con;
				   con="DSN=shuzi;UID=root;PWD=123456;";
				   String^sql="SELECT*FROM record ORDER BY score desc";
				   OdbcConnection^OdbcCon=gcnew OdbcConnection(con);
				  OdbcCon->Open();
				  OdbcCommand^Command=OdbcCon->CreateCommand();
				   Command->CommandText=sql;
				  OdbcDataReader^Reader=Command->ExecuteReader();
				   f->textBox1->Text="";
				 while(Reader->Read())
				   {
					  f->textBox1->Text+=Reader["name"];
					  f->textBox1->Text+="\t\t";
					  f->textBox1->Text+=Reader["score"];
					  f->textBox1->Text+="\r\n";
				   }
				   Reader->Close();
				   OdbcCon->Close();


				  con="DSN=record;UID=root;PWD=123456;";
				  sql="SELECT*FROM record order by time desc ";
				  OdbcConnection^OdbcCon1=gcnew OdbcConnection(con);
				  OdbcCon1->Open();
				  OdbcCommand^Command1=OdbcCon1->CreateCommand();
				  Command1->CommandText=sql;
				  OdbcDataReader^Reader1=Command1->ExecuteReader();
				 while(Reader1->Read())
				   {
					 f->textBox1->Text+=Reader1["name"];
					  f->textBox1->Text+="\t\t";
					  f->textBox1->Text+=Reader1["time"];
					  f->textBox1->Text+="\r\n";
				   }
				   Reader1->Close();
				  OdbcCon1->Close();



		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

