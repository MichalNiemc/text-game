#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>


using namespace std;


//glowna struktura gry, ze zdefiniowanom od razu wartoscia
struct gra
{
    char kolor = 'N';
    int moc = 1;
};

//definiowane podprogramy
void bot(gra G[max_k][max_w]);
void wyswietl(gra G[max_k][max_w], string TAB[]);
void ruch(gra G[max_k][max_w], string TAB[], char pop);
void wzrost(gra G[max_k][max_w], int b, int c, char znak_grajacego);
void sprawdzanie(gra G[max_k][max_w], char znak_grajacego);
int koniec(gra G[max_k][max_w]);

//glowny program gry (main)
int main()
{
    gra G[max_k][max_w];
    string TAB[K];
    TAB[0]='F';
    TAB[1]='E';
    TAB[2]='D';
    TAB[3]='C';
    TAB[4]='B';
    TAB[5]='A';


    cout << endl << "Witaj w mojej grze, nacisnij enter aby rozpoczac! :)" << endl<< endl << endl;
    system("pause");
    system("CLS");
    int i = 0;
//glowna petla gry
	do
    {
        c = 0;
        a = 'Z';
//pierwszy i co 2 ruch komputera
        if(i%2 == 0)
        {
            znak_grajacego = 'B';
            pop = 'C';

            bot(G);
            wzrost(G, b, c, znak_grajacego);
            sprawdzanie(G, znak_grajacego);
        }
//drugi i co 2 ruch gracza
        else
        {
            znak_grajacego = 'C';
            pop = 'B';

            system("CLS");
            wyswietl(G, TAB);
            ruch(G, TAB, pop);
            wzrost(G, b, c, znak_grajacego);
            sprawdzanie(G, znak_grajacego);
        }
        i++;

    }while( koniec(G) == 0);

    system("CLS");
    wyswietl(G, TAB);
//koncowy if rozrozniajacy kto wygral
    if ( koniec(G) == 1 )
    {
        cout << endl << "Gratulacje!!! Dobra rozgrywka, wygrales. :)" << endl << endl;
    }
    else if ( koniec(G) == 2 )
    {
        cout << endl << "Niestety, nie udalo ci sie wygrac. Sprobuj ponownie :)" << endl << endl;
    }

    system("pause");
    return 0;
}
//koniec maina


// podprogram wyswietlajacy zawartosc tablicy struktur/ glowna plansza gry
void wyswietl(gra G[max_k][max_w],string TAB[])
{
    cout << endl << endl << "(Player_1)-- wykonal swoj ruch. " << endl << "(Player_2) -- Teraz grasz ty." << endl << endl;

    for(int j=0; j<max_w; j++)
    {
        cout << "  "<< TAB[j] << "    ";
        for(int i=0; i<max_k; i++)
        {
             cout << "| " << G[i][j].kolor << ":" << G[i][j].moc;
        }
        cout << "|" << endl << endl;
    }
    cout << "          0    1    2    3    4    5" << endl << endl;
}


//podprogram dla gracza, gracz wpisuje na ktore pole ustawic (pionka?)
void ruch(gra G[max_k][max_w],string TAB[], char pop)
{
    do{
        cout << "Pole, na ktore chcesz wykonac ruch: " << endl;
        while( a != TAB[0] && a != TAB[1] && a != TAB[2] && a != TAB[3] && a != TAB[4] && a != TAB[5])
        {
            cout << "Podaj litere (A, B, C, D, E, F)";
            cin >> a;
            for(int i=0; i<K; i++)
            {
                if (TAB[i] == a)
                {
                    c=i;
                }
            }
            system("CLS");
            wyswietl(G, TAB);
        }

        while ( b > 5 or b < 0);
        {
            cout << "Podaj liczbe (0, 1, 2, 3, 4, 5,)";
            cin >> b;
            system("CLS");
            wyswietl(G, TAB);
        }
        if ( G[b][c].kolor == pop )
        {
            cout << "nie mozesz wybrac pola przeciwnika :)" << endl << endl;
        }
    }while(G[b][c].kolor == pop);
}


// podprogram stosujacy wzrost liczb do przedmaksymalnej wartosci
void wzrost(gra G[max_k][max_w], int b, int c, char znak_grajacego)
{
    if ( G[b][c].moc == 1 && G[b][c].kolor == 'N')                                          // dla neutrealnych
    {
        G[b][c].moc = 2;
        G[b][c].kolor = znak_grajacego;
    }

    else if (b<=4 && b>=1 && c<=4 && c>=1)                                                  //srodek
    {
        if (G[b][c].moc <= 4)
        {
            G[b][c].moc++;
        }
    }

    else if ((b==0 or b==5) && (c==0 or c==5))                                             // kanty
    {
        if (G[b][c].moc <= 2)
        {
            G[b][c].moc++;
        }
    }

    else                                                                                   //sciany
    {
        if (G[b][c].moc <= 3)
        {
            G[b][c].moc++;
        }
    }
}


