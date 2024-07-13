#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

//constant paths

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string BASE_PATH = "C:\\Users\\SubhanAmjad\\Documents\\Canvas\\";

void printBanner() {
    cout << CYAN << "\n";
    cout << "  ____    _    _   ___     __    _    ____" << endl;
    cout << " / ___|  / \\  | \\ | \\ \\   / /   / \\  / ___|" << endl;
    cout << "| |     / _ \\ |  \\| |\\ \\ / /   / _ \\ \\___ \\" << endl;
    cout << "| |___ / ___ \\| |\\  | \\ V /   / ___ \\ ___) |" << endl;
    cout << " \\____/_/   \\_\\_| \\_|  \\_/   /_/   \\_\\____/" << endl;
    cout << "\n           Management System\n" << RESET << endl;
}

void printCenteredText(const std::string& text, int width) {
    int padding = (width - text.length()) / 2;
    std::cout << std::setw(padding) << "" << text << std::endl;
}


void printMainMenu() {
    int width = 50;
    cout << YELLOW << string(width, '=') << RESET << endl;
    printCenteredText("MAIN MENU", width);
    cout << YELLOW << string(width, '=') << RESET << endl;
    cout << BLUE << "1. " << GREEN << "Admin Login" << RESET << endl;
    cout << BLUE << "2. " << GREEN << "Student Login" << RESET << endl;
    cout << BLUE << "3. " << GREEN << "Faculty Login" << RESET << endl;
    cout << BLUE << "4. " << RED << "Exit" << RESET << endl;
    cout << YELLOW << string(width, '-') << RESET << endl;
    cout << MAGENTA << "Enter your choice: " << RESET;
}



void printErrorMessage(string message) {
    cout << RED << "\n✗ ERROR: " << message << RESET << endl;
}


void printMenuOptions(vector<string> options) {
    for (int i = 0; i < options.size(); i++) {
        cout << BLUE << i+1 << ". " << YELLOW << options[i] << RESET << endl;
    }
    cout << MAGENTA << "\nSelect an option: " << RESET;
}

class Person
{
public:
	string loginid;
	string pass;
	string name;
	string phone;
};

class User : public Person
{
private:
	string sem, year;

public:

	void set(string loginid, string pass, string name, string phone, string year)
    {
        this->loginid = loginid;
        this->pass = pass;
        this->name = name;
        this->phone = phone;
        this->year = year;
        this->sem = "0";  // Initialize semester to 0 for new students
    }

	void reg()
    {
        fstream fout;
        fout.open(BASE_PATH + "students\\students.txt", ios::app);
        if (fout.is_open())
        {
            fout << loginid << endl;
            fout << pass << endl;
            fout << name << endl;
            fout << phone << endl;
            fout << sem << endl;
            fout << year << endl;
            fout << endl;  // Add an extra newline for separation
            fout.close();
            cout << "Student registered successfully." << endl;
        }
        else
        {
            cout << "FAILED TO OPEN FILE DUE TO SOME ERROR." << endl;
        }
    }

	void returnName(string* name)
	{
		*name = this->name;
	}

	int auth(string l, string p)
	{
		fstream fin;
		fin.open(BASE_PATH + "students\\students.txt", ios::in);
		if (fin.is_open())
		{

			string ignoreline;

			getline(fin, ignoreline);
			while (!fin.eof())
			{
				getline(fin, this->loginid);
				getline(fin, this->pass);

				if (this->loginid == l && this->pass == p)
				{

					getline(fin, this->name);
					getline(fin, this->phone);
					getline(fin, this->sem);
					getline(fin, this->year);
					return 1;
				}

				this->loginid = "";
				this->pass = "";
				getline(fin, ignoreline);
				getline(fin, ignoreline);
				getline(fin, ignoreline);
				getline(fin, ignoreline);
			}
			return 0;
		}
		else
		{
			cout << "FAILED TO OPEN FILE." << endl;
			return 0;
		}
	}

