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
    position = Vector2D(50,50);

    acceleration = target - position;
    acceleration.normalize();

    velocity = acceleration;
}

void Drone::draw() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,droneId);
    glPushMatrix();
    glTranslatef(position.x,position.y,1.0);
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
}

void Drone::move() {
    position = position + velocity;

    acceleration = target - position;
    acceleration.normalize();
    velocity = (velocity + acceleration);

    if (velocity.norm() > 20) {
        velocity = 0.2 * velocity;
        velocity.normalize();
        velocity = 20 * velocity;
    }
}

void Drone::updateServer(Server server) {
    target = *server.location;
}
