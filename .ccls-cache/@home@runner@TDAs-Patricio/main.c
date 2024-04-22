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
  puts("3) Mostrar lista por orden de llegada");
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
  scanf(" %50[^\n]", nuevo_paciente->nombre);

  printf("Ingrese la edad del paciente: ");
  scanf("%d", &nuevo_paciente->edad);

  printf("Ingrese el síntoma del paciente: ");
  scanf(" %150[^\n]", nuevo_paciente->sintoma);

  // Asignar un ID único al paciente
  nuevo_paciente->id = ids++;
  nuevo_paciente->prioridad = 1;

  // Agregar el paciente a la lista
  list_pushBack(pacientes, nuevo_paciente);
}

//-------------------------------------------------------------------------------

void asignar_prioridad(List *pacientes) {
  printf("Asignar prioridad a paciente\n");
  printf("Lista de pacientes:\n\n");

  Persona *current = list_first(pacientes);
  size_t talla = 1;

  while (current != NULL) 
  {
    printf("%zu) Nombre: %s || Edad: %d || Síntoma: %s || ", talla,
    current->nombre, current->edad, current->sintoma);

    if (current->prioridad == 1)
      printf("Prioridad: Baja\n");

    else if (current->prioridad == 2)
      printf("Prioridad: Media\n");

    else if (current->prioridad == 3)
      printf("Prioridad: Alta\n");

    current = list_next(pacientes);
    talla++;
  }
  printf("\n");

  size_t seleccion;
  printf("Seleccione el número del paciente: ");
  scanf("%zu", &seleccion);

  // Verificar que la selección sea válida
  if (seleccion < 1 || seleccion > talla - 1) {
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
  printf("Ingrese la prioridad del paciente: \n");
  printf("1) Baja\n");
  printf("2) Media\n");
  printf("3) Alta\n");
  printf("Seleccione una opción: ");

  scanf("%d", &prioridad);

  if (prioridad < 1 || prioridad > 3) {
    printf("Prioridad inválida.\n");
    return;
  }

  current->prioridad = prioridad;
  printf("Prioridad asignada al paciente %s.\n", current->nombre);
}

//-------------------------------------------------------------------------------

void mostrar_lista_pacientes(List *pacientes) {
  printf("Pacientes en espera: \n\n");

  Persona *current = list_first(pacientes);

  while (current != NULL) {
    printf("Nombre: %s || Edad: %d || Síntoma: %s || ",
      current->nombre, current->edad, current->sintoma);

    if (current->prioridad == 1)
      printf("Prioridad: Baja\n");

    else if (current->prioridad == 2)
      printf("Prioridad: Media\n");

    else if (current->prioridad == 3)
      printf("Prioridad: Alta\n");

    current = list_next(pacientes);
  }
  printf("\n");
}

//-------------------------------------------------------------------------------

void atender_paciente(List *pacientes) {
  printf("Atender al siguiente paciente\n");
  Persona *current = list_first(pacientes);
  if (current == NULL)
    printf("No hay pacientes en espera. La lista está vacía.\n");

  else {
    printf("Paciente a atender: %s\n", current->nombre);
    list_popFront(pacientes);
  }
}
//-------------------------------------------------------------------------------

void mostrar_pacientes_por_prioridad(List *pacientes){
  printf("\nPacientes por prioridad \n");
  printf("1) Baja\n");
  printf("2) Media\n");
  printf("3) Alta\n\n");

  Persona *current = list_first(pacientes);
  int prioridad;
  printf("Ingrese la prioridad a mostrar: ");
  scanf("%d", &prioridad);
  while (current != NULL)
  {
    if (current->prioridad == prioridad)
    {
      printf("\nNombre: %s || Edad: %d || Síntoma: %s || ",
        current->nombre, current->edad, current->sintoma);

        if (current->prioridad == 1)
        {
          printf("Prioridad: Baja\n");
          current = list_next(pacientes);
        }

        else if (current->prioridad == 2)
        {
          printf("Prioridad: Media\n");
          current = list_next(pacientes);
        }

        else if (current->prioridad == 3)
        {
          printf("Prioridad: Alta\n");
          current = list_next(pacientes);
        }
    }
    current = list_next(pacientes);
  }
  printf("\n");
}

//-------------------------------------------------------------------------------

void mostrar_orden_de_prioridad(List *pacientes){
  printf("Mostrar pacientes por orden de prioridad\n\n");

  Persona *current;
  for (int i = 3; i >= 1; i--)
  {
    current = list_first(pacientes);
    while (current != NULL)
    {
      if (current->prioridad == i)
      {
        printf("Nombre: %s || Edad: %d || Síntoma: %s || ", current->nombre, current->edad, current->sintoma);

        if (current->prioridad == 1)
          printf("Prioridad: Baja\n");

        else if (current->prioridad == 2)
          printf("Prioridad: Media\n");

        else if (current->prioridad == 3)
          printf("Prioridad: Alta\n");
      }
      current = list_next(pacientes);
    }
  }
}

//-------------------------------------------------------------------------------

void mostrar_prioridad(List *pacientes){
  printf("\nMostrar pacientes por prioridad\n\n");
  char opcion1;

  printf("1) Mostrar pacientes de una sola prioridad\n");
  printf("2) Mostrar pacientes por orden de prioridad\n\n");

  printf("Ingrese su opción: ");
  scanf(" %c", &opcion1);

  switch (opcion1) {
  case '1':
    mostrar_pacientes_por_prioridad(pacientes);
    break;
  case '2':
    mostrar_orden_de_prioridad(pacientes);
    break;
  default:
    puts("Opción no válida. Por favor, intente de nuevo.");
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
      atender_paciente(pacientes);
      break;
    case '5':
      mostrar_prioridad(pacientes);
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