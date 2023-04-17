//
// Generujemy dane, mierzymy czas
//

#include "Main.h"

#define ARR_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\arr_data.txt"
#define ARR_CSV "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\array.csv"
#define LIST_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\list_data.txt"
#define LIST_CSV "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\list.csv"
#define HEAP_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\heap_data.txt"
#define HEAP_CSV "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\heap.csv"
#define BST_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\bst_data.txt"
#define BST_CSV "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\bst.csv"

using namespace std;

double pc_freq = 0.0;
__int64 counter_start = 0;

void start_counter() {
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    pc_freq = double(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    counter_start = li.QuadPart;
}
double get_counter() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - counter_start) / pc_freq;
}

int rand_int() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);
    return dist(gen);
}


// generowanie losowych danych do pliku
bool generate_random_data(string file_name, int size_obj) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100000);
    ofstream file(file_name);
    if (file.eof()) {
        cout << "Data file is empty!" << endl;
        return false;
    }
    if (file.is_open()) {
        file << size_obj << endl;
        int rand_num;
        for (int j = 0; j < size_obj; j++) {
            rand_num = dist(gen);
            file << rand_num << " ";
        }
        file << endl << EOF;
        file.close();
        return true;
    } else {
        cout << "Could not open data file!" << endl;
        return false;
    }
}

// przetwarzanie danych z pliku
DynamicArray* parse_data_to_arr(string file_name) {
    ifstream file(file_name);
    auto da = new DynamicArray();
    if (file.is_open()) {
        int size_obj;
        file >> size_obj;
        for (int i = 0; i < size_obj; i++) {
            int input;
            if (!(file >> input)) {
                cout << "Parsing data was not completed!" << endl;
            }
            da->add_back(input);
        }
        return da;
    } else {
        cout << "Parsing data was not completed!" << endl;
        return nullptr;
    }
}

DoublyLinkedList* parse_data_to_list(string file_name) {
    ifstream file(file_name);
    auto dl = new DoublyLinkedList();
    if (file.is_open()) {
        int size_obj;
        file >> size_obj;
        for (int i = 0; i < size_obj; i++) {
            int input;
            if (!(file >> input)) {
                cout << "Parsing data was not completed!" << endl;
            }
            dl->add_back(input);
        }
        return dl;
    } else {
        cout << "Parsing data was not completed!" << endl;
        return nullptr;
    }

}

BinaryHeap* parse_data_to_heap(string file_name) {
    ifstream file(file_name);
    if (file.is_open()) {
        int size_obj;
        file >> size_obj;
        auto bh = new BinaryHeap(size_obj + 500);
        for (int i = 0; i < size_obj; i++) {
            int input;
            if (!(file >> input)) {
                cout << "Parsing data was not completed!" << endl;
            }
            bh->add(input);
        }
        return bh;
    } else {
        cout << "Parsing data was not completed!" << endl;
        return nullptr;
    }
}

BST* parse_data_to_bst(string file_name) {
    ifstream file(file_name);
    if (file.is_open()) {
        int size_obj, root_value;
        file >> size_obj;
        file >> root_value;
        auto root = new TreeNode(root_value, nullptr, nullptr, nullptr);
        auto bst = new BST(root);
        for (int i = 0; i < size_obj - 1; i++) {
            int input;
            if (!(file >> input)) {
                cout << "Parsing data was not completed!" << endl;
            }
            bst->add(input);
        }
        return bst;
    } else {
        cout << "Parsing data was not completed!" << endl;
        return nullptr;
    }
}

