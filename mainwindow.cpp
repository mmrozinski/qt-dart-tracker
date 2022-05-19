#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(QRectF(0, 0, ui->graphicsView->height(), ui->graphicsView->height()), this);

    pixmap = new QPixmap(ui->graphicsView->height(), ui->graphicsView->height());

    painter = new QPainter(pixmap);

    buttonGroup = new QButtonGroup(this);

    intValidator = new QIntValidator(this);

    buttonGroup->addButton(ui->orderModeRadio);
    buttonGroup->addButton(ui->standardModeRadio);

    ui->maxScoreLineEdit->setValidator(intValidator);

    connect(ui->menuContinueButton, &QPushButton::clicked, this, &MainWindow::switchToPlayerWindow);
    connect(ui->selectionContinueButton, &QPushButton::clicked, this, &MainWindow::switchToModeWindow);
    connect(ui->modeContinueButton, &QPushButton::clicked, this, &MainWindow::switchToGameWindow);
    connect(ui->graphicsView, &MyGraphicsView::mouseClicked, this, &MainWindow::readClickInput);
    connect(ui->graphicsView, &MyGraphicsView::resized, this, &MainWindow::drawBoard);
}

void MainWindow::switchToPlayerWindow()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void MainWindow::switchToModeWindow()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    setPlayers();
}

void MainWindow::switchToGameWindow()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    setMode();
}

void MainWindow::setMode()
{
    if (ui->standardModeRadio->isChecked())
    {
        game->setMode(ui->maxScoreLineEdit->text().toInt());
    }

}

void MainWindow::setPlayers()
{
    this->game = new GameLogic(ui->playerSpinBox->value());

    game->addPlayer(ui->playerLineEdit_1->text().toStdString());
    game->addPlayer(ui->playerLineEdit_2->text().toStdString());
    game->addPlayer(ui->playerLineEdit_3->text().toStdString());
    game->addPlayer(ui->playerLineEdit_4->text().toStdString());
}

