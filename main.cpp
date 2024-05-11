#include <iostream>
#include <string>

#define QUEUEMAX 10
#define STACKMAX 10

using namespace std;

typedef string Numero;
typedef struct queuer {
	int front; //Frente de la cola
	int rear; //Final de la cola
	Numero queue[QUEUEMAX];
	bool isEmpty;
	bool isFull;
} Cola_Virtual;

typedef char Digito;
typedef struct stacker {
	int top;
	Digito stack[STACKMAX];
} Pila;

//Para cola
void newQueue(Cola_Virtual *queue);
void enqueue(Cola_Virtual *q_ptr, Numero elem);
Numero dequeue(Cola_Virtual *q_ptr);
//Para pila
void newStack(Pila *stack);
void push (Pila *st_ptr, Digito elem);
Digito pop(Pila *st_ptr);
bool isEmpty(Pila *st_ptr);
bool isFull(Pila *st_ptr);

char menu();
bool verificador_menu(char &);
string pedir_cedula();
Numero generarClave(Cola_Virtual queue, Numero cedula);
void imprimir_informacion(Cola_Virtual cola, Numero taquilla[]);

int main(){
	Cola_Virtual cola;
	newQueue(&cola);
	Numero taquilla[3], clave;
	int pos_taquilla;
	char resp;
	
	do {
		resp = menu();
		switch(resp){
			case 'A':
				clave = generarClave(cola, pedir_cedula());
				if (!clave.empty())
					enqueue(&cola, clave);
				imprimir_informacion(cola, taquilla);
				break;
			case '1':
			case '2':
			case '3':
				clave = dequeue(&cola);
				pos_taquilla = resp - '0';
				taquilla[pos_taquilla-1] = clave;
				cout << "|\n| Pase a la TAQUILLA " << resp << ": " << (clave.empty() ? "La cola esta vacia" : clave) << "\n| ";
				imprimir_informacion(cola, taquilla);
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
	return !(resp == 'A' || resp == '1' || resp == '2' || resp == '3' || resp == 'F');
}

string pedir_cedula(){
	string cedula;
	cout << "|\n| Ingrese numero de cedula: ";
	cin >> cedula;
	return cedula;
}

// Codigo para la cola
void newQueue(Cola_Virtual *q_ptr){ //Nueva cola
	q_ptr->front = -1;
    q_ptr->rear = -1;
    q_ptr->isEmpty = true;
    q_ptr->isFull = false;
}

void enqueue(Cola_Virtual *q_ptr, Numero elem){ //Insertar un elemento en la cola
	if (!q_ptr->isFull){
		q_ptr->rear = (q_ptr->rear + 1) % QUEUEMAX;
		q_ptr->queue[q_ptr->rear] = elem;
		q_ptr->isEmpty = false;
		
		if (q_ptr->front == -1)
			q_ptr->front = q_ptr->rear;	
		q_ptr->isFull = (q_ptr->rear + 1) % QUEUEMAX == q_ptr->front;
	} else {
		cout << "La cola esta llena" << endl;
	}
}

Numero dequeue(Cola_Virtual *q_ptr){ //Eliminar elemento de la cola
	Numero element;
	if (!q_ptr->isEmpty){
		element = q_ptr->queue[q_ptr->front];
		if (q_ptr->front == q_ptr->rear){
			q_ptr->front = -1;
			q_ptr->rear = -1;
			q_ptr->isEmpty = true;
		} else {
			q_ptr->front = (q_ptr->front + 1) % QUEUEMAX;
		}
		q_ptr->isFull = false;
		return element;
	}
	return "";
}

//CODIGO PARA PILA
void newStack(Pila *st_ptr){
	st_ptr->top = -1;
}

void push(Pila *st_ptr, Digito elem){
	if (st_ptr == NULL || isFull(st_ptr))
		return;
	else{
		st_ptr->top++;
		st_ptr->stack[st_ptr->top] = elem;
		return;
	}
}

Digito pop(Pila *st_ptr){
	if (isEmpty(st_ptr))
		return '\0';
	else
		return st_ptr->stack[st_ptr->top--];
}

bool isEmpty(Pila *st_ptr){
	return (st_ptr == NULL || st_ptr->top == -1) ? true : false;
}

bool isFull(Pila *st_ptr){
	return (st_ptr == NULL || st_ptr->top == STACKMAX) ? true : false;
}

bool claveExisteEnCola(const Cola_Virtual &cola, const Numero &clave) {
	if (cola.isEmpty) {
        return false;
    }
    
    for (int i = cola.front; i != (cola.rear + 1) % QUEUEMAX; i = (i + 1) % QUEUEMAX) {
        if (cola.queue[i] == clave) {
            return true;
        }
    }
    return false;
}

Numero invertirCedula(const Numero &cedula){
	Pila pila;
	newStack(&pila);
	for(int j = 0; j < cedula.length(); j++){
		push(&pila, cedula[j]);
	}
	
	Numero cedulaInvertida = "";
	while(!isEmpty(&pila)){
		cedulaInvertida += pop(&pila);
	}
	
	return cedulaInvertida;
}

Numero generarClave(Cola_Virtual cola, Numero cedula) {    
    if (cola.isFull){
		cout << "| La cola ha llegado a su maximo. \n| ";
    	return "";
    }
    
    int len = cedula.length();
    
    for (int i = len - 3; i >= 0; i--) {
        Numero clave = cedula.substr(i, 3);
        if(!claveExisteEnCola(cola, clave)){
        	cout << "| La clave generada es: " << clave << "\n| ";
        	return clave;
		}
	}
	
	Numero cedulaInvertida = invertirCedula(cedula);
	for (int i = len - 3; i >= 0; i--) {
        Numero clave = cedulaInvertida.substr(i, 3);
        if(!claveExisteEnCola(cola, clave)){
        	cout << "| La clave generada es: " << clave << "\n| ";
        	return clave;
		}
	}
	
	cout << "| No hay posibles ternas para esta cedula." << "\n| ";
	return "";
}

void imprimir_informacion(Cola_Virtual cola, Numero taquilla[]){
	system("PAUSE");
	system("cls");
	cout << "|------- B A N C O  E L  T E S O R O -------|" << endl;
	cout << "|--------- Informacion Actualizada ---------|" << endl;
	cout << "| En taquilla 1: " << (taquilla[0].empty() ? "Vacia" : taquilla[0]) << endl;
	cout << "| En taquilla 2: " << (taquilla[1].empty() ? "Vacia" : taquilla[1]) << endl;
	cout << "| En taquilla 3: " << (taquilla[2].empty() ? "Vacia" : taquilla[2]) << endl;
	cout << "|-------------------------------------------|" << endl;
	cout << "|-------------- Cola virtual ---------------|" << endl;
	//Imprimir cola:
	if (!cola.isEmpty) {
        int num = 1;
        for (int i = cola.front; i != (cola.rear + 1) % QUEUEMAX; i = (i + 1) % QUEUEMAX) {
            cout << "| " << num++ << ". " << cola.queue[i] << endl;
        }
    } else {
        cout << "| Cola virtual vacia actualmente." << endl;
    }
    cout << "|\n| ";
    system("PAUSE");
}
