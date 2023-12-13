#include <iostream>

using namespace std;

class Date
{
	int day;
	int month;
	int year;

public:
	Date(): day(0), month(0), year(0){}
	Date(int d, int m, int y): day(d), month(m),year(y) {} //nu am cum sa instantiez obiecte daca nu am constructorul public
	
};

class Person
{
	string name;
	string pin;
	Date birthday;
	string* addresses;
	int addressesCount;

public:
	Person()
	{
		this->name = "";
		this->pin = "";
		Date d;
		this->birthday = d;
		this->addresses = nullptr;
		this->addressesCount = 0;
	}
	Person(string name, string pin, Date birthday, string* addresses, int addressesCount) :
		 name(name), pin(pin), birthday(birthday), addressesCount(addressesCount)
	{
		this->addresses = new string[addressesCount];
		for(int i = 0; i < addressesCount; i++)
		{
			this->addresses[i] = addresses[i];
		}
	}

	Person(const Person& person)
	{
		this->name = person.name;
		this->pin = person.pin;
		this->addressesCount = person.addressesCount;
		this->birthday = person.birthday;
		this->addresses = new string[person.addressesCount];
		for (int i = 0; i < person.addressesCount; i++)
		{
			this->addresses[i] = person.addresses[i];
		}
	}

	Person& operator=(const Person& person)
	{
		if (this != &person)
		{
			this->name = person.name;
			this->pin = person.pin;
			this->addressesCount = person.addressesCount;
			this->birthday = person.birthday;
			delete[] this->addresses;
			this->addresses = new string[person.addressesCount];
			for (int i = 0; i < person.addressesCount; i++)
			{
				this->addresses[i] = person.addresses[i];
			}
		}
		return* this;
	}

	~Person()
	{
		delete[] addresses;
	}
};

class Student : Person
{
	int regNo;
	float* grades;
	int gradesCount;
	bool scholarship;

public:
	Student() : Person()
	{
		this->regNo = 0;
		this->grades = nullptr;
		this->gradesCount = 0;
		this->scholarship = false;
	}

	Student(string name, string pin, Date birthday, string* addresses, int addressesCount,
		int regNo, float* grades, int gradesCount, bool scholarship) : Person(name, pin, birthday, addresses, addressesCount),
		regNo(regNo), gradesCount(gradesCount), scholarship(scholarship)
	{
		this->grades = new float[gradesCount];
		for (int i = 0; i < gradesCount; i++)
		{
			this->grades[i] = grades[i];
		}
	}

	Student(const Student& s) : Person(s), regNo(s.regNo), gradesCount(s.gradesCount), 
		scholarship(s.scholarship)
	{
		this->grades = new float[s.gradesCount];
		for (int i = 0; i < s.gradesCount; i++)
		{
			grades[i] = s.grades[i];
		}
	}

	Student& operator=(const Student& s)
	{
		Person::operator=(s);
		if (this != &s)
		{
			this->regNo = s.regNo;
			this->gradesCount = s.gradesCount;
			this->scholarship = s.scholarship;

			delete[] grades;
			this->grades = new float[s.gradesCount];
			for (int i = 0; i < s.gradesCount; i++)
			{
				grades[i] = s.grades[i];
			}
		}
		return *this;
	}

	~Student()
	{
		delete[]grades;
	}

};

class University
{
	string name = "";
	string address = "";
	Student* students = nullptr;
	int studentsCount = 0;

public:
	University(string name, string address, Student* students, int studentsCount)
		: name(name), address(address), studentsCount(studentsCount)
	{
		this->students = new Student[studentsCount];
		for (int i = 0; i < studentsCount; i++) //discutie despre shallow copy si constructorul de copiere
		{
			this->students[i] = students[i];
		}
	}

	University(const University& u) : name(u.name), address(u.address), studentsCount(u.studentsCount)
	{
		this->students = new Student[u.studentsCount];
		for (int i = 0; i < u.studentsCount; i++)
		{
			students[i] = u.students[i];
		}
	}

	University& operator=(const University& u)
	{
		if (this != &u)
		{
			this->name = u.name;
			this->address = u.address;
			this->studentsCount = u.studentsCount;

			delete[] this->students;
			
			this->students = new Student[u.studentsCount];
			for (int i = 0; i < u.studentsCount; i++)
			{
				students[i] = u.students[i];
			}
		}

		return *this;
	}

	~University()
	{
		delete[] students;
	}

};

int main()
{

	Date d1;
	Date d2(5, 5, 1992);
	Person p1;
	string* addresses = new string[3];
	addresses[0] = "Bucuresti";
	addresses[1] = "Arad";
	addresses[2] = "Sibiu";

	Person p2("popescu andrii", "123456789", d2, addresses, 3 );

	Student  s1;
	float* grades = new float[5];
	grades[0] = 6;
	grades[1] = 7;
	grades[2] = 8;
	grades[3] = 9;
	grades[4] = 10;

	Student s2("popescu andrii", "123456789", d2, addresses, 3, 123, grades, 5, true);

	Student s3("andresan andrii", "123456789", d2, addresses, 3, 123, grades, 5, true);

	Student* students = new Student[3];
	students[0] = s1;
	students[1] = s2;
	students[2] = s3;

	University u1("ase", "bucuresti", students, 3);

	return 0;
}