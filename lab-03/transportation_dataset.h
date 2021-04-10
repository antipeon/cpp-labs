#ifndef TRANSPORTATIONDATASET_H
#define TRANSPORTATIONDATASET_H

#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "./pugixml-1.11/src/pugixml.hpp"

struct TransportationDataset {
  TransportationDataset(const char* file_path);

  void PrintMaxLocation() const;
  void PrintMaxRoutes() const;
  void PrintLongestRoutes() const;

 private:
  using double_pair = std::pair<double, double>;
  pugi::xml_document xml_file;
  pugi::xml_node dataset;
  size_t stations_number;
  std::set<std::string> transportation_types;

  // core functions
  std::pair<std::string, int32_t> GetMaxLocation() const;
  std::pair<std::string, double> GetLongestRoute(
      const std::string& transportation_type) const;
  std::pair<std::string, int32_t> GetMaxRoute(
      const std::string& transportation_type) const;

  // function helpers
  std::vector<std::string> SplitbyComma(const std::string& locations) const;
  std::string Strip(const std::string& str) const;
  std::string ReplaceDotWithComma(const std::string& str) const;
  double GetRouteLength(const std::vector<double_pair>& stations) const;
  double StationsDistance(const double_pair& station1,
                          const double_pair& station2) const;
};

#endif  // TRANSPORTATIONDATASET_H
