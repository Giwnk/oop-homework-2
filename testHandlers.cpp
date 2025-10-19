#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "Database.cpp"
#include "Handlers/handlers.h"
using namespace std;



// Taruh fungsi ini di atas main()
void setupDummyData(time_t now, const time_t DAY) {
    cout << "--> Mengisi database dengan data tes...\n";

    

    cout << "--> Data tes siap!\n\n";
}

int main() {
    // 1. Siapkan data dummy
    const time_t DAY_IN_SECONDS = 24 * 60 * 60;
    time_t currentTime = time(0);

    // 1. Siapkan data tes
    setupDummyData(currentTime, DAY_IN_SECONDS);

    // 2. Jalankan skenario-skenario tes
    
    // Skenario 1: Mencari 3 item terlaris
    cout << "--- SKENARIO 1: Tes untuk 3 item terlaris ---\n";
    mostFrequentMItems(3);

    // Skenario 2: Mencari 1 item paling laris
    cout << "--- SKENARIO 2: Tes untuk 1 item terlaris ---\n";
    mostFrequentMItems(1);
    
    // Skenario 3: Mencoba meminta lebih banyak dari item yang ada
    cout << "--- SKENARIO 3: Tes jika m > jumlah item unik ---\n";
    mostFrequentMItems(5);

    return 0;
}