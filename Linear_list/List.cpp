#include <iostream>
#include <cstddef>
#include <fstream>
#include <cstdlib>
using namespace std;

/* Используйте линейный список для представления многочлена от переменной x,
упорядоченного по степеням x. Напишите программу для дифференциального многочлена */

struct Node
{
	int coeff;
	int deg;
	Node *next;
};

typedef Node *PNode;

PNode CreateNode(int _coeff, int _deg) 
{
	PNode NewNode = new Node;
	NewNode->coeff = _coeff;
	NewNode->deg = _deg;
	NewNode->next = NULL;
	return NewNode;
}

class polynom
{
	private:
		PNode Head;
	public:
		polynom();
		~polynom();
		void input();
		void input_file(string filename);
		void output();
		void output_file(string filename);
		void diff();
		friend ostream& operator<<(ostream& os, polynom&); 
		friend istream& operator >> (istream& in, polynom&);
};

void polynom::input_file(string filename)
{
	int _coeff, _deg;
	PNode p = Head;
	ifstream f;
	f.open(filename);

	if (f.is_open() == 0)
	{
		cout << endl << "Ошибка: файл не существует или не может быть открыт" << endl;
		exit(1);
	}
	else
	{
		cout << endl << "Файл успешно загружен!" << endl;
		f >> _coeff;
		f >> _deg;
		while (!f.eof())
		{
			p->next = CreateNode(_coeff, _deg);
			p = p->next;
			f >> _coeff;
			f >> _deg;
		}
	}
	f.close();
}

void polynom::input()
{
	int _coeff, _deg;
	PNode p = Head;
	cout << "Введите упорядоченный по степеням x многочлен:" << endl << "(для остановки ввода используйте 0 0)" << endl << endl;
	cout << "Введите 1-й одночлен: " << endl;
	cout << "Коэффициент при x: ";
	cin >> _coeff;
	cout << "Степень x: ";
	cin >> _deg;
	cout << endl;
	int i = 2;
	while (_coeff != 0)
	{
		cout << "Введите " << i << "-й одночлен: " << endl;
		p->next = CreateNode(_coeff, _deg);
		p = p->next;
		cout << "Коэффициент при x: ";
		cin >> _coeff;								// пост-условие для цикла
		cout << "Степень x: ";
		cin >> _deg;
		cout << endl;
		i++;
	}
}

polynom::polynom()
{
	Head = new Node;
}

void polynom::output()
{
	PNode p = Head->next;
	while (p)
	{
		if ((p->deg) > 0)
		{
			cout << p->coeff << "x^" << p->deg;
		}
		else
		{
			cout << p->coeff;
		}
		if (p->next)
		{
			cout << "+";
		}
		p = p->next;
	}
	cout << endl;
}

void polynom::output_file(string filename)
{
	cout << endl << "Записать вывод в файл?" << endl << "1 - да, 0 - нет" << endl;
	bool choose;
	cin >> choose;
	if (choose)
	{
		ofstream f;
		f.open(filename);
		f << "Результат дифференцирования: " << endl;
		PNode p = Head->next;
		while (p)
		{
			if ((p->deg) > 0)
			{
				f << p->coeff << "x^" << p->deg;
			}
			else
			{
				f << p->coeff;
			}
			if (p->next)
			{
				f << "+";
			}
			p = p->next;
		}
		f << endl;
		f.close();
		cout << "Файл был успешно записан" << endl;
	}
	else return;
}

void polynom::diff()
{
	PNode p = Head->next;
	while (p)
	{
		p->coeff = (p->coeff)*(p->deg);
		p->deg -= 1;
		p = p->next;
	}
}

polynom::~polynom()
{
	delete[] Head;
}

ostream& operator<<(ostream& os, polynom &object)
{
	PNode p = object.Head->next;
	while (p)
	{
		if ((p->deg) > 0)
		{
			os << p->coeff << "x^" << p->deg;
		}
		else
		{
			os << p->coeff;
		}
		if (p->next)
		{
			os << "+";
		}
		p = p->next;
	}
	cout << endl;
	return os;
}

istream& operator >> (istream& in, polynom &object)
{
	char trash;
	char again;
	int _coeff, _deg;
	PNode p = object.Head;
	in >> _coeff;
	in >> _deg;
	while (!in.eof())
	{
		p->next = CreateNode(_coeff, _deg);
		p = p->next;
		in >> _coeff;
		in >> _deg;
	}
	return in;
}

void choose_input(polynom &A, string filename)
{
	cout << endl << "Введите способ ввода многочлена (0 - клавиатура, 1 - файл): ";
	bool choose;
	cin >> choose;
	if (choose == false)
	{
		A.input();
	}
	else
	{
		ifstream f;
		f.open(filename);
		if (f.is_open() == 0)
		{
			cout << endl << "Ошибка: файл не существует или не может быть открыт" << endl;
			exit(1);
		}
		else
		{
			cout << endl << "Файл успешно загружен!" << endl;
			f >> A;
		}
		f.close();
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	polynom A;
	
	cout << "Программа дифференцирования многочлена";
	choose_input(A, "input.txt");

	cout << "Полученный многочлен: ";
	cout << A;
	A.diff();
	cout << "Результат дифференцирования: ";
	cout << A;
	A.output_file("output.txt");
	return 0;
}