#include <iostream>
#include <climits>
using namespace std;

const int N = 3; // Amõba tábla mérete

// Függvények deklarációja
void inicializalTabla(char tabla[][N]);
void tablaKiir(char tabla[][N]);
bool ervenyesLepes(char tabla[][N], int sor, int oszlop);
bool jatekVege(char tabla[][N]);
char nyertes(char tabla[][N]);
int minimax(char tabla[][N], int depth, bool maximizingPlayer);
void gepLepes(char tabla[][N]);

int main() {
    char tabla[N][N];

    inicializalTabla(tabla);

    while (!jatekVege(tabla)) {

        tablaKiir(tabla);

        int sor, oszlop;
        do {
            cout << "Te kovetkezel. Add meg a sor es oszlop szamat (1-3): ";
            cin >> sor >> oszlop;
            sor--; oszlop--;

            if (!ervenyesLepes(tabla, sor, oszlop)) {
                cout << "Ervenytelen lepes! Probald ujra." << endl;
            }
        } while (!ervenyesLepes(tabla, sor, oszlop));

        tabla[sor][oszlop] = 'X';

        char winner = nyertes(tabla);
        if (winner == 'X') {
            tablaKiir(tabla);
            cout << "Gratulalunk! A gyoztes: X" << endl; //valojaban ez nem fog bekovetkezni
            break;
        } else if (winner == 'O') {
            tablaKiir(tabla);
            cout << "Sajnalom, a gep nyert! (O)" << endl;
            break;
        }

        gepLepes(tabla);
    }

    if (jatekVege(tabla) && nyertes(tabla) == ' ') {
        tablaKiir(tabla);
        cout << "Dontetlen!" << endl;
    }

    return 0;
}

void inicializalTabla(char tabla[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabla[i][j] = ' ';
        }
    }
}

void tablaKiir(char tabla[][N]) {
    cout << "  ";
    for (int i = 0; i < N; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < N; j++) {
            cout << tabla[i][j];
            if (j < N - 1) {
                cout << "|";
            }
        }
        cout << endl;
        if (i < N - 1) {
            cout << "  ";
            for (int k = 0; k < N; k++) {
                cout << "-";
                if (k < N - 1) cout << "+";
            }
            cout << endl;
        }
    }
    cout << endl;
}

bool ervenyesLepes(char tabla[][N], int sor, int oszlop) {
    return tabla[sor][oszlop] == ' ';
}

bool jatekVege(char tabla[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabla[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

char nyertes(char tabla[][N]) {
    for (int i = 0; i < N; i++) {
        if (tabla[i][0] == tabla[i][1] && tabla[i][1] == tabla[i][2] && tabla[i][0] != ' ') {
            return tabla[i][0];
        }
        if (tabla[0][i] == tabla[1][i] && tabla[1][i] == tabla[2][i] && tabla[0][i] != ' ') {
            return tabla[0][i];
        }
    }

    if (tabla[0][0] == tabla[1][1] && tabla[1][1] == tabla[2][2] && tabla[0][0] != ' ') {
        return tabla[0][0];
    }
    if (tabla[0][2] == tabla[1][1] && tabla[1][1] == tabla[2][0] && tabla[0][2] != ' ') {
        return tabla[0][2];
    }
    return ' ';
}

int minimax(char tabla[][N], int depth, bool maximizingPlayer) {
    char result = nyertes(tabla);
    if (result != ' ') {
        if (result == 'O') {
            return 1;
        } else {
            return -1;
        }
    }

    if (jatekVege(tabla)) {
        return 0;
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (tabla[i][j] == ' ') {
                    tabla[i][j] = 'O';
                    int eval = minimax(tabla, depth + 1, false);
                    tabla[i][j] = ' '; // Visszaállítjuk az eredeti állapotot
                    maxEval = max(maxEval, eval);
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (tabla[i][j] == ' ') {
                    tabla[i][j] = 'X';
                    int eval = minimax(tabla, depth + 1, true);
                    tabla[i][j] = ' ';
                    minEval = min(minEval, eval);
                }
            }
        }
        return minEval;
    }
}

//  Minimax algoritmus
void gepLepes(char tabla[][N]) {
    int moveVal = INT_MIN;
    int moveRow = -1;
    int moveCol = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (tabla[i][j] == ' ') {
                tabla[i][j] = 'O';
                int eval = minimax(tabla, 0, false);
                tabla[i][j] = ' ';

                if (eval > moveVal) {
                    moveRow = i;
                    moveCol = j;
                    moveVal = eval;
                }
            }
        }
    }

    tabla[moveRow][moveCol] = 'O';
}

