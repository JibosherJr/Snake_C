#include "backend.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
 * Removes from the list or returns false
 */ 
bool removeList(PointList* elt, PointList** list) {
  PointList *currP, *prevP;
  prevP = NULL;
  currP = *list;
  start:
  if (currP == NULL) {
    return false;
  }
  if (isPlace(currP, elt)) {
    if (prevP == NULL) {
      *list = currP->next;
    } else {
      prevP->next = currP->next;
    }
    free(currP);
    return true;
  }
  prevP = currP;
  currP = currP->next;
  goto start;
}

enum Status moveSnake(Board* board, enum Direction dir) {
    // Check boundaries.
    PointList* beginning = nextMove(board, dir);
    if (beginning == NULL) {
        return FAILURE;
    }

    // Stops from going bacwaards
    if (board->snake->next && isPlace(beginning, board->snake->next)) {
        beginning->next = NULL;
        free(beginning);
        return SUCCESS;
  }

  // Check for collisions
    if (isList(beginning, board->snake)) {
        return FAILURE;
    }

  // Check for food
    if (isList(beginning, board->foods)) {
        beginning->next = board->snake;
        board->snake = beginning;
        removeList(beginning, &(board->foods));
        addFood(board);

        return SUCCESS;
  }

  
    beginning->next = board->snake;
    board->snake = beginning;
    PointList* end = board->snake;

    end_next_next:
        if (end->next->next) {
            end = end->next;
            goto end_next_next;
        }       
    free(end->next);
    end->next = NULL;

        return SUCCESS;
}

    bool isPlace(PointList* cell1, PointList* cell2) {
        bool flag;
        if(cell1->x == cell2->x && cell1->y == cell2->y)
            flag = true;
        else flag = false;
        return flag;
}


    PointList* nextMove(Board* board, enum Direction dir) {
    PointList* snake = board->snake;
    int new_x = snake->x;
    int new_y = snake->y;

    switch(dir) {
        case UP:
            new_y = snake->y - 1;
            break;
        case DOWN:
            new_y = snake->y + 1;
            break;
        case LEFT:
            new_x = snake->x - 1;
            break;
        case RIGHT:
            new_x = snake->x + 1;
            break;
  }

    if (new_x < 0 || new_y < 0 || new_x >= board->xmax || new_y >= board->ymax) {
        return NULL;
    } else {
        return createCell(new_x, new_y);
    }
}

    PointList* createRandCell(int xmax, int ymax) {
        return createCell(rand() % xmax, rand() % ymax);
}

    void addFood(Board* board) {
        PointList* new_food;
        while(isList(new_food, board->foods) || isList(new_food, board->snake)){
            new_food = createRandCell(board->xmax, board->ymax);
            free(new_food);
        }
            
        new_food->next = board->foods;
        board->foods = new_food;
    }



    bool isList(PointList* cell, PointList* list) {
        PointList* s = list;
        while (s) {
            if (isPlace(s, cell)) {
                return true;
                }
            s = s->next;
            }
        return false;
}



    PointList* createCell(int x, int y) {
        PointList* cell = malloc(sizeof(*cell));
        cell->x = x;
        cell->y = y;
        cell->next = NULL;
        return cell;
    }

    Board* createBoard(PointList* snake, PointList* foods, int xmax, int ymax) {
        Board* board = malloc(sizeof(*board));
        board->foods = foods;
        board->snake = snake;
        board->xmax = xmax;
        board->ymax = ymax;
        return board;
    }

    PointList* createSnake() {
        PointList* a = createCell(2,3);
        PointList* b = createCell(2,2);
        a->next = b;
        return a;
    }

