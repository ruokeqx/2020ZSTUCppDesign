#pragma once
#include"Person.h"
//默认构造函数
Person::Person() {
	//普通门诊科室信息容器初始化
	ifstream in1(COMMON_FILE, ios::in);
	Department d;
	while (in1>>d.departmentName>>d.aMaxNum>>d.aHad[0]>>d.aHad[1]>>d.aHad[2]>>d.aHad[3]>>d.aHad[4]>>d.aHad[5]>>d.aHad[6]>>d.pMaxNum>>d.pHad[0]>>d.pHad[1]>>d.pHad[2]>>d.pHad[3]>>d.aHad[4]>>d.aHad[5]>>d.aHad[6]) {
		vDepartmentInfo.push_back(d);
	}
	in1.close();

	//专家门诊科室信息容器初始化
	ifstream in2(EXPERT_FILE, ios::in);
	ExpertDepartment e;
	while (in2 >> e.expertName >> e.departmentName >> e.weekDay >> e.aorp >> e.maxnNum >> e.nowNum) {
		vExpertDepartmentInfo.push_back(e);
	}
	in2.close();

	//电子预约单容器初始化
	ifstream in3(FORM_FILE, ios::in);
	Form f;
	while (in3 >> f.departmentName >> f.myName >> f.weekDay >> f.aorp >> f.serial >> f.expertName) {
		vForm.push_back(f);
	}
	in3.close();
}
//查看普通门诊科室名称 预约数量
void Person::showInfo() {
	cout << "当前科室数量为： " << vDepartmentInfo.size() << endl;
	for (vector<Department>::iterator it = vDepartmentInfo.begin(); it != vDepartmentInfo.end(); it++) {
		cout << "科室名称： " << it->departmentName << "\t上午最大预约数量： " << it->aMaxNum <<"\t下午最大预约数量：" << it->pMaxNum << endl;
	}
	system("pause");
}
//查看科室 时间下是否有专家
bool Person::hasExpert(string departmentName, int weekDay) {
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		if (it->departmentName == departmentName && it->weekDay == weekDay) {
			return true;
		}
	}
	return false;
}