	void regInSem()
	{
		fstream fin;
		fin.open(BASE_PATH + "semester\\" + to_string(stoi(sem) + 1) + " " + year + ".txt", ios::in);
		if (fin.is_open())
		{
			fin.close();
			fin.open(BASE_PATH + "semester\\" + to_string(stoi(sem) + 1) + " " + year + ".txt", ios::app);
			cout << endl;
			cout << "SEMESTER NUMBER : " << stoi(sem) + 1 << endl;
			char opt;
			cout << "ARE YOU SURE YOU WANT TO REGISTER IN ABOVE SEMESTER [1=SURE , 0=NO] : ";
			cin >> opt;
			if (opt == '1')
			{
				fin << endl;
				fin << loginid;
				sem = to_string(stoi(sem) + 1);
				fstream old;
				fstream nava;
				old.open(BASE_PATH + "students\\students.txt", ios::in);
				nava.open(BASE_PATH + "students\\temporary.txt", ios::app);
				string line;
				getline(old, line);
				while (!old.eof())
				{
					nava << endl;
					getline(old, line);
					if (line == loginid)
					{
						nava << line << endl;
						getline(old, line);
						nava << line << endl;
						getline(old, line);
						nava << line << endl;
						getline(old, line);
						nava << line << endl;
						nava << sem << endl;
						getline(old, line);
						getline(old, line);
						nava << line;
					}
					else
						nava << line;
				}
				old.close();
				nava.close();

                remove((BASE_PATH + "students\\students.txt").c_str());
                rename((BASE_PATH + "students\\temporary.txt").c_str(), (BASE_PATH + "students\\students.txt").c_str());
			}
		}
		else
		{
			cout << "NO SEMESTER IS OFFERED YET." << endl;
		}
	}
	void regInCourse()
	{
		cout << "ENTER COURSE CODE : ";
		string code;
		cin.clear();
		cin.ignore();
		getline(cin, code);
		fstream fout;
		fout.open(BASE_PATH + "courses\\" + code + ".txt", ios::in);
		if (fout.is_open())
		{

			fout.close();
			fout.open(BASE_PATH + "courses\\" + code + ".txt", ios::app);
			fout << endl;
			fout << loginid;

			//
			fstream fin;
			fin.open(BASE_PATH + "students\\" + loginid + " " + code + ".txt", ios::app);
			fin.close();

		}
		else
		{
			cout << "NO SUCH COURSE EXISTS" << endl;
		}
	}
	void viewattendance()
	{
		string code;
		cout << "COURSE CODE : ";
		cin.clear();
		cin.ignore();
		getline(cin, code);
		fstream fin;
		fin.open(BASE_PATH + "students\\" + loginid + " " + code + ".txt", ios::in);
		if (!fin.is_open())
		{
			cout << "YOU AREN'T ENROLLED IN THIS COURSE OR THIS COURSE ISN'T OFFERED YET." << endl;
		}
		else
		{
			string line;
			getline(fin, line);
			while (!fin.eof())
			{
				getline(fin, line);
				cout << "DATE : " << line << endl;
				getline(fin, line);
				cout << "STATUS : " << line << endl;
			}
		}
	}
	void submitquiz()
	{
		string ass_name, teacher_id;
		cout << "SUMITTED TO : ";
		cin.clear();
		cin.ignore();
		getline(cin, teacher_id);
		cout << "ASSIGNMENT FILE : ";
		cin.ignore(0);
		getline(cin, ass_name);
		fstream fout;
		fout.open(BASE_PATH + "quiz\\submittedquiz.txt", ios::app);
		fout << endl;
		fout << teacher_id << endl;
		fout << loginid << endl;
		fout << ass_name;
	}
};

