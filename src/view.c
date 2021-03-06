//
// Created by sadegh on 12/19/18.
//

#include "view.h"
#include "structs.h"
#include "logic.h"
#include "physics.h"
#include "playwav.h"
#include "saveandload.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>

const double pi = 3.14159265358979323846264338327950288419716939937510;
int EXIT = 10000;
int is_selected;
int FPS;
int NOS;//number of saves
long long int time_passed_during_game;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *imageSurface = NULL;
SDL_Surface *windowSurfae;
int tank_radius = 18;
int x_max = 11 * 100 + 50;
int y_max = 6 * 100 + 100;
int r_msg;
int g_msg;
int b_msg;

void initialize_game_values(Map *map) {
    win_score = 20;
    is_selected = 0;
    map->frames = 0;
    map->game_pause = 1;
    map->first_menu = 1;
    map->game_finished = 0;
    srand((unsigned int)(time(NULL)));
    r_msg = (rand() % 80) + 0; g_msg = (rand() % 80) + 80; b_msg = (rand() % 80) + 160;
    tanks_rand_place(map);
    for (int i = 0; i < 3; ++i) {
        map->tank[i].is_alive = 1;
        map->tank[i].score = 0;
        for (int j = 0; j < 3; ++j) {
            if (i != j) {
                map->tank[i].color[j] = 50;
            } else {
                map->tank[i].color[j] = 255;
            }
        }
        for (int k = 0; k < 6; ++k) {
            map->tank[i].bullet[k].is_fired = 0;
        }
    }
    zero_key_pressed(map);
}

void zero_key_pressed(Map *map) {
    for (int i = 0; i < 3; ++i) {
        for (int r = 0; r < 4; ++r) {
            map->tank[i].key_pressed[r] = 0;
        }
    }
}

void tanks_rand_place(Map *map) {
    FPS = 33;
    srand((unsigned int)(time(NULL)));
    for (int i = 0; i < 3; ++i) {
        map->tank[i].x = (rand() % 11) * 100 + 20 + 50 + (rand() % 10);
        map->tank[i].y = (rand() % 6) * 100 + 20 + 50 + (rand() % 10);
        map->tank[i].angle = (rand() % 360) * pi / 180;
        map->tank[i].is_alive = 1;
        map->tank[i].powered_up = 0;
        map->tank[i].frag_section = 0;
        map->tank[i].have_mine = 0;
        for (int j = 0; j < 6; ++j) {
            map->tank[i].bullet[j].is_fired = 0;
        }
    }
    for (int i = 0; i < 5; ++i) {
        map->powerup[i].is_on = 0;
    }
    for (int i = 0; i < 3; ++i) {
        map->tank[i].fragBomb.is_released = 0;
        for (int j = 0; j < 9; ++j) {
            map->tank[i].fragBomb.bullet[j].is_fired = 0;
        }
    }
    for (int i = 0; i < 15; ++i) {
        map->mine[i].is_planted = 0;
        map->mine[i].frame_from_born = 0;
        map->mine[i].is_in_range = 0;
        map->mine[i].frame_from_in_range = 0;
    }
}

void powerup_rand_place(Powerup *powerup) {
    srand((unsigned int)(time(NULL)));
    powerup->x = (rand() % 11) * 100 + 20 + 50 + (rand() % 30) - 15;
    powerup->y = (rand() % 6) * 100 + 20 + 50 + (rand() % 30) - 15;
}

void init_window() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return;
    window = SDL_CreateWindow("AlterTank",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              x_max, y_max,
                              SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

void render_clear() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
}

void present_window() {
    SDL_RenderPresent(renderer);
//    SDL_UpdateWindowSurface(window);
//    SDL_BlitSurface(imageSurface, NULL, windowSurfae, NULL);
    SDL_Delay(1000 / FPS);
}

void quit_window() {
    SDL_Quit();
}

void draw_first_menu(Map *map) {
    draw_dancing_lines(map, renderer);
    int first_y = 120;
    draw_button("NEW GAME", x_max / 2, 1.5 * first_y, 200, 100, 0, 255);
    draw_button("LOAD GAME", x_max / 2, 2.5 * first_y, 200, 100, 1, 255);
    draw_button("QUIT", x_max / 2, 3.5 * first_y, 200, 100, 2, 255);
    SDL_RenderSetScale(renderer, 2.5, 2.5);
    stringRGBA(renderer, 30, 10, "Use Up and Down keys and then Enter key to select!", 0, 0, 0, 255);
    SDL_RenderSetScale(renderer, 1, 1);
}

void draw_background() {
    windowSurfae = SDL_GetWindowSurface(window);
    imageSurface = SDL_LoadBMP("test.bmp");
    if (imageSurface == NULL) {
        printf("Error :%s\n", SDL_GetError());
    } else {
        printf("OK\n");
    }
}

