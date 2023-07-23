#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

struct Course
{
	string courseNo;
	string courseName;
	int creditHr;
	string grade = "-";
	Course *next;
};

struct Student
{
	string id;
	string FirstName;
	string LastName;
	int age;
	char sex;
	Course *course1 = NULL;
	Student *next;
};

Student *head = NULL;

void mainPage();
void studentPage();
void teacherPage();

void registerStudent();
void registerCourse();
void assignCourse(Student*, string, string, int);
void addCourse(Student*, string);
void studentDetails();
void gradeReport();

void assignGrade();
void sortByName();
void viewAllStudents();
string computeGrade(double);
double calculateGPA(Student*);
int ects(string);
double score(string);
void deleteStudent();
void dropCourse();

Course* searchCourse(Student *, string);
Student* searchStudent(string);

bool areThereStudents();
bool isTakingCourse(Student*);


int main()
{

	mainPage();

	return 0;
}

void mainPage()
{
	int choice;
	do{
		system("@cls||clear");
		cout << "\t\t====================================\n";
		cout << "\t\t> STUDENT RECORD MANAGEMENT SYSTEM <\n";
		cout << "\t\t====================================\n\n";

		cout<<"Log in as:\n";
		cout<<"\t1. Student\n";
		cout<<"\t2. Teacher\n\n";
		cout<<"Enter 0 to Exit\n";
		cout<<"Your choice: ";

		cin>>choice;

		switch(choice){
			case 1:
				studentPage();
				break;

			case 2:
				teacherPage();
				break;

			case 0:
				cout<<"\nApplication Closed\n\n";
				break;
			default:
				cout<<"Invalid Input";
				cin.ignore();
				getch();
		}


	}while(choice != 0);
}

void studentPage()
{
	char choice;
	do{
		system("@cls||clear");
		cout << "\t\t====================================\n";
		cout << "\t\t> STUDENT RECORD MANAGEMENT SYSTEM <\n";
		cout << "\t\t====================================\n\n";

		cout << "\t\b1. Register Student\n";
		cout << "\t\b2. Register Course\n";
		cout << "\t\b3. View Student's details\n";
		cout << "\t\b4. Grade Report\n";
		cout << "\t\b0. Log out\n\n";

		cout << "Enter your choice: ";
		cin >> choice;

		switch(choice){
			case '1':
				registerStudent();
				break;
			case '2':
				registerCourse();
				break;
			
			case '3':
				studentDetails();
				break;
			
			case '4':
				gradeReport();
				break;
			
			case '0':
				break;

			default:
				cout<<"Invalid Input";
				cin.ignore();
				getch();
		}
	}while(choice != '0');
}

void teacherPage()
{
	char choice;
	do{
		system("@cls||clear");
		cout << "\t\t====================================\n";
		cout << "\t\t> STUDENT RECORD MANAGEMENT SYSTEM <\n";
		cout << "\t\t====================================\n\n";

		cout << "\t\b1. Submit Grade\n";
		cout << "\t\b2. View All Students' details\n";
		cout << "\t\b3. Delete Student data\n";
		cout << "\t\b4. Drop Course\n";
		cout << "\t\b0. Log out\n\n";

		cout << "Enter your choice: ";
		cin >> choice;

		switch(choice){
			case '1':
				assignGrade();
				break;
			
			case '2':
				sortByName();
				viewAllStudents();
				break;
			
			case '3':
				deleteStudent();
				break;
			
			case '4':
				dropCourse();
				break;

			case '0':
				break;

			default:
				cout<<"Invalid Input";
				cin.ignore();
				getch();

		}
	}while(choice != '0');
}

void registerStudent()
{
	system("@cls||clear");
	Student *temp = new Student;
	Student *current;

	cout << "Full Name: ";
	cin >> temp -> FirstName;
	cin >> temp -> LastName;
	
	cout << "ID No: ";
	cin >> temp -> id;
	temp -> id = temp -> id.substr(0, 11);

	cout << "Age: ";
	cin >> temp -> age;
	
	cout << "Sex: ";
	cin >> temp -> sex;

	temp -> next = NULL;

	Student* duplicateID = searchStudent(temp->id);

	if (head == NULL)
		head = temp;

	else if(duplicateID == nullptr){
		current = head;
	
		while(current->next != nullptr)
			current = current->next;

		current->next = temp;
	}

	else{
		cout<<"There is already a student with id number: "<<temp->id<<endl;
		cin.ignore();
		getch();
		return;
	}

	cout<<"\nRegistration Successful\n";
	cin.ignore();
	getch();
}

