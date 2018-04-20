#include <iostream>
#include <cmath>

using namespace std;


float fa(float);
float fb(float);
float fc(float);
float fd(float);
float fclase1(float);
float fclase2(float);

float alpha( float(*funcion)(float), float, float);

int main()
{
    float exactitud = 0.00003;
    float diferencia = 1;
    float alpha1, alpha2;
    int n = 2; //TENDERÁ AL INFINITO
    while( diferencia > exactitud ){
            alpha1 = alpha(fclase2, 0, n); //alpha(FUNCION, LIMITE, n) 
            alpha2 = alpha(fclase2, 0, n+1);
            diferencia = abs(alpha1 -  alpha2);
            n++;
    }
    cout <<  "alpha = " << alpha1 << ", n creció hasta " << n << " para tener una exactitud de "<<exactitud<<'\n';
}

float alpha( float(*funcion)(float), float limite , float n)
{
    float xnmas1 = funcion(n+1);
    float xn = funcion(n);
    float xnmenos1 = funcion(n-1);
    return log(abs((xnmas1-limite)/(xn-limite)))/log(abs((xn-limite)/(xnmenos1-limite)));
}

float fclase1(float n)
{
    return 1.0/n; //limite 0
}

float fclase2(float n)
{
    return 1/pow(2.0,pow(2.0,n)); // limite 0
}


float fa(float n)
{
    return (n*n*n - 2*n +4)/(2*n*n*n + 1); // limite 0.5
}

float fb(float n)
{
    return ;
}

float fc(float n)
{
    return ;
}

float fd(float n)
{
    return ;
}

