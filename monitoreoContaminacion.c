#include <stdio.h>
#include <string.h>

#define CANTIDAD_ZONAS 5
#define CANTIDAD_DIAS_HISTORICOS 30

#define LIMITE_CO2 1000
#define LIMITE_SO2 40
#define LIMITE_NO2 25
#define LIMITE_PM25 15

struct Zona {
    char nombre[30];
    float contaminacion_actual[4];      // CO2, SO2, NO2, PM2.5
    float contaminacion_historica[CANTIDAD_DIAS_HISTORICOS][4];
    float contaminacion_predicha[4];   
    float temperatura_actual;
    float viento_actual;
    float humedad_actual;
};

//Funciones
void cargarDatos(struct Zona zonas[CANTIDAD_ZONAS]);
void ingresarDatosContaminacion(struct Zona zonas[CANTIDAD_ZONAS]);
void mostrarContaminacion(struct Zona zonas[CANTIDAD_ZONAS]);
void calcularPromediosHistoricos(struct Zona zonas[CANTIDAD_ZONAS]);
void predecirContaminacion(struct Zona zonas[CANTIDAD_ZONAS]);
void generarAlertas(struct Zona zonas[CANTIDAD_ZONAS]);
void recomendaciones(struct Zona zonas[CANTIDAD_ZONAS]);
void guardarDatos(struct Zona zonas[CANTIDAD_ZONAS]);
void menu(struct Zona zonas[CANTIDAD_ZONAS]);
float leerNumeroPositivo(const char *mensaje);
void limpiarBuffer();

int main() {
    struct Zona zonas[CANTIDAD_ZONAS];
    cargarDatos(zonas);
    menu(zonas);
    return 0;
}

void menu(struct Zona zonas[CANTIDAD_ZONAS]) {
    int opcion;
    int resultado;

    do {
        printf("\n========================================\n");
        printf(" SISTEMA DE GESTION DE CONTAMINACION\n");
        printf("========================================\n");
        printf(" 1. Ingresar datos de contaminacion\n");
        printf(" 2. Mostrar contaminacion actual\n");
        printf(" 3. Predecir contaminacion (24h)\n");
        printf(" 4. Generar alertas\n");
        printf(" 5. Generar recomendaciones\n");
        printf(" 6. Guardar reporte en archivo\n");
        printf(" 7. Mostrar promedios historicos\n");
        printf(" 0. Salir\n");
        printf("========================================\n");
        printf("Seleccione una opcion: ");

        resultado = scanf("%d", &opcion);
        limpiarBuffer();
        
        if (resultado != 1) {
            printf("Entrada invalida. Debe ingresar un numero.\n");
            continue;
        }
        
        if (opcion < 0 || opcion > 7) {
            printf("Opcion fuera de rango (0-7). Intente nuevamente.\n");
            continue;
        }
        
        switch (opcion) {
            case 1: ingresarDatosContaminacion(zonas); break;
            case 2: mostrarContaminacion(zonas); break;
            case 3: predecirContaminacion(zonas); break;
            case 4: generarAlertas(zonas); break;
            case 5: recomendaciones(zonas); break;
            case 6: guardarDatos(zonas); break;
            case 7: calcularPromediosHistoricos(zonas); break;
            case 0: printf("\nSaliendo del sistema...\n"); break;
        }

    } while (opcion != 0);
}
// Validacion
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

