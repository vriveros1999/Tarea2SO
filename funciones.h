#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>         
#include <fcntl.h>            
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

typedef struct {
    int pos;
    int turno;
}Jugador;

int inicializar_posiciones(){
    return 1;
}

void string(int n1, int n2, int n3, int n4, int pos, char *str){
	int resto;
	for(int x=0; x<5; x++){
		if (n1==pos){
			strcat(str,"1");
			n1=0;
		}
		else{
			if(n2==pos){
			    strcat(str,"2");
		      	n2=0;
		    }
		    else{
		    	if(n3==pos){
			        strcat(str,"3");
			        n3=0;
			    }
			     else{
			     	if(n4==pos){
			             strcat(str,"4");
			             n4=0;
		            }
			     }
		    }
		}
	}
	resto=4-strlen(str);
	while (resto>0){
		strcat(str," ");
		resto--;
	}
}

void concateno2(char *tablero,int n,int n1, int n2, int n3, int n4, char *str, int invertido){
	if(n==1){
		int pos=20;
		string(n1,n2,n3,n4,pos,str);
		strcat(tablero,"|");
		strcat(tablero,str);
		strcat(tablero,"|");
		strcpy(str,"");
		strcat(tablero,"\n|    |");
		strcat(tablero,"\n|____|");
	}
	else{
		int pos=10;
		strcat(tablero,"                                        ");
		string(n1,n2,n3,n4,pos,str);
		strcat(tablero,"|");
		strcat(tablero,str);
		strcat(tablero,"|");
		strcpy(str,""); 
		strcat(tablero,"\n                                        |    |");
		strcat(tablero,"\n _______________________________________|____|");
	}
}

void concateno(char *tablero,int n,int n1,int n2,int n3,int n4, char *str, int invertido){
	int pos=1;
	int largo=9;
	char *intermedio=(char *)malloc(sizeof(char)*200);
	if(n==1){
		strcat(tablero,"\n ____________________________________________\n");
		if(invertido==1){
			if(n1<10){
				n1=10-n1;
			}
			else{
				n1=0;
			}
			if(n2<10){
				n2=10-n2;
			}
			else{
				n2=0;
			}
			if(n3<10){
				n3=10-n3;
			}
			else{
				n3=0;
			}
			if(n4<10){
				n4=10-n4;
			}
			else{
				n4=0;
			}
		}
		if(invertido==0){
			if(n1>=21){
				n1=n1-20;
			}
			else{
			    n1=0;
		    }
		    if(n2>=21){
			    n2=n2-20;
		    }
		    else{
		   	    n2=0;
		    }
		    if(n3>=21){
			    n3=n3-20;
		    }
		    else{
			    n3=0;
		    }
		    if(n4>=21){
			    n4=n4-20;
		    }
		    else{
			    n4=0;
		    }

		}
	}
	if(n==2){
		strcat(tablero,"_______________________________________ \n");
		if(invertido==1){
			if(n1>10 || n1<19){
				n1=n1-10;
			}
			else{
				n1=0;
			}
			if(n2>10 || n2<19){
				n2=n2-10;
			}
			else{
				n2=0;
			}
			if(n3>10 || n3<19){
				n3=n3-10;
			}
			else{
				n3=0;
			}
			if(n4>10 || n4<19){
				n4=n4-10;
			}
			else{
				n4=0;
			}
		}
		if(invertido==0){

		    if(n1>10 || n1<19){
			    n1=20-n1;
		    }
		    else{
			    n1=0;
		    }
		    if(n1>10 || n1<19){
			    n2=20-n2;
		    }
		    else{
			    n2=0;
		    }
		    if(n1>10 || n1<19){
			    n3=20-n3;
		    }
		    else{
			    n3=0;
		    }
		    if(n1>10 || n1<19){
			    n4=20-n4;
		    }
		    else{
			    n4=0;
		    }
		}
		
	}
	if(n==3){
		if (invertido==1){
			strcat(tablero,"\n");
			if(n1>20 && n1<30){
			    n1=30-n1;
		    }
		    else{
		    	n1=0;
		    }
		    if(n2>20 && n2<30){
			    n2=30-n2;
		    }
		    else{
		    	n2=0;
		    }
		    if(n3>20 && n3<30){
			    n3=30-n3;
		    }
		    else{
		    	n3=0;
		    }
		    if(n4>20 && n4<30){
			    n4=30-n4;
		    }
		    else{
		    	n4=0;
		    }
		}
		if(invertido==0){
			strcat(tablero,"\n");

		}


	}
	while (largo>0){
		string(n1,n2,n3,n4,pos,str);
		strcat(intermedio,"|");
		strcat(intermedio,str);
		strcpy(str,"");
		largo--;
		pos++;
	}
	strcat(intermedio,"|");
	largo=9;
	strcat(intermedio,"\n");
	while (largo>0){
		if (n==3){
			if(largo==3 || largo==5 || largo==7){
				if(invertido==1){
					strcat(intermedio,"| ?? ");

				}
				if(invertido==0){
					strcat(intermedio,"|  ? ");

				}
			}
			if(largo==9){
				if(invertido==1){
					strcat(intermedio,"| FIN");

				}
				if(invertido==0){
					strcat(intermedio,"|IN >");

				}

			}
			if(largo==1){
				if(invertido==1){
					strcat(intermedio,"|  < ");
				}
				if(invertido==0){
					strcat(intermedio,"|  > ");

				}
			}
			if(largo == 2 || largo == 4 || largo == 6 || largo == 8 )
				strcat(intermedio,"|    ");
		}
		if (n==2){
			if(largo==7){
				if(invertido==1){
					strcat(intermedio,"| ?  ");

				}
				if(invertido==0){
					strcat(intermedio,"| ?? ");

				}
			}
			if(largo==3 || largo==5){
				if(invertido==1){
					strcat(intermedio,"| ?? ");

				}
				if(invertido==0){
					strcat(intermedio,"|  ? ");
				}
			}
			if (largo== 9){
				if(invertido==1){
					strcat(intermedio,"|  > ");

				}
				if(invertido==0){
					strcat(intermedio,"|  ^ ");

				}
			}
			if (largo== 1){
				if(invertido==1){
					strcat(intermedio,"|  v ");

				}
				if (invertido==0){
					strcat(intermedio,"|  < ");

				}
			}
			if( largo==8 || largo==6 || largo==4 || largo==2){
				strcat(intermedio,"|    ");
			}
		}
		if (n==1){
			if(largo==3 || largo==5 || largo==7){
				if(invertido==1){
					strcat(intermedio,"| ?  ");

				}
				if(invertido==0){
					strcat(intermedio,"| ?? ");

				}

			}
			if(largo==2 || largo==4 || largo==6 || largo==8){
				if (invertido==1){
					strcat(intermedio,"| ?? ");

				}
				if(invertido==0){
					strcat(intermedio,"|  ? ");

				}
			}
			if(largo==9){
				if(invertido==1){
					strcat(intermedio,"|  v ");

				}
				if(invertido==0){
					strcat(intermedio,"|  > ");

				}

			}
			if(largo==1){
				if(invertido==1){
					strcat(intermedio,"| IN ");

				}
				if(invertido==0){
					strcat(intermedio,"| FIN");

				}
			}
		}
		largo--;
	}
	largo=9;
	strcat(intermedio,"|\n");
	while(largo>0){
		strcat(intermedio,"|____");
		largo--;
	}
	strcat(intermedio,"|\n");
	strcat(tablero,intermedio);
	free(intermedio);
}

