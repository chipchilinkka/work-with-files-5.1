#include <iostream>
#include<windows.h>
#include<fstream>
#include<vector>
#include <iomanip>

using namespace std;

//NAMES.TXT
struct names
{
	int number; //номер
	string name_b; // имя банка
};

//PLANX.TXT
struct plans
{
	char plan; //буква
	int num_sc; //номер счета
	string name;
};

//101F
struct money
{
	int regn; //рег номер банка
	char plan; //буква
	int num_sc; //номер счета
	char a_p;
	float vr;
	float vv;
	float vitg;
	float ora;
	float ova;
	float oitga;
	float orp;
	float ovr;
	float oitgp;
	float ir;
	float iv;
	float iitg; //денежный остаток на счете
	string dt; // отчетная дата
	int time;
	float priz;
};

//для храненич результаов
struct res
{
	int regn; //рег номер
	int num_sc; //нмоер счета
	string dt; //отчетная дата
	float iitg; //денежный остаток на счете
};

//фции для считывания данных и записи в векторы 
void read_names(const char* file_n, vector<names>& vec_n);
void read_plans(const char* file_n, vector<plans>& vec_n);
void read_money(const char* file_n, vector<money>& vec_n);

//для поиска имени банка
string  read_name(int num_regn, vector<names> vec_n); //имя банка по номеру
string read_plan(int num_sc_n, vector<plans> vec_n); //имя счета по номеру

//по н рег и н счета денежные остатки на все отчет даты и резульатт в вектор
void search_money(int num_regn, int num_sc_n, vector<money> vec_mon, vector<res>& vec_r);

void show_res(vector<res> vec_r); //вывод 
void write_res(const char* file_n, vector<res> vec_r); //результаты в файл

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char* file_names = "C:\\Users\\79523\\Documents\\прога 2 сем\\NAMES.txt";
	const char* file_plan = "C:\\Users\\79523\\Documents\\прога 2 сем\\PLAN.txt";
	const char* file_101F = "C:\\Users\\79523\\Documents\\прога 2 сем\\101F.txt";
	const char* file_result = "C:\\Users\\79523\\Documents\\прога 2 сем\\RESULT.txt";


	vector<names> vname;
	vector<plans> vplan;
	vector<money> vmoney;
	vector<res> vres;

	int regn;
	int num_sc;

	read_names(file_names, vname);
	cout << "Загружено " << vname.size() << " записей из файла NAMES.txt" << endl;

	read_plans(file_plan, vplan);
	cout << "Загружено " << vplan.size() << " записей из файла PLAN.txt" << endl;

	read_money(file_101F, vmoney);
	cout << "Загружено " << vmoney.size() << " записей из файла 101F.txt" << endl;

	cout << "Введите рег. номер банка: ";
	cin >> regn;

	cout << "Введите номер счета: ";
	cin >> num_sc;


	string name_sc = read_plan(num_sc, vplan);
	cout << endl << "Денежные остатки на счете " << num_sc << " " << name_sc << endl;

	string bank_name = read_name(regn, vname);
	cout << endl << "Для банка " << regn << " " << bank_name << endl;

	search_money(regn, num_sc, vmoney, vres);
	show_res(vres);

	write_res(file_result, vres);
}

//NAMES.TXT
void read_names(const char* file_n, vector<names>& vec_n)
{
	ifstream file(file_n);
	int regn;
	char ch;
	const int M = 80;
	char str[M];

	names temp;

	while (file)
	{
		file >> regn;
		if (file.eof())
		{
			break;
		}

		file >> ch; //;

		file.get(str, M); //имя банка в массив символов

		temp.number = (int)regn;
		temp.name_b = str;

		vec_n.push_back(temp);
	}

}

