#include <iostream>
namespace laba3 {

    struct Item {
        float x;
        float y;
    };

    class Polygon {
    private:
        int SIZE, realSIZE;
        Item* d;
        void Add_memory();
    public:
        Polygon() : realSIZE(0), SIZE(5) {
            d = new Item[SIZE];
            for (int i = 0; i < SIZE; i++) {
                d[i].x = 0;
                d[i].y = 0;
            }
        }
        Polygon(Item& item) : SIZE(6), realSIZE(1) {
            d = new Item[SIZE];
            d[0].x = item.x; d[0].y = item.y;
        }

        Polygon(const Polygon& polygon) :SIZE(polygon.SIZE), realSIZE(polygon.realSIZE) {  //  ���������� �����������
            d = new Item[polygon.SIZE];
            for (int i = 0; i < SIZE; i++) {
                d[i] = polygon.d[i];
            }
        }

        Polygon(Polygon&& tmp) :SIZE(tmp.SIZE), realSIZE(tmp.realSIZE) {     // ������������ �����������
            this->d = tmp.d;
            tmp.d = nullptr;
        }

        ~Polygon() { delete[] d; }

        int getSIZE() { return realSIZE; };
        Item getNum(int i) { return d[i]; }

        void turn(int number, int angle, float x, float y);

        friend std::ostream& operator << (std::ostream&, Polygon&); // ����� ��������������
        Polygon& operator += (Item item);  // ���������� �����
        Item& operator [](int number);   // ����� ����� �� �� ������
        friend void operator+=(Item&, const Polygon& polygon);   // ���������� ������ ������� ��������������
        friend void operator + (Polygon& polygon, Item& vector);    // ����������� �� ������

        Polygon& operator = (Polygon&& poly);
    };
}