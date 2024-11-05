// Yunus Emre Ay - 21100011016

#include "kitapislemleri.h"
#include "ui_kitapislemleri.h"

Kitapislemleri::Kitapislemleri(QSqlDatabase DB,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Kitapislemleri)
{
    ui->setupUi(this);
    listele();
}

Kitapislemleri::~Kitapislemleri()
{
    delete ui;
}

void Kitapislemleri::listele()
{
    model=new QSqlTableModel();
    model->setTable("kitap");
    model->select();
    ui->tableView_kitap->setModel(model);
}

void Kitapislemleri::on_tableView_kitap_clicked(const QModelIndex &index)
{
    ui->lineEdit_KitapNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_Ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_Stok->setText(model->index(index.row(),2).data().toString());

    QSqlQuery sorgu1;
    QSqlQuery sorgu2;
    QSqlQueryModel *sorgu_model1=new QSqlQueryModel();
    QSqlQueryModel *sorgu_model2=new QSqlQueryModel();



    sorgu1.prepare("select * from odunc_alinan where kitap_no=?");
    sorgu1.addBindValue(ui->lineEdit_KitapNo->text().toInt());
    if(!sorgu1.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu1.lastError().text(),"OK");
    }
    sorgu_model1->setQuery(sorgu1);
    ui->tableView_odunc->setModel(sorgu_model1);



    sorgu2.prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu2.addBindValue(ui->lineEdit_KitapNo->text().toInt());
    if(!sorgu2.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu2.lastError().text(),"OK");
    }
    sorgu_model2->setQuery(sorgu2);
    ui->tableView_onceden_odunc->setModel(sorgu_model2);


}


void Kitapislemleri::on_pushButton_clicked()
{
    if(ui->lineEdit_Ad->text() == "" | ui->lineEdit_Stok->text() == "")
    {
        QMessageBox::critical(this,"ERROR!","Gerekli alanları doldurunuz","OK");
        return;
    }

    QSqlQuery sorgu;
    sorgu.prepare("insert into kitap (kitap_ad,kitap_sayisi) values (?,?)");
    sorgu.addBindValue(ui->lineEdit_Ad->text());
    sorgu.addBindValue(ui->lineEdit_Stok->text());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}


void Kitapislemleri::on_pushButton_2_clicked()
{
    QSqlQuery sorgu;
    sorgu.prepare("update kitap set kitap_ad=?, kitap_sayisi=? where kitap_no=?");
    sorgu.addBindValue(ui->lineEdit_Ad->text());
    sorgu.addBindValue(ui->lineEdit_Stok->text());
    sorgu.addBindValue(ui->lineEdit_KitapNo->text());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}


void Kitapislemleri::on_pushButton_3_clicked()
{
    QSqlQuery sorgu;
    sorgu.prepare("select * from odunc_alinan where kitap_no=?");
    sorgu.addBindValue(ui->lineEdit_KitapNo->text().toInt());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }

    int sayac = 0;
    while(sorgu.next())
        sayac++;


    if(sayac>0)
    {
        QMessageBox::critical(this,"ERROR!","Bu kitap silinemez! Bu kitap bir üyeye ödünç verilmiştir.","OK");
        return;
    }

    sorgu.prepare("delete from kitap where kitap_no=?");
    sorgu.addBindValue(ui->lineEdit_KitapNo->text().toInt());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}

