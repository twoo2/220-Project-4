//Tyler Woo
//Project 4
//Recursion

// The aim of this assignment is to make sure that you understand and are familiar 
// with the concepts covered in the lectures, including array, character, string, 
// pointer, structures, linked list, parameter passing, recursion, and 
// multi-dimensional dynamic array.

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

struct Book { //Struct for each book node
    char title[50]; //First char at title[0] is the key for the binary tree
    char url[50];
    Book *left; //Point to books to the left on the bookshelf
    Book *right; //Point to books to the right on the bookshelf
};

class Contact {
private:
	char cAddress[75];
	char cPhone[25];
	char cEmail[75];
public:
	void setAddress(char *cAddress) {strcpy(this->cAddress, cAddress);} // strcpy is the new version of strcpt
	void setPhone(char *cPhone) { strcpy(this->cPhone, cPhone); }
	void setEmail(char *cEmail) { strcpy(this->cEmail, cEmail); }
	char* getAddress() { return cAddress; }
	char* getPhone() { return cPhone; }
	char* getEmail() { return cEmail; }
	
	Contact(char *cAddress, char *cPhone, char *cEmail) { // constructor
		setAddress(cAddress);
		setPhone(cPhone);
		setEmail(cEmail);
	}
};

class Personnel {
private:
	char cName[50];
	int iId;
	char cBirthday[11];
	protected:
	Contact *pContact;
public:
	void setName(char *cName) { strcpy(this->cName, cName); }
	void setBirthday(char *cBirthday) {strcpy(this->cBirthday, cBirthday);}
	void setId(int iId) { this->iId = iId; }
	char* getName() { return cName; }
	int getId() { return iId;}
	char* getBirthday() { return cBirthday; }
	Contact * getContact() { return pContact; }
	
	virtual void display() {
		cout << "PERSONNEL" << endl;
		cout << "Name:\t" << getName() << endl;
		cout << "Id:\t" << getId() << endl;
		cout << "Birthday:\t" << getBirthday() << endl;
		cout << "Address:\t" << pContact->getAddress() << endl;
		cout << "Phone:\t" << pContact->getPhone() << endl;
		cout << "Email:\t" << pContact->getEmail() << endl;
	}
	
	Personnel(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail) { // constructor
		static int iIdCounter = 0;
		setName(cName); // set Name
		setId(iIdCounter); // set Id by a self-incremental counter
		iIdCounter++; // increment the ID generator;
		setBirthday(cBirthday); // set Birthday
		pContact = new Contact(cAddress, cPhone, cEmail);
	}
	
	virtual ~Personnel() { // destructor
		delete pContact; // delete the object linked to pContact
		pContact = NULL; // Make sure pContact not point to an object
	}
};

class Employee : public Personnel { // inherit from Personnel
private:
	char cDepartment[75];
	float fSalary;
	char cRank[75];
public:
	void setDepartment(char *cDepartment) {strcpy(this->cDepartment, cDepartment);}
	void setSalary(float fSalary) { this->fSalary = fSalary; }
	virtual void setRank(char *cRank) { strcpy(this->cRank, cRank); }
	char* getDepartment() { return cDepartment; }
	float getSalary() { return fSalary; }
	virtual char* getRank() { return cRank; }
	
	void display() {
		Personnel::display();
		cout << "EMPLOYEE" << endl;
		cout << "Department:\t" << getDepartment() << endl;
		cout << "Salary:\t" << getSalary() << endl;
		cout << "Rank:\t" << getRank() << endl;
	}
	
	Employee(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, char *cDepartment, float fSalary, char *cRank)
	: Personnel(cName, cBirthday, cAddress, cPhone, cEmail)
	{
		setDepartment(cDepartment);
		setSalary(fSalary);
		setRank(cRank);
	}
	
	virtual ~Employee() { // destructor
		delete pContact; // delete the object linked to pContact
		pContact = NULL; // Make sure pContact does not point to
	} // any object
};

class Faculty : public Employee { // inherit from Employee
private:
	char cResearch[75];
public:
	virtual void setResearch(char *cResearch) {
		strcpy(this->cResearch, cResearch);
	}
	char* getResearch() { return cResearch; }
	
	virtual void display() {
		Employee::display();
		cout << "FACULTY" << endl;
		cout << "Research\t" << getResearch() << endl;
	}
	
	Faculty(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, char *cDepartment, float fSalary, char *cRank, char *cResearch)
	: Employee(cName, cBirthday, cAddress, cPhone, cEmail, cDepartment, fSalary, cRank)
	{
		setResearch(cResearch);
	}
	
	virtual ~Faculty() { // destructor
		delete pContact; // delete the object linked to pContact
		pContact = NULL; // Make sure pContact does not
	} // point to any object
};

