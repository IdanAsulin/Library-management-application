//
//  DB.h
//  Library_DB_app
//
//  Created by Idan Asulin on 29/07/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
//

#ifndef DB_h
#define DB_h
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
using namespace sql;
using namespace std;
#define DB_NAME "books_library"
#define DB_HOST "tcp://127.0.0.1/"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "Idan100asulin"

class Database {
private:
    // singleton instance
    static Database *instance;
    
    Driver *driver;
    ConnectOptionsMap connection_properties;
    
    // private CTOR (singleton)
    Database();
public:
    static Database& getInstance();
    
    Connection *getConnection();
    
    void showBooksInStock ();
    void showOpenOrders ();
    void showCostumers ();
    void showSuppliers ();
    void showTransactionBetween ();
    void showBooksWithDiscount ();
    void checkBookInStock ();
    void showBookSuppliers ();
    void howManyCopiesSoldSince ();
    void howManyBooksPurchByCostumer ();
    void showCostuDetWitMostPurch ();
    void showSuppDetWitMostOrd ();
    
    virtual ~Database() {}
};


#endif /* DB_h */
