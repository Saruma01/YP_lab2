#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

// Функция для генерации случайной матрицы целых чисел
vector<vector<int>> generateIntMatrix(int rows, int cols, int minVal, int maxVal) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    return matrix;
}

// Функция для генерации случайной стохастической матрицы
vector<vector<double>> generateStochasticMatrix(int n) {
    vector<vector<double>> matrix(n, vector<double>(n));

    for (int j = 0; j < n; ++j) {
        double sum = 0;
        // Генерируем случайные числа для столбца
        for (int i = 0; i < n; ++i) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;
            sum += matrix[i][j];
        }
        // Нормализуем столбец
        for (int i = 0; i < n; ++i) {
            matrix[i][j] /= sum;
        }
    }

    return matrix;
}

// Функция для вывода матрицы целых чисел
void printIntMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << setw(4) << val;
        }
        cout << endl;
    }
}

// Функция для вывода матрицы вещественных чисел
void printDoubleMatrix(const vector<vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << fixed << setprecision(4) << setw(8) << val;
        }
        cout << endl;
    }
}

// Функция для перемножения матриц целых чисел
vector<vector<int>> multiplyIntMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = A[0].size(); // равно B.size()
    int k = B[0].size();

    vector<vector<int>> result(n, vector<int>(k, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int l = 0; l < m; ++l) {
                result[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return result;
}

// Функция для перемножения матриц вещественных чисел
vector<vector<double>> multiplyDoubleMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> result(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Функция для умножения матрицы на вектор
vector<double> multiplyMatrixVector(const vector<vector<double>>& A, const vector<double>& x) {
    int n = A.size();
    vector<double> result(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }

    return result;
}
// функция вычисления матрицы целых чисел
void matrixMultiplicationTask() {
    int N, M, K;
    cout << "Введите N (1-10): ";
    cin >> N;
    cout << "Введите M (1-10): ";
    cin >> M;
    cout << "Введите K (1-10): ";
    cin >> K;

    if (N < 1 || N > 10 || M < 1 || M > 10 || K < 1 || K > 10) {
        cout << "Числа должны быть в диапазоне от 1 до 10" << endl;
        return;
    }

    auto matrix1 = generateIntMatrix(N, M, 1, 9);
    auto matrix2 = generateIntMatrix(M, K, 1, 9);

    cout << "\nПервая матрица (NxM):\n";
    printIntMatrix(matrix1);
    cout << "\nВторая матрица (MxK):\n";
    printIntMatrix(matrix2);

    auto result = multiplyIntMatrices(matrix1, matrix2);

    cout << "\nРезультат умножения (NxK):\n";
    printIntMatrix(result);
}
// функция вычисления матрицы вещественных чисел
void stochasticMatrixTask() {
    int N;
    cout << "Введите N (2-10): ";
    cin >> N;

    if (N < 2 || N > 10) {
        cout << "Число должно быть в диапазоне от 2 до 10" << endl;
        return;
    }

    auto A = generateStochasticMatrix(N);
    cout << "\nСтохастическая матрица A:\n";
    printDoubleMatrix(A);

    // Вектор начальных вероятностей
    vector<double> x(N, 1.0 / N);

    // Быстрое возведение в степень 2^20
    vector<vector<double>> currentPower = A;
    int power = 1;
    const int targetPower = pow(2, 20);

    while (power < targetPower) {
        currentPower = multiplyDoubleMatrices(currentPower, currentPower);
        power *= 2;
        cout << "\nМатрица A^" << power << ":\n";
        printDoubleMatrix(currentPower);
    }

    // Умножение на вектор начальных вероятностей
    auto result = multiplyMatrixVector(currentPower, x);

    cout << "\nВероятности после 2^20 шагов:\n";
    for (double val : result) {
        cout << fixed << setprecision(6) << val << " ";
    }
    cout << endl;
}
// меню
void showMenu() {
    cout << "\nМеню:\n";
    cout << "1. Перемножение прямоугольных матриц\n";
    cout << "2. Работа со стохастической матрицей\n";
    cout << "3. Выход\n";
    cout << "Выберите задание: ";
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            matrixMultiplicationTask();
            break;
        case 2:
            stochasticMatrixTask();
            break;
        case 3:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 3);

    return 0;
}