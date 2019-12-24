#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long int timer=0;
int pos[2],escape=0,hammer_aktif=0,hammer=0,px,lv=9,musuh,lamamusuh=5,ghdw=0, ghrg=0;
long int skor[7];
char nama_skor[7][25];

int lv1();
int lv2();
int lv3();
int lv4();
int lv5();
int menu();
int credit();
void gameover();
void save();
void load();
void newhighscore();
int help();
int showhigh();
int win();

int main(){
	allegro_init();
	load();

	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A");
	MIDI *background;
	background = load_midi ("sound/background.mid");
	play_midi (background, true);

	while(lv){
		if(lv==1) lv=lv1();
		else if(lv==2) lv=lv2();
		else if(lv==3) lv=lv3();
		else if(lv==4) lv=lv4();
		else if(lv==5) lv=lv5();
		else if(lv==9) lv=menu();
		else if(lv==10) lv=credit();
		else if(lv==11) lv=showhigh();
		else if(lv==13) lv=help();
		else if(lv==14) lv=win();
	}
	save();
    return 0;
}

int help(){
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *gambar;
    gambar = load_bitmap("menu/showhelp.bmp",NULL);
	while ( !key[KEY_ENTER] ){
		draw_sprite(screen, gambar,0,0);
    	release_screen();
	}
	return 9;
}

int win(){
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *gambar;
    gambar = load_bitmap("menu/win.bmp",NULL);
	while ( !key[KEY_ENTER] ){
		draw_sprite(screen, gambar,0,0);
    	release_screen();
	}
	return 9;
}

int showhigh(){
	int i;
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *gambar,*buffer;
	buffer = create_bitmap(500,500);
    gambar = load_bitmap("menu/showhighscore.bmp",NULL);
	while (!key[KEY_ENTER]){
		draw_sprite(buffer,gambar,0,0);
		for(i=1;i<6;i++){
			textprintf_ex(buffer,font,150,250+(i*15), makecol(0,255,255),-1," lv-%d : %ld    %s",i,skor[i],nama_skor[i]);
		}
		draw_sprite(screen,buffer,0,0);
		rest(100);
    	release_screen();
	}
	return 9;
}

int credit(){
	int vertical=-500;
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *gambar;
    gambar = load_bitmap("menu/showcredit.bmp",NULL);
	while ( vertical<500 ){
		vertical+=10;
		draw_sprite( screen, gambar,0,vertical);
		rest(50);
    	release_screen();
	}
	return 9;
}

void gameover(){
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *gambar;
    gambar = load_bitmap("menu/gameover.bmp",NULL);
	while ( !key[KEY_ENTER] ){
		draw_sprite( screen, gambar,0,0);
    	release_screen();
	}
}

void newhighscore(){
	install_keyboard();
   set_color_depth(16);
   set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
   clear_keybuf();
   acquire_screen();
   clear_to_color(screen,makecol(0,0,0));
   BITMAP *gambar,*buffer;
   gambar = load_bitmap("menu/newhigh.bmp",NULL);
   buffer = create_bitmap(500,500);
   int chskor=0;
   do{
   	draw_sprite( buffer, gambar,0,0);
      if(keypressed())
      {
         int  newkey   = readkey();
         char ASCII    = newkey & 0xff;
         char scancode = newkey >> 8;

         if(ASCII >= 32 && ASCII <= 126)
        {
			nama_skor[lv][chskor] = ASCII;
            chskor++;
            nama_skor[lv][chskor] = '\0';
		}
         else if(scancode == KEY_BACKSPACE)
         {
            if (chskor > 0) chskor--;
            nama_skor[lv][chskor] = '\0';
         }
      }
      textprintf_ex(buffer,font,250,300, makecol(0,255,255),-1,"%s",nama_skor[lv]);
	  draw_sprite(screen,buffer,0,0);
	  rest(100);
	  release_screen();
	  skor[lv]=timer;
   }
   while(!key[KEY_ENTER]);
}

void save(){
	FILE *files;
	files=fopen("highscore.txt","w");
	int i;
    for(i=1;i<6;i++)
    {
    	fprintf(files,"%ld %s\n",skor[i],nama_skor[i]);
	}
	fclose(files);
}

void load(){
	FILE *files;
	files=fopen("highscore.txt","r");
	int i;
    for(i=1;i<6;i++)
    {
    		fscanf(files,"%ld",&skor[i]);
    		fscanf(files,"%s",nama_skor[i]);
	}
	fclose(files);
}

int menu(){
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	int mm=10;
	BITMAP *play,*high,*exit,*credit,*help,*buffer;

	credit = load_bitmap("menu/credit.bmp",NULL);
    play = load_bitmap("menu/play.bmp",NULL);
    high = load_bitmap("menu/highscore.bmp",NULL);
    exit = load_bitmap("menu/exit.bmp",NULL);
	help = load_bitmap("menu/help.bmp",NULL);
	buffer = create_bitmap(500,500);

	while (1){
		if(mm==10) draw_sprite( buffer, play,0,0);
		else if(mm==11) draw_sprite( buffer, credit,0,0);
		else if(mm==12) draw_sprite( buffer, high,0,0);
		else if(mm==13) draw_sprite( buffer, exit,0,0);
		else if(mm==14) draw_sprite( buffer, help,0,0);
		if (key[KEY_UP]){
			mm--;
		}
		else if (key[KEY_DOWN]){
			mm++;
		}
		else if(key[KEY_ENTER]){
			if(mm==10){
				return 1;
			}
			else if(mm==11){
				return 10;
			}
			else if(mm==12){
				return 11;
			}
			else if(mm==13){
				return 0;
			}
			else if(mm==14){
				return 13;
			}
		}
		mm=mm%5+10;
		draw_sprite(screen,buffer,0,0);
		rest(100);
		release_screen();
	}
}

