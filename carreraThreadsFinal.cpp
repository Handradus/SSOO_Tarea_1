#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib> // Para rand() y atoi()
#include <ctime>   // Para inicializar la semilla del generador de números aleatorios
#include <vector>

using namespace std;

// Constantes que definen los valores máximos y mínimos
const int MAX_PROGRESS = 10; // Máximo avance por iteración en metros
const int MIN_DELAY = 100;   // Tiempo mínimo de espera en milisegundos
const int MAX_DELAY = 500;   // Tiempo máximo de espera en milisegundos

// Códigos ANSI para colores en la terminal
const string GREEN = "\033[32m"; // Color verde para indicar que un auto termina
const string RESET = "\033[0m";  // Reinicia el color al valor predeterminado

// Variables globales compartidas
mutex mtx;        // Mutex para evitar condiciones de carrera en el acceso a la salida y leaderboard
int *leaderboard; // Puntero al array que almacenará los resultados de la carrera (posiciones de los autos)
int position = 1; // Variable global para rastrear la posición de llegada

void move_car(int finish, string car_name, int id_car)
{
    int distance_traveled = 0, progress;

    while (distance_traveled < finish)
    {
        progress = rand() % MAX_PROGRESS + 1;
        distance_traveled += progress;

        if (distance_traveled >= finish)
        {
            // Sección crítica la cual requiere el uso de mutex
            mtx.lock();
            cout << GREEN << car_name << " avanza " << progress << " metros y termina la carrera en el lugar " << position << "!" << RESET << endl;
            leaderboard[position - 1] = id_car; // Se guarda el numero del auto en el leaderboard en orden de llegada a la meta
            position++;                         // Se incrementa el lugar de llegada para el siguiente auto
            mtx.unlock();
            return;
        }

        // Sección crítica la cual requiere el uso de mutex
        mtx.lock();
        cout << car_name << " avanza " << progress << " metros (total: " << distance_traveled << " metros)" << endl;
        mtx.unlock();

        // La hebra se detiene por un tiempo aleatorio entre MIN_DELAY y MAX_DELAY milisegundos
        this_thread::sleep_for(chrono::milliseconds(rand() % (MAX_DELAY - MIN_DELAY + 1) + MIN_DELAY));
    }
}

int main(int argc, char *argv[])
{
    srand(time(0)); // Inicializa la semilla para los números aleatorios
    if (argc != 3)  // Mensaje de uso en caso de error en los argumentos
    {
        cout << "Uso: ./code <metros> <autos>";
        return 1;
    }

    int finish = atoi(argv[1]), cars = atoi(argv[2]); // Se convierte la entrada de argumentos a enteros
    if (finish < 1 || cars < 1)
    {
        cout << "Error: Debe ingresar enteros positivos mayores o iguales a 1.\n";
        return 1;
    }

    leaderboard = new int[cars]; // Se asigna memoria para almacenar los resultados de la carrera
    thread car[cars];            // Se crea un array de hebras para los autos

    cout << "Distancia total carrera: " << finish << " metros" << endl;
    cout << "---------------------------------------" << endl;

    // Se lanzan las hebras, cada una representando un auto
    for (int i = 0; i < cars; i++)
    {
        string car_name = "Auto" + to_string(i);        // Se asigna un nombre único al auto
        car[i] = thread(move_car, finish, car_name, i); // Se inicia la hebra con la función move_car
    }

    // Se espera a que todas las hebras terminen
    for (int i = 0; i < cars; i++)
    {
        car[i].join();
    }

    // Se muestra el leaderboard final con las posiciones de llegada
    cout << "Lugar \t Auto" << endl;
    cout << "---------------" << endl;
    for (int i = 0; i < cars; i++)
    {
        cout << i + 1 << " \t " << "Auto" << leaderboard[i] << endl;
    }

    delete[] leaderboard; // Se libera la memoria asignada para el leaderboard

    return 0;
}
