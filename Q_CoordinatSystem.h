#pragma once
#pragma once

#include "..\..\TESTWIN32_GRAPHICAPP\Q_Vector.h"
#include "..\..\TESTWIN32_GRAPHICAPP\Q_Rect.h"
#include <math.h>
#include <string.h>

using namespace std;

double humanRound(double delta);
Vector makePerpendikularLine(const Vector& mainVector);
void drawArrows(const Vector& mainVector, const Vector& startArrowPoint);

struct coordinatSysConfig
{
    int font = 20;
    COLORREF backgroundColor;
    COLORREF axisColor;
};

class CoordinatSys
{
public:
    Rect pixRect;
    Vector coorSize_;
    Vector nullCoor_;
    Vector nullPoint; // координата в нуле
    Vector cUnits; // количество клеточек по х
    coordinatSysConfig config_;
    string xName;
    string yName;
private: 
    Rect   sysBorderPix_ = { startPosPix_, scalePix_ };
    Vector lastNDelta = {};

public: 
    Vector intepretK_ = { 1, 1 }; //= scalePix / coorSize;

    coordinatSys();
    coordinatSys(Vector startPosPix, Vector finishPosPix, Vector nullCoor);
    Vector drawFunc(const char* func);

    Vector drawCircle(const Vector& vector, double r = 10);
    void drawLine(Vector startLPos, Vector finishLPos, COLORREF color = 1);
    Vector interpret(Vector vector);
    Vector convertFromPixels(Vector vector);
    void drawAxis(Vector nDelta);
    void clean();
    Vector getXBound();
    Vector getYBound();

};

coordinatSys::coordinatSys(Vector startPosPix, Vector finishPosPix, Vector nullCoor) :
    startPosPix_(startPosPix),
    finishPosPix_(finishPosPix),
    nullCoor_(nullCoor)
{
}

coordinatSys::coordinatSys() :
    startPosPix_({ 0, 0 }),
    finishPosPix_({ (double)txGetExtentX(), (double)txGetExtentY() }),
    scalePix_({ (double)txGetExtentX(), (double)txGetExtentY() }),
    coorSize_({ (double)txGetExtentX(), (double)txGetExtentY() }),
    nullCoor_({ (double)txGetExtentX() / 2, (double)txGetExtentY() / 2 }),
    nullPoint({}),
    xName(NULL),
    yName(NULL)
{
    intepretK_.x = 1;
    intepretK_.y = -1;
}

void coordinatSys::drawLine(Vector startLPos, Vector finishLPos, COLORREF color)
{
    Vector startLPixPos = interpret(startLPos);

    Vector finishLPixPos = interpret(finishLPos);

    $s

        txSetFillColor(color);

    txLine(startLPos.x, startLPos.y, finishLPos.x, finishLPos.y);

}

Vector coordinatSys::drawCircle(const Vector& vector, double r/* = 1*/)
{
    Vector pixPos = interpret(vector);

    double rScale = 1;

    if (pixPos < finishPosPix_)
    {
        if (pixPos > startPosPix_)
        {
            txCircle(pixPos.x, pixPos.y, r * rScale);
        }
    }

    return pixPos;
}

void coordinatSys::clean()
{
    drawAxis(lastNDelta);
}

