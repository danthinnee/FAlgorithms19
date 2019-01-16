#include <iostream>
using namespace std;
class Person { // Class 1: Person class
	private: // member variables
	  string name;
	  string address;
	  int age;
	public:
	  void readPersonInfo() // asks for keyboard inputs of the person's 3 private attributes
		{
		  cout << "\nName?: ";
		  cin.get();  getline(cin, name); //allows for spaces in the title but first clear the input buffer.
		  cout << "\nAddress?: ";
		  cin.get();  getline(cin, address); //allows for spaces in the title but first clear the input buffer.
		  cout << "\nAge?: ";
		  cin >> age;
		}
	  void printPersonInfo() // displays person's 3 private attributes
		{ cout << "\nName: " << name; 
		  cout << "\nAddress: " << address;
		  cout << "\nAge: " << age; }
	  int personAGE() // returns person's age
		{ return age; }
	  string personName() // returns person's name
		{ return name; }
};

class Student : public Person { // Class 2: Student class derived from Person class
	private: // member variables
	  string ID;
	  string major;
	  float gpa;
	public:
	  void readStudentInfo() // calls readPersonInfo, then asks for keyboard inputs of person's 3 private attributes
		{
		  readPersonInfo(); // call parent function
		  cout << "\nID?: ";
		  cin >> ID; 
		  cout << "\nMajor?: ";
		  cin.get();  getline(cin, major); //allows for spaces in the title but first clear the input buffer.
		  cout << "\nGPA? ";
		  cin >> gpa;
		}
	  void printStudentInfo() // invokes printPersonInfo, then prints student's 3 private attributes
		{
		  printPersonInfo(); // call parent function
		  cout << "\nID: " << ID;
		  cout << "\nMajor: " << major;
		  cout << "\nGPA: " << gpa;
		}
	  float studentGPA() // returns student's GPA
		{ return gpa; }
};

class Course { // Class 3: Course class
	private: // member variables
	  string ID;
	  string title;
	  int credits;
	public:
	  Course(string& i, string& t, int c) // constructor
		{
		  ID = i;
		  title = t;
		  credits = c;
		}
	  void printCourseInfo() // displays the course's 3 private attributes
		{
		  cout << "\nID: " << ID;
		  cout << "\nTitle: " << title;
		  cout << "\nCredits:" << credits;
		}
};

class CourseSection : public Course {
	private: // member variables
	  int sectionSize; // number of students enrolled in the section
	  Student *roster; // to store a list of the students' objects enrolled in the section
	public:
	  CourseSection(string& i, string& t, int c, int s) : Course(i, t, c)
		{ 
		  sectionSize = s;
		  roster = new Student [s];
		}
	  void fillRosterInfo()  // read the info of all students in the section and store them in the roster
		{
		  for(int i=0; i < sectionSize; i++){
			cout << "---\nStudent " << i+1 << "\n";
			Student student;
			student.readStudentInfo();
			*(roster+i)=student;
		  }
		}
	  void printSectionInfo() // prints the section info starting with its course info, followed by printing the info of all students in the section
		{
		  printCourseInfo();
		  cout << "\nSection Size: " << sectionSize;
		  cout << "\nRoster: ";		  
		  for(int i=0; i < sectionSize; i++){
			cout << "---\nStudent " << i+1 << "\n";
			roster[i].printStudentInfo();
		  }
		}
	  void printTopGPAStudent() // prints the info of the student with the highest GPA
		{
		  float max = 0; // maximum GPA
		  int sindex = 0; // index of student with maximum GPA
		  for(int i=0; i < sectionSize; i++){ // sequential search
			if(roster[i].studentGPA() > max)
			{
				max = roster[i].studentGPA();
				sindex = i;
			}
		  }
		  cout << "\nStudent " << sindex+1 << "\n";
		  roster[sindex].printStudentInfo(); // prints student info
		}
	  Student returnStudent(int i)
		{
		  return roster[i];
		}
	  ~CourseSection() // destructor
		{
		  delete [] roster;
		}
};

template <class T> // extra credit template class
class anyList {
	private:
	  T * ListElements;
	  int lSize;
	public:
	  anyList() // default constructor, Lecture 2 slides
	  	{
		  ListElements = new T[100];
		  lSize = 100; 
	  	}
	  anyList(int sz) // constructor based on size, Lecture 2 slides
	  	{
		  ListElements = new T[sz];
		  lSize = sz;
	  	}

	  void addElement(T e, int i) // add one element to list at index i 
	  	{
		  ListElements[i] = e;
	  	}
	  void dispList() // display the list contents, Lecture 2 slides
		{
		  for(int i=0; i<lSize; i++)
			cout << "-->" << ListElements[i] << endl;
		}
	  void sortList() // inertion sort algorithm, Lecture 2 slides
		{
		  int j;
		  T temp;
		  for(int i=0; i<lSize; i++){
			j=i;
			while(j>0 && ListElements[j] < ListElements[j-1]){
			  temp = ListElements[j];
			  ListElements[j] = ListElements[j-1];
			  ListElements[j-1] = temp;
			  j--;
			}
		  }
		} 
};


int main() {
	int num, cr;
	string id, tl;
	cout << "Course ID?: "; cin >> id;
	cout << "Course Title?: ";
	cin.get();  getline(cin, tl); //allows for spaces in the title but first clear the input buffer.
	cout << "Course Credits?: "; cin >> cr;
	cout << "How many students in the course section?: "; cin >> num;
	CourseSection sec(id, tl, cr, num);
	cout << "\n----------------------\n";
	cout << "Input the info of all students in the section:\n";
	sec.fillRosterInfo();
	cout << "\n----------------------\n";
	cout << "The following is the section info:\n";
	sec.printSectionInfo();
	cout << "\n----------------------\n";
	cout << "The student with the highest GPA:\n";
	sec.printTopGPAStudent();

	// extra credit implementation
	anyList<string> nameList(num);
	anyList<int> ageList(num);
	anyList<float> gpaList(num);

	for(int i=0; i<num; i++){
		nameList.addElement(sec.returnStudent(i).personName(),i);
		ageList.addElement(sec.returnStudent(i).personAGE(),i);
		gpaList.addElement(sec.returnStudent(i).studentGPA(),i);
	}
	
	nameList.sortList();
	ageList.sortList();
	gpaList.sortList();

	cout << "\nSorted Names:\n";
	nameList.dispList();
	cout << "\nSorted Ages:\n";
	ageList.dispList();
	cout << "\nSorted GPAs:\n";
	gpaList.dispList();
	
	return 0;
}
