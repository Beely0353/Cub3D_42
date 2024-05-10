/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:58:13 by biaroun           #+#    #+#             */
/*   Updated: 2024/05/09 14:12:07 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100
#define KEY_N 110
#define KEY_ESC 65307
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2

typedef struct map {
    void *mlx;
    void *mlx_win;
    int win_size[2];

    int mapX;
    int mapY;
    int mapS;
    char **map;
    int  *map2;

    double p_pos[2];
    double pd_pos[2];
    double prev_p_pos[2];
    double p_angle;
    double prev_p_angle;
    double p_dir[2];
    int p_size;
    double FOV[2];
    double time[2];

    void *wall;
    void *ground;


    int key_states[65536]; // Tableau pour stocker l'état de chaque touche
} map;

void put_bg(void *mlx, void *mlx_win, map *map) {
    int i = -2;
    int j = -2;

    while (++i != map->win_size[0] + 1) 
    {
        while (++j != map->win_size[1] + 1)
            mlx_pixel_put(mlx, mlx_win, 1 + i, 1 + j, 0xD3D3D3);
        j = -2;
    }
}

void put_square(map *map, int x, int y, int lengh, int color) 
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (++i != lengh)
    {
        while (++j != lengh)
            mlx_pixel_put(map->mlx, map->mlx_win, x + i, y + j, color);
        j = -1;
    }
}

void draw_line(map *map, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        mlx_pixel_put(map->mlx, map->mlx_win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void put_player(void *mlx, void *mlx_win, map *map) 
{
    int i = 0;
    int j;

    int half_size = map->p_size / 2;

    while (i < map->p_size) {
        j = 0;
        while (j < map->p_size) {
            mlx_pixel_put(mlx, mlx_win, map->p_pos[0] + i - half_size, map->p_pos[1] + j - half_size, 0xFF0000);
            j++;
        }
        i++;
    }

    // Draw line representing player's direction
    int x0 = map->p_pos[0];
    int y0 = map->p_pos[1];
    int x1 = x0 + cos(map->prev_p_angle) * 20;
    int y1 = y0 + sin(map->prev_p_angle) * 20;
    draw_line(map, x0, y0, x1, y1, 0xFF0000);
}



void clear_player(void *mlx, void *mlx_win, map *map) {
    int i;
    int j;

    i = -1;
    j = -1;
    while (++i != map->p_size)
    {
        while (++j != map->p_size)
            mlx_pixel_put(mlx, mlx_win, map->p_pos[0] + i, map->p_pos[1] + j, 0xffffff);
        j = -1;
    }
    int x0 = map->prev_p_pos[0] + map->p_size / 2;
    int y0 = map->prev_p_pos[1] + map->p_size / 2;
    int x1 = x0 + cos(map->prev_p_angle) * 20;
    int y1 = y0 + sin(map->prev_p_angle) * 20;
    draw_line(map, x0, y0, x1, y1, 0xffffff);
}

int key_press(int keycode, map *map) {
    map->key_states[keycode] = 1;
    return 0;
}

int key_release(int keycode, map *map) {
    map->key_states[keycode] = 0;
    return 0;
}

void drawMap2D (map *map)
{
    int x;
    int y;

    x = -1;
    y = -1;

    while (map->map[++y])
    {
        x = -1;
        while (map->map[y][++x])
        {
            if (map->map[y][x] == '1')
                mlx_put_image_to_window(map->mlx, map->mlx_win, map->wall, x * map->mapS, y * map->mapS);
            else 
                mlx_put_image_to_window(map->mlx, map->mlx_win, map->ground, x * map->mapS, y * map->mapS);
        }
    }
}

void RaysMap3D(map *map)
{
    int r, mx, my, mp, dof;
    double rx, ry, ra, xo, yo, aTan, nTan;

    r = 0;
    ra = map->p_angle;
    while (r < 1)
    {
        //---Check horizontal line---
        dof = 0;
        aTan = -1/tan(ra);
        if (ra > PI)
        {
            ry = (((int)map->p_pos[1] >> 6)<< 6) - 0.0001;
            rx = (map->p_pos[1] - ry) * aTan + map->p_pos[0];
            yo = -64;
            xo = -yo * aTan;
        }
        if (ra < PI)
        {
            ry = (((int)map->p_pos[1] >> 6)<< 6) + 64;
            rx = (map->p_pos[1] - ry) * aTan + map->p_pos[0];
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra==0 || ra == PI)
        {
            rx = map->p_pos[0];
            ry = map->p_pos[1];
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int) (rx) >> 6;
            mp = my * map->mapX + mx;
            if (mp>0 && mp < (map->mapX * map->mapY) && map->map2[mp]== 1)
            {
                dof = 8;
            }
            else 
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        int x0 = map->p_pos[0];
        int y0 = map->p_pos[1];
        draw_line(map, x0, y0, rx, ry, 0x0000FF);
        r++;

        //---Check vetical line---
        dof = 0;
        nTan = -tan(ra);
        if (ra > P2 && ra < P3)
        {
            rx = (((int)map->p_pos[0] >> 6)<< 6) - 0.0001;
            ry = (map->p_pos[1] - rx) * nTan + map->p_pos[1];
            xo = -64;
            yo = -xo * nTan;
        }
        if (ra < P2 || ra > P3)
        {
            rx = (((int)map->p_pos[0] >> 6)<< 6) + 64;
            ry = (map->p_pos[0] - rx) * nTan + map->p_pos[1];
            xo = 64;
            yo = -xo * nTan;
        }
        if (ra==0 || ra == PI)
        {
            rx = map->p_pos[0];
            ry = map->p_pos[1];
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)(rx) >> 6;
            my = (int) (rx) >> 6;
            mp = my * map->mapX + mx;
            if (mp>0 && mp < (map->mapX * map->mapY) && map->map2[mp]== 1)
            {
                dof = 8;
            }
            else 
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        int x20 = map->p_pos[0];
        int y20 = map->p_pos[1];
        draw_line(map, x0, y0, rx, ry, 0x00FF00);
        r++;
    }
}

int in_wall(map *map, double x, double y) {
    double left = map->p_pos[0] + x;
    double right = left + map->p_size - 1;
    double top = map->p_pos[1] + y;
    double bottom = top + map->p_size - 1;

    int left_index = left / map->mapS;
    int right_index = right / map->mapS;
    int top_index = top / map->mapS;
    int bottom_index = bottom / map->mapS;

    for (int i = top_index; i <= bottom_index; i++) {
        for (int j = left_index; j <= right_index; j++) {
            if (i >= 0 && i < map->mapY && j >= 0 && j < map->mapX && map->map[i][j] == '1') {
                return 1;
            }
        }
    }
    return 0;
}

void move_player(map *map) {
    double x = 0;
    double y = 0;

    map->prev_p_pos[0] = map->p_pos[0];
    map->prev_p_pos[1] = map->p_pos[1];
    map->prev_p_angle  = map->p_angle;
    if (map->key_states[KEY_Q]) {
        map->p_angle -= 0.1;
        if (map->p_angle < 0) {
            map->p_angle += 2 * PI;
        }
        map->pd_pos[0] = cos(map->p_angle) * 5;
        map->pd_pos[1] = sin(map->p_angle) * 5;
    }
    if (map->key_states[KEY_D]) {
        map->p_angle += 0.1;
        if (map->p_angle > 2*PI) {
            map->p_angle -= 2 * PI;
        }
        map->pd_pos[0] = cos(map->p_angle) * 5;
        map->pd_pos[1] = sin(map->p_angle) * 5;
    }

    if (map->key_states[KEY_Z]) {
        x = map->pd_pos[0];
        y = map->pd_pos[1];
    }
    if (map->key_states[KEY_S]) {
        x = -map->pd_pos[0];
        y = -map->pd_pos[1];
    }
    /*if (map->key_states[KEY_N]) {
        clear_player(map->mlx, map->mlx_win, map);
        usleep(300000);
    }*/

    if (!in_wall(map, x, y)) {
        double new_x = map->p_pos[0] + x;
        double new_y = map->p_pos[1] + y;

        if (new_x >= 0 && new_x <= (map->mapX - 1) * map->mapS &&
            new_y >= 0 && new_y <= (map->mapY - 1) * map->mapS) {
            //clear_player(map->mlx, map->mlx_win, map);
            mlx_clear_window(map->mlx, map->mlx_win);
            //mlx_put_image_to_window(map->mlx, map->mlx_win, map->wall, 128, 128);
            drawMap2D(map);
            map->p_pos[0] += x;
            map->p_pos[1] += y;
            put_player(map->mlx, map->mlx_win, map);
            RaysMap3D(map);
            usleep(30000);
        }
    }
}




