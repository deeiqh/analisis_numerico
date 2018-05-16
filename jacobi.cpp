#include<cstdio>
#include<cmath>
#include<iostream>

using namespace std;

int main()
{
	int N = 3;
	double A[N][N+1] = {
		{4, 1, -1, 4},
		{1, -3, 1, -1},
		{1, 1, -4, -2}
	};

	int iteraciones_max = 300; //PARADA
	double tolerancia = 0.000001; //PARADA
	double X0[N],X[N];
	bool validado = false;
	
	//ver si es diagonal dominante por fila o columna
	int nv = 0;
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			if( abs(A[i-1][i-1]) >= abs(A[i-1][j-1]) ){
				nv++;
			}
		}
	}
	if(nv == N*N){ //N*N pues cada componente de la diagonal es comprobada N veces en cada N filas
		// Aproximación inicial
		for(int i = 1; i <= N; i++)
			X0[i-1] = 0; 

		int K = 1;	
	
		//Calculamos los X^K
		while ((!validado) && (K <= iteraciones_max)) {
			//X^K, propiamente
			double sumatoria;
			for (int i=1; i<=N; i++) {
				sumatoria = 0;
				for (int j=1; j<=N; j++){
					if(j == i) continue;
					sumatoria = sumatoria - A[i-1][j-1] * X0[j-1];
				}
					X[i-1] = (sumatoria + A[i-1][N]) / A[i-1][i-1];
			}
		
			// calculando error = || X-X0 ||, en norma-inf
			double dif = abs(X[0] - X0[0]);
			double componente_mayor = abs(X[0]);
			for (int i=1; i<=N; i++){
				if(abs(X[i-1] - X0[i-1]) > dif)
					dif = abs(X[i-1] - X0[i-1]);
				if(abs(X[i-1]) > componente_mayor)
					componente_mayor = abs(X[i-1]);
			}
			double error = dif/componente_mayor;
		
			if (error <= tolerancia) validado = true;//FIN
			else{
				K++;
				for(int i =1; i<=N; i++) //actualizamos X0
					X0[i-1] = X[i-1]; 
			}
		}
		if (!validado) 
			cout<<"Se llegó al número máximo de iteraciones.\n";
		else {
			cout<<"Iteraciones = "<< K <<'\n';
			cout<<"X: \n";
			for (int i=1; i<=N; i++)
				cout<<"X["<<i <<"]= " << X[i-1] <<'\n';
		}
	}
	else
		cout << "No es diagonal dominante ni por columnas ni por filas.\n";
	return 0;
}


