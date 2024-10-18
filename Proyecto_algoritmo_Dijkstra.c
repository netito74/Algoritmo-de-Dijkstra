#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 33 // Número total de nodos

// Definición de nodos
const char *lugares[N] = {
    "Mercado", "Coppel", "Imss No32", "Bodega Aurrera", "Secundaria Tecnica No86", "Neto",
    "Angel del Mar", "Primaria 21 de Marzo", "CBTis 240", "Hospital general", 
    "Gasolinera G500 del Aeropuerto", "ISSSTE", "DHL Express", "Terminal ADO", 
    "CitiBanamex", "Agencia Municipal", "Bahia Principal", "Marinero", 
    "BBVA", "OXXO Aeropuerto", "Umar(Universidad)", "Manzanillo", 
    "Puerto Angelito", "Carrizalillo", "Cafecito", "Villa Mexicana", 
    "Bacocho", "Aeropuerto", "OXXO Costa Chica", "Tienda Neto", "DHL",
    "Puerto Angelito", "Secundaria Tecnica", "Imss"
};

// Matriz de adyacencia con los pesos
int grafo[N][N];

// Función para encontrar el vértice con la distancia mínima
int minDistancia(int dist[], int visitado[]) {
    int min = INT_MAX, min_index;
    int v ;
    for (v= 0; v < N; v++) {
        if (visitado[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// Función para imprimir el camino más corto
void imprimirCamino(int padres[], int j) {
    if (padres[j] == -1) {
        return;
    }
    imprimirCamino(padres, padres[j]);
    printf(" -> %s", lugares[j]);
}

// Función para imprimir la distancia y el camino
void imprimirResultado(int dist[], int padres[], int destino) {
    if (dist[destino] == INT_MAX) {
        printf("No existe ruta desde el origen hasta %s\n", lugares[destino]);
        return;
    }

    printf("Distancia desde el origen hasta %s es: %d metros\n", lugares[destino], dist[destino]);
    printf("Ruta: %s", lugares[0]);
    imprimirCamino(padres, destino);
    printf("\n");
}

// Algoritmo de Dijkstra
void dijkstra(int grafo[N][N], int inicio, int destino) {
    int dist[N]; // dist[i] almacena la distancia más corta desde inicio hasta i
    int visitado[N]; // visitado[i] será 1 si ya se ha procesado el nodo i
    int padres[N]; // padres[i] almacena el nodo previo para reconstruir el camino
        int i, count, v ;

    for (i = 0; i < N; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        padres[i] = -1;
    }
    dist[inicio] = 0;

    for (count = 0; count < N - 1; count++) {
        int u = minDistancia(dist, visitado);
        visitado[u] = 1;

        for ( v = 0; v < N; v++) {
            if (!visitado[v] && grafo[u][v] && dist[u] != INT_MAX && dist[u] + grafo[u][v] < dist[v]) {
                dist[v] = dist[u] + grafo[u][v];
                padres[v] = u;
            }
        }
    }

    imprimirResultado(dist, padres, destino);
}

// Obtener el índice del lugar en el array
int obtenerIndice(char lugar[]) {
	int i;
    for (i = 0; i < N; i++) {
        if (strcmp(lugares[i], lugar) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
	int i, j;
    for (i = 0; i < N; i++) {
        for ( j = 0; j < N; j++) {
            grafo[i][j] = 0;
        }
    }

// Matriz de adyacencia actualizada con nuevas rutas
grafo[0][1] = grafo[1][0] = 500;   // Mercado - Coppel
grafo[0][2] = grafo[2][0] = 550;   // Mercado - Imss No32
grafo[0][3] = grafo[3][0] = 300;   // Mercado - Bodega Aurrera
grafo[1][4] = grafo[4][1] = 220;   // Coppel - Secundaria Tecnica No86
grafo[1][5] = grafo[5][1] = 720;   // Coppel - Neto
grafo[1][6] = grafo[6][1] = 300;   // Coppel - Angel del Mar
grafo[4][7] = grafo[7][4] = 235;   // Secundaria Tecnica No86 - Primaria 21 de Marzo
grafo[4][5] = grafo[5][4] = 470;   // Secundaria Tecnica No86 - Tienda Neto
grafo[7][5] = grafo[5][7] = 360;   // Primaria 21 de Marzo - Neto
grafo[5][8] = grafo[8][5] = 1960;  // Neto - CBTis 240
grafo[5][10] = grafo[10][5] = 1220;  // Neto - Gasolinera G500 del Aeropuerto
grafo[8][9] = grafo[9][8] = 965;   // CBTis 240 - Hospital general
grafo[8][10] = grafo[10][8] = 1570; // CBTis 240 - Gasolinera G500 del Aeropuerto
grafo[6][11] = grafo[11][6] = 190; // Angel del Mar - ISSSTE
grafo[6][2] = grafo[2][6] = 430;   // Angel del Mar - Imss No32
grafo[2][3] = grafo[3][2] = 347;   // Imss No32 - Bodega Aurrera
grafo[2][12] = grafo[12][2] = 470; // Imss No32 - DHL Express
grafo[3][12] = grafo[12][3] = 490; // Bodega Aurrera - DHL Express
grafo[12][13] = grafo[13][12] = 550; // DHL Express - Terminal ADO
grafo[13][14] = grafo[14][13] = 430; // Terminal ADO - CitiBanamex
grafo[13][15] = grafo[15][13] = 430; // Terminal ADO - Agencia Municipal
grafo[14][16] = grafo[16][14] = 320; // CitiBanamex - Bahia Principal
grafo[16][17] = grafo[17][16] = 500; // Bahia Principal - Marinero
grafo[16][18] = grafo[18][16] = 754; // Bahia Principal - BBVA
grafo[17][18] = grafo[18][17] = 360; // Marinero - BBVA
grafo[10][19] = grafo[19][10] = 438; // Gasolinera G500 del Aeropuerto - OXXO Aeropuerto
grafo[19][20] = grafo[20][19] = 507; // OXXO Aeropuerto - Umar (Universidad)
grafo[15][21] = grafo[21][15] = 800; // Agencia Municipal - Manzanillo
grafo[15][22] = grafo[22][15] = 897; // Agencia Municipal - Puerto Angelito
grafo[15][23] = grafo[23][15] = 620; // Agencia Municipal - Cafecito
grafo[22][21] = grafo[21][22] = 227; // Puerto Angelito - Manzanillo
grafo[22][24] = grafo[24][22] = 400; // Puerto Angelito - Carrizalillo
grafo[23][24] = grafo[24][23] = 200; // Cafecito - Carrizalillo
grafo[23][25] = grafo[25][23] = 820; // Cafecito - Villa Mexicana
grafo[25][26] = grafo[26][25] = 1060; // Villa Mexicana - Bacocho
grafo[26][27] = grafo[27][26] = 1840; // Bacocho - Aeropuerto
grafo[27][28] = grafo[28][27] = 1740; // Aeropuerto - OXXO Costa Chica

// Nuevas conexiones añadidas
grafo[8][26] = grafo[26][8] = 1400;  // CBTis 240 - Bacocho
grafo[27][22] = grafo[22][27] = 1600; // Aeropuerto - Puerto Angelito
grafo[25][16] = grafo[16][25] = 1800; // Villa Mexicana - Bahia Principal
grafo[30][32] = grafo[32][30] = 1200; // Tienda Neto - Secundaria Tecnica
grafo[21][8]  = grafo[8][21]  = 900;  // Manzanillo - CBTis 240
grafo[0][32]  = grafo[32][0]  = 950;  // Mercado - Secundaria Tecnica
grafo[12][25] = grafo[25][12] = 980;  // DHL - Villa Mexicana



    char inicio[50], destino[50];
    int indice_inicio, indice_destino;
    char continuar = 's';

    // Bucle para permitir redireccionar
    while (continuar == 's') {
        printf("Introduce el lugar de inicio: ");
        fgets(inicio, sizeof(inicio), stdin);
        inicio[strcspn(inicio, "\n")] = 0;  // Eliminar salto de línea

        printf("Introduce el lugar de destino: ");
        fgets(destino, sizeof(destino), stdin);
        destino[strcspn(destino, "\n")] = 0;

        indice_inicio = obtenerIndice(inicio);
        indice_destino = obtenerIndice(destino);

        if (indice_inicio == -1) {
            printf("Lugar de inicio no válido: %s\n", inicio);
        } else if (indice_destino == -1) {
            printf("Lugar de destino no válido: %s\n", destino);
        } else {
            dijkstra(grafo, indice_inicio, indice_destino);
        }

        // Preguntar si desea continuar
        printf("¿Deseas redireccionar a otro destino desde el último punto? (s/n): ");
        scanf(" %c", &continuar);
        getchar();  // Limpiar el buffer para fgets
        if (continuar == 's') {
            strcpy(inicio, destino);
        }
    }

    return 0;
}

