
## Código de Ejemplo (main)
Para ejecutar el main primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````
./main
````

## Requerimentos
Es recomendable extender la página del `shell` para una mejor visualización de las listas, además de ingresar un nombre con menos de 50 caracteres y síntomas con menos de 150 caracteres.

## CONTRA
La mayor contra de este programa es que no se puede atender en orden de prioridad, solamente en orden de llegada.

También tiene complicaciones sobre la hora de llegada, pero se imprime bien.

## Funcionamiento
Este código utiliza una lista enlazada simple como estructura principal, gracias al struct Persona se recopilan los siguientes datos:

````c
typedef struct {
  char nombre[100];
  int edad;
  int id;
  char sintoma[200];
  int prioridad;
} Persona;
````

## Funciones
Estas son las funciones usadas en el programa:

````c
//Ingresar un nuevo paciente a la lista
void registrar_paciente(List *pacientes) {

//Se le asigna prioridad a un paciente (default: Baja)
void asignar_prioridad(List *pacientes) {

//Se muestra la lista de pacientes por orden de llegada (sin importar prioridad)
void mostrar_lista_pacientes(List *pacientes) {

//Se atiende al primer paciente ingresado (sin importar prioridad)
void atender_paciente(List *pacientes) {

//Se ingresa una prioridad y muestra todos los pacientes con esa prioridad
void mostrar_pacientes_por_prioridad(List *pacientes){

//Se muestran todos los pacientes ordenados por prioridad
void mostrar_orden_de_prioridad(List *pacientes){

//Función que hace de menú para las dos funciones anteriores
void mostrar_prioridad(List *pacientes){

````




