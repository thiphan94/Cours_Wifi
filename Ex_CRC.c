#include<stdio.h>
#include<stdlib.h>


// Déclaration du prototype de la fonction
unsigned int get_crc(unsigned int Trame_RTS[], int taille);


//*******************************CRC*************************************

unsigned int get_crc(unsigned int Trame_RTS[], int taille){

  int i,j; // variables intermédiaires pour balayer la totalité du tableau (tous les octets) et l'octet
     
     // unsigned int poly_gen = 0xA001; // Initialisation du polynôme générateur sur 2 octets
      
      unsigned int poly_gen = 0xEDB88320;
      
      unsigned int crc=0xFFFFFFFF; // Initialiser le variable du CRC à calculer

	// passage d'octet à octet
      for ( j=0 ; j<taille ; j++) // Balayer les octets un à un jusqu'à atteindre la fin de la trame RTS
    {
    crc = crc ^ Trame_RTS[j]; // faire un OU exclusif (Première division) qui correspondrait automatiquement
    					//   au minimum à un décalage à droite

	// Boucle pour un octet présenté
    for ( i=8 ; i>0 ; i--){	// data[j=0]=0xAA = 10101010
							//					87654321
      if (crc & 0x01) // masque : retenue
        {
        crc = crc ^ poly_gen; // Appliquer le OU exclusif
        crc >>= 1;
      }

      else crc >>= 1; // si pas retenue je décale (0+0)
    }
      }
     
      return(crc);
}

int main(){

printf("\n donner la trame \n");

unsigned int tableau[7]= {0xAACF,0x1000,0x34AA,0xFFFF,0x4566,0xF12F,0xAAA8}; // Trame : AACF100034A4FFFF4566FA12FFFF8CRC unsigned int CRC_resul;
int i;
int taille1 = 7;

/*	for(i=0;i<taille1;i++){
	
	printf("\n");
	scanf("%ud",&tableau[i]);
	printf("\n");

	}
*/	

unsigned int CRC_resul = get_crc(tableau,taille1);
printf("La valeur du CRC pour la trame TRTS est de : 0x%x\n\n",CRC_resul); 

}