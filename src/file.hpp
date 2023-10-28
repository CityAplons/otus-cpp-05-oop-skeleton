#pragma once

#include "log.hpp"

#include <iostream>
#include <fstream>
#include <string>

namespace otus_gfx
{

class File
{
public:
  File(const char* path) : logger_(Log::Get()), path_(path)
  {
    logger_.Debug("[File] {} opened", path_);
    // file_.open(path_, std::ios::binary | std::ios::in | std::ios::out);
  };
  ~File()
  {
    logger_.Debug("[File] {} closed", path_);
    // file_.close();
  };

  // TODO: make proper return type like ifstream
  void Read(char* buf, std::size_t size) {
    logger_.Debug("[File] {} read {} bytes", path_, size);
    (void)buf;
  };

  void Write(const char* buf, std::size_t size) {
    logger_.Debug("[File] {} wrote {} bytes", path_, size);
    (void)buf;
  }

  void Seek(unsigned long offset) {
    logger_.Debug("[File] {} set offset {} bytes", path_, offset);
  }

private:
  Log& logger_;
  std::string path_;
  // std::ofstream file_;
};

}  // namespace otus_gfx
