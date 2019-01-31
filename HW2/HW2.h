/* Fundamentals of Algorithms - Spring 2019
 * Elisa Danthinne
 * HW2
 */

#ifndef HW2_H
#define HW2_H

#include <string>
using namespace std;
class Person { // Class 1: Person class
	private: // member variables
	  string name;
	  string address;
	  int age;
	public:
	  void readPersonInfo(ifstream* pf); // read the person's three private attributes from the text file whose stream is pointed to by pf
	  void printPersonInfo(); // displays person's 3 private attributes
	  int personAGE(); // returns person's age
	  string personName(); // returns person's name
};

class Student : public Person { // Class 2: Student class derived from Person class
	private: // member variables
	  string ID;
	  string major;
	  float gpa;
	public:
	  void readStudentInfo(ifstream* pf); // calls readPersonInfo, then reads the student's 3 private attributes from the text file whose stream is pointed to by sf	
	  void printStudentInfo(); // invokes printPersonInfo, then prints student's 3 private attributes
	  void printInfo(); // added as a generic print function to be called from the anyList template
	  float studentGPA(); // returns student's GPA
};

class Course { // Class 3: Course class
	private: // member variables
	  string ID;
	  string title;
	  int credits;
	public:
	  Course(string i, string t, int c); // constructor
	  void printCourseInfo(); // displays the course's 3 private attributes
};

class CourseSection : public Course {
	private: // member variables
	  int sectionSize; // number of students enrolled in the section
	  Student *roster; // to store a list of the students' objects enrolled in the section
	public:
	  CourseSection(string i, string t, int c, int s);
	  void fillRosterInfo(ifstream* rf);  // read the info of all students in the section and store them in the roster; the students' info is stored in the text file whose stream is pointed to by rf
	  void printSectionInfo(); // prints the section info starting with its course info, followed by printing the info of all students in the section
	  Student* getStudent(int i); // return pointer for student at index i
	  ~CourseSection(); // destructor
};
#endif
