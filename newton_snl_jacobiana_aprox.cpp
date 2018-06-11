#include <iostream>
//#include "sistema_ecuaciones.cpp"
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <cmath>


using namespace std;
using pdd = pair<double, double>;
using vd = vector<double>;
using vvd = vector<vector<double>>;
const double aproximacion = 0.0001;

vd newton_sistema (vector<map<string,pdd>> F_, vector<vector<map<string,pdd>>> JF_, vd X0, int n, double tolerancia);

vd evalua(vector<map<string,pdd>> F_, vd X0, int n);

vvd aproxima_jacobiana(vector<map<string, pdd>> F_, vd X0, int n);

//POR NO HACER HEADERS:::::::::::::::::::::
//-----------------------------------------
const int n = 3;
const int filas = n;
const int columnas = n;
double **escalona(double AE[filas][columnas+1]);
double *sust_regresiva(double A[filas][columnas], double [filas]);
double *met_gauss(double A[filas][columnas], double b[filas]);
double **escalona_piv(double AE[filas][columnas+1]);
double *met_gauss_piv(double A[filas][columnas], double b[filas]);
//-----------------------------------------

int main()
{
	/*
	f[0] = map[x] map[y] map[z] -> map_evalua(map, x,y,z)
	f[1] = map[x] map[y] map[z]
	f[n-1] = map[x] map[y] map[z]
	*/	
	/*
	x²+y²+z²=2
	x+y+z = 1
	x²+y²-z=0
	*/	
	/*
	cos(x-y) + e^(cosx-y) = 1
	arctan(xy) + ln(x²+y³) = 2
	*/

    //F_
    //------------------------------- 
    
	vector<map<string, pdd>> F_;
	
	map<string, pdd> f1;
	f1["x"] = pdd(1,2); //pdd(coeficiente, expondente) ->x²
	f1["y"] = pdd(1,2);
	f1["z"] = pdd(1,2);
	f1["zz"] = pdd(-2,1);//"zz" simboliza la constane: pdd(coeficiente, expondente) -> -2(1)¹
	
	F_.push_back(f1);	
	
	map<string, pdd> f2;
	f2["x"] = pdd(1,1);
	f2["y"] = pdd(1,1);
	f2["z"] = pdd(1,1);
	f2["zz"] = pdd(-1,1);
	
	F_.push_back(f2);	
	
	map<string, pdd> f3;
	f3["x"] = pdd(1,2);
	f3["y"] = pdd(1,2);
	f3["z"] = pdd(-1,1);
	f3["zz"] = pdd(0,1);//pdd(coeficiente, expondente) -> 0(1)²
	
	F_.push_back(f3);
	
	vd X0 = {1,0,0};	

    //JF_
    //------------------------------- 
    
    vector<vector<map<string,pdd>>> JF_;
    //JF_ = jacobiano(F_, n);	NO NECESITAMOS DERIVAR SI LA MATRIZ JACOBIANA ES APROX
    
    //Newton_sistema
    //-------------------------------     
    double tolerancia = 0.000001;
    vd resultado = newton_sistema(F_,JF_,X0,n,tolerancia);

    for(int i=0;i<=n-1;i++)
		cout << "X["<<i+1<<"] = "<<resultado[i] << '\n';
	
	//Para verificar el resultado
    //-------------------------------
	
	return 0;
}

vd newton_sistema (vector<map<string,pdd>> F_, vector<vector<map<string,pdd>>> JF_, vd X0, int n, double tolerancia)
{
    double A[3][3];//Se pone 3 y no n por no usar header
    int c;
    double b[3];//Se pone 3 y no n por no usar header
    double *V_;
    double *ptr;
    vd V;
    double suma_tolerancia, x0_;
    vd F;
    vvd JF;
    do{
    	F = evalua(F_, X0, n);
        JF = aproxima_jacobiana(F_, X0, n);
        //Por no usar header
        //----
        int f=0;
        for(auto it=JF.begin(); it!=JF.end(); it++){
            c = 0;
            for(auto it_2=it->begin(); it_2!=it->end(); it_2++){
                A[f][c++] = *it_2;
            }
            f++;
        }    
        c=0;
        for(auto it=F.begin(); it!=F.end(); it++){
            b[c++]=*it;
        }    
        //----
	    //V
	    V_ = met_gauss_piv(A,b);
	    ptr=V_;
	    V.clear();
        for(int i=0; i<=n-1; i++){
            V.push_back(*(ptr++));
        }    	
	    //Xn = X-V;
	    suma_tolerancia=0;
	    for(int i=0; i<=n-1; i++){
	    	x0_ = X0[i];
	    	//cerr << "x0_="<<x0_<<"\n";
            X0[i] = X0[i]-V[i];
            //cerr << "X0["<<i<<"]="<<X0[i]<<"\n";
            suma_tolerancia += abs(X0[i]-x0_);            
        }
        //cerr << "suma_tolerancia: " <<suma_tolerancia << "\n\n\n";      
    }while(suma_tolerancia > tolerancia);
    
	return X0;
}

vd evalua(vector<map<string,pdd>> F_, vd X0, int n)
{
	vd r;
	double suma=0;
	int c;
	for(int i=0; i<=n-1; i++){
	    c = 0;
	    auto it=F_[i].begin();
	    for(; it!=F_[i].end() && c<=n-1; it++){	    	
	        suma += it->second.first * pow(X0[c++],it->second.second);
	    }
	    suma += it->second.first;//la constante!
	    r.push_back(suma);
	    suma=0;
	}
	return r;
}

vvd aproxima_jacobiana(vector<map<string, pdd>> F_, vd X0, int n)
{
	vd e = {0,0,0};	
	vvd matriz_jacobiana;
	for (int i = 0; i <= n - 1; i++) {
		double numero=0;
		vd fila;
		for (int j = 0; j <= n - 1; j++) {
			e[j] = 1;

			//vd p_he
			vd p_he;
			for (int k = 0; k <= n - 1; k++) { p_he.push_back(X0[k]); }
			p_he[j] = X0[j] + aproximacion * e[j];

			//valor numérico de f(p_he)
			map<string, pdd> f = F_[i];			
			double suma = 0;
			int c = 0;
			auto it = f.begin();
			for (; it != f.end() && c <= n - 1; it++) {
				suma += it->second.first * pow(p_he[c++], it->second.second);
			}
			suma += it->second.first;//la constante!
			
			//valor numérico de f(p)
			double suma2 = 0;
			c = 0;
			it = f.begin();
			for (; it != f.end() && c <= n - 1; it++) {
				suma2 += it->second.first * pow(X0[c++], it->second.second);
			}
			suma2 += it->second.first;//la constante!

			//guardo
			fila.push_back((suma-suma2)/aproximacion);

			e[j] = 0;
		}
		matriz_jacobiana.push_back(fila);
	}
	return matriz_jacobiana;
}

//POR NO HACER HEADERS:::::::::::::::::::::
//-----------------------------------------

double **escalona(double AE[filas][columnas+1])
{
	const int f = filas, c= columnas+1;
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
	const int f = filas, c= columnas+1;
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

//-----------------------------------------