void draw_game_menu() {
    int length = 120;
    roundedBoxRGBA(renderer, x_max/2 - 150, y_max/2 - 210, x_max/2 + 150, y_max/2 + 210, 20, 255, 99, 99, 160);
    draw_button("RESUME", x_max / 2, y_max/2 - 1 * length, 200, 100, 0, 160);
    draw_button("SAVE GAME", x_max / 2, y_max/2 + 0 * length, 200, 100, 1, 160);
    draw_button("MAIN MENU", x_max / 2, y_max/2 + 1 * length, 200, 100, 2, 160);
}

void draw_button(char *string, int x, int y, int a, int b, int NUMBER, int alpha) {
    if (NUMBER > 9) {
        int red = 100, green = 100, blue = 100;
        switch(NUMBER) {
            case 10:
                red = 255;
                break;
            case 11:
                green = 255;
                break;
            case 12:
                blue = 255;
                break;
        }
        roundedBoxRGBA(renderer, x - a/2, y - b/2, x + a/2, y + b/2, 30, red, green, blue, alpha);
        stringRGBA(renderer, x - 4*strlen(string) + 3, y, string, 0, 0, 0, 255);
        return;
    }
    int color, color2, radian;
    if (NUMBER == is_selected) {
        color = 0;
        color2 = 180;
        radian = 40;
    } else {
        color = 200;
        color2 = 0;
        radian = 30;
    }
    roundedBoxRGBA(renderer, x - a/2, y - b/2, x + a/2, y + b/2, radian, color, color2, color, alpha);
    stringRGBA(renderer, x - 4*strlen(string) + 3, y, string, 0, 0, 0, 255);
}

