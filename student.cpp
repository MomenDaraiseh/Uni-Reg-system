#include "Student.h"
#include <iostream>
#include <algorithm>

// Constructor
Student::Student(std::string name, int id, std::string password, std::string dept, bool registered, int totalPassedCredits)
    : Person(name, id), password(password), dept(dept), totalPassedCredits(totalPassedCredits), registered(registered) {
}

// Getters
std::string Student::getPassword() const {
    return password;
}


int Student::getTotalPassedCredits() const {
    return totalPassedCredits;
}

bool Student::isRegistered() const {
    return registered;
}

Registration* Student::getRegisteredCourses() {
    return curRegistrationPtr;
}

void Student::setCurRegistrationPtr(Registration* RegistrationPtr) {
    curRegistrationPtr = RegistrationPtr;
}

// Setters
void Student::setPassword(const std::string& newPassword) {
    password = newPassword;
}

void Student::setRegistered(bool status) {
    registered = status;
}

// Course management
bool Student::addCourse(int courseId, int credits) {

    return curRegistrationPtr->addCourse(courseId, credits);
}

bool Student::dropCourse(int courseId, int credits) {

    return curRegistrationPtr->dropCourse(courseId, credits);
}


void Student::saveStudent(std::ofstream& ofs, bool last) const {

    if (last)
        ofs << id << " " << totalPassedCredits << " " << registered << " " << name << "\t" << password << "\t" << dept;
    else
        ofs << id << " " << totalPassedCredits << " " << registered << " " << name << "\t" << password << "\t" << dept << "\n";
}

// Override virtual function
void Student::info() {
    std::cout << "Student Info:\n"
        << "Name: " << name << "\n"
        << "ID: " << id << "\n"
        << "Passed Credits: " << totalPassedCredits << "\n"
        << "Status: " << (registered ? "Registered" : "Not Registered") << "\n";
    if (curRegistrationPtr != nullptr)
        curRegistrationPtr->displayRegistration();
}

bool Student::isEnrooledIn(int cid) {
    if (curRegistrationPtr != nullptr)
    {
        for (int i = 0; i < curRegistrationPtr->getNumberOfRegisteredCourses(); i++)
            if (cid == curRegistrationPtr->getRegisteredCourses()[i])
                return true;
    }
    return false;
}


void Student::clearRegistration() {
    delete curRegistrationPtr;
    curRegistrationPtr = nullptr;
    registered = false;
}