void registerCourse()
{
	system("@cls||clear");

	if(!areThereStudents())
		return;

	cout << "\t\tCOURSE REGISTRATION\n\n";

	string key;
	Student *temp;
	
	cout << "Enter Your ID: ";
	cin >> key;
	temp = searchStudent(key);
	if(temp == nullptr){
		cout << "Student not found";
		cin.ignore();
		getch();
		return;
	}

	cout << "Name: " << temp -> FirstName + ' ' + temp -> LastName << endl;
	cout << "ID No: " << temp -> id << endl;
	cout << "Department: Computer Science\n";
	cout << "Year: III\n\n";

	cout << "Courses for this semester: \n";
	cout << "\t1. Fundamentals of Database\n";
	cout << "\t2. Software Engineering I\n";
	cout << "\t3. Calculus II\n";
	cout << "\t4. Global Trends\n";
	cout << "\t5. Introduction to probability theory\n";
	cout << "\t6. Data communication and networking\n";
	cout << "\t7. Data structures and algorithm analysis\n\n";
	cout << "Enter the numbers of the courses to be registered. Enter '8' to register to all courses\n";
	string choice;

	cin >> choice;
	if(choice == "8")
		choice = "1234567";

		addCourse(temp, choice);
		cout<<"Successfully registered to the selected courses";
	cin.ignore();
	getch();
}

void viewAllStudents()
{
	system("@cls||clear");
	Student *temp = head;
	cout << "\tLIST ALL STUDENTS\n\n";

	cout <<left <<setw(6) << "No" << setw(15) << "ID" << setw(20) << "Name" << setw(6) << "Age" << setw(6) << "Sex";

	for(int i = 1; temp != NULL; i++){
		cout <<endl <<setw(6) << i << setw(15) << temp -> id << setw(20) << temp -> FirstName + ' ' + temp -> LastName << setw(6) << temp->age << setw(6) <<temp->sex;
		temp = temp->next;

	}

	cin.ignore();
	getch();
}

Student* searchStudent(string key)
{
	Student *temp = head;
	while(temp != nullptr){
		if (temp -> id.compare(key) == 0)
			return temp;

		temp = temp -> next;
	}
	return nullptr;
}

Course* searchCourse(Student* temp, string key)
{
	Course* course = temp -> course1;

	while(course != nullptr){
		if (course -> courseNo.compare(key) == 0)
			return course;
		
		course = course -> next;
	}
	return nullptr;
}

void assignCourse(Student* temp, string courseName,string courseNo, int creditHr)
{
	Course* duplicateCourse = searchCourse(temp, courseNo);
	Course* currentCourse = new Course;
	Course* iterator;
	currentCourse -> next = nullptr;

	currentCourse -> courseName = courseName;
	currentCourse -> courseNo = courseNo;
	currentCourse -> creditHr = creditHr;

	if (temp -> course1 == NULL)
		temp -> course1 = currentCourse;
	else if(duplicateCourse == nullptr){
		iterator = temp -> course1;

		while(iterator -> next != nullptr)
			iterator = iterator -> next;

		iterator -> next = currentCourse;
	}
}

void addCourse(Student* temp,string choice)
{
	for (int i = 0; i < choice.length(); ++i)
	{
		switch(choice[i])
		{
			case '1':
				assignCourse(temp, "Fundamentals of Database", "CoSc3051", 4);
				break;
			case '2':
				assignCourse(temp, "Software Engineering I", "CoSc3311", 4);
				break;
			case '3':
				assignCourse(temp, "Calculus II", "Math2022", 4);
				break;
			case '4':
				assignCourse(temp, "Global Trends", "GlTr1012", 2);
				break;
			case '5':
				assignCourse(temp, "Introduction to probability theory", "Stat2182", 3);
				break;
			case '6':
				assignCourse(temp, "Data communication and networking", "CoSc3211", 3);
				break;
			case '7':
				assignCourse(temp, "Data structures and algorithm analysis", "CoSc3111", 3);
				break;


		}
	}
}

