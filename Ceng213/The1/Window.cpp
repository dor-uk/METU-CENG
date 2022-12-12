include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    if(tabs.isEmpty())
    {
        Tab new_tab = Tab();
        //tabs.append(new_tab);
        
        activeTab = 0;
        
        return new_tab;
    }
    
    else
    {
        
        return ((tabs.getNodeAtIndex(activeTab)->data));
        //std::cout << this->activeTab;
    }
}

bool Window::isEmpty() const {
    
    return (tabs.isEmpty());
}
void Window::newTab(const Tab &tab) {
    if(tabs.isEmpty() == 0)
    {
        tabs.insertAfterNode(tab,tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }

    else
    {
        tabs.append(tab);
        activeTab = 0;
    }
}

void Window::closeTab() {   //geri don
    int i=tabs.getSize();
    if(activeTab == i-1)
    {
        if(i==1)
        {
            tabs.removeNodeAtIndex(0);
            activeTab =- 1;
        }
        else
        {
            tabs.removeNode(tabs.getNode(getActiveTab()));
            activeTab = i-2;
        }
    }
    else
    {
        tabs.removeNode(tabs.getNode(getActiveTab()));
    }
}

void Window::moveActiveTabTo(int index) {
    if(index >= tabs.getSize())
    {
        index = tabs.getSize()-1;
    }
    
    //std::cout<<index<<888<<'\n';
    tabs.moveToIndex(activeTab, index);
    
    activeTab = index;
}

void Window::changeActiveTabTo(int index) {
    if(index < tabs.getSize() && index >-1)
    {
        activeTab = index;
    }
}

void Window::addTab(Node<Tab> &tab) {
    if(tabs.isEmpty())
    {
        tabs.append(tab.data);
        activeTab = 0;
        //std::cout<< activeTab<<'\n';
    }
    
    else
    {
        tabs.append(tab.data);
    }
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}


