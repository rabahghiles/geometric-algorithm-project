//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "Server.h"

void Server::draw() {

    int size = 48;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, serverId);
    glPushMatrix();
    glTranslatef(this->location->x, this->location->y, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(size, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(size, size);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, size);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x + size / 2, location->y + size + 10, this->city, GlutWindow::ALIGN_CENTER,
                         GLUT_BITMAP_8_BY_13);
}

bool Server::operator==(const Server &t) const {
    return (t.location->x == location->x && t.location->y == location->y);
}
