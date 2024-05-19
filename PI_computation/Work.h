#pragma once

#include <stdlib.h>

#include "Worker.h"

struct Vec
{
  double x, y;
};

struct Area
{
  Vec leftUp;
  Vec rightDown;
};

double getXSize(Area area)
{
  return area.rightDown.x - area.leftUp.x;
}

double getYSize(Area area)
{
  return area.leftUp.y - area.rightDown.y;
}

struct Work
{
  int sampleNum;
  Area area;
};

const Work NoWork{};

const Vec LeftUp = Vec{-1., 1.};
const Vec RightDown = Vec{1., -1.};
const double sqR = 1.;

const int GlobalSampleNum = 1000;

Work getWork(Worker worker)
{
  Work work{};

  work.sampleNum = GlobalSampleNum / worker.worldSize;

  const double yWidth = LeftUp.y - RightDown.y;
  const double yStep =  yWidth / worker.worldSize;

  Area workArea{
    .leftUp = Vec{LeftUp.x,  yStep * worker.rank},
    .rightDown = Vec{RightDown.x, yStep * (worker.rank + 1)}
  };

  work.area = workArea;

  return work;
}

double getRandFloat()
{
  // TODO: add seed
  return double(rand()) / RAND_MAX;
}

Vec getRandPoint(Area area)
{
  const double xWidth = getXSize(area);
  const double yWidth = getYSize(area);

  const double xRand = getRandFloat() * xWidth;
  const double yRand = getRandFloat() * yWidth;

  Vec randPoint{
    .x = area.leftUp.x + xRand,
    .y = area.rightDown.y + yRand
  };

  return randPoint;
}

int doWork(Work work)
{
  int circleNum = 0;

  for (int sample_id = 0; sample_id < work.sampleNum; sample_id++)
  {
    Vec randPoint = getRandPoint(work.area);

    double sqDist = randPoint.x*randPoint.x +
                    randPoint.y*randPoint.y;

    if (sqDist < sqR)
    {
      circleNum++;
    }
  }

  return circleNum;
}
