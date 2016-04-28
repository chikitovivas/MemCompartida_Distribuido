 typedef struct ElementoLista {
  void                *buf;
  struct ElementoLista *siguiente;
}Elemento;

typedef struct ListaIdentificar {
  Elemento *inicio;
  Elemento *fin;
  int tamano;
}Lista;

   Lista *lista ;
   Elemento *actual;
   Elemento *anterior;
   
  pthread_mutex_t mutexG; /* controlar el acceso a dato */
 pthread_mutex_t mlectores; /* controla acceso n_lectores */
 pthread_mutex_t actual_;
 int lectores;
 
 
//the thread function
void *connection_handler_TCP(void *);

void *connection_handler_UDP(void *);

void inicializacion(Lista * lista);
