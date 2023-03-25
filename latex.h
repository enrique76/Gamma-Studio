#ifndef LATEX_H
#define LATEX_H

#include <QWidget>
#include<QTreeWidget>
#include"matriz.h"

namespace Ui {
class LaTex;
}

class LaTex : public QWidget
{
    Q_OBJECT

public:
    explicit LaTex(QWidget *parent = nullptr);
    ~LaTex();
    void PasarDatos(QList<QTreeWidgetItem *> d);
    void PasarMatrices(vector<Matriz *> m);
    void CrearCodigoLatex(int i);

private slots:
    void on_arbol_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::LaTex *ui;
    vector<Matriz *> m;
};

#endif // LATEX_H
