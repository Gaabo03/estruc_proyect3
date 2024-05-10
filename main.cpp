#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Para cola
#define QUEUEMAX 100
typedef string Numero;
typedef struct queuer {
	int front; //Frente de la cola
	int rear; //Final de la cola
	Numero queue[QUEUEMAX];
} Cola_Virtual;

void newQueue(Cola_Virtual *queue);
void enqueue(Cola_Virtual *q_ptr, Numero elem);
Numero dequeue(Cola_Virtual *q_ptr);
Numero front(Cola_Virtual *q_ptr);
bool isempty(Cola_Virtual *q_ptr);
bool isFull(Cola_Virtual *q_ptr);


char menu();
bool verificador_menu(char &);
string pedir_cedula();

void generarClave(Numero &clave, Cola_Virtual *queue);
int main(){
	//INICIALIZAR COLAS Y PILAS
	Cola_Virtual cola;
	newQueue(&cola);
	
	Numero numero;
	char resp;
	do {
		resp = menu();
		
		switch(resp){
			case 'A':
				numero = pedir_cedula();
				generarClave(numero,&cola);
				enqueue(&cola, numero);
				cout << "La clave es: " << numero << endl;
				system("PAUSE");
				break;
			case '1':
				numero = dequeue(&cola);
				cout << "Pase a la taquilla 1: " << numero << endl;
				system("PAUSE");
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


// Código para la cola
void newQueue(Cola_Virtual *q_ptr){ //Nueva cola
	q_ptr->front = 0;
	q_ptr->rear = -1;
}

void enqueue(Cola_Virtual *q_ptr, Numero elem){ //Insertar un elemento en la cola
	if (!isFull(q_ptr)){
		q_ptr->rear++;
		q_ptr->queue[q_ptr->rear] = elem;
	}
	return;
}

Numero dequeue(Cola_Virtual *q_ptr){ //Eliminar elemento de la cola
	Numero element;
	int i;
	if (!isempty(q_ptr)){
		element = q_ptr->queue[q_ptr->front];
		q_ptr->rear--;
		for (i = 0; i <= q_ptr->rear; i++)
			q_ptr->queue[i] = q_ptr->queue[i + 1];
		return element;
	}
	return "";
}

Numero front(Cola_Virtual *q_ptr){ //Para encontrar la cabeza de la cola
	if (!isempty(q_ptr))
		return q_ptr->queue[q_ptr->front];
	else
		return "";
}

bool isempty(Cola_Virtual *q_ptr){
	if (q_ptr->rear == -1)
		return true;
	else
		return false;
}

bool isFull(Cola_Virtual *q_ptr){
	if (q_ptr->rear == QUEUEMAX - 1)
		return true;
	else
		return false;
}

void generarClave(Numero &clave, Cola_Virtual *cola) {
    Numero cedula = clave;
    int len = cedula.length();

    for (int i = len - 3; i >= 0; i--) {
        // Genera una nueva clave con los últimos 3 dígitos
        clave = cedula.substr(i, 3);
        
        // Verifica si la clave generada ya existe en la cola
        bool clave_existente = false;
        for (int j = cola->front; j <= cola->rear; j++) {
            if (cola->queue[j] == clave) {
                clave_existente = true;
                break;
            }
        }

        // Si la clave no existe, termina el bucle
        if (!clave_existente)
            break;
    }
/*
    // Si no se encontró una clave única, invierte la cédula y repite el proceso
    if (clave == cedula) {
		
		reverse(cedula.begin(), cedula.end());
		for (int i = len - 3; i >= 0; i--) {
			clave = cedula.substr(i, 3);
            bool clave_existente = false;
            for (int j = cola->front; j <= cola->rear; j++) {
                if (cola->queue[j] == clave) {
                    clave_existente = true;
                    break;
                }
            }
            if (!clave_existente)
                return;
		}
        generarClave(cedula, cola); // Llama recursivamente a la función con la cédula invertida
    }*/
}

