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