// трёхгранная пирамида
// - 3д пространство (оси для ориентировки)
// - создать
// - цвет границ
////// - заливка
// - подписать
// - связать с клавой
// - переместить
// - повернуть
// - масштабировать

#include <iostream>
#include <math.h>
#include <queue>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

#define P 3.14
#define TEXTCOL 13 //красный 12 белый 15 маждента 13 циан 11 жёлтый 14
#define MAINCOL 11 
#define FILLCOL 14
#define BLACK 0
#define WHITE 15

using namespace std;


// отрисовка линии попиксельно
void line_DDA(float x1, float y1, float x2, float y2, COLORREF cColor, int full) {
    // Целочисленные значения координат начала и конца отрезка, округлённые до ближайшего целого
    int iX1 = roundf(x1);
    int iY1 = roundf(y1);
    int iX2 = roundf(x2);
    int iY2 = roundf(y2);

    // Длина и высота линии
    int deltaX = abs(iX1 - iX2);
    int deltaY = abs(iY1 - iY2);

    // Считаем минимальное количество итераций, необходимое  для отрисовки отрезка
    // Выбирая максимум из длины и высоты линии, обеспечиваем связность линии
    int length = max(deltaX, deltaY);

    // особый случай, на экране закрашивается ровно один пиксель
    if (length == 0) {
        putpixel(iX1, iY1, cColor);
        return;
    }
    // Вычисляем приращения на каждом шаге по осям абсцисс и ординат
    double dX = (x2 - x1) / length;
    double dY = (y2 - y1) / length;

    // Начальные значения
    double x = x1;
    double y = y1;

    length++;
    if (full == 1) {
        // Основной цикл целая линия
        while (length--) {
            x += dX;
            y += dY;
            putpixel(roundf(x), roundf(y), cColor);
        }
    }
    else {
        // Основной цикл пунктир
        int i = 0;
        int curCol = cColor;
        while (length--) {
            x += dX;
            y += dY;
            if (i % 15 == 0 && curCol != cColor) {
                curCol = cColor;
            }
            else if (i % 15 == 0 && curCol == cColor) {
                curCol = BLACK;
            }
            putpixel(roundf(x), roundf(y), curCol);
            i++;
        }
    }

}


// класс для точек
class Point {
public:
    float x;
    float y;
    float z; // z = 0.5x + 0.5y для угла в 45. Проблемы с округлением? не делать короче 2х пикселей тогда??
    char* name;

    void namePoint(char* name) {
        outtextxy(x, y, name);
    }
};


// класс трёхгранной пирамиды
class Piramid {
public:
    Point A;
    Point B;
    Point C;
    Point D;
    char name_A[2] = "A";
    char name_B[2] = "B";
    char name_C[2] = "C";
    char name_D[2] = "D";
    int col = MAINCOL;

    // конструктор
    Piramid() {
        A.x = 20; A.y = 250;
        A.name = name_A;
        B.x = 400; B.y = 50;
        B.name = name_B;
        C.x = 100; C.y = 50;
        C.name = name_C;
        D.x = 10; D.y = 5;
        D.name = name_D;
        drawPiramid();
    }

    // отрисовка
    void drawPiramid() {
        // оси
        // окно 1400 на 700 => центр 700 350
        setcolor(WHITE);
        line(700, 350, 730, 350);
        line(700, 350, 700, 320); // не 380
        line(700, 350, 685, 365); // и не 335, т.к. нужна инверсия по y 

        setcolor(TEXTCOL);
        A.namePoint(A.name);
        B.namePoint(B.name);
        C.namePoint(C.name);
        D.namePoint(D.name);

        line_DDA(A.x, A.y, B.x, B.y, col, 1); // линия 1
        line_DDA(B.x, B.y, C.x, C.y, col, 0); // линия 2-
        line_DDA(A.x, A.y, C.x, C.y, col, 0); // линия 3-

        line_DDA(A.x, A.y, D.x, D.y, col, 1); // линия 4
        line_DDA(B.x, B.y, D.x, D.y, col, 1); // линия 5
        line_DDA(C.x, C.y, D.x, D.y, col, 0); // линия 6-

        // заливка
        /*
        Point Cen; // точка центра треугольника
        Cen.x = (A.x + B.x + C.x) / 3;
        Cen.y = (A.y + B.y + C.y) / 3;
        Cen.x = floor(Cen.x);
        Cen.y = floor(Cen.y);
        fill(Cen, FILLCOL);
        */
    }

    // заливка
    /*
    void fill(Point S, COLORREF colour) {
        Point pt = S;
        queue <Point> Pts;
        Pts.push(pt);

        while (!Pts.empty()) {
            pt = Pts.front();
            Pts.pop();
            if (getpixel(pt.x, pt.y) != BLACK || pt.x <= 0 || pt.y <= 0) {
                if (getpixel(pt.x, pt.y) == TEXTCOL) {
                    pt.x--;
                    Pts.push(pt);
                }
            }
            else {
                putpixel(pt.x, pt.y, colour);
                pt.y--;         Pts.push(pt); // вниз
                pt.y++; pt.y++; Pts.push(pt); // вверх
                pt.y--; pt.x++; Pts.push(pt); // вправо
                pt.x--; pt.x--; Pts.push(pt); // влево
            }
        }
    }
    */

    // пермещение
    void moveX(float amt) {
        A.x += amt;
        B.x += amt;
        C.x += amt;
        D.x += amt;
    }
    void moveY(float amt) {
        A.y += amt;
        B.y += amt;
        C.y += amt;
        D.y += amt;
    }
    void moveZ(float amt) { // при движении на нас увеличивать, от нас уменьшать
        A.x += 0.5 * amt;
        B.x += 0.5 * amt;
        C.x += 0.5 * amt;
        D.x += 0.5 * amt;

        A.y -= 0.5 * amt;
        B.y -= 0.5 * amt;
        C.y -= 0.5 * amt;
        D.y -= 0.5 * amt;
    }

