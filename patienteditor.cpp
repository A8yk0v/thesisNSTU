#include "patienteditor.h"
#include "ui_patienteditor.h"

PatientEditor::PatientEditor(DBService &_dbs, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientEditor),
    dbs(_dbs)
{
    ui->setupUi(this);

    symptoms = dbs.getAllSymptoms();

    ui->listWidget->clear();
    for (int i=0; i<symptoms.size(); ++i)
    {
        auto item = new QListWidgetItem(symptoms[i].getDescription().c_str());
        item->setCheckState(Qt::Unchecked);
        ui->listWidget->insertItem(i, item);
    }
}

PatientEditor::~PatientEditor()
{
    delete ui;
}

void PatientEditor::on_pushButton_Cancel_clicked()
{
    reject();
}

void PatientEditor::on_pushButton_Add_clicked()
{
    // TODO добавить проверку введенных полей
    //!

    // Создаем нового пациента
    Patient patient(-1,
                    ui->lineEdit_name->text().toStdString(),
                    ui->lineEdit_surname->text().toStdString(),
                    ui->lineEdit_age->text().toInt()
                   );

    // Сохраняем его симптомы
    std::vector<Symptom> symptoms_in_the_patient;

    auto item = ui->listWidget->takeItem(0);
    while ( item != nullptr)
    {
        if ( item->checkState() == Qt::Checked ) {
            for (int j=0; j<symptoms.size(); ++j)
                if (item->text().toStdString() == symptoms[j].getDescription())
                    symptoms_in_the_patient.push_back(symptoms[j]);
        }

        item = ui->listWidget->takeItem(0);
    }

    dbs.addPatient(patient);
    dbs.addSymptomsToPatient(patient, symptoms_in_the_patient);

    reject();
}
