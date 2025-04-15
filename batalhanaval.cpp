/*Em um tabuleiro NXN(você escolhe N), o computador deve sortear N posições nesse
tabuleiro, sem que o usuário saiba. Essas posições são a de navios. Agora você deve
dar chutes (tiros na água) para tentar acertar os navios. A cada tiro você der, o 
programa deve dizer se você acertou ou se errou, e se erra, deve dizer quantos navios
tem ali ao redor daquele ponto.*/

#include <iostream>
#include <ctime>

using namespace std;

void mostrar(char mapa[][100], int tam) {
    cout<<"=================\n";
    cout<<"\033[35m  Batalha Naval\n\033[0m";
    cout<<"=================\n\n";
    cout << "   ";
    for (int i = 0; i < tam; i++) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < tam; i++) {
        cout << i << "  ";
        for (int j = 0; j < tam; j++) {
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
}

int contar(int l, int c, int barcos[][100], int tam) {
    int q = 0;
    for (int i = l - 1; i <= l + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
        if (i >= 0 && i < tam && j >= 0 && j < tam) {
            if (barcos[i][j] == 1) {
                    q++;
            }
            }
        }
    }
    return q;
}

int main() {
    srand(time(0));

    int tam, qtd, maxTent;

    cout << "Tamanho do tabuleiro: ";
    cin >> tam;

    cout << "Quantidade de navios: ";
    cin >> qtd;

    cout << "Máximo de tentativas: ";
    cin >> maxTent;
    

    char mapa[100][100];
    int barcos[100][100];

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            mapa[i][j] = '-';
            barcos[i][j] = 0;
        }
    }

    int colocados = 0;
    while (colocados < qtd) {
        int x = rand() % tam;
        int y = rand() % tam;
        if (barcos[y][x] == 0) {
            barcos[y][x] = 1;
            colocados++;
        }
    }

    int pontos = 0;
    int tent = 0;

    while (pontos < qtd && tent < maxTent) {
        
         int x, y;
        system("clear");
        
        if(tent>0){
             if (x < 0 || x >= tam || y < 0 || y >= tam) {
            cout << "Coordenada inválida\n";
            continue;
        }

        if (mapa[y][x] != '-') {
            cout << "Você já tentou aqui\n";
            continue;
        }

        

        if (barcos[y][x] == 1) {
            cout << "Acertou!\n";
            mapa[y][x] ='X';
            pontos++;
        } 
        else {
            int perto = contar(y, x, barcos, tam);
            cout << "Errou! Tem " << perto << " navio(s) por perto\n";
            mapa[y][x] = 'O';
        }

        cout << "Acertos: " << pontos << " de " << qtd << "\n\n";
        }
       
        mostrar(mapa, tam);

       
        cout << "Tentativa " << tent + 1 << " de " << maxTent << endl;
        cout << "Digite a coordenada X (coluna): ";
        cin >> x;
        cout << "Digite a coordenada Y (linha): ";
        cin >> y;
         tent++;
       
    }

    if (pontos == qtd) {
        cout << "Parabéns! Você ganhou!\n";
    } else {
        cout << "Acabaram as tentativas...\n Você perdeu!\n";
        cout << "Navios que faltaram:\n";

        for (int i = 0; i < tam; i++) {
            for (int j = 0; j < tam; j++) {
                if (barcos[i][j] == 1 && mapa[i][j] != 'X') {
                    mapa[i][j] = 'N';
                }
            }
        }

        mostrar(mapa, tam);
    }

    return 0;
}