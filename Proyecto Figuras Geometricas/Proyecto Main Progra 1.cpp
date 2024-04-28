#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>

using namespace std;

int currentX, currentY;

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
}

void dibujarTriangulo(int base, int x, int y) {
    int altura = base / 2 + 1;
    for (int i = 0; i < altura; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < altura - i - 1; j++) {
            cout << " ";
        }
        for (int k = 0; k < 2 * i + 1; k++) {
            cout << "*";
        }
        cout << endl;
    }
}

void dibujarCuadrado(int lado, int x, int y) {
    for (int i = 0; i < lado; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < lado * 2; j += 2) {
            cout << "* ";
        }
        cout << endl;
    }
}

void dibujarRectangulo(int base, int altura, int x, int y) {
    for (int i = 0; i < altura; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < base * 2; j += 2) {
            cout << "* ";
        }
        cout << endl;
    }
}

void dibujarCirculo(int radio, int x, int y) {
    for (int i = -radio; i <= radio; i++) {
        gotoxy(x - radio * 2, y + i);
        for (int j = -radio * 2; j <= radio * 2; j += 2) {
            if (sqrt(i * i + (j / 2) * (j / 2)) <= radio) {
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void mostrarMenu() {
    char opcion;
    do {
        system("cls");
        cout << "Seleccione la figura geometrica que deseas dibujar:" << endl;
        cout << "1. Triangulo equilatero" << endl;
        cout << "2. Cuadrado" << endl;
        cout << "3. Rectangulo" << endl;
        cout << "4. Circulo" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        switch(opcion) {
            case '1': {
                int base;
                cout << "Ingrese la medida de la base del triangulo: ";
                cin >> base;
                int x, y;
                centrarFigura(base, base / 2 + 1, x, y);
                currentX = x + base / 2;
                currentY = y + base / 2;
                cout << "Triangulo equilatero:" << endl;
                dibujarTriangulo(base, x, y);
                char tecla;
                cout << "Para salir presiona la letra X ";
                do {
                    tecla = _getch();
                    if (tecla == 'a') {
                        if (currentX > x) {
                            gotoxy(--currentX, currentY);
                        }
                    } else if (tecla == 'd') {
                        if (currentX < x + base - 1) {
                            gotoxy(++currentX, currentY);
                        }
                    } else if (tecla == 'w') {
                        if (currentY > y) {
                            gotoxy(currentX, --currentY);
                        }
                    } else if (tecla == 's') {
                        if (currentY < y + base / 2) {
                            gotoxy(currentX, ++currentY);
                        }
                    }
                } while (tecla != 'x');
                break;
            }
            case '2': {
                int lado;
                cout << "Ingrese la medida de un lado del cuadrado: ";
                cin >> lado;
                int x, y;
                centrarFigura(lado * 2, lado, x, y);
                currentX = x + 2;
                currentY = y + 1;
                cout << "Cuadrado:" << endl;
                dibujarCuadrado(lado, x, y);
                char tecla;
                cout << "Para salir presiona la letra X ";
                do {
                    tecla = _getch();
                    if (tecla == 'a') {
                        if (currentX > x + 2) {
                            gotoxy(--currentX, currentY);
                        }
                    } else if (tecla == 'd') {
                        if (currentX < x + lado * 2 - 2) {
                            gotoxy(++currentX, currentY);
                        }
                    } else if (tecla == 'w') {
                        if (currentY > y + 1) {
                            gotoxy(currentX, --currentY);
                        }
                    } else if (tecla == 's') {
                        if (currentY < y + lado) {
                            gotoxy(currentX, ++currentY);
                        }
                    }
                } while (tecla != 'x');
                break;
            }
            case '3': {
                int base, altura;
                cout << "Ingrese la medida de la base del rectangulo: ";
                cin >> base;
                cout << "Ingrese la medida de la altura del rectangulo: ";
                cin >> altura;
                int x, y;
                centrarFigura(base * 2, altura, x, y);
                currentX = x + 2;
                currentY = y + 1;
                cout << "Rectangulo:" << endl;
                dibujarRectangulo(base, altura, x, y);
                char tecla;
                cout << "Para salir presiona la letra X ";
                do {
                    tecla = _getch();
                    if (tecla == 'a') {
                        if (currentX > x + 2) {
                            gotoxy(--currentX, currentY);
                        }
                    } else if (tecla == 'd') {
                        if (currentX < x + base *

2 - 2) {
                            gotoxy(++currentX, currentY);
                        }
                    } else if (tecla == 'w') {
                        if (currentY > y + 1) {
                            gotoxy(currentX, --currentY);
                        }
                    } else if (tecla == 's') {
                        if (currentY < y + altura) {
                            gotoxy(currentX, ++currentY);
                        }
                    }
                } while (tecla != 'x');
                break;
            }
            case '4': {
                int radio;
                cout << "Ingrese la medida del radio del circulo: ";
                cin >> radio;
                int x, y;
                centrarFigura(radio * 4, radio * 2, x, y);
                currentX = x + 2;
                currentY = y + 1;
                cout << "Circulo:" << endl;
                dibujarCirculo(radio, x, y);
                char tecla;
                cout << "Para salir presiona la letra X ";
                do {
                    tecla = _getch();
                    if (tecla == 'a') {
                        if (currentX > x + 2) {
                            gotoxy(--currentX, currentY);
                        }
                    } else if (tecla == 'd') {
                        if (currentX < x + radio * 4 - 2) {
                            gotoxy(++currentX, currentY);
                        }
                    } else if (tecla == 'w') {
                        if (currentY > y + 1) {
                            gotoxy(currentX, --currentY);
                        }
                    } else if (tecla == 's') {
                        if (currentY < y + radio * 2) {
                            gotoxy(currentX, ++currentY);
                        }
                    }
                } while (tecla != 'x');
                break;
            }
            case '5':
                cout << "Regresando al programa principal..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intentelo de nuevo." << endl;
        }
    } while (opcion != '5');
}

int main() {
    cout << "Presiona la tecla F12 para mostrar el menu..." << endl;
    while (true) {
        if (GetAsyncKeyState(VK_F12) & 0x8000) {
            cout << " Bienvenido Ismael!" << endl;
            mostrarMenu();
            break;
        }
    }
    return 0;
}
