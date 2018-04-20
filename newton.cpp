#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double r = 1;
    int n = 7;
    for(int i = 1; i <= n; i++){
        r = r - (r*r*r + 2*r*r + r - 3)/(3*r*r + 4*r + 1);
        cout << "r" << i << " = "<< r << '\n';   
    }
    
    cout << "\nDado que el número correcto de dígitos después de la coma decimal  inicia en 1, luego 4 y queda estabilizado en 6, podemos decir que el orden de convergencia de la sucesión es cuadrática.\n";
    
    
    

    return 0;
}

