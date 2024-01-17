#include <iostream>
#include <iomanip>   
#include <string>
#include <limits>
#include "model/validation.h"
#include "model/node.h"
#include "model/struct.h"
#include "model/bill.h"
#include "model/seller.h"
#include "model/clients.h"
#include "model/articles.h"
#include "file.h"
#include <conio.h>
#include "settings/style.h"
using namespace std;

Seller *previousSeller = NULL;
Client *previousClient = NULL;
Article *previousArticles = NULL;
SalesCheck *previousCheck = NULL;

// descuentos ------------
int M = 15;
int D1 = 10, V1 = 10;
int D2 = 20, V2 = 20;
int D3 = 30, V3 = 30;


// Bonus -----------------
int B1 = 500;
int B2 = 100;
int B3 = 1500;
int CB1 = 1;
int CB2 = 10;
int CB3 = 15;

// List------------------
Client *LClient = NULL;
Article *LArticles = NULL;
Seller *LSeller = NULL;
SalesCheck *LCheck = NULL;

// variables----------------
bool loadingArticles = true;
long long int number, dni;
long int keyArticles, keyCheck, stock, isKey, counterCLient, counterSeller;
float price;
string name, address, code , nameDB;
int opt;

void menuSeller();
void menuClient();
void buys();
void newClient();
void menuCheck();
void menuDiscount();
void salesCommission();
int findCheck(SalesCheck *&, long long int, SalesCheck *&);
int findCheckSeller(SalesCheck *&, long long int, SalesCheck *&, bool);
void cousin();



