#pragma once
#include"Admin.h"
//Ĭ�Ϲ��캯��
Admin::Admin() {

}
//�вι���
Admin::Admin(string username, string password) {
	this->username = username;
	this->password = password;
}
//����
void Admin::page() {
	cout << "��ӭ����Ա��" << this->username << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.չʾ��Ϣ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�����Ϣ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�޸���Ϣ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.ɾ����Ϣ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|        5.�鿴�������          |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}
//����
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
			cout << "��������ȷѡ�" << endl;
			system("pause");
			this->operate();
			break;
		}
		cout << "��ѡ�����Ĳ����� " << endl;
	}
}
//��ӿ������� ԤԼ����
void Admin::addInfo() {
	//��ȡҪ��ӵ���Ϣ
	Department d;
	cout << "������Ҫ��ӵĿ������ƣ�" << endl;
	cin >> d.departmentName;
	//ȥ��
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		if ((*it).departmentName == d.departmentName) {
			cout << "���ҡ�" + d.departmentName + "'�Ѵ��ڣ�" << endl;
			system("pause");
			return;
		}
	}
	cout << "���������������ԤԼ������" << endl;
	cin >> d.aMaxNum;
	cout << "���������������ԤԼ������" << endl;
	cin >> d.pMaxNum;
	vDepartmentInfo.push_back(d);

	//�����ļ�
	ofstream out(COMMON_FILE, ios::app);
	out << d.departmentName << "\t" << d.aMaxNum << "\t" << d.aHad[0] << "\t" << d.aHad[1] << "\t" << d.aHad[2] << "\t" << d.aHad[3] << "\t" << d.aHad[4] << "\t" << d.aHad[5] << "\t" << d.aHad[6] << "\t" << d.pMaxNum << "\t" << d.pHad[0] << "\t" << d.pHad[1] << "\t" << d.pHad[2] << "\t" << d.pHad[3] << "\t" << d.pHad[4] << "\t" << d.pHad[5] << "\t" << d.pHad[6] << endl;
	out.close();
}
//�޸Ŀ������� ԤԼ����
void Admin::chageInfo() {
	//��ȡҪ�޸ĵ���Ϣ
	Department d;	//���Ҫ�޸����ֵĻ�������cinһ��string
	cout << "������Ҫ�޸ĵĿ������ƣ�" << endl;
	cin >> d.departmentName;
	cout << "���������������ԤԼ������" << endl;
	cin >> d.aMaxNum;
	cout << "���������������ԤԼ������" << endl;
	cin >> d.pMaxNum;

	//ˢ������
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		if ((*it).departmentName == d.departmentName) {
			(*it).aMaxNum = d.aMaxNum;
			(*it).pMaxNum = d.pMaxNum;
			break;
		}
	}
	
	//ˢ���ļ�
	ofstream out(COMMON_FILE, ios::trunc);
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
		out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
	}
	out.close();
}
//ɾ���������� ԤԼ����
void Admin::deleteInfo() {
	//��ȡɾ���Ŀ���
	string t;
	cout << "������Ҫɾ���Ŀ������ƣ�" << endl;
	cin >> t;

	//ˢ������
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();++it) {
		if ((*it).departmentName == t) {
			vDepartmentInfo.erase(it);
			break;	//�����++it һ��Ҫbreak ��Ȼ����� nullptr
		}
	}

	//ˢ���ļ�
	ofstream out(COMMON_FILE, ios::trunc);
	for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++)
		if ((*it).departmentName != t)
			out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
	out.close();
}
//�鿴ԤԼ
void Admin::showAppointment() {

}