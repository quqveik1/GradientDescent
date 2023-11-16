#pragma once
#include "GraphicInfoButton.h" 
#include <fstream>


void GraphicInfoButton::onClick(Vector mp)
{
    TextView::onClick(mp);

    char* outputText = app->readText("Files\\FAQ.txt");
    
    if (outputText)
    {
        app->messageBox(outputText, text);
        delete outputText;
    }
}