    // поворот
    void rotate(int u) { // u = -1 по часовой, u = 1 против
        Point tmpA = A, tmpB = B, tmpC = C, tmpD = D;
        float ang = u * 0.05; // угол поворота

        Point Cen; // точка центра треугольника
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;

        A.x = A.x - Cen.x; // расстояние от а до центра по х
        A.y = A.y - Cen.y; // по у
        B.x = B.x - Cen.x; // расстояние от b до центра по х
        B.y = B.y - Cen.y; // по у
        C.x = C.x - Cen.x; // расстояние от c до центра по х
        C.y = C.y - Cen.y; // по у
        D.x = D.x - Cen.x; // расстояние от d до центра по х
        D.y = D.y - Cen.y; // по у

        // поворот вокруг нк
        // A
        float tmpX = A.x * cos(ang) + A.y * sin(ang);
        float tmpY = -A.x * sin(ang) + A.y * cos(ang);
        A.x = tmpX + Cen.x;
        A.y = tmpY + Cen.y;
        // B
        tmpX = B.x * cos(ang) + B.y * sin(ang);
        tmpY = -B.x * sin(ang) + B.y * cos(ang);
        B.x = tmpX + Cen.x;
        B.y = tmpY + Cen.y;
        // C
        tmpX = C.x * cos(ang) + C.y * sin(ang);
        tmpY = -C.x * sin(ang) + C.y * cos(ang);
        C.x = tmpX + Cen.x;
        C.y = tmpY + Cen.y;\
         // D
        tmpX = D.x * cos(ang) + D.y * sin(ang);
        tmpY = -D.x * sin(ang) + D.y * cos(ang);
        D.x = tmpX + Cen.x;
        D.y = tmpY + Cen.y;
    }

    // масштабирование
    void scale(float e) {
        Point Cen; // точка центра треугольника
        Cen.x = (A.x + B.x + C.x + D.x) / 4;
        Cen.y = (A.y + B.y + C.y + D.y) / 4;

        if ((abs(A.x - Cen.x) >= 1 && abs(A.y - Cen.y) >= 1) && (abs(B.x - Cen.x) >= 1 && abs(B.y - Cen.y) >= 1) &&
            (abs(C.x - Cen.x) >= 1 && abs(C.y - Cen.y) >= 1) && (abs(D.x - Cen.x) >= 1 && abs(D.y - Cen.y) >= 1) || 
            e > 1) { // предотвращение сжатия в точку
            // A.x
            float xe = (Cen.x + A.x) / 2;
            float lx = Cen.x - A.x;
            lx = lx * e;
            A.x = xe - lx / 2;
            // A.y
            float ye = (Cen.y + A.y) / 2;
            float ly = Cen.y - A.y;
            ly = ly * e;
            A.y = ye - ly / 2;

            // B.x
            xe = (Cen.x + B.x) / 2;
            lx = Cen.x - B.x;
            lx = lx * e;
            B.x = xe - lx / 2;
            // B.y
            ye = (Cen.y + B.y) / 2;
            ly = Cen.y - B.y;
            ly = ly * e;
            B.y = ye - ly / 2;

            // C.x
            xe = (Cen.x + C.x) / 2;
            lx = Cen.x - C.x;
            lx = lx * e;
            C.x = xe - lx / 2;
            // C.y
            ye = (Cen.y + C.y) / 2;
            ly = Cen.y - C.y;
            ly = ly * e;
            C.y = ye - ly / 2;

            // D.x
            xe = (Cen.x + D.x) / 2;
            lx = Cen.x - D.x;
            lx = lx * e;
            D.x = xe - lx / 2;
            // D.y
            ye = (Cen.y + D.y) / 2;
            ly = Cen.y - D.y;
            ly = ly * e;
            D.y = ye - ly / 2;
        }

    }
};



int main() {
    initwindow(1400, 700); // создаём консольное окно 1400 на 700

    Piramid Tri; // создание трёхгранной пирамиды

    // управление
    int i = 1; // условие выхода
    while (i) {
        switch (getch()) {
        case 'w':
            cout << 'w' << endl;
            Tri.moveY(-10); // вверх
            break;
        case 'a':
            cout << 'a' << endl;
            Tri.moveX(-10); // влево
            break;
        case 's':
            cout << 's' << endl;
            Tri.moveY(10); // вниз
            break;
        case 'd':
            cout << 'd' << endl;
            Tri.moveX(10); // вправо
            break;



        case 'x':
            cout << 'x' << endl;
            Tri.moveZ(10); // назад
            Tri.scale(0.9);
            break;
        case 'z':
            cout << 'z' << endl;
            Tri.moveZ(-10); // вперёд
            Tri.scale(1.1);
            break;



        case 'q':
            cout << 'q' << endl;
            Tri.rotate(1); // против часовой
            break;
        case 'e':
            cout << 'e' << endl;
            Tri.rotate(-1); // по часовой
            break;
        case '=':
            cout << '+' << endl;
            Tri.scale(1.5); // увеличение
            break;
        case '-':
            cout << '-' << endl;
            Tri.scale(0.5); // уменьшение
            break;
        default:
            cout << "default -> exit" << endl;
            i = 0;
            break;
        }
        cleardevice(); // отичстка экрана
        Tri.drawPiramid(); // перерисовка трёхгранной пирамиды
    }

    getch(); // чтение одного символа с клавиатуры
    closegraph(); // освобождает всю память, выделенную под графическую систему, затем восстанавливает экран в режим, который был до вызова initwindow

    return 0;
}