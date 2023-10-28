#include "project.h"
#include "log.hpp"
#include "gui.hpp"

#include <unistd.h>

static otus_gfx::Log::Severity GetSeverityFromArgs(int argc, char* const argv[], otus_gfx::Log::Severity previous)
{
  int opt, parsed;
  otus_gfx::Log::Severity set = previous;
  while ((opt = getopt(argc, argv, "d:")) != -1)
  {
    switch (opt)
    {
      case 'd':
        parsed = std::atoi(optarg);
        break;

      default:
        break;
    }
  }

  if (parsed <= otus_gfx::Log::Severity::DEBUG && parsed >= otus_gfx::Log::Severity::ERROR)
  {
    set = static_cast<otus_gfx::Log::Severity>(parsed);
  }

  return set;
}

int main(int argc, char* const argv[])
{
  using namespace otus_gfx;

  struct ProjectInfo info = {};
  auto& logger = Log::Get();

  auto severityDefault = Log::Severity::DEBUG;
  severityDefault = GetSeverityFromArgs(argc, argv, severityDefault);

  logger.SetSeverity(severityDefault);
  logger.Debug("{}\t{}", info.nameString, info.versionString);

  Window gui(logger);

  gui.CreateCanvasCallback();
  gui.OpenFromFileCallback();
  gui.SaveToFileCallback();
  gui.CreatePolygonCallback();
  gui.RemovePolygonCallback();

  return 0;
}
