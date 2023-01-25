#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include<fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int SIZE_TABLE=100; // ������ �������
int s=0;

// �������� ����
void menu_main()
{
	cout << "����\n"
		<< "1. ������ � �������\n"
		<< "2. ������ � ������\n"
		<< "3. ������ � ������ � �������� ����������� � �����\n"
		<< "0. ���������� ������\n";
	cout << "=====================\n�������� ��������:  ";
}

// ���� ��������
void menu_patients()
{
	cout << "�������\n"
		<< "1. ����������� ��������\n"
		<< "2. �������� ��������\n"
		<< "3. �������� �������\n"
		<< "4. ����� �������� �� ���������������� ������\n"
		<< "5. ����� �������� �� ���\n"
		<< "6. �������� ���� �������\n"
		<< "7. ������� ������� �� �����\n"
		<< "0. ������� � ����\n";
	cout << "=======================================\n�������� ��������:  ";
}

// ���� �����
void menu_doctors()
{
	cout << "����\n"
		<< "1. ���������� �����\n"
		<< "2. �������� �����\n"
		<< "3. �������� ���� ������\n"
		<< "4. ����� ����� �� ���\n"
		<< "5. ����� ����� �� ���������\n"
		<< "6. �������� ���� ������\n"
		<< "7. ������� ������ �� �����\n"
		<< "0. ������� � ����\n";
	cout << "==============================\n�������� ��������:  ";
}

// ���� ��� ������ � �������� �����������
void menu_issue_and_refund()
{
	cout << "������ � ������� ����������� � �����\n"
		<< "1. ������ �����������\n"
		<< "2. ������� �����������\n"
		<<"3.���������� ��� �����������\n"
		<<"4.��������� ����������� �� �����\n"
		<< "0. ������� � ����\n";
	cout << "=============================\n�������� ��������:  ";
}

//�������
struct Patient
{
	string regist_number; // �MM-NNNNNN�,��� MM � ����� �������(�����); NNNNNN � ���������� �����(�����)
	string all_name; // ���
	int year_of_birth; // ��� ��������
	string address; // �����
	string place_of_work; // ����� ������
};

// ��������� ���-�������
struct Hash
{
	int collision = 0; // ���-�� ��������
	int position = 0; // �������
	Patient* patient=NULL; // �������
	Hash* next = NULL; // ��������� ������� ����������� ������
	Hash* prev = NULL; // ���������� ������� ����������� ������
	string metka;
};

//����
struct Doctor
{
	string fio_doctor; //��� �����
	string position; // 
	int number_cabinet; //
	string time; // 
	string time_1;
};

//��������� ������
struct Three
{
	int height; // ������ ���������
	Doctor* doctor = NULL; // ������ � �����
	Three* left = NULL; // ����� ������� ���������
	Three* right = NULL; // ������ ������� ���������
};

//�����������
struct Ticket
{
	string registr;
	string fio_doctor;
	string date;
	string time;
};

//��������� ������
struct Data
{
	Ticket* ticket;
	Data* next = NULL;
	Data* prev = NULL;
};

// �������� ���-�������
void create_hash_table(Hash*& start_ht, Hash*& end_ht)
{
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		if (i == 0)
		{
			end_ht = start_ht;
			continue;
		}
		Hash* append = new Hash;
		append->position = i;
		append->next = start_ht;
		append->prev = end_ht;
		end_ht->next = append;
		end_ht = append;
		append->metka = "";
		append->patient = NULL;
	}
}

//��������� ����
int HashFunctionHorner(string s, int key)
{
	int hash_result = 0;
	for (int i = 0; i < s.size(); i++)
		hash_result = (key * hash_result + s[i]) % SIZE_TABLE;
	hash_result = (hash_result * 2 + 1) % SIZE_TABLE;
	return hash_result;
}

// ������ ��� �������
int hash_position(string r)
{
	return HashFunctionHorner(r, SIZE_TABLE - 1);
}

//������ ��� �������
int hash_position2(string r)
{
	return HashFunctionHorner(r, SIZE_TABLE + 1);
}

// �������� �� ���� �������. ������
void checkRegist(string& regist)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, regist);
	while (true)
	{
		//�MM-NNNNNN� MM � ����� �������(�����), NNNNNN � ���������� �����(�����)
		if ((int)regist[0] >= 48 && (int)regist[0] <= 57 && (int)regist[1] >= 48 && (int)regist[1] <= 57 
			&& (int)regist[2] == 45 && (int)regist[3] >= 48 && (int)regist[3] <= 57
			&& (int)regist[4] >= 48 && (int)regist[4] <= 57 &&  (int)regist[5] >= 48 && (int)regist[5] <= 57
			&& (int)regist[6] >= 48 && (int)regist[6] <= 57 && (int)regist[7] >= 48 && (int)regist[7] <= 57 
			&& (int)regist[8] >= 48 && (int)regist[8] <= 57 && regist.size() == 9)
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "������� ��������������� ����� �������� �MM-NNNNNN�,��� MM � ����� �������(�����); NNNNNN � ���������� �����(�����): ";
			getline(cin, regist);
		}
	}
}

// �������� ����� ������ ���� ������
int check_menu(int& m)
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin >> m;
	while ((cin.fail()) || (cin.get() != '\n') || (m < 0) || (m > 3))
	{
		cout << "������� ����� ���� ��������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> m;
	}
	return m;
}

//�������� �� ���� ������ ���� ������� � ������
int check_menu1(int& m)
{
	cin >> m;
	while ((cin.fail()) || (cin.get() != '\n') || (m < 0) || (m > 7))
	{
		cout << "������� ����� ���� ��������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> m;
	}
	return m;
}

//�������� ������ ���� �����������
int check_menu2(int& m)
{
	cin >> m;
	while ((cin.fail()) || (cin.get() != '\n') || (m < 0) || (m > 4))
	{
		cout << "������� ����� ���� ��������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> m;
	}
	return m;
}

//�������� �� ���� ���� ��������
int check_year(int& m)
{
	cin >> m;
	while ((cin.fail()) || (cin.get() != '\n') || (m < 1920) || (m > 2022))
	{
		cout << "������� ��� �������� ��������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> m;
	}
	return m;
}

//�������� ��������� ��� ��������
string check_fio(string z)
{
	int check = 0;
	int kolvo = 0;
	for (int i = 0; i < z.length(); i++) {
		if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int(z[i]) == int('�') ||
			int(z[i]) == int('�') ||
			int(z[i]) == 32)
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length()+1; i++) {
		if (int(z[i]) == 32) kolvo++;
		if (int(z[i]) == 32 && int(z[i + 1]) == 32 || int(z[0]) == int('\0') || int(z[0])==int(' '))
			check = 0;
		if (int(z[i]) == 32 && !(int('�') <= int(z[i+1]) && int(z[i+1]) <= int('�')|| int(z[i]) == int('�')) || (!(int('�') <= int(z[0]) && int(z[0]) <= int('�')|| int(z[i]) == int('�'))))
			check = 0;
	}

	while ((cin.fail()) || check == 0 || kolvo != 2)
	{
		kolvo = 0;
		cout << "������������ ����!. ���������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		for (int i = 0; i < z.length(); i++) {
			if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int(z[i]) == int('�') ||
				int(z[i]) == int('�') ||
				int(z[i]) == 32)
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length(); i++) {
			if (int(z[i]) == 32) kolvo++;
			if (int(z[i]) == 32 && int(z[i + 1]) == 32 || int(z[0]) == int('\0') || int(z[0]) == int(' '))
				check = 0;
			if (int(z[i]) == 32 && !(int('�') <= int(z[i + 1]) && int(z[i + 1]) <= int('�') || int(z[i+1]) == int('�')) || (!(int('�') <= int(z[0]) && int(z[0]) <= int('�')|| int(z[0]) == int('�'))))
				check = 0;
		}
	}
	return z;
}