void MainWindow::drawBoard()
{
    delete painter;
    delete pixmap;
    delete scene;

    scene = new QGraphicsScene(QRectF(0, 0, ui->graphicsView->height(), ui->graphicsView->height()), this);

    pixmap = new QPixmap(ui->graphicsView->height(), ui->graphicsView->height());

    painter = new QPainter(pixmap);

    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    painter->setBackground(Qt::black);
    painter->setBackgroundMode(Qt::TransparentMode);

    for (int i = 0; i < 10; i++)
    {
        int ringWidth = ui->graphicsView->height() / 40;
        int ringOffset = ui->graphicsView->height() / 4 - ringWidth;

        // Evens
        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);

        painter->drawPie(QRectF(0, 0, ui->graphicsView->height() - 1, ui->graphicsView->height() - 1), 2 * i * 288 + 144, 288);

        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);

        painter->drawPie(QRectF(ringWidth, ringWidth, ui->graphicsView->height() - 1 - ringWidth * 2, ui->graphicsView->height() - 1 - ringWidth * 2), 2 * i * 288 + 144, 288);

        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);

        painter->drawPie(QRectF(ringOffset, ringOffset, ui->graphicsView->height() - 1 - ringOffset * 2, ui->graphicsView->height() - 1 - ringOffset * 2), 2 * i * 288 + 144, 288);

        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);

        painter->drawPie(QRectF(ringWidth + ringOffset, ringWidth + ringOffset, ui->graphicsView->height() - 1 - (ringWidth + ringOffset) * 2, ui->graphicsView->height() - 1 - (ringWidth + ringOffset) * 2), 2 * i * 288 + 144, 288);


        // Odds
        painter->setPen(Qt::green);
        painter->setBrush(Qt::green);

        painter->drawPie(QRectF(0, 0, ui->graphicsView->height() - 1, ui->graphicsView->height() - 1), (2 * i + 1) * 288 + 144, 288);

        painter->setPen(Qt::white);
        painter->setBrush(Qt::white);

        painter->drawPie(QRectF(ringWidth, ringWidth, ui->graphicsView->height() - 1 - ringWidth * 2, ui->graphicsView->height() - 1 - ringWidth * 2), (2 * i + 1) * 288 + 144, 288);

        painter->setPen(Qt::green);
        painter->setBrush(Qt::green);

        painter->drawPie(QRectF(ringOffset, ringOffset, ui->graphicsView->height() - 1 - ringOffset * 2, ui->graphicsView->height() - 1 - ringOffset * 2), (2 * i + 1) * 288 + 144, 288);

        painter->setPen(Qt::white);
        painter->setBrush(Qt::white);

        painter->drawPie(QRectF(ringWidth + ringOffset, ringWidth + ringOffset, ui->graphicsView->height() - 1 - (ringWidth + ringOffset) * 2, ui->graphicsView->height() - 1 - (ringWidth + ringOffset) * 2), (2 * i + 1) * 288 + 144, 288);

        // Middle
        painter->setPen(Qt::green);
        painter->setBrush(Qt::green);

        painter->drawEllipse(QRectF(ui->graphicsView->height() / 2 - ringWidth * 2, ui->graphicsView->height() / 2 - ringWidth * 2, ringWidth * 4, ringWidth * 4));

        painter->setPen(Qt::red);
        painter->setBrush(Qt::red);

        painter->drawEllipse(QRectF(ui->graphicsView->height() / 2 - ringWidth, ui->graphicsView->height() / 2 - ringWidth, ringWidth * 2, ringWidth * 2));
    }

    for (int i = 0; i < 20; i++)
    {
        int x = (ui->graphicsView->height() / 2 - ui->graphicsView->height() / 8) * cos(i * 18 * M_PI / 180) + ui->graphicsView->height() / 2 - 5; // the -5 is a magic number - should change to something more reasonable
        int y = -(ui->graphicsView->height() / 2 - ui->graphicsView->height() / 8) * sin(i * 18 * M_PI / 180) + ui->graphicsView->height() / 2;
        painter->save();
        if (i % 2)
        {
            painter->setBrush(Qt::white);
            painter->setPen(Qt::white);
        }
        else
        {
            painter->setBrush(Qt::black);
            painter->setPen(Qt::black);
        }
        painter->translate(x, y);
        painter->drawText(0, 0, QString::number(boardNumbers[i]));
        painter->restore();
    }

    scene->addPixmap(*pixmap);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->show();
}

void MainWindow::readClickInput(int x, int y)
{
    int hitNumber = 0;
    int height = ui->graphicsView->height();
    int width = ui->graphicsView->width();
    int ringWidth = height / 40;
    int ringOffset = height / 4 - ringWidth;

    double radius = sqrt(pow(width / 2. - x, 2) + pow(height / 2. - y, 2));

    double angle = (y - height / 2) >= 0 ? -acos((x - width / 2) / radius) : acos((x - width / 2) / radius);

    if (angle < 0)
        angle = 2 * M_PI + angle;

    angle = angle * 180 / M_PI;

    if ((angle >= 351 || angle < 9) && radius <= height / 2)
        hitNumber = 6;
    for (int i = 1; i < 20; i++)
    {
        int rangeStart = i * 18 - 9;
        if (angle >= rangeStart && angle < rangeStart + 18 && radius <= height / 2)
        {
            hitNumber = boardNumbers[i];
            break;
        }
    }

    if (radius > height / 2) {}
    else if (radius >= height / 2 - ringWidth && radius <= height / 2)
        hitNumber *= 2;
    else if (radius <= height / 2 - ringOffset && radius >= height / 2 - ringOffset - ringWidth)
        hitNumber *= 3;
    else if (radius >= ringWidth && radius <= ringWidth * 2)
        hitNumber = 25;
    else if (radius <= ringWidth)
        hitNumber = 50;

    game->commitThrow(hitNumber);

    QString playerName = QString::fromStdString(game->getPlayer(game->getCurrentPlayer()));
    QString score = QString::number(game->getScore(game->getCurrentPlayer()));
    QString currentThrow = QString::number(game->getCurrentThrow());

    ui->testLabel->setText(playerName + "   " + score + "\n" + currentThrow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