void deleteStudent()
{
	system("@cls||clear");

	if(!areThereStudents())
		return;
	string id;

	Student* current = head;
	Student* previous = head;

	cout<<"\t\tDELETE STUDENT DATA\n\n";
	cout<<"Enter Student ID number: ";
	cin>>id;

	while(id.compare(current -> id) != 0)
	{
		current = current->next;
		if(current == nullptr)
		{
			cout<<"\nStudent not found\n";
			cin.ignore();
			getch();
			return;
		}
	}

	if(current == head)
	{
		head = head->next;
		delete current;
	}
	

	else
	{
		while(previous ->next != current)
			previous = previous->next;

		previous->next = current->next;
		delete current;
	}
	cout<<"\nDeleted Successfully\n";
	cin.ignore();
	getch();
}

void dropCourse()
{
	system("@cls||clear");
	
	if(!areThereStudents())
		return;

	string id;
	string courseCode;

	cout<<"\t\tDrop Course\n\n";
	cout<<"\nEnter Student ID number\n-> ";
	cin>>id;
	
	Student* temp = searchStudent(id);
	if (temp == nullptr)
	{
		cout<<"\nStudent not found.\n";
		cin.ignore();
		getch();
		return;
	}
	
	Course *current = temp -> course1;
	Course *previous = temp -> course1;

	if (current == nullptr){
		cout << "\nNo courses to delete!\n";
		cin.ignore();
		getch();
		return;
	}
	// courseCode = (searchCourse(temp, courseCode))->courseNo;
	
	cout<<"Enter Course Code\n-> ";
	cin>>courseCode;

	while ((current -> courseNo).compare(courseCode) != 0)
	{
		current = current -> next;
		if(current == nullptr){
			cout<<"\nCourse not found\n";
			cin.ignore();
			getch();
			return;
		}
	}

	if (current == temp -> course1)
	{
		temp -> course1 = temp -> course1 -> next;
		delete current;
	}

	else{
		while(previous -> next != current)
			previous = previous -> next;
		previous -> next = current -> next;
		delete current;
	}
	
	cout<<"\nCourse dropped successfully\n";
	cin.ignore();
	getch();
}

void studentDetails()
{
	system("@cls||clear");

	if(!areThereStudents())
		return;

	string key;
	cout << "Enter ID No: ";
	cin >> key;

	Student *temp = searchStudent(key);
	
	if(temp == nullptr){
		cout << "\nStudent not found\n";
		cin.ignore();
		getch();
		return;
	}

	Course *current = temp -> course1;

	cout << "\nName: " << temp -> FirstName + ' ' + temp -> LastName << endl;
	cout << "ID No: " << temp->id << endl;
	cout << "Department: Computer Science\n";
	cout << "Year: III\n\n";

	cout << "Regitered to:\n";
	cout <<setw(6) << left << "No" << setw(45) << "Course Title" << setw(12) << "Course Code" << setw(15) << "Credit Hours\n";
	for (int i = 1; current != nullptr; ++i)
	{
		cout << endl << setw(6) << i << setw(45) << current -> courseName << setw(12) << current -> courseNo << setw(15) << current -> creditHr;
		current = current -> next;
	}
	cin.ignore();
	getch();
}

void sortByName()
{
	Student * head2 = nullptr;
	Student * iterator = head2;
	Student * current = head;
	Student * temporary;
	if(head == nullptr || head->next == nullptr)
		return;

	while(current != nullptr)	
	{
		temporary = current->next;

		if(head2 == nullptr)
		{
			head2 = current;
			head2->next = nullptr;	
		}

		else
		{
			iterator = head2;

			if((current->FirstName + current->LastName).compare(iterator->FirstName + iterator->LastName)== -1)
			{
				current->next = iterator;
				head2 = current;
			}

			else
			{
				while(iterator->next != nullptr){
					if((current-> FirstName + current->LastName).compare(iterator->next->FirstName + iterator->next->LastName) == 1)	
						iterator = iterator->next;
					else break;
			}

			current->next = iterator->next;
			iterator -> next = current;
			}
		}	
		current = temporary;
	}
	head = head2;
}