void test_array(int num_of_test_cases, int arr_size, int precision, double unit) {
    double add_front_time = 0;
    double add_back_time = 0;
    double add_at_time = 0;
    double remove_front_time = 0;
    double remove_back_time = 0;
    double remove_at_time = 0;

    for (int i = 0; i < num_of_test_cases; i++) {
        if (generate_random_data(ARR_DATA_FILE, arr_size)) {
            auto da = parse_data_to_arr(ARR_DATA_FILE);
            if (da != nullptr) {
                cout << "Starting to measure time... (" << i << ")" << endl;
                start_counter();
                da->add_front(i);
                add_front_time += get_counter();

                start_counter();
                da->add_back(i);
                add_back_time += get_counter();

                start_counter();
                da->add_at(i ,da->get_size() / 2);
                add_at_time += get_counter();

                start_counter();
                da->remove_front();
                remove_front_time += get_counter();

                start_counter();
                da->remove_back();
                remove_back_time += get_counter();

                start_counter();
                da->remove_at(da->get_size() / 2);
                remove_at_time += get_counter();
            }
        }
    }
    cout << setprecision(precision)
        << "Tablica Dynamiczna (ms) (Rozmiar: " << arr_size << ")" << endl
        << "Dodawanie na poczatek --> " << (add_front_time / num_of_test_cases) * unit << endl
        << "Dodawanie na koniec --> " << (add_back_time / num_of_test_cases) * unit << endl
        << "Dodawanie na pozycje --> " << (add_at_time / num_of_test_cases) * unit << endl
        << "Usuwanie z poczatku --> " << (remove_front_time / num_of_test_cases) * unit << endl
        << "Usuwanie z konca --> " << (remove_back_time / num_of_test_cases) * unit << endl
        << "Usuwanie z pozycji --> " << (remove_at_time / num_of_test_cases) * unit << endl << endl;

    // dodawanie czasow do pliku csv do sprawozdania
    ofstream csv_file(ARR_CSV, ios::app | ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(6)
            << arr_size << ";"
            << (add_front_time / num_of_test_cases) * unit << ";"
            << (add_back_time / num_of_test_cases) * unit << ";"
            << (add_at_time / num_of_test_cases) * unit << ";"
            << (remove_front_time / num_of_test_cases) * unit << ";"
            << (remove_back_time / num_of_test_cases) * unit << ";"
            << (remove_at_time / num_of_test_cases) * unit << endl;
        csv_file.close();
    }


}

void test_list(int num_of_test_cases, int list_size, int precision, double unit) {
    double add_front_time = 0;
    double add_back_time = 0;
    double add_at_time = 0;
    double remove_front_time = 0;
    double remove_back_time = 0;
    double remove_at_time = 0;
    double find_time = 0;

    for (int i = 0; i < num_of_test_cases; i++) {
        if (generate_random_data(LIST_DATA_FILE, list_size)) {
            auto dl = parse_data_to_list(LIST_DATA_FILE);
            if (dl != nullptr) {
                cout << "Starting to measure time... (" << i << ")" << endl;
                start_counter();
                dl->add_front(i);
                add_front_time += get_counter();

                start_counter();
                dl->add_back(i);
                add_back_time += get_counter();

                start_counter();
                dl->add_at(i, dl->get_size() / 2);
                add_at_time += get_counter();

                start_counter();
                dl->remove_front();
                remove_front_time += get_counter();

                start_counter();
                dl->remove_back();
                remove_back_time += get_counter();

                start_counter();
                dl->remove_at(dl->get_size() / 2);
                remove_at_time += get_counter();

                start_counter();
                dl->find(dl->get_size() / 2);
                find_time += get_counter();
            }
        }
    }
    cout << setprecision(precision)
        << "Lista dwukierunkowa (ms) (Rozmiar: " << list_size << ")" << endl
        << "Dodawanie na poczatek --> " << (add_front_time / num_of_test_cases) * unit << endl
        << "Dodawanie na koniec --> " << (add_back_time / num_of_test_cases) * unit << endl
        << "Dodawanie na pozycje --> " << (add_at_time / num_of_test_cases) * unit << endl
        << "Usuwanie z poczatku --> " << (remove_front_time / num_of_test_cases) * unit << endl
        << "Usuwanie z konca --> " << (remove_back_time / num_of_test_cases) * unit << endl
        << "Usuwanie z pozycji --> " << (remove_at_time / num_of_test_cases) * unit << endl
        << "Wyszukiwanie --> " << (find_time / num_of_test_cases) * unit << endl << endl;

    ofstream csv_file(LIST_CSV, ios::app|ios::out);
    if (csv_file.is_open()) {
        csv_file << list_size << ";";
        csv_file << setprecision(precision) << (add_front_time / num_of_test_cases) * unit << ";"
            << (add_front_time / num_of_test_cases) * unit << ";"
            << (add_back_time / num_of_test_cases) * unit << ";"
            << (add_at_time / num_of_test_cases) * unit << ";"
            << (remove_front_time / num_of_test_cases) * unit << ";"
            << (remove_back_time / num_of_test_cases) * unit << ";"
            << (remove_at_time / num_of_test_cases) * unit << ";"
            << (find_time / num_of_test_cases) * unit << endl;
        csv_file.close();
    }
}