void coordinatSys::drawAxis(Vector nDelta)
{
    lastNDelta = nDelta;
    txSetFillColor(RGB(240, 240, 240));
    txRectangle(startPosPix_.x, startPosPix_.y, finishPosPix_.x, finishPosPix_.y);

    txSetColor(RGB(120, 120, 120), 3);
    txSetFillColor(RGB(120, 120, 120));
    txLine(nullCoor_.x, finishPosPix_.y, nullCoor_.x, startPosPix_.y);
    drawArrows({ nullCoor_.x - nullCoor_.x, startPosPix_.y - finishPosPix_.y }, { nullCoor_.x, startPosPix_.y });

    txLine(startPosPix_.x, nullCoor_.y, finishPosPix_.x, nullCoor_.y);
    drawArrows({ finishPosPix_.x - startPosPix_.x, -nullCoor_.y + nullCoor_.y }, { finishPosPix_.x, nullCoor_.y });
    txSetColor(RGB(200, 200, 200), 1);

    Vector roundDelta = { (humanRound(((((finishPosPix_.x) - (startPosPix_.x))) / (nDelta.x)))),
                         (humanRound(((((finishPosPix_.y) - (startPosPix_.y))) / (nDelta.y))))
    };

    char text[20] = {};

    txSelectFont("Arial", config_.font);

    Vector num = nullPoint;
    for (int x = 0; x < nDelta.x * 10; x++)
    {
        if (nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x) < finishPosPix_.x && startPosPix_.x < nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x))
        {
            sprintf(text, "%lg", num.x);
            txLine(nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), finishPosPix_.y, nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), startPosPix_.y);
            txTextOut(nullCoor_.x + ((num.x - nullPoint.x) * intepretK_.x), nullCoor_.y, text);
        }
        if (nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x) < finishPosPix_.x && startPosPix_.x < nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x))
        {
            sprintf(text, "%lg", -num.x);
            txLine(nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), finishPosPix_.y, nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), startPosPix_.y);
            txTextOut(nullCoor_.x - ((num.x - nullPoint.x) * intepretK_.x), nullCoor_.y, text);
        }

        num.x += roundDelta.x;
    }

    for (int y = 0; y < nDelta.y * 10; y++)
    {

        if (nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y) < finishPosPix_.y && startPosPix_.y < nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y))
        {
            sprintf(text, "%lg", num.y);
            txTextOut(nullCoor_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y), text);
            txLine(startPosPix_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y), finishPosPix_.x, nullCoor_.y + ((num.y - nullPoint.y) * intepretK_.y));
        }

        if (nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y) < finishPosPix_.y && startPosPix_.y < nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y))
        {
            sprintf(text, "%lg", num.y);
            txTextOut(nullCoor_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y), text);
            txLine(startPosPix_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y), finishPosPix_.x, nullCoor_.y - ((num.y - nullPoint.y) * intepretK_.y));
        }

        num.y += roundDelta.y;
    }

    if (xName)
    {
        txSetTextAlign(TA_RIGHT);
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txTextOut(finishPosPix_.x - 5, nullCoor_.y + 5, xName);
    }

    if (yName)
    {
        txSetTextAlign(TA_RIGHT);
        txSetColor(TX_BLACK);
        txSetFillColor(TX_BLACK);
        txTextOut(nullCoor_.x - 5, startPosPix_.y, yName);
    }
}

void drawArrows(const Vector& mainVector, const Vector& finishPoint)
{
    Vector perpendicular1 = makePerpendikularLine(mainVector);
    Vector perpendicular2 = perpendicular1 * -1;

    Vector arrow1 = perpendicular1 * 0.01 - mainVector * 0.02;
    Vector arrow2 = perpendicular2 * 0.01 - mainVector * 0.02;

    Vector arrow1finishPoint = ((arrow1)+finishPoint);
    Vector arrow2finishPoint = ((arrow2)+finishPoint);

    txLine(finishPoint.x, finishPoint.y, arrow1finishPoint.x, arrow1finishPoint.y);
    txLine(finishPoint.x, finishPoint.y, arrow2finishPoint.x, arrow2finishPoint.y);
}

Vector makePerpendikularLine(const Vector& mainVector)
{
    Vector perpendikularLine = {};
    perpendikularLine.x = mainVector.y;
    perpendikularLine.y = -(mainVector.x);

    return perpendikularLine;
}

double humanRound(double delta)
{
    /*
    * 0.1 -> 0.1
    * 0.12 -> 0.1
    * 0.2  -> .
    * 0.23 -> 0.25
    * 0.25 -> 0.25
    * 0.28 -> 0.25
    * 0.3  -> 0.25
    * 0.35 - >0.5
    * 0.4  0.5
    * 0.5  0.5
    * 0.6  0.5
    * 0.7  1
    * 0.8  1
    * 0.9  1
    * 3.14 exp:1
    *
    */

    delta = fabs(delta);
    double exp = log10(delta);
    double mantissa = delta / (pow(10, ceil(exp)));

    if (mantissa < 0.15) mantissa = 0.1;
    if (0.15 <= mantissa && mantissa < 0.23) mantissa = 0.2;
    if (0.23 <= mantissa && mantissa < 0.35) mantissa = 0.25;
    if (0.35 <= mantissa && mantissa < 0.65) mantissa = 0.5;
    if (0.65 <= mantissa && mantissa <= 1)   mantissa = 1;

    return mantissa * pow(10, ceil(exp));
}

Vector coordinatSys::interpret(Vector vector)
{
    return nullCoor_ + (intepretK_ * (vector - nullPoint));
}

Vector coordinatSys::convertFromPixels(Vector vector)
{
    Vector answer = {};
    answer = ((vector - nullCoor_) / intepretK_) + nullPoint;
    return answer;
}

Vector coordinatSys::getXBound()
{
    Vector minAnswer = convertFromPixels(startPosPix_);
    Vector maxAnswer = convertFromPixels(finishPosPix_);

    Vector answer = {};
    answer.x = std::min(minAnswer.x, maxAnswer.x);
    answer.y = std::max(minAnswer.x, maxAnswer.x);
    return answer;
}

Vector coordinatSys::getYBound()
{
    Vector minAnswer = convertFromPixels(startPosPix_);
    Vector maxAnswer = convertFromPixels(finishPosPix_);

    Vector answer = {};
    answer.x = std::min(minAnswer.y, maxAnswer.y);
    answer.y = std::max(minAnswer.y, maxAnswer.y);
    return answer;
}
