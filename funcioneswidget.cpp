#include "funcioneswidget.h"
#include "ui_funcioneswidget.h"

FuncionesWidget::FuncionesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FuncionesWidget)
{
    ui->setupUi(this);
}

FuncionesWidget::~FuncionesWidget()
{
    delete ui;
}
