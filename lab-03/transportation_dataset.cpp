#include "transportation_dataset.h"

#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "./pugixml-1.11/src/pugixml.hpp"

TransportationDataset::TransportationDataset(const char* file_path) {
  auto is_load_good = xml_file.load_file(file_path);
  if (is_load_good == false) {
    throw std::runtime_error(is_load_good.description());
  }
  dataset = xml_file.child("dataset");

  stations_number = 0;
  for (const auto& station : dataset) {
    ++stations_number;
    transportation_types.insert(station.child("type_of_vehicle").child_value());
  }
}

std::string TransportationDataset::ReplaceDotWithComma(
    const std::string& str) const {
  return std::regex_replace(str, std::regex("\\."), ",");
}

std::string TransportationDataset::Strip(const std::string& str) const {
  std::string result_str = "";
  size_t begin = 0;
  for (; begin < str.length() && str[begin] == ' '; ++begin)
    ;
  result_str = str.substr(begin, str.length() - begin);

  while (!result_str.empty() && result_str.back() == ' ') {
    result_str.pop_back();
  }

  return result_str;
}

std::vector<std::string> TransportationDataset::SplitbyComma(
    const std::string& locations) const {
  std::vector<std::string> locations_array;

  size_t i = 0;
  while (i < locations.length()) {
    const auto pos = locations.find(',', i);
    if (pos == std::string::npos) {
      locations_array.emplace_back(
          Strip(locations.substr(i, locations.length() - i)));
      return locations_array;
    }

    locations_array.emplace_back(Strip(locations.substr(i, pos - i)));
    i = pos + 1;
  }
  return locations_array;
}

std::pair<std::string, int32_t> TransportationDataset::GetMaxLocation() const {
  std::unordered_map<std::string, int32_t> location_stations;
  for (const auto& transportation_station : dataset) {
    const auto locations =
        SplitbyComma(transportation_station.child("location").child_value());
    for (const auto& location : locations) {
      auto search = location_stations.find(location);
      if (search != location_stations.end()) {
        location_stations[location]++;
      } else {
        location_stations[location] = 1;
      }
    }
  }

  int32_t max_stations = -1;
  std::string max_location = "";
  for (const auto& item : location_stations) {
    const auto cur_location = item.first;
    const auto& cur_stations = item.second;
    if (cur_stations > max_stations) {
      max_location = cur_location;
      max_stations = cur_stations;
    }
  }

  return std::make_pair(max_location, max_stations);
}

void TransportationDataset::PrintMaxLocation() const {
  const auto max_location = GetMaxLocation();
  std::cout << "Улица с наибольшим числом остановок: " << max_location.first
            << ", кол-во остановок: " << max_location.second << std::endl;
}

std::pair<std::string, int32_t> TransportationDataset::GetMaxRoute(
    const std::string& transportation_type) const {
  std::unordered_map<std::string, int32_t> route_stations;
  for (const auto& transportation_station : dataset) {
    if (transportation_station.child("type_of_vehicle").child_value() !=
        transportation_type) {
      continue;
    }
    const auto routes = SplitbyComma(ReplaceDotWithComma(
        transportation_station.child("routes").child_value()));
    for (const auto& route : routes) {
      auto search = route_stations.find(route);
      if (search != route_stations.end()) {
        route_stations[route]++;
      } else {
        route_stations[route] = 1;
      }
    }
  }

  int32_t max_stations = -1;
  std::string max_route = "";
  for (const auto& item : route_stations) {
    const auto cur_route = item.first;
    const auto& cur_stations = item.second;
    if (cur_stations > max_stations) {
      max_route = cur_route;
      max_stations = cur_stations;
    }
  }

  return std::make_pair(max_route, max_stations);
}

void TransportationDataset::PrintMaxRoutes() const {
  std::cout << "Маршрут с наибольшим количеством остановок для" << std::endl;
  for (const auto& transportation_type : transportation_types) {
    const auto max_route = GetMaxRoute(transportation_type);
    std::cout << transportation_type << ": " << max_route.first
              << ", кол-во остановок: " << max_route.second << std::endl;
  }
}

double TransportationDataset::StationsDistance(
    const double_pair& station1, const double_pair& station2) const {
  const auto phi1 = station1.first * M_PI / 180;
  const auto phi2 = station2.first * M_PI / 180;
  const auto delta_l = (station1.second - station2.second) * M_PI / 180;
  const auto R = 6371;
  const auto y = phi1 - phi2;
  const auto x = delta_l * std::cos((phi1 + phi2) / 2.);
  const auto d = R * std::sqrt(x * x + y * y);
  return d;
}

double TransportationDataset::GetRouteLength(
    const std::vector<double_pair>& stations) const {
  const int32_t not_defined = -1;
  const auto stations_number = stations.size();
  double min_route_length = not_defined;
  for (int32_t start_vertice = 0; start_vertice < stations_number;
       ++start_vertice) {
    double route_length = 0;
    std::vector<bool> visited(stations_number, false);
    int32_t visited_number = 0;

    int32_t from = start_vertice;
    visited[from] = true;
    visited_number++;


    while (visited_number < stations_number) {
      int32_t min_to = not_defined;
      for (int32_t to = 0; to < stations_number; ++to) {
        if (visited[to]) {
          continue;
        }
        if (min_to == not_defined ||
            StationsDistance(stations[from], stations[to]) <
                StationsDistance(stations[from], stations[min_to])) {
          min_to = to;
        }
      }

      route_length += StationsDistance(stations[from], stations[min_to]);

      from = min_to;
      visited[from] = true;
      visited_number++;
    }

    if (min_route_length == -1) {
      min_route_length = route_length;
      continue;
    }
    min_route_length = std::min(min_route_length, route_length);
  }

  return min_route_length;
}

std::pair<std::string, double> TransportationDataset::GetLongestRoute(
    const std::string& transportation_type) const {
  std::unordered_map<std::string, std::vector<double_pair>> route_stations;
  for (const auto& transportation_station : dataset) {
    if (transportation_station.child("type_of_vehicle").child_value() !=
        transportation_type) {
      continue;
    }
    const auto routes = SplitbyComma(ReplaceDotWithComma(
        transportation_station.child("routes").child_value()));
    const auto coordinates =
        SplitbyComma(transportation_station.child("coordinates").child_value());
    if (coordinates.size() != 2) {
      throw std::runtime_error("wrong coordinates data");
    }
    for (const auto& route : routes) {
      auto search = route_stations.find(route);
      if (search == route_stations.end()) {
        route_stations[route] = std::vector<double_pair>();
      }
      route_stations[route].push_back(
          std::make_pair(std::stod(coordinates[0]), std::stod(coordinates[1])));
    }
  }

  double max_route_length;
  std::string route_name = "";

  for (const auto& item : route_stations) {
    const auto route_length = GetRouteLength(item.second);
    if (route_name.empty()) {
      route_name = item.first;
      max_route_length = route_length;
      continue;
    }
    if (route_length > max_route_length) {
      route_name = item.first;
      max_route_length = route_length;
    }
  }

  return std::make_pair(route_name, max_route_length);
}

void TransportationDataset::PrintLongestRoutes() const {
  std::cout << "Наиболее длинный маршрут (основываясь на координатах) "
               "по отдельным видам транспорта для"
            << std::endl;
  for (const auto& transportation_type : transportation_types) {
    const auto longest_route = GetLongestRoute(transportation_type);
    std::cout << transportation_type << ": " << longest_route.first
              << ", протяженность маршрута: " << longest_route.second << " км"
              << std::endl;
  }
}
