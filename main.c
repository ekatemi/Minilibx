#include <stdlib.h>
#include <stdio.h>
#include "mlx/mlx.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
    ON_EXIT = 53 ///my var check it
};

int handle_keypress(int keysym, t_data *data)
{
    if (keysym == ON_DESTROY)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    }
    printf("Keypress: %d\n", keysym);
    return (0);
}

void put_pixel(t_data *data, int x, int y, int color)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}



int main(void)
{
    t_data data;
    data.mlx_ptr = NULL;
    data.win_ptr = NULL;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    if (data.win_ptr == NULL)
    {
        return (1);
    }
    /* IMAGE */
    data.img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    /*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

    /* Put a red pixel in the middle of the window */
    int middle_x = WINDOW_WIDTH / 2;
    int middle_y = WINDOW_HEIGHT / 2;
    int color = 0x00FF0000;
    put_pixel(&data, middle_x, middle_y, color);
    /* Display the image in the window */
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);
    /* SETUP HOOKS */
    mlx_key_hook(data.win_ptr, &handle_keypress, &data);

    mlx_loop(data.mlx_ptr);

    mlx_destroy_window(data.mlx_ptr, data.win_ptr);

    
    
    
    return (0);
}

