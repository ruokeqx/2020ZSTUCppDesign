#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include<Windows.h>
using namespace std;
#include"Admin.h"
#include"Patient.h"
#include"File.h"

class System {
public:
	//构造函数
	System();
	//开始
	void Start();
private:
	//登录
	void login(int);
};