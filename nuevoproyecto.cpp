#include "nuevoproyecto.h"
#include "ui_nuevoproyecto.h"

NuevoProyecto::NuevoProyecto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoProyecto)
{
    ui->setupUi(this);
}

NuevoProyecto::~NuevoProyecto()
{
    delete ui;
}

bool NuevoProyecto::GetOk(){
    return this->ok;
}

void NuevoProyecto::on_buttonBox_accepted()
{
    close();
}

