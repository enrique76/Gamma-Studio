#ifndef IMPORTAR_H
#define IMPORTAR_H

#include <QDialog>

namespace Ui {
class Importar;
}

class Importar : public QDialog
{
    Q_OBJECT

public:
    explicit Importar(QWidget *parent = nullptr);
    ~Importar();

private slots:
    void on_buttonBox_accepted();

    void on_buscarRuta_clicked();

    void on_ruta_editingFinished();

private:
    Ui::Importar *ui;
};

#endif // IMPORTAR_H
