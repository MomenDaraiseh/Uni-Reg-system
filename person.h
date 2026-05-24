#pragma once
#include <string>

class Person {
protected:
	//attributes
	std::string name;
	int id;

public:
	//declarations
	Person(std::string name, int id) :name(name), id(id) {}
	int getId() { return id; }
	std::string getName() { return name; }
	virtual void info() {}

};