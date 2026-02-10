#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "header.h"


void BackRec4(int i,int weight,int volume, std::vector<int>& items){
    using namespace std;
    if (i==N){
        //входит ли в диапазон
        if (weight >= A && weight <= B){
            if (volume < min_volume){
                min_volume = volume;
                final_weight = weight;
                best_items = items;
            }
        }
        return;
    }
    //если подходит - берём
    if (weight + weights[i] <= B){
        items.push_back(i+1);
        BackRec4(i+1,weight+weights[i],volume+volumes[i],items);
        items.pop_back();
    }
    //не берём
    BackRec4(i+1,weight,volume,items);

}
int num1(){
    using namespace std;
    vector<int> current;
    ifstream inputFile("input.txt");

    if (!inputFile.is_open()){
        cout<<"File don't opened\n";
        return 1;
    }

    //считывание данных из файла
    inputFile>>N>>A>>B;
    weights.resize(N);
    volumes.resize(N);
    for (int i = 0; i<N;i++){
        inputFile>>weights[i];
    }
    for (int i = 0; i<N;i++){
        inputFile>>volumes[i];
    }

    BackRec4(0,0,0,current);

    //результат
    cout<<"The artifacts take\n";
    for (int i = 0; i<best_items.size();i++){
        cout<<best_items[i]<<"\n";
    }
    cout<<"Final weight: "<<final_weight<<"\nMinimum volume: "<<min_volume;

    return 0;
}

int num2(){
    using namespace std;
    int N;
    ifstream inputFile("input2.txt");
    ofstream outputFile("output2.txt");

    if (!inputFile.is_open()){
        cout<<"File don't opened\n";
        return 1;
    }

    inputFile>>N;
    vector<vector<int>> board(N, vector<int>(N));
    vector<vector<int>> turtle(N, vector<int>(N));

    //считываем доску
    for (int i = 0; i<N; i++){
        for (int j = 0; j<N; j++){
            inputFile>>board[i][j];
        }
    }
    turtle[0][N-1] = board[0][N-1];

    for (int i = 0; i<N; i++){
        for (int j = N-1; j>=0; j--){
            if (i==0 && j==N-1) continue;
            int from_bottom = (i>0) ? turtle[i-1][j] : -1;
            int from_left = (j<N-1) ? turtle[i][j+1] : -1;

            turtle[i][j] = board[i][j] + max(from_bottom,from_left);
        }
    }
    outputFile<<turtle[N-1][0];
    cout<<"Task is solved. The answer is in \"output2.txt\"";

    return 0;
}

int main(){
    using namespace std;
    cout<<"-----------------------\n";
    cout<<"|  Laboratory work #8 |\n";
    cout<<"-----------------------\n";
    cout<<"Tasks:\n1. BackRec4\n2. HomeDyn1\n";
    int number;
    cout<<"Input task number:\n";
    cin>>number;
    cout<<"\n";
    switch (number) {
        case 1:
            num1();
            break;
        case 2:
            num2();
            break;
    }

}