class PersonnelNode { // This is a container class
private:
	Personnel *pNode; // It contains a Personnel class
	PersonnelNode *pNext; // pointer used to form a linked list
public:
	void setNode(Personnel *pNode) { this->pNode = pNode; }
	void setNext(PersonnelNode *pNext) { this->pNext = pNext; }
	Personnel* getNode() { return pNode; }
	PersonnelNode* getNext() { return pNext; }
	
	PersonnelNode() { // constructor
		pNode = NULL;
		pNext = NULL;
	}
} *head = NULL;// declare a global pointer variable head


class Student : public Personnel { //inherit from Personnel
private:
    enum level {
        freshman=9, sophomore=10, junior=11, senior=12
    } gradeLevel;
public:
    int count; //Increment with each book added and reset whenever all books are deleted.
    struct Book *bookTree;
    void setBook(struct Book* tree) { //Set the head of the book tree
        bookTree = tree;
    }
    void setLevel(int l) { //Set the grade level of the student
        switch(l) {
            case 9:
                gradeLevel=freshman;
                break;
            case 10:
                gradeLevel=sophomore;
                break;
            case 11:
                gradeLevel=junior;
                break;
            case 12:
                gradeLevel=senior;
                break;
            default:
                cout << "Not an acceptable level." << endl;
                break;
        }
    }
    struct Book* getBook() { //Return the head of the book tree
        return bookTree;
    }
    level getLevel() { //Return the grade level
        return gradeLevel;
    }
    void display() { //Display the grade level and all the book titles
        Personnel::display();
        cout << "STUDENT" << endl;
        cout << "Level: " << getLevel() << endl;
        cout << "Title before call: " << this->bookTree->title << endl;
        if(bookTree != NULL) {
        displayBooks(this->bookTree);
        }
    }
    void displayBooks(struct Book *p) { //Display all the book titles
        cout << "Entered display books" << endl;
        if(p != NULL) {
            cout << "Title: " << p->title << endl;
            if(p->left != NULL) {
                displayBooks(p->left);
            }
            else if(p->right != NULL) {
                displayBooks(p->right);
            }
        }
    }
    Student(char *cName, char *cBirthday, char *cAddress, char *cPhone, char *cEmail, int lev)
    : Personnel(cName, cBirthday, cAddress, cPhone, cEmail) { //Constructor
        this->bookTree=NULL;
        setLevel(lev);
        
    }
    virtual ~Student() { //Destructor
        delete pContact;
        pContact=NULL;
    }
};

// Forward declaration of global functions outside any class
int main(); // The main function
void menu(); // display main choices
void branching(char); // branch to the chosen function
void sub_menu(); // display different insertion options
void insert(); // call sub_menu() and branch to chosen function
int insert_personnel(); // insert a personnel node
int insert_employee(); // insert an employee node
int insert_faculty(); // insert a faculty node
void remove(); // call remove function
void display_all(); // display members in all nodes in the linked list
void display_node(Personnel*, int); // display the members in one node
int insert_student(); //Insert a student node
int insert_book(Student*); //Insert a book in the correct place in a specific student node
int searchTree(Student*, char*); //Search for a specific book title in a specific student node
void deleteTree(struct Book*); //Delete the book tree
Student* find_student(); //Return a student node based on title information entered by the user

int main() { // main function is the entry point of the program
	char ch;
	cout << "CLASSES INHERITANCE, HIERARCHY AND POLYMORPHISM" << endl;
	cout << "***********************************************" << endl;
	do {
		menu(); // display choices
		cin >> ch; // enter a choice from the keyboard
		ch = tolower(ch); // convert to lower case
		branching(ch); // branch to the chosen function
	} while (ch != 'q'); // 'q' for quit

	return 0;
}

void menu() {
	cout << endl << endl << "MENU" << endl;
	cout << "----" << endl;
	cout << "i: Insert a new entry." << endl;
	cout << "d: display all entries." << endl;
	cout << "r: remove an entry." << endl;
	cout << "s: search all books." << endl;
	cout << "b: delete all books." << endl;
	cout << "q: Quit the program." << endl;
	cout << endl << "Please enter your choice (i, d, r, s, b, or q) --> ";
}

void branching(char c) { // branch to chosen function
	char title[50];
	Student* p;
	switch(c) {
		case 'i': insert();
			break;
		case 'd': display_all();
			break;
		case 'r': remove();
			break;
		case 's': 
			cout << "Enter a book title for which to search." << endl;
			cin.ignore();
			cin.getline(title,50); //The user will enter the title of the book
			if(searchTree(find_student(), title) != 0) {
				cout <<"@SEARCH OPERATION FAILED." << endl;
			}
			break;
		case 'b':
			p = find_student();
			deleteTree(p->getBook());
			break;
		case 'q': 
			cout << endl << "@Exiting the program..............." << endl;
			cin.get(); //type any key.
			break;
		default:
			cout << endl << "@ERROR - Invalid input." << endl;
			cout << "@Try again....." << endl;
	}
}

