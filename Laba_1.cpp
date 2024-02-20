#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

bool zamen(double** A, double* b, double N, int i){
    int y;
    bool flag = true;
    for (int j = i; j < N; j++){
        if(A[i][j] != 0){
            y = j;
            for(int k = 0; k < N; k++){
                int c;
                c = A[j][i];
                A[j][i] = A[j][y];
                A[j][y] = c;
            }
            bool flag = true;
            break;
        }
        else
            flag = false; 
    }
    return flag;
}

void del(double** A, double* b, double N, int i){
    for (int j = i + 1; j < N; j++){
        double per = 0.0;
        if (i < N - 1)
            per = A[j][i];
        for (int k = i; k < N; k ++){
            A[j][k] = A[j][k] - (A[i][k] * per);
        }
        b[j] = b[j] - b[i] * per;
    }
}

void Info(double** A, double* b, double N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << A[i][j] << "*x" << j+1;
            if (j < N - 1)
                cout << " + ";
        }
        cout << " = " << b[i] << endl;   
    }
}

int main(){
    mt19937 gen;
    gen.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist;
    int N = 0;
    while (N < 2){
        N = dist(gen) % 7;
    }
    double** A = new double*[N];
    double* b = new double[N];

    for (int i = 0; i < N; i++){
        A[i] = new double[N];
    }
    for (int i = 0; i < N; i ++){
        for (int j = 0; j < N; j ++){
            A[i][j] = 1 + dist(gen) % 20;
        }
        b[i] = dist(gen) % 100;
    }
    cout << N << endl;
    Info(A, b, N);
    double** B = new double* [N];
    for (int j = 0; j < N; j++){
        B[j] = new double[N];
        for (int k = 0; k < N; k++)
            B[j][k] = A[j][k];
    }
    for (int i = 0; i < N; i ++){
        double GlEl = 0;
        GlEl = A[i][i];
        bool fl = true;
        if (GlEl == 0){
        fl = zamen(A, b, N, i);
            if (!fl){
                cout << "Eror";
                return 0;
            }
            cout << "--------------------------" << endl;
            Info(A, b, N);
            cout << "--------------------------" << endl;
        }
        for (int j = i; j < N; j ++){
            A[i][j] = A[i][j] / GlEl;
        }
        b[i] = b[i] / GlEl;

        cout << "--------------------------" << endl;
        del(A, b, N, i);
        Info(A, b, N);
        cout << "--------------------------" << endl;
    }

    double* korni = new double [N];
    for (int j = N; j > 0; j--){
        korni[j] = b[j];
        for (int k = j + 1; k < N; k++){
            korni[j] = korni[j] - korni[k] * A[j][k];
        }
    }
    for (int j = 0; j < N; j++){
        cout << "x" << j + 1 << " = " << korni[j] << endl;
    }
    cout << "Матрица погрешности" << endl;
    Info(B, b, N);


    for (int i = 0; i < N; i++){
        delete [] A[i];
    }
    delete [] b;

    return 0;
}