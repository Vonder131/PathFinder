#include "raylib.h"
#include "math.h"
#define DRAW_AREA_WIDTH 1278
#define DRAW_AREA_HEIGHT 594
#define CELL_SIZE 18

Color textColor;

typedef struct Node Node;
typedef struct Item Item;
typedef struct Deque Deque;

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

Rectangle drawArea = { 0,0,DRAW_AREA_WIDTH,DRAW_AREA_HEIGHT };

void DrawCells();
void Draw();

//---Util Functions---
Rectangle getCellFromMousePosition();
bool MouseInDrawArea();
float CalculateDistanceBetweenNodes(Node* source, Node* destination);

//---Debug Functions---
void printNode(Node* node);


int main()
{
    Node node1 = { 113, 120, 0, 0 , 0 , NULL };
    Node node2 = { 380, 920, 0, 0 , 0 , NULL };

    printf("Distance is: %.5f\n", CalculateDistanceBetweenNodes(&node1, &node2));

    InitWindow(1280, 720, "Pathfinder visualizer");

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

void printNode(Node* node) {
    printf("Node:{ X = %d; Y = %d; G = %.3f; H = %.3f; F = %.3f};\n", node->x, node->y, node->g, node->h, node->f);
}