float leerNumeroPositivo(const char *mensaje) {
    float valor;
    int resultado;
    
    do {
        printf("%s", mensaje);
        resultado = scanf("%f", &valor);
        
        if (resultado != 1) {
            printf("Error: Debe ingresar un numero valido.\n");
            limpiarBuffer();
            continue;
        }
        
        limpiarBuffer();
        
        if (valor < 0) {
            printf("Error: El valor no puede ser negativo.\n");
            continue;
        }
        
        return valor;
        
    } while (1);
}
// Datos históricos
void cargarDatos(struct Zona zonas[CANTIDAD_ZONAS]) {
    char *nombres[CANTIDAD_ZONAS] = {
        "Carcelen", "Chillogallo", "Quitumbe", "Calderon", "Cumbaya"
    };

    float historico[CANTIDAD_ZONAS][CANTIDAD_DIAS_HISTORICOS][4] = {
    // Carcelen 
    {{760,24,20,18},{770,25,21,19},{780,26,22,18},{790,27,22,19},{780,26,21,18},
     {770,25,20,17},{760,24,20,18},{750,23,19,17},{745,22,18,16},{740,22,18,16},
     {735,21,17,15},{730,21,17,15},{735,22,18,16},{745,23,19,17},{755,24,20,18},
     {765,25,21,18},{775,25,21,19},{785,26,22,19},{790,27,22,19},{785,26,21,18},
     {775,25,20,17},{765,24,20,17},{755,23,19,16},{750,23,19,16},{745,22,18,15},
     {740,21,17,15},{735,21,17,15},{740,22,18,16},{750,23,19,17},{760,24,20,18}},

    // Chillogallo
    {{780,28,24,22},{790,29,25,23},{800,30,26,23},{810,31,26,24},{800,30,25,23},
     {790,29,24,22},{780,28,24,22},{770,27,23,21},{765,26,22,20},{760,26,22,20},
     {755,25,21,19},{750,25,21,19},{755,26,22,20},{765,27,23,21},{775,28,24,22},
     {785,29,25,22},{795,30,26,23},{805,31,26,24},{810,31,26,24},{805,30,25,23},
     {795,29,24,22},{785,28,24,22},{775,27,23,21},{770,27,23,21},{765,26,22,20},
     {760,25,21,19},{755,25,21,19},{760,26,22,20},{770,27,23,21},{780,28,24,22}},

    // Quitumbe
    {{820,30,28,26},{830,31,29,27},{840,32,30,27},{850,33,30,28},{840,32,29,27},
     {830,31,28,26},{820,30,28,26},{810,29,27,25},{805,28,26,24},{800,28,26,24},
     {795,27,25,23},{790,27,25,23},{795,28,26,24},{805,29,27,25},{815,30,28,26},
     {825,31,29,26},{835,32,30,27},{845,33,30,28},{850,33,30,28},{845,32,29,27},
     {835,31,28,26},{825,30,28,26},{815,29,27,25},{810,29,27,25},{805,28,26,24},
     {800,27,25,23},{795,27,25,23},{800,28,26,24},{810,29,27,25},{820,30,28,26}},

    // Calderón 
    {{700,20,16,14},{710,21,17,14},{720,22,18,15},{730,23,18,15},{720,22,17,14},
     {710,21,16,13},{700,20,16,14},{690,19,15,13},{685,19,14,12},{680,18,14,12},
     {675,18,14,11},{670,17,13,11},{675,18,14,12},{685,19,15,13},{695,20,16,14},
     {705,21,17,14},{715,22,18,15},{725,23,18,15},{730,23,18,15},{725,22,17,14},
     {715,21,16,13},{705,20,16,13},{695,19,15,12},{690,19,15,12},{685,18,14,11},
     {680,18,14,11},{675,17,13,11},{680,18,14,12},{690,19,15,13},{700,20,16,14}},

    // Cumbayá 
    {{500,12,10,8},{510,13,11,8},{520,14,12,9},{530,15,12,9},{520,14,11,8},
     {510,13,11,8},{500,12,10,8},{495,12,9,7},{490,11,9,7},{485,11,9,6},
     {480,10,8,6},{475,10,8,6},{480,11,9,7},{490,11,9,7},{500,12,10,8},
     {510,13,11,8},{520,14,12,9},{530,15,12,9},{525,14,11,8},{515,13,11,8},
     {505,13,10,8},{495,12,10,7},{490,11,9,7},{485,11,9,6},{480,10,8,6},
     {475,10,8,6},{480,11,9,7},{490,11,9,7},{500,12,10,8},{510,13,11,8}}
    };


    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        strcpy(zonas[i].nombre, nombres[i]);
        for (int d = 0; d < CANTIDAD_DIAS_HISTORICOS; d++)
            for (int c = 0; c < 4; c++)
                zonas[i].contaminacion_historica[d][c] = historico[i][d][c];

        for (int c = 0; c < 4; c++)
            zonas[i].contaminacion_actual[c] = 0;

        zonas[i].temperatura_actual = 0;
        zonas[i].viento_actual = 0;
        zonas[i].humedad_actual = 0;
    }
}