// podprogram sprawdzajacy czy wartosc na polach jest maksymalna, jesli tak to rozprasza pole
void sprawdzanie(gra G[max_k][max_w], char znak_grajacego)
{
    for(int i=0; i<5; i++)
    {
    do{
        bool spr;
        spr = true;

        for (int i=0; i<6; i++)
        {
            for (int j=0; j<6; j++)
            {
                if ((i==0 && j==0) or (i==5 && j==0) or (i==0 && j==5) or (i==5 && j==5))
                {
                    if (G[0][0].moc >= 3)
                    {
                        G[0][0].moc -= 2;

                        G[1][0].moc += 1;
                        G[0][1].moc += 1;
                        G[1][0].kolor = znak_grajacego;
                        G[0][1].kolor = znak_grajacego;

                        spr = false;
                    }
                    if (G[5][0].moc >= 3)
                    {
                        G[5][0].moc -= 2;

                        G[4][0].moc += 1;
                        G[5][1].moc += 1;
                        G[4][0].kolor = znak_grajacego;
                        G[5][1].kolor = znak_grajacego;

                        spr = false;
                    }
                    if (G[0][5].moc >= 3)
                    {
                        G[0][5].moc -= 2;

                        G[0][4].moc += 1;
                        G[1][5].moc += 1;
                        G[0][4].kolor = znak_grajacego;
                        G[1][5].kolor = znak_grajacego;

                        spr = false;
                    }
                    if (G[5][5].moc >= 3)
                    {
                        G[5][5].moc -= 2;

                        G[4][5].moc += 1;
                        G[5][4].moc += 1;
                        G[4][5].kolor = znak_grajacego;
                        G[5][4].kolor = znak_grajacego;

                        spr = false;
                    }

                }
                else if (i<=4 && i>=1 && j<=4 && j>=1)
                {
                    if (G[i][j].moc >= 5)
                    {
                        G[i][j].moc -= 4;

                        G[i+1][j].moc += 1;
                        G[i-1][j].moc += 1;
                        G[i][j+1].moc += 1;
                        G[i][j-1].moc += 1;

                        G[i+1][j].kolor = znak_grajacego;
                        G[i-1][j].kolor = znak_grajacego;
                        G[i][j+1].kolor = znak_grajacego;
                        G[i][j-1].kolor = znak_grajacego;

                        spr = false;
                    }
                }
                else
                {
                    if (G[i][j].moc >= 4)
                    {
                        if ( i == 0 )
                        {
                            G[i][j].moc -= 3;

                            G[i+1][j].moc += 1;
                            G[i][j+1].moc += 1;
                            G[i][j-1].moc += 1;

                            G[i+1][j].kolor = znak_grajacego;
                            G[i][j+1].kolor = znak_grajacego;
                            G[i][j-1].kolor = znak_grajacego;

                            spr = false;
                        }
                        else if ( i == 5 )
                        {
                            G[i][j].moc -= 3;

                            G[i-1][j].moc += 1;
                            G[i][j+1].moc += 1;
                            G[i][j-1].moc += 1;

                            G[i-1][j].kolor = znak_grajacego;
                            G[i][j+1].kolor = znak_grajacego;
                            G[i][j-1].kolor = znak_grajacego;

                            spr = false;
                        }
                        else if ( j == 0 )
                        {
                            G[i][j].moc -= 3;

                            G[i+1][j].moc += 1;
                            G[i-1][j].moc += 1;
                            G[i][j+1].moc += 1;

                            G[i+1][j].kolor = znak_grajacego;
                            G[i-1][j].kolor = znak_grajacego;
                            G[i][j+1].kolor = znak_grajacego;

                            spr = false;
                        }
                        else
                        {
                            G[i][j].moc -= 3;

                            G[i+1][j].moc += 1;
                            G[i-1][j].moc += 1;
                            G[i][j-1].moc += 1;

                            G[i+1][j].kolor = znak_grajacego;
                            G[i-1][j].kolor = znak_grajacego;
                            G[i][j-1].kolor = znak_grajacego;

                            spr = false;
                        }
                    }
                }
            }
       }
    }while( spr = false );
    }
}

//zmienne/stale globalne, czemu nikt nie powiedzia³ ¿e nie mo¿na ://///
const int max_k = 6;
const int max_w = 6;
const int K = 6;
string a;
int b;
int c;
char znak_grajacego;
char pop;
bool spr;
int h = 0;



//podprogram definiujacy koniec gry
int koniec(gra G[max_k][max_w])
{
	int wynik = 1;

	for (int i=0; i<6; i++)
    {
        for (int j=0; j<6; j++)
        {
            if ( G[i][j].kolor == 'B' )
            {
                wynik = 0;
                return wynik;
            }
            if ( G[i][j].kolor == 'N' )
            {
                wynik = 0;
                return wynik;
            }
        }
    }
    if ( wynik == 1 )
    {
        return wynik;
    }
    else
    {
        int wynik = 2;

        for (int i=0; i<6; i++)
        {
            for (int j=0; j<6; j++)
            {
                if ( G[i][j].kolor == 'C' )
                {
                    wynik = 0;
                    return wynik;
                }
                if ( G[i][j].kolor == 'N' )
                {
                    wynik = 0;
                    return wynik;
                }
            }
        }
	return wynik;
    }
}


// podprogram odpowiedzialny za ruch komputera (liczby pseudolosowe)
void bot(gra G[max_k][max_w])
{
    do
    {
        srand( time( NULL ) ^ clock() );
        b = (rand() % 6 );
        c = (rand() % 6 );

    }while(G[b][c].kolor == 'C');
}

