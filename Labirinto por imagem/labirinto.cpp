#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

struct Cor {
    int r, g, b;
};

struct Cor cores[] = {
    {255, 255, 255}, //branco = nada
    {100, 100, 100}, //cinza = parede
    {255, 255, 0}, //amarelo = passagem
    {255, 0, 0}, //vermelho = fim de faze
    {0, 0, 0}, //preto = background
    {0, 0, 255}, //Azul = porta
    {0, 255, 255} //Ciano = Chave
};

void atualizarCorCasa(int boardMap[][25], int x, int y, int novaCor) {
    boardMap[y][x] = novaCor;
}

void lerMapas(char mapas[15][20]){
    strcpy(mapas[0], "labirinto1.bmp");
    strcpy(mapas[1], "labirinto2.bmp");
    strcpy(mapas[2], "labirinto3.bmp");
    strcpy(mapas[3], "labirinto4.bmp");
    strcpy(mapas[4], "labirinto5.bmp");
    strcpy(mapas[5], "labirinto6.bmp");
    strcpy(mapas[6], "labirinto7.bmp");
    strcpy(mapas[7], "labirinto8.bmp");
    strcpy(mapas[8], "labirinto9.bmp");
    strcpy(mapas[9], "labirinto10.bmp");
    strcpy(mapas[10], "labirinto11.bmp");
    strcpy(mapas[11], "labirinto12.bmp");
    strcpy(mapas[12], "labirinto13.bmp");
    strcpy(mapas[13], "labirinto14.bmp");
    strcpy(mapas[14], "labirinto15.bmp");
}

void lerCores(){
    cores[0].r = 255;
    cores[0].g = 255;
    cores[0].b = 255;
    cores[1].r = 100;
    cores[1].g = 100;
    cores[1].b = 100;
    cores[2].r = 255;
    cores[2].g = 255;
    cores[2].b = 0;
    cores[3].r = 255;
    cores[3].g = 0;
    cores[3].b = 0;
    cores[4].r = 0;
    cores[4].g = 0;
    cores[4].b = 0;
    cores[5].r = 0;
    cores[5].g = 0;
    cores[5].b = 255;
    cores[6].r = 0;
    cores[6].g = 255;
    cores[6].b = 255;
}


void carregarImagem(char *nomeArquivo, int boardMap[][25], int largura, int altura) {
    readimagefile(nomeArquivo, 0, 0, largura, altura);
    printf("\n%d, %d", largura, altura);
    int x, y;
    for (y = 0; y < altura; y++) {
        for (x = 0; x < largura; x++) {
            boardMap[y][x] = getpixel(x, y);
        }
    }
}

int valorDaCasa(int boardMap[][25], int playerX, int playerY) {
    int cor = boardMap[playerY][playerX];

    for (int i = 0; i < sizeof(cores) / sizeof(cores[0]); i++) {
        if (cor == COLOR(cores[i].r, cores[i].g, cores[i].b)) {
            return i;
        }
    }

    return -1;
}


void desenharTabuleiro(int boardMap[][25], int largura, int altura, int width, int height, bool lines) {
    cleardevice();
    int pixelWidth = 50;
    int pixelHeight = 50;

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int cor = boardMap[i][j];
            setfillstyle(SOLID_FILL, cor);
            bar(j * pixelWidth, i * pixelHeight, (j + 1) * pixelWidth, (i + 1) * pixelHeight);
        }
    }

    if(lines){
        setcolor(RGB(0,0,0));
        for(int i = 0; i <= width; i += width / 25){
            line(i, 0, i, height);

            for(int j = 0; j <= height; j += height / 15){
                line(0, j, width, j);
            }
        }
    }
}


