#include<iostream>
#include <vector>
#include <cmath>
#include <windows.h>

float testfunction(float x) {
        float val = 5;
        return val *sin(x);
}
class Matrix {
    public:
        float rate = 0.3f;
        float strength = 0.5f;
        std::vector<std::vector<float>> Weights;
        int Rows;
        int Collumns;
        void RandomNew(int RowsC, int CollumnsC) {
            Rows = RowsC;
            Collumns = CollumnsC;


            for (int i = 0; i< Collumns; i++) {
                std::vector<float> Collumn;
                for (int j = 0; j< Rows; j++) {
                    //Collumn.push_back(std::rand());
                    Collumn.push_back(((float)std::rand() / RAND_MAX - 0.5f) * 2.0f);

                }
                Weights.push_back(Collumn);
          
            }
        }
        void SetWeights(std::vector<std::vector<float>> input) {
            Weights = input;
            Collumns = Weights.size();
            Rows = Weights[0].size();
        }
        void PrintMatrix() {
             for (int i =0; i< Collumns; i++) {
                for (int j = 0; j< Rows; j++) {
                    std:: cout << Weights[i][j] << " ";
                }
                //std::cout << std::endl;
          
            }
            //std::cout << std::endl;
        }
        void Transform(Matrix T){
            
            if (T.Rows == Collumns){

                std::vector<std::vector<float>> Product(T.Collumns,std::vector<float>(Rows,0));
                //std::cout<< "bruh?";
                int Operations = Rows;
                //std::cout << Rows<< std::endl;
                //std::cout << T.Collumns << std::endl;
                for (int rowT = 0; rowT < Rows; rowT++) {
                    for (int ColW = 0; ColW < T.Collumns; ColW++) {
                        float result = 0;
                        for (int Comp = 0; Comp < Collumns; Comp++) {

                            float num1 =  T.Weights[ColW][Comp];
                            float num2 = Weights[Comp][rowT];
                            result += num1 * num2;
                            //std::cout << num1 << " ";
                            //std::cout << num2 << std::endl;
                            //std::cout<< result << std::endl;
                        }
                        
                        Product[ColW][rowT] = result;
                        //std:: cout << rowT << "," << ColW << std::endl;
                       // std::cout<< Product[rowT][ColW] << std::endl;
                    }
                }
              
                Weights = Product;
                Weights = Product;
                Collumns = T.Collumns;

            } 
            else {
                std::cout << "Cant be multiplied";

            }

        }
        void Mutate() {
            for (int i =0; i< Collumns; i++) {
                for (int j = 0; j< Rows; j++) {
                    if ((float)std::rand() / RAND_MAX < rate) {
                        float noise = ((float)std::rand() / RAND_MAX - 0.5f) * 2 * strength;
                        Weights[i][j] += noise;
                    }
                }
          
            }

        }
        void ActivationF(){
            for (int i =0; i< Collumns; i++) {
                for (int j = 0; j< Rows; j++) {
                    Weights[i][j] = std::tanh(Weights[i][j]);
                }
            }
        }
};
class NeuralNet {
    public:
    int Population;
    Matrix L1,L2,L3;
    std::vector<Matrix> Net;
    void Make() {
        L1.RandomNew(1,16);
        L2.RandomNew(16,16);
        L3.RandomNew(16,1);
    }
    float Query(float x) {
        Matrix Input;
        //std::cout << "PPPPPP" << std::endl;
        Input.SetWeights({{x}});
        //Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
        Input.Transform(L1);
        Input.ActivationF();
        //Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
        Input.Transform(L2);
        Input.ActivationF();
       // Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
        Input.Transform(L3);
        //Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
         return Input.Weights[0][0];

    }
    void Mutate() {
        L1.Mutate();
        L2.Mutate();
        L3.Mutate();
    }
    NeuralNet clone(NeuralNet body) {
        NeuralNet New;
        New.Make();
        New.L1.Weights = body.L1.Weights;
        New.L2.Weights = body.L2.Weights;
        New.L3.Weights = body.L3.Weights;
        return New;
    }
    int TestOnIntereval(int start) {
        float totaltdif = 0;
        for (int j = 0; j< 15;j++) {
            int x = start + j;
            float correct = testfunction(x);
            float result = Query(x);
            float difference = correct - result;
            if (difference < 0) {
                difference *= -1;
            }
            totaltdif += difference;
        }
        return totaltdif;
    }
};
class Population {

    public:
    int Size = 100;
    std::vector<NeuralNet> Pop;
    void Create() {
        for (int i =0; i< Size; i++) {
            NeuralNet Person;
            Person.Make();
            Pop.push_back(Person);
        }

    }
    int TestOnIntereval(float start) {
        int best = 0;
        float bestdif =-1;
        for (int i =0; i< Size; i++) {
            NeuralNet Person = Pop[i];
            float totaltdif = 0;
            for (int j = 0; j< 160; j++) {
                float x = start + j * 0.1f;
                float correct = testfunction(x);
                float result = Person.Query(x);
                float difference = correct - result;
                if (difference < 0) {
                    difference *= -1;
                }
                totaltdif += difference;

            }
            if (bestdif == -1 || bestdif > totaltdif) {
                bestdif = totaltdif;
                best = i;
            }
        }
        return best;
    }
    void Life(int best) {
        NeuralNet Person = Pop[best];
        std::vector<NeuralNet> NewPop;
        NeuralNet New;
        New = New.clone(Person);
        NewPop.push_back(New);    
        for (int i =1; i< Size; i++) {
            NeuralNet New;
            New = New.clone(Person);
            New.Mutate();
            NewPop.push_back(New);
            
        }
        Pop = NewPop;
    }


};

class Display {
    public:
    int l = 20;
    int w = 80;
    std::vector<std::vector<char>> Screen;
    
    void Start() {
        for (int i = -l; i < l; i++) {
            std::vector<char> layer;
            for (int j = -w; j < w; j++) layer.push_back(' ');
            Screen.push_back(layer);
        }
    }
    void Clear() {
        for (int i = 0; i < (int)Screen.size(); i++)
            for (int j = 0; j < (int)Screen[i].size(); j++)
                Screen[i][j] = ' ';
    }
    void Refresh() {
        COORD coord = {0, 0};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        for (int i = -l; i < l; i++) {
            for (int j = -w; j < w; j++)
                std::cout << Screen[i+l][j+w];
            std::cout << "\n";
        }
        std::cout.flush();
    }
    void DrawTest() {
        float yscale = l / 5.0f;
        for (int i = -w; i < w; i++) {
            int result = static_cast<int>(testfunction(i / 10.0f) * yscale);
            if (result > -l && result < l)
                Screen[l - result][i + w] = '#';
        }
    }
    void DrawNet(NeuralNet& net) {
        float yscale = l / 5.0f;
        for (int i = -w; i < w; i++) {
            float x = i / 10.0f;
            int result = static_cast<int>(net.Query(x) * yscale);
            if (result > -l && result < l)
                Screen[l - result][i + w] = '*';
        }
    }
};


int main(){

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    Population Pro;
    Pro.Create();
    Display Graph;
    Graph.Start();
    for (int i=0; i< 10000; i++) {
        int best = Pro.TestOnIntereval(-8.0f);
        //std::cout << Point << std::endl;
        //std::cout << best << std::endl;
        Graph.Clear();
        Graph.DrawTest();               
        Graph.DrawNet(Pro.Pop[best]);   
        Graph.Refresh();
        Pro.Life(best);
    }
   


    return 0;
}