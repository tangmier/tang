#include "stdafx.h"
int s=0;
void sets(){
	s=0;
}
void score(int totalTime)
{
	if(totalTime<20)
		s=s + 20;
	else 
		s=s + int(20*20/totalTime);
	
}
int getScore()
{
	return s;
}