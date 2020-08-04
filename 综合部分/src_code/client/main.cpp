#include "pokemonwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PokemonWidget w;
    w.show();
    return a.exec();
}
