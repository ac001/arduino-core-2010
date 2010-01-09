#include "Tween.h"
// easing equations from
// robert penner BSD license

// pointer, time_now
float Tween_linearTween(Tween_t *me, float t) 
{
	// t: current time, b: beginning value, c: change in value, d: duration
	me->v = ((me->c * t) / me->d) + me->b;
	//c*t/d + b;
	return me->v;
}
// *, val, time
void Tween_line(Tween_t *me, float val, float duration) 
{
	me->b = me->v; // beginning = current
	me->c = val - me->v; // change in value = target - current
	me->d = duration;
}

void Tween_init(Tween_t *me)
{
	me->v = 0;
	me->c = 0;
	me->b = 0;
	me->d = 0;
}
float Tween_tick(Tween_t *me, float t) 
{
	float ret = 0;
	// if done ( >  duration)
	if (t > me->d)
	{
		ret = me->b + me->c; // arrived
	} 
	else
	{
		switch (me->tweentype)
		{
			// call appropriate tween function
			default:
			case TWEEN_EASEINOUTCUBIC:
				ret = Tween_easeInOutCubic(me,t);
				break;
			case TWEEN_LINEAR:
				ret = Tween_linearTween(me, t); 
				break;
		}
	}
	me->v = ret; // IMPORTANT
	return ret;
}
void Tween_setType(Tween_t *me, int newtype) 
{
	switch (newtype)
	{
		// those are ok
		case TWEEN_EASEINOUTCUBIC:
		case TWEEN_LINEAR:
			me->tweentype = newtype;
			break;
		default:
			// call linear tween
			me->tweentype = TWEEN_LINEAR;
			break;
	}
}

// cubic easing in/out - acceleration until halfway, then deceleration
float Tween_easeInOutCubic(Tween_t *me, float t) 
{
	if ((t /= me->d/2) < 1) 
	{ 
		return me->c/2*t*t*t + me->b;
	}
	return me->c / 2* ((t-=2)*t*t + 2) + me->b;
}