//�������� ���������� ����� ������
string check_work(string z)
{
	int check = 0;
	int kolvo = 0;
	for (int i = 0; i < z.length(); i++) {
		if (int('a') <= int(z[i]) && int(z[i]) <= int('z') ||
			int('A') <= int(z[i]) && int(z[i]) <= int('Z') ||
			int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int(z[i]) == int('�') ||
			int(z[i]) == int('�') ||
			int(z[i]) == 32)
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0'))
		{
			check = 0; break;
		}
		else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[z.length() - 1] == 32)) || int(z[0]) == int('\0') || int(z[0]) == int(' '))
		{
			check = 0; break;
		}
	}

	while ((cin.fail()) || check == 0)
	{
		kolvo = 0;
		cout << "������������ ����!. ���������: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		for (int i = 0; i < z.length(); i++) {
			if (int('a') <= int(z[i]) && int(z[i]) <= int('z') ||
				int('A') <= int(z[i]) && int(z[i]) <= int('Z') ||
				int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int(z[i]) == int('�') ||
				int(z[i]) == int('�') ||
				int(z[i]) == 32)
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length(); i++) {
			if (int(z[0]) == int('\0'))
			{
				check = 0; break;
			}
			else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[z.length() - 1] == 32)) || int(z[0]) == int('\0') || int(z[0]) == int(' '))
			{
				check = 0; break;
			}
		}
	}
	return z;
}

//�������� �� ���� ������
string check_adress(string z)
{
	int check = 0;
	for (int i = 0; i < z.length(); i++) {
		if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
			int(z[i]) == int('�') || int(z[i]) == int('�') ||
			int(z[i]) >= int('0') && int(z[i]) <= ('9') || 
			int (z[i])==int('.')|| int(z[i])==int(',')||int (z[i])==int('-')||
			int(z[i]) == 32)
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0'))
		{
			check = 0; break;
		}
		else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[0] == 32)) || int(z[0]) == int('\0') ||
			//�������� ������� ������� �� ������������ ������� � ��������� ������ ����������� ����� (����, ��������)
			int(z[0]) == int('.') || int(z[0]) == int(',') || int(z[0]) == int('-') || int(z[z.length() - 1]) < int('0') || int(z[z.length() - 1]) > int('9'))
		{
			check = 0; break;
		}

	}

	while ((cin.fail()) || check == 0)
	{
		cout << "������������ ����!. ���������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		for (int i = 0; i < z.length(); i++) {
			if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int('�') <= int(z[i]) && int(z[i]) <= int('�') ||
				int(z[i]) == int('�') || int(z[i]) == int('�') ||
				int (z[i])>=int('0')&& int (z[i])<=('9')||
				int(z[i]) == int('.') || int(z[i]) == int(',') || int(z[i]) == int('-') ||
				int(z[i]) == 32)
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length(); i++) {
			if (int(z[0]) == int('\0'))
			{
				check = 0; break;
			}
			else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[0] == 32))||
				int(z[0]) == int('.') || int(z[0]) == int(',') || int(z[0]) == int('-') || int(z[z.length() - 1]) < int('0') || int(z[z.length() - 1]) > int('9'))
				check = 0;
		}
	}
	return z;
}

//��� �������� ���������� ������� �������
int find_to_registr(Hash*& start_ht, Hash*& end_ht, int k)
{
	// ���� ���������� ������
	if (start_ht->next == NULL)
	{
		return 0;
	}
	int count_searching = 0; // ��� �������� �� ������� ����������
	Hash* help = start_ht;
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		// ���� ������ �����
		if (help->patient == NULL)
		{
			help = help->next;
			continue;
		}
		// ���� ������ �� �����
		if (help->patient != NULL)
		{
			string regist=help->patient->regist_number;
			string num = regist.erase(0, 3);
			int reg = stoi(num);
			if (reg==k)
			{
				count_searching++;
			}
		}
		help = help->next;
	}
	if (count_searching == 0)
	{
		return 0;
	}
	else return 1;
}

//�������� �� ���� ������� � ���������������� ������
void checkM(string& regist)
{
	while (true)
	{
		if ((int)regist[0] >= 48 && (int)regist[0] <= 57 && (int)regist[1] >= 48 && (int)regist[1] <= 57
			&& regist.size() == 2 && regist != "00")
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cout << "������� ����� ������� (�� - �����) ��������; ";
			getline(cin, regist);
		}
	}
}

//��������� ���������������� ������ �� �������
string generate_regist_number(string key, int counter_patient)
{
	key += "-";
	if (counter_patient < 10)
	{
		key += "00000";
		key += to_string(counter_patient);
	}
	else if (counter_patient >= 10 && counter_patient < 100)
	{
		key += "0000";
		key += to_string(counter_patient);
	}
	else if (counter_patient >= 100 && counter_patient < 1000)
	{
		key += "000";
		key += to_string(counter_patient);
	}
	else if (counter_patient >= 1000 && counter_patient < 10000)
	{
		key += "00";
		key += to_string(counter_patient);
	}
	else if (counter_patient >= 10000 && counter_patient < 100000)
	{
		key += "0";
		key += to_string(counter_patient);
	}
	else
	{
		key += to_string(counter_patient);
	}
	return key;
}

//�������� ��������� �� �������
bool isfull(Hash*& start_ht)
{
	Hash* help = start_ht;
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		if (help->patient == NULL)
			return 1;
		help = help->next;
	}
	return 0;
}

// ���������� ��������
void add_patient(Hash*& start_ht, Hash*& end_ht, int& k)
{
	Patient* bolnoy = new Patient;
	int hash1;
	string key;
	cout << "������� ����� ������� (��-�����); ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, key);
	checkM(key);
	if (isfull(start_ht) == 0)
	{
		cout << "Table is full" << endl;
		system("pause");
		return;
	}
	bolnoy->regist_number = generate_regist_number(key,k);
	cout << "������� ��� ��������: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, bolnoy->all_name);
	bolnoy->all_name=check_fio(bolnoy->all_name);
	cout << "������� ��� �������� ��������: ";
	check_year(bolnoy->year_of_birth);
	cout << "������� ����� ����������: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, bolnoy->address);
	bolnoy->address = check_adress(bolnoy->address);
	cout << "������� ����� ������ (�����): ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, bolnoy->place_of_work);
	bolnoy->place_of_work=check_work(bolnoy->place_of_work);
	system("cls");
	hash1 = hash_position(bolnoy->regist_number); // ���������� ������� � �������
	// ���� ������� �� �������
	if (start_ht->next == NULL)
	{
		create_hash_table(start_ht, end_ht); // ������ �������
		Hash* help = start_ht;
		// �������� � ������� ��������
		for (int i = 0; i <= hash1; i++)
		{
			if (help->position == hash1)
			{
				// �������� � ������� � ������� �� �������
				help->patient = bolnoy;
				return;
			}
			help = help->next;
		}
	}
		// ������ ��������������� ���������� ��� �������� �� �������
		Hash* help = start_ht;
		// ���� ����� � ������� � ������������ ��������
		for (int i = 0; i <= (hash1+1); i++)
		{
			// ���� ��� ������ � �� ����� ������ �� �������� �������
			if (help->position == hash1 && help->patient == NULL)
			{
				help->patient = bolnoy;
				if (help->metka == "del")
					help->metka = "";
				return;
			}
			// ����� ���� ��� ������ � �� ����� ������ �������� �������
			else if (help->position == hash1 && help->patient != NULL)
			{
				help->collision++; // ��������� ��������
				int hash2 = hash_position2(bolnoy->regist_number);
				for (int j = 0;; j++)
				{
					hash1 = (hash1 + j * hash2) % SIZE_TABLE; // ������� �����������
					help = start_ht; // ������ ���������� ��� ��������� ��������
					for (int n = 0; n <= (hash1+1); n++)
					{
						// ���� ��� ������ � �� ����� ������ �� �������� �������
						if (help->position == hash1 && help->patient == NULL)
						{
							help->patient = bolnoy;
							if (help->metka == "del")
								help->metka = "";
							return;
						}
						// ���� ��� ������ � �� ����� ������ �������� �������
						else if (help->position == hash1 && help->patient != NULL)
						{
							help->collision++;
							break;
						}
						help = help->next;
					}
				}
				return;
			}
			help = help->next;
		}
}

