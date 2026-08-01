#define Vector DArray


#include <iostream>
#include "DS/BasicDS.h"

int main(){
    std::cout << "Normal arrays[] \n";
    std::cout << "CPP's array: \n";
    int* defArr = new int[5];
    defArr[0] = 1;
    defArr[1] = 2;
    defArr[2] = 3;
    defArr[3] = 4;
    defArr[4] = 5;

    for(int i = 0;i < 5;++i){
        std::cout << defArr[i] << std::endl;
    }

    std::cout << "My array: \n";

    MyDses::Array<int> myArr(5);
    myArr[0] = 1;
    myArr[1] = 2;
    myArr[2] = 3;
    myArr[3] = 4;
    myArr[4] = 5;

    for(size_t i = 0;i < myArr.size();++i){
        std::cout << myArr[i] << std::endl;    
    }

    std::cout << "First elem: " << myArr.first() << std::endl;
    std::cout << "Last elem: " << myArr.last() << std::endl;

    std::cout << "Dynamic arrays[] heap allocation \n";
    MyDses::Vector<int> myDArr(5);
    myDArr.add_back(1);
    myDArr.add_back(2);
    myDArr.add_back(3);
    myDArr.add_back(4);
    myDArr.add_back(5);

    for(size_t i = 0;i < myArr.size();++i){
        std::cout << myDArr[i] << std::endl;    
    }

    std::cout << "First elem: " << myDArr.first() << std::endl;
    std::cout << "Last elem: " << myDArr.last() << std::endl;
    std::cout << "Currently at the max \n";

    myDArr.add_back(6);

    for(size_t i = 0;i < myDArr.size();++i){
        std::cout << myDArr[i] << std::endl;    
    }

    std::cout << "Dynamicly allocated more space for 6 \n";


    return 0;
}