#include "Dynamic_array.h"

Dynamic_array::Dynamic_array() {
    capacity = 1;
    array = new int[1];
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
    if (capacity < size) {
        increase_capacity();
    }
    // przesuwam elementy znajdujace sie po prawo od docelowej pozycji nowej wartosci nastepnie ja dodaje
    for (int i = size - 1; i > position; i--) {
        array[i] = array[i - 1];
    }
    array[position] = value;
}

auto Dynamic_array::add_front(int value) -> bool {
    size++;
    // sprawdzam czy ilosc zaalokowanej pamieci wystarczy jak nie zwiekszam ja 
    if (capacity < size) {
        increase_capacity();
    }
    // przesuwam wartosci o 1 w prawo
    for (int i = size - 1; i > 0; i--) {
        array[i] = array[i - 1];
    }
    // dodaje nowa wartosc na poczatek tablicy
    array[0] = value;
    return true;
}

auto Dynamic_array::add_back(int value) -> bool {
    size++;
    // to samo co wyzej
    if (capacity < size) {
        increase_capacity();
    }
    // dodaje nowa wartosc na koniec tablicy
    array[size - 1] = value; 
    
    return true;
}

auto Dynamic_array::remove_front() -> bool {

    return true;
}

auto Dynamic_array::remove_back() -> bool {
    
    return true;
}

auto Dynamic_array::remove_at(int position) -> bool {

    return true;
}

auto Dynamic_array::increase_capacity() -> void {
    int* new_array = new int[capacity * 2];
    for (int i = 0; i < capacity; i++) {
        new_array[i] = array[i];
    }
    capacity *= 2;
    delete[] array;
    array = new_array;
}

auto Dynamic_array::decrease_capacity() -> void {

}

auto Dynamic_array::print() {
    for (int i = 0; i < sizeof(array) / sizeof(int); i++)
    {
        std::cout << array[i] << " ";
    }
}

int main() {

    Dynamic_array da;
    da.add_front(321);
    da.print();

    return 0;
}