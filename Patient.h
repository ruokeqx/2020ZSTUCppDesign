#pragma once
#include"Person.h"
class Patient :public Person {
public:
	//Ĭ�Ϲ��캯��
	Patient();
	//�вι���
	Patient(string myName,string idNum,string phoneNum, string password);
	//����
	virtual void page();
	//����
	void operate();
	//ԤԼ
	void makeAppointment();
	//�鿴ԤԼ
	void showAppointment();
	//*ȡ��ԤԼ
	void cancelAppointment();
private:
	string myName, idNum;
};