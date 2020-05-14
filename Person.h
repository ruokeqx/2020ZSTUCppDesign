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
	//��ͨ���������Ϣ������
	vector<Department> vDepartmentInfo;
	//�鿴�������� ԤԼ����
	void showInfo();

	//ר��������Ϣ
	vector<ExpertDepartment> vExpertDepartmentInfo;
	//�鿴���� ʱ�����Ƿ���ר��
	bool hasExpert(string, int);

	//�Һŵ�����
	vector<Form> vForm;
};