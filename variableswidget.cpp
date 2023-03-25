#include "variableswidget.h"
#include "ui_variableswidget.h"
#include<iostream>
#include<QMessageBox>
#include<QCompleter>
#include<QPushButton>
#include<QFile>
#include<QTextStream>
#include<QFileDialog>

using namespace std;

VariablesWidget::VariablesWidget(QWidget *parent) :QWidget(parent),ui(new Ui::VariablesWidget){
    ui->setupUi(this);

    ui->progressBar->setVisible(false);

    QStringList lm;

    lm << "m" << "s" << "kg" << "k" << "A" << "cd" << "mol";

    QCompleter *c = new QCompleter(lm,this);

    ui->unidades->setCompleter(c);

    ui->unidadesMedida->addItems(lm);

    p = new QSortFilterProxyModel(this);
    p->setSourceModel(this->model);
    p->setFilterCaseSensitivity(Qt::CaseInsensitive);

}

VariablesWidget::~VariablesWidget(){
    delete ui;
}





void VariablesWidget::PasarInformacion(QTreeWidgetItem *item){
    this->arbol = item;

}

void VariablesWidget::CargarVariables(){
    db.setDatabaseName(QDir::currentPath()+"/db.db");



    if(!db.open()){
        qDebug()<<"No se pudo abri la base de datos";

        return;
    }

    q->prepare(query);

    q->exec();

    model->setQuery(*q);

    ui->tabla->setModel(model);

    ui->tabla->resizeColumnsToContents();

    for(int i=0;i<ui->tabla->model()->rowCount();i++){
        QString simbolo = ui->tabla->model()->index(i,1).data().toString();
        QString unidad = ui->tabla->model()->index(i,3).data().toString();

        QTreeWidgetItem *item = new QTreeWidgetItem();

        item->setText(0,simbolo+"["+unidad+"]");
        item->setIcon(0,this->arbol->icon(0));

        this->arbol->addChild(item);
    }


}

void VariablesWidget::Vaciar(){
    ui->nombre->setText("");
    ui->simbolo->setText("");
    ui->valor->setText("");
    ui->unidades->setText("");
    ui->comentarios->setText("");
}



void VariablesWidget::on_agregar_clicked(){
    QString nombre = ui->nombre->text();
    QString simbolo = ui->simbolo->text();
    QString valor = ui->valor->text();
    QString unidad = ui->unidades->text();
    QString comentario = ui->comentarios->toPlainText();

    q->prepare("SELECT EXISTS (SELECT * FROM variables WHERE nombre = '"+nombre+"');");

    q->exec();



    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(*q);

    if(model->index(0,0).data().toInt()){
        QMessageBox::information(this,"Agregar Variable","Esta variable ya Existe");
    }
    else{

        q->prepare("INSERT INTO variables (nombre, simbolo, valor, unidad, comentario) VALUES(:nombre, :simbolo, :valor, :unidad, :comentario)");

        q->bindValue(":nombre", nombre);
        q->bindValue(":simbolo", simbolo);
        q->bindValue(":valor", valor);
        q->bindValue(":unidad", unidad);
        q->bindValue(":comentario", comentario);

        if(!q->exec()){
            QMessageBox::critical(this,"Agregar Variable",q->lastError().text());
        }

        q->prepare(this->query);

        if(!q->exec()){
            QMessageBox::critical(this,"Agregar Variable",q->lastError().text());
        }

        this->model->setQuery(*q);

        ui->tabla->setModel(this->model);

        ui->tabla->resizeColumnsToContents();

        QTreeWidgetItem *item = new QTreeWidgetItem();

        item->setText(0,simbolo+"["+unidad+"]");
        item->setIcon(0,this->arbol->icon(0));

        this->arbol->addChild(item);
    }

    Vaciar();

}



void VariablesWidget::on_editar_clicked(){
    QString nombre = ui->nombre->text();
    QString simbolo = ui->simbolo->text();
    QString valor = ui->valor->text();
    QString unidad = ui->unidades->text();
    QString comentario = ui->comentarios->toPlainText();

    q->prepare("SELECT EXISTS (SELECT * FROM variables WHERE nombre = :nombre);");

    q->bindValue(":nombre", nombre);

    if(!q->exec()){
        QMessageBox::critical(this,"Editar Variable",q->lastError().text());
    }

    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery(*q);

    if(model->index(0,0).data().toInt()){
        q->prepare("UPDATE variables SET simbolo = :simbolo, valor = :valor, unidad = :unidad, comentario = :comentario WHERE nombre = :nombre");
    }
    else{
        QMessageBox::critical(this,"Editar Variable","Esta variable no existe");
        Vaciar();
        return;
    }

    q->bindValue(":nombre", nombre);
    q->bindValue(":simbolo", simbolo);
    q->bindValue(":valor", valor);
    q->bindValue(":unidad", unidad);
    q->bindValue(":comentario", comentario);

    if(!q->exec()){
        QMessageBox::critical(this,"Editar Variable",q->lastError().text());
    }

    q->prepare(this->query);

    if(!q->exec()){
        QMessageBox::critical(this,"Editar Variable",q->lastError().text());
    }

    this->model->setQuery(*q);

    ui->tabla->setModel(this->model);

    ui->tabla->resizeColumnsToContents();

    Vaciar();
}


