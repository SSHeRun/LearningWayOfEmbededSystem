#include <QApplication>
#include"SingleGame.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SingleGame w;
    w.setFixedSize(950,600);
    w.setMaximumSize(950,600);

    w.show();

    return a.exec();
}
