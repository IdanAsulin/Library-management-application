//
//  costumer.h
//  Library_DB_app
//
//  Created by Idan Asulin on 31/07/2018.
//  Copyright © 2018 Idan Asulin. All rights reserved.
//

#ifndef costumer_h
#define costumer_h

class costumerSupplier {
private:
    int cosID, numOfBooks;
public:
    costumerSupplier () : cosID (0), numOfBooks(0) {}
    inline int getCosID () { return cosID; }
    inline int getNumOfBooks () { return numOfBooks; }
    inline void setCosID (int _cosID) { cosID = _cosID; }
    inline void addBooks (int books) { numOfBooks += books; }
};

#endif /* costumer_h */
