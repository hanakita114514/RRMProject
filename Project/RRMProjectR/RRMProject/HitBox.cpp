#include "HitBox.h"

HitBox::HitBox() : hitstop(0), power(0), rc(0, 0, 0, 0), vec(0,0)
{
}

HitBox::HitBox(float power, float hitstop, const Rect& rc, const Vector2& vec, const Vector2& dir) : power(power), hitstop(hitstop), rc(rc), vec(vec), dir(dir)
{
}