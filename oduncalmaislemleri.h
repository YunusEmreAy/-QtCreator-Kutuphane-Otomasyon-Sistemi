#ifndef ODUNCALMAISLEMLERI_H
#define ODUNCALMAISLEMLERI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Oduncalmaislemleri;
}

class Oduncalmaislemleri : public QDialog
{
    Q_OBJECT

public:
    explicit Oduncalmaislemleri(QSqlDatabase DB,QWidget *parent = nullptr);
    ~Oduncalmaislemleri();

private slots:
    void on_tableView_uyeler_clicked(const QModelIndex &index);

    void on_tableView_kitaplar_clicked(const QModelIndex &index);

    void on_OduncAl_clicked();

private:
    Ui::Oduncalmaislemleri *ui;

    QSqlTableModel *model1, *model2, *model3;
    void listele();
};

#endif // ODUNCALMAISLEMLERI_H
