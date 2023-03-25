#ifndef FUNCIONESWIDGET_H
#define FUNCIONESWIDGET_H

#include <QWidget>

namespace Ui {
class FuncionesWidget;
}

class FuncionesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FuncionesWidget(QWidget *parent = nullptr);
    ~FuncionesWidget();

private:
    Ui::FuncionesWidget *ui;
};

#endif // FUNCIONESWIDGET_H