class Professor : public Person
{
public:
	void set(string loginid, string pass, string name, string phone)
	{
		this->loginid = loginid;
		this->pass = pass;
		this->name = name;
		this->phone = phone;
	}
	void reg()
	{
		fstream fout;

		fout.open(BASE_PATH + "faculty\\faculty.txt", ios::app);
		if (fout.is_open())
		{
			fout << endl;
			fout << loginid << endl;
			fout << pass << endl;
			fout << name << endl;
			fout << phone;
			fstream fin;
			fin.open(BASE_PATH + "faculty\\" + loginid + ".txt", ios::in);
			if (fin.is_open())
			{
				cout << "FACULTY MEMBER ALREADY EXITS" << endl;
			}
			else
			{
				fin.close();
				fin.open(BASE_PATH + "faculty\\" + loginid + ".txt", ios::out);
				fin.close();
			}
		}
		else
		{
			cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR" << endl;
		}
	}

	void returnName(string* name)
	{
		*name = this->name;
	}

	int auth(string l, string p)
	{
		fstream fin;
		fin.open(BASE_PATH + "faculty\\faculty.txt", ios::in);
		if (fin.is_open())
		{

			string ignoreline;

			getline(fin, ignoreline);
			while (!fin.eof())
			{
				getline(fin, this->loginid);
				getline(fin, this->pass);

				if (this->loginid == l && this->pass == p)
				{
					getline(fin, this->name);
					getline(fin, this->phone);
					return 1;
				}

				this->loginid = "";
				this->pass = "";
				getline(fin, ignoreline);
				getline(fin, ignoreline);
			}
			return 0;
		}
		else
		{
			cout << "FAILED TO OPEN" << endl;
			return 0;
		}
	}
	void uploadattendance()
	{
		string id, code, date, status;
		cout << "STUDENT ID : ";
		cin.clear();
		cin.ignore();
		getline(cin, id);
		cout << "COURSE CODE : ";
		cin.ignore(0);
		getline(cin, code);
		cout << "DATE : ";
		cin.ignore(0);
		getline(cin, date);
		cout << "STATUS : ";
		cin.ignore(0);
		getline(cin, status);
		fstream fout;
		fout.open(BASE_PATH + "students\\" + id + " " + code + ".txt", ios::in);
		if (!fout.is_open())
		{
			cout << "NO SUCH STUDENT IN RECORD" << endl;
		}
		else
		{
			fout.close();
			fout.open(BASE_PATH + "students\\" + id + " " + code + ".txt", ios::app);
			fout << endl;
			fout << date << endl;
			fout << status;
		}
	}
	void quizfunc()
	{
		string code, date, marks;
		cout << "ENTER COURSE CODE : ";
		cin.clear();
		cin.ignore();
		getline(cin, code);
		cout << "QUIZ DATE : ";
		cin.ignore(0);
		getline(cin, date);
		cout << "QUIZ MARKS : ";
		cin.ignore(0);
		getline(cin, marks);
		fstream f;
		f.open(BASE_PATH + "quiz\\quiz.txt", ios::app);
		f << endl;
		f << loginid << endl;
		f << code << endl;
		f << date << endl;
		f << marks;
	}
	void showquiz()
	{
		fstream f;
		f.open(BASE_PATH + "quiz\\quiz.txt", ios::in);
		string line;
		getline(f, line);
		while (!f.eof())
		{
			getline(f, line);
			if (loginid == line)
			{
				getline(f, line);
				cout << "COURSE CODE : " << line << endl;
				getline(f, line);
				cout << "QUIZ DATE : " << line << endl;
				getline(f, line);
				cout << "MARKS : " << line << endl;
			}
			else
			{
				getline(f, line);
				getline(f, line);
				getline(f, line);
			}
		}
		f.close();
	}
	void showsubmittedquiz()
	{
		fstream f;
		f.open(BASE_PATH + "quiz\\submittedquiz.txt", ios::in);
		string line;
		getline(f, line);
		while (!f.eof())
		{
			getline(f, line);
			if (loginid == line)
			{
				getline(f, line);
				cout << "FROM : " << line << endl;
				getline(f, line);
				cout << "ASSIGNMENT : " << line << endl;
			}
			else
			{
				getline(f, line);
				getline(f, line);
			}
		}
		f.close();
	}
};
class Semester
{
private:
	string no, year;
public:
	void set(string no, string year)
	{
		this->no = no;
		this->year = year;
	}
	void offer()
	{
		fstream f;
		f.open(BASE_PATH + "semester\\" + no + " " + year + ".txt", ios::in);
		if (f.is_open())
		{
			cout << "SEMESTER IS ALREADY OFFERED." << endl;
			f.close();
		}
		else
		{
			fstream f1;
			f1.open(BASE_PATH + "semester\\semester.txt", ios::app);
			f1 << endl;
			f1 << no << endl;
			f1 << year;
			f1.close();
			f.open(BASE_PATH + "semester\\" + no + " " + year + ".txt", ios::app);
			if (f.is_open())
			{
				cout << "SUCCESSFULLY OFFERED SEMESTER" << endl;
			}
			else
			{
				cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR" << endl;
			}
		}

	}

};
class Course
{
private:
	string code;
	string title;
	string hours;
	string teacher;
public:
	void set(string code, string title, string hours, string teacher)
	{
		this->code = code;
		this->title = title;
		this->hours = hours;
		this->teacher = teacher;
	}
	void offer()
	{
		fstream f;
		f.open(BASE_PATH + "courses\\" + code + ".txt", ios::in);
		if (f.is_open())
		{
			cout << "COURSE IS ALREADY OFFERED." << endl;
			f.close();
		}
		else
		{
			fstream f1;
			f1.open(BASE_PATH + "courses\\course.txt", ios::app);
			f1 << endl;
			f1 << code << endl;
			f1 << title << endl;
			f1 << hours << endl;
			f1 << teacher;
			f1.close();
			f.open(BASE_PATH + "courses\\" + code + ".txt", ios::app);
			if (f.is_open())
			{
				cout << "SUCCESSFULLY OFFERED COURSE" << endl;
			}
			else
			{
				cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR" << endl;
			}
		}
	}
};
class Admin
{
private:
	string loginid;
	string pass;

public:
	Admin()
	{
		loginid = "subhan";
		pass = "subhan";
	}
	string returnloginid()
	{
		return loginid;
	}
	string password()
	{
		return pass;
	}
	bool isStudentIdUnique(const string& loginid)
    {
        fstream f;
        f.open(BASE_PATH + "students\\students.txt", ios::in);
        if (!f.is_open())
        {
            cout << "Error opening students file." << endl;
            return true; // Assume unique if file can't be opened
        }

        string line;
        while (getline(f, line))
        {
            if (line == loginid)
            {
                f.close();
                return false; // ID already exists
            }
            // Skip the next 5 lines (password, name, phone, sem, year)
            for (int i = 0; i < 5 && getline(f, line); ++i) {}
        }
        f.close();
        return true; // ID is unique
    }
    bool isFacultyIdUnique(const string& loginid)
    {
        fstream f;
        f.open(BASE_PATH + "faculty\\faculty.txt", ios::in);
        string line;
        while (getline(f, line)) {
            if (line == loginid) {
                f.close();
                return false;
            }
            // Skip other lines
            for (int i = 0; i < 3; i++) {
                getline(f, line);
            }
        }
        f.close();
        return true;
    }

