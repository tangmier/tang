#include <iostream>
#include "Service.h"
#include "DBO.h"
using namespace std;

int main()
{
	cout << "Server starts" << endl;
	Service service;
	service.start_service();
}