#pragma once
#include"Patient.h"
//Ĭ�Ϲ��캯��
Patient::Patient() {

}
//�вι���
Patient::Patient(string myName, string idNum, string username, string password) {			
	this->myName = myName;			//����
	this->idNum = idNum;			//���֤��
	this->username = username;		//�ֻ���
	this->password = password;		//����
}
//����
void Patient::page() {
	cout << "��ӭ��" << this->myName << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.ԤԼ�Һ�             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.�鿴ԤԼ��¼         |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.ȡ��ԤԼ             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.ע����¼             |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}
//����
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
			cout << "��������ȷѡ�" << endl;
			system("pause");
			this->operate();
			break;
		}
		cout << "��ѡ�����Ĳ����� " << endl;
	}
}
//ԤԼ
void Patient::makeAppointment() {
	Form f;
	int needExpert = 0;	//�Ƿ�ר�Һ�


	cout << "��������Ҫѡ��Ŀ��ң�" << endl;	//��ȡ��������
	cin >> f.departmentName;

	cout << "��ѡ����ҪԤԼ�����ڣ�" << endl;	//���ڻ�ȡ
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	cout << "6������" << endl;
	cout << "7������" << endl;
	while (cin >> f.weekDay) {	//�жϺ�����
		if (f.weekDay < 1 || f.weekDay>7) {
			cout << "��������ȷ�����ڣ���Χ1-7��";
		}
		else {
			break;
		}
	}

	if (hasExpert(f.departmentName, f.weekDay)) {	//��ʾר�Һ�
		cout << "�����¼�λר�ң�" << endl;
		for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
			if (it->departmentName == f.departmentName && it->weekDay == f.weekDay) {
				cout << it->expertName << endl;
			}
		}

		//�Ƿ��ר�Һ�
		cout << "�����Ƿ�Ҫ��ר�Һţ�0.��	1.��" << endl;
		cin >> needExpert;
		if (needExpert) {
			cout << "������Ҫѡ���ר������" << endl;
			cin >> f.expertName;
		}
	}

	cout << "��ѡ����ҪԤԼ��ʱ��Σ�" << endl;	//������ʱ���ȡ
	cout << "1.����" << endl;
	cout << "2.����" << endl;
	while (cin >> f.aorp) {
		if (f.weekDay != 1 && f.weekDay!=2) {	//�жϺ�����
			cout << "��������ȷ��ʱ�䣬��Χ1-2��";
		}
		else {
			break;
		}
	}

	if (needExpert && hasExpert(f.departmentName, f.weekDay)) {
		for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
			if (it->departmentName == f.departmentName && it->weekDay == f.weekDay && it->expertName==f.expertName) {
				if (it->nowNum <= it->maxnNum) {
					cout << "ԤԼ�ɹ���" << endl;
					f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->nowNum);	//���ɾ����

					it->nowNum++;	//ˢ������

					ofstream out(EXPERT_FILE,ios::trunc);	//ˢ���ļ�append
					for (vector<ExpertDepartment>::iterator it = vExpertDepartmentInfo.begin();it != vExpertDepartmentInfo.end();it++) {
						out << it->expertName << "\t" << it->departmentName << "\t" << it->weekDay << "\t" << it->aorp << "\t" << it->maxnNum << "\t" << it->nowNum << endl;;
					}
					out.close();
				}
				else {
					cout << "ԤԼ��������������ԤԼ��" << endl;
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
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay-1]+1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if(f.weekDay == 2 && it->aHad[1] < it->aMaxNum){
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1]+1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 3 && it->aHad[2] < it->aMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 4 && it->aHad[3] < it->aMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 5 && it->aHad[4] < it->aMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 6 && it->aHad[5] < it->aMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 7 && it->aHad[6] < it->aMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + f.expertName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->aHad[f.weekDay - 1] + 1);	//���ɾ����
						it->aHad[f.weekDay - 1]++;	//ˢ������
					}
					else {
						cout << "ԤԼ��������������ԤԼ��" << endl;
						this->makeAppointment();
					}
				}
				else {
					if (f.weekDay == 1 && it->pHad[0]<=it->pMaxNum ){
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1]+1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 2 && it->pHad[1] <= it->pMaxNum){
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 3 && it->pHad[2] <= it->pMaxNum){
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 4 && it->pHad[3] <= it->pMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 5 && it->pHad[4] <= it->pMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 6 && it->pHad[5] <= it->pMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else if (f.weekDay == 7 && it->pHad[6] <= it->pMaxNum) {
						cout << "ԤԼ�ɹ���" << endl;
						f.serial = f.departmentName + to_string(f.weekDay) + to_string(f.aorp) + to_string(it->pHad[f.weekDay - 1] + 1);	//���ɾ����
						it->pHad[f.weekDay - 1]++;	//ˢ������
					}
					else {
						cout << "ԤԼ��������������ԤԼ��" << endl;
						this->makeAppointment();
					}
				}
				//ˢ���ļ�
				ofstream out(COMMON_FILE, ios::trunc);
				for (vector<Department>::iterator it = vDepartmentInfo.begin();it != vDepartmentInfo.end();it++) {
					out << it->departmentName << "\t" << it->aMaxNum << "\t" << it->aHad[0] << "\t" << it->aHad[1] << "\t" << it->aHad[2] << "\t" << it->aHad[3] << "\t" << it->aHad[4] << "\t" << it->aHad[5] << "\t" << it->aHad[6] << "\t" << it->pMaxNum << "\t" << it->pHad[0] << "\t" << it->pHad[1] << "\t" << it->pHad[2] << "\t" << it->pHad[3] << "\t" << it->pHad[4] << "\t" << it->pHad[5] << "\t" << it->pHad[6] << endl;
				}
				out.close();
			}
		}
	}
	cout <<"��ľ�����ǣ�" <<f.serial << endl;
	//��ӡ���ӹҺŵ�
	cout << "�������ĵ��ӹҺŵ���" << endl;
	cout << "�������ƣ�" << f.departmentName << "\t����������" << myName << "\t�������ڣ�" << f.weekDay << f.aorp << "\t����ţ�" << f.serial << "\tר��������" << f.expertName << endl;
	
	//ˢ������
	f.myName = myName;
	vForm.push_back(f);

	//�����ļ�
	ofstream out2(FORM_FILE,ios::app);
	out2 << f.departmentName << "\t" << myName << "\t" << f.weekDay << "\t" << f.aorp << "\t" << f.serial << "\t" << f.expertName << endl;
	out2.close();

	system("pause");
}
//�鿴ԤԼ
void Patient::showAppointment() {
	for (vector<Form>::iterator it = vForm.begin();it != vForm.end();it++) {
		if (it->myName == myName) {		//���߲鿴�Լ���ԤԼ��¼
			cout << "�������ƣ�" << it->departmentName << "\t����������" << it->myName << "\t�������ڣ�" << it->weekDay << it->aorp << "\t����ţ�" << it->serial << "\tר��������" << it->expertName << endl;
		}
	}
}
//*ȡ��ԤԼ
void Patient::cancelAppointment() {

}