#include "struktura.h"
#include "vector.h"

void irasimas(vector<studentas> &stud, std::size_t &ilgvardas, std::size_t &ilgpavarde)
{
	int b;
	std::string v, p, t, t1;
	std::cout << "iveskite varda: ";
	std::cin >> v;
	size_t i = 0;
	while (v != "0")
	{
		stud.push_back(studentas());
		stud[i].vardas(v);
		if (v.size() > ilgvardas)
		{
			ilgvardas = v.size();
		}
		std::cout << "iveskite pavarde: ";
		std::cin >> p;
		stud[i].pavarde(p);
		if (p.size() > ilgpavarde)
		{
			ilgpavarde = p.size();
		}
		std::cout << "Ar norite, kad studinio egzamino ir namų darbų rezultatai būtu generuojami atsitiktinai? \n";
		std::cout << "Jei ne rašykite 0, jei taip - 1 \n";
		std::cin >> t;

		while (t != "0" && t != "1")
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Įveskite skaičių 0 - duomenų įvedimui arba 1 - duomenų generavimui. \n";
			std::cin >> t;
		}

		if (t == "0")
		{
			std::cout << "iveskite egzamino rezultata: ";
			std::cin >> t1;
			stud[i].egzaminorez(tikrinimas(t1));
			std::cout << "iveskite namu darbu rezultatus: ";
			std::cin >> t1;
			b = tikrinimas(t1);
			while (b != 0)
			{
				stud[i].ndrez(b);
				std::cin >> t1;
				b = tikrinimas(t1);
			}
			i++;
			std::cout << "iveskite varda: ";
			std::cin >> v;
		}
		else if (t == "1")
		{
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(0, 10);
			stud[i].egzaminorez(uni(rng));
			std::cout << "egzamino rezultatas: " << stud[i].getEgzaminorez() << "\n";
			std::cout << "kiek namų darbų rezultatų sugeneruoti? \n";
			std::cin >> t1;
			while (!std::all_of(t1.begin(), t1.end(), ::isdigit) || std::stoi(t1) < 0 )
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Įveskite skaičių ne mazesni nei 0 \n";
				std::cin >> t1;
			}
			b = std::stoi(t1);
			std::cout << "namų darbų rezultatai yra: \n";
			int random_skaicius;
			for (int j = 0; j < b; j++)
			{
				random_skaicius = uni(rng);
				stud[i].ndrez(random_skaicius);
				std::cout << stud[i].getNdrez(j) << "\n";
			}
			i++;
			std::cout << "iveskite varda: ";
			std::cin >> v;
		}
	}
}

int tikrinimas(std::string a)
{
	while (!std::all_of(a.begin(), a.end(), ::isdigit) || std::stoi(a) < 0 || std::stoi(a) > 10)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Įveskite skaičių nuo 0 iki 10 \n";
		std::cin >> a;
	}
	return std::stoi(a);
}