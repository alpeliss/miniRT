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

static void		print_point(t_point point, char *name)
{
	printf("%s: ", name);
	printf("x = %f, y = %f, z = %f\n", point.x, point.y, point.z);
}

int         inter(t_vector v, t_shapes sp)
{
    double  a;
    double  b;
    double  c;
    double  t1;
    double  t2;
    double  delta;

    a = 1;
    b = 2 * scal_prod(v.dir, basic_op_point(v.or, sp.pos, 0));
    c = square_norm(basic_op_point(v.or, sp.pos, 0)) - sp.diameter * sp.diameter;
    delta = b * b - 4 * a * c;
    if (delta < 0)
        return (0);
    t1 = (-b - sqrt(delta)) / (2 * a);
    t2 = (-b + sqrt(delta)) / (2 * a);
    if (t2 > 0)
        return (1);
    return (0);  
}

void        complete(int *data)
{
    int         i;
    int         j;
    t_vector    v;
    t_point     ray;
    t_shapes    sph;

    ray.x = 0;
    ray.y = 0;
    ray.z = -55;
    sph.pos = ray;
    sph.diameter = 10;  
    ray.z = 0;
    v.or = ray;
    i = 0;
    while (i < 700)
    {
        j = 0;
        while (j < 700)
        {
            ray.x = j - 700 / 2; //W / 2
            ray.y = i - 700 / 2; //H / 2  
            ray.z = -350 / tan((60 * PI) / 360); // -W / (2 *tan(alpha / 2))

            if (i == 400 && i == j)
                print_point(ray, "direction");
            ray = normalize(ray);
            v.dir = ray;
            data[i*700 + j] = inter(v, sph) * 255;
            if (i == 400 && i == j)
                print_point(v.dir, "direction");
            j++;
        }
        i++;
    }
}

int         expose_hook(t_env *e)
{
    int     i;
    void    *img;
    int    *data;

    i = 0;
    img = mlx_new_image(e->ptr, 700, 700);
    data = (int *)mlx_get_data_addr(img, &i, &i, &i);
    complete (data);
    mlx_put_image_to_window(e->ptr, e->win, img, 0, 0);
    return (1);
}

int			main()
{
    t_env    *e;

    e = (t_env *)malloc(sizeof(t_env));
    e->f = 0;
    e->ptr = mlx_init();
    e->win = mlx_new_window(e->ptr, 700, 700, "Reload");
    //mlx_loop_hook(e->ptr, expose_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->ptr);
}