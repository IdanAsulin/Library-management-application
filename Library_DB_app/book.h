//
//  book.h
//  Library_DB_app
//
//  Created by Idan Asulin on 05/08/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
//

#ifndef book_h
#define book_h

class book {
private:
    int sold;
    string bookName;
public:
    book () : bookName(""), sold(0) {}
    inline string getBookName () { return bookName; }
    inline int getSold () { return sold; }
    inline void setBookName (string _bookName) { bookName = _bookName; }
    inline void addBooks (int books) { sold += books; }
    inline void setSold (int _sold) { sold = _sold; }
};

#endif /* book_h */
