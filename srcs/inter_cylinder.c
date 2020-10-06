#include "mini_rt.h"
#include <math.h>

static	double	inter2(t_vector v, double t1, double t2, t_shapes *s)
{
	double		t;
    t_shapes    plan;
    t_vector    inter;
    double      dist_to_base;

	t = pow(2, 24);
	if (t1 >= 0)
		t = t1;
	else if (t2 >= 0)
		t = t2;
	else
		return (-1);
	inter.origin = add_point(v.origin, mult_point(v.dir, t, 1), 1);
    inter.dir = mult_point(s->v_or, -1, 1);
    plan.pos = s->pos;
    plan.v_or = s->v_or;
    dist_to_base = inter_plane(inter, &plan);
    if (dist_to_base > s->diameter || dist_to_base < 0)
        return (-1);
    return (t);
}

double		inter_cylinder(t_vector v, t_shapes *s)
{	
	double      a;
    double      b;
    double      c;
    double      t1;
    double      t2;
    double      det;
    t_point     sub;
    t_point     cross;
    t_point     cross2;

	cross = vec_cross(v.dir , s->v_or);
	sub = add_point(v.origin, s->pos, 0);
	cross2 = vec_cross(sub, s->v_or);
	a = scal_prod(cross, cross);
	b = 2 * scal_prod(cross, cross2);
	c = scal_prod(cross2, cross2) - (pow(s->diameter / 2, 2)
		* scal_prod(s->v_or, s->v_or));
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (-1);
	a = 2 * a;
	det = sqrt(det);
	t1 = (-b - det) / a;
	t2 = (-b + det) / a;
	t1 = inter2(v, t1, t2, s);
    return (t1);
}