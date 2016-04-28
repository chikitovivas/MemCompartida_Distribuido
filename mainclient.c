#include "libreria_cliente.h"





int main(int argc, char *argv[]){  
	int i, x;
	//char mensaje[100];
		//i = (int *) malloc(sizeof(int *));
		i = /*(int *)*/ 2154;
x=1;
   typedef struct ListaIdentificar {
     int inicio;
     int fin;

   }Elemento;
   
   Elemento estructura = {2016,25};
   Elemento recibido;
		//printf("conexion 1");
		conexion(argc,argv);
		create(&estructura,sizeof(Elemento));
		/*mensaje = "hola, how are you?";
		unsigned char buf;

		buf = malloc(100);
			
		memcpy(buf,&mensaje,size);*/

		create("3. Hola, niño ",strlen("3. Hola, niño "));
		create("4. Hola, patricia",strlen("4. Hola, patricia"));
		create("5. Hola, houston ",strlen("5. Hola, houston "));
		printf("\nGet %d: %s",x,(char*)get (&x));            
		//sleep(1);
		int j=0;
			while (j<10){
				create("Hola, chikito ",strlen("Hola, chikito "));
				j++;
			}
		//sleep(1);
		int c=15,m=33,t=1;
		float w=3.2;
		 //j=6.7;
		
		create((void *)&w,sizeof(float));
		printf("\nGet %d: %f",c,*((float*)get (&c)));
		create("3. Hola, niño ",strlen("3. Hola, niño "));
		create("4. Hola, patricia",strlen("4. Hola, patricia"));
		create("5. Hola, houston ",strlen("5. Hola, houston "));
		enviar("6",sizeof("6"));
		printf("\nGet %d: %d",m,*((int*)get (&m)));
		recibido = *((Elemento*) get(&t));
		printf("\nEstructura %d",recibido.inicio);
		/*create(&j,sizeof(j));*/
		


		int p=8, l=7;
		//printf("\nTamaño: %d",length_mem());
		/*char * mensaje1 = "Hola Patricia, quiero agua";
		printf("\nGet %d**: %s\n\n",p,(char *)get (&p));
		printf("\nRespuesta de update: %d",update ((void *)mensaje1,&p,strlen("Hola Patricia, quiero agua")));
		enviar("6",sizeof("6")); 

		printf("\n\nBorro el %d: %d\n",p,delete (&p));
		printf("\n\nBorro el %d: %d\n",p,delete (&p));

		printf("\n\nPut %d: %s\n",p,(char*)get (&p));
		printf("\nGet %d: %s",l,(char *)get (&l));
		enviar("6",sizeof("6")); 
/*
		

		for(j=1; j<=length_mem(); j++)
		
		printf("\n\nGet %d: %s\n",c,(char*)get (&c));
		printf("\nRespuesta de update: %d",update ("Hola Patricia, quiero agua",&c));
		printf("\n\nGet %d: %s\n",c,(char*)get (&c));

		printf("\n\nGet %d: %s\n",c,(char*)get (&c));
		printf("\nRespuesta de update: %d",update (&c,&c));
		printf("\n\nGet %d: %s\n",c,atoi(get (&c)));
j=2;
		for(j=1; j<=length_mem(); j++)
			printf("\nGet %d: %s",j,(char*)get (&j));

		printf("\n\nBorro el %d: %d\n",c,delete (&c));
		
		for(j=1; j<=length_mem(); j++)
			printf("\nGet %d: %s",j,(char*)get (&j));
int y=4;
		printf("\n\nGet %d: %s\n",y,(char*)get (&y));
		
		printf("\n\nBorro el %d: %d\n",c,delete (&y));
		for(j=1; j<=length_mem(); j++)
			printf("\nGet %d: %s",j,(char*)get (&j));

		
		//sleep(1);
		//sleep(1);
		printf("\n\n\nHola soy el get: %s\n\n\n",(char*)get (&c)); 
		delete (&c);
		printf("\n\n\nHola soy el get: %s\n\n\n",(char*)get (&c));
		printf("\n\n\nHola soy el tamaño: %d\n\n\n",length_mem());
		*/desconectar();


		/*printf("conexion 2");
		x= create("Hola, chikito puto");

 		printf("Hola  %d",x);

		create("Hola, chikito feo");
		x = length_mem();
 		printf("Hola soy el length %d",x);
		
		int c=149;
		printf("\n\n\nHola soy el put: %s\n\n\n",(char*)get (&c));

		//get ();
		create("Hola, chikito negro");
		create("Hola, chikito chocolate");
		create(&i);*/

		
		//x = length_mem();
 		//printf("Hola soy el length %d",x);
	/*	/*	
int y=4;
		printf("\n\n\nHola soy el put: %d\n\n\n",*((int*)get (&y)));
	/*/	//Recv del servidor
		//	recibir(fd);

		/* Llamada al menu*/
			//menu(fd);

		/* cerramos fd =) */
		//cerrar_archivo(fd);

}
