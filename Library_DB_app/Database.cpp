//
//  DB.cpp
//  Library_DB_app
//
//  Created by Idan Asulin on 29/07/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
//

#include "Database.h"

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
                          "stock INT, "
                          "global_discount_precents INT UNSIGNED, "
                          "supplier_num INT UNSIGNED "
                          ")");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Harry Potter', 100, 15, 0, 1)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Monte Cristo', 150, 453, 0, 2)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('The Ring', 80, 0, 0, 3)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Fire', 40, 33, 0, 4)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Way To Heaven', 120, 45, 0, 5)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Bible', 55, 33, 0, 6)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Computers', 33, 10, 15, 7)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('Web Development', 90, 3, 20, 7)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('C++', 96, 6, 30, 7)");
            stmt->execute("INSERT INTO book (book_name, price_before_discount, stock, global_discount_precents, supplier_num) VALUES ('C sharp', 48, 8, 10, 4)");
            
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
                          "transaction_id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, "
                          "transaction_date DATETIME, "
                          "costumer_id INT UNSIGNED, "
                          "order_status VARCHAR(25), "
                          "is_canceled BIT, "
                          "num_of_books INT UNSIGNED, "
                          "cost INT UNSIGNED, " // assume that orders cost can be only interger
                          "discount_ils INT UNSIGNED, "
                          "emp_id INT UNSIGNED "
                          ")");
            stmt->execute("INSERT INTO transaction (transaction_id, transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES (1, '2000-1-1', 1, 'Payed', 0, 1, 150, 0, 1)");
            stmt->execute("INSERT INTO transaction (transaction_date, costumer_id, order_status, is_canceled, num_of_books, cost, discount_ils, emp_id) VALUES ('2002-3-2', 1, 'Payed', 0, 1, 50, 10, 1)");
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
                          "PRIMARY KEY(order_id, book_name) "
                          ")");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (1, 'Harry Potter')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (2, 'Harry Potter')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (3, 'C++')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (4, 'C++')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (5, 'Monte Cristo')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (6, 'Monte Cristo')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (7, 'Monte Cristo')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (8, 'C++')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (9, 'C++')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (10, 'Harry Potter')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (11, 'C sharp')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (12, 'C sharp')");
            stmt->execute("INSERT INTO contain (order_id, book_name) VALUES (13, 'Way To Heaven')");
            
            stmt->execute("CREATE TABLE IF NOT EXISTS supply ( "
                          "supplier_id INT UNSIGNED, "
                          "book_name VARCHAR(25), "
                          "supply_date DATETIME, "
                          "PRIMARY KEY(supplier_id, book_name) "
                          ")");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (1, 'Harry Potter', '1999-3-9')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (1, 'C++', '2008-4-20')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (2, 'Monte Cristo', '2013-6-27')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (3, 'C sharp', '1998-5-28')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (4, 'Way To Heaven', '2011-11-11')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (5, 'Web Development', '2005-8-18')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (6, 'Web Development', '2007-3-27')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (3, 'Fire', '2007-2-10')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (3, 'Computers', '1999-8-9')");
            stmt->execute("INSERT INTO supply (supplier_id, book_name, supply_date) VALUES (5, 'Computers', '2001-2-10')");
            
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
