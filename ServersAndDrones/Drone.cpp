//
// Created blocation->ygadegbe on 20/01/2020.
//
#include "Drone.h"

Drone::Drone() {
    //Drone draw
    int lx, ly;
    droneId = GlutWindow::loadTGATexture("../Images/dronesecond100x100.tga", lx, ly);
    assert(droneId != 0);

    location = new Vector2D(50, 50);
    speed = new Vector2D();
    acceleration = new Vector2D();
    start = new Vector2D();
    server = new Server("", new Vector2D(), "");

    // average weight of a drone in kg
    weight = 0.8;
    // drone size radius
    radius = 25;
    //legal max speed of 100 mph
    maxSpeed = 44.704;
    // distance of collision activation
    dmax = radius + 96;
    // distance of max collision force activation
    r = radius + 48;
    //the thrust force strength
    thrustForceStrength =3;
    //the collison max force
    collisionForceStrength = 1;
    // smooth damping
    smoothDamping = 0.9;
}

void Drone::draw(vector<Drone> drones) {
    float width = 1000;
    float height = 1000;

    updateSpeed(drones);

    location->x += speed->x;
    location->y += speed->y;

//    if (location->x >= width - 50 || location->x <= 50) {
//        speed->x = -speed->x;
//    }
//
//    if (location->y >= height - 50 || location->y <= 50) {
//        speed->y = -speed->y;
//    }

    float a = (float) (atan(speed->y / speed->x) + M_PI_2);
//    float a = M_PI_2;

    if (speed->x > 0) {
        a += M_PI;
    }


    glEnable(GL_TEXTURE_2D);
    //glColor3f(0.0f,0.0f,0.0f);

    glBindTexture(GL_TEXTURE_2D, droneId);
    glPushMatrix();
    glTranslatef(location->x - 25, location->y-25, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(radius * 2, 0.0);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(radius * 2, radius * 2);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(0.0, radius * 2);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glColor3fv(BLACK);
    glPushMatrix();
    float centerx = location->x;
    float centery = location->y;
    glTranslatef(centerx, centery, 0);
    glLineWidth(1);
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    float rad = dmax;
    for (int i = 0; i < 21; i++) {
        glVertex2f(rad * cos(a), rad * sin(a));
        a += (float) (M_PI / 20.0);
    }
    glDisable(GL_LINE_STIPPLE);
    glEnd();
    glLineWidth(1);
    glPopMatrix();

    glColor3fv(BLACK);
    glPushMatrix();
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(centerx, centery);
    glVertex2f(centerx + (speed->x * 25), centery + (speed->y * 25));
    glEnd();
    glPopMatrix();

    glColor3fv(BLACK);
    glPushMatrix();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(centerx, centery);
    glVertex2f(server->location->x, server->location->y);
    glEnd();
    glPopMatrix();

    //GlutWindow:

    // Affichage des métriques
//
//    GlutWindow::drawText(200, 200,
//                         ("SPEED : " + to_string(speed->norm())),
//                         GlutWindow::ALIGN_RIGHT);


    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y, "speed : " + to_string( roundf((float) speed->norm() * 100) / 100), GlutWindow::ALIGN_RIGHT, GLUT_BITMAP_8_BY_13);
    GlutWindow::drawText(location->x, location->y - 20, "accel : " + to_string( roundf((float)acceleration->norm() * 100) / 100), GlutWindow::ALIGN_RIGHT, GLUT_BITMAP_8_BY_13);


    /*
    glColor3fv(BLACK);
    GlutWindow::drawText(100, 100,
                         ("ACC : (x : " + to_string(acceleration->x) + " , y : " + to_string(acceleration->y) + " ) "),
                         GlutWindow::ALIGN_RIGHT);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y - 40, "Server X : " + to_string(acceleration->x),
                         GlutWindow::ALIGN_RIGHT);

    glColor3fv(BLACK);
    GlutWindow::drawText(location->x, location->y - 60, "Server Y : " + to_string(acceleration->y),
                         GlutWindow::ALIGN_RIGHT);
                         */

}

void Drone::updateServer(Server *newServer) {
//    this->server->location->x = newServer->location->x;
//    this->server->location->y = newServer->location->y;
//    Server *tmpServer = new Server("", new Vector2D(newServer->location->x, newServer->location->y), "");
    server = new Server("", new Vector2D(newServer->location->x, newServer->location->y), "");
    start = new Vector2D(location->x, location->y);
//    this->server->location->x = tmpServer->location->x;
//    this->server->location->y = tmpServer->location->y;
}

void Drone::updateSpeed(vector<Drone> drones) {
    // Solution 1
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


//  solution 2
//    Vector2D tmpAcc = (*server->location - *this->location);
//    tmpAcc.normalize();
//    tmpAcc = 0.01 * tmpAcc;
//
//    for (auto drone:drones) {
//        if (drone.location->x != this->location->x && drone.location->y != this->location->y) {
//            Vector2D ab = *this->location - *drone.location;
//            double dab = ab.norm();
//            if (dab < r) {
//                ab.normalize();
//                tmpAcc = tmpAcc + ab;
//            } else if (dab < dmax) {
//                ab.normalize();
//                Vector2D f = ((dab - dmax) / (r - dmax)) * ab;
//                tmpAcc = tmpAcc + f;
//            }
//        }
//    }
//
//    acceleration->x = tmpAcc.x;
//    acceleration->y = tmpAcc.y;
//
//    Vector2D tmpSpeed = *speed + *acceleration;

    // Solution 3

    // drag force |df| , consider in void
    Vector2D dragForce = Vector2D();
    // weight is an altitude force on x = 0 , y = 0 ,  z = mg
    Vector2D weightForce = Vector2D();
    // lift force is an altitude force too on x = 0 , y = 0 , z = -mg
    Vector2D liftForce = Vector2D();
    // thrust force in the direction of the target
    Vector2D thrustForce = (*server->location - *this->location);
    // normalize the direction vector to get 1 as norm
    thrustForce.normalize();
    // calculate the force vector
    thrustForce = thrustForceStrength * thrustForce;

    // the result force
    Vector2D force = weightForce + liftForce + dragForce + thrustForce;

    // collision detection
    for (auto drone:drones) {
        // were drone different to the actual drone
        if (drone.location->x != this->location->x && drone.location->y != this->location->y) {
            Vector2D ab = *this->location - *drone.location;
            double dab = ab.norm();
            ab.normalize();
            ab = collisionForceStrength * ab;
            float coef;
            if (dab < r) {
                coef = 1;
            } else if (dab < dmax) {
                coef = (dab - dmax) / (r - dmax);
            }
            Vector2D collisionForce = coef * ab;
            force = force + collisionForce;
        }
    }

    Vector2D tmpAcc = (1 / weight) * force;
//    tmpAcc.normalize();
    acceleration->x = tmpAcc.x;
    acceleration->y = tmpAcc.y;

    smoothDamping = (*server->location - *this->location).norm()/(*server->location - *this->start).norm();

    Vector2D tmpSpeed = smoothDamping * (*speed + *acceleration);


    speed->x = tmpSpeed.x;
    speed->y = tmpSpeed.y;

//    cout << "SPEED : " << speed->norm() << " | ACC : " << acceleration->norm() <<   " | SMOOTH : "<< smoothDamping <<   " | VAL : "<< (smoothDamping * (speed->norm() - acceleration->norm()))  << endl;
}

