/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

#include "funciones.h"


 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , flag=1,c;
    struct sockaddr_in server , client;
    char protocolo[3];
    

    
    lista = (Lista *)malloc(sizeof(Lista));
    actual = (Elemento *)malloc(sizeof(Elemento));
    anterior = (Elemento *)malloc(sizeof(Elemento));
    //mensaje = (void*) malloc(sizeof(void)*100);
    inicializacion(lista);
    pthread_mutex_init(&mutexG, NULL);
    pthread_mutex_init(&mutexG, NULL);
    pthread_mutex_init(&mlectores, NULL);
    pthread_mutex_init(&actual_, NULL);
    lectores = 0;
    
    //printf("puts: %s\n",argv[1]);
    if(argc != 3)
    {
	  printf("\n\tEjecute: ./nombre PROTOCOLO PUERTO");
	  printf("\n\t\tEj: ./server TCP 7000");
	  printf("\n\t\tEj: ./server UDP 7300\n\n");
	  exit(-1);

	}
	if(strcmp(argv[1],"TCP") != 0 && strcmp(argv[1],"UDP") != 0)
	{	  
	  printf("\n\tIngrese protocolo valido>\n");
	  printf("\n\tEjecute: ./nombre PROTOCOLO PUERTO");
	  printf("\n\t\tEj: ./server TCP 7000");
	  printf("\n\t\tEj: ./server UDP 7300\n\n");
	  exit(-1);

	}	
	
	if (atoi(argv[2])==0){
	  printf("\n\tIngrese puerto valido>\n");
	  printf("\n\tEjecute: ./nombre PROTOCOLO PUERTO");
	  printf("\n\t\tEj: ./server TCP 7000");
	  printf("\n\t\tEj: ./server UDP 7300\n\n");
	  exit(-1);
	}

    //Creacion de socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("No se pudo crear el socket");
    }
    puts("Socket creado");
     
    //Preparando la estructura sockaddr_in 
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( atoi(argv[2]) );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("Bind Hecho");
     
    //Listen
    listen(socket_desc , 3);
         

    //Aceptar una connexion entrante
    	if(strcmp(argv[1],"TCP") == 0 )
		{
			puts("Estamos trabajando con TCP, esperando por conexiones entrantes...");
		}else{
			puts("Estamos trabajando con UDP, esperando por conexiones entrantes...");
		}
    
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Conexion aceptada");
		//printf("id: %d\n",(int)thread_id);
		if(strcmp(argv[1],"TCP") == 0 )
		{
			if( pthread_create( &thread_id , NULL ,  connection_handler_TCP , (void*) &client_sock) < 0)
			{
				perror("No se pudo crear el Hilo");
				return 1;
			}
		}else{		
			if( pthread_create( &thread_id , NULL ,  connection_handler_UDP , (void*) &client_sock) < 0)
			{
				perror("No se pudo crear el Hilo");
				return 1;
			}
		}
         
        //Now join the thread , so that we dont terminate before the thread
        pthread_join( thread_id , NULL);
        puts("Manejador asignado");
    }
     
    if (client_sock < 0)
    {
        perror("aceptacion fallo");
        return 1;
    }
    
    pthread_mutex_destroy(&mutexG);
    return 0;
}
 

