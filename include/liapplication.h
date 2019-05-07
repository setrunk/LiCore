#ifndef LIAPPLICATION_H
#define LIAPPLICATION_H

#include <QApplication>

class LiApplication : public QApplication
{
public:
    explicit LiApplication(int &argc, char **argv);
};

#endif // LIAPPLICATION_H
