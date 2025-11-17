#include <iostream>
#include <cstdlib>

uint16_t array[6] = {8,9,2,4,7,1};

void insertion_sort(uint16_t arr[], uint16_t length) {

    for(int step = 1; step < length; step++) {
        uint16_t key = arr[step]; 
        uint16_t j = step - 1; 

        while(j >= 0 && (key < arr[j])) {
            arr[j + 1] = arr[j];
        }


    }

}

int main() {

}