void VariablesWidget::on_eliminar_clicked(){
    QString nombre = ui->nombre->text();
    QSqlQuery *q = new QSqlQuery(db);

    q->prepare("SELECT EXISTS (SELECT * FROM variables WHERE nombre = :nombre);");
    q->bindValue(":nombre", nombre);

    if(!q->exec()){
        QMessageBox::critical(this,"Eliminar Variable",q->lastError().text());
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(*q);

    if(model->index(0,0).data().toInt()){
        q->prepare("DELETE FROM variables WHERE nombre = :nombre");
    }
    else{
        QMessageBox::critical(this,"Eliminar Variable","Esta variable no existe");
        Vaciar();
        return;
    }

    q->bindValue(":nombre", nombre);

    if(!q->exec()){
        QMessageBox::critical(this,"Eliminar Variable",q->lastError().text());
    }



    if(!q->exec()){
        QMessageBox::critical(this,"Eliminar Variable",q->lastError().text());
    }

    this->model->setQuery(*q);

    ui->tabla->setModel(this->model);

    ui->tabla->resizeColumnsToContents();

    Vaciar();

}


void VariablesWidget::on_buscar_textChanged(const QString &arg1){
    if(ui->buscar->text().isEmpty()){
        this->model->setQuery(*q);

        ui->tabla->setModel(this->model);

        ui->tabla->resizeColumnsToContents();
        ui->tabla->setStyleSheet("QTableView::item:selected { background-color: white; }");
        ui->tabla->clearSelection();
    }
    else{

        ui->tabla->setModel(this->p);

        QRegularExpression regex(arg1, QRegularExpression::CaseInsensitiveOption);
            p->setFilterRegularExpression(regex);
           // Encontrar la fila filtrada correspondiente en el QTableView
           QModelIndexList matchingIndexes = p->match(p->index(0, 0), Qt::DisplayRole, arg1, 1, Qt::MatchContains);
           if (!matchingIndexes.isEmpty()) {
               QModelIndex matchingIndex = matchingIndexes.first();
               int matchingRow = matchingIndex.row();

               // Resaltar la fila correspondiente en el QTableView
               ui->tabla->selectRow(matchingRow);
           } else {
               // Si no se encuentra ninguna fila filtrada, deseleccionar todas las filas
               ui->tabla->clearSelection();
           }

    }
}


void VariablesWidget::on_tabla_customContextMenuRequested(const QPoint &pos){


}

void VariablesWidget::on_tabla_cellDoubleClicked(int row, int column){

}


void VariablesWidget::on_unidadesMedida_currentTextChanged(const QString &arg1){

}




void VariablesWidget::on_tabla_doubleClicked(const QModelIndex &index){
    QString nombre = index.model()->index(index.row(),0).data().toString();
    QString simbolo = index.model()->index(index.row(),1).data().toString();
    QString valor = index.model()->index(index.row(),2).data().toString();
    QString unidad = index.model()->index(index.row(),3).data().toString();
    QString comentario = index.model()->index(index.row(),4).data().toString();

    ui->nombre->setText(nombre);
    ui->simbolo->setText(simbolo);
    ui->valor->setText(valor);
    ui->unidades->setText(unidad);
    ui->comentarios->setText(comentario);
}


void VariablesWidget::on_buscar_editingFinished(){

    if(ui->buscar->text().isEmpty()){


        this->model->setQuery(*q);

        ui->tabla->setModel(this->model);

        ui->tabla->resizeColumnsToContents();

        ui->tabla->setStyleSheet("QTableView::item:selected { background-color: white; }");
        ui->tabla->clearSelection();

    }
    else{
//        // Obtener el modelo subyacente del QTableView
//        QAbstractItemModel *model = ui->tabla->model();

//        // Obtener el número de filas y columnas del modelo
//        int rowCount = model->rowCount();
//        int columnCount = model->columnCount();

//        // Obtener el texto del QLineEdit
//        QString searchStr = ui->buscar->text();

//        // Iterar sobre todas las filas y columnas del modelo
//        for (int row = 0; row < rowCount; ++row) {
//            for (int col = 0; col < columnCount; ++col) {
//                // Obtener el ítem en la celda actual
//                QModelIndex index = model->index(row, col);
//                QString cellText = index.data().toString();

//                // Comparar el texto de la celda actual con el texto del QLineEdit
//                if (cellText.contains(searchStr, Qt::CaseInsensitive)) {
//                    for (int i = 0; i < columnCount; ++i) {
//                        QModelIndex idx = model->index(row, i);
//                        ui->tabla->setStyleSheet(QString("QTableView::item:selected { background-color: rgb(51, 255, 51);color: black; }"));
//                        ui->tabla->selectionModel()->select(idx, QItemSelectionModel::Select);
//                    }

//                    // Enfocar la fila correspondiente al dato encontrado
//                    ui->tabla->setCurrentIndex(index);
//                    //return;
//                }
//            }
//        }
    }
}

