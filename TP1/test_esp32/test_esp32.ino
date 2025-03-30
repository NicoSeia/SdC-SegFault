// Función para calcular el n-ésimo número de Fibonacci con carga adicional
unsigned long fibonacciConCarga(int n) {
    if (n <= 1) {
        return n;
    }
    unsigned long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;

        // Agregar una operación de carga adicional (multiplicación)
        for (volatile int j = 0; j < 10000; j++) {
            c = c * 2;  // Operación adicional para consumir tiempo
        }
    }
    return b;
}

// Función para medir el tiempo de cálculo
void medirTiempo(int n) {
    unsigned long inicio = millis();
    unsigned long resultado = fibonacciConCarga(n);  // Calcular Fibonacci con carga adicional
    unsigned long tiempoFinal = millis() - inicio;  // Tiempo que tarda en calcularse

    Serial.print("Resultado Fibonacci de ");
    Serial.print(n);
    Serial.print(": ");
    Serial.println(resultado);
    
    Serial.print("Tiempo total: ");
    Serial.print(tiempoFinal);
    Serial.println(" ms");
}

void setup() {
    Serial.begin(115200);
    
    int n = 5000;
    
    // Ejecutar cálculo con frecuencia inicial
    setCpuFrequencyMhz(80);  // Fijar la frecuencia a 80 MHz
    Serial.println("\nEjecutando a 80 MHz...");
    medirTiempo(n);  // Ejecutar cálculo

    // Ejecutar cálculo con frecuencia duplicada
    setCpuFrequencyMhz(160);  // Subir la frecuencia a 160 MHz
    Serial.println("\nEjecutando a 160 MHz...");
    medirTiempo(n);  // Ejecutar cálculo

    // Ejecutar cálculo con frecuencia duplicada
    setCpuFrequencyMhz(240);  // Subir la frecuencia a 240 MHz
    Serial.println("\nEjecutando a 240 MHz...");
    medirTiempo(n);  // Ejecutar cálculo
}

void loop() {
    // No es necesario hacer nada en el loop para este ejercicio
}
