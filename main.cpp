#include <iostream>
#include <iomanip>   
#include <string>
#include <limits>
#include "model/validation.h"
#include "model/struct.h"
#include "model/seller.h"
#include "model/clients.h"
#include "model/articles.h"
#include "model/node.h"
#include "file.h"
#include <conio.h>
#include "settings/style.h"
using namespace std;


// List------------------
Client *LClient = NULL;
Article *LArticles = NULL;
Seller *LSeller = NULL;

// variables----------------
bool loadingArticles = true;
long long int number, dni;
long int keyArticles, stock, isKey, counterCLient, counterSeller;
float price;
string name, address, code;
int opt;

void menuSeller();
void menuClient();

int main() {
    readFileArticle(LArticles, keyArticles);
    readFileClient(LClient, counterCLient);
    readFileSeller(LSeller, counterSeller);

    createFile("ARTICULOS",DBArticles);
    createFile("CLIENTES",DBClients);
    createFile("VENDEDORES",DBSellers);

    do{
        fflush(stdin);

        system("cls");
        if (loadingArticles){
            cout << "CARGANDO BD..." << endl;  
            cout << "ARTICULOS" << (keyArticles == 0? RED : GREEN) <<"["<< keyArticles << "]" NC << " | " << "VENDEDORES" << (counterSeller == 0? RED : GREEN) <<"["<< counterSeller << "]" NC << " | " << "CLIENTES" <<(counterCLient == 0? RED : GREEN) <<"["<< counterCLient << "]" NC<<endl << endl;
            loadingArticles = false;
        }
        

        cout << BLUE "\t-TIENDA DE ARTICULOS-" NC << endl;
        cout << "1 - Ingresar nuevo articulo " << endl;
        cout << "2 - Editar articulo " << endl;
        cout << "3 - Eliminar articulo" << endl;
        cout << "4 - Busqueda de Articulos" << endl;
        cout << "5 - Ingreso de Stock al Inventario" << endl;
        cout << "6 - Ver Articulos " << endl << endl;
        
        cout << "7 - Menu Gestion de Facturas " << endl;
        cout << "8 - Menu Gestion de Clientes " << endl;
        cout << "9 - Menu Gestion de Descuentos " << endl;
        cout << "10 - Menu Gestion de Bonos " << endl;
        cout << "11 - Menu Gestion de Comisiones " << endl;
        cout << "12 - Menu Gestion de Vendedores " << endl;

        cout << "0 - Salir " << endl;
        cout << "V0.1.2.8 " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");
        cin.ignore();

        
        switch (opt){
            case 1:
                // add article
                system("cls");
                cout << BLUE "\t-INGRESAR NUEVO ARTICULO-" NC<< endl;
                cout << "Introduce el codigo >> ";
                getline(cin, code);
                cout << "Introduce el nombre >> ";
                getline(cin, name);

                price = validateNumber("Introduce el precio >> ");
                stock = validateNumber("Introduce el stock >> ");
                keyArticles++;

                addNode(LArticles, createArticle( keyArticles, code, name, price, stock), false,fileUploadArticle);
                _getch();
                
                break;
            case 2:
                // edit article
                system("cls");
                if (LArticles != NULL){
                    cout << BLUE "\t-EDITAR ARTICULO-" NC<< endl;
                    isKey = validateNumber(" Introduce la clave >> ");

                    Article *previous = NULL;
                    Article *current = findArticle(LArticles, isKey, previous);


                    if(current != NULL){
                        editArticle(LArticles, isKey, fileUploadArticle);
                    } else{
                        cout << " Articulo no existe!"<< endl;
                        cout << "Presione un boton para continuar.";
                        _getch();
                    }
                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch(); 
                }
                break;

            case 3:
                fflush(stdin);
                system("cls");
                cout << BLUE "\t-ELIMINAR ARTICULO- " NC<< endl;
                
                if (LArticles != NULL) {
                    isKey = validateNumber(" Introduce la clave >> ");
                    removeArticles(LArticles, isKey);
                    fileUploadArticle(LArticles);
                } else {
                    cout << "No existen articulos. Presione un boton para continuar";
                    _getch();
                }
                break; 

            case 4:

                system("cls");

                if (LArticles != NULL){
                    searchArticle(LArticles);

                } else {
                    cout << "No existen articulos. Presione un boton para continuar";
                    _getch();
                }
                break;
            case 6:
                showArticles(LArticles);
                break;

            case 8:
                // MENU CLIENT
                menuClient();
                break;

            case 12:
                menuSeller();
                break;
            case 0:
                break;
            default:
                cout << " " << REDB "Opcion no valida" NC;
                _getch();
                break;
            }
    }while (opt != 0);
    return 0;
}

