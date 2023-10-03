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
    void move(int n)
    {
        switch (direction)
        {
        case 0:
            y++;
            break;
        case 1:
            x++;
            break;
        case 2:
            y--;
            break;
        case 3:
            x--;
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
};

class Rabbit : public Animal
{
private:
    int breed;

public:
    Rabbit(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), breed(0)
    {
    }
    // void breed()
};

class Fox : public Animal
{
private:
    int food;

public:
    Fox(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), food(0)
    {
    }
    // void food()
};

class Model
{
private:
    int n, m;
    int turn;
    int quant_rab;
    int quant_fox;
    std::vector<Rabbit> masR;
    std::vector<Fox> masF;
    int **mas;

public:
    Model(int n, int m) : n(n), m(m), turn(0), quant_rab(0), quant_fox(0)
    {
        mas = new int *[n];
        for (int i = 0; i < n; i++)
        {
            mas[i] = new int[m];
        }
    }
    void step(int i){};
    void draw(int i)
    {
        std:: cout << "Model step: " << i << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                //проверять существует ли заяц или лиса на этой координате 'F' 'R'
                std::cout << '_';
            }
            std::cout << std::endl;
        }
    }

    void write(){};
    void addR(int x, int y, int s, int dir)
    {
        masR.push_back(Rabbit(x, y, s, dir));
        mas[x][y]++;
    }
    void addF(int x, int y, int s, int dir)
    {
        masF.push_back(Fox(x, y, s, dir));
        mas[x][y]++;
    }
};
int main()
{
    //  Ввод заданных значений для построения модели
    Model M(10, 10);
    //  vector<Rabbit> masR;
    M.addR(5, 5, 5, 0);
    // Ввод данных для зайцев и добавление зайцев (через объект класс Модель)
    M.addF(7, 7, 5, 0);
    // Ввод данных для лис и добавление лис (через объект класс Модель)
    // ХОД
    int K = 10;
    for (int i = 0; i < K; ++i)
    {
        M.draw(i);
        M.step(i); // M - объект класса модель
        Sleep(1000);
    }
    M.write();
    return 0;
}