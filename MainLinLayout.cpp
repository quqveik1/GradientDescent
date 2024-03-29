#pragma once
#include "MainLinLayout.h"
#include <thread>
#include <LinearLayout.cpp>
#include <iostream>
#include "CustomRCoordinatSystemWindow.cpp"
#include "MultiLayCoordinatSystemWindow.cpp"


double MainLinLayout::currOriginalK = 5;
double MainLinLayout::currOriginalB = 7;

MainLinLayout::MainLinLayout(AbstractAppData* _app, Vector _startPos) :
    LinearLayout(_app, _startPos, LinearLayout::FLAG_VERTICAL),
    topSystem(_app),
    bottomSystem(_app),
    downLinLayout(_app, {}, LinearLayout::FLAG_HORIZONTAL),
    backGroundComputation(_app),
    suggestedCoeff(_app),
    answerCoeff(_app),
    topDescribtions(_app, {},  LinearLayout::FLAG_VERTICAL),
    topDescribtion1(_app),
    topDescribtion2(_app),
    topDescribtion3(_app),
    bottomDescribtions(_app, {}, LinearLayout::FLAG_VERTICAL),
    bottomDescribtion1(_app),
    bottomDescribtion2(_app),
    graphicInfoButton(_app)
{
    initCoordinats();

    initDescribtions();

    initDownLinLayout();

    startMonteCarloComputation();
}

void MainLinLayout::initCoordinats()
{
    topSystem.setCCells({ 20, 20 });
    topSystem.pixNullPercantage = { 0.5, 0.5 };
    topSystem.onSize({}, { 0, 0, 50, 500 });
    topSystem.setAxisXName("X");
    topSystem.setAxisYName("Y");

    LinearLayoutInfo* topInfo = new LinearLayoutInfo();
    topInfo->margin = Rect{ 0, 0, 0, 10 };
    topSystem.setLayoutInfo(topInfo);

    topSystem.setMatchParentX(true);
    topSystem.addLay();
    addWindow(topSystem);

    bottomSystem.setCellNull({ 0, 6.8 });
    bottomSystem.setCCells({ 12, 0.5 });
    bottomSystem.onSize({}, { 0, 0, 50, 500 });
    bottomSystem.setMatchParentX(true);
    bottomSystem.setOnClickListener(this);
    bottomSystem.setAxisXName("K");
    bottomSystem.setAxisYName("B");
    bottomSystem.addLay();
    addWindow(bottomSystem);
}

void MainLinLayout::initDescribtions()
{
    addWindow(topDescribtions);

    topDescribtion1.setColor(C_TRANSPARENT);
    topDescribtion1.needTransparencyOutput = true;
    topDescribtion1.setFont(20);
    topDescribtion1.setWrapStatus(1);
    topDescribtion1.setFormat(DT_LEFT);
    topDescribtion1.setText("������� - ������������ ������ � �����");
    topDescribtions.addWindow(topDescribtion1);

    topDescribtion2.setColor(C_TRANSPARENT);
    topDescribtion2.needTransparencyOutput = true;
    topDescribtion2.setFont(20);
    topDescribtion2.setWrapStatus(1);
    topDescribtion2.setFormat(DT_LEFT);
    topDescribtion2.setText("������� - ���������� ������");
    topDescribtions.addWindow(topDescribtion2);

    topDescribtion3.setColor(C_TRANSPARENT);
    topDescribtion3.needTransparencyOutput = true;
    topDescribtion3.setFont(20);
    topDescribtion3.setWrapStatus(1);
    topDescribtion3.setFormat(DT_LEFT);
    topDescribtion3.setText("������� - ������, ����������� �� ������� ��� �������������");
    topDescribtions.addWindow(topDescribtion3);

    addWindow(bottomDescribtions);

    bottomDescribtion1.setColor(C_TRANSPARENT);
    bottomDescribtion1.needTransparencyOutput = true;
    bottomDescribtion1.setFont(20);
    bottomDescribtion1.setWrapStatus(1);
    bottomDescribtion1.setFormat(DT_LEFT);
    bottomDescribtion1.setText("����� - ����������� ����������");
    bottomDescribtions.addWindow(bottomDescribtion1);

    bottomDescribtion2.setColor(C_TRANSPARENT);
    bottomDescribtion2.needTransparencyOutput = true;
    bottomDescribtion2.setFont(20);
    bottomDescribtion2.setFormat(DT_LEFT);
    bottomDescribtion2.setWrapStatus(1);
    bottomDescribtion2.setText("������� - ������� ���������� ����������");
    bottomDescribtions.addWindow(bottomDescribtion2);
}

