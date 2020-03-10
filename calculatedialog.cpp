#include "calculatedialog.h"
#include "ui_calculatedialog.h"

CalculateDialog::CalculateDialog(DBService &dbs, const Patient &patient,
                                 CalculateLogic &calculateLogic, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalculateDialog)
{
    ui->setupUi(this);


    ui->lineEdit_PatientView->setText(QString(patient.getName().c_str()) + " " +
                                      QString(patient.getSurname().c_str()) + " " +
                                      QString::number(patient.getAge()) );

    std::vector<double> probabilities = calculateLogic.CalculateForPatient(patient);
    std::vector<Diagnosis> diagnosis = dbs.getAllDiagnosis();

    // TODO

    //QByteArray str;
    //QTextStream stream(str);
    char str[100];
    QString string;
    foreach (auto item, diagnosis) {
        //stream << QTextStream::AlignLeft << item.getName().c_str() << QTextStream::AlignRight << "test";
        string.sprintf("%-20s %10s", item.getName().c_str(), QString::number(111).toStdString().c_str());
        QListWidgetItem *it = new QListWidgetItem("string");
        ui->listWidget_Diagnosis->addItem(it);
    }
}

CalculateDialog::~CalculateDialog()
{
    delete ui;
}
