#include "project.h"

#include "log.hpp"
#include "file.hpp"
#include "canvas.hpp"
#include "shapes.hpp"

#include <vector>
#include <memory>

using namespace otus_gfx;

class WindowModel
{
public:
  WindowModel() : logger_(Log::Get())
  {
    logger_.Info("[Model] created");
  }
  ~WindowModel()
  {
    logger_.Info("[Model] deleted");
  }

  unsigned GetTabsAmount()
  {
    return tabs_.size();
  }

  void AddTab(std::shared_ptr<Canvas>& canvas)
  {
    currentTab_ = canvas;
    tabs_.push_back(canvas);
    logger_.Info("[Model][{}] new canvas added", tabs_.size() - 1);
  }

  std::shared_ptr<Canvas> GetTab(unsigned id)
  {
    if (id >= tabs_.size())
    {
      logger_.Error("[Canvas] wrong id {}", id);
      return std::shared_ptr<Canvas>(nullptr);
    }

    logger_.Info("[Model][{}] canvas selected", id);
    currentTab_ = tabs_[id];
    return tabs_[id];
  }

  std::shared_ptr<Canvas> GetActiveTab()
  {
    return currentTab_;
  }

private:
  Log& logger_;
  std::vector<std::shared_ptr<Canvas>> tabs_;
  std::shared_ptr<Canvas> currentTab_;
};

class WindowView
{
public:
  WindowView() : logger_(Log::Get())
  {
    logger_.Info("[View] created");
  }
  ~WindowView()
  {
    logger_.Info("[View] deleted");
  }

  void Draw(std::string& view, IDrawable& object)
  {
    logger_.Info("[View][{}] drawcall", view);
    (void)object;  // TODO
  }

private:
  Log& logger_;
};

class WindowController
{
private:
  WindowModel model_;
  WindowView view_;
  Log& logger_;

public:
  WindowController(WindowModel&& model, WindowView&& view) : model_(model), view_(view), logger_(Log::Get())
  {
    logger_.Info("[Controller] created");
  };

  ~WindowController()
  {
    logger_.Info("[Controller] deleted");
  };

  void CreateCanvasCallback(void)
  {
    logger_.Debug("[{}] canvas creation", __PRETTY_FUNCTION__);

    std::shared_ptr<Canvas> blank = std::make_shared<Canvas>();
    model_.AddTab(blank);
  }

  void OpenFromFileCallback(const char* path)
  {
    logger_.Debug("[{}] load canvas from a file", __PRETTY_FUNCTION__);

    File savedCanvas(path);
    std::shared_ptr<Canvas> loaded = std::make_shared<Canvas>(savedCanvas);
    model_.AddTab(loaded);
  }

  void SaveToFileCallback(const char* path)
  {
    logger_.Debug("[{}] save canvas to a file", __PRETTY_FUNCTION__);

    std::shared_ptr<Canvas> current = model_.GetActiveTab();
    File fileTo(path);
    current.get()->Save(fileTo);
  }

  void CreatePolygonCallback(std::string& alias, std::vector<Position>& trace)
  {
    logger_.Debug("[{}] create polygon", __PRETTY_FUNCTION__);

    std::shared_ptr<Canvas> current = model_.GetActiveTab();
    std::shared_ptr<IDrawable> poly = std::make_shared<Polygon>(trace);
    current.get()->AddObject(alias, poly);
  }

  void RemovePolygonCallback(std::string& alias)
  {
    logger_.Debug("[{}] delete polygon", __PRETTY_FUNCTION__);

    std::shared_ptr<Canvas> current = model_.GetActiveTab();
    current.get()->RemoveObject(alias);
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

  WindowModel model;
  WindowView view;
  WindowController gui(std::move(model), std::move(view));

  // Simulating GUI callbacks
  gui.CreateCanvasCallback();
  gui.OpenFromFileCallback("test.canvas");
  gui.SaveToFileCallback("saved.canvas");
  
  std::string name("cool_polygon");
  std::vector<Position> shape{ { 0, 0 }, { 1, 1 }, { 3, 5 } };
  gui.CreatePolygonCallback(name, shape);
  gui.RemovePolygonCallback(name);

  return 0;
}
