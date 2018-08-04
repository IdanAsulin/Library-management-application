//
//  DB.cpp
//  Library_DB_app
//
//  Created by Idan Asulin on 29/07/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
//

#include "Database.h"
#include <string>
#include "costumerSupplier.h"
#include "book.h"
void cinClearing () {
    string temp;
    getline(cin, temp);
}

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
    connection_properties["hostName"] = DB_HOST;
    connection_properties["port"] = DB_PORT;
    connection_properties["userName"] = DB_USER;
    connection_properties["password"] = DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
    // use database
    try {
        Connection *con = driver->connect(connection_properties);
        try {
            con->setSchema(DB_NAME);
        }
        catch (SQLException &e) {
            Statement *stmt = con->createStatement();
            string q = "CREATE DATABASE IF NOT EXISTS ";
            q.append(DB_NAME);
            stmt->execute(q);
            con->setSchema(DB_NAME); // switch database
            stmt->execute("CREATE TABLE IF NOT EXISTS book ( "
                          "book_name VARCHAR(25) PRIMARY KEY, "
                          "price_before_discount INT UNSIGNED, "
                          "stock INT UNSIGNED, "
                          "global_discount_precents INT UNSIGNED, "
                          "supplier_num INT UNSIGNED, "
                          "sold_copies INT UNSIGNED"
                          ")");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Harry Potter', 100, 15, 0, 1, 10)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Monte Cristo', 150, 453, 0, 2, 11)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('The Ring', 80, 0, 0, 3, 3)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Fire', 40, 33, 0, 4, 23)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Way To Heaven', 120, 45, 0, 5, 55)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Bible', 55, 33, 0, 6, 2)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Computers', 33, 10, 15, 7, 0)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('Web Development', 90, 3, 20, 7, 0)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('C++', 96, 6, 30, 7, 0)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num, sold_copies) VALUES ('C sharp', 48, 8, 10, 4, 4)");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS costumer ( "
                          "costumer_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, "
                          "private_name VARCHAR(20), "
                          "last_name VARCHAR(25), "
                          "join_date DATETIME, "
                          "transaction_lastyear INT UNSIGNED, "
                          "transaction_total INT UNSIGNED "
                          ")");
            stmt->execute("INSERT INTO costumer (costumer_id, private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES (1, 'Idan', 'Asulin', '2000-1-1', 200, 400)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Uri', 'Elimelech', '1999-3-9', 345, 500)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Omri', 'Gil', '2013-6-27', 33, 98)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Edan', 'Azran', '2017-4-9', 0, 0)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Linoy', 'Aharon', '2002-6-29', 0, 0)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Yafit', 'Nachum', '2012-4-26', 0, 100)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Tal', 'Cohen', '1998-5-28', 1000, 1500)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Eyal', 'Levi', '2011-11-11', 1200, 1600)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Eliran', 'Sum', '2005-8-18', 980, 1000)");
            stmt->execute("INSERT INTO costumer (private_name, last_name, join_date, transaction_lastyear, transaction_total) VALUES ('Shiran', 'Naftali', '2007-3-26', 555, 976)");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS transaction ( "
                          "order_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, "
                          "transaction_date DATETIME, "
                          "costumer_id INT UNSIGNED, "
                          "order_status VARCHAR(25), "
                          "is_canceled BIT, "
                          "num_of_books INT UNSIGNED, "
                          "cost INT UNSIGNED, " // assume that orders cost can be only interger
                          "discount_ils INT UNSIGNED, "
                          "emp_id INT UNSIGNED "
                          ")");
            stmt->execute("INSERT INTO transaction (order_id, transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES (1, '2000-1-1', 1, 'Payed', 0, 1, 150, 0, 1)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2002-3-2', 1, 'Payed', 0, 3, 50, 10, 1)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('1999-3-9', 2, 'Payed', 1, 1, 145, 0, 2)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2008-4-20', 2, 'Payed', 0, 1, 100, 0, 1)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2013-6-27', 3, 'Payed', 1, 1, 33, 0, 5)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('1998-5-28', 7, 'Payed', 1, 1, 1000, 100, 3)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2011-11-11', 8, 'Payed', 0, 1, 1200, 120, 3)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2005-8-18', 9, 'Payed', 0, 1, 400, 0, 2)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2007-3-27', 10, 'Payed', 0, 1, 555, 19, 10)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2007-2-10', 9, 'Payed', 1, 1, 580, 10, 9)");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS orders ( "
                          "order_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, "
                          "order_date DATETIME, "
                          "costumer_id INT UNSIGNED, "
                          "order_status VARCHAR(25), "
                          "num_of_books INT UNSIGNED "
                          ")");
            stmt->execute("INSERT INTO orders (order_id, order_date, costumer_id, order_status, num_of_books) VALUES (1, '2000-1-1', 1, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2002-3-2', 1, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('1999-3-9', 2, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2008-4-20', 2, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2013-6-27', 3, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('1998-5-28', 7, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2011-11-11', 8, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2005-8-18', 9, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2007-3-27', 10, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2007-2-10', 9, 'Payed', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('1999-8-9', 6, 'Message sent', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2001-2-10', 5, 'Arrived', 1)");
            stmt->execute("INSERT INTO orders (order_date, costumer_id, order_status, num_of_books) VALUES ('2009-4-3', 1, 'In order', 1)");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS contain ( "
                          "order_id INT UNSIGNED, "
                          "book_name VARCHAR(25), "
                          "order_date DATETIME, "
                          "PRIMARY KEY(order_id, book_name) "
                          ")");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (1, 'Harry Potter', '2000-1-1')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (2, 'Harry Potter', '2002-3-2')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (3, 'C++', '1999-3-9')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (4, 'C++', '2008-4-20')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (5, 'Monte Cristo', '2013-6-27')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (6, 'Monte Cristo', '1998-5-28')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (7, 'Monte Cristo', '2011-11-11')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (8, 'C++', '2005-8-18')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (9, 'C++', '2007-3-27')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (10, 'Harry Potter', '2007-2-10')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (11, 'C sharp', '1999-8-9')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (12, 'C sharp', '2001-2-10')");
            stmt->execute("INSERT INTO contain (order_id, book_name, order_date) VALUES (13, 'Way To Heaven', '2009-4-3')");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS supply ( "
                          "supplier_id INT UNSIGNED, "
                          "book_name VARCHAR(25), "
                          "supply_date DATETIME, "
                          "amount INT UNSIGNED, "
                          "supply_cost INT UNSIGNED, "
                          "PRIMARY KEY(supplier_id, book_name) "
                          ")");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (1, 'Harry Potter', '1999-3-9', 10, 100)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (1, 'C++', '2008-4-20', 1, 50)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (2, 'Monte Cristo', '2013-6-27', 33, 30)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (3, 'C sharp', '1998-5-28', 32, 55)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (4, 'Way To Heaven', '2011-11-11', 55, 67)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (5, 'Web Development', '2005-8-18', 43, 74)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (6, 'Web Development', '2007-3-27', 2, 23)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (3, 'Fire', '2007-2-10', 12, 54)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (3, 'Computers', '1999-8-9', 11, 67)");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date, amount, supply_cost) VALUES (5, 'Computers', '2001-2-10', 6, 188)");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS supplier ( "
                          "supplier_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, "
                          "supplier_name VARCHAR(25) "
                          ")");
            stmt->execute("INSERT INTO supplier (supplier_id, supplier_name) VALUES (1, 'Danny')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Yuval')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Ran')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Avi')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Tal')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Yossi')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Gal')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Moshe')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Itzik')");
            stmt->execute("INSERT INTO supplier (supplier_name) VALUES ('Shimi')");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS supplier_supplies ( "
                          "supplier_id INT UNSIGNED, "
                          "book_name VARCHAR(25), "
                          "store_cost INT UNSIGNED, "
                          "PRIMARY KEY(supplier_id, book_name) "
                          ")");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (1, 'Harry Potter', 80)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (1, 'Bible', 30)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (1, 'Monte Cristo', 100)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (2, 'Harry Potter', 80)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (3, 'Harry Potter', 70)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (4, 'Monte Cristo', 98)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (5, 'C++', 49)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (6, 'Bible', 30)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (7, 'Monte Cristo', 100)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (8, 'Bible', 30)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (9, 'C++', 77)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (10, 'Harry Potter', 65)");
            stmt->execute("INSERT INTO supplier_supplies (supplier_id, book_name, store_cost) VALUES (10, 'Bible', 30)");
            
            delete stmt;
        }
        
        delete con;
    }
    catch (SQLException &e) {
        cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
        throw e;
    }
}

