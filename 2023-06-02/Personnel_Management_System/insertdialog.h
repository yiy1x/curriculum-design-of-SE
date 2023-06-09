#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class insertDialog;
}

class insertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit insertDialog(QWidget *parent = 0);
    ~insertDialog();

private slots:
    void on_insert_pushButton_clicked();

private:
    Ui::insertDialog *ui;
};

#endif // INSERTDIALOG_H
