#pragma once

#include <file.hpp>

namespace otus_gfx {

class Canvas {
 private:
  /* data */
 public:
  Canvas(File& file);
  Canvas(/* args */);
  ~Canvas();
};

Canvas::Canvas(/* args */) {}

Canvas::~Canvas() {}

}  // namespace otus_gfx
