#pragma once
#include"Admin.h"
//默认构造函数
Admin::Admin() {

}
//有参构造
Admin::Admin(string username, string password) {
	this->username = username;
	this->password = password;
}
//界面
void Admin::page() {
	cout << "欢迎管理员：" << this->username << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.展示信息            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.添加信息            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.修改信息            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.删除信息            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|        5.查看就诊情况          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}
//操作
void Admin::operate() {
	this->page();
	int ch = 0;
	while (cin >> ch) {
		switch (ch)
		{
		case 1:
			this->showInfo();
			break;
		case 2:
			this->addInfo();
			break;
		case 3:
			this->chageInfo();
			break;
		case 4:
			this->deleteInfo();
			break;
		case 5:
			this->showAppointment();
			break;
		case 0:
			return;
		default:
			cout << "请输入正确选项！" << endl;
			system("pause");
			this->operate();
			break;
		}
		cout << "请选择您的操作： " << endl;
	}
}
//添加科室名称 预约数量
void Admin::addInfo() {
	//获取要添加的信息
	Department d;
	cout << "请输入要添加的科室名称：" << endl;
	cin >> d.departmentName;
	//去重
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		if ((*it).departmentName == d.departmentName) {
			cout << "科室‘" + d.departmentName + "'已存在！" << endl;
			system("pause");
			return;
		}
	}
	cout << "请输入其上午最大预约数量：" << endl;
	cin >> d.aMaxNum;
	cout << "请输入其下午最大预约数量：" << endl;
	cin >> d.pMaxNum;
	vDepartmentInfo.push_back(d);

	//存入文件
	ofstream out(COMMON_FILE, ios::app);
	out << d.departmentName << "\t" << d.aMaxNum << "\t" << d.aHad[0] << "\t" << d.aHad[1] << "\t" << d.aHad[2] << "\t" << d.aHad[3] << "\t" << d.aHad[4] << "\t" << d.aHad[5] << "\t" << d.aHad[6] << "\t" << d.pMaxNum << "\t" << d.pHad[0] << "\t" << d.pHad[1] << "\t" << d.pHad[2] << "\t" << d.pHad[3] << "\t" << d.pHad[4] << "\t" << d.pHad[5] << "\t" << d.pHad[6] << endl;
	out.close();
}
//修改科室名称 预约数量
void Admin::chageInfo() {
	//获取要修改的信息
	Department d;	//如果要修改名字的话可以再cin一个string
	cout << "请输入要修改的科室名称：" << endl;
	cin >> d.departmentName;
	cout << "请输入其上午最大预约数量：" << endl;
	cin >> d.aMaxNum;
	cout << "请输入其下午最大预约数量：" << endl;
	cin >> d.pMaxNum;

	//刷新容器
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		if ((*it).departmentName == d.departmentName) {
			(*it).aMaxNum = d.aMaxNum;
			(*it).pMaxNum = d.pMaxNum;
			break;
		}
	}
	
	//刷新文件
	ofstream out(COMMON_FILE, ios::trunc);
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
	}
	out.close();
}
//删除科室名称 预约数量
void Admin::deleteInfo() {
	//获取删除的科室
	string t;
	cout << "请输入要删除的科室名称：" << endl;
	cin >> t;

	//刷新容器
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();++it) {
		if ((*it).departmentName == t) {
			vDepartmentInfo.erase(it);
			break;	//如果是++it 一定要break 不然会出错 nullptr
		}
	}

	//刷新文件
	ofstream out(COMMON_FILE, ios::trunc);
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++)
		if ((*it).departmentName != t)
			out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
	out.close();
}
//查看预约
void Admin::showAppointment() {

}