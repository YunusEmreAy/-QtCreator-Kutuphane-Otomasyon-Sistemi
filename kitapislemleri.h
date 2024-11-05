#ifndef KITAPISLEMLERI_H
#define KITAPISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Kitapislemleri;
}

class Kitapislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit Kitapislemleri(QSqlDatabase DB,QWidget *parent = nullptr);
    ~Kitapislemleri();

private slots:
    void on_tableView_kitap_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Kitapislemleri *ui;

    QSqlTableModel *model;

    void listele();

};

#endif // KITAPISLEMLERI_H
