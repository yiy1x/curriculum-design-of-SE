#ifndef STU_MAINWINDOW_H
#define STU_MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include"changemima.h"
#include<QSqlDatabase>
#include"stu_stuinfo.h"
#include"stu_apartinfo.h"
#include"stu_tiwen.h"
#include"stu_baoxiu1.h"
#include"stu_baoxiu2.h"

namespace Ui {
class stu_mainwindow;
}

class stu_mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit stu_mainwindow(QWidget *parent = nullptr);
    ~stu_mainwindow();
    void initUI();

private slots:
    void slotpwd(QString o_pwd,QString n_pwd);

    void on_pushButton_mima_clicked();

    void on_pushButton_searchStu_clicked();

    void on_pushButton_searchApart_clicked();

    void on_pushButton_searchTiwen_clicked();

    void on_pushButton_searchTiwen_2_clicked();

    void on_pushButton_searchTiwen_3_clicked();

private:
    Ui::stu_mainwindow *ui;
    void initResetPwd();
    changeMiMa * MiMa_UI;
    changeMiMa* rpwd;
    stu_stuinfo* stuinfo_UI;
    stu_apartinfo* apartinfo_UI;
    stu_tiwen* tiwen_UI;
    stu_baoxiu1* baoxiu1_UI;
    stu_baoxiu2* baoxiu2_UI;


    void ReadInit(QString key,QString &value);
    void loadcfg();
    bool connectDB();
    bool stu_info_connect;
    bool apart_info_connect;

    QString username;
    QString passwd;
    QSqlDatabase m_db;
};

#endif // STU_MAINWINDOW_H
