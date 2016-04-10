#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <string>

using namespace std;

// todo next lvl 
	
void movePictureRight(string picture1[]) {		// moves the menu picture to the right
	for(int i = 0; i < 9; i++) {
		picture1[i] = "  " + picture1[i];		
	}
}

void movePictureLeft(string picture1[]) {		// moves the menu picture to the left
	for(int i = 0; i < 9; i++) {
		picture1[i]. erase(0,2);	
	}
}

void updateMenuPointer(int a, string menuItems[]) {
			for (int i = 0; i < 5; i++) {
				menuItems[i].replace(1,1, " ");
			}
				
			if ( a == 0 ) {
				menuItems[0].replace(1,1, ">");
			}
			else if ( a == 1 ) {
				menuItems[1].replace(1,1, ">");
			}
			else if ( a == 2 ) {
				menuItems[2].replace(1,1, ">");
			}
			else if ( a == 3 ) {
				menuItems[3].replace(1,1, ">");	
			} 
			else if ( a == 4 ) {
				menuItems[4].replace(1,1, ">");
			}
}

void gameOver(int score, int level) {
	
	system("cls");
	
	cout << "	  #####                          #######                      " << endl;
	cout << "	 #     #   ##   #    # ######    #     # #    # ###### #####  " << endl;
	cout << "	 #        #  #  ##  ## #         #     # #    # #      #    # " << endl;
	cout << "	 #  #### #    # # ## # #####     #     # #    # #####  #    # " << endl;
	cout << "	 #     # ###### #    # #         #     # #    # #      #####  " << endl;
	cout << "	 #     # #    # #    # #         #     #  #  #  #      #   #  " << endl;
	cout << "	  #####  #    # #    # ######    #######   ##   ###### #    # " << endl;
	cout << "\n\n";
	
	cout << "				Bodovi: " << score << endl;		// ispis bodova
	
	cout << "				Level: " << level << endl;
	cout << "\n\n";
	
	exit (EXIT_FAILURE);
}

	char polje[20][40] = {								// playing field
		"#######################################",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#                                     #",
		"#          abcd                       #",
		"#                                     #",
		"#                  ^                  #",
		"#######################################"
	};

bool radi = true;	

int x = 19;				// player/ship coordinates
int y = 18;

int c = 0;             // za projektile
int k = 0;
int metakx[999999];
int metaky[999999];
bool tak[999999];

int f = 0;				// za micanje protivnickih brodova
int g = 2;
int h = 8;

int xprot[72];			// za micanje protivnickih brodova
int yprot[72];
int m = 0;
bool desno = true;
bool lijevo = false;

bool protivnici[72];	// broj protivnika koji su jos u igri
int ostaliprot = 0;

int vr = 0;    			// vrijeme za pucanje
int vre = 0;			// vrijeme za micanje protivnika
int brzprot = 500; 		// brzina protivnika
int brzmet  = 400;		// f tvojih metaka

int score = 0;			// bodovi
int preskoci[73];		// ne diraj, da se if loop ne ponavlja kod kolizije
int zivoti = 3;			// zivoti

int vrem = 0;			// vrijeme pucanja protivnika
int pew = 500;			// f pucanja protivnika
int lj = 0;

int xmetakp[999999];	// x koordinata protivnickog metka
int ymetakp[999999];    // y koordinata protivnickog metka
int prpu = 0;			// broj protivnickih metka
bool protmetci[999999]; // za koliziju metaka 

int level = 1;			// level

bool mute = false;		// za gasenje zvuka
int mo = 0;

int ulaz = 0;

void options();
void menu();
void game();

int main() {	
	system("Color 1B");
	menu();
	
	system("PAUSE");
	return 0;
}

