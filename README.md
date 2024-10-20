# Simulador de carrera de autos usando multihebras
Este programa simula una carrera de autos utilizando programación multihebras en C++. Cada auto es ejecutado en una hebra separada y la carrera finaliza cuando todos los autos han recorrido la distancia indicada.

## Requisitos:
- Sistema operativo Linux.
- Compilador GNU g++. En caso de no tenerlo instalado. Ejecutar los siguientes comandos:

        sudo apt-get update
        sudo apt-get install g++

- Makefile para la compilación. En caso de no tenerlo instalado. Ejecutar los siguientes comandos:

        sudo apt-get update
        sudo apt-get install make


## Instalacion y ejecución:  
1. Clonar repositorio:

        git clone https://github.com/Handradus/SSOO_Tarea_1.git

2. Compilar archivo usando el siguiente comando:

        make

3. Ejecutar ingresando por parámetro la distancia total a recorrer (metros) y la cantidad de competidores (autos), la cual deben ser números enteros mayores o iguales a 1:

        ./carrerasThreadsFinal <metros> <autos>

### Ejemplo de ejecución:

    make
    ./carrerasThreadsFinal 100 3

    Distancia total carrera: 100 metros
    ---------------------------------------
    Auto1 avanza 9 metros (total: 9 metros)
    Auto2 avanza 1 metros (total: 1 metros)
    Auto1 avanza 10 metros (total: 19 metros)
    Auto2 avanza 1 metros (total: 2 metros)
    
    ...
    
    Auto1 avanza 7 metros y termina la carrera en el lugar 1!
    Auto2 avanza 9 metros (total: 94 metros)
    Auto0 avanza 7 metros (total: 98 metros)
    Auto0 avanza 6 metros y termina la carrera en el lugar 2!
    Auto2 avanza 1 metros (total: 95 metros)
    Auto2 avanza 9 metros y termina la carrera en el lugar 3!

    Lugar   Auto
    ---------------
    1       Auto1
    2       Auto0
    3       Auto2