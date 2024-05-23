#include<iostream>
using namespace std;
int main() {

	char array[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m',
					  'n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char P1, P2, C1, C2, P1_index = -1, P2_index = -1, C1_index = -1, C2_index = -1;
	int i, j, det_A = 0, det_A_inv = 0, N;
	cout << "Enter First PlainText Letter : ";
	cin >> P1;
	cout << "\nEnter First CipherText letter :";
	cin >> C1;
	cout << "\nEnter Second PlainText letter :";
	cin >> P2;
	cout << "\nEnter Second CipherTextletter :";
	cin >> C2;

	for (i = 0; i < 26; i++) {
		if (array[i] == P1) {
			P1_index = i;
			break;
		}
	}
	for (i = 0; i < 26; i++) {
		if (array[i] == P2) {
			P2_index = i;
			break;
		}
	}
	for (i = 0; i < 26; i++) {
		if (array[i] == C1) {
			C1_index = i;
			break;
		}
	}
	for (i = 0; i < 26; i++) {
		if (array[i] == C2) {
			C2_index = i;
			break;
		}
	}

	int A[2][2] = { {P1_index,1},{P2_index,1} };
	int B[2] = { C1_index,C2_index };
	int X[2] = { 0 };
	int Adj_A[2][2];


	cout << "Matrix A : " << endl;

	for (i = 0; i < 2; i++) {

		for (j = 0; j < 2; j++) {
			cout << A[i][j] << " ";

		}
		cout << endl;

	}
	cout << "\nMatrix B : ";

	for (i = 0; i < 2; i++) {
		cout << B[i] << " ";
	}

	det_A = ((A[0][0] * A[1][1]) - (A[1][0] * A[0][1])) % 26;
	if (det_A < 0) {
		det_A = det_A + 26;
	}


	cout << "\ndeterminat of A : " << det_A << endl;

	if (det_A == 0 || det_A % 2 == 0 || det_A % 13 == 0) {
		cout << "Program not executed: multiplicative inverse of " << det_A << " does not exist in Z26." << endl;
		system("pause>0");
		return 0;
	}


	// Finding Adjoint of A 
	Adj_A[0][0] = A[1][1];
	Adj_A[0][1] = -A[0][1];
	Adj_A[1][0] = -A[1][0];
	Adj_A[1][1] = A[0][0];
	cout << "\nAdjoint of A : " << endl;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			cout << Adj_A[i][j] << " ";
		}
		cout << endl;
	}

	int a = det_A, n = 26;
	int t1 = 0, t2 = 1, r1 = n, r2 = a, t, r, q;
	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	// output results
	if (r1 == 1) {
		if (t1 < 0) {
			t1 += n;
		}
		det_A_inv = t1;
	}

	cout << "\nDeterminant_A_Inverse : " << det_A_inv;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			X[i] += det_A_inv * Adj_A[i][j] * B[j];
			X[i] = X[i] % 26;
			if (X[i] < 0) {
				X[i] += 26;
			}
		}
	}

	cout << "\n\n Keys  : " << endl;
	cout << "K1 = " << X[0] << endl;
	cout << "K2 = " << X[1] << endl;

	cout << "Enter the no of letters in your Name: ";
	cin >> N;
	// dynamically allocate memory
	char* P = new char[N];
	char* C = new char[N];
	cout << "Enter the PlainText (maximum " << N << " letters): " << endl;
	for (int i = 0; i < N; i++)
	{
		cin >> C[i];
	}

	for (j = 0; j < N; j++)
	{

		for (i = 0; i < 26; i++)
		{
			if (array[i] == C[j])
			{
				break;
			}
		}
		int K1_inv = 0;
		for (int k = 1; k < 26; k++)
		{
			if (((X[0] * k) % 26) == 1)
			{
				K1_inv = k;
				break;
			}
		}
		P[j] = array[((K1_inv * (i - X[1] + 26)) % 26)];
	}

	cout << "Decrypted array: ";
	for (int i = 0; i < N; i++)
	{
		cout << P[i];
	}
	cout << endl;



	system("pause>0");
	return 0;
}