Database & Database::getInstance() {
    if (Database::instance == 0) {
        instance = new Database();
    }
    return *instance;
}

Connection * Database::getConnection() {
    try {
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        return con;
    } catch (SQLException &e) {
        cout << e.what();
    }
    return 0;
}

void Database::showBooksInStock() {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    ResultSet *row = stmt->executeQuery("SELECT * FROM book WHERE stock > 0");
    int count = 1;
    row->beforeFirst();
    cout << "Currently in stock:" << endl;
    while(row->next()) {
        cout << count++ << ". " << row->getString("book_name") << endl;
    }
    cout << endl;
    delete con;
    delete stmt;
    delete row;
}

void Database::showOpenOrders () {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    ResultSet *row = stmt->executeQuery("SELECT * FROM orders WHERE order_status != 'Payed'");
    int count = 1;
    row->beforeFirst();
    cout << "Open orders list:" << endl;
    while(row->next()) {
        cout << count++ << ". " << "Order number: " << row->getString("order_id") << ", Status: " << row->getString("order_status") << endl;
    }
    cout << endl;
    delete con;
    delete stmt;
    delete row;
}

void Database::showCostumers () {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    ResultSet *row = stmt->executeQuery("SELECT * FROM costumer");
    int count = 1;
    row->beforeFirst();
    cout << "Costumers list:" << endl;
    while(row->next()) {
        cout << count++ << ". " << row->getString("private_name") << " " << row->getString("last_name") << endl;
    }
    cout << endl;
    delete con;
    delete stmt;
    delete row;
}

