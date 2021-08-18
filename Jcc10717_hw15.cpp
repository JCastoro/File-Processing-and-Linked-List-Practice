
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

class Employee {
	int idNumber;
	string name;
	double hourlyPayRate;

	double hoursWorked;
	double paycheckAmount;

public:
	Employee() {
		idNumber = 0;
		name = "NA";
		hourlyPayRate = 0.00;
		hoursWorked = 0.00;
	};
	Employee(int newIdNumber, string newName, double newHourlyPayRate) :
		idNumber(newIdNumber), name(newName), hourlyPayRate(newHourlyPayRate) {
		hoursWorked = 0;
		paycheckAmount = 0;
	}

	int	getIdNumber() { return idNumber; };
	string getName() { return name; };
	double getHourlyPayRate() { return hourlyPayRate; };
	double getHoursWorked() { return hoursWorked; };
	double getpaycheckAmount() { return paycheckAmount; };


	void setIdNumber(int newIdNumber) { idNumber = newIdNumber; };
	void setName(string newName) { name = newName; };
	void setHourlyPayRate(double newHourlyPayRate) { hourlyPayRate = newHourlyPayRate; };
	void setHoursWorked(double newHoursWorked) { hoursWorked=newHoursWorked; };
	void setpaycheckAmount(double newPaycheckAmount) { paycheckAmount=newPaycheckAmount; };

	void updatePaycheck(double nextPaycheckAmount) { paycheckAmount += nextPaycheckAmount; };


	Employee& operator =(const Employee& rhs);
	


private:

};

Employee& Employee::operator =(const Employee& rhs) {
	if (this == &rhs) {
		return *this;
	}
	hourlyPayRate = rhs.hourlyPayRate;
	hoursWorked = rhs.hoursWorked;
	name = rhs.name;
	idNumber = rhs.idNumber;
	paycheckAmount = rhs.paycheckAmount;
	return *this;
};



//_____________________________________________LINKED LIST_____________________________________________________ 
template <class T>
class LList;
template <class T>
class LListItr;

template <class T>
class LListNode {
	T data;
	LListNode<T>* next;
	LListNode<T>* prev;
public:
	LListNode(const T& newdata = T(), LListNode<T>* newnext = nullptr, LListNode<T>* newprev = nullptr) :data(newdata), next(newnext), prev(newprev) {}
	friend class LList<T>;
	friend class LListItr<T>;

	LListNode<T>* getNext() {
		return next;
	};
	LListNode<T> getNextNode() {
		return (*(this->next));
	};

	T* getData() {
		return &data;
	};

};

class EmptyListError {};

template <class S>
class LListItr {
	LListNode<S>* ptr;
public:
	LListItr(LListNode<S>* newptr = nullptr) :ptr(newptr) {}
	S& operator*() { return ptr->data; }
	S operator*() const { return ptr->data; }
	LListItr operator++(int);
	LListItr& operator++();
	LListItr operator--(int);
	LListItr& operator--();
	bool operator==(const LListItr<S>& rhs) const { return ptr == rhs.ptr; }
	bool operator!=(const LListItr<S>& rhs) const { return ptr != rhs.ptr; }
	friend class LList<S>;
};

template <class T>
class LList {
	LListNode<T>* head;
	LListNode<T>* tail;
	int numElements;
public:

	LListItr<T> begin() { return head->next; }
	LListItr<T> end() { return tail; }
	bool isEmpty() const { return numElements == 0; }
	LList();
	virtual ~LList();
	void push_front(const T& newdata);
	void push_back(const T& newdata) { insertAfter(newdata, tail->prev); }
	int size() const { return numElements; }
	void clear();
	LList(const LList<T>& rhs);
	LList& operator=(const LList& rhs);
	T pop_front() { if (!isEmpty()) return removeNode(head->next); else throw EmptyListError(); }
	T pop_back() { if (!isEmpty()) return removeNode(tail->prev); else throw EmptyListError(); }

	void insertAfter(const T& newdata, LListItr<T> itr);
	T removeNode(LListItr<T> itr);
	LListNode<T>* getHead() { return this->head; };
	
};


