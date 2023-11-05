#include <vector>
#include <iostream>

class Creature
{
protected:
    int x, y;

public:
    Creature(int x, int y) : x(x), y(y)
    {
    }
    ~Creature() {}
    int get_x() { return x; }
    int get_y() { return y; }
};

class Cucumber : public Creature
{
public:
    Cucumber(int x, int y) : Creature(x, y)
    {
    }
    ~Cucumber() {}
};

class Animal : public Creature
{
protected:
    int stability;
    int direction;
    int age;

public:
    Animal(int x, int y, int stability, int direction) : Creature(x, y), stability(stability), direction(direction), age(0)
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

    int get_stability() { return stability; }
    int get_direction() { return direction; }
    int get_age() { return age; }
};

class Wolf : public Animal
{
protected:
    int food;

public:
    Wolf(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), food(0)
    {
    }
    ~Wolf() {}
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
protected:
    int breed;

public:
    Rabbit(int x, int y, int stability, int direction) : Animal(x, y, stability, direction), breed(5)
    {
    }
    ~Rabbit() {}
    int get_breed() { return breed; }
};

class Model
{
protected:
    int n, m;
    std::vector<Cucumber> masC;
    std::vector<Rabbit> masR;
    std::vector<Wolf> masW;

public:
    Model(int n, int m) : n(n), m(m)
    {
    }
    ~Model() {}
    void step(int i)
    {
        updateC(i);
        updateR(i);
        updateF(i);
    };


    void updateC(int i)
    {
        if(i%2==0){
            addC();
        }
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
        // Wolf
        unsigned NF = masW.size();
        for (unsigned r = 0; r < NF; r++)
        {
            masW[r].move(n, m);
            eating(&(masW[r]));
            masW[r].move(n, m);
            eating(&(masW[r]));
            masW[r].age1();
            if (i % masW[r].get_stability() == 0)
            {
                masW[r].changeD();
            }

            if (masW[r].get_food() >= 2)
            {
                addF(masW[r].get_x(), masW[r].get_y(), masW[r].get_stability(), masW[r].get_direction() + 1);
                masW[r].food_to_zero();
            }
            if (masW[r].get_age() == 50)
            {
                masW.erase(masW.begin() + r);
                NF--;
            }
        }
    }
    void addC()
    {
        masC.push_back(Cucumber(rand()%n,rand()%m));
    }
    void addR(int x, int y, int s, int dir)
    {
        masR.push_back(Rabbit(x, y, s, dir));
    }
    void addF(int x, int y, int s, int dir)
    {
        masW.push_back(Wolf(x, y, s, dir));
    }
    void eating(Wolf *W)
    {
        for (unsigned i = 0; i < masR.size(); i++)
        {
            if (masR[i].get_x() == W->get_x() && masR[i].get_y() == W->get_y())
            {
                masR.erase(masR.begin() + i);
                W->food1();
            }
        }
    }

    void draw(int i)
    {
        std::cout << "Model step: " << i << std::endl;
        std::cout << "CUCUMBERS " << masC.size() << std::endl;
        std::cout << "RABBITS " << masR.size() << std::endl;
        std::cout << "WolfES " << masW.size() << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int flag = 0;
                for (unsigned r = 0; r < masC.size(); r++)
                {
                    if ((masC[r].get_x() == j) && (masC[r].get_y() == i))
                    {
                        std::cout << 'C';
                        flag = 1;
                        break;
                    }
                }
                for (unsigned r = 0; r < masR.size(); r++)
                {
                    if ((masR[r].get_x() == j) && (masR[r].get_y() == i))
                    {
                        std::cout << 'R';
                        flag = 1;
                        break;
                    }
                }
                for (unsigned r = 0; r < masW.size(); r++)
                {
                    if ((masW[r].get_x() == j) && (masW[r].get_y() == i))
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