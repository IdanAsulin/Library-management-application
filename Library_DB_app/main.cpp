//
//  main.cpp
//  Library_DB_app
//
//  Created by Idan Asulin on 25/07/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
// Made by Idan Asulin 203949250, Uri Elimelech 308431931

#include <iostream>
#include "Database.h"

using namespace std;

int main(int argc, const char * argv[]) {
    bool flag = true;
    int option;
    cout << "Hello, Please wait while database is loading..." << endl;
    Database& db = Database::getInstance();
    cout << "Database ready !" << endl;
    while(flag) {
        cout << "Please choose an option from the menu followed by enter:" << endl << "1. Print books in stock" << endl << "2. Print all open orders" << endl << "3. Print all costumers" << endl << "4. Print all library suppliers" << endl << "5. Print all transactions between dates" << endl << "6. Print all discounted books" << endl << "7. Check book availability" << endl << "8. Print all book suppliers" << endl << "9. Check how many book copies were sold from a specific date" << endl << "10. Check how many books purchased by a specific costumer" << endl << "11. Print the details of the customer who has purchased the most books since a certain date" << endl << "12. Print supplier details with the most orders since a certain date" << endl << "13. Print how many books were ordered between dates" << endl << "14. Print how many orders turn to transactions between dates" << endl << "15. Print total discount for a specific costumer since a certain date" << endl << "16. Print store revenue by quarters" << endl << "17. Print how many costumers were added since a certain date" << endl << "18. Print total purchases from a certain supplier" << endl << "19. Print total sales of a scertain sales man" << endl << "20. Print 10 best seller books between dates" << endl << "21. Exit" << endl;
        cin >> option;
        switch (option) {
            case 1: {
                db.showBooksInStock();
                break;
            }
            case 2: {
                db.showOpenOrders();
                break;
            }
            case 3: {
                db.showCostumers();
                break;
            }
            case 4: {
                db.showSuppliers();
                break;
            }
            case 5: {
                db.showTransactionBetween();
                break;
            }
            case 6: {
                db.showBooksWithDiscount();
                break;
            }
            case 7: {
                db.checkBookInStock();
                break;
            }
            case 8: {
                db.showBookSuppliers();
                break;
            }
            case 9: {
                db.howManyCopiesSoldSince();
                break;
            }
            case 10: {
                db.howManyBooksPurchByCostumer();
                break;
            }
            case 11: {
                db.showCostuDetWitMostPurch();
                break;
            }
            case 12: {
                db.showSuppDetWitMostOrd();
                break;
            }
            case 13: {
                db.showNumOfOrdersBetween();
                break;
            }
            case 14: {
                db.showOrdersBecomeDeals();
                break;
            }
            case 15: {
                db.howMuchDiscForCos();
                break;
            }
            case 16: {
                db.totalRev();
                break;
            }
            case 17: {
                db.howManyNewCos();
                break;
            }
            case 18: {
                db.sumOfPurchFromSupp();
                break;
            }
            case 19: {
                db.sumOfSales();
                break;
            }
            case 20: {
                db.topTen();
                break;
            }
            case 21: {
                cout << "Bye Bye..." << endl << endl;
                flag = false;
                break;
            }
            default:
                cout << "This is not an available option" << endl << endl;
                option = 11111;
                cin.clear();
                cin.ignore(10000, '\n');
                break;
        }
    }
    return 0;
}
