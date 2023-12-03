#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Nomer { ONE, TWO };
string nomerStr[] = { "одномісний", "двомісний" };
struct Client
{
	string prizv;
	string inits;
	union {
		Nomer nomer;
		int n;
	};
	
	
};
void Create(Client* p, const int N);
void Print(Client* p, const int N);
void LineSearch(Client* p, const int N);
void SaveToFile(Client* p, const int N, const char* filename);
void LoadFromFile(Client*& p, int& N, const char* filename);
void AddClient(Client*& p, int& N);
void EditClient(Client* p, const int N);
void DeleteClient(Client*& p, int& N);
int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість клієнтів N: "; cin >> N;

	Client* p = new Client[N];
	double proc;
	int iposada;
	Nomer nomer;
	string prizv;
	int found;
	char filename[100];
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - пошук клієнта за прізвищем"<<endl;
		cout << " [4] - додання нового клієнта" << endl;
		cout << " [5] - редагування клієнта" << endl;
		cout << " [6] - видалення клієнта" << endl;
		cout << " [7] - запис даних у файл" << endl;
		cout << " [8] - зчитування даних із файлу" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			LineSearch(p, N);
			break;
		case 4:
			AddClient(p, N);
			break;
		case 5:
			EditClient(p, N);
			break;
		case 6:
			DeleteClient(p, N);
			break;
		case 7:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 8:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Client* p, const int N)
{
	int nomer;
	for (int i = 0; i < N; i++)
	{
		cout << "Клієнт № " << i + 1 << ":" << endl;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " ініціали.: "; cin >> p[i].inits;
		cout << " номер (0 - одномісний, 1 - двомісний, ): ";
		cin >> nomer;
		p[i].nomer = (Nomer)nomer;
		cout << " № номера в готелі: "; cin >> p[i].n;
		
		cout << endl;
	}
}
void Print(Client* p, const int N)
{
	cout << "========================================================================="
		<< endl;
	cout << "| № | Прізвище | Ініціали |   Тип Номера  | Номер |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << p[i].prizv
			<< "| " << setw(8) << right << p[i].inits << " "
			<< "| " << setw(13) << left << nomerStr[p[i].nomer] << " "
			<< "| " << setw(5) << right << p[i].n << " |";
		cout << "========================================================================="
			<< endl;
	}
	
	cout << endl;
}
void LineSearch(Client* p, const int N)
{
	string prizv, inits;
	cout << "Введіть прізвище клієнта:  " << endl;
	cin >> prizv;
	
	int k = 0, n = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].prizv == prizv)
		{
			n++;
			k = i;
		}
	}
	if (n > 1) {
		cout << "Введіть ініціали клієнта: ";
		cin >> inits;
		for (int i = 0; i < N; i++)
		{
			if (p[i].prizv == prizv && p[i].inits==inits)
			{
				cout << p[i].prizv << " " << p[i].inits << " " << nomerStr[p[i].nomer] <<" "<<p[i].n<< endl;
			}
		}
	}
	else if(n==1){
		cout << p[k].prizv << " " << p[k].inits << " " << nomerStr[p[k].nomer] << " " << p[k].n << endl;
	}
	else {
		cout << "Клієнта не знайдено" << endl;
	}

}


void SaveToFile(Client* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Client)); // записали елементи масиву
	fout.close(); // закрили файл
}
void LoadFromFile(Client*& p, int& N, const char* filename)
{
	delete[] p; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	p = new Client[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Client)); // прочитали елементи масиву
	fin.close();
}
	void AddClient(Client * &p, int& N)
	{
		N++;
		Client* newP = new Client[N];
		for (int i = 0; i < N - 1; i++)
		{
			newP[i] = p[i];
		}
		delete[] p;
		p = newP;
		cout << "Введіть дані для нового клієнта:" << endl;

		cout << "Прізвище: ";
		cin >> p[N - 1].prizv;

		cout << "Ініціали: ";
		cin >> p[N - 1].inits;

		cout << "Номер (0 - ONE, 1 - TWO): ";
		int nomer;
		cin >> nomer;
		p[N - 1].nomer = static_cast<Nomer>(nomer);

		// Ви можете продовжити зчитування інших полів за необхідності
	}

	void EditClient(Client* p, const int N)
	{
	
		string searchPrizv;
		cout << "Введіть прізвище клієнта, якого ви хочете редагувати: ";
		cin >> searchPrizv;

		int foundIndex = -1;

		for (int i = 0; i < N; i++)
		{
			if (p[i].prizv == searchPrizv)
			{
				foundIndex = i;
				break;
			}
		}

		if (foundIndex != -1)
		{
			cout << "Інформація про клієнта для редагування:" << endl;
			cout << "Прізвище: " << p[foundIndex].prizv << endl;
			cout << "Ініціали: " << p[foundIndex].inits << endl;
			cout << "Номер: " << nomerStr[p[foundIndex].nomer] << endl;

			cout << "Введіть нові дані для клієнта:" << endl;

			cout << "Нові ініціали: ";
			cin >> p[foundIndex].inits;

			cout << "Новий номер (0 - ONE, 1 - TWO): ";
			int nomer;
			cin >> nomer;
			p[foundIndex].nomer = static_cast<Nomer>(nomer);

			// Ви можете продовжити редагування інших полів за необхідності
		}
		else
		{
			cout << "Клієнта з прізвищем " << searchPrizv << " не знайдено." << endl;
		}
	}


	// Видалення клієнта
	void DeleteClient(Client*& p, int& N)
	{
	
		string searchPrizv;
		cout << "Введіть прізвище клієнта, якого ви хочете видалити: ";
		cin >> searchPrizv;

		int foundIndex = -1;

		for (int i = 0; i < N; i++)
		{
			if (p[i].prizv == searchPrizv)
			{
				foundIndex = i;
				break;
			}
		}

		if (foundIndex != -1)
		{
			cout << "Інформація про клієнта для видалення:" << endl;
			cout << "Прізвище: " << p[foundIndex].prizv << endl;
			cout << "Ініціали: " << p[foundIndex].inits << endl;
			cout << "Номер: " << nomerStr[p[foundIndex].nomer] << endl;

			cout << "Видалення клієнта..." << endl;

			N--;

			Client* newP = new Client[N];

			for (int i = 0, j = 0; i < N + 1; i++)
			{
				if (i != foundIndex)
				{
					newP[j++] = p[i];
				}
			}

			delete[] p;

			p = newP;
			cout << "Клієнт " << searchPrizv << " видалено." << endl;
		}
		else
		{
			cout << "Клієнта з прізвищем " << searchPrizv << " не знайдено." << endl;
		}
	}
