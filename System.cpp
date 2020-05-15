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
            patientRegiste();
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




//检验身份证号正确性
int cal(string a)
{
    return (a[0] - '0') * 7 + (a[1] - '0') * 9 + (a[2] - '0') * 10 + (a[3] - '0') * 5 + (a[4] - '0') * 8 + (a[5] - '0') * 4 + (a[6] - '0') * 2 + (a[7] - '0') * 1 + (a[8] - '0') * 6 + (a[9] - '0') * 3 + (a[10] - '0') * 7 + (a[11] - '0') * 9 + (a[12] - '0') * 10 + (a[13] - '0') * 5 + (a[14] - '0') * 8 + (a[15] - '0') * 4 + (a[16] - '0') * 2;
}

char s(string a)
{
    int k = cal(a) % 11;
    if (k == 0)
        return '1';
    else if (k == 1)
        return '0';
    else if (k == 2)
        return 'X';
    else
        return '0' + 12 - k;
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
//注册患者账号
void System::patientRegiste() {
    string myName, idNum, phoneNum, password;
    //姓名
    cout << "请输入你的姓名:" << endl;
    cin >> myName;
    //身份证
    cout << "请输入你的身份证号：" << endl;
    while (cin >> idNum) {
        if (idNum.length() == 18) {                 //长度校验
            if (idNum.substr(6, 4) <= "2020") {     //年份校验
                if (idNum[17] == s(idNum)) {        //校验码校验
                    break;
                }
                else {
                    cout<<"亲，我可是智能的，别输入假身份证骗我！"<<endl;
                }
            }
            else {
                cout << "朋友，您搁这穿越呢？" << endl;
            }
        }
        else {
            cout << "请输入正确长度的身份证号：" << endl;
        }
    }
    //去重
    ifstream in1(PATIENT_FILE, ios::in);
    string a, b, c, d;
    while (in1 >> a >> b >> c >> d) {
        if (b==idNum) {
            cout << "该用户已存在！请重新输入！" << endl;
            in1.close();
            this->patientRegiste();
        }
    }
    in1.close();
    //手机号
    cout << "请输入手机号：" << endl;
    while (cin >> phoneNum) {
        if (phoneNum.length() == 11) {
            break;
        }
        else {
            cout << "请输入正确长度的手机号：" << endl;
        }
    }
    //去重
    ifstream in2(PATIENT_FILE, ios::in);
    while (in2 >> a >> b >> c >> d) {
        if (c == phoneNum) {
            cout << "该用户已存在！请重新输入！" << endl;
            in2.close();
            this->patientRegiste();
        }
    }
    in2.close();
    //密码
    cout << "请输入你的密码：" << endl;
    while (cin >> password) {
        if (password.length() >= 6) {
            regex judge("^[A-Za-z0-9]+$");
            if (regex_match(password, judge)) {
                break;
            }
            else {
                cout << "密码只能包含字母和数字：" << endl;
            }
        }
        else {
            cout << "密码长度不得小于6：" << endl;
        }
    }
    //添加用户
    ofstream out(PATIENT_FILE, ios::app);
    out << myName << "\t" << idNum << "\t" << phoneNum << "\t" << password << endl;
    out.close();
}