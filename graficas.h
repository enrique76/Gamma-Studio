#ifndef GRAFICAS_H
#define GRAFICAS_H

#include <QWidget>
#include<QTreeWidgetItem>

namespace Ui {
class Graficas;
}

class Graficas : public QWidget
{
    Q_OBJECT

public:
    explicit Graficas(QWidget *parent = nullptr);
    ~Graficas();
    void PasarArbolMatrices(QTreeWidgetItem *ArbolMatrices);
    void PasarItem(QTreeWidgetItem* item);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Graficas *ui;
    QTreeWidgetItem* ArbolMatrices;
    QTreeWidgetItem* item;
};

#endif // GRAFICAS_H