    bool isCourseCodeUnique(const string& code)
    {
        fstream f;
        f.open(BASE_PATH + "courses\\course.txt", ios::in);
        string line;
        while (getline(f, line)) {
            if (line == code) {
                f.close();
                return false;
            }
            // Skip other lines
            for (int i = 0; i < 3; i++) {
                getline(f, line);
            }
        }
        f.close();
        return true;
    }

    bool isSemesterUnique(const string& no, const string& year) {
        fstream f;
        f.open(BASE_PATH + "semester\\semester.txt", ios::in);
        string line, currentNo, currentYear;
        while (getline(f, currentNo)) {
            getline(f, currentYear);
            if (currentNo == no && currentYear == year) {
                f.close();
                return false;
            }
        }
        f.close();
        return true;
    }
    bool professorExists(const string& professorId)
    {
        fstream f;
        f.open(BASE_PATH + "faculty\\faculty.txt", ios::in);
        if (!f.is_open()) {
            cout << "Error opening faculty file." << endl;
            return false;
        }

        string line;
        while (getline(f, line)) {
            if (line == professorId) {
                f.close();
                return true; // Professor found
            }
            // Skip the next 3 lines (password, name, phone)
            for (int i = 0; i < 3 && getline(f, line); ++i) {}
        }
        f.close();
        return false; // Professor not found
    }
	void regUser()
    {
        User user;

        string loginid, pass, name, phone, year;

        cout << "LOGIN ID: ";
        cin.clear();
        cin.ignore();
        getline(cin, loginid);

        if (!isStudentIdUnique(loginid))
        {
            cout << "Error: A student with this ID already exists." << endl;
            return;
        }

        cout << "PASS: ";
        getline(cin, pass);

        cout << "NAME: ";
        getline(cin, name);

        cout << "PHONE: ";
        getline(cin, phone);

        cout << "YEAR: ";
        getline(cin, year);

        user.set(loginid, pass, name, phone, year);
        user.reg();
    }

