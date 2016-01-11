#include<iostream>
#include<string>
#include<cstring>
#include<conio.h>
using namespace std;


struct UserFileDirectory				//用户文件目录
{
	string File_Name;			//文件名
	bool	Read;				//读保护码，true为可读
	bool	Write;				//写保护码，true为可写
	int Address;             // 物理地址
	int Length_File;		   //文件长度
};
struct MainFileDirectory				//主文件目录
{
	string	User_Name;		 //用户名
	int   Password;          //用户密码
	UserFileDirectory*Pointer;		//用户文件目录指针
};
struct OpeingFileDirectory					//打开文件目录
{
	int File_ID;			//打开的文件号
	bool	Read;				//读保护码，true为可读
	bool	Write;				//写保护码，true为可写
	int Pointer;			//读写指针
};


class FILE_SYSTEM				//文件系统类
{
public:
	void Initial();			//初始化
	void Start();				//开始运行文件系统
private:
	int _Number_Users;			//用户的数量
	int _Number_Files;			//每个用户可保存的文件数
	int _MaxNumber_Open_Files;	//每个用户在每次执行中打开的最大文件数
	MainFileDirectory *_MFD;					//主文件目录
	UserFileDirectory *_UFD;					//用户文件目录
	OpeingFileDirectory	 *_OFD;					//当前打开文件目录
};

void main()								//主函数
{
	FILE_SYSTEM FS;
	cout << "****************************************************" << endl;
	cout << "              Welcome to Filesystem " << endl;
	cout << "           dir       打开登录用户目录                    " << endl;
	cout << "           create    创建新文件                             " << endl;
	cout << "           delete    删除文件                                " << endl;
	cout << "           open      打开文件                        " << endl;
	cout << "           logout    退出登录                               " << endl;
	cout << "           close     关闭文件                                " << endl;
	cout << "           read      读文件                                   " << endl;
	cout << "           write     写文件                                   " << endl;
	cout << "           quit      退出                                   " << endl;
	cout << "           系统当前有用户tangxiaoli，密码123456                                   " << endl;
	cout << "***************************************************" << endl;
	FS.Initial();
	FS.Start();
}

