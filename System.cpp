#pragma once
#include"System.h"
//构造函数
System::System() {

}
//开始
void System::Start() {
    while (1) {
        SetConsoleTitle("自主预约挂号系统");
        cout << "*****************************************************\n";
        cout << "*                                                   *\n";
        cout << "*                欢迎来到预约挂号系统               *\n";
        cout << "*                  请选择你的操作                   *\n";
        cout << "*                                                   *\n";
        cout << "*                                                   *\n";
        cout << "*   0.管理员登录  1.患者登录  2.注册账号   3.退出   *\n";
        cout << "*                                                   *\n";
        cout << "*                                                   *\n";
        cout << "*****************************************************\n";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 0:
            login(0);
            break;
        case 1:
            login(1);
            break;
        case 2:
            break;
        case 3:
            cout << "欢迎下次使用！\n";
            system("pause");
            exit(0);
        default:
            cout << "请选择正确的选项!\n";
            break;
        }
    }
}
//登录
void System::login(int type) {
    //文件操作
    string fileName;
    type ? fileName = PATIENT_FILE : fileName = ADMIN_FILE;
    ifstream in(fileName, ios::in);
    if (!in.is_open()) {
        cout << "文件不存在" << endl;
        in.close();
        return;
    }

    //登录
    Person* person = NULL;
    string username, password;
    cout << "请输入用户名：" << endl;
    cin >> username;
    cout << "请输入密码： " << endl;
    cin >> password;
    if (type) { //患者
        string myName, idNum, phoneNum, passwd;
        while (in >> myName >> idNum >> phoneNum >> passwd) {
            if (username == phoneNum && password == passwd) {
                cout << "患者验证登录成功!" << endl;
                system("pause");
                person = new Patient(myName, idNum, phoneNum, passwd);
                Patient* patient = (Patient*)person;
                patient->operate();
                delete patient;
                person = NULL;
                return;
            }
        }
        cout << "没用这个用户，请检查用户名和密码！" << endl;
        int ch;
        cout << "*******************************************\n";
        cout << "*              请选择你的操作             *\n";
        cout << "*                                         *\n";
        cout << "*        1.重新登录     2.回到主页        *\n";
        cout << "*******************************************\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            this->login(1);
            break;
        case 2:
            this->Start();
        default:
            break;
        }
    }
    else if (type == 0) {   //管理员
        string usr, passwd;
        while (in >> usr >> passwd) {
            if (username == usr && password == passwd) {
                cout << "管理员验证登录成功!" << endl;
                system("pause");
                person = new Admin(usr, passwd);
                Admin* admin = (Admin*)person;
                admin->operate();
                delete admin;
                person = NULL;
                return;
            }
        }
        cout << "没用这个管理员，请检查用户名和密码！" << endl;
        int ch;
        cout << "*******************************************\n";
        cout << "*              请选择你的操作             *\n";
        cout << "*                                         *\n";
        cout << "*        1.重新登录     2.回到主页        *\n";
        cout << "*******************************************\n";
        cin >> ch;
        switch (ch)
        {
        case 1:
            this->login(0);
            break;
        case 2:
            this->Start();
        default:
            break;
        }
    }
    system("pause");
    in.close();
    return;
}