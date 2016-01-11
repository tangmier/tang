#pragma once
#include"stdafx.h"
#include<stdlib.h>
#include"record.h"
using namespace System::Data::Odbc;

namespace youxi {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	/// <summary>
	/// name 摘要
	/// </summary>
	
	
	

	public ref class name : public System::Windows::Forms::Form
	{
	public:
		name(void)
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
		~name()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;


	private: 

	private: System::Windows::Forms::Label^  label4;
	public: System::Windows::Forms::Label^  label5;
	private: 

	private: System::Windows::Forms::Button^  button1;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(30, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(49, 19);
			this->label1->TabIndex = 9;
			this->label1->Text = L"姓名";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(141, 56);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(159, 21);
			this->textBox1->TabIndex = 10;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(30, 109);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 19);
			this->label4->TabIndex = 13;
			this->label4->Text = L"成绩";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"楷体", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label5->Location = System::Drawing::Point(137, 109);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(39, 19);
			this->label5->TabIndex = 14;
			this->label5->Text = L"‘s";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"楷体", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(127, 160);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 30);
			this->button1->TabIndex = 18;
			this->button1->Text = L"提交";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &name::button1_Click);
			// 
			// name
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(343, 212);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"name";
			this->Text = L"姓名";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		ref class SharedData
	{
	public:
		static DataSet^recordDataSet;
	};

#pragma endregion
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

					OdbcConnection^Conn=gcnew OdbcConnection("DSN=shuzi;UID=root;PWD=123456;");
				   OdbcDataAdapter^Adapter;
				   Adapter=gcnew OdbcDataAdapter("SELECT * FROM record",Conn);
				   SharedData::recordDataSet=gcnew DataSet();
				   Adapter->Fill(SharedData::recordDataSet,"record");
				   DataTable^recordTable=SharedData::recordDataSet->Tables["record"];
				   DataRow^NewRow;
				   NewRow=recordTable->NewRow();
				   NewRow["name"]=textBox1->Text;
				   NewRow["score"]=label5->Text;
				   recordTable->Rows->Add(NewRow);
				   DataSet^UpdataDS;
				   UpdataDS=SharedData::recordDataSet->GetChanges();
				   if(UpdataDS)
				   {
					   OdbcCommandBuilder^bu=gcnew OdbcCommandBuilder(Adapter);
					   Adapter->Update(UpdataDS,"record");
					   SharedData::recordDataSet->AcceptChanges();

				   }
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
				   this->Visible=false;
			 }
};
}