void test_heap(int num_of_test_cases, int heap_size, int precision, double unit) {
    double add_time = 0;
    double remove_top_time = 0;
    double find_time = 0;

    for (int i = 0; i < num_of_test_cases; i++) {
        if (generate_random_data(HEAP_DATA_FILE, heap_size)) {
            auto bh = parse_data_to_heap(HEAP_DATA_FILE);
            if (bh != nullptr) {
                cout << "Starting to measure time... (" << i << ")" << endl;

                int random_input = rand_int();
                start_counter();
                bh->add(random_input);
                add_time += get_counter();

                start_counter();
                bh->find(random_input);
                find_time += get_counter();

                start_counter();
                bh->remove_top();
                remove_top_time += get_counter();
            }
        }
    }
    cout << setprecision(precision)
        << "Maksymalny kopiec binarny (ms) (Rozmiar: " << heap_size << ")" << endl
        << "Dodawanie --> " << (add_time / num_of_test_cases) * unit << endl
        << "Wyszukiwanie --> " << (find_time / num_of_test_cases) * unit << endl
        << "Usuwanie z gory --> " << (remove_top_time / num_of_test_cases) * unit << endl << endl;

    ofstream csv_file(HEAP_CSV, ios::app|ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(6)
            << heap_size << ";"
            << (add_time / num_of_test_cases) * unit << ";"
            << (find_time / num_of_test_cases) * unit << ";"
            << (add_time / num_of_test_cases) * unit << endl;
        csv_file.close();
    }
}

void test_bst(int num_of_test_cases, int bst_size, int precision, double unit) {
    double add_time = 0;
    double remove_time = 0;
    double dsw_time = 0;
    double find_time = 0;
    double rotation_time = 0;

    for (int i = 0; i < num_of_test_cases; i++) {
        if (generate_random_data(BST_DATA_FILE, bst_size)) {
            auto bst = parse_data_to_bst(BST_DATA_FILE);
            if (bst != nullptr) {
                cout << "Starting to measure time... (" << i << ")" << endl;

                int random_input = rand_int();
                start_counter();
                bst->add(random_input);
                add_time += get_counter();

                start_counter();
                auto node = bst->find_BST(random_input);
                find_time += get_counter();

                start_counter();
                bst->rotate_left(node);
                rotation_time += get_counter();

                start_counter();
                bst->balance_tree_DSW();
                dsw_time += get_counter();

                start_counter();
                bst->remove(random_input);
                remove_time += get_counter();
            }
            delete bst;
        }
    }

    cout << setprecision(precision)
        << "BST (ms) (Rozmiar: " << bst_size << ")" << endl
        << "Dodawanie --> " << (add_time / num_of_test_cases) * unit << endl
        << "Wyszukiwanie --> " << (find_time / num_of_test_cases) * unit << endl
        << "DSW --> " << (dsw_time / num_of_test_cases) * unit << endl
        << "Usuwanie --> " << (remove_time / num_of_test_cases) * unit << endl
        << "Rotacja --> " << (rotation_time / num_of_test_cases) * unit << endl << endl;

    // dodawanie czasow do pliku csv do sprawozdania
    ofstream csv_file(BST_CSV, ios::app | ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(precision)
            << bst_size << ";"
            << (add_time / num_of_test_cases) * unit << ";"
            << (find_time / num_of_test_cases) * unit << ";"
            << (dsw_time / num_of_test_cases) * unit << ";"
            << (remove_time / num_of_test_cases) * unit << ";"
            << (rotation_time / num_of_test_cases) * unit << endl;
        csv_file.close();
    }
}