void game(int score, int level, int pew, int brzprot) {
	radi = true;

	for( int m = 1; m < 17; m++ )
		for ( int i = 1; i < 38; i++ )
			polje[m][i] = ' ';

	int k = 0;
	int c = 0;
	int h = 8;
	
	int g = 2;
	int f = 0;
	int m = 0;
	int lj = 0;
	
	for( int i = 0; i < 72; i++)			// svi protivnici su true(postoje)
		protivnici[i] = true;
	
	for( int i = 0; i < 72; i++)
		preskoci[i] = -1;
	
	for( int i = 2; i < 8; i++ )				// upisivanje protivnickih brodova
		for( int d = 2; d < 26; d = d + 2 ) {
			xprot[m] = d;
			yprot[m] = i;
			polje[i][d] = 'V';
			m++;						
		}
	
	srand(time(NULL));
	
	while (radi == true) {		// pocetak igre
		system ("cls");
		
		for (int a = 0; a < 20; a++)				// ispis svega
			cout << polje[a] << endl;
			
		cout << "Zivoti: " ;						// ispis zivota
		for(int i = 0; i < zivoti; i++)
			cout << "^ ";		
		
		cout << "\n";
		
		cout << "Bodovi: " << score << endl;		// ispis bodova
		
		cout << "Level: " << level << endl;
		
		cout << "Zvuk: ";
		if (mute == true)
			cout << "Off";
			else
				cout << "On";
		
		int a = clock();
		while((clock() - a ) < 100){}			// brzina igre
		
		if (clock() > vre) {
			if (desno == true) {
				for(int n = 0; n < 72; n++) {					// obrise prot brodove i napise 1 red za desno
					if( protivnici[n] == true) {
						if (clock() > vrem) {					// frekv. pucanja protivnika
							if (polje[yprot[n]+1][xprot[n]] == ' ' && ((rand() % 72 ) == n)) {    // random protivnici pucaju
								polje[yprot[n]+1][xprot[n]] = 'v';
								
								xmetakp[prpu] = xprot[n];
								ymetakp[prpu] = (yprot[n] + 1);
								protmetci[prpu] = true;
								prpu++;
								
								vrem = (clock() + pew);
							}
						}
						polje[yprot[n]][xprot[n]] = ' ';
						polje[yprot[n]][++xprot[n]] = 'V';
					}
						
				}
			}			
			lj = 0;
			
			for ( int s = 0; s < 72; s++)
				if ( xprot[s] == 37 ) {							// kad protivnici dodu do desnog kraja spustaju se red nize
					for( int n = 0; n < 72; n++ )
						polje[yprot[n]][xprot[n]] = ' ';
					
					for( int n = 0; n < 72; n++ )
						if ( protivnici[n] == true )
							polje[++yprot[n]][xprot[n]] = 'V';			
					
					desno = false;
					lijevo = true; 
					break;
				}
			
			for (int s = 0; s < 72; s++)
				if (xprot[s] == 2) {							// kad protivnici dodu do ljevog kraja spustaju se red nize
					for(int n = 0; n < 72; n++)
						polje[yprot[n]][xprot[n]] = ' ';
						
					for(int n = 0; n < 72; n++)
						if (protivnici[n] == true)
							polje[++yprot[n]][xprot[n]] = 'V';	
					
					desno = true;
					lijevo = false;
					break;
				}	
			
			if (lijevo == true) {
				for(int n = 0; n < 72; n++) {					// obrise prot brodove i napise 1 red za lijevo
					if(protivnici[n] == true) {
						if (clock() > vrem) {					// frekv. pucanja protivnika
							if ( polje[yprot[n]+1][xprot[n]] == ' ' && ( ( rand() % 72 ) == n )) {   // random protivnici pucaju
								polje[yprot[n]+1][xprot[n]] = 'v';
								
								xmetakp[prpu] = xprot[n];
								ymetakp[prpu] = ( yprot[n] + 1 );
								protmetci[prpu] = true;
								prpu++;
								 
								vrem = ( clock() + pew );
							}
						}
						polje[yprot[n]][xprot[n]] = ' ';
						polje[yprot[n]][--xprot[n]] = 'V';
					}
				}
			}
			vre = (clock() + brzprot);
		}
		
		for (int s = 0; s < 72; s++)					// game over kad protivnici dodu pre blizu
			if (yprot[s] == 17) {
				radi = false;
				gameOver(score, level);	 
			}
			
		if (zivoti <= 0) {							// game over kad igrac ima 0 zivota
			radi = false;
			gameOver(score, level);	
		}
		
		for (int i = 0; i < prpu; i++) {
			if (protmetci[i] == true) {							// micanje protivnickih metka
				polje[ymetakp[i]][xmetakp[i]] = ' ';
				polje[++ymetakp[i]][xmetakp[i]] = 'v';
			}
			
			if (polje[ymetakp[i]][xmetakp[i]] == polje[y][x]) {		// kad prot metak pogodi igraca
				--zivoti;
				if (mute == false)
					cout << '\a';
				polje[ymetakp[i]][xmetakp[i]] = ' ';
				int po = clock();
				while((clock() - po) < 1000) {}
				polje[ymetakp[i]][xmetakp[i]] = '^';
				
				protmetci[i] = false;
				xmetakp[i] = 7;							// da se igrac ne sudari opet s istim metkom
				ymetakp[i] = 1;
			}
			
			if (ymetakp[i] == 18) {						// kad protivnicki metci dodu do kraja polja ih izbrise
				polje[ymetakp[i]][xmetakp[i]] = ' ';
				protmetci[i] = false;
				xmetakp[i] = 6;							// da se igrac ne sudari opet s istim metkom
				ymetakp[i] = 1;
			}
		}
		
		for(int b = 0; b < k; b++) {              // micanje metka
			if ( tak[b] == true ) {		
				polje[metaky[b]][metakx[b]] = ' ';
				metaky[b]--;
				polje[metaky[b]][metakx[b]] = '*';
										
			}
			
			if( metaky[b] == 1 ) {
				tak[b] = false;
				polje[metaky[b]][metakx[b]] = ' ';
			}	
		}		
		
		for (int i = 0; i < 72; i++)					// provjerava koliko protivnika ima	
			if ( protivnici[i] == true )
				ostaliprot++;
					
		if (ostaliprot == 0) {						// game over kad nema protivnika
    		for (int b = 0; b < k; b++) {              // micanje metka
    			if (tak[b] == true) {		
    				polje[metaky[b]][metakx[b]] = ' ';    										
    			}
            }
  			
  			if (level >= 3)
				game(score+500, level+1, pew-500, brzprot-50);
  				else
  					game(score+500, level+1, pew-500, brzprot-100);
		}

		for (int s = 0; s < 72; s++) 											// kolizija
			for (int r = 0; r < k; r++)
				if ( preskoci[s] != s )
					if ( polje[metaky[r]][metakx[r]] == polje[yprot[s]][xprot[s]] ) {  // gresku tu negdje
						polje[metaky[r]][metakx[r]] = ' ';
						
						tak[r] = false;
						metaky[r] = 2;
						metakx[r] = 2;
						
						protivnici[s] = false;
						yprot[s] = 1;
						xprot[s] = 5;
						
						preskoci[s] = s;
						score += 20;	                     
					}
			
		ostaliprot = 0;	
		
		if (GetAsyncKeyState ('M'))	{	// za gasit zvuk
			mute = true;
			
			if ( mo == 1) {
				mute = false;
				mo = 0;
			}
				else
					mo = 1;			
		}
		
		if (GetAsyncKeyState (VK_SPACE)) {          // pucanje
			if ( clock() > vr ) {
				metakx[k] = x;
				metaky[k] = (y - 1);
				polje[metaky[k]][metakx[k]] = '*';
				tak[k] = true;
				k++;
				if ( mute == false )
					cout << '\a';
				vr = clock() + brzmet;
			}
		}	
		
		if (GetAsyncKeyState (VK_RIGHT)) {          // pomak u desno
			int x2 = x+1;
			if ( polje[y][x2] == ' ') {
				polje[y][x] = ' ';
				x++;
				polje[y][x]	= '^';	
			}
		}	
		
		if (GetAsyncKeyState (VK_LEFT)) {				// pomak u lijevo
			int x2 = x-1;
			if ( polje[y][x2] == ' ')
			{
				polje[y][x] = ' ';
				x--;
				polje[y][x]	= '^';	
			}
		}
		
		if (GetAsyncKeyState ('P')) {
			system("cls");
			
			cout<<"\n\n";
			cout<<"		########     ###    ##     ##  ######  ######## " << endl;
			cout<<"		##     ##   ## ##   ##     ## ##    ## ##       " << endl;
			cout<<"		##     ##  ##   ##  ##     ## ##       ##       " << endl;
			cout<<"		########  ##     ## ##     ##  ######  ######   " << endl;
			cout<<"		##        ######### ##     ##       ## ##       " << endl;
			cout<<"		##        ##     ## ##     ## ##    ## ##       " << endl;
			cout<<"		##        ##     ##  #######   ######  ######## " << endl;
			
			cout <<"\n\n                             Press P to continue." << endl;
			Sleep(200);
			bool pauza = true;
			while( pauza == true) {
				if (GetAsyncKeyState ('P')) 
					pauza = false;
			}
		}
		
		if (GetAsyncKeyState (VK_ESCAPE))			// zatvaranje igre
			radi = false;
	}
}