// ����� �������
void show_patient(Hash*& start_ht, Hash*& end_ht)
{
	Hash* help = start_ht;
	int count = 0; // ��� �������� ������� ������� � ������
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		if (start_ht->next == NULL)
		{
			cout << "������� ���\n";
			cout << "================================" << endl;
			system("pause");
			return;
		}
		if (help->patient != NULL)
		{
			count++;
			cout << "��� ��������: " << help->patient->all_name << endl;
			cout << "��������������� �����: " << help->patient->regist_number << endl;
			cout << "��� ��������: " << help->patient->year_of_birth << endl;
			cout << "�����: " << help->patient->address << endl;
			cout << "����� ������ (�����): " << help->patient->place_of_work << endl;
			cout << "position number: " << help->position << endl;
			cout << "================================" << endl;
		}
		help = help->next;
	}
	if (!count)
	{
		cout << "������� ���\n";
		cout << "================================" << endl;
	}
	system("pause");
}

//����� ����������� � ���� ��������������� �������
void search_registr_in_data(Data*& head, Data*&tail, string registr)
{
	Data* help = head;
	if (help == 0)
	{
		return;
	}
	else
	{
		do
		{
			if (help->ticket->registr == registr)
			{
				cout << "======================================" << endl;
				cout << "����������� � " << help->ticket->fio_doctor << endl;
			}
			help = help->next;
		} while (help != head);
	}
}

//����� �������� �� ���������������� ������
void search_to_registr(Hash*& start_ht, Hash*& end_ht, Data*&head,Data*&tail)
{
	// ���� ���������� ������
	if (start_ht->next == NULL)
	{
		cout << "������ ���\n";
		cout << "======================================" << endl;
		system("pause");
		return;
	}
	int count_searching = 0; // ��� �������� �� ������� ����������
	int metka = 0;
	Hash* help = start_ht;
	string registr_in_function;
	cout << "������� ��������������� ����� �MM-NNNNNN�,��� MM � ����� �������(�����); NNNNNN � ���������� �����(�����): ";
	checkRegist(registr_in_function);
	cout << "================================" << endl;
	int hash1 = hash_position(registr_in_function);
	int hash2 = hash_position2(registr_in_function);
	for (int i = 0; i <= hash1; i++)
	{
		if (help->position == hash1 && help->patient != NULL && help->patient->regist_number == registr_in_function)
		{
			cout << "��� ��������: " << help->patient->all_name << endl;
			cout << "��������������� �����: " << help->patient->regist_number << endl;
			cout << "��� ��������: " << help->patient->year_of_birth << endl;
			cout << "�����: " << help->patient->address << endl;
			cout << "����� ������ (�����): " << help->patient->place_of_work << endl;
			search_registr_in_data(head, tail, help->patient->regist_number);
			cout << "================================" << endl;
			count_searching++;
			break;
		}
		else if (help->position == hash1 && (help->patient == NULL || help->patient != NULL && help->patient->regist_number != registr_in_function))
		{
			for (int j = 0;j<SIZE_TABLE*11; j++)
			{
				hash1 = (hash1 + j * hash2) % SIZE_TABLE; 
				help = start_ht; 
				for (int n = 0; n <= hash1; n++)
				{
					if (help->position == hash1 && help->patient != NULL && help->patient->regist_number == registr_in_function)
					{
						cout << "��� ��������: " << help->patient->all_name << endl;
						cout << "��������������� �����: " << help->patient->regist_number << endl;
						cout << "��� ��������: " << help->patient->year_of_birth << endl;
						cout << "�����: " << help->patient->address << endl;
						cout << "����� ������ (�����): " << help->patient->place_of_work << endl;
						search_registr_in_data(head, tail, help->patient->regist_number);
						cout << "================================" << endl;
						count_searching++;
					}
					else if (help->position == hash1 && help->metka == "del")
					{
						metka++;
					}
					help = help->next;

				}
				if (count_searching != 0||metka!=0)
					break;
			}
			break;
		}
		help=help->next;
	}
	if (count_searching == 0)
	{
		cout << "���������� ���\n";
		cout << "======================================" << endl;
	}
	system("pause");
}

// ����� �������� �� ���
void search_to_FUO_patient(Hash*& start_ht, Hash*& end_ht)
{
	if (start_ht->next == NULL)
	{
		cout << "������� ���\n";
		cout << "======================================" << endl;
		system("pause");
		return;
	}
	string name; // ������ ��� ���
	cout << "������� ��� ��������: ";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, name);
	name=check_fio(name);
	Hash* help = start_ht;
	int count = 0; // ��� �������� ������� �������� � ������
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		if (help->patient != NULL)
		{
			// ���� ��� ���������
			if (help->patient->all_name == name)
			{
				cout << "��� ��������: " << help->patient->regist_number << endl;
				cout << "��������������� �����: " << help->patient->all_name << endl;
				cout << "================================" << endl;
				count++;
			}
		}
		help = help->next;
	}
	if (!count)
	{
		cout << "�������� � ����� ��� ����\n";
		cout << "================================" << endl;
	}
	system("pause");
}

//����� ���������������� ������ � ������ ����������� ��� �������� ������ � �����
bool check_registr_in_data(Data*& head, Data*& tail, string registr)
{
	Data* help = head;
	if (help == 0)
	{
		return 0;
	}
	else
	{
		do
		{
			if (help->ticket->registr == registr)
				return 1;
			help = help->next;
		} while (help != head);
	}
	return 0;
}

// �������� ��������
void del_patient(Hash*& start_ht, Hash*& end_ht,Data*& head, Data*& tail)
{
	if (start_ht->next == NULL)
	{
		cout << "======================================" << endl;
		cout << "������� ���\n";
		cout << "======================================" << endl;
		system("pause");
		return;
	}
	string registr; // ��� ������ ���������������� �����
	cout << "������� ��������������� ����� �MM-NNNNNN�,��� MM � ����� �������(�����); NNNNNN � ���������� �����(�����): ";
	checkRegist(registr); // ������ ��������������� ����� ���������
	if (check_registr_in_data(head, tail, registr))
	{
		cout << "===========================================================" << endl;
		cout << "�������� �������� ����������, � ���� ���� ����������� � �����\n";
		cout << "===========================================================" << endl;
		system("pause");
		return;
	}
	Hash* help = start_ht;
	int count = 0; // ��� �������� ������� �������� � ������
	int hash1 = hash_position(registr);
	int hash2 = hash_position2(registr);
	for (int i = 0; i <= hash1; i++)
	{
		if (help->position == hash1 && help->patient != NULL && help->patient->regist_number == registr)
		{
			count++;
			delete help->patient;
			help->patient = nullptr;
			help->patient = NULL;
			help->collision = 0;
			help->metka = "del";
			cout << "======================================" << endl;
			cout << "������� �����\n";
			cout << "======================================" << endl;
			system("pause");
			return;
		}
		else if (help->position == hash1 && (help->patient == NULL || help->patient != NULL && help->patient->regist_number != registr))
		{
			for (int j = 0; j < SIZE_TABLE * 11; j++)
			{
				hash1 = (hash1 + j * hash2) % SIZE_TABLE;
				help = start_ht;
				for (int n = 0; n <= hash1; n++)
				{
					if (help->position == hash1 && help->patient != NULL && help->patient->regist_number == registr)
					{
						count++;
						delete help->patient;
						help->patient = nullptr;
						help->patient = NULL;
						help->collision = 0;
						help->metka = "del";
						cout << "======================================" << endl;
						cout << "������� �����\n";
						cout << "======================================" << endl;
						system("pause");
						return;
					}
					help = help->next;

				}
				if (count != 0)
					break;
			}
			break;
		}
		help = help->next;
	}
	if (count==0)
	{
		cout << "======================================" << endl;
		cout << "�������� � ����� ��������������� ������� ���\n";
		cout << "======================================" << endl;
	}
	system("pause");
}

