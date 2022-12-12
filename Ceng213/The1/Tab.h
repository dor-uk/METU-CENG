#ifndef TAB_H
#define TAB_H

#include <iostream>

class Tab
{
public:

    Tab()
    {
        url="";
        title="";
        contents="";
    }

    Tab(const std::string &url, const std::string &title, const std::string &contents)
    {
        this->url = url;
        this->title = title;
        this->contents = contents;
    }

    friend std::ostream &operator<<(std::ostream &os, const Tab &obj)
    {
        os << obj.title << std::endl << obj.url << std::endl << obj.contents << std::endl;
        return os;
    }

    bool operator==(const Tab &rhs)
    {
        return url == rhs.url && title == rhs.title && contents == rhs.contents;
    }

    std::string getUrl() {
        return url;
    }

    std::string getTitle() {
        return title;
    }

    std::string getContents() {
        return contents;
    }
    
private:
    std::string url;
    std::string title;
    std::string contents;
};

#endif // TAB_H
