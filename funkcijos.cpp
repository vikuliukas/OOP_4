#include "struktura.h"
#include "vector.h"

double vidurkis(studentas & a)
{	
	double vid;

	if (a.ndrez_ar_tuscias())
	{
		vid = 0;
	}
	else
	{
		vid = a.ndrez_suma() / a.ndrez_dydis();
	}
	return round((0.40 * vid + 0.60 * a.getEgzaminorez())*100)/100;
}

double mediana(studentas & a)
{
	double med;
	if (a.ndrez_ar_tuscias())
	{
		med = 0;
	}
	else
	{
		a.ndrez_isrikiuoti();
		if (a.ndrez_dydis() % 2 == 0)
		{
			med = (double)(a.getNdrez(a.ndrez_dydis() / 2) + a.getNdrez(a.ndrez_dydis() / 2 - 1)) / 2;
		}
		else
		{
			med = (double)a.getNdrez(a.ndrez_dydis() / 2);
		}
	}
	return round((0.40 * med + 0.60 * a.getEgzaminorez())*100)/100;
}

void spausdinimas(vector<studentas> &stud, std::size_t ilgvardas, std::size_t ilgpavarde)
{
	std::sort(stud.begin(), stud.end(), operator>);
	std::size_t i = 0;
	while ((stud[i].getGalutinis() >= 5) && ( i <= stud.size())) 
	{
		i++;
	}

	vector<studentas> saunuoliai;
	vector<studentas> vargsiukai;
	saunuoliai.assign(stud.begin(), stud.begin() + i);
	vargsiukai.assign(stud.begin() + i, stud.end());
	stud.clear();
	stud.shrink_to_fit();

	std::ofstream s("šaunuoliai.txt");
	for (std::size_t i = 0; i < saunuoliai.size(); i++)
	{
		s << std::left << std::setw(ilgpavarde + 1) << saunuoliai[i].getPavarde() << std::left << std::setw(ilgvardas + 1) << saunuoliai[i].getVardas();
		s << std::left << std::setw(20) << std::fixed << std::setprecision(2) << saunuoliai[i].getGalutinis() << "\r\n";
	}
	s.close();
	std::ofstream v("vargšiukai.txt");
	for (std::size_t i = 0; i < vargsiukai.size(); i++)
	{
		v << std::left << std::setw(ilgpavarde + 1) << vargsiukai[i].getPavarde() << std::left << std::setw(ilgvardas + 1) << vargsiukai[i].getVardas();
		v << std::left << std::setw(20) << std::fixed << std::setprecision(2) << vargsiukai[i].getGalutinis() << "\r\n";
	}
	v.close();
	saunuoliai.clear();
	saunuoliai.shrink_to_fit();
	vargsiukai.clear();
	vargsiukai.shrink_to_fit();
}