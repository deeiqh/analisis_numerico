#include <iostream>
#include <cmath>

using namespace std;

const int filas = 4;
const int columnas = 4;
double **escalona(double AE[filas][columnas+1]);
double *sust_regresiva(double A[filas][columnas], double [filas]);
double *met_gauss(double A[filas][columnas], double b[filas]);
double **escalona_piv(double AE[filas][columnas+1]);
double *met_gauss_piv(double A[filas][columnas], double b[filas]);

int main()
{
	double A[filas][columnas]= {
		{2,3,4,-5},
		{-3,4,-5,7},
		{5,1,-1,6},
		{7,9,-13,17}
	};
	double b[filas] = {7,2,5,21};

	double *X = met_gauss_piv(A,b);
	
	for(int f=0;f!=filas;f++)
	        cout << "X["<<f+1<<"] = "<<X[f] << '\n';
	        
	//----- Solo para verificar
	double r[filas];
	for(int i=0; i <=filas-1; i++){
	  r[i] = 0;
	  for(int j=0; j<= filas-1; j++){
		r[i] += A[i][j]*X[j];
	  }
	}
	cout << '\n';
	for(int i=0;i<=filas-1;i++)
		cout << "b["<<i+1<<"] = "<<r[i] << '\n';
	//----- 
	 
	return 0;
}

double **escalona(double AE[filas][columnas+1])
{
	int f = filas, c= columnas+1;
	double m[f][c];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			m[i][j] = 0;		
		}	
	}
	for(int j=0; j <= c-2; j++){
		for(int i=j+1; i <= f-1; i++){
			m[i][j] = AE[i][j]/AE[j][j];
			for(int k=0; k<= c-1; k++){
				AE[i][k] = AE[i][k] - m[i][j]*AE[j][k];
			}
		}	
	}
	
	double **E = new double*[filas];
    for(int i = 0; i < filas; i++)
        E[i] = new double[columnas+1];
	
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			E[i][j] = AE[i][j];		
		}	
	}
	return E;
}

double *sust_regresiva(double A[filas][columnas], double b[filas])
{
	int f = filas;
	double *X = new double[f];
	for(int i=0; i != f; i++){
		X[i] = 0;
	}
	for(int i = f-1; i != -1; i--){
		X[i] = b[i];
		for(int j = i+1; j != f; j++){
			X[i] = X[i]-A[i][j]*X[j];
		}
		X[i] = X[i]/A[i][i];
	}
	return X;
}

double *met_gauss(double A[filas][columnas], double b[filas])
{
	const int f = filas, c = columnas;
	double B[f][c+1];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			B[i][j] = A[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		B[i][c] = b[i];
	}
	double **B_; 
	B_ =  escalona(B);
	double X[f];
	double Ba[f][c];
	double Bb[f];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			Ba[i][j] = B_[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		Bb[i] = B[i][columnas];
	}
	double *X_ = sust_regresiva(Ba,Bb);
	return X_;
}	

void pivotea(double AE[filas][columnas+1], int c)
{
	// en la matriz extendida pivotea la columna c a partir de c, en c va el mayor elemento
	int fila_mayor = c;
	for(int f=c; f <= filas-1;f++){
	    if(abs(AE[f][c]) >= abs(AE[fila_mayor][c]))
	        fila_mayor = f;
	}
	double aux;
	for(int col=0; col <= columnas;col++){
	    aux = AE[c][col];
	    AE[c][col] =  AE[fila_mayor][col]; 
	    AE[fila_mayor][col] = aux;
	}
}
double **escalona_piv(double AE[filas][columnas+1])
{
	int f = filas, c= columnas+1;
	double m[f][c];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			m[i][j] = 0;		
		}	
	}
	for(int j=0; j != c-2; j++){
		pivotea(AE,j);
		for(int i=j+1; i <= f-1; i++){		    	
			m[i][j] = AE[i][j]/AE[j][j];
			for(int k=0; k<= c-1; k++){
				AE[i][k] = AE[i][k] - m[i][j]*AE[j][k];
			}
		}	
	}
	
	double **E = new double*[filas];
    for(int i = 0; i < filas; i++)
        E[i] = new double[columnas+1];
        
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			E[i][j] = AE[i][j];		
		}	
	}
	return E;
}

double *met_gauss_piv(double A[filas][columnas], double b[filas])
{
	const int f = filas, c = columnas;
	double B[f][c+1];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			B[i][j] = A[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		B[i][c] = b[i];
	}
	double **B_; 
	B_ =  escalona_piv(B);
	double X[f];
	double Ba[f][c];
	double Bb[f];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			Ba[i][j] = B_[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		Bb[i] = B[i][columnas];
	}
	double *X_ = sust_regresiva(Ba,Bb);
	return X_;
}
























