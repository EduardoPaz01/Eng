// CODE BY EDUARDO PAZ //

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <cmath>

int main() {
    
    //Lê o arquivo inicial como string
    std::string nome_arquivo = "arquivo";
    std::wifstream arquivo(nome_arquivo);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    arquivo.imbue(loc);
    std::wstringstream buffer;
    if (arquivo) {
        buffer << arquivo.rdbuf();
        arquivo.close();
    }
    std::wstring conteudo = buffer.str();
    
    //Remove virgula travessoes e espaços excessivos
    std::replace(conteudo.begin(), conteudo.end(), L',', L'.');
    std::replace(conteudo.begin(), conteudo.end(), L'-', L' ');
    std::replace(conteudo.begin(), conteudo.end(), L'–', L' ');
    size_t pos = conteudo.find(L"   ");
    while (pos != std::wstring::npos) {
        conteudo.erase(pos, 2);
        pos = conteudo.find(L"   ");
    }
    
    //Substitui no arquivo original
    std::wofstream arquivo2(nome_arquivo);
    arquivo2.imbue(loc);
    arquivo2 << conteudo;
    arquivo2.close();
    
    
    //Lê o arquivo com números
    std::wifstream arquivo3("arquivo");
    std::vector<float> numeros;
    float num;
    while (arquivo3 >> num) {
        numeros.push_back(num);
    }
    arquivo3.close();
    
    //Booble Short
    float repete,  aux, tamanho = (int)(numeros.size());
    int pos2;
    repete = 0;
    bool trocou;
    do{
        trocou = false;
        for(pos2 = 0; pos2 < tamanho -1; pos2++)
            if(numeros[pos2] > numeros[pos2 +1])
            {
                aux = numeros[pos2];
                numeros[pos2] = numeros[pos2 +1];
                numeros[pos2 +1] = aux;
                trocou = true;
            }
        if (trocou)
            repete ++;
    }
    while (repete < tamanho && trocou);
    
    //Substitui no arquivo original
    std::wofstream arquivo4(nome_arquivo);
    arquivo4.imbue(loc);
    for (int i = 0; i < tamanho; i++) 
        arquivo4 << numeros[i] << " ";
    arquivo4.close();
    std::wcout << L" ";


    
///////////////////////////////////////////////////////////////////////////////////////////


    
    float *vetor = new float(tamanho);
    for (int i = 0; i < tamanho; i++) 
        vetor[i] = numeros[i];
    
    for (int i = 0; i < tamanho; i++)
        std::wcout<< *(vetor+i) << " ";
    
    float soma = 0;
    for (int i = 0; i < tamanho; i++) 
        soma += *(vetor+i);
    float media = soma/tamanho;
    std::wcout << std::endl << "A soma é: " << soma << " tamanho: " << tamanho <<std::endl;
    std::wcout << "Media: " << media << std::endl; 
    
    //Mediana
    int piso = floor(tamanho/2.0);
    if((int)(tamanho)%2 == 0)
        std::wcout << "Mediana par: " << ((*(vetor+piso)+*(vetor+piso-1))/2.0) << std::endl;
    else
        std::wcout << "Mediana impar: " << *(vetor+piso) << std::endl;
    
    //Variância
    float quadrados = 0;
    for (int i = 0; i < tamanho; i++) {
        quadrados+= (*(vetor+i)-media)*(*(vetor+i));
    }
    float variancia = quadrados / tamanho;
    std::wcout << "Variancia: " << quadrados << " / " << tamanho << " = " << variancia << std::endl;
    
    //Desvio Padrao
    float desvio_padrao = sqrt(variancia);
    std::wcout << "Desvio padrao: " << desvio_padrao << std::endl;
    
    //Coeficiente de variação
    float cv = desvio_padrao / media;
    std::wcout << "Coeficiente de variacao: " << cv << std::endl;
    
    //Calculo dos 3 quartis
    float POSquartil[4];
    for (int i = 1; i < 4; i++) {
        if ((int)(tamanho)%2 == 0)
            POSquartil[i] = (i*tamanho + 2)/4.0;
        else
            POSquartil[i] = i*(tamanho + 1)/4.0;
        std::wcout << "Pos Quartil " << i << ": " << POSquartil[i] << std::endl;
    }
    
    //Calculo do I e dos limites
    float quartil[4];
    for(int i = 1; i < 4; i++){
        double parte_decimal = std::abs(POSquartil[i] - std::floor(POSquartil[i]));
        if (parte_decimal == 0.5){
            quartil[i] = (numeros[floor(POSquartil[i])-1] + numeros[ceil(POSquartil[i])-1])/2.0;
        }
        else
            quartil[i] = numeros[POSquartil[i]-1];
        std::wcout << "Valor Quartil " << i << ": " << quartil[i] << std::endl;
    }
    float Aq = quartil[3] - quartil[1];
    float LimiteInferior, LimiteSuperior;
    if((quartil[1]-1.5*Aq) < numeros[0])
        LimiteInferior = numeros[0];
    else
        LimiteInferior = quartil[1]-1.5*Aq;
    if((quartil[3]+1.5*Aq) > numeros[tamanho-1])
        LimiteSuperior = numeros[tamanho-1];
    else
        LimiteSuperior = quartil[3]+1.5*Aq;
    std::wcout << "Aplitude interquartilica (Aq) : " << Aq << std::endl;
    std::wcout << "Limite Inferior: " << LimiteInferior << std::endl;
    std::wcout << "Limite Superior: " << LimiteSuperior << std::endl;
    
    
    
    
    

    
///////////////////////////////////////////////////////////////////////////////////////////



    //Localiza o menor
    float menor = numeros[0];
    for (const auto& n : numeros)
        if(n < menor)
            menor = n;
    std::wcout << "\nMenor valor encontrado: " << menor << std::endl;
    
    //Localiza o maior
    float maior = numeros[0];
    for (const auto& n : numeros)
        if (n > maior)
            maior = n;
    std::wcout << "Maior valor encontrado: " << maior << std::endl;
    std::wcout << "Aplitute de classe: " << maior - menor << std::endl;

    std::vector<float> num2; 
    std::vector<int> Quant_num;
            int Quantidade_de_intervalos = ceil(1 + 3.3*log10(numeros.size()));
    if (numeros.size()<= 50)
        Quantidade_de_intervalos = ceil(sqrt(numeros.size()));
    float Aplitute_Intervalos = (ceil(1*(maior-menor)/Quantidade_de_intervalos))/1;
    std::wcout << "Quantidade_de_intervalos: " << Quantidade_de_intervalos << std::endl;
    std::wcout << "Aplitute_Intervalos: " << Aplitute_Intervalos << std::endl << std::endl;
    
    //Calcula os intervalos
    for (int i = 0; i <= Quantidade_de_intervalos; i++)
        num2.push_back(menor + Aplitute_Intervalos*i);
    std::wcout << "Intervalos: ";
    for (auto i : num2) 
        std::wcout << " " << i;
    std::wcout << std::endl;
    
    //Localiza os termos nesse intervalo
    for (int i = 0; i < Quantidade_de_intervalos; i++) {
        Quant_num.push_back(0);
        for (const auto& n : numeros)
            if(n>= num2[i] && n < num2[i+1])
                Quant_num[i]+=1;
    }
    
    //Printa a quantidade de termos em cada intervalo
    std::wcout << "Valores de cada intervalo: ";
    for (const auto& n : Quant_num)
        std::wcout << " " << n;
    std::wcout << std::endl;
    
    //Acumula a quantidade de termos de cada intervalo
    std::vector<int> Acumulado;
    for (int i = 0; i < Quantidade_de_intervalos; i++) {
        Acumulado.push_back(0);
        for (int j = i; j >= 0; j--) {
            Acumulado[i] += Quant_num[j];
        }
    }
    
    //Printa a quantidade de termos de cada intervalo Acumulado
    std::wcout << "Acumulado: ";
    for (auto i : Acumulado) {
        std::wcout << " " << i;
    }
    std::wcout << std::endl;
    
    //Calcula a frequencia relativa
    std::vector<float> frequencia_relativa;
    soma = 0.0;
    for (auto i : Quant_num) {
        soma += i;
    }
    for (int i = 0; i < Quantidade_de_intervalos; i++) {
        frequencia_relativa.push_back(Quant_num[i]/soma);
    }
    std::wcout << "frequencias relativas: ";
    for (auto i : frequencia_relativa) {
        std::wcout << " " << i*100;
    }
    std::wcout << std::endl;
    
    //Acumula a frequencia relativa
    std::vector<float> Acumulado_Relativa;
    for (int i = 0; i < Quantidade_de_intervalos; i++) {
        Acumulado_Relativa.push_back(0);
        for (int j = i; j >= 0; j--) {
            Acumulado_Relativa[i] += frequencia_relativa[j];
        }
    }
    
    //Printa a frequencia relativa Acumulado
    std::wcout << "Acumulado: ";
    for (auto i : Acumulado_Relativa) {
        std::wcout << " " << i;
    }
    std::wcout << std::endl;

    return 0;
}
