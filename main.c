
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Dimension {
    int Matriz[6][59];
    int MatrizTranspuesta[59][6];
    int ProductoDeMatrices[59][59];
}
Peliculas;


int main() {
    char archivo[] = "peliculasFavoritasESD135_2021.csv";
    //leemos el archivo tal cual   
    leer(archivo);
    //muestra la matriz,obtenida con los datos
    generando_Matriz();
    //TRANSPONE LAS MATRICES
    transpuesta();
    //Producto de matrices
    producto();
    //Integrante
    integrante();

    return (EXIT_SUCCESS);
}

void leer(char*direccion) {
    //APERTURA DE ARCHIVO TAL CUAL ES
    FILE * archivo = fopen(direccion, "r");
    if (archivo == NULL) {
        perror("DIRECCION NO VALIDA");
    }
    char caracteres;
    while (feof(archivo) == 0) {
        caracteres = fgetc(archivo);
        printf("%c", caracteres);
    }
    fclose(archivo);
    printf("\n\n LECTURA EXITOSA\n\n");

}
void generando_Matriz() {
    //APERTURA DE ARCHIVO NUEVAMENTE
    FILE *archivo = fopen("peliculasFavoritasESD135_2021.csv", "r");

    if (archivo == NULL) {
        perror("Error al abrir archivo.");

        for (int fila = 0; fila < 59; fila++) {
            for (int columna = 0; columna < 6; columna++) {
                Peliculas.Matriz[fila][columna] = 0;
            }
        }
    }
    //genero la cuenta de comas dentro de una linea para poder extraer los datos 
    int ncoma = 0, fila = 0, columna = 0, acumulador;
    char caracter[60];
    char *token;
    while (fgets(caracter, sizeof (caracter), archivo)) {

        token = strtok(caracter, ",");

        if (ncoma > 1) {
            while (token != NULL) {
                if (columna == 0) {
                    token = strtok(NULL, ",");
                } else if (columna > 0) {
                    acumulador = strtol(token, NULL, 10);
                    if (acumulador != 0) {
                        Peliculas.Matriz[columna - 1][fila] = acumulador;
                    } else {
                        Peliculas.Matriz[columna - 1][fila] = 0;
                    }
                    token = strtok(NULL, ",");
                }
                columna++;
            }

        } else if (ncoma <= 1) {
            token = strtok(NULL, ",");
        }

        ncoma++;

        if (ncoma > 1 && columna >= 6) {
            fila++;
            columna = 0;
        }
    }
    for (int a = 0; a < 59; a++) {
        for (int b = 0; b < 6; b++) {
            printf("%i\t", Peliculas.Matriz[b][a]);
        }
        printf("\n");
    }
    printf("\n\n");
}
void transpuesta() {
    for (int largo = 0; largo < 59; largo++) {
        for (int ancho = 0; ancho < 6; ancho++) {
            Peliculas.MatrizTranspuesta[largo][ancho] = 0;

        }
    }
    for (int a = 0; a < 59; a++) {
        for (int b = 0; b < 6; b++) {
            Peliculas.MatrizTranspuesta[a][b] = Peliculas.Matriz[b][a];
        }
    }
    for (int b = 0; b < 6; b++) {
        for (int a = 0; a < 59; a++) {
            printf("%i ", Peliculas.Matriz[b][a]);

        }
        printf("\n\n");
    }
}

void producto() {
    for (int fila = 0; fila < 59; fila++) {
        for (int columna = 0; columna < 59; columna++) {
            Peliculas.ProductoDeMatrices[fila][columna] = 0;
        }
    }
    for (int filapro = 0; filapro < 59; filapro++) {
        for (int fila = 0; fila < 59; fila++) {
            for (int columna = 0; columna < 6; columna++) {
                Peliculas.ProductoDeMatrices[filapro][fila] += Peliculas.Matriz[columna][filapro] * Peliculas.MatrizTranspuesta[fila][columna];
            }
        }
    }


    for (int b = 0; b < 59; b++) {
        for (int a = 0; a < 59; a++) {
            printf("%i ", Peliculas.ProductoDeMatrices[b][a]);
        }
        printf("\n");
    }
}

void integrante() {
    const char *Carnet1 = "JM17015";
    const char *Carnet2 = "ZE17002";
    printf("Estudiantes: %s,%s\n", Carnet1, Carnet2);
}