#include <iostream>

using namespace std;
const int f = 4, c = 4;
using  pair_mm = pair<double[f][c], double[f][c]>  ;
using  pair_mmm = pair<double[f][c], pair<double[f][c], double[f][c]> >  ;

pair_mm descomp_lu(double A[f][c]);
double *sust_progresiva(double A[f][c], double b[f]);
double *resuelve_sist_con_lu(double A[f][c], double b[f]);
pair_mmm descomp_plu(double A[f][c]);
double *resuelve_sist_con_plu(double A[f][c], double b[f]);

int main()
{
    /*
    double A[f][c]= {{0,0,-1,1},{1,1,-1,2},{-1,-1,2,0},{1,2,0,2}};
	double b[f] = {4,3,2,1};
	*/
	/*
	double A[f][c]= {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	double b[f] = {1,2,3,4};
	*/
	/*
	double A[f][c]= {{1,-1,2,2},{2,-2,1,1},{-2,-1,0,1},{3,2,-1,1}};
	double b[f] = {1,2,3,4};
	*/
	
	double A[f][c]= {
				{2,3,4,-5},
				{-3,4,-5,7},
				{5,1,-1,6},
				{7,9,-13,17}};
				
	double b[f] = {7,2,5,21};
		
	double *x = resuelve_sist_con_plu(A,b);
    
    	//----- Solo para verificar
	double r[f];
	for(int i=0; i <=f-1; i++){
		r[i] = 0;
		for(int j=0; j<= f-1; j++){
			r[i] += A[i][j]*x[j];
	 	}
	}
	for(int i=0;i<=f-1;i++)
		cout << "b["<<i+1<<"] = "<<r[i] << '\n';
	//----- 

    return 0;
}

pair_mm descomp_lu(double A[f][c])
{
    pair_mm l_u;
    // L = identidad
    for(int i=0; i<= f-1; i++){
         for(int j=0; j<= c-1; j++){
            if(i==j) l_u.first[i][j] = 1;
            else
                l_u.first[i][j] = 0;
         };
    }
    
    for(int j=0; j <= c-2; j++){
		for(int i=j+1; i <= f-1; i++){
			l_u.first[i][j] = A[i][j]/A[j][j];
			for(int k=0; k<= c-1; k++){
				A[i][k] = A[i][k] - l_u.first[i][j]*A[j][k];
			}
		}	
	}
    for(int i=0; i <= f-1; i++){
		for(int j=0; j <= c-1; j++){
			l_u.second[i][j] = A[i][j];		
			if(i==j && l_u.second[i][j] == 0){
			    cout << "No admite descomposición LU.\n";			    
			}
		}	
	}
    return l_u;    
}

double *sust_progresiva(double A[f][c], double b[f])
{
    double *X = new double[f];
    for(int i=0; i != f; i++){
	   X[i] = 0;
    }
	for(int i = 0; i != f; i++){
		X[i] = b[i];
		for(int j = i-1; j != -1; j--){
			X[i] = X[i]-A[i][j]*X[j];
		}
		X[i] = X[i]/A[i][i];
	}
    return X;
}

double *sust_regresiva(double A[f][c], double b[f])
{
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

double *resuelve_sist_con_lu(double A[f][c], double b[f])
{
    pair_mm l_u = descomp_lu(A);
    double *y = sust_progresiva(l_u.first,b);		
    double *x = new double[f];
    x = sust_regresiva(l_u.second, y);
    return x;
}

void int_filas(double m[f][c],int x, int y)
{
    double t;
    for(int i=0; i<=c-1;i++){
        t = m[x][i];
        m[x][i] = m[y][i];
        m[y][i] = t;        
    }
}

pair_mmm descomp_plu(double A[f][c])
{
    pair_mmm p_l_u;
    // U = A
    for(int i=0; i<= f-1; i++){
         for(int j=0; j<= c-1; j++){
            p_l_u.second.second[i][j] = A[i][j];
         }
    }
    //P identidad
    for(int i=0; i<= f-1; i++){
         for(int j=0; j<= c-1; j++)
            if(i==j) p_l_u.first[i][j] = 1;
            else
                p_l_u.first[i][j] = 0;
    }
    //L, ceros
    for(int i=0; i<= f-1; i++){
         for(int j=0; j<= c-1; j++){
            p_l_u.second.first[i][j] = 0;
         }
    }
    
    for(int j=0; j <=f-2; j++){
        double max = p_l_u.second.second[j][j];
        int max_f = j;
        for(int x=j+1; x<=f-1; x++){
            if(max < p_l_u.second.second[x][j]){
                max =  p_l_u.second.second[x][j];
                max_f = x;
            }
        }
        if(j!=max_f){
            int_filas(p_l_u.second.second,j, max_f);
            int_filas(p_l_u.first,j, max_f);
            int_filas(p_l_u.second.first,j, max_f);
        }
        for(int i=j+1; i<=f-1;i++){
            double v = p_l_u.second.second[i][j]/p_l_u.second.second[j][j];
            p_l_u.second.first[i][j] = v;
            for(int k=0; k<=c-1;k++){
                p_l_u.second.second[i][k] -= v*p_l_u.second.second[j][k];
            }
        }
    }
    
    for(int i=0; i<= f-1; i++){
        for(int j=0; j<= c-1; j++){
            if(i==j) 
            p_l_u.second.first[i][j] += 1;
        }
    }
    
    return p_l_u;    
}

double *resuelve_sist_con_plu(double A[f][c], double b[f])
{
    pair_mmm p_l_u = descomp_plu(A);
    double pb[f];
    // pb = p*b, matricial
    for(int i=0; i <=f-1; i++){
        pb[i] = 0;
        for(int j=0; j<= c-1; j++){
            pb[i] += p_l_u.first[i][j]*b[j];
        }
    }
    double *y = sust_progresiva(p_l_u.second.first,pb);
    double *x = new double[f];
    x = sust_regresiva(p_l_u.second.second, y);
    return x;
}















