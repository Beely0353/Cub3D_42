/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biaroun <biaroun@student.42nice.fr> >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:58:13 by biaroun           #+#    #+#             */
/*   Updated: 2024/05/14 14:12:58 by biaroun          ###   ########.fr       */
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

typedef struct map {
    void *mlx;
    void *mlx_win;
    int win_size[2];

    int mapX;
    int mapY;
    int mapS;
    char **map;
    int  **map3;

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
    // Draw line representing player's direction
    int x0 = map->p_pos[0] + map->p_size / 2;
    int y0 = map->p_pos[1] + map->p_size / 2;
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
        clear_player(map->mlx, map->mlx_win, map);
        if (map->p_angle < 0) {
            map->p_angle += 2 * PI;
        }
        map->pd_pos[0] = cos(map->p_angle) * 5;
        map->pd_pos[1] = sin(map->p_angle) * 5;
    }
    if (map->key_states[KEY_D]) {
        map->p_angle += 0.1;
        clear_player(map->mlx, map->mlx_win, map);
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
            clear_player(map->mlx, map->mlx_win, map);
            mlx_clear_window(map->mlx, map->mlx_win);
            //mlx_put_image_to_window(map->mlx, map->mlx_win, map->wall, 128, 128);
            drawMap2D(map);
            map->p_pos[0] += x;
            map->p_pos[1] += y;
            put_player(map->mlx, map->mlx_win, map);
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

int raycasting(map *map)
{
    double posX = 4, posY = 4;
    double dirX = -1, dirY = 0;
    double planeX = 0, planeY = 0.66;
    int h = 20;
    
    double time = 0;
    double oldTime = 0;
    int x = 0;
    int w = 1024; //longueur ecran
    
    /*while (1)
    {*/
        x = 0;
        while (x < w)
        {
            double cameraX = 2 * x / (double) w - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            
            //which box of the map we're in
            int mapX = (int) posX;
            int mapY = (int) posY;

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
            double perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?
            

            //calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }


            //perform DDA
            while (hit == 0)
            {
                //jump to next map square, either in x-direction, or in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                printf("test = %d / %d\n", mapX, mapY);
                printf("test2 = %d\n", map->map3[mapX][mapY]);
                //Check if ray has hit a wall
                if (map->map3[mapX][mapY] > 0) 
                    hit = 1;
            }

            if(side == 0) 
                perpWallDist = (sideDistX - deltaDistX);
            else          
                perpWallDist = (sideDistY - deltaDistY); 

            printf("test1 \n");
            //Calculate height of line to draw on screen
            int lineHeight = (int)(h / perpWallDist);

            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + h / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if(drawEnd >= h)drawEnd = h - 1;
            draw_line(map, 0, drawEnd, 0, drawStart, 0xFF0000);
            
            x++;
        }
    //}
}

int** createMap3Array() {
    // Allouer de la mémoire pour le tableau de pointeurs
    int** map = (int**)malloc(8 * sizeof(int*));

    // Définition du schéma du tableau
    int schema[8][8] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Allouer de la mémoire et initialiser chaque ligne du tableau en utilisant les boucles
    for (int i = 0; i < 8; i++) {
        map[i] = (int*)malloc(8 * sizeof(int));
        for (int j = 0; j < 8; j++) {
            map[i][j] = schema[i][j];
        }
    }

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
    map.pd_pos[0] = cos(map.p_angle) * 5;
    map.pd_pos[1] = sin(map.p_angle) * 5;
    map.p_size   = 9;
    map.mapX = 8;
    map.mapY = 8;
    map.mapS = 32;
    map.FOV[0] = 0;
    map.FOV[0] = 0.66;
    int size;
    
    map.map = createMapArray();
    for (i = 0; i < 65536; i++) {
        map.key_states[i] = 0;
    }

    map.map3 = createMap3Array();
    map.mlx = mlx_init();
    map.mlx_win = mlx_new_window(map.mlx, 1024, 512, "Hello world!");
    map.wall = mlx_xpm_file_to_image(map.mlx, "src/wall.xpm", &size, &size);
    map.ground = mlx_xpm_file_to_image(map.mlx, "src/ground.xpm", &size, &size);
    //mlx_put_image_to_window(map.mlx, map.mlx_win, map.wall, 0, 0);
    //put_bg(map.mlx, map.mlx_win, &map);
    raycasting(&map);
    /*drawMap2D(&map);
    put_player(map.mlx, map.mlx_win, &map);
    mlx_hook(map.mlx_win, 2, 1L<<0, (void *)key_press, &map);
    mlx_hook(map.mlx_win, 3, 1L<<1, (void *)key_release, &map);
    mlx_loop_hook(map.mlx, (void *)move_player, &map);*/
    mlx_loop(map.mlx);
    return 0;
}