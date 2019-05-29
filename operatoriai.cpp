#include "struktura.h"

bool operator > (const studentas &a, const studentas &b) { return a.getGalutinis() > b.getGalutinis(); }

bool operator >= (const studentas &a, const studentas &b) { return a.getGalutinis() >= b.getGalutinis(); }

bool operator < (const studentas &a, const studentas &b) { return a.getGalutinis() < b.getGalutinis(); }

bool operator <= (const studentas &a, const studentas &b) { return a.getGalutinis() <= b.getGalutinis(); }

bool operator == (const studentas &a, const studentas &b) { return a.getGalutinis() == b.getGalutinis(); }

bool operator != (const studentas &a, const studentas &b) { return a.getGalutinis() != b.getGalutinis(); }

std::ofstream & operator << (std::ofstream &os, studentas &a){
    os << "Studento vardas: " << a.getVardas() <<"\n";
    os << "Studento pavardė: " << a.getPavarde() <<"\n";
    os << "Studento galutinis balas: " << a.getGalutinis() << "\n";
    return os;
}