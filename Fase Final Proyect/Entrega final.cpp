#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
# include <string>
#include <fstream>
#include <vector>

using namespace std;




const int COLOR_DEFAULT = 7;
const int COLOR_RED = 12;
const int COLOR_GREEN = 10;
const int COLOR_BLUE = 9;

int currentX = 0;
int currentY = 0;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void seleccionarColor() {
    cout << "Seleccione el color del texto:" << endl;
    cout << "1. Rojo" << endl;
    cout << "2. Verde" << endl;
    cout << "3. Azul" << endl;
    cout << "4. Predeterminado" << endl;

    char opcion = _getch(); // Captura la tecla presionada

    switch (opcion) {
        case '1':
            setColor(COLOR_RED); // Cambia el color del texto a rojo
            cout << "Color cambiado a rojo." << endl;
            break;
        case '2':
            setColor(COLOR_GREEN); // Cambia el color del texto a verde
            cout << "Color cambiado a verde." << endl;
            break;
        case '3':
            setColor(COLOR_BLUE); // Cambia el color del texto a azul
            cout << "Color cambiado a azul." << endl;
            break;
        case '4':
            setColor(COLOR_DEFAULT); // Restaura el color predeterminado del texto
            cout << "Color cambiado al predeterminado." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
    }
}



char caracter = '*'; // Define la variable caracter fuera de cualquier función


void seleccionarCaracter() {
    cout << "Seleccione el caracter con el que desea graficar las figuras:" << endl;
    cout << "1. * (Asterisco)" << endl;
    cout << "2. + (Signo mas)" << endl;


    char opcion = _getch(); // Captura la tecla presionada

    switch (opcion) {
        case '1':
            caracter = '*'; // Asigna el valor '*' a la variable caracter
            cout << "Caracter seleccionado: *" << endl;
            break;
        case '2':
            caracter = '+'; // Asigna el valor '+' a la variable caracter
            cout << "Caracter seleccionado: +" << endl;
            break;
        default:
            cout << "Opción no valida. Se mantendrá el carácter anterior." << endl;
            break;
    }
}


void grabarPantalla() {
    string rutaArchivo, nombreArchivo;

    cout << "Ingrese la ruta completa del archivo para guardar el contenido de la pantalla: ";
    getline(cin, rutaArchivo);

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    string rutaCompleta = rutaArchivo + "\\" + nombreArchivo;

    ofstream archivo(rutaCompleta);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD bufferSize = csbi.dwSize;

    CHAR_INFO *buffer = new CHAR_INFO[bufferSize.X * bufferSize.Y];

    COORD bufferCoord = {0, 0};
    SMALL_RECT readRect = {0, 0, bufferSize.X - 1, bufferSize.Y - 1};

    if (!ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), buffer, bufferSize, bufferCoord, &readRect)) {
        cout << "Error al leer la pantalla." << endl;
        delete[] buffer;
        return;
    }

    for (int y = 0; y < bufferSize.Y; y++) {
        for (int x = 0; x < bufferSize.X; x++) {
            archivo << buffer[y * bufferSize.X + x].Char.AsciiChar;
        }
        archivo << endl;
    }

    archivo.close();
    delete[] buffer;

    cout << "El contenido de la pantalla se ha guardado en el archivo \"" << rutaCompleta << "\"." << endl;
}




