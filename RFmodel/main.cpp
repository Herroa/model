#include <iostream>
#include <vector>
#include <windows.h>

class Animal
{
private:
    int x, y;
    int stability;
    int direction;
    int age;

public:
    Animal(int x, int y, int stability, int direction) : x(x), y(y), stability(stability), direction(direction), age(0)
    {
    }
    void move(int max_n, int max_m)
    {
        switch (direction)
        {
        case 0:
            y--;
            if (y < 0)
            {
                y = max_n - 1;
            }
            break;
        case 1:
            x++;
            if (x == max_m)
            {
                x = 0;
            }
            break;
        case 2:
            y++;
            if (y == max_n)
            {
                y = 0;
            }
            break;
        case 3:
            x--;
            if (x < 0)
            {
                x = max_m - 1;
            }
            break;
        }
        // board out check
        // check if fox up rabbit
    }
    void changeD()
    {
        direction = (direction + 1) % 4;
    }
    void age1()
    {
        age++;
    }
    int get_x() { return x; }
    int get_y() { return y; }
    int get_stability() { return stability; }
    int get_direction() { return direction; }
    int get_age() { return age; }
};

class Rabbit : public Animal
{
private:
    int breed;

public:
    Rabbit(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), breed(10)
    {
    }
    int get_breed() { return breed; }
};

class Fox : public Animal
{
private:
    int food;

public:
    Fox(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), food(0)
    {
    }
    void food1() { food++; }
    int get_food()
    {
        food++;
        return food;
    }
};

class Model
{
private:
    int n, m;
    int turn;
    std::vector<Rabbit> masR;
    std::vector<Fox> masF;
    int **mas;

public:
    Model(int n, int m) : n(n), m(m), turn(0)
    {
        mas = new int *[n];
        for (int i = 0; i < n; i++)
        {
            mas[i] = new int[m];
        }
    }
    void step(int i)
    {
        // rabbit
        unsigned NR = masR.size();
        for (unsigned r = 0; r < NR; r++)
        {
            masR[r].move(n, m);
            masR[r].age1();
            if (i % masR[r].get_stability() == 0)
            {
                masR[r].changeD();
            }
            if (i % masR[r].get_breed() == 0)
            {
                addR(masR[r].get_x() + 1, masR[r].get_y() + 1, masR[r].get_stability(), masR[r].get_direction());
            }
            if (masR[r].get_age() == 50)
            {
                masR.erase(masR.begin() + r);
            }
        }
        // fox
        unsigned NF = masF.size();
        for (unsigned r = 0; r < NF; r++)
        {
            masF[r].move(n, m);
            eating(masF[r]);
            masF[r].move(n, m);
            eating(masF[r]);
            masF[r].age1();
            if (i % masF[r].get_stability() == 0)
            {
                masF[r].changeD();
            }
            if (masF[r].get_food() == 2)
            {
                addF(masF[r].get_x() + 1, masF[r].get_y() + 1, masF[r].get_stability(), masF[r].get_direction());
            }
            if (masF[r].get_age() == 50)
            {
                masF.erase(masF.begin() + r);
            }
        }
    };
    void draw(int i)
    {
        std::cout << "Model step: " << i << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int flag = 0;
                for (unsigned r = 0; r < masR.size(); r++)
                {
                    if ((masR[r].get_x() == j) && (masR[r].get_y() == i))
                    {
                        std::cout << 'R';
                        flag = 1;
                        break;
                    }
                }
                for (unsigned r = 0; r < masF.size(); r++)
                {
                    if ((masF[r].get_x() == j) && (masF[r].get_y() == i))
                    {
                        std::cout << 'F';
                        flag = 1;
                        break;
                    }
                }
                // проверять существует ли заяц или лиса на этой координате 'F' 'R'
                if (!flag)
                {
                    std::cout << '_';
                }
            }
            std::cout << std::endl;
        }
    }

    void write(){};
    void addR(int x, int y, int s, int dir)
    {
        masR.push_back(Rabbit(x, y, s, dir));
    }
    void addF(int x, int y, int s, int dir)
    {
        masF.push_back(Fox(x, y, s, dir));
    }
    void eating(Fox F)
    {
        for (unsigned i = 0; i < masR.size(); i++)
        {
            if (masR[i].get_x() == F.get_x() && masR[i].get_y() == F.get_y())
            {
                masF.erase(masF.begin() + i);
                F.food1();
            }
        }
    }
};
int main()
{
    //  Ввод заданных значений для построения модели
    Model M(10, 20);
    M.addR(5, 5, 7, 1);
    // Ввод данных для зайцев и добавление зайцев (через объект класс Модель)
    M.addF(1, 5, 5, 1);
    // Ввод данных для лис и добавление лис (через объект класс Модель)
    // ХОД
    int K = 50;
    for (int i = 1; i < K; ++i)
    {
        M.draw(i);
        M.step(i); // M - объект класса модель
        Sleep(1000);
    }
    M.write();
    return 0;
}