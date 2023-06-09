#ifndef SEARCHBAOXIU_3_H
#define SEARCHBAOXIU_3_H

#include <QWidget>

namespace Ui {
class searchbaoxiu_3;
}

class searchbaoxiu_3 : public QWidget
{
    Q_OBJECT

public:
    explicit searchbaoxiu_3(QWidget *parent = nullptr);
    ~searchbaoxiu_3();
    void tableReflash(QString selectSql = QString());//刷新表格

private slots:
    void on_pushButton_clicked();

private:
    Ui::searchbaoxiu_3 *ui;
    // 单元格设置
    void cellSetting(int row, int column, QString text);
};

#endif // SEARCHBAOXIU_3_H
