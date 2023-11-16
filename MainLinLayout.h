#pragma once
#include <LinearLayout.h>
#include "CoordinatSystemWindow.h"
#include "ColorfullCoordinatSystemWindow.h"
#include <TextView.cpp>
#include "GraphicInfoButton.cpp"
#include "CustomRCoordinatSystemWindow.h"
#include "MultiLayCoordinatSystemWindow.h"


struct MainLinLayout : LinearLayout
{
    MultiLayCoordinatSystemWindow topSystem;
    MultiLayCoordinatSystemWindow bottomSystem;
    COLORREF originalFncColor = C_LIGHTCYAN;
    COLORREF suggestedFncColor = C_LIGHTRED;
    COLORREF userSelectedFncColor = C_GREEN;
    Vector downLineSize = {};
    int maxMinDeltaR = 10;
    COLORREF minDeltaColor = C_LIGHTRED;
    COLORREF maxDeltaColor = C_BLUE;

    LinearLayout topDescribtions;
    TextView topDescribtion1;
    TextView topDescribtion2;
    TextView topDescribtion3;
    LinearLayout bottomDescribtions;
    TextView bottomDescribtion1;
    TextView bottomDescribtion2;

    LinearLayout downLinLayout;
    TextView backGroundComputation;
    TextView suggestedCoeff;
    TextView answerCoeff;
    GraphicInfoButton graphicInfoButton;

    size_t originalLayIndex = 0;
    size_t suggestedOddsLayIndex = 1;

    size_t gradientLay = 0;

    static double currOriginalK;
    static double currOriginalB;

    int cCountingCoef = 100000;
    int cQuadraticDeltaCountingPoints = 100;

    int cOriginalPoints = 1000;
    int computingQuadraticDeltaPointsIncrementDelta = 5;

    double answerK = 0;
    double answerB = 0;
    bool wasAnswerFinded = false;

    mutex  maxQuadraticDeltaMutex;
    double maxQuadraticDelta = DBL_MIN;
    int    maxQuadraticDeltaIndex = -1;

    mutex  minQuadraticDeltaMutex;
    double minQuadraticDelta = DBL_MAX;
    int    minQuadraticDeltaIndex = -1;

    mutex gradientDescentMutex;
    double gradientDescentDelta = DBL_MAX;
    Vector gradientDescentPos;
    Vector gradientDelta = { 1e-6, 1e-6 };
    size_t gradientCoorBottomSystemIndex = 1;
    COLORREF gradientDescentColor = C_BROWN;
    int gradientDescentR = 10;

    M_HDC onWindowMovingCopyDC;

    MainLinLayout(AbstractAppData* _app, Vector _startPos);

    void initCoordinats();
    void initDescribtions();
    void initDownLinLayout();

    static double originalSinFnc(double x);
    static double sinFnc(double k, double b, double x);

    double calcQuadratic(double k, double b, double x, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
    double calcQuadratic(double k, double b, size_t xIndex, double(*fnc)(double k, double b, double x), MultiLayCoordinatSystemWindow& lay);
    
    double calcTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step);
    double calcTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), int start, int finish, int step, MultiLayCoordinatSystemWindow& lay);
    double calcAndPrintTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x), double start, double finish, double step);
    double calcAndPrintTotalQuadratic(double k, double b, double(*fnc)(double k, double b, double x), int start, int finish, int step, MultiLayCoordinatSystemWindow& lay);

    void startGradientDescent(Vector _startPos);

    COLORREF getQuadraticDeltaColor(double quadraticDelta);

    void threadCoeffFinder(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x), double (*originalFnc)(double x));
    void threadCoeffFinderWithUnknownFnc(double* k, double* b, Vector& kBound, Vector& bBound, double(*fnc)(double k, double b, double x));
    void changeAndPrintNewMaxOrMinDelta(double* curminMaxDelta, double currDelta, int* currIndex, COLORREF color);
    void startMonteCarloComputation();
    void countGradientMap();
    void countOriginalFnc();
    void computeOriginalFunction(double k, double b, COLORREF _color = NULL);
    void computeFncOnTopSystem(double k, double b, COLORREF _color = NULL);
    void onCertainPointSelection(Vector clickedCellP);

    virtual void onMessageRecieve(const char* name, void* data) override;

    virtual void draw() override;
    virtual int onSize(Vector managerSize, Rect _newRect) override;
};