void abrirArchivo() {
    string ruta;
    cout << "Ingrese la ruta del archivo a abrir: ";
    getline(cin, ruta);
    ifstream archivo(ruta);
    if (archivo.is_open()) {
        cout << "Contenido del archivo:" << endl;
        char caracter;
        while (archivo.get(caracter)) {
            cout << caracter;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void centrarFigura(int anchoFigura, int altoFigura, int &x, int &y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    x = (screenWidth - anchoFigura) / 2;
    y = (screenHeight - altoFigura) / 2;
    gotoxy(x, y);
}

void limpiarPantalla() {
    system("cls"); // Limpia la pantalla ejecutando el comando "cls"
}

void mostrarMensajeLimpiarPantalla() {
    limpiarPantalla(); // Limpia la pantalla
    cout << "La pantalla ha sido limpiada." << endl;
}




void dibujarTriangulo(int base, int x, int y, string orientacion) {

  int altura = base / 2 + 1;
    if (orientacion == "Arriba") {
        for (int i = 0; i < altura; i++) {
            gotoxy(x, y + i);
            for (int j = 0; j < altura - i - 1; j++) {
                cout << " ";
            }
            for (int k = 0; k < 2 * i + 1; k++) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Abajo") {
        for (int i = altura - 1; i >= 0; i--) {
            gotoxy(x, y + (altura - 1 - i));
            for (int j = 0; j < altura - i - 1; j++) {
                cout << " ";
            }
            for (int k = 0; k < 2 * i + 1; k++) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Derecha") {
        for (int i = 0; i < altura; i++) {
            gotoxy(x + i, y + i);
            for (int k = 0; k <= i; k++) {
                cout << " ";
            }
            cout << endl;
        }
        for (int i = altura - 2; i >= 0; i--) {
            gotoxy(x + (altura - 1 - i), y + (altura - 1 - i));
            for (int k = 0; k <= i; k++) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Izquierda") {
        for (int i = 0; i < altura; i++) {
            gotoxy(x - i, y + i);
            for (int k = 0; k <= i; k++) {
                cout << " ";
            }
            cout << endl;
        }
        for (int i = altura - 2; i >= 0; i--) {
            gotoxy(x - (altura - 1 - i), y + (altura - 1 - i));
            for (int k = 0; k <= i; k++) {
                cout << caracter;
            }
            cout << endl;
        }
    }
}

void dibujarCuadrado(int lado, int x, int y, string orientacion) {
    if (orientacion == "Arriba" || orientacion == "Abajo") {
        for (int i = 0; i < lado; i++) {
            gotoxy(x, y + i);
            for (int j = 0; j < lado * 2; j += 2) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Derecha" || orientacion == "Izquierda") {
        for (int i = 0; i < lado; i++) {
            gotoxy(x + i, y);
            for (int j = 0; j < lado; j++) {
                cout << caracter;
            }
            cout << endl;
        }
    }
}

void dibujarRectangulo(int base, int altura, int x, int y, string orientacion) {
    if (orientacion == "Arriba") {
        for (int i = 0; i < altura; i++) {
            gotoxy(x, y + i);
            for (int j = 0; j < base * 2; j += 2) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Abajo") {
        for (int i = altura - 1; i >= 0; i--) {
            gotoxy(x, y + (altura - 1 - i));
            for (int j = 0; j < base * 2; j += 2) {
                cout << caracter;
            }
            cout << endl;
        }
    }
}

void dibujarCirculo(int radio, int x, int y, char caracter) {
    for (int i = -radio; i <= radio; i++) {
        for (int j = -radio; j <= radio; j++) {
            if (sqrt(i * i + j * j) <= radio) {
                gotoxy(x + j, y + i);
                cout << caracter;
            }
        }
    }
}

void dibujarLinea(int longitud, int x, int y, string orientacion) {
    gotoxy(x, y);
    if (orientacion == "Arriba") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x, y - i);
            cout << caracter;
        }
    } else if (orientacion == "Abajo") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x, y + i);
            cout << caracter;
        }
    } else if (orientacion == "Derecha") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x + i, y);
            cout << caracter;
        }
    } else if (orientacion == "Izquierda") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x - i, y);
            cout << caracter;
        }
    } else if (orientacion == "Diagonal Derecha Arriba") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x + i, y - i);
            cout << caracter;
        }
    } else if (orientacion == "Diagonal Derecha Abajo") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x + i, y + i);
            cout << caracter;
        }
    } else if (orientacion == "Diagonal Izquierda Arriba") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x - i, y - i);
            cout << caracter;
        }
    } else if (orientacion == "Diagonal Izquierda Abajo") {
        for (int i = 0; i < longitud; i++) {
            gotoxy(x - i, y + i);
            cout << caracter;
        }
    }
}

