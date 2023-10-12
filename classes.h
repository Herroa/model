#include <vector>
#include <iostream>

class Animal
{
protected:
    int x, y;
    int stability;
    int direction;
    int age;

public:
    Animal(int x, int y, int stability, int direction) : x(x), y(y), stability(stability), direction(direction), age(0)
    {
    }
    ~Animal() {}
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
            if (x >= max_m)
            {
                x = 0;
            }
            break;
        case 2:
            y++;
            if (y >= max_n)
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

class Fox : public Animal
{
private:
    int food;

public:
    Fox(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), food(0)
    {
    }
    ~Fox(){}
    void food1()
    {
        food++;
    }
    void food_to_zero()
    {
        food = 0;
    }
    int get_food()
    {
        return food;
    }
};

class Rabbit : public Animal
{
private:
    int breed;

public:
    Rabbit(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), breed(5)
    {
    }
    ~Rabbit(){}
    int get_breed() { return breed; }
};

class Model
{
private:
    int n, m;
    std::vector<Rabbit> masR;
    std::vector<Fox> masF;

public:
    Model(int n, int m) : n(n), m(m)
    {
    }
    ~Model() {}
    void step(int i){
        updateR(i);
        updateF(i);
    };
    void updateR(int i)
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
                addR(masR[r].get_x(), masR[r].get_y(), masR[r].get_stability(), masR[r].get_direction() + 1);
            }
            if (masR[r].get_age() == 10)
            {
                masR.erase(masR.begin() + r);
                NR--;
            }
        }
    }
    void updateF(int i)
    {
        // fox
        unsigned NF = masF.size();
        for (unsigned r = 0; r < NF; r++)
        {
            masF[r].move(n, m);
            eating(&(masF[r]));
            masF[r].move(n, m);
            eating(&(masF[r]));
            masF[r].age1();
            if (i % masF[r].get_stability() == 0)
            {
                masF[r].changeD();
            }

            if (masF[r].get_food() >= 2)
            {
                addF(masF[r].get_x(), masF[r].get_y(), masF[r].get_stability(), masF[r].get_direction() + 1);
                masF[r].food_to_zero();
            }
            if (masF[r].get_age() == 50)
            {
                masF.erase(masF.begin() + r);
                NF--;
            }
        }
    }
    void addR(int x, int y, int s, int dir)
    {
        masR.push_back(Rabbit(x, y, s, dir));
    }
    void addF(int x, int y, int s, int dir)
    {
        masF.push_back(Fox(x, y, s, dir));
    }
    void eating(Fox *F)
    {
        for (unsigned i = 0; i < masR.size(); i++)
        {
            if (masR[i].get_x() == F->get_x() && masR[i].get_y() == F->get_y())
            {
                masR.erase(masR.begin() + i);
                F->food1();
            }
        }
    }

    void draw(int i)
    {
        std::cout << "Model step: " << i << std::endl;
        std::cout << "RABBITS " << masR.size() << std::endl;
        std::cout << "FOXES " << masF.size() << std::endl;
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
                if (!flag)
                {
                    std::cout << '_';
                }
            }
            std::cout << std::endl;
        }
    }
};