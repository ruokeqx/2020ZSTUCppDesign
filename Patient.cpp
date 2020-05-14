#pragma once
#include"Patient.h"
//默认构造函数
Patient::Patient() {

}
//有参构造
Patient::Patient(string myName, string idNum, string username, string password) {			
	this->myName = myName;			//姓名
	this->idNum = idNum;			//身份证号
	this->username = username;		//手机号
	this->password = password;		//密码
}
//界面
void Patient::page() {
	cout << "欢迎：" << this->myName << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.预约挂号             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看预约记录         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.取消预约             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}
//操作
void Patient::operate() {
	this->page();
	int ch = 0;
	while (cin >> ch) {
		switch (ch)
		{
		case 1:
			this->makeAppointment();
			break;
		case 2:
			this->showAppointment();
			break;
		case 3:
			this->cancelAppointment();
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
//预约
void Patient::makeAppointment() {
	Form f;
	int needExpert = 0;	//是否专家号


	cout << "请输入你要选择的科室：" << endl;	//获取科室名称
	cin >> f.departmentName;

	cout << "请选择你要预约的日期：" << endl;	//日期获取
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	cout << "6、周六" << endl;
	cout << "7、周日" << endl;
	while (cin >> f.weekDay) {	//判断合理性
		if (f.weekDay < 1 || f.weekDay>7) {
			cout << "请输入正确的日期，范围1-7！";
		}
		else {
			break;
		}
	}

	if (hasExpert(f.departmentName, f.weekDay)) {	//提示专家号
		cout << "有如下几位专家：" << endl;
		for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
			if (it->departmentName == f.departmentName && it->weekDay == f.weekDay) {
				cout << it->expertName << endl;
			}
		}

		//是否挂专家号
		cout << "请问是否要挂专家号？0.否	1.是" << endl;
		cin >> needExpert;
		if (needExpert) {
			cout << "请输入要选择的专家名：" << endl;
			cin >> f.expertName;
		}
	}

	cout << "请选择你要预约的时间段：" << endl;	//上下午时间获取
	cout << "1.上午" << endl;
	cout << "2.下午" << endl;
	while (cin >> f.aorp) {
		if (f.weekDay != 1 && f.weekDay!=2) {	//判断合理性
			cout << "请输入正确的时间，范围1-2！";
		}
		else {
			break;
		}
	}

	if (needExpert && hasExpert(f.departmentName, f.weekDay)) {
		for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
			if (it->departmentName == f.departmentName && it->weekDay == f.weekDay && it->expertName==f.expertName) {
				if (it->nowNum <= it->maxnNum) {
					cout << "预约成功！" << endl;
					f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->nowNum);	//生成就诊号

					it->nowNum++;	//刷新容器

					ofstream out(EXPERT_FILE,ios::trunc);	//刷新文件append
					for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
						out << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;;
					}
					out.close();
				}
				else {
					cout << "预约数已满，请重新预约！" << endl;
					this->makeAppointment();
				}
			}
		}
	}
	else {
		for (vector<Department>::iterator it = vDepartmentInfo.begin(); it != vDepartmentInfo.end(); it++) {
			if (it->departmentName==f.departmentName) {
				if (f.aorp == 1) {
					if (f.weekDay == 1 && it->aHad[0] < it->aMaxNum ) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay-1]+1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if(f.weekDay == 2 && it->aHad[1] < it->aMaxNum){
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1]+1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 3 && it->aHad[2] < it->aMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 4 && it->aHad[3] < it->aMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 5 && it->aHad[4] < it->aMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 6 && it->aHad[5] < it->aMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 7 && it->aHad[6] < it->aMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//生成就诊号
						it->aHad[f.weekDay - 1]++;	//刷新容器
					}
					else {
						cout << "预约数已满，请重新预约！" << endl;
						this->makeAppointment();
					}
				}
				else {
					if (f.weekDay == 1 && it->pHad[0]<=it->pMaxNum ){
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1]+1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 2 && it->pHad[1] <= it->pMaxNum){
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 3 && it->pHad[2] <= it->pMaxNum){
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 4 && it->pHad[3] <= it->pMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 5 && it->pHad[4] <= it->pMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 6 && it->pHad[5] <= it->pMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else if (f.weekDay == 7 && it->pHad[6] <= it->pMaxNum) {
						cout << "预约成功！" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//生成就诊号
						it->pHad[f.weekDay - 1]++;	//刷新容器
					}
					else {
						cout << "预约数已满，请重新预约！" << endl;
						this->makeAppointment();
					}
				}
				//刷新文件
				ofstream out(COMMON_FILE, ios::trunc);
				for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
					out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
				}
				out.close();
			}
		}
	}
	cout <<"你的就诊号是：" <<f.serial << endl;
	//打印电子挂号单
	cout << "请查收你的电子挂号单：" << endl;
	cout << "科室名称：" << f.departmentName << "\t患者姓名：" << myName << "\t就诊日期：" << f.weekDay << f.aorp << "\t就诊号：" << f.serial << "\t专家姓名：" << f.expertName << endl;
	
	//刷新容器
	f.myName = myName;
	vForm.push_back(f);

	//存入文件
	ofstream out2(FORM_FILE,ios::app);
	out2 << f.departmentName << "\t" << myName << "\t" << f.weekDay << "\t" << f.aorp << "\t" << f.serial << "\t" << f.expertName << endl;
	out2.close();

	system("pause");
}
//查看预约
void Patient::showAppointment() {
	if (vForm.empty())
		cout << "当前没用预约记录！" << endl;
	for (vector<Form>::iterator it = vForm.begin();it != vForm.end();it++) {
		if (it->myName == myName) {		//患者查看自己的预约记录
			cout << "科室名称：" << it->departmentName << "\t患者姓名：" << it->myName << "\t就诊日期：" << it->weekDay << it->aorp << "\t就诊号：" << it->serial << "\t专家姓名：" << it->expertName << endl;
		}
	}
}
//*取消预约
void Patient::cancelAppointment() {
	string toDelete;	//要删除的对应就诊号
	int flag = 0;	//标记是否删除成功
	Form t;
	while (!vForm.empty()) {
		cout << "你的预约如下：" << endl;
		this->showAppointment();
		cout << "请输入你要取消的预约的就诊号：" << endl;
		while (cin >> toDelete) {
			for (vector<Form>::iterator it = vForm.begin();it != vForm.end();it++) {
				if (it->serial == toDelete) {
					flag = 1;	//标记
					t = *it;
					vForm.erase(it);	//刷新容器
					break;
				}
			}
			if (flag) {
				cout << "删除成功！" << endl;
				//刷新电子挂单文件
				ofstream out(FORM_FILE, ios::trunc);
				for (vector<Form>::iterator it = vForm.begin();it != vForm.end();it++) {
					out << it->departmentName << "\t" << it->myName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->serial << "\t" << it->expertName << endl;
				}
				out.close();

				//刷新对应门诊预约数量
				if (t.expertName == "非专家门诊") {
					//刷新容器
					for (vector<Department>::iterator it = vDepartmentInfo.begin(); it != vDepartmentInfo.end(); it++) {
						if (t.departmentName == it->departmentName) {
							if (t.aorp == 1) {
								it->aHad[t.weekDay - 1]--;
							}
							else {
								it->pHad[t.weekDay - 1]--;
							}
						}

					}
					//刷新文件
					ofstream o(COMMON_FILE, ios::trunc);
					for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
						o << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
					}
					o.close();
				}
				else {
					//刷新容器
					for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
						if (t.expertName==it->expertName && t.departmentName==it->departmentName && t.weekDay==it->weekDay && t.aorp==it->aorp) {
							it->nowNum--;
						}
					}
					//刷新文件
					ofstream o(EXPERT_FILE, ios::trunc);
					for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
						o << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;
					}
					o.close();
				}

				system("pause");
				return;
			}
			else
				cout << "请输入正确的就诊号：" << endl;
		}
	}
	cout << "你当前还没有任何预约记录！" << endl;
	this->operate();
}