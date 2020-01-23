//
// Created by Kwabena Bamfo on 27/12/2019.
//

#ifndef SERVERSANDDRONES_FIELDDRAW_H
#define SERVERSANDDRONES_FIELDDRAW_H


#include <glutWindow.h>

#include "Field.h"

class FieldDraw: public GlutWindow {
private:
    std::string filename;
    Field *field;
    GLuint droneId;
public:
    FieldDraw(const string& title, int argc, char **argv, unsigned int width, unsigned int height);

    void onStart() override;
    void onDraw() override;
    void onQuit() override;
    void onMouseMove(double cx,double cy) override;
    void onKeyPressed(unsigned char c,double x,double y) override;

};


#endif //SERVERSANDDRONES_FIELDDRAW_H
