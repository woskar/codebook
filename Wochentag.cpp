#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int weekday2001(int d, int m, int y);
int floorDiv(int a, int b);
int floorMod(int a, int b);
int weekday(int d, int m, int y);
int weekday1(int d, int m, int y);

//Definieren der Wochentagswerte zur besseren Übersicht beim Überprüfen
#define MONTAG		0
#define DIENSTAG	1
#define MITTWOCH	2
#define DONNERSTAG	3
#define FREITAG		4
#define	SAMSTAG		5
#define SONNTAG		6

int main()
{
	//Testen der Wochentags berechnung mit Floor Div:
	// Ausfallendes Schaltjahr vor 2001
	assert(weekday(11,1,1900)==DONNERSTAG);
	assert(weekday(11,9,1900)==DIENSTAG);
	// kein Schaltjahr vor 2001
	assert(weekday(19,10,1591)==SAMSTAG);
	assert(weekday(11,2,1931)==MITTWOCH);
	assert(weekday(27,6,1931)==SAMSTAG);
	// Schaltjahr vor 2001
	assert(weekday(3,1,1968)==MITTWOCH);
	assert(weekday(7,8,1968)==MITTWOCH);
	// Ausfallendes Schaltjahr nach 2001
	assert(weekday(15,2,2100)==MONTAG);
	assert(weekday(7,12,2100)==DIENSTAG);
	// kein Schaltjahr nach 2001
	assert(weekday(27,1,2030)==SONNTAG);
	assert(weekday(16,7,2030)==DIENSTAG);
	assert(weekday(19,10,2001)==FREITAG);
	// Schaltjahr nach 2001
	assert(weekday(18,11,2016)==FREITAG);
	assert(weekday(25,11,2016)==FREITAG);
	assert(weekday(11,1,2016)==MONTAG);
	assert(weekday(19,10,2016)==MITTWOCH);
	
	
	//Testen der Wochentags berechnung ohne Floor Div:
	// Ausfallendes Schaltjahr vor 2001
	assert(weekday1(11,1,1900)==DONNERSTAG);
	assert(weekday1(11,9,1900)==DIENSTAG);
	// kein Schaltjahr vor 2001
	assert(weekday1(19,10,1591)==SAMSTAG);
	assert(weekday1(11,2,1931)==MITTWOCH);
	assert(weekday1(27,6,1931)==SAMSTAG);
	// Schaltjahr vor 2001
	assert(weekday1(3,1,1968)==MITTWOCH);
	assert(weekday1(7,8,1968)==MITTWOCH);
	// Ausfallendes Schaltjahr nach 2001
	assert(weekday1(15,2,2100)==MONTAG);
	assert(weekday1(7,12,2100)==DIENSTAG);
	// kein Schaltjahr nach 2001
	assert(weekday1(27,1,2030)==SONNTAG);
	assert(weekday1(16,7,2030)==DIENSTAG);
	assert(weekday1(19,10,2001)==FREITAG);
	// Schaltjahr nach 2001
	assert(weekday1(18,11,2016)==FREITAG);
	assert(weekday1(25,11,2016)==FREITAG);
	assert(weekday1(11,1,2016)==MONTAG);
	assert(weekday1(19,10,2016)==MITTWOCH);
	
	return 0;
}

//a) Berechnung des Wochentags für ein Daum, Jahr muss größer 2001
int weekday2001(int d, int m, int y)
{
	//bool schaltjahr = (!(y % 4) && (y % 100)) || !(y % 400);				//original: funktioniert weil bools intern int sind und ==0 => false; >0 => true
	bool schaltjahr = ((y % 4 == 0) && (y % 100 !=0)) || (y % 400 == 0);  	//find ich lesbarer
	
	//Berechnung des Wochentags am ersten Januar
	int z = y - 2001;
	int j_1 = (365*z + z/4 - z/100 + z/400) % 7;
	
	//Berechnung, der wievielte Tag es ist
	int p =	(m==1)? 				d:
			(m==2)? 				d+31:
			(m >2 && !schaltjahr)? 	d + 59 + (153*m - 457)/5:
			/*else*/				d + 60 + (153*m - 457)/5;
				
	//Bestimmung des Wochentags
	int w = (j_1 + p - 1) % 7;
	
	return w;
}


//b) Division mit abrunden statt truncat
int floorDiv(int a, int b)
{	
	//Normale Division wenn Ergebnis positiv oder Rest, sonst minus 1
	//return a/b - ((a%b && ((a>0) != (b>0)))? 1 : 0);						//original 


	//und mit hinweis aus dem Zettel
	int betr_a = ( a>= 0)? a : -a;
	int betr_b = ( b>= 0)? b : -b;
	int c = betr_b - 1; 

	return (a*b < 0 ) ? -((betr_a + c)/betr_b) :
						a/b; 
	
	//return (a+(a/b)*b)/b;
}

//c) Modulo funktion zur Floor Division
int floorMod(int a, int b)
{
	//cout << a%b + b;
	//cout << a%b + ((a%b && (!(a<0) != !(b<0)))? b : 0);
	//return a%b + ((a%b && (!(a<0) != !(b<0)))? b : 0);

	return a-floorDiv(a,b)*b; 								//definition vom Rest
}

//d) Wochentag berechnen für beliebiges Jahr ab 1583
int weekday(int d, int m, int y)
{
	//bool schaltjahr = (!(y % 4) && (y % 100)) || !(y % 400);
	bool schaltjahr = ((y % 4 == 0) && (y % 100 !=0)) || (y % 400 == 0);  	//find ich lesbarer
	
	//Berechnung des Wochentags am ersten Januar
	int z = y - 2001;
	int j_1 = floorMod((365*z + floorDiv(z,4) - floorDiv(z,100) + floorDiv(z,400)), 7);
	
	//Berechnung, der wievielte Tag es ist
	int p =	(m==1)? 				d:
			(m==2)? 				d+31:
			(m >2 && !schaltjahr)? 	d + 59 + floorDiv((153*m - 457),5):
			/*else*/				d + 60 + floorDiv((153*m - 457),5);
				
	//Bestimmung des Wochentags
	int w = floorMod((j_1 + p - 1) , 7);
	
	return w;
	
}

//e) Alternative zu d) ohne Floor Division
//   
//   Das ist möglich, weil 2000 durch 4, 100 und 400 teilbar ist. Da bei allen Teilrechnungen 
//   Modulo gerechnet wird hat dies keinen Einfluss ob Schaltjahr ist. Da das Jahr aber immer
//   positiv ist wird keine floorDiv benötigt
int weekday1(int d, int m, int y)
{
	//bool schaltjahr = (!(y % 4) && (y % 100)) || !(y % 400);
	bool schaltjahr = ((y % 4 == 0) && (y % 100 !=0)) || (y % 400 == 0);  	//find ich lesbarer
	
	//Berechnung des Wochentags am ersten Januar
	int z = y - 1;
	int j_1 = (365*z + z/4 - z/100 + z/400) % 7;
	
	//Berechnung, der wievielte Tag es ist
	int p =	(m==1)? 				d:
			(m==2)? 				d + 31:
			(m >2 && !schaltjahr)? 	d + 59 + (153*m - 457)/5:
			/*else*/				d + 60 + (153*m - 457)/5;
				
	//Bestimmung des Wochentags
	int w = (j_1 + p - 1) % 7;
	
	return w;
	
}
