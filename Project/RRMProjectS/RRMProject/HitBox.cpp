#include "HitBox.h"

HitBox::HitBox() : hitstop(0), power(0), rc(0, 0, 0, 0)
{
}

HitBox::HitBox(float power, float hitstop, Rect rc) : power(power), hitstop(hitstop), rc(rc)
{
}