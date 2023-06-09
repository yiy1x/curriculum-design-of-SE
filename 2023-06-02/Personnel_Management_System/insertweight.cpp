#include "insertweight.h"
#include "ui_insertweight.h"

insertWeight::insertWeight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insertWeight)
{
    ui->setupUi(this);
}

insertWeight::~insertWeight()
{
    delete ui;
}