void ingresarDatosContaminacion(struct Zona zonas[CANTIDAD_ZONAS]) {
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        char respuesta;
        
        do {
            printf("\n¿Ingresar datos para %s? (s/n): ", zonas[i].nombre);
            scanf(" %c", &respuesta);
            limpiarBuffer();
            
            if (respuesta != 's' && respuesta != 'S' &&
                respuesta != 'n' && respuesta != 'N') {
                printf("Entrada invalida. Use solo 's' o 'n'.\n");
            }
        } while (respuesta != 's' && respuesta != 'S' &&
                 respuesta != 'n' && respuesta != 'N');

        if (respuesta == 's' || respuesta == 'S') {
            zonas[i].contaminacion_actual[0] = leerNumeroPositivo("CO2 (ppm): ");
            zonas[i].contaminacion_actual[1] = leerNumeroPositivo("SO2 (µg/m³): ");
            zonas[i].contaminacion_actual[2] = leerNumeroPositivo("NO2 (µg/m³): ");
            zonas[i].contaminacion_actual[3] = leerNumeroPositivo("PM2.5 (µg/m³): ");
            zonas[i].temperatura_actual = leerNumeroPositivo("Temperatura (°C): ");
            zonas[i].viento_actual = leerNumeroPositivo("Velocidad de viento (m/s): ");
            zonas[i].humedad_actual = leerNumeroPositivo("Humedad (porcentaje): ");
        }
    }
}

void mostrarContaminacion(struct Zona zonas[CANTIDAD_ZONAS]) {
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        printf("\nZona %s -> CO2: %.2f SO2: %.2f NO2: %.2f PM2.5: %.2f",
               zonas[i].nombre,
               zonas[i].contaminacion_actual[0],
               zonas[i].contaminacion_actual[1],
               zonas[i].contaminacion_actual[2],
               zonas[i].contaminacion_actual[3]);
    }
    printf("\n");
}

void generarAlertas(struct Zona zonas[CANTIDAD_ZONAS]) {
    int hayAlertas = 0;
    
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("\n Alerta CO2 en %s", zonas[i].nombre);
            hayAlertas = 1;
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_SO2) {
            printf("\n Alerta SO2 en %s", zonas[i].nombre);
            hayAlertas = 1;
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_NO2) {
            printf("\n Alerta NO2 en %s", zonas[i].nombre);
            hayAlertas = 1;
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("\n Alerta PM2.5 en %s", zonas[i].nombre);
            hayAlertas = 1;
        }
    }
    
    if (!hayAlertas) {
        printf("\nNo hay alertas activas en ninguna zona.");
    }
    printf("\n");
}

void calcularPromediosHistoricos(struct Zona zonas[CANTIDAD_ZONAS]) {
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        float prom[4] = {0};
        for (int d = 0; d < CANTIDAD_DIAS_HISTORICOS; d++)
            for (int c = 0; c < 4; c++)
                prom[c] += zonas[i].contaminacion_historica[d][c];

        for (int c = 0; c < 4; c++)
            prom[c] /= CANTIDAD_DIAS_HISTORICOS;

        printf("\nPromedio %s -> CO2 %.2f SO2 %.2f NO2 %.2f PM2.5 %.2f",
               zonas[i].nombre, prom[0], prom[1], prom[2], prom[3]);
    }
    printf("\n");
}