// �������� ���� �������
void delete_all_patients(Hash*& start_ht, Hash*& end_ht, Data*&head)
{
	if (head != NULL)
	{
		cout << "������ ������� ���� �������, � ��� ���� ����������� � �����\n";
		cout << "======================================================" << endl;
		system("pause");
		return;
	}
	if (start_ht->next == NULL)
	{
		cout << "������� ���\n";
		cout << "======================================" << endl;
		system("pause");
		return;
	}
	Hash* help = start_ht;
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		// ���� � ������ �����
		if (help->patient == NULL)
		{
			help = help->next;
			continue;
		}
		// ���� � ������ �� �����
		if (help->patient != NULL)
		{
			delete help->patient;
			help->patient = nullptr;
		}
		help = help->next;
	}
	cout << "������� �������\n";
	cout << "======================================" << endl;
	system("pause");
}

// ������ ������ �� ����� � ������
void ReadHelp(Patient* bolnoy, Hash*& start_ht, Hash*& end_ht)
{
	if (isfull(start_ht) == 0)
	{
		cout << "Table is full" << endl;
		system("pause");
		return;
	}
	int hash1 = hash_position(bolnoy->regist_number);
	if (start_ht->next == NULL)
	{
		create_hash_table(start_ht, end_ht); // ������ �������
		Hash* help = start_ht;
		// �������� � ������� ��������
		for (int i = 0; i <= hash1; i++)
		{
			if (help->position == hash1)
			{
				// �������� � ������� � ������� �� �������
				help->patient = bolnoy;
				return;
			}
			help = help->next;
		}
	}
		// ������ ��������������� ���������� ��� �������� �� �������
		Hash* help = start_ht;
		// ���� ����� � ������� � ������������ ��������
		for (int i = 0; i <= (hash1 + 1); i++)
		{
			// ���� ��� ������ � �� ����� ������ �� �������� �������
			if (help->position == hash1 && help->patient == NULL)
			{
				help->patient = bolnoy;
				if (help->metka == "del")
					help->metka = "";
				return;
			}
			// ����� ���� ��� ������ � �� ����� ������ �������� �������
			else if (help->position == hash1 && help->patient != NULL)
			{
				help->collision++; // ��������� ��������
				int hash2 = hash_position2(bolnoy->regist_number);
				for (int j = 0;; j++)
				{
					hash1 = (hash1 + j * hash2) % SIZE_TABLE; // ������� �����������
					help = start_ht; // ������ ���������� ��� ��������� ��������
					for (int n = 0; n <= (hash1 + 1); n++)
					{
						// ���� ��� ������ � �� ����� ������ �� �������� �������
						if (help->position == hash1 && help->patient == NULL)
						{
							help->patient = bolnoy;
							if (help->metka == "del")
								help->metka = "";
							return;
						}
						// ���� ��� ������ � �� ����� ������ �������� �������
						else if (help->position == hash1 && help->patient != NULL)
						{
							help->collision++;
							break;
						}
						help = help->next;
					}
				}
				return;
			}
			help = help->next;
		}
}

// ������ �� �����
void Read(Hash*& Start, Hash*& End, int &n)
{
	Hash* st = Start;
	ifstream read_file("patient.txt");
	string str, fio, work, year, registr, adress;
	char txt[10050];
	int x;
	if (!read_file.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else {
		do {
			Patient* patient = new Patient;
			read_file.getline(txt, 1050);
			for (int i = 0; i < 1050; i++)
			{
				str += txt[i];
			}
			x = 0;
			while (str[x] != '|')
			{
				registr += str[x];
				x++;
				patient->regist_number = registr;
			}
			x++;
			while (str[x] != '|')
			{
				fio += str[x];
				x++;
				patient->all_name=fio;
			}
			x++;
			while (str[x] != '|')
			{
				year += str[x];
				x++;
				patient->year_of_birth = atoi(year.c_str());
			}
			x++;
			while (str[x] != '|')
			{
				adress += str[x];
				x++;
				patient->address = adress;
			}
			x++;
			while (str[x] != ';')
			{
				work += str[x];
				x++;
				patient->place_of_work = work;
			}
			x++;
			ReadHelp(patient,Start, End);
			str.clear();
			fio.clear();
			registr.clear();
			year.clear();
			adress.clear();
			work.clear();
			n++;
		} while (!read_file.eof());
		read_file.close();
	}
}

// ������ � ����
void Record(Hash*& Start)
{
	cout << "��� ������� ������������ ���� ������. ������ ����������?\n1.��\n2.���" << endl;
	int choce;
	cin >> choce;
	switch (choce) {
	case 1: {
		Hash* st = Start;
		ofstream record_file;
		record_file.open("patient.txt", ios_base::trunc);
		if (!record_file.is_open()) // ���� ���� �� ������
			cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
		else {
			for (int i=0; i < SIZE_TABLE; i++)
			{
				if (st->patient == NULL)
				{
					st = st->next; continue;
				}
				else
				{
					record_file << st->patient->regist_number << "|" << st->patient->all_name << "|" << st->patient->year_of_birth
						<< "|" << st->patient->address << "|" << st->patient->place_of_work << ";";
					Hash* help = st->next;
					for (int j = st->position; j < SIZE_TABLE; j++)
					{
						if (help->patient != NULL)
						{
							record_file << endl; break;
						}
						help = help->next;
					}
				}
				st = st->next;
			}
			cout << endl << "������� ���������" << endl << endl;
			break;
		}

		record_file.close();
	}
	case 2:
	{
		break;
	}
	}

}

//��� �������� ������
int height(Three*& element)
{
	if (element == NULL)
	{
		return -1;
	}
	else
	{
		return element->height;
	}
}

//����� ����� �������
Three* single_left_rotate(Three*& element)
{
	Three* help = element->right;
	element->right = help->left;
	help->left = element;
	element->height = max(height(element->left), height(element->right)) + 1;
	help->height = max(height(element->left), element->height) + 1;
	return help;
}

//����� ������ �������
Three* single_right_rotate(Three*& element)
{
	Three* help = element->left;
	element->left = help->right;
	help->right = element;
	element->height = max(height(element->left), height(element->right)) + 1;
	help->height = max(height(help->left), element->height) + 1;
	return help;
}

//������� ����� �������
Three* big_left_rotate(Three*& element)
{
	element->right = single_right_rotate(element->right);
	return single_left_rotate(element);
}

//������� ������ �������
Three* big_right_rotate(Three*& element)
{
	element->left = single_left_rotate(element->left);
	return single_right_rotate(element);
}

//�������� ��������� ���
string check_fio_doctor()
{
	string z;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, z);
	int check = 0;
	int kolvo = 0;
	for (int i = 0; i < z.length(); i++) {
		if (int('�') <= int(z[i]) && int(z[i]) <= int('�') || int('�') <= int(z[i]) && int(z[i]) <= int('�') ||int(z[i]) == int('�') ||int(z[i]) == int('�') ||int(z[i])==int('.')|| int(z[i]) == 32)
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
		{
			check = 0; break;
		}
		if (int(z[z.length() - 1] != int('.')) && int(z[z.length() - 3] != int('.')))
		{
			check = 0; break;
		}
		if (int(z[i]) == 32 && !(int('�') <= int(z[i + 1]) && int(z[i + 1]) <= int('�') ||
			int(z[i]) == int('.') && !(int('�') <= int(z[i + 1]) && int(z[i + 1]) <= int('�') || int(z[i]) == int('�')) || (!(int('�') <= int(z[0]) && int(z[0]) <= int('�') || int(z[i]) == int('�')))))
			check = 0;
	}

	while ((cin.fail()) || check == 0 || z.length()==26)
	{
		kolvo = 0;
		cout << "������������ ����!. ���������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		for (int i = 0; i < z.length(); i++) {
			if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||int('�') <= int(z[i]) && int(z[i]) <= int('�') ||int(z[i]) == int('�') ||int(z[i]) == int('�') ||int(z[i]) == int ('.')|| int(z[i]) == 32)
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length(); i++) {
			if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
			{
				check = 0; break;
			}
			if (int(z[z.length() - 1] != int('.')) && int(z[z.length() - 3] != int('.')))
			{
				check = 0; break;
			}
			if (int(z[i]) == 32 && !(int('�') <= int(z[i + 1]) && int(z[i + 1]) <= int('�') ||
				int(z[i]) == int('.') && !(int('�') <= int(z[i + 1]) && int(z[i + 1]) <= int('�') || int(z[i]) == int('�')) || (!(int('�') <= int(z[0]) && int(z[0]) <= int('�') || int(z[i]) == int('�')))))
			{
				check = 0; break;
			}
		}
	}
	return z;
}