void tablero(int n1,int n2, int n3, int n4, int invertido){
    char *str=(char *)malloc(sizeof(char)*6);
	char *tablero=(char *)malloc(sizeof(char)*700);
	concateno(tablero,1,n1,n2,n3,n4,str,invertido);
	concateno2(tablero,1,n1,n2,n3,n4,str,invertido);
	concateno(tablero,2,n1,n2,n3,n4,str,invertido);
	concateno2(tablero,2,n1,n2,n3,n4,str,invertido);
	concateno(tablero,3,n1,n2,n3,n4,str,invertido);
	printf("%s\n",tablero);
	free(tablero);
	free(str);
}

int dado(){
    srand(time(NULL));
    int numero = (rand() % 6) + 1;
    sleep(2);
    printf("El numero obtenido es: %d\n", numero);
    return numero;
}

int verificar_signo(int posicion){
	if (posicion == 3 || posicion == 5 || posicion == 7 || posicion == 13 || posicion == 15 || posicion == 22 || posicion == 24 || posicion == 26 || posicion == 28){
		return 1;
	}else if (posicion == 17 || posicion == 23 || posicion == 25 || posicion == 27){
		return 2;
	}
	else{
		return 0;
	}
}

int jugador_desea(int signo){
	int desea;
	if (signo == 1){
		printf("El jugador cayo en ?, ¿Desea activar el efecto?\n");
		printf("1. Activar el efecto\n");
		printf("2. No activar el efecto\n");
		scanf("%d", &desea);
		return desea; 
	}else if (signo == 2){
		printf("El jugador cayo en ??, ¿Desea activar el efecto?\n");
		printf("1. Activar el efecto\n");
		printf("2. No activar el efecto\n");
		scanf("%d", &desea);
		return desea;
	}
	else{
		return 2;
	}
}

int efecto_aleatorio(int signo){
	int numero;
	if (signo == 1){
		srand(time(NULL));
		numero = (rand() % 5) + 1;
		return numero;
	}else if(signo == 2){
		srand(time(NULL));
		numero = (rand() % 10) + 1;
		return numero;
	}
	return 0;
}

int jugador_retrocede(int posicion, int espacios){
	int retrocedio;
	if (posicion == 1){
		retrocedio = posicion;
	}else if(posicion == 2 && espacios == 2){
		retrocedio = posicion - 1;
	}else{
		retrocedio = posicion - espacios;
	}
	return retrocedio;
}

int jugador_avanza(int posicion, int espacios,int opcion){
	int avanza;
	if(opcion==1){
		avanza = posicion+espacios;
	    return avanza;
	}
	if(opcion==2){
		if(posicion==2 || posicion==4 || posicion==6 || posicion==12 || posicion==14 || posicion==16){
			avanza=posicion+2;
		}
		else if(posicion >= 21){
			return posicion;
		}
		else {
			avanza=posicion+espacios;
		}
		return avanza;
	}
	return 0;
}

int ultimo(int pos1, int pos2, int pos3, int pos4){
	int ultimo1 = 0;
	int posicion;
	if (pos1 <= pos2){
		ultimo1 = 0;
		posicion = pos1;
	}else{
		ultimo1 = 1;
		posicion = pos2;
	}

	if (posicion > pos3){
		ultimo1 = 2;
		posicion = pos3;
	}

	if (posicion > pos4){
		ultimo1 = 3;
		posicion = pos4;
	}
	return ultimo1;
}

int primero(int pos1, int pos2, int pos3, int pos4){
	int primero1 = 0;
	int posicion;
	if (pos1 > pos2){
		primero1 = 0;
		posicion = pos1;
	}else{
		primero1 = 1;
		posicion = pos2;
	}

	if (posicion < pos3){
		primero1 = 2;
		posicion = pos3;
	}

	if (posicion < pos4){
		primero1 = 3;
		posicion = pos4;
	}
	return primero1;
}