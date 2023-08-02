#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 4

struct Boundary {
    int x;
    int y;
    int width;
    int height;
};

// Representing a point
struct Point {
    int x;
    int y;
};

// Node Structure
struct QuadNode {
    struct Boundary boundary;
    struct Point* points[MAX_CAPACITY];
    int numPoints;
    struct QuadNode* children[4];
};

// Creating a new node
struct QuadNode* createQuadNode(struct Boundary boundary) {
    struct QuadNode* newNode = (struct QuadNode*)malloc(sizeof(struct QuadNode));
    newNode->boundary = boundary;
    newNode->numPoints = 0;
    for (int i = 0; i < MAX_CAPACITY; i++) {
        newNode->points[i] = NULL;
    }
    for (int i = 0; i < 4; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

int isPointInBoundary(struct Point* point, struct Boundary boundary) {
    return (point->x >= boundary.x && point->x < boundary.x + boundary.width &&
            point->y >= boundary.y && point->y < boundary.y + boundary.height);
}

void splitQuadNode(struct QuadNode* node) {
    int subWidth = node->boundary.width / 2;
    int subHeight = node->boundary.height / 2;
    int x = node->boundary.x;
    int y = node->boundary.y;

    node->children[0] = createQuadNode((struct Boundary){x, y, subWidth, subHeight});
    node->children[1] = createQuadNode((struct Boundary){x + subWidth, y, subWidth, subHeight}); 
    node->children[2] = createQuadNode((struct Boundary){x, y + subHeight, subWidth, subHeight});
    node->children[3] = createQuadNode((struct Boundary){x + subWidth, y + subHeight, subWidth, subHeight});
}

// Inserting a point in Quadtree
void insertPoint(struct QuadNode* node, struct Point* point) {
    if (!isPointInBoundary(point, node->boundary)) {
        return;
    }

    if (node->numPoints < MAX_CAPACITY) {
        node->points[node->numPoints++] = point;
        return;
    }

    if (node->children[0] == NULL) {
        splitQuadNode(node);
    }

    for (int i = 0; i < 4; i++) {
        insertPoint(node->children[i], point);
    }
}

// Initializing Quadtree
struct QuadNode* createQuadtree(struct Boundary boundary) {
    struct QuadNode* root = createQuadNode(boundary);
    return root;
}

// Print points in Quad Tree
void printPoints(struct QuadNode* node) {
    for (int i = 0; i < node->numPoints; i++) {
        printf("(%d, %d) ", node->points[i]->x, node->points[i]->y);
    }
    printf("\n");

    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            printPoints(node->children[i]);
        }
    }
}

// Freeing Memory
void freeQuadtree(struct QuadNode* node) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < node->numPoints; i++) {
        free(node->points[i]);
    }

    for (int i = 0; i < 4; i++) {
        freeQuadtree(node->children[i]);
    }

    free(node);
}

int main() {
    struct QuadNode* root = createQuadtree((struct Boundary){0, 0, 8, 8});

    struct Point* p1 = (struct Point*)malloc(sizeof(struct Point));
    p1->x = 2;
    p1->y = 3;
    insertPoint(root, p1);

    struct Point* p2 = (struct Point*)malloc(sizeof(struct Point));
    p2->x = 5;
    p2->y = 6;
    insertPoint(root, p2);

    struct Point* p3 = (struct Point*)malloc(sizeof(struct Point));
    p3->x = 7;
    p3->y = 1;
    insertPoint(root, p3);

    printPoints(root);

    freeQuadtree(root);

    return 0;
}
