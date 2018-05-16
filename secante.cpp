#include <iostream> 
#include <cstdio>
#include <cmath>

using namespace std;

#define pi      3.14159265

double foo(double x)
{
	double f; 
	f = cos(x) - x;
      return f;
}

int main()
{
      double p0 = 0.5;  //ejemplo del libro
      double p1 = pi/4.0; //ejemplo del libro
      
      double tolerancia = 0.00000000001;
      int iteraciones_max = 300; 

      int i = 2;      
      double f0 = foo(p0);
      double f1 = foo(p1);
      
      bool valido = true;                                
	
	double p;
	double fp;
      while ((i<=iteraciones_max) && valido) {   
	 	 p = p1 - f1 * (p1 - p0) / (f1 - f0); //TEOREMA
		 cout << "Iteración "<< i << ", p = " << p << '\n';
		 if (abs(p - p1) < tolerancia) {
		 	//FIN
		    	valido = false;
		 }
		 else {
			i++;
		   	p0 = p1;
		    	f0 = f1;
		    	p1 = p;
		    	f1 = foo(p);
	 	}
      }
      
      return 0;
}

