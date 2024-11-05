#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("KutupHane.db");
    if(!db.open())
    {
        this->statusBar()->showMessage("Veri Tabanına Bağlanılamadı!");
    }
    else
    {
        this->statusBar()->showMessage("Veri Tabanına Bağlanıldı!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Uyeislemleri *uye=new Uyeislemleri(db);
    uye->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    Kitapislemleri *kitap=new Kitapislemleri(db);
    kitap->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    Oduncalmaislemleri *odunc=new Oduncalmaislemleri(db);
    odunc->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    Oduncteslimetmeislemleri *odunc_teslim=new Oduncteslimetmeislemleri(db);
    odunc_teslim->show();
}

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



