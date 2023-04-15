//
// Generujemy dane, mierzymy czas
//

#include "Main.h"
#include "Dynamic_array.h"
#include "Doubly_linked_list.h"
#include "Binary_heap.h"
#include "BST.h"

#define ARR_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\arr_data.txt"
#define LIST_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\list_data.txt"
#define HEAP_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\heap_data.txt"
#define BST_DATA_FILE "C:\\Users\\ayaro\\CLionProjects\\SDiZO\\bst_data.txt"

using namespace std;

long long int read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

// generowanie losowych danych
void generate_random_data(string file_name, int num_obj, int size_obj) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);
    ofstream file(file_name);

    if (file.is_open()) {
        file << num_obj << endl;
        file << size_obj << endl;
        int rand_num;
        for (int i = 0; i < num_obj; i++) {
            for (int j = 0; j < size_obj; j++) {
                rand_num = dist(gen);
                file << rand_num << " ";
            }
            file << endl;
        }
        file.close();
    }
}

int main() {
    generate_random_data(ARR_DATA_FILE, 100, 40);
    generate_random_data(LIST_DATA_FILE, 100, 40);
    generate_random_data(HEAP_DATA_FILE, 100, 40);
    generate_random_data(BST_DATA_FILE, 100, 40);

    auto root = new TreeNode(321, nullptr, nullptr, nullptr);
    auto bst = new BST(root);
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    start = read_QPC();
    // kod ktorego czas wykonania mierzymy

    elapsed = read_QPC() - start;
    cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
                                                         frequency << endl;
    cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
                                                 frequency << endl;
    cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
                                                 frequency << endl << endl;
    system("PAUSE");








}