void MainLinLayout::initDownLinLayout()
{
    addWindow(downLinLayout);
    downLinLayout.setMatchParentX(true);

    backGroundComputation.setText("��� ������� �����");
    backGroundComputation.setFont(30);
    backGroundComputation.setWrapStatus(1);
    downLinLayout.addWindow(backGroundComputation);

    static char suggestedCoeffText[MAX_PATH]{};
    Vector suggestedCoefVector = { currOriginalK, currOriginalB };
    sprintf(suggestedCoeffText, "���������� ����������: %s", suggestedCoefVector.getStr());
    suggestedCoeff.setText(suggestedCoeffText);
    suggestedCoeff.setFont(30);
    suggestedCoeff.setWrapStatus(1);
    downLinLayout.addWindow(suggestedCoeff);

    answerCoeff.setText("������ ���� ���");
    answerCoeff.setFont(30);
    answerCoeff.setWrapStatus(1);
    downLinLayout.addWindow(answerCoeff);

    graphicInfoButton.setText("��� ��� �� �������?");
    graphicInfoButton.setFont(30);
    graphicInfoButton.setWrapStatus(1);
    downLinLayout.addWindow(graphicInfoButton);
}

void MainLinLayout::draw()
{
    int timeBefore = clock();

    LinearLayout::draw();

    int timeAfter = clock();
    int delta = timeAfter - timeBefore;
}

void MainLinLayout::onMessageRecieve(const char* name, void* data)
{
    Vector clickedCellPos = *(Vector*)data;
    if (!strcmp(name, "1"))
    {
        onCertainPointSelection(clickedCellPos);
    }  
    if (!strcmp(name, "2"))
    {
        
        thread gradientDescentThread(&MainLinLayout::startGradientDescent, this, clickedCellPos);
        gradientDescentThread.detach();
    }
}

void MainLinLayout::startGradientDescent(Vector _startPos)
{
    static bool isWorking = false;
    if (isWorking) return;
    isWorking = true;
    bottomSystem.clearLay(gradientCoorBottomSystemIndex);
    gradientDescentPos = _startPos;

    bottomSystem.addPoint(gradientDescentPos, gradientDescentColor, gradientDescentR, gradientCoorBottomSystemIndex);

    int finishPos = (int)topSystem.getCoordinatLay(gradientLay)->size();

    Vector learning_rate = {0.0001, 0.000001};
    int iterations = 100;
    for (int i = 0; i < iterations; i++)
    {
        if (app->getAppCondition() == 0) break;
        double currQuadraticDelta = calcTotalQuadratic(gradientDescentPos.x,                   gradientDescentPos.y,                   sinFnc, 0, finishPos, computingQuadraticDeltaPointsIncrementDelta, topSystem);
        double dxQuadraticDelta =   calcTotalQuadratic(gradientDescentPos.x + gradientDelta.x, gradientDescentPos.y,                   sinFnc, 0, finishPos, computingQuadraticDeltaPointsIncrementDelta, topSystem);
        double dyQuadraticDelta =   calcTotalQuadratic(gradientDescentPos.x,                   gradientDescentPos.y + gradientDelta.y, sinFnc, 0, finishPos, computingQuadraticDeltaPointsIncrementDelta, topSystem);
        
        double xDerivative = (dxQuadraticDelta - currQuadraticDelta) / gradientDelta.x;
        double yDerivative = (dyQuadraticDelta - currQuadraticDelta) / gradientDelta.y;

        gradientDescentPos.x -= learning_rate.x * xDerivative;
        gradientDescentPos.y -= learning_rate.y * yDerivative;

        bottomSystem.addPoint(gradientDescentPos, gradientDescentColor, gradientDescentR, gradientCoorBottomSystemIndex);
    }

    isWorking = false;
    cout << "gradientDescentPos: " << gradientDescentPos << endl;
}

