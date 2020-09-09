#include "mini_rt.h"
#include "reload.h"

t_point 	basic_op_point(t_point pa, t_point pb, int op)
{
	t_point	pc;

	pc.x = (op) ? pa.x + pb.x : pa.x - pb.x;
	pc.y = (op) ? pa.y + pb.y : pa.y - pb.y;
	pc.z = (op) ? pa.z + pb.z : pa.z - pb.z;
	return (pc);
}

t_point		mult_point(t_point p, float m, int op)
{
	t_point	r;

	if (!m && !op)
		return (p);
	r.x = (op) ? m * p.x : p.x / m;
	r.y = (op) ? m * p.y : p.y / m;
	r.z = (op) ? m * p.z : p.z / m;
	return (r);
}

float		scal_prod(t_point p, t_point q)
{
	return (p.x * q.x + p.y * q.y + p.z * q.z);
}

float		square_norm(t_point p)
{
	return (p.x * p.x + p.y * p.y + p.z * p.z);
}

t_point		normalize(t_point p)
{
	t_point	q;
	float	norm;

	if (!(norm = sqrtf(square_norm(p))))
		return (p);
	q.x = p.x / norm;
	q.y = p.y / norm;
	q.z = p.z / norm;
	return (q);
}
