// Yunus Emre Ay - 21100011016

#include "oduncteslimetmeislemleri.h"
#include "ui_oduncteslimetmeislemleri.h"

Oduncteslimetmeislemleri::Oduncteslimetmeislemleri(QSqlDatabase DB,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Oduncteslimetmeislemleri)
{
    ui->setupUi(this);
    listele();
}

Oduncteslimetmeislemleri::~Oduncteslimetmeislemleri()
{
    delete ui;

}

void Oduncteslimetmeislemleri::listele()
{
    model1=new QSqlTableModel();
    model1->setTable("odunc_alinan");
    model1->select();
    ui->tableView_odunc->setModel(model1);

    model2=new QSqlTableModel();
    model2->setTable("odunc_teslim_edilen");
    model2->select();
    ui->tableView_onceden_odunc->setModel(model2);
}

void Oduncteslimetmeislemleri::on_tableView_odunc_clicked(const QModelIndex &index)
{
    ui->lineEdit_UyeNo->setText(model1->index(index.row(),0).data().toString());
    ui->lineEdit_KitapN->setText(model1->index(index.row(),1).data().toString());
}


void Oduncteslimetmeislemleri::on_OduncAl_clicked()
{
    QSqlQuery sorgu1, sorgu2, sorgu3;
    QString odunc_alma_tarihi;
    int borc, teslim_etme_gun, odunc_alma_gun;

    sorgu1.prepare("select odunc_alma_tarihi from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu1.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    sorgu1.addBindValue(ui->lineEdit_KitapN->text().toInt());
    if(!sorgu1.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu1.lastError().text(),"OK");
    }
    sorgu1.next();
    odunc_alma_tarihi = sorgu1.value(0).toString();


    odunc_alma_gun = odunc_alma_tarihi.split(".")[0].toInt()+ odunc_alma_tarihi.split(".")[1].toInt()*30 + odunc_alma_tarihi.split(".")[2].toInt()*365;
    teslim_etme_gun = ui->dateEdit->text().split(".")[0].toInt()+ ui->dateEdit->text().split(".")[1].toInt()*30 + ui->dateEdit->text().split(".")[2].toInt()*365;

    if(teslim_etme_gun - odunc_alma_gun < 15)
    {
        borc = 0;
    }
    else
    {
        borc = ((teslim_etme_gun - odunc_alma_gun)-15)*2;
    }

    sorgu2.prepare("insert into odunc_teslim_edilen values(?,?,?,?,?)");
    sorgu2.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    sorgu2.addBindValue(ui->lineEdit_KitapN->text().toInt());
    sorgu2.addBindValue(odunc_alma_tarihi);
    sorgu2.addBindValue(ui->dateEdit->text());
    sorgu2.addBindValue(borc);
    if(!sorgu2.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu2.lastError().text(),"OK");
    }



    sorgu3.prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu3.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    sorgu3.addBindValue(ui->lineEdit_KitapN->text().toInt());
    if(!sorgu3.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu3.lastError().text(),"OK");
    }

    listele();
}