//�������� �� ���� ���������
string check_position()
{
	string z;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, z);
	int check = 0;
	for (int i = 0; i < z.length(); i++) {
		if (int('�') <= int(z[i]) && int(z[i]) <= int('�') || int('�') <= int(z[i]) && int(z[i]) <= int('�') || int(z[i]) == int('�') || int(z[i]) == int('�') || int(z[i]) == 32)
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0'))
		{
			check = 0; break;
		}
		else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[z.length() - 1] == 32)) || int(z[0]) == int('\0') || int(z[0]) == int(' '))
		{
			check = 0; break;
		}
	}

	while ((cin.fail()) || check == 0)
	{
		cout << "������������ ����!. ���������: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		for (int i = 0; i < z.length(); i++) {
			if (int('�') <= int(z[i]) && int(z[i]) <= int('�') ||int('�') <= int(z[i]) && int(z[i]) <= int('�') ||int(z[i]) == int('�') ||int(z[i]) == int('�') || int(z[i]) == 32)
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length(); i++) {
			if (int(z[0]) == int('\0'))
			{
				check = 0; break;
			}
			else if (int(z[i]) == 32 && int(z[i + 1]) == 32 || (int(z[z.length() - 1] == 32)) || int(z[0]) == int('\0') || int(z[0]) == int(' '))
			{
				check = 0; break;
			}
		}
	}
	return z;
}

//�������� �� ���� ��������
int check_cabinet()
{
	int m;
	cin >> m;
	while ((cin.fail()) || (cin.get() != '\n') || m<=0)
	{
		cout << "������� ��������: ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> m;
	}
	return m;
}

//�������� �� ���������� ������� 
string check_time()
{
	string z;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, z);
	int check = 0, time10, time20;
	string time1, time2;
	for (int i = 0; i < z.length(); i++) {
		if (int('0') <= int(z[i]) && int(z[i]) <= int('9') || int(z[i]) == int(':')||int(z[i]) == int('-'))
			check = 1;
		else {
			check = 0; break;
		}
		if (i < 2)
		{
			time1 += z[i];
		}
		if (i > 5 && i < 8)
			time2 += z[i];
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
		{
			check = 0; break;
		}
		if (int (z[2])!=int(':') || int(z[8]) != int(':') || int(z[5]) != int('-') || int('3') <= int(z[0]) && int(z[0]) <= int('9')
			|| int('2') == int(z[0]) && int(z[1]) >= int('1')||int('3') <= int(z[6]) && int(z[6]) <= int('9')
			|| int('2') == int(z[6]) && int(z[7]) >= int('1'))
		{
			check = 0; break;
		}
	}
	time10 = stoi(time1);
	time20 = stoi(time2);
	if (time10 > time20)
		check = 0;

	while ((cin.fail()) || check == 0)
	{
		cout << "������������ ����!. ���������: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		time1.clear();
		time2.clear();
		for (int i = 0; i < z.length(); i++) {
			if (int('0') <= int(z[i]) && int(z[i]) <= int('9') || int(z[i]) == int(':') || int(z[i]) == int('-'))
				check = 1;
			else {
				check = 0; break;
			}
			if (i < 2)
			{
				time1 += z[i];
			}
			if (i > 5 && i < 8)
				time2 += z[i];
		}
		for (int i = 0; i < z.length() + 1; i++) {
			if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
			{
				check = 0; break;
			}
			if (int(z[2]) != int(':') || int(z[8]) != int(':') || int(z[5]) != int('-'))
			{
				check = 0; break;
			}
			if (int(z[2]) != int(':') || int(z[8]) != int(':') || int(z[5]) != int('-') || int('3') <= int(z[0]) && int(z[0]) <= int('9')
				|| int('2') == int(z[0]) && int(z[1]) >= int('1') || int('3') <= int(z[6]) && int(z[6]) <= int('9')
				|| int('2') == int(z[6]) && int(z[7]) >= int('1'))
			{
				check = 0; break;
			}
		}
		time10 = stoi(time1);
		time20 = stoi(time2);
		if (time10 > time20)
			check = 0;
	}
	return z;
}

// ���������� ��������� � ������
void add_doctor(Three*& element, string value)
{
	if (element == NULL)
	{
		Doctor* r = new Doctor;
		r->fio_doctor = value;
		cout << "������� ���������: ";
		r->position = check_position();
		cout << "������� ����� ��������: ";
		r->number_cabinet= check_cabinet();
		cout << "������� ������ ������:";
		r->time = check_time();
		element = new Three;
		element->height = 0;
		element->doctor = r;
	}
	else
	{
		if (value < element->doctor->fio_doctor)
		{
			add_doctor(element->left, value);
			//���� ��������� ���������������
			if (height(element->left) - height(element->right) == 2)
			{
				if (value < element->left->doctor->fio_doctor)
				{
					element = single_right_rotate(element);
				}
				else
				{
					element = big_right_rotate(element);
				}
			}
		}
		else if (value > element->doctor->fio_doctor)
		{
			add_doctor(element->right, value);
			if (height(element->right) - height(element->left) == 2)
			{
				if (value > element->right->doctor->fio_doctor)
				{
					element = single_left_rotate(element);
				}
				else
				{
					element = big_left_rotate(element);
				}
			}
		}
	}
	element->height = max(height(element->left), height(element->right)) + 1;
}

// ����� ������
void show_doctors(const Three* element)
{
	if (element == NULL)
	{
		return;
	}
	show_doctors(element->left); // ������ ����� ��������� 
	cout << "��� �����: " << element->doctor->fio_doctor << endl;
	cout << "���������: " << element->doctor->position << endl;
	cout << "����� ��������: " << element->doctor->number_cabinet << endl;
	cout << "������ ������: " << element->doctor->time << endl;
	cout << "====================================\n";
	show_doctors(element->right); // ������ ������ ���������   
}

// �������� ������������ ��������
Doctor* deletemin(Three*& element)
{
	Doctor* a;
	if (element->left == NULL)
	{
		a = element->doctor;
		element = element->right;
		return a;
	}
	else
	{
		a = deletemin(element->left);
		return a;
	}
}

//���� �� �������� ����������� � ����� �����
bool check_fio_in_data(Data*& head, Data*& tail, string fio)
{
	Data* help = head;
	if (help == 0)
	{
		return 0;
	}
	else
	{
		do
		{
			if (help->ticket->fio_doctor == fio)
				return 1;
			help = help->next;
		} while (help != head);
	}
	return 0;
}

// �������� �������� �� ������
void del_doctor(Three*& element, string value, Data*& head, Data*& tail)
{
	if (check_fio_in_data(head, tail, value))
	{
		cout << "�������� ����� ����������, � ���� ���� �����������\n";
		cout << "===========================================================" << endl;
		return;
	}
	Three* d;
	if (element == NULL)
	{
		cout << "������ ����� ���" << endl;
		cout << "======================================" << endl;
	}
	else if (value < element->doctor->fio_doctor)
	{
		del_doctor(element->left, value, head, tail);
	}
	else if (value > element->doctor->fio_doctor)
	{
		del_doctor(element->right, value, head, tail);
	}
	else if ((element->left == NULL) && (element->right == NULL))
	{
		d = element;
		free(element->doctor);
		element->doctor = nullptr;
		free(d);
		d = nullptr;
		element = nullptr;
		cout << "���� ������" << endl;
		cout << "======================================" << endl;
	}
	else if (element->left == NULL)
	{
		Three* help = element->right;
		d = element;
		delete element->doctor;
		element->doctor = nullptr;
		delete d;
		d = nullptr;
		element = help;
		cout << "���� ������" << endl;
		cout << "======================================" << endl;
	}
	else if (element->right == NULL)
	{
		d = element;
		element = element->left;
		free(element->doctor);
		element->doctor = nullptr;
		free(d);
		d = nullptr;
		cout << "���� ������" << endl;
		cout << "======================================" << endl;
	}
	else
	{
		free(element->doctor);
		element->doctor = nullptr;
		element->doctor = deletemin(element->right);
		cout << "���� ������" << endl;
		cout << "======================================" << endl;
	}
}

