#pragma once
#include <string>
#include <fstream>

class Course {
private:
    int courseId;
    std::string courseName;
    int maxCapacity;
    int currentlyEnrolled;
    int credits;
    int instructorId;

public:
    // Constructor
    Course(int id, const std::string& name, int capacity, int enrolled, int crdts, int instructorId);

    // Getters
    int getCourseId() const;
    std::string getCourseName() const;
    int getMaxCapacity() const;
    int getCurrentlyEnrolled() const;
    int getInstructorId() const;
    void saveCourse(std::ofstream& ofs, bool last);
    // Setters
    void setCourseName(const std::string& name);
    void setMaxCapacity(int capacity);
    void setInstructorId(int id);

    // Enrollment management
    bool incCurrentlyEnrolled();  // Returns true if successful
    bool decCurrentlyEnrolled();  // Returns true if successful

    // Utility function
    bool isFull() const;
    void info(); 
    int getNumCredits();
};