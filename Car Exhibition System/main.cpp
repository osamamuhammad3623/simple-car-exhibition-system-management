#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Cars.h"
#include "Employees.h"
#include "Sales.h"
#include "SysFunctions.h"

using namespace std;

int main() {

	header();
	check_password();

	while(1){
		header();
		mainMenu();
		space(4);

		int option;
		cin >> option;
		limitCheck(option, 1, 11);

		//View all cars
		if (option == 1) {
			header();
			if (is_empty_file("Cars.txt") == true) {
				space(4); cout << "No cars yet!" << endl;
				re_directed();
			}
			else {
				viewCars();
			}
		}

		//Add a car
		if (option == 2) {
			header();
			ofstream *cars_file = new ofstream();

			(*cars_file).open("Cars.txt", ios_base::app);

			if ((*cars_file).is_open()){
				addCars(cars_file);
			}
			else{
				error_happen();
			}
		}

		//Search for a car
		if (option == 3) {
			header();
			cout << "\t\t\t";  cout << "Enter any info about the car you want to search for : ";
			string search_word; cin >> search_word;

			ifstream *cars_file = new ifstream();
			(*cars_file).open("Cars.txt");

			if ((*cars_file).is_open()) {
				searchForCars(cars_file, search_word);
			}
			else {
				error_happen();
			}
			(*cars_file).close();
		}

		//View all sales
		if (option == 4) {
			header();

			if (is_empty_file("Sales.txt") == true) {
				space(4); cout << "No sales yet!" << endl;
				re_directed();
				continue;
			}
			else {
				viewSales();
			}
		}

		// Add a successful sale
		if (option == 5) {
			header();

			ofstream *sales_file = new ofstream();

			(*sales_file).open("Sales.txt", ios_base::app);

			if ((*sales_file).is_open()){
				addSales(sales_file);
			}
			else{
				error_happen();
			}
		}

		// View all employees info
		if (option == 6) {
			header();

			if (is_empty_file("Employees.txt") == true) {
				space(4); cout << "No employees yet!" << endl;
				re_directed();
				continue;
			}
			else {
				viewEmployees();
			}
		}

		// Add an employee
		if (option == 7) {
			header();

			Employees *employee_list= new Employees[100];
			ofstream employees_file;
			employees_file.open("Employees.txt");

			if (employees_file.is_open()) {

				// The table first row (if the text file is empty)
				if (is_empty_file("Employees.txt")) {
					employees_file << setw(30) << left << "Full Name" <<
						setw(15) << left << "National ID" <<
						setw(25) << left << "Job position" <<
						setw(10) << left << "Salary" << endl;
					employees_file << endl;
				}

				for (short i = 0; i <= 99; ++i) {
					cin.ignore(1000, '\n');
					space(4); cout << "Full name of the employee : ";
					string fullName; getline(cin, fullName);
					employee_list[i].full_name = fullName;
					cout << endl;

					space(4); cout << "National ID : ";
					int nationalID; cin >> nationalID; limitCheck_ID(nationalID, 0, 999999999999999);
					//IDs is 15-digit long
					employee_list[i].id = nationalID;
					cout << endl;

					cin.ignore(1000, '\n');
					space(4); cout << "Job position : ";
					string job; getline(cin, job);
					employee_list[i].job = job;
					cout << endl;

					space(4); cout << "Salary : ";
					int salary; cin >> salary; limitCheck(salary, 1000, 50000);
					//assuming no salary is less that 1k or more than 50k
					employee_list[i].salary = salary;
					cout << endl;

					employees_file << setw(30) << left << employee_list[i].full_name <<
						setw(15) << left << employee_list[i].id <<
						setw(25) << left << employee_list[i].job <<
						setw(10) << left << employee_list[i].salary << endl;

					space(4); cout << "Add another employee (Y/N) ? : ";
					char addOneMore;
					cin >> addOneMore;
					while (addOneMore != 'Y' && addOneMore != 'y' && addOneMore != 'N' && addOneMore != 'n') {
						space(4); cout << "Enter a valid option : ";
						cin >> addOneMore;
					}
					if (addOneMore == 'Y' || addOneMore == 'y') {
						cout << endl;
						continue;
					}
					else {
						cout << endl;
						space(4); cout << "You'll be directed to Main Menu in 2 seconds.";
						Sleep(2000);
						continue;
					}
				}
				employees_file.close();
			}
			else {
				error_happen();
				continue;
			}
			delete[] employee_list;
		}

		// Remove an employee's info
		if (option == 8) {
			header();

			ifstream employees_file; employees_file.open("Employees.txt"); //regular employees file
			ifstream employees_file_edit; employees_file_edit.open("Employees.txt"); //same file for editing operations
			ofstream temp; temp.open("temp.txt");
			
			if (employees_file.is_open()) {
				string line;
				while (getline(employees_file, line)) {
					cout << line << endl;
				}
				cout << endl;
				cout << "\t\t\t";; cout << "Enter the index number of the employee you want to remove : ";
				int remove_index; cin >> remove_index; limitCheck(remove_index, 1, 31);
				cout << endl;

				if (temp.is_open()) {
					int count = 0;

					while (getline(employees_file_edit, line)) {

						if (count == (remove_index + 1)) {
							// so here, when the required line is reached, it's not copied to the new file.
						}
						else { temp << line << endl; }// copying the lines to a temp text file
						count++;
					}
					
					employees_file.close(); temp.close(); employees_file_edit.close();

					char employees_old_file[] = "Employees.txt";
					char old_tmep[] = "temp.txt";
					char new_file[] = "Employees.txt";

					if (remove(employees_old_file) == 0) {

						if (rename(old_tmep, new_file) == 0) {//remove() & rename() functions need char parameters the point to the files
							header();
							space(4); cout << "Updated !" << endl;
							space(4); cout << "You'll be directed to Main Menu.";
							Sleep(2000);
							continue;
						}
						else {
							error_happen();
							continue;
						}
						
					}
					else {
						error_happen();
						continue;
					}
				}
				else {
					error_happen();
					continue;
				}
			}
			else {
				error_happen();
				continue;
			}
		}

		// Search for an employee
		if (option == 9) {
			header();

			space(4);  cout << "Enter any info about the employee you want to search for : ";
			string search_word;
			cin >> search_word;

			ifstream employees_file;
			employees_file.open("Employees.txt");

			if (employees_file.is_open()) {
				string* line = new string;
				while (getline(employees_file, *line)) {
					if ((*line).find(search_word) != string::npos ) {
						cout << *line << endl;
					}
				}
				back();
				continue;
			}
			else {
				error_happen();
				continue;
			}
			employees_file.close();
		}

		// Change password
		if (option == 10) {
			header();
			change_password();
			re_directed();
			continue;
		}

		// Exit the pogram/while loop
		if (option == 11) {
			return 0;
		}
	}
}