void menu() {
	char polje1[13] = {' ','>',' ','S','t','a','r','t',' ','G','a','m','e'};
	char polje2[10]	= {' ',' ',' ','O','p','t','i','o','n','s'};

	string picture1[9];
	picture1[0] = "                             ##          ## ";
	picture1[1] = "                             ##          ## ";
	picture1[2] = "                             ############## ";
	picture1[3] = "                           ####  ######  #### ";
	picture1[4] = "                         ###################### ";
	picture1[5] = "                         ##  ##############  ## ";
	picture1[6] = "                         ##  ##          ##  ## ";
	picture1[7] = "                         ##  ##############  ## ";
	picture1[8] = "                               ####  #### ";
	
	int picture1Left = 0;		// magic numbers that position the spaceman in the middle of the screen
	int picture1Right = -15;
	
	boolean mouthOpen = true;
	
	while (true) {	
		system("cls");
		
		cout<<"              .---.                   ,                .        " << endl;    
		cout<<"              \\___  ,-. ,-. ,-. ,-.   . ,-. .  , ,-. ,-| ,-. ,-. ,-. "<< endl;
		cout<<"                  \\ | | ,-| |   |-'   | | | | /  ,-| | | |-' |   `-. "<< endl;
		cout<<"              `---' |-' `-^ `-' `-'   ' ' ' `'   `-^ `-' `-' '   `-' "<< endl;
		cout<<"                    |                                               "<< endl;
		cout<<"                    '                                              "<< endl;
		                                                                                                                                                                                                                                   
		if (picture1Right == 0) {
			movePictureLeft(picture1);
			picture1Left +=1;
			
			if (picture1Left == 27) {
				picture1Right = -1 * picture1Left;
				picture1Left = 0;
			}
		} else {
			movePictureRight(picture1);
			picture1Right += 1;
		}
			
		for (int i = 0; i < 6; i++)
			cout << picture1[i] << endl;
			
		if (mouthOpen) {
			cout << picture1[6] << endl;
			cout << picture1[8] << endl << endl << endl;
			mouthOpen = false;
		}
		else {
			cout << picture1[7] << endl << endl << endl << endl;
			mouthOpen = true;
		}		

		for ( int i = 0; i < 13; i++)
			cout << polje1[i];
		cout <<"         Pomoc: Kretanje - strjelice " << endl;
		for ( int i = 0; i < 10; i++)
			cout << polje2[i];
		cout <<"                   Pucanje - space " << endl;
		cout <<"                             Zvuk - M " << endl;
		cout <<"                             Ugasit igru - esc " << endl;
		cout <<"                             Odabir u opcijama - enter " << endl;
		cout <<"                             Pauza - P " << endl;
		
		switch(ulaz) {
			case 1:						// start game
//				goto nextlvl;
				game(score, level, pew, brzprot);
				ulaz = 0;
				break;
				
			case 2: 
				options();
				ulaz = 0;
				break;
		}
		
		if (GetAsyncKeyState (VK_UP)) {
			polje1[1] = '>';
			polje2[1] = ' ';
		}
		
		if (GetAsyncKeyState (VK_DOWN)) {
			polje1[1] = ' ';
			polje2[1] = '>';
		}
		
		Sleep(150);
		
		if (GetAsyncKeyState (VK_RETURN)) {
			if ( polje1[1] == '>' )
				ulaz = 1;
			
			if ( polje2[1] == '>' )
				ulaz = 2;
		}
	}
}

