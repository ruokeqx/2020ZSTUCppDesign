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
	//���캯��
	System();
	//��ʼ
	void Start();
private:
	//��¼
	void login(int);
};