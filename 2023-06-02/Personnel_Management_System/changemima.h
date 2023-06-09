#ifndef CHANGEMIMA_H
#define CHANGEMIMA_H

#include <QWidget>

namespace Ui {
class changeMiMa;
}

class changeMiMa : public QWidget
{
    Q_OBJECT

public:
    explicit changeMiMa(QWidget *parent = nullptr);
    ~changeMiMa();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::changeMiMa *ui;
    QString o_pwd;
    QString n_pwd;
    QString rn_pwd;

signals:
    void sigpwd(QString o_pwd,QString n_pwd);
};

#endif // CHANGEMIMA_H
