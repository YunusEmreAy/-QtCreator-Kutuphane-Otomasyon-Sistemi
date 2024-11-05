// Yunus Emre Ay - 21100011016

#include "oduncalmaislemleri.h"
#include "ui_oduncalmaislemleri.h"


Oduncalmaislemleri::Oduncalmaislemleri(QSqlDatabase DB,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Oduncalmaislemleri)
{
    ui->setupUi(this);

    listele();
}

Oduncalmaislemleri::~Oduncalmaislemleri()
{
    delete ui;
}

void Oduncalmaislemleri::listele()
{
    model1=new QSqlTableModel();
    model1->setTable("üye");
    model1->select();
    ui->tableView_uyeler->setModel(model1);

    model2=new QSqlTableModel();
    model2->setTable("kitap");
    model2->select();
    ui->tableView_kitaplar->setModel(model2);

    model3=new QSqlTableModel();
    model3->setTable("odunc_alinan");
    model3->select();
    ui->tableView_odunc->setModel(model3);
}

void Oduncalmaislemleri::on_tableView_uyeler_clicked(const QModelIndex &index)
{
    ui->lineEdit_UyeNo->setText(model1->index(index.row(),0).data().toString());
}


void Oduncalmaislemleri::on_tableView_kitaplar_clicked(const QModelIndex &index)
{
    ui->lineEdit_KitapN->setText(model2->index(index.row(),0).data().toString());
}


void Oduncalmaislemleri::on_OduncAl_clicked()
{
    QSqlQuery sorgu1, sorgu2, sorgu3, sorgu4;
    int sayac = 0, kitapSayisi = 0;

    sorgu1.prepare("select * from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu1.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    sorgu1.addBindValue(ui->lineEdit_KitapN->text().toInt());
    if(!sorgu1.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu1.lastError().text(),"OK");
    }

    while(sorgu1.next())
    {
        sayac++;
    }

    if(sayac>0)
    {
        QMessageBox::information(this,"HATA","Bu üye kitabın bir tanesini şu an ödünç almış tekrar ödünç verilemez!");
        return;
    }




    sorgu2.prepare("select * from odunc_alinan where kitap_no=?");
    sorgu2.addBindValue(ui->lineEdit_KitapN->text().toInt());
    if(!sorgu2.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu2.lastError().text(),"OK");
    }

    sayac=0;
    while(sorgu2.next())
    {
        sayac++;
    }


    sorgu3.prepare("select kitap_sayisi from kitap where kitap_no=?");
    sorgu3.addBindValue(ui->lineEdit_KitapN->text().toInt());
    if(!sorgu3.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu3.lastError().text(),"OK");
    }


    sorgu3.next();
    kitapSayisi = sorgu3.value(0).toInt();

    if(sayac==kitapSayisi)
    {
        QMessageBox::information(this,"HATA","Stokta bu kitap bulunmamaktadır!");
        return;
    }






    sorgu4.prepare("insert into odunc_alinan values (?,?,?)");
    sorgu4.addBindValue(ui->lineEdit_UyeNo->text());
    sorgu4.addBindValue(ui->lineEdit_KitapN->text());
    sorgu4.addBindValue(ui->dateEdit->text());

    if(!sorgu4.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu4.lastError().text(),"OK");
    }
    listele();
}

