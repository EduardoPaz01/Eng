// CODE BY EDUARDO PAZ //

#include <iostream>
#include <vector>

using namespace std;

char naipes[4] = { 'P' , 'C' , 'E' , 'O' };
int valores[10] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 10 , 11 , 12 };

class EspacoAmostral{
private:
    vector<pair<char, int>> Hand;
    vector<pair<char, int>> Allcards;
public:
    EspacoAmostral( void );
    ~EspacoAmostral();
    
    double Probabilidade ( pair<char, int> Card );
    
    void Print_Hand( void );
    void Print_Card( pair<char, int> Card );
    
    void Set_NewCard ( void );
    void Play_hand( void );
    
    int Get_Hand_Size ( void );
    vector<pair<char, int>> Get_Hand(void);
    
    void Remove_Card ( pair<char, int> Card );
};

int main() {
    EspacoAmostral EA;
    bool game = true;
    
    //Cartas recebidas
    for(int i = 0; i<3 ; i++){
        EA.Set_NewCard();
    }
    EA.Print_Hand();
    
    //Looping principal
    while(game){
        bool vez;
        cout<<"De quem é a vez( 0-Eu, 1-Outro )? ";
        cin >> vez;
        switch(vez){
            case 0:
                for(int i =0; i<3; i++)
                    EA.Probabilidade(EA.Get_Hand()[i]);
                
                
            case 1:
                pair<char, int> Card;
    
                cout<<"Digite a carta jogada: "<< endl << "Naipe( P,C,E,O ): ";
                cin >> Card.first;
                cout<<"Valor( 1-12 ): ";
                cin >> Card.second;
                cout<<endl;
                
                EA.Remove_Card( Card );
        }
    }
    
    return 0;
}

//Construtores
EspacoAmostral::EspacoAmostral( void ){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<10; j++){
            Allcards.push_back(make_pair(naipes[i], valores[j]));
        }
    }    
}
EspacoAmostral::~EspacoAmostral( void ){
    
}

//Probabilidade
double EspacoAmostral::Probabilidade( pair<char, int> Card ){
    
    //realiza backup do Allcard para fazer remoção temporária da mão atual
    vector<pair<char, int>> EspacoReal = Allcards;
    
    //Remove as cartas já vistas do espaço amostral
    for(int i = 0; i<Hand.size(); i++) Remove_Card( Hand[i] );
    
    //Adiciona a carta a ser analisada
    Allcards.push_back( Card );
    
    //Conta quantos cartas são maiores que a sua
    //Entre 1 e 3
    int szMaiores = 0;
    if(Card.second < 4) {
        for(int i = 0; i<Allcards.size(); i++){
            if(Allcards[i].second > Card.second && Allcards[i].second < 4) szMaiores++;
        }
    }
    else if(Card.second > 3){
        for(int i = 0; i<Allcards.size(); i++){
            if(Allcards[i].second>0 && Allcards[i].second < 4) szMaiores++;
        }
    }
    //Entre 4 e 12
    if(Card.second > 3){
        for(int i = 0; i<Allcards.size(); i++){
            if(Allcards[i].second > Card.second) szMaiores++;
        }
    }
    Print_Card( Card );
    double probabilidade = 100.0 - 100*szMaiores/(float)Allcards.size();
    cout<< ":" << probabilidade << "%" << endl;
    //cout<<"Quantidade de cartas maiores: "<<szMaiores<<endl;
    
    //Retorna ao normal o vetor do allcards
    Allcards = EspacoReal;
}

//Iterativo tela
void EspacoAmostral::Print_Hand( void ){
    
    for (int i = 0; i<Hand.size(); i++){
        Print_Card( Hand[i] );
        cout << endl;
    }
    
}
void EspacoAmostral::Print_Card( pair<char, int> Card ){
    
    cout<< "( " << Card.first << " , " <<Card.second << " )";
    
}

//Set's
void EspacoAmostral::Set_NewCard( void ){
    
    pair<char, int> Card;
    
    cout<<"Digite a sua nova carta: "<< endl << "Naipe( P,C,E,O ): ";
    cin >> Card.first;
    cout<<"Valor( 1-12 ): ";
    cin >> Card.second;
    cout<<endl;
    
    Hand.push_back( Card );
    
}
void EspacoAmostral::Play_hand( void ){
    
    cout << "Digite a carta jogada: "<< endl << "Naipe( P,C,E,O ): ";
    cin >> Card.first;
    cout << "Valor( 1-12 ): ";
    cin >> Card.second;
    cout << endl;
    
    EA.Remove_Card( Card );
    bool flag = true;
    //Remove a carta
    for(int i = 0; i<Allcards.size()  && flag; i++) 
        if(Card.first == Allcards[i].first)
            if(Card.second == Allcards[i].second)
                Allcards.erase(Allcards.begin() + i);
};

//Get's
int EspacoAmostral::Get_Hand_Size( void ){
    
    return Hand.size();
    
}
vector<pair<char, int>> EspacoAmostral::Get_Hand(void){
    return Hand;
};

//Remove
void EspacoAmostral::Remove_Card( pair<char, int> Card ){
    
    bool flag = true;
    
    //Remove a carta
    for(int i = 0; i<Allcards.size()  && flag; i++) 
        if(Card.first == Allcards[i].first)
            if(Card.second == Allcards[i].second)
                Allcards.erase(Allcards.begin() + i);
}



