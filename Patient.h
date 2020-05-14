#pragma once
#include"Person.h"
class Patient :public Person {
public:
	//默认构造函数
	Patient();
	//有参构造
	Patient(string myName,string idNum,string phoneNum, string password);
	//界面
	virtual void page();
	//操作
	void operate();
	//预约
	void makeAppointment();
	//查看预约
	void showAppointment();
	//*取消预约
	void cancelAppointment();
private:
	string myName, idNum;
};