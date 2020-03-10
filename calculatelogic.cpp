#include "calculatelogic.h"

CalculateLogic::CalculateLogic(DBService &_dbs)
    : dbs(_dbs)
{

}

std::vector<double> CalculateLogic::CalculateForPatient(const Patient &patient)
{
    std::vector<Symptom> symptoms = dbs.getAllSymptoms();
    std::vector<Symptom> symptomsPatient = dbs.getSymptomByIdPatient(patient.getId());

    std::vector<Diagnosis> diagnosis = dbs.getAllDiagnosis();
    //std::vector<Symptom> symptomsDiagnosis = dbs.getSymptomsDiagnosis( .. );
    // TODO
    // ...

    // Вероятности диагнозов
    std::vector<double> probabilities(diagnosis.size());

    // рассчитаем
    for (int i=0; i<diagnosis.size(); ++i)
    {
        std::vector<Symptom> symptomsDiagnosis = dbs.getSymptomsDiagnosis(diagnosis[i]);
        std::vector<double>array_tak(symptoms.size());
        std::vector<double>array_inache(symptoms.size());

        for(int i=0; i<symptoms.size(); ++i)
        {
            //if (s prinadlegit D)
            //if ( prinadlegit(symptoms[i], symptomsDiagnosis) )
                array_tak[i] = schitaem_tak(symptomsPatient, symptomsDiagnosis);
            //else
                array_inache[i] = schitaem_inache(symptomsDiagnosis,
                                           symptomsPatient,
                                           symptoms);
        }

        double P_D = 0.5;
        for (int i = 0; i < symptoms.size(); ++i)
        {
            if ( isSymptom(symptoms[i], symptomsPatient) )
                P_D = ( P_D * array_tak[i] ) / ( (P_D * array_tak[i]) + (1 - P_D)*array_inache[i] );
            else
                P_D = ( P_D * (1 - ((1 - array_inache[i]))) ) / ( ( P_D * (1 - ((1 - array_inache[i]))) ) + (1 - P_D)*(1 - array_inache[i]) );
        }
        qDebug() << "P_D:" << P_D;
        probabilities[i] = P_D;
    }

    return probabilities;
}

bool CalculateLogic::prinadlegit(Symptom &symptoms, std::vector<Symptom> &symptomsDiagnosis)
{
    for(int i=0; i<symptomsDiagnosis.size(); ++i)
    {
        if (symptoms.getId() == symptomsDiagnosis[i].getId())
            return true;
    }
    return false;
}

bool CalculateLogic::isSymptom(Symptom &symptoms, std::vector<Symptom> &symptomsPatient)
{
    for(int i=0; i<symptomsPatient.size(); ++i)
    {
        if (symptoms.getId() == symptomsPatient[i].getId())
            return true;
    }
    return false;
}

double CalculateLogic::schitaem_tak(std::vector<Symptom> &symptomsPatient,
                                    std::vector<Symptom> &symptomsDiagnosis)
{
    double sum_DA = 0;
    double sum_NO = 0;
    for(int i=0; i<symptomsDiagnosis.size(); ++i)
    {
        for (int j=0; j<symptomsPatient.size(); ++j)
            if (symptomsDiagnosis[i].getId() == symptomsPatient[j].getId())
            {
                ++sum_DA;
                continue;
            }
        ++sum_NO;
    }
    return sum_DA / (sum_DA + sum_NO);
}

double CalculateLogic::schitaem_inache(std::vector<Symptom> &symptomsDiagnosis,
                                       std::vector<Symptom> &symptomsPatient,
                                       std::vector<Symptom> &symptoms)
{
    double sum_DA = 0;
    double sum_NO = 0;
    for (int i = 0; i < symptoms.size(); ++i) {
        // Не рассматриваем симптомы диагноза
        for (int j = 0; j < symptomsDiagnosis.size(); ++j) {
            if (symptoms[i].getId() == symptomsDiagnosis[j].getId())
                continue;
        }

        for (int j=0; j<symptomsPatient.size(); ++j)
            if (symptoms[i].getId() == symptomsPatient[j].getId())
            {
                ++sum_DA;
                continue;
            }
        ++sum_NO;
    }
    return sum_DA / (sum_DA + sum_NO);
}
