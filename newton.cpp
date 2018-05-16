#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double r = 1;
    double r0;
    int n = 7; //ITERACIONES
    double tolerancia = 0.000001;
    for(int i = 1; i <= n; i++){
        r0 = r;
        r = r - (r*r*r + 2*r*r + r - 3)/(3*r*r + 4*r + 1);
        cout << "Iteración "<< i << ", x = "<<r<<'\n';   
        if(abs(r-r0) < tolerancia)
        	break;
    }
    
    cout << "\nDado que el número correcto de dígitos después de la coma decimal  inicia en 1, luego 4 y queda estabilizado en 6, podemos decir que el orden de convergencia de la sucesión es cuadrática.\n";
    
    
    

    return 0;
}

