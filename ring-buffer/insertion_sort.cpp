#include <iostream>
#include <cstdlib>

void insertion_sort(uint16_t arr[], uint16_t length) {
    for(int step = 1; step < length; step++) {
        uint16_t key = arr[step]; 
        int j = step - 1; 
        while(j >= 0 && (key < arr[j])) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


void print_array(uint16_t arr[], uint16_t len) {
    for(uint16_t i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
} 

int main() {
    puts("Insertion sort test\r\n");
    uint16_t data[] = {9, 5, 1, 4, 3};
    uint16_t size = sizeof(data) / sizeof(data[0]);
    printf("%d\r\n", size);

    insertion_sort(data, size);

    printf("Sorted array in ascending order:\n");
    print_array(data, size);

    return 0;
}
