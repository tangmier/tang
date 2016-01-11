#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<array>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

int * A;//棋盘，声明为全局变量，可当做黑板
int row = 1;//黑板数据
int N;//皇后的个数
int countc = 0;//计数器，计算总的可行布局


CRITICAL_SECTION mutex;

bool check(int *A, int n);//检查当前位置是否有冲突
void output(int* A, int N);//输出结果
void huisu(int *A, int** conflict, int N);//回溯法
DWORD WINAPI filter(LPVOID lpParameter);//管道过滤器风格， 这里我们把main函数当做一个管道，把线程当做过滤器来模拟风格
void call_and_return(int*A, int N);//调用返回风格，调用check函数检查是否位置冲突，check返回结果
DWORD WINAPI ks(LPVOID lp);//黑板风格 ，知识源,简称ks
void control();//黑板风格，过滤器


void main(){
	int select;
	int select2;
	int fre;//电脑计算频率，用于计时
	long costtime;
	LARGE_INTEGER temp;
	LARGE_INTEGER begin;//计时开始时间
	LARGE_INTEGER end;//结束时间
	QueryPerformanceFrequency(&temp);
	fre = temp.QuadPart;
	cout << "输入1执行n皇后计算,输入2读取测试数据,输入CTRL+Z退出:";
	while (cin >> select)
	{
		switch (select)
		{
		case 1:
		{
				  cout << "请输入N的数值:";
				  cin >> N;
				  A = new int[N + 1];
				  for (int i = 0; i<N + 1; i++)
					  A[i] = 0;
				  countc = 0;
				  cout << "请输入计算方法：" << endl;
				  cout << "1.回溯" << endl;
				  cout << "2.调用返回风格" << endl;
				  cout << "3.管道过滤器风格" << endl;
				  cout << "4.黑板仓库风格" << endl << endl;
				  cout << "输入CTRL+Z退出" << endl;
				  cin >> select2;


				  switch (select2)
				  {

				  case 1:
				  {
							QueryPerformanceCounter(&begin);//开始计时
							int ** conflict;//初始化冲突数组
							conflict = new int*[N + 1];
							for (int a = 0; a<N + 1; a++)
								conflict[a] = new int[N + 1];


							for (int i = 0; i<N + 1; i++)
							for (int k = 0; k < N + 1; k++)
							{
								conflict[i][k] = 0;
							}

							huisu(A, conflict, N);//回溯法函数

							QueryPerformanceCounter(&end);//结束计时
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "总数：" << countc << endl;
							cout << "耗时" << costtime << "us" << endl;
							break;

				  }
				  case 2:
				  {
							QueryPerformanceCounter(&begin);

							call_and_return(A, N);//调用返回函数

							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "总数：" << countc << endl;
							cout << "耗时" << costtime << "us" << endl;
							break;

				  }
				  case 3:
				  {

							QueryPerformanceCounter(&begin);
							HANDLE *threads = new HANDLE[(N + 1) / 2 + 1];
							LPVOID lp;
							int *id = new int[N];
							InitializeCriticalSection(&mutex);//初始化临界区

							for (int i = 1; i <= (N + 1) / 2; i++)
							{
								id[i] = i;
								lp = (LPVOID)(&id[i]);
								threads[i] = CreateThread(NULL, 0, filter, lp, 0, NULL);//过滤器线程
							}
							for (int i = 1; i <= (N + 1) / 2; i++)
							{
								WaitForSingleObject(threads[i], INFINITE);//等待线程结束
							}
							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "总数：" << countc << endl;
							cout << "耗时" << costtime << "us" << endl;
							break;

				  }
				  case 4:
				  {

							InitializeCriticalSection(&mutex);
							QueryPerformanceCounter(&begin);
							row = 1;
							control();//黑板风格，控制器

							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "总数：" << countc << endl;
							cout << "耗时" << costtime << "us" << endl;
							break;

				  }
				  default:
				  {
							 cout << "请正确输入" << endl;
							 break;
				  }


				  }
				  break;
		}
		case 2:
		{
				  ifstream myfile("data.txt");
				  if (!myfile)
				  {
					  cout << "找不到data.txt文件" << endl;
					  break;
				  }
				  int a, b;
				  int i = 0, j = 0;
				  int data[6][2];
				  char buffer[256];
				  char out;
				  while (!myfile.eof())
				  {
					  out = myfile.get();
					  cout << out;
				  }
				  myfile.close();
				  break;
		}
		default:
		{
				   cout << "请正确输入" << endl;
				   break;
		}
		}
		cout << "\n输入1执行n皇后计算,输入2读取测试数据,输入CTRL+Z退出:";
	}
	system("pause");
}

void output(int* A, int N){
	cout << endl;
	for (int i = 1; i<N + 1; i++){
		for (int k = 1; k<N + 1; k++){
			if (A[i] != k)
				cout << "* ";
			else
				cout << "Q ";
		}
		cout << endl;
	}
	cout << endl;
}

