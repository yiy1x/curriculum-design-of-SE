#ifndef BAOXIU_1_H
#define BAOXIU_1_H

#include <QDialog>

namespace Ui {
class baoxiu_1;
}

class baoxiu_1 : public QDialog
{
    Q_OBJECT

public:
    explicit baoxiu_1(QWidget *parent = nullptr);
    ~baoxiu_1();
     void load(QString building,QString room,QString t_date);

private slots:
     void on_update_pushButton_clicked();

private:
    Ui::baoxiu_1 *ui;
};

#endif // BAOXIU_1_H
