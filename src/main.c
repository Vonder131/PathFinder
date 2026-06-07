#include "raylib.h"
#include "math.h"
#define DRAW_AREA_WIDTH 1278
#define DRAW_AREA_HEIGHT 594
#define CELL_SIZE 18

Color textColor;

typedef struct Node Node;

struct Node {
    int x;
    int y;
    float g;
    float h;
    float f;

    Node *parent;
};

Rectangle drawArea = { 0,0,DRAW_AREA_WIDTH,DRAW_AREA_HEIGHT };

void DrawCells();
void Draw();
Rectangle getCellFromMousePosition();
bool MouseInDrawArea();
float CalculateDistanceBetweenNodes(Node* source, Node* destination);


int main()
{
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
    return 0;
}