#pragma once
#include<iostream>
using namespace std;
class Department{
public:
	string departmentName;	//科室名称
	int aMaxNum=30;	//上午最大容量
	int aHad[7] = {0};	//上午已预约量
	int pMaxNum=30;	//下午最大容量
	int pHad[7] = {0};	//下午已预约量
};