int main() {
    readFileArticle(LArticles, keyArticles, DBArticles, false);
    readFileClient(LClient, counterCLient);
    readFileSeller(LSeller, counterSeller);

    createFile("ARTICULOS",DBArticles);
    createFile("CLIENTES",DBClients);
    createFile("VENDEDORES",DBSellers);
    createFile("FACTURA",DBSelesCheck);


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
        cout << "13 - compra " << endl;

        cout << "0 - Salir " << endl<< endl;

        opt = validateNumber("Introduce la opcion >> ");
        
        switch (opt){
            case 1:
                // add article
                system("cls");
                cout << BLUE "\t-INGRESAR NUEVO ARTICULO-" NC<< endl;

                code = isVoid("Introduce el codigo >> ");
                name = isVoid("Introduce el nombre >> ");
                price = validateNumber("Introduce el precio >> ");
                stock = validateNumber("Introduce el stock >> ");
                keyArticles++;  

                addNode(LArticles, createArticle( keyArticles, code, name, price, stock), false);
                fileUploadArticle(LArticles);
                _getch();
                
                break;
            case 2:
                // edit article
                system("cls");
                if (LArticles != NULL){
                    cout << BLUE "\t-EDITAR ARTICULO-" NC<< endl;
                    isKey = validateNumber(" Introduce la clave >> ");

                    Article *previous = NULL;
                    Article *current = findKey(LArticles, isKey, previous);


                    if(current != NULL){
                        editArticle(LArticles, isKey, fileUploadArticle);
                    } else{
                        cout << REDB " Articulo no existe!" NC;
                        _getch();
                    }
                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch(); 
                }
                break;

            case 3:
                // Remove article 
                fflush(stdin);
                system("cls");
                cout << BLUE "\t-ELIMINAR ARTICULO- " NC<< endl;
                
                if (LArticles != NULL) {
                    isKey = validateNumber(" Introduce la clave >> ");
                    removeArticles(LArticles, isKey);
                    fileUploadArticle(LArticles);
                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch();
                }
                break; 

            case 4:
                // search article
                system("cls");

                if (LArticles != NULL){
                    searchMenu(LArticles);

                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch();
                }
                break;
            case 5:

                // Add stock
                system("cls");
                cout << BLUE "\t-INGRESO DE STOCK- " NC<< endl; 
                nameDB = isVoid("Introduce el nombre del archivo >> ");
                readFileArticle(LArticles, keyArticles, "db/"+nameDB+".txt", true);
                break;

            case 6:
                //Show articles
                showArticles(LArticles);
                break;

            case 7:
                //Show check
                menuCheck();
                break;

            case 8:
                // MENU CLIENT
                menuClient();
                break;
            case 9:
                menuDiscount();
                break;
            case 10:
                cousin();
                break;

            case 11:
                salesCommission();
                break;

            case 12:
                // MENU SELLER
                menuSeller();
                break;
            case 13:
                buys();
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

// void cousin(){
//     int opt;
//     int count, newB;
//     Seller *current = new Seller();
//     SalesCheck *currentCheck;

//     do{
//         fflush(stdin);
//         system("cls");
//         cout << BLUE "\t-GESTION DE BONUS-" NC<< endl;
//         cout << "1 - Mostrar Tabla " << endl;
//         cout << "2 - Edtar % de bonus " << endl;
//         cout << "0 - Salir " << endl << endl;

//         opt = validateNumber("Introduce la opcion >> ");
//         switch (opt){
//             case 1: 
//                 system("cls");
//                 current = LSeller;
//                 cout << BLUE "\t-TABLA DE BONUS-" NC << endl;
//                 cout << BLUE "\t\t\t\t-LISTA VENDEDORES-" NC << endl;
//                 cout << BLACK BLUEB ;
//                 cout << left << setw(15) << "DNI" << setw(30) << "NOMBRE" << setw(12) << "COMISION %" << setw(10) <<"VENTAS"<< setw(10) << "BONUS" <<endl ;
//                 cout << NC;
//                 while(current != NULL){
//                     count = 0;
//                     currentCheck = LCheck;

//                     while(currentCheck != NULL) {

//                         if(currentCheck->seller.person.dni == current->person.dni){
//                             count++;
//                         }
//                         currentCheck = currentCheck->next;
//                     }
//                     cout << left << setw(15) << current->person.dni << setw(32) << current->person.name << setw(13) << current->commission    << count << endl;
//                     current = current->next;
//                 }
//                 cout << endl;
//                 cout << "Presione cualquier tecla para continuar";
//                 _getch();
                
//                 break;
//             case 2 :
//                 int optB;
//                 do {
//                     system("cls");
//                     cout << BLUE "\tEDITAR DE BONUS-" NC << endl;
//                     cout << "1 - Cantidad de "<< CB1 << " para bonus de  " << B1 << endl;
//                     cout << "2 - Cantidad de "<< CB2 << " para bonus de  " << B2 << endl;
//                     cout << "3 - Cantidad de "<< CB3 << " para bonus de  " << B3 << endl;
//                     cout << "0 - Salir " << endl << endl;
//                     switch (optB){
//                         case 1:
//                             newB = validateNumber("Nuevo bonus >> ");
//                             B1 = newB;                            
//                             break;
//                         case 2:
//                             newB = validateNumber("Nuevo bonus >> ");
//                             B2 = newB;
//                             break;
//                         case 3:
//                             newB = validateNumber("Nuevo bonus >> ");
//                             B3 = newB;
//                         default:
//                             break;
//                     }
//                 } while (optB != 0);
//                 break;
//             case 0:
//                 break;

//             default:
//                 cout << " " << REDB "Opcion no valida" NC;
//                 _getch();
//                 break;
//         }

//     } while(opt != 0);

// }

void cousin(){

    int opt;
    int count, newB, bonus;
    Seller *current = nullptr;
    SalesCheck *currentCheck = nullptr;

    do{
        fflush(stdin);
        system("cls");
        cout << BLUE "\t-GESTION DE BONUS-" NC<< endl;
        cout << "1 - Mostrar Tabla " << endl;
        cout << "2 - Edtar % de bonus " << endl;
        cout << "0 - Salir " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");
        switch (opt){
            case 1: 
                system("cls");
                current = LSeller;
                cout << BLUE "\t-TABLA DE BONUS-" NC << endl;
                cout << BLUE "\t\t\t\t-LISTA VENDEDORES-" NC << endl;
                cout << BLACK BLUEB ;
                cout << left << setw(15) << "DNI" << setw(30) << "NOMBRE" << setw(12) << "COMISION %" << setw(10) <<"VENTAS"<< setw(10) << "BONUS" <<endl ;
                cout << NC;
                while(current != NULL){
                    bonus = 0;
                    count = 0;
                    currentCheck = LCheck;

                    while(currentCheck != NULL) {

                        if(currentCheck->seller.person.dni == current->person.dni){
                            count++;
                        }
                        currentCheck = currentCheck->next;
                    }
                    if (count >= CB1 && count < B2) {
                        bonus = B1;
                    } else if (count >= CB2 && count < B3) {
                        bonus = B2;
                    } else if (count >= CB3) {
                        bonus = B3;
                    }
                    cout << left << setw(15) << current->person.dni << setw(32) << current->person.name << setw(13) << current->commission << setw(8)   << count <<bonus <<  endl;
                    current = current->next;
                }
                cout << endl;
                cout << "Presione cualquier tecla para continuar";
                _getch();
                
                break;
            case 2 :
                int optB;
                do {
                    system("cls");
                    cout << BLUE "\tEDITAR DE BONUS-" NC << endl;
                    cout << "1 - Cantidad de "<< CB1 << " para bonus de  " << B1 << endl;
                    cout << "2 - Cantidad de "<< CB2 << " para bonus de  " << B2 << endl;
                    cout << "3 - Cantidad de "<< CB3 << " para bonus de  " << B3 << endl;
                    cout << "0 - Salir " << endl << endl;
                    optB = validateNumber("Introduce la opcion >> ");
                    switch (optB){
                        case 1:
                            newB = validateNumber("Nuevo bonus >> ");
                            B1 = newB;                            
                            break;
                        case 2:
                            newB = validateNumber("Nuevo bonus >> ");
                            B2 = newB;
                            break;
                        case 3:
                            newB = validateNumber("Nuevo bonus >> ");
                            B3 = newB;
                        default:
                            break;
                    }
                } while (optB != 0);
                break;
            case 0:
                break;

            default:
                cout << " " << REDB "Opcion no valida" NC;
                _getch();
                break;
        }

    } while(opt != 0);

}



void salesCommission(){
    system("cls");
    cout << BLUE "\t-GESTION DE CLIENTES-" NC<< endl;
    dni = validateNumber("DNI Vendedor >> ");
    Seller *currentSeller = find(LSeller, dni, previousSeller);

    if (currentSeller == NULL) {
        cout << REDB "No existe el vendedor" NC;
        _getch();
    } else {
        cout << "VENDEDOR >> " << currentSeller->person.name << endl;
        cout << "COMISION >> " << currentSeller->commission << endl;
        cout << "CANTIDAD DE VENTAS >> " << findCheckSeller(LCheck, currentSeller->person.dni, previousCheck, false) << endl;
        cout << "MONTO A PAGAR >> " << (findCheckSeller(LCheck, currentSeller->person.dni, previousCheck, true)/100.0)*currentSeller->commission;
        
    }
    _getch();

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

        
        switch (opt){
            case 1:
                // ADD CLIENT 
                system("cls");
                newClient();
                break;
            case 2:
                system("cls");
                if (LClient != NULL){
                    cout <<BLUE "\t-EDITAR CLIENTE-" NC<< endl;
                    dni = validateNumber("DNI del cliente: ");

                    editClient(LClient, dni, fileUploadCLient);

                } else {
                    cout << REDB "Lista vacia." NC;
                    _getch(); 
                }
                break; 

            case 3:
                system("cls");
                if (LClient != NULL) {

                    searchMenu(LClient);

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


void newClient(){
    bool rDNI;
    fflush(stdin);
    cout << BLUE "\t-AGREGAR NUEVO CLIENTE-" NC << endl;
    while(true) {
        dni = validateNumber("DNI del cliente >> ");
        rDNI = isDuplicate(LClient, dni);
        if (rDNI){
            cout << " " << REDB "Ya existe el DNI" NC << endl;
        } else {
            break;
        }
    }
    fflush(stdin);
    name = isVoid("Nombre del cliente >> ");
    fflush(stdin);
    address = isVoid("Direccion del cliente >> ");
    fflush(stdin);
    number = validateNumber("Numero telefonico del cliente >> ");                
    addClient(LClient, createClient(dni, name,  address, number),false, fileUploadCLient);
    _getch();
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
                // ADD SELLER
                bool rDNI;
                system("cls");
                fflush(stdin);
                cout << BLUE "\t-AGREGAR NUEVO VENDEDOR-" NC << endl;
                while(true){
                    dni = validateNumber("DNI del vendedor >> ");
                    rDNI = isDuplicate(LSeller, dni);
                    if(rDNI){
                        cout << " " << REDB "Ya existe el DNI" NC << endl;
                    } else {
                        break;
                    }

                }

                fflush(stdin);
                cout << "Nombre del vendedor >> ";
                getline(cin, name);

                fflush(stdin);
                cout << "-Fecha de admision: "<<endl;
                do {
                    day = validateNumber("Dia >> ");
                    validateDate(day, limiteDay);
                } while (day > limiteDay || day == 0);
                do {
                    month = validateNumber("Mes >> ");
                    validateDate(month, limiteMonth);
                } while( month > limiteMonth || month == 0);
               do {
                    year = validateNumber("Año >> ");
                    validateYear(year, limiteYear);
               } while (year < limiteYear || year == 0);



                comission = validateNumber("Comision del vendedor >> ");

                addNode(LSeller, createSeller(dni, name,  day, month, year,comission),false);
                fileUploadSeller(LSeller);
                _getch();

                break;
            
            case 2:
                system("cls");
                fflush(stdin);
                cout << BLUE "\t-EDITAR VENDEDOR-" NC << endl;

                dni = validateNumber("DNI del vendedor >> ");
                editSeller(LSeller, dni, fileUploadSeller);
                break;

            case 3:
                searchMenu(LSeller);
                break;


            case 4:
                system("cls");
                cout <<BLUE "\t-ELIMINAR VENDEDOR-" NC<< endl;
                fflush(stdin);
                dni = validateNumber("DNI del vendedor >> ");
                removeSeller(LSeller, dni);
                fileUploadSeller(LSeller);
                break;
            case 5:
                showSellers(LSeller);
                break;
            case 0:
                break;  

            default:
                cout << " " << REDB "Opcion no valida" NC;
                _getch();
                break;
            }


    } while (opt != 0);
}
void menuDiscount() {
    int opt;
    int optPor;
    int* V[] = {&V1, &V2, &V3};
    int* D[] = {&D1, &D2, &D3};

    do {
        system("cls");
        cout << BLUE "\t-GESTION DE DESCUENTOS-" NC<< endl;
        for(int i = 0; i < 3; i++) {
            cout << i+1 << " - "<< *V[i] <<" Ventas -> "<< *D[i] <<"% " << endl;
        }
        cout << "4 - Monto > 1000 $ -> "<< M <<"% " << endl;
        cout << "0 - Salir " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");

        if(opt >= 1 && opt <= 3) {
            do {
                cout << "1 - Numero de ventas "<< endl;
                cout << "2 - % " << endl;
                cout << "0 - Salir " << endl << endl;
                optPor = validateNumber("Introduce la opcion >> ");
                switch (optPor){
                    case 1:
                        *V[opt-1] = validateNumber("Nuevo numero de ventas >> ");
                        break;
                    case 2:
                        *D[opt-1] = validateNumber("Nuevo % por ventas >>  ");
                        break;
                    case 0:
                        break;
                    default:
                        cout << " " << REDB "Opcion no valida" NC;
                        _getch();
                        break;
                }
            } while (optPor != 0);
        } else if(opt == 4) {
            M = validateNumber("Nuevo % por el monto >> ");
        } else if(opt != 0) {
            cout << " " << REDB "Opcion no valida" NC;
            _getch();
        }
    } while (opt != 0);
}



void menuCheck(){
    int opt;
    do {
        fflush(stdin);

        system("cls");
        cout << BLUE "\t-GESTION DE FACTURAS-" NC<< endl;
        cout << "1 - Ver Facturas " << endl;
        cout << "2 - Editar Facturas " << endl;
        cout << "3 - Eliminar " << endl;
        cout << "0 - Salir " << endl << endl;

        opt = validateNumber("Introduce la opcion >> ");

        switch (opt){
        case 1:
            showCheck(LCheck);
            break;
        case 2:
            fflush(stdin);
            system("cls");
            cout << BLUE "\t-EDITAR FACTURA- " NC<< endl;
            
            if (LArticles != NULL) {
                isKey = validateNumber(" Introduce la clave >> ");
                editChek(LCheck, LSeller, LClient, isKey);
            } else {
                cout << REDB "Lista vacia." NC;
                _getch();
            }
            break;

        case 3:
            fflush(stdin);
            system("cls");
            cout << BLUE "\t-ELIMINAR FACTURA- " NC<< endl;
            
            if (LArticles != NULL) {
                isKey = validateNumber(" Introduce la clave >> ");
                removeCheck(LCheck, isKey);
            } else {
                cout << REDB "Lista vacia." NC;
                _getch();
            }
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


void buys(){
    int DT = 0;
    int discount = 0; 
    Article *LBuys = NULL;
    int key;
    long double monto, priceCurrent = 0;


    do {
        fflush(stdin);
        system("cls");
        cout << BLUE "\t-COMPRA-" NC<< endl;

        dni = validateNumber("DNI Vendedor >> ");
        Seller *currentSeller = find(LSeller, dni, previousSeller);

        if (currentSeller == NULL) {
            cout << REDB "No existe el vendedor" NC;
            _getch();
            break;
        }
        cout << "VENDEDOR [ " << currentSeller->person.name << " ]" << endl<< endl;

        fflush(stdin);
        dni = validateNumber("DNI Comprador >> ");
        Client *currentClient = find(LClient, dni, 
        previousClient);

        if (currentClient == NULL){
            cout << REDB "\tComprador no registrado" NC << endl;
            newClient();
            currentClient = find(LClient, dni, previousClient);
        }
        while(true){
            priceCurrent = 0;
            int countArticle;
            system("cls");
            cout << BLUE "\t-COMPRA-" NC<< endl;
            cout << "VENDEDOR >> " << currentSeller->person.name  << endl;
            cout << "CLIENTE >> " << currentClient->person.name << endl;
            cout << BLUE "\t-ARTICULOS-" NC<< endl;
            if(LBuys != NULL){
                Article *current = LBuys;
                while(current != NULL){
                cout << current->stock<< setw(7) << setw(10) << current->name << setw(7) << current->price << setw(5)<< "$" << endl;
                if (current->stock > 1){
                    priceCurrent += (current->stock * current->price);

                } else {
                    priceCurrent += current->price;

                }
                current = current->next;
                } 
            }
            cout << "-------------------------" << endl;            
            cout << "MONTO >> " << priceCurrent << endl;
            cout << "> Presione 00 para monto total" << endl;
            key = validateNumber("Codigo >> ");
            Article *currentArticle = findKey(LArticles, key, previousArticles);
            if ( key != 00){
                if ( currentArticle == NULL) {
                    cout << REDB "EL articulos no existe" NC;
                    _getch();
                } else {

                    countArticle = searchArticle(LBuys, "name", currentArticle->name, true);

                    if (countArticle == 0){
                        addNode(LBuys, createArticle(currentArticle->key, currentArticle->code, currentArticle->name, currentArticle->price, (countArticle == 0 ? 1 : countArticle)), true );
                    } else {
                        Article *currentArticle = findKey(LBuys, key, previousArticles);
                        currentArticle->stock = currentArticle->stock + 1;
                    }
                }
            } else {
                int countClient = findCheck(LCheck, currentClient->person.dni, previousCheck);
                int* V[] = {&V1, &V2, &V3};
                int* D[] = {&D1, &D2, &D3};
                monto = priceCurrent;

                for(int i = 0; i < 3; i++) {
                    if(countClient >= *V[i]) {
                        cout << "Descuento por frecuencia " << *D[i] <<"%" << endl;
                        monto = monto - ((*D[i]/100.0)*monto);
                        break;
                        DT = *D[i];
                    }
                }

                if (monto > 1000) {
                    cout << "Descuento por monto de compra " << M <<"%" << endl;
                    monto = monto - ((M/100.0)*monto);
                    cout << "Monto total            " << monto << endl;
                    DT += M;
                }


                break;
                
            }
        }
        keyCheck++;

        addNode(LCheck, createBill(keyCheck, currentSeller, currentClient, LBuys, DT, priceCurrent, monto), false);
        fileUploadCheck(LCheck);


        _getch();
        break;

    } while(opt != 0);
}


int findCheck(SalesCheck *&list, long long int dni, SalesCheck *&previous) {
    int  countClient = 0;
    SalesCheck *current = list;
    previous = NULL;

    while (current != NULL) {
        previous = current;
        if (current->client.person.dni == dni){
            countClient ++;
        }
        current = current->next;
    }
    return countClient;
}

int findCheckSeller(SalesCheck *&list, long long int dni, SalesCheck *&previous, bool type) {
    int  m = 0;
    int countCheck =0 ;
    SalesCheck *current = list;
    previous = NULL;

    while (current != NULL) {
        previous = current;
        if (current->seller.person.dni == dni){
            m = m + current->discountedAmount;
            countCheck++;
        }
        current = current->next;
    }
    if (type){
        return m;

    } else {
        return countCheck;

    }
}