	void dispUser()
	{
		fstream f;
		f.open(BASE_PATH + "students\\students.txt", ios::in);

		string ignoreline;

		if (f.is_open())
		{
			string loginid;
			string pass;

			string name;
			string phone;
			string year;
			string sem;

			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << endl;
			cout << left << setw(9) << "LOGIN ID" << " " << setw(8) << "PASSWORD" << " " << setw(24) << "NAME" << " " << setw(13) << "PHONE" << setw(13) << "SEMESTER" << setw(3) << "YEAR" << endl;
			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << "-" << "---------------------" << endl;

			getline(f, ignoreline); // ignore
			while (!f.eof())
			{
				getline(f, loginid);
				getline(f, pass);
				getline(f, name);
				getline(f, phone);
				getline(f, sem);
				getline(f, year);
				cout << left << setw(10) << loginid << setw(8) << pass << setw(25) << name << setw(14) << phone << setw(13) << sem << setw(5) << year << endl;
				cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << "-" << "--------------------" << endl;

			}
		}
		else
		{
			cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR." << endl;
		}

	}
	void regFaculty()
	{
		Professor professor;

		string loginid;
		string pass;

		string name;
		string phone;

		cout << "LOGIN ID: ";
		cin.clear();
		cin.ignore();
		getline(cin, loginid);

		if (!isFacultyIdUnique(loginid))
        {
            cout << "Error: A faculty with this ID already exists." << endl;
            return;
        }

		cout << "PASS: ";
		cin.ignore(0);
		getline(cin, pass);

		cout << "NAME: ";
		cin.ignore(0);
		getline(cin, name);

		cout << "PHONE: ";
		cin.ignore(0);
		getline(cin, phone);

		professor.set(loginid, pass, name, phone);
		professor.reg();

	}
	void dispFaculty()
	{
		fstream f;
		f.open(BASE_PATH + "faculty\\faculty.txt", ios::in);

		string ignoreline;

		if (f.is_open())
		{
			string loginid;
			string pass;

			string name;
			string phone;
			string sem;

			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "---------------" << endl;
			cout << left << setw(9) << "LOGIN ID" << " " << setw(8) << "PASSWORD" << " " << setw(25) << "NAME" << " " << setw(11) << "PHONE" << endl;
			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "---------------" << endl;

			getline(f, ignoreline); // ignore
			while (!f.eof())
			{
				getline(f, loginid);
				getline(f, pass);
				getline(f, name);
				getline(f, phone);

				cout << left << setw(8) << loginid << setw(8) << pass << setw(25) << name << setw(11) << phone <<  endl;
				cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << endl;

			}
		}
		else
		{
			cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR." << endl;
		}

	}
	void offerSemester()
	{
		Semester semester;

		string no, year;

		cout << "SEMESTER NUMBER : ";
		cin.clear();
		cin.ignore();
		getline(cin, no);

		cout << "YEAR : ";
		cin.ignore(0);
		getline(cin, year);

		if (!isSemesterUnique(no , year))
        {
            cout << "Error: This semester has already been offered for this year." << endl;
            return;
        }


		semester.set(no, year);
		semester.offer();

	}
	void dispSemester()
	{
		fstream f;
		f.open(BASE_PATH + "semester\\semester.txt", ios::in);

		string ignoreline;

		if (f.is_open())
		{
			string no;
			string year;

			cout << left << "-----" << "-" << "--------" << "-" << endl;
			cout << left << setw(5) << "NO" << " " << setw(8) << "YEAR" << endl;
			cout << left << "-----" << "-" << "--------" << "-" << endl;

			getline(f, ignoreline); // ignore
			while (!f.eof())
			{
				getline(f, no);
				getline(f, year);

				cout << left << setw(5) << no << setw(8) << year << endl;
				cout << left << "-----" << "-" << "--------" << "-" << endl;

			}
		}
		else
		{
			cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR." << endl;
		}
	}
	void offerCourses()
	{
        Course course;

        string code, title, hours, teacher;

        cout << "COURSE CODE: ";
        cin.clear();
        cin.ignore();
        getline(cin, code);

        if (!isCourseCodeUnique(code)) {
            cout << "Error: A course with this code already exists." << endl;
            return;
        }

        cout << "TITLE: ";
        getline(cin, title);

        cout << "HOURS: ";
        getline(cin, hours);

        int attempts = 0;
        bool validProfessor = false;

        while (attempts < 3 && !validProfessor) {
            cout << "PROFESSOR ID: ";
            getline(cin, teacher);

            if (professorExists(teacher)) {
                validProfessor = true;
            } else {
                attempts++;
                if (attempts < 3) {
                    cout << "Error: Professor with ID " << teacher << " does not exist. You have "
                         << (3 - attempts) << " more attempts." << endl;
                }
            }
        }

        if (!validProfessor) {
            cout << "Failed to provide a valid professor ID after 3 attempts. Course offering cancelled." << endl;
            return;
        }

        course.set(code, title, hours, teacher);
        course.offer();

        cout << "Course offered successfully." << endl;
    }
	void dispCourses()
	{
		fstream f;
		f.open(BASE_PATH + "courses\\course.txt", ios::in);

		string ignoreline;

		if (f.is_open())
		{
			string code;
			string title;
			string hours;
			string teacher;

			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << endl;
			cout << left << setw(5) << "CODE" << " " << setw(8) << "TITLE" << " " << setw(25) << "HOURS" << " " << setw(11) << "PROFESSOR" << endl;
			cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << endl;

			getline(f, ignoreline); // ignore
			while (!f.eof())
			{
				getline(f, code);
				getline(f, title);
				getline(f, hours);
				getline(f, teacher);

				cout << left << setw(5) << code << setw(8) << title << setw(25) << hours << setw(11) << teacher << endl;
				cout << left << "-----" << "-" << "--------" << "-" << "-------------------------" << "-" << "-----------" << endl;
			}
		}
		else
		{
			cout << "FAILED TO OPEN FILE DUE TO INTERNAL ERROR." << endl;
		}
	}
};

