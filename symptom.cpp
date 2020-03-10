#include "symptom.h"

Symptom::Symptom(int _id, std::string _description)
    : id(_id), description(_description)
{

}

void Symptom::setId(int _id)
{
    id = _id;
}

void Symptom::setDescription(std::string _description)
{
    description = _description;
}
