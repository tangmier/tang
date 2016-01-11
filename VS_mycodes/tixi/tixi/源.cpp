#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<array>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

int * A;//���̣�����Ϊȫ�ֱ������ɵ����ڰ�
int row = 1;//�ڰ�����
int N;//�ʺ�ĸ���
int countc = 0;//�������������ܵĿ��в���


CRITICAL_SECTION mutex;

bool check(int *A, int n);//��鵱ǰλ���Ƿ��г�ͻ
void output(int* A, int N);//������
void huisu(int *A, int** conflict, int N);//���ݷ�
DWORD WINAPI filter(LPVOID lpParameter);//�ܵ���������� �������ǰ�main��������һ���ܵ������̵߳�����������ģ����
void call_and_return(int*A, int N);//���÷��ط�񣬵���check��������Ƿ�λ�ó�ͻ��check���ؽ��
DWORD WINAPI ks(LPVOID lp);//�ڰ��� ��֪ʶԴ,���ks
void control();//�ڰ��񣬹�����


void main(){
	int select;
	int select2;
	int fre;//���Լ���Ƶ�ʣ����ڼ�ʱ
	long costtime;
	LARGE_INTEGER temp;
	LARGE_INTEGER begin;//��ʱ��ʼʱ��
	LARGE_INTEGER end;//����ʱ��
	QueryPerformanceFrequency(&temp);
	fre = temp.QuadPart;
	cout << "����1ִ��n�ʺ����,����2��ȡ��������,����CTRL+Z�˳�:";
	while (cin >> select)
	{
		switch (select)
		{
		case 1:
		{
				  cout << "������N����ֵ:";
				  cin >> N;
				  A = new int[N + 1];
				  for (int i = 0; i<N + 1; i++)
					  A[i] = 0;
				  countc = 0;
				  cout << "��������㷽����" << endl;
				  cout << "1.����" << endl;
				  cout << "2.���÷��ط��" << endl;
				  cout << "3.�ܵ����������" << endl;
				  cout << "4.�ڰ�ֿ���" << endl << endl;
				  cout << "����CTRL+Z�˳�" << endl;
				  cin >> select2;


				  switch (select2)
				  {

				  case 1:
				  {
							QueryPerformanceCounter(&begin);//��ʼ��ʱ
							int ** conflict;//��ʼ����ͻ����
							conflict = new int*[N + 1];
							for (int a = 0; a<N + 1; a++)
								conflict[a] = new int[N + 1];


							for (int i = 0; i<N + 1; i++)
							for (int k = 0; k < N + 1; k++)
							{
								conflict[i][k] = 0;
							}

							huisu(A, conflict, N);//���ݷ�����

							QueryPerformanceCounter(&end);//������ʱ
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "������" << countc << endl;
							cout << "��ʱ" << costtime << "us" << endl;
							break;

				  }
				  case 2:
				  {
							QueryPerformanceCounter(&begin);

							call_and_return(A, N);//���÷��غ���

							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "������" << countc << endl;
							cout << "��ʱ" << costtime << "us" << endl;
							break;

				  }
				  case 3:
				  {

							QueryPerformanceCounter(&begin);
							HANDLE *threads = new HANDLE[(N + 1) / 2 + 1];
							LPVOID lp;
							int *id = new int[N];
							InitializeCriticalSection(&mutex);//��ʼ���ٽ���

							for (int i = 1; i <= (N + 1) / 2; i++)
							{
								id[i] = i;
								lp = (LPVOID)(&id[i]);
								threads[i] = CreateThread(NULL, 0, filter, lp, 0, NULL);//�������߳�
							}
							for (int i = 1; i <= (N + 1) / 2; i++)
							{
								WaitForSingleObject(threads[i], INFINITE);//�ȴ��߳̽���
							}
							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "������" << countc << endl;
							cout << "��ʱ" << costtime << "us" << endl;
							break;

				  }
				  case 4:
				  {

							InitializeCriticalSection(&mutex);
							QueryPerformanceCounter(&begin);
							row = 1;
							control();//�ڰ��񣬿�����

							QueryPerformanceCounter(&end);
							costtime = (long)((end.QuadPart - begin.QuadPart) * 1000000 / fre);
							cout << "������" << countc << endl;
							cout << "��ʱ" << costtime << "us" << endl;
							break;

				  }
				  default:
				  {
							 cout << "����ȷ����" << endl;
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
					  cout << "�Ҳ���data.txt�ļ�" << endl;
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
				   cout << "����ȷ����" << endl;
				   break;
		}
		}
		cout << "\n����1ִ��n�ʺ����,����2��ȡ��������,����CTRL+Z�˳�:";
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


	int i = 1; int n = 1; A[1] = 0; int j = 1;//�ӵ�һ�п�ʼ���ûʺ�
	while (A[1] <= (N + 1) / 2)//��A[1]<=(N+1)/2�Ĳ��֣�ͨ���仯���Եõ����в���
	{

		for (j = n; j <= N&&conflict[i][j]; j++){};

		A[i] = j;
		if (A[i] <= N)//��i�еĻʺ��óɹ����޸ľ���conflict��ֵ
		{

			for (int k = i + 1; k <= N; k++)//�޸�conflict���·���ֵ
				conflict[k][j]++;
			for (int k = i + 1, m = j - 1; k <= N&&m>0; k++, m--)//�޸�conflict���·���ֵ
				conflict[k][m]++;
			for (int k = i + 1, m = j + 1; k <= N&&m <= N; k++, m++)//�޸�conflict���·���ֵ
				conflict[k][m]++;


			i++;
			if (i <= N){//�ظ����ûʺ���̣�ֱ������λ��
				n = 1;
				continue;
			}

			output(A, N);//���һ�ֳɹ�����
			countc++;
			//�任�õ���һ�ֲ��֣������

			if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//���N��������ôA[n]==(N+1)/2��һ��������ñ任
			{
				for (int l = 1; l < N + 1; l++)
				{
					B[l] = N + 1 - A[l];
				}
				output(B, N);
				countc++;
			}

			i = N; n = A[N] + 1;//��n�лʺ�������Ϊ��Ѱ����һ�����������Ĳ���


		}
		else//���лʺ����޷����ã�������i-1�У�������conflict����
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
	int n = 2; A[1] = 1;//��ʼ�����ӵ�һ�п�ʼ
	while (A[1] <= (N + 1) / 2 && n >= 1)//���A[1]>n��˵��ȫ������ѱ���
	{
		A[n]++;//����һλ
		if (A[n]>N + 1) A[n] = 1; //�������֮�󳬳��߽磬������Ϊ1

		while (check(A, n) == 0 && A[n] <= N)//���ó�ͻ������飬�����ݷ��ؽ�����ûʺ�
			A[n]++;

		if (A[n] <= N)
		{
			if (n == N)//n==N��˵���ɹ�����һ�ֲ���
			{
				countc++;//����+1
				output(A, N);//���
				//�任�õ���һ�ֳɹ����֣������
				if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//���N��������ôA[n]==(N+1)/2��һ��������ñ任
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
				n++;//������һ�з���
			}

		}
		else
		{
			n--;//����
		}

	}
}

DWORD WINAPI filter(LPVOID lpParameter)//�������߳�
{
	int col = *(int*)(lpParameter);//��1������,
	int *a;
	a = new int[N + 1];//��ʼ�������飬ÿһ���ܵ��̶߳����Լ������飬�����ͱ����˶�ȫ��������в������ɲ��н��м���
	int * B;
	B = new int[N + 1];//��ʼ���仯����
	for (int i = 0; i <= N; i++)
	{
		a[i] = 0;
	}

	a[1] = col;
	int n = 2; a[n] = 0;
	while (a[2] <= N&&n >= 2)//�ӵ�2�п�ʼ
	{

		a[n]++;//����һλ
		if (a[n]>N + 1) a[n] = 1; //�������֮�󳬳��߽磬������Ϊ1

		while (check(a, n) == 0 && a[n] <= N)//���ó�ͻ������飬�����ݷ��ؽ�����ûʺ�
			a[n]++;

		if (a[n] <= N)
		{
			if (n == N)//n==N��˵���ɹ�����һ�ֲ���
			{
				EnterCriticalSection(&mutex);//�����ٽ���,�Լ������޸�
				countc++;//����+1
				output(a, N);//���	
				if (!((N % 2 != 0) && (a[1] == (N + 1) / 2)))//���N��������ôA[n]==(N+1)/2��һ��������ñ任
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
				LeaveCriticalSection(&mutex);//�뿪�ٽ���
			}
			else
			{
				n++;//������һ�з���
			}

		}
		else
		{

			n--;//����
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



void control()//������
{
	while (row >= 1)//���ݺڰ�����״̬������֪ʶԴ�ĵ���
	{
		LPVOID lp = &row;
		HANDLE thread = CreateThread(NULL, 0, ks, NULL, 0, NULL);
		WaitForSingleObject(thread, INFINITE);
	}
}

DWORD WINAPI ks(LPVOID lp)//֪ʶԴ�����߳���ģ��
{
	if ((A[1]>(N + 1) / 2))//�Ż��㷨,��һ�е�����С��(N+1)/2
	{
		row--;
		return 0;
	}
	else
	{
		A[row]++;//����һλ
		if (A[row]>N + 1) A[row] = 1; //�������֮�󳬳��߽磬������Ϊ1
		while (check(A, row) == 0 && A[row] <= N)//���ó�ͻ������飬�����ݷ��ؽ�����ûʺ�
			A[row]++;

		if (A[row] <= N)
		{
			if (row == N)//n==N��˵���ɹ�����һ�ֲ���
			{
				EnterCriticalSection(&mutex);
				countc++;//����+1
				output(A, N);//���
				//�任�õ���һ�ֳɹ����֣������
				if (!((N % 2 != 0) && (A[1] == (N + 1) / 2)))//���N��������ôA[n]==(N+1)/2��һ��������ñ任
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
				row++;//������һ�з���
			}

		}
		else
		{
			row--;//������1��������������һ���̷߳���
		}

		return 0;
	}
}