int main() {
    int width = 1250, height = 750;
    initwindow(width, height);

    int faze = 0;
    char mapas[15][20];
    int largura = 25, altura = 15;
    int boardMap[15][25];
    bool lines = false;

    lerMapas(mapas);
    lerCores();

    carregarImagem(mapas[faze], boardMap, largura, altura);
    desenharTabuleiro(boardMap, largura, altura, width, height, lines);

    int playerX = 1, playerY = 1;

    setfillstyle(SOLID_FILL, GREEN);
    bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);

    bool keyPressed = false;
    bool chave = false;

    while (1) {
        int newPlayerX = playerX;
        int newPlayerY = playerY;
        if (GetAsyncKeyState('A') & 0x8000) {
            newPlayerX--;
            keyPressed = true;
            Sleep(100);
        }
        if (GetAsyncKeyState('D') & 0x8000) {
            newPlayerX++;
            keyPressed = true;
            Sleep(100);
        }
        if (GetAsyncKeyState('W') & 0x8000) {
            newPlayerY--;
            keyPressed = true;
            Sleep(100);
        }
        if (GetAsyncKeyState('S') & 0x8000) {
            newPlayerY++;
            keyPressed = true;
            Sleep(100);
        }
        if(GetAsyncKeyState('P') & 0x8000 && keyPressed == false){
            lines = !lines;
            desenharTabuleiro(boardMap, largura, altura, width, height, lines);
            keyPressed = true;
            Sleep(100);
        }
        if(GetAsyncKeyState('U') & 0x8000 && keyPressed == false){
            faze++;
            printf("\n%d\n", faze);
            playerX = 1;
            playerY = 1;
            if(faze == 15){
                    char text[] = "Você Venceu";
                    settextstyle(1, 0, 32);
                    int x = (width - textwidth("Você Venceu!")) / 2;
                    int y = (height - textheight("Você Venceu!")) / 2;

                    outtextxy(x, y, text);
                    Sleep(5000);
                    exit(0);
                }
            carregarImagem(mapas[faze], boardMap, largura, altura);
            desenharTabuleiro(boardMap, largura, altura, width, height, lines);
            setfillstyle(SOLID_FILL, GREEN);
            bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
            keyPressed = true;
            Sleep(100);
        }
        if (keyPressed) {

            int cellValue = valorDaCasa(boardMap, newPlayerX, newPlayerY);
            printf("%d", cellValue);

            if(cellValue == 0){
                setfillstyle(SOLID_FILL, WHITE);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
                playerY = newPlayerY;
                playerX = newPlayerX;
                setfillstyle(SOLID_FILL, GREEN);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
            }

            if(cellValue == 2){
                setfillstyle(SOLID_FILL, WHITE);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
                if (GetAsyncKeyState('A') & 0x8000) {
                    playerX = largura - 2;
                }
                else if (GetAsyncKeyState('D') & 0x8000) {
                    playerX = 1;
                }
                else if (GetAsyncKeyState('W') & 0x8000) {
                    playerY = altura - 2;
                }
                else if (GetAsyncKeyState('S') & 0x8000) {
                    playerY = 1;
                }
                setfillstyle(SOLID_FILL, GREEN);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
            }
            if(cellValue == 3){
                faze++;
                printf("\n%d\n", faze);
                playerX = 1;
                playerY = 1;
                if(faze == 15){
                    char text[] = "Você Venceu";
                    settextstyle(1, 0, 32);
                    int x = (width - textwidth("Você Venceu!")) / 2;
                    int y = (height - textheight("Você Venceu!")) / 2;

                    outtextxy(x, y, text);
                    Sleep(2000);
                    exit(0);
                }
                carregarImagem(mapas[faze], boardMap, largura, altura);
                desenharTabuleiro(boardMap, largura, altura, width, height, lines);
                setfillstyle(SOLID_FILL, GREEN);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
            }
            if(cellValue == 5 && chave == true){
                carregarImagem(mapas[faze], boardMap, largura, altura);
                desenharTabuleiro(boardMap, largura, altura, width, height, lines);
                cores[5].r = 0;
                cores[5].g = 0;
                cores[5].b = 0;
                playerY = newPlayerY;
                playerX = newPlayerX;
                setfillstyle(SOLID_FILL, GREEN);
                bar(playerX * 50 + 10, playerY * 50 + 10, playerX * 50 + 40, playerY * 50 + 40);
            }
            if(cellValue == 6){
                chave = true;
                cores[6].r = 0;
                cores[6].g = 0;
                cores[6].b = 0;
            }

            keyPressed = false;
        }
    }

    closegraph();
    return 0;
}

