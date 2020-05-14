#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"File.h"
#include"Department.h"
#include"ExpertDepartment.h"
#include"Form.h"
using namespace std;
class Person {
public:
	Person();
	virtual void page() = 0;
	string username;
	string password;
	//普通门诊科室信息的容器
	vector<Department> vDepartmentInfo;
	//查看科室名称 预约数量
	void showInfo();

	//专家门诊信息
	vector<ExpertDepartment> vExpertDepartmentInfo;
	//查看科室 时间下是否有专家
	bool hasExpert(string, int);

	//挂号单容器
	vector<Form> vForm;
};