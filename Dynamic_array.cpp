#include "Dynamic_array.h"

Dynamic_array::Dynamic_array() {
    capacity = 1;
    array = new int[capacity];
    size = 0;
}

Dynamic_array::~Dynamic_array() {
    delete[] array;
}

auto Dynamic_array::add_at(int value, int position) -> bool {
    //sprawdzam czy podana przez uzytkownika pozycja znajduje sie w zakresie tablicy
    if (position < 0 || position > size) {
        std::cerr << "Podana pozycja znajduje sie poza zakresem tablicy [0-" << size << "]"; 
        return false;
    }
    size++;
    // sprawdzam czy ilosc zaalokowanej pamieci wystarczy jak nie zwiekszam ja 
    increase_capacity();
    // przesuwam elementy znajdujace sie po prawo od docelowej pozycji nowej wartosci nastepnie ja dodaje
    for (int i = size - 1; i > position; i--) {
        array[i] = array[i - 1];
    }
    array[position] = value;

    return true;
}

auto Dynamic_array::add_front(int value) -> bool {
    // sprawdzam czy ilosc zaalokowanej pamieci wystarczy jak nie zwiekszam ja
    increase_capacity();
    //std::cout << sizeof(array) / sizeof(int) << std::endl;
    // przesuwam wartosci o 1 w prawo
    for (int i = size - 1; i > 0; i--) {
        array[i] = array[i - 1];
    }
    // dodaje nowa wartosc na poczatek tablicy
    array[0] = value;
    size++;
    return true;
}

auto Dynamic_array::add_back(int value) -> bool {
    // to samo co wyzej
    increase_capacity();
    // dodaje nowa wartosc na koniec tablicy
    array[size - 1] = value;
    size++;
    return true;
}

auto Dynamic_array::remove_front() -> bool {
    // przesuwamy elementy w lewo usuwajac/nadpisujac wartosc na poczatku 
    for (int i = 0; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    size--;
    //sprawdzamy czy mozna zredukowac zajmowana przez tablice pamiec
    decrease_capacity();
    return true;
}

auto Dynamic_array::remove_back() -> bool {
    array[size - 1] = 0;
    size--;
    decrease_capacity();
    return true;
}

auto Dynamic_array::remove_at(int position) -> bool {
    if (position < 0 || position > size) {
        std::cerr << "Podana pozycja znajduje sie poza zakresem tablicy [0-" << size << "]";
        return false;
    }
    // nadpisuje element na danej pozycji i przesuwajac reszte arrayu w lewo
    for (int i = position; i < size; i++) {
        if (i == size - 1) {
            array[i] = 0;
        } else {
            array[i] = array[i + 1];
        }
    }
    size--;
    decrease_capacity();
    return true;
}

// funkcja zwiekszajaca zaalokowana pamiec
auto Dynamic_array::increase_capacity() -> void {
    if (capacity == size) {
        int* new_array = new int[capacity * CAP_GROW];
        for (int i = 0; i < capacity; i++) {
            new_array[i] = array[i];
        }
        capacity *= CAP_GROW;
        delete[] array;
        array = new_array;
    }
}

// funkcja zmniejszajaca zaalokowana pamiec
auto Dynamic_array::decrease_capacity() -> void {
    if (size <= capacity / CAP_GROW) {
        capacity = size;
        int* new_array = new int[capacity];
        for (int i = 0; i < size; i++) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }
}

auto Dynamic_array::print() {
    for (int i = 0; i < capacity; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

//int main() {
//
//    Dynamic_array da;
//    std::cout << "Dodawanie na poczatek:" << std::endl;
//    for (int i = 0; i < 32; i++) {
//        da.add_front(i);
//        da.print();
//    }
//
//    std::cout << "Dodawanie na pozycje:" << std::endl;
//    da.add_at(124, 5);
//    da.print();
//
//    std::cout << "Usuwanie z pozycji:" << std::endl;
//    da.remove_at(5);
//    da.print();
//
//    std::cout << "Dodawanie na koniec:" << std::endl;
//    for (int i = 0; i < 32; i++) {
//        da.add_back(i);
//        da.print();
//    }
//    std::cout << "Usuwanie z konca:" << std::endl;
//    for (int i = 0; i < 32; i++) {
//        da.remove_back();
//        da.print();
//    }
//    std::cout << "Usuwanie z poczatku:" << std::endl;
//    for (int i = 0; i < 32; i++) {
//        da.remove_front();
//        da.print();
//    }
//
//    return 0;
//}