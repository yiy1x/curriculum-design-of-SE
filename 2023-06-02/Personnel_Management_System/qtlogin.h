#ifndef QTLOGIN_H
#define QTLOGIN_H

#include <QDialog>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QPushButton>
#include<QRadioButton>
#include<QMessageBox>
#include<QLabel>

namespace Ui {
class QtLogin;
}

class QtLogin : public QDialog
{
    Q_OBJECT

public:
    explicit QtLogin(QWidget *parent = nullptr);
    ~QtLogin();
    void initUI();//初始化登录界面的成员函数
     QRadioButton* radio_admin,* radio_stu;

private:
    Ui::QtLogin *ui;
    QVBoxLayout* theLayout;//登录界面的总体布局
    QLineEdit* edit_user,* edit_pwd;//用户名和密码的编辑框
    QLabel* user_show,* pwd_show;//显示用户名和密码
    QLabel* kongge;

    QHBoxLayout* user_layout,* pwd_layout;
    QHBoxLayout* usertype_layout;


    QHBoxLayout* button_layout;//按钮的水平布局
    QPushButton* btn_login,* btn_exit;//登录退出按钮

protected:
    void WriteInit(QString key,QString value);

private slots:
    void on_login();//执行登录操作的槽函数
    void on_exit();//执行退出操作的槽函数
    void on_radio_admin();
    void on_radio_stu();
};

#endif // QTLOGIN_H
