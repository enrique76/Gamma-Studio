#ifndef MATRICESWIDGET_H
#define MATRICESWIDGET_H

#include <QWidget>

namespace Ui {
class MatricesWidget;
}

class MatricesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatricesWidget(QWidget *parent = nullptr);
    ~MatricesWidget();

private:
    Ui::MatricesWidget *ui;
};

#endif // MATRICESWIDGET_H