void dibujarRombo(int diagonal, int x, int y, string orientacion) {
    int mitad = diagonal / 2;
    if (orientacion == "Arriba") {
        for (int i = 0; i <= mitad; i++) {
            gotoxy(x + mitad - i, y + i);
            for (int j = 0; j < 2 * i + 1; j++) {
                cout << caracter;
            }
            cout << endl;
        }
        for (int i = mitad - 1; i >= 0; i--) {
            gotoxy(x + mitad - i, y + (diagonal - 1) - i);
            for (int j = 0; j < 2 * i + 1; j++) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Abajo") {
        for (int i = 0; i <= mitad; i++) {
            gotoxy(x + mitad - i, y - i);
            for (int j = 0; j < 2 * i + 1; j++) {
                cout << caracter;
            }
            cout << endl;
        }
        for (int i = mitad - 1; i >= 0; i--) {
            gotoxy(x + mitad - i, y - (diagonal - 1) + i);
            for (int j = 0; j < 2 * i + 1; j++) {
                cout << caracter;
            }
            cout << endl;
        }
    }
}

void dibujarHexagono(int lado, int x, int y, string orientacion) {
    int altura = lado;
    if (orientacion == "Vertical") {
        for (int i = 0; i < lado; i++) {
            gotoxy(x + lado - i - 1, y + i);
            for (int j = 0; j < lado + 2 * i; j++) {
                cout << caracter;
            }
            cout << endl;
        }
        for (int i = lado - 2; i >= 0; i--) {
            gotoxy(x + lado - i - 1, y + (altura + lado - i - 1));
            for (int j = 0; j < lado + 2 * i; j++) {
                cout << caracter;
            }
            cout << endl;
        }
    } else if (orientacion == "Horizontal") {
        for (int i = 0; i < lado; i++) {
            gotoxy(x + i, y + lado - i - 1);
            for (int j = 0; j < lado + 2 * i; j++) {
                cout << caracter;
            }
            cout << endl;
        }
        for (int i = lado - 2; i >= 0; i--) {
            gotoxy(x + lado - i - 1, y + (altura + lado - i - 1));
            for (int j = 0; j < lado + 2 * i; j++) {
                cout << caracter;
            }
            cout << endl;
        }
    }
}



int main(){
    vector<pair<int, int>> coordenadas_figuras;




    char opcion;
    do {
         opcion = _getch();
    if (opcion == '0') { // Verifica si la tecla presionada es el número 0
        cout << "Seleccionaste la opcion: Grabar pantalla" << endl;
        grabarPantalla();
        continue;

    }

    if (opcion == '5') { // Verifica si la tecla presionada es el número 0
        cout << "Seleccionaste la opcion: Abrir archivo" << endl;
        abrirArchivo();
        continue;
    }

         // Vuelve al inicio del bucle sin mostrar el mensaje "Opcion no reconocida"



        cout << "---- Menu Inicial -----" << endl;
        cout << "F1. Triangulo equilatero" << endl;
        cout << "F2. Cuadrado" << endl;
        cout << "F3. Rectangulo" << endl;
        cout << "F4. Circulo" << endl;
        cout << "F5. Linea" << endl;
        cout << "F6. Rombo" << endl;
        cout << "F7. Hexagono" << endl;
        cout << "F8. Nuevo caracter" << endl;
        cout << "F9. Limpiar pantalla "<< endl;
        cout << "F10. Color de Caracter " << endl;
        cout << "F12. Grabar pantalla" << endl;
        cout << "Ctrl + A. Abrir archivo y mostrar en pantalla " << endl;
        cout << "Presiona la tecla correspondiente para elegir una opcion:" << endl;
        cout << "" << endl;

        opcion = _getch(); // Captura la tecla presionada

        switch(opcion) {
            case 0: // Comprueba si es una tecla especial
            case 224: {
                opcion = _getch(); // Captura el segundo byte de la secuencia de teclas especiales
                switch(opcion) {
                    case 59: {// Código ASCII para F1
                      int base;
                string orientacion;
                cout << "Ingrese la base del triangulo: ";
                cin >> base;
                cout << "Arriba, Abajo, Derecha, Izquierda:";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(base, base / 2 + 1, x, y);
                dibujarTriangulo(base, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;
                    }
                    case 60: { // Código ASCII para F2
                        cout << "Seleccionaste la opcion: Cuadrado" << endl;
                            int lado;
                string orientacion;
                cout << "Ingrese la medida de un lado del cuadrado: ";
                cin >> lado;
                cout << "Ingrese la orientacion (Arriba, Abajo, Derecha, Izquierda): ";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(lado * 2, lado, x, y);
                dibujarCuadrado(lado, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;// Aquí puedes llamar a la función correspondiente para dibujar un cuadrado
                }
                    case 61: { // Código ASCII para F3
                        cout << "Seleccionaste la opcion: Rectangulo" << endl;
                            int base, altura;
                string orientacion;
                cout << "Ingrese la medida de la base del rectangulo: ";
                cin >> base;
                cout << "Ingrese la medida de la altura del rectangulo: ";
                cin >> altura;
                cout << "Ingrese la orientacion (Arriba, Abajo): ";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(base * 2, altura, x, y);
                dibujarRectangulo(base, altura, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;// Aquí puedes llamar a la función correspondiente para dibujar un rectángulo
                }
                     case 62: { // Código ASCII para F4
                        cout << "Seleccionaste la opcion: Circulo" << endl;
                        int radio;
                        cout << "Ingrese la medida del radio del circulo: ";
                        cin >> radio;
                        int x, y;
                        centrarFigura(radio * 4, radio * 2, x, y);
                        dibujarCirculo(radio, x, y, '*'); // Cambiar '*' por el caracter deseado
                        coordenadas_figuras.push_back(make_pair(x, y));
                        break;
                    }
                    case 63: {// Código ASCII para F5
                        cout << "Seleccionaste la opcion: Linea" << endl;
                            int longitud;
                string orientacion;
                cout << "Ingrese la medida de la longitud de la linea: ";
                cin >> longitud;
                cout << "Ingrese la orientacion (Arriba, Abajo, Derecha, Izquierda, Diagonal Derecha Arriba, Diagonal Derecha Abajo, Diagonal Izquierda Arriba, Diagonal Izquierda Abajo): ";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(longitud, 1, x, y);
                dibujarLinea(longitud, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;// Aquí puedes llamar a la función correspondiente para dibujar una línea
                }
                    case 64: { // Código ASCII para F6
                        cout << "Seleccionaste la opcion: Rombo" << endl;
                           int diagonal;
                string orientacion;
                cout << "Ingrese la medida de la diagonal del rombo: ";
                cin >> diagonal;
                cout << "Ingrese la orientacion (Arriba, Abajo): ";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(diagonal, diagonal, x, y);
                dibujarRombo(diagonal, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;// Aquí puedes llamar a la función correspondiente para dibujar un rombo
                   }

                    case 65: {// Código ASCII para F7
                        cout << "Seleccionaste la opcion: Hexagono" << endl;
                           int lado;
                string orientacion;
                cout << "Ingrese la medida del lado del hexagono: ";
                cin >> lado;
                cout << "Ingrese la orientacion (Vertical, Horizontal): ";
                cin.ignore();
                getline(cin, orientacion);
                int x, y;
                centrarFigura(lado * 2 + lado, lado * 2, x, y);
                dibujarHexagono(lado, x, y, orientacion);
                coordenadas_figuras.push_back(make_pair(x, y));
                break;// Aquí puedes llamar a la función correspondiente para dibujar un hexágono
                }
                    case 66: {// Código ASCII para F8
                        cout << "Seleccionaste la opcion: Nuevo caracter" << endl;
                           seleccionarCaracter();

                // Aquí puedes llamar a la función correspondiente para la opción Nuevo Caracter
                        break;
                    }
                    case 67: {// Código ASCII para F9
                        cout << "Seleccionaste la opcion: Limpiar pantalla" << endl;
                         mostrarMensajeLimpiarPantalla(); // Aquí puedes llamar a la función correspondiente para la opción Limpiar Pantalla
                        break;
                    }
                    case 68: { // Código ASCII para F10
                        cout << "Seleccionaste la opcion: Color de Caracter" << endl;
                             seleccionarColor();  // Aquí puedes llamar a la función correspondiente para la opción Color de Caracter
                        break;
                }
                    case 53: { // Código ASCII para el número 5
                       cout << "Seleccionaste la opcion: Grabar pantalla" << endl;
                        grabarPantalla();
                       break;
                }
                    case 164: { // Código ASCII para la letra "ñ"
                cout << "Seleccionaste la opcion: Abrir archivo y mostrar en pantalla" << endl;
                abrirArchivo(); // Llama a la función correspondiente para abrir archivo
                break;

                    }
                    default:
                        cout << "Opcion no reconocida" << endl;
                        break;
                }
                break;
            }
            default:
                cout << "Opcion no reconocida" << endl;
                break;
        }


        _getch(); // Espera a que el usuario presione cualquier tecla para continuar

    } while (true); // Salir del menú cuando se presione la tecla 'x'


      return 0;
}

