#include <iostream>
#include <string>

using namespace std;


struct Alumno {
    string carne;
    string nombre;
    int edad;
    char sexo;
    int matematica;
    int ciencias;
    int computacion;
    int fisica;
    int idioma;
    int literatura;
};

const int NUM_ALUMNOS = 10;


float calcularPromedio(const Alumno& alumno) {
    return (alumno.matematica + alumno.ciencias + alumno.computacion + alumno.fisica + alumno.idioma + alumno.literatura) / 6.0;
}

int main() {
    Alumno alumnos[NUM_ALUMNOS];


    for (int i = 0; i < NUM_ALUMNOS; ++i) {
        cout << "Ingrese informacion del alumno " << i+1 << ":" << endl;
        cout << "Carne: ";
        cin >> alumnos[i].carne;
        cout << "Nombre: ";
        cin.ignore();
        getline(cin, alumnos[i].nombre);
        cout << "Edad: ";
        cin >> alumnos[i].edad;
        cout << "Sexo (M/F): ";
        cin >> alumnos[i].sexo;
        cout << "Nota de Matematica: ";
        cin >> alumnos[i].matematica;
        cout << "Nota de Ciencias: ";
        cin >> alumnos[i].ciencias;
        cout << "Nota de Computacion: ";
        cin >> alumnos[i].computacion;
        cout << "Nota de Fisica: ";
        cin >> alumnos[i].fisica;
        cout << "Nota de Idioma: ";
        cin >> alumnos[i].idioma;
        cout << "Nota de Literatura: ";
        cin >> alumnos[i].literatura;
    }


    int hombres = 0;
    int mujeres = 0;
    int menorEdad = alumnos[0].edad;
    string nombresMenorEdad;
    int clasesReprobadasCarlos = 0;
    string nombresAprobados;
    float promedioMasAlto = 0;
    string nombreMasAlto;
    float promedioMasBajo = 100;
    string nombreMasBajo;
    float sumaMatematica = 0;
    float promedioMatematica;
    float promedioMayorHombre = 0;
    string nombreMayorHombre;
    float promedioMayorMujer = 0;
    string nombreMayorMujer;
    int maxReprobadas = 0;
    string nombreMaxReprobadas;
    string cursosReprobadosMax;


    for (int i = 0; i < NUM_ALUMNOS; ++i) {

        if (alumnos[i].sexo == 'M') {
            hombres++;
        } else {
            mujeres++;
        }

        if (alumnos[i].edad < menorEdad) {
            menorEdad = alumnos[i].edad;
            nombresMenorEdad = alumnos[i].nombre;
        } else if (alumnos[i].edad == menorEdad) {
            nombresMenorEdad += ", " + alumnos[i].nombre;
        }

        if (alumnos[i].nombre == "Carlos Suarez") {
            if (alumnos[i].matematica < 61) clasesReprobadasCarlos++;
            if (alumnos[i].ciencias < 61) clasesReprobadasCarlos++;
            if (alumnos[i].computacion < 61) clasesReprobadasCarlos++;
            if (alumnos[i].fisica < 61) clasesReprobadasCarlos++;
            if (alumnos[i].idioma < 61) clasesReprobadasCarlos++;
            if (alumnos[i].literatura < 61) clasesReprobadasCarlos++;
        }

        if (alumnos[i].matematica >= 61 && alumnos[i].ciencias >= 61 && alumnos[i].computacion >= 61 &&
            alumnos[i].fisica >= 61 && alumnos[i].idioma >= 61 && alumnos[i].literatura >= 61) {
            if (!nombresAprobados.empty()) nombresAprobados += ", ";
            nombresAprobados += alumnos[i].nombre;
        }

        float promedio = calcularPromedio(alumnos[i]);
        if (promedio > promedioMasAlto) {
            promedioMasAlto = promedio;
            nombreMasAlto = alumnos[i].nombre;
        }
        if (promedio < promedioMasBajo) {
            promedioMasBajo = promedio;
            nombreMasBajo = alumnos[i].nombre;
        }

        sumaMatematica += alumnos[i].matematica;

        if (alumnos[i].sexo == 'M' && promedio > promedioMayorHombre) {
            promedioMayorHombre = promedio;
            nombreMayorHombre = alumnos[i].nombre;
        } else if (alumnos[i].sexo == 'F' && promedio > promedioMayorMujer) {
            promedioMayorMujer = promedio;
            nombreMayorMujer = alumnos[i].nombre;
        }

        int cursosReprobados = 0;
        if (alumnos[i].matematica < 61) cursosReprobados++;
        if (alumnos[i].ciencias < 61) cursosReprobados++;
        if (alumnos[i].computacion < 61) cursosReprobados++;
        if (alumnos[i].fisica < 61) cursosReprobados++;
        if (alumnos[i].idioma < 61) cursosReprobados++;
        if (alumnos[i].literatura < 61) cursosReprobados++;
        if (cursosReprobados > maxReprobadas) {
            maxReprobadas = cursosReprobados;
            nombreMaxReprobadas = alumnos[i].nombre;
            cursosReprobadosMax = "";
            if (alumnos[i].matematica < 61) cursosReprobadosMax += "Matematicas, ";
            if (alumnos[i].ciencias < 61) cursosReprobadosMax += "Ciencias, ";
            if (alumnos[i].computacion < 61) cursosReprobadosMax += "Computacion, ";
            if (alumnos[i].fisica < 61) cursosReprobadosMax += "Fisica, ";
            if (alumnos[i].idioma < 61) cursosReprobadosMax += "Idioma, ";
            if (alumnos[i].literatura < 61) cursosReprobadosMax += "Literatura, ";

            cursosReprobadosMax = cursosReprobadosMax.substr(0, cursosReprobadosMax.size() - 2);
        }
    }


    cout << "\nEstadisticas:\n";
    cout << "Cantidad de alumnos hombres: " << hombres << endl;
    cout << "Cantidad de alumnas mujeres: " << mujeres << endl;
    cout << "Alumno(s) mas joven(es): " << nombresMenorEdad << endl;
    cout << "Clases reprobadas por Carlos Suarez: " << clasesReprobadasCarlos << endl;
    cout << "Alumno(s) que aprobaron todos los cursos: " << nombresAprobados << endl;
    cout << "Alumno(s) con el promedio mas alto (" << promedioMasAlto << "): " << nombreMasAlto << endl;
    cout << "Alumno(s) con el promedio mas bajo (" << promedioMasBajo << "): " << nombreMasBajo << endl;
    promedioMatematica = sumaMatematica / NUM_ALUMNOS;
    cout << "Nota promedio en Matematicas: " << promedioMatematica << endl;
    cout << "Hombre con el mayor promedio en Matematica, Computacion y Fisica: " << nombreMayorHombre << endl;
    cout << "Mujer con el mayor promedio en Matematica, Computacion y Fisica: " << nombreMayorMujer << endl;
    cout << "Alumno que reprobo mas cursos (" << maxReprobadas << "): " << nombreMaxReprobadas << " (" << cursosReprobadosMax << ")" << endl;

    return 0;
}
