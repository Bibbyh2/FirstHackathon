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
                std::cout << std::endl;
          
            }
            std::cout << std::endl;
        }
        void Transform(Matrix T){
            
            if (T.Collumns == Rows){

                std::vector<std::vector<float>> Product(T.Collumns,std::vector<float>(Rows,0));
                std::cout<< "bruh?";
                int Operations = Rows;
                std::cout << Rows<< std::endl;
                std::cout << T.Collumns << std::endl;
                for (int rowT = 0; rowT < Rows; rowT++) {
                    for (int ColW = 0; ColW < T.Collumns; ColW++) {
                        float result = 0;
                        for (int Comp = 0; Comp < Collumns; Comp++) {

                            float num1 =  T.Weights[rowT][Comp];
                            float num2 = Weights[Comp][ColW];
                            result += num1 * num2;
                            std::cout << num1 << " ";
                            std::cout << num2 << std::endl;
                            //std::cout<< result << std::endl;
                        }
                        
                        Product[rowT][ColW] = result;
                        std:: cout << rowT << "," << ColW << std::endl;
                        std::cout<< Product[rowT][ColW] << std::endl;
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

int main(){
    Matrix Test;
    Test.SetWeights(
        {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
        }
    );
    Matrix Transform;
    Transform.SetWeights(
        {
        {5,6,7},
        {3,4,2},
        {1,0,3},
        {6,7,8}
        }

    );
    Test.PrintMatrix();
    Transform.PrintMatrix();
    Test.Transform(Transform);
    Test.PrintMatrix();



    return 0;
}