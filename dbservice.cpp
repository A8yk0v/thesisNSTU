#include "dbservice.h"

DBService::DBService()
{
    //Подключаем базу данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dissertationDB.db");
    if ( !db.open() )
        qDebug() << "Cannot open database";

//    QStringList lst = db.tables();
//    foreach (QString str, lst) {
//        qDebug() << "Table:" << str;
//    }



//    QSqlQuery query(db);


//    query.exec("CREATE TABLE patients ("
//               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
//               "name TEXT NOT NULL,"
//               "suranme TEXT,"
//               "age INTEGER);");

//    if ( query.isActive() )
//        qDebug() << "create is done!)";
//    else {
//        qDebug() << query.lastError();
//    }


//    query.exec("INSERT INTO patients (name, suranme, age) "
//               "VALUES ('Petr', 'Petrov', 23);");
//    if ( query.isActive() )
//        qDebug() << "INSERT is done!)";
//    else {
//        qDebug() << query.lastError();
//    }


//    if ( query.exec("select * from patients") )
//        qDebug() << "query - ok";
//    else {
//        qDebug() << query.lastError();
//    }
//    qDebug() << "query.size(): " << query.size();

//    while ( query.next() ) {
//        qDebug() << "query.value(1): " + query.value(1).toString();
//        qDebug() << "query.value(2): " + query.value(2).toString();
//        qDebug() << "query.value(3): " + query.value(3).toString();
//        qDebug() << "--------";
//        //Patient patient(query.value(6))
//    }
}

std::vector<Patient> DBService::getAllPatients()
{
    QSqlQuery query(db);
    query.exec("SELECT * FROM patients;");

    if (!query.isActive())
        qDebug() << "getAllPatients: " << query.lastError();

    std::vector<Patient> patients;
    while ( query.next() ) {
        Patient patient(query.value(0).toInt(),
                        query.value(1).toString().toStdString(),
                        query.value(2).toString().toStdString(),
                        query.value(3).toInt());
        patients.push_back(patient);
    }
    return patients;
}

std::vector<Symptom> DBService::getSymptomByIdPatient(int id)
{
    QSqlQuery query(db);
    query.exec("select * from symptoms "
               "JOIN patients_symptoms "
               "ON patients_symptoms.id_p = " + QString::number(id) +
               " and symptoms.id = patients_symptoms.id_s;");

    if (!query.isActive())
        qDebug() << "getSymptomByIdPatient: " << query.lastError();

    std::vector<Symptom> symptoms;
    while ( query.next() ) {
        Symptom symptom (query.value(0).toInt(), query.value(1).toString().toStdString());
        symptoms.push_back(symptom);
    }
    return symptoms;
}

std::vector<Symptom> DBService::getAllSymptoms()
{
    QSqlQuery query(db);
    query.exec("SELECT * FROM symptoms;");

    if (!query.isActive())
        qDebug() << "getAllSymptoms: " << query.lastError();

    std::vector<Symptom> symptoms;
    while ( query.next() ) {
        Symptom symptom(query.value(0).toInt(), query.value(1).toString().toStdString());
        symptoms.push_back(symptom);
    }
    return symptoms;
}

std::vector<Diagnosis> DBService::getAllDiagnosis()
{
    QSqlQuery query(db);
    query.exec("SELECT * FROM diagnosis;");

    if (!query.isActive())
        qDebug() << "getDiagnosis: " << query.lastError();

    std::vector<Diagnosis> diagnosis_vector;
    while ( query.next() ) {
        Diagnosis diagnosis(query.value(0).toInt(),
                            query.value(1).toString().toStdString(),
                            query.value(2).toString().toStdString());
        diagnosis_vector.push_back(diagnosis);
    }
    return diagnosis_vector;
}

std::vector<Symptom> DBService::getSymptomsDiagnosis(const Diagnosis &diagnosis)
{
    QSqlQuery query(db);
    query.exec("select * from symptoms "
               "JOIN diagnosis_symptoms "
               "ON diagnosis_symptoms.id_d = " + QString::number(diagnosis.getId()) +
               " and symptoms.id = diagnosis_symptoms.id_s;");

    if (!query.isActive())
        qDebug() << "getSymptomsDiagnosis: " << query.lastError();

    std::vector<Symptom> symptoms;
    while ( query.next() ) {
        Symptom symptom (query.value(0).toInt(), query.value(1).toString().toStdString());
        symptoms.push_back(symptom);
    }
    return symptoms;
}

bool DBService::addPatient(const Patient &patient)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO patients (name, surname, age) "
                  "VALUES (:name, :surname, :age); ");
    query.bindValue(":name", patient.getName().c_str() );
    query.bindValue(":surname", patient.getSurname().c_str() );
    query.bindValue(":age", patient.getAge() );

    query.exec();
    if (!query.isActive()) {
        qDebug() << "addPatient: " << query.lastError();
        return false;
    }

    return true;
}

bool DBService::addSymptomsToPatient(const Patient &patient, const std::vector<Symptom> &symptoms)
{
    QSqlQuery query(db);
    int id_tmp = patient.getId();

    // определить id, если нужно
    if (id_tmp == -1) {
        query.exec("select id from patients "
                   "where name = \"" + QString::fromStdString(patient.getName().c_str()) +
                   "\" and surname = \"" + QString::fromStdString(patient.getSurname().c_str()) +
                   "\" and age = " + QString::number(patient.getAge())
                   );

        if (!query.isActive()) {
            qDebug() << "addSymptomsToPatient: " << query.lastError();
            return false;
        }

        query.first();
        id_tmp = query.value(0).toInt();
    }

    for (int i=0; i<symptoms.size(); ++i) {
        query.clear();
        query.prepare("INSERT INTO patients_symptoms (id_p, id_s) "
                      "VALUES (:id_p, :id_s); ");
        query.bindValue(":id_p", id_tmp);
        query.bindValue(":id_s", symptoms[i].getId() );

        query.exec();
        if (!query.isActive()) {
            qDebug() << "addSymptomsToPatient: " << query.lastError();
        }

    }

    return false;
}

bool DBService::deletePatient(Patient &patient)
{
    QSqlQuery query(db);
    query.exec("DELETE FROM patients_symptoms "
               "WHERE id_p = " + QString::number(patient.getId()) +
               ";");

    if (!query.isActive()) {
        qDebug() << "deletePatient: " << query.lastError();
        return false;
    }

    query.clear();
    query.exec("DELETE FROM patients "
               "WHERE id = " + QString::number(patient.getId()) +
               ";");

    if (!query.isActive()) {
        qDebug() << "deletePatient: " << query.lastError();
        return false;
    }

    return true;
}
