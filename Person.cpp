#pragma once
#include"Person.h"
//Ĭ�Ϲ��캯��
Person::Person() {
	//��ͨ���������Ϣ������ʼ��
	ifstream in1(COMMON_FILE, ios::in);
	Department d;
	while (in1>>d.departmentName>>d.aMaxNum>>d.aHad[0]>>d.aHad[1]>>d.aHad[2]>>d.aHad[3]>>d.aHad[4]>>d.aHad[5]>>d.aHad[6]>>d.pMaxNum>>d.pHad[0]>>d.pHad[1]>>d.pHad[2]>>d.pHad[3]>>d.aHad[4]>>d.aHad[5]>>d.aHad[6]) {
		vDepartmentInfo.push_back(d);
	}
	in1.close();

	//ר�����������Ϣ������ʼ��
	ifstream in2(EXPERT_FILE, ios::in);
	ExpertDepartment e;
	while (in2 >> e.expertName >> e.departmentName >> e.weekDay >> e.aorp >> e.maxnNum >> e.nowNum) {
		vExpertDepartmentInfo.push_back(e);
	}
	in2.close();

	//����ԤԼ��������ʼ��
	ifstream in3(FORM_FILE, ios::in);
	Form f;
	while (in3 >> f.departmentName >> f.myName >> f.weekDay >> f.aorp >> f.serial >> f.expertName) {
		vForm.push_back(f);
	}
	in3.close();
}
//�鿴��ͨ����������� ԤԼ����
void Person::showInfo() {
	cout << "��ǰ��������Ϊ�� " << vDepartmentInfo.size() << endl;
	for (vector<Department>::iterator it = vDepartmentInfo.begin(); it != vDepartmentInfo.end(); it++) {
		cout << "�������ƣ� " << it->departmentName << "\t�������ԤԼ������ " << it->aMaxNum <<"\t�������ԤԼ������" << it->pMaxNum << endl;
	}
	system("pause");
}
//�鿴���� ʱ�����Ƿ���ר��
bool Person::hasExpert(string departmentName, int weekDay) {
	for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
		if (it->departmentName == departmentName && it->weekDay == weekDay) {
			return true;
		}
	}
	return false;
}
