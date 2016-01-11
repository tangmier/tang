#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
using namespace std;


struct UserFileDirectory				//�û��ļ�Ŀ¼
{
	string File_Name;			//�ļ���
	bool	Read;				//�������룬trueΪ�ɶ�
	bool	Write;				//д�����룬trueΪ��д
	int Address;             // �����ַ
	int Length_File;		   //�ļ�����
};
struct MainFileDirectory				//���ļ�Ŀ¼
{
	string	User_Name;		 //�û���
	int   Password;          //�û�����
	UserFileDirectory*Pointer;		//�û��ļ�Ŀ¼ָ��
};
struct OpeingFileDirectory					//���ļ�Ŀ¼
{
	int File_ID;			//�򿪵��ļ���
	bool	Read;				//�������룬trueΪ�ɶ�
	bool	Write;				//д�����룬trueΪ��д
	int Pointer;			//��дָ��
};


class FILE_SYSTEM				//�ļ�ϵͳ��
{
public:
	void Initial();			//��ʼ��
	void Start();				//��ʼ�����ļ�ϵͳ
private:
	int _Number_Users;			//�û�������
	int _Number_Files;			//ÿ���û��ɱ�����ļ���
	int _MaxNumber_Open_Files;	//ÿ���û���ÿ��ִ���д򿪵�����ļ���
	MainFileDirectory *_MFD;					//���ļ�Ŀ¼
	UserFileDirectory *_UFD;					//�û��ļ�Ŀ¼
	OpeingFileDirectory	 *_OFD;					//��ǰ���ļ�Ŀ¼
};

void main()								//������
{
	FILE_SYSTEM FS;
	cout << "****************************************************" << endl;
	cout << "              Welcome to Filesystem " << endl;
	cout << "           dir       �򿪵�¼�û�Ŀ¼                    " << endl;
	cout << "           create    �������ļ�                             " << endl;
	cout << "           delete    ɾ���ļ�                                " << endl;
	cout << "           open      ���ļ�                        " << endl;
	cout << "           logout    �˳���¼                               " << endl;
	cout << "           close     �ر��ļ�                                " << endl;
	cout << "           read      ���ļ�                                   " << endl;
	cout << "           write     д�ļ�                                   " << endl;
	cout << "           quit      �˳�                                   " << endl;
	cout << "           ϵͳ��ǰ���û�tangxiaoli������123456                                   " << endl;
	cout << "***************************************************" << endl;
	FS.Initial();
	FS.Start();
}

void FILE_SYSTEM::Initial()
{
	_Number_Users = 10;      //��ϵͳ������ʮ���û�
	_Number_Files = 10;		  //ÿ���û���ӵ��ʮ���ļ�
	_MaxNumber_Open_Files = 5;//ÿ���û���ÿ��ִ���д򿪵�����ļ���Ϊ5
	//�û�Ŀ¼�ĳ�ʼ��
	_UFD = new UserFileDirectory[_Number_Users*_Number_Files];


	//��Ŀ¼�ĳ�ʼ��
	_MFD = new MainFileDirectory[_Number_Users];
	for (int i = 0; i<_Number_Users; i++)
	{
		_MFD[i].Pointer = &(_UFD[i*_Number_Files]);
	}

	//��ǰ���ļ�Ŀ¼�ĳ�ʼ��
	_OFD = new OpeingFileDirectory[_MaxNumber_Open_Files];

	//
	_MFD[0].User_Name = "tangxiaoli";  //���û�ӵ��ufd��ǰʮ���ļ�
	_MFD[0].Password = 123456;
	_UFD[0].File_Name = "tang.txt";
	_UFD[0].Length_File = 50;
	_UFD[0].Read = true;
	_UFD[0].Write = true;
	_UFD[0].Address = 10000;
	_UFD[1].File_Name = "xiaoli.bat";
	_UFD[1].Length_File = 20;
	_UFD[1].Read = true;
	_UFD[1].Write = false;
	_UFD[1].Address = 10001;
	for (int i = 2; i<_Number_Files; i++)
	{
		_UFD[i].File_Name = "";
		_UFD[i].Length_File = -1;	//��ʾû���ļ�
		_UFD[i].Read = false;
		_UFD[i].Write = false;
		_UFD[i].Address = 10000 + i;
	}

}

