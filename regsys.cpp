#include "RegSys.h"
#include "Student.h"
#include "Instructor.h"
#include "Course.h"
#include "Registration.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>


RegSys::RegSys(std::string currentSemesterId) :currentSemesterId(currentSemesterId) {
}

RegSys::~RegSys() {// other than desrtoying the objects we are gonna make it clean up the allocated memory
    for (Student* s : students) {
        delete s;
}
    for (Course* c : courses) {
        delete c;
    }
    for (Instructor* i : instructors) {
        delete i;
    }
    for (Registration* r : registrations) {
        delete r;
    }
    std::cout << " everything has been cleared out\n";
}

bool RegSys::login(int username, const std::string& password) {
    //login for students (id above 10 thousand) checks if logged in info matches info found in students vector after transfer from file
    if (username > 10000) {
        for (int i = 0; i < students.size(); i++) {
            int j = students[i]->getId();
            std::string s = students[i]->getPassword();
            if (username == j && password == s) {
                currentStudentId = username;
                currentInstructorId = 0;
                return true;
            }

        }
        return false;
    }
    else if (username >= 1) {
 //login for instructors (id 1-10 thousand) checks if logged in info matches info found in instructors vector after transfer from file
        for (int i = 0; i < instructors.size(); i++) {
            int j = instructors[i]->getId();
            std::string s = instructors[i]->getPassword();
            if (username == j && password == s) {
                currentInstructorId = username;
                currentStudentId = 0;
                return true;
            }

        }
        return false;

    }
    else
        //returns false if id below 1
        return false;

}

void RegSys::loadStudents(std::string filename) {
    //loads info from file into students vector (stores pointers of (new) objects from Student class created using data from files)
    std::ifstream ifc(filename);
    //while not the end of file keep looping and taking data storing them into vars then using them to create a new student obj and pointing 
    //at it through students vector
    while (!ifc.eof()) {
        int tc, i;
        bool rg;
        std::string n, p, d;
        ifc >> i >> tc >> rg;
        ws(ifc);
        getline(ifc, n, '\t');
        getline(ifc, p, '\t');
        getline(ifc, d, '\n');

        //Student(std::string name, int id, std::string password, std::string dept, bool registered, int totalPassedCredits)
        students.push_back(new Student(n, i, p, d, rg, tc));
    }

    ifc.close();
    //match students with their registrations to ensure every change on student is consistant with the change on their registration
    for (int i = 0; i < students.size(); i++) {
        for (int j = 0; j < registrations.size(); j++)
            if (students[i]->getId() == registrations[j]->getStudentId())//making sure student=registration using id's
            {
             //a Registration points in Student class that gives access to students registration through the Student class
                students[i]->setCurRegistrationPtr(registrations[j]);
                break;
            }
    }

}

void RegSys::saveStudents(std::string filename) {
    std::ofstream ofc(filename);

    for (int i = 0; i < students.size() - 1; i++)
        students[i]->saveStudent(ofc, false);
    students[students.size() - 1]->saveStudent(ofc, true);

    ofc.close();

}

void RegSys::loadInstructors(std::string filename) {
    std::ifstream ifc(filename);


    while (!ifc.eof()) {
        int id, load;
        std::string name, pass;
        ifc >> id >> load;
        ws(ifc);
        getline(ifc, name, '\t');
        getline(ifc, pass);

        //Student(std::string name, int id, std::string password, std::string dept, bool registered, int totalPassedCredits)
        instructors.push_back(new Instructor(name, id, pass, load));
    }

    ifc.close();
    //match instructors with their courses
    for (int i = 0; i < instructors.size(); i++)
        for (int j = 0; j < courses.size(); j++)
            if (instructors[i]->getId() == courses[j]->getInstructorId())
                instructors[i]->addCourse(courses[j]->getCourseId());
}

void RegSys::saveInstructors(std::string filename) {
    std::ofstream ofc(filename);

    for (int i = 0; i < instructors.size() - 1; i++)
        instructors[i]->saveInstructor(ofc, false);
    instructors[instructors.size() - 1]->saveInstructor(ofc, true);

    ofc.close();

}

void RegSys::loadCourses(std::string filename) {
    std::ifstream ifc(filename);

    while (!ifc.eof()) {
        int i, mc, ce, c, inid;
        std::string n;
        ifc >> i >> mc >> ce >> c >> inid;
        ws(ifc);
        getline(ifc, n, '\n');
        courses.push_back(new Course(i, n, mc, ce, c, inid));
    }
    ifc.close();

}

void RegSys::saveCourses(std::string filename) {
    std::ofstream ofc(filename);

    for (int i = 0; i < courses.size() - 1; i++)
        courses[i]->saveCourse(ofc, false);
    courses[courses.size() - 1]->saveCourse(ofc, true);

    ofc.close();
}

