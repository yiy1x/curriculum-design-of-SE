#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"changemima.h"
#include"stuguanli.h"
#include"searchstu.h"
#include"searchapart.h"
#include"searchtiwen.h"
#include"searchbaoxiu.h"
#include"searchbaoxiu_2.h"
#include"searchbaoxiu_3.h"
#include<QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();
private slots:

    void on_pushButton_mima_clicked();

    void on_pushButton_stuGM_clicked();

    void on_pushButton_searchStu_clicked();

   void on_pushButton_searchApart_clicked();

    void on_pushButton_searchTiwen_clicked();

    void slotpwd(QString o_pwd,QString n_pwd);



    void on_pushButton_searchTiwen_2_clicked();

    void on_pushButton_searchTiwen_3_clicked();

    void on_pushButton_searchTiwen_4_clicked();

private:
    Ui::MainWindow *ui;
    changeMiMa * MiMa_UI;
    stuGuanLi * GuanLi_UI;
    searchStu * ser_Stu_UI;
    searchApart * ser_Apart_UI;
    searchTiWen * ser_Tiwen_UI;
    searchbaoxiu* ser_baoxiu_UI;
    searchbaoxiu_2* ser_baoxiu2_UI;
    searchbaoxiu_3* ser_baoxiu3_UI;

    void initResetPwd();
    changeMiMa* rpwd;

    void ReadInit(QString key,QString &value);
    void loadcfg();
    bool connectDB();


    QString username;
    QString passwd;
    QSqlDatabase m_db;
};
#endif // MAINWINDOW_H
