#include "tdas/list.h"
#include "tdas/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[100];
  int edad;
  int id;
  char sintoma[200];
  int prioridad;
} Persona;

size_t ids = 0;

//-------------------------------------------------------------------------------

void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

//-------------------------------------------------------------------------------

void registrar_paciente(List *pacientes) {
  printf("Registrar nuevo paciente\n");

  // Crear un nuevo paciente
  Persona *nuevo_paciente = malloc(sizeof(Persona));
  
  if (nuevo_paciente == NULL) {
    printf("Error: No se pudo asignar memoria para el nuevo paciente.\n");
    return;
  }
  printf("Ingrese el nombre del paciente: ");
  scanf("%s", nuevo_paciente->nombre);

  printf("Ingrese la edad del paciente: ");
  scanf("%d", &nuevo_paciente->edad);

  printf("Ingrese el síntoma del paciente: ");
  scanf("%s", nuevo_paciente->sintoma);

  // Asignar un ID único al paciente
  nuevo_paciente->id = ids++;
  nuevo_paciente->prioridad = 0;

  // Agregar el paciente a la lista
  list_pushBack(pacientes, nuevo_paciente);
}

//-------------------------------------------------------------------------------

void asignar_prioridad(List *pacientes)
{
  printf("Asignar prioridad a paciente\n");
  printf("Lista de pacientes:\n");

  Persona *current = list_first(pacientes);
  size_t talla = 1;

  while (current != NULL) {
    printf("%zu) Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %d\n",
           talla, current->nombre, current->edad, current->sintoma,
           current->prioridad);

    current = list_next(pacientes);
    talla++;
  }

  size_t seleccion;
  printf("Seleccione el número del paciente: ");
  scanf("%zu", &seleccion);

  // Verificar que la selección sea válida
  if (seleccion < 1 || seleccion > talla - 1)
  {
    printf("Selección inválida.\n");
    return;
  }

  current = list_first(pacientes);
  talla = 1;

  // Buscar el paciente seleccionado
  while (current != NULL && talla < seleccion) {
    current = list_next(pacientes);
    talla++;
  }

  int prioridad;
  printf("Ingrese la prioridad del paciente (0-2): ");
  scanf("%d", &prioridad);

  if (prioridad < 0 || prioridad > 2)
  {
    printf("Prioridad inválida.\n");
    return;
  }
  
  current->prioridad = prioridad;
  printf("Prioridad asignada al paciente %s.\n", current->nombre);
}

//-------------------------------------------------------------------------------

void mostrar_lista_pacientes(List *pacientes) {
  printf("Pacientes en espera: \n");

  Persona *current = list_first(pacientes);

  while (current != NULL) {
    printf("Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %d\n",
           current->nombre, current->edad, current->sintoma,
           current->prioridad);

    current = list_next(pacientes);
  }
}

//-------------------------------------------------------------------------------

int main() {
  char opcion;
  List *pacientes = list_create();

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos
  free(pacientes);

  return 0;
}
