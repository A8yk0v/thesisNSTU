#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

MainWindow::MainWindow(DBService &_dbs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbs(_dbs)
{
    ui->setupUi(this);
    refreshPatientsList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    PatientEditor patientEditor(dbs);
    patientEditor.setModal(true);
    patientEditor.exec();

    refreshPatientsList();
}

void MainWindow::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Внимание");
    msgBox.setText("Удалить пациента?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int res = msgBox.exec();

    if (res == QMessageBox::Ok) {
        dbs.deletePatient(this->patients[ui->listWidget->currentRow()]);
        refreshPatientsList();
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_2->clear();

    std::vector<Symptom> symptoms = dbs.getSymptomByIdPatient( this->patients[ui->listWidget->currentRow()].getId() );
    for (int i=0; i<symptoms.size(); ++i)
    {
        ui->listWidget_2->insertItem(i, new QListWidgetItem(symptoms[i].getDescription().c_str()));
    }

    ui->pushButton_2->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}

void MainWindow::refreshPatientsList()
{
    ui->listWidget->clear();
    ui->pushButton_2->setEnabled(false);
    ui->deleteButton->setEnabled(false);

    this->patients = dbs.getAllPatients();
    for (int j=0; j<patients.size(); ++j) {
        QListWidgetItem *newItem = new QListWidgetItem(QString(patients[j].getName().c_str()) + " " +
                                                       QString(patients[j].getSurname().c_str()) + " " +
                                                       QString::number(patients[j].getAge())
                                                      );
        ui->listWidget->insertItem(j, newItem);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Patient &currentPatient = patients[ui->listWidget->currentRow()];
    CalculateLogic calculateLogic(dbs);

    calculateDialog = new CalculateDialog(dbs, currentPatient, calculateLogic, this);
    calculateDialog->show();
}
