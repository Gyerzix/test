#include <iostream>
#include <vector>

using namespace std;
//Класс для коэффициентов тензора
template <typename T>
class tensor {
private:
	vector<vector<T>> tensors;
	int rows;
	int cols;
public:
	tensor() {
		rows = 0;
		cols = 0;
	}
	tensor(int new_row, int new_col) {
		Reset(new_row, new_col);
	}
	void Reset(int new_rows, int new_cols) {
		if (new_rows < 0) {
			throw out_of_range("num_rows must be >= 0");
		}
		else if (new_cols < 0) {
			throw out_of_range("num_cols must be >= 0");
		}
		else if (new_rows == 0 || new_cols == 0) {
			rows = cols = 0;
		}
		else {
			rows = new_rows;
			cols = new_cols;
			tensors.assign(rows, vector<T>(cols));
		}
	}
	int At(int num_row, int num_col) const {
		return tensors.at(num_row).at(num_col);
	}
	int& At(int num_row, int num_col) {
		return tensors.at(num_row).at(num_col);
	}
	int GetNumRows() const {
		return rows;
	}
	int GetNumColumns() const {
		return cols;
	}
	
};

//Перегрузка операторов ввода/вывода для консоли
template <typename T>
istream& operator>>(istream& stream, tensor<T>& Tensor) {
	int rows, cols; stream >> rows >> cols;
	Tensor = tensor<T>(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			stream >> Tensor.At(i, j);
			//  if (stream.peek() != ' ') {
			//	    throw exception();
			//  }
			stream.ignore(1);
		}
	}
	return stream;
}

template <typename T>
ostream& operator<<(ostream& stream, const tensor<T>& Tensor) {
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	stream << rows << " " << cols << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			stream << Tensor.At(i, j) << " ";
			if ((j + 1) % cols == 0) {
				stream << endl;
			}
		}
	}
	return stream;
}

//Операция транспонирования
template <typename T>
tensor<T> transpose(const tensor<T>& Tensor) {
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	tensor<T> result(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = Tensor.At(j, i);
		}
	}
	return result;
}

//Сложение
template <typename T>
tensor<T> operator+(const tensor<T>& lhs, const tensor<T>& rhs) { // Операция сложения только для тензоров одинакового размера
	if ((lhs.GetNumColumns() != rhs.GetNumColumns()) || (lhs.GetNumRows() != rhs.GetNumRows())) {
		throw("dimensions must be the same");
	}
	else {
		int rows = lhs.GetNumRows(); int cols = lhs.GetNumColumns();
		tensor<T> result(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
			}
		}
		return result;
	}
}
//Вычитание
template <typename T>
tensor<T> operator-(const tensor<T>& lhs, const tensor<T>& rhs) { // Операция вычитания только для тензоров одинакового размера
	if ((lhs.GetNumColumns() != rhs.GetNumColumns()) || (lhs.GetNumRows() != rhs.GetNumRows())) {
		throw("dimensions must be the same");
	}
	else {
		int rows = lhs.GetNumRows(); int cols = lhs.GetNumColumns();
		tensor<T> result(rows, cols);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.At(i, j) = lhs.At(i, j) - rhs.At(i, j);
			}
		}
		return result;
	}
}
//Деление
template <typename T>
tensor<T> operator/(const tensor<T>& Tensor, const int& k) {
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	tensor<T> result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = (Tensor.At(i, j)) / k;
		}
	}
	return result;
}
//Симметризация
template <typename T>
tensor<T> Symmetrization(const tensor<T>& Tensor) {
	tensor result = (Tensor + transpose(Tensor)) / 2;
	return result; // result - симметричный тензор
}

//Антисимметризация
template <typename T>
tensor<T> Antisymmetrization(const tensor<T>& Tensor) {
	tensor<T> result = (Tensor - transpose(Tensor)) / 2;
	return result; //result - антисимметричный тензор
}
//Умножение тензоров
template <typename T>
tensor<T> product(const vector<T>& rhs, const vector<T>& lhs) {
	int rows = rhs.size(); int cols = lhs.size();
	tensor<T> result(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = rhs[i] * lhs[j];
		}
	}
	return result;
}

//След
template <typename T>
int tr(const tensor<T>& Tensor) {
	int trace = 0;
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) {
				trace += Tensor.At(i, j);
			}
		}
	}
	return trace;
}

int main() {
	try {
		tensor<int> A;
		cin >> A;
		cout << endl;
		//Антисимметризация и симметризация
		tensor<int> B = Symmetrization(A);
		tensor<int> C = Antisymmetrization(A);
		cout << B + C;

		//След - свертка тензора
		cout << tr(A) << endl;

		//Умножение тензоров
		vector<int> v = { 1, 2, 3 };
		vector<int> s = { 2, 4, 6 };
		tensor<int> C = product(v, s);
		cout << C;
	}

	catch (exception& ex) {
		cout << ex.what();
	}

	return 0;
}