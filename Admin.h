#pragma once
#include"Person.h"
class Admin :public Person {
public:
	//Ĭ�Ϲ��캯��
	Admin();
	//�вι���
	Admin(string username, string password);
	//����
	virtual void page();
	//����
	void operate();
	//��ӿ������� ԤԼ����
	void addInfo();
	//�޸Ŀ������� ԤԼ����
	void chageInfo();
	//ɾ���������� ԤԼ����
	void deleteInfo();
	//�鿴ԤԼ
	void showAppointment();
};