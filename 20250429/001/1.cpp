#include <iostream>
#include <vector>

class MergeSort {
public:
    void sort(std::vector<int>& arr) {
        if (arr.size() > 1) {
            int mid = arr.size() / 2;

            std::vector<int> left(arr.begin(), arr.begin() + mid);
            std::vector<int> right(arr.begin() + mid, arr.end());

            sort(left);
            sort(right);

            merge(arr, left, right);
        }
    }

    void printArray(const std::vector<int>& arr) {
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

private:
    void merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        int i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                arr[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            arr[k++] = left[i++];
        }

        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    MergeSort mergeSort;
    std::vector<int> arr;

    std::cout << "Enter array contents (separated by spaces), ending with a non-int" << std::endl;
    std::cout << "> ";
    int num;
    while (std::cin >> num) {
        arr.push_back(num);
    }

    std::cout << "OG: ";
    mergeSort.printArray(arr);

    mergeSort.sort(arr);

    std::cout << "Sorted: ";
    mergeSort.printArray(arr);

    return 0;
}