//����� �������� ����������� � ����� �����
void search_fio_in_data(Data*& head, Data*& tail, string fio)
{
	Data* help = head;
	if (help == 0)
	{
		return;
	}
	else
	{
		do
		{
			if (help->ticket->fio_doctor == fio)
			{
				cout << "�������: " << help->ticket->registr << endl;
				cout << "======================================" << endl;
			}
			help = help->next;
		} while (help != head);
	}
}

// ����� ����� �� ���
void search_doctor(const Three* element, string fio, Data*& head, Data*& tail)
{
	if (element == NULL)
	{
		return;
	}
	search_doctor(element->left, fio, head, tail); // ������ ����� ��������� 
	if (element->doctor->fio_doctor == fio)
	{
		cout << "��� �����: " << element->doctor->fio_doctor << endl;
		cout << "���������: " << element->doctor->position << endl;
		cout << "����� ��������: " << element->doctor->number_cabinet << endl;
		cout << "������ ������: " << element->doctor->time << endl;
		cout << "====================================\n";
		search_fio_in_data(head, tail, fio);
	}
	search_doctor(element->right,fio, head, tail); // ������ ������ ���������   
}

// �������� ���� ������
void delete_all_doctors(Three*& element, Data*& head)
{
	if (head != NULL)
	{
			cout << "�������� ������ ����������, � ��� ���� �����������\n";
			cout << "===========================================================" << endl;
			return;
	}
	if (element == NULL)
	{
		return;
	}
	delete_all_doctors(element->left, head); // ������ ����� ��������� 
	delete_all_doctors(element->right, head); // ������ ������ ���������  
	delete element->doctor;
	element->doctor = nullptr;
	delete element;
	element = nullptr;
}

//�������� ������
bool straigth_search(string str, string substr)
{
	int length_sub = substr.length(); // ����� ���������
	int length_str = str.length(); // ����� ������
	int check = 0;
	if (length_str == 0 || length_sub == 0 || length_sub == 1 || length_str == 1)
	{
		return false;
	}
	else
	{
		for (int i = 0; i <= length_str - length_sub; i++)
		{
			for (int j = 0; j < length_sub; j++)
				if (int(str[j + i]) != int(substr[j]))
					break;
				else if (j == length_sub - 1)
					return true;

		}
	}
	return false;
}

// ����� �� ���������
void position_search(const Three* element, string pos)
{
	if (element == NULL)
	{
		return;
	}
	position_search(element->left, pos); // ������ ����� ��������� 
	if (straigth_search(element->doctor->position, pos))
	{
		cout << "��� �����: " << element->doctor->fio_doctor << endl;
		cout << "���������: " << element->doctor->position << endl;
		cout << "����� ��������: " << element->doctor->number_cabinet << endl;
		cout << "����� ������: " << element->doctor->time << endl;
		cout << "====================================\n";
	}
	position_search(element->right, pos); // ������ ������ ���������
}

//������ ������ �� �����
void ReadHelp1(Doctor* doctor, Three*& element, string value)
{
	if (element == NULL)
	{
		element = new Three;
		element->height = 0;
		element->doctor = doctor;
	}
	else
	{
		if (value < element->doctor->fio_doctor)
		{
			ReadHelp1(doctor, element->left, value);
			//���� ��������� ���������������
			if (height(element->left) - height(element->right) == 2)
			{
				if (value < element->left->doctor->fio_doctor)
				{
					element = single_right_rotate(element);
				}
				else
				{
					element = big_right_rotate(element);
				}
			}
		}
		else if (value > element->doctor->fio_doctor)
		{
			ReadHelp1(doctor, element->right, value);
			if (height(element->right) - height(element->left) == 2)
			{
				if (value > element->right->doctor->fio_doctor)
				{
					element = single_left_rotate(element);
				}
				else
				{
					element = big_left_rotate(element);
				}
			}
		}
	}
	element->height = max(height(element->left), height(element->right)) + 1;
}

// ������ �� �����
void Read1(Three*& Start)
{
	ifstream read_file("doctors.txt");
	string str, fio, cabinet, time, pos;
	char txt[1050];
	int x;
	if (!read_file.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else {
		do {
			Doctor* doctor = new Doctor;
			if (!read_file.getline(txt, 1050))
				break;
			for (int i = 0; i < 1050; i++)
			{
				str += txt[i];
			}
			x = 0;
			while (str[x] != '|')
			{
				fio += str[x];
				x++;
				doctor->fio_doctor = fio;
			}
			x++;
			while (str[x] != '|')
			{
				pos += str[x];
				x++;
				doctor->position = pos;
			}
			x++;
			while (str[x] != '|')
			{
				cabinet += str[x];
				x++;
				doctor->number_cabinet = atoi(cabinet.c_str());
			}
			x++;
			while (str[x] != ';')
			{
				time += str[x];
				x++;
				doctor->time = time;
			}
			x++;
			ReadHelp1(doctor, Start, doctor->fio_doctor);
			str.clear();
			fio.clear();
			cabinet.clear();
			pos.clear();
			time.clear();
		} while (!read_file.eof());
		read_file.close();
	}
}

// ������ � ����
void Record1(Three* element)
{
		ofstream record_file;
		record_file.open("doctors.txt", ios::in | ios::app);
		if (!record_file.is_open()) // ���� ���� �� ������
			cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
		else {
			if (element == NULL)
			{
				return;
			}
			Record1(element->left); // ������ ����� ��������� 
			record_file << element->doctor->fio_doctor << "|"<< element->doctor->position  << "|" << element->doctor->number_cabinet <<"|" << element->doctor->time << ";";
			Record1(element->right); // ������ ������ ��������� 
		}
		record_file << endl;
		record_file.close();
}

//���������� �� ����� ��������������� ����� � ���� ���������
bool search_data(Hash*& start_ht, Hash*& end_ht, string registr)
{
	Hash* help = start_ht;
	cout << "================================" << endl;
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		// ���� ���-������� ������
		if (start_ht->next == NULL)
		{
			return false;
		}
		// ���� � ������ ������ ����, ��������� � ���������
		if (help->patient == NULL)
		{
			help = help->next;
			continue;
		}
		// ���� � ������ ���-�� ����
		if (help->patient != NULL)
		{
			if (help->patient->regist_number == registr)
			{
				return true;
			}
		}
		help = help->next;
	}
	return false;
}

//���������� �� ����� ������
Doctor* search_doc(const Three* element, string fio)
{
	if (element == NULL)
	{
		return 0;
	}
	search_doc(element->left, fio); // ������ ����� ��������� 
	if (element->doctor->fio_doctor == fio)
	{
		return element->doctor;
	}
	search_doc(element->right, fio); // ������ ������ ���������   
}

//�������� �� ������ � ���� � �� �� ����� � ������ � ���� �� �����
bool searchtime(Ticket*& data, Data*& head,string time)
{
	Data* help = head;
	if (head == NULL)
		return 1;
	else {
		do
		{
			if (data->registr == help->ticket->registr && data->date == help->ticket->date && time == help->ticket->time && data->fio_doctor == help->ticket->fio_doctor)
			{
				return 0;
				break;
			}
			if (data->date == help->ticket->date && time == help->ticket->time && data->fio_doctor == help->ticket->fio_doctor)
			{
				return 0;
				break;
			}
			if (data->date == help->ticket->date && time == help->ticket->time && data->registr == help->ticket->registr)
			{
				return 0;
				break;
			}
			help = help->next;
		} while (help != head);
		return 1;
	}
}

//���������� ��������
Data* merge(Data* a, Data* f, int m, int rem)
{
	if (!a) return f;
	if (!f) return a;
	Data* c = 0;
		if (a->ticket->fio_doctor < f->ticket->fio_doctor) {
			c = a;
			c->next = merge(a->next, f, m, rem);
		}
		else {
			c = f;
			c->next = merge(a, f->next, m, rem);
		}
	return c;
}

