#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker_multiply_row(int row, const vector<vector<int>>& matrix,
                         const vector<int>& vec, vector<int>& result) {
    int sum = 0;
    for (size_t col = 0; col < vec.size(); col++)
        sum += matrix[row][col] * vec[col];
    result[row] = sum;
}

int main() {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<int> vec = {1, 2, 3};
    vector<int> result(3, 0);
    vector<thread> threads;

    for (int i = 0; i < 3; i++)
        threads.emplace_back(worker_multiply_row, i, cref(matrix), cref(vec), ref(result));
    for (auto& t : threads) t.join();

    cout << "Result Vector : [";
    for (size_t i = 0; i < result.size(); i++)
        cout << result[i] << (i + 1 < result.size() ? ", " : "");
    cout << "]" << endl;
    return 0;
}
