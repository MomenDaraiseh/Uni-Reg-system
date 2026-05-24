#pragma once
#include "Person.h"
#include <string>
#include <vector>
#include <fstream>

class Instructor : public Person {
private:

    std::string password;
    int myLoad;  // Current teaching load (in credit hours)
    std::vector<int> courseIds;  // IDs of courses being taught

public:
    // Constructor
    Instructor(std::string name, int id, std::string password, int load);

    // Getters
    std::string getPassword() const;
    int getTeachingLoad() const;
    const std::vector<int>& getCourseIds() const;

    // Setters
    void setPassword(const std::string& newPassword);
    void setTeachingLoad(int load);

    // Course management
    void addCourse(int courseId, int credits);
    void addCourse(int courseId);
    void removeCourse(int courseId, int credits);

    // View functions
    void viewCourses() const;
    bool isMyCourse(int courseId) const;

    // File operations
    void saveInstructor(std::ofstream& outFile, int last) const;

    // Override virtual function
    void info() override;
};