#include "MoveEvent.h"



MoveEvent::MoveEvent(BodyComponent* body, int dir, int speed, int xDestination): _myBody(body), _dir(dir), _speed(speed), _xDestination(xDestination)
{
}

