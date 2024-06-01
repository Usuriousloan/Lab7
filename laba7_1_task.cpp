#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

class Matrix {
public:
    virtual void display() const = 0;
    virtual int countRowsWithoutZeros() const = 0;
    virtual int maxRepeatedNumber() const = 0;
    virtual void transform() = 0;
};

template <typename T>
class MyMatrix : public Matrix {
private:
    vector<vector<T>> matrix;

public:
    MyMatrix(const vector<vector<T>>& mat) : matrix(mat) {}

    void display() const override {
        for (const auto& row : matrix) {
            for (const auto& elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    int countRowsWithoutZeros() const override {
        int count = 0;
        for (const auto& row : matrix) {
            if (find(row.begin(), row.end(), 0) == row.end()) {
                count++;
            }
        }
        return count;
    }

    int maxRepeatedNumber() const override {
        unordered_map<T, int> frequency;
        for (const auto& row : matrix) {
            for (const auto& num : row) {
                frequency[num]++;
            }
        }

        T maxRepeated = numeric_limits<T>::min();
        bool found = false;
        for (const auto& [num, count] : frequency) {
            if (count > 1 && num > maxRepeated) {
                maxRepeated = num;
                found = true;
            }
        }
        return found ? maxRepeated : -1;
    }

    void transform() override {
        for (auto& row : matrix) {
            vector<T> non_zeros;
            vector<T> zeros;
            for (const auto& num : row) {
                if (num == 0) {
                    zeros.push_back(num);
                } else {
                    non_zeros.push_back(num);
                }
            }
            row = zeros;
            row.insert(row.end(), non_zeros.begin(), non_zeros.end());
        }
    }
};

int main() {
    vector<vector<int>> mat = {
        {1, 2, 0},
        {4, 5, 6},
        {0, 8, 9},
        {10, 0, 12}
    };

    MyMatrix<int> matrix(mat);

    cout << "Оригінальна матриця:" << endl;
    matrix.display();

    int numRowsWithoutZeros = matrix.countRowsWithoutZeros();
    cout << "Кількість рядків без нульових елементів: " << numRowsWithoutZeros << endl;

    int maxRepeated = matrix.maxRepeatedNumber();
    cout << "Максимальне число, що повторюється більше одного разу: " << (maxRepeated != -1 ? to_string(maxRepeated) : "Не знайдено") << endl;

    matrix.transform();
    cout << "Перетворена матриця:" << endl;
    matrix.display();

    return 0;
}
