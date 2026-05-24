#pragma once
#include <vector>
#include <fstream>

class Registration {
private:
    int studentId;
    int numberOfRegisteredCourses;

    int totalCredits;
    std::vector<int> registeredCourses;

public:
    // Constructor
    Registration(int studentId, int nrc, int tc);
    Registration(int studentId);

    // Getters
    int getStudentId() const;
    int getNumberOfRegisteredCourses() const;
    int getTotalCredits() const;
    const std::vector<int>& getRegisteredCourses() const;

    // Course management
    bool addCourse(int courseId, int credits);
    bool addCourse(int courseId);
    bool dropCourse(int courseId, int credits);

    // File operations
    void saveRegistration(std::ofstream& outFile, int last) const;
    void displayRegistration();
};