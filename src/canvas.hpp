#pragma once

#include "file.hpp"
#include "log.hpp"

namespace otus_gfx {

class Canvas {
 private:
  /* data */
 public:
  Canvas(File& file);
  Canvas(/* args */);
  ~Canvas();
};

}  // namespace otus_gfx
