#ifndef STU_BAOXIU1_H
#define STU_BAOXIU1_H

#include <QWidget>

namespace Ui {
class stu_baoxiu1;
}

class stu_baoxiu1 : public QWidget
{
    Q_OBJECT

public:
    explicit stu_baoxiu1(QWidget *parent = nullptr);
    ~stu_baoxiu1();
    void initUI(QString id);

private slots:
    void on_pushButton_clicked();

private:
    Ui::stu_baoxiu1 *ui;
    QString id;
};

#endif // STU_BAOXIU1_H