void FILE_SYSTEM::Start()
{
	int User_ID;
	int i, temp_int;
	string temp;
	char   choice;
	int Number_Open_Files;			//��ǰ�û��򿪵��ļ���
	string User_Name;				//��ǰ��¼���û���
	int Password;              //����
	string Command;					//��ǰ�û����������
	UserFileDirectory *UFD;					//��ǰ��¼���û����ļ�Ŀ¼

	do
	{
		do					//�û���¼
		{
			cout << "�������û���:";
			cin >> User_Name;
			//����Ŀ¼�в��Ҹ��û�
			for (User_ID = 0; User_ID<_Number_Users; User_ID++)
			{
				if (_MFD[User_ID].User_Name == User_Name)
				{
					cout << "���������룺";
				loop:					cin >> Password;
					if (_MFD[User_ID].Password == Password)
						break;
					else
					{
						cout << "�����������������:";
						goto loop;
					}
				}
			}
			if (User_ID == _Number_Users)
				cout << "���û������ڣ�������." << endl;
		} while (User_ID == _Number_Users);
		cout << "��¼�ɹ�����ӭ���� " << User_Name << " !" << endl;
		UFD = _MFD[User_ID].Pointer;

		//��ʼ�������ļ��б�
		for (i = 0; i<_MaxNumber_Open_Files; i++)
		{
			_OFD[i].File_ID = -1;
		}
		Number_Open_Files = 0;

		do
		{
			//��������
			cout << "MyDirectory:\\" << User_Name << ">";
			cin >> Command;
			///////////////////////////////////////////////////////

			if (Command == "dir")
			{
				//��ʾ�û��ļ��б�
				cout << endl;
				cout << User_Name << "���ļ�Ŀ¼�� " << User_Name << endl;
				cout << "\t" << "Read\t" << "Write\t" << "Length\t" << "File name\t" << "Address" << endl;
				for (i = 0; i<_Number_Files; i++)
				{
					if (UFD[i].Length_File != -1)	//���ļ����
					{
						//��ӡ�ļ�״̬����������
						cout << "\t";
						if (UFD[i].Read == true)
							cout << "Y";
						else
							cout << "N";
						cout << "\t";
						if (UFD[i].Write == true)
							cout << "Y";
						else
							cout << "N";
						//��ӡ�ļ�����
						cout << "\t";
						cout << UFD[i].Length_File;
						//��ӡ�ļ���
						cout << "\t";
						cout << UFD[i].File_Name;
						//��ӡ�ļ������ַ
						cout << "\t";
						cout << "ox" << UFD[i].Address << endl;
					}
				}
				cout << endl;
				////////////////////////////////////////////////////////
			}
			else if (Command == "diropen")
			{
				//��ʾ�û��ļ��б�
				cout << endl;
				cout << User_Name << "��ǰ�򿪵��ļ��� " << endl;
				cout << "\t" << "Read\t" << "Write\t" << "Open File name" << endl;
				for (i = 0; i<_MaxNumber_Open_Files; i++)
				{
					if (_OFD[i].File_ID != -1)	//���ļ����
					{
						//��ӡ�ļ�״̬����������
						cout << "\t";
						if (_OFD[i].Read == true)
							cout << "Y";
						else
							cout << "N";
						cout << "\t";
						if (_OFD[i].Write == true)
							cout << "Y";
						else
							cout << "N";
						//��ӡ�ļ���
						cout << "\t";
						cout << UFD[_OFD[i].File_ID].File_Name << endl;
					}
				}
				cout << endl;
				////////////////////////////////////////////////////////
			}
			else if (Command == "create")
			{
				//�����Ƿ���û����пյ��ļ�����Ƿ񻹿����½��ļ�
				for (i = 0; i<_Number_Files; i++)
				if (UFD[i].Length_File == -1)
					break;
				if (i == _Number_Files)
					cout << "�Ѵ��� " << _Number_Files << " ���ļ����ﵽ���� ." << endl;
				else
				{
					cout << "�������ļ���Ϣ:" << endl;
					cout << "�ļ��� : ";
					cin >> temp;
					UFD[i].File_Name = temp;
					///////////////////////////////////////////
					//read
					cout << "Read (y/n):";
					do
					{
						cin >> choice;
					} while (choice != 'y' && choice != 'n');
					if (choice == 'y')
						UFD[i].Read = true;
					else
						UFD[i].Read = false;
					////////////////////////////////////////////
					///////////////////////////////////////////
					//write
					cout << "Write (y/n):";
					do
					{
						cin >> choice;
					} while (choice != 'y' && choice != 'n');
					if (choice == 'y')
						UFD[i].Write = true;
					else
						UFD[i].Write = false;
					////////////////////////////////////////////
					///////////////////////////////////////////
					//length
					cout << "Length :";
					cin >> temp_int;
					if (temp_int > 0)
						UFD[i].Length_File = temp_int;
					//�����ַ
					UFD[i].Address = 10000 + i;
					////////////////////////////////////////////
					cout << "�ļ��� " << UFD[i].File_Name << "�ѳɹ�����!" << endl;
				}
			}
			else if (Command == "delete")
			{
				cout << "������Ҫɾ�����ļ��� :";
				cin >> temp;
				//����Ҫɾ�����ļ���
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//û�ҵ�����ļ������ļ�
					cout << "�����ڸ��ļ��������� ." << endl;
				else						//�ɹ��ҵ��ļ�
				{
					UFD[i].Length_File = -1;	//ɾ���ļ�
					cout << "�ļ���" << UFD[i].File_Name << " �ѳɹ�ɾ��!" << endl;
				}
			}
			else if (Command == "open")
			{
				if (Number_Open_Files == _MaxNumber_Open_Files)
					cout << "���Ѵ� " << Number_Open_Files << " ���ļ����ﵽ����." << endl;
				else
				{
					cout << "������Ҫ�򿪵��ļ��� :";
					cin >> temp;
					//����Ҫ�򿪵��ļ���
					for (i = 0; i<_Number_Files; i++)
					if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
						break;
					if (i == _Number_Files)	//û�ҵ�����ļ������ļ�
						cout << "�����ڸ��ļ��������� ." << endl;
					else
					{
						Number_Open_Files++;
						for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
						if (_OFD[temp_int].File_ID == -1)
							break;
						_OFD[temp_int].File_ID = i;
						_OFD[temp_int].Pointer = 0;
						cout << "�����ô�ģʽ���ɽ���2�α���:" << endl;
						///////////////////////////////////////////
						//read
						if (UFD[i].Read == true)
						{
							cout << "Read (y/n):";
							do
							{
								cin >> choice;
							} while (choice != 'y' && choice != 'n');
							if (choice == 'y')
								_OFD[temp_int].Read = true;
							else
								_OFD[temp_int].Read = false;
						}
						else
							_OFD[temp_int].Read = false;
						////////////////////////////////////////////
						//write
						if (UFD[i].Write == true)
						{
							cout << "Write (y/n):";
							do
							{
								cin >> choice;
							} while (choice != 'y' && choice != 'n');
							if (choice == 'y')
								_OFD[temp_int].Write = true;
							else
								_OFD[temp_int].Write = false;
						}
						else
							_OFD[temp_int].Write = false;
						////////////////////////////////////////////

						cout << "�ļ� " << temp << " �򿪳ɹ� ." << endl;
					}
				}
			}
			else if (Command == "logout")
			{
				cout << "�ټ� " << User_Name << " !" << endl;
				break;
			}
			else if (Command == "close")
			{
				cout << "������Ҫ�رյ��ļ��� :";
				cin >> temp;
				//����Ҫ�رյ��ļ���
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//û�ҵ�����ļ������ļ�
					cout << "�����ڸ��ļ������������� ." << endl;
				else
				{							//�ҵ�������ļ�
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//���ļ�û�д��ڴ�״̬
						cout << "�ļ�" << temp << "δ�� ." << endl;
					else										//���ļ����ڴ�״̬
					{
						_OFD[temp_int].File_ID = -1;
						Number_Open_Files--;
						cout << "�ļ�" << temp << " �ɹ��ر� ." << endl;
					}
				}
			}
			else if (Command == "read")
			{
				cout << "������Ҫ�����ļ��� :";
				cin >> temp;
				//����Ҫ�����ļ���
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//û�ҵ�����ļ������ļ�
					cout << "�����ڸ��ļ������������� ." << endl;
				else
				{							//�ҵ�������ļ�
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//���ļ�û�д��ڴ�״̬
						cout << "�ļ� " << temp << " δ�� ." << endl;
					else										//���ļ����ڴ�״̬
					{
						if (_OFD[temp_int].Read == true)
							cout << "�ļ�" << temp << " �ɹ�����." << endl;
						else
							cout << "���ļ���ģʽ��������ļ���" << endl;
					}
				}
			}
			else if (Command == "write")
			{
				cout << "������Ҫд����ļ���:";
				cin >> temp;
				//����Ҫд����ļ���
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//û�ҵ�����ļ������ļ�
					cout << "�����ڸ��ļ�������������  ." << endl;
				else
				{							//�ҵ�������ļ�
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//���ļ�û�д��ڴ�״̬
						cout << "�ļ� " << temp << " δ�� ." << endl;
					else										//���ļ����ڴ�״̬
					{
						if (_OFD[temp_int].Write == true)
							cout << "�ļ� " << temp << " �ɹ�д��." << endl;
						else
							cout << "���ļ���ģʽ������д��." << endl;
					}
				}
			}
			else if (Command == "quit")
			{
				cout << "�˳���¼��........" << endl;
				cout << "�ټ� , " << User_Name << " !" << endl;
				cout << "���ڹر�ϵͳ.........." << endl;
				break;
			}
			else
			{
				cout << "�����ڸ���������� ." << endl;
			}
		} while (Command != "logout" && Command != "quit");		//�û�ѭ��
	} while (Command != "quit");								//�����ѭ��
}