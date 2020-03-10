#ifndef PATIENTEDITOR_H
#define PATIENTEDITOR_H

#include <QDialog>

#include "dbservice.h"

namespace Ui {
class PatientEditor;
}

class PatientEditor : public QDialog
{
    Q_OBJECT

public:
    explicit PatientEditor(DBService &dbs, QWidget *parent = nullptr);
    ~PatientEditor();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Add_clicked();

private:
    Ui::PatientEditor *ui;

    DBService &dbs;
    std::vector<Symptom> symptoms;
};

#endif // PATIENTEDITOR_H