void adminTasks(Admin* admin)
{
	while (true)
	{

		cout << "1. REGISTER STUDENT" << endl;
		cout << "2. SHOW STUDENTS" << endl;
		cout << "3. ADD FACULTY" << endl;
		cout << "4. SHOW FACULTY" << endl;
		cout << "5. OFFER SEMESTER" << endl;
		cout << "6. DISPLAY SEMESTER INFO" << endl;
		cout << "7. OFFER COURSES" << endl;
		cout << "8. DISPLAY COURSES INFO" << endl;
		cout << "9. LOGOUT" << endl;
		cout << "SELECT ONE OF THE ABOVE OPTIONS [1-9] : ";
		char opt;
		cin >> opt;
		switch (opt)
		{
		case '1':
			admin->regUser();
			break;
		case '2':
			admin->dispUser();
			break;
		case '3':
			admin->regFaculty();
			break;
		case '4':
			admin->dispFaculty();
			break;
		case '5':
			admin->offerSemester();
			break;
		case '6':
			admin->dispSemester();
			break;
		case '7':
			admin->offerCourses();
			break;
		case '8':
			admin->dispCourses();
			break;
		case '9':
			return;
		default:
			cout << "INCORRECT OPTION" << endl;
		}
	}
}

void userTasks(User* user)
{
	cout << "LOGIN: " << endl;
	cout << "LOGIN ID: ";

	string loginid;
	string pass;

	cin.clear();
	cin.ignore();
	getline(cin, loginid);
	cout << "PASSWORD: ";
	cin.ignore(0);
	getline(cin, pass);

	if (user->auth(loginid, pass))
	{
		string name;
		user->returnName(&name);
		cout << "WELCOME " << name;
		cout << endl;

		char c;

		cout << "1. REGISTER SEMESTER" << endl;
		cout << "2. REGISTER IN COURSES" << endl;
		cout << "3. VIEW ATTENDANCE" << endl;
		cout << "4. SUBMIT QUIZ" << endl;
		cout << "OPTION : ";
		cin >> c;

		switch (c)
		{
		case '1':
			user->regInSem();
			break;
		case '2':
			user->regInCourse();
			break;
		case '3':
			user->viewattendance();
			break;
		case '4':
			user->submitquiz();
			break;
		case '5':
			return;
			break;
		default:
			cout << "INCORRECT OPTION" << endl;
		}
	}
	else
	{
		cout << "INVALID LOGIN ID OR PASSWORD" << endl;
	}
}