Data* sort(Data* head, Data* tail, int l)
{
	if (head == 0 || head->next == 0)
		return head;
	int m = (l) / 2;
	int rem = l - m;
	int k = 0;
	Data* help = head->prev;
	Data* a = head, * f = head->next;
	while ((f != 0) && (f->next != 0))
	{
		head = head->next;
		f = f->next->next;
	}
	f = head->next;
	head->next = NULL;
	return merge(sort(a, help, m), sort(f, tail, rem), m, rem);
}

//�������� �� ���� ����
bool Date(string a)//�������� �� ������������ ����� ���� ������
{
	bool bolt = false;
	string day = " ", month = " " , year = " ";
	int day1, month1, year1;
	if (a.length() != 10)
		bolt = true;//�����
	else
	{
		if (a[2] != 46 || a[5] != 46)
			bolt = true;//�����
		else
			for (int i = 0; i < 10; i++)
			{
				if (i != 2 && i != 5)
					if (a[i] < 48 || a[i]>57) {
						bolt = true;
						return bolt;
					}//�����, �����������������
			}
		day.append (a,0,2);
		month.append(a,3,2);
		year.append(a,6,4);
		day1 = stoi(day);
		month1 = stoi(month);
		year1 = stoi(year);
		if ((month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12) && day1 > 31)
			bolt = true;
		else if (month1 == 2 && day1 > 29)
			bolt = true;//�������
		else if ((day1 > 30) && (month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11))
			bolt = true;
		else if (year1 < 2022 || month1 < 5 && year1 == 2022 || year1 > 2022)
			bolt = true;
	}
	return bolt;
}

//�������� �� ���� �������
string time1()
{
	string z;
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, z);
	int check = 0, time10, time20;
	string time1, time2;
	for (int i = 0; i < z.length(); i++) {
		if (int('0') <= int(z[i]) && int(z[i]) <= int('9') || int(z[i]) == int(':'))
			check = 1;
		else {
			check = 0; break;
		}
	}
	for (int i = 0; i < z.length() + 1; i++) {
		if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
		{
			check = 0; break;
		}
		if (int(z[2]) != int(':') || int('3') <= int(z[0]) && int(z[0]) <= int('9')
			|| int('2') == int(z[0]) && int(z[1]) >= int('1')|| int('0') == int(z[0]) && int(z[1]) <= int('9'))
		{
			check = 0; break;
		}
	}

	while ((cin.fail()) || check == 0)
	{
		cout << "������������ ����!. ���������: " << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, z);
		time1.clear();
		time2.clear();
		for (int i = 0; i < z.length(); i++) {
			if (int('0') <= int(z[i]) && int(z[i]) <= int('9') || int(z[i]) == int(':'))
				check = 1;
			else {
				check = 0; break;
			}
		}
		for (int i = 0; i < z.length() + 1; i++) {
			if (int(z[0]) == int('\0') || int(z[0]) == int(' '))
			{
				check = 0; break;
			}
			if (int(z[2]) != int(':'))
			{
				check = 0; break;
			}
			if (int(z[2]) != int(':') || int('3') <= int(z[0]) && int(z[0]) <= int('9')
				|| int('2') == int(z[0]) && int(z[1]) >= int('1')||int('0') == int(z[0]) && int(z[1]) <= int('9'))
			{
				check = 0; break;
			}
		}
	}
	return z;
}

//���������� ����������� � ������
void Insert(Data*& head, Data*& tail, Hash*& start_ht, Hash*& end_ht, Three*& element)
{
	Ticket* data2 = new Ticket;
	string registr;
	cout << "������� ��������������� �����\n";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, registr);
	data2->registr = registr;
	if (search_data(start_ht, end_ht, registr))
	{
		s++;
		cout << "������� ��� �������\n";
		string fio;
		fio = check_fio_doctor();
		while (!search_doc(element, fio))
		{
			cout << "�������� � ����� �����������." << endl;
			cout << "������� ��� ������� ��������\n";
			fio = check_fio_doctor();
		}
		data2->fio_doctor = fio;
		string date1;
		cout << "������� ���� ������ �������(������: 03.06.2022): ";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, date1);
		while (Date(date1))
		{
			cin.sync();
			if (Date(date1))
			{
				cout << "������������ ����, ������� ���� ������: ";
				getline(cin, date1);
			}
		}
		data2->date = date1;
		cout << "������� ����� ������\n";
		string time;
		time = time1();
		Data* st = head;
		while (!searchtime(data2, st,time))
		{
			cout << "������ �� ��� ����� ������. ������� ������ �����" << endl;
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			getline(cin, time);
		}
		data2->time = time;
		Data* help = new Data;
		help->ticket = data2;
		if (head == NULL)
		{
			head = help; // ���������� ��������� ������� �������� �� ����� �������
			tail = help; // ���������� ��������� �������� �������� �� ����� �������
			tail->next = head; // ���������� ��������� ���������� �������� �� ����� �������
			tail->prev = help; // ���������� ��������� ����������� �������� �� ����� �������
			head->prev = tail;  // �������������� ���������� ������������ �� �������
		}
		else
		{
			help->next = tail->next; // �������������� ��������� ���������� �������� � �����������
			help->next->prev = help;	// �������������� ��������� ���������� �������� �� �����������
			tail->next = help;  // �������������� ��������� ��������� �� �����������
			help->prev = tail;  // �������������� ���������� ������������ �� �������
			tail = help;
			if (s > 1)
			{
				Data* st = head;
				st->prev = NULL;
				tail->next = NULL;
				head = sort(st, tail, s);
				Data* help = head;
				while (help->next != 0)
				{
					tail = help->next;
					tail->prev = help;
					help = help->next;
				}
				head->prev = tail;
				tail->next = head;
			}
		}
	}
	else
	{
		cout << "������� ���������������� ������ ��� � ����\n";
		cout << "======================================================" << endl;
		return;
	}
}

//�������� �����������
void Delete(Data*& head, Data*& tail, Hash*& start_ht, Hash*& end_ht, Three*& element)
{
	Ticket* data2 = new Ticket;
	string registr;
	cout << "������� ��������������� �����\n";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, registr);
	data2->registr = registr;
	if (search_data(start_ht, end_ht, registr))
	{
		cout << "������� ��� �������\n";
		string fio;
		fio = check_fio_doctor();
		while (!search_doc(element, fio))
		{
			cout << "�������� � ����� �����������." << endl;
			cout << "������� ��� ������� ��������\n";
			fio = check_fio_doctor();
		}
		data2->fio_doctor = fio;
		cout << "������� ���� ������\n";
		string date;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, date);
		data2->date = date;
		cout << "������� ����� ������\n";
		string time;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, time);
		Data* help = head;
		if (searchtime(data2, help, time))
		{
			cout << "������ ��� � ����\n";
			cout << "======================================================" << endl;
			return;
		}
		else
		{
			s--;
			data2->time = time;
			Data* help = head;
			// ���� ����� 1 �������
			if (head == tail)
			{
				delete head;
				head = nullptr;
				tail = nullptr;
				cout << "����������� ����������\n";
				cout << "======================================================" << endl;
				return;
			}
			// ���� ������� ������� ������-�� �� ������
			else
			{
				// �����, ���� �� �������� ��������� ��������� ���������
				do
				{
					if (data2->registr == help->ticket->registr && data2->date == help->ticket->date && time == help->ticket->time && data2->fio_doctor == help->ticket->fio_doctor)
					{
						help->prev->next = help->next; // ������������ ���������
						help->next->prev = help->prev; // ������������ ���������
						delete help;
						help = nullptr;
						break;
					}
					help = help->next;
				} while (help != head);
				cout << "����������� ����������\n";
				cout << "======================================================" << endl;
				return;
			}
		}
	}
	else
	{
		cout << "������� ���������������� ������ ��� � ����\n";
		cout << "======================================================" << endl;
		return;
	}
}

