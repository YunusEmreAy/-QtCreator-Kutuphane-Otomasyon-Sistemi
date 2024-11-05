#ifndef UYEISLEMLERI_H
#define UYEISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


namespace Ui {
class Uyeislemleri;
}

class Uyeislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit Uyeislemleri(QSqlDatabase DB,QWidget *parent = nullptr);
    ~Uyeislemleri();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Uyeislemleri *ui;
    QSqlTableModel *model;

    void listele();

};

#endif // UYEISLEMLERI_H