void MainLinLayout::onCertainPointSelection(Vector clickedCellPos)
{
    topSystem.clearLay(suggestedOddsLayIndex);
    countOriginalFnc();
    if(wasAnswerFinded) computeFncOnTopSystem(answerK, answerB, suggestedFncColor);
    computeFncOnTopSystem(clickedCellPos.x, clickedCellPos.y, userSelectedFncColor);
    invalidateButton();
}

int MainLinLayout::onSize(Vector managerSize, Rect _newRect)
{
    int res1 = LinearLayout::onSize(managerSize, _newRect);
    Vector _size = getSize();
    downLineSize = _size * 0.1;
    downLineSize.x = _size.x;

    topSystem.onSize(_size, { 0, 0, topSystem.getSize().x, (_size.y - downLineSize.y) * 0.5 });

    bottomSystem.onSize(_size, { 0, 0, bottomSystem.getSize().x, (_size.y - downLineSize.y) * 0.5 });                                                                                                                     

    downLinLayout.onSize(_size, { {}, downLineSize });

    int res2 = LinearLayout::onSize(managerSize, _newRect);

    topDescribtions.MoveWindowTo(topSystem.rect.pos);
    bottomDescribtions.MoveWindowTo(bottomSystem.rect.pos);
    downLinLayout.MoveWindowTo({ bottomSystem.rect.pos.x, bottomSystem.rect.finishPos.y });

    return res2 + res1;
}

double MainLinLayout::originalSinFnc(double x)
{
    return sinFnc(currOriginalK, currOriginalB, x);
}

double MainLinLayout::sinFnc(double k, double b, double x)
{
    /// k - A, B - f(�������)
    return k * sin(b * x);
}

void MainLinLayout::changeAndPrintNewMaxOrMinDelta(double* curminMaxDelta, double currDelta, int* currIndex, COLORREF _color)
{
    if (*currIndex >= 0)
    {
        COLORREF _maxQuadraticDeltaColor = getQuadraticDeltaColor(*curminMaxDelta);
        bottomSystem.setPointColor(*currIndex, _maxQuadraticDeltaColor);
        bottomSystem.setPointR(*currIndex, 0);
    }
    *curminMaxDelta = currDelta;
    *currIndex = (int)bottomSystem.getPointsSize() - 1;

    bottomSystem.setPointColor(*currIndex, _color);
    bottomSystem.setPointR(*currIndex, maxMinDeltaR);
}

double MainLinLayout::calcTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step)
{
    double answer = 0;
    for (double x = start; x < finish; x += step)
    {
        double quadraticDelta = calcQuadratic(k, b, x, fnc, originalFnc);
        answer += quadraticDelta;
    }
    return answer;
}

double MainLinLayout::calcTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), int start, int finish, int step, MultiLayCoordinatSystemWindow& lay)
{
    double answer = 0;
    for (int index = start; index < finish; index += step)
    {
        double quadraticDelta = calcQuadratic(k, b, index, fnc, lay);
        answer += quadraticDelta;
    }
    return answer;
}

double MainLinLayout::calcAndPrintTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step)
{
    double currQuadraticDelta = 0;

    currQuadraticDelta = calcTotalQuadratic(k, b, fnc, originalFnc, start, finish, step);
    COLORREF quadraticDeltaColor = getQuadraticDeltaColor(currQuadraticDelta);
    Vector point = { k, b };
    bottomSystem.addPoint(point, quadraticDeltaColor, 0, gradientLay, false);

    return currQuadraticDelta;
}

