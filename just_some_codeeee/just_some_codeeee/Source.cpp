#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<iomanip>
#include <fstream>

using namespace std;

struct Student
{
	string name, surname, date;
};

void RW(Student *student, int n, const char *file_name);	//1 реалізац
void RW(int n, string file_name);	//2
void RD(Student *student, int n, const char *file_name);	//1 реалізац
int RD(string **student_data, int n, string file_name);	//2

int main()
{
	int n, i = 0, j = 0;
	const char *file_name1 = "INFO.dat";
	string file_name2 = "INFO.txt";
	cout << "Enter number of students: ";	cin >> n;
	Student *student, *student1;
	student = new Student[n];
	student1 = new Student[n];
	RW(student, n, file_name1);
	RD(student1, n, file_name1);

	cout << "Enter new number of students: ";	cin >> n;
	string **student_data = new string*[n];
	for (i = 0; i < n; i++)
	{
		student_data[i] = new string[4];
	}

	RW(n, file_name2);
	RD(student_data, n, file_name2);

	for (int i = 0; i < n; i++)
		delete[]student_data[i];

	system("pause");
	return 0;
}

void RW(Student *student, int n, const char *file_name)	//1 реалізація
{
	int i = 0;
	while (i < n)
	{
		cout << "name: ";		cin >> student[i].name;
		cout << "surname: ";	cin >> student[i].surname;
		cout << "date: ";		cin >> student[i].date;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		i++;
	}
	FILE *ostream = fopen(file_name, "w+");
	if (!ostream)
	{
		cout << "Errror! Can't open file!!!";
		system("pause");
		exit(1);
	}
	fwrite(&student, sizeof(student), 1, ostream);
	fclose(ostream);
}

void RW(int n, string file_name)	//2 реалізація
{
	int i = 0;
	string name, surname, adress, phone;
	ofstream File(file_name);
	while (i < n)
	{
		cout << "name: ";		cin >> name;		File << name << ' ';
		cout << "surname: ";	cin >> surname;		File << surname << ' ';
		cout << "adress: ";		cin >> adress;		File << adress << ' ';
		cout << "phone: ";		cin >> phone;		File << phone << ' ';
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		i++;
	}
	File.close();
}

void RD(Student *student, int n, const char *file_name)	//1 реалізація
{
	int i = 0;
	string search_date;
	FILE *istream = fopen(file_name, "rb");
	if (istream == NULL)
	{
		cout << "Error. Can't open file!!!";
		system("pause");
		exit(1);
	}
	fread(&student, sizeof(student), 1, istream);
	cout << "Enter date you want to search: ";	cin >> search_date;
	cout << "Searched students: " << endl;
	for (int i = 0; i < n; i++)
	{
		if (student[i].date == search_date)
		{
			cout << student[i].surname << endl;
		}
	}
	fclose(istream);
}

int RD(string **student_data, int n, string file_name)		//2 реалізація
{
	int i = 0, j = 0;

	ifstream File(file_name);
	if (!File)
	{
		cout << "Errror! Can't open file!!!";
		return 1;
	}
	else
	{
		i = 0;
		cout << "Students' data from file: " << endl;
		while (i < n)
		{
			getline(File, student_data[i][j], ' ');
			getline(File, student_data[i][j + 1], ' ');
			getline(File, student_data[i][j + 2], ' ');
			getline(File, student_data[i][j + 3], ' ');
			i++;
		}
		for (i = 0; i < n - 1; i++)
		{
			for (int k = i + 1; k < n; k++)
			{
				if (strcmp(student_data[i][j + 2].c_str(), student_data[k][j + 2].c_str()) > 0) swap(student_data[i][j + 2], student_data[k][j + 2]);
			}
		}
		for (i = 0; i < n; i++)
		{
			cout << student_data[i][j + 1] << ' ';
			cout << student_data[i][j + 2] << endl;
		}
	}

	File.close();
	return 0;
}