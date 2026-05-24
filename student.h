#pragma once
#include "Person.h"
#include "Registration.h"
#include <string>
#include <vector>
#include <fstream>

class Student : public Person {
private:
    //attributes
    std::string password;
    std::string dept;
    int totalPassedCredits;
    bool registered;

    Registration* curRegistrationPtr = nullptr; // Stores current login ID

public:
    // Constructor
    Student(std::string name, int id, std::string password, std::string dept, bool registered, int totalPassedCredits);

    // Getters
    std::string getPassword() const;
    int getTotalPassedCredits() const;
    bool isRegistered() const;
    Registration* getRegisteredCourses();
    void setCurRegistrationPtr(Registration* RegistrationPtr);

    // Setters
    void setPassword(const std::string& newPassword);
    void setRegistered(bool);

    // Course management
    bool addCourse(int courseId, int credits);
    bool dropCourse(int courseId, int credits);

    // File operations
    void saveStudent(std::ofstream& ofs, bool last) const;

    // Override virtual function
    void info() override;
    bool isEnrooledIn(int cid);
    void clearRegistration();
};