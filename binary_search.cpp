#include <iostream>
#include <algorithm>
#include <vector>


int binarySearch(std::vector<int>::iterator start, std::vector<int>::iterator end, int target) {
    std::vector<int>::iterator middle;
    std::vector<int>::iterator low = start;
    std::vector<int>::iterator high = end;

    int step = 0;
    while (low <= high) {
        middle = low +(high - low) / 2;
        int value = *middle;
        std::cout << "Step " << step << " : " << value << std::endl;

        step++;
        if (value < target) {
            low = middle + 1;
        }
        else if (value > target) {
            high = middle - 1;
        }
        else 
            return value;

    }
    return -1;
}

int main(void) {
    std::vector<int>    test;
    int                 target = 15;
    for (size_t i = 0; i < 100000000000; ++i) {
        test.push_back(i);
    }


    // for(std::vector<int>::iterator it = test.begin(); it != test.end(); ++ it) { 
    //     std::cout << "i = " << *it << std::endl;
    // }

    if (binarySearch(test.begin(), test.end(), target) == -1) {
        std::cerr << target << " not found\n";
    }
    else {
        std::cout << target << " is found\n";
    }
    return 0;
}