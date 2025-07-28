#include <iostream>
#include<windows.h>
#include<fstream>
#include<vector>
#include <iomanip>

using namespace std;

//NAMES.TXT
struct names
{
	int number; //�����
	string name_b; // ��� �����
};

//PLANX.TXT
struct plans
{
	char plan; //�����
	int num_sc; //����� �����
	string name;
};

//101F
struct money
{
	int regn; //��� ����� �����
	char plan; //�����
	int num_sc; //����� �����
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
	float iitg; //�������� ������� �� �����
	string dt; // �������� ����
	int time;
	float priz;
};

//��� �������� ����������
struct res
{
	int regn; //��� �����
	int num_sc; //����� �����
	string dt; //�������� ����
	float iitg; //�������� ������� �� �����
};

//���� ��� ���������� ������ � ������ � ������� 
void read_names(const char* file_n, vector<names>& vec_n);
void read_plans(const char* file_n, vector<plans>& vec_n);
void read_money(const char* file_n, vector<money>& vec_n);

//��� ������ ����� �����
string  read_name(int num_regn, vector<names> vec_n); //��� ����� �� ������
string read_plan(int num_sc_n, vector<plans> vec_n); //��� ����� �� ������

//�� � ��� � � ����� �������� ������� �� ��� ����� ���� � ��������� � ������
void search_money(int num_regn, int num_sc_n, vector<money> vec_mon, vector<res>& vec_r);

void show_res(vector<res> vec_r); //����� 
void write_res(const char* file_n, vector<res> vec_r); //���������� � ����

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char* file_names = "C:\\Users\\79523\\Documents\\����� 2 ���\\NAMES.txt";
	const char* file_plan = "C:\\Users\\79523\\Documents\\����� 2 ���\\PLAN.txt";
	const char* file_101F = "C:\\Users\\79523\\Documents\\����� 2 ���\\101F.txt";
	const char* file_result = "C:\\Users\\79523\\Documents\\����� 2 ���\\RESULT.txt";


	vector<names> vname;
	vector<plans> vplan;
	vector<money> vmoney;
	vector<res> vres;

	int regn;
	int num_sc;

	read_names(file_names, vname);
	cout << "��������� " << vname.size() << " ������� �� ����� NAMES.txt" << endl;

	read_plans(file_plan, vplan);
	cout << "��������� " << vplan.size() << " ������� �� ����� PLAN.txt" << endl;

	read_money(file_101F, vmoney);
	cout << "��������� " << vmoney.size() << " ������� �� ����� 101F.txt" << endl;

	cout << "������� ���. ����� �����: ";
	cin >> regn;

	cout << "������� ����� �����: ";
	cin >> num_sc;


	string name_sc = read_plan(num_sc, vplan);
	cout << endl << "�������� ������� �� ����� " << num_sc << " " << name_sc << endl;

	string bank_name = read_name(regn, vname);
	cout << endl << "��� ����� " << regn << " " << bank_name << endl;

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

		file.get(str, M); //��� ����� � ������ ��������

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

		file.get(dt, M); // ������ ����


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

//��� ����� �� ������
string  read_name(int num_regn, vector<names> vec_n)
{
	for (int i = 0; i < vec_n.size(); i++)
	{
		if (vec_n[i].number == num_regn)
		{
			return vec_n[i].name_b;
		}
	}
	return "��� �����";
}

//��� ����� �� ������
string read_plan(int num_sc_n, vector<plans> vec_n)
{
	for (int i = 0; i < vec_n.size(); i++)
	{
		if (vec_n[i].num_sc == num_sc_n)
		{
			return vec_n[i].name;
		}
	}

	return "��� �����";
}

//�� � ��� � � ����� �������� ������� �� ��� ����� ���� � ��������� � ������
void search_money(int num_regn, int num_sc_n, vector<money> vec_mon, vector<res>& vec_r)
{
	for (int i = 0; i < vec_mon.size(); i++)
	{
		if (vec_mon[i].regn == num_regn and vec_mon[i].num_sc == num_sc_n) //����
		{
			res r;
			r.regn = vec_mon[i].regn; //��� �����
			r.num_sc = vec_mon[i].num_sc; //����� �����
			r.dt = vec_mon[i].dt; //�������� ����
			r.iitg = vec_mon[i].iitg; //������� �� �����

			vec_r.push_back(r);
		}
	}
}

void show_res(vector<res> vec_r)
{
	if (vec_r.empty())
	{
		cout << "��� �����������" << endl;
		return;
	}

	cout << setw(15) << "����" << setw(25) << "�����, ���. ���." << endl;

	for (int i = 0; i < vec_r.size(); i++)
	{
		cout << setw(15) << vec_r[i].dt << setw(25) << vec_r[i].iitg << endl;
	}
}
void write_res(const char* file_n, vector<res> vec_r)
{
	ofstream file(file_n);
	file << setw(15) << "����" << setw(25) << "�����, ���. ���." << endl;

	for (int i = 0; i < vec_r.size(); ++i) //�� ���� ����� ���
	{
		file << setw(15) << vec_r[i].dt << setw(25) << vec_r[i].iitg << endl;
	}

	cout << "���������� (" << vec_r.size() << ") �������� � ����" << endl;
}