#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <QCoreApplication>

#include "environment.hpp"

class Simulator : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Simulator(int argc, char *argv[]);
    ~Simulator();
public:
    int execute();
private:
    Environment *environment;
};

#endif // SIMULATOR_HPP
