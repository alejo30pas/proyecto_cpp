using namespace std;

int main() {
    int n, num, suma;

    cout << "Cuantos numeros va a ingresar: ";
    cin >> n;

    for (int i = 0; i < n; i++) {

        cout << "Ingrese un numero: ";
        cin >> num;

        if (num <= 0) {
            cout << "Numero invalido\n";
        }
        else {
            suma = 0;

            for (int j = 1; j < num; j++) {
                if (num % j == 0) {
                    suma = suma + j;
                }
            }

            if (suma == num)
                printf ("Perfecto\n");
            else
                printf ("No perfecto\n");
        }
    }

    return 0;
}
