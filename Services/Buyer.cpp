// File: Buyer.cpp

#include "../Headers/Buyer.h"
#include "../Headers/Seller.h" // <- KUNCI UTAMA: Include Seller.h di sini
#include "../Headers/Store.h"  // Pastikan Store.h juga di-include
#include "../Headers/BankTransaction.h"



Buyer::Buyer(string inputName, string inputEmail, string inputAddress, string inputPhoneNum, BankCustomer* inputCustomer) 
    : id(++buyerIdCounter), name(inputName),email(inputEmail),address(inputAddress), phoneNumber(inputPhoneNum), customerAccount(*inputCustomer){}

// Implementasi atau isi dari fungsi purchaseItem
void Buyer::purchaseItem(int inputItemId, int inputQuantity, Store* inputStore, Seller* inputSeller, vector<Transaction>* transactionHistory){
    if (!inputStore || !inputSeller) {
        cout << "ERROR: Data toko, penjual, atau akun pembeli tidak valid." << endl;
        return;
    }

    Item* item = inputStore->searchItemById(inputItemId);
    if (!item) {
        cout << "ERROR: Item dengan ID " << inputItemId << " tidak ditemukan." << endl;
        return;
    }

    if (item->getItemQuantity() < inputQuantity) {
        cout << "ERROR: Stok item tidak cukup." << endl;
        return;
    }
    
    double totalPrice = item->getItemPrice() * inputQuantity;
    if (customerAccount.getBalance() < totalPrice) {
        cout << "ERROR: Saldo Anda tidak cukup untuk melakukan pembelian." << endl;
        return;
    }

    if (customerAccount.withdraw(totalPrice))
    {
        BankCustomer* sellerAccount = inputSeller->getBuyerAccount();
        if (sellerAccount != nullptr)
        {
            sellerAccount->deposit(totalPrice);
            item->reduceQuantity(inputQuantity);
            transactionHistory->emplace_back(totalPrice, this->id, inputSeller->getSellerId(), item->getItemId(), inputQuantity, item->getItemName(), inputSeller->getStoreName());
            
            cout << "Pembelian berhasil." << endl;
        }else{
            cout << "ERROR: Akun bank penjual tidak ditemukan. Transaksi dibatalkan." << endl;
            // Transaksi gagal, kembalikan uang ke pembeli (rollback)
            customerAccount.deposit(totalPrice);
        }
    } else{
        cout << "ERROR: Transaksi gagal." << endl;
        return;
    }

}
void  Buyer::showInfoBuyer(){
    cout << "\n========================" << endl;
    cout << ">>> == BUYER INFO == <<< " << endl;
    cout << "========================\n" << endl;
    cout << "Buyer ID: " << getBuyerID() << endl;
    cout << "Buyer Name: " << getBuyerName() << endl;
    cout << "Buyer Email: " << getBuyerEmail() << endl;
    cout << "Buyer Phone Number: " << getBuyerPhoneNum() << endl;
    cout << "Buyer Address: " << getBuyerAddress() << endl;
    
        cout << "This Buyer linked with Bank Account" << endl;
        customerAccount.showInfo();
        cout << "\n" << endl;
    
}