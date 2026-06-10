#include <stdio.h>
#include <stdlib.h>
#include <math.h>   
#include "raylib.h"

#define DRAW_AREA_WIDTH 1278
#define DRAW_AREA_HEIGHT 594
#define CELL_SIZE 18

Color textColor;

typedef struct Node Node;
typedef struct Item Item;
typedef struct Deque Deque;

//---Structs---

struct Node {
    int x;
    int y;
    float g;
    float h;
    float f;

    Node *parent;
};

struct Item {
    Node node;
    Item* prev;
    Item* next;
};

struct Deque {
    Item* first;
    Item* last;
};

//---Data---
Rectangle drawArea = { 0,0,DRAW_AREA_WIDTH,DRAW_AREA_HEIGHT };

//---Draw functions---
void DrawCells();
void Draw();

//---Util Functions---
Rectangle getCellFromMousePosition();
bool MouseInDrawArea();
float CalculateDistanceBetweenNodes(Node* source, Node* destination);


int pushFront(Deque* deque, Node node);
int pushBack(Deque* deque, Node node);
Node popFront(Deque* deque);
Node popBack(Deque* deque);
Node getFront(Deque* deque);
Node getBack(Deque* deque);



//---Debug Functions---
int printNode(Node* node);
int printDeque(Deque* deque);
void Test();



int main()
{
    InitWindow(1280, 720, "Pathfinder visualizer");
    Test();

    while (!WindowShouldClose()) {
        Draw();
    }

    CloseWindow();
	return 0;
}

void DrawCells() {
    for (int i = 0; i < DRAW_AREA_WIDTH / CELL_SIZE; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, DRAW_AREA_HEIGHT, BLACK);
    }

    for (int i = 0; i < DRAW_AREA_HEIGHT / CELL_SIZE; i++) {
        DrawLine(0, i * CELL_SIZE, DRAW_AREA_WIDTH, i * CELL_SIZE, BLACK);
    }
}

void Draw() {
    BeginDrawing();
    
    DrawRectangleLinesEx(drawArea, 3, DARKBLUE);
    ClearBackground(LIGHTGRAY);
    DrawCells();

    DrawText(TextFormat("%d; %d", GetMouseX(), GetMouseY()), 200, DRAW_AREA_HEIGHT + 20, 12, textColor);
    
    if (MouseInDrawArea()) {
        textColor = DARKGREEN;
    }
    else {
        textColor = RED;
    }

    if (MouseInDrawArea())
        DrawRectangleRec(getCellFromMousePosition(), RED);

    EndDrawing();
}

Rectangle getCellFromMousePosition() {
    Rectangle cell = { 0, 0,CELL_SIZE,CELL_SIZE };

    cell.x = ((int)(GetMouseX() / CELL_SIZE) * CELL_SIZE);
    cell.y = ((int)(GetMouseY() / CELL_SIZE) * CELL_SIZE);

    return cell;
}

bool MouseInDrawArea() {
    if (GetMouseX() < DRAW_AREA_WIDTH && GetMouseY() < DRAW_AREA_HEIGHT)
        return true;
    else
        return false;
}

float CalculateDistanceBetweenNodes(Node* source, Node* destination) {
    return sqrtf((pow(destination->x - source->x, 2) + pow(destination->y - source->y, 2)));
}

int printNode(Node* node) {
    if(node){
        printf("Node:{ X = %d; Y = %d; G = %.3f; H = %.3f; F = %.3f};\n", node->x, node->y, node->g, node->h, node->f);
        return 0;
    }
    else {
        printf("[ERROR]Error printing the node!\n Node is null!");
        return -1;
    }
}

int pushFront(Deque* deque, Node node) {
    if (deque) {
        if (deque->first) {
            Item* item = malloc(sizeof(Item));
            item->node = node;
            item->next = deque->first;
            deque->first = item;
            return 0;
        }
        else {
            Item* item = malloc(sizeof(Item));
            item->node = node;
            item->next = NULL;
            item->prev = NULL;
            deque->first = item;
            deque->last = item;
            return 0;
        }
    }
    else {
        printf("[ERROR]Deque is NULL!");
        return -1;
    }
}

int pushBack(Deque* deque, Node node) {
    if (deque) {
        if (deque->last) {
            Item* item = malloc(sizeof(Item));
            item->node = node;
            item->prev = deque->last;
            item->prev->next = item;
            item->next = NULL;
            deque->last = item;
            return 0;
        }
        else {
            Item* item = malloc(sizeof(Item));
            item->node = node;
            item->next = NULL;
            item->prev = NULL;
            deque->first = item;
            deque->last = item;
            return 0;
        }
    }
    else {
        printf("[ERROR]Deque is NULL!");
        return -1;
    }
}

Node popFront(Deque* deque) {
    Node node;

    if (deque) {
        node = deque->first->node;

        Item* temp = deque->first;
        deque->first = deque->first->next;
        free(temp);
        temp = NULL;
    }


    return node;
}

int printDeque(Deque* deque) {
    if (deque) {
        if (deque->first) {
            Item* item = deque->first;
            printNode(&item->node);
            while (item = item->next) {
                printNode(&item->node);
            }
            return 0;
        }
        else {
            printf("[WARNING]Deque is empty!");
            return 1;
        }
    }
    else {
        printf("[ERROR]Deque is NULL!");
        return -1;
    }
}

void Test() {
    //Here write all printf test code
    //WARNING! NO DRAWING! -> the call for this function is outside of drawing scope

    Deque d;
    d.first = NULL;
    d.last = NULL;

    for (int i = 0; i < 100; i++) {
        Node node = { i, 0 , 0 , 0 , 0 , NULL};
        pushFront(&d, node);
    }

    Node newNode = popFront(&d);

    printNode(&newNode);

    //printDeque(&d);
}