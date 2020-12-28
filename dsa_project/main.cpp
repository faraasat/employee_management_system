#include <iostream>
#include <Windows.h>
#include<stdlib.h>
#include <string>
#include<regex>
#include <ctime>
#include<fstream>
#include<iomanip>
#include<vector>
#include <sstream>
using namespace std;

ofstream fout;
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class Employee {
private:

	// Structure to be used in linked List to store the data
	struct Node
	{
		char id[13];
		char name[21];
		char qualification[21];
		char address[31];
		char city[21];
		char jobTitle[21];
		double salary;
		char startDate[11];
		Node* prev, * next;
	} *Head = NULL;

	int choice = 0;

	bool checkEmpId(string empId, int size) {
		SetConsoleTextAttribute(hConsole, 12);
		regex regExp("(Emp-)[0-9]{5}(-)[0-9]{2}");
		if (size > 12) {
			cout << "\n\t\tId should not exceed max 12 characters";
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		else if (!regex_match(empId, regExp)) {
			cout << "\n\t\tThe format of Id should be Emp-xxxxx-xx where x are the numbers!";
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	bool checkLength(int req_size, int pro_size) {
		SetConsoleTextAttribute(hConsole, 12);
		if ((pro_size > req_size) || (pro_size < 3)) {
			cout << "\n\t\tName Should be at least 3 characters or donot exceed " << req_size << " characters\n";
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	double checkDouble(string str) {
		SetConsoleTextAttribute(hConsole, 12);
		double dob;
		try
		{
			dob = stod(str);
		}
		catch (const std::exception&)
		{
			cout << "\n\t\tYour given value is either not a number or out of range!\n";
			SetConsoleTextAttribute(hConsole, 10);
			return -1;
		}
		SetConsoleTextAttribute(hConsole, 10);
		return dob;
	}

	bool checkDate(string empId, int size) {
		SetConsoleTextAttribute(hConsole, 12);
		regex regExp("\\b\\d{4}[-]\\d{2}[-]\\d{2}\\b");
		if (size > 10 || !regex_match(empId, regExp)) {
			cout << "\n\t\tThe format of date should be yyyy-mm-dd!\n";
			SetConsoleTextAttribute(hConsole, 10);
			return 0;
		}
		else {
			struct tm newTime;
			time_t t = time(NULL);
			localtime_s(&newTime, &t);
			int givenYear = stoi(empId.substr(0, 4));
			int givenMonth = stoi(empId.substr(5, 2));
			int givenDay = stoi(empId.substr(8, 2));
			int currentYear = 1900 + newTime.tm_year;
			int currentMonth = newTime.tm_mon + 1;
			int currentDay = newTime.tm_mday;
			if (givenMonth > 12 || givenMonth < 1) {
				cout << "\n\t\tPlease Correct Your Month Value!\n";
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			else if (givenDay > 31 || givenDay < 1) {
				cout << "\n\t\tPlease Correct Your Day Value!\n";
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			else if (givenYear > currentYear) {
				cout << "\n\t\tHow can be start date year can be greater than current year!\n";
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			else if (givenMonth > currentMonth) {
				cout << "\n\t\tHow can be start date month can be greater than current month!\n";
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
			else if (givenDay > currentDay) {
				cout << "\n\t\tHow can be start date can be greater than current date!\n";
				SetConsoleTextAttribute(hConsole, 10);
				return 0;
			}
		}
		SetConsoleTextAttribute(hConsole, 10);
		return 1;
	}

	bool checkHead() {
		if (Head == NULL)
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\n\n\t\tList is empty!" << endl;
			SetConsoleTextAttribute(hConsole, 10);
			return false;
		}
		return true;
	}

	vector<string> split(const string& s, char delim) {
		vector<string> result;
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			result.push_back(item);
		}
		return result;
	}

	bool searchForNodeId(string empId) {
		bool flag = false;
		if (checkHead()) {
			Node* ptr = Head;

			while (ptr != NULL) {
				if (ptr->id == empId)
				{
					flag = true;
					break;
				}
				ptr = ptr->next;
			}
		}
		if (flag == true) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tThis Id Already Exist Please try again";
		}
		SetConsoleTextAttribute(hConsole, 10);
		return flag;
	}

	Node* nodeValue() {
		Node* tempNode = new Node;
		string tempVar;

	emp_id:
		cout << "\n\n\n\t\tEnter the Employee ID in format of Emp-xxxxx-xx (x: number):\t\t\t";
		cin >> tempVar;
		if (!checkEmpId(tempVar, size(tempVar))) goto emp_id;
		if (searchForNodeId(tempVar)) goto emp_id;
		strcpy_s(tempNode->id, tempVar.c_str());
		cin.ignore();

	emp_name:
		cout << "\n\t\tEnter the employee Full name (3 - 20):\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkLength(20, size(tempVar))) goto emp_name;
		strcpy_s(tempNode->name, tempVar.c_str());

	emp_qual:
		cout << "\n\t\tEnter the Qualification (3 - 20):\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkLength(20, size(tempVar))) goto emp_qual;
		strcpy_s(tempNode->qualification, tempVar.c_str());

	emp_address:
		cout << "\n\t\tEnter the Address of Employee (3 - 20):\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkLength(30, size(tempVar))) goto emp_address;
		strcpy_s(tempNode->address, tempVar.c_str());

	emp_city:
		cout << "\n\t\tEnter the City (3 - 20):\t\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkLength(20, size(tempVar))) goto emp_city;
		strcpy_s(tempNode->city, tempVar.c_str());

	emp_job_title:
		cout << "\n\t\tEnter the employee Job title (3 - 20):\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkLength(20, size(tempVar))) goto emp_job_title;
		strcpy_s(tempNode->jobTitle, tempVar.c_str());

	emp_salary:
		cout << "\n\t\tEnter the Employee the Salary:\t\t\t\t\t\t\t";
		cin >> tempVar;
		if (checkDouble(tempVar) == -1) goto emp_salary;
		else tempNode->salary = checkDouble(tempVar);
		cin.ignore();

	emp_start_date:
		cout << "\n\t\tEnter the start Date:\t\t\t\t\t\t\t\t";
		getline(cin, tempVar);
		if (!checkDate(tempVar, size(tempVar))) goto emp_start_date;
		strcpy_s(tempNode->startDate, tempVar.c_str());

		return tempNode;
	}

	void generateNode(string id, string name, string qualification, string address, string city, string jobTitle, double salary, string startDate) {

		Node* tempNode = new Node();
		strcpy_s(tempNode->id, id.c_str());
		strcpy_s(tempNode->name, name.c_str());
		strcpy_s(tempNode->qualification, qualification.c_str());
		strcpy_s(tempNode->address, address.c_str());
		strcpy_s(tempNode->city, city.c_str());
		strcpy_s(tempNode->jobTitle, jobTitle.c_str());
		tempNode->salary = salary;
		strcpy_s(tempNode->startDate, startDate.c_str());

		if (Head == NULL)
		{
			Head = tempNode;
		}
		else
		{
			Node* ptr = Head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			tempNode->next = NULL;
			ptr->next = tempNode;
			tempNode->prev = ptr;
		}
	}

public:

	int getChoice() {
		return choice;
	}

	// Method to display Main menu for selection
	// 0 - BLACK, 1 - DARK BLUE, 2 - DARK GREEN, 3 - GREENISH BLUE, 4 - RED, 5 - PURPLE, 6 - YELLOW, 7 - WHITE, 8 - GREY, 9 - BRIGHT BLUE
	// 10 - BRIGHT GREEM, 11 - BLUEISH GREEN, 12 - ORANGEISH RED, 

	void mainMenu() {
		FlushConsoleInputBuffer(hConsole);
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
		SetConsoleTextAttribute(hConsole, 7);
		cout << "\n\n\t\t\t\t\t\t\t\tPlease Enter Your Choice:\t";
		SetConsoleTextAttribute(hConsole, 11);
		cin >> choice;
		SetConsoleTextAttribute(hConsole, 7);
	}

	void insertAtStart()
	{
		system("CLS");
		Node* tempNode = nodeValue();

		tempNode->next = Head;
		tempNode->prev = NULL;

		if (Head != NULL)
		{
			Head->prev = tempNode;
		}

		Head = tempNode;

		SetConsoleTextAttribute(hConsole, 10);
		cout << "\n\t\t\Record inserted Successfully!" << endl;
		cout << "\n\t\t\**********THANK YOU **********" << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}

	void insertAtEnd()
	{
		if (!checkHead()) {
			insertAtStart();
		}
		else {
			Node* tempNode = nodeValue();
			Node* ptr = Head;

			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}

			tempNode->next = NULL;
			ptr->next = tempNode;
			tempNode->prev = ptr;

			SetConsoleTextAttribute(hConsole, 10);
			cout << "\n\t\t\Record inserted Successfully!" << endl;
			cout << "\n\t\t\**********THANK YOU **********" << endl;
			SetConsoleTextAttribute(hConsole, 7);
		}
	}

	void insertAfterN()
	{
		char ch;
		int pos = 0;
		bool flag = false;

		if (!checkHead()) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tDo you want to add it at first position? Press y if Yes.\t\n\n";
			SetConsoleTextAttribute(hConsole, 10);
			SetConsoleTextAttribute(hConsole, 8);
			cin >> ch;
			if (tolower(ch) == 'y') {
				insertAtStart();
			}
			else {
				SetConsoleTextAttribute(hConsole, 20);
				cout << "\n\n\t\t          \tRedirecting to Menu";
				Sleep(1500);
				SetConsoleTextAttribute(hConsole, 7);
			}
			SetConsoleTextAttribute(hConsole, 10);
		}
		else {
			Node* ptr = Head, * temp;

		insertAfterNth:
			cout << "\n\n\t\tPlease Enter a position after which you want to enter the record:";
			cin >> pos;

			if (pos == 0) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tInvalid Value List starts from 1" << endl;
				SetConsoleTextAttribute(hConsole, 7);
				system("CLS");
				cout << "\n\n";
				goto insertAfterNth;
			}
			else {
				for (int i = 0; i < pos - 1; i++) {
					if (ptr == NULL) {
						SetConsoleTextAttribute(hConsole, 4);
						cout << "\n\n\t\tPosition Donot Exist" << endl;
						SetConsoleTextAttribute(hConsole, 7);
						flag = true;
						break;
					}
					else {
						ptr = ptr->next;
					}
				}
				if (!flag) {
					if (ptr->next == NULL) {
						insertAtEnd();
						flag = true;
					}
					else {
						Node* tempNode = nodeValue();
						temp = ptr->next;
						ptr->next = tempNode;
						tempNode->prev = ptr;
						tempNode->next = temp;
						temp->prev = tempNode;
						flag = true;
					}
					SetConsoleTextAttribute(hConsole, 10);
					cout << "\n\t\t\ Record inserted Successfully!" << endl;
					cout << "\n\t\t\ **********THANK YOU **********" << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
	}

	void insertBeforeN()
	{
		char ch;
		int pos = 0;
		bool flag = false;

		if (!checkHead()) {
			SetConsoleTextAttribute(hConsole, 4);
			cout << "\n\t\tDo you want to add it at first position? Press y if Yes.\t\n\n";
			SetConsoleTextAttribute(hConsole, 10);
			SetConsoleTextAttribute(hConsole, 8);
			cin >> ch;
			if (tolower(ch) == 'y') {
				insertAtStart();
			}
			else {
				SetConsoleTextAttribute(hConsole, 20);
				cout << "\n\n\t\t          \tRedirecting to Menu";
				Sleep(1500);
				SetConsoleTextAttribute(hConsole, 7);
			}
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			Node* ptr = Head, * temp;

		insertBeforeNth:
			cout << "\n\n\t\tPlease Enter a position before which you want to enter the record:";
			cin >> pos;

			if (pos == 0) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tInvalid Value List starts from 1" << endl;
				SetConsoleTextAttribute(hConsole, 7);
				system("CLS");
				cout << "\n\n";
				goto insertBeforeNth;
			}
			else if (pos == 1) {
				cout << "\n\n";
				insertAtStart();
			}
			else {
				for (int i = 0; i < pos - 1; i++) {
					if (ptr == NULL) {
						SetConsoleTextAttribute(hConsole, 4);
						cout << "\n\n\t\tPosition Donot Exist" << endl;
						SetConsoleTextAttribute(hConsole, 7);
						flag = true;
						break;
					}
					else {
						ptr = ptr->next;
					}
				}
				if (!flag) {
					if (ptr->next == NULL) {
						insertAtEnd();
						flag = true;
					}
					else {
						Node* tempNode = nodeValue();
						temp = ptr->prev;
						temp->next = tempNode;
						tempNode->prev = temp;
						tempNode->next = ptr;
						ptr->prev = tempNode;
					}
					SetConsoleTextAttribute(hConsole, 10);
					cout << "\n\t\t\ Record inserted Successfully!" << endl;
					cout << "\n\t\t\ **********THANK YOU **********" << endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
		}
	}

	void searchById() {
		if (checkHead()) {
			string val;
			Node* ptr = Head;
			bool flag = false;

			cout << "\n\t\tEnter the employee ID which you want to search a record:\t";
			cin >> val;

			while (ptr != NULL) {
				if (ptr->id == val)
				{
					cout << "\n\t\t***********************INFORMATION OF EMLOYEE**********************" << endl;
					cout << "\n\t\tID:\t\t" << ptr->id << endl;
					cout << "\n\t\tName:\t\t" << ptr->name << endl;
					cout << "\n\t\tQualification:\t" << ptr->qualification << endl;
					cout << "\n\t\tAddress:\t" << ptr->address << endl;
					cout << "\n\t\tCity:\t\t" << ptr->city << endl;
					cout << "\n\t\tJob Title:\t" << ptr->jobTitle << endl;
					cout << "\n\t\tSalary:\t\t" << ptr->salary << endl;
					cout << "\n\t\tStarting Date:\t" << ptr->startDate << endl;
					flag = true;
					break;
				}
				ptr = ptr->next;
			}
			if (flag == false) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tSorry, Record does not exist for given Id!\n\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	void searchByName() {
		if (checkHead()) {
			string val;
			Node* ptr = Head;
			bool flag = false;

			cout << "\n\t\tEnter the employee Name which you want to search a record:\t";
			cin >> val;

			while (ptr != NULL) {
				if (ptr->name == val)
				{
					cout << "\n\t\t***********************INFORMATION OF EMLOYEE**********************" << endl;
					cout << "\n\t\tID:\t\t" << ptr->id << endl;
					cout << "\n\t\tName:\t\t" << ptr->name << endl;
					cout << "\n\t\tQualification:\t" << ptr->qualification << endl;
					cout << "\n\t\tAddress:\t" << ptr->address << endl;
					cout << "\n\t\tCity:\t\t" << ptr->city << endl;
					cout << "\n\t\tJob Title:\t" << ptr->jobTitle << endl;
					cout << "\n\t\tSalary:\t\t" << ptr->salary << endl;
					cout << "\n\t\tStarting Date:\t" << ptr->startDate << endl << endl;
					flag = true;
				}
				ptr = ptr->next;
			}
			if (flag == false) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tSorry, Record does not exist for given Id!\n\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	void printNames() {
		if (checkHead()) {
			Node* ptr = Head;
			int count = 1;
			cout << "\n\n\t\t\tFollowing Employee Names are found in the list: \n\n\t\t\t";
			while (ptr != NULL) {
				cout << count << ".\t" << ptr->name << "\t\t";
				if (count % 5 == 0) {
					cout << '\n\t\t\t';
				}
				ptr = ptr->next;
				count++;
			}
		}
	}

	void printTotalRecord() {
		if (checkHead()) {
			Node* ptr = Head;
			int count = 1;
			cout << "\n\n\t\t\tFollowing are the details of employees:\n\n\t\t\t";
			cout << "S#\t\tID\t\t\tNAME\t\tQUALIFICATION\t\tADDRESS\t\tCITY\t\tJOB TITLE\t\tSALARY\t\tSTART DATE\n\n";
			while (ptr != NULL) {
				cout << "\n\t\t\t" << count << ".\t\t" << ptr->id << "\t\t" << ptr->name << "\t\t" << ptr->qualification << "\t\t" << ptr->address
					<< "\t\t" << ptr->city << "\t\t" << ptr->jobTitle << "\t\t" << ptr->salary << "\t\t" << ptr->startDate;
				ptr = ptr->next;
				count++;
			}
			cout << endl;
		}
	}

	void initialize() {
		ifstream fin;
		fin.open("data.csv");
		string line;
		int count = 0;
		vector<string> out;
		while (fin) {
			if (count > 3) {
				getline(fin, line);
				if (line != "") {
					vector<string> value = split(line, ',');
					double sal = stod(value[7]);
					generateNode(value[1], value[2], value[3], value[4], value[5], value[6], sal, value[8]);
				}
			}
			count++;
		}
	}

	void updateRecord() {
		system("CLS");
		SetConsoleTextAttribute(hConsole, 6);
		bool flag = false;
		if (checkHead()) {
			string val;
			Node* ptr = Head;
			Node* temp;

			cout << "\n\n\t\t\t\tEnter the employee ID which you want to update a record:";
			cout << "\n\t\t\t\t\tType back to return\n\n\t\t\t\tID: ";
			cin >> val;

			while (ptr != NULL) {
				if (val == "back" || val == "BACK") {
					break;
				}
				if (ptr->id == val)
				{
					temp = nodeValue();
					ptr = temp;
					break;
				}
				ptr = ptr->next;
			}
			if (flag == false) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tRecord does not exist for given Id!\n\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
			system("CLS");
		}
	}

	void deleteRecord() {
		system("CLS");
		SetConsoleTextAttribute(hConsole, 6);
		if (checkHead()) {
			string val;
			Node* ptr = Head;
			bool flag = false;
			cout << "\n\n\t\t\t\tEnter the employee ID of the record which you want to delete:";
			cout << "\n\t\t\t\t\tType back to return\n\n\t\t\t\tID: ";
			cin >> val;
			int counter = 0;
			while (ptr != NULL) {

				if (val == "back" || val == "BACK") { system("CLS"); return; }

				if (ptr->id == val) {
					counter++;
					flag = true;
					struct Node* s;
					s = Head;
					for (int i = 1; i < counter; i++) {
						ptr = s;
						s = s->next;
					}
					ptr->next = s->next;
					cout << "\n\t\t\t\t\tDeleted Successfully!\n";
					break;
				}
				ptr = ptr->next;
				counter++;
			}
			if (flag == false) {
				SetConsoleTextAttribute(hConsole, 4);
				cout << "\n\n\t\tRecord does not exist for given Id!\n\n";
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}

	void exitProgram() {
		system("CLS");

		ofstream fout;
		fout.open("data.csv");

		if (checkHead()) {
			Node* ptr = Head;

			int count = 1;
			while (ptr != NULL) {
				fout << count << "." << "," << ptr->id << "," << "" << ptr->name << "," << ptr->qualification << "," << ptr->address << ","
					<< ptr->city << "," << ptr->jobTitle << "," << ptr->salary << "," << ptr->startDate << "\n";
				ptr = ptr->next;
				count++;
			}

		}

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
		SetConsoleTextAttribute(hConsole, 7);
		Sleep(500);
		cout << endl;
	}
};

int main() {

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Employee employee;
	employee.initialize();

	do {
		employee.mainMenu();
		int choice = employee.getChoice();
		int n;

		switch (choice)
		{
		case 1:
			do {
			insertStart:
				system("CLS");
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tWhere do you want to add the record: " << endl;
				cout << "\n\t\t        1.\tInsert Record at the Beginning of List:" << endl;
				cout << "\n\t\t        2.\tInsert Record at the End of List:" << endl;
				cout << "\n\t\t        3.\tInsert Record after the Given Position:" << endl;
				cout << "\n\t\t        4.\tInsert Record before the Given Position: " << endl;
				cout << "\n\t\t        5.\tGo to Main Menu: " << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS");
					employee.insertAtStart();
					break;
				case 2:
					system("CLS");
					employee.insertAtEnd();
					break;
				case 3:
					system("CLS");
					employee.insertAfterN();
					break;
				case 4:
					system("CLS");
					employee.insertBeforeN();
					break;
				case 5:
					system("CLS");
					break;
				default:
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);
					goto insertStart;
					break;
				}
				if (n != 5) {
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (n != 5);
			system("CLS");
			break;
		case 2:
			do {
			searchStart:
				system("CLS");
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tHow do you want to see the record: " << endl;
				cout << "\n\t\t        1.\tSearch Employee by Id:" << endl;
				cout << "\n\t\t        2.\tSearch Employee by Name:" << endl;
				cout << "\n\t\t        3.\tGo to Main Menu: " << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS");
					employee.searchById();
					break;
				case 2:
					system("CLS");
					employee.searchByName();
					break;
				case 3:
					system("CLS");
					break;
				default:
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);
					goto searchStart;
					break;
				}
				if (n != 3) {
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (n != 3);
			system("CLS");
			break;
		case 3:
			employee.updateRecord();
			system("CLS");
			break;
		case 4:
			employee.deleteRecord();
			break;
		case 5:
			do {
			printStart:
				system("CLS");
				SetConsoleTextAttribute(hConsole, 6);
				cout << "\n\n\n\t\tHow do you want to see the record: " << endl;
				cout << "\n\t\t        1.\tOnly print names of all the Employees:" << endl;
				cout << "\n\t\t        2.\tPrint whole record of Employees:" << endl;
				cout << "\n\t\t        3.\tGo to Main Menu: " << endl;
				SetConsoleTextAttribute(hConsole, 7);
				cout << "\n\n\t\t          \tEnter choice:\t";
				SetConsoleTextAttribute(hConsole, 11);
				cin >> n;
				SetConsoleTextAttribute(hConsole, 10);
				switch (n)
				{
				case 1:
					system("CLS");
					employee.printNames();
					break;
				case 2:
					system("CLS");
					employee.printTotalRecord();
					break;
				case 3:
					system("CLS");
					break;
				default:
					SetConsoleTextAttribute(hConsole, 12);
					cout << "\n\n\t\t          \tInvalid Choice!" << endl;
					SetConsoleTextAttribute(hConsole, 7);
					cout << "\n\n\t\t          \tRedirecting to Menu";
					Sleep(1500);
					goto printStart;
					break;
				}
				if (n != 3) {
					SetConsoleTextAttribute(hConsole, 19);
					cout << "\n\n\t\t\t";
					system("pause");
					SetConsoleTextAttribute(hConsole, 7);
				}
			} while (n != 3);
			break;
		case 6:
			employee.exitProgram();
			break;
		default:
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Invalid Choice!" << endl;
			SetConsoleTextAttribute(hConsole, 7);
			system("CLS");
			break;
		}
	} while (employee.getChoice() != 6);

	return 0;
}