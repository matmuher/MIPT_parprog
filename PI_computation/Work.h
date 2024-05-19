#pragma once

#include <stdlib.h>
#include <time.h>

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

const double SquareArea = (RightDown.x - LeftUp.x) * (LeftUp.y - RightDown.y);

// const int GlobalSampleNum = 1000;

#ifndef GlobalSampleNum

#define GlobalSampleNum 1000

#endif

Work getWork(Worker worker)
{
  Work work{};

  work.sampleNum = GlobalSampleNum / worker.worldSize;

  const double yWidth = LeftUp.y - RightDown.y;
  const double yStep =  yWidth / worker.worldSize;

  Area workArea{
    .leftUp = Vec{LeftUp.x, RightDown.y + yStep * worker.rank + yStep},
    .rightDown = Vec{RightDown.x, RightDown.y + yStep * worker.rank}
  };

  work.area = workArea;

  return work;
}

bool initRand()
{
  srand(time(NULL));

  return true;
}

double getRandFloat()
{
  static bool isInit = initRand();

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
