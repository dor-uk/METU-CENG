#ifndef BROWSER_H
#define BROWSER_H

#include "Tab.h"
#include "LinkedList.h"
#include "Window.h"

class Browser
{
public:
    Browser();

    void addWindow(Window& w) {
        windows.append(w);
    }

    void newWindow();
    void closeWindow();
    void switchToWindow(int index);
    Window &getWindow(int index);
    void moveTab(Window &from, Window &to);
    void mergeWindows(Window &window1, Window &window2);
    void mergeAllWindows();
    void closeAllWindows();
    void closeEmptyWindows();
    void print();

private:
    LinkedList<Window> windows;
};

#endif
