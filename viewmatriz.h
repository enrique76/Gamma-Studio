#ifndef VIEWMATRIZ_H
#define VIEWMATRIZ_H

#include <QWidget>
#include"matriz.h"
#include<QTableWidgetItem>
#include<QMenu>
#include<QAction>
#include<QCompleter>

namespace Ui {
class viewMatriz;
}

class viewMatriz : public QWidget
{
    Q_OBJECT

public:
    explicit viewMatriz(QWidget *parent = nullptr);
    ~viewMatriz();
    void Crear(Matriz *m);
    void Redibujar(Matriz *m);
    void setValor(int f,int c, QString v);
    void PasarVariables(QStringList l);
    QPixmap* CrearImagen();
    void setFont(QFont f);
    void setColor(QString c);
    void setHLabes(QStringList l);
    void setVLabes(QStringList l);
    void GuardarMatriz(QString ruta);
private slots:
    void on_matriz_cellPressed(int row, int column);

    void on_matriz_cellDoubleClicked(int row, int column);

    void on_matriz_itemChanged(QTableWidgetItem *item);

    void on_matriz_customContextMenuRequested(const QPoint &pos);


    void on_matriz_itemDoubleClicked(QTableWidgetItem *item);


private:
    Ui::viewMatriz *ui;
    QList<double> seleccionados;
    Matriz *m;
    bool c = false;
    QMenu *menu = new QMenu();
    QCompleter *co;
    QStringList *lista;

};

#endif // VIEWMATRIZ_H
