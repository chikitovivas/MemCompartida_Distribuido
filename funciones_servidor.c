#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

#include "funciones.h"






/* inserción en una lista vacía */
int ins_en_lista_vacia (Lista * lista, void *buf, int n){
  Elemento *nuevo_elemento;
  
  if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;
  if ((nuevo_elemento->buf = (void *) malloc (n))
      == NULL)
    return -1;
  
  memcpy(nuevo_elemento->buf, buf, n);
  
  nuevo_elemento->siguiente = NULL;
  
  pthread_mutex_lock(&mutexG);
  lista->inicio = nuevo_elemento;
  lista->fin = nuevo_elemento;
  lista->tamano++;
  pthread_mutex_unlock(&mutexG);

  return 0;
}
/*inserción al final de la lista */
int ins_fin_lista (Lista * lista, Elemento * actual, void *buf, int n){
  Elemento *nuevo_elemento;
  if ((nuevo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;
  if ((nuevo_elemento->buf = (void *) malloc (n))
      == NULL)
    return -1;

  memcpy(nuevo_elemento->buf, buf, n);
  
  nuevo_elemento->siguiente = NULL;
  pthread_mutex_lock(&mutexG);  
  //actual->siguiente = nuevo_elemento;
  lista->fin->siguiente = nuevo_elemento;
  lista->fin = nuevo_elemento;

  lista->tamano++;
  pthread_mutex_unlock(&mutexG);
  return 0;
}

void inicializacion (Lista * lista){
	
  lista->inicio = NULL;
  lista->fin = NULL;
  lista->tamano = 0;

}

void imprimir(Lista *lista){
	Elemento *actual;

	actual = lista->inicio;

	for(int i = 1 ; i <= lista->tamano ; i++){
		printf("Indice #%d --> %s\n",i,(char *)actual->buf);
		actual = actual->siguiente;
	}
}
 

/*
 * Esto manejara el hilo del cliente
 * */
void *connection_handler_UDP(void *socket_desc)
{
    //Obtener el descriptor del socket
    int sock = *(int*)socket_desc;
    int read_size,ch, indice,n;
    char *message , client_message[2000], *cliente;
    char *opcion;
    
    
    FILE *fp;
    
    cliente = (char*) malloc(sizeof(char) * 100);
  
    //Recibir algunos mensajes del cliente
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {send(sock , "1" , strlen("1"),0); //Envio de acuse
		
      if(client_message[0] == '1')                 //Si la opcion del cliente es 1, quiere crear
      {		 
			 void *guardar;

			 char mensajito[1000] = {0};

			 int error;
			 

			 n=recv(sock , mensajito , 1000, 0); //Texto a guardar en la lista  

		 	 error = send(sock , (void *)"1" ,strlen("1"),0); //Envio de acuse
			 
			 if (error < 0)
			  perror("ERROR sending to socket");

			 guardar = (void *) malloc(n);

			 memcpy(guardar,mensajito,n);
			 
			 if(lista->tamano == 0){
				if(ins_en_lista_vacia (lista, guardar,n) == 0){
					message = "1";//Boolean al cliente de que todo salio bien
					 pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->inicio;//Leer
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
					
				}else{
					message = "-1";//Boolean al cliente de que todo salio mal
				}
			 }else{
				 					 pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->fin;//Leer
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
				if(ins_fin_lista (lista, actual, guardar,n) == 0){
					message = "1";//Boolean al cliente de que todo salio bien
				}else{
					message = "-1";//Boolean al cliente de que todo salio mal
				}			
			 }
							   
			 send(sock , message , strlen(message),0); //Envio del boolean  
             //free(mensajito);  
                 

      }else if(client_message[0] == '2')           //Consultar segmentos     
      {
			 memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
			 recv(sock , client_message , 2000 , 0);   //Indice que se quiere consultar  
			 send(sock , "1" , strlen("1"),0); //Envio de acuse
			 
			 if(*((int *)client_message) >= 1 && *((int *)client_message) <= lista->tamano ){
				  pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->inicio;     //Actual, ahora sera el principio de la lista
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
				
			 
				 for(int i = 1 ; i < *((int *)client_message) ; i++){	//Buscamos el indice de la lista       
					 actual = actual->siguiente;	         
				 }

				 send(sock , actual->buf , 100,0); //Envio de la informacion 
			 }else{
				send(sock , "-1" , sizeof("-1"),0); //Envio de la informacion
			 }    
         
      }else if(client_message[0] == '3')           //Actualizar segmentos  En prueba
      {       	
         char mensajito[1000] = {0};
         int n;
         memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
         recv(sock , client_message , 2000 , 0);   //Indice que se quiere actualizar  
         send(sock , "1" , strlen("1"),0); //Envio de acuse
         
         if(*((int *)client_message) >= 1 && *((int *)client_message) <= lista->tamano ){
			if (lectores == 1)
			  pthread_mutex_lock(&mutexG);
			  
			 pthread_mutex_unlock(&mlectores);
					actual = lista->inicio;                   //Actual, ahora sera el principio de la lista
			 pthread_mutex_lock(&mlectores);
			 lectores--;
			 
			 if (lectores == 0)
			  pthread_mutex_unlock(&mutexG);
			  
			 pthread_mutex_unlock(&mlectores);				

	        pthread_mutex_lock(&actual_);
	         for(int i = 1 ; i < *((int *)client_message) ; i++){	//Buscamos el indice de la lista       
	            actual = actual->siguiente;
	         }
	         pthread_mutex_unlock(&actual_);
			 memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje

	         n = recv(sock , mensajito ,  1000 , 0);   //Lo que se quiere actualizar
	         send(sock , "1" , strlen("1"),0); //Envio de acuse

			    pthread_mutex_lock(&actual_);
	         actual->buf =  (void *) malloc(n);
	         memcpy(actual->buf, mensajito, n);

	         pthread_mutex_unlock(&actual_);
	         send(sock , "1" , sizeof("1"),0); //Envio de la informacion
	      }else{
	         send(sock , "-1" , sizeof("-1"),0); //Envio de la informacion
	      }

      }else if(client_message[0] == '4')           //Eliminar segmentos
      {      
    
         int num=0;
        memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
		  recv(sock , client_message , 2000 , 0);   //Indice
		  send(sock , "1" , sizeof("1"),0); //Envio de acuse
		  
		  num = *((int *)client_message);   // Recibe Indice que se quiere eliminar


		 if (lista->tamano <= 0 || num < 1 || num > lista->tamano)
		    send(sock , "-1" , sizeof("-1"),0); //Envio de -1 
				 

			 if (num == 1){ 
				 pthread_mutex_lock(&mutexG);
				  lista->inicio = lista->inicio->siguiente;				 
				 if (lista->tamano == 1)
				    lista->fin = NULL;

				  lista->tamano--;
				  pthread_mutex_unlock(&mutexG);
			  	  send(sock , "1" , sizeof("1"),0); //Envio de 1
			  } else { 
				  pthread_mutex_lock(&mutexG);	
				  Elemento *actual;
				  actual = lista->inicio;

				  for (int j = 1; j < num-1; j++)
				    actual = actual->siguiente;


				  actual->siguiente = actual->siguiente->siguiente;

				  if(actual->siguiente == NULL)
						lista->fin = actual;
 
				  lista->tamano--;
				  pthread_mutex_unlock(&mutexG);
				  send(sock , "1" , sizeof("1"),0); //Envio de 1

			}

      }else if(client_message[0] == '5')           //Consulta de tamano de la lista
	  {

		 send(sock , &lista->tamano , sizeof(lista->tamano),0); //Envio de 1

	  }else if(client_message[0] == '6')
	  {		

			imprimir(lista);
	  }

		
		//limpiar el buffer del cliente
		memset(client_message, 0, 2000);

    }
     
    if(read_size == 0)
    {
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv fallo");
    }
         
    return 0;
} 
/*
 * TCP
 * */
void *connection_handler_TCP(void *socket_desc)
{
    //Obtener el descriptor del socket
    int sock = *(int*)socket_desc;
    int read_size,ch, indice,n;
    char *message , client_message[2000], *cliente;
    char *opcion;
    
    FILE *fp;
    
    cliente = (char*) malloc(sizeof(char) * 100);
  
     //Recibir algunos mensajes del cliente
    while( (read_size = read(sock , client_message , 2000 )) > 0 )
    {write(sock , "1" , strlen("1")); //Envio de acuse
		
      if(client_message[0] == '1')                 //Si la opcion del cliente es 1, quiere crear
      {		 
			 void *guardar;
			 char mensajito[1000] = {0};

			 int error;
			 
			 
			 n=read(sock , mensajito , 1000); //Texto a guardar en la lista  

		 	 error = write(sock , "1" ,strlen("1")); //Envio de acuse
			 
			 if (error < 0)
			  perror("ERROR sending to socket");

			 guardar = (void *) malloc(n);

			 memcpy(guardar,mensajito, n);

			 if(lista->tamano == 0){

				if(ins_en_lista_vacia (lista, guardar,n) == 0){
					message = "1";//Boolean al cliente de que todo salio bien
					 pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->inicio;//Leer
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
					
				}else{
					message = "-1";//Boolean al cliente de que todo salio mal
				}
			 }else{
				 					 pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->fin;//Leer
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
				if(ins_fin_lista (lista, actual, guardar,n) == 0){
					message = "1";//Boolean al cliente de que todo salio bien
				}else{
					message = "-1";//Boolean al cliente de que todo salio mal
				}			
			 }
							   
			 write(sock , message , strlen(message)); //Envio del boolean  
                 

      }else if(client_message[0] == '2')           //Consultar segmentos     
      {
			 memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
			 read(sock , client_message , 2000);   //Indice que se quiere consultar  
			 write(sock , "1" , strlen("1")); //Envio de acuse
			 
			 if(*((int *)client_message) >= 1 && *((int *)client_message) <= lista->tamano ){
				  pthread_mutex_lock(&mlectores);
					 lectores++;
					 
					 if (lectores == 1)
					  pthread_mutex_lock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
							actual = lista->inicio;     //Actual, ahora sera el principio de la lista
					 pthread_mutex_lock(&mlectores);
					 lectores--;
					 
					 if (lectores == 0)
					  pthread_mutex_unlock(&mutexG);
					  
					 pthread_mutex_unlock(&mlectores);
				
			 
				 for(int i = 1 ; i < *((int *)client_message) ; i++){	//Buscamos el indice de la lista       
					 actual = actual->siguiente;	         
				 }

				 write(sock , actual->buf , 100); //Envio de la informacion 
			 }else{
				write(sock , "-1" , sizeof("-1")); //Envio de la informacion
			 }    
         
      }else if(client_message[0] == '3')           //Actualizar segmentos  En prueba
      {       	
         char mensajito[1000] = {0};
         int n;
         memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
         read(sock , client_message , 2000);   //Indice que se quiere actualizar  
         write(sock , "1" , strlen("1")); //Envio de acuse
         
         if(*((int *)client_message) >= 1 && *((int *)client_message) <= lista->tamano ){
			if (lectores == 1)
			  pthread_mutex_lock(&mutexG);
			  
			 pthread_mutex_unlock(&mlectores);
					actual = lista->inicio;                   //Actual, ahora sera el principio de la lista
			 pthread_mutex_lock(&mlectores);
			 lectores--;
			 
			 if (lectores == 0)
			  pthread_mutex_unlock(&mutexG);
			  
			 pthread_mutex_unlock(&mlectores);				
            
	        pthread_mutex_lock(&actual_);
	         for(int i = 1 ; i < *((int *)client_message) ; i++){	//Buscamos el indice de la lista       
	            //anterior = actual;
	            actual = actual->siguiente;
	         }
	         pthread_mutex_unlock(&actual_);
			 memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje

	         n = read(sock , mensajito ,  1000);   //Lo que se quiere actualizar
	         write(sock , "1" , strlen("1")); //Envio de acuse

			    pthread_mutex_lock(&actual_);
	         actual->buf =  (void *) malloc(n);
	         memcpy(actual->buf, mensajito, n);

	         pthread_mutex_unlock(&actual_);
	         write(sock , "1" , sizeof("1")); //Envio de la informacion
	      }else{
	         write(sock , "-1" , sizeof("-1")); //Envio de la informacion
	      }

      }else if(client_message[0] == '4')           //Eliminar segmentos
      {      
   
         int num=0;
        memset(client_message, 0, 2000);          //Limpieza de buffer del mensaje
		  read(sock , client_message , 2000 );   //Indice
		  write(sock , "1" , sizeof("1")); //Envio de acuse
		  
		  num = *((int *)client_message);   // Recibe Indice que se quiere eliminar


		 if (lista->tamano <= 0 || num < 1 || num > lista->tamano)
		    write(sock , "-1" , sizeof("-1")); //Envio de -1 
				 

			 if (num == 1){ 
				 pthread_mutex_lock(&mutexG);
				  lista->inicio = lista->inicio->siguiente;				 
				 if (lista->tamano == 1)
				    lista->fin = NULL;

				  lista->tamano--;
				  pthread_mutex_unlock(&mutexG);
			  	  write(sock , "1" , sizeof("1")); //Envio de 1
			  } else { 
				  pthread_mutex_lock(&mutexG);	
				  Elemento *actual;
				  actual = lista->inicio;

				  for (int j = 1; j < num-1; j++)
				    actual = actual->siguiente;


				  actual->siguiente = actual->siguiente->siguiente;

				  if(actual->siguiente == NULL)
						lista->fin = actual;
 
				  lista->tamano--;
				  pthread_mutex_unlock(&mutexG);
				  write(sock , "1" , sizeof("1")); //Envio de 1

			}

      }else if(client_message[0] == '5')           //Consulta de tamano de la lista
	  {
		 write(sock , &lista->tamano , sizeof(lista->tamano)); //Envio de 1

	  }else if(client_message[0] == '6')
	  {		
			imprimir(lista);
	  }

		
		//limpiar el buffer del cliente
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0)
    {
        puts("Cliente desconectado");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv fallo");
    }
         
    return 0;
} 
