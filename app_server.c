// Mise en oeuvre du server
// Ensemble des bibliothèques (Headers) nécessaires pour la mise en oeuvre du programme
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<ctype.h>

// Définir un port de communication Client-Server
// de préférence qu'il soit déclaré en variable globale (ne change pas dans le programme)
// comme la valeur pi en trigonomitrie pi = 3.14
#define PORT 4444
#define SIZE 1024

int factorial(int n)
{
   int c;
   int result = 1;

   for( c = 1 ; c <= n ; c++ )
         result = result*c;

   return ( result );
}


void write_file(FILE *fp, char *buffer){
  int n, res;
  res = atoi(buffer);
  res = factorial(res);
  fprintf(fp, "%d", res);
  bzero(buffer, SIZE);
}

void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("Erreur");
      exit(1);
    }
    bzero(data, SIZE);
  }
}

char* GetFilenameFromRequest(char* request){

	char *file_name = strchr(request, ' ');
	return file_name + 1;
}
int main(){

		// Phase déclarative
		// Déclaration et initialisation de la socket côté Server
		int sockfd;
		// Socket associé au client (elle réalise la liaison d'échange entre le Client et le Server  à
		//partir de la sochet Server)
		int newSocket; // (Socket côté server, structure de la socket du client, taille de la structure)

		// Décrire la structure du client et du server
		struct sockaddr_in serverAddr, newAddr;

		// Initialisation d'un Buffer
    char buffer[1024];
		FILE *fp;
  	char *filename = "reponse.txt";
		socklen_t addr_size;
    int num;
		// Phase de Création
		// Créer et construire la socket côté Server "sockfd"
		// On a besoin de 3 arguments
		// AF_INET : Domaine d'@ IPV4 ou IPV6
		// SOCK_STREAM : Configurer en type "flux de données" correspondant au TCP (Retour d'information)
		// "0" : Type de protocole (UDP / TCP)
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		printf("[+] Server Socket Created Successfully\n");

		// Phase de Paramétrage
		// Consiste à définir les différents paramètre de la communication que doit contenir la socket "sockfd"
		// ANYDDR_ANY : Any adress du réseau Server
		// Port de communication "PORT" faire appel à la fonction htons

		// Il se trouve des fois qu'il faille initialiser la structure du server (idem pour celle du client)
		// appel d'une fonction "memset" pour juste des précautions à prendre
		memset(&serverAddr, '\0', sizeof(serverAddr));

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT); // conversion en octets
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // adresse du server

		// Phase de liaison avec le port de communication Client-Server "PORT" Binding
		// Appel de la fonction bind()
		bind(sockfd,(struct sockaddr *) &serverAddr , sizeof(serverAddr));
		printf("[+] Bind to Port Number %d.\n", PORT);

		// Mise en écoute du server par appel de la fonction "listen()"
		// Boucle infinie en attente d'un client
		// L'attente est limité dans le cas du TCP/IP à un maximum de 5 clients
		listen(sockfd, 5);
		printf("\n[+] Server en attente du Client....\n");
		// pour que le server collabore avec le Client, il doit déterminer une nouvelle
		// socket dite de "communication avec le Client" en faisant appel à la fonction "accept()"
		//clilen = sizeof(cli_addr);
		newSocket = accept(sockfd , (struct sockaddr *) &newAddr , &addr_size);

		// Si le Server accepte la communication
		// Il va faire appel à la fonction de lecture "read()"
		read(newSocket, buffer, 1024);
		printf("\n (Client) message : %s\n",buffer);

		printf("\n Réponse du Server: \n");

		// // Chaine de type pointeur, taille, flot de données pointe vers le fichier
		// fgets(buffer, 1024, stdin);
		// // Ecrire le message en spécifiant le nombre d'octets dans le buffer "write()"
		// write(newSocket, buffer, strlen(buffer));
    fp = fopen(filename, "w");
    write_file(fp, buffer);//calculer factoriel et stocker dans file reponse.txt
    printf("filename %s\n",filename );

    write(newSocket, "reponse.txt" , 12);
    // send_file(fp, sockfd);
	  // printf("[+]File data sent successfully.\n");
    //
		// printf("[+]Closing the connection.\n");

  	printf("[+]Ok, I am going to close the connection.\n");
  	printf("[+]SEE YOU.\n");
return 0;
}
