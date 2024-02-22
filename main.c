#include <stdlib.h>
#include <stdio.h>
#include "mlx/mlx.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
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
    if (keysym == ON_EXIT)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    printf("Keypress: %d\n", keysym);
    return (0);
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
        free(data.win_ptr);
        return (1);
    }
    /* SETUP HOOKS */
    mlx_key_hook(data.win_ptr, &handle_keypress, &data);

    mlx_loop(data.mlx_ptr);

    mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    free(data.mlx_ptr);
    
    
    return (0);
}

