
#include "qtlogin.h"
#include "ui_qtlogin.h"
#include<QVBoxLayout>
#include<QLineEdit>
#include<QPushButton>
#include<QRadioButton>
#include<QMessageBox>
#include<QtSql/QSqlDatabase>
#include<QSqlQuery>
#include<QLabel>
#include<QRegExpValidator>

#include <QSettings>
#include<QDebug>
#include<iostream>
using namespace std;
QtLogin::QtLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtLogin)
{
    ui->setupUi(this);
    initUI();//初始化登录界面
}

QtLogin::~QtLogin()
{
    delete ui;
}

void QtLogin::initUI()
{//初始化登录界面
    this->setWindowTitle("公司人事管理系统登录窗口");
    this->setFixedSize(600,400);
    this->setWindowIcon(QIcon(":/myImages/images/tubiao.png"));
    //设定登录界面节基本字体
    QFont ft;
    ft.setBold(true);//加粗
    ft.setPointSize(12);



    //先创建一个总体布局，采用垂直布局实现
    theLayout = new QVBoxLayout;

    user_layout = new QHBoxLayout;
    pwd_layout = new QHBoxLayout;
    //在行的左边增加一个弹性的填充框
    //user_layout->addStretch(1);
    //pwd_layout->addStretch(1);
    //标签添加
    user_show = new QLabel("           用户名");
    pwd_show = new QLabel("            密码 ");
    user_show->setFont(ft);
    pwd_show->setFont(ft);
    user_layout->addWidget(user_show);
    pwd_layout->addWidget(pwd_show);
    //用户框和密码框的设置
    edit_user = new QLineEdit;
    edit_pwd = new QLineEdit;
    edit_user->setPlaceholderText("请输入您的用户名");
    edit_pwd->setPlaceholderText("请输入您的密码");
    edit_user->setFont(ft);
    edit_pwd->setFont(ft);
    edit_user->setAttribute(Qt::WA_InputMethodEnabled,false);//屏蔽中文输入
    QRegExp regx("[a-zA-Z0-9]+$");//创建一个正则表达式对象
    QValidator* validator =new QRegExpValidator(regx);//只能输入字母和数字
    edit_user->setValidator(validator);
    edit_pwd->setAttribute(Qt::WA_InputMethodEnabled,false);//屏蔽中文输入

    edit_user->setMaxLength(12);
    edit_pwd->setMaxLength(12);
    edit_pwd->setEchoMode(QLineEdit::Password);//设为密码属性，不可见
    user_layout->addWidget(edit_user);//将用户名加入
    pwd_layout->addWidget(edit_pwd);//将密码加入子布局
    //在行的右边增加一个弹性的填充框
    user_layout->addStretch(1);
    pwd_layout->addStretch(1);

    //放入总体布局中
    theLayout->addLayout(user_layout);
    theLayout->addLayout(pwd_layout);

    //添加单选按钮的布局
    usertype_layout = new QHBoxLayout;
    //用户和管理员入口
    radio_admin = new QRadioButton("管理员");
    radio_stu = new QRadioButton("员工");
    radio_admin->setFont(ft);
    radio_stu->setFont(ft);
    usertype_layout->addStretch();
    usertype_layout->addWidget(radio_admin);
    usertype_layout->addStretch();
    usertype_layout->addWidget(radio_stu);
     usertype_layout->addStretch();
    theLayout->addLayout(usertype_layout);

    //创建单选按钮的操作连接
    connect(
                radio_admin,
                SIGNAL(toggled(bool)),
                this,
                SLOT(on_radio_admin())
                );
    connect(
                radio_stu,
                SIGNAL(toggled(bool)),
                this,
                SLOT(on_radio_stu())
                );
    radio_admin->setChecked(true);


    //添加按钮的布局
    button_layout = new QHBoxLayout;
    button_layout->addStretch();
    btn_login = new QPushButton("登录");
    btn_exit = new QPushButton("退出");
    btn_login->setFixedSize(120,60);
    btn_exit->setFixedSize(120,60);
    btn_login->setFont(ft);
    btn_exit->setFont(ft);
    button_layout->addWidget(btn_login);
    button_layout->addStretch();
    button_layout->addWidget(btn_exit);
    button_layout->addStretch();

    theLayout->addLayout(button_layout);

    this->setLayout(theLayout);//将theLayout设为当前窗口的总体布局

    //添加按钮的处理功能
    connect(
                btn_login,
                SIGNAL(clicked()),//发出单击信号
                this,
                SLOT(on_login())//指定接收信号的槽函数
                );
    connect(
                btn_exit,
                SIGNAL(clicked()),//发出单击信号
                this,
                SLOT(on_exit())//指定接收信号的槽函数
                );
}


void QtLogin::on_login()//登录操作的槽函数
{
   // QMessageBox::information(this,"提示","您已进入登录界面！",QMessageBox::Ok);
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QODBC");

        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("PMB");
        db.setUserName("root");
        db.setPassword("liuzhao201414");

     if(!db.open())//打开失败
     {
        QMessageBox::critical(this,"错误","打开数据库失败！",QMessageBox::Ok);
        return;
     }

     QString user_name = edit_user->text();//获得编辑框中用户名文本
     QString user_pwd = edit_pwd->text();
     //检查数据库中是否有对应用户名和密码的存在
     QSqlQuery* query = new QSqlQuery(db);
     QString str_type = "1";
     if(radio_admin->isChecked())//管理员登录
     {
         str_type = "1";
     }
     else
     {
         str_type = "0";//学生登录
     }

    QString str_sql =  QString("select * from users where username = '%1' and password = '%2' and type = '%3' ").arg(
                user_name,
                user_pwd,
                str_type
                );
      //%1,%2,%3以及.arg（）的作用是将arg的参数按顺序填入之前的3个占位符，拼接成完整的字符


    if(!query->exec(str_sql))
    {//执行sql语句失败
       QMessageBox::critical(this,"错误","执行查询失败！",QMessageBox::Ok);
        return;
    }

    //执行成功继续分析结果
    if(query->next())
    {//有记录存在
        if(query->next())//多于一条记录
        {

            QMessageBox::warning(this,tr("警告！"),tr("用户名或密码或身份错误！"),QMessageBox::Yes);
            //清空输入框内容
            edit_user->clear();
           edit_pwd->clear();
            //光标定位
            edit_user->setFocus();
        }
        else
        {//查询结果一行则用户名密码匹配
            query->first();
            QMessageBox::information(this,"提示","登录成功!");
            WriteInit("username",user_name);
            WriteInit("password",user_pwd);
            db.close();
            accept();//关闭窗体(对话框），返回值为accepted
        }

    }
    else
    {
        QMessageBox::warning(this,tr("警告！"),tr("用户名或密码或身份错误！"),QMessageBox::Yes);
        //清空输入框内容
        edit_user->clear();
        edit_pwd->clear();
        //光标定位
        edit_user->setFocus();
    }
}

//将用户名和密码写入到配置文件中
void QtLogin::WriteInit(QString key, QString value){
    QString path="QtLogin.ini";
    QSettings *config = new QSettings(path,QSettings::IniFormat);
    QVariant variant;
    variant.setValue(value);
    //将信息写入到配置文件中
    config->beginGroup("config");
    config->setValue(key,variant);
    config->endGroup();
    delete config;
}

void QtLogin::on_exit()
{
    this->close();
}

void QtLogin::on_radio_admin()
{
   // qDebug()<<"0";
}

void QtLogin::on_radio_stu()
{
    // qDebug()<<"1";
}