void huisu(int *A, int** conflict, int N)
{
	int * B;
	B = new int[N + 1];


	int i = 1; int n = 1; A[1] = 0; int j = 1;//从第一行开始安置皇后
	while (A[1] <= (N + 1) / 2)//求A[1]<=(N+1)/2的布局，通过变化可以得到所有布局
	{

		for (j = n; j <= N&&conflict[i][j]; j++){};

		A[i] = j;
		if (A[i] <= N)//第i行的皇后安置成功，修改矩阵conflict的值
		{

			for (int k = i + 1; k <= N; k++)//修改conflict正下方的值
				conflict[k][j]++;
			for (int k = i + 1, m = j - 1; k <= N&&m>0; k++, m--)//修改conflict左下方的值
				conflict[k][m]++;
			for (int k = i + 1, m = j + 1; k <= N&&m <= N; k++, m++)//修改conflict右下方的值
				conflict[k][m]++;


			i++;
			if (i <= N){//重复安置皇后过程，直到放完位置
				n = 1;
				continue;
			}

			output(A, N);//输出一轮成功布局
			countc++;
			//变换得到另一种布局，并输出

			if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//如果N是奇数那么A[n]==(N+1)/2的一轮输出不用变换
			{
				for (int l = 1; l < N + 1; l++)
				{
					B[l] = N + 1 - A[l];
				}
				output(B, N);
				countc++;
			}

			i = N; n = A[N] + 1;//第n行皇后右移以为，寻找下一个互不攻击的布局


		}
		else//该行皇后已无法放置，回溯至i-1行，并回溯conflict数组
		{
			i--; j = A[i];
			for (int k = i + 1; k <= N; k++)
				conflict[k][j]--;
			for (int k = i + 1, m = j - 1; k <= N&&m>0; k++, m--)
				conflict[k][m]--;
			for (int k = i + 1, m = j + 1; k <= N&&m <= N; k++, m++)
				conflict[k][m]--;

			n = A[i] + 1;
		}
	}

}


void call_and_return(int * A, int N)
{
	int * B;
	B = new int[N + 1];
	int n = 2; A[1] = 1;//初始化，从第一行开始
	while (A[1] <= (N + 1) / 2 && n >= 1)//如果A[1]>n则说明全部情况已遍历
	{
		A[n]++;//右移一位
		if (A[n]>N + 1) A[n] = 1; //如果右移之后超出边界，则重置为1

		while (check(A, n) == 0 && A[n] <= N)//调用冲突检查数组，并根据返回结果放置皇后
			A[n]++;

		if (A[n] <= N)
		{
			if (n == N)//n==N，说明成功放置一轮布局
			{
				countc++;//总数+1
				output(A, N);//输出
				//变换得到另一种成功布局，并输出
				if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//如果N是奇数那么A[n]==(N+1)/2的一轮输出不用变换
				{
					for (int l = 1; l < N + 1; l++)
					{
						B[l] = N + 1 - A[l];
					}
					output(B, N);
					countc++;
				}

			}
			else
			{
				n++;//继续下一行放置
			}

		}
		else
		{
			n--;//回溯
		}

	}
}

DWORD WINAPI filter(LPVOID lpParameter)//过滤器线程
{
	int col = *(int*)(lpParameter);//第1行列数,
	int *a;
	a = new int[N + 1];//初始化新数组，每一个管道线程都有自己的数组，这样就避免了对全局数组进行操作，可并行进行计算
	int * B;
	B = new int[N + 1];//初始化变化数组
	for (int i = 0; i <= N; i++)
	{
		a[i] = 0;
	}

	a[1] = col;
	int n = 2; a[n] = 0;
	while (a[2] <= N&&n >= 2)//从第2行开始
	{

		a[n]++;//右移一位
		if (a[n]>N + 1) a[n] = 1; //如果右移之后超出边界，则重置为1

		while (check(a, n) == 0 && a[n] <= N)//调用冲突检查数组，并根据返回结果放置皇后
			a[n]++;

		if (a[n] <= N)
		{
			if (n == N)//n==N，说明成功放置一轮布局
			{
				EnterCriticalSection(&mutex);//进入临界区,对计数器修改
				countc++;//总数+1
				output(a, N);//输出	
				if (!((N % 2 != 0) && (a[1] == (N + 1) / 2)))//如果N是奇数那么A[n]==(N+1)/2的一轮输出不用变换
				{
					int *B;
					B = new int[N + 1];
					for (int l = 1; l < N + 1; l++)
					{
						B[l] = N + 1 - a[l];
					}
					output(B, N);
					countc++;
				}
				LeaveCriticalSection(&mutex);//离开临界区
			}
			else
			{
				n++;//继续下一行放置
			}

		}
		else
		{

			n--;//回溯
		}

	}
	return 0;
}


bool check(int *A, int n)
{
	for (int i = 1; i < n; i++)
	{
		if (abs(n - i) == abs(A[i] - A[n]) || A[n] == A[i]) return 0;
	}
	return 1;
}



void control()//控制器
{
	while (row >= 1)//根据黑板数据状态来控制知识源的调用
	{
		LPVOID lp = &row;
		HANDLE thread = CreateThread(NULL, 0, ks, NULL, 0, NULL);
		WaitForSingleObject(thread, INFINITE);
	}
}

DWORD WINAPI ks(LPVOID lp)//知识源，用线程来模拟
{
	if ((A[1]>(N + 1) / 2))//优化算法,第一行的列数小于(N+1)/2
	{
		row--;
		return 0;
	}
	else
	{
		A[row]++;//右移一位
		if (A[row]>N + 1) A[row] = 1; //如果右移之后超出边界，则重置为1
		while (check(A, row) == 0 && A[row] <= N)//调用冲突检查数组，并根据返回结果放置皇后
			A[row]++;

		if (A[row] <= N)
		{
			if (row == N)//n==N，说明成功放置一轮布局
			{
				EnterCriticalSection(&mutex);
				countc++;//总数+1
				output(A, N);//输出
				//变换得到另一种成功布局，并输出
				if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//如果N是奇数那么A[n]==(N+1)/2的一轮输出不用变换
				{
					int *B;
					B = new int[N + 1];

					for (int l = 1; l < N + 1; l++)
					{

						B[l] = N + 1 - A[l];
					}
					output(B, N);
					countc++;
				}

				LeaveCriticalSection(&mutex);
			}
			else
			{
				row++;//继续下一行放置
			}

		}
		else
		{
			row--;//行数减1，控制器创建下一个线程放置
		}

		return 0;
	}
}