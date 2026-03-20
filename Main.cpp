#include<iostream>
#include <vector>
class Matrix {
    public:
        std::vector<std::vector<float>> Weights;
        int Rows;
        int Collumns;
        void RandomNew(int RowsC, int CollumnsC) {
            Rows = RowsC;
            Collumns = CollumnsC;


            for (int i = 0; i< Collumns; i++) {
                std::vector<float> Collumn;
                for (int j = 0; j< Rows; j++) {
                    Collumn.push_back(std::rand());

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
        //Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
        Input.Transform(L2);
       // Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
        Input.Transform(L3);
        //Input.PrintMatrix();
         //std::cout << "PPPPPP" << std::endl;
         return Input.Weights[0][0];

    }
};

int main(){
    NeuralNet Pro;
    Pro.Make();
    float result = Pro.Query(1);
    std::cout<< std::endl <<result;
    result = Pro.Query(1);
    std::cout<< std::endl <<result;


    return 0;
}