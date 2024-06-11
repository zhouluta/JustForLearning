#include <iostream>
#include <cmath>

const int WIDTH = 41; // 控制台宽度
const int HEIGHT = 21; // 控制台高度
const int CENTER_X = WIDTH / 2; // X轴中心
const int CENTER_Y = HEIGHT / 2; // Y轴中心

void drawCircle(char canvas[HEIGHT][WIDTH], int radius, char ch) {
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                canvas[CENTER_Y + y][CENTER_X + x] = ch;
            }
        }
    }
}

void drawRing(char canvas[HEIGHT][WIDTH], int outerRadius, int innerRadius, char ch) {
    for (int y = -outerRadius; y <= outerRadius; ++y) {
        for (int x = -outerRadius; x <= outerRadius; ++x) {
            int distanceSquared = x * x + y * y;
            if (distanceSquared <= outerRadius * outerRadius && distanceSquared >= innerRadius * innerRadius) {
                canvas[CENTER_Y + y][CENTER_X + x] = ch;
            }
        }
    }
}

int main() {
    char canvas[HEIGHT][WIDTH];

    // 初始化画布
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            canvas[i][j] = ' ';
        }
    }

    // 绘制坐标轴
    for (int i = 0; i < WIDTH; ++i) {
        canvas[CENTER_Y][i] = '-';
    }
    for (int i = 0; i < HEIGHT; ++i) {
        canvas[i][CENTER_X] = '|';
    }
    canvas[CENTER_Y][CENTER_X] = '+'; // 原点

    // 绘制圆环
    drawRing(canvas, 4, 2, '*');

    // 输出画布
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << canvas[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}