void menuClient(){
    int opt;
    do{
        fflush(stdin);

        system("cls");
        cout << BLUE "\t-GESTION DE CLIENTES-" NC<< endl;
        cout << "1 - Agregar cliente " << endl;
        cout << "2 - Editar cliente " << endl;
        cout << "3 - Buscar cliente " << endl;
        cout << "4 - Eliminar cliente " << endl;
        cout << "5 - Mostar lista de clientes" << endl;
        cout << "0 - Salir " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");
        cin.ignore();

        
        switch (opt){
            case 1:

                // ADD CLIENT 
                system("cls");
                fflush(stdin);
                cout << BLUE "\t-AGREGAR NUEVO CLIENTE-" NC << endl;

                dni = validateNumber("DNI del cliente >> ");
                cin.ignore();

                fflush(stdin);
                cout << "Nombre del cliente: ";
                getline(cin, name);

                fflush(stdin);
                cout << "Direccion del cliente: ";
                getline(cin, address);

                fflush(stdin);
                number = validateNumber("Numero telefonico del cliente: ");
                cin.ignore();
                
                addClient(LClient, createClient(dni, name,  address, number),false, fileUploadCLient);
                _getch();

                break;
            case 2:
                system("cls");
                if (LClient != NULL){
                    cout <<BLUE "\t-EDITAR CLIENTE-" NC<< endl;
                    cout << "DNI del cliente: ";
                    cin >> dni;
                    cin.ignore();

                    editClient(LClient, dni, fileUploadCLient);

                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch(); 
                }
                break; 

            case 3:
                system("cls");
                if (LClient != NULL) {

                    searchClient(LClient);

                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch(); 
                }
                break; 
                

            case 4:
                system("cls");
                cout <<BLUE "\t-ELIMINAR CLIENTE-" NC<< endl;
                fflush(stdin);
                dni = validateNumber("DNI del cliente >> ");
                removeClient(LClient, dni);
                fileUploadCLient(LClient);
                break;

            case 5:
                showClients(LClient);
                break;
            case 0:
                break;
            default:
                cout << " " << REDB "Opcion no valida" NC;
                _getch();
                break;
            }
    }while (opt != 0);

}



void menuSeller(){
    int opt, day, month, year, comission;
    do {
        fflush(stdin);

        system("cls");
        cout << BLUE "\t-GESTION DE VENDEDORES-" NC<< endl;
        cout << "1 - Agregar vendedor " << endl;
        cout << "2 - Editar vendedor " << endl;
        cout << "3 - Buscar vendedor " << endl;
        cout << "4 - Eliminar vendedor " << endl;
        cout << "5 - Mostar lista de vendedores" << endl;
        cout << "0 - Salir " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");

        switch (opt) {
        case 1:
            // ADD CLIENT 
            system("cls");
            fflush(stdin);
            cout << BLUE "\t-AGREGAR NUEVO VENDEDOR-" NC << endl;

            dni = validateNumber("DNI del vendedor >> ");
            cin.ignore();

            fflush(stdin);
            cout << "Nombre del vendedor: ";
            getline(cin, name);

            fflush(stdin);
            cout << "-Fecha de admision: "<<endl;
            day = validateNumber("Dia >> ");
            month = validateNumber("Mes >> ");
            year = validateNumber("Año >> ");

            cout << endl;

            comission = validateNumber("Comision del vendedor >> ");

            cin.ignore();
            addNode(LSeller, createSeller(dni, name,  day, month, year,comission),false, fileUploadSeller);
            _getch();

            break;
        
        case 5:
            showSellers(LSeller);
            break;


        default:
            break;
        }


    } while (opt != 0);
}