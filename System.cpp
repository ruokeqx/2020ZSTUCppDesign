#pragma once
#include"System.h"
//���캯��
System::System() {

}
//��ʼ
void System::Start() {
    while (1) {
        SetConsoleTitle("����ԤԼ�Һ�ϵͳ");
        cout << "*****************************************************\n";
        cout << "*                                                   *\n";
        cout << "*                ��ӭ����ԤԼ�Һ�ϵͳ               *\n";
        cout << "*                  ��ѡ����Ĳ���                   *\n";
        cout << "*                                                   *\n";
        cout << "*                                                   *\n";
        cout << "*   0.����Ա��¼  1.���ߵ�¼  2.ע���˺�   3.�˳�   *\n";
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
            cout << "��ӭ�´�ʹ�ã�\n";
            system("pause");
            exit(0);
        default:
            cout << "��ѡ����ȷ��ѡ��!\n";
            break;
        }
    }
}




//�������֤����ȷ��
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




//��¼
void System::login(int type) {
    //�ļ�����
    string fileName;
    type ? fileName = PATIENT_FILE : fileName = ADMIN_FILE;
    ifstream in(fileName, ios::in);
    if (!in.is_open()) {
        cout << "�ļ�������" << endl;
        in.close();
        return;
    }

    //��¼
    Person* person = NULL;
    string username, password;
    cout << "�������û�����" << endl;
    cin >> username;
    cout << "���������룺 " << endl;
    cin >> password;
    if (type) { //����
        string myName, idNum, phoneNum, passwd;
        while (in >> myName >> idNum >> phoneNum >> passwd) {
            if (username == phoneNum && password == passwd) {
                cout << "������֤��¼�ɹ�!" << endl;
                system("pause");
                person = new Patient(myName, idNum, phoneNum, passwd);
                Patient* patient = (Patient*)person;
                patient->operate();
                delete patient;
                person = NULL;
                return;
            }
        }
        cout << "û������û��������û��������룡" << endl;
        int ch;
        cout << "*******************************************\n";
        cout << "*              ��ѡ����Ĳ���             *\n";
        cout << "*                                         *\n";
        cout << "*        1.���µ�¼     2.�ص���ҳ        *\n";
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
    else if (type == 0) {   //����Ա
        string usr, passwd;
        while (in >> usr >> passwd) {
            if (username == usr && password == passwd) {
                cout << "����Ա��֤��¼�ɹ�!" << endl;
                system("pause");
                person = new Admin(usr, passwd);
                Admin* admin = (Admin*)person;
                admin->operate();
                delete admin;
                person = NULL;
                return;
            }
        }
        cout << "û���������Ա�������û��������룡" << endl;
        int ch;
        cout << "*******************************************\n";
        cout << "*              ��ѡ����Ĳ���             *\n";
        cout << "*                                         *\n";
        cout << "*        1.���µ�¼     2.�ص���ҳ        *\n";
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
//ע�Ỽ���˺�
void System::patientRegiste() {
    string myName, idNum, phoneNum, password;
    //����
    cout << "�������������:" << endl;
    cin >> myName;
    //���֤
    cout << "������������֤�ţ�" << endl;
    while (cin >> idNum) {
        if (idNum.length() == 18) {                 //����У��
            if (idNum.substr(6, 4) <= "2020") {     //���У��
                if (idNum[17] == s(idNum)) {        //У����У��
                    break;
                }
                else {
                    cout<<"�ף��ҿ������ܵģ�����������֤ƭ�ң�"<<endl;
                }
            }
            else {
                cout << "���ѣ������⴩Խ�أ�" << endl;
            }
        }
        else {
            cout << "��������ȷ���ȵ����֤�ţ�" << endl;
        }
    }
    //ȥ��
    ifstream in1(PATIENT_FILE, ios::in);
    string a, b, c, d;
    while (in1 >> a >> b >> c >> d) {
        if (b==idNum) {
            cout << "���û��Ѵ��ڣ����������룡" << endl;
            in1.close();
            this->patientRegiste();
        }
    }
    in1.close();
    //�ֻ���
    cout << "�������ֻ��ţ�" << endl;
    while (cin >> phoneNum) {
        if (phoneNum.length() == 11) {
            break;
        }
        else {
            cout << "��������ȷ���ȵ��ֻ��ţ�" << endl;
        }
    }
    //ȥ��
    ifstream in2(PATIENT_FILE, ios::in);
    while (in2 >> a >> b >> c >> d) {
        if (c == phoneNum) {
            cout << "���û��Ѵ��ڣ����������룡" << endl;
            in2.close();
            this->patientRegiste();
        }
    }
    in2.close();
    //����
    cout << "������������룺" << endl;
    while (cin >> password) {
        if (password.length() >= 6) {
            regex judge("^[A-Za-z0-9]+$");
            if (regex_match(password, judge)) {
                break;
            }
            else {
                cout << "����ֻ�ܰ�����ĸ�����֣�" << endl;
            }
        }
        else {
            cout << "���볤�Ȳ���С��6��" << endl;
        }
    }
    //����û�
    ofstream out(PATIENT_FILE, ios::app);
    out << myName << "\t" << idNum << "\t" << phoneNum << "\t" << password << endl;
    out.close();
}