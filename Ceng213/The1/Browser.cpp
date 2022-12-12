#include "Browser.h"

Browser::Browser() {
    
    windows.append(Window());
}

void Browser::newWindow() {
    
    windows.prepend(Window());
}

void Browser::closeWindow() {
    
    if(windows.isEmpty())
    {
        //std::cout<< '1'<<'\n';
        return;
    }
    else
    {
        //std::cout<< '1'<<'\n';
        windows.removeNode(windows.getFirstNode());
        return;
    }
}

void Browser::switchToWindow(int index) {
    
    windows.moveToIndex(index,0);
}

Window &Browser::getWindow(int index) {
    
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    
    to.newTab(from.getActiveTab());
    from.closeTab();
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    window2.changeActiveTabTo(0);
    
    while(window2.isEmpty()==0)
    {
        window1.newTab(window2.getActiveTab());
        window2.closeTab();   
    }   
}

void Browser::mergeAllWindows() {
    
    if(windows.getFirstNode())
    {
        Node<Window>* current=windows.getFirstNode();
        current=current->next;
        
        while(current!=windows.getFirstNode())
        {
            mergeWindows(windows.getFirstNode()->data,current->data);
            
            current=current->next;
        }
    }
}

void Browser::closeAllWindows() {
    
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows() {
    
    if(windows.getFirstNode() == NULL)
    {
        return;
    }
    
    Node<Window>* current = windows.getFirstNode();
    //Node<Window>* head = windows.getFirstNode();
    Node<Window>* next = NULL;

    while(current->next != windows.getFirstNode())
    {
        next = current->next;
        
        if(current->data.isEmpty())
        {
            windows.removeNode(current);
        }
        
        current = next;
    }
    
    if(current->data.isEmpty())
    {
        windows.removeNode(current);
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}

