#ifndef PATIENT_H
#define PATIENT_H

#include <string>

class Patient
{
public:
    Patient(int id, std::string name, std::string surname, int age);

    void setId(int);
    void setName(std::string);
    void setSurname(std::string);
    void setAge(int);

    int getId() const                     {return id;}
    const std::string& getName() const    {return name;}
    const std::string& getSurname() const {return surname;}
    int getAge() const                    {return age;}

private:
    int id;
    std::string name;
    std::string surname;
    int age;
};

#endif // PATIENT_H
