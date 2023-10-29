#pragma once

#include "shapes.hpp"
#include "file.hpp"
#include "log.hpp"

#include <map>
#include <memory>

namespace otus_gfx
{

class Canvas
{
public:
  Canvas() : logger_(Log::Get())
  {
    logger_.Info("[Canvas] blank canvas created");
  };

  Canvas(File& file) : logger_(Log::Get())
  {
    logger_.Info("[Canvas] canvas from file loaded");
    (void)file;
  };

  ~Canvas()
  {
    logger_.Info("[Canvas] canvas deleted");
  };

  void Save(File& file) {
    file.Write(reinterpret_cast<char*>(this), sizeof(*this));
    logger_.Info("[Canvas] active canvas saved");
  }

  void SetSize(unsigned width, unsigned height)
  {
    logger_.Info("[Canvas] resize canvas to {}x{} px", width, height);
  }

  void AddObject(std::string& alias, std::shared_ptr<IDrawable> object) {
    objects_.insert({alias, std::move(object)});
    logger_.Info("[Canvas] object {} added", alias);
  }

  std::shared_ptr<IDrawable> GetObject(std::string& alias) {
    return std::move(objects_.at(alias));
  }

  void RemoveObject(std::string& alias) {
    objects_.erase(alias);
    logger_.Info("[Canvas] object {} removed", alias);
  }

private:
  Log& logger_;
  std::map<std::string, std::shared_ptr<IDrawable>> objects_;
};

}  // namespace otus_gfx
