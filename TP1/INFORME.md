# UNIVERSIDAD NACIONAL DE CÓRDOBA
# FACULTAD DE CIENCIAS EXACTAS, FÍSICAS Y NATURALES

# SISTEMAS DE COMPUTACIÓN	
## Trabajo Práctico N°1: Rendimiento
### Grupo: SegFault

| Nombre |
|--------|
| Madrid, Santiago |
| Ricci, Matias |

### Docentes
- Jorge, Javier
- Solinas, Miguel

### Marzo del 2025

---

# Rendimiento de procesadores para compilar linux en OpenBenchmarking

## Comparativa entre procesadores
Para esta parte del TP se debia comprar los procesadores: Intel Core i5-13600K y AMD Ryzen 9 5900X 12-Core basandonos en las pruebas de compilacion de kernel en la pagina https://openbenchmarking.org/test/pts/build-linux-kernel-1.15.0 . Hemos llegado a estos resultados:

| Procesador                 | Precio(u$d)  | Tiempo (s) | TDP (W) |
|----------------------------|--------------|------------|---------|
| Intel i5-13600K 14-core    | 230          | 83 ± 3     | 125     |
| AMD Ryzen 9 5900X  12-core | 255          | 97 ± 6     | 105     |

Si analizamos la tabla podemos observar que el Intel i5 tiene mejor tiempo y menor precio, pero un mayor consumo. Para una evaluacion mas clara podemos sacar el rendimiento haciendo 1/Tiempo(s)
- Intel i5-13600K -> 0,1204
- AMD Ryzen 9 5900X -> 0,1030
Con esto podemos decir que el rendimiento del Intel i5 es mayor solo fijandonos en el tiempo de ejecucion.

Para obtener el rendimiento segun precio podemos hacer Rendimiento/Precio, obteniendo
- Intel i5-13600K -> 5,2347e-6
- AMD Ryzen 9 5900X -> 4,0392e-6
Si analizamos estos resultados podemos ver que el rendimiento teniendo en cuenta el precio es un 29,6% mayor en el Intel i5.

Por otro lado podemos analizar el rendimiento teniendo en cuenta el consumo, haciendo Rendimiento/TDP
- Intel i5-13600K -> 963,2e-6
- AMD Ryzen 9 5900X -> 980,9e-6
Teniendo en cuenta esto, el AMD Ryzen 9 es ligeramente superior en rendimiento sobre consumo

Por ultimo podemos analizar el rendimiento por core, haciendo Rendimiento/n-cores
- Intel i5-13600K -> 86e-4
- AMD Ryzen 9 5900X -> 85,8e-4
En este apartado tambien es mejor el Intel i5, aunque por muy poco.

## Aceleracion respecto al AMD Ryzen 9 7950X 16-Core

Esta parte termina con una comparativa de aceleracion del AMD Ryzen 9 7950X 16-Core. Este ultimo tiene un tiempo de ejecucion de 53 +/- 3 s. 
Teniendo en cuenta el tiempo de ejecucion, la aceleracion de este ultimo respecto a los ya analizados es
- Intel i5-13600K -> x1,53
- AMD Ryzen 9 5900X -> x1,83

Como se puede observar, el Ryzen 9 7950X es considerablemente mas potente que ambos.
Vale considerar tambien que este ultimo se encuentra a un precio de ~U$D520, y un TDP de 170W, lo que significa una gran diferencia a favor de los menos potentes.

## Comparacion con nuestro dispositivo
Para agregar otro punto de comparacion realizamos el testeo de compilacion del kernel sobre una de nuestras computadors. Esta cuenta con las siguientes especificaciones:
- AMD Ryzen 7 7435HS (8 cores 16 threads)
Al realizar la compilacion esta tardo 131 segundos, poniendola por debajo de los 3 procesadores anteriores. Comparando con los otros procesadors obtenemos que:
- Intel Core i5-13600K es 1.35 veces más rápido
- AMD Ryzen 9 5900X 12-Core es 1.58 veces más rápido
- AMD Ryzen 9 7950X 16-Core es 2.47 veces más rápido



## Conclusiones
Si lo que se busca es potencia bruta, podemos decir que el AMD Ryzen 9 7950X 16-Core es claramente el ganador.
Por otra parte, en cuanto a rendimiento por precio el Intel i5 es el más indicado. 
Si de consumo se habla el AMD Ryzen 9 5900X  12-core es el mejor, pero la minima diferencia en este apartado contrastada con la mejora en cuanto a rendimiento nos hace pensar que el Intel i5-13600K es el mejor en casi todo aspecto en esa comparativa mano a mano.

---

# Tutorial gprof

Para comenzar la el test de profiling g_prof primero debemos tener dos archivos como los que se muestran, que fueron brindados por el profesor.

