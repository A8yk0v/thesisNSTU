#include "diagnosis.h"

Diagnosis::Diagnosis(int _id, std::string _name, std::string _description)
    : id(_id), name(_name), description(_description)
{

}

void Diagnosis::setId(int _id)
{
    id = _id;
}

void Diagnosis::setName(std::string _name)
{
    name = _name;
}

void Diagnosis::setDescription(std::string _description)
{
    description = _description;
}