void facultyTasks(Professor* professor)
{
	cout << "LOGIN: " << endl;
	cout << "LOGIN ID: ";

	string loginid;
	string pass;

	cin.clear();
	cin.ignore();
	getline(cin, loginid);
	cout << "PASSWORD: ";
	cin.ignore(0);
	getline(cin, pass);
	char c;
	if (professor->auth(loginid, pass))
	{
		string name;
		professor->returnName(&name);
		cout << "WELCOME " << name;
		cout << endl;
		cout << "1) UPLOAD ATTENDANCE" << endl;
		cout << "2) UPLOAD QUIZ" << endl;
		cout << "3) SHOW QUIZES" << endl;
		cout << "4) SHOW SUBMITTED QUIZES" << endl;
		cin >> c;
		switch (c)
		{
		case '1':
			professor->uploadattendance();
			break;
		case '2':
			professor->quizfunc();
			break;
		case '3':
			professor->showquiz();
			break;
		case '4':
			professor->showsubmittedquiz();
			break;
		}
	}
	else
	{
		cout << "INVALID LOGIN ID OR PASSWORD" << endl;
	}
}



int main()
{
    User user;
    Admin admin;
    Professor professor;

    printBanner();  // Add this at the start of main

    while (true)
    {
        printMainMenu();  // Replace the existing menu print statements with this
        char ch;
        cin >> ch;

        string id, pass;  // Moved these declarations outside the switch

        switch (ch)
        {
        case '1':
            {
                string id, pass;
                cout << CYAN << "\n=== " << "Admin" << " Login ===" << RESET << endl;
                cout << GREEN << "Login ID: " << RESET;
                cin >> id;
                cout << GREEN << "Password: " << RESET;
                cin >> pass;
                if (id == admin.returnloginid() && pass == admin.password())
                    adminTasks(&admin);
                else
                    cout << "Invalid login credentials!" << endl;
            }
            break;
        case '2':
            {
                userTasks(&user);
            }
            break;
        case '3':
            {
                facultyTasks(&professor);
            }
            break;
        case '4':
            cout <<"Exiting program. Goodbye!"<<endl;
            exit(0);
        default:
            cout<<"Incorrect option."<<endl;
        }
    }
    return 0;
}
