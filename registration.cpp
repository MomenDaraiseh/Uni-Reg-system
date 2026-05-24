#include "Registration.h"
#include <iostream>
#include <algorithm> // for std::find

// Constructor
Registration::Registration(int studentId, int nrc, int tc)
    : studentId(studentId), numberOfRegisteredCourses(nrc), totalCredits(tc) {
}

Registration::Registration(int studentId)
    : studentId(studentId), numberOfRegisteredCourses(0), totalCredits(0) {
}

// Getters
int Registration::getStudentId() const {
    return studentId;
}


int Registration::getNumberOfRegisteredCourses() const {
    return numberOfRegisteredCourses;
}

int Registration::getTotalCredits() const {
    return totalCredits;
}

const std::vector<int>& Registration::getRegisteredCourses() const {
    return registeredCourses;
}

// Add a course to registration
bool Registration::addCourse(int courseId, int credits) {
    // Check if course already registered
    if (std::find(registeredCourses.begin(), registeredCourses.end(), courseId) != registeredCourses.end()) {
        return false; // Course already registered
    }

    registeredCourses.push_back(courseId);
    numberOfRegisteredCourses++;
    totalCredits += credits;
    return true;
}

bool Registration::addCourse(int courseId) {
    if (std::find(registeredCourses.begin(), registeredCourses.end(), courseId) != registeredCourses.end()) {
        return false; // Course already registered
    }
    registeredCourses.push_back(courseId);
    return true;
}

// Drop a course from registration
bool Registration::dropCourse(int courseId, int credits) {
    auto it = std::find(registeredCourses.begin(), registeredCourses.end(), courseId);
    if (it == registeredCourses.end()) {
        return false; // Course not found
    }

    registeredCourses.erase(it);
    numberOfRegisteredCourses--;
    totalCredits -= credits;
    return true;
}

// Save registration data to file
void Registration::saveRegistration(std::ofstream& outFile, int last) const {
    outFile << studentId << " " << numberOfRegisteredCourses << " " << totalCredits << " ";

    // Save all registered course IDs
    for (int i = 0; i < registeredCourses.size() - 1; i++) {
        outFile << registeredCourses[i] << " ";
    }

    if (!last)
        outFile << registeredCourses[registeredCourses.size() - 1] << "\n";
    else
        outFile << registeredCourses[registeredCourses.size() - 1];


}

void Registration::displayRegistration() {
   
    std::cout << "No of Reg Courses: " << numberOfRegisteredCourses << "\n";
    std::cout << "No of Credit Hours: " << totalCredits << "\n";

    std::cout << "Registered Courses: \n";
    //searches registered courses gives thier value to courseId and prints it out
    for (int courseId : registeredCourses) {
        std::cout << courseId << " ";
    }
    std::cout << "\n";
}