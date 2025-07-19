#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;
using namespace std::chrono;

// Clear screen (Windows)
void clearScreen() {
    system("cls"); // use "clear" on Linux/macOS
}

// Draw vertical bar graph
void drawGraph(const vector<int>& arr, int highlight1 = -1, int highlight2 = -1) {
    clearScreen();
    int maxVal = *max_element(arr.begin(), arr.end());

    for (int level = maxVal; level >= 1; --level) {
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] >= level) {
                if (i == highlight1)
                    cout << "\033[1;32m █ \033[0m"; // green
                else if (i == highlight2)
                    cout << "\033[1;31m █ \033[0m"; // red
                else
                    cout << " █ ";
            } else {
                cout << "   ";
            }
        }
        cout << '\n';
    }

    // Print index line
    for (int i = 0; i < arr.size(); ++i) {
        cout << " " << (i + 1) % 10 << " ";
    }
    cout << "\n";
    this_thread::sleep_for(milliseconds(300));
}

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            drawGraph(arr, j, j + 1);
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    drawGraph(arr);
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            drawGraph(arr, minIdx, j);
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[minIdx], arr[i]);
            drawGraph(arr, minIdx, i);
        }
    }
    drawGraph(arr);
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            drawGraph(arr, j, j + 1);
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        drawGraph(arr, j + 1, -1);
    }
    drawGraph(arr);
}

// Merge Sort helpers
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (int p = 0; p < k; p++) {
        arr[l + p] = temp[p];
        drawGraph(arr, l + p, -1);
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Quick Sort helpers
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        drawGraph(arr, j, high);
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            if (i != j) drawGraph(arr, i, j);
        }
    }
    swap(arr[i + 1], arr[high]);
    drawGraph(arr, i + 1, high);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Heap Sort helpers
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        drawGraph(arr, i, largest);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        drawGraph(arr, 0, i);
        heapify(arr, i, 0);
    }
    drawGraph(arr);
}

// Function to get user input for array
vector<int> getArrayInput() {
    vector<int> arr;
    int n, val;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        arr.push_back(val);
    }
    
    return arr;
}

// Function to generate random array
vector<int> generateRandomArray() {
    vector<int> arr;
    int n;
    
    cout << "Enter number of elements (e.g., 10-20): ";
    cin >> n;
    
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 15 + 1); // heights from 1 to 15
    }
    
    return arr;
}

int main() {
    vector<int> arr;
    int choice;
    char dataChoice;
    
    cout << "\033[1;36mC++ SORTING VISUALIZER\033[0m\n";
    cout << "=========================\n\n";
    
    cout << "Choose data input method:\n";
    cout << "1. Enter data manually\n";
    cout << "2. Generate random data\n";
    cout << "Enter choice (1-2): ";
    cin >> dataChoice;
    
    if (dataChoice == '1') {
        arr = getArrayInput();
    } else if (dataChoice == '2') {
        arr = generateRandomArray();
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
    
    cout << "\nChoose sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";
    cout << "6. Heap Sort\n";
    cout << "Enter choice (1-6): ";
    cin >> choice;
    
    cout << "\nInitial Array:\n";
    drawGraph(arr);
    cout << "\nSorting...\n";
    this_thread::sleep_for(milliseconds(1000));
    
    switch(choice) {
        case 1:
            bubbleSort(arr);
            break;
        case 2:
            selectionSort(arr);
            break;
        case 3:
            insertionSort(arr);
            break;
        case 4:
            mergeSort(arr, 0, arr.size() - 1);
            drawGraph(arr);
            break;
        case 5:
            quickSort(arr, 0, arr.size() - 1);
            drawGraph(arr);
            break;
        case 6:
            heapSort(arr);
            break;
        default:
            cout << "Invalid choice. Exiting.\n";
            return 1;
    }
    
    cout << "\n\033[1;34mSorting Complete!\033[0m\n";
    return 0;
}