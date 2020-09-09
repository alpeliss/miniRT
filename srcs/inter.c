#include "mini_rt.h"

float	inter_sphere(t_vector r, t_shapes *s, t_env e)
{
	//	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	double	t2;
	t_point	p;
	t_point	n;
	double	i;

	r.dir = normalize(r.dir);
	r.origin = normalize(r.origin);
	//	a = 1;
	b = 2 * scal_prod(r.dir, basic_op_point(r.origin, s->pos, 0));
	c = square_norm(basic_op_point(r.origin, s->pos, 0)) - s->diameter * s->diameter;
	//	d = b * b - 4 * a * c;
	d = b * b - 4 * c;
	if (d < 0)
		return (0);
	//	t1 = (-b - sqrtf(d)) / (2 * a);
	//	t2 = (-b + sqrtf(d)) / (2 * a);
	t1 = (-b - sqrtf(d)) / 2;
	t2 = (-b + sqrtf(d)) / 2;
	if (t2 < 0)
		return (0);
	t2 = (t1 > 0) ? t1 : t2;
	p = basic_op_point(r.origin, mult_point(r.dir, t2, 1), 1);
	n = normalize(basic_op_point(p, s->pos, 0));
	i = (scal_prod(normalize(basic_op_point(e.l->pos, p, 0)), n));
	i /= square_norm(basic_op_point(e.l->pos, p, 0));
	i *= e.l->ratio;
//	return (0.0001 + i);
	return (1);
}
