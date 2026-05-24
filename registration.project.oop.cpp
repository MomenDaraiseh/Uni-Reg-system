// proj3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "RegSys.h"
#include <iostream>
#include <string>
#include <cstdlib>

void clearTerminal() {
#ifdef _WIN32
    system("cls");  // Windows
#endif
}

int main() {


    std::string curTerm = "253";
    // Create Registration System object
    RegSys registrationSystem(curTerm);
    std::string stdfile = "C:\\temp\\Students.txt";
    std::string coursesfile = "C:\\temp\\courses_" + curTerm + ".txt";
    std::string instfile = "C:\\temp\\instructor.txt";
    std::string regfile = "C:\\temp\\registration_" + curTerm + ".txt";

    // Load initial data

    registrationSystem.loadCourses(coursesfile);
    registrationSystem.loadRegistrations(regfile);
    registrationSystem.loadStudents(stdfile);
    registrationSystem.loadInstructors(instfile);

    // Example usage
    bool loggedIn = false;
    std::string  password;
    int username;

    // Login loop
    while (!loggedIn) {
        std::cout << "University Registration System\n";
        std::cout << "Username: ";
        std::cin >> username;
        std::cin.ignore();
        std::cout << "Password: ";
        getline(std::cin, password);

        loggedIn = registrationSystem.login(username, password);

        if (!loggedIn) {
            std::cout << "Invalid credentials. Try again.\n";
        }
    }

    //keep a pointer to the logged in instructor or students so that we don't have to search the list every time
    Instructor* ip = nullptr;
    Student* sp = nullptr;

    if (registrationSystem.currentInstructorId) {
        for (int i = 0; i < registrationSystem.instructors.size(); i++)
            if (registrationSystem.instructors[i]->getId() == registrationSystem.currentInstructorId)
            {
                ip = registrationSystem.instructors[i];
                break;
            }
    }
    else {
        for (int i = 0; i < registrationSystem.students.size(); i++)
            if (registrationSystem.students[i]->getId() == registrationSystem.currentStudentId)
            {
                sp = registrationSystem.students[i];
                break;
            }
    }

    // Main menu
    int choice;
    Student* stdadder=nullptr;
    Registration* regadder = nullptr;
        do {
        registrationSystem.printMenu();
        std::cout << "\n Enter your choice: \n";
        std::cin >> choice;
        if (ip != nullptr) {
            if (registrationSystem.currentInstructorId <= 10) {
                switch (choice) {
                case 1: {
                    //show all students
                    clearTerminal();
                    for (int i = 0; i < registrationSystem.students.size(); i++)
                        registrationSystem.students[i]->info();
                    std::cout << "\n";
                    break;
                }
                case 2: {
                    //show all courses
                    clearTerminal();
                    for (int i = 0; i < registrationSystem.courses.size(); i++)
                        registrationSystem.courses[i]->info();
                    std::cout << "\n";
                    break;
                }
                case 3: {
                    //show all registrations
                    clearTerminal();
                    for (int i = 0; i < registrationSystem.registrations.size(); i++)
                        registrationSystem.registrations[i]->displayRegistration();
                    std::cout << "\n";
                    break;
                }
                case 4: {
                    //show all instructors
                    clearTerminal();
                    for (int i = 0; i < registrationSystem.instructors.size(); i++)
                        registrationSystem.instructors[i]->info();
                    std::cout << "\n";
                    break;
                }
                case 5: {
                   //add student example
                    clearTerminal();
                    std::string name, pass, dept;
                    int id, hours;
                    bool isreg;
                    std::cout << "enter name of student you want to add:\n ";
                    std::cin.ignore();
                    getline(std::cin, name);
                    std::cout << "enter pass of added student:\n ";
                    std::cin.ignore();
                    getline(std::cin, pass);
                    std::cout << "enter student id:\n ";
                    std::cin >> id;
                    std::cout << "enter department of added student:\n ";
                    std::cin.ignore();
                    getline(std::cin, dept);
                    //std::cout << "is the student registered (1 or 0):\n ";
                    //std::cin >> isreg;
                    //std::cout << "enter total credit hours:\n ";
                    //std::cin >> hours;
                    //stdadder = ();
                    registrationSystem.addStudent(new Student(name, id, pass, dept, 0, 0));
                    break;
                }
                case 6: {
                    //add instructor 
                    clearTerminal();
                    std::string name, pass;
                    int id, load;
                    std::cout << "enter name of instructor you want to add:\n ";
                    std::cin.ignore();
                    getline(std::cin, name);
                    std::cout << "enter pass of added instructor:\n ";
                    std::cin.ignore();
                    getline(std::cin, pass);
                    std::cout << "enter instructor id:\n ";
                    std::cin >> id;
                    Instructor* insadder = (new Instructor(name, id, pass,0));
                    registrationSystem.addInstructor(insadder);
                    break;
                }
                case 7: {
                    //add course
                    clearTerminal();
                    std::string name;
                    int id, currentcap, totalcap,credits,insID;
                    std::cout << "enter name of course you want to add:\n ";
                    std::cin.ignore();
                    getline(std::cin, name);
                    std::cout << "enter the max capacity of the course:\n ";
                    std::cin >> totalcap;
                    std::cout << "enter course id:\n ";
                    std::cin >> id;
                    std::cout << "enter instructor id:\n ";
                    std::cin >> insID;
                    std::cout << "enter course credits(1 or 3):\n ";
                    std::cin >> credits;
                    
                    Instructor* insP= registrationSystem.getInstructor(insID);
                    if (insP == nullptr)
                    {
                        std::cout << "Instructor Doesn't exist\n";
                        break;
                    }
                    int crd = registrationSystem.checkIfCourseExists( id);
                    if (crd != -1)
                    {
                        std::cout << "course is already offered\n";
                        break;
                    }

                    Course* crsadder = (new Course(id, name, totalcap, 0, credits, insID));
                    registrationSystem.addCourse(crsadder);
                    insP->addCourse(id, credits);



                    break;
                    

                }
                case 8: {
                    //register students
                    clearTerminal();
                        std::cout << "Insert studentID\n";
                        int id;
                        std::cin >> id;
                        Student* sp = registrationSystem.getStudent(id);
                        if (sp == nullptr) {
                            std::cout << "Student ID not Found\n";
                            break;
                        }

                        if (sp->getRegisteredCourses() == nullptr) {
                            sp->setCurRegistrationPtr(new Registration(id));
                        }

                        int coursesID;
                        
                        while (true) {
                            std::cout << "please enter Course ID, -1 to stop\n ";
                            std::cin >> coursesID;
                            if (coursesID == -1)
                                break;
                            int credits = registrationSystem.checkIfCourseExists(coursesID);
                            if (credits == -1)
                            {
                                std::cout << "Course  ID not Found in offered courses\n";
                                break;
                            }

                            if (sp->getRegisteredCourses()->addCourse(coursesID, credits)) {
                                std::cout << "Course added sucessfully\n";
                            }
                            else
                                std::cout << "Course is already registered\n";
                        }
                        
                       
               
                    
                }
                case 9: {
                    // Remove student example
                    clearTerminal();
                    int id;
                    std::cout << "Enter student ID to remove: ";
                    std::cin >> id;
                    std::cout << "\n";
                    registrationSystem.removeStudent(id);
                    std::cout << "\n";
                    break;
                }
                case 10: {
                    // Remove course example
                    clearTerminal();
                    int id;
                    std::cout << "Enter course ID to remove: ";
                    std::cin >> id;
                    std::cout << "\n";
                    registrationSystem.removeCourse(id);
                    std::cout << "\n";
                    break;
                }
                case 11: {
                    // Remove instructor example
                    clearTerminal();
                    int id;
                    std::cout << "Enter instructor ID to remove: ";
                    std::cin >> id;
                    std::cout << "\n";
                    registrationSystem.removeInstructor(id);
                    std::cout << "\n";
                    break;
                }
                case 12: {
                    // Remove student registration example
                    clearTerminal();
                    int sid;
                    std::cout << "Enter student ID to remove from registrations: ";
                    std::cin >>sid;
                    std::cout << "\n";
                    registrationSystem.removeRegistration(sid);
                    std::cout << "\n";
                    break;
                }
                       
                case 0:
                    clearTerminal();
                    std::cout << "Exiting system...\n";
                    break;
                default:
                    clearTerminal();
                    std::cout << "Invalid choice!\n";
                }
            }
            else if (registrationSystem.currentInstructorId > 10) {
                switch (choice) {
                case 1: {
                    //show all my load
                    clearTerminal();
                    std::cout << "Current Load is: " << ip->getTeachingLoad() << "\n";
                    break;
                  

                }
                case 2: {
                    //show all courses
                    clearTerminal();
                    ip->info();
                    std::cout << "\n";
                    break;
                    
                }
                case 3: {
                    //show enrooled students
                    clearTerminal();
                    int courseid;
                    std::cout << "please insert course ID: ";
                    std::cin >> courseid;
                    if (ip->isMyCourse(courseid)) {
                        for (int i = 0; i < registrationSystem.students.size(); i++)
                            if (registrationSystem.students[i]->isEnrooledIn(courseid))
                                std::cout << registrationSystem.students[i]->getId() << " " << registrationSystem.students[i]->getName() << "\n";
                    }
                    else
                        std::cout << "Course doesn't belong to you";
                    std::cout << "\n";
                    break;
                
                }
                case 4: {
                    //reset pass
                    clearTerminal();
                    std::string pass;
                    std::cout << "enter current password: ";
                    std::cin.ignore();
                    getline(std::cin, pass);
                    if (pass == ip->getPassword())
                    {
                        std::cout << "enter new password: ";
                        getline(std::cin, pass);
                        ip->setPassword(pass);
                    }
                    std::cout << "\n";
                    break;
                }
                case 0:
                    clearTerminal();
                    std::cout << "Exiting system...\n";
                    break;
                default:
                    clearTerminal();
                    std::cout << "Invalid choice!\n";
                }
            }
        }
        if (sp != nullptr) {
            switch (choice) {
            case 1: {
                //show my info
                clearTerminal();
                sp->info();
                std::cout << "\n";
                break;
               
            }
            case 2: {
                //show my registered courses
                clearTerminal();
                Registration* r = sp->getRegisteredCourses();
                if (r != nullptr) {
                    r->displayRegistration();
                }
                else
                    std::cout << "you are not registered yet.";
                std::cout << "\n";
              
                break;
              
            }
            case 3: {
                //add course
                clearTerminal();
                if (sp->getRegisteredCourses() == nullptr) {
                    std::cout << "Create a registartion record first\n";
                    break;
                    std::cout << "\n";
                }
                int cid;
                std::cout << "insert course ID: ";
                std::cin >> cid;
                int credits = registrationSystem.checkIfCourseExists(cid);
                if (credits == -1)
                {
                    std::cout << "Course  ID not Found in offered courses\n";
                    break;
                }
                if (sp->addCourse(cid, credits))
                    std::cout << "course was added successfully\n";
                else
                    std::cout << "course was NOT added\n";
                break;
               
            }
            case 4: {
                //drop course
                clearTerminal();
                if (sp->getRegisteredCourses() == nullptr) {
                    std::cout << "Create a registartion record first\n";
                    break;
                }
                int cid;
                std::cout << "insert course ID, then course credit hours: ";
                std::cin >> cid ;
                int credits = registrationSystem.checkIfCourseExists(cid);
                if (credits == -1)
                {
                    std::cout << "Course  ID not Found in offered courses\n";
                    break;
                }
                if (sp->dropCourse(cid, credits))
                    std::cout << "course was removed successfully\n";
                else
                    std::cout << "course was NOT removed\n";

                break;
                
            }
            case 5: {
                //create registration record
                clearTerminal();
                sp->setCurRegistrationPtr(new Registration(sp->getId()));
                sp->setRegistered(true);
                registrationSystem.registrations.push_back(sp->getRegisteredCourses());
                std::cout << "registartion record was created successfully\n";
                break;
            }
            case 6: {
                //show all courses
                clearTerminal();
                for (int i = 0; i < registrationSystem.courses.size(); i++)
                    registrationSystem.courses[i]->info();
                std::cout << "\n";
                break;
               
            }

            case 7: {
                // reset pass
                clearTerminal();
                std::string pass;
                std::cout << "\n enter current password: ";
                std::cin.ignore();
                getline(std::cin, pass);
                if (pass == sp->getPassword())
                {
                    std::cout << "enter new password:\n ";
                    getline(std::cin, pass);
                    sp->setPassword(pass);
                    std::cout << "\n";
                }

                break;
              
            }

            
                  // Add other cases for different menu options
            case 0:
                clearTerminal();
                std::cout << "Exiting system...\n";
                break;
            default:
                clearTerminal();
                std::cout << "Invalid choice!\n";
            }
        }


    } while (choice != 0);

    // Save data before exiting
    registrationSystem.saveStudents(stdfile);
    registrationSystem.saveInstructors(instfile);
    registrationSystem.saveCourses(coursesfile);
    registrationSystem.saveRegistrations(regfile);

    return 0;
}