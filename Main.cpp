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

void test_array(int num_of_test_cases, int arr_size) {
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
    cout << setprecision(3)
        << "Tablica Dynamiczna (ms):" << endl
        << "Dodawanie na poczatek --> " << (add_front_time / num_of_test_cases) * 1000.0 << endl
        << "Dodawanie na koniec --> " << (add_back_time / num_of_test_cases) * 1000.0 << endl
        << "Dodawanie na pozycje --> " << (add_at_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z poczatku --> " << (remove_front_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z konca --> " << (remove_back_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z pozycji --> " << (remove_at_time / num_of_test_cases) * 1000.0 << endl << endl;

    // dodawanie czasow do pliku csv do sprawozdania
    ofstream csv_file(ARR_CSV, ios::app | ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(3)
            << arr_size << ";"
            << (add_front_time / num_of_test_cases) * 1000.0 << ";"
            << (add_back_time / num_of_test_cases) * 1000.0 << ";"
            << (add_at_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_front_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_back_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_at_time / num_of_test_cases) * 1000.0 << ";" << endl;
        csv_file.close();
    }


}

void test_list(int num_of_test_cases, int list_size) {
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
    cout << setprecision(3)
        << "Lista dwukierunkowa (ms):" << endl
        << "Dodawanie na poczatek --> " << (add_front_time / num_of_test_cases) * 1000.0 << endl
        << "Dodawanie na koniec --> " << (add_back_time / num_of_test_cases) * 1000.0 << endl
        << "Dodawanie na pozycje --> " << (add_at_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z poczatku --> " << (remove_front_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z konca --> " << (remove_back_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z pozycji --> " << (remove_at_time / num_of_test_cases) * 1000.0 << endl
        << "Wyszukiwanie --> " << (find_time / num_of_test_cases) * 1000.0 << endl << endl;

    ofstream csv_file(LIST_CSV, ios::app|ios::out);
    if (csv_file.is_open()) {
        csv_file << list_size << ";";
        csv_file << setprecision(3) << (add_front_time / num_of_test_cases) * 1000.0 << ";"
            << (add_front_time / num_of_test_cases) * 1000.0 << ";"
            << (add_back_time / num_of_test_cases) * 1000.0 << ";"
            << (add_at_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_front_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_back_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_at_time / num_of_test_cases) * 1000.0 << ";"
            << (find_time / num_of_test_cases) * 1000.0 << ";" << endl;
        csv_file.close();
    }
}

void test_heap(int num_of_test_cases, int heap_size) {
    double add_time = 0;
    double remove_top_time = 0;

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
                bh->remove_top();
                remove_top_time += get_counter();
            }
        }
    }
    cout << setprecision(3)
        << "Maksymalny kopiec binarny (ms):" << endl
        << "Dodawanie --> " << (add_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie z gory --> " << (remove_top_time / num_of_test_cases) * 1000.0 << endl << endl;

    ofstream csv_file(HEAP_CSV, ios::app|ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(3)
            << heap_size << ";"
            << (add_time / num_of_test_cases) * 1000.0 << ";"
            << (add_time / num_of_test_cases) * 1000.0 << ";" << endl;
        csv_file.close();
    }
}

void test_bst(int num_of_test_cases, int bst_size) {
    double add_time = 0;
    double remove_time = 0;
    double dsw_time = 0;
    double find_time = 0;

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
                bst->balance_tree_DSW();
                dsw_time += get_counter();

                start_counter();
                bst->remove(random_input);
                remove_time += get_counter();
            }
        }
    }

    cout << setprecision(3)
        <<  "BST (ms):" << endl
        << "Dodawanie --> " << (add_time / num_of_test_cases) * 1000.0 << endl
        << "Wyszukiwanie --> " << (find_time / num_of_test_cases) * 1000.0 << endl
        << "DSW --> " << (dsw_time / num_of_test_cases) * 1000.0 << endl
        << "Usuwanie --> " << (remove_time / num_of_test_cases) * 1000.0 << endl << endl;

    // dodawanie czasow do pliku csv do sprawozdania
    ofstream csv_file(BST_CSV, ios::app | ios::out);
    if (csv_file.is_open()) {
        csv_file << setprecision(3)
            << bst_size << ";"
            << (add_time / num_of_test_cases) * 1000.0 << ";"
            << (find_time / num_of_test_cases) * 1000.0 << ";"
            << (dsw_time / num_of_test_cases) * 1000.0 << ";"
            << (remove_time / num_of_test_cases) * 1000.0 << ";" << endl;
        csv_file.close();
    }
}

int main() {
    int diff = 10;
    int struct_size = 5000;
    int number_of_testcases = 100;

//    test_array(5, 10000);
//
//    test_list(5, 10000);
//    test_heap(5, 10000);
    for (int i = 1; i <= diff; i++) {
        test_array(number_of_testcases, struct_size * i);
        test_list(number_of_testcases, struct_size * i);
        test_heap(number_of_testcases, struct_size * i);
        test_bst(number_of_testcases, struct_size * i);
    }
}
