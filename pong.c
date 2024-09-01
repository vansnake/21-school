#include <stdio.h>

int Move_Racket1(int rPos, char key);
int Move_Racket2(int rPos, char key);
int Move_Ball(int ballX, int ballY);
void Screen_Drawing(int racket1PosY, int racket2PosY, int ballX, int ballY, int pl1_score, int pl2_score);
int ball(int ballPosX, int ballPosY, int racket1PosY, int racket2PosY, int ballMoveX, int ballMoveY);

int main() {
    int racket1PosY = 12, racket2PosY = 12;
    int ballPosX = 40, ballPosY = 10;
    int ballMoveX = -1, ballMoveY = -1;
    int XYmvXY = 0;
    int pl1_score = 0, pl2_score = 0;
    char key;


    while (1) {
        Screen_Drawing(racket1PosY, racket2PosY, ballPosX, ballPosY, pl1_score, pl2_score);
        key = getchar();
        racket1PosY = Move_Racket1(racket1PosY, key);
        racket2PosY = Move_Racket2(racket2PosY, key);
        XYmvXY = ball(ballPosX, ballPosY, racket1PosY, racket2PosY, ballMoveX, ballMoveY);
        int razdelenie;
        razdelenie = XYmvXY / 10000;
        ballMoveX = razdelenie / 10;
        ballMoveY = razdelenie % 10;
        ballPosX = (XYmvXY % 10000) / 100;
        ballPosY = XYmvXY % 100;

        if (ballMoveX == 2) {
            ballMoveX = -1;
        } 
        if (ballMoveY == 2) {
            ballMoveY = -1;
        }
        // printf("%d, %d, %d, %d", ballMoveX, ballMoveY, ballPosX, ballPosY);
    }
}

void Screen_Drawing(int racket1PosY, int racket2PosY, int ballPosX, int ballPosY, int pl1_score, int pl2_score) {
    int flag = 0;

    printf("\033[H\033[J");
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            if (i == 0 || i == 25 - 1) {
                printf("=");
            } else if (j == 2 &&
                       (i >= racket1PosY - 1 && i <= racket1PosY + 1)) {  // позиция ракетки игрок №1
                printf("]");
            } else if (j == 80 - 3 &&
                       (i >= racket2PosY - 1 && i <= racket2PosY + 1)) {  // позиция ракетки игрок №2
                printf("[");
            } else if (i == ballPosY && j == ballPosX) {
                printf("o");
            } else if (j == 44 && i == 5) {  // счет игры игрок №1
                flag = 2;
                printf("%0*d", 2, pl1_score);
            } else if (j == 35 && i == 5) {  // счет игры игрок №2
                flag = 2;
                printf("%0*d", 2, pl1_score);
            } else if (((0 < i) && (i < 25 - 1)) && (j == 0 || j == 80 - 1 || j == 80 / 2)) {
                printf("|");
            } else if (flag == 0) {
                printf(" ");
            }
            if (flag > 0) {
                flag--;
            }
        }
        printf("\n");
    }
}

int Move_Racket1(int rPos1, char key) {
    if (key == '\n') {
    } else if ((key == 'a' || key == 'A') && rPos1 <= 22 && rPos1 > 2) {
        rPos1--;
    } else if ((key == 'z' || key == 'Z') && rPos1 < 22 && rPos1 >= 2) {
        rPos1++;
    }
    return rPos1;
}
int Move_Racket2(int rPos2, char key) {
    if (key == '\n') {
    } else if ((key == 'k' || key == 'K') && rPos2 <= 22 && rPos2 > 2) {
        rPos2--;
    } else if ((key == 'm' || key == 'M') && rPos2 < 22 && rPos2 >= 2) {
        rPos2++;
    }
    return rPos2;
}

int ball(int ballPosX, int ballPosY, int racket1PosY, int racket2PosY, int ballMoveX, int ballMoveY) {

    if (ballPosX == 3 && (racket1PosY == ballPosY || racket1PosY + 1 == ballPosY || racket1PosY - 1 == ballPosY)) {
        ballMoveX *= -1;
    }
    if (ballPosX == 77 && (racket2PosY == ballPosY || racket2PosY + 1 == ballPosY || racket2PosY - 1 == ballPosY)) {
        ballMoveX *= -1;
    }
    if (ballPosY == 1 || ballPosY == 24) {
        ballMoveY *= -1;
    }
    if ((ballPosY == 1 && racket1PosY == ballPosY) || (ballPosY == 24 && ballPosX == 1 && racket1PosY == ballPosY) || (ballPosY == 2 && ballPosX == 76 && racket2PosY == ballPosY) || (ballPosY == 24 && ballPosX == 76 && racket2PosY == ballPosY)) {
        ballMoveY *= -1; ballMoveX *= -1;
    }
    if ((ballPosY == 1 && racket1PosY + 1 == ballPosY) || (ballPosY == 24 && ballPosX == 1 && racket1PosY == ballPosY + 1) || (ballPosY == 2 && ballPosX == 76 && racket2PosY == ballPosY + 1) || (ballPosY == 24 && ballPosX == 76 && racket2PosY == ballPosY + 1)) {
        ballMoveY *= -1; ballMoveX *= -1;
    }
    if ((ballPosY == 1 && racket1PosY - 1 == ballPosY) || (ballPosY == 24 && ballPosX == 1 && racket1PosY == ballPosY - 1) || (ballPosY == 2 && ballPosX == 76 && racket2PosY == ballPosY - 1) || (ballPosY == 24 && ballPosX == 76 && racket2PosY == ballPosY - 1)) {
        ballMoveY *= -1; ballMoveX *= -1;
    }


    ballPosX += ballMoveX;
    ballPosY += ballMoveY;
    int XYmvXY;

    if ((ballMoveX == 1) && (ballMoveY == 1)) {
        XYmvXY = ballMoveX * 100000 + ballMoveY * 10000 + ballPosX * 100 + ballPosY;
    }
    if ((ballMoveX == -1) && (ballMoveY == -1)) {
        XYmvXY = ballMoveX * 200000 + ballMoveY * 20000 + ballPosX * 100 + ballPosY;
    }
    if ((ballMoveY == 1) && (ballMoveX == -1)) {
        XYmvXY = ballMoveX * (-200000) + ballMoveY * 10000 + ballPosX * 100 + ballPosY;
    }
    if ((ballMoveY == -1) && (ballMoveX == 1)) {
        XYmvXY = ballMoveX * 100000 + ballMoveY * (-20000) + ballPosX * 100 + ballPosY;
    }
return XYmvXY;
}