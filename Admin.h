#pragma once
#include"Person.h"
class Admin :public Person {
public:
	//默认构造函数
	Admin();
	//有参构造
	Admin(string username, string password);
	//界面
	virtual void page();
	//操作
	void operate();
	//添加科室名称 预约数量
	void addInfo();
	//修改科室名称 预约数量
	void chageInfo();
	//删除科室名称 预约数量
	void deleteInfo();
	//添加专家门诊
	void addExpertInfo();
	//修改专家门诊
	void changeExpertInfo();
	//删除专家门诊
	void deleteExpertInfo();
	//查看预约
	void showAppointment();
};