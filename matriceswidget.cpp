#include "matriceswidget.h"
#include "ui_matriceswidget.h"

MatricesWidget::MatricesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatricesWidget)
{
    ui->setupUi(this);
}

MatricesWidget::~MatricesWidget()
{
    delete ui;
}