void predecirContaminacion(struct Zona zonas[CANTIDAD_ZONAS]) {
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        float pred[4] = {0};
        float peso = 0;
        //recorre los 30 dias
        for (int d = 0; d < CANTIDAD_DIAS_HISTORICOS; d++) {
            int p = d + 1;
            for (int c = 0; c < 4; c++)
            //multiplica el contaminante de cd día con el peso del día (CO2dia1 * 1)
                pred[c] += zonas[i].contaminacion_historica[d][c] * p;
            //suma los pesos = 465
            peso += p;
        }
        
        for (int c = 0; c < 4; c++)
        //Suma ponderada / suma de pesos
            pred[c] /= peso; // estimacion incial para 24 horas 

            //Mejorar predicción con temperatura y viento
        pred[0] += zonas[i].temperatura_actual * 0.1;
        pred[3] -= zonas[i].viento_actual * 0.2;
        pred[3] += zonas[i].humedad_actual * 0.05;
        // Evitar predicciones negativas
        for (int c = 0; c < 4; c++) {
            if (pred[c] < 0) 
                pred[c] = 0;
        } //lo minimo posible es 0

        for (int c = 0; c < 4; c++) {
            zonas[i].contaminacion_predicha[c] = pred[c];
        }
        printf("\nPrediccion 24h %s -> CO2 %.2f SO2 %.2f NO2 %.2f PM2.5 %.2f",
               zonas[i].nombre, pred[0], pred[1], pred[2], pred[3]);
    }
    printf("\n");
}

void recomendaciones(struct Zona zonas[CANTIDAD_ZONAS]) {
    int hayRecomendaciones = 0;
    
    for (int i = 0; i < CANTIDAD_ZONAS; i++) {
        if (zonas[i].contaminacion_actual[0] > LIMITE_CO2) {
            printf("\nPromover el teletrabajo y la reducción del uso del vehículo privado en %s", zonas[i].nombre);
            hayRecomendaciones = 1;
        }
        if (zonas[i].contaminacion_actual[1] > LIMITE_NO2){
            printf("\nReducción del tráfico vehicular en %s", zonas[i].nombre);
            hayRecomendaciones = 1;
        }
        if (zonas[i].contaminacion_actual[2] > LIMITE_SO2) {
            printf("\nCerrar industrias en %s", zonas[i].nombre);
            hayRecomendaciones = 1;
        }
        if (zonas[i].contaminacion_actual[3] > LIMITE_PM25) {
            printf("\nSuspender actividades al aire libre en %s", zonas[i].nombre);
            hayRecomendaciones = 1;
        }
    }
    
    if (!hayRecomendaciones) {
        printf("\nNo hay recomendaciones. Todas las zonas dentro de limites.");
    }
    printf("\n");
}

void guardarDatos(struct Zona zonas[CANTIDAD_ZONAS]) {
    FILE *f = fopen("reporte.txt", "w");
    
    if (f == NULL) {
        printf("\nError: No se pudo crear el archivo reporte.txt\n");
        return;
    }
    
    for (int i = 0; i < CANTIDAD_ZONAS; i++)
        fprintf(f, "Datos actuales -> %s %.2f %.2f %.2f %.2f / Predicciones -> %.2f %.2f %.2f %.2f\n",
                zonas[i].nombre,
                zonas[i].contaminacion_actual[0],
                zonas[i].contaminacion_actual[1],
                zonas[i].contaminacion_actual[2],
                zonas[i].contaminacion_actual[3],
                zonas[i].contaminacion_predicha[0],
                zonas[i].contaminacion_predicha[1],
                zonas[i].contaminacion_predicha[2],
                zonas[i].contaminacion_predicha[3]);
    
    fclose(f);
    printf("\nReporte guardado exitosamente en 'reporte.txt'\n");
}