void Database::showSuppliers () {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    ResultSet *row = stmt->executeQuery("SELECT * FROM supplier");
    int count = 1;
    row->beforeFirst();
    cout << "Suppliers list:" << endl;
    while(row->next()) {
        cout << count++ << ".Supplier name: " << row->getString("supplier_name") << ", Supplier number: " << row->getString("supplier_id") << endl;
    }
    cout << endl;
    delete con;
    delete stmt;
    delete row;
}

void Database::showTransactionBetween () {
    string d1, d2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cin >> d1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cin >> d2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transaction WHERE transaction_date BETWEEN ? AND ?");
    pstmt->setString(1, d1);
    pstmt->setString(2, d2);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    int count = 1;
    while(row->next()) {
        cout << count++ << ". " << "Transaction number: " << row->getString("order_id") << ", Transaction date: " << row->getString("transaction_date") << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showBooksWithDiscount () {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *stmt = con->createStatement();
    ResultSet *row = stmt->executeQuery("SELECT * FROM book WHERE global_discount_precents > 0");
    int count = 1;
    row->beforeFirst();
    cout << "Books with global discount:" << endl;
    while(row->next()) {
        cout << count++ << ". " << row->getString("book_name") << endl;
    }
    cout << endl;
    delete con;
    delete stmt;
    delete row;
}

void Database::checkBookInStock () {
    string bookName;
    cout << "Please enter book name followed by enter" << endl;
    cinClearing();
    getline(cin, bookName);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM book WHERE book_name = ?");
    pstmt->setString(1, bookName);
    ResultSet *row = pstmt->executeQuery();
    if(row->first())
        cout << "There is " << row->getUInt("stock") << " copies in stock" << endl;
    else
        cout << "This book is not available" << endl << endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showBookSuppliers () {
    string bookName;
    cout << "Please enter book name followed by enter" << endl;
    cinClearing();
    getline(cin, bookName);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM supplier_supplies WHERE book_name = ?");
    pstmt->setString(1, bookName);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    int count = 1;
    cout << "These suppliers (supplier number) provide " << bookName << ":" << endl;
    while(row->next()) {
        cout << count++ << ". " << row->getString("supplier_id") << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::howManyCopiesSoldSince () {
    string bookName, date;
    cout << "Please enter book name followed by enter" << endl;
    cinClearing();
    getline(cin, bookName);
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    getline(cin, date);
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM contain INNER JOIN transaction ON contain.order_id = transaction.order_id WHERE contain.book_name = ? AND contain.order_date >= ?");
    pstmt->setString(1, bookName);
    pstmt->setString(2, date);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    if(row->next()) {
        cout << endl << row->getString("book_name") << " has purchased " << row->rowsCount() << " times" << endl;
    }
    else
        cout << "No purchased found" << endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::howManyBooksPurchByCostumer () {
    int cosID;
    string date;
    cout << "Please enter costumer ID followed by enter" << endl;
    cinClearing();
    cin >> cosID;
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    cin >> date;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM transaction WHERE costumer_id = ? AND transaction_date >= ?");
    pstmt->setUInt(1, cosID);
    pstmt->setString(2, date);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    int count = 0;
    while(row->next()) {
        count += row->getUInt("num_of_books");
    }
    cout << endl << "Costumer: " << cosID << " has purchased " << count << " books" << endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showCostuDetWitMostPurch () {
    string date;
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT costumer_id FROM transaction WHERE transaction_date >= ?"); // we choose only id column because we want to know how many clients were bought books and in this way we prevent counting twice the same client
    pstmt->setString(1, date);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    int arraySize = (int)row->rowsCount();
    costumerSupplier c [arraySize]; // insert all costumers who bought books in the relevant date into an array
    int index = 0;
    while(row->next())
        c[index++].setCosID(row->getUInt("costumer_id")); // set al costumers id in array
    pstmt = con->prepareStatement("SELECT * FROM transaction WHERE transaction_date >= ?");
    pstmt->setString(1, date);
    row = pstmt->executeQuery();
    row->beforeFirst();
    index = 0;
    while(row->next())
        for(index = 0; index < arraySize; ++index)
            if(row->getUInt("costumer_id") == c[index].getCosID())
                c[index].addBooks(row->getUInt("num_of_books"));
    int max = c[0].getNumOfBooks();
    int memory = 0; // tells us who is the maximum client because we finally want to print his details
    for(index = 1; index < arraySize; index++)
        if(max < c[index].getNumOfBooks()) {
            max = c[index].getNumOfBooks();
            memory = index;
        }
    memory = c[memory].getCosID();
    pstmt = con->prepareStatement("SELECT * FROM costumer WHERE costumer_id = ?");
    pstmt->setUInt(1, memory);
    row = pstmt->executeQuery();
    row->first();
    cout << endl << "Top client is: " << row->getString("private_name") << " " << row->getString("last_name") << " Costumer ID: " << memory << " Number of books: " << max << endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showSuppDetWitMostOrd () {
    string date;
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT supplier_id FROM supply WHERE supply_date >= ?");
    pstmt->setString(1, date);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    int arraySize = (int)row->rowsCount();
    costumerSupplier c [arraySize]; // insert all costumers who bought books in the relevant date into an array
    int index = 0;
    while(row->next())
        c[index++].setCosID(row->getUInt("supplier_id"));
    pstmt = con->prepareStatement("SELECT * FROM supply WHERE supply_date >= ?");
    pstmt->setString(1, date);
    row = pstmt->executeQuery();
    row->beforeFirst();
    index = 0;
    while(row->next())
        for(index = 0; index < arraySize; ++index)
            if(row->getUInt("supplier_id") == c[index].getCosID())
                c[index].addBooks(row->getUInt("amount"));
    int max = c[0].getNumOfBooks();
    int memory = 0;
    for(index = 1; index < arraySize; index++)
        if(max < c[index].getNumOfBooks()) {
            max = c[index].getNumOfBooks();
            memory = index;
        }
    memory = c[memory].getCosID();
    pstmt = con->prepareStatement("SELECT * FROM supplier WHERE supplier_id = ?");
    pstmt->setUInt(1, memory);
    row = pstmt->executeQuery();
    row->first();
    cout << endl << "Top supplier is: " << row->getString("supplier_name") << " Supplier ID: " << memory << " Number of books: " << max << endl;
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showNumOfOrdersBetween () {
    string date1,date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders WHERE order_date BETWEEN ? AND ?");
    pstmt->setString(1, date1);
    pstmt->setString(2, date2);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    cout << "Number of orders: " << row->rowsCount() << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::showOrdersBecomeDeals () {
    string date1,date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM orders WHERE order_date BETWEEN ? AND ? AND order_status = 'Payed'");
    pstmt->setString(1, date1);
    pstmt->setString(2, date2);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    cout << "Number of orders: " << row->rowsCount() << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::howMuchDiscForCos () {
    int cosNum;
    string date;
    cout << "Please enter costumer number" << endl;
    cinClearing();
    cin >> cosNum;
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(discount_ils) as counter FROM transaction WHERE transaction_date >= ? AND costumer_id = ?");
    pstmt->setString(1, date);
    pstmt->setUInt(2, cosNum);
    ResultSet *row = pstmt->executeQuery();
    row->first();
    cout << "Total discount: " << row->getUInt("counter") << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::totalRev () {
    string date, s_date, e_date;
    int q;
    cout << "Please enter year (yyyy)" << endl;
    cinClearing();
    cin >> date;
    cout << "Please enter quarter number (number between 1-4)" << endl;
    cinClearing();
    cin >> q;
    switch (q) {
        case 1:
            s_date = date + "-1-1";
            e_date = date + "-3-30";
            break;
        case 2:
            s_date = date + "-4-1";
            e_date = date + "-6-30";
            break;
        case 3:
            s_date = date + "-7-1";
            e_date = date + "-9-30";
            break;
        case 4:
            s_date = date + "-10-1";
            e_date = date + "-12-30";
            break;
    }
    cout << s_date << endl;
    cout << e_date << endl;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(cost) as totalIn FROM transaction WHERE transaction_date BETWEEN ? AND ?");
    pstmt->setString(1, s_date);
    pstmt->setString(2, e_date);
    ResultSet *row = pstmt->executeQuery();
    row->first();
    int in = row->getUInt("totalIn");
    pstmt = con->prepareStatement("SELECT SUM(supply_cost) as totalOut FROM supply WHERE supply_date BETWEEN ? AND ?");
    pstmt->setString(1, s_date);
    pstmt->setString(2, e_date);
    row = pstmt->executeQuery();
    row->first();
    int out = row->getUInt("totalOut");
    cout << "Total incomes: " << in - out << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::howManyNewCos () {
    string date;
    cout << "Please enter date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM costumer WHERE join_date >= ?");
    pstmt->setString(1, date);
    ResultSet *row = pstmt->executeQuery();
    row->beforeFirst();
    cout << "Number of costumers who joined since then: " << row->rowsCount() << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::sumOfPurchFromSupp () {
    int suppId;
    string date1, date2;
    cout << "Please enter supplier ID" << endl;
    cinClearing();
    cin >> suppId;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(supply_cost) as counter FROM supply WHERE supplier_id = ? AND supply_date BETWEEN ? AND ?");
    pstmt->setUInt(1, suppId);
    pstmt->setString(2, date1);
    pstmt->setString(3, date2);
    ResultSet *row = pstmt->executeQuery();
    row->first();
    cout << "Total orders cost: " << row->getUInt("counter") << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::sumOfSales () {
    int empID;
    string date1, date2;
    cout << "Please enter employee ID" << endl;
    cinClearing();
    cin >> empID;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT SUM(cost) AS counter FROM transaction WHERE emp_id = ? AND transaction_date BETWEEN ? AND ?");
    pstmt->setUInt(1, empID);
    pstmt->setString(2, date1);
    pstmt->setString(3, date2);
    ResultSet *row = pstmt->executeQuery();
    row->first();
    cout << "Total sales: " << row->getUInt("counter") << endl << endl;
    delete con;
    delete pstmt;
    delete row;
}

void Database::topTen () {
    string date1, date2;
    cout << "Please enter start date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date1;
    cout << "Please enter end date (yyyy-mm-dd)" << endl;
    cinClearing();
    cin >> date2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    PreparedStatement *pstmt = con->prepareStatement("SELECT book_name FROM contain INNER JOIN transaction ON contain.order_id = transaction.order_id WHERE transaction.transaction_date BETWEEN ? AND ?");
    pstmt->setString(1, date1);
    pstmt->setString(2, date2);
    ResultSet *row = pstmt->executeQuery();
    int numOfDifBooks = (int)row->rowsCount();
    int count = 1;
    cout << "Top 10 books: " << endl;
    if(numOfDifBooks <= 10)
        while(row->next())
            cout << count++ << ". " << row->getString("book_name") << endl;
    else {
    book books[numOfDifBooks];
    row->beforeFirst();
    int i = 0;
    while(row->next())
        books[i].setBookName(row->getString("book_name"));
    pstmt = con->prepareStatement("SELECT book_name, order_id FROM contain INNER JOIN transaction ON contain.order_id = transaction.order_id WHERE transaction.transaction_date BETWEEN ? AND ?");
    pstmt->setString(1, date1);
    pstmt->setString(2, date2);
    row = pstmt->executeQuery();
    row->beforeFirst();
    while(row->next())
        for(i = 0; i < numOfDifBooks; ++i)
            if(row->getString("book_name") == books[i].getBookName())
                books[i].addBooks(1);
    for(i = 0; i < numOfDifBooks; ++ i)
        for(int j = i + 1; j < numOfDifBooks; ++j)
            if(books[i].getSold() > books[j].getSold()) {
                int temp = books[i].getSold();
                books[i].setSold(books[j].getSold());
                books[j].setSold(temp);
            }
        for(i = numOfDifBooks - 9; i <= numOfDifBooks; ++i)
            cout << count++ << ". " << books[i].getBookName() << ", Sold copies: " << books[i].getSold() << endl;
    }
    cout << endl;
    delete con;
    delete pstmt;
    delete row;
}
