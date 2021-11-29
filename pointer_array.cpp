#include <iostream>

int* oneD_array_with_pointer(int n){
    int *array_pointer ;
    array_pointer = (int*) malloc(sizeof(int)*n);
    for (int i = 0 ; i < n ; i++ ){
        *(array_pointer+i) = i ;
    }
    return array_pointer ;
}

int** twoD_array_with_pointer(int m,int n){
    int **array_pointer_pointer ;
    array_pointer_pointer = (int**) malloc(sizeof(int*)*m) ;
    for(int i = 0 ; i < m ; i++ ) {
        *(array_pointer_pointer+i) = (int*) malloc(sizeof(int)*n);
        for(int j = 0 ; j < n ; j++) {
            *(*(array_pointer_pointer+i)+j) = (n*i+j) ;
        }
    }
    return array_pointer_pointer ;
}

int main() {
    // int n , *array_pointer ;
    // std::cin >> n ;
    // array_pointer = oneD_array_with_pointer(n) ;
    // for(int i = 0 ; i < n ; i++) {
    //     std::cout << " ||"  << array_pointer+i << " | " <<  *(array_pointer+i) << " || --> " ;
    // }

    int n , m ;
    std::cin >> m >> n ;
    int** arr_pointer_pointer = twoD_array_with_pointer(m,n);
    for(int i = 0 ; i < m ; i++) {
        for(int j = 0 ; j < n ; j++) {
            std::cout << " || " << arr_pointer_pointer+i << " | " <<  *(arr_pointer_pointer+i) << " | " <<  (*(arr_pointer_pointer+i)+j) << " | " <<  *(*(arr_pointer_pointer+i)+j) << " || -->";
        }
    }

    return 0 ;
}