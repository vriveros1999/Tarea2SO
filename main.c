#include "funciones.h"

#define READ 0
#define WRITE 1

int  main(){
    pid_t pid, pid_hijos[2], pid_padre;
    int op, mensaje, numero, signo, desea, efecto, flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1; 
    int pipe12[2], pipe13[2], pipe14[2];
    int pipe21[2], pipe23[2], pipe24[2];
    int pipe31[2], pipe32[2], pipe34[2];
    int pipe41[2], pipe42[2], pipe43[2];
    key_t clave;
    long int id;
    int *ptr = NULL;
    pid_padre = getpid();
    int flag = 1;
    Jugador *jugadores = (Jugador*)malloc(sizeof(Jugador)*4);

    clave = ftok("/bin/ls", 33);
    id = shmget(clave,sizeof(int)*100,0777|IPC_CREAT);
	ptr = (int *)shmat(id,(char *)0,0);

    pipe(pipe12);
    pipe(pipe13);
    pipe(pipe14);
    pipe(pipe21);
    pipe(pipe23);
    pipe(pipe24);
    pipe(pipe31);
    pipe(pipe32);
    pipe(pipe34);
    pipe(pipe41);
    pipe(pipe42);
    pipe(pipe43);

    printf("Bienvenidos a la Grieta del Invocador\n");
    printf("Seleccione en que posicion decide partir: \n");
    printf("1. Primero\n");
    printf("2. Segundo\n");
    printf("3. Tercero\n");
    printf("4. Cuarto\n");
    printf("5. Salir del juego\n");
    scanf("%d",&op);

    for(int i=0; i<3; i++){
        pid = fork();
        if(pid<0){
            printf("Error al crear el hijo %d\n",i);
            exit(1);
        }
        else if(pid==0){
            pid_hijos[i] = getpid();
            break;
        }
    }

    jugadores[0].pos = inicializar_posiciones();
    jugadores[1].pos = inicializar_posiciones();
    jugadores[2].pos = inicializar_posiciones();
    jugadores[3].pos = inicializar_posiciones();
    ptr[0] = jugadores[0].pos;
    ptr[1] = jugadores[1].pos;
    ptr[2] = jugadores[2].pos;
    ptr[3] = jugadores[3].pos;

    if(op==1){
        if(pid_padre == getpid()){
            tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
        }
    }else if (op == 2 || op == 3 || op == 4){
        if(pid_hijos[0] == getpid()){
            tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
        }
    }

    while(flag == 1){
        if (op == 1){
            if (pid_padre == getpid()){
                while (flag1 == 1){
                    jugadores[0].turno = 1;
                    printf("Turno del jugador 1 (Principal)\n");
                    numero = dado();
                    jugadores[0].pos += numero;
                    if (jugadores[0].pos >= 29){
                        flag = 0;
                        jugadores[0].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 1");
                        return 0;
                    }
                    ptr[0] = jugadores[0].pos;
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    sleep(2);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    signo = 2; //verificar_signo(jugadores[0].pos);
                    desea = jugador_desea(signo);
                    if (desea == 1){
                        efecto = 1; //efecto_aleatorio(signo);
                        if (signo == 1){
                            if (efecto == 1){
                                ptr[0] = jugador_retrocede(jugadores[0].pos, 1);
                                printf("El jugador retrocedio 1 espacio\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if(efecto == 2){
                                ptr[1] = jugador_retrocede(jugadores[1].pos, 1);
                                ptr[2] = jugador_retrocede(jugadores[2].pos, 1);
                                ptr[3] = jugador_retrocede(jugadores[3].pos, 1);
                                printf("Todos los jugadores retroceden 1 espacio\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if(efecto == 3){
                                printf("Efecto 3\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if(efecto == 4){
                                printf("El siguiente jugador no juega su turno\n");
                                mensaje = 0;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if(efecto == 5){
                                printf("Cambio en el sentido de los turnos\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }
                        }else if (signo == 2){
                            if (efecto == 1 || efecto == 2 || efecto == 3){
                                printf("Todos los jugadores retroceden 2 espacios\n");
                                ptr[0] = jugador_retrocede(jugadores[0].pos, 2);
                                ptr[1] = jugador_retrocede(jugadores[1].pos, 2);
                                ptr[2] = jugador_retrocede(jugadores[2].pos, 2);
                                ptr[3] = jugador_retrocede(jugadores[3].pos, 2);
                                tablero(ptr[0], ptr[1], ptr[2], ptr[3]);
                                sleep(2);
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if (efecto == 4 || efecto == 5){
                                printf("Efecto 2 ??\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if (efecto == 6 || efecto == 7){
                                printf("Efecto 3 ??\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if (efecto == 8 || efecto == 9){
                                printf("Efecto 4 ??\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }else if (efecto == 10){
                                printf("Efecto 5 ??\n");
                                mensaje = 2;
                                write(pipe12[WRITE], &mensaje, sizeof(int));
                                read(pipe21[READ], &flag1, sizeof(int));
                            }
                        }
                    }else{
                        mensaje = 2;
                        write(pipe12[WRITE], &mensaje, sizeof(int));
                        read(pipe21[READ], &flag1, sizeof(int));
                    }
                }  
            }else if (pid_hijos[0] == getpid()){
                while (flag2 == 1){
                    read(pipe12[READ], &jugadores[1].turno, sizeof(int));
                    if (jugadores[1].turno != 0){
                        printf("Turno del jugador 2\n");
                        jugadores[1].pos = ptr[1];
                        numero = dado();
                        jugadores[1].pos += numero;
                        if (jugadores[1].pos >= 29){
                            flag = 0;
                            jugadores[1].pos = 29;
                            tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                            printf("El ganador es el jugador 2");
                            return 0;
                        }
                        jugadores[0].pos = ptr[0];
                        jugadores[2].pos = ptr[2];
                        jugadores[3].pos = ptr[3];
                        ptr[1] = jugadores[1].pos;
                        sleep(3);
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    }
                    mensaje = 3;
                    write(pipe23[WRITE], &mensaje, sizeof(int));
                    flag1 = 0;
                    read(pipe32[READ], &flag2, sizeof(int));
                    write(pipe21[WRITE], &flag1, sizeof(int));
                }
            }else if (pid_hijos[1] == getpid()){
                while (flag3 == 1){
                    read(pipe23[READ], &jugadores[2].turno, sizeof(int));
                    printf("Turno del jugador 3\n");
                    numero = dado();
                    jugadores[2].pos += numero;
                    if (jugadores[2].pos >= 29){
                        flag = 0;
                        jugadores[2].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 3");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[3].pos = ptr[3];
                    ptr[2] = jugadores[2].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 4;
                    write(pipe34[WRITE], &mensaje, sizeof(int));
                    flag2 = 0;
                    read(pipe43[READ], &flag3, sizeof(int));
                    write(pipe32[WRITE], &flag2, sizeof(int)); 
                }
            }else if (pid_hijos[2] == getpid()){
                while (flag4 == 1){
                    read(pipe34[READ], &jugadores[3].turno, sizeof(int));
                    printf("Turno del jugador 4\n");
                    numero = dado();
                    jugadores[3].pos += numero;
                    if (jugadores[3].pos >= 29){
                        flag = 0;
                        jugadores[3].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 4");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    ptr[3] = jugadores[3].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    flag3 = 0;
                    write(pipe43[WRITE], &flag3, sizeof(int));
                    flag4 = 0;
                } 
            }
        }else if(op == 2){
            if (pid_padre == getpid()){
                while (flag2 == 1){
                    read(pipe21[READ], &jugadores[1].turno, sizeof(int));
                    printf("Turno del jugador 2 (Principal)\n");
                    numero = dado();
                    jugadores[1].pos += numero;
                    if (jugadores[1].pos >= 29){
                        flag = 0;
                        jugadores[1].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 2");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    ptr[1] = jugadores[1].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 3;
                    write(pipe13[WRITE], &mensaje, sizeof(int));
                    flag1 = 0;
                    read(pipe31[READ], &flag2, sizeof(int));
                    write(pipe12[WRITE], &flag1, sizeof(int));
                }
            }else if (pid_hijos[0] == getpid()){
                while (flag1 == 1){
                    jugadores[0].turno = 1;
                    printf("Turno del jugador 1\n");
                    numero = dado();
                    jugadores[0].pos += numero;
                    if (jugadores[0].pos >= 29){
                        flag = 0;
                        jugadores[0].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 1");
                        return 0;
                    }
                    ptr[0] = jugadores[0].pos;
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 2;
                    write(pipe21[WRITE], &mensaje, sizeof(int));
                    read(pipe12[READ], &flag1, sizeof(int));
                }  
            }else if (pid_hijos[1] == getpid()){
                while (flag3 == 1){
                    read(pipe13[READ], &jugadores[2].turno, sizeof(int));
                    printf("Turno del jugador 3\n");
                    numero = dado();
                    jugadores[2].pos += numero;
                    if (jugadores[2].pos >= 29){
                        flag = 0;
                        jugadores[2].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 3");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[3].pos = ptr[3];
                    ptr[2] = jugadores[2].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 4;
                    write(pipe34[WRITE], &mensaje, sizeof(int));
                    flag2 = 0;
                    read(pipe43[READ], &flag3, sizeof(int));
                    write(pipe31[WRITE], &flag2, sizeof(int));
                }
            }else if (pid_hijos[2] == getpid()){
                while (flag4 == 1){
                    read(pipe34[READ], &jugadores[3].turno, sizeof(int));
                    printf("Turno del jugador 4\n");
                    numero = dado();
                    jugadores[3].pos += numero;
                    if (jugadores[3].pos >= 29){
                        flag = 0;
                        jugadores[3].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 4");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    ptr[3] = jugadores[3].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    flag3 = 0;
                    write(pipe43[WRITE], &flag3, sizeof(int));
                    flag4 = 0;
                } 
            }
        }else if(op == 3){
            if (pid_padre == getpid()){
                while (flag3 == 1){
                    read(pipe31[READ], &jugadores[2].turno, sizeof(int));
                    printf("Turno del jugador 3 (Principal)\n");
                    numero = dado();
                    jugadores[2].pos += numero;
                    if (jugadores[2].pos >= 29){
                        flag = 0;
                        jugadores[2].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 3");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[3].pos = ptr[3];
                    ptr[2] = jugadores[2].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 4;
                    write(pipe14[WRITE], &mensaje, sizeof(int));
                    flag2 = 0;
                    read(pipe41[READ], &flag3, sizeof(int));
                    write(pipe13[WRITE], &flag2, sizeof(int));
                }
            }else if (pid_hijos[0] == getpid()){
                while (flag1 == 1){
                    jugadores[0].turno = 1;
                    printf("Turno del jugador 1\n");
                    numero = dado();
                    jugadores[0].pos += numero;
                    if (jugadores[0].pos >= 29){
                        flag = 0;
                        jugadores[0].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 1");
                        return 0;
                    }
                    ptr[0] = jugadores[0].pos;
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 2;
                    write(pipe23[WRITE], &mensaje, sizeof(int));
                    read(pipe32[READ], &flag1, sizeof(int));
                }  
            }else if (pid_hijos[1] == getpid()){
                while (flag2 == 1){
                    read(pipe23[READ], &jugadores[1].turno, sizeof(int));
                    printf("Turno del jugador 2\n");
                    numero = dado();
                    jugadores[1].pos += numero;
                    if (jugadores[1].pos >= 29){
                        flag = 0;
                        jugadores[1].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 2");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    ptr[1] = jugadores[1].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 3;
                    write(pipe31[WRITE], &mensaje, sizeof(int));
                    flag1 = 0;
                    read(pipe13[READ], &flag2, sizeof(int));
                    write(pipe32[WRITE], &flag1, sizeof(int));
                }
            }else if (pid_hijos[2] == getpid()){
                while (flag4 == 1){
                    read(pipe14[READ], &jugadores[3].turno, sizeof(int));
                    printf("Turno del jugador 4\n");
                    numero = dado();
                    jugadores[3].pos += numero;
                    if (jugadores[3].pos >= 29){
                        flag = 0;
                        jugadores[3].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 4");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    ptr[3] = jugadores[3].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    flag3 = 0;
                    write(pipe41[WRITE], &flag3, sizeof(int));
                    flag4 = 0;
                } 
            }
        }else if(op == 4){
            if (pid_padre == getpid()){
                while (flag4 == 1){
                    read(pipe41[READ], &jugadores[3].turno, sizeof(int));
                    printf("Turno del jugador 4 (Principal)\n");
                    numero = dado();
                    jugadores[3].pos += numero;
                    if (jugadores[3].pos >= 29){
                        flag = 0;
                        jugadores[3].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 4");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    ptr[3] = jugadores[3].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    flag3 = 0;
                    write(pipe14[WRITE], &flag3, sizeof(int));
                    flag4 = 0;
                } 
            }else if (pid_hijos[0] == getpid()){
                while (flag1 == 1){
                    jugadores[0].turno = 1;
                    printf("Turno del jugador 1\n");
                    numero = dado();
                    jugadores[0].pos += numero;
                    if (jugadores[0].pos >= 29){
                        flag = 0;
                        jugadores[0].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 1");
                        return 0;
                    }
                    ptr[0] = jugadores[0].pos;
                    jugadores[1].pos = ptr[1];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 2;
                    write(pipe23[WRITE], &mensaje, sizeof(int));
                    read(pipe32[READ], &flag1, sizeof(int));
                }  
            }else if (pid_hijos[1] == getpid()){
                while (flag2 == 1){
                    read(pipe23[READ], &jugadores[1].turno, sizeof(int));
                    printf("Turno del jugador 2\n");
                    numero = dado();
                    jugadores[1].pos += numero;
                    if (jugadores[1].pos >= 29){
                        flag = 0;
                        jugadores[1].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 2");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[2].pos = ptr[2];
                    jugadores[3].pos = ptr[3];
                    ptr[1] = jugadores[1].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 3;
                    write(pipe34[WRITE], &mensaje, sizeof(int));
                    flag1 = 0;
                    read(pipe43[READ], &flag2, sizeof(int));
                    write(pipe32[WRITE], &flag1, sizeof(int));
                }
            }else if (pid_hijos[2] == getpid()){
                while (flag3 == 1){
                    read(pipe34[READ], &jugadores[2].turno, sizeof(int));
                    printf("Turno del jugador 3\n");
                    numero = dado();
                    jugadores[2].pos += numero;
                    if (jugadores[2].pos >= 29){
                        flag = 0;
                        jugadores[2].pos = 29;
                        tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                        printf("El ganador es el jugador 3");
                        return 0;
                    }
                    jugadores[0].pos = ptr[0];
                    jugadores[1].pos = ptr[1];
                    jugadores[3].pos = ptr[3];
                    ptr[2] = jugadores[2].pos;
                    sleep(3);
                    tablero(jugadores[0].pos,jugadores[1].pos,jugadores[2].pos,jugadores[3].pos);
                    mensaje = 4;
                    write(pipe41[WRITE], &mensaje, sizeof(int));
                    flag2 = 0;
                    read(pipe14[READ], &flag3, sizeof(int));
                    write(pipe43[WRITE], &flag2, sizeof(int));
                }
            }
        }else{
            return 0;
        }
        flag1 = 1;
        flag2 = 1;
        flag3 = 1;
        flag4 = 1;
    }
    

    close(pipe12[READ]);
    close(pipe12[WRITE]);
    close(pipe13[READ]);
    close(pipe13[WRITE]);
    close(pipe14[READ]);
    close(pipe14[WRITE]);
    close(pipe21[READ]);
    close(pipe21[WRITE]);
    close(pipe23[READ]);
    close(pipe23[WRITE]);
    close(pipe24[READ]);
    close(pipe24[WRITE]);
    close(pipe31[READ]);
    close(pipe31[WRITE]);
    close(pipe32[READ]);
    close(pipe32[WRITE]);
    close(pipe34[READ]);
    close(pipe34[WRITE]);
    close(pipe41[READ]);
    close(pipe41[WRITE]);
    close(pipe42[READ]);
    close(pipe42[WRITE]);
    close(pipe43[READ]);
    close(pipe43[WRITE]);

    shmdt((char *)id);
    shmctl(id,IPC_RMID,0);

    return 0;

}