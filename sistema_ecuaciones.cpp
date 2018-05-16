#include <iostream>
#include <cmath>

using namespace std;

double E[4][5] escalona(double A[4][5]);
double X[4] sust_regresiva(double A[4][5], b[4]);
double X[4] met_gauss(double A[4][5], double b[4]);
double E[4][5] escalona_piv(double A[4][5]);

int main()
{
	

	return 0;
}

double E[4][5] escalona(double A[4][5])
{
	int f = 4, c= 5;
	double m[f][c];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			m[i][j] = 0;		
		}	
	}
	for(int j=0; j != c-1; j++){
		for(int j=j+1; j != f; j++){
			m[i][j] = A[i][j]/A[j][j];
			for(int k=0; k!= c; k++){
				A[i][k] = A[i][k] - m[i][j]*A[j][k];
			}
		}	
	}
	double E[4][5];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			E[i][j] = A[i][j];		
		}	
	}
	return E;
}

double X[4] sust_regresiva(double A[4][5],double b[4])
{
	int f = 4;
	double X[f];
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

double X[4] met_gauss(double A[4][5], double b[4])
{
	int f = 4, c = 4;
	double B[f][c+1];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			B[i][j] = A[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		B[i][4] = b[i];
	}
	B =  escalona(B[4][5]);
	double X[f];
	double Ba[f][c];
	double Bb[f];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			Ba[i][j] = B[i][j];		
		}	
	}
	for(int i=0; i != f; i++){ //matriz extendida
		Bb[i] = B[i][4];
	}
	X = sust_regresiva(Ba,Bb);
	return X;
}	

double A[4][5] pivotea(double A[4][5], int c);
double E[4][5] escalona_piv(double A[4][5])
{
	int f = 4, c= 5;
	double m[f][c];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			m[i][j] = 0;		
		}	
	}
	for(int j=0; j != c-1; j++){
		//pivoteamos
		A = pivotea(A,j);
		for(int j=j+1; j != f; j++){
			m[i][j] = A[i][j]/A[j][j];
			for(int k=0; k!= c; k++){
				A[i][k] = A[i][k] - m[i][j]*A[j][k];
			}
		}	
	}
	double E[4][5];
	for(int i=0; i != f; i++){
		for(int j=0; j != c; j++){
			E[i][j] = A[i][j];		
		}	
	}
	return E;
}

double A[4][5] pivotea(double A[4][5], int c)
{
	// en la matriz extendida pivotea la columna c a partir de c+1
	
}


























