# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include "../miniLibX/mlx.h"
# include <math.h>
# define PI 3.14159265359


typedef struct		s_env
{
    void        *ptr;
    void        *win;
    int         *f;
}					t_env;

typedef struct			s_point
{
	float				x;
	float				y;
	float				z;
}						t_point;

typedef struct			s_vector
{
	t_point				or;
	t_point				dir;
}				t_vector;

typedef struct			s_shapes
{
	int					id;
	t_point				pos;
	t_point				v_orientation;
	t_point				a;
	t_point				b;
	t_point				c;
	float				diameter;
	float				height;
	t_point				color;
	struct s_shapes		*next;
}						t_shapes;

typedef struct			s_lights
{
	t_point				pos;
	float				ratio;
//	t_color				color;
	struct s_lights		*next;
}						t_lights;