#ifndef TWEEN_H
#define TWEEN_H

#define TWEEN_LINEAR 0
#define TWEEN_EASEINOUTCUBIC  1 
// todo add more tweentypes

typedef struct
{
	// t: current time, b: beginning value, c: change in value, d: duration
	float b;
	float c;
	float d;
	float v; // current value
	int tweentype;
	// FIXME TODO add start time / current time
} Tween_t;
// functions
// constr
void  Tween_init(Tween_t *me);
// Tween_tick() should be renamed (since it doesnt manage time)
float Tween_tick(Tween_t *me, float t);// calls the proper tween func
float Tween_linearTween(Tween_t *me, float t);
void  Tween_line(Tween_t *me, float val, float duration);
void  Tween_setType(Tween_t *me, int newtype);
float Tween_easeInOutCubic(Tween_t *me, float t);

#endif

