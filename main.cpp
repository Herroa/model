#include <iostream>
#include <vector>
#include <windows.h>
#include "classes.h"

int main()
{
    while (true)
    {
        // 10 20 100
        int n, m, turns;
        std::cout << "Input height: ";
        std::cin >> n;
        std::cout << "Input width: ";
        std::cin >> m;
        std::cout << "Input turns: ";
        std::cin >> turns;
        Model M(n, m);
        M.addR(4, 3, 7, 1);
        M.addR(5, 3, 7, 1);
        M.addR(7, 5, 7, 1);
        M.addF(1, 2, 5, 1);
        for (int i = 1; i < turns; ++i)
        {
            M.draw(i);
            M.step(i);
            Sleep(100);
        }
        system("pause");
    }

    return 0;
}