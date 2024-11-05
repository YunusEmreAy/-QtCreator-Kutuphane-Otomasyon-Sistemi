#ifndef ODUNCTESLIMETMEISLEMLERI_H
#define ODUNCTESLIMETMEISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QString>

namespace Ui {
class Oduncteslimetmeislemleri;
}

class Oduncteslimetmeislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit Oduncteslimetmeislemleri(QSqlDatabase DB,QWidget *parent = nullptr);
    ~Oduncteslimetmeislemleri();

private slots:
    void on_tableView_odunc_clicked(const QModelIndex &index);

    void on_OduncAl_clicked();

private:
    Ui::Oduncteslimetmeislemleri *ui;

    QSqlTableModel *model1, *model2;
    void listele();
};

#endif // ODUNCTESLIMETMEISLEMLERI_H