void options() {
	signed int a = 0;
	bool optionz = true;
	
	string menuItems[5];
	menuItems[0] = " > Zivoti -";
	menuItems[1] = "   Frekvencija pucanja -";
	menuItems[2] = "   Frekvencija pucanja protivnika -";
	menuItems[3] = "   Brzina protivnika -";
	menuItems[4] = "   Natrag";
	
	while (optionz == true) {
		Sleep(150);
		system("cls");
		     
		cout<<"\n";
		cout<<"            #######  ########  ######## ####  #######  ##    ##  ######  " << endl;
		cout<<"           ##     ## ##     ##    ##     ##  ##     ## ###   ## ##    ## " << endl;
		cout<<"           ##     ## ##     ##    ##     ##  ##     ## ####  ## ##       " << endl;
		cout<<"           ##     ## ########     ##     ##  ##     ## ## ## ##  ######  " << endl;
		cout<<"           ##     ## ##           ##     ##  ##     ## ##  ####       ## " << endl;
		cout<<"           ##     ## ##           ##     ##  ##     ## ##   ### ##    ## " << endl;
		cout<<"            #######  ##           ##    ####  #######  ##    ##  ######  \n\n" << endl;
		
		cout << menuItems[0];
			
		cout << " " << zivoti;		// ispis zivota u opcijama
			
		cout << "\n\n";
		cout << menuItems[1];
			
		cout << " " << brzmet << " (Veca brojka --> manja frekvencija)";		// ispis frekv. metaka u opcijama
		
		cout << "\n\n";	
		cout << menuItems[2];
			
		cout << " " << pew << " (Veca brojka --> manja frekvencija)";		// ispise frekv. pucanja protivnika
			
		cout << "\n\n";
		
		cout << menuItems[3];
			
		cout << " " << brzprot << " (Veca brojka --> sporiji protivnici)";		// ispis brznine metaka u opcijama
		
		cout << "\n\n";
		
		cout << menuItems[4]; 
		cout << "\n\n";
		
		cout <<"                       Povecaj i smanjuj s strijelicama." << endl;
		
		if (GetAsyncKeyState (VK_UP)) {
			if (a > 0) {
				a--;
				updateMenuPointer(a, menuItems); 
			}
		}
		
		if (GetAsyncKeyState (VK_DOWN)) {
			if(a < 4) {
				a++;
				updateMenuPointer(a, menuItems);
			}
		}
		
		if (GetAsyncKeyState (VK_RIGHT)) {
			if (a == 0 && zivoti < 10)		// mijenjanje zivota
				zivoti++;
				
				
			if (a == 1 && brzmet < 700)		// mijenjanje frekv. pucanja
				brzmet += 50;
				
			if (a == 2 && pew < 700)
				pew += 50;
				
			if (a == 3 && brzprot < 700)		// mijenjanje brzine protivnika
				brzprot += 50;
		}		
		
		if (GetAsyncKeyState (VK_LEFT)) {
			if (a == 0 && zivoti > 1)			// mijenjanje zivota
				zivoti--;
			
			if (a == 1 && brzmet > 100)		// mijenjanje frekv. pucanja
				brzmet -= 50;
				
			if (a == 2 && pew > 50)
				pew -= 50;
				
			if (a == 3 && brzprot > 50)		// mijenjanje brzine protivnika
				brzprot -= 50;
		}
		
		if (GetAsyncKeyState (VK_RETURN)) {
			if (a == 4)
				optionz = false;	
		}
			
	}	
	
}
