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
using vvd = vector< vector<double> >;

vd newton_sistema (vd F, vvd JF, vd X0, int n, double tolerancia);

vd evalua(vector<map<string,pdd>> F_, vd X0, int n);

vector<vector<map<string,pdd>>> jacobiano(vector<map<string,pdd>> F_, int n);

vvd evalua(vector<vector<map<string,pdd>>> JF_, vd X0, int n);

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

    //F   
    //------------------------------- 
    
	vector< map<string, pdd> > F_;
	
	map<string, pdd> f1;
	f1["x"] = pdd(1,2);
	f1["y"] = pdd(1,2);
	f1["z"] = pdd(1,2);
	f1["zz"] = pdd(-2,1);
	
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
	f3["zz"] = pdd(0,1);
	
	F_.push_back(f3);
	
	vd X0 = {1,0,0};
	vd F = evalua(F_, X0, n);

    //JF
    //------------------------------- 
    
    vector< vector< map<string, pdd> > >JF_;
    JF_ = jacobiano(F_, n);
    vvd JF = evalua(JF_, X0, n);
    
    //Newton_sistema
    //-------------------------------     
    double tolerancia = 0.000001;
    vd resultado = newton_sistema(F,JF,X0,n,tolerancia);
    
    for(int i=0;i<=n-1;i++)
		cout << "X["<<i+1<<"] = "<<resultado[i] << '\n';
	
	//Para verificar resultado
    //-------------------------------
	
	
	return 0;
}

vd newton_sistema (vd F, vvd JF, vd X0, int n, double tolerancia)
{
    double A[3][3];//Se pone 3 y no n por no usar header
    int f=0,c;
    double b[3];//Se pone 3 y no n por no usar header
    double *V_;
    double *ptr;
    vd V;
    double suma_tolerancia, x0_;
    do{
        //Por no usar header
        //----
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
        for(int i=0; i<=n-1; i++){
            V.push_back(*(ptr++));
        }    	
	    //Xn = X-V;
	    suma_tolerancia=0;
	    for(int i=0; i<=n-1; i++){
	    	x0_ = X0[i];
            X0[i] = X0[i]-V[i];
            suma_tolerancia += abs(X0[i]-x0_);
        }
    }while(suma_tolerancia <= tolerancia);
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

map<string,pdd> derivada(map<string,pdd> mapa_fi,string letra);
vector<vector<map<string,pdd>>> jacobiano(vector<map<string,pdd>> F_, int n)
{
    vector<string> letras = {"x","y","z","v","w"};
    vector<vector<map<string,pdd>>> matriz_jacobiana;
    for(int i=0; i<=n-1; i++){
        vector<map<string,pdd>> fila;
        for(int j=0; j<=n-1; j++){
            fila.push_back(derivada(F_[i],letras[j]));
        }
        matriz_jacobiana.push_back(fila);
    }
    return matriz_jacobiana;
}
map<string,pdd> derivada(map<string,pdd> mapa_fi,string letra)
{
    map<string,pdd> mapa_r;
    pdd termino;
    termino.first = mapa_fi[letra].second * mapa_fi[letra].first;
    termino.second = mapa_fi[letra].second-1;
    mapa_r[letra] = termino;
    return mapa_r;
}


vvd evalua(vector<vector<map<string,pdd>>> JF_, vd X0, int n)
{
    vector<string> letras = {"x","y","z","v","w"};
    vvd matriz_jacobiana_r;
    for(int i=0; i<=n-1; i++){
        vd fila;
        for(int j=0; j<=n-1; j++){
            fila.push_back(
                        JF_[i][j][letras[j]].first*pow(X0[j],JF_[i][j][letras[j]].second)
                        );
        }
        matriz_jacobiana_r.push_back(fila);
    }
    return matriz_jacobiana_r;
}







//POR NO HACER HEADERS:::::::::::::::::::::
//-----------------------------------------

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

//-----------------------------------------















