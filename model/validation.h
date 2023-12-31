#include <iostream>
#include "../settings/style.h"
#include <conio.h>

using namespace std;


const int limiteDay = 31, limiteMonth = 12, limiteYear = 2000;

string isVoid(string text){

    string input;
    while(true){
        cout << text;
        getline(cin, input);
        if (input.empty()){
            cout << REDB "No se acepta una entrada vacia, vuelve a intentar.\n" NC;
        } else {\
            break;
        }

    }
    return input;

}

double validateNumber(string text) {
    double number;
    string input;

    while (true) {
        cout << text;
        getline(cin, input);

        // Verifica si la entrada está vacía
        if (input.empty()) {    
            cout << REDB "No se acepta una entrada vacia, vuelve a intentar.\n" NC;
            continue;
        }

        // Convierte la entrada a double
        stringstream ss(input);
        ss >> number;

        if (ss.fail() || !ss.eof()) {
            cout << REDB "No se aceptan letras, vuelve a intentar.\n" NC;
        } else if (number < 0) {
            cout << REDB "Cantidad incorrecta, vuelve a intentarlo\n" NC;
        } else {
            break; //  la entrada es válida
        }
    }
    return number;
}


void validateDate(int date, int limiteDate) {
    if (date > limiteDate || date == 0){
        cout <<  REDB "Fecha incorrecta"  NC << endl;
    }  
}

void validateYear(int year, int limiteYear) {
    if (year < limiteYear || year == 0){
        cout <<  REDB "Fecha incorrecta"  NC << endl;
    }  
}