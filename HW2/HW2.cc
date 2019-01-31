/* Fundamentals of Algorithms - Spring 2019
 * Elisa Danthinne
 * HW2
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "HW2.h"

using namespace std;


void Person::readPersonInfo(ifstream* pf) // read the person's three private attributes from the text file whose stream is pointed to by pf
		{
		  getline(*pf, name);
		  getline(*pf, address);
		  string a; // convert from string to char to int
		  getline(*pf, a);
		  const char * ag = a.c_str();
		  age = atoi(ag);
		}
void Person::printPersonInfo() // displays person's 3 private attributes
		{ cout << name << "\t" << address << "\t" << age; }
int Person::personAGE() // returns person's age
		{ return age; }
string Person::personName() // returns person's name
		{ return name; }

void Student::readStudentInfo(ifstream* pf) // calls readPersonInfo, then reads the student's 3 private attributes from the text file whose stream is pointed to by sf
		{
		  readPersonInfo(pf); // call parent function
		  getline(*pf, ID);
		  getline(*pf, major);
		  string g; // convert from string to char to float
		  getline(*pf, g);
		  const char * gp = g.c_str();
		  gpa = atof(gp);
		}
void Student::printStudentInfo() // invokes printPersonInfo, then prints student's 3 private attributes
		{
		  printPersonInfo(); // call parent function
		  cout << "\t" << ID << "\t" << major << "\t" << gpa << "\n";
		}
void Student::printInfo() // added as a generic print function to be called from the anyList template
		{
		  printStudentInfo();
		}
float Student::studentGPA() // returns student's GPA
		{ return gpa; }


// Course class implementation	  
Course::Course(string i, string t, int c) // constructor
		{
		  ID = i;
		  title = t;
		  credits = c;
		}
void Course::printCourseInfo() // displays the course's 3 private attributes
		{
		  cout << "\nID: " << ID;
		  cout << "\nTitle: " << title;
		  cout << "\nCredits:" << credits;
		}
	  
CourseSection::CourseSection(string i, string t, int c, int s) : Course(i, t, c)
		{ 
		  sectionSize = s;
		  roster = new Student [s];
		}
void CourseSection::fillRosterInfo(ifstream* rf)  // read the info of all students in the section and store them in the roster; the students' info is stored in the text file whose stream is pointed to by rf
		{
		  for(int i=0; i < sectionSize; i++){
			cout << "---\nStudent " << i+1 << "\n";
			Student student;
			student.readStudentInfo(rf);
			*(roster+i)=student;
		  }
		}
void CourseSection::printSectionInfo() // prints the section info starting with its course info, followed by printing the info of all students in the section
		{
		  printCourseInfo();
		  cout << "\nSection Size: " << sectionSize;
		  cout << "\nRoster: \n";		  
		  cout << "Seq\t" << "Name\t\t" << "Address\t\t" << "Age\t" << "ID\t\t" << "Major\t" << "GPA\n";
		  cout << "===\t" << "====\t\t" << "=======\t\t" << "===\t" << "==\t\t" << "=====\t" << "===\n";
		  for(int i=0; i < sectionSize; i++){ // print each object in roster
			cout << i+1 << "\t";
			roster[i].printStudentInfo();
		  }
		}
Student* CourseSection::getStudent(int i) // return pointer for student at index i
		{
			return (roster+i);
		}
	
CourseSection::~CourseSection() // destructor
		{
		  if(sectionSize) delete [] roster;
		}


// template class implementation
template<class T, class P>
class anyList {
	private:
	T * ListKeys;
	P * ListObjectsP; // store a list of type P that is pointer to object with corresponding key
	int lCapacity; // max # elements allowed in the list
	int lSize;

	public:
	anyList(int cap) // constructor based on size, Lecture 2 slides
	  	{
		  ListKeys = new T[cap];
		  ListObjectsP = new P[cap];
		  lCapacity = cap;
		  lSize = 0;
	  	}

	void addListKey(T ky, P objp) // add ky to ListKeys, objp to ListObjectsP updates lSize 
	  	{
		  ListKeys[lSize] = ky;
		  ListObjectsP[lSize] = objp;
		  lSize = lSize + 1;
	  	}
	void dispList() // display the list contents, Lecture 2 slides
		{
		  cout << "Seq\t" << "Name\t\t" << "Address\t\t" << "Age\t" << "ID\t\t" << "Major\t" << "GPA\n";
		  cout << "===\t" << "====\t\t" << "=======\t\t" << "===\t" << "==\t\t" << "=====\t" << "===\n";
		  for(int i=0; i<lSize; i++) // print info for each item in roster
			{
				cout << i << "\t";
				ListObjectsP[i]->printInfo();
			}
		}
	void sortList() // inertion sort algorithm, Lecture 2 slides
		{
		  int j;
		  T temp1;
		  P temp2;
		  for(int i=0; i<lSize; i++){
			j=i;
			while(j>0 && ListKeys[j] < ListKeys[j-1]){ // sort according to ListKeys
			  temp1 = ListKeys[j]; // reorder listkeys
			  ListKeys[j] = ListKeys[j-1];
			  ListKeys[j-1] = temp1;
			  temp2 = ListObjectsP[j]; // reorder listobjects
			  ListObjectsP[j] = ListObjectsP[j-1];
			  ListObjectsP[j-1] = temp2;
			  j--;
			}
		  }
		}
	~anyList() // destructor
		{
		  delete[] ListObjectsP;
		  delete[] ListKeys;
		}
};

// main function
int main() {
	int num, cr;
	string id, tl;
	ifstream inf; // create and open ifstream file
	inf.open("./section01.txt");
	if (inf.fail()){
	    cerr << "Error: Could not open input file\n";
	    exit(1);
	}
	// activate the exception handling of inf stream
	inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);  

	cout << "Course ID? ";   
	cin >> id; cin.get(); //remove the leftover "new line" character from cin
	cout << "Course Title? ";
	getline(cin, tl);
	cout << "Course Credits?";    
	cin >> cr; cin.get(); //remove the leftover "new line" character from cin
	cout << "How many students in the course section? ";  
	cin >> num; cin.get(); //remove the leftover "new line" character from cin
	CourseSection sec(id, tl, cr, num);

	sec.fillRosterInfo(&inf); //ifstream cannot be passed by value
	cout << "The following is the section info (course and students info):\n";
	sec.printSectionInfo();
	inf.close(); //closes the file stream
	//Displaying the students ino sorted by name
	anyList<string, Student*> nameList(num);
	for (int i = 0; i < num; i++)  
	     nameList.addListKey(sec.getStudent(i)->personName(), sec.getStudent(i));
        nameList.sortList();
        cout << "\nThe students sorted by name:\n"; nameList.dispList();
        //Displaying the students ino sorted by age
        anyList<int, Student*> ageList(num);
        for (int i = 0; i < num; i++)  
             ageList.addListKey(sec.getStudent(i)->personAGE(), sec.getStudent(i));
        ageList.sortList();
        cout << "\nThe students sorted by age:\n"; ageList.dispList();
        //Displaying the students ino sorted by GPA
        anyList<float, Student*> gpaList(num);
        for (int i = 0; i < num; i++)  
        	gpaList.addListKey(sec.getStudent(i)->studentGPA(), sec.getStudent(i));
        gpaList.sortList();
	cout << "\nThe students sorted by GPA:\n"; gpaList.dispList();
	return 0;
}
