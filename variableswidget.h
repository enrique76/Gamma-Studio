#ifndef VARIABLESWIDGET_H
#define VARIABLESWIDGET_H

#include <QWidget>
#include<QVector>
#include<QTreeWidgetItem>
#include<QMenu>
#include<QtSql>

namespace Ui {
class VariablesWidget;
}

struct datos{
    QString nombre,simbolo,valor,unidad,comentario;

    bool comparar(datos d){
        if(nombre == d.nombre && simbolo == d.simbolo && valor == d.valor && unidad == d.unidad && comentario == d.comentario){
            return true;
        }
        else{
            return false;
        }
    }

    void setNombre(QString nombre){
        this->nombre = nombre;
    }
};

class VariablesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VariablesWidget(QWidget *parent = nullptr);
    ~VariablesWidget();
    void PasarInformacion(QTreeWidgetItem *item);
    void CargarVariables();

    // inputs

    void Vaciar();


    // Agregar Variable, Editarla, Eliminarla, Actualizar


private slots:

    void on_buscar_textChanged(const QString &arg1);

    void on_tabla_customContextMenuRequested(const QPoint &pos);

    void on_agregar_clicked();

    void on_editar_clicked();

    void on_eliminar_clicked();

    void on_tabla_cellDoubleClicked(int row, int column);

    void on_unidadesMedida_currentTextChanged(const QString &arg1);

    void on_tabla_doubleClicked(const QModelIndex &index);

    void on_buscar_editingFinished();

private:
    Ui::VariablesWidget *ui;
    QVector<datos> d;
    QTreeWidgetItem *arbol;
    QMenu *m = new QMenu();
    int indexChild = 0;
    QString ruta;
    QStringList *listaVariables;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *q = new QSqlQuery(db);
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT nombre, simbolo, valor, unidad, comentario FROM variables;";
    QSortFilterProxyModel *p;
};

#endif // VARIABLESWIDGET_H
