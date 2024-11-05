// Yunus Emre Ay - 21100011016

#include "uyeislemleri.h"
#include "ui_uyeislemleri.h"

Uyeislemleri::Uyeislemleri(QSqlDatabase DB,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Uyeislemleri)
{
    ui->setupUi(this);

    listele();
}


Uyeislemleri::~Uyeislemleri()
{
    delete ui;
}


void Uyeislemleri::listele()
{
    model=new QSqlTableModel();
    model->setTable("üye");
    model->select();
    ui->tableView->setModel(model);
}


void Uyeislemleri::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_UyeNo->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_Uye_Ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_UyeSoyad->setText(model->index(index.row(),2).data().toString());
}



void Uyeislemleri::on_pushButton_clicked()
{
    if(ui->lineEdit_Uye_Ad->text() == "" | ui->lineEdit_UyeSoyad->text() == "")
    {
        QMessageBox::critical(this,"ERROR!","Gerekli alanları doldurunuz","OK");
        return;
    }

    QSqlQuery sorgu;
    sorgu.prepare("insert into üye (uye_Ad,uye_soyad) values (?,?)");
    sorgu.addBindValue(ui->lineEdit_Uye_Ad->text());
    sorgu.addBindValue(ui->lineEdit_UyeSoyad->text());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}


void Uyeislemleri::on_pushButton_2_clicked()
{
    QSqlQuery sorgu;
    sorgu.prepare("update üye set uye_Ad=?, uye_soyad=? where uye_no=?");
    sorgu.addBindValue(ui->lineEdit_Uye_Ad->text());
    sorgu.addBindValue(ui->lineEdit_UyeSoyad->text());
    sorgu.addBindValue(ui->lineEdit_UyeNo->text());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}


void Uyeislemleri::on_pushButton_3_clicked()
{
    QSqlQuery sorgu;
    sorgu.prepare("select * from odunc_alinan where uye_no=?");
    sorgu.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }

    int sayac = 0;
    while(sorgu.next())
        sayac++;


    if(sayac>0)
    {
        QMessageBox::critical(this,"ERROR!","Bu üye silinemez. Üyenin henüz teslim etmediği kitaplar vardır.","OK");
        return;
    }

    sorgu.prepare("delete from üye where uye_no=?");
    sorgu.addBindValue(ui->lineEdit_UyeNo->text().toInt());
    if(!sorgu.exec())
    {
        QMessageBox::critical(this,"ERROR!",sorgu.lastError().text(),"OK");
    }
    listele();
}

