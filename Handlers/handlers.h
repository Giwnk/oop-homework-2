#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <tuple>
#include <ctime>
#include <limits>
#include "../Headers/Buyer.h"
#include "../Headers/BankCustomer.h"
#include "../Headers/Bank.h"
#include "../Headers/Item.h"
#include "../Headers/Store.h"
#include "../Headers/Seller.h"
#include "../Headers/Transaction.h"
#include "../Headers/BankTransaction.h"
#include "../Database.h"
using namespace std;


// Utility Handlers
void clearScreen();

void pressEnterToContinue();

string time_t_to_date_string(time_t timeValue);

// Store Handlers
void listTransactionLatestKDays();

void listPendingTransactions();

void mostFrequentMItems();

void listMostActiveBuyerPerDay();

void listMostActiveSellerPerDay();



// Handlers Bank

void listAllTransactionLastWeek();

void listWithdrawalsLatestKDays(int inputKDays);

void listAllBankCustommers();

void searchCustomersById();

void filterTransactionByType();

void listDormantAccounts();

void listTopActiveUsersToday();

/// =============================================================
/// Buyer Handlers
void checkAccountStatus();

void upgradeToSeller();

void showBuyerInfo();

void showListStores();

void showInventory();

void purchaseItem();

void showAllOrders();

void showLatestSpending();

/// =============================================================
/// Seller Handlers
void showSellerInfo();

void addItem();

void updateItem();

void showMyInventory();

void updateOrderStatus();

void checkSellerBalance();

/// =============================================================
