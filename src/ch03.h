// 第3章：フライトウェイト

#pragma once

#include <iostream>
#include "ch03-2.h"

class Tree // データ量が大きすぎて１フレームの間にGPUに送るのが難しい
{
private:
  Mesh mesh_;
  Texture bark_;
  Texture leaves_;
  Vector position_;
  double height_;
  double thickness_;
  Color barkTint_;
  Color leafTint_;
};

// Dryにする
// メッシュやテクスチャは共有できる
class TreeModel
{
private:
  Mesh mesh_;
  Texture bark_;
  Texture leaves_;
};

// 各TreeオブジェクトはTreeModelへの参照と、インスタンス固有のデータを持つ
class Tree
{
private:
  TreeModel* model_;

  Vector position_;
  double height_;
  double thickness_;
  Color barkTint_;
  Color leafTint_;
};

// 地面（タイルベース）も同様の考え方で実装できる
enum ETerrain //terrain: 地形
{
  TERRAIN_GRASS,
  TERRAIN_HILL,
  TERRAIN_RIVER
  // ...
};

// Terrainで構成されるゲームワールド

const int WIDTH = 100, HEIGHT = 100;
class World
{
public:
  int getMovementCost(int x, int y) const
  {
    switch (tiles_[x][y])
    {
    case TERRAIN_GRASS:
      return 1;
    case TERRAIN_HILL:
      return 3;
    case TERRAIN_RIVER:
      return 2;
    // ...
    }
  }

  bool isWater(int x, int y) const
  {
    return tiles_[x][y] == TERRAIN_RIVER;
  }
  
private:
  ETerrain tiles_[WIDTH][HEIGHT];
};

// 移動コストや水系地形のフラグをデータとして持つために、カプセル化する
class Terrain
{
public:
  Terrain(int movementCost, bool isWater, Texture texture)
    : movementCost_(movementCost), 
      isWater_(isWater),
      texture_(texture)
  {}

  int getMovementCost() const { return movementCost_; }
  bool isWater() const { return isWater_; }
  const Texture& getTexture() const { return texture_; }

private:
  int movementCost_;
  bool isWater_;
  Texture texture_;
};

// WorldクラスをTerrainオブジェクトの格子に変更
class World
{
  //...

private:
  Terrain* tiles_[WIDTH][HEIGHT];
};

// `World`クラスは `Terrain`オブジェクトへのポインタ格納した動的配列を持つようになった。しかし、`Terrain`のライフタイムを気にする必要が出てくる。

// →`World`クラスに直接インスタンスを持たせる。
class World
{
public:
  World()
  : grassTerrain_(1, false, GRASS_TEXTURE),
    hillTerrain_(3, false, HILL_TEXTURE),
    riverTerrain_(2, true, RIVER_TEXTURE)
  {}

  void generateTerrain();

  int getMovementCost(int x, int y) const
  {
    return getTile(x, y).getMovementCost();
  }

  const Terrain& getTile(int x, int y) const;
  
private:
  Terrain grassTerrain_;
  Terrain hillTerrain_;
  Terrain riverTerrain_;
  Terrain* tiles_[WIDTH][HEIGHT]; // 上記インスタンスへのポインタを持つことで再利用可能
  //...
};

void World::generateTerrain()
{
  // 地面を草で覆う
  for (int x = 0; x < WIDTH; ++x)
  {
    for (int y = 0; y < HEIGHT; ++y)
    {
      // 丘を点在させる
      if (rand() % 10 == 0)
      {
        tiles_[x][y] = &hillTerrain_;
      }
      else
      {
        tiles_[x][y] = &grassTerrain_;
      }
    }
  }

  // 川を生成
  int x = rand() % WIDTH;
  for (int y = 0; y < HEIGHT; ++y)
  {
    tiles_[x][y] = &riverTerrain_; //x方向に流れる川
  }
}

const Terrain& World::getTile(int x, int y) const
{
  return *tiles_[x][y];
}