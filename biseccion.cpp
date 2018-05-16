#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

#define cero 0.0000000000001

double foo(double);

main()
{
   double a = 1;
   double b = 2;
   double fa = foo(a);
   double fb = foo(b);
   
   double tolerancia = 0.000001; 
   int iteraciones_max = 100;

   int i = 1;     
   bool valido = true; 
   while ((i<=iteraciones_max) && valido) 
   { 
       double long_semi_intervalo = (b-a)/2;
       double punto_medio = a + long_semi_intervalo;

       double f_punto_medio = foo(punto_medio);  

       cout << "Iteración "<< i << ", x: "<< punto_medio<< '\n';
   
       if ((abs(f_punto_medio) < cero) || (long_semi_intervalo < tolerancia)) 
       {
		//PROCESO CONCLUIDO	
		valido = false;	
       }
       else 
       {
	    i++; 
	    if (fa*f_punto_medio > 0){
	       a = punto_medio; 
	       fa = f_punto_medio;
	    }
	    else{
	       b = punto_medio;
	       fb = f_punto_medio;
	    }
       }
   }

   return 0;
}

double foo(double x)
{
   double f; 
   f = x*x*x + 4*x*x-10; 
   return f;
}


