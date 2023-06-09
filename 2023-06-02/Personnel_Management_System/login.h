#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>

class LoginData;

class Login
{

public:
    Login();
    Login(const Login &);
    Login &operator=(const Login &);
    ~Login();
    void start_login();//开始登录
    int welcome();//欢迎界面
    bool connectDB();//连接数据库

private:
    QSharedDataPointer<LoginData> data;
};

#endif // LOGIN_H