void sub_menu() { // display insertion options
	cout << endl << endl << "INSERTION SUB-MENU" << endl;
	cout << "------------------" << endl;
	cout << "p: insert a personnel entry." << endl;
	cout << "e: insert an employee entry." << endl;
	cout << "f: insert a faculty entry." << endl;
	cout << "s: insert a student entry." << endl;
	cout << "b: insert a book entry." << endl;
	cout << "q: Quit insertion and back to main menu." << endl;
	cout << endl << "Please enter your choice (p, e, f, s, b, or q) --> ";
}

// insert() is the umbrella insertion function that calls different insertion
// functions according to the selection in the sub-menu.
void insert() {
	char ch;
	cout << endl << "@Insertion module...............";
	do {
		sub_menu();
		cin >> ch;
		ch = tolower(ch);
		switch(ch) {
			case 'p': if(insert_personnel() != 0)
			cout << "@INSERTION OPERATION FAILED." << endl;
			else
			cout << "@INSERTED SUCCESSFULLY." << endl;
			break;
			case 'e': if(insert_employee() != 0)
			cout << "@INSERTION OPERATION FAILED." << endl;
			else
			cout << "@INSERTED SUCCESSFULLY." << endl;
			break;
			case 'f': if(insert_faculty() != 0)
			cout << "@INSERTION OPERATION FAILED." << endl;
			else
			case 's': if(insert_student() != 0)
			cout << "@INSERTION OPERATION FAILED." << endl;
			else
			break;
			case 'b': 
			if(insert_book(find_student()) != 0)
			cout << "@INSERTION OPERATION FAILED." << endl;
			else
			break;
			case 'q': cout << endl << "@Exiting the insertion..." << endl;
			cin.get();
			break;
			default: cout << endl << "@ERROR - Invalid input." << endl;
			cout << "@Try again....." << endl;
		}
	} while (ch != 'q');
}

