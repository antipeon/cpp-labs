#include <iostream>

#include "transportation_dataset.h"

int main() {
  const char* filepath = "./data.xml";
  TransportationDataset transport_dataset(filepath);

  transport_dataset.PrintMaxRoutes();
  std::cout << std::endl;
  transport_dataset.PrintLongestRoutes();
  std::cout << std::endl;
  transport_dataset.PrintMaxLocation();

  return 0;
}
