#include <stdio.h>
#include <math.h>
#include "operaciones.h"
#include "lecturas.h"

void agregarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float precios[], int *numProductos) {
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
        printf("No se pueden agregar mas productos. Se ha alcanzado el limite.\n");
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
}