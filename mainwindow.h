#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uyeislemleri.h"
#include "kitapislemleri.h"
#include "oduncalmaislemleri.h"
#include "oduncteslimetmeislemleri.h"
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
};
#endif // MAINWINDOW_H
