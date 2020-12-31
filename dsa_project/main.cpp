#include <iostream>  // Main C++ STD Library
#include <Windows.h>  // To use function System
#include <string>  // To define string
#include<regex>  // To create regex
#include <ctime>  // To get time
#include<fstream>  // To read and write files
#include<vector>  // To use vector
#include <sstream>  // StringStrem to split the string
using namespace std;  // To use standard namespace

// For file handling
ofstream fout;
// For Color handling
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Employee {
private:  // Private functions and variables

	// Structure to be used in doubly linked List to store the data
	struct Node
	{
		char id[13];  // To store Employee Id
		char name[21];  // To store Employee Name
		char qualification[21];  // To store Employee Qualificaion
		char address[31];  // To store Employee Address
		char city[21];  // To store Employee City
		char jobTitle[21];  // To store Employee Job Title
		double salary;  // To store Employee Salary
		char startDate[11];  // To store Employee Start Date
		Node* prev, * next;  // *next to hold next address and *prev to hold previous address of record
		// Starting point of linked list is Head
	} *Head = NULL;

	// Since we are asking for selection within the class therefore this will save that choice
	int choice = 0;

	// It will validate employee Id to be (Emp-xxxxx-xx where x is a number) by using a regex
	bool checkEmpId(string empId, int size) {
		// To set Color to red
		SetConsoleTextAttribute(hConsole, 12);
		// Regex to match our Id pattern
		regex regExp("(Emp-)[0-9]{5}(-)[0-9]{2}");
		// In this if, we are checking that id donot exceed 12 characters
		if (size > 12) {
			cout << "\n\t\tId should not exceed max 12 characters";
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		// Here we are matching the regex
		else if (!regex_match(empId, regExp)) {
			cout << "\n\t\tThe format of Id should be Emp-xxxxx-xx where x are the numbers!";
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		// Setting console text color to green
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	// It will check the length of string provided
	bool checkLength(int req_size, int pro_size) {
		// Setting console text color to red
		SetConsoleTextAttribute(hConsole, 12);
		// In this if, we are comparing string length
		if ((pro_size > req_size) || (pro_size < 3)) {
			cout << "\n\t\tField Should be at least 3 characters or donot exceed " << req_size << " characters\n";
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		// Setting console text color to green
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	// It will check whether it is a valid double i.e. it must not be a string or out of range value
	double checkDouble(string str) {
		// Setting console text color to red
		SetConsoleTextAttribute(hConsole, 12);
		double dob;
		// Using try catch to save our program from crashing
		try
		{
			// Trying to convert string to double
			dob = stod(str);
		}
		catch (const std::exception&)
		{
			// Catching if any exception occurs
			cout << "\n\t\tYour given value is either not a number or out of range!\n";
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return -1;
		}
		// Setting console text color to green
		SetConsoleTextAttribute(hConsole, 10);
		return dob;
	}

	// It will validate the date according to yyyy-mm-dd pattern
	bool checkDate(string empId, int size) {
		// Setting console text color to red
		SetConsoleTextAttribute(hConsole, 12);
		// Regex to compare dates
		regex regExp("\\b\\d{4}[-]\\d{2}[-]\\d{2}\\b");
		// Checking for string size and match
		if (size > 10 || !regex_match(empId, regExp)) {
			cout << "\n\t\tThe format of date should be yyyy-mm-dd!\n";
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		else {
			tm newTime;  // Creating object of struct tm
			time_t t = time(NULL);  // Creating Object of time_t and initializing it
			localtime_s(&newTime, &t);  // Getting local time and passing it to newTime variable
			int givenYear = stoi(empId.substr(0, 4));  // Slicing our year from provided string
			int givenMonth = stoi(empId.substr(5, 2));  // Slicing our month from provided string
			int givenDay = stoi(empId.substr(8, 2));  // Slicing our date from provided string
			int currentYear = 1900 + newTime.tm_year;  // Getting Current Year
			int currentMonth = newTime.tm_mon + 1;  // Getting Current Month
			int currentDay = newTime.tm_mday;  // Getting Current Day
			// Validating month that it should not be less than 1 or greater than 12
			if (givenMonth > 12 || givenMonth < 1) {
				cout << "\n\t\tPlease Correct Your Month Value!\n";
				// Setting console text color to green
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			// Validating day that it should not be less than 1 or greater than 31
			else if (givenDay > 31 || givenDay < 1) {
				cout << "\n\t\tPlease Correct Your Day Value!\n";
				// Setting console text color to green
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			// Checking that if given year is greater than current year
			else if (givenYear > currentYear) {
				cout << "\n\t\tHow can be start date year can be greater than current year!\n";
				// Setting console text color to green
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			// Validating month and that it should not be greater than month of current year
			else if (givenMonth > currentMonth) {
				cout << "\n\t\tHow can be start date month can be greater than current month!\n";
				// Setting console text color to green
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			// Validating day and that it should not be greater than day of current mont of current year
			else if (givenDay > currentDay) {
				cout << "\n\t\tHow can be start date can be greater than current date!\n";
				// Setting console text color to green
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
		}
		// Setting console text color to green
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	// It will check that Head is NULL or not
	bool checkHead() {
		if (Head == NULL)
		{
			// Setting console text color to red
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\n\n\t\tList is empty!" << endl;
			// Setting console text color to green
			SetConsoleTextAttribute(hConsole, 10);
			return false;
		}
		return true;
	}

	// It will split our given string according to delimiter
	vector<string> split(const string& s, char delim) {
		vector<string> result;  // Varible to store splitted values
		stringstream ss(s);  // Used for breaking words 
		string item;  // to store individual words 
		// Getline extracts characters from is and stores them into str until the delimitation character delim is found 
		while (getline(ss, item, delim)) {
			// push_back push item to result variable
			result.push_back(item);
		}
		return result;
	}

	// Checks that whether an Employee Id exist or not
	bool searchForNodeId(string empId) {
		bool flag = false;
		if (checkHead()) {
			Node* ptr = Head;  // Initiallizing Node struct with Head
			while (ptr != NULL) {  // Looping through values until ptr becomes NULL
				if (ptr->id == empId)  // Checking if given id matches id in record
				{
					flag = true;
					break;
				}
				ptr = ptr->next;
			}
		}
		if (flag == true) { // If id matches than flag will be true
			// Setting console text color to red
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tThis Id Already Exist Please try again";
		}
		// Setting console text color to green
		SetConsoleTextAttribute(hConsole, 10);
		return flag;
	}

	// To create Node with values
	Node* nodeValue() {
		Node* tempNode = new Node;  // Allocating space for Node struct in memory
		string tempVar;  // Initiallizing variable to store string

	emp_id:
		cout << "\n\n\n\t\tEnter the Employee ID in format of Emp-xxxxx-xx (x: number):\t\t\t";
		cin >> tempVar;
		// Validating string length. If result is false it will jump to emp_id
		if (!checkEmpId(tempVar, size(tempVar))) goto emp_id;
		// Validating that duplicate id do not exists. If result is false it will jump to emp_id
		if (searchForNodeId(tempVar)) goto emp_id;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->id, tempVar.c_str());
		// To ignore stucked value in buffer
		cin.ignore();

	emp_name:
		cout << "\n\t\tEnter the employee Full name (3 - 20):\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating string length. If result is false it will jump to emp_name
		if (!checkLength(20, size(tempVar))) goto emp_name;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->name, tempVar.c_str());

	emp_qual:
		cout << "\n\t\tEnter the Qualification (3 - 20):\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating string length. If result is false it will jump to emp_qual
		if (!checkLength(20, size(tempVar))) goto emp_qual;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->qualification, tempVar.c_str());

	emp_address:
		cout << "\n\t\tEnter the Address of Employee (3 - 20):\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating string length. If result is false it will jump to emp_address
		if (!checkLength(30, size(tempVar))) goto emp_address;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->address, tempVar.c_str());

	emp_city:
		cout << "\n\t\tEnter the City (3 - 20):\t\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating string length. If result is false it will jump to emp_city
		if (!checkLength(20, size(tempVar))) goto emp_city;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->city, tempVar.c_str());

	emp_job_title:
		cout << "\n\t\tEnter the employee Job title (3 - 20):\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating string length. If result is false it will jump to emp_job_title
		if (!checkLength(20, size(tempVar))) goto emp_job_title;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->jobTitle, tempVar.c_str());

	emp_salary:
		cout << "\n\t\tEnter the Employee the Salary:\t\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		cin >> tempVar;
		// Converting and checking if given string is a type of double. If result is false it will jump to emp_salary
		if (checkDouble(tempVar) == -1) goto emp_salary;
		// If condition is true the setting our node value
		else tempNode->salary = checkDouble(tempVar);
		// To ignore stucked value in buffer
		cin.ignore();

	emp_start_date:
		cout << "\n\t\tEnter the start Date (yyyy-mm-dd):\t\t\t\t\t\t";
		// Getting a line in tempVar variable
		getline(cin, tempVar);
		// Validating date format length. If result is false it will jump to emp_start_date
		if (!checkDate(tempVar, size(tempVar))) goto emp_start_date;
		// Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->startDate, tempVar.c_str());

		return tempNode;
	}

	// To generate nodes when data is loaded from the file on program startup
	void generateNode(string id, string name, string qualification, string address, string city, string jobTitle, double salary, string startDate) {

		Node* tempNode = new Node();
		strcpy_s(tempNode->id, id.c_str());  // Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->name, name.c_str());  // Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->qualification, qualification.c_str());  // Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->address, address.c_str());  // Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->city, city.c_str());  // Coverting string into char array and copying it to our char array variable
		strcpy_s(tempNode->jobTitle, jobTitle.c_str());  // Coverting string into char array and copying it to our char array variable
		tempNode->salary = salary;  // Setting a node value with given value
		strcpy_s(tempNode->startDate, startDate.c_str());  // Coverting string into char array and copying it to our char array variable

		if (Head == NULL)  // Checks if head is NULL or not
		{
			// Setting Head to this node
			Head = tempNode;
		}
		else  // Else we create and allocate memory for a node
		{
			Node* ptr = Head;  // Initiallizing Node struct with Head
			while (ptr->next != NULL)  // Loopig through until ptr->next becomes NULL
			{
				ptr = ptr->next;  // Going on the next value
			}
			tempNode->next = NULL;  // Setting next Node address to null
			ptr->next = tempNode;  // Connecting with previous node with next node
			tempNode->prev = ptr;  // Also connecting next node with previous node
		}
	}

public:

	int getChoice() {  // Return the choice becaut variable is private
		return choice;
	}

	// Method to display Main menu for selection
	// 0 - BLACK, 1 - DARK BLUE, 2 - DARK GREEN, 3 - GREENISH BLUE, 4 - RED, 5 - PURPLE, 6 - YELLOW, 7 - WHITE, 8 - GREY, 9 - BRIGHT BLUE
	// 10 - BRIGHT GREEM, 11 - BLUEISH GREEN, 12 - ORANGEISH RED, 

	// Displays Menu and gets the choice
	void mainMenu() {
		FlushConsoleInputBuffer(hConsole);
		// Set text Color to green
		SetConsoleTextAttribute(hConsole, 10);
		cout << "\n\n\n\n\t\t\t\t\t\t\t\t******************************************************************************";
		cout << "\n\t\t\t\t\t\t\t\t******************** WELCOME TO THE EMPLOYEE SYSTEM MENU *********************";
		cout << "\n\t\t\t\t\t\t\t\t******************************************************************************";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     1.\t  Add a record\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     2.\t  Search a record                    *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     3.\t  Update a record                    *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     4.\t  Delete a record                    *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     5.\t  Display a record                   *********";
		cout << "\n\t\t\t\t\t\t\t\t********* \t\t     6.\t  Exit\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t*********\t\t\t\t\t                     *********";
		cout << "\n\t\t\t\t\t\t\t\t******************************************************************************";
		cout << "\n\t\t\t\t\t\t\t\t******************************************************************************";
		cout << "\n\t\t\t\t\t\t\t\t******************************************************************************" << endl;
		// Set text Color to white
		SetConsoleTextAttribute(hConsole, 7);
		cout << "\n\n\t\t\t\t\t\t\t\tPlease Enter Your Choice:\t";
		// Set text Color to bluish green
		SetConsoleTextAttribute(hConsole, 11);
		cin >> choice;
		// Set text Color to white
		SetConsoleTextAttribute(hConsole, 7);
	}

	// To insert value at very beggining
	void insertAtStart()
	{
		system("CLS");  // Clearing the screen
		Node* tempNode = nodeValue();  // Initiallizing Node Struct with Our values
		tempNode->prev = NULL;  // Setting previous address of node to NULL
		if (Head != NULL)  // Checking if head is empty or not
		{
			tempNode->next = Head;  // Linking head to this new Node
			Head->prev = tempNode;
		}
		else {
			tempNode->next = NULL;  // If Head is NULL then setting node's next address to NULL
		}
		Head = tempNode; // Setting Head value
		// Set text Color to green
		SetConsoleTextAttribute(hConsole, 10);
		cout << "\n\t\t\Record inserted Successfully!" << endl;
		cout << "\n\t\t\**********THANK YOU **********" << endl;
		// Set text Color to white
		SetConsoleTextAttribute(hConsole, 7);
	}

	void insertAtEnd()
	{
		if (!checkHead()) {
			insertAtStart();
		}
		else {
			Node* tempNode = nodeValue();  // Initiallizing Node struct object with values
			Node* ptr = Head;  // Initiallizing Node struct object with Head
			while (ptr->next != NULL)  // Looping through untill ptr->next becomes NULL
			{
				ptr = ptr->next;  // jumping to next record
			}
			tempNode->next = NULL;  // Setting next address to be NULL
			ptr->next = tempNode;  // Conneting previous node with next node
			tempNode->prev = ptr;  // Also connecting next node with previous node
			// Set text Color to green
			SetConsoleTextAttribute(hConsole, 10);
			cout << "\n\t\t\Record inserted Successfully!" << endl;
			cout << "\n\t\t\**********THANK YOU **********" << endl;
			// Set text Color to white
			SetConsoleTextAttribute(hConsole, 7);
		}
	}

	// To insert after a specified value
	void insertAfterN()
	{
		char ch;  // Initialize a char variable to check yes or no
		int pos = 0;  // Initialize int variable to save position
		bool flag = false;  // flag to check condition is truthy or falsy

		if (!checkHead()) {  // Checking if head is null or not
			// Set text Color to red
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tDo you want to add it at first position? Press y if Yes.\t\n\n";
			// Set text Color to greenish grey
			SetConsoleTextAttribute(hConsole, 8);
			cin >> ch;
			if (tolower(ch) == 'y') {  // Check If user wants to insert
				insertAtStart();  // Call insertAtStart
			}
			else {
				// Set text Color to blue
				SetConsoleTextAttribute(hConsole, 20);
				cout << "\n\n\t\t          \tRedirecting to Menu";
				Sleep(1500);
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
			}
			// Set text Color to green
			SetConsoleTextAttribute(hConsole, 10);
		}
		else {
			Node* ptr = Head, * temp;  // Initiallizing Node struct objects

		insertAfterNth:
			cout << "\n\n\t\tPlease Enter a position after which you want to enter the record:";
			cin >> pos;

			if (pos <= 0) { // Check if position is valid or not
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tInvalid Value List starts from 1" << endl;
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
				system("CLS"); // Clearing the scrren
				cout << "\n\n";
				goto insertAfterNth;  // Jump to the label
			}
			else {  // if position is valid
				for (int i = 0; i < pos - 1; i++) { // loop through until we have ptr before the given position
					if (ptr == NULL) {  // Check if ptr is NULL
						// Set text Color to red
						SetConsoleTextAttribute(hConsole, 4);
						cout << "\n\n\t\tPosition Donot Exist" << endl;
						// Set text Color to white
						SetConsoleTextAttribute(hConsole, 7);
						flag = true;  // To tell that position have not found
						break;
					}
					else {
						ptr = ptr->next;  // Go the next value
					}
				}
				if (!flag) {  // If value is found
					if (ptr->next == NULL) {  // If it is an end node
						insertAtEnd();  // Call insertAtEnd
					}
					else {
						Node* tempNode = nodeValue();  // Intialize Node struct with values
						temp = ptr->next;  // Setting one value after the position in temp
						ptr->next = tempNode;  // Connecting ptr with tempNode
						tempNode->prev = ptr;  // Connecting tempNode with ptr
						tempNode->next = temp;  // Connecting tempNode with temp
						temp->prev = tempNode;  // Connecting temp with tempNode
					}
					// Set text Color to green
					SetConsoleTextAttribute(hConsole, 10);
					cout << "\n\t\t\ Record inserted Successfully!" << endl;
					cout << "\n\t\t\ **********THANK YOU **********" << endl;
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
	}

	// To insert before a specified value
	void insertBeforeN()
	{
		char ch;  // Initialize a char variable to check yes or no
		int pos = 0;  // Initialize int variable to save position
		bool flag = false;  // flag to check condition is truthy or falsy

		if (!checkHead()) {  // Checking if head is null or not
			// Set text Color to red
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tDo you want to add it at first position? Press y if Yes.\t\n\n";
			// Set text Color to greenish grey
			SetConsoleTextAttribute(hConsole, 8);
			cin >> ch;
			if (tolower(ch) == 'y') {  // Check If user wants to insert 
				insertAtStart();  // Call Insert
			}
			else {
				// Set text Color to blue
				SetConsoleTextAttribute(hConsole, 20);
				cout << "\n\n\t\t          \tRedirecting to Menu";
				Sleep(1500);
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
			}
			// Set text Color to white
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			Node* ptr = Head, * temp;  // Initiallizing Node struct object

		insertBeforeNth:
			cout << "\n\n\t\tPlease Enter a position before which you want to enter the record:";
			cin >> pos;

			if (pos == 0) {  // Check if position is valid or not
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tInvalid Value List starts from 1" << endl;
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
				system("CLS"); // To clear the screen
				cout << "\n\n";
				goto insertBeforeNth; // Jum to label
			}
			else if (pos == 1) {  // If givenn position is 1
				cout << "\n\n";
				insertAtStart();  // call insertAtStart
			}
			else {
				for (int i = 0; i < pos - 1; i++) {  // loop through until we have ptr before the given position
					if (ptr == NULL) {  // Check if ptr is NULL
						// Set text Color to red
						SetConsoleTextAttribute(hConsole, 4);
						cout << "\n\n\t\tPosition Donot Exist" << endl;
						// Set text Color to white
						SetConsoleTextAttribute(hConsole, 7);
						flag = true;  // To tell that position have not found 
						break;
					}
					else {
						ptr = ptr->next;  // Go the next value
					}
				}
				if (!flag) {   // If value is found
					if (ptr->next == NULL) {  // If it is an end node
						insertAtEnd();  // Call insertAtEnd
					}
					else {
						Node* tempNode = nodeValue();  // Intialize Node struct with values
						temp = ptr->prev;  // Setting one value after the position in temp
						temp->next = tempNode;  // Connecting temp with tempNode
						tempNode->prev = temp;  // Connecting tempNode with temp
						tempNode->next = ptr;  // Connecting tempNode with ptr
						ptr->prev = tempNode;  // Connecting ptr with tempNode
					}
					// Set text Color to green
					SetConsoleTextAttribute(hConsole, 10);
					cout << "\n\t\t\ Record inserted Successfully!" << endl;
					cout << "\n\t\t\ **********THANK YOU **********" << endl;
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
	}

	// To search the record by Employee Id
	void searchById() {
		if (checkHead()) {  // Checks if head is null or not
			string val;  // Initialize string variable to store id
			Node* ptr = Head;  // Initialize Node struct pointer object with Head
			bool flag = false;  // To indicate whether rcord is found or not

			cout << "\n\t\tEnter the employee ID which you want to search a record:\t";
			cin >> val;

			while (ptr != NULL) {  // Loop through until ptr becomes NULL
				if (ptr->id == val)  // check if given id matches the record
				{  // Condition is true the print the following:
					cout << "\n\t\t***********************INFORMATION OF EMLOYEE**********************" << endl;
					cout << "\n\t\tID:\t\t" << ptr->id << endl;
					cout << "\n\t\tName:\t\t" << ptr->name << endl;
					cout << "\n\t\tQualification:\t" << ptr->qualification << endl;
					cout << "\n\t\tAddress:\t" << ptr->address << endl;
					cout << "\n\t\tCity:\t\t" << ptr->city << endl;
					cout << "\n\t\tJob Title:\t" << ptr->jobTitle << endl;
					cout << "\n\t\tSalary:\t\t" << ptr->salary << endl;
					cout << "\n\t\tStarting Date:\t" << ptr->startDate << endl;
					flag = true;  // To indicate record is found
					break;
				}
				ptr = ptr->next;  // Goes to the next value
			}
			if (flag == false) {  // If record is not found
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tSorry, Record does not exist for given Id!\n\n";
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	// To search record by Name of Employee
	void searchByName() {
		if (checkHead()) {  // Checks if Head is empty or not
			string val;  // Initialize string variable to store id
			Node* ptr = Head;  // Initialize Node struct pointer object with Head
			bool flag = false;  // To indicate whether rcord is found or not

			cout << "\n\t\tEnter the employee Name which you want to search a record:\t";
			cin.ignore();
			getline(cin, val);

			while (ptr != NULL) {  // Loop through until ptr becomes NULL
				if (ptr->name == val)  // check if given name matches the records
				{  // Condition is true the print the following:
					cout << "\n\t\t***********************INFORMATION OF EMLOYEE**********************" << endl;
					cout << "\n\t\tID:\t\t" << ptr->id << endl;
					cout << "\n\t\tName:\t\t" << ptr->name << endl;
					cout << "\n\t\tQualification:\t" << ptr->qualification << endl;
					cout << "\n\t\tAddress:\t" << ptr->address << endl;
					cout << "\n\t\tCity:\t\t" << ptr->city << endl;
					cout << "\n\t\tJob Title:\t" << ptr->jobTitle << endl;
					cout << "\n\t\tSalary:\t\t" << ptr->salary << endl;
					cout << "\n\t\tStarting Date:\t" << ptr->startDate << endl << endl;
					flag = true;  // To indicate record is found
				}
				ptr = ptr->next;  // Goes to the next value
			}
			if (flag == false) {  // If record is not found
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tSorry, Record does not exist for given Name!\n\n";
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	// To only print the employee names from record
	void printNames() {
		if (checkHead()) {  // Checks if Head is NULL or not
			Node* ptr = Head;  // Initializing Node struct pointer object with Head
			int count = 1;  // Initializing Count to 1
			cout << "\n\n\t\t\tFollowing Employee Names are found in the list: \n\n\t\t\t";
			while (ptr != NULL) {  // Looping through until ptr becomes NULL
				cout << count << ".\t" << ptr->name << "\t\t";
				if (count % 5 == 0) {  // Check if count is divisible by 5
					cout << '\n\t\t\t';  // Go to next line and give indentations
				}
				ptr = ptr->next;  // Go to the next value
				count++;  // Incrementint Counter
			}
		}
	}

	// To only print the all of the record
	void printTotalRecord() {
		if (checkHead()) {  // Checks if Head is Empty or not
			Node* ptr = Head;  // Initializing Node struct pointer object with Head
			int count = 1;  // Initializing Count to 1
			cout << "\n\n\t\t\tFollowing are the details of employees:\n\n\t\t\t";
			cout << "S#\t\tID\t\t\tNAME\t\tQUALIFICATION\t\tADDRESS\t\tCITY\t\tJOB TITLE\t\tSALARY\t\tSTART DATE\n\n";
			while (ptr != NULL) {  // Looping through until ptr becomes NULL
				cout << "\n\t\t\t" << count << ".\t\t" << ptr->id << "\t\t" << ptr->name << "\t\t" << ptr->qualification << "\t\t" << ptr->address
					<< "\t\t" << ptr->city << "\t\t" << ptr->jobTitle << "\t\t" << ptr->salary << "\t\t" << ptr->startDate;
				ptr = ptr->next;  // Go to the next value
				count++;  // Incrementint Counter
			}
			cout << endl;
		}
	}

	// To generate nodes by fetching data from file when program starts
	void initialize() {
		ifstream fin;  // Initialize read stream
		fin.open("data.csv");  // openning file
		string line;  // initializing string in which we save our line
		vector<string> out;  // To store splitted line
		while (fin) {  // Loop until line exist in the file
			getline(fin, line);  // Getting the line
			if (line != "") {  // checking if line is not empty
				vector<string> value = split(line, ',');  // Saving splited array in value vector
				double sal = stod(value[7]);  // Convert string value to double
				generateNode(value[1], value[2], value[3], value[4], value[5], value[6], sal, value[8]);  // To generate a node of this line
			}
		}
	}

	// To update the record
	void updateRecord() {
		system("CLS"); // To clear the screen
		SetConsoleTextAttribute(hConsole, 6);  // To change the text color to yellow 
		if (checkHead()) {
			string val;  // Initialize string variable to store id
			Node* ptr = Head;  // Initialize Node struct pointer object with Head
			bool flag = false;  // To indicate whether rcord is found or not
			Node* temp;  // Initialize Node struct pointer to store temp object

			cout << "\n\n\t\t\t\tEnter the employee ID which you want to update a record:";
			cout << "\n\t\t\t\t\tType back to return\n\n\t\t\t\tID: ";
			cin >> val;

			while (ptr != NULL) {  // Loop through until ptr donot becomes NULL
				if (val == "back" || val == "BACK") { // if user writes back
					flag = true;  // To indicate that user donot want to proceed
					break;  // Break from the loop
				}
				if (ptr->id == val)  // if ptr->id matches our given Id
				{
					temp = nodeValue(); // Creating our nodes with values
					ptr = temp;  // Giving ptr values og temp
					flag = true;  // To indicate that updated succeffully
					break;  // Break from the loop
				}
				ptr = ptr->next;  // Go to next node
			}
			if (flag == false) {  // If not updated successfully or not found
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tRecord does not exist for given Id!\n\n";
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 7);
			}
			system("CLS");
		}
	}

	// To delete a record
	void deleteRecord() {
		system("CLS");  // To clear the screen
		// Set text Color to yellow
		SetConsoleTextAttribute(hConsole, 6);
		if (checkHead()) {
			string val;  // Initialize string variable to store id
			Node* ptr = Head;  // Initialize Node struct pointer object with Head
			bool flag = false;  // To indicate whether rcord is found or not
			cout << "\n\n\t\t\t\tEnter the employee ID of the record which you want to delete:";
			cout << "\n\t\t\t\t\tType back to return\n\n\t\t\t\tID: ";
			cin >> val;
			int counter = 0;  // Initialize the counter
			while (ptr != NULL) {  // Looping through until ptr becomes NULL
				if (val == "back" || val == "BACK") system("CLS"); return;
				if (ptr->id == val) {  // Checks if ptr->id matches given value
					counter++;  // Incrementing the counter
					flag = true;  // To indicate value to delete is found
					struct Node* s = Head; // Initializing Node struct pointer object with Head
					for (int i = 1; i < counter; i++) {  // Looping through unril it reaches the specified position
						ptr = s;  // Giving value of s to ptr
						s = s->next;  // Going to next Node
					}
					ptr->next = s->next;
					free(s);  // disallocating the node in s
					cout << "\n\t\t\t\t\tDeleted Successfully!\n";
					break;  // To break out of loop
				}
				ptr = ptr->next;  // Go to next node
				counter++;  // Increment Counter
			}
			if (flag == false) {  // If value is not found
				// Set text Color to red
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tRecord does not exist for given Id!\n\n";
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	// Exit the program
	void exitProgram() {
		ofstream fout;  // To initialize write stream
		fout.open("data.csv");
		if (Head != NULL) {  // Check if Head is not NULL
			Node* ptr = Head;  // Initializing Node struct pointer with Head
			int count = 1;  // Incrementing counter
			while (ptr != NULL) {  // Loop until the pointer do not becomes NULL
				// Writing line to a file
				fout << count << "." << "," << ptr->id << "," << "" << ptr->name << "," << ptr->qualification << "," << ptr->address << ","
					<< ptr->city << "," << ptr->jobTitle << "," << ptr->salary << "," << ptr->startDate << "\n";
				ptr = ptr->next;  // Go to the next value
				count++;  // Incrementing counter
			}

		}
		fout.close();  // To close the object opened to write the file
		system("CLS");  // To clear the screen
		// Set text Color to bright blue
		SetConsoleTextAttribute(hConsole, 9);
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\n\t\t\t\t\t||||||||||||   |||||        |||||   ||||||||||||    ||||||||||||   ||||||||||||    |||||||||     ||||||    |||||||||||||||||||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||||||||||     ||||      ||||     ||||||||||||    ||||||||||||   ||||||||||||    |||||||||     ||||||    |||||||||||||||||||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||              ||||    ||||          ||||            ||||           ||||        |||| ||||      ||||     ||||             ||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||               ||||  ||||           ||||            ||||           ||||        ||||  ||||     ||||     ||||             ||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||||||            ||||||||            ||||            ||||           ||||        ||||   ||||    ||||     ||||                 "; Sleep(100);
		cout << "\n\t\t\t\t\t||||||||            ||||||||            ||||            ||||           ||||        ||||    ||||   ||||     ||||                 "; Sleep(100);
		cout << "\n\t\t\t\t\t||||               ||||  ||||           ||||            ||||           ||||        ||||     ||||  ||||     ||||     ||||||||||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||              ||||    ||||          ||||            ||||           ||||        ||||      |||| ||||     ||||     ||||||||||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||||||||||     ||||      ||||     |||||||||||        ||||||      |||||||||||    ||||||     |||||||||     |||||||||||||    ||||"; Sleep(100);
		cout << "\n\t\t\t\t\t||||||||||||   |||||        |||||   |||||||||||       ||||||||     |||||||||||    ||||||     |||||||||     |||||||||||||    ||||"; Sleep(100);
		// Set text Color to white
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(500);  // To pause for 0.5 sec
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}
};

int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);  // To maximize the window
	Employee employee;  // Creating object of employee class
	employee.initialize();  // Reading data from file and creating node

	do {
		employee.mainMenu();  // Shows Main Menu
		int choice = employee.getChoice();  // Gets the choice from menu
		int n;  // To store inner choice

		switch (choice)
		{
		case 1:
			do {
			insertStart:
				system("CLS");  // Clear the Screen
				// Set text Color to yellow
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tWhere do you want to add the record: " << endl;
				cout << "\n\t\t        1.\tInsert Record at the Beginning of List:" << endl;
				cout << "\n\t\t        2.\tInsert Record at the End of List:" << endl;
				cout << "\n\t\t        3.\tInsert Record after the Given Position:" << endl;
				cout << "\n\t\t        4.\tInsert Record before the Given Position: " << endl;
				cout << "\n\t\t        5.\tGo to Main Menu: " << endl;
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				// Set text Color to Bluish green
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				// Set text Color to green
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS"); // Clear the Screen
					employee.insertAtStart();  // call insertAtStart
					break;
				case 2:
					system("CLS"); // Clear the Screen
					employee.insertAtEnd();   // Call insertAtEnd
					break;
				case 3:
					system("CLS"); // Clear the Screen
					employee.insertAfterN();  // Call insertAfterN
					break;
				case 4:
					system("CLS"); // Clear the Screen
					employee.insertBeforeN();  // Call insertBeforeN
					break;
				case 5:
					system("CLS");  // Clear the Screen
					break;
				default:
					// Set text Color to orangish red
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);  // pause for 1.5sec
					goto insertStart;  // Jump to label
					break;
				}
				if (n != 5) {
					// Set text Color to green
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (n != 5);
			system("CLS");  // Clear the Screen
			break;
		case 2:
			do {
			searchStart:
				system("CLS");  // Clear the Screen
				// Set text Color to yellow
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tHow do you want to see the record: " << endl;
				cout << "\n\t\t        1.\tSearch Employee by Id:" << endl;
				cout << "\n\t\t        2.\tSearch Employee by Name:" << endl;
				cout << "\n\t\t        3.\tGo to Main Menu: " << endl;
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				// Set text Color to bluish green
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				// Set text Color to green
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS");  // Clear the Screen
					employee.searchById();  // Call searchById
					break;
				case 2:
					system("CLS");  // Clear the Screen
					employee.searchByName();  // Call searchByName
					break;
				case 3:
					system("CLS");  // Clear the Screen
					break;
				default:
					// Set text Color to orange red
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);  // pause for 1.5sec
					goto searchStart;  // Jump to label
					break;
					n = NULL;
				}
				if (n != 3) {
					// Set text Color to green
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
					n = NULL;
				}
			} while (n != 3);
			system("CLS");  // Clear the Screen
			break;
		case 3:
			employee.updateRecord();  // Call updateRecord
			system("CLS"); // Clear the Screen
			break;
		case 4:
			employee.deleteRecord();  // Call deleteRecord
			system("CLS"); // Clear the Screen
			break;
		case 5:
			do {
			printStart:
				system("CLS");  // Clear the screen
				// Set text Color to yellow
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tHow do you want to see the record: " << endl;
				cout << "\n\t\t        1.\tOnly print names of all the Employees:" << endl;
				cout << "\n\t\t        2.\tPrint whole record of Employees:" << endl;
				cout << "\n\t\t        3.\tGo to Main Menu: " << endl;
				// Set text Color to white
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				// Set text Color to bluish green
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				// Set text Color to green
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS");  // Clear the Screen
					employee.printNames();  // Call printNames
					break;
				case 2:
					system("CLS");  // Clear the Screen
					employee.printTotalRecord();  // Call printTotalRecord
					break;
				case 3:
					system("CLS");  // Clear the Screen
					break;
				default:
					// Set text Color to orangish red
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);  // Pause for 1.5sec
					goto printStart;  // jump to label
					break;
				}
				if (n != 3) {
					// Set text Color to green
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					// Set text Color to white
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (n != 3);
			break;
		case 6:
			employee.exitProgram();
			break;
		default:
			// Set text Color to orangish red
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid Choice!" << endl;
			// Set text Color to white
			SetConsoleTextAttribute(hConsole, 7);
			system("CLS");  // Clear the Screen
			break;
		}
	} while (employee.getChoice() != 6);

	return 0;
}