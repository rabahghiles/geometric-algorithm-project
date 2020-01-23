//
// Created by Kwabena Bamfo on 23/01/2020.
//

#include "Drone.h"
#include <glutWindow.h>

Drone::Drone() {
    int lx, ly;
    droneId = GlutWindow::loadTGATexture("../Textures/drone_image.tga",lx,ly);
    width = 48.0;
    height = 48.0;
    motion = new Vector2D(50,50);
}

void Drone::draw() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,droneId);
    glPushMatrix();
    glTranslatef(motion->x,motion->y,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(width,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(width,height);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,height);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    if(motion->x == 221 && motion->y == 128) {
        motion->x -= 10;
        motion->y -= 10;
    } else {
        motion->x++;
        motion->y++;
    }
}

void Drone::move() {

}
