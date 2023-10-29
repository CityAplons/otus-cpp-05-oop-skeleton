#pragma once

#include "log.hpp"

#include <vector>

namespace otus_gfx
{

struct Position
{
  unsigned x, y;
};

class IDrawable
{
public:
  virtual ~IDrawable(){};
  virtual void Draw(Position& pos) = 0;

private:
  Position position_;
};

class Line : public IDrawable
{
public:
  Line(std::pair<Position, Position>& local) : logger_(Log::Get())
  {
    start_ = local.first;
    end_ = local.second;
    logger_.Info("[Line] line at ({},{})({},{}) created", start_.x, start_.y, end_.x, end_.y);
  };

  ~Line()
  {
    logger_.Info("[Line] deleted");
  };

  void Draw(Position& global) override
  {
    logger_.Info("[Line] draw line at ({},{})({},{})", start_.x + global.x, start_.y + global.y, end_.x + global.x,
                 end_.y + global.y);
  }

private:
  Log& logger_;
  Position start_, end_;
};

class Polygon : public IDrawable
{
public:
  Polygon(std::vector<Position>& localVertices) : logger_(Log::Get())
  {
    logger_.Info("[Polygon] polygon with {} vertices created", localVertices.size());
    vertices_ = std::move(localVertices);
  };

  ~Polygon()
  {
    logger_.Info("[Polygon] polygon deleted");
  };

  void Draw(Position& pos) override
  {
    logger_.Info("[Polygon] draw polygon with {} vertices", vertices_.size());
    (void)pos;
  }

private:
  Log& logger_;
  std::vector<Position> vertices_;
};

}  // namespace otus_gfx
