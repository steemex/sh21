#include <stdio.h>

int renderFrame(int padX1, int padY1, int padX2, int padY2, int ballX, int ballY, int score1, int score2);
int renderScore(int score1, int score2);
int checkPaddleIntersec(int ballX, int ballY, int padX, int padY);
int checkHorizIntersec(int posY);
int checkPlayer1Goal(int posX);
int checkPlayer2Goal(int posX);
int printHLine();
int renderScore(int score1, int score2);

int main() {
    int ballXstart = 41;
    int ballYstart = 13;

    int padX1 = 5;
    int padY1 = 13;

    int padX2 = 75;
    int padY2 = 13;

    int ballX = ballXstart;
    int ballY = ballYstart;

    int vectorX = 1;
    int vectorY = -1;

    int score1 = 0;
    int score2 = 0;

    char key = ' ';

    renderFrame(padX1, padY1, padX2, padY2, ballX, ballY, score1, score2);

    while (key != 'q' && score1 < 21 && score2 < 21) {
        key = getchar();

        if (key == ' ') {
            if (checkHorizIntersec(ballY + vectorY)) {
                vectorY = -vectorY;
            }

            if (checkPaddleIntersec(ballX + vectorX, ballY + vectorY, padX1, padY1)) {
                vectorX = -vectorX;
            }
            if (checkPaddleIntersec(ballX + vectorX, ballY + vectorY, padX2, padY2)) {
                vectorX = -vectorX;
            }

            ballX += vectorX;
            ballY += vectorY;

            if (checkPlayer1Goal(ballX)) {
                score1 += 1;
                ballX = ballXstart - 2;
                ballY = ballYstart;
                padY1 = 13;
                padY2 = 13;
                vectorX = -1;
            }

            if (checkPlayer2Goal(ballX)) {
                score2 += 1;
                ballX = ballXstart;
                ballY = ballYstart;
                padY1 = 13;
                padY2 = 13;
                vectorX = 1;
            }
        }

        if (key == 'a') {
            if (padY1 - 2 != 0) padY1--;
        }
        if (key == 'z') {
            if (padY1 + 2 != 26) padY1++;
        }

        if (key == 'k') {
            if (padY2 - 2 != 0) padY2--;
        }
        if (key == 'm') {
            if (padY2 + 2 != 26) padY2++;
        }

        renderFrame(padX1, padY1, padX2, padY2, ballX, ballY, score1, score2);
    }

    return 0;
}

int renderFrame(int padX1, int padY1, int padX2, int padY2, int ballX, int ballY, int score1, int score2) {
    printf("\033[0d\033[2J");
    char ballChar = '*';
    char paddleChar = '|';
    for (int y = 0; y <= 26; y++) {
        if (y == 0 || y == 26) {
            printHLine();
        } else {
            for (int x = 0; x <= 82; x++) {
                if (x == 82) {
                    printf("\n");
                } else if ((x == ballX && y == ballY)) {
                    printf("%c", ballChar);
                } else if (checkPaddleIntersec(x, y, padX1, padY1) ||
                           checkPaddleIntersec(x, y, padX2, padY2)) {
                    printf("%c", paddleChar);
                } else if (x == 40) {
                    printf("|");
                } else
                    printf(" ");
            }
        }
    }
    printf("\n");
    renderScore(score1, score2);
    return 0;
}

int checkHorizIntersec(int posY) {
    int ans = 0;
    if (posY == 0 || posY == 26) ans = 1;
    return ans;
}

int checkPaddleIntersec(int ballX, int ballY, int padX, int padY) {
    int ans = 0;
    if (ballX == padX && (ballY >= padY - 1 && ballY <= padY + 1)) ans = 1;
    return ans;
}

int printHLine() {
    for (int i = 0; i <= 81; i++) {
        printf("-");
    }
    printf("\n");
    return 0;
}

int renderScore(int score1, int score2) {
    if (score1 < 21 && score2 < 21) {
        printf("Player1: %d\n", score1);
        printf("\n");
        printf("Player2: %d", score2);
        printf("\n");
    } else {
        if (score1 >= 21) {
            printf("Player 1 won! Congratulations!\n");
        } else {
            printf("Player 2 won! Congratulations!\n");
        }
    }
    return 0;
}

int checkPlayer1Goal(int posX) {
    int ans = 0;
    if (posX == 81) ans = 1;
    return ans;
}

int checkPlayer2Goal(int posX) {
    int ans = 0;
    if (posX == 0) ans = 1;
    return ans;
}