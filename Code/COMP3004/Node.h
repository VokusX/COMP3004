#ifndef NODE_H
#define NODE_H

#include <QStringList>

/*
 * A class to hold the data of a menu as well as its
 * parent menu.  This allows the "Back" button to easily
 * return to the previous menu.
 *
 */

class Node{
public:
    Node();
    Node(Node * u);
    Node(Node * parent, QStringList * link);
    Node * getParent();
    QStringList* getData();
private:
    Node * parent;
    QStringList* link;
};

#endif // NODE_H
