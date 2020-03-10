#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>

#include "calculatedialog.h"
#include "dbservice.h"
#include "patienteditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DBService &, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    CalculateDialog *calculateDialog;
    DBService &dbs;

    std::vector<Patient> patients;

    void refreshPatientsList();
};

#endif // MAINWINDOW_H
