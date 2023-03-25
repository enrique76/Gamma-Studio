#include "etiquetas.h"
#include "ui_etiquetas.h"
#include<QMessageBox>

etiquetas::etiquetas(QWidget *parent) :QDialog(parent),ui(new Ui::etiquetas){
    ui->setupUi(this);

}

etiquetas::~etiquetas(){
    delete ui;
}

bool etiquetas::Automatico(){
    return this->automatico;
}

bool etiquetas::Cambio(){
    return this->cambio;
}

QString etiquetas::Filas(){
    return ui->filas->text();
}

QString etiquetas::Columnas(){
    return ui->columnas->text();
}

QString etiquetas::Caracter(){
    return ui->caracter->text();
}

QString etiquetas::Separador(){
    return ui->separador->text();
}

int etiquetas::Incremento(){
    return ui->incremento->text().toInt();
}

void etiquetas::on_separadorOpcciones_currentTextChanged(const QString &arg1){
    ui->separador->setText(arg1);
}


void etiquetas::on_tabWidget_currentChanged(int index){
    if(index == 0){
        this->automatico = true;
    }
    else{
        this->automatico = false;
    }
}


void etiquetas::on_buttonBox_accepted(){
    int index = ui->tabWidget->currentIndex();

    if(index == 0){
        if(ui->caracter->text().isEmpty()){
            QMessageBox::critical(this,"Creacion de Caracteres Automaticos","Debes de agregar un caracter");
        }
        else{
            this->cambio = true;
            close();
        }
    }
    else if(index == 1){
        if(!ui->filas->text().isEmpty() && !ui->columnas->text().isEmpty() && !ui->separador->text().isEmpty()){
            QString t = ui->separador->text();
            int f = ui->filas->text().count(t);
            int c = ui->columnas->text().count(t);
            if((f > 0 && c > 0) && (f == c)){
                this->cambio = true;
                close();
            }
            else{
                QMessageBox::critical(this,"Creacion de Caracteres Manual",t+" no se encuentra en \n\n" + ui->filas->text() + "\n" + ui->columnas->text() + "\n\n\n O no las mismas veces");
            }
        }
        else{
            QMessageBox::critical(this,"Creacion de Caracteres Manual","Faltan Campos por llenar");
        }
    }
}

