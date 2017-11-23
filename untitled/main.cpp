// Manipulator.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include<iostream>
#include<math.h>
#include<time.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

//Êëàññ Manipulator. Õðàíèò êîëè÷åñòâî çâåíüåâ, èìååò ìåòîä ïåðåíîñà ìàññèâà ñ ïàðàìåòðàìè Äåíàâèòà-Õàðòåíáåðãà

class Manipulator
{
public:
    float **A, *B, *coord;
    int m, n;
    float C[4][4]; float D[4][4]; float E[4][4];
public:
    Manipulator() {};
    Manipulator(int l, int f);                //èíèöèàëèçàöèÿ
    Manipulator(const Manipulator &ob);      //è ñîçäàíèå ìàòðèö
    ~Manipulator();
    void show();
    void function(int m1, int n1);
    void matrix(float q,float w, float e, float r);        //ñîçäàíèå ìàòðèöû Ñ
    void solution();
};

Manipulator::Manipulator(int l, int f)
{
    function(l, f);
}
Manipulator::Manipulator(const Manipulator &ob)
{
    function(ob.m, ob.n);
    for (int i = 0; i<ob.m; i++)
    {
        for (int j = 0; j<ob.n; j++)
        {
            A[i][j] = ob.A[i][j];
        }
    }
}
Manipulator::~Manipulator()
{
    for (int i = 0; i<m; i++)
    {
        delete[]A[i];
    }
    delete[]A;
}
void Manipulator::show()
{
    int k = 0;
    std::srand(time(NULL));
    for (int i = 0; i<m; i++)
    {
        for (int j = 0; j<n; j++)
        {                                      //òóò çàïîëíåíèå
            k++;

            cout << A[i][j] << ' ';
        }
        cout << endl;
    }
}
void Manipulator::function(int m1, int n1)
{
    A = new float*[n1];
    B = new float[m1];
    coord = new float[m1];
    //cout <<"ìàññèâ B ñîçäàí";
    for (int i = 0; i<m1; i++)
    {
        for (int j = 0; j<n1; j++)
        {
            A[i] = new float[n1];
        }
    }
    m = m1;
    n = n1;
}
void Manipulator::matrix(float q, float w, float e, float r) {
    C[0][0] = cos(q); C[0][1] = -cos(w)*sin(q); C[0][2] = sin(w)*sin(q); C[0][3] = e*cos(q);
    C[1][0] = sin(q); C[1][1] = cos(w)*cos(q); C[1][2] = -sin(w)*cos(q); C[1][3] = e*sin(q);
    C[2][0] = 0; C[2][1] = sin(w); C[2][2] = cos(w); C[2][3] = r;
    C[3][0] = 0; C[3][1] = 0; C[3][2] = 0; C[3][3] = 1;
    /*for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<4; j++)
        {                                      //òóò çàïîëíåíèå

            cout << C[i][j] << ' ';
        }
    } */
}
void Manipulator::solution() {
    if (B[0] == 0)
        matrix(A[0][0], A[0][1], A[0][2], coord[0]);
    else matrix(coord[0], A[0][0], A[0][1], A[0][2]);
    for (int h = 0; h < 4; h++)
        for (int x = 0; x < 4; x++)
            D[h][x] = C[h][x];                   //èíèöèàëèçàöèÿ
    for (int g = 1; g < n; g++) {
        if (B[g] == 0)
            matrix(A[g][0], A[g][1], A[g][2], coord[g]);
        else matrix(coord[g], A[g][0], A[g][1], A[g][2]);   //C=A

            for (int a = 0; a < 4; a++)
                for (int b = 0; b < 4; b++)
                {
                    E[a][b] = 0;
                    for (int v = 0; v < 4; v++)
                        E[a][b] += D[a][v] * C[v][b];
                }                                            //E=DC
            for (int as = 0; as < 4; as++)
                for (int qw = 0; qw < 4; qw++)
                    D[as][qw] = E[as][qw];     //D=E
    }
}







int main() {
    cout << "Vvedite kolichestvo zveniev: ";
    int n, p;                         //n-êîëè÷åñòâî çâåíüåâ, p-ïðîìåæóòî÷íàÿ ïåðåìåííàÿ äëÿ õðàíåíèÿ òèïà êèíåì.ïàðû
    n = 0;
    p = 0;
    cin >> n;                        //ââîäèì êîëè÷åñòâî çâåíüåâ
    Manipulator puma(n, 3);          //îáúåêò-ìàíèïóëÿòîð ñ ìàòðèöåé ïàðàìåòðîâ
                                     //int *inform=new int [n];     //ìàññèâ äëÿ õðàíåíèÿ òèïà êèíåìàòè÷åñêîé ïàðû
                                     //delete(n);
    for (int i = 0; i<n; i++) {
        //    cout << i;
        cout << "Tip kinematicheskoy pari(0-postupatel, 1-vrashatelnaya): ";
        cin >> p;
        //inform[i]=p;
        puma.B[i] = p;         //ñîçäàžì ìàññèâ ñ èíôîðìàöèåé
        if (puma.B[i] == 0) {          //åñëè ïîñòóïàòåëüíàÿ
            cout << "Vvedite q: ";
            cin >> puma.A[i][0];
            cout << "Vvedite alpha: ";
            cin >> puma.A[i][1];
            cout << "Vvedite a: ";
            cin >> puma.A[i][2];
            //puma.show();           //ïðîìåæóòî÷íûé âûâîä ìàòðèöû ñ ïàðàìåòðàìè
        }
        else {                   //åñëè âðàùàòåëüíàÿ
            cout << "Vvedite alpha: ";
            cin >> puma.A[i][0];
            cout << "Vvedite a: ";
            cin >> puma.A[i][1];
            cout << "Vvedite d: ";
            cin >> puma.A[i][2];
        //	puma.show();           //ïðîìåæóòî÷íûé âûâîä ìàòðèöû ñ ïàðàìåòðàìè
        }
    }
    cout << "Vvedite obobshenie coordinati:\n";
    for (int l = 0; l<n; l++) {
        if (puma.B[l] == 0) {
            cout << "Vvedite d" << l + 1 << " :";
            cin >> puma.coord[l];
        }
        else {
            cout << "Vvedite q" << l + 1 << " :";
            cin >> puma.coord[l];
        }
    }
    //for (int f = 0; f < n; f++)
        //cout << puma.B[0]<<"wqe";
    puma.solution();
    cout << "Pologeniya shvata:  ";
    cout << puma.E[0][3] << " " << puma.E[1][3] << " " << puma.E[2][3]<<"\n";

    return(0);
}


/*int main() {
    float s = sin(1)*sin(1);
    cout << s;
    return 0;
}*/
