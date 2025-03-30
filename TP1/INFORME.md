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

## Conclusiones
Si lo que se busca es potencia bruta, podemos decir que el AMD Ryzen 9 7950X 16-Core es claramente el ganador.
Por otra parte, en cuanto a rendimiento por precio el Intel i5 es el más indicado. 
Si de consumo se habla el AMD Ryzen 9 5900X  12-core es el mejor, pero la minima diferencia en este apartado contrastada con la mejora en cuanto a rendimiento nos hace pensar que el Intel i5-13600K es el mejor en casi todo aspecto en esa comparativa mano a mano.

---

# Tutorial gprof

Para comenzar la el test de profiling g_prof primero debemos tener dos archivos como los que se muestran, que fueron brindados por el profesor.

![Image](https://github.com/user-attachments/assets/72ec18e2-d4dc-479e-b404-5245b3d0b332)

Dentro de estos encontramos lo siguiente:
test_gprof.c: 
test_gprof_new.c:

Se compilan ambos archivos juntos para obtener test_gprof (como ejecutable). Este se corre en la terminal y se genera un archivo de salida gmon.out

![Image](https://github.com/user-attachments/assets/a5d713a1-5a1b-44bd-af49-cdf40916026d)

Este archivo se puede manejar para obtener la salida en un archivo analysis.txt, donde se guardará toda la información que devuelve el test.

El instructivo nos brinda diferentes formas de ejecutar el test dependiendo de la información específica que se requiera. A continuación se detalla la salida de cada ejecución.

![Image](https://github.com/user-attachments/assets/74de356f-62fa-4a43-a304-d2382dab25e0)



### - gprof -a test_gprof gmon.out > analysis.txt

Aplicando la flag -a se suprimen las funciones declaradas estáticamente (privadas). Por ejemplo, en este caso la func2 no devolverá información por ser estática.

![Image](https://github.com/user-attachments/assets/fe628b27-24f7-40e3-ab02-b1a075c15e7d)



### - gprof -b test_gprof gmon.out > analysis.txt

Aplicando la flag -b se suprimen los textos detallados. Entonces podemos observar que se obtienen solo gráficos y resultados concretos del test.

![Image](https://github.com/user-attachments/assets/20523f80-0183-4710-a5a8-8a2ec67296a8)



### - gprof -p -b test_gprof gmon.out > analysis.txt

Aplicando la flag -p se obtiene como salida solo el perfil plano.

![Image](https://github.com/user-attachments/assets/e4cd8337-f6c2-406a-a8a1-fb87c07ebe3b)



### - gprof -p<función> -b test_gprof gmon.out > analysis.txt

Aplicando la flag -p<funcion> se imprime la información relacionada con la función indicada.

![Image](https://github.com/user-attachments/assets/7303302e-a90c-466b-b66b-4a5ec115f57f)



### - gprof -P -b test_gprof gmon.out > analysis.txt

Aplicando la flag -P se suprime el flat profile.

![Image](https://github.com/user-attachments/assets/fe44c884-16c3-4c5a-b66d-d0fcda4582f3)



### - gprof -P<función> -b test_gprof gmon.out > analysis.txt

Aplicando esta flag se suprime la función determinada en el flat profile.

![Image](https://github.com/user-attachments/assets/6495901f-981b-4b57-897f-9cca32dcec0e) 



### - gprof -q -b test_gprof gmon.out > analysis.txt

Aplicando la flag -q se imprime solo graph information.

![Image](https://github.com/user-attachments/assets/14ab051e-668d-4bb5-b5c7-5f26d7368900)


 
### - gprof -q<función> -b test_gprof gmon.out > analysis.txt

Aplicando esta flag se imprime solo la información solicitada en call graph.

![Image](https://github.com/user-attachments/assets/35980b63-bea6-470d-a466-6e929d936a99)



### - gprof -Q -b test_gprof gmon.out > analysis.txt

Aplicando la flag -Q se suprime call graph.

![Image](https://github.com/user-attachments/assets/c73d55d8-6145-47fd-a891-d1e66e164869)



### - gprof -Q<función> -b test_gprof gmon.out > analysis.txt

Aplicando la flag -Q<función> se suprime graph information sobre la función seleccionada.

![Image](https://github.com/user-attachments/assets/5b8af77f-b4e4-4080-86eb-620b21dec37d)

---

# Benchmarks

## _**Motion Mark 1.0 - Capacidad renderizado gráfico browser.**__

 1. Benchmark que mide la capacidad de renderizado gráfico de un navegador.


 2. Evalúa el rendimiento en animaciones y gráficos 2D basados en HTML5 y JavaScript.


 3. Usa múltiples escenarios con diferentes niveles de carga gráfica para probar la GPU y CPU.


 4. Su resultado se expresa en puntos, reflejando cuántos FPS puede mantener el navegador.

![Image](https://github.com/user-attachments/assets/205f651e-2972-420c-abf9-9bcbca6530b9)



## _**Basemark - Cargado y renderizado de páginas._**

1. Benchmark multiplataforma que evalúa el rendimiento de navegadores y dispositivos.


2. Mide gráficos con WebGL, ejecución de JavaScript y capacidad de procesamiento de datos.


3. Realiza pruebas intensivas para simular aplicaciones web complejas y juegos en el navegador.


4. Su puntuación final representa la eficiencia del sistema en tareas web exigentes.

![Image](https://github.com/user-attachments/assets/039b1ab8-780a-4c80-bd79-bec172b48fa6)



## _**ARES-6 - Memoria y eficiencia energética browser.**_

1. Benchmark diseñado para medir el rendimiento de motores de JavaScript modernos.


2. Evalúa la ejecución de código avanzado como promesas, clases y manipulación de objetos.


3. Simula cargas de trabajo reales utilizadas en aplicaciones web dinámicas.


4. Su puntuación refleja la velocidad con la que el motor ejecuta código en milisegundos.

![Image](https://github.com/user-attachments/assets/348c140b-6cda-4f40-be8e-6a1ab63c57a7)



## _**Sysbench - Prueba el rendimiento del CPU ejecutando operaciones matemáticas.**_

1. Herramienta de benchmarking que evalúa CPU, memoria y disco en sistemas Linux.


2. Realiza operaciones matemáticas intensivas para medir la velocidad del procesador.


3. Puede ejecutar pruebas de I/O para evaluar la velocidad de lectura y escritura en disco.


4. Permite generar carga en múltiples hilos para simular estrés en el hardware.

![Image](https://github.com/user-attachments/assets/f1b4a275-4b8f-4183-8897-5afbc642f3f6)

---

# Prueba práctica

Para la experiencia de modificar la frecuencia de una placa y revisar el tiempo que tarda en hacer cálculos hemos utilizado una placa ESP32 NodeMCU. 
Se programó para calcular la serie de Fibonacci de 5000, calculando el tiempo con frecuencias de 80 Mhz, 160 Mhz y 240 Mhz.

![Image](https://github.com/user-attachments/assets/1de1fe35-147c-48fe-9646-1203b3425c54)

Como se puede observar en la imagen, al variar la frecuencia se puede considerar una variación del tiempo cercana a la lineal.