void draw_shapes(Map *map) {
    draw_walls(map);
    for (int i = 0; i < 15; ++i) {
        Mine *purpose = &(map->mine[i]);
        if (purpose->is_planted && (purpose->frame_from_born < 60 || purpose->is_in_range) ) {
            draw_mine(purpose);
            if (purpose->frame_from_born > 80 && purpose->is_in_range) {
                filledCircleRGBA(renderer, purpose->x, purpose->y, 2 * tank_radius, 255, 0, 255, 160);
            }
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (map->powerup[i].is_on) {
            draw_powerup(&(map->powerup[i]));
        }
    }
    for (int i = 0; i < 3; ++i) {
        if (map->tank[i].is_alive) {
            draw_tank(&(map->tank[i]));
        }
        if (map->tank[i].fragBomb.bullet[0].is_fired == 0) {
            map->tank[i].fragBomb.is_released = 0;
            if (map->tank[i].frag_section == 2) {
                map->tank[i].frag_section = 0;
                map->tank[i].powered_up = 0;
            }
        }
        if (map->tank[i].fragBomb.is_released) {
            draw_bomb(&(map->tank[i].fragBomb.bullet[0]));
        }
        for (int j = 0; j < 6; ++j) {
            if (map->tank[i].bullet[j].is_fired) {
                draw_bullet(&(map->tank[i].bullet[j]));
            }
        }
        for (int j = 1; j < 9; ++j) {
            Bullet *purpose = &(map->tank[i].fragBomb.bullet[j]);
            if (purpose->is_fired) {
                draw_bullet(purpose);
            }
        }
    }
    draw_scores(map);
}

void draw_powerup(Powerup *powerup) {
    boxRGBA(renderer, powerup->x - 10, powerup->y - 10, powerup->x + 10, powerup->y + 10, 140, 140, 140, 255);
    switch (powerup->type) {
        case 0:
            filledCircleRGBA(renderer, powerup->x, powerup->y, 7, 15, 15, 15, 200);
            break;
        case 1:
            //can better font?
            stringRGBA(renderer, powerup->x - 4, powerup->y - 4, "M", 255, 0, 0, 255);
            break;
    }
}

char *convert_number_to_string(long long int number) {
    char *mystring = malloc(100);
    if (number == 0) {
        mystring[0] = '0';
        mystring[1] = '\0';
        return mystring;
    }
    int tedad_ragham = 0;
    long long int x = number;
    while (x) {
        x /= 10;
        tedad_ragham++;
    }
    for (int i = tedad_ragham - 1; i > -1; i--) {
        mystring[i] = (char) ('0' + (number % 10));
        number /= 10;
    }
    mystring[tedad_ragham] = '\0';
    return mystring;
}

void draw_scores(Map *map) {
    int distance = 200;
    for (int i = 0; i < 3; ++i) {
        draw_button(convert_number_to_string(map->tank[i].score), x_max/2 + (i - 1)*distance, (y_max * 16) / 17, 20, 20, 10 + i, 255);
    }
}

void draw_walls(Map *map) {
    for (int i = 0; i < map->number_of_walls; ++i) {
        draw_wall(map->walls + i);
    }
}

void draw_wall(Wall *wall) {
//    thickLineRGBA(renderer, wall->x1, wall->y1, wall->x2, wall->y2, 5, 0, 0, 0, 255);
    lineRGBA(renderer, wall->x1, wall->y1, wall->x2, wall->y2, 0, 0, 0, 255);
}

void draw_tank(Tank *tank) {
    filledCircleRGBA(renderer, tank->x, tank->y, tank_radius, tank->color[0], tank->color[1], tank->color[2], 255);
    draw_tank_gun(tank);
}

void draw_bullet(Bullet *bullet) {
    filledCircleRGBA(renderer, bullet->x, bullet->y, 3, 20, 20, 20, 255);
}

void draw_bomb(Bullet *bullet) {
    filledCircleRGBA(renderer, bullet->x, bullet->y, 5, 20, 20, 20, 255);
}

void draw_mine(Mine *mine) {
    filledCircleRGBA(renderer, mine->x, mine->y, 10, 0, 0, 0, 255);
}

void draw_tank_gun(Tank *tank) {
    int x_gun = tank->x + (int) ((tank_radius + 3) * cos(tank->angle));
    int y_gun = tank->y + (int) ((tank_radius + 3) * sin(tank->angle));
    filledCircleRGBA(renderer, x_gun, y_gun, 5, 90, 90, 90, 255);
}

int maximum(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

void draw_dancing_lines(Map *map, SDL_Renderer *sdl_renderer) {
    for (int i = 0; i < 30; ++i) {
        Line *line = &(map->lines[i]);
        thickLineRGBA(sdl_renderer, line->x1, line->y1, line->x2, line->y2, 4, line->color[0] + rand() % 60, line->color[1] + rand() % 60, line->color[2] + rand() % 60, 255);
        //move lines
        line->x1 -= 4;line->x2 += 2;line->y1 += 2;line->y2 -= 4;
        line->x1 %= x_max;line->x2 %= x_max;
        line->y1 %= y_max;line->y2 %= y_max;
        if (line->x1 < 0) {line->x1 = x_max;}
        if (line->y2 < 0) {line->y2 = y_max;}
    }
}

void draw_results(Map *map) {
    //dancing lines
    draw_dancing_lines(map, renderer);
    //score of tanks
    for (int i = 0; i < 3; ++i) {
        Tank *tank = &(map->tank[i]);
        roundedBoxRGBA(renderer, x_max/2 - 200, y_max/2 - 200 + 150*i, x_max/2 + 200, y_max/2 - 100 + 150*i, 15, maximum(100, tank->color[0]), maximum(100, tank->color[1]), maximum(100, tank->color[2]), 255);
        SDL_RenderSetScale(renderer, 3, 3);
        stringRGBA(renderer, (x_max/2 - 150) / 3, (y_max/2 - 165 + 150*i) / 3, convert_number_to_string(tank->score), 0, 0, 0, 255);
        if (tank->score == win_score) {
            stringRGBA(renderer, (x_max/2 - 10) / 3, (y_max/2 - 165 + 150*i) / 3, "Winner!!", 0, 0, 0, 255);
        }
        SDL_RenderSetScale(renderer, 1, 1);
    }
    //passed time
    roundedBoxRGBA(renderer, x_max/2 - 165, y_max/2 - 220 + 150*3, x_max/2 + 165, y_max/2 - 140 + 150*3, 15, 120, 120, 120, 255);
    SDL_RenderSetScale(renderer, 3, 3);
    stringRGBA(renderer, (x_max/2 - 275) / 3, (y_max/2 - 120 - 150*1) / 3, "Press enter to continue", r_msg, g_msg, b_msg, 255);
    stringRGBA(renderer, (x_max/2 - 150) / 3, (y_max/2 - 192 + 150*3) / 3, "TIME:   m   s", 0, 0, 0, 255);
    stringRGBA(renderer, (x_max/2 - 20) / 3, (y_max/2 - 192 + 150*3) / 3, convert_number_to_string(time_passed_during_game / 60), 0, 0, 0, 255);
    stringRGBA(renderer, (x_max/2 + 80) / 3, (y_max/2 - 192 + 150*3) / 3, convert_number_to_string(time_passed_during_game % 60), 0, 0, 0, 255);
    SDL_RenderSetScale(renderer, 1, 1);
    //changing color
    r_msg = (r_msg + rand() % 5) % 255;
    g_msg = (g_msg + rand() % 5) % 255;
    b_msg = (b_msg + rand() % 5) % 255;
}

int event_handling(Map *map) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXIT;
        if (map->game_pause == 0) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    //tank0
                    case SDLK_DOWN:
                        map->tank[0].key_pressed[0] = 1;
                        break;
                    case SDLK_UP:
                        map->tank[0].key_pressed[1] = 1;
                        break;
                    case SDLK_RIGHT:
                        map->tank[0].key_pressed[2] = 1;
                        break;
                    case SDLK_LEFT:
                        map->tank[0].key_pressed[3] = 1;
                        break;
                        //tank1
                    case SDLK_d:
                        map->tank[1].key_pressed[0] = 1;
                        break;
                    case SDLK_e:
                        map->tank[1].key_pressed[1] = 1;
                        break;
                    case SDLK_f:
                        map->tank[1].key_pressed[2] = 1;
                        break;
                    case SDLK_s:
                        map->tank[1].key_pressed[3] = 1;
                        break;
                        //tank2
                    case SDLK_KP_5:
                        map->tank[2].key_pressed[0] = 1;
                        break;
                    case SDLK_KP_8:
                        map->tank[2].key_pressed[1] = 1;
                        break;
                    case SDLK_KP_6:
                        map->tank[2].key_pressed[2] = 1;
                        break;
                    case SDLK_KP_4:
                        map->tank[2].key_pressed[3] = 1;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    //tank0
                    case SDLK_ESCAPE:
                        zero_key_pressed(map);
                        map->game_pause = 1;
                        map->first_menu = 0;
                        break;
                    case SDLK_DOWN:
                        map->tank[0].key_pressed[0] = 0;
                        break;
                    case SDLK_UP:
                        map->tank[0].key_pressed[1] = 0;
                        break;
                    case SDLK_RIGHT:
                        map->tank[0].key_pressed[2] = 0;
                        break;
                    case SDLK_LEFT:
                        map->tank[0].key_pressed[3] = 0;
                        break;
                    case SDLK_m:
                        fire(&(map->tank[0]), map);
                        break;
                        //tank1
                    case SDLK_d:
                        map->tank[1].key_pressed[0] = 0;
                        break;
                    case SDLK_e:
                        map->tank[1].key_pressed[1] = 0;
                        break;
                    case SDLK_f:
                        map->tank[1].key_pressed[2] = 0;
                        break;
                    case SDLK_s:
                        map->tank[1].key_pressed[3] = 0;
                        break;
                    case SDLK_q:
                        fire(&(map->tank[1]), map);
                        break;
                        //tank2
                    case SDLK_KP_5:
                        map->tank[2].key_pressed[0] = 0;
                        break;
                    case SDLK_KP_8:
                        map->tank[2].key_pressed[1] = 0;
                        break;
                    case SDLK_KP_6:
                        map->tank[2].key_pressed[2] = 0;
                        break;
                    case SDLK_KP_4:
                        map->tank[2].key_pressed[3] = 0;
                        break;
                    case SDLK_KP_0:
                        fire(&(map->tank[2]), map);
                        break;
                }
            }
        } else {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    //tank0
                    case SDLK_DOWN:
                        //map->tank[0].key_pressed[0] = 1;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    //tank0
                    case SDLK_ESCAPE:
                        if (map->first_menu == 0) {
                            map->game_pause = 0;
//                            playingforme();
                        }
                        break;
                    case SDLK_DOWN:
                        is_selected = (is_selected + 1) % 3;
                        break;
                    case SDLK_UP:
                        is_selected--;
                        if (is_selected == -1) {
                            is_selected = 2;
                        }
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        if (map->game_finished) {
                            random_line_place(map);
                            map->game_finished = 0;
                            map->game_pause = 1;
                            map->first_menu = 1;
                            is_selected = 0;
                            break;
                        }
                        switch (is_selected) {
                            case 0:
                                if (map->first_menu) {
                                    generate_map(map);
                                    initialize_game_values(map);
                                }
                                map->game_pause = 0;
                                break;
                            case 1:
                                if (map->first_menu) {
                                    NOS = number_of_saves();
                                    if (NOS) {
                                        int load_number = get_load_number(map, renderer);
                                        if (load_number == EXIT) {
                                            return EXIT;
                                        }
                                        load_game(map, load_number);//felan shomareh 1
                                        map->first_menu = 0;
                                        map->game_pause = 0;
                                    }
                                } else {
                                    save_game(map);
                                }
                                break;
                            case 2:
                                if (map->first_menu) {
                                    return EXIT;
                                } else {
                                    map->first_menu = 1;
                                }
                        }
                        break;
                }
            }
        }
    }
    move_tank(map);
    turn_tank(map);
}