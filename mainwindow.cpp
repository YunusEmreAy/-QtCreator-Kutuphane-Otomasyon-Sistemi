// Yunus Emre Ay - 21100011016

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

