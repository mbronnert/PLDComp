#include "Parametre.h"
#include <iostream>
#include <list>
#include <map>


Parametre::Parametre(Type t, string n) {
    type = t;
    nom = n;
}

void Parametre::affiche () {
	cout << "-> Parametre { type :" << type << ", nom : " << nom << " }" << endl;
}

Type Parametre::getType() {
	return type;
}

string Parametre::getNom() {
	return nom;
}



