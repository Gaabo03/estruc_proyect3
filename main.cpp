#include <iostream>
#include <string>

using namespace std;

//Para cola
#define QUEUEMAX 6
typedef string Numero;
typedef struct queuer {
	int front; //Frente de la cola
	int rear; //Final de la cola
	Numero queue[QUEUEMAX];
	bool isEmpty;
	bool isFull;
} Cola_Virtual;

void newQueue(Cola_Virtual *queue);
void enqueue(Cola_Virtual *q_ptr, Numero elem);
Numero dequeue(Cola_Virtual *q_ptr);
Numero front(Cola_Virtual *q_ptr);


char menu();
bool verificador_menu(char &);
string pedir_cedula();

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
	q_ptr->front = -1;
	q_ptr->rear = -1;
	q_ptr->isEmpty = true;
	q_ptr->isFull = false;
}

void enqueue(Cola_Virtual *q_ptr, Numero elem){ //Insertar un elemento en la cola
	if (!q_ptr->isFull){
		if (q_ptr->rear >= QUEUEMAX-1)
			q_ptr->rear = 0;
		else
			q_ptr->rear++;

		q_ptr->queue[q_ptr->rear] = elem;
		
		if (q_ptr->front == -1)
			q_ptr->front = q_ptr->rear;	
		q_ptr->isEmpty = false;
		if (q_ptr->front == q_ptr->rear+1)
			q_ptr->isFull = true;
	} else {
		cout << "La cola esta llena" << endl;
	}
	return;
}

Numero dequeue(Cola_Virtual *q_ptr){ //Eliminar elemento de la cola
	Numero element;
	int i;
	if (!q_ptr->isEmpty){
		element = q_ptr->queue[q_ptr->front];
		if (q_ptr->front == q_ptr->rear){
			q_ptr->front = -1;
			q_ptr->rear = -1;
			q_ptr->isEmpty = true;
		} else {
			if (q_ptr->front >= QUEUEMAX-1)
				q_ptr->front = 0;
			else
				q_ptr->front++;
		}
		return element;
	} else {
		cout << "La cola esta vacia" << endl;
	}
	return "";
}

Numero front(Cola_Virtual *q_ptr){ //Para encontrar la cabeza de la cola
	if (!q_ptr->isEmpty)
		return q_ptr->queue[q_ptr->front];
	else
		return "";
}



