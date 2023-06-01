#include "program.h"
#include "menu.c"
struct children{
    int row, column;
    bool happy;
};
void game(int y, int x,int lines, int cols, char world[lines][cols], int boundaries[], int n_map, int count_shots, int children, struct children child[children],int info[2]);

int main(){
    initscr();
    start_color();

    init_pair(1, COLOR_BLACK, COLOR_WHITE);    
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(4, COLOR_RED, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_RED);
    init_pair(6, COLOR_BLACK, 0013);
    init_pair(7, COLOR_BLACK, COLOR_MAGENTA); 
    init_pair(9, COLOR_BLUE, COLOR_BLUE); 
    init_pair(11, COLOR_WHITE,0020);
    init_pair(13, 0017, 0014);
    init_pair(14, COLOR_RED, COLOR_BLACK);
    init_pair(15, COLOR_BLACK, 0337);
    init_pair(16, COLOR_BLACK, 0324);
    init_pair(17, COLOR_BLACK, COLOR_RED);
    init_pair(18, COLOR_BLACK, 0017);
    init_pair(19, COLOR_GREEN, COLOR_BLACK);
    init_pair(20, COLOR_BLUE, COLOR_BLACK);
    init_pair(21, COLOR_RED, COLOR_BLACK);
    init_pair(22, COLOR_CYAN, COLOR_BLACK);

    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    all();

    endwin();

  return 0;
}
void all(){ 
    char world[LINES][COLS];
    int boundaries[4];
    int lines = 34;
    int cols = 130;
    boundaries_func(lines, cols, boundaries);
    int y = boundaries[1]-11;
    int x = boundaries[2];
    if(LINES < lines || COLS < cols){
        endwin();
        fprintf(stderr, "Window is too small.\n");
        exit(EXIT_FAILURE);
    }
    char text[][16] = {
		{"     Start     "},
		{"  Information  "},
		{"     Quit      "}
	};
    char logo[8][78] = {
        {"                                                                             "},
        {"   ____   _       U  ___ u              _   _                  ____ U _____ u"},
        {"U /\"___| |\"|       \\/\"_ \\/__        __ | \\ |\"|       ___    U /\"___|\\| ___\"|/"},
        {"\\| | u U | | u     | | | |\\\"\\      /\"/<|  \\| |>     |_\"_|   \\| | u   |  _|\"  "},
        {" | |/__ \\| |/__.-,_| |_| |/\\ \\ /\\ / /\\U| |\\  |u      | |     | |/__  | |___  "},
        {"  \\____| |_____|\\_)-\\___/U  \\ V  V /  U|_| \\_|     U/| |\\u    \\____| |_____| "},
        {" _// \\\\  //  \\\\      \\\\  .-,_\\ /\\ /_,-.||   \\\\,-.-,_|___|_,-._// \\\\  <<   >> "},
        {"(__)(__)(_\")(\"_)    (__)  \\_)-'  '-(_/ (_\")  (_/ \\_)-' '-(_/(__)(__)(__) (__)"}
    };
    int info[] = {-1,1};
    int choosen = 0;
    int num = 0;

    do{
        if(info[1]==1 && choosen == 0){
            draw_logo(8, 78, logo, 10,1);
            choosen = menu(18,3,16,text, -1, 14);
            if(choosen == -1){
                endwin();
                exit(EXIT_SUCCESS);
            }
        }
        if(choosen == 0){
            if(info[0] != 0 || info[1]!= 0) num = levels();
            if(num==-1) continue;
            if(num==0){
                int children = 1;
                struct children child[children];
                for(int i = 0; i < children; i++){
                    child[i].happy= false;
                }
                child[0].row = y+2;
                child[0].column = boundaries[3]- 12;
                init_pair(8, COLOR_GREEN, 0026);  
                init_pair(10, COLOR_BLACK, COLOR_CYAN);
                init_pair(15, COLOR_BLACK, 0337);
                game(y, x,lines, cols, world, boundaries, num, 1, children, child, info);}

            else if(num==1) {
                int children = 3;
                struct children child[children];
                for(int i = 0; i < children; i++){
                    child[i].happy= false;
                }
                child[0].row = y+2;
                child[0].column = boundaries[3]- 12;
                child[1].row = y-6;
                child[1].column = boundaries[3]- 12;
                child[2].row = y-14;
                child[2].column = boundaries[3]- 12;
                init_pair(8, COLOR_GREEN, 0026);  
                init_pair(10, 0337, 0021);
                init_pair(15, COLOR_BLACK, 0337);
                game(y, x,lines, cols, world, boundaries, num, 3, children, child, info);
            }
            else{
                int children = 1;
                struct children child[children];
                for(int i = 0; i < children; i++){
                    child[i].happy= false;
                }
                child[0].row = boundaries[0];
                child[0].column = boundaries[2];
                init_pair(8, COLOR_YELLOW, 0013);  
                init_pair(10, COLOR_BLACK, 0074);
                init_pair(15, COLOR_BLACK, 0027);
                game(y, x,lines, cols, world, boundaries, num, 1, children, child, info);
            }
        }
        else if(choosen == 1){
            instruction();
            choosen = 0;
        }
    }while(info[1]!=2 && choosen != 2);
    
}
void game(int y, int x,int lines, int cols, char world[lines][cols], int boundaries[], int n_map, int count_shots, int children, struct children child[children], int info[2]){
    char player[][13] = {
        {"     {_}     "},
        {"     /*\\     "},
        {"    /_*_\\    "},
        {"   {('o')}   "},
        {"C{  [^*^]  }D"},
        {"    [ * ]    "},
        {"   /  Y  \\   "},
        {"  _\\__|__/_  "},
        {"(____/ \\____)"}
    };
    char shot_char[][7] = {
        {"   ()  "},
        {"  (__) "},
        {" (____)"},
        {"  \\/\\/ "},
        {"   \\/  "}
    };
    char sad_child[][11] = {
        {" _________ "},
        {"|         |"},
        {"| ___ ___ |"},
        {"|         |"},
        {"+---------+"},
        {"   |___|   "},
        {"   _| |_   "},
    };
    char happy_child[][11] = {
        {" _________ "},
        {"|  _   _  |"},
        {"| | | | | |"},
        {"| <  O  > |"},
        {"+---------+"},
        {"  ~|___|~  "},
        {"   _| |_   "},
    };
    struct timespec ts = {
        .tv_sec = 0,                    
        .tv_nsec = 100000000
    };
    struct shoot{
        int row, column, count;
        bool active;
    };
    clear();
    
    int c;
    int coor_xy[2];
    bool main_sc = false;

    struct shoot shot;
    shot.active = false;
    shot.count = count_shots; 

    int win = 0;
    if(n_map == 0) map1(boundaries[0], boundaries[2], lines, cols, world);
    else if(n_map == 1) map2(boundaries[0], boundaries[2], lines, cols, world);
    else map3(boundaries[0], boundaries[2], lines, cols, world);

    print_hero(y, x, 9, 13, player);
    for(int i = 0; i < children; i++){
        print_child(child[i].row, child[i].column, 7, 11, sad_child, happy_child, lines, cols, world, child[i].happy);
    }
    attron(A_BOLD); 
    print_shots(boundaries[2], boundaries[0], lines, cols, world);
    print_shot(boundaries[0] + 2, boundaries[2]+cols - 15, 5, 7, shot_char,13);
    attron(COLOR_PAIR(13));
    mvprintw(boundaries[0] + 4, boundaries[2]+cols - 5,"%d",shot.count); 
    attroff(COLOR_PAIR(13));
    attroff(A_BOLD);
    int poz = 0;
    while(win!=children){    
        if(shot.active) {
            ts.tv_nsec = 40000000;
            if(shot.column < boundaries[3]-7 && detect(shot.row, shot.column, 5, 7, lines, cols, world, 's')) {
                print_shot(shot.row, shot.column, 5, 7, shot_char, 10);   
                shot.column++;
            }
            else{
                print_empty(shot.row, shot.column, 5, 7, 'a');
                shot.active = false;
            }
            for(int i = 0; i < children; i++){
                if(check_shot(shot.row, shot.column, 5, 7, child[i].row, child[i].column, 7, 11) && !child[i].happy){
                    child[i].happy = true;
                    win++;
                }
            }
            
        }
        refresh();
        nanosleep(&ts,NULL);

        c = getch();
        if(c == KEY_LEFT || c == 'A'|| c == 'a'){
            print_empty(y, x, 9, 13, 'l');
        }
        else if(c == 'D'|| c == 'd' || c == KEY_RIGHT){
            print_empty(y, x, 9, 13, 'r');
        }
        switch(c){
            case KEY_LEFT:
            case 'A':
            case 'a':
                x = (x > boundaries[2] && detect(y, x, 9, 13, lines, cols, world, 'l')) ? x - 1 : x;
                y = falling(y, x, 9, 13, player, lines, cols, world, boundaries[0]);
                break;
            case KEY_RIGHT:
            case 'D':
            case 'd':
                x = (x + 13 < boundaries[3] && detect(y, x, 9, 13, lines, cols, world, 'r')) ? x + 1: x;
                y = falling(y, x, 9, 13, player, lines, cols, world, boundaries[0]);
                break;
            case ' ':
                if(!shot.active){
                    shot.row = y + 3;
                    shot.column = x + 13;
                    if(detect(shot.row, shot.column, 5, 7, lines, cols, world, 'r') && x < boundaries[3]-20 && shot.count>0){
                        shot.active = 1;
                        shot.count--;
                        attron(COLOR_PAIR(13));
                        attron(A_BOLD);
                        mvprintw(boundaries[0] + 4, boundaries[2]+cols - 5,"%d",shot.count);
                        attroff(A_BOLD);
                        attroff(COLOR_PAIR(13)); 
                    }
                }                
                break;
            case KEY_UP:
            case 'W':
            case 'w':
                if(!shot.active) jump(y, x, 9, 13, player, 0, 34, 130,world, coor_xy, boundaries[2], boundaries[3]);
                break;
            case 'Q':
            case 'q':
                if(!shot.active){
                    jump(y, x, 9, 13, player, -1, 34, 130,world, coor_xy, boundaries[2], boundaries[3]);
                    x = coor_xy[0];
                    y = coor_xy[1];
                    y = falling(y, x, 9, 13, player, lines, cols, world, boundaries[0]);
                } 
                break;
            case 'E':
            case 'e':
                if(!shot.active){
                    jump(y, x, 9, 13, player, 1, lines, cols, world, coor_xy, boundaries[2], boundaries[3]);
                    x = coor_xy[0];
                    y = coor_xy[1];
                    y = falling(y, x, 9, 13, player, lines, cols, world, boundaries[0]);
                }
                break;
            case KEY_BACKSPACE:
                main_sc = true;
        }
        if(main_sc || y==boundaries[1]-9){
            win = -1;
            break;
        }
        ts.tv_nsec = 15000000;
        for(int i = 0; i < children; i++){
            print_child(child[i].row, child[i].column, 7, 11, sad_child, happy_child, lines, cols, world, child[i].happy);
        }
        //Maps
        if(n_map==1 && x - boundaries[2] > 47){
            attron(COLOR_PAIR(8));
            for(int i = 25 + boundaries[2]; i < 41 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 13,i,"#");
                world[boundaries[0] + lines - 13][i] = '1';
                mvprintw(boundaries[0] + lines - 14,i,"#");
                world[boundaries[0] + lines - 14][i] = '1';
            }
            for(int i = 3 + boundaries[2]; i < 18 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 17,i,"#");
                world[boundaries[0] + lines - 17][i] = '1';
                mvprintw(boundaries[0] + lines - 18,i,"#");
                world[boundaries[0] + lines - 18][i] = '1';
            }
            attron(COLOR_PAIR(8));
        }
        if(n_map==1 && x - boundaries[2] > 67){
            attron(COLOR_PAIR(8));
            for(int i = 81 + boundaries[2]; i < 94 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 10,i,"#");
                world[boundaries[0] + lines - 10][i] = '1';
            }
            attron(COLOR_PAIR(8));
        }
        if(n_map==2 && x - boundaries[2] >= 116 && poz == 0){
            attron(COLOR_PAIR(8));
            for(int i = 91 + boundaries[2]; i < 104 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 7,i,"o");
                world[boundaries[0] + lines - 7][i] = '1';
                mvprintw(boundaries[0] + lines - 6,i,"o");
                world[boundaries[0] + lines - 6][i] = '1';
            }
            for(int i = 60 + boundaries[2]; i < 74 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 10,i,"o");
                world[boundaries[0] + lines - 10][i] = '1';
                 mvprintw(boundaries[0] + lines - 9,i,"o");
                world[boundaries[0] + lines - 9][i] = '1';
            }
            for(int i = 37 + boundaries[2]; i < 45 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 15,i,"o");
                world[boundaries[0] + lines - 15][i] = '1';
                 mvprintw(boundaries[0] + lines - 14,i,"o");
                world[boundaries[0] + lines - 14][i] = '1';
            }
            for(int i = 15 + boundaries[2]; i < 30 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 20,i,"o");
                world[boundaries[0] + lines - 20][i] = '1';
                 mvprintw(boundaries[0] + lines - 19,i,"o");
                world[boundaries[0] + lines - 19][i] = '1';
            }
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(10));
            for(int i = 74 + boundaries[2]; i < 91 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 1,i," ");
                world[boundaries[0] + lines - 1][i] = ' ';
                mvprintw(boundaries[0] + lines - 2,i," ");
                world[boundaries[0] + lines - 2][i] = ' ';
            }
            for(int i = 45 + boundaries[2]; i < 60 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 1,i," ");
                world[boundaries[0] + lines - 1][i] = ' ';
                mvprintw(boundaries[0] + lines - 2,i," ");
                world[boundaries[0] + lines - 2][i] = ' ';
            }
            attroff(COLOR_PAIR(10));
            poz = 1;
        }
        if(n_map==2 && x - boundaries[2] <= 30 && poz == 1){
            attron(COLOR_PAIR(10));
            for(int i = 91 + boundaries[2]; i < 104 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 7,i," ");
                world[boundaries[0] + lines - 7][i] = ' ';
                mvprintw(boundaries[0] + lines - 6,i," ");
                world[boundaries[0] + lines - 6][i] = ' ';
            }
            for(int i = 60 + boundaries[2]; i < 74 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 10,i," ");
                world[boundaries[0] + lines - 10][i] = ' ';
                 mvprintw(boundaries[0] + lines - 9,i," ");
                world[boundaries[0] + lines - 9][i] = ' ';
            }
            for(int i = 37 + boundaries[2]; i < 45 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 15,i," ");
                world[boundaries[0] + lines - 15][i] = ' ';
                 mvprintw(boundaries[0] + lines - 14,i," ");
                world[boundaries[0] + lines - 14][i] = ' ';
            }
            for(int i = 15 + boundaries[2]; i < 30 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 20,i," ");
                world[boundaries[0] + lines - 20][i] = ' ';
                 mvprintw(boundaries[0] + lines - 19,i," ");
                world[boundaries[0] + lines - 19][i] = ' ';
            }
            for(int i = boundaries[2] + cols-14; i < boundaries[2] + cols - 1; i++){
                mvprintw(boundaries[0]+ lines - 4,i," ");
                world[boundaries[0] + lines - 4][i] = ' ';
                mvprintw(boundaries[0] + lines - 5,i," ");
                world[boundaries[0] + lines - 5][i] = ' ';
            }
            attroff(COLOR_PAIR(10));
            attron(COLOR_PAIR(8));
            for(int i = boundaries[2]; i < boundaries[3]; i++){
                mvprintw(boundaries[0] + lines - 1,i,"o");
                mvprintw(boundaries[0] + lines - 2,i,"o");
                world[boundaries[0] + lines - 1][i] = '1';
                world[boundaries[0] + lines - 2][i] = '1';
            }
            for(int i = 50 + boundaries[2]; i < 64 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 6,i,"o");
                mvprintw(boundaries[0] + lines - 7,i,"o");
                world[boundaries[0] + lines - 6][i] = '1';
                world[boundaries[0] + lines - 7][i] = '1';
            }
            for(int i = 70 + boundaries[2]; i < 84 + boundaries[2]; i++){
                mvprintw(boundaries[0] + lines - 11,i,"o");
                mvprintw(boundaries[0] + lines - 12,i,"o");
                world[boundaries[0] + lines - 11][i] = '1';
                world[boundaries[0] + lines - 12][i] = '1';
            }
            attroff(COLOR_PAIR(8));
            y = falling(y, x, 9, 13, player, lines, cols, world, boundaries[0]);
            print_empty(child[0].row, child[0].column, 7, 11, 'a');
            child[0].row = boundaries[1]-9;
            child[0].column = boundaries[3]- 12;
            poz = 2;
        }
        //
        print_hero(y, x, 9, 13, player);
        if(shot.count==0 && !shot.active){break;}
    }
    print_empty(shot.row, shot.column, 5, 7, 'a');
    for(int i = 0; i < children; i++){
        print_child(child[i].row, child[i].column, 7, 11, sad_child, happy_child, lines, cols, world, child[i].happy);
    }

    if(y==boundaries[1]-9) print_empty(y, x, 9, 13, 'a');
    if(!main_sc && n_map==2 && win==children)sleep(2);
    else sleep(1);
    clear();
    if(win==children){
        info[0] = 1;
        info[1] = winner();
        } 
    else{
        info[0] = 0;
        info[1] = loser();
    }
    refresh();
}
void print_hero(int y, int x, int row, int column, const char player[row][column]){
    int color;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if((player[i][j]!=' ' && i==0)|| (player[i][j]!=' ' && player[i][j]!='o' && i ==3) || player[i][j]=='C' || player[i][j]=='D' ) {color = 1;}
            else if(player[i][j]!=' ' && i <=2 && i>=1 ) {color = 3;}
            else if(player[i][j]=='o') {
                attron(A_BOLD);
                color = 4;}
            else if(((j>=1 && j<=3)||(j>=9 && j<=11)) && i==4) {color = 7;}
            else if((j>=4 && j<=8 && i==4) || (j>=5 && j<=7 && i==5)) {color = 6;}
            else if(player[i][j]=='[' || (player[i][j]==']' && i==5) || (j>2 && j<10 && i==6) || (j>1 && j<11 && i==7)) {color = 7;}//
            else if(player[i][j]!=' ') {color = 7;}
            else color = 10;
            attron(COLOR_PAIR(color));
            mvprintw(y + i, x + j,"%c",player[i][j]);
            attroff(COLOR_PAIR(color));
            attroff(A_BOLD);
        }
    }
    refresh();
}
void print_child(int y, int x, int row, int column, const char player[row][column], const char player1[row][column], int lines, int cols, char world[lines][cols], bool happy){
    int color;
    if(!happy){
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                if(i == 0) color = 10;
                else if((i >= 5 && (((j>=0 && j<=2) || (j>7 && j<=10)))) || (i==6 && j==5 )) color = 10;
                else color = 11;
                if ((i == 3 || i == 4 ) && (j ==3  || j ==7 )) color = 9;
                attron(COLOR_PAIR(color));
                mvprintw(y + i, x + j,"%c",player[i][j]);
                attroff(COLOR_PAIR(color));
                world[y + i][x + j] = '2';
            }
        }
    }
    else{
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                if(i == 0) color = 10;
                else if((i >= 5 && (((j>=0 && j<=2) || (j>7 && j<=10)))) || (i==6 && j==5 )) color = 10;
                else color = 15;
                if(i==2 && (j==3 || j==7)) color = 0;
                else if(player1[i][j]=='<' || player1[i][j]=='>') color = 16;
                else if(i==5 && j>=3 && j<=7) color = 17;
                else if(player1[i][j]=='~'){
                    attron(A_BOLD);
                }
                attron(COLOR_PAIR(color));
                mvprintw(y + i, x + j,"%c",player1[i][j]);
                attroff(COLOR_PAIR(color));
                attroff(A_BOLD);
                world[y + i][x + j] = '2';
            }
        }
    }
    refresh();
}
void print_shot(int y, int x, int row, int column, const char player[row][column], int COL){
    int color;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            if((i < 3 && player[i][j]!=' ') || (i==1 && j==3)) color = 1;
            else if (player[i][j]!=' '|| (i==3 && (j==3 || j==4))) color = 2;
            else color = COL;
            attron(COLOR_PAIR(color));
            mvprintw(y + i, x + j,"%c",player[i][j]);
            attroff(COLOR_PAIR(color));
        }
    }
    refresh();
}
void print_empty(int y, int x, int row, int column, char dir){
    attron(COLOR_PAIR(10));
    if(dir=='l'){
        for(int j = 0; j < row; j++){
            mvprintw(y + j, x + column - 1," ");
        }   
    }
    else if(dir == 'r'){
        for(int j = 0; j < row; j++){
            mvprintw(y + j, x," ");
        } 
    }
    else if(dir == 'u'){
        for(int j = 0; j < column; j++){
            mvprintw(y, x + j," ");
        }  
    }
    else if(dir == 'd'){
        for(int j = 0; j < column; j++){
            mvprintw(y+row, x + j," ");
        } 
    }
    else {
        for(int i = 0; i < row; i++){
            for(int j = 0; j < column; j++){
                mvprintw(y + i, x + j," ");
            }
        }
    }
    attroff(COLOR_PAIR(10));
    refresh();
}
void jump(int y, int x, int row, int column, const char player[row][column], int dir, int lines, int cols, char world[lines][cols], int mas[2], int start_col, int col){
    struct timespec ts = {
        .tv_sec = 0,                    
        .tv_nsec = 40000000
    };
    bool border;
    char ch = (dir > 0) ? 'r': 'l';
    for(int i = 1; i <= 8 && detect(y, x, 9, 13, lines, cols, world, 'u'); i++){
        border = (dir > 0) ? x + 13 < col : x > start_col;
        if(!detect(y - 1, x + dir, 9, 13, lines, cols, world, ch) || !border) dir = 0;
        print_empty(y,x,row,column,ch);
        x = x + dir;
        y = y - 1;
        print_empty(y,x,row,column,'d');
        print_hero(y, x, 9, 13, player);
        refresh();
        nanosleep(&ts,NULL);
    }
    for(int i = 1; i <= 8 && detect(y, x, 9, 13, lines, cols, world, 'd'); i++){
        border = (dir > 0) ? x + 13 < col : x > start_col;
        if(!detect(y + 1, x + dir, 9, 13, lines, cols, world, ch) || !border) dir = 0;
        print_empty(y,x,row,column,ch);
        x = x + dir;
        print_empty(y,x,row,column,'u');
        y = y + 1;
        print_hero(y, x, 9, 13, player);
        refresh();
        nanosleep(&ts,NULL);
    }
    print_empty(y,x,row,column,'A');
    mas[0] = x;
    mas[1] = y;
}
bool detect(int y, int x, int row, int column, int lines, int cols, const char world[lines][cols], char dir){
    if(dir=='r'){
        for(int i = 0; i < row; i++){
            if(world[y + i][x + column]== '1'){
                return false;
            }
        }
    }
    else if(dir=='l'){
        for(int i = 0; i < row; i++){
            if(world[y + i][x-1]== '1'){
                return false;
            }
        }
        
    }
    else if(dir=='d'){
        for(int i = 0; i < column; i++){
            if(world[y+row][x + i] == '1'){
                return false;
            } 
        }
        
    }
    else if(dir=='u'){
        for(int i = 0; i < column; i++){
            if(world[y - 1][x + i] == '1' || y - 1 == LINES -lines){
                return false;
            } 
        }
        
    }
    else if(dir=='s'){
        for(int i = 0; i < row; i++){
            if(world[y + i][x + column]== '1' || world[y + i][x + column]== '2'){
                return false;
            }
        }
        
    }
    return true;
}
void map1(int start_row, int start_col, int lines, int cols, char world[lines][cols]){
    attron(COLOR_PAIR(10));
    for(int rows = start_row; rows < lines + start_row; rows++){
        for(int columns = start_col; columns < cols + start_col; columns++){
            mvprintw(rows, columns, " ");
            world[rows][columns] = ' ';
        }
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(8));
    for(int i = start_col; i < cols + start_col; i++){
        mvprintw(start_row + lines - 1,i,"#");
        mvprintw(start_row + lines - 2,i,"#");
        world[start_row + lines - 1][i] = '1';
        world[start_row + lines - 2][i] = '1';
    }
    //
    for(int i = 50 + start_col; i < 64 + start_col; i++){
        mvprintw(start_row + lines - 6,i,"#");
        mvprintw(start_row + lines - 7,i,"#");
        world[start_row + lines - 6][i] = '1';
        world[start_row + lines - 7][i] = '1';
    }
    for(int i = 70 + start_col; i < 84 + start_col; i++){
        mvprintw(start_row + lines - 11,i,"#");
        mvprintw(start_row + lines - 12,i,"#");
        world[start_row + lines - 11][i] = '1';
        world[start_row + lines - 12][i] = '1';
    }
    attroff(COLOR_PAIR(8));
}
void map2(int start_row, int start_col, int lines, int cols, char world[lines][cols]){
    attron(COLOR_PAIR(10));
    for(int rows = start_row; rows < lines + start_row; rows++){
        for(int columns = start_col; columns < cols + start_col; columns++){
            mvprintw(rows, columns, " ");
            world[rows][columns] = ' ';
        }
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(8));
    for(int i = start_col; i < cols + start_col; i++){
        mvprintw(start_row + lines - 1,i,"#");
        mvprintw(start_row + lines - 2,i,"#");
        world[start_row + lines - 1][i] = '1';
        world[start_row + lines - 2][i] = '1';
    }
    //
    for(int i = start_col + 27; i < start_col + 41; i++){
        mvprintw(start_row + lines - 4,i,"#");
        world[start_row + lines - 4][i] = '1';
        mvprintw(start_row + lines - 3,i,"#");
        world[start_row + lines - 3][i] = '1';
    }
    for(int i = start_col +  47; i < start_col + 61; i++){
        mvprintw(start_row + lines - 8,i,"#");
        world[start_row + lines - 8][i] = '1';
        mvprintw(start_row + lines - 9,i,"#");
        world[start_row + lines - 9][i] = '1';
    }
    for(int i = start_col +  67; i < start_col + 81; i++){
        mvprintw(start_row + lines - 13,i,"#");
        world[start_row + lines - 13][i] = '1';
        mvprintw(start_row + lines - 14,i,"#");
        world[start_row + lines - 14][i] = '1';
    }
    for(int i = start_col + cols-14; i < start_col + cols; i++){
        mvprintw(start_row + lines - 18,i,"#");
        world[start_row + lines - 18][i] = '1';
    }
    for(int i = start_col + cols-14; i < start_col + cols; i++){
        mvprintw(start_row + lines - 10,i,"#");
        world[start_row + lines - 10][i] = '1';
    }
    attroff(COLOR_PAIR(8));
}
void map3(int start_row, int start_col, int lines, int cols, char world[lines][cols]){
    attron(COLOR_PAIR(10));
    for(int rows = start_row; rows < lines + start_row; rows++){
        for(int columns = start_col; columns < cols + start_col; columns++){
            mvprintw(rows, columns, " ");
            world[rows][columns] = ' ';
        }
    }
    attroff(COLOR_PAIR(10));
    attron(COLOR_PAIR(8));
    for(int i = start_col; i < cols + start_col; i++){
        mvprintw(start_row + lines - 1,i,"o");
        mvprintw(start_row + lines - 2,i,"o");
        world[start_row + lines - 1][i] = '1';
        world[start_row + lines - 2][i] = '1';
    }
    //
    for(int i = start_col + cols-14; i < start_col + cols - 1; i++){
        mvprintw(start_row + lines - 4,i,"o");
        world[start_row + lines - 4][i] = '1';
        mvprintw(start_row + lines - 5,i,"o");
        world[start_row + lines - 5][i] = '1';
    }
    attroff(COLOR_PAIR(8));
}
void boundaries_func(int lines, int cols, int mas[4]){
    int start_col = (COLS - cols)/2;
    int start_row = (LINES - lines)/2;
    int arr[4] = {start_row,lines + start_row,start_col,cols + start_col};
    for(int i = 0; i < 4; i++){
        mas[i]=arr[i];
    }
}
int falling(int y, int x, int row, int column, const char player[row][column], int lines, int cols, const char world[lines][cols], int start_row){
    struct timespec ts = {
        .tv_sec = 0,                    
        .tv_nsec = 40000000
    };
    int count = 0;
    do{
        count = 0;
        for(int k = x; k < x + column;k++){
            if(world[y+row][k] != '1') count++;
        }
        if(count==column){
            print_empty(y,x,row,column,'u');
            y++;
            print_hero(y, x, 9, 13, player);
            refresh();
            nanosleep(&ts,NULL);
        }
    }while(count==column && y!=lines + start_row - row); 
    return y;
}
void print_shots(int start_col, int start_row, int lines, int cols, char world[lines][cols]){
    for(int i = start_row+1; i<start_row + 8; i++){
        for(int j = start_col + cols - 18; j<start_col + cols -1;j++){
            attron(COLOR_PAIR(13));
            mvprintw(i,j," ");
            attroff(COLOR_PAIR(13));
            world[i][j]='1';
        }
    }
    attron(COLOR_PAIR(13));
    for(int i = start_row+1; i<start_row + 8; i+=2){
            mvprintw(i,start_col + cols - 18,"+");
            if(i!=start_row + 7) mvprintw(i + 1,start_col + cols - 18,"|");

            mvprintw(i,start_col + cols -2,"+");
            if(i!=start_row + 7) mvprintw(i + 1,start_col + cols -2,"|");
    }
    for(int j = start_col + cols - 18; j<start_col + cols -1;j+=2){
            mvprintw(start_row+1,j,"+");
            if(j!=start_col + cols -2) mvprintw(start_row+1,j+1,"-");

            mvprintw(start_row+7,j,"+");
            if(j!=start_col + cols -2) mvprintw(start_row+7,j+1,"-");
        }
    attroff(COLOR_PAIR(13));
}
bool check_shot(int y1, int x1, int row1, int column1, int y2, int x2, int row2, int column2){
    for(int y_shot = y1; y_shot < y1 + row1; y_shot++){
        for(int y_child = y2; y_child < y2 + row2; y_child++){
            for(int x_shot = x1; x_shot <= x1 + column1; x_shot++){
                for(int x_child = x2; x_child <= x2 + column2; x_child++){
                    if(x_shot == x_child && y_shot == y_child) return true;
                }
            }
        }
    }
    return false;
}
