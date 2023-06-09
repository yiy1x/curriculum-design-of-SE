#ifndef STU_YICHANG_H
#define STU_YICHANG_H

#include <QDialog>
#include"stu_tiwen.h"

namespace Ui {
class stu_yichang;
}

class stu_yichang : public QDialog
{
    Q_OBJECT

public:
    explicit stu_yichang(QWidget *parent = nullptr);
    ~stu_yichang();

private slots:

    void on_insert_pushButton_clicked();

    void on_insert_pushButton_2_clicked();

private:
    Ui::stu_yichang *ui;
};

#endif // STU_YICHANG_H
