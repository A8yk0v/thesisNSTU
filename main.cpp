#include "mainwindow.h"
#include <QApplication>
#include <vector>

#include "dbservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBService dbs;

//    std::vector<Patient> tmp = dbs.getAllPatients();
//    for (int j=0; j<tmp.size(); ++j) {
//        qDebug() << tmp[j].getName().c_str() << ":";
//        std::vector<Symptom> tmp_2 = dbs.getSymptomByIdPatient(tmp[j].getId());
//        for (int i=0; i<tmp_2.size(); ++i)
//        {
//            qDebug() << tmp_2[i].getDescription().c_str();
//        }
//    }

    MainWindow w(dbs);
    w.show();


    return a.exec();
}
