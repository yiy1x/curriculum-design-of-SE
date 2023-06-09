#ifndef INSERTWEIGHT_H
#define INSERTWEIGHT_H

#include <QWidget>

namespace Ui {
class insertWeight;
}

class insertWeight : public QWidget
{
    Q_OBJECT

public:
    explicit insertWeight(QWidget *parent = nullptr);
    ~insertWeight();

private:
    Ui::insertWeight *ui;
};

#endif // INSERTWEIGHT_H