//�������� ���� �����������
void show(Data*& head, Data*& tail)
{
	Data* help = head;
	if (head == NULL)
	{
		cout << "������� ���.\n";
		return;
	}
	do
	{
		cout << "��������������� �����: " << help->ticket->registr << endl;
		cout << "��� �����: "<< help->ticket->fio_doctor << endl;
		cout <<"���� ������: "<< help->ticket->date << endl;
		cout <<"����� ������: "<< help->ticket->time << endl;
		cout << "====================================\n";
		help = help->next;
	} while (help != head);
}

// ������ ������ �� ����� � ������
void ReadHelp2(Ticket*ticket, Data*& head, Data*& tail)
{
	Data* help = new Data;
	help->ticket = ticket;
	if (head == 0)
	{
		head = help; 
		tail = help; 
		tail->next = head;
		tail->prev = help;
		head->prev = tail;
		return;
	}
	else
	{
		help->next = tail->next;
		help->next->prev = help;	
		tail->next = help; 
		help->prev = tail; 
		tail = help;
		if (s > 1)
		{
			Data* st = head;
			st->prev = NULL;
			tail->next = NULL;
			head = sort(st, tail, s);
			Data* help = head;
			while (help->next != 0)
			{
				tail = help->next;
				tail->prev = help;
				help = help->next;
			}
			head->prev = tail;
			tail->next = head;
		}

	}
}

// ������ �� �����
void Read2(Data*& Start, Data*& End)
{
	Data* st = Start;
	ifstream read_file("ticket.txt");
	string str, fio, date, time, registr;
	char txt[10050];
	int x;
	if (!read_file.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
	else {
		do {
			Ticket* ticket = new Ticket;
			read_file.getline(txt, 1050);
			for (int i = 0; i < 1050; i++)
			{
				str += txt[i];
			}
			x = 0;
			while (str[x] != '|')
			{
				registr += str[x];
				x++;
				ticket->registr = registr;
			}
			x++;
			while (str[x] != '|')
			{
				fio += str[x];
				x++;
				ticket->fio_doctor = fio;
			}
			x++;
			while (str[x] != '|')
			{
				date += str[x];
				x++;
				ticket->date=date;
			}
			x++;
			while (str[x] != ';')
			{
				time += str[x];
				x++;
				ticket->time=time;
			}
			x++;
			s++;
			ReadHelp2(ticket, Start, End);
			str.clear();
			fio.clear();
			registr.clear();
			time.clear();
			date.clear();
		} while (!read_file.eof());
		read_file.close();
	}
}

// ������ � ����
void Record2(Data*& Start, Data*&tail)
{
	cout << "��� ������� ������������ ���� ������. ������ ����������?\n1.��\n2.���" << endl;
	int choce;
	cin >> choce;
	switch (choce) {
	case 1: {
		Data* st = Start;
		ofstream record_file;
		record_file.open("ticket.txt");
		if (!record_file.is_open()) // ���� ���� �� ������
			cout << "���� �� ����� ���� ������!\n"; // �������� �� ����
		else {
			while (st->next != Start)
			{
				record_file << st->ticket->registr << "|" << st->ticket->fio_doctor << "|" << st->ticket->date << "|" << st->ticket->time << ";" << endl;
				st = st->next;
			}
			record_file << st->ticket->registr << "|" << st->ticket->fio_doctor << "|" << st->ticket->date << "|" << st->ticket->time << ";";
			cout << endl << "������� ���������" << endl << endl;
			break;
		}
		record_file.close();
	}
	case 2:
	{
		break;
	}
	}

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	Hash* start_ht = new Hash; // ��������� �� ������ �������
	Hash* end_ht; // ��������� �� ����� �������
	Three* start = NULL; // ������ ��������� �� ������
	Data* head = NULL; // ��������� �� ������ ������
	Data* tail = NULL; // ��������� �� ����� ������*/
	while (true)
	{
		menu_main();
		int k;
		int num=1;
		check_menu(k);
		cout << k;
		switch (k)
		{
		case 1:
			while (true)
			{
				system("cls");
				menu_patients();
				int k1;
				check_menu1(k1);
				int l = 0;
				switch (k1)
				{
				case 1:
					system("cls");
					add_patient(start_ht, end_ht,num);
					Record(start_ht);
					show_patient(start_ht, end_ht);
					break;
				case 2:
					system("cls");
					del_patient(start_ht, end_ht,head, tail);
					Record(start_ht);
					break;
				case 3:
					system("cls");
					show_patient(start_ht, end_ht);
					break;
				case 4:
					system("cls");
					search_to_registr(start_ht, end_ht, head,tail);
					break;
				case 5:
					system("cls");
					search_to_FUO_patient(start_ht, end_ht);
					break;
				case 6:
					system("cls");
					delete_all_patients(start_ht, end_ht,head);
					Record(start_ht);
					num=1;
					break;
				case 7:
					system("cls");
					Read(start_ht, end_ht, num);
					show_patient(start_ht, end_ht);
					break;
				case 0:
					l++;
					break;
				}
				if (l == 1)
				{
					system("cls");
					break;
				}
			}
			break;
		case 2:
			while (true)
			{
				system("cls");
				menu_doctors();
				int k2;
				check_menu1(k2);
				int l = 0;
				switch (k2)
				{
				case 1:
				{
					system("cls");
					cout << "������� ��� �����: " << endl;
					string value = check_fio_doctor();
					add_doctor(start, value);
					cout << "��� ������� ������������ ���� ������. ������ ����������?\n1.��\n2.���" << endl;
					int choce;
					cin >> choce;
					switch (choce) {
					case 1: {
						ofstream ("doctors.txt");
						Record1(start); break; }
					case 2: {break; }
					}
					system("pause");
					break;
				}
				case 2:
				{
					system("cls");
					cout << "������� ��� �����: " << endl;
					string value = check_fio_doctor();
					del_doctor(start, value,head,tail);
					cout << "��� ������� ������������ ���� ������. ������ ����������?\n1.��\n2.���" << endl;
					int choce;
					cin >> choce;
					switch (choce) {
					case 1: {
						ofstream("doctors.txt");
						Record1(start); break; }
					case 2: {break; }
					}
					system("pause");
					break;
				}
				case 3:
					system("cls");
					show_doctors(start);
					system("pause");
					break;
				case 4:
				{
					system("cls");
					cout << "������� ��� �����: " << endl;
					string value=check_fio_doctor();
					search_doctor(start, value,head,tail);
					system("pause");
					break;
				}
				case 5:
				{
					system("cls");
					string value;
					cout << "������� ���������: ";
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					getline(cin, value);
					position_search(start, value);
					system("pause");
					break;
				}
				case 6:
					system("cls");
					delete_all_doctors(start,head);
					cout << "��� ������� ������������ ���� ������. ������ ����������?\n1.��\n2.���" << endl;
					int choce;
					cin >> choce;
					switch (choce) {
					case 1: {
						ofstream("doctors.txt");
						break; }
					case 2: {break; }
					}
					system("pause");
					break;
				case 7:
					system("cls");
					Read1(start);
					show_doctors(start);
					system("pause");
					break;
				case 0:
					l++;
					break;
				}
				if (l == 1)
				{
					system("cls");
					break;
				}
			}
			break;
		case 3:
			while (true)
			{
				system("cls");
				menu_issue_and_refund();
				int k3;
				check_menu2(k3);
				int l = 0;
				switch (k3)
				{
				case 1:
				{
					system("cls");
					Insert(head, tail, start_ht, end_ht, start);
					Record2(head, tail);
					show(head, tail);
					system("pause");
					break;
				}
				case 2:
					system("cls");
					Delete(head, tail, start_ht, end_ht, start);
					Record2(head, tail);
					show(head, tail);
					system("pause");
					break;
				case 3:
					system("cls");
					show(head, tail);
					system("pause");
				case 4:
					system("cls");
					Read2(head, tail);
					show(head, tail);
					system("pause");
					break; 
				case 0:
				{
					l++;
				break; }
				}
				if (l == 1)
				{
					system("cls");
					break;
				}
			}
			break;
		case 0:
			return 0;
		}
	}
}