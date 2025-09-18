#ifndef FILE_MANAGEMENT_HPP
#define FILE_MANAGEMENT_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <strstream>
#include <vector>

class FileManagement {

private:
  std::ofstream writeData;
  std::ifstream readData;

  const std::string pathDataSvg = "../assert/data.csv";
  std::vector<std::string> header;

  void writeHeader() {
    for (auto row : header) {
      this->writeData << row;
      this->writeData << std::endl;
    }
    std::cout << "header sudah di buat";
  }

public:
  FileManagement(std::vector<std::string> header) {
    this->header = header;
    // tulis header header utama nya
    this->writeHeader();
  }
  // destructor
  ~FileManagement() {
    this->writeData.close();
    this->readData.close();
    std::cout << "sumber daya untuk membaca dan menulis di close \n";
  }

public:
  /**
   * @brif kealikan data vector per barisnya
   */
  std::vector<std::string> readDataCsv() {
    this->readData.open(this->pathDataSvg);
    std::string row;
    std::vector<std::string> newData;

    // tambah 1 baris
    while (std::getline(this->readData, row)) {
      newData.push_back(row);
    }
    return newData;
  }

  /*
   * @brif mabil 1 baris yg pertama sekali di temukan
   */
  std::vector<std::string> getOneLine(std::string word) {

    std::vector<std::string> newdata;
    this->readData.open(this->pathDataSvg);
    std::string row;
    while (std::getline(this->readData, row)) {
      std::string items;
      std::istringstream stringStream(row);

      // loop pada setipa barisnya untuk collomn (pisah dengan ",")
      while (std::getline(stringStream, items, ',')) {
        if (word == items) {
          // tambahkan baris yg di dapat
          newdata.push_back(row);
        }
      }
    }
    return newdata;
  }

  /**
   * @brif : tulis data ke file csv
   * @params : data
   *
   * @example :
   *   auto data = {
   *    {"asasa","asasa","asas"},
   *    {"asasa","asasa","asas"},
   *    ...
   *  }
   *
   */
  void writeFileCSv(const std::vector<std::vector<std::string>> data) {

    this->writeData.open(pathDataSvg);

    if (this->writeData.is_open()) {
      for (const auto &row : data) {
        for (const auto &value : row) {
          this->writeData << value;
        }
        this->writeData << std::endl;
      }

    } else {
      std::cerr << " file gagal di buka";
      std::exit(EXIT_FAILURE);
    }
  }
};

#endif // !FILE_MANAGEMENT_HPP
