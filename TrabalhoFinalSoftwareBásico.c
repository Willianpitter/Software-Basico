#include<stdlib.h>
#include<stdio.h>


void limpacarry(unsigned char *stat){	// tranforma o 0000**1* em 0000**0*
		*stat = 0;

	}
	
void limpaoverflow(unsigned char *stat){ // tranforma o 0000*1** em 00000***
		*stat = 0;
	}

void carry(unsigned char*stat){	// tranforma o 0000**0* em 0000**1*
		*stat = 2;
		
	}
			

void overflow(unsigned char *stat){ // tranforma o 000000** em 00001***
		*stat = 4;
	}



void main(int argc,char *argv[]){

	int i=0,j=0,acc=0,pc=0,accaux=0;
	FILE *fbin;
	unsigned char byte[2],memoria[256],maux[256],aux=0;
	char stat=0;

	fbin = fopen(argv[1],"rb"); // Abre o arquivo bonario
	if(fbin == NULL){
			printf("Não foi possível abrir o arquivo\n");
			exit(0);
	}

	
	while(!feof(fbin)){	// Passa o dados do arquivo para a memoria 
		fread(&byte,1,2,fbin);	
		memoria[j] = byte[i];
		i++;
		j++;
		memoria[j] = byte[i];
		i = 0;
		j++;
	}	

	while(pc<j){
				
		aux = memoria[pc+1]; // Aux lê o número que está associoado à instrução

		switch(memoria[pc]){

			case 0: // LOAD MEMORIA
				maux[pc] = aux;
				limpaoverflow(&stat);
				limpacarry(&stat);
			break;
		
			case 1: // LOAD VALOR
				acc = aux;
				limpaoverflow(&stat);
				limpacarry(&stat);
			break;

			case 2: // STORE MEMORIA
				maux[aux] = acc;
				limpaoverflow(&stat);
				limpacarry(&stat);
			break;

			case 3:// ADD
				accaux = acc + maux[aux];
				if(accaux < 255){
					acc = accaux;
				}else{
					carry(&stat);
					acc = 255;
				}
			break;

			case 4:// SUB
				acc = acc - maux[aux];
			break;

			case 5: // MULL
				accaux = acc * maux[aux];
				if(accaux < 255){
					acc = accaux;
				}else{
					overflow(&stat);
					acc = 255;
				}
				
					
			break;
	
			case 6: // DIV
				if(maux[aux] == 0){
					printf("Impossível dividir por zero\n");
					exit(0);
				}
				acc =(int) (acc/maux[aux]);
			break;

			case 7: // INCREMENTO
				acc+=1;
				if(acc > 255){
					carry(&stat);
					acc = 255;
				
				}
				
			break;

			case 8: //DECREMENTO
				acc-=1;					
			break;
			
			case 9 : // AND LÓGICO	
				acc = acc & maux[aux];
				limpaoverflow(&stat);
				limpacarry(&stat);

			break;

			case 10: // OR LÓGICO
				acc = acc | maux[aux];
				limpaoverflow(&stat);
				limpacarry(&stat);
			break;

			case 11: //NOT LÓGICO
				acc = ~acc;
				limpaoverflow(&stat);
				limpacarry(&stat);

			break;

			case 12: // JUMP
				pc = aux-2;
				
			break;
				
			case 13: // JUMP IF 0
				if(acc == 0){
					pc = aux-2; //Este -2 eh para corrigir a linha para onde o label vai.
				

					
				}
			break;
			case 14: // JUMP IF NO 0
				if(acc != 0){
					pc = aux-2;
				}
				
			break;
			
			case 15:
				printf("\n\n\n");
				if(acc == 0){
					stat = 1;
					printf("      ---------------------------\n      |                         |\n      |         stat : 001      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
					exit(0);
				}
				if(stat == 2){
					printf("      ---------------------------\n      |                         |\n      |         stat : 010      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
					exit(0);
				}
				if(stat == 4){

					printf("      ---------------------------\n      |                         |\n      |         stat : 100      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
					exit(0);			
				}

				if(stat == 0){
					printf("      ---------------------------\n      |                         |\n      |         stat : 000      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
				exit(0);
			
				}
			break;
					

		
			}	
		pc+=2;
		}
		printf("\n\n\n");
		if(acc == 0){
			stat = 1;
			printf("      ---------------------------\n      |                         |\n      |         stat : 001      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
			exit(0);
		}
		if(stat == 2){
			printf("      ---------------------------\n      |                         |\n      |         stat : 010      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
			exit(0);
		}
		if(stat == 4){
			printf("      ---------------------------\n      |                         |\n      |         stat : 100      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
			exit(0);			
		}

		if(stat == 0){
			printf("      ---------------------------\n      |                         |\n      |         stat : 000      |       \n      |                         |\n      |      acumulador = %d     |\n      |                         |\n      --------------------------\n",acc);
			exit(0);
			
		}
}	
	


