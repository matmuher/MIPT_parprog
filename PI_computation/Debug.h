#pragma once

void print(Worker worker)
{
  printf(
        "\n"
        "Rank: %d\n"
        "World: %d\n",
        worker.rank, worker.worldSize);
}

void print(Worker worker, Work work)
{
  printf(
        "\n"
        "Rank: %d\n"
        "Sample: %d\n"
        "LeftUp: %lg\n"
        "RightDown: %lg\n"
        "\n",
        worker.rank,
        work.sampleNum,     
        work.area.leftUp.y, work.area.rightDown.y);
}
