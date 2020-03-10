#ifndef SYMPTOM_H
#define SYMPTOM_H

#include <string>

class Symptom
{
public:
    Symptom(int id, std::string description);

    void setId(int);
    void setDescription(std::string);

    int getId() const {return id;}
    const std::string &getDescription() const {return description;}

private:
    int id;
    std::string description;
};

#endif // SYMPTOM_H
