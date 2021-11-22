# Proyecto final Multiprocesadores
Instrucciones generales
- Ejecutar cada programa de 1 a 200 threads
## ¿Cómo ejecutar los códigos?
### 1. Compilar el programa de la siguiente forma:
```
gcc -fopenmp {nombre_programa.c} -o {nombre_programa}
```
Ejemplo:
```
gcc -fopenmp integral.c -o integral
```
### 2. Dentro de una terminal tipo Unix/Linux o Git Bash, ejecutar el binario redirigiendo la salida a un archivo CSV.
```
./{nombre_programa} > {nombre_programa}_results.csv
```
Ejemplo:
```
./integral > integral_results.csv
```
### 3. Abrir el CSV generado con Excel. Copiar y pegar resultados en {nombre_programa}_results.csv en una pestaña diferente para cada equipo/nube.