void RegSys::loadRegistrations(std::string filename) {

    std::ifstream ifc(filename);

    while (!ifc.eof()) {
        int sid, n, t, c;
        ifc >> sid >> n >> t;

        Registration* rp = new Registration(sid, n, t);

        for (int i = 0; i < n; i++) {
            ifc >> c;
            rp->addCourse(c);
        }
        registrations.push_back(rp);
    }
    ifc.close();

}

void RegSys::saveRegistrations(std::string filename) {
    std::ofstream ofc(filename);

    for (int i = 0; i < registrations.size() - 1; i++)
        registrations[i]->saveRegistration(ofc, false);
    registrations[registrations.size() - 1]->saveRegistration(ofc, true);

    ofc.close();

}

void RegSys::printMenu() {
    if (currentInstructorId) {
        if (currentInstructorId <= 10) {//admin menu
            std::cout << " 1. to view all students\n";
            std::cout << " 2. to view all courses\n";
            std::cout << " 3. to view all registrations\n";
            std::cout << " 4. to view all Instructors\n";
            std::cout << " 5. add new student\n";
            std::cout << " 6. add new instructor\n";
            std::cout << " 7. add new course\n";
            std::cout << " 8. register student\n";
            std::cout << " 9. delete student\n";
            std::cout << " 10. delete course\n";
            std::cout << " 11. delete instructor\n";
            std::cout << " 12. deelete student registration\n";

        }
        else {//instructor menu
            std::cout << " 1. show my current load\n";
            std::cout << " 2. show my current courses\n";
            std::cout << " 3. show enrolled students in a specific course\n";
            std::cout << " 4. reset password\n";
        }
    }
    else {//student menu
        std::cout << " 1. show my information\n";
        std::cout << " 2. show my registered courses\n";
        std::cout << " 3. enroll in a course\n";
        std::cout << " 4. drop from a course\n";
        std::cout << " 5. create a registartion record\n";
        std::cout << " 6. view offered courses\n";
        std::cout << " 7. reset password\n";
    }
    std::cout << " 0. to exit\n";
}

void RegSys::addStudent(Student *student) {//takes info entered by admin to create a new student obj
        students.push_back(student);
        std::cout << "Student added successfully with ID: " << student->getId() << std::endl;
    }


void RegSys::removeStudent(int studentId) {
    //uses iterator to scan the students vector and erases the info from heap then deletes the iterator
    auto it = students.begin();
    while (it != students.end()) {
        if ((*it)->getId() == studentId) {
            delete* it;
            it = students.erase(it);
            std::cout << "student with ID: " << studentId << " has been removed\n";
            return;
        }
        else
            it++;

    }
    std::cout << "Student was not found\n";
}

void RegSys::addInstructor(Instructor* instructor) {
  
        instructors.push_back(instructor);
        std::cout << "m3lem added successfully with ID: " << instructor->getId() << std::endl;
}

void RegSys::removeInstructor(int instructorId) {
auto it = instructors.begin();
while (it != instructors.end()) {
    if ((*it)->getId() == instructorId) {
        delete* it;
        it = instructors.erase(it);
        std::cout << "Instructor with ID: " << instructorId << " has been removed\n";
        return;
    }
    else
        it++;
}
std::cout << "Instructor was not found\n";
}
void RegSys::addCourse(Course* course) {
    courses.push_back(course);
    std::cout << "course added successfully with ID: " << course->getCourseId() << std::endl<< std::endl;
}
void RegSys::removeCourse(int courseId) {
    auto it = courses.begin();
    while (it != courses.end()) {
        if ((*it)->getCourseId() == courseId) {
            delete* it;
            it = courses.erase(it);
            std::cout << "Course with ID: " << courseId << " has been removed\n";
            return ;
        }
        else
            it++;
    }
    std::cout << "Course was not found\n";
}

void RegSys::addRegistrations(Registration* registration) {
    registrations.push_back(registration);
    std::cout << "registration added successfully with ID: " << registration->getStudentId() << std::endl;
}
void RegSys::removeRegistration(int ID) {
    Student* sp = getStudent(ID);
    
    auto it = registrations.begin();
    while (it != registrations.end()) {
        if ((sp->getRegisteredCourses()->getStudentId() == ID)) {
            it = registrations.erase(it);
            std::cout << "student with ID: " << ID << " has been removed from registrations\n";
            break;
        }
        else
            it++;
    }
    sp->clearRegistration();
}
void RegSys::info() {
    std::cout << "new reg sys";
}

Student* RegSys::getStudent(int id) {
    for (int i = 0; i < students.size(); i++)
        if (students[i]->getId() == id)
            return students[i];

    return nullptr;
}

Instructor* RegSys::getInstructor(int id) {
    for (int i = 0; i < instructors.size(); i++)
        if (instructors[i]->getId() == id)
            return instructors[i];

    return nullptr;
}


int RegSys::checkIfCourseExists(int id) {
    for (int i = 0; i < courses.size(); i++)
        if (courses[i]->getCourseId() == id)
            return courses[i]->getNumCredits();

    return -1;
}