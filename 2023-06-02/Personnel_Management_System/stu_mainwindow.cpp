#include "stu_mainwindow.h"
#include "ui_stu_mainwindow.h"
#include<QMessageBox>
#include <QSettings>
#include<QDebug>
#include<QSqlQuery>


stu_mainwindow::stu_mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::stu_mainwindow)
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
     stuinfo_UI = new stu_stuinfo();
     ui->stackedWidget->addWidget(stuinfo_UI);
     apartinfo_UI = new stu_apartinfo();
     ui->stackedWidget->addWidget(apartinfo_UI);
     tiwen_UI = new stu_tiwen();
     ui->stackedWidget->addWidget(tiwen_UI);
     baoxiu1_UI = new stu_baoxiu1();
     ui->stackedWidget->addWidget(baoxiu1_UI);

baoxiu2_UI = new stu_baoxiu2();
ui->stackedWidget->addWidget(baoxiu2_UI);
     rpwd = new changeMiMa();
     connect(rpwd,&changeMiMa::sigpwd,this,&stu_mainwindow::slotpwd);
    stu_info_connect = false;
    apart_info_connect = false;
     //修改密码
     initResetPwd();
}

stu_mainwindow::~stu_mainwindow()
{
    delete ui;
    delete MiMa_UI;
    delete stuinfo_UI;
    delete apartinfo_UI;
    delete tiwen_UI;
}

void stu_mainwindow::initUI()
{
    this->setWindowTitle("公司人事管理系统");
    setFixedSize(1600,800);//限制窗口大小
    this->setWindowIcon(QIcon(":/myImages/images/tubiao.png"));
}

void stu_mainwindow::ReadInit(QString key, QString &value){
    value.clear();
    QString path = "QtLogin.ini";
    QSettings *config = new QSettings(path,QSettings::IniFormat);
    //读取配置信息
    QVariant variant = config->value(QString("config/")+key);
    value=variant.value<QString>();
    delete config;
}
//从配置文件中读取用户名和密码
void stu_mainwindow::loadcfg(){
    ReadInit("username",username);
    ReadInit("password",passwd);
    qDebug()<<"  u and p"<<endl;
    qDebug() << username << passwd;
}
//链接数据库
bool stu_mainwindow::connectDB(){
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

void stu_mainwindow::slotpwd(QString o_pwd, QString n_pwd){
    if(o_pwd == passwd){
        QSqlQuery query;
        QString sql = QString("update users set password = '%2' where username = '%1'").arg(username).arg(n_pwd);
        query.exec(sql);
        QSqlDatabase::database().commit();
        passwd = n_pwd;
        qDebug()<<"  xin mi ma "<<endl;
        qDebug() << passwd;
        QMessageBox::information(this,"成功","恭喜您修改密码成功！");

        //delete MiMa_UI;
    }else {
        QMessageBox::critical(this,"错误","您输入的原密码错误");
        return;
    }
}


void stu_mainwindow::initResetPwd(){//修改密码

   connect(MiMa_UI,&changeMiMa::sigpwd,this,&stu_mainwindow::slotpwd);
}

void stu_mainwindow::on_pushButton_mima_clicked()
{
     ui->stackedWidget->setCurrentWidget(MiMa_UI);
}

void stu_mainwindow::on_pushButton_searchStu_clicked()
{
     ui->stackedWidget->setCurrentWidget(stuinfo_UI);
     if(!stu_info_connect)
     {
         stuinfo_UI->initUI(username);
         stu_info_connect = true;
     }
}

void stu_mainwindow::on_pushButton_searchApart_clicked()
{
    ui->stackedWidget->setCurrentWidget(apartinfo_UI);
    if(!apart_info_connect)
    {
        apartinfo_UI->tableReflash(username);
        apart_info_connect = true;
    }
}

void stu_mainwindow::on_pushButton_searchTiwen_clicked()
{
    ui->stackedWidget->setCurrentWidget(tiwen_UI);
    tiwen_UI->initUI(username);
}

void stu_mainwindow::on_pushButton_searchTiwen_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(baoxiu1_UI);
    baoxiu1_UI->initUI(username);
}


void stu_mainwindow::on_pushButton_searchTiwen_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(baoxiu2_UI);
    baoxiu2_UI->initUI(username);
    baoxiu2_UI->tableReflash();
}