void assignGrade()
{
	system("@cls||clear");
	Student *temp = head;
	Course *current;
	
	if(!areThereStudents())
		return;
	

	bool courseHaveStudents = false;
	double mark;
	string key;

	cout << "\t\tSubmit Grade\n\n";
	cout << "Enter Course Code: ";
	cin >> key;
	cout<<endl;

	for (int i = 1; temp != nullptr; ++i)
	{
		
		current = searchCourse(temp, key);
		if (current == nullptr)
		{
			temp = temp -> next;
			i--;
			continue;
		}

		courseHaveStudents = true;
		cout << setw(6) << left << i << setw(12) << temp -> id << setw(20) << temp -> FirstName + ' ' + temp -> LastName << "Total Mark: ";
		cin >> mark;
		current -> grade = computeGrade(mark);
		temp = temp -> next;
	
	}

	if(!courseHaveStudents){
		cout<<"No student are taking this course currently";
		cin.ignore();
		getch();
	}
	cout<<"\nSubmitted successfully\n";
}

string computeGrade(double mark)
{
	if(mark >= 90)
		return "A+";
	else if (mark >= 83)
		return "A";
	else if (mark >= 80)
		return "A-";
	else if (mark >= 75)
		return "B+";
	else if (mark >= 68)
		return "B";
	else if (mark >= 60)
		return "B-";
	else if (mark >= 55)
		return "C+";
	else if (mark >= 50)
		return "C";
	else if (mark >= 45)
		return "C-";
	else if (mark >= 40)
		return "D";
	else 
		return "F"; 
}

void gradeReport()
{
	system("@cls||clear");
	
	if(!areThereStudents())
		return;

	string key;

	cout << "\t\bGRADE REPORT\n\n";
	cout << "Enter Student ID number: ";
	cin >> key;

	Student* temp = searchStudent(key);

	if (temp == nullptr)
	{
		cout << "\nStudent not found\n";
		cin.ignore();
		getch();
		return;
	}

	if (!isTakingCourse(temp))
		return;

	Course* current = temp -> course1;

	cout << left << setw(6) << "No" << setw(45) << "Course Title" << setw(12) << "Course Code" << setw(15) << "Credit Hour" << setw(6) << "Grade";
	
	for(int i = 1; current != nullptr; i++){
		cout << endl << setw(6) << i << setw(45) << current -> courseName << setw(12) << current -> courseNo << setw(15) << current -> creditHr << setw(6) << current -> grade;
		current = current->next;
	}

	double gpa = calculateGPA(temp);
	if(gpa == -1)
		cout << endl << "\n=> GPA: Not determined\n";
	else
		cout << endl << "\n=> GPA: " << setprecision(2) << gpa;
	
	cin.ignore();
	getch();
}

double calculateGPA(Student* temp)
{
	Course* current = temp ->course1;
	bool allGradesIn = true;
	int totalECTS = 0;
	double gpa = 0;
	while(current != nullptr && allGradesIn == true)
	{
		if(current->grade == "-"){
			
			allGradesIn = false;
		}
		current = current->next;
	}
	if (allGradesIn == false)
		return -1;
	current = temp->course1;
	while(current != nullptr)
	{
		gpa += ects(current->courseNo)*score(current->grade);
		totalECTS +=ects(current->courseNo);
		current = current->next;
	}

	gpa /= totalECTS;
	return gpa;
}

int ects(string courseNo)
{
	if(courseNo == "CoSc3051")
		return 6;
	else if(courseNo == "CoSc3311")
		return 6;
	else if(courseNo == "Math2022")
		return 7;
	else if(courseNo == "GlTr1012")
		return 4;
	else if(courseNo == "Stat2182")
		return 5;
	else if(courseNo == "CoSc3211")
		return 5;
	else if(courseNo == "CoSc3111")
		return 5;
	else
		return -1;
}

double 	score(string grade)
{
	if(grade == "A+" || grade == "A")
		return 4;
	else if (grade == "A-")
		return 3.75;
	else if (grade == "B+")
		return 3.5;
	else if (grade == "B")
		return 3;
	else if (grade == "B-")
		return 2.75;
	else if (grade == "C+")
		return 2.5;
	else if (grade == "C")
		return 2;
	else if (grade == "C-")
		return 1.5;
	else if (grade == "D")
		return 1;
	else if (grade == "F")
		return 0;
	else
		return -1;
}

bool areThereStudents(){
	if (head == nullptr)
	{
		cout<<"\nNo students are registered\n";
		cin.ignore();
		getch();
		return 0;
	}
	return 1;
}

bool isTakingCourse(Student* temp){
	if(temp->course1 == nullptr)
	{
		cout<<"\nNot registered to any course\n";
		cin.ignore();
		getch();
		return 0;
	}
	return 1;
}