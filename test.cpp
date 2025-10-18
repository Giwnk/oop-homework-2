#include <iostream>
#include <vector>
#include <string>
#include "Services/Buyer.cpp"
#include "Services/BankCustomer.cpp"
#include "Services/Bank.cpp"
#include "Services/Item.cpp"
#include "Services/Store.cpp"
#include "Services/Seller.cpp"
#include "Services/Transaction.cpp"
#include "Services/BankTransaction.cpp"

using namespace std;

int main() {
    cout << "===== Memulai Simulasi E-Commerce =====\n" << endl;

    // --- 1. SETUP BANK DAN NASABAH ---
    cout << "[TAHAP 1] Menyiapkan Bank dan Akun Nasabah..." << endl;
    Bank myBank;
    BankCustomer buyerAccount(101, "Budi Hartono", 2000000); // Saldo awal Budi 2 juta
    BankCustomer buyer2Account(404, "Andi Wijaya", 3000000);
    BankCustomer sellerAccount(202, "Siti Komala", 5000000); // Saldo awal Siti 5 juta
    myBank.addBankCustomer(buyerAccount);
    myBank.addBankCustomer(buyer2Account);
    myBank.addBankCustomer(sellerAccount);
    cout << "Akun untuk Budi dan Siti telah dibuat." << endl;

    // --- 2. SETUP TOKO DAN INVENTARIS ---
    cout << "\n[TAHAP 2] Menyiapkan Toko dan Item..." << endl;
    Store myStore(901, "Toko Jaya Abadi");
    Item mouse("Mouse Gaming RGB", 250000, 10); // Stok 10
    Item keyboard("Keyboard Mechanical", 750000, 5); // Stok 5
    myStore.addItem(mouse);
    myStore.addItem(keyboard);
    cout << "Toko '" << myStore.getStoreName() << "' telah diisi dengan item." << endl;
    myStore.showInventory();

    // --- 3. BUAT OBJEK BUYER DAN SELLER ---
    cout << "\n[TAHAP 3] Membuat objek Pembeli dan Penjual..." << endl;
    // Penting: Objek 'buyerAccount' dan 'sellerAccount' harus ada sebelum membuat Buyer/Seller
    Buyer budi(12345, "Budi Hartono", "budi@email.com", "Jl. Merdeka 1", buyerAccount);
    Buyer andi(98755, "Andi Wijaya", "andi@gmail.com", "Bekasi, Narogong", buyer2Account);
    budi.showInfoBuyer();
    andi.showInfoBuyer();
    
    // Ingat: Seller adalah Buyer, jadi kita teruskan semua info yang relevan
    Seller siti(67890, "Siti Komala", myStore.getStoreName(), "siti@email.com", "Jl. Sudirman 2", sellerAccount, myStore);
    cout << "Objek Budi (Pembeli) dan Siti (Penjual) berhasil dibuat." << endl;

    siti.showInfoSeller();


    // --- 4. SIMULASI TRANSAKSI ---
    cout << "\n[TAHAP 4] Budi akan mencoba membeli 2 Mouse Gaming..." << endl;
    vector<Transaction> transactionHistory;

    // Ini adalah fungsi inti yang menguji hubungan semua class
    budi.purchaseItem(1, 2, &myStore, &siti, &transactionHistory);

    buyerAccount.showAllReceipt();
    sellerAccount.showAllReceipt();

    // --- 5. CEK HASIL AKHIR ---
    cout << "\n[TAHAP 5] Mengecek status akhir setelah transaksi..." << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Saldo akhir Budi: Rp " << budi.getBuyerAccount()->getBalance() << endl;
    cout << "Saldo akhir Siti: Rp " << siti.getBuyerAccount()->getBalance() << endl; // Memanggil getBuyerAccount() karena Seller adalah Buyer
    
    cout << "\nInventaris Toko Setelah Pembelian:" << endl;
    myStore.showInventory();
    
    cout << "\nRiwayat Transaksi:" << endl;
    if (!transactionHistory.empty()) {
        transactionHistory[0].printReceipt();
    } else {
        cout << "Tidak ada transaksi yang tercatat." << endl;
    }
    
    cout << "\n===== Simulasi Selesai =====\n" << endl;

    return 0;
}