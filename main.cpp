#include "struktura.h"
#include "vector.h"

int main()
{
	auto pradzia = std::chrono::high_resolution_clock::now();
	vector<studentas> stud;
	std::string t;
	std::size_t ilgvardas = 10, ilgpavarde = 10;
	setlocale(LC_ALL, "Lithuanian");

	//*Failų generavimas*
	std::cout<<"Kiek failų norite sugeneruoti? (nuo 0 iki 5)\n";
	std::cin>>t;
	while (!std::all_of(t.begin(), t.end(), ::isdigit) || std::stoi(t) < 0 || std::stoi(t) > 5)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Įveskite skaičių nuo 0 iki 5 \n";
		std::cin >> t;
	}
	int failu_sk = std::stoi(t);
	//int failu_sk = 0;
	if(failu_sk != 0){
		failu_generavimas(failu_sk);
	}

	//*Duomenų įrašymas arba skaitymas iš failo*
	std::cout << "Ar norite duomenis ivesti ar nuskaityti nuo failo? \n";
	std::cout << "jei norite įvesti duomenis tada rašykite 0, jei skaityti - 1 \n";
	std::cin >> t;
	while (t != "0" && t != "1")
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Įveskite skaičių 0 - duomenų įvedimui arba 1 - duomenų nuskaitymui. \n";
		std::cin >> t;
	}
	//t = "1";
	if (t == "0")
	{
		irasimas(stud, ilgvardas, ilgpavarde);
	}
	else
	{
		std::string failo_pav;
		std::cout<<"Įveskite failo pavadinimą iš kurio norite nuskaityti duomenis. (pvz. kursiokai1)\n";
		std::cin>>failo_pav;
		//failo_pav = "kursiokai1";
		failo_pav += ".txt";
		try
		{
			skaitymas(failo_pav, stud, ilgvardas, ilgpavarde);
		}
		catch (std::exception &e)
		{
			std::cout << "Nepavyko atidaryti failo \n";
			return 0;
		}
		catch (int x)
		{
			std::cout << "failo " << x + 1 << " eiluteje yra klaida\n";
			return 0;
		}
	}

	//*Galutinio balo skaičiavimas*
	std::cout << "jei galutini bala skaiciuoti pagal vidurki rasykite 0, jei pagal mediana - 1 \n";
	std::cin >> t;
	while (t != "0" && t != "1")
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Įveskite skaičių 0 - skaiciavimui pagal vidurki arba 1 - skaiciavimui pagal mediana. \n";
		std::cin >> t;
	}
	//t = "0";
	if(t == "0"){
		for(size_t i = 0; i < stud.size(); i++){
			stud[i].galutinis(vidurkis(stud[i]));
			stud[i].ndrez_istrinti();
		}
	}
	else{
		for(size_t i = 0; i < stud.size(); i++){
			stud[i].galutinis(mediana(stud[i]));
			stud[i].ndrez_istrinti();
		}
	}

	//*Rezultato išvedimas*
	spausdinimas(stud, ilgvardas, ilgpavarde);
	
	auto pabaiga = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> trukme = pabaiga - pradzia;
	std::cout << "visa programa uztruko " << trukme.count() << " sek.\n";
	return 0;
}