int get_value_from_user() {
    int value;
    bool correct_value = false;
    cout << "...Podaj wartosc..." << endl;
    cin >> value;
    while (!correct_value) {
        if (value < 0 || value > 1000000)  {
            cout << "Podana wartosc jest nieprawidlowa! Sprobuj jeszcze raz. (Musi byc intem)" << endl;
        } else correct_value = true;
    }
    return value;
}

void arr_menu() {
    int menu_choice;
    bool run_menu = true;
    int value, position, arr_size;

    cout << "Podaj rozmiar tablicy:" << endl;
    arr_size = get_value_from_user();
    auto da = new DynamicArray(arr_size);

    while (run_menu) {
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Przed" << endl;
        da->print();
        cout << "-------------------------------------------------------" << endl;
        cout << "0 - Zakoncz, 1 - Dodaj elem na poczatek, 2 - Dodaj elem na koniec" << endl
            << "3 - Dodaj elem na pozycje, 4 - Usun z poczatku, 5 - Usun z konca" << endl
            << "6 - Usun z pozycji" << endl;
        cin >> menu_choice;

        switch (menu_choice) {
            case 0:
                run_menu = false;
                break;
            case 1:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                da->add_front(value);
                break;
            case 2:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                da->add_back(value);
                break;
            case 3:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                cout << "Pozycja:" << endl;
                position = get_value_from_user();
                da->add_at(value, position);
                break;
            case 4:
                da->remove_front();
                break;
            case 5:
                da->remove_back();
                break;
            case 6:
                cout << "Pozycja:" << endl;
                position = get_value_from_user();
                da->remove_at(position);
                break;
            default:
                cout << "Nieprawidlowy numer, sprobuj jeszcze raz.";

        }
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Po" << endl;
        da->print();
        cout << "-------------------------------------------------------" << endl;
    }

}

void list_menu() {
    int menu_choice;
    bool run_menu = true;
    auto dl = new DoublyLinkedList();
    Node* node;
    int value, position;

    while (run_menu) {
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Przed" << endl;
        dl->print();
        cout << "-------------------------------------------------------" << endl;
        cout << "0 - Zakoncz, 1 - Dodaj elem na poczatek, 2 - Dodaj elem na koniec" << endl
             << "3 - Dodaj elem na pozycje, 4 - Usun z poczatku, 5 - Usun z konca" << endl
             << "6 - Usun z pozycji, 7 - Wyszukaj" << endl;
        cin >> menu_choice;

        switch (menu_choice) {
            case 0:
                run_menu = false;
                break;
            case 1:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                dl->add_front(value);
                break;
            case 2:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                dl->add_back(value);
                break;
            case 3:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                cout << "Pozycja:" << endl;
                position = get_value_from_user();
                dl->add_at(value, position);
                break;
            case 4:
                dl->remove_front();
                break;
            case 5:
                dl->remove_back();
                break;
            case 6:
                cout << "Pozycja:" << endl;
                position = get_value_from_user();
                dl->remove_at(position);
                break;
            case 7:
                cout << "Pozycja:" << endl;
                position = get_value_from_user();
                node = dl->find(position);
                if (node != nullptr)
                    cout << "Znaleziono --> " << node->value << endl;
                else cout << "Nie znaleziono!" << endl;
            default:
                cout << "Nieprawidlowy numer, sprobuj jeszcze raz.";
        }
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Po" << endl;
        dl->print();
        cout << "-------------------------------------------------------" << endl;
    }

}

