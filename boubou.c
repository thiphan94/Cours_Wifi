#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<pthread.h>

void *RTS();
unsigned int get_crc(unsigned int data[], int taille);
void *CTS(void *x);

//*******************************CRC*************************************

unsigned int get_crc(unsigned int data[], int taille){
  int i,j;
     
      unsigned int poly_gen = 0xEDB88320;
      unsigned int crc=0xFFFFFFFF;

      for ( j=0 ; j<taille ; j++)
    {
    crc = crc ^ data[j];
    for ( i=8 ; i>0 ; i--){

      if (crc & 1)
        {
        crc = crc ^ poly_gen;
        crc >>= 1;
      }

      else crc >>= 1;
    }
      }
     
      return(crc);
}

//*************************************RTS******************

void *RTS(){
  	int T=17;
  	unsigned int tab[T];
  tab[0]=0x00;
  tab[1]=0x01;
  tab[2]=0x1011;
  tab[3]=0x0;
  tab[4]=0x0;
  tab[5]=0x1;
  tab[6]=0x1;
  tab[7]=0x1;
  tab[8]=0x1;
  tab[9]=0x1;
  tab[10]=0x1;
//le champ duration
 //unsigned int duration = (unsigned int)(8*20)/(54*(pow(10,6)));
 unsigned int duration = 5+8*(2+2+6+6+4);
  tab[11]=duration;
//adresse 1
  tab[12]=0x111120;
  tab[13]=0x510205;
//adresse 2
  tab[14]=0x222200;
  tab[15]=0x510201;
//FSC
  tab[16]=get_crc(tab,16);
 	printf("\n%x\n",tab[1]);
 	printf("\n%x\n",duration);
 	
    printf("trame RTS : ");
    for(int i = 0 ; i<=16 ; i++)
    {
        printf("%x | ",tab[i]);
    }
    unsigned int result_crc= get_crc(tab,17);
    printf("\n le CRC du RTS est : %x\n",result_crc);


    if(result_crc == 0){

      	pthread_t thread_CTS;
      	pthread_create(&thread_CTS,NULL,&RTS,NULL);
      	pthread_join(thread_CTS,NULL);
     }
}


//*********************************CTS**************************/

void *CTS(void *x){
  int T=15;
  int tab [T];
  tab[0]=0;
  tab[1]=01;
  tab[2]=1011;
  tab[3]=1;
  tab[4]=0;
  tab[5]=1;
  tab[6]=1;
  tab[7]=0;
  tab[8]=1;
  tab[9]=1;
  tab[10]=0;
  tab[11]=0x1020;
  tab[12]=0x1020F10201;
  tab[13]=get_crc(tab,13);

 
      printf("trame CTS : ");
    for(int i = 0 ; i<14 ; i++)
    {
        printf("%x",tab[i]);
    }
        unsigned long result_crc= get_crc(tab,14);


    		printf("\n CRC du CTS est : %lx\n",result_crc);

 
}
//**********************************ACK**************************		

/*void ACK(){
  	int T=14;
 	int tab [T];
  tab[0]=0;
  tab[1]=01;
  tab[2]=1011;
  tab[3]=1;
  tab[4]=0;
  tab[5]=1;
  tab[6]=1;
  tab[7]=0;
  tab[8]=1;
  tab[9]=1;
  tab[10]=0;
  tab[11]=0x1020;
  tab[12]=0x1020F1020135;
  tab[13]=get_crc(tab,13);
 

  		printf("trame ACK : ");

  for(int i = 0 ; i<14 ; i++)
    {
      printf("%x",tab[i]);
    }

  unsigned long result_crc= get_crc(tab,14);
 	 result_crc = get_crc(tab,14);
 	 printf("\n crc du ACK : %lx\n",result_crc);
}*/


int main(){
 
  // déclaration des threads

  	pthread_t thread_RTS;
  	pthread_t thread_CTS;
  	//pthread_t thread_ACK;
 

  //création des threads

  	pthread_create(&thread_RTS,NULL,&RTS,NULL);
  	pthread_join (thread_RTS, NULL);
  	pthread_create(&thread_CTS,NULL,&CTS,NULL);
  	pthread_join(thread_CTS,NULL);
  	//pthread_create(&thread_ACK,NULL,ACK,NULL);
  	//pthread_join(thread_ACK,NULL);
return 0;
 

}