double MainLinLayout::calcAndPrintTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), int start, int finish, int step, MultiLayCoordinatSystemWindow& lay)
{
    double currQuadraticDelta = 0;

    currQuadraticDelta = calcTotalQuadratic(k, b, fnc, start, finish, step, lay);
    COLORREF quadraticDeltaColor = getQuadraticDeltaColor(currQuadraticDelta);
    Vector point = { k, b };
    bottomSystem.addPoint(point, quadraticDeltaColor, 0, gradientLay, false);

    return currQuadraticDelta;
}

void MainLinLayout::threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    int detalisationK = 1000;
    int kDelta = (int)abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = (int)(abs(bBound.delta()) * (double)detalisationK);
    double bStart = bBound.x * detalisationK;

    Vector topCellXBound = topSystem.getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();

    double xDelta = abs(topCellXBoundLen / cQuadraticDeltaCountingPoints);

    for (int i = 0; i < cCountingCoef; i++)
    {
        if (!app->getAppCondition()) break;      
        double _k = ((rand() % kDelta) + kStart) / detalisationK;
        double _b = ((rand() % bDelta) + bStart) / detalisationK;

        double currQuadraticDelta = calcAndPrintTotalQuadratic(_k, _b, fnc, originalFnc, topCellXBound.x, topCellXBound.y, xDelta);

        scoped_lock lock1(maxQuadraticDeltaMutex);
        scoped_lock lock2(minQuadraticDeltaMutex);
        if (isSmaller(maxQuadraticDelta, currQuadraticDelta))
        {
            changeAndPrintNewMaxOrMinDelta(&maxQuadraticDelta, currQuadraticDelta, &maxQuadraticDeltaIndex, maxDeltaColor);
        }

        if (isBigger(minQuadraticDelta, currQuadraticDelta))
        {
            *k = _k;
            *b = _b;

            changeAndPrintNewMaxOrMinDelta(&minQuadraticDelta, currQuadraticDelta, &minQuadraticDeltaIndex, minDeltaColor);
        }
    }
    wasAnswerFinded = true;
    computeFncOnTopSystem(*k, *b, suggestedFncColor);

    invalidateButton();
    cout << "FinishedCountGraientMap\n";
}

void MainLinLayout::threadCoeffFinderWithUnknownFnc(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x))
{
    int detalisationK = 1000;
    int kDelta = (int)abs(kBound.delta()) * detalisationK;
    double kStart = kBound.x * detalisationK;

    int bDelta = (int)(abs(bBound.delta()) * (double)detalisationK);
    double bStart = bBound.x * detalisationK;

    int finishPos = (int)topSystem.getCoordinatLay(originalLayIndex)->size();

    for (int i = 0; i < cCountingCoef; i++)
    {
        if (!app->getAppCondition()) break;
        double _k = ((rand() % kDelta) + kStart) / detalisationK;
        double _b = ((rand() % bDelta) + bStart) / detalisationK;

        double currQuadraticDelta = calcAndPrintTotalQuadratic(_k, _b, fnc, 0, finishPos, computingQuadraticDeltaPointsIncrementDelta, topSystem);

        scoped_lock lock1(maxQuadraticDeltaMutex);
        scoped_lock lock2(minQuadraticDeltaMutex);
        if (isSmaller(maxQuadraticDelta, currQuadraticDelta))
        {
            changeAndPrintNewMaxOrMinDelta(&maxQuadraticDelta, currQuadraticDelta, &maxQuadraticDeltaIndex, maxDeltaColor);
        }

        if (isBigger(minQuadraticDelta, currQuadraticDelta))
        {
            *k = _k;
            *b = _b;

            changeAndPrintNewMaxOrMinDelta(&minQuadraticDelta, currQuadraticDelta, &minQuadraticDeltaIndex, minDeltaColor);
        }
    }
    wasAnswerFinded = true;
    computeFncOnTopSystem(*k, *b, suggestedFncColor);

    bottomSystem.invalidateButton();
    cout << "FinishedCountGraientMap\n";
}

