
// Purpose: Reads and validates the four data files, printing a warning for each
//          rejected record and a load summary after each file.
// Author:  Shared work (all members)
#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include "CampusGraph.h"
#include "Facility.h"
#include "DepartmentTree.h"

namespace loader {

void loadBuildings(const std::string& path, CampusGraph& graph);
void loadConnections(const std::string& path, CampusGraph& graph);
void loadFacilities(const std::string& path, const CampusGraph& graph, FacilityDatabase& db);
void loadDepartments(const std::string& path, DepartmentTree& tree);

} // namespace loader

#endif
