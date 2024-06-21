CC = cc
CFLAGS = -Imlx -Wall -Wextra -Werror 
NAME = miniRT

SRCS_DIR = ./mandatory/
SRCS_SRCS = main.c\
			utile.c
SRCS = $(addprefix $(SRCS_DIR),$(SRCS_SRCS))
SRCS_OBJS = $(SRCS:.c=.o)

VEC_DIR = ./mandatory/vector/
VEC_SRCS = vec_div_mul.c\
			vec_init.c\
			vec_plus_minus.c\
			vec_pro.c\
			vec_utile.c
VEC = $(addprefix $(VEC_DIR),$(VEC_SRCS))
VEC_OBJS = $(VEC:.c=.o)

RAY_DIR = ./mandatory/ray/
RAY_SRCS = cam.c\
			ray.c\
			light.c \
			phong_light.c\
			shadow.c
RAY = $(addprefix $(RAY_DIR),$(RAY_SRCS))
RAY_OBJS = $(RAY:.c=.o)

SPHERE_DIR = ./mandatory/sphere/
SPHERE_SRCS = sphere.c \
				object.c \
				plane.c \
				cylinder.c
SPHERE = $(addprefix $(SPHERE_DIR),$(SPHERE_SRCS))
SPHERE_OBJS = $(SPHERE:.c=.o)

HIT_DIR = ./mandatory/hit/
HIT_SRCS = hit.c
HIT = $(addprefix $(HIT_DIR),$(HIT_SRCS))
HIT_OBJS = $(HIT:.c=.o)

all : $(NAME)

clean : 
	rm -f $(SRCS_OBJS) $(VEC_OBJS) $(RAY_OBJS) $(SPHERE_OBJS) $(HIT_OBJS)
#	rm -f $(BUNUS_OBJS)

fclean : clean
	rm -f $(NAME)

re:
	make fclean
	make all

$(NAME) : $(SRCS_OBJS) $(VEC_OBJS) $(RAY_OBJS) $(SPHERE_OBJS) $(HIT_OBJS)
		$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $^ -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@ 

.PHONY : all clean fclean re 
