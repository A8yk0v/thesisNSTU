#ifndef BDSERVICE_H
#define BDSERVICE_H

#include <QtSql>
#include <QSqlQuery>
#include <forward_list>

#include "patient.h"
#include "symptom.h"
#include "diagnosis.h"

class DBService
{
public:
    DBService();

    // Получить список всех пациентов
    std::vector<Patient> getAllPatients();
    // Получить список симптомов пациента по id
    std::vector<Symptom> getSymptomByIdPatient(int id);
    // Получить список всех симптомов
    std::vector<Symptom> getAllSymptoms();
    // Получить список всех диагнозов
    std::vector<Diagnosis> getAllDiagnosis();
    // Получить симптомы диагноза
    std::vector<Symptom> getSymptomsDiagnosis(const Diagnosis&);

    //Добавить пациента
    bool addPatient(const Patient &);
    // Добавить симптомы пациенту
    bool addSymptomsToPatient(const Patient &, const std::vector<Symptom> &);

    bool deletePatient(Patient &);

private:
    QSqlDatabase db;
};

#endif // BDSERVICE_H