int lv1()
{
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *dinding,*jalan;
	BITMAP *atas[3], *bawah[3], *kanan[3], *kiri[3], *kunci[2], *musuh[4], *buffer;
	int map [10][10]={
    {2,2,2,2,2,0,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,2},
	{2,0,2,2,2,2,2,2,0,2},
	{2,0,0,0,0,0,0,0,0,2},
	{2,2,2,2,0,2,2,2,0,2},
	{2,0,0,0,0,2,0,0,0,2},
	{2,0,0,2,2,2,0,2,2,2},
	{2,2,0,0,2,2,0,0,0,2},
	{2,0,0,0,0,0,0,0,3,2},
	{2,2,2,2,2,2,2,2,2,2}
	};

	int move[4]={};
	move[0]=1;
	buffer = create_bitmap(500,500);
    jalan = load_bitmap("lv1/jalan.bmp",NULL);
    dinding = load_bitmap("lv1/dinding.bmp",NULL);
	atas[0]=load_bitmap("lv1/charAtas1.bmp",NULL);
	atas[1]=load_bitmap("lv1/charAtas2.bmp",NULL);
	atas[2]=load_bitmap("lv1/charAtas3.bmp",NULL);
	bawah[0]=load_bitmap("lv1/charBawah1.bmp",NULL);
	bawah[1]=load_bitmap("lv1/charBawah2.bmp",NULL);
	bawah[2]=load_bitmap("lv1/charBawah3.bmp",NULL);
	kanan[0]=load_bitmap("lv1/charKanan1.bmp",NULL);
	kanan[1]=load_bitmap("lv1/charKanan2.bmp",NULL);
	kanan[2]=load_bitmap("lv1/charKanan3.bmp",NULL);
	kiri[0]=load_bitmap("lv1/charKiri1.bmp",NULL);
	kiri[1]=load_bitmap("lv1/charKiri2.bmp",NULL);
	kiri[2]=load_bitmap("lv1/charKiri3.bmp",NULL);
	kunci[0]=load_bitmap("lv1/kunci1.bmp",NULL);
	kunci[1]=load_bitmap("lv1/kunci2.bmp",NULL);
	musuh[0]=load_bitmap("lv1/musuhBawah.bmp",NULL);
	musuh[1]=load_bitmap("lv1/musuhAtas.bmp",NULL);
	musuh[2]=load_bitmap("lv1/musuhKiri.bmp",NULL);
	musuh[3]=load_bitmap("lv1/musuhKanan.bmp",NULL);
	int x = 0;
	int y = 5;
	pos[0]=x;
	pos[1]=y;
	px=50;
	timer=0;

	while ( !key[KEY_ESC] ){
    	if(timer%100==0){
    		map[5][6]=rand() % 4 + 6;;
    	}
    	if (map[x][y]>5){
    		gameover();
			return 9;
    	}

		for (int i=0;i<10;i++){
			for (int j=0;j<10;j++){
				if (map[i][j] == 0)
					draw_sprite( buffer, jalan,i*px,j*px);
				else if(map[i][j] == 3 && timer%2==0)
					draw_sprite( buffer, kunci[0],i*px,j*px);
				else if(map[i][j] == 3 && timer%2==1)
					draw_sprite( buffer, kunci[1],i*px,j*px);
				else if(map[i][j] == 6 ){
					if(map[i][j+1] ==0){
					draw_sprite( buffer, musuh[0],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghdw==0){
							map[i][j]=0;
							map[i][j+1]=6;
							ghdw++;
						}
						else ghdw--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 7){
					if(map[i][j-1] ==0){
					draw_sprite( buffer, musuh[1],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i][j-1]=7;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 8){
					if(map[i-1][j] ==0){
					draw_sprite( buffer, musuh[2],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i-1][j]=8;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 9){
					if(map[i+1][j] ==0){
					draw_sprite( buffer, musuh[3],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghrg==0){
							map[i][j]=0;
							map[i+1][j]=9;
							ghrg++;
						}
						else ghrg--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else
					draw_sprite( buffer, dinding,i*px,j*px);
			}
		}


		if (key[KEY_UP]){
			if (map[x][y-1]==3){
				y--;
				move[1]=3;
				move[0]=0;
				move[2]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x][y-1]!=1 &&map[x][y-1]!=2){
				y--;
				move[1]=3;
				move[0]=0;
				move[2]=0;
				move[3]=0;
			}
		}
        else if (key[KEY_DOWN]){
        	if (map[x][y+1]==3){
				y++;
				move[0]=3;
				move[1]=0;
				move[2]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x][y+1]!=1&&map[x][y+1]!=2){
				y++;
				move[0]=3;
				move[1]=0;
				move[2]=0;
				move[3]=0;
			}
        }
        else if (key[KEY_RIGHT]){
        	if (map[x+1][y]==3){
				x++;
				move[2]=3;
				move[1]=0;
				move[0]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x+1][y]!=1&&map[x+1][y]!=2){
				x++;
				move[2]=3;
				move[1]=0;
				move[0]=0;
				move[3]=0;
			}
		}
        else if (key[KEY_LEFT]){
        	if(escape>0 && x-1==pos[0] && y==pos[1]){
        		if(timer<skor[lv])newhighscore();
        		return 2;
        	}
        	else if (map[x-1][y]==3){
				x--;
				move[3]=3;
				move[1]=0;
				move[2]=0;
				move[0]=0;
				escape++;
				map[x][y]=0;
			}
        	else if (map[x-1][y]!=1&&map[x-1][y]!=2){
				x--;
				move[3]=3;
				move[1]=0;
				move[2]=0;
				move[0]=0;
			}
        }
        if(move[0]>0){
        	if (move[0]==3){
        		draw_sprite(buffer,bawah[0],x*px,y*px-30);
        		move[0]--;
        	}
        	else if (move[0]==2){
        		draw_sprite(buffer,bawah[2],x*px,y*px-10);
        		move[0]--;
        	}
        	else {
        		draw_sprite(buffer,bawah[1],x*px,y*px);
           	}
        }
        else if(move[1]>0){
        	if (move[1]==3){
        		draw_sprite(buffer,atas[0],x*px,y*px+30);
        		move[1]--;
        	}
        	else if (move[1]==2){
        		draw_sprite(buffer,atas[2],x*px,y*px+10);
        		move[1]--;
        	}
        	else {
        		draw_sprite(buffer,atas[1],x*px,y*px);
           	}
        }
        else if(move[2]>0){
        	if (move[2]==3){
        		draw_sprite(buffer,kanan[0],x*px-30,y*px);
        		move[2]--;
        	}
        	else if (move[2]==2){
        		draw_sprite(buffer,kanan[2],x*px-10,y*px);
        		move[2]--;
        	}
        	else {
        		draw_sprite(buffer,kanan[1],x*px,y*px);
           	}
        }
        else if(move[3]>0){
        	if (move[3]==3){
        		draw_sprite(buffer,kiri[0],x*px+30,y*px);
        		move[3]--;
        	}
        	else if (move[3]==2){
        		draw_sprite(buffer,kiri[2],x*px+10,y*px);
        		move[3]--;
        	}
        	else {
        		draw_sprite(buffer,kiri[1],x*px,y*px);
           	}
        }
        textprintf_ex(buffer,font,250,0, makecol(0,255,255),-1,"Time %9.ld",timer/10);
        textprintf_ex(buffer,font,250,10, makecol(0,255,255),-1,"Press ESC = Keluar");
		draw_sprite(screen,buffer,0,0);
		release_screen();
		timer++;
		rest(100);
	}
	return 9;
}

int lv2()
{
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *dinding,*jalan;
	BITMAP *atas[3], *bawah[3], *kanan[3], *kiri[3], *kunci[2], *musuh[4], *buffer;
	escape=0;
	timer=0;
	int map [20][20]={
	{2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2},
	{2,0,2,2,0,2,2,2,2,0,0,0,2,2,2,2,0,2,0,2},
	{2,0,0,2,0,0,0,2,2,0,2,0,2,0,0,0,0,2,0,2},
	{2,2,0,2,2,2,0,0,2,0,2,0,2,0,2,2,2,2,0,2},
	{2,0,0,2,0,0,2,0,2,0,2,2,0,0,0,0,0,0,0,2},
	{2,0,2,2,0,2,0,0,0,2,2,2,2,2,2,2,2,2,0,2},
	{2,0,0,0,0,2,0,2,0,0,0,0,0,0,0,2,0,0,0,2},
	{2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,2,0,2,2,2},
	{2,0,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,2},
	{2,0,2,2,0,2,0,2,0,2,0,0,0,2,0,2,2,2,2,2},
	{2,0,2,2,0,2,0,0,0,2,0,0,0,2,0,0,0,0,2,2},
	{2,0,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,0,0,2},
	{2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,2,2,2,0,2},
	{2,2,0,0,2,0,2,0,2,2,2,2,2,2,0,0,0,0,0,2},
	{2,2,2,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2},
	{2,0,0,0,2,2,0,2,2,2,2,0,0,2,2,0,0,0,0,2},
	{2,0,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,2,0,2},
	{2,0,0,0,0,0,2,0,0,0,0,0,2,2,2,0,0,0,3,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	int move[4]={};
	move[0]=1;

	buffer = create_bitmap(500,500);
    jalan = load_bitmap("lv2/jalan.bmp",NULL);
    dinding = load_bitmap("lv2/dinding.bmp",NULL);
	atas[0]=load_bitmap("lv2/charAtas1.bmp",NULL);
	atas[1]=load_bitmap("lv2/charAtas2.bmp",NULL);
	atas[2]=load_bitmap("lv2/charAtas3.bmp",NULL);
	bawah[0]=load_bitmap("lv2/charBawah1.bmp",NULL);
	bawah[1]=load_bitmap("lv2/charBawah2.bmp",NULL);
	bawah[2]=load_bitmap("lv2/charBawah3.bmp",NULL);
	kanan[0]=load_bitmap("lv2/charKanan1.bmp",NULL);
	kanan[1]=load_bitmap("lv2/charKanan2.bmp",NULL);
	kanan[2]=load_bitmap("lv2/charKanan3.bmp",NULL);
	kiri[0]=load_bitmap("lv2/charKiri1.bmp",NULL);
	kiri[1]=load_bitmap("lv2/charKiri2.bmp",NULL);
	kiri[2]=load_bitmap("lv2/charKiri3.bmp",NULL);
	kunci[0]=load_bitmap("lv2/kunci1.bmp",NULL);
	kunci[1]=load_bitmap("lv2/kunci2.bmp",NULL);
	musuh[0]=load_bitmap("lv2/musuhBawah.bmp",NULL);
	musuh[1]=load_bitmap("lv2/musuhAtas.bmp",NULL);
	musuh[2]=load_bitmap("lv2/musuhKiri.bmp",NULL);
	musuh[3]=load_bitmap("lv2/musuhKanan.bmp",NULL);
	px=25;
	int x = 0;
	int y = 11;
	pos[0]=x;
	pos[1]=y;

	while ( !key[KEY_ESC] ){
    	if(timer%100==0){
    		map[11][11]=rand() % 4 + 6;;
    	}
    	if (map[x][y]>5){
    		gameover();
			return 9;
    	}

		for (int i=0;i<20;i++){
			for (int j=0;j<20;j++){
				if (map[i][j] == 0)
					draw_sprite( buffer, jalan,i*px,j*px);
				else if(map[i][j] == 3 && timer%2==0)
					draw_sprite( buffer, kunci[0],i*px,j*px);
				else if(map[i][j] == 3 && timer%2==1)
					draw_sprite( buffer, kunci[1],i*px,j*px);
				else if(map[i][j] == 6 ){
					if(map[i][j+1] ==0){
					draw_sprite( buffer, musuh[0],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghdw==0){
							map[i][j]=0;
							map[i][j+1]=6;
							ghdw++;
						}
						else ghdw--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 7){
					if(map[i][j-1] ==0){
					draw_sprite( buffer, musuh[1],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i][j-1]=7;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 8){
					if(map[i-1][j] ==0){
					draw_sprite( buffer, musuh[2],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i-1][j]=8;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 9){
					if(map[i+1][j] ==0){
					draw_sprite( buffer, musuh[3],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghrg==0){
							map[i][j]=0;
							map[i+1][j]=9;
							ghrg++;
						}
						else ghrg--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else
					draw_sprite( buffer, dinding,i*px,j*px);
					}
				}

		if (key[KEY_UP]){
			if (map[x][y-1]==3){
				y--;
				move[1]=3;
				move[0]=0;
				move[2]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x][y-1]!=1 &&map[x][y-1]!=2){
				y--;
				move[1]=3;
				move[0]=0;
				move[2]=0;
				move[3]=0;
			}
		}
        else if (key[KEY_DOWN]){
        	if (map[x][y+1]==3){
				y++;
				move[0]=3;
				move[1]=0;
				move[2]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x][y+1]!=1&&map[x][y+1]!=2){
				y++;
				move[0]=3;
				move[1]=0;
				move[2]=0;
				move[3]=0;
			}
        }
        else if (key[KEY_RIGHT]){
        	if (map[x+1][y]==3){
				x++;
				move[2]=3;
				move[1]=0;
				move[0]=0;
				move[3]=0;
				escape++;
				map[x][y]=0;
			}
			else if (map[x+1][y]!=1&&map[x+1][y]!=2){
				x++;
				move[2]=3;
				move[1]=0;
				move[0]=0;
				move[3]=0;
			}
		}
        else if (key[KEY_LEFT]){
        	if(escape>0 && x-1==pos[0] && y==pos[1]){
        		if(timer<skor[lv])newhighscore();
        		return 3;
        	}
        	else if (map[x-1][y]==3){
				x--;
				move[3]=3;
				move[1]=0;
				move[2]=0;
				move[0]=0;
				escape++;
				map[x][y]=0;
			}
        	else if (map[x-1][y]!=1&&map[x-1][y]!=2){
				x--;
				move[3]=3;
				move[1]=0;
				move[2]=0;
				move[0]=0;
			}
        }
        if(move[0]>0){
        	if (move[0]==3){
        		draw_sprite(buffer,bawah[0],x*px,y*px-20);
        		move[0]--;
        	}
        	else if (move[0]==2){
        		draw_sprite(buffer,bawah[2],x*px,y*px-10);
        		move[0]--;
        	}
        	else {
        		draw_sprite(buffer,bawah[1],x*px,y*px);
           	}
        }
        else if(move[1]>0){
        	if (move[1]==3){
        		draw_sprite(buffer,atas[0],x*px,y*px+20);
        		move[1]--;
        	}
        	else if (move[1]==2){
        		draw_sprite(buffer,atas[2],x*px,y*px+10);
        		move[1]--;
        	}
        	else {
        		draw_sprite(buffer,atas[1],x*px,y*px);
           	}
        }
        else if(move[2]>0){
        	if (move[2]==3){
        		draw_sprite(buffer,kanan[0],x*px-20,y*px);
        		move[2]--;
        	}
        	else if (move[2]==2){
        		draw_sprite(buffer,kanan[2],x*px-10,y*px);
        		move[2]--;
        	}
        	else {
        		draw_sprite(buffer,kanan[1],x*px,y*px);
           	}
        }
        else if(move[3]>0){
        	if (move[3]==3){
        		draw_sprite(buffer,kiri[0],x*px+20,y*px);
        		move[3]--;
        	}
        	else if (move[3]==2){
        		draw_sprite(buffer,kiri[2],x*px+10,y*px);
        		move[3]--;
        	}
        	else {
        		draw_sprite(buffer,kiri[1],x*px,y*px);
           	}
        }
        textprintf_ex(buffer,font,250,0, makecol(0,255,255),-1,"Time %9.ld",timer/10);
        textprintf_ex(buffer,font,250,10, makecol(0,255,255),-1,"Press ESC = Keluar");
		draw_sprite(screen,buffer,0,0);
		release_screen();
		timer++;
		rest(100);
	}
	return 9;
}

int lv3()
{
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *dinding,*jalan;
	BITMAP *atas[3], *bawah[3], *kanan[3], *kiri[3], *kunci[2], *musuh[4],*power, *buffer;
	escape=0;
	timer=0;
	int map [25][25]={
	{2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,2},
	{2,0,1,1,1,0,1,0,1,1,1,0,0,0,0,0,1,0,1,0,1,1,1,0,2},
	{2,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,2},
	{2,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,2},
	{2,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,2},
	{2,0,1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1,0,2},
	{2,0,1,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,0,1,0,0,2},
	{2,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,2},
	{2,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,0,2},
	{2,0,1,0,1,1,1,1,1,1,1,0,1,0,1,0,0,0,0,1,0,1,1,0,2},
	{2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,2},
	{2,0,1,1,0,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,1,1,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,2},
	{2,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,0,1,0,1,0,2},
	{2,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,0,2},
	{2,1,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,1,0,2},
	{2,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,2},
	{2,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,2},
	{2,0,1,0,0,0,0,1,0,1,0,1,1,0,0,0,1,1,0,1,4,0,0,1,2},
	{2,0,1,0,0,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,2},
	{2,0,1,1,1,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,2},
	{2,0,0,0,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,1,0,0,1,1,2},
	{2,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,3,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	int move[4]={};
	move[0]=1;

	buffer = create_bitmap(500,500);
    jalan = load_bitmap("lv3/jalan.bmp",NULL);
    dinding = load_bitmap("lv3/dinding.bmp",NULL);
	atas[0]=load_bitmap("lv3/charAtas1.bmp",NULL);
	atas[1]=load_bitmap("lv3/charAtas2.bmp",NULL);
	atas[2]=load_bitmap("lv3/charAtas3.bmp",NULL);
	bawah[0]=load_bitmap("lv3/charBawah1.bmp",NULL);
	bawah[1]=load_bitmap("lv3/charBawah2.bmp",NULL);
	bawah[2]=load_bitmap("lv3/charBawah3.bmp",NULL);
	kanan[0]=load_bitmap("lv3/charKanan1.bmp",NULL);
	kanan[1]=load_bitmap("lv3/charKanan2.bmp",NULL);
	kanan[2]=load_bitmap("lv3/charKanan3.bmp",NULL);
	kiri[0]=load_bitmap("lv3/charKiri1.bmp",NULL);
	kiri[1]=load_bitmap("lv3/charKiri2.bmp",NULL);
	kiri[2]=load_bitmap("lv3/charKiri3.bmp",NULL);
	kunci[0]=load_bitmap("lv3/kunci1.bmp",NULL);
	kunci[1]=load_bitmap("lv3/kunci2.bmp",NULL);
	musuh[0]=load_bitmap("lv3/musuhBawah.bmp",NULL);
	musuh[1]=load_bitmap("lv3/musuhAtas.bmp",NULL);
	musuh[2]=load_bitmap("lv3/musuhKiri.bmp",NULL);
	musuh[3]=load_bitmap("lv3/musuhKanan.bmp",NULL);
	power=load_bitmap("lv3/hammer.bmp",NULL);
	px=20;
	int x = 0;
	int y = 13;
	pos[0]=x;
	pos[1]=y;

	while ( !key[KEY_ESC] ){
		if(timer%100==0){
    		map[11][11]=rand() % 4 + 6;;
    	}
		if (map[x][y]>5){
			gameover();
			return 9;
		}
		if (map[x][y]==4) {
			hammer_aktif+=2;
			map[x][y]=0;
		}

		for (int i=0;i<25;i++){
			for (int j=0;j<25;j++){
				if (map[i][j] == 0)
					draw_sprite( buffer, jalan,i*px,j*px);
				else if(map[i][j] == 3 && timer%2==0)
					draw_sprite( buffer, kunci[0],i*px,j*px);
				else if(map[i][j] == 3 && timer%2==1)
					draw_sprite( buffer, kunci[1],i*px,j*px);
				else if(map[i][j] == 4)
					draw_sprite( buffer, power,i*px,j*px);

				else if(map[i][j] == 6 ){
					if(map[i][j+1] ==0){
					draw_sprite( buffer, musuh[0],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghdw==0){
							map[i][j]=0;
							map[i][j+1]=6;
							ghdw++;
						}
						else ghdw--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 7){
					if(map[i][j-1] ==0){
					draw_sprite( buffer, musuh[1],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i][j-1]=7;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 8){
					if(map[i-1][j] ==0){
					draw_sprite( buffer, musuh[2],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i-1][j]=8;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 9){
					if(map[i+1][j] ==0){
					draw_sprite( buffer, musuh[3],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghrg==0){
							map[i][j]=0;
							map[i+1][j]=9;
							ghrg++;
						}
						else ghrg--;
					}
					}
				else map[i][j]=rand()%4+6;
				}
				else
					draw_sprite( buffer, dinding,i*px,j*px);
			}
		}

			if (key[KEY_ENTER] && hammer_aktif>0){
				hammer_aktif--;
				hammer++;
			}
			else if (key[KEY_UP] && hammer>0 && map[x][y-1]==1){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_DOWN] && hammer>0 &&map[x][y+1]==1){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_RIGHT]&& hammer>0 &&map[x+1][y]==1){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_LEFT]&& hammer>0 &&map[x-1][y]==1){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					hammer--;
				}
		else {
			if (key[KEY_UP]){
				if (map[x][y-1]==3){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y-1]!=1 &&map[x][y-1]!=2){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_DOWN]){
        		if (map[x][y+1]==3){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y+1]!=1&&map[x][y+1]!=2){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
				}
        	}
        	else if (key[KEY_RIGHT]){
        		if (map[x+1][y]==3){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x+1][y]!=1&&map[x+1][y]!=2){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_LEFT]){
        		if(escape>0 && x-1==pos[0] && y==pos[1]){
        			if(timer<skor[lv])newhighscore();
        			return 4;
        		}
        		else if (map[x-1][y]==3){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					escape++;
					map[x][y]=0;
				}
        		else if (map[x-1][y]!=1&&map[x-1][y]!=2){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
				}
        	}
		}

        if(move[0]>0){
        	if (move[0]==3){
        		draw_sprite(buffer,bawah[0],x*px,y*px-15);
        		move[0]--;
        	}
        	else if (move[0]==2){
        		draw_sprite(buffer,bawah[2],x*px,y*px-10);
        		move[0]--;
        	}
        	else {
        		draw_sprite(buffer,bawah[1],x*px,y*px);
           	}
        }
        else if(move[1]>0){
        	if (move[1]==3){
        		draw_sprite(buffer,atas[0],x*px,y*px+15);
        		move[1]--;
        	}
        	else if (move[1]==2){
        		draw_sprite(buffer,atas[2],x*px,y*px+10);
        		move[1]--;
        	}
        	else {
        		draw_sprite(buffer,atas[1],x*px,y*px);
           	}
        }
        else if(move[2]>0){
        	if (move[2]==3){
        		draw_sprite(buffer,kanan[0],x*px-15,y*px);
        		move[2]--;
        	}
        	else if (move[2]==2){
        		draw_sprite(buffer,kanan[2],x*px-10,y*px);
        		move[2]--;
        	}
        	else {
        		draw_sprite(buffer,kanan[1],x*px,y*px);
           	}
        }
        else if(move[3]>0){
        	if (move[3]==3){
        		draw_sprite(buffer,kiri[0],x*px+15,y*px);
        		move[3]--;
        	}
        	else if (move[3]==2){
        		draw_sprite(buffer,kiri[2],x*px+10,y*px);
        		move[3]--;
        	}
        	else {
        		draw_sprite(buffer,kiri[1],x*px,y*px);
           	}
        }

        textprintf_ex(buffer,font,250,0, makecol(0,255,255),-1,"Time %9.ld",timer/10);
        textprintf_ex(buffer,font,50,0, makecol(0,255,255),-1,"Power Up = %d",hammer_aktif);
        textprintf_ex(buffer,font,250,10, makecol(0,255,255),-1,"Press ESC = Keluar");
		draw_sprite(screen,buffer,0,0);
		release_screen();
		timer++;
		rest(100);
	}
	return 9;
}

int lv4()
{
	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *dinding,*jalan;
	BITMAP *atas[3], *bawah[3], *kanan[3], *kiri[3], *kunci[2], *musuh[4],*power, *buffer;
	escape=0;
	timer=0;
	int map [50][50]={
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,0,2},
    {2,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,0,0,1,1,1,1,0,1,2},
    {2,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,1,0,1,1,1,1,0,1,2},
    {2,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,1,1,0,0,1,0,0,0,1,2},
    {2,0,0,0,0,0,1,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,2},
    {2,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,2},
    {2,1,1,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,2},
    {2,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2},
    {2,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,2},
    {2,1,1,1,0,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,1,2},
    {2,0,1,1,0,1,1,1,1,1,0,1,1,0,0,0,1,0,1,1,1,1,0,0,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,1,2},
    {2,0,0,1,0,0,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,2},
    {2,0,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,2},
    {2,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2},
    {2,0,1,1,0,1,1,0,1,0,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,1,2},
    {2,1,1,0,0,1,1,0,1,0,1,1,1,0,0,0,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,2},
    {2,1,1,1,1,1,0,0,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,0,1,1,1,0,1,1,1,1,1,1,0,1,2},
    {2,0,0,1,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,0,1,2},
    {2,0,0,0,0,1,0,1,1,1,1,0,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,2},
    {2,1,1,1,0,0,0,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,2},
    {2,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,0,2},
    {2,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,2},
    {2,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,2},
    {2,1,1,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,1,2},
    {2,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,2},
    {2,0,1,1,1,1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,2},
    {2,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,2},
    {2,0,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,2},
    {2,0,0,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,2},
    {2,1,1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,2},
    {2,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,2},
    {2,1,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,2},
    {2,1,1,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2},
    {2,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,0,1,2},
    {2,1,0,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,0,2},
    {2,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,0,0,1,0,1,0,0,0,1,1,0,2},
    {2,1,0,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,0,2},
    {2,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,1,1,1,0,1,1,0,2},
    {2,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,0,0,1,0,2},
    {2,1,1,1,1,1,4,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,0,2},
    {2,1,1,1,0,0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,2},
    {2,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,1,0,1,2},
    {2,0,1,1,0,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,0,0,0,1,2},
    {0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,2},
    {2,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,0,0,0,1,0,1,1,0,0,0,0,2},
    {2,1,1,0,0,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,2},
    {2,1,1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,0,1,0,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,1,0,2},
    {2,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	int move[4]={};
	move[0]=1;

    buffer = create_bitmap(500,500);
    jalan = load_bitmap("lv4/jalan.bmp",NULL);
    dinding = load_bitmap("lv4/dinding.bmp",NULL);
	atas[0]=load_bitmap("lv4/charAtas1.bmp",NULL);
	atas[1]=load_bitmap("lv4/charAtas2.bmp",NULL);
	atas[2]=load_bitmap("lv4/charAtas3.bmp",NULL);
	bawah[0]=load_bitmap("lv4/charBawah1.bmp",NULL);
	bawah[1]=load_bitmap("lv4/charBawah2.bmp",NULL);
	bawah[2]=load_bitmap("lv4/charBawah3.bmp",NULL);
	kanan[0]=load_bitmap("lv4/charKanan1.bmp",NULL);
	kanan[1]=load_bitmap("lv4/charKanan2.bmp",NULL);
	kanan[2]=load_bitmap("lv4/charKanan3.bmp",NULL);
	kiri[0]=load_bitmap("lv4/charKiri1.bmp",NULL);
	kiri[1]=load_bitmap("lv4/charKiri2.bmp",NULL);
	kiri[2]=load_bitmap("lv4/charKiri3.bmp",NULL);
	kunci[0]=load_bitmap("lv4/kunci1.bmp",NULL);
	kunci[1]=load_bitmap("lv4/kunci2.bmp",NULL);
	musuh[0]=load_bitmap("lv4/musuhBawah.bmp",NULL);
	musuh[1]=load_bitmap("lv4/musuhAtas.bmp",NULL);
	musuh[2]=load_bitmap("lv4/musuhKiri.bmp",NULL);
	musuh[3]=load_bitmap("lv4/musuhKanan.bmp",NULL);
	power=load_bitmap("lv4/hammer.bmp",NULL);
	int x = 0;
	int y = 32;//bedo
	pos[0]=x;
	pos[1]=y;
	px=10;

	while ( !key[KEY_ESC] ){
		if(timer%100==0){
    		map[30][25]=rand() % 4 + 6;;
    	}
		if (map[x][y]>5){
			gameover();
			return 9;
		}
		if (map[x][y]==4) {
			hammer_aktif+=2;
			map[x][y]=0;
		}

		for (int i=0;i<50;i++){
			for (int j=0;j<50;j++){
				if (map[i][j] == 0)
					draw_sprite( buffer, jalan,i*px,j*px);
				else if(map[i][j] == 3 && timer%2==0)
					draw_sprite( buffer, kunci[0],i*px,j*px);
				else if(map[i][j] == 3 && timer%2==1)
					draw_sprite( buffer, kunci[1],i*px,j*px);
				else if(map[i][j] == 4)
					draw_sprite( buffer, power,i*px,j*px);

				else if(map[i][j] == 6 ){
					if(map[i][j+1] ==0){
					draw_sprite( buffer, musuh[0],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghdw==0){
							map[i][j]=0;
							map[i][j+1]=6;
							ghdw++;
						}
						else ghdw--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 7){
					if(map[i][j-1] ==0){
					draw_sprite( buffer, musuh[1],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i][j-1]=7;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 8){
					if(map[i-1][j] ==0){
					draw_sprite( buffer, musuh[2],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i-1][j]=8;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 9){
					if(map[i+1][j] ==0){
					draw_sprite( buffer, musuh[3],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghrg==0){
							map[i][j]=0;
							map[i+1][j]=9;
							ghrg++;
						}
						else ghrg--;
					}
					}
				else map[i][j]=rand()%4+6;
				}
				else
					draw_sprite( buffer, dinding,i*px,j*px);
			}
		}

			if (key[KEY_ENTER] && hammer_aktif>0){
				hammer_aktif--;
				hammer++;
			}
			else if (key[KEY_UP] && hammer>0 && map[x][y-1]==1){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_DOWN] && hammer>0 &&map[x][y+1]==1){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_RIGHT]&& hammer>0 &&map[x+1][y]==1){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_LEFT]&& hammer>0 &&map[x-1][y]==1){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					hammer--;
				}
		else {
			if (key[KEY_UP]){
				if (map[x][y-1]==3){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y-1]!=1 &&map[x][y-1]!=2){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_DOWN]){
        		if (map[x][y+1]==3){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y+1]!=1&&map[x][y+1]!=2){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
				}
        	}
        	else if (key[KEY_RIGHT]){
        		if (map[x+1][y]==3){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x+1][y]!=1&&map[x+1][y]!=2){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_LEFT]){
        		if(escape>0 && x-1==pos[0] && y==pos[1]){
        			if(timer<skor[lv])newhighscore();
        			return 5;
        		}
        		else if (map[x-1][y]==3){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					escape++;
					map[x][y]=0;
				}
        		else if (map[x-1][y]!=1&&map[x-1][y]!=2){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
				}
        	}
		}

        if(move[0]>0){
        	if (move[0]==3){
        		draw_sprite(buffer,bawah[0],x*px,y*px-8);
        		move[0]--;
        	}
        	else if (move[0]==2){
        		draw_sprite(buffer,bawah[2],x*px,y*px-3);
        		move[0]--;
        	}
        	else {
        		draw_sprite(buffer,bawah[1],x*px,y*px);
           	}
        }
        else if(move[1]>0){
        	if (move[1]==3){
        		draw_sprite(buffer,atas[0],x*px,y*px+8);
        		move[1]--;
        	}
        	else if (move[1]==2){
        		draw_sprite(buffer,atas[2],x*px,y*px+3);
        		move[1]--;
        	}
        	else {
        		draw_sprite(buffer,atas[1],x*px,y*px);
           	}
        }
        else if(move[2]>0){
        	if (move[2]==3){
        		draw_sprite(buffer,kanan[0],x*px-8,y*px);
        		move[2]--;
        	}
        	else if (move[2]==2){
        		draw_sprite(buffer,kanan[2],x*px-3,y*px);
        		move[2]--;
        	}
        	else {
        		draw_sprite(buffer,kanan[1],x*px,y*px);
           	}
        }
        else if(move[3]>0){
        	if (move[3]==3){
        		draw_sprite(buffer,kiri[0],x*px+8,y*px);
        		move[3]--;
        	}
        	else if (move[3]==2){
        		draw_sprite(buffer,kiri[2],x*px+3,y*px);
        		move[3]--;
        	}
        	else {
        		draw_sprite(buffer,kiri[1],x*px,y*px);
           	}
        }

        textprintf_ex(buffer,font,250,0, makecol(0,255,255),-1,"Time %9.ld",timer/10);
        textprintf_ex(buffer,font,50,0, makecol(0,255,255),-1,"Power Up = %d",hammer_aktif);
        textprintf_ex(buffer,font,250,10, makecol(0,255,255),-1,"Press ESC = Keluar");
		draw_sprite(screen,buffer,0,0);
		release_screen();
		timer++;
		rest(100);
	}
	return 9;
}

int lv5()
{

	install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0);
    clear_keybuf();
	acquire_screen();
	clear_to_color(screen,makecol(0,0,0));
	BITMAP *dinding,*jalan;
	BITMAP *atas[3], *bawah[3], *kanan[3], *kiri[3], *kunci[2], *musuh[4],*power, *buffer;
	escape=0;
	timer=0;
	int map[50][50]={
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,2},
    {2,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,2},
    {2,0,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,2},
    {2,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,2},
    {2,1,1,0,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,2},
    {2,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,2},
    {2,0,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,1,2},
    {2,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,2},
    {2,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,2},
    {2,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,2},
    {2,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,2},
    {2,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,1,2},
    {2,1,1,1,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,2},
    {2,1,1,1,0,1,1,1,1,0,1,0,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {2,0,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,2},
    {2,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,2},
    {2,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,0,0,0,0,2},
    {2,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,2},
    {2,0,0,0,1,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,2},
    {2,0,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,0,1,0,0,1,2},
    {2,1,1,0,1,1,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,0,1,1,1,1,2},
    {2,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,0,0,1,1,1,2},
    {2,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,2},
    {2,1,1,1,1,0,1,1,1,0,0,0,1,1,0,1,1,0,1,0,0,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,2},
    {2,1,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,2},
    {2,1,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,2},
    {2,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,2},
    {2,1,1,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,2},
    {2,0,0,0,0,0,1,1,1,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,2},
    {2,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,0,0,0,0,1,1,1,0,1,1,0,1,1,0,0,0,0,1,1,1,1,1,1,2},
    {2,1,1,0,0,0,1,1,1,0,1,1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,1,2},
    {2,1,0,0,1,0,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,0,1,1,1,1,0,1,2},
    {2,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,2},
    {2,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,2},
    {2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,0,0,2},
    {2,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,1,1,1,2},
    {2,0,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,2},
    {2,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,1,2},
    {2,0,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1,0,1,2},
    {2,0,0,0,1,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,2},
    {2,1,0,1,1,1,0,1,1,0,0,1,0,0,0,0,1,1,0,1,1,0,1,3,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2},
    {2,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,1,0,1,1,1,2},
    {2,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,1,1,1,2},
    {2,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,1,2},
    {2,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,1,2},
    {2,4,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,4,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	};

	int move[4]={};
	move[0]=1;

    buffer = create_bitmap(500,500);
    jalan = load_bitmap("lv5/jalan.bmp",NULL);
    dinding = load_bitmap("lv5/dinding.bmp",NULL);
	atas[0]=load_bitmap("lv5/charAtas1.bmp",NULL);
	atas[1]=load_bitmap("lv5/charAtas2.bmp",NULL);
	atas[2]=load_bitmap("lv5/charAtas3.bmp",NULL);
	bawah[0]=load_bitmap("lv5/charBawah1.bmp",NULL);
	bawah[1]=load_bitmap("lv5/charBawah2.bmp",NULL);
	bawah[2]=load_bitmap("lv5/charBawah3.bmp",NULL);
	kanan[0]=load_bitmap("lv5/charKanan1.bmp",NULL);
	kanan[1]=load_bitmap("lv5/charKanan2.bmp",NULL);
	kanan[2]=load_bitmap("lv5/charKanan3.bmp",NULL);
	kiri[0]=load_bitmap("lv5/charKiri1.bmp",NULL);
	kiri[1]=load_bitmap("lv5/charKiri2.bmp",NULL);
	kiri[2]=load_bitmap("lv5/charKiri3.bmp",NULL);
	kunci[0]=load_bitmap("lv5/chest1.bmp",NULL);
	kunci[1]=load_bitmap("lv5/chest2.bmp",NULL);
	musuh[0]=load_bitmap("lv5/musuhBawah.bmp",NULL);
	musuh[1]=load_bitmap("lv5/musuhAtas.bmp",NULL);
	musuh[2]=load_bitmap("lv5/musuhKiri.bmp",NULL);
	musuh[3]=load_bitmap("lv5/musuhKanan.bmp",NULL);
	power=load_bitmap("lv5/hammer.bmp",NULL);
	int x = 0;
	int y = 30;
	pos[0]=x;
	pos[1]=y;
	px=10;

	while ( !key[KEY_ESC] ){
		if(timer%100==0){
    		map[30][25]=rand() % 4 + 6;;
    	}
		if (map[x][y]>5){
			gameover();
			return 9;
		}
		if (map[x][y]==4) {
			hammer_aktif+=2;
			map[x][y]=0;
		}

		for (int i=0;i<50;i++){
			for (int j=0;j<50;j++){
				if (map[i][j] == 0)
					draw_sprite( buffer, jalan,i*px,j*px);
				else if(map[i][j] == 3 && timer%2==0)
					draw_sprite( buffer, kunci[0],i*px,j*px);
				else if(map[i][j] == 3 && timer%2==1)
					draw_sprite( buffer, kunci[1],i*px,j*px);
				else if(map[i][j] == 4)
					draw_sprite( buffer, power,i*px,j*px);

				else if(map[i][j] == 6 ){
					if(map[i][j+1] ==0){
					draw_sprite( buffer, musuh[0],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghdw==0){
							map[i][j]=0;
							map[i][j+1]=6;
							ghdw++;
						}
						else ghdw--;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 7){
					if(map[i][j-1] ==0){
					draw_sprite( buffer, musuh[1],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i][j-1]=7;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 8){
					if(map[i-1][j] ==0){
					draw_sprite( buffer, musuh[2],i*px,j*px);
					if(timer%lamamusuh==0){
						map[i][j]=0;
						map[i-1][j]=8;
					}
					}
					else map[i][j]=rand()%4+6;
				}
				else if(map[i][j] == 9){
					if(map[i+1][j] ==0){
					draw_sprite( buffer, musuh[3],i*px,j*px);
					if(timer%lamamusuh==0){
						if(ghrg==0){
							map[i][j]=0;
							map[i+1][j]=9;
							ghrg++;
						}
						else ghrg--;
					}
					}
				else map[i][j]=rand()%4+6;
				}
				else
					draw_sprite( buffer, dinding,i*px,j*px);
			}
		}

			if (key[KEY_ENTER] && hammer_aktif>0){
				hammer_aktif--;
				hammer++;
			}
			else if (key[KEY_UP] && hammer>0 && map[x][y-1]==1){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_DOWN] && hammer>0 &&map[x][y+1]==1){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_RIGHT]&& hammer>0 &&map[x+1][y]==1){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					hammer--;
				}
        	else if (key[KEY_LEFT]&& hammer>0 &&map[x-1][y]==1){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					hammer--;
				}
		else {
			if (key[KEY_UP]){
				if (map[x][y-1]==3){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y-1]!=1 &&map[x][y-1]!=2){
					y--;
					move[1]=3;
					move[0]=0;
					move[2]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_DOWN]){
        		if (map[x][y+1]==3){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x][y+1]!=1&&map[x][y+1]!=2){
					y++;
					move[0]=3;
					move[1]=0;
					move[2]=0;
					move[3]=0;
				}
        	}
        	else if (key[KEY_RIGHT]){
        		if (map[x+1][y]==3){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
					escape++;
					map[x][y]=0;
				}
				else if (map[x+1][y]!=1&&map[x+1][y]!=2){
					x++;
					move[2]=3;
					move[1]=0;
					move[0]=0;
					move[3]=0;
				}
			}
        	else if (key[KEY_LEFT]){
        		if(escape>0 && x-1==pos[0] && y==pos[1]){
        			if(timer<skor[lv])newhighscore();
        			return 14;
        		}
        		else if (map[x-1][y]==3){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
					escape++;
					map[x][y]=0;
				}
        		else if (map[x-1][y]!=1&&map[x-1][y]!=2){
					x--;
					move[3]=3;
					move[1]=0;
					move[2]=0;
					move[0]=0;
				}
        	}
		}

        if(move[0]>0){
        	if (move[0]==3){
        		draw_sprite(buffer,bawah[0],x*px,y*px-8);
        		move[0]--;
        	}
        	else if (move[0]==2){
        		draw_sprite(buffer,bawah[2],x*px,y*px-3);
        		move[0]--;
        	}
        	else {
        		draw_sprite(buffer,bawah[1],x*px,y*px);
           	}
        }
        else if(move[1]>0){
        	if (move[1]==3){
        		draw_sprite(buffer,atas[0],x*px,y*px+8);
        		move[1]--;
        	}
        	else if (move[1]==2){
        		draw_sprite(buffer,atas[2],x*px,y*px+3);
        		move[1]--;
        	}
        	else {
        		draw_sprite(buffer,atas[1],x*px,y*px);
           	}
        }
        else if(move[2]>0){
        	if (move[2]==3){
        		draw_sprite(buffer,kanan[0],x*px-8,y*px);
        		move[2]--;
        	}
        	else if (move[2]==2){
        		draw_sprite(buffer,kanan[2],x*px-3,y*px);
        		move[2]--;
        	}
        	else {
        		draw_sprite(buffer,kanan[1],x*px,y*px);
           	}
        }
        else if(move[3]>0){
        	if (move[3]==3){
        		draw_sprite(buffer,kiri[0],x*px+8,y*px);
        		move[3]--;
        	}
        	else if (move[3]==2){
        		draw_sprite(buffer,kiri[2],x*px+3,y*px);
        		move[3]--;
        	}
        	else {
        		draw_sprite(buffer,kiri[1],x*px,y*px);
           	}
        }

        textprintf_ex(buffer,font,250,0, makecol(0,255,255),-1,"Time %9.ld",timer/10);
        textprintf_ex(buffer,font,50,0, makecol(0,255,255),-1,"Power Up = %d",hammer_aktif);
        textprintf_ex(buffer,font,250,10, makecol(0,255,255),-1,"Press ESC = Keluar");
		draw_sprite(screen,buffer,0,0);
		release_screen();
		timer++;
		rest(100);
	}
	return 9;
}

END_OF_MAIN();
