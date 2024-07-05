/*Universidad De Las Américas
Integrantes: Josue Chiriboga
             Nicole Yepez
             Gustavo Zarate
Semana: 12
Actividad: Taller Punteros Y Archivos
Fecha: 04/07/2024 */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "lecturas.h"
#include "operaciones.h"

/*#define MAX_PRODUCTOS 100 // Número máximo de productos
#define MAX_NOMBRE 50 // Longitud máxima del nombre del producto

void agregarProducto(char[][MAX_NOMBRE], int[], float[], int*);
void imprimirProductos(char[][MAX_NOMBRE], int[], float[], int);
void buscarProducto(char[][MAX_NOMBRE], int[], float[], int);
void modificarProducto(char[][MAX_NOMBRE], int[], float[], int);
void eliminarProducto(char[][MAX_NOMBRE], int[], float[], int*);*/

void mostrarMenu();

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE]; // Arreglo para nombres de productos
    int cantidades[MAX_PRODUCTOS]; // Arreglo para cantidades de productos
    float precios[MAX_PRODUCTOS]; // Arreglo para precios de productos
    int numProductos = 0; // Número actual de productos
    int opcion; // Opción seleccionada por el usuario
    FILE *archivo; // Puntero a archivo

    archivo = fopen("Inventario.txt", "a+"); // Abre el archivo

    if (archivo == NULL) { // Verifica si se abrió el archivo
        printf("No fue posible abrir el archivo\n");
        return 1;
    }

    // Lee los datos del archivo y los carga en memoria
    rewind(archivo); // Coloca el cursor al inicio del archivo
    while (fscanf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%f\n\n", nombres[numProductos], &cantidades[numProductos], &precios[numProductos]) != EOF) {
        numProductos++;
    }
    fclose(archivo);

    do {
        mostrarMenu();
        opcion = leerEnteroPositivo("Ingrese su opcion: ");

        switch (opcion) {
            case 1:
                agregarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 2:
                imprimirProductos(nombres, cantidades, precios, numProductos);
                break;
            case 3:
                buscarProducto(nombres, cantidades, precios, numProductos);
                break;
            case 4:
                modificarProducto(nombres, cantidades, precios, numProductos);
                break;
            case 5:
                eliminarProducto(nombres, cantidades, precios, &numProductos);
                break;
            case 6:
                printf("\nCerrando Sistema de Inventario\n");
                break;
            default:
                printf("\nOpcion incorrecta. Ingrese nuevamente.\n");
        }
    } while (opcion != 6);

    return 0;
}

void mostrarMenu() {
    printf("\n-----------------SISTEMA DE INVENTARIO-----------------\n");
    printf("1. Ingresar producto\n");
    printf("2. Imprimir productos\n");
    printf("3. Buscar producto\n");
    printf("4. Modificar producto\n");
    printf("5. Eliminar producto\n");
    printf("6. Salir\n");
}

/*void agregarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int *numProductos) {
    FILE *archivo = fopen("Inventario.txt", "a+");
    if (*numProductos < MAX_PRODUCTOS) {
        printf("Ingrese el nombre del producto: ");
        scanf("%s", nombres[*numProductos]);

        cantidades[*numProductos] = leerEnteroPositivo("Ingrese la cantidad del producto: ");
        precios[*numProductos] = leerFlotantePositivo("Ingrese el precio del producto: ");

        // Escribir en el archivo
        fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[*numProductos], cantidades[*numProductos], precios[*numProductos]);
        fclose(archivo);

        printf("Producto registrado exitosamente\n");
        (*numProductos)++;
    } else {
        printf("No se pueden agregar más productos. Se ha alcanzado el límite.\n");
    }
}

void imprimirProductos(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    printf("\nProductos registrados:\n");
    for (int i = 0; i < numProductos; i++) {
        printf("Nombre: %s\n", nombres[i]);
        printf("Cantidad: %d\n", cantidades[i]);
        printf("Precio: %.2f\n", precios[i]);
        printf("\n");
    }
}

void buscarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    printf("\nIngrese el nombre del producto a buscar: ");
    char nombreBuscar[MAX_NOMBRE];
    scanf("%s", nombreBuscar);
    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreBuscar) == 0) {
            printf("Producto encontrado:\n");
            printf("Nombre: %s\n", nombres[i]);
            printf("Cantidad: %d\n", cantidades[i]);
            printf("Precio: %.2f\n", precios[i]);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

void modificarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int numProductos) {
    printf("\nIngrese el nombre del producto a modificar: ");
    char nombreModificar[MAX_NOMBRE];
    scanf("%s", nombreModificar);
    int encontrado = 0;
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(nombres[i], nombreModificar) == 0) {
            printf("Producto encontrado. Ingrese la nueva cantidad: ");
            cantidades[i] = leerEnteroPositivo("");
            printf("Ingrese el nuevo precio: ");
            precios[i] = leerFlotantePositivo("");

            // Sobrescribir el archivo
            FILE *archivo = fopen("Inventario.txt", "w");
            for (int j = 0; j < numProductos; j++) {
                fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[j], cantidades[j], precios[j]);
            }
            fclose(archivo);

            printf("Producto modificado exitosamente\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}

void eliminarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int *numProductos) {
    printf("\nIngrese el nombre del producto a eliminar: ");
    char nombreEliminar[MAX_NOMBRE];
    scanf("%s", nombreEliminar);
    int encontrado = 0;
    for (int i = 0; i < *numProductos; i++) {
        if (strcmp(nombres[i], nombreEliminar) == 0) {
            // Elimina el producto moviendo los productos siguientes una posición hacia atrás
            for (int j = i; j < *numProductos - 1; j++) {
                strcpy(nombres[j], nombres[j + 1]);
                cantidades[j] = cantidades[j + 1];
                precios[j] = precios[j + 1];
            }
            (*numProductos)--;

            // Sobrescribir el archivo
            FILE *archivo = fopen("Inventario.txt", "w");
            for (int j = 0; j < *numProductos; j++) {
                fprintf(archivo, "Nombre:%s\nCantidad:%d\nPrecio:%.2f\n\n", nombres[j], cantidades[j], precios[j]);
            }
            fclose(archivo);

            printf("Producto eliminado exitosamente\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Producto no encontrado.\n");
    }
}*/
