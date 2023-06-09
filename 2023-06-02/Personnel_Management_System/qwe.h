#ifndef LOGIN_H
#define LOGIN_H


class Login
{
public:
    Login();
    void start_login();//开始登录
    int welcome();//欢迎界面
    bool connectDB();//连接数据库
};

#endif // LOGIN_H
