#pragma once

#include "log.hpp"

namespace otus_gfx
{
class Window
{
private:
  Log& logger_;

public:
  Window(Log& logger) : logger_(logger)
  {
    logger_.Info("[Window] created");
  };
  ~Window()
  {
    logger_.Info("[Window] deleted");
  };

  void CreateCanvasCallback(void)
  {
    logger_.Debug("[{}] canvas creation", __PRETTY_FUNCTION__);
  }

  void OpenFromFileCallback(void)
  {
    logger_.Debug("[{}] load canvas from a file", __PRETTY_FUNCTION__);
  }

  void SaveToFileCallback(void)
  {
    logger_.Debug("[{}] save canvas to a file", __PRETTY_FUNCTION__);
  }

  void CreatePolygonCallback(void)
  {
    logger_.Debug("[{}] create polygon", __PRETTY_FUNCTION__);
  }

  void RemovePolygonCallback(void)
  {
    logger_.Debug("[{}] delete polygon", __PRETTY_FUNCTION__);
  }
};

}  // namespace otus_gfx
