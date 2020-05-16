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
	cout << "\t\t|          5.添加专家            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          6.修改专家            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          7.删除专家            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          8.查看就诊            |\n";
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
			this->addExpertInfo();
			break;
		case 6:
			this->changeExpertInfo();
			break;
		case 7:
			this->deleteExpertInfo();
			break;
		case 8:
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
//添加专家门诊
void Admin::addExpertInfo() {
	ExpertDepartment e;
	//获取信息
	cout << "请输入专家姓名：" << endl;
	cin >> e.expertName;
	cout << "请输入科室名称：" << endl;
	cin >> e.departmentName;
	cout << "请输入坐诊日期：" << endl;
	cin >> e.weekDay;
	cout << "请输入上午还是下午：1.上午 2.下午：" << endl;
	cin >> e.aorp;
	cout << "请输入最大接诊数量：" << endl;
	cin >> e.maxnNum;
	//刷新容器
	vExpertDepartmentInfo.push_back(e);
	//刷新文件
	ofstream out(EXPERT_FILE, ios::trunc);
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		out << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;
	}
	out.close();
}
//修改专家门诊
void Admin::changeExpertInfo() {
	ExpertDepartment e;
	//获取信息
	cout << "请输入专家姓名：" << endl;
	cin >> e.expertName;
	cout << "请输入科室名称：" << endl;
	cin >> e.departmentName;
	cout << "请输入坐诊日期：" << endl;
	cin >> e.weekDay;
	cout << "请输入上午还是下午：1.上午 2.下午：" << endl;
	cin >> e.aorp;
	cout << "请输入你要修改的最大数量：" << endl;
	cin >> e.maxnNum;
	//刷新容器
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		if (it->expertName == e.expertName && it->departmentName == e.departmentName && it->weekDay == e.weekDay && it->aorp == e.aorp) {
			it->maxnNum = e.maxnNum;
			cout << "修改成功！" << endl;
		}
	}
	//刷新文件
	ofstream out(EXPERT_FILE, ios::trunc);
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		out << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;
	}
	out.close();
}
//删除专家门诊
void Admin::deleteExpertInfo() {
	ExpertDepartment e;
	//获取信息
	cout << "请输入专家姓名：" << endl;
	cin >> e.expertName;
	cout << "请输入科室名称：" << endl;
	cin >> e.departmentName;
	cout << "请输入坐诊日期：" << endl;
	cin >> e.weekDay;
	cout << "请输入上午还是下午：1.上午 2.下午：" << endl;
	cin >> e.aorp;
	//刷新容器
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		if (it->expertName == e.expertName && it->departmentName == e.departmentName && it->weekDay == e.weekDay && it->aorp == e.aorp) {
			vExpertDepartmentInfo.erase(it);
			cout << "删除成功" << endl;
			break;
		}
	}
	//刷新文件
	ofstream out(EXPERT_FILE, ios::trunc);
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		out << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;
	}
	out.close();
}


//查看预约
void Admin::showAppointment() {
	string departmentName;
	int isExpert;
	int c0 = 0,c1=0;
	cout << "请输入你要查看的科室名称：" << endl;
	cin >> departmentName;
	cout << "请问你要查询普通门诊还是专家门诊：0.普通门诊 1.专家门诊" << endl;
	cin >> isExpert;
	cout << "查询结果如下：" << endl;
	//历遍容器
	for (vector<Form>::iterator it = vForm.begin();it != vForm.end();it++) {
		if (it->departmentName == departmentName) {
			if (isExpert && it->expertName != "非专家门诊") {
				cout << it->departmentName << "\t" << it->myName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->serial << "\t" << it->expertName << endl;
				c1++;
			}
			else if (!isExpert && it->expertName == "非专家门诊") {
				cout << it->departmentName << "\t" << it->myName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->serial << "\t" << it->expertName << endl;
				c0++;
			}
		}
	}
	cout << "查询结束，结果如上!" << endl;
	if (isExpert) {
		cout << "专家门诊共：" << c1 << " 单！" << endl;
	}
	else {
		cout<<"普通门诊共："<<c0<< " 单！" << endl;
	}
}