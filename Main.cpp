#include<iostream>
#include <vector>
class Matrix {
    public:
        std::vector<std::vector<int>> Weights;
        int Rows;
        int Collumns;
        void RandomNew(int RowsC, int CollumnsC) {
            Rows = RowsC;
            Collumns = CollumnsC;


            for (int i = 0; i< Collumns; i++) {
                std::vector<int> Collumn;
                for (int j = 0; j< Rows; j++) {
                    Collumn.push_back(std::rand());

                }
                Weights.push_back(Collumn);
          
            }
        }
        void SetWeights(std::vector<std::vector<int>> input) {
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
        }



};

int main(){
    Matrix Test;
    Test.RandomNew(4,5);
    Test.SetWeights(
        {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
        }
    );
    Test.PrintMatrix();



    return 0;
}