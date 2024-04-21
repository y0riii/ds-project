#include <bits/stdc++.h>
#include <cmath>
#include <chrono>

using namespace std;

class Student {
    string id;
    string name;
    double gpa;
    public:
    Student(string s, string s2, double n) {
        id = s;
        name = s2;
        gpa = n;
    }

    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getGpa() const {
        return gpa;
    }

    void setId(const string& s) {
        id = s;
    }

    void setName(const string& s) {
        name = s;
    }

    void setGpa(double n) {
        gpa = n;
    }

    bool operator<(const Student& other) const {
        return name < other.getName();
    }

    bool operator>(const Student& other) const {
        return name > other.getName();
    }
};

template<typename T>
void bubbleSort(vector<T>& arr, int& comps, bool byGpa) {
    int n = arr.size();
    comps = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comps;
            if (byGpa ? (arr[j].getGpa() < arr[j + 1].getGpa()) : (arr[j].getName() > arr[j + 1].getName())) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template<typename T>
void selectionSort(vector<T>& arr, int& comps, bool byGpa) {
    int n = arr.size();
    comps = 0;

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            ++comps;
            if (byGpa ? (arr[j].getGpa() > arr[minIndex].getGpa()) : (arr[j].getName() < arr[minIndex].getName())) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

template<typename T>
void insertionSort(vector<T>& arr, int& comps, bool byGpa) {
    int n = arr.size();
    comps = 0;

    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && (byGpa ? (arr[j].getGpa() < key.getGpa()) : (arr[j].getName() > key.getName()))) {
            ++comps;
            arr[j + 1] = arr[j];
            --j;
        }
        ++comps;
        arr[j + 1] = key;
    }
}

template<typename T>
void writeAnswer(string algo, vector<T>& arr, int& comps, double time, bool byGpa) {
    string fileName = "SortedByGPA.txt";
    if(!byGpa) fileName = "SortedByName.txt";

    FILE* file = freopen(fileName.c_str(), "a", stdout);
    if (!file) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return;
    }
    string wAlgo = "";
    bool prevSpace = true;
    for(int i=0; i<algo.length(); ++i) {
        if(prevSpace) {
            wAlgo += toupper(algo[i]);
            prevSpace = false;
            continue;
        }
        wAlgo += algo[i];
        if(algo[i] == ' ') prevSpace = true;
    }

    // Write content to the 

    cout << "Algorithm: " << wAlgo << "\n";
    cout << "Number of comparisons: " << comps << "\n";
    cout << "Running Time: " << time << " microseconds\n";
    for(int i=0; i<arr.size(); ++i) {
        cout << arr[i].getName() << "\n";
        cout << arr[i].getId() << "\n";
        cout << arr[i].getGpa() << "\n";
    }
    cout << "\n";
    fclose(file);
    freopen("CON", "w", stdout);
}

template<typename T>
void assess(string algo, vector<T> arr, bool byGpa=true, bool stop=false) {
    int comps = 0;
    vector<T> arr2;
    if(!stop) {
        for(int i=0; i<arr.size(); ++i) {
            arr2.push_back(arr[i]);
        }
    }
    auto start = std::chrono::high_resolution_clock::now();

    if(algo == "bubble sort") {
        bubbleSort(arr, comps, byGpa);
    } else if(algo == "selection sort") {
        selectionSort(arr, comps, byGpa);
    } else if(algo == "insertion sort") {
        insertionSort(arr, comps, byGpa);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    writeAnswer(algo, arr, comps, duration.count(), byGpa);
    if(!stop) assess(algo, arr2, !byGpa, true);
}

void resetFiles() {
    FILE* file = freopen("SortedByGPA.txt", "w", stdout);
    if (!file) {
        cerr << "Error: Unable to open file " << "SortedByGPA.txt" << endl;
    }
    fclose(file);
    file = freopen("SortedByName.txt", "w", stdout);
    if (!file) {
        cerr << "Error: Unable to open file " << "SortedByName.txt" << endl;
    }
    fclose(file);
    freopen("CON", "w", stdout);
}

int main() {
    resetFiles();
    vector<Student> students;
    string fileName = "students.txt";
    FILE *file = freopen(fileName.c_str(), "r", stdin);

    if (!file) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return 0;
    }

    string id, name;
    double gpa;
    int t;
    cin >> t;
    getline(cin, name);
    while(t--) {
        getline(cin, name);
        getline(cin, id);
        cin >> gpa;
        students.push_back(Student(id, name, gpa));
        getline(cin, name);
    }
    assess("bubble sort", students);
    assess("selection sort", students);
    assess("insertion sort", students);
    return 0;
}