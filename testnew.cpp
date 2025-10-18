#include <iostream>
#include <string>
#include <ctime>

// Sesuaikan path ke file header-mu jika perlu
#include "Services/BankTransaction.cpp"

using namespace std;

int main() {
    cout << "--- Testing BankTransaction (Static Factory Method) ---\n\n";

    // Skenario 1: Menekan "tombol" createDeposit
    cout << "Membuat objek via BankTransaction::createDeposit(101, 500000.0)...\n";
    BankTransaction depositTx = BankTransaction::createDeposit(101, 500000.0);

    // Cek hasilnya pakai getter
    cout << "ID Nasabah: " << depositTx.getCustomerId() << endl;
    cout << "Jumlah    : " << depositTx.getAmount() << endl;
    cout << "Tipe      : " << depositTx.getTypeString() << endl;
    cout << "--------------------------------------------------------\n\n";

    // Skenario 2: Menekan "tombol" createWithdrawal
    cout << "Membuat objek via BankTransaction::createWithdrawal(202, 75000.0)...\n";
    BankTransaction withdrawalTx = BankTransaction::createWithdrawal(202, 75000.0);

    // Cek hasilnya pakai getter
    cout << "ID Nasabah: " << withdrawalTx.getCustomerId() << endl;
    cout << "Jumlah    : " << withdrawalTx.getAmount() << endl;
    cout << "Tipe      : " << withdrawalTx.getTypeString() << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}