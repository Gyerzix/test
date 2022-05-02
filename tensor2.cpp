#include <iostream>
#include <vector>

using namespace std;
//Класс для коэффициентов тензора
class tensor {
private:
	vector<vector<int>> tensors;
	int rows;
	int cols;
public:
	tensor() {
		rows = 0;
		cols = 0;
	}
	tensor(const int& new_row, const int& new_col) {
		Reset(new_row, new_col);
	}
	void Reset(const int& new_rows, const int& new_cols) {
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
			tensors.assign(rows, vector<int>(cols));
		}
	}
	void show() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << tensors[i][j] << " ";
			}
			cout << endl;
		}
	}
	int At(const int& num_row, const int& num_col) const {
		return tensors.at(num_row).at(num_col);
	}
	int& At(const int& num_row, const int& num_col) {
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
istream& operator>>(istream& stream, tensor& Tensor) {
	int rows, cols; stream >> rows >> cols;
	Tensor = tensor(rows, cols);
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

ostream& operator<<(ostream& stream, const tensor& Tensor) {
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
tensor transpose(const tensor& Tensor) {
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	tensor result(rows, cols); // rows, cols
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = Tensor.At(j, i);
		}
	}
	return result;
}

//Симметризация и антисимметризация тензора
tensor operator+(const tensor& lhs, const tensor& rhs) { // Операция сложения только для тензоров одинакового размера
	int rows = lhs.GetNumRows(); int cols = lhs.GetNumColumns();
	tensor result(rows, cols);
	//if lhs.GetDim() = rhs.GetDim()
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return result;
}

tensor operator-(const tensor& lhs, const tensor& rhs) { // Операция вычитания только для тензоров одинакового размера
	int rows = lhs.GetNumRows(); int cols = lhs.GetNumColumns();
	tensor result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = lhs.At(i, j) - rhs.At(i, j);
		}
	}
	return result;
}

tensor operator/(const tensor& Tensor, const int& k) {
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	tensor result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = (Tensor.At(i, j))/k;
		}
	}
	return result;
}

//Симметризация
tensor Symmetrization(const tensor& Tensor) {
	tensor result = (Tensor + transpose(Tensor))/2;
	return result; // result - симметричный тензор
}

//Антисимметризация
tensor Antisymmetrization(const tensor& Tensor) {
	tensor result = (Tensor - transpose(Tensor))/2;
	return result; //result - антисимметричный тензор
}

//Свертка - след
int Tr(const tensor& Tensor) {
	int trace = 0;
	int rows = Tensor.GetNumRows(); int cols = Tensor.GetNumColumns();
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i = j) {
				trace += Tensor.At(i, j);
			}
		}
	}
	return trace;
}

//Умножение тензоров
tensor product(const vector<int>& rhs, const vector<int>& lhs) {
	int rows = rhs.size(); int cols = lhs.size();
	tensor result(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.At(i, j) = rhs[i] * lhs[j];
		}
	}
	return result;
}

int main() {
	tensor A;
	cin >> A;
	tensor B = transpose(A);
	cout << A;
	cout << endl;
	cout << B;
	/*vector<int> v = {1, 2, 3};
	vector<int> s = { 2, 4, 6 };
	tensor C = product(v, s); //Тензорное произведение двух тензоров 1 ранга дает тензор 2 ранга
	C.show();*/
	return 0;
}