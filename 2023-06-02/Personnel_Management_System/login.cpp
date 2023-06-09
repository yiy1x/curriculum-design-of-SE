#include "login.h"
#include<QApplication>
#include<QSqlDriver>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include"QMessageBox"
#include"QErrorMessage"
#include"QSqlError"
#include<iostream>
using namespace std;


class LoginData : public QSharedData
{
public:

};

Login::Login() : data(new LoginData)
{

}

Login::Login(const Login &rhs) : data(rhs.data)
{

}

Login &Login::operator=(const Login &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

bool Login::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("yy");
        db.setUserName("root");
        db.setPassword("123456");
        if(!db.open())
        {
            QMessageBox::information(0, "infor", "open failed");
            qDebug()<<"error open database because"<<db.lastError().text();
            return  false;
        }
        return  true;
}

Login::~Login()
{

}
