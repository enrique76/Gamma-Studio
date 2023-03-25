#include "viewmatriz.h"
#include "ui_viewmatriz.h"

#include<QDebug>
#include<QMessageBox>
#include<QTreeWidgetItem>
#include<QCompleter>
#include<QLineEdit>
#include<QFile>
#include<QTextStream>
#include <QStandardItemModel>
#include <QStandardItem>
#include<QtSql>

class HtmlCompleter : public QCompleter {
public:
    explicit HtmlCompleter(QObject* parent = nullptr)
        : QCompleter(parent)
    {
        setModel(new QStringListModel(this));
        setCompletionRole(Qt::DisplayRole);
        //setHtml(true);
    }

protected:
    QString pathFromIndex(const QModelIndex& index) const override {
        QString html = index.data(Qt::DisplayRole).toString();
        return "<html>" + html + "</html>";
    }

//    QModelIndexList splitPath(const QString& path) const {
//        QString plainText = QString(path).remove(QRegularExpression("<[^>]*>"));
//        return QCompleter::splitPath(plainText);
//    }
};



viewMatriz::viewMatriz(QWidget *parent) : QWidget(parent),ui(new Ui::viewMatriz){
    ui->setupUi(this);

    ui->matriz->setContextMenuPolicy(Qt::CustomContextMenu);

    QAction *actionAgregarVariable = new QAction("Agregar Variables",this->menu);

    actionAgregarVariable->setIcon(QIcon(":/new/prefix1/iconos/x.png"));

    this->menu->addAction(actionAgregarVariable);



}

viewMatriz::~viewMatriz()
{
    delete ui;
}

void viewMatriz::Crear(Matriz *m){
    ui->matriz->setRowCount(m->getFilas());
    ui->matriz->setColumnCount(m->getColumnas());

    for(int i=0;i<m->getFilas();i++){
        for(int j=0;j<m->getColumnas();j++){
            ui->matriz->setItem(i,j,new QTableWidgetItem(QString::number(m->getValor(i,j))));
        }
    }


    this->m = m;
    this->c = true;

}

void viewMatriz::Redibujar(Matriz *m){
    int f = m->getFilas();
    int c = m->getColumnas();

    if(f > ui->matriz->rowCount() || c > ui->matriz->columnCount()){
        ui->matriz->setRowCount(f);
        ui->matriz->setColumnCount(c);

        for(int i=0;i<f;i++){
            for(int j=0;j<c;j++){
                ui->matriz->setItem(i,j,new QTableWidgetItem(QString::number(m->getValor(i,j))));
            }
        }
    }
    else{
        ui->matriz->setRowCount(f);
        ui->matriz->setColumnCount(c);
    }

}

void viewMatriz::setValor(int f, int c, QString v){
    ui->matriz->item(f,c)->setText(v);

    on_matriz_itemChanged(ui->matriz->item(f,c));
}

void viewMatriz::PasarVariables(QStringList l){
    co = new QCompleter(l,this);
}

QPixmap* viewMatriz::CrearImagen(){
    QPixmap *p = new QPixmap(ui->matriz->size());

    this->render(p);

    return p;
}

void viewMatriz::setFont(QFont f){
    ui->matriz->setFont(f);
}

void viewMatriz::setColor(QString c){
    ui->matriz->setStyleSheet(c);
}

void viewMatriz::setHLabes(QStringList l){
    ui->matriz->setHorizontalHeaderLabels(l);
}

void viewMatriz::setVLabes(QStringList l){
    ui->matriz->setVerticalHeaderLabels(l);
}

void viewMatriz::GuardarMatriz(QString ruta){
    QFile m(ruta+"/"+QString::fromStdString(this->m->getNombre())+".txt");

    m.open(QFile::WriteOnly | QFile::Text);

    QTextStream out(&m);

    QString texto;

    for(int i=0;i<this->m->getFilas();i++){
        for(int j=0;j<this->m->getColumnas();j++){
            texto += QString::number(this->m->getValor(i,j))+",";
        }
        texto += "\n";
        out << texto;
        texto.clear();
    }

    m.flush();
    m.close();
}


void viewMatriz::on_matriz_cellPressed(int row, int column){
    for(int i=0;i<ui->matriz->rowCount();i++){
        for(int j=0;j<ui->matriz->columnCount();j++){
            ui->matriz->item(i,j)->setBackground(QColor(255,255,255)); // blanco
        }
    }

    if(ui->matriz->item(row,column)->background().color().name() != QColor(51,255,51).name()){
        for(int i=0;i<ui->matriz->columnCount();i++){
            ui->matriz->item(row,i)->setBackground(QColor(51,255,51));
        }

        for(int i=0;i<ui->matriz->rowCount();i++){
            ui->matriz->item(i,column)->setBackground(QColor(51,255,51));
        }
    }
}

