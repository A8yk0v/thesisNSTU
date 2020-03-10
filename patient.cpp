#include "patient.h"

Patient::Patient(int _id, std::string _name, std::string _surname, int _age)
    : id(_id), name(_name), surname(_surname), age(_age)
{

}

void Patient::setId(int _id)
{
    id = _id;
}

void Patient::setName(std::string _name)
{
    name = _name;
}

void Patient::setSurname(std::string _surname)
{
    surname = _surname;
}

void Patient::setAge(int _age)
{
    age = _age;
}
