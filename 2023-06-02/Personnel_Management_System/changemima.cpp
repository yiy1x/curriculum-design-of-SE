#include "changemima.h"
#include "ui_changemima.h"
#include<QMessageBox>

changeMiMa::changeMiMa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeMiMa)
{
    ui->setupUi(this);
}

changeMiMa::~changeMiMa()
{
    delete ui;
}

void changeMiMa::on_pushButton_close_clicked()
{
    ui->o_pwd->clear();
    ui->n_pwd->clear();
    ui->rn_pwd->clear();
    ui->o_pwd->setFocus();//光标指向原密码
   // this->clear();
}

void changeMiMa::on_pushButton_ok_clicked()
{
    o_pwd =  ui->o_pwd->text();
    n_pwd = ui->n_pwd->text();
    rn_pwd = ui->rn_pwd->text();
    if(o_pwd.isEmpty() || n_pwd.isEmpty() || rn_pwd.isEmpty()){
        QMessageBox::critical(this,"错误","密码不能为空");
        return;
    }
    if(n_pwd != rn_pwd){
        QMessageBox::critical(this,"错误","两次输入的新密码不一致");
        return;
    }
    if(o_pwd == n_pwd)
    {
        QMessageBox::critical(this,"错误","新密码和旧密码不能相同");
        return;
    }
    emit sigpwd(o_pwd,n_pwd);
}
