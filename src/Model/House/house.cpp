#include "headers.h"
#include "house.h"
#include "geometry.h"
#include "texture.h"
#include "weather.h"
#include "lighting.h" 
#include <iostream>

void drawHouse() {
    glDisable(GL_CULL_FACE);
    GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // 后墙 (x-50, z-60)
    GenerateTrapezoidalPrism(270, 50, -60, 80, 160, 10);
    RenderTrapezoidalPrism();
    GenerateTrapezoidalPrism(430, 50, -60, -80, 160, 10);
    RenderTrapezoidalPrism();

    // 前墙 (x-50, z-60)
    GenerateTriangularPrism(270, 130, 335, 130, 335, 195, 100, 10);
    RenderTriangularPrism();
    GenerateTriangularPrism(430, 130, 365, 130, 365, 195, 100, 10);
    RenderTriangularPrism();
    GenerateTriangularPrism(335, 195, 365, 195, 350, 210, 100, 10);
    RenderTriangularPrism();

    GenerateCuboid(335, 130, 100, 30, 10, 10);
    RenderCuboid();
    GenerateCuboid(335, 170, 100, 30, 25, 10);
    RenderCuboid();
    GenerateCuboid(270, 50, 100, 20, 80, 10);
    RenderCuboid();
    GenerateCuboid(410, 50, 100, 20, 80, 10);
    RenderCuboid();
    GenerateCuboid(290, 50, 100, 30, 40, 10);
    RenderCuboid();
    GenerateCuboid(380, 50, 100, 35, 40, 10);
    RenderCuboid();
    GenerateCuboid(320, 50, 100, 15, 70, 10);
    RenderCuboid();
    GenerateCuboid(365, 50, 100, 15, 70, 10);
    RenderCuboid();
    GenerateCuboid(290, 120, 100, 140, 10, 10);
    RenderCuboid();
    GenerateCuboid(335, 110, 100, 30, 10, 10);
    RenderCuboid();

    // 左墙 (x-50, z-60)
    GenerateTrapezoidalPrism(270, 120, -60, 10, 20, 160);
    RenderTrapezoidalPrism();
    GenerateCuboid(270, 50, -60, 10, 70, 70);
    RenderCuboid();
    GenerateCuboid(270, 50, 40, 10, 70, 60);
    RenderCuboid();
    GenerateCuboid(270, 50, 10, 10, 40, 30);
    RenderCuboid();

    // 右墙 (x-50, z-60)
    GenerateTrapezoidalPrism(430, 120, -50, -10, 20, 150);
    RenderTrapezoidalPrism();
    GenerateCuboid(430, 50, -50, -10, 70, 60);
    RenderCuboid();
    GenerateCuboid(430, 50, 40, -10, 70, 60);
    RenderCuboid();
    GenerateCuboid(430, 50, 10, -10, 40, 30);
    RenderCuboid();

    disableTexture();
    glPopMatrix();

    // 房顶 (x-50, z-60)
    glPushMatrix();
    applyBrickTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateParallelogramPrism(350, 210, 350, 220, 260, 120, 260, 130, -65, 180);
    RenderParallelogramPrism();
    GenerateParallelogramPrism(350, 210, 350, 220, 440, 120, 440, 130, -65, 180);
    RenderParallelogramPrism();

    // 烟囱 (x-50, z-60)
    GenerateTrapezoidalPrism(300, 180, 10, -20, -40, 20);
    RenderTrapezoidalPrism();
    disableTexture();
    glPopMatrix();

    // 大门 (x-50, z-60)
    glPushMatrix();
    applyDarkWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateCuboid(335, 60, 100, 30, 50, 5);
    RenderCuboid();
    disableTexture();

    // 门装饰 (x-50, z-60)
    glColor3f(GRAY);
    GenerateCuboid(340, 65, 105, 20, 2, 0.5);
    RenderCuboid();
    GenerateCuboid(340, 105, 105, 20, -2, 0.5);
    RenderCuboid();
    GenerateCuboid(340, 84, 105, 20, 2, 0.5);
    RenderCuboid();
    GenerateCuboid(340, 65, 105, 2, 40, 0.5);
    RenderCuboid();
    GenerateCuboid(358, 65, 105, 2, 40, 0.5);
    RenderCuboid();

    // 棚子 (x-50, z-60)
    glPushMatrix();
    applyBrickTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateParallelogramPrism(350, 135, 350, 125, 320, 105, 320, 95, 110, 70);
    RenderParallelogramPrism();
    GenerateParallelogramPrism(350, 135, 350, 125, 380, 105, 380, 95, 110, 70);
    RenderParallelogramPrism();

    GenerateCuboid(325, 50, 170, 4, 57, 4);
    RenderCuboid();
    GenerateCuboid(375, 50, 170, -4, 57, 4);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    applyMarbleTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // 走道 (x-50, z-60)
    GenerateCuboid(335, 50, 100, 30, 10, 60);
    RenderCuboid();
    GenerateCuboid(325, 50, 110, 10, 10, 50);
    RenderCuboid();
    GenerateCuboid(365, 50, 110, 10, 10, 50);
    RenderCuboid();
    GenerateCuboid(325, 40, 110, 50, 10, 80);
    RenderCuboid();

    // 左边围栏 (x-50, z-60)
    for (int i = 0; i < 6; i++) {
        GenerateCuboid(328, 60, 110 + i * 10, 4, 30, 4);
        RenderCuboid();
    }
    GenerateCuboid(328, 90, 110, 4, 4, 58);
    RenderCuboid();

    // 右边围栏 (x-50, z-60)
    for (int i = 0; i < 6; i++) {
        GenerateCuboid(368, 60, 110 + i * 10, 4, 30, 4);
        RenderCuboid();
    }
    GenerateCuboid(368, 90, 110, 4, 4, 58);
    RenderCuboid();

    // 台阶 (x-50, z-60)
    GenerateCuboid(325, 50, 160, 50, 10, 10);
    RenderCuboid();
    GenerateCuboid(335, 50, 170, 30, 5, 10);
    RenderCuboid();

    // 地板 (x-50, z-60)
    GenerateCuboid(275, 50, -55, 150, 10, 150);
    RenderCuboid();

    // 外围边缘 (x-50, z-60)
    GenerateCuboid(265, 40, -65, 170, 23, 5);
    RenderCuboid();
    GenerateCuboid(265, 40, -60, 5, 23, 175);
    RenderCuboid();
    GenerateCuboid(435, 40, -60, -5, 23, 175);
    RenderCuboid();
    GenerateCuboid(270, 40, 110, 65, 23, 5);
    RenderCuboid();
    GenerateCuboid(430, 40, 110, -65, 23, 5);
    RenderCuboid();

    // 烟囱顶部边缘 (x-50, z-60)
    GenerateCuboid(305, 185, 5, -30, -10, 5);
    RenderCuboid();
    GenerateCuboid(305, 185, 30, -30, -10, 5);
    RenderCuboid();
    GenerateCuboid(305, 185, 10, -5, -10, 20);
    RenderCuboid();
    GenerateCuboid(280, 185, 10, -5, -10, 20);
    RenderCuboid();

    disableTexture();
    glPopMatrix();

    // 内部装饰 (x-50, z-60)
    // 床铺床板
    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(40, 40, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateCuboid(280, 60, -50, 30, 20, 3);
    RenderCuboid();
    GenerateCuboid(280, 60, -47, 30, 10, 60);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 被子
    glColor3f(WHITE);
    GenerateCuboid(280, 70, -47, 30, 10, 15);
    RenderCuboid();
    glColor3f(RED);
    GenerateCuboid(280, 70, -32, 30, 10, 45);
    RenderCuboid();

    // 沙发垫子
    glColor3f(WHITE);
    GenerateCuboid(420, 70, -10, -30, 10, 60);
    RenderCuboid();
    GenerateCuboid(420, 80, -10, -5, 12, 60);
    RenderCuboid();

    // 沙发底座
    glPushMatrix();
    applyWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(40, 40, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateCuboid(420, 60, -20, -30, 30, 10);
    RenderCuboid();
    GenerateCuboid(420, 60, 50, -30, 30, 10);
    RenderCuboid();
    GenerateCuboid(420, 60, -20, -30, 10, 80);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 架子
    glPushMatrix();
    applyDarkWoodTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);

    GenerateCuboid(420, 60, 60, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(420, 80, 60, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(420, 100, 60, -30, 2, 40);
    RenderCuboid();
    GenerateCuboid(420, 60, 60, -30, 42, 2);
    RenderCuboid();
    GenerateCuboid(420, 60, 98, -30, 42, 2);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 地毯
    glPushMatrix();
    applyCarpetTexture();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(10, 10, 1.0);
    glMatrixMode(GL_MODELVIEW);

    GenerateCuboid(290, 60, -40, 130, 1, 130);
    RenderCuboid();
    disableTexture();
    glPopMatrix();

    // 窗户边框 (x-50, z-60)
    glColor3f(BROWN);
    // 正面窗户1
    GenerateCuboid(330, 135, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(330, 170, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(330, 140, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(365, 140, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(349, 140, 110, 2, 30, 1);
    RenderCuboid();

    // 正面窗户2
    GenerateCuboid(285, 85, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(285, 120, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(285, 90, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(320, 90, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(304, 90, 110, 2, 30, 1);
    RenderCuboid();

    // 正面窗户3
    GenerateCuboid(375, 85, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(375, 120, 110, 40, 5, 1);
    RenderCuboid();
    GenerateCuboid(375, 90, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(410, 90, 110, 5, 30, 1);
    RenderCuboid();
    GenerateCuboid(394, 90, 110, 2, 30, 1);
    RenderCuboid();

    // 左面窗户
    GenerateCuboid(270, 85, 5, -1, 5, 40);
    RenderCuboid();
    GenerateCuboid(270, 125, 5, -1, -5, 40);
    RenderCuboid();
    GenerateCuboid(270, 90, 10, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(270, 90, 45, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(270, 90, 24, -1, 30, 2);
    RenderCuboid();

    // 右面窗户
    GenerateCuboid(431, 85, 5, -1, 5, 40);
    RenderCuboid();
    GenerateCuboid(431, 125, 5, -1, -5, 40);
    RenderCuboid();
    GenerateCuboid(431, 90, 10, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(431, 90, 45, -1, 30, -5);
    RenderCuboid();
    GenerateCuboid(431, 90, 24, -1, 30, 2);
    RenderCuboid();

    // 半透明窗户玻璃 (x-50, z-60)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    bool isNight = !lightingSystem.isDaytime();

    if (isNight) {
        GLfloat emission[] = { 0.9f, 0.7f, 0.1f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glColor4f(1.0f, 0.9f, 0.3f, 0.6f);
    }
    else {
        GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
        glColor4f(0.8f, 0.9f, 1.0f, 0.3f);
    }

    // 左面窗户玻璃
    GenerateCuboid(270, 90, 10, 1, 30, 30);
    RenderCuboid();
    // 右面窗户玻璃
    GenerateCuboid(430, 90, 10, -1, 30, 30);
    RenderCuboid();
    // 正面窗户1玻璃
    GenerateCuboid(335, 140, 110, 30, 30, 1);
    RenderCuboid();
    // 正面窗户2玻璃
    GenerateCuboid(290, 90, 110, 30, 30, 1);
    RenderCuboid();
    // 正面窗户3玻璃
    GenerateCuboid(380, 90, 110, 30, 30, 1);
    RenderCuboid();

    GLfloat no_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}
