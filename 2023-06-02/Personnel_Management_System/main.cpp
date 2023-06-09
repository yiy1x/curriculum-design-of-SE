#include "mainwindow.h"//管理员界面
#include"stu_mainwindow.h"
#include"qtlogin.h"//登录界面
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //先弹出登录窗口，如果正确登录才显示主窗口
    QtLogin theLogin;//登录界面类对象theLogin
    theLogin.show();//显示登录界面

    if(theLogin.exec()==QDialog::Accepted)//如果登录对话框是正确关闭或隐藏，就说明已经正常登录
    {
        if(theLogin.radio_admin->isChecked())
        {
            theLogin.close();
            MainWindow w;
            w.show();//显示主窗口
            return a.exec();//返回应用程序的执行过程，无其他设计就结束
        }
        else//学生进入
        {
            theLogin.close();
            stu_mainwindow w;
            w.show();
            return a.exec();//返回应用程序的执行过程，无其他设计就结束
        }
    }
    else return  0;
}
