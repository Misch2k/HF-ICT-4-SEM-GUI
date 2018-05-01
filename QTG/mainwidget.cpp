#include "mainwidget.h"
#include "gamearea.h"

#include <string>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QSlider>
#include <QPaintEvent>
#include <QtMultimedia/QSound>
#include <QMediaPlayer>
#include <QUrl>
#include <QMessageBox>
#include <QApplication>

MainWidget::MainWidget(QWidget *parent, int speed, int angle)
    : QWidget(parent)
{
    ga = new GameArea(parent);

//    Initialisation of speed and angle
    speed = 0;
    angle = 0;

//    Initialisation of shootSound
    shootSound = new QMediaPlayer();
    //shootSound->setMedia(QUrl("qrc:/sounds/1_audio/shoot_playermusic.mp3"));
    shootSound->setMedia(QUrl("//Users//patrick//Downloads//img//1_audio//shoot_playermusic.mp3"));

    createObjects();
    createLayout();
    connectObjects();
}

void MainWidget::onGameFinished()
{
//    Hier MessageBox implementieren

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "You won!", "Do you want to start a new Game?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
      } else {
          qDebug() << "Yes was *not* clicked";
          QApplication::quit();
      }
}

void MainWidget::createObjects()
{
    //1. Create Objects

    titleLabel = new QLabel("<h1>Welcome Player ONE</h1>");
    titleLabel->setGeometry(0, 0, 10, 10);

    shootsLabel = new QLabel("#Shoots:");
    speedLabel = new QLabel("Speed:");
    angleLabel = new QLabel("Angle:");

    numberOfShotsInput = new QLineEdit();

    speedInput = new QLineEdit();
    //speedInput->setReadOnly(true);
    speedInput->setText("1");

    angleInput = new QLineEdit();
    //angleInput->setReadOnly(true);
    angleInput->setText("0");

    actionButton = new QPushButton("Start");

    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(100);

    angleSlider = new QSlider(Qt::Horizontal);
    angleSlider->setMinimum(0);
    angleSlider->setMaximum(90);
}

void MainWidget::createLayout()
{
    //2. Create Layout
    QVBoxLayout *vAll = new QVBoxLayout();
    QVBoxLayout *vGameArea = new QVBoxLayout();
    QHBoxLayout *hBottom = new QHBoxLayout();

    //Adds the Backgroudimage and everything else from a gamearea object
    vAll->addWidget(titleLabel);

    vGameArea->addWidget(ga);

    //Das Widget ga bekommt am meisten Platz und andere schrumpfen zusammen so viel wie es geht
    ga->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    hBottom->addWidget(actionButton);
    hBottom->addWidget(shootsLabel);
    hBottom->addWidget(numberOfShotsInput);
    hBottom->addWidget(speedLabel);
    hBottom->addWidget(speedSlider);
    hBottom->addWidget(speedInput);
    hBottom->addWidget(angleLabel);
    hBottom->addWidget(angleSlider);
    hBottom->addWidget(angleInput);

    vAll->addLayout(vGameArea);
    vAll->addLayout(hBottom);

    //3. Set Main Layout
    this->setLayout(vAll);
}

void MainWidget::connectObjects()
{
    //Speedsilder
    QObject::connect(
                speedSlider, SIGNAL(valueChanged(int)),
                this, SLOT(speedSliderMoved(int)));

    //angleslider
    QObject::connect(
                angleSlider, SIGNAL(valueChanged(int)),
                this, SLOT(angleSliderMoved(int)));

    //actionbutton
    QObject::connect(
                actionButton, SIGNAL(clicked()),
                this, SLOT(actionButtonClicked()));

    //GameFinished
    QObject::connect(
                ga, SIGNAL(gameFinished()),
                this, SLOT(onGameFinished()));
}

void MainWidget::speedSliderMoved(int value)
{
    //qDebug() << "SpeedSlider Value: " << value;

    speed = value;

    QString s = QString::number(speed);
    speedInput->setText(s);
}

void MainWidget::angleSliderMoved(int value)
{
    //qDebug() << "AngleSlider Value: " << value;

    angle = value;

    QString s = QString::number(angle);
    angleInput->setText(s);

}

void MainWidget::actionButtonClicked()
{
    //qDebug() << "actionButton clicked" << endl;

    actionButton->setText("Shoot");

    numberOfShots = numberOfShots + 1;
    numberOfShotsInput->setText(numberOfShots);

    static int count = -1;
    count++;

    numberOfShotsInput->setText(QString::number(count));

    if(count == 0) {
        qDebug() << "MainWidget - start Game";
        actionButton->setText("Shoot");
        ga->startGame();
    } else {
        shootSound->play();
        ga->shoot(speed, angle);
    }
}