void heap_menu() {
    int menu_choice;
    bool run_menu = true;
    int value, position, heap_size;


    cout << "Podaj rozmiar kopca:" << endl;
    heap_size = get_value_from_user();
    auto bh = new BinaryHeap(heap_size);

    while (run_menu) {
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Przed" << endl;
        bh->print();
        cout << "-------------------------------------------------------" << endl;
        cout << "0 - Zakoncz, 1 - Dodaj elem, 2 - Usun z gory" << endl;
        cin >> menu_choice;

        switch (menu_choice) {
            case 0:
                run_menu = false;
                break;
            case 1:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                bh->add(value);
                break;
            case 2:
                bh->remove_top();
                break;
            default:
                cout << "Nieprawidlowy numer, sprobuj jeszcze raz.";
        }
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Po" << endl;
        bh->print();
        cout << "-------------------------------------------------------" << endl;
    }
}

void bst_menu() {
    int menu_choice;
    bool run_menu = true;
    auto bst = new BST();
    TreeNode* node;
    int value, position;

    while (run_menu) {
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Przed" << endl;
        bst->print_BST(bst->get_root());
        cout << "-------------------------------------------------------" << endl;
        cout << "0 - Zakoncz, 1 - Dodaj elem, 2 - Usun elem" << endl
             << "3 - Wyszukaj, 4 - Rotacja w lewo, 5 - Rotacja w prawo" << endl
             << "6 - DSW" << endl;
        cin >> menu_choice;

        switch (menu_choice) {
            case 0:
                run_menu = false;
                break;
            case 1:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                bst->add(value);
                break;
            case 2:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                bst->remove(value);
                break;
            case 3:
                cout << "Wartosc:" << endl;
                value = get_value_from_user();
                node = bst->find_BST(value);
                if (node != nullptr)
                    cout << "Znaleziono --> " << node->value << endl;
                else cout << "Nie znaleziono!" << endl;
                break;
            case 4:
                cout << "Klucz" << endl;
                value = get_value_from_user();
                node = bst->find_BST(value);
                if (node != nullptr)
                    bst->rotate_left(node);
                else cout << "Nie znaleziono takiego wezla!" << endl;
                break;
            case 5:
                cout << "Klucz" << endl;
                value = get_value_from_user();
                node = bst->find_BST(value);
                if (node != nullptr)
                    bst->rotate_right(node);
                else cout << "Nie znaleziono takiego wezla!" << endl;
                break;
            case 6:
                bst->balance_tree_DSW();
                break;
            default:
                cout << "Nieprawidlowy numer, sprobuj jeszcze raz.";
        }
        cout << endl << "-------------------------------------------------------" << endl;
        cout << "Po" << endl;
        bst->print_BST(bst->get_root());
        cout << endl << "-------------------------------------------------------" << endl;
    }
}

void menu() {
    int menu_choice;
    bool run_menu = true;

    while (run_menu) {
        cout << "0 - zakoncz, 1 - Tablica, 2 - Lista, 3 - Kopiec, 4 - BST" << endl;
        cin >> menu_choice;
        switch (menu_choice) {
            case 0:
                run_menu = false;
                break;
            case 1:
                arr_menu();
                break;
            case 2:
                list_menu();
                break;
            case 3:
                heap_menu();
                break;
            case 4:
                bst_menu();
                break;
            default:
                cout << "Nieprawidlowy numer, sprobuj jeszcze raz.";
        }
    }
}

void run_tests() {
    int diff = 10;
    int struct_size = 5000;
    int number_of_testcases = 100;
    int precision = 6;
    double unit = 1000.0;
    for (int i = 1; i <= diff; i++) {
        test_array(number_of_testcases,  struct_size * i, precision, unit);
        test_list(number_of_testcases,struct_size * i, precision, unit);
        test_heap(number_of_testcases, struct_size * i, precision, unit);
        test_bst(number_of_testcases, struct_size * i, precision, unit);
    }
}

// W CELU URUCHOMIENIA TESTOW NALEZY ODKOMENTOWAC run_tests()
int main() {
    run_tests();
    menu();
}
