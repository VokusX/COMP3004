#ifndef MENU_H
#define MENU_H
#include <QStringList>


class Menu : public QStringList{
    public:
        Menu(QString title);
        ~Menu();



    private:
        QString *title;
};


#endif // MENU_H
