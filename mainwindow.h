#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamelogic.h"
#include "qgraphicsscene.h"
#include <QMainWindow>
#include <QButtonGroup>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToModeWindow();
    void switchToPlayerWindow();
    void switchToGameWindow();
    void readClickInput(int x, int y);
    void drawBoard();

private:
    Ui::MainWindow *ui;
    QPixmap *pixmap;
    QGraphicsScene *scene;
    QPainter *painter;
    QButtonGroup *buttonGroup;
    QIntValidator *intValidator;
    GameLogic *game;
    const int boardNumbers[20] = {6, 13, 4, 18, 1, 20, 5, 12, 9, 14, 11, 8, 16, 7, 19, 3, 17, 2, 15, 10};

private:
    void setPlayers();
    void setMode();
};
#endif // MAINWINDOW_H