int insert_personnel() { // insert a Personnel node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75];
	cout << endl << "@Inserting personnel node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore(); // fflush()
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	person = new Personnel(name, birthday, address, phone, email);
	node = new PersonnelNode();
	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_employee() { // insert an Employee node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], department[75], rank[75];
	float salary;
	cout << endl << "@Inserting employee node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address:";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	cout << "Enter the department: ";
	cin.getline(department, 75);
	cout << "Enter the salary. It must be a float number: ";
	cin >> salary;
	cout << "Enter the rank: ";
	cin.ignore();
	cin.getline(rank, 75);
	person = new Employee(name, birthday, address, phone, email, department, salary, rank);
	node = new PersonnelNode();
	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_faculty() { // insert a Faculty node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], department[75], rank[75], research[75];
	float salary;
	cout << endl << "@Inserting faculty node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	cout << "Enter the department: ";
	cin.getline(department, 75);
	cout << "Enter the salary. It must be a float number: ";
	cin >> salary;
	cout << "Enter the rank: ";
	cin.ignore();
	cin.getline(rank, 75);
	cout << "Enter the research: ";
	cin.getline(research, 75);
	person = new Faculty(name, birthday, address, phone, email, department, salary, rank, research);
	node = new PersonnelNode();
	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

/* void remove() function removes a node in the linked list. In the remove function, an id number will be entered as the key. The node whose id field stored an id number that is equal to the entered id number will be removed. */
void remove() {
	int id;
	PersonnelNode *temp, *prev;
	Personnel *person;
	int index = 1;
	cout<<"Remove module...............\n" << endl ;
	cout<<"Please enter the ID number of the person to be deleted: "<<endl;
	cin>> id;
	temp = head;
	while (temp != NULL) {
		person = temp->getNode();
		if (id != person->getId()){
			prev = temp;
			temp = temp->getNext();
			index++;
		}
		else {
			cout <<"Person to delete is found at index" << index<<endl;
			display_node(person, index);
			if(temp != head)
			prev->setNext(temp->getNext());
			else
			head = head->getNext();
			delete person; // explicit garbage-collection
			person = NULL; // Make person not to point to any object
			delete temp; // explicit garbage-collection
			temp = NULL; // Make temp not to point to any object
			return;
		}
	}
	cout <<"The person with ID = << id << does not exist."<< endl;
}

void display_all() { // Display contents of all nodes in the linked list
	PersonnelNode *node;
	int node_count= 0;
	cout << endl << "@Display module...............";
	node = head;
	while(node != NULL) {
		display_node(node->getNode(), ++node_count);
		node = node->getNext();
	}
	cout << endl << "@No more records." << endl;
}

void display_node(Personnel *node, int index) {// Display contents of node
	cout << endl << "Record " << index << "." << endl;
	node->display();// Polymorphic call. Depending on the object pointed to
}

void deleteTree(struct Book *head) { // Delete
    if (head == 0) return;
	if (head->left != NULL)  // size-m problem
		deleteTree (head->left);
	if (head->right != NULL) // size-m problem
		deleteTree (head->right);
	delete head;
	return;
}

Student* find_student() {
	char name[50];
	PersonnelNode *temp, *prev;
	Student *person;
	cout<<"Please enter the name of the student: "<<endl;
	cout << "Enter the name: ";
	cin.ignore(); // fflush()
	cin.getline(name, 50);
	temp = head;
	while (temp != NULL) {
		person = (Student*) temp->getNode();
		if (strcmp(name,person->getName()) != 0){
			prev = temp;
			temp = temp->getNext();
		}
		else { // Found the student
			delete temp; // explicit garbage-collection
			temp = NULL; // Make temp not to point to any object
			return person;
		}
	}
	cout << "Could not find specified student." << endl;
	return NULL;
}

int searchTree(Student* student, char* title) {
    char key = title[0];
    struct Book* temp = student->getBook();
    while(temp != NULL) {
        if(temp->title[0] == key) {
            cout << "Title: " << temp->title << endl;
            cout << "URL: " << temp->url << endl;
            delete temp;
            temp = NULL;
            return 0;
        }
        if(temp->title[0] < key) {
            temp = temp->right;
        }
        if(temp->title[0] > key) {
            temp = temp->left;
        }
    }
        cout << "Could not find specified book." << endl;
        delete temp;
        temp = NULL;
        return -1;
}

int insert_student() {		// insert a Student node
	Personnel *person = NULL;
	PersonnelNode *node = NULL;
	char name[50], birthday[11], address[75], phone[25], email[75], id[15];
	int level;
	bool real = false;

	cout << endl << "@Inserting student node.........." << endl;
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "Enter the birthday, e.g., 05/24/1985: ";
	cin.getline(birthday, 11);
	cout << "Enter the address: ";
	cin.getline(address, 75);
	cout << "Enter the phone number: ";
	cin.getline(phone, 25);
	cout << "Enter the email: ";
	cin.getline(email, 75);
	
	do{
		cout << "Enter the level. It must be an integer value (9 for freshmen, 10 for sophomore, 11 for junior, or 12 for senior: ";
		cin >> level;	//check syntax
		
		if (level == 9 || level == 10 || level == 11 || level == 12)
		{
			real = true;
		}
	}while(!real);
	

	person = new Student(name, birthday, address, phone, email, level);
	node = new PersonnelNode();

	if((person != NULL) && (node != NULL)) {
		node->setNode(person);
		node->setNext(head);
		head = node;
		return 0;
	}
	else {
		cout << endl << "@ERROR - Could not allocate enough memory!" << endl;
		return -1;
	}
}

int insert_book(Student* student)
{
	char title[50], url[50];

	if (student == NULL)
	{
		return -1;
	}
	
	cout << "name: " << student->getName() << endl;
	cout << endl << "@Inserting book.........." << endl;
	cout << "Enter the title: ";
	cin.getline(title,50);
	cout << "Enter the url: ";
	cin.getline(url, 50);	

	cout << "Url saved" << endl;
    char key = title[0];
    cout << "key = " << key << endl;
    struct Book* temp = student->getBook();
    
	while(temp != NULL) {	
		if(key > temp->title[0])
		{
			cout << "key > title" << endl;
			if(temp->left == NULL)
			{
				cout << "left is null" << endl;
				strcpy(temp->title, title);
				strcpy(temp->url, title);
				temp->left = NULL;
				temp->right = NULL;
				student->bookTree=temp;
				delete temp;
				cout << "delete temp" << endl;
				temp=NULL;
				cout << "temp=null" << endl;
				return 0;
			}
			else
			{
				temp = temp->left;
			}
		}
		if(key <= temp->title[0])
		{
			cout << "key <= title" << endl;
			if(temp->right == NULL)
			{
				cout << "right is null" << endl;
				strcpy(temp->title, title);
				strcpy(temp->url, title);
				temp->left = NULL;
				temp->right = NULL;
				student->bookTree=temp;
				delete temp;
				cout << "delete temp" << endl;
				temp=NULL;
				cout << "temp=null" << endl;
				return 0;
			}	
			else
			{
				temp = temp->right;
			}
		}
	}
	
    struct Book gnu;
    cout << "temp is null" << endl;
    strcpy(gnu.title,title);
	cout << "title copied" << endl;
	strcpy(gnu.url, url);
	cout << "url copied" << endl;
	gnu.left = NULL;
	cout << "left set to null" << endl;
	gnu.right = NULL;
	cout << "right set to null" << endl;
	student->bookTree = &gnu;
	cout << "student->bookTree->title = " << student->getBook()->title << endl;
	
	return 0;
}