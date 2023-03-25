#include "nuevoproyecto.h"
#include "ui_nuevoproyecto.h"
#include<QFileDialog>
#include<QMessageBox>
#include<QFont>
#include<QFontDialog>
#include<QColor>
#include<QColorDialog>


NuevoProyecto::NuevoProyecto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuevoProyecto)
{
    ui->setupUi(this);


    // completer


    QFileSystemModel *m = new QFileSystemModel(this);
    QCompleter *c = new QCompleter(m,this);

    m->setRootPath(QDir::rootPath());

    ui->ruta->setCompleter(c);

    ui->baseOpccionesAvanzadas->setVisible(false);



   //this->setGeometry(this->x,this->y,(this->width()-ui->baseOpccionesAvanzadas->width()),this->height());

    this->adjustSize();


}

NuevoProyecto::~NuevoProyecto()
{
    delete ui;
}

bool NuevoProyecto::GetOk(){
    return this->ok;
}

QString NuevoProyecto::getNombreMatriz(){
    return ui->matriz->text();
}

int NuevoProyecto::getFilas(){
    return ui->filas->value();
}

int NuevoProyecto::getColumnas(){
    return ui->columnas->value();
}

void NuevoProyecto::setEstado(bool t){
    ui->nombreProyecto->setVisible(t);
    ui->label_4->setVisible(t);
    ui->ruta->setVisible(t);
    ui->buscarRuta->setVisible(t);
    ui->label->setVisible(t);

    this->proyecto = t;
}

QString NuevoProyecto::getNombreProyecto(){
    return ui->nombreProyecto->text();
}

QString NuevoProyecto::getRuta(){
    return ui->ruta->text();
}

bool NuevoProyecto::OpccionesAvanzadas(){
    return ui->opccionesAvanzadas->isChecked();
}

bool NuevoProyecto::LlenarDe0(){
    return ui->llenar0->isChecked();
}

bool NuevoProyecto::LlenarDe1()
{
    return ui->llenar1->isChecked();
}

bool NuevoProyecto::LlenarDe(){
    return ui->llenarDe->isChecked();
}

bool NuevoProyecto::MatrizIdentidad()
{
    return ui->matrizIdentidad->isChecked();
}

bool NuevoProyecto::Aleatorio()
{
    return ui->aleatorio->isChecked();
}

int NuevoProyecto::Inferior(){
return ui->inferior->value();
}

int NuevoProyecto::Superior(){
return  ui->superior->value();
}

double NuevoProyecto::Aux(){
return ui->aux->value();
}

double NuevoProyecto::Valor(){
    return ui->valor->value();
}

QFont NuevoProyecto::Fuente(){
return ui->lineEdit->font();
}

QString NuevoProyecto::Color(){
    return ui->lineEdit->styleSheet();
}

void NuevoProyecto::on_buttonBox_accepted(){
    if(!ui->matriz->text().isEmpty() && !ui->ruta->text().isEmpty() && !ui->nombreProyecto->text().isEmpty() && this->proyecto){
        this->ok = true;

        close();
    }
    else if(!this->proyecto && !ui->matriz->text().isEmpty()){
        this->ok = true;

        close();
    }
    else{
        QMessageBox::critical(this,"Crear Proyecto","Faltan Datos \n \n \n  1. Nombre del proyecto \n 2. Nombre de la Matriz \n Ruta del proyecto \n \n \n  Son requeridos");
    }
}


void NuevoProyecto::on_buscarRuta_clicked(){
    ui->ruta->setText(QFileDialog::getExistingDirectory(this,"Guardar Proyecto en ...",QDir::homePath()));
}

void NuevoProyecto::on_pushButton_clicked(){
    bool ok;
    QFont fuente = QFontDialog::getFont(&ok);

    if(ok){
        ui->lineEdit->setFont(fuente);
    }
}


void NuevoProyecto::on_pushButton_2_clicked(){
    QColor c = QColorDialog::getColor(Qt::white, this, "Seleccionar color de fondo");

    ui->lineEdit->setStyleSheet(QString("background-color: %1").arg(c.name()));
}


void NuevoProyecto::on_inferior_valueChanged(int arg1){
    if(arg1 >= ui->superior->value()){
        QMessageBox::information(this,"Cambio de valor","El rango inferior no puede ser igual o superior al rango superior");
        ui->inferior->setValue(ui->superior->value()-1);
    }
}





void NuevoProyecto::on_opccionesAvanzadas_toggled(bool checked)
{
    ui->baseOpccionesAvanzadas->setVisible(checked);

    this->adjustSize();

    this->opccionesAvanzadas = checked;
}

void NuevoProyecto::on_llenarDe_toggled(bool checked){
   ui->valor->setEnabled(checked);
}


void NuevoProyecto::on_aleatorio_toggled(bool checked){
    ui->inferior->setEnabled(checked);
    ui->aux->setEnabled(checked);
    ui->superior->setEnabled(checked);
}

