#include <iostream>

#include "project.h"

namespace gui {

static void CreateCanvasCallback(void) {
  std::cout << "Invoking: canvas creation" << std::endl;
}

static void OpenFromFileCallback(void) {
  std::cout << "Invoking: load canvas from a file" << std::endl;
}

static void SaveToFileCallback(void) {
  std::cout << "Invoking: save canvas to a file" << std::endl;
}

static void CreatePolygonCallback(void) {
  std::cout << "Invoking: create polygon" << std::endl;
}

static void RemovePolygonCallback(void) {
  std::cout << "Invoking: delete polygon" << std::endl;
}

}  // namespace gui

int main(int argc, char const *argv[]) {
  struct ProjectInfo info = {};

  std::cout << info.nameString << "\t" << info.versionString << '\n';

  gui::CreateCanvasCallback();
  gui::OpenFromFileCallback();
  gui::SaveToFileCallback();
  gui::CreatePolygonCallback();
  gui::RemovePolygonCallback();

  (void)argc;
  (void)argv;
  return 0;
}
