#include "cub3D.h"

void    w_key(t_cub *cub)
{
    printf("w key pressed\n");
    double next_x;
    double next_y;
    
    next_x = cub->player.ppos.x + cub->player.dir.x * PLAYER_SPEED;
    next_y = cub->player.ppos.y + cub->player.dir.y * PLAYER_SPEED;
    
   if (is_not_wall(cub->map[(int)(cub->player.ppos.y)][(int)(next_x)]))
    {
        cub->player.ppos.x = next_x;
    }
    if (is_not_wall(cub->map[(int)(next_y)][(int)(cub->player.ppos.x)]))
    {
        cub->player.ppos.y = next_y;
    }
}

void    s_key(t_cub *cub)
{
    printf("s key pressed\n");
    double prev_x;
    double prev_y;
    
    prev_x = cub->player.ppos.x - cub->player.dir.x * PLAYER_SPEED;
    prev_y = cub->player.ppos.y - cub->player.dir.y * PLAYER_SPEED;
    if (is_not_wall(cub->map[(int)(cub->player.ppos.y)][(int)(prev_x)]))
        cub->player.ppos.x = prev_x;
    if (is_not_wall(cub->map[(int)(prev_y)][(int)(cub->player.ppos.x)]))
        cub->player.ppos.y = prev_y;
}

void    a_key(t_cub *cub)
{
    printf("a key pressed\n");
    double left_x;
    double left_y;
    
    left_x = cub->player.ppos.x - cub->player.plane_x * PLAYER_SPEED;
    left_y = cub->player.ppos.y - cub->player.plane_y * PLAYER_SPEED;
    if (is_not_wall(cub->map[(int)(cub->player.ppos.y)][(int)(left_x)]))
        cub->player.ppos.x = left_x;
    if (is_not_wall(cub->map[(int)(left_y)][(int)(cub->player.ppos.x)]))
        cub->player.ppos.y = left_y;
}

void    d_key(t_cub *cub)
{
    printf("d key pressed\n");
    double right_x;
    double right_y;
    
    right_x = cub->player.ppos.x + cub->player.plane_x * PLAYER_SPEED;
    right_y = cub->player.ppos.y + cub->player.plane_y * PLAYER_SPEED;
    if (is_not_wall(cub->map[(int)(cub->player.ppos.y)][(int)(right_x)]))
    {
        cub->player.ppos.x = right_x;
        printf("updated x pos\n");    
    }
    if (is_not_wall(cub->map[(int)(right_y)][(int)(cub->player.ppos.x)]))
    {
        cub->player.ppos.y = right_y;
        printf("updated y pos\n");
    }
}