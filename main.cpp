#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define QUEUEMAX 10
#define STACKMAX 10

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
				numero = generarClave(cola, pedir_cedula());
				if (numero != "")
					enqueue(&cola, numero);
				system("PAUSE");
				break;
			case '1':
			case '2':
			case '3':
				numero = dequeue(&cola);
				if (numero != "")
					cout << "|\n| Pase a la TAQUILLA " << resp << ": " << numero;
				else
					cout << "|\n| La cola esta vacia ";
				cout <<"\n| ";
				system("PAUSE");
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
	cout << "|\n| Ingrese numero de cedula: ";
	cin >> cedula;
	return cedula;
}


// C�digo para la cola
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
		q_ptr->isEmpty = false;
		
		if (q_ptr->front == -1)
			q_ptr->front = q_ptr->rear;	
		if ((q_ptr->rear + 1) % QUEUEMAX == q_ptr->front)
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

Numero generarClave(Cola_Virtual cola, Numero cedula) {
    Numero clave;
    int len = cedula.length();
    bool clave_existente = false;
    
    if (cola.isFull){
		cout << "| La cola ha llegado a su maximo. \n| ";
    	return "";
    }
    for (int i = len - 3; i >= 0; i--) {
        // Genera una nueva clave con los �ltimos 3 d�gitos
        clave = cedula.substr(i, 3);
        clave_existente = false;
        // Verifica si la clave generada ya existe en la cola
        if (!cola.isEmpty){
	        for (int j = 0; j < QUEUEMAX; j++) {
	            if (cola.queue[j] == clave) {
	                clave_existente = true;
	                break;
	            }
	        }
	        
	        if (!clave_existente)
	        	break;
		} else {
			break;
		}
    }
    	if (clave_existente){
        	Pila pila;
        	newStack(&pila);
        	
        	for(int j = 0; j < len; j++){
        		push(&pila, cedula[j]);
			}
			
			cedula = "";
			while(!isEmpty(&pila)){
				cedula = cedula + pop(&pila);
			}
			
			for (int i = len - 3; i >= 0; i--) {
				clave = cedula.substr(i, 3);
	            clave_existente = false;
	            for (int j = 0; j < QUEUEMAX; j++) {
	                if (cola.queue[j] == clave) {
	                    clave_existente = true;
	                    break;
	                }
	            }
	            
	            if (!clave_existente)
	                break;
			}
		}
		
		if (clave_existente){
			clave = "";
			cout << "| No hay posibles ternas para esta cedula." << "\n| ";
		} else
			cout << "| La clave generada es: " << clave << "\n| ";
			
    return clave;
}