template <class T>
LListItr<T> LListItr<T>::operator--(int) {
	LListItr<T> temp = *this;
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator--() {
	if (ptr->prev != nullptr)
		ptr = ptr->prev;
	return *this;
}

template <class T>
LListItr<T> LListItr<T>::operator++(int) {
	LListItr<T> temp = *this;
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator++() {
	if (ptr->next != nullptr)
		ptr = ptr->next;
	return *this;
}



template <class T>
T LList<T>::removeNode(LListItr<T> itr) {
	LListNode<T>* toDelete = itr.ptr;
	T retval = toDelete->data;
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;

	delete toDelete;
	numElements--;
	return retval;
}

template <class T>
void LList<T>::insertAfter(const T& newdata, LListItr<T> itr) {
	LListNode<T>* temp = itr.ptr;
	numElements++;
	temp->next = new LListNode<T>(newdata, temp->next, temp);
	temp->next->next->prev = temp->next;


}
template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs) {
	if (this == &rhs)
		return *this;
	clear();

	for (LListNode<T>* temp = rhs.head->next; temp != rhs.tail; temp = temp->next)
		push_back(temp->data);
	return *this;
}
template <class T>
LList<T>::LList(const LList<T>& rhs) {
	numElements = 0;
	head = new LListNode<T>(T(), new LListNode<T>); //create two dummy nodes.
	tail = head->next;
	tail->prev = head;
	*this = rhs;
}
template <class T>
void LList<T>::clear() {
	while (!isEmpty())
		removeNode(head->next);
}
template <class T>
void LList<T>::push_front(const T& newdata) {
	insertAfter(newdata, head);
}
template <class T>
LList<T>::~LList() {
	clear();
	delete head;
	delete tail;
}
template <class T>
LList<T>::LList() {
	numElements = 0;
	head = new LListNode<T>(T(), new LListNode<T>); //create two dummy nodes.
	tail = head->next;
	tail->prev = head;
}


void openInputFile(ifstream& inFile);

//debugging
void openEmployeeInfo(ifstream& inFile);
void openpayrollInfo(ifstream& inFile);
//done

void loadEmployeesIntoList(LList<Employee>& employeeList, ifstream& inFile);
void loadHoursWorked(LList<Employee>& employeeList, ifstream& inFile);

void printEmployeeList(LList<Employee> toPrint);
void printPayroll(LList<Employee> toPrint);

void bubbleSortEmployee(LListNode<Employee>* unsortedList);
void swap(Employee& left, Employee& right);

int main()
{

	list<Employee> tester;
	Employee mark(3,"mark",23.32);

	tester.push_back(mark);

	//for (Employee i : tester) {
	//	cout << i.getName();
	//}

	for(list<Employee>::iterator i=tester.begin();i!=tester.end();i++)
		cout << (*i).getName();


	//	//opening employee info
	//ifstream employeeFile;
	//openEmployeeInfo(employeeFile);
	////opening payroll file
	//ifstream payrollFile;
	//openpayrollInfo(payrollFile);


	////	//loading employees into linked list
	//LList<Employee> employeeList = LList<Employee>();
	//loadEmployeesIntoList(employeeList, employeeFile);
	//loadHoursWorked(employeeList, payrollFile);

	//bubbleSortEmployee(employeeList.getHead()->getNext());
	//
	//printPayroll(employeeList);

	//cout << endl;

	//

	//employeeFile.close();
	//payrollFile.close();
}

//swaps by reference the left and right employees
void swap(Employee& left, Employee& right) {
	
	Employee temp;
	temp = left;
	left = right;
	right = temp;
	

}






void openInputFile(ifstream& inFile) {
	string fileName;
	cout << "What is filename?\n";
	cin >> fileName;

	inFile.open(fileName);
	while (!inFile) {
		cout << "FILE FAILED TO OPEN!" << endl;
		cout << "What is filename?\n";
		
		cin >> fileName;
		inFile.open(fileName);
	}
}
void openEmployeeInfo(ifstream& inFile) {
	string fileName;
	cout << "What is file Name of Employee info file?\n";
	cin >> fileName;

	inFile.open(fileName);
	while (!inFile) {
		cout << "FILE FAILED TO OPEN!" << endl;
		cout << "What is filename?\n";

		cin >> fileName;
		inFile.open(fileName);
	}



			//used so i dont need to keep typing in file name

	//string fileName;
	//cout << "Press any key then enter to load employeeFile. \n";
	//cin >> fileName;
	//fileName = "EmployeeInfo.txt";
	//inFile.open(fileName);
	//while (!inFile) {
	//	cout << "FILE FAILED TO OPEN!" << endl;
	//	cout << "What is filename?\n";

	//	cin >> fileName;
	//	inFile.open(fileName);
	
}
void openpayrollInfo(ifstream& inFile) {

	string fileName;
	cout << "What is file Name of Payroll info file?\n";
	cin >> fileName;

	inFile.open(fileName);
	while (!inFile) {
		cout << "FILE FAILED TO OPEN!" << endl;
		cout << "What is filename?\n";

		cin >> fileName;
		inFile.open(fileName);
	}




	//string fileName;
	//cout << "Press any key then enter to load payroll info file. \n";
	//cin >> fileName;
	//fileName = "payroll_Info.txt";
	//inFile.open(fileName);
	//while (!inFile) {
	//	cout << "FILE FAILED TO OPEN!" << endl;
	//	cout << "What is filename?\n";

	//	cin >> fileName;
	//	inFile.open(fileName);
	//}
}

void loadEmployeesIntoList(LList<Employee>& employeeList, ifstream& inFile) {
	
	int tempIdNumber;
	string tempName;
	double tempHourlyPayRate;

	Employee temp;

	while (inFile >> tempIdNumber >> tempHourlyPayRate) {
		getline(inFile, tempName);
		//inFile.ignore(9999, '\n');
		//cout << tempHourlyPayRate;
		temp.setIdNumber(tempIdNumber);
		temp.setName(tempName);
		temp.setHourlyPayRate(tempHourlyPayRate);
		employeeList.push_back(temp);
	}
}

void loadHoursWorked(LList<Employee>& employeeList, ifstream& inFile) {
	int tempUserId;
	double tempHoursWorked;

	double currentHrsWrkd;
	double hourlyrate;


	while (inFile>>tempUserId>>tempHoursWorked) {
		//inFile.ignore(9999, '\n');

		for (LListItr<Employee> i = LListItr<Employee>(employeeList.begin()); i != employeeList.end(); i++) {
			if (tempUserId == (*i).getIdNumber()) {
				//updating hours worked
				currentHrsWrkd = (*i).getHoursWorked();
				(*i).setHoursWorked(tempHoursWorked+currentHrsWrkd);
			}

		}
		for (LListItr<Employee> i = LListItr<Employee>(employeeList.begin()); i != employeeList.end(); i++) {

			//updating paycheck amount
			currentHrsWrkd = (*i).getHoursWorked();
			hourlyrate = (*i).getHourlyPayRate();
			double paycheck = currentHrsWrkd * hourlyrate;
			(*i).setpaycheckAmount(paycheck);
			

		}
	}
}

void bubbleSortEmployee(LListNode<Employee>* firstNode) {
	bool swapped = false;

	LListNode<Employee>* left = nullptr;
	LListNode<Employee>* right = nullptr;
	
	if (firstNode == nullptr) {
		return;
	}
	do {
		swapped = false;
		left = firstNode;
		while (left->getNext() != right) {
			//cout << "left name " << left->getData().getName()<<endl;
			//cout << "next to left name " << left->getNext()->getData().getName()<<endl;
			
			if ((left->getData()->getpaycheckAmount()) < (left->getNext()->getData()->getpaycheckAmount())) {
				//cout << left->getData().getName();
				swap(*left->getData(),*left->getNext()->getData());
			
				swapped = true;
			}
			left = left->getNext();
		}
		right = left;
	} while (swapped);

		}
	
void printEmployeeList(LList<Employee> toPrint) {// should be constant but .begin() will not let me...
	double paycheck;

	int id;
	double hourlyPay;
	double hoursWorked;
	string name;
	
	for (LListItr<Employee> i = LListItr<Employee>(toPrint.begin()); i != toPrint.end(); i++) {
		id = (*i).getIdNumber();
		hourlyPay = (*i).getHourlyPayRate();
		name = (*i).getName();
		hoursWorked = (*i).getHoursWorked();

		cout << id <<'\t';
		cout << hourlyPay << '\t';
		cout << name << '\t';
		paycheck = hoursWorked * hourlyPay;

		//need to set the precision of this
		cout<< hoursWorked <<'\t'<<"$"<< paycheck<<endl;
		
	}

}

void printPayroll(LList<Employee> toPrint) {
	double paycheck;

	int id;
	double hourlyPay;
	double hoursWorked;
	string name;

	int idOfHighestPay;
	double highestPay=0;


	cout << "*********Payroll Information*********\n";

		//need to set the precision of this??

	for (LListItr<Employee> i = LListItr<Employee>(toPrint.begin()); i != toPrint.end(); i++) {
		cout << (*i).getName() << ", $" << (*i).getpaycheckAmount() << endl;

	}
	cout << "*********End Payroll*****************\n";
	}


