#ifndef NUEVOPROYECTO_H
#define NUEVOPROYECTO_H

#include <QDialog>
#include<QCompleter>
#include<QFileSystemModel>

namespace Ui {
class NuevoProyecto;
}

class NuevoProyecto : public QDialog
{
    Q_OBJECT

public:
    explicit NuevoProyecto(QWidget *parent = nullptr);
    ~NuevoProyecto();
    bool GetOk();
    QString getNombreMatriz();
    int getFilas();
    int getColumnas();
    void setEstado(bool t);
    QString getNombreProyecto();
    QString getRuta();
    bool OpccionesAvanzadas();
    bool LlenarDe0();
    bool LlenarDe1();
    bool LlenarDe();
    bool MatrizIdentidad();
    bool Aleatorio();

    int Inferior();
    int Superior();
    double Aux();
    double Valor();

    QFont Fuente();
    QString Color();


private slots:
    void on_buttonBox_accepted();

    void on_buscarRuta_clicked();



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_inferior_valueChanged(int arg1);


    void on_opccionesAvanzadas_toggled(bool checked);


    void on_llenarDe_toggled(bool checked);

    void on_aleatorio_toggled(bool checked);

private:
    Ui::NuevoProyecto *ui;
    bool ok = false;
    bool proyecto = true;
    bool opccionesAvanzadas = false;
};

#endif // NUEVOPROYECTO_H
