#include <stdio.h>

// Declaración de la función en assembler
extern int procesar_gini_via_stack(float valor);

int main() {
    float gini_values[] = {41.5, 42.3, 40.7};  // Simulado como si viniera desde Python
    int cantidad = sizeof(gini_values) / sizeof(gini_values[0]);
    int resultados[cantidad];

    for (int i = 0; i < cantidad; i++) {
        resultados[i] = procesar_gini_via_stack(gini_values[i]);
    }

    for (int i = 0; i < cantidad; i++) {
        printf("GINI procesado: %d\n", resultados[i]);
    }

    return 0;
}
