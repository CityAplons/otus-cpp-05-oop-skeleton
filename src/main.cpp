#include "project.h"
#include "log.hpp"

using namespace otus_gfx;

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

int main(int argc, char* const argv[])
{
  struct ProjectInfo info = {};
  auto& logger = Log::Get();

  if (!logger.SetSeverityFromArgs(argc, argv))
  {
    logger.SetSeverity(Log::Severity::DEBUG);
  }

  logger.Debug("{}\t{}", info.nameString, info.versionString);

  Window gui(logger);

  gui.CreateCanvasCallback();
  gui.OpenFromFileCallback();
  gui.SaveToFileCallback();
  gui.CreatePolygonCallback();
  gui.RemovePolygonCallback();

  return 0;
}
