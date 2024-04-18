/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:58:13 by biaroun           #+#    #+#             */
/*   Updated: 2024/04/19 01:34:17 by biaroun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define KEY_Z 122
#define KEY_Q 113
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define PI 3.14159265

typedef struct map {
    void *mlx;
    void *mlx_win;
    int win_size[2];

    int mapX;
    int mapY;
    int mapS;
    char **map;

    int p_pos[2];
    int p_angle;
    int p_size;
    int key_states[65536]; // Tableau pour stocker l'état de chaque touche
} map;

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        mlx_pixel_put(mlx, win, x0, y0, color);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

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
    while (++i != lengh - 1)
    {
        while (++j != lengh - 1)
            mlx_pixel_put(map->mlx, map->mlx_win, x + i, y + j, color);
        j = -1;
    }
}

void put_player(void *mlx, void *mlx_win, map *map) 
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (++i != map->p_size)
    {
        while (++j != map->p_size)
            mlx_pixel_put(mlx, mlx_win, map->p_pos[0] + i, map->p_pos[1] + j, 0xFF0000);
        j = -1;
    }
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
                put_square(map, x * map->mapS, y * map->mapS, map->mapS, 0x808080);
            else 
                put_square(map, x * map->mapS, y * map->mapS, map->mapS, 0xffffff);
        }
    }
}

int in_wall(map *map, int x, int y)
{
    printf("x = %i y = %i\n",(map->p_pos[1]) , (map->p_pos[0]));
    printf("x = %i y = %i\n",(map->p_pos[1] - y)  / 64 , (map->p_pos[0] - x) / 64);
    if (map->map[(map->p_pos[1] + y) / 64][(map->p_pos[0] + x) / 64] == '1')
        return (1);
    return (0);
}

void move_player(map *map) {
    int m;
    int x;
    int y;

    m = 0;
    x = 0;
    y = 0;
    if (map->key_states[KEY_ESC])
    {
        exit(0);
    }
    if (map->key_states[KEY_Z])
    {
        y = -3;
        m = 1;
        if (in_wall(map, x, y))
            y = 0;
    }
    if (map->key_states[KEY_S])
    {
        y = 3;
        m = 1;
        if (in_wall(map, x, y + 7))
            y = 0;
    }
    if (map->key_states[KEY_Q])
    {
        x = -3;
        m = 1;
        if (in_wall(map, x, y))
            x = 0;
    }
    if (map->key_states[KEY_D])
    {
        x = 3;
        m = 1;
        if (in_wall(map, x + 7, y))
            x = 0;
    }

    if (m)
    {
        drawMap2D(map);
        map->p_pos[0] += x;
        map->p_pos[1] += y;
        put_player(map->mlx, map->mlx_win, map);
        usleep(30000);
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
    map.p_angle  = 0;
    map.p_size   = 8;
    map.mapX = 8;
    map.mapY = 8;
    map.mapS = 64;

    
    map.map = createMapArray();
    for (i = 0; i < 65536; i++) {
        map.key_states[i] = 0;
    }

    map.mlx = mlx_init();
    map.mlx_win = mlx_new_window(map.mlx, 1024, 512, "Hello world!");
    img = mlx_xpm_file_to_image(map.mlx, "test.xpm", 1920, 1080);
    //put_bg(map.mlx, map.mlx_win, &map);
    drawMap2D(&map);
    put_player(map.mlx, map.mlx_win, &map);
    mlx_hook(map.mlx_win, 2, 1L<<0, (void *)key_press, &map);
    mlx_hook(map.mlx_win, 3, 1L<<1, (void *)key_release, &map);
    mlx_loop_hook(map.mlx, (void *)move_player, &map);
    mlx_loop(map.mlx);
    return 0;
}