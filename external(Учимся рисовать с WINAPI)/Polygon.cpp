#include "pch.h"
#include "framework.h"

namespace laba3 {

    std::ostream& operator<<(std::ostream& s, Polygon& polygon) {   // Вывод многоугольника
        for (int i = 0; i < polygon.realSIZE; i++) {
            s << "X:" << polygon.d[i].x << ' ';
            s << "Y:" << polygon.d[i].y << ' ';
            s << std::endl;
        } return s;
    }

    void operator+=(Item& point, const Polygon& polygon) {   // нахождение центра тяжести многоугольника
        float help = 0;
        point.x = 0;
        point.y = 0;
        for (int i = 0; i < polygon.realSIZE; i++) {
            point.x = point.x + polygon.d[i].x; // прибавляем значения всех координат вершин
            point.y = point.y + polygon.d[i].y;

            if (polygon.d[i].x != 0)
                help++;
        }
        point.x = point.x / help; // центр тяжести - координаты точки, являющейся
        point.y = point.y / help; // средним арифметическим всех точек
    }

    void Polygon::turn(int number, int angle, float x, float y) {        // Поворот многоугольника
        float help1;
        float help2;
        int helpAngle;
        for (int i = 0; i < number; i++) {
            if (angle == 90) {  // 90 градусов
                help1 = x + (y - d[i].y);
                help2 = y + (d[i].x - x);
                d[i].x = help1;
                d[i].y = help2;
            }
            if (angle == 180) {  // 180 градусов
                help1 = x + (x - d[i].x);
                help2 = y + (y - d[i].y);
                d[i].x = help1;
                d[i].y = help2;
            }
            if (angle == 270) {  // 270 градусов
                help1 = x + (d[i].y - y);
                help2 = y + (x - d[i].x);
                d[i].x = help1;
                d[i].y = help2;
            }
            if (angle == 360 || angle == 0) { // 360 градусов или 0
                d[i].x = d[i].x; d[i].y = d[i].y;
            }

        }

    }

    void operator + (Polygon& polygon, Item& vector) {   // Перемещение на вектор
        for (int i = 0; i < polygon.realSIZE; i++) {
            polygon[i].x += vector.x;
            polygon[i].y += vector.y;
        }
    }


    Item& laba3::Polygon::operator [](int number) {    // Поиск точки по ее номеру с помощью оператора
        if (number<0 || number>realSIZE)
            throw std::exception("There is no such element");
        return d[number];
    }

    Polygon& laba3::Polygon:: operator += (Item item) { // Добавление точки через оператора
        //Add_memory();
        if (realSIZE == SIZE)
            Add_memory();
        d[realSIZE] = item;
        realSIZE++;
        return *this;
    }

    void Polygon::Add_memory() {
        Item* f = new Item[SIZE + 5];
        SIZE += 5;
        for (int i = 0; i < this->realSIZE; i++) {
            f[i] = d[i];
        }
        delete[] d;
        d = f;
    }

    Polygon& Polygon::operator = (Polygon&& poly) {
        if (&poly == this) {
            return *this;
        }
        delete[] this->d;
        this->d = poly.d;
        poly.d = nullptr;
        this->SIZE = poly.SIZE;
        return *this;
    }
}
