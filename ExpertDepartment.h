#pragma once
#include<iostream>
using namespace std;
class ExpertDepartment {
public:
	string expertName;	//专家姓名
	string departmentName;	//科室名称
	int weekDay;	//日期
	int aorp;	//上下午
	int maxnNum=30;	//最大预约数量（默认30）
	int nowNum = 1;	//现在预约号
};