#include "mywidget.h"
#include "ui_mywidget.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>

QString filename = "C:/contactbook/myfile.txt";

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->contactbook->setColumnCount(4);
    QStringList colTotal;
    colTotal<<"學號"<<"班級"<<"姓名"<<"電話";
    ui->contactbook->setHorizontalHeaderLabels(colTotal);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *col1,*col2,*col3,*col4;

    col1 = new QTableWidgetItem(ui->lineEdit_1->text());
    col2 = new QTableWidgetItem(ui->lineEdit_2->text());
    col3 = new QTableWidgetItem(ui->lineEdit_3->text());
    col4 = new QTableWidgetItem(ui->lineEdit_4->text());

    ui->contactbook->insertRow(ui->contactbook->rowCount());

    ui->contactbook->setItem(ui->contactbook->rowCount()-1,0,col1);
    ui->contactbook->setItem(ui->contactbook->rowCount()-1,1,col2);
    ui->contactbook->setItem(ui->contactbook->rowCount()-1,2,col3);
    ui->contactbook->setItem(ui->contactbook->rowCount()-1,3,col4);
}
void CbWrite(QString filename ,QString str){
    QFile outFile(filename);
    if(!outFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug();
        return;
    }
    QTextStream out(&outFile);
    out.setEncoding(QStringConverter::System);
    out<<str;
    outFile.flush();
    outFile.close();
}

void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"",".","csv(*.csv);;text(*.txt");

    for(int i=0;i<ui->contactbook->rowCount();i++){
        for(int j=0;j<ui->contactbook->columnCount();j++){
            if (ui->contactbook->item(i, j))
            {
                saveStr += ui->contactbook->item(i, j)->text();
            }
            if (j < 3)
            {
                saveStr += ",";
            }
        }
        saveStr+="\n";
    }
    CbWrite(fileName,saveStr);
}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"匯入通訊錄",".","CSV 檔案 (*.csv);;文字檔案 (*.txt)");
    QFile inFile(fileName);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug();
        return;
    }
    QTextStream in(&inFile);
    in.setEncoding(QStringConverter::System);
    ui->contactbook->setRowCount(0);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(',');
        if (line.trimmed().isEmpty())
        {
            continue;
        }
        if (data[0].trimmed() == "學號")
        {
            continue;
        }
        int row = ui->contactbook->rowCount();
        ui->contactbook->insertRow(row);
        for (int col = 0; col < 4; col++)
        {
            QTableWidgetItem *item =new QTableWidgetItem(data[col].trimmed());
            ui->contactbook->setItem(row, col, item);
        }
    }
}

