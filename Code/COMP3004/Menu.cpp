#include <Menu.h>

Menu::Menu(QString title)
    :QStringList()
{
    this->title = &title;
}

Menu::~Menu(){
    delete this->title;
    delete this;
}
