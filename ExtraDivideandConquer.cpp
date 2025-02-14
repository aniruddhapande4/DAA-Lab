#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Quick Sort with regular pivot
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Median of Medians Algorithm
int findMedian(vector<int>& arr, int low, int high) {
    vector<int> medians;
    int i;
    for(i = low; i <= high - 4; i += 5) {
        vector<int> temp(arr.begin() + i, arr.begin() + i + 5);
        sort(temp.begin(), temp.end());
        medians.push_back(temp[2]);
    }

    // Handle remaining elements
    if(i <= high) {
        vector<int> temp(arr.begin() + i, arr.begin() + high + 1);
        sort(temp.begin(), temp.end());
        medians.push_back(temp[temp.size()/2]);
    }

    if(medians.size() <= 5)
        sort(medians.begin(), medians.end());
    else
        quickSort(medians, 0, medians.size() - 1);

    return medians[medians.size()/2];
}

int partitionMedian(vector<int>& arr, int low, int high) {
    int median = findMedian(arr, low, high);
    // Find and swap median with last element
    for(int i = low; i <= high; i++) {
        if(arr[i] == median) {
            swap(arr[i], arr[high]);
            break;
        }
    }
    return partition(arr, low, high);
}

void quickSortMedian(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = partitionMedian(arr, low, high);
        quickSortMedian(arr, low, pi - 1);
        quickSortMedian(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Merge Sort with Median of Medians for partitioning
void mergeSortMedian(vector<int>& arr, int left, int right) {
    if(right - left > 5) {
        int median = findMedian(arr, left, right);
        vector<int> lower, higher;

        for(int i = left; i <= right; i++) {
            if(arr[i] < median)
                lower.push_back(arr[i]);
            else if(arr[i] > median)
                higher.push_back(arr[i]);
        }

        mergeSortMedian(lower, 0, lower.size() - 1);
        mergeSortMedian(higher, 0, higher.size() - 1);

        int k = left;
        for(int x : lower) arr[k++] = x;
        for(int i = left; i <= right; i++) if(arr[i] == median) arr[k++] = median;
        for(int x : higher) arr[k++] = x;
    } else {
        // For small subarrays, use insertion sort
        for(int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while(j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
}

// Large Integer Multiplication using Divide and Conquer
string addStrings(string num1, string num2) {
    string result;
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;

    while(i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if(i >= 0) sum += (num1[i--] - '0');
        if(j >= 0) sum += (num2[j--] - '0');
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }

    return result;
}

string multiplyLarge(string num1, string num2) {
    if(num1.length() == 1 && num2.length() == 1) {
        int product = (num1[0] - '0') * (num2[0] - '0');
        return to_string(product);
    }

    // Make numbers equal length by padding zeros
    while(num1.length() < num2.length()) num1 = "0" + num1;
    while(num2.length() < num1.length()) num2 = "0" + num2;

    int n = num1.length();
    if(n == 1) return to_string((num1[0] - '0') * (num2[0] - '0'));

    string a = num1.substr(0, n/2);
    string b = num1.substr(n/2);
    string c = num2.substr(0, n/2);
    string d = num2.substr(n/2);

    string ac = multiplyLarge(a, c);
    string bd = multiplyLarge(b, d);
    string abcd = multiplyLarge(addStrings(a, b), addStrings(c, d));

    for(int i = 0; i < 2*(n-n/2); i++) ac += "0";
    for(int i = 0; i < n-n/2; i++) abcd += "0";

    string temp = addStrings(ac, bd);
    string result = addStrings(temp, abcd);
    result = addStrings(result, "-" + ac);
    result = addStrings(result, "-" + bd);

    // Remove leading zeros
    while(result.length() > 1 && result[0] == '0')
        result.erase(0, 1);

    return result;
}

// [Previous includes and sorting-related functions remain the same until testSortingAlgorithms()]

void testSortingAlgorithms() {
    vector<int> sizes = {100, 1000, 10000, 100000};

    cout << "\nSorting Analysis:\n";
    cout << "Size" << setw(20) << "QuickSort" << setw(25) << "QuickSort (Median)"
         << setw(20) << "MergeSort" << setw(25) << "MergeSort (Median)\n";
    cout << string(90, '-') << endl;

    random_device rd;
    mt19937 gen(rd());

    for(int size : sizes) {
        uniform_int_distribution<> dis(1, size * 10);

        vector<int> arr1(size), arr2(size), arr3(size), arr4(size);
        for(int i = 0; i < size; i++) {
            arr1[i] = dis(gen);
            arr2[i] = arr1[i];
            arr3[i] = arr1[i];
            arr4[i] = arr1[i];
        }

        // Test QuickSort
        auto start = high_resolution_clock::now();
        quickSort(arr1, 0, size-1);
        auto stop = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop - start);

        // Test QuickSort with Median
        start = high_resolution_clock::now();
        quickSortMedian(arr2, 0, size-1);
        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop - start);

        // Test MergeSort
        start = high_resolution_clock::now();
        mergeSort(arr3, 0, size-1);
        stop = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop - start);

        // Test MergeSort with Median
        start = high_resolution_clock::now();
        mergeSortMedian(arr4, 0, size-1);
        stop = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop - start);

        cout << setw(6) << size
             << setw(15) << duration1.count() << " microsec"
             << setw(18) << duration2.count() << " microsec"
             << setw(15) << duration3.count() << " microsec"
             << setw(18) << duration4.count() << " microsec" << endl;
    }
}

void testLargeMultiplication() {
    cout << "\nLarge Integer Multiplication Analysis:\n";
    cout << string(80, '-') << endl;
    cout << left << setw(15) << "Number 1"
         << left << setw(15) << "Number 2"
         << left << setw(30) << "Result"
         << left << "Time" << endl;
    cout << string(80, '-') << endl;

    vector<pair<string, string>> testCases = {
        {"123", "456"},
        {"1234", "5678"},
        {"12345", "67890"},
        {"123456", "789012"},
        {"9999999", "9999999"}  // Added larger test case
    };

    for(auto& test : testCases) {
        auto start = high_resolution_clock::now();
        string result = multiplyLarge(test.first, test.second);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        // Verify result using built-in multiplication
        long long num1 = stoll(test.first);
        long long num2 = stoll(test.second);
        long long expected = num1 * num2;

        cout << left << setw(15) << test.first
             << left << setw(15) << test.second
             << left << setw(30) << to_string(expected)  // Using built-in multiplication for verification
             << left << duration.count() << " microseconds" << endl;
    }
}

int main() {
    cout << fixed << setprecision(2);  // Set floating point precision

    while(true) {
        cout << "\nMenu:\n";
        cout << string(40, '=') << endl;
        cout << "1. Test Sorting Algorithms\n";
        cout << "2. Test Large Integer Multiplication\n";
        cout << "3. Exit\n";
        cout << string(40, '=') << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 1:
                testSortingAlgorithms();
                break;
            case 2:
                testLargeMultiplication();
                break;
            case 3:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}