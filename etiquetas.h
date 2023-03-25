#ifndef ETIQUETAS_H
#define ETIQUETAS_H

#include <QDialog>

namespace Ui {
class etiquetas;
}

class etiquetas : public QDialog
{
    Q_OBJECT

public:
    explicit etiquetas(QWidget *parent = nullptr);
    ~etiquetas();
    bool Automatico();
    bool Cambio();
    QString Filas();
    QString Columnas();
    QString Caracter();
    QString Separador();
    int Incremento();


private slots:

    void on_separadorOpcciones_currentTextChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::etiquetas *ui;
    bool automatico = true;
    bool cambio = false;
};

#endif // ETIQUETAS_H
