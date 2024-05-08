#include <iostream>
#include <string>

using namespace std;

char menu();
bool verificador_menu(char &);

int main(){
	//INICIALIZAR COLAS Y PILAS
	
	char resp;
	do {
		resp = menu();
		
		switch(resp){
			case 'A':
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			default:
				break;
		}
		
		
		
	} while (resp != 'F');
	return 0;
}

char menu(){
	char resp;
	do {
		system("CLS");
		cout << "|------- B A N C O  E L  T E S O R O -------|" << endl;
		cout << "| A. Ingresar Cliente                       |" << endl;
		cout << "| 1. Llamar siguiente cliente Taquilla 1    |" << endl;
		cout << "| 2. Llamar siguiente cliente Taquilla 2    |" << endl;
		cout << "| 3. Llamar siguiente cliente Taquilla 3    |" << endl;
		cout << "| F. Finalizar Programa                     |" << endl;
		cout << "|-------------------------------------------|" << endl;
		cout << "| Respuesta: ";
		cin >> resp;
		
		if (verificador_menu(resp)){
			cout << "| Digito erroneo, intente de nuevo." << endl; 
			system("PAUSE");
		}
	} while(verificador_menu(resp));
	
	return resp;
}

bool verificador_menu(char &resp){
	if (resp >= 'a' && resp <= 'z') {
        resp -= 32;
    }
	return (resp == 'A' || resp == '1' || resp == '2' || resp == '3' || resp == 'F') ? false : true;
}

string pedir_cedula(){
	string cedula;
	cout << "Ingrese numero de cedula:";
	cin >> cedula;
	return cedula;
}

