#ifndef CALCULATELOGIC_H
#define CALCULATELOGIC_H

#include "dbservice.h"
#include "patient.h"

class CalculateLogic
{
public:
    CalculateLogic(DBService &);

    std::vector<double> CalculateForPatient(const Patient &);

private:
    DBService &dbs;

    bool prinadlegit(Symptom &symptoms, std::vector<Symptom> &symptomsDiagnosis);

    bool isSymptom(Symptom &symptoms, std::vector<Symptom> &symptomsPatient);

    double schitaem_tak(std::vector<Symptom> &symptomsPatient,
                        std::vector<Symptom> &symptomsDiagnosis);

    double schitaem_inache(std::vector<Symptom> &symptomsDiagnosis,
                           std::vector<Symptom> &symptomsPatient,
                           std::vector<Symptom> &symptoms);
};

#endif // CALCULATELOGIC_H
