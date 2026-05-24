#pragma once
#include "Student.h"
#include "Instructor.h"
#include "Course.h"
#include "Registration.h"
#include <vector>
#include <string>

// Forward declarations to avoid circular dependencies
//class Student;
//class Instructor;
//class Course;
//class Registration;


class RegSys {
public:
    std::vector<Student*> students;
    std::vector<Instructor*> instructors;
    std::vector<Course*> courses;
    std::vector<Registration*> registrations;

    int currentStudentId;
    int currentInstructorId;
    //int currentCourseId;
    std::string currentSemesterId;

public:
    // Constructor
    RegSys(std::string);

    // Destructor
    ~RegSys();

    // Authentication
    bool login(int username, const std::string& password);

    // Data loading/saving
    void loadStudents(std::string filename);
    void saveStudents(std::string filename);
    void loadInstructors(std::string filename);
    void saveInstructors(std::string filename);
    void loadCourses(std::string filename);
    void saveCourses(std::string filename);
    void loadRegistrations(std::string filename);
    void saveRegistrations(std::string filename);


    // UI
    void printMenu();

    // Student operations
    void addStudent(Student* student);
    void removeStudent(int studentId);
    Student * getStudent(int id);

    // Instructor operations
    void addInstructor(Instructor* instructor);
    void removeInstructor(int instructorId);
    Instructor * getInstructor(int id);

    // Course operations
    void addCourse(Course* course);
    void removeCourse(int courseId);
    // student registration creator
    void addRegistrations(Registration* registration);
    void removeRegistration(int stdID);
    void info();
    int checkIfCourseExists(int id);

    // Note: You might want to add getters for the vectors if needed
    // const std::vector<Student*>& getStudents() const { return students; }
    // etc...
};
