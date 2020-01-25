//
// Created blocation->ygadegbe on 20/01/2020.
//
#include "Drone.h"

Drone::Drone() {
    //Drone draw
    int lx, ly;
    droneId = GlutWindow::loadTGATexture("../Images/drone50x50.tga", lx, ly);
    assert(droneId != 0);

    location = new Vector2D(50, 50);
    speed = new Vector2D();
    acceleration = new Vector2D();
    server = new Server("", new Vector2D(), "");
}

void Drone::draw(vector<Drone> drones) {
    float width = 1000;
    float height = 1000;

    updateSpeed(drones);

    location->x += speed->x;
    location->y += speed->y;

    if (location->x >= width - 50 || location->x <= 50) {
        speed->x = -speed->x;
    }

    if (location->y >= height - 50 || location->y <= 50) {
        speed->y = -speed->y;
    }

    float a = (float) (atan(speed->y / speed->x) + M_PI_2);
//    float a = M_PI_2;

    if (speed->x > 0) {
        a += M_PI;
    }


    glEnable(GL_TEXTURE_2D);
    //glColor3f(0.0f,0.0f,0.0f);

    glBindTexture(GL_TEXTURE_2D, droneId);
    glPushMatrix();
    glTranslatef(location->x, location->y, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(48.0, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(48.0, 48.0);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, 48.0);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3fv(BLACK);
    glPushMatrix();
    float centerx = location->x + 25;
    float centery = location->y + 25;
    glTranslatef(centerx, centery, 0);
    glLineWidth(1);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    float radius = 50;
    for (int i = 0; i < 21; i++) {
        glVertex2f(radius * cos(a), radius * sin(a));
        a += (float) (M_PI / 20.0);
    }
    glEnd();
    glLineWidth(1);
    glPopMatrix();

    glColor3fv(BLACK);
    glPushMatrix();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(centerx, centery);
    glVertex2f(centerx + (speed->x * 25), centery + (speed->y * 25));
    glEnd();
    glPopMatrix();

    //GlutWindow:


    glColor3fv(BLACK);
    GlutWindow::drawText(100, 100, ("ACC : (x : " + to_string(acceleration->x) + " , y : " + to_string(acceleration->y) + " ) ") ,
                         GlutWindow::ALIGN_RIGHT);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y, "SPEED : " + to_string(speed->norm()), GlutWindow::ALIGN_RIGHT);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y - 40, "Server X : " + to_string(acceleration->x),
                         GlutWindow::ALIGN_RIGHT);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y - 60, "Server Y : " + to_string(acceleration->y),
                         GlutWindow::ALIGN_RIGHT);

}

void Drone::updateServer(Server *newServer) {
//    this->server->location->x = newServer->location->x;
//    this->server->location->y = newServer->location->y;
//    Server *tmpServer = new Server("", new Vector2D(newServer->location->x, newServer->location->y), "");
    server = new Server("", new Vector2D(newServer->location->x, newServer->location->y), "");
//    this->server->location->x = tmpServer->location->x;
//    this->server->location->y = tmpServer->location->y;
}

void Drone::updateSpeed(vector<Drone> drones) {
    double dmax = 96;
    double r = 48;

//    Vector2D distance = (*(server->location) - *(this->location));
//    Vector2D tmpSpeed = 0.01 * distance;
//
//    for (auto drone:drones) {
//        if (drone.location->x != this->location->x && drone.location->y != this->location->y) {
//            Vector2D ab = *this->location - *drone.location;
//            double dab = ab.norm();
//            if (dab < r) {
//                ab.normalize();
//                tmpSpeed = tmpSpeed + ab;
//            } else if (dab < dmax) {
//                ab.normalize();
//                Vector2D f = ((dab - dmax) / (r - dmax)) * ab;
//                tmpSpeed = tmpSpeed + f;
//            }
//        }
//    }
//
//    speed->x = tmpSpeed.x;
//    speed->y = tmpSpeed.y;

    Vector2D tmpAcc = (*server->location - *this->location);
    tmpAcc.normalize();
    tmpAcc = 0.01 * tmpAcc;

    for (auto drone:drones) {
        if (drone.location->x != this->location->x && drone.location->y != this->location->y) {
            Vector2D ab = *this->location - *drone.location;
            double dab = ab.norm();
            if (dab < r) {
                ab.normalize();
                tmpAcc = tmpAcc + ab;
            } else if (dab < dmax) {
                ab.normalize();
                Vector2D f = ((dab - dmax) / (r - dmax)) * ab;
                tmpAcc = tmpAcc + f;
            }
        }
    }

    acceleration->x = tmpAcc.x;
    acceleration->y = tmpAcc.y;

    Vector2D tmpSpeed = *speed + *acceleration;

    speed->x = tmpSpeed.x;
    speed->y = tmpSpeed.y;
}