![image](https://github.com/user-attachments/assets/34331494-33cd-449c-871b-0a04ac29dda8)

Dentro de estos encontramos lo siguiente:
test_gprof.c: 
test_gprof_new.c:

Se compilan ambos archivos juntos para obtener test_gprof (como ejecutable). Este se corre en la terminal y se genera un archivo de salida gmon.out

![image](https://github.com/user-attachments/assets/c0a6c46a-ab7b-4ff4-bfa8-611ab9054a77)

Este archivo se puede manejar para obtener la salida en un archivo analysis.txt, donde se guardará toda la información que devuelve el test.

El instructivo nos brinda diferentes formas de ejecutar el test dependiendo de la información específica que se requiera. A continuación se detalla la salida de cada ejecución.

![image](https://github.com/user-attachments/assets/2b936ccd-edfb-412e-be6a-bee0b22c4c57)



### - gprof -a test_gprof gmon.out > analysis.txt

Aplicando la flag -a se suprimen las funciones declaradas estáticamente (privadas). Por ejemplo, en este caso la func2 no devolverá información por ser estática.

![image](https://github.com/user-attachments/assets/8e183143-ec5f-415c-b94c-0134e1a32902)



### - gprof -b test_gprof gmon.out > analysis.txt

Aplicando la flag -b se suprimen los textos detallados. Entonces podemos observar que se obtienen solo gráficos y resultados concretos del test.

![image](https://github.com/user-attachments/assets/b1e52f17-d24f-42b2-8f93-99c9172e1d48)



### - gprof -p -b test_gprof gmon.out > analysis.txt

Aplicando la flag -p se obtiene como salida solo el perfil plano.

![image](https://github.com/user-attachments/assets/f6df6621-1ae1-4cad-a814-0154ced86f9c)



### - gprof -p<función> -b test_gprof gmon.out > analysis.txt

Aplicando la flag -p<funcion> se imprime la información relacionada con la función indicada.

![image](https://github.com/user-attachments/assets/247f7418-7da8-4777-8ae2-5f481f49a8d1)



### - gprof -P -b test_gprof gmon.out > analysis.txt

Aplicando la flag -P se suprime el flat profile.

![image](https://github.com/user-attachments/assets/b1e875c1-126f-487c-a503-b5ffabfd3b96)



### - gprof -P<función> -b test_gprof gmon.out > analysis.txt

Aplicando esta flag se suprime la función determinada en el flat profile.

![image](https://github.com/user-attachments/assets/9e8388e7-65b5-4a6a-9164-dd30ca078cdc)




### - gprof -q -b test_gprof gmon.out > analysis.txt

Aplicando la flag -q se imprime solo graph information.

![image](https://github.com/user-attachments/assets/8f32ed48-9308-49fc-b3c0-8511b4678def)


 
### - gprof -q<función> -b test_gprof gmon.out > analysis.txt

Aplicando esta flag se imprime solo la información solicitada en call graph.

![image](https://github.com/user-attachments/assets/ec7e96ff-434a-4d88-b577-ea08a65999b4)



### - gprof -Q -b test_gprof gmon.out > analysis.txt

Aplicando la flag -Q se suprime call graph.

![image](https://github.com/user-attachments/assets/0f1246b8-5a59-4abe-9836-2a861812fd73)



### - gprof -Q<función> -b test_gprof gmon.out > analysis.txt

Aplicando la flag -Q<función> se suprime graph information sobre la función seleccionada.

![image](https://github.com/user-attachments/assets/b93a6260-35c5-4766-8b9c-f0e36631bfd4)


---

# Benchmarks

## _**Motion Mark 1.0 - Capacidad renderizado gráfico browser.**_

 1. Benchmark que mide la capacidad de renderizado gráfico de un navegador.


 2. Evalúa el rendimiento en animaciones y gráficos 2D basados en HTML5 y JavaScript.


 3. Usa múltiples escenarios con diferentes niveles de carga gráfica para probar la GPU y CPU.


 4. Su resultado se expresa en puntos, reflejando cuántos FPS puede mantener el navegador.

![image](https://github.com/user-attachments/assets/c6f069c7-ef9b-44ee-9ac6-f870274cb8b8)




## _**Basemark - Cargado y renderizado de páginas.**_

1. Benchmark multiplataforma que evalúa el rendimiento de navegadores y dispositivos.


2. Mide gráficos con WebGL, ejecución de JavaScript y capacidad de procesamiento de datos.


3. Realiza pruebas intensivas para simular aplicaciones web complejas y juegos en el navegador.


4. Su puntuación final representa la eficiencia del sistema en tareas web exigentes.

![image](https://github.com/user-attachments/assets/01885cfa-6ff3-48ef-98e0-12bf2343f7f3)




## _**ARES-6 - Memoria y eficiencia energética browser.**_

1. Benchmark diseñado para medir el rendimiento de motores de JavaScript modernos.


2. Evalúa la ejecución de código avanzado como promesas, clases y manipulación de objetos.


3. Simula cargas de trabajo reales utilizadas en aplicaciones web dinámicas.


4. Su puntuación refleja la velocidad con la que el motor ejecuta código en milisegundos.

![image](https://github.com/user-attachments/assets/81a08459-33c8-46e7-9cbb-e81e66f3df6b)




## _**Sysbench - Prueba el rendimiento del CPU ejecutando operaciones matemáticas.**_

1. Herramienta de benchmarking que evalúa CPU, memoria y disco en sistemas Linux.


2. Realiza operaciones matemáticas intensivas para medir la velocidad del procesador.


3. Puede ejecutar pruebas de I/O para evaluar la velocidad de lectura y escritura en disco.


4. Permite generar carga en múltiples hilos para simular estrés en el hardware.

![image](https://github.com/user-attachments/assets/605419ea-1c04-473c-bfb6-41f1f436b120)


---

# Prueba práctica

Para la experiencia de modificar la frecuencia de una placa y revisar el tiempo que tarda en hacer cálculos hemos utilizado una placa ESP32 NodeMCU. 
Se programó para calcular la serie de Fibonacci de 5000, calculando el tiempo con frecuencias de 80 Mhz, 160 Mhz y 240 Mhz.

![image](https://github.com/user-attachments/assets/cdf2b084-3dc3-48d4-96da-aebe372a27e0)


Como se puede observar en la imagen, al variar la frecuencia se puede considerar una variación del tiempo cercana a la lineal.
