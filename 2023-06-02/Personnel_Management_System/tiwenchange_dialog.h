#ifndef TIWENCHANGE_DIALOG_H
#define TIWENCHANGE_DIALOG_H

#include <QDialog>

namespace Ui {
class TiWenchange_Dialog;
}

class TiWenchange_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit TiWenchange_Dialog(QWidget *parent = nullptr);
    ~TiWenchange_Dialog();
    // 通过体温表id字段值和体温字段值加载数据到修改界面
    void load(QString id,QString tiwen);

private slots:
    void on_update_pushButton_clicked();

private:
    Ui::TiWenchange_Dialog *ui;
    QString id;
    QString date;
};

#endif // TIWENCHANGE_DIALOG_H
