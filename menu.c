#include "program.h"

int menu(int y, int rows, int columns, char text[rows][columns], int a, int color){
	columns--;
	rows = 3;
	int c;
	int number = 0;
	do{
		c = getch();
		switch(c){
			case KEY_UP:
			case 'W':
			case 'w':
				number = (number > 0) ? number-1 : rows-1;
				break;
			case KEY_DOWN:
			case 'S':
			case 's':
				number = (number < rows-1) ? number+1 : 0;
				break;
			case KEY_BACKSPACE:
				c = '\n';
				number = -1;
				break;
		}
		int y_mas[rows];
		for(int i = 0; i < rows; i++){
			y_mas[i] = y + i;
		} 
		for(int i = 0; i < rows; i++){
			if(color == 14) option(text[i], columns, y_mas[i], COLS/2 - columns/2 + a, number, i, color);
			else option(text[i], columns, y_mas[i], COLS/2 - columns/2 + a, number, i, color + i);
		}
		refresh();
		
	}while(c!='\n');
	return number;
}
void option(char mas[], int columns, int y, int x, int choose, int guess, int color){
	if(choose == guess){
		char new_mas[columns];
		int first = 0;
		for(int k = 0; mas[k]==' '; k++) first++;
		int second = columns - 1;
		for(int k = columns - 1; mas[k]==' '; k--) second--;
		first-=2; second+=2;
		for(int i = 0; i < columns; i++){
			if(i==first) new_mas[first] = '>';
			else if(i==second) new_mas[second] = '<';
			else new_mas[i] = mas[i];
		}
		new_mas[columns] = '\0';
		attron(A_BOLD);
		attron(COLOR_PAIR(color));//14
		mvprintw( y, x,"%s", new_mas);
		attroff(COLOR_PAIR(color));
		attroff(A_BOLD);
	}
	else mvprintw( y, x,"%s", mas);
}
void draw_logo(int rows, int columns, const char logo[rows][columns], int target , bool col){
	struct timespec ts = {
        .tv_sec = 0,                    
        .tv_nsec = 25000000
    };
    clear(); 
    int center = COLS/2 - strlen(logo[0])/2;
    for( int row_count = rows-1; row_count >= 1; row_count-- ){
        for( int y = 1; y <= target; y++ ){
            if(col) color_logo(y, center, rows, columns, logo, row_count);
			else mvprintw(y, center,"%s", logo[row_count]);
            refresh();
            nanosleep(&ts,NULL);
            mvprintw(y,center,"%s", logo[0]);
        }
        if(col) color_logo(target, center, rows, columns, logo, row_count);
		else mvprintw(target, center,"%s", logo[row_count]);
        target--;
    }
}
int winner(){
	char text[][16] = {
		{"     Levels    "},
		{"  Main screen  "},
		{"     Quit      "}
	};
	char logo[][84] = {
		{"                                                                                   "},
		{"$$\\     $$\\                                                           $$\\ $$\\ $$\\  "},
		{"\\$$\\   $$  |                                                          $$ |$$ |$$ | "},
		{" \\$$\\ $$  /$$$$$$\\  $$\\   $$\\       $$\\  $$\\  $$\\  $$$$$$\\  $$$$$$$\\  $$ |$$ |$$ | "},
		{"  \\$$$$  /$$  __$$\\ $$ |  $$ |      $$ | $$ | $$ |$$  __$$\\ $$  __$$\\ $$ |$$ |$$ | "},
		{"   \\$$  / $$ /  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ /  $$ |$$ |  $$ |\\__|\\__|\\__| "},
		{"    $$ |  $$ |  $$ |$$ |  $$ |      $$ | $$ | $$ |$$ |  $$ |$$ |  $$ |             "},
		{"    $$ |  \\$$$$$$  |\\$$$$$$  |      \\$$$$$\\$$$$  |\\$$$$$$  |$$ |  $$ |$$\\ $$\\ $$\\  "},
		{"     \\__|   \\______/  \\______/        \\_____\\____/  \\______/ \\__|  \\__|\\__|\\__|\\__|"}
	};	
	draw_logo(9, 84, logo, 10,0);
	int choosen = menu(18,3,16,text, 0, 14);
	return choosen;
}
int loser(){
	char text[][16] = {
		{"     Retry     "},
		{"  Main screen  "},
		{"     Quit      "}
	};
	char logo[][37] = {
		{"                                    "},
		{"__   __            _                "},
		{"\\ \\ / /           | |               "},
		{" \\ V /___  _   _  | | ___  ___  ___ "},
		{"  \\ // _ \\| | | | | |/ _ \\/ __|/ _ \\"},
		{"  | | (_) | |_| | | | (_) \\__ \\  __/"},
		{"  \\_/\\___/ \\__,_| |_|\\___/|___/\\___|"}
	};	
	draw_logo(7, 37, logo, 10,0);
	int choosen = menu(18,3,16,text,-1, 14);
	return choosen;
}
int levels(){
	clear();//24
	int y = LINES/2 - 7/2 - 4;
	int x = COLS/2 - 25/2;
	for(int i = 0; i < 24; i+=2){
		mvprintw(y, x + i,"+-");
		mvprintw(y + 6, x + i,"+-");
	}
	for(int i = 0; i < 7; i+=2){
		mvprintw(y + i, x,"+");
		mvprintw(y + i, x + 24,"+");
		if(i<5){
			mvprintw(y + i + 1, x,"|");
			mvprintw(y + i + 1, x + 24,"|");
		}
	}
	char text[][24] = {
		{"        Level 1        "},
		{"        Level 2        "},
		{"        Level 3        "},
		{"   Choose the level:   "}
	};
	mvprintw(y+1,x + 1,"%s",text[3]);
	int a = menu(y + 3, 3, 24, text, 0, 19);
	return a;
};
void instruction(){
	clear();
	FILE *fp = fopen("Information.txt","r");

	if(fp == NULL){
		endwin();
		fprintf(stderr,"Information.txt file is corrupted.\n");
		exit(EXIT_FAILURE);
	}

	char ch = fgetc(fp);
	char text[200];
	int index = 0;
	while(ch != EOF){
		text[index] = ch; 
		index++;
		ch = fgetc(fp);
	}
	fclose(fp);
	text[index] = '\0';
	attron(A_BOLD);
	attron(A_ITALIC);
	mvprintw(LINES/2 - 14,COLS/2 - 11/2,"Backstory:\n");
	attroff(A_BOLD);
	attroff(A_ITALIC);

	int y = LINES/2 - 12;
	int start_center = COLS/2 - 53/2;
	int center = COLS/2 - 53/2;
	for(int i = 0; i < index; i++){
		if(text[i]=='\\'){
			center = start_center;
			y++;
			i++;
		}
		mvprintw(y,center,"%c",text[i]);
		center++;
	}

	attron(A_BOLD);
	attron(A_ITALIC);
	mvprintw(LINES/2 - 9/2 - 2,COLS/2 - 9/2,"Controls:");
	attroff(A_BOLD);
	attroff(A_ITALIC);//{"Back to the previous screen - Backspace"}
	char controls[][26] = {
		{"Go left - A, arrow left  "},
		{"Go right - D, arrow right"},
		{"Jump - W, arrow up       "},
		{"Jump left - Q            "},
		{"Jump right - E           "},
		{"Shoot - Space            "}
	};

	center = COLS/2 - 20;
	char t_back[] = {"Back to the previous screen - Backspace"};
	for(int x = 0; x < 40; x++){
		if(t_back[x-1]=='-' && x!=0){ 
			attron(A_BOLD);
			attron(A_ITALIC);
		}
		mvprintw(LINES/2 - 9/2,center,"%c",t_back[x-1]);
		center++;
	}
	attroff(A_BOLD);
	attroff(A_ITALIC);

	start_center = COLS/2 - strlen(controls[0])/2;
	center = start_center;
	for(int y = 0; y < 6; y++){
		for(int x = 0; x < 26; x++){
			if(controls[y][x-1]=='-' && x!=0){ 
				attron(A_BOLD);
				attron(A_ITALIC);
			}
			mvprintw(y + LINES/2 - 2,center,"%c",controls[y][x]);
			center++;
		}
		attroff(A_BOLD);
		attroff(A_ITALIC);
		center = start_center;
	}
	int c;
	do{
		c = getch();
	}while(c != KEY_BACKSPACE);
}
void color_logo(int y, int center, int rows, int columns,const char logo[rows][columns], int index ){
	int color = 0;
	for(int x = 0; x < columns; x++){
		if(index==1 && ( (x>=3 && x<=6) || x==10 || (x>=21 && x<=24) || x == 40 || x==44 || (x>=63 && x<=66) || (x>=70 && x<=75) ) ){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==2 && ((x>=2 && x<=7) || (x>=9 && x<=11) || (x>=20 && x<=24) || x==26 || x==27 || x==36||x==37||(x>=39 && x<=45) || (x>=53 && x<=55) || (x>=62 && x<=67) || (x>=69 && x<=75) )){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==3 && ((x>=1 && x<=3)||(x>=9 && x<=11)||(x>=19 && x<=37)||(x>=39 && x<=45)||(x>=52 && x<=56)||(x>=61 && x<=63)||(x>=69 && x<=74))){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==4 && ((x>=1 && x<=3)||x==5||x==6||(x>=9 && x<=11)||x==13||x==14||(x>=19 && x<=25)||(x>=27 && x<=36)||(x>=39 && x<=45)||x>=53)){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==5 && ((x>=0 && x<=15)||(x>=20 && x<=24)||(x>=28 && x<=35)||(x>=39 && x<=45)||(x>=52 && x<=56)||(x>=62 && x<=76))){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==6 && ((x>=29 && x<=34)||(x>=52 && x<=56))){
			color = 22;
			attron(A_BOLD);
		}
		else if(index==7 && (x==30 || x==33)){
			color = 22;
			attron(A_BOLD);
		}
		else color = 0;
		attron(COLOR_PAIR(color));
		mvprintw(y,center+x,"%c",logo[index][x]);
		attroff(COLOR_PAIR(color));
		attroff(A_BOLD);
	}
}
