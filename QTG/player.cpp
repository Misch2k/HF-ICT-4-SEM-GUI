#include "player.h"
#include "gameobejct.h"
#include "constants.h"
#include <QDebug>

Player::Player(int x, int y, int direction, int heightGA)
    : GameObject(x, y, constants::ImgFolder + "player.png", 250)
{
//player.jpg
//    this->direction = direction;
//    this->heightGA = heightGA;
}

void Player::move()
{
    if(direction == 1){
        if(y+7 <=  340 ){
        y = y+5;
        }
    }
    if(direction == 2){
        if(y-7 >=  -heightGA+120){
             y = y-5;
        }
    }
}