char** createMapArray() {
    char** map = (char**)malloc(8 * sizeof(char*));

    map[0] = "11111111";
    map[1] = "10100001";
    map[2] = "10100001";
    map[3] = "10100001";
    map[4] = "10000001";
    map[5] = "10000101";
    map[6] = "10000001";
    map[7] = "11111111";

    return map;
}

int main(void) {
    map map;
    void *img;

    int i = -1;
    int j = -1;
    map.win_size[0] = 1024;
    map.win_size[1] = 512;
    map.p_pos[0] = 100;
    map.p_pos[1] = 100;
    map.p_angle  = 90;
    map.pd_pos[0] = cos(map.p_angle) * 5;
    map.pd_pos[1] = sin(map.p_angle) * 5;
    map.p_size   = 8;
    map.mapX = 8;
    map.mapY = 8;
    map.mapS = 64;
    map.FOV[0] = 0;
    map.FOV[0] = 0.66;

    int size;
int map3[]=
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};
    
    map.map2 = map3;
    map.map = createMapArray();
    for (i = 0; i < 65536; i++) {
        map.key_states[i] = 0;
    }

    map.mlx = mlx_init();
    map.mlx_win = mlx_new_window(map.mlx, 1024, 512, "Hello world!");
    map.wall = mlx_xpm_file_to_image(map.mlx, "src/wall.xpm", &size, &size);
    map.ground = mlx_xpm_file_to_image(map.mlx, "src/ground.xpm", &size, &size);
    //mlx_put_image_to_window(map.mlx, map.mlx_win, map.wall, 0, 0);
    //put_bg(map.mlx, map.mlx_win, &map);
    drawMap2D(&map);
    put_player(map.mlx, map.mlx_win, &map);
    mlx_hook(map.mlx_win, 2, 1L<<0, (void *)key_press, &map);
    mlx_hook(map.mlx_win, 3, 1L<<1, (void *)key_release, &map);
    mlx_loop_hook(map.mlx, (void *)move_player, &map);
    mlx_loop(map.mlx);
    return 0;
}