void viewMatriz::on_matriz_cellDoubleClicked(int row, int column){
    for(int i=0;i<ui->matriz->rowCount();i++){
        for(int j=0;j<ui->matriz->columnCount();j++){
            ui->matriz->item(i,j)->setBackground(QColor(255,255,255));
        }
    }

    // crear el QLineEdit



    // saber cuantas variables tenemos
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery *q = new QSqlQuery(db);
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT nombre, simbolo, valor, unidad, comentario FROM variables;";

    db.setDatabaseName(QDir::currentPath()+"/db.db");



    if(!db.open()){
        qDebug()<<"No se pudo abri la base de datos";

        return;
    }else{
        qDebug()<<"Si se pudo";
    }

    q->prepare(query);

    q->exec();

    model->setQuery(*q);

    // Crear el QCompleter
       QCompleter* completer = new HtmlCompleter(this);
       completer->setCaseSensitivity(Qt::CaseInsensitive);
       completer->setFilterMode(Qt::MatchContains);

       // Agregar los datos al QCompleter con html
       QStringList dataList;
       for (int i = 0; i < model->rowCount(); i++) {
           QString nombre = model->record(i).value("nombre").toString();
           QString simbolo = model->record(i).value("simbolo").toString();
           QString valor = model->record(i).value("valor").toString();
           QString unidades = model->record(i).value("unidades").toString();

           QString html = "<font size='5'>" + nombre + "</font><br>"
                          "<font size='3'>" + simbolo+ "=" +valor + "[" + unidades + "]" + "</font>";
           dataList << html;
       }
       completer->setModel(new QStringListModel(dataList, completer));

       // Obtener el QLineEdit actual
       QTableWidgetItem* item = ui->matriz->item(row, column);
       QString text = item->text();

       // Verificar si el texto contiene un "="
       if (text.contains("=")) {
           // Cambiar el item por un QLineEdit
           QLineEdit* lineEdit = new QLineEdit(ui->matriz);
           lineEdit->setCompleter(completer);
           lineEdit->setText(text.mid(1));
           ui->matriz->setCellWidget(row, column, lineEdit);
           lineEdit->selectAll();
           lineEdit->setFocus();

           // Conectar el signal editingFinished() para guardar los datos en la base de datos
           connect(lineEdit, &QLineEdit::editingFinished, [this, model, lineEdit, row, column](){
               QString newValue = lineEdit->text();
               if (!newValue.isEmpty()) {
                   QString simbolo = model->record(row).value("simbolo").toString();
                   QString unidades = model->record(row).value("unidades").toString();
                   QString value = "=" + newValue + " " + simbolo + "[" + unidades + "]";
                   model->setData(model->index(row, 2), value);
               }
               ui->matriz->removeCellWidget(row, column);

               QTableWidgetItem* newItem = new QTableWidgetItem(newValue);
               ui->matriz->setItem(row, column, newItem);
           });
       } else {
           // Mostrar el QCompleter en el item actual
           QLineEdit* lineEdit = new QLineEdit(ui->matriz);
           lineEdit->setCompleter(completer);
           lineEdit->setText(text);
           ui->matriz->setCellWidget(row, column, lineEdit);
           lineEdit->selectAll();
           lineEdit->setFocus();

           // Conectar el signal editingFinished() para guardar los datos en la base de datos
           connect(lineEdit, &QLineEdit::editingFinished, [model, lineEdit, row, column, this](){
               QString newValue = lineEdit->text();
               if (!newValue.isEmpty()) {
                   QTableWidgetItem* newItem = new QTableWidgetItem(newValue);
                   ui->matriz->setItem(row, column, newItem);
                   model->setData(model->index(row, column), newValue);
               }
               ui->matriz->removeCellWidget(row, column);
           });
       }
}

void viewMatriz::on_matriz_itemChanged(QTableWidgetItem *item){
    if(this->c){
        int f = item->row();
        int c = item->column();

        if(ui->matriz->item(f,c)->text().toDouble() != this->m->getValor(f,c)){
            this->m->setValor(f,c,ui->matriz->item(f,c)->text().toDouble());
        }
    }
}

void viewMatriz::on_matriz_customContextMenuRequested(const QPoint &pos){
    if(ui->matriz->itemAt(pos) != nullptr){
        this->menu->exec(ui->matriz->mapToGlobal(pos));
    }
}

void viewMatriz::on_matriz_itemDoubleClicked(QTableWidgetItem *item){
    int f = item->row();
    int c = item->column();

    QString t = item->text();

    QLineEdit* editor = new QLineEdit();

    editor->setText(t);
    editor->setCompleter(co);
    ui->matriz->setCellWidget(f, c, editor);

    connect(editor, &QLineEdit::editingFinished, this,  [=](){
        ui->matriz->removeCellWidget(f,c);

        editor->text().removeFirst();

        if(!editor->text().isEmpty()){
            ui->matriz->setItem(f,c, new QTableWidgetItem(editor->text()));
        }
        else{
            ui->matriz->setItem(f,c, new QTableWidgetItem(t));
        }

    });
}




