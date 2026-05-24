#include "Instructor.h"
#include <iostream>
#include <algorithm>

// Constructor
Instructor::Instructor(std::string name, int id, std::string password, int load)
    : Person(name, id), password(password), myLoad(load) {
}


// Getters
std::string Instructor::getPassword() const {
    return password;
}

int Instructor::getTeachingLoad() const {
    return myLoad;
}

const std::vector<int>& Instructor::getCourseIds() const {
    return courseIds;
}

// Setters
void Instructor::setPassword(const std::string& newPassword) {
    password = newPassword;
}

void Instructor::setTeachingLoad(int load) {
    myLoad = load;
}

// Course management
void Instructor::addCourse(int courseId, int credits) {
    if (std::find(courseIds.begin(), courseIds.end(), courseId) == courseIds.end()) {
        courseIds.push_back(courseId);
        myLoad += credits;
    }
}

void Instructor::addCourse(int courseId) {
    if (std::find(courseIds.begin(), courseIds.end(), courseId) == courseIds.end()) {
        courseIds.push_back(courseId);
    }
}

void Instructor::removeCourse(int courseId, int credits) {
    auto it = std::find(courseIds.begin(), courseIds.end(), courseId);
    if (it != courseIds.end()) {
        courseIds.erase(it);
        myLoad -= credits;
    }
}

// View functions
void Instructor::viewCourses() const {
    std::cout << "Courses taught by " << name << " (ID: " << id << "):\n";
    for (int courseId : courseIds) {
        std::cout << "- Course ID: " << courseId << "\n";
    }
    std::cout << "Current teaching load: " << myLoad << " credit hours\n";
}

bool Instructor::isMyCourse(int courseId) const {

    for (int i = 0; i < courseIds.size(); i++)
        if (courseId == courseIds[i])
            return true;

    return false;


}

// Save instructor data to file
void Instructor::saveInstructor(std::ofstream& outFile, int last) const {

    if (!last)
        outFile << id << " " << myLoad << " " << name << "\t" << password << "\n";
    else
        outFile << id << " " << myLoad << " " << name << "\t" << password;



}

// Override virtual function
void Instructor::info() {
    std::cout << "Instructor Info:\n"
        << "Name: " << name << "\n"
        << "ID: " << id << "\n"
        << "Teaching Load: " << myLoad << " credit hours\n"
        << "Assigned Courses: ";

    for (int i = 0; i < courseIds.size(); i++) {
        std::cout << courseIds[i] << " ";
    }
    std::cout << "\n";

}