//PLAN.txt
void read_plans(const char* file_n, vector<plans>& vec_n)
{
	ifstream file(file_n);

	char plan;
	int num_sc;
	char ch;
	const int M = 380;
	char name[M];
	plans temp;

	while (file)
	{
		file >> plan;
		if (file.eof())
		{
			break;
		}
		file >> ch >> num_sc >> ch;

		file.get(name, M);

		temp.plan = plan;
		temp.num_sc = num_sc;
		temp.name = name;

		vec_n.push_back(temp);
	}

}
//101F.txt
void read_money(const char* file_n, vector<money>& vec_n)
{
	const int M = 11;
	float regn, vr, vv, vitg, ora, ova, oitga, orp, ovr, oitgp, ir, iv, iitg, priz;
	char ch, plan, a_p;
	int num_sc, time;
	char dt[M];

	money temp;

	ifstream file(file_n);

	while (file)
	{
		file >> regn;
		if (file.eof())
		{
			break;
		}
		file >> ch >> plan >> ch >> num_sc >> ch >> a_p >> ch
			>> vr >> ch >> vv >> ch >> vitg >> ch >> ora
			>> ch >> ova >> ch >> oitga >> ch >> orp >> ch
			>> ovr >> ch >> oitgp >> ch >> ir >> ch >> iv
			>> ch >> iitg >> ch;

		file.get(dt, M); // Читаем дату


		file >> ch >> time >> ch >> priz;

		temp.regn = (int)regn;
		temp.plan = plan;
		temp.num_sc = num_sc;
		temp.a_p = a_p;
		temp.vr = vr;
		temp.vv = vv;
		temp.vitg = vitg;
		temp.ora = ora;
		temp.ova = ova;
		temp.oitga = oitga;
		temp.orp = orp;
		temp.ovr = ovr;
		temp.oitgp = oitgp;
		temp.ir = ir;
		temp.iv = iv;
		temp.iitg = iitg;
		temp.dt = dt;
		temp.time = time;
		temp.priz = priz;
		vec_n.push_back(temp);
	}


}

//имя банка по номеру
string  read_name(int num_regn, vector<names> vec_n)
{
	for (int i = 0; i < vec_n.size(); i++)
	{
		if (vec_n[i].number == num_regn)
		{
			return vec_n[i].name_b;
		}
	}
	return "Нет банка";
}

//имя счета по номеру
string read_plan(int num_sc_n, vector<plans> vec_n)
{
	for (int i = 0; i < vec_n.size(); i++)
	{
		if (vec_n[i].num_sc == num_sc_n)
		{
			return vec_n[i].name;
		}
	}

	return "Нет счета";
}

//по н рег и н счета денежные остатки на все отчет даты и резульатт в вектор
void search_money(int num_regn, int num_sc_n, vector<money> vec_mon, vector<res>& vec_r)
{
	for (int i = 0; i < vec_mon.size(); i++)
	{
		if (vec_mon[i].regn == num_regn and vec_mon[i].num_sc == num_sc_n) //усие
		{
			res r;
			r.regn = vec_mon[i].regn; //рег номер
			r.num_sc = vec_mon[i].num_sc; //номер счета
			r.dt = vec_mon[i].dt; //отчетная дата
			r.iitg = vec_mon[i].iitg; //остаток на счете

			vec_r.push_back(r);
		}
	}
}

void show_res(vector<res> vec_r)
{
	if (vec_r.empty())
	{
		cout << "Нет результатов" << endl;
		return;
	}

	cout << setw(15) << "Дата" << setw(25) << "Сумма, тыс. руб." << endl;

	for (int i = 0; i < vec_r.size(); i++)
	{
		cout << setw(15) << vec_r[i].dt << setw(25) << vec_r[i].iitg << endl;
	}
}
void write_res(const char* file_n, vector<res> vec_r)
{
	ofstream file(file_n);
	file << setw(15) << "Дата" << setw(25) << "Сумма, тыс. руб." << endl;

	for (int i = 0; i < vec_r.size(); ++i) //по всем элтам вра
	{
		file << setw(15) << vec_r[i].dt << setw(25) << vec_r[i].iitg << endl;
	}

	cout << "Результаты (" << vec_r.size() << ") записаны в файл" << endl;
}