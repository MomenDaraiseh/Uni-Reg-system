#include "Course.h"
#include <iostream>
// Constructor
Course::Course(int id, const std::string& name, int capacity, int enrolled, int crdts, int instructorId)
    : courseId(id), courseName(name), maxCapacity(capacity), currentlyEnrolled(enrolled), credits(crdts), instructorId(instructorId) {
}

// Getters
int Course::getCourseId() const {
    return courseId;
}

int Course::getNumCredits() {
    return credits;
}
std::string Course::getCourseName() const {
    return courseName;
}

int Course::getMaxCapacity() const {
    return maxCapacity;
}

int Course::getCurrentlyEnrolled() const {
    return currentlyEnrolled;
}

int Course::getInstructorId() const {
    return instructorId;
}

// Setters
//admin features
void Course::setCourseName(const std::string& name) {
    courseName = name;
}

void Course::setMaxCapacity(int capacity) {
    maxCapacity = capacity;
}

void Course::setInstructorId(int id) {
    instructorId = id;
}

// Increment enrolled students (returns success status)
bool Course::incCurrentlyEnrolled() {
    if (currentlyEnrolled < maxCapacity) {
        currentlyEnrolled++;
        return true;
    }
    return false;  // Course is full
}

// Decrement enrolled students (returns success status)
bool Course::decCurrentlyEnrolled() {
    if (currentlyEnrolled > 0) {
        currentlyEnrolled--;
        return true;
    }
    return false;  // No students enrolled
}

// Check if course is full
bool Course::isFull() const {
    return currentlyEnrolled >= maxCapacity;
}

void Course::saveCourse(std::ofstream& ofs, bool last) {

    if (last)
        ofs << courseId << " " << maxCapacity << " " << currentlyEnrolled << " " << credits << " " << instructorId << " " << courseName;
    else
        ofs << courseId << " " << maxCapacity << " " << currentlyEnrolled << " " << credits << " " << instructorId << " " << courseName << "\n";
}

void Course::info() {
    std::cout << courseId << " " << maxCapacity << " " << currentlyEnrolled << " " << credits << " " << instructorId << " " << courseName << "\n";
}