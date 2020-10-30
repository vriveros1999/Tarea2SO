README

Tomas Allendes Vasquez    - 201873602-3
Valentin Riveros Calderon - 201873583-3

Instrucciones de uso:
- Para ejecutar el programa, solamente poner make en la terminal y se ejecuta automaticamente todo el programa.
- Al ejecutarse, el programa dará la bienvenida y le pedirá la posición donde quiere empezar el jugador principal.
  Debe colocar 1, 2, 3 o 4 dependiendo de la posición.
- Al comenzar el juego, los jugadores por computadora comenzaran su ejecución normal, realizando cada efecto dependiendo
  de la posición en que cayo. Al jugador principal se le preguntará si quiere realizar el efecto antes de saber este. Debe
  colocar 1 si quiere realizarlo o 2 si no quiere realizar el efecto.

Uso de pipes:
Los pipes se utilizaron para los turnos de cada jugador, es decir, dependiendo de la posición donde el jugador principal
quiere partir, el uso de pipes sera distinto. En el caso de que el jugador principal elija la opción 1, el proceso padre
comenzará la ejecución del programa (jugador principal), luego mandará un mensaje con el turno al proceso hijo 1, quien lo
recibe y comienza su ejecución. Luego, este mandará un mensaje al proceso hijo 2 y del proceso 2 al proceso 3, para
finalizar la primera ronda de turnos y comenzar nuevamente. 

Estos procesos se repiten en todos los demas casos (2, 3 y 4), es por ello que nuestro código resulto bastante largo, pero 
cumple con todas las funciones que debe hacer.

Uso de memoria compartida:
Utilizamos la memoria compartida para las distintas posiciones de los jugadores. Utilizamos las variables ptr[] para hacer
los usos de estas memorias. Del ptr[0] al ptr[3] son las posiciones de los jugadores almacenadas en memoria compartida, 
para que todos los procesos conozcan las posiciones de los demas procesos y ejecutar el programa de forma correcta.
El ptr[4] corresponde al flag del while, donde se ejecutan las distintas rondas de turnos y cambia solamente si un jugador 
gano. El ptr[5] corresponde a la variable de cambio del tablero, donde si ptr[5] es 0, es el tablero original, pero
si ptr[5] es 1, el tablero cambia su sentida, asi como otros efectos. El ptr[6] corresponde al salto de turno desde el 
jugador 4 al jugador 1, ya que no se pasaba ningun mensaje entre ellos. 
Desde el ptr[7] al ptr[11] tenemos las variables de memoria para el cambio en el sentido de los turnos, donde, si se 
mantiene el juego original, ptr[7] hasta ptr[10] son 1s y ptr[11] es 0. De lo contrario, se ejecuta la funcion de cambio 
de turno, donde cada variable desde ptr[7] hasta ptr[10] cambiará su valor a 0 dependiendo del jugador que le toque jugar 
en el siguiente turno, y ptr[11] cambiará su valor a 1.

Sintesis: Es un código bastante largo, ya que se tuvo que copiar todos los casos posibles en cada una de las operaciones,
pero su funcionalidad es eficiente, donde cada proceso actua como un jugador comunicandose entre ellos para el uso de turnos
y las posiciones junto con otros efectos tienen sus definiciones a partir de memoria compartida.