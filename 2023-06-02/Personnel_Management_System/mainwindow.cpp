#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"changemima.h"//修改密码
#include"stuguanli.h"
#include"searchstu.h"
#include"searchapart.h"
#include"searchtiwen.h"
#include"searchbaoxiu.h"
#include"searchbaoxiu_2.h"
#include<QMessageBox>
#include <QSettings>
#include<QDebug>
#include<QSqlQuery>
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //读取用户登录时候输入的用户名和密码
    loadcfg();
    //链接数据库
    bool bl = connectDB();
    if(bl == false){
        QMessageBox::critical(this,"错误","链接数据库失败！");
        return;
    }
    initUI();//初始化主界面

    //加入堆栈窗口
     MiMa_UI = new changeMiMa();
     ui->stackedWidget->addWidget(MiMa_UI);
     GuanLi_UI = new stuGuanLi();
     ui->stackedWidget->addWidget( GuanLi_UI );

     ser_Stu_UI = new searchStu();
     ui->stackedWidget->addWidget(ser_Stu_UI);
     ser_Apart_UI = new searchApart();
     ui->stackedWidget->addWidget(ser_Apart_UI);

     ser_Tiwen_UI = new searchTiWen();
     ui->stackedWidget->addWidget(ser_Tiwen_UI);
     ser_baoxiu_UI = new searchbaoxiu();
     ui->stackedWidget->addWidget(ser_baoxiu_UI);
     ser_baoxiu2_UI = new searchbaoxiu_2();
     ui->stackedWidget->addWidget(ser_baoxiu2_UI);
     ser_baoxiu3_UI = new searchbaoxiu_3();
     ui->stackedWidget->addWidget(ser_baoxiu3_UI);

     rpwd = new changeMiMa();
     connect(rpwd,&changeMiMa::sigpwd,this,&MainWindow::slotpwd);

     //修改密码
     initResetPwd();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete MiMa_UI;
    delete GuanLi_UI;
    delete ser_Stu_UI;
    delete ser_Apart_UI;
    delete ser_Tiwen_UI;
}

void MainWindow::initUI()
{
    this->setWindowTitle("公司人事管理系统");
    setFixedSize(1600,800);//限制窗口大小
    this->setWindowIcon(QIcon(":/myImages/images/tubiao.png"));
}

void MainWindow::ReadInit(QString key, QString &value){
    value.clear();
    QString path = "QtLogin.ini";
    QSettings *config = new QSettings(path,QSettings::IniFormat);
    //读取配置信息
    QVariant variant = config->value(QString("config/")+key);
    value=variant.value<QString>();
    delete config;
}
//从配置文件中读取用户名和密码
void MainWindow::loadcfg(){
    ReadInit("username",username);
    ReadInit("password",passwd);
    qDebug()<<"u and p";
    qDebug() << username << passwd;
}
//链接数据库
bool MainWindow::connectDB(){
    m_db = QSqlDatabase::addDatabase("QODBC");
    //设置链接数据库的主机名，数据库名，用户名和密码
    m_db.setHostName("127.0.0.1");
    m_db.setPort(3306);
    m_db.setDatabaseName("PMB");
    m_db.setUserName("root");
    m_db.setPassword("liuzhao201414");
    if(m_db.open() == false){
        QMessageBox::critical(this,"ERROR","链接数据库失败");
        return false;
    }
    return true;
}




void MainWindow::initResetPwd(){//修改密码
    //connect(ui->reset_pwd,&QAction::triggered,this,[=](){
     //   rpwd = new changeMiMa(this);
     //   rpwd->show();
     //   connect(rpwd,&changeMiMa::sigpwd,this,&MainWindow::slotpwd);
   // });

   connect(MiMa_UI,&changeMiMa::sigpwd,this,&MainWindow::slotpwd);
}

void MainWindow::slotpwd(QString o_pwd, QString n_pwd){
    if(o_pwd == passwd){
        QSqlQuery query;
        QString sql = QString("update users set password = '%2' where username = '%1'").arg(username).arg(n_pwd);
        query.exec(sql);
        QSqlDatabase::database().commit();
        passwd = n_pwd;
        qDebug()<<"new password"<<endl;
        qDebug() << passwd;
        QMessageBox::information(this,"成功","恭喜您修改密码成功！");

        //delete MiMa_UI;
    }else {
        QMessageBox::critical(this,"错误","您输入的原密码错误");
        return;
    }
}

void MainWindow::on_pushButton_mima_clicked()
{
     ui->stackedWidget->setCurrentWidget(MiMa_UI);
}

void MainWindow::on_pushButton_stuGM_clicked()
{
    ui->stackedWidget->setCurrentWidget(GuanLi_UI);
}

void MainWindow::on_pushButton_searchStu_clicked()
{
     ui->stackedWidget->setCurrentWidget(ser_Stu_UI);
}

void MainWindow::on_pushButton_searchApart_clicked()
{
    ui->stackedWidget->setCurrentWidget(ser_Apart_UI);
}

void MainWindow::on_pushButton_searchTiwen_clicked()
{
     ui->stackedWidget->setCurrentWidget(ser_Tiwen_UI);
}

void MainWindow::on_pushButton_searchTiwen_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ser_baoxiu_UI);
    ser_baoxiu_UI->tableReflash();
}

void MainWindow::on_pushButton_searchTiwen_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ser_baoxiu2_UI);
    ser_baoxiu2_UI->tableReflash();
}

void MainWindow::on_pushButton_searchTiwen_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ser_baoxiu3_UI);
    ser_baoxiu3_UI->tableReflash();
}