void FILE_SYSTEM::Initial()
{
	_Number_Users = 10;      //该系统可容纳十个用户
	_Number_Files = 10;		  //每个用户可拥有十个文件
	_MaxNumber_Open_Files = 5;//每个用户在每次执行中打开的最大文件数为5
	//用户目录的初始化
	_UFD = new UserFileDirectory[_Number_Users*_Number_Files];


	//主目录的初始化
	_MFD = new MainFileDirectory[_Number_Users];
	for (int i = 0; i<_Number_Users; i++)
	{
		_MFD[i].Pointer = &(_UFD[i*_Number_Files]);
	}

	//当前打开文件目录的初始化
	_OFD = new OpeingFileDirectory[_MaxNumber_Open_Files];

	//
	_MFD[0].User_Name = "tangxiaoli";  //该用户拥有ufd的前十个文件
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
		_UFD[i].Length_File = -1;	//表示没有文件
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
	int Number_Open_Files;			//当前用户打开的文件数
	string User_Name;				//当前登录的用户名
	int Password;              //密码
	string Command;					//当前用户输入的命令
	UserFileDirectory *UFD;					//当前登录的用户的文件目录

	do
	{
		do					//用户登录
		{
			cout << "请输入用户名:";
			cin >> User_Name;
			//在主目录中查找该用户
			for (User_ID = 0; User_ID<_Number_Users; User_ID++)
			{
				if (_MFD[User_ID].User_Name == User_Name)
				{
					cout << "请输入密码：";
				loop:					cin >> Password;
					if (_MFD[User_ID].Password == Password)
						break;
					else
					{
						cout << "密码错误，请重新输入:";
						goto loop;
					}
				}
			}
			if (User_ID == _Number_Users)
				cout << "该用户不存在，请重试." << endl;
		} while (User_ID == _Number_Users);
		cout << "登录成功，欢迎您， " << User_Name << " !" << endl;
		UFD = _MFD[User_ID].Pointer;

		//初始化运行文件列表
		for (i = 0; i<_MaxNumber_Open_Files; i++)
		{
			_OFD[i].File_ID = -1;
		}
		Number_Open_Files = 0;

		do
		{
			//接收命令
			cout << "MyDirectory:\\" << User_Name << ">";
			cin >> Command;
			///////////////////////////////////////////////////////

			if (Command == "dir")
			{
				//显示用户文件列表
				cout << endl;
				cout << User_Name << "的文件目录： " << User_Name << endl;
				cout << "\t" << "Read\t" << "Write\t" << "Length\t" << "File name\t" << "Address" << endl;
				for (i = 0; i<_Number_Files; i++)
				{
					if (UFD[i].Length_File != -1)	//该文件项不空
					{
						//打印文件状态，即保护码
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
						//打印文件长度
						cout << "\t";
						cout << UFD[i].Length_File;
						//打印文件名
						cout << "\t";
						cout << UFD[i].File_Name;
						//打印文件物理地址
						cout << "\t";
						cout << "ox" << UFD[i].Address << endl;
					}
				}
				cout << endl;
				////////////////////////////////////////////////////////
			}
			else if (Command == "diropen")
			{
				//显示用户文件列表
				cout << endl;
				cout << User_Name << "当前打开的文件： " << endl;
				cout << "\t" << "Read\t" << "Write\t" << "Open File name" << endl;
				for (i = 0; i<_MaxNumber_Open_Files; i++)
				{
					if (_OFD[i].File_ID != -1)	//该文件项不空
					{
						//打印文件状态，即保护码
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
						//打印文件名
						cout << "\t";
						cout << UFD[_OFD[i].File_ID].File_Name << endl;
					}
				}
				cout << endl;
				////////////////////////////////////////////////////////
			}
			else if (Command == "create")
			{
				//查找是否该用户还有空的文件项，即是否还可以新建文件
				for (i = 0; i<_Number_Files; i++)
				if (UFD[i].Length_File == -1)
					break;
				if (i == _Number_Files)
					cout << "已存在 " << _Number_Files << " 个文件，达到上限 ." << endl;
				else
				{
					cout << "请输入文件信息:" << endl;
					cout << "文件名 : ";
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
					//物理地址
					UFD[i].Address = 10000 + i;
					////////////////////////////////////////////
					cout << "文件： " << UFD[i].File_Name << "已成功创建!" << endl;
				}
			}
			else if (Command == "delete")
			{
				cout << "请输入要删除的文件名 :";
				cin >> temp;
				//查找要删除的文件名
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//没找到这个文件名的文件
					cout << "不存在该文件，请重试 ." << endl;
				else						//成功找到文件
				{
					UFD[i].Length_File = -1;	//删除文件
					cout << "文件：" << UFD[i].File_Name << " 已成功删除!" << endl;
				}
			}
			else if (Command == "open")
			{
				if (Number_Open_Files == _MaxNumber_Open_Files)
					cout << "您已打开 " << Number_Open_Files << " 个文件，达到上限." << endl;
				else
				{
					cout << "请输入要打开的文件名 :";
					cin >> temp;
					//查找要打开的文件名
					for (i = 0; i<_Number_Files; i++)
					if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
						break;
					if (i == _Number_Files)	//没找到这个文件名的文件
						cout << "不存在该文件，请重试 ." << endl;
					else
					{
						Number_Open_Files++;
						for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
						if (_OFD[temp_int].File_ID == -1)
							break;
						_OFD[temp_int].File_ID = i;
						_OFD[temp_int].Pointer = 0;
						cout << "请设置打开模式，可进行2次保护:" << endl;
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

						cout << "文件 " << temp << " 打开成功 ." << endl;
					}
				}
			}
			else if (Command == "logout")
			{
				cout << "再见 " << User_Name << " !" << endl;
				break;
			}
			else if (Command == "close")
			{
				cout << "请输入要关闭的文件名 :";
				cin >> temp;
				//查找要关闭的文件名
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//没找到这个文件名的文件
					cout << "不存在该文件，请重新输入 ." << endl;
				else
				{							//找到了这个文件
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//该文件没有处于打开状态
						cout << "文件" << temp << "未打开 ." << endl;
					else										//该文件处于打开状态
					{
						_OFD[temp_int].File_ID = -1;
						Number_Open_Files--;
						cout << "文件" << temp << " 成功关闭 ." << endl;
					}
				}
			}
			else if (Command == "read")
			{
				cout << "请输入要读的文件名 :";
				cin >> temp;
				//查找要读的文件名
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//没找到这个文件名的文件
					cout << "不存在该文件，请重新输入 ." << endl;
				else
				{							//找到了这个文件
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//该文件没有处于打开状态
						cout << "文件 " << temp << " 未打开 ." << endl;
					else										//该文件处于打开状态
					{
						if (_OFD[temp_int].Read == true)
							cout << "文件" << temp << " 成功读出." << endl;
						else
							cout << "该文件打开模式不允许读文件！" << endl;
					}
				}
			}
			else if (Command == "write")
			{
				cout << "请输入要写入的文件名:";
				cin >> temp;
				//查找要写入的文件名
				for (i = 0; i<_Number_Files; i++)
				if ((UFD[i].Length_File != -1) && (UFD[i].File_Name == temp))
					break;
				if (i == _Number_Files)	//没找到这个文件名的文件
					cout << "不存在该文件，请重新输入  ." << endl;
				else
				{							//找到了这个文件
					for (temp_int = 0; temp_int<_MaxNumber_Open_Files; temp_int++)
					if (_OFD[temp_int].File_ID == i)
						break;
					if (temp_int == _MaxNumber_Open_Files)		//该文件没有处于打开状态
						cout << "文件 " << temp << " 未打开 ." << endl;
					else										//该文件处于打开状态
					{
						if (_OFD[temp_int].Write == true)
							cout << "文件 " << temp << " 成功写入." << endl;
						else
							cout << "该文件打开模式不允许写入." << endl;
					}
				}
			}
			else if (Command == "quit")
			{
				cout << "退出登录中........" << endl;
				cout << "再见 , " << User_Name << " !" << endl;
				cout << "正在关闭系统.........." << endl;
				break;
			}
			else
			{
				cout << "不存在该命令，请重试 ." << endl;
			}
		} while (Command != "logout" && Command != "quit");		//用户循环
	} while (Command != "quit");								//计算机循环
}