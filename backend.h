#include <stdbool.h>

enum Direction { UP, DOWN, LEFT, RIGHT };
enum Status { SUCCESS, FAILURE };
struct PointList {
  int x;
  int y;
  struct PointList* next;
};

typedef struct PointList PointList;

typedef struct {
  PointList* snake;
  PointList* foods;
  PointList* walls;
  int xmax;
  int ymax;
} Board;


bool isPlace(PointList* cell1, PointList* cell2);
enum Status moveSnake(Board* board, enum Direction dir);
PointList* nextMove(Board* board, enum Direction dir);
PointList* createCell(int x, int y);
PointList* createRandCell(int xmax, int ymax);
PointList* createSnake();
Board* createBoard(PointList* foods, PointList* snake, int xmax, int ymax);
bool isList(PointList* cell, PointList* list);
bool removeList(PointList* elt, PointList** list);
void addFood(Board* board);
