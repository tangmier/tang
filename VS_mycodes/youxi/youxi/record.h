#pragma once

namespace youxi {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// record ժҪ
	/// </summary>
	public ref class record : public System::Windows::Forms::Form
	{
	public:
		record(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴����ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~record()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label4;
	public: System::Windows::Forms::TextBox^  textBox1;
	private: 


	protected: 

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"����", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(46, 35);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(49, 19);
			this->label1->TabIndex = 10;
			this->label1->Text = L"����";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"����", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label4->Location = System::Drawing::Point(201, 35);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(49, 19);
			this->label4->TabIndex = 14;
			this->label4->Text = L"�ɼ�";
			// 
			// textBox1
			// 
			this->textBox1->AccessibleRole = System::Windows::Forms::AccessibleRole::ScrollBar;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"����", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBox1->Location = System::Drawing::Point(50, 68);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(221, 170);
			this->textBox1->TabIndex = 15;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &record::textBox1_TextChanged);
			// 
			// record
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(309, 269);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label1);
			this->Name = L"record";
			this->Text = L"��ʷ��¼";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}