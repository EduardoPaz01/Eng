// CODE BY EDUARDO PAZ //

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Sistema{
private:
    vector<vector<double>> A;
    vector<double> B;
    vector<double> x;
    unsigned int Ordem;

public:
    Sistema(size_t Ordem)
        : Ordem(Ordem), A(Ordem, vector<double>(Ordem, 0.0)), B(Ordem), x(Ordem) {};
    ~Sistema() {};

    void entrada_A(void);
    void Cholesky(void);
    void printSistema(void);
    void printSolucao(void);
};


int main(){

    // Define como será o sistema
    size_t Ordem;
    cout <<"Defina a ordem da matriz dos coeficientes:";
    cin >> Ordem;
    Sistema SistemaLinear(Ordem);

    // Define o Sistema
    SistemaLinear.entrada_A();

    // Calcula o Sistema
    SistemaLinear.Cholesky();

    // Mostra a Solução
    SistemaLinear.printSolucao();

    return 0;
}


void Sistema::entrada_A(void){

    cout << "Defina a matrix dos coeficientes:"<<endl;

    // Entrada da Matrix A
    for(unsigned int i=0; i<Ordem; i++){
        for(unsigned int j=0; j<Ordem; j++){
            for(unsigned int u=0; u<Ordem; u++){
                cout << '[';
                for(unsigned int k=0; k<Ordem; k++){
                    if(u < i) cout << " "<< A[u][k] <<" ";
                    else if(u > i) cout << "   ";
                    else{
                        if(k < j) cout << " "<< A[u][k] <<" ";
                        else if(k == j) cout << " * ";
                        else cout << "   ";
                    }
                }
                cout << "]\n";
            }
            cout << "\n";

            cout << "Termo a" << i+1 << j+1 << ": ";
            cin >> A[i][j];
            system("clear");//Dependendo do compilador, é necessário trocar o "clear" por "cls"
        }
    }

}
void Sistema::Cholesky(void){

    // Variáveis
    vector<vector<double>> G(Ordem, vector<double>(Ordem, 0.0));
    vector<vector<double>> Gt(Ordem, vector<double>(Ordem, 0.0));
    vector<double> y(Ordem);
    
    //Verifica se é simétrica
    bool simetrica = true;
    for (int i = 0; i < Ordem; ++i) {
        for (int j = 0; j < Ordem; ++j) {
            if (A[i][j] != A[j][i]) {
                simetrica = false;
                cout << "Erro: A matriz não é simétrica." << endl;
            }
        }
    }
    
    //Verifica se é determinada positiva e calcula G
    bool determinadaPositiva = true;
    for (unsigned int i = 0; i < Ordem; i++) {
        for (unsigned int j = 0; j <= i; j++) {
            double sum = 0;
            if (j == i) {
                for (unsigned int k = 0; k < j; k++) sum += G[j][k] * G[j][k];
                double valor = A[j][j] - sum;
                if (valor < 0){
                    cout << "Erro: A matriz não é positiva definida." << endl;
                    determinadaPositiva = false;
                }
                G[j][j] = sqrt(valor);
            } else {
                for (unsigned int k = 0; k < j; k++) sum += G[i][k] * G[j][k];
                G[i][j] = (A[i][j] - sum) / G[j][j];
            }
        }
    }

    //Função recursiva para inserir matriz de coeficientes válida
    if(!determinadaPositiva || !simetrica) {
        cout<<"Tente novamente."<<endl<<endl;
        entrada_A();
        Cholesky();
    }
    else {
        // Entrada do B
        cout<<"\nEntre com o vetor B:"<<endl;
        for(unsigned int i=0; i<Ordem; i++){
            cout<<"B "<<i<<": ";
            cin >> B[i];
        }
        
        //Printa o Sistema
        printSistema();
    
        // Gt
        for (unsigned int i = 0; i < Ordem; i++)
            for (unsigned int j = 0; j < Ordem; j++)
                Gt[j][i] = G[i][j];
    
        // G.y = B
        for(unsigned int i=0;i<Ordem; i++){
            double sum = B[i];
            for(unsigned int j=Ordem-i, a=0; j<Ordem; j++,a++) sum -= G[i][a]*y[a];
            y[i] = sum/G[i][i];
        }
    
        // Gt.x = y
        int i = Ordem - 1;
        while (i >= 0) {
            double sum = y[i];
            for (unsigned int j = i + 1, a = Ordem - 1; j < Ordem; j++, a--) sum -= Gt[i][a] * x[a];
            x[i] = sum / Gt[i][i];
            i--;
        }
    }
}
void Sistema::printSistema(void){

    system("clear");//Dependendo do compilador, é necessário trocar o "clear" por "cls"

    for (unsigned int i = 0; i < Ordem; i++) {
        for (int j = 0; j < Ordem; j++) cout << " + "<< right << setw(8) << A[i][j] << " x" << j+1;
        cout <<" = " << left << setw(8) << B[i]<< endl;
    }

}
void Sistema::printSolucao(void){

    for (unsigned int i=0; i<Ordem; i++)
        cout << "x" << i+1 << ": " << x[i] << endl;

}
