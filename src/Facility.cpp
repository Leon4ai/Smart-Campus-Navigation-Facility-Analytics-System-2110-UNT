#include "Facility.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

void printFacility(const Facility& f) {
    std::cout << f.id << " | " << f.name << " | " << f.building << " | " << f.category << "\n";
}

FacilityDatabase::FacilityDatabase() : index(HashTable::DEFAULT_CAPACITY) {}

bool FacilityDatabase::isValidId(const std::string& id) {
    if (id.length() != 4) return false;
    if (id[0] != 'F') return false;
    for (int i = 1; i < 4; i++) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

bool FacilityDatabase::containsId(const std::string& id) const {
    int tempValue;
    return index.find(id, tempValue);
}

bool FacilityDatabase::add(const Facility& f) {
    std::string upperId = utils::toUpper(f.id);
    if (containsId(upperId)) return false;
    
    records.push_back(f);
    index.insert(upperId, (int)records.size() - 1);
    return true;
}

int FacilityDatabase::count() const {
    return (int)records.size();
}

const HashTable& FacilityDatabase::table() const {
    return index;
}

void FacilityDatabase::displayAll() const {
    if (records.empty()) {
        std::cout << "No facilities available.\n";
        return;
    }
    for (size_t i = 0; i < records.size(); i++) {
        printFacility(records[i]);
    }
    std::cout << "Total facilities: " << records.size() << "\n";
}

void FacilityDatabase::searchById(const std::string& input) const {
    std::string upperId = utils::toUpper(input);
    if (!isValidId(upperId)) {
        std::cout << "Invalid format: an ID is F followed by exactly three digits\n";
        return;
    }
    
    int val = -1;
    if (index.find(upperId, val)) {
        std::cout << "Found: ";
        printFacility(records[val]);
    } else {
        std::cout << "Not found: no facility with ID " << upperId << "\n";
    }
}

void FacilityDatabase::searchByName(const std::string& name) const {
    int matches = 0;
    for (size_t i = 0; i < records.size(); i++) {
        if (utils::equalsIgnoreCase(records[i].name, name)) {
            printFacility(records[i]);
            matches++;
        }
    }
    std::cout << "Matches: " << matches << "\n";
}

void FacilityDatabase::searchByCategory(const std::string& category) const {
    int matches = 0;
    for (size_t i = 0; i < records.size(); i++) {
        if (utils::equalsIgnoreCase(records[i].category, category)) {
            printFacility(records[i]);
            matches++;
        }
    }
    std::cout << "Matches: " << matches << "\n";
}

void FacilityDatabase::categoryReport() const {
    if (records.empty()) {
        std::cout << "No facilities available.\nTotal: 0\n";
        return;
    }
    
    struct CatData {
        std::string name;
        int count;
    };
    std::vector<CatData> categories;
    
    for (size_t i = 0; i < records.size(); i++) {
        bool found = false;
        for (size_t j = 0; j < categories.size(); j++) {
            if (utils::equalsIgnoreCase(categories[j].name, records[i].category)) {
                categories[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            CatData cd;
            cd.name = records[i].category; // Preserve first spelling
            cd.count = 1;
            categories.push_back(cd);
        }
    }
    
    std::cout << "Category Count Percentage\n";
    std::cout << "-------------------------\n";
    for (size_t i = 0; i < categories.size(); i++) {
        double pct = (double)categories[i].count / records.size() * 100.0;
        std::cout << categories[i].name << " | " << categories[i].count << " | " 
                  << std::fixed << std::setprecision(1) << pct << "%\n";
    }
    std::cout << "Total: " << records.size() << "\n";
}