COLORREF MainLinLayout::getQuadraticDeltaColor(double quadraticDelta)
{
    const double _maxQuadraticDelta = 5000;
    const double _minQuadraticDelta = 32;
    const double rangeDelta = _maxQuadraticDelta - _minQuadraticDelta;
    const int r0 = 0;
    const int r1 = 255;

    const int g0 = 0;
    const int g1 = 0;

    const int b0 = 255;
    const int b1 = 0;

    double t = (quadraticDelta - _minQuadraticDelta) / rangeDelta;

    int r2 = (int)r0 + (int)((double)(r1 - r0) * t);
    int g2 = 0;
    int b2 = (int)b0 + (int)((double)(b1 - b0) * t);


    COLORREF answer = RGB(r2, g2, b2);

    return answer;
}

double MainLinLayout::calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x))
{
    double dy = fnc(k, b, x) - originalFnc(x);
    return (dy * dy);
}

double MainLinLayout::calcQuadratic(double k, double b, size_t xIndex, double(*fnc)(double k, double b, double x), MultiLayCoordinatSystemWindow& lay)
{
    Vector originPoint = lay.getPoint(xIndex, originalLayIndex);

    double dy = fnc(k, b, originPoint.x) - originPoint.y;

    return dy * dy;
}

void MainLinLayout::countOriginalFnc()
{
    computeOriginalFunction(currOriginalK, currOriginalB, originalFncColor);
};

void MainLinLayout::computeFncOnTopSystem(double k, double b, COLORREF _color/* = NULL*/)
{
    Vector topCellXBound = topSystem.getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();
    double xDelta = abs(topCellXBoundLen / 1000);

    for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
    {
        if (!app->getAppCondition()) break;
        double fncRes = sinFnc(k, b, x);
        Vector newPoint = { x, fncRes };
        topSystem.addPoint(newPoint, _color, 0, suggestedOddsLayIndex, false);
    }
    topSystem.invalidateButton();
}

void MainLinLayout::computeOriginalFunction(double k, double b, COLORREF _color/* = NULL*/)
{
    Vector topCellXBound = topSystem.getXCellBound();
    double topCellXBoundLen = topCellXBound.delta();
    double xDelta = abs(topCellXBoundLen / 1000);

    for (double x = topCellXBound.x; x < topCellXBound.y; x += xDelta)
    {
        if (!app->getAppCondition()) break;
        double noise = 2 * sin(70 * x);
        double fncRes = sinFnc(k, b, x) + noise;
        Vector newPoint = { x, fncRes };
        topSystem.addPoint(newPoint, _color, 0, originalLayIndex, false);
    }
    invalidateButton();
}

void MainLinLayout::startMonteCarloComputation()
{
    int timeStart = clock();

    countOriginalFnc();
    countGradientMap();

    int timeFinish = clock();

    int delta = timeFinish - timeStart;
}

void MainLinLayout::countGradientMap()
{
    double k = 0, b = 0;
    Vector kBound = { 0,   10  }; //k = A - ��������� ��������� A = 5
    Vector bBound = { 6.8, 7.2 }; // b = f - ����  ��������� f = 7
    backGroundComputation.setText("������ ���������");
    threadCoeffFinderWithUnknownFnc(&answerK, &answerB, kBound, bBound, &MainLinLayout::sinFnc);
    backGroundComputation.setText("��� ������� �����");

    static char ans[MAX_PATH] = {};
    Vector answerVector = { answerK, answerB };
    sprintf(ans, "���������� �����������: %s", answerVector.getStr());

    answerCoeff.setText(ans);
    invalidateButton();
}
