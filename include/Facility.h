
// Purpose: Facility record and the FacilityDatabase that stores accepted
//          facilities in file order and indexes them by ID with HashTable.
// Author:  Member A
#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>
#include "HashTable.h"

struct Facility {
    std::string id;        // uppercase, e.g. F004
    std::string name;
    std::string building;  // spelling from buildings.txt
    std::string category;
};

// Prints "ID | Name | Building | Category".
void printFacility(const Facility& f);

class FacilityDatabase {
public:
    FacilityDatabase();

    // True if id (already uppercase) is F followed by exactly three digits.
    static bool isValidId(const std::string& id);

    // True if a facility with this ID is already stored (uses the hash table).
    bool containsId(const std::string& id) const;

    // Adds an accepted facility. Returns false if the ID is a duplicate.
    bool add(const Facility& f);

    int count() const;
    const HashTable& table() const;

    // Menu operations.
    void displayAll() const;                         // FAC-2
    void searchById(const std::string& input) const; // FAC-3
    void searchByName(const std::string& name) const;         // FAC-4 (Final)
    void searchByCategory(const std::string& category) const; // FAC-5 (Final)
    void categoryReport() const;                     // RPT-1 (Final)

private:
    std::vector<Facility> records;  // file order
    HashTable index;                // ID -> position in records
};

#endif
