#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <string>

class Diagnosis
{
public:
    Diagnosis(int id, std::string name, std::string description);

    int getId() const {return id;}
    const std::string& getName() const {return name;}
    const std::string& getDecscription() const {return description;}

    void setId(int);
    void setName(std::string);
    void setDescription(std::string);

private:
    int id;
    std::string name;
    std::string description;
};

#endif // DIAGNOSIS_H
