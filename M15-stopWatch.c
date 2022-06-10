#include   <stdio.h>  
#include   <time.h> 
#include   <signal.h> 
 
struct status startTimer(); 
void stopTimer(int signum); 
//////////////////////////////////////////////////////////// 
sig_atomic_t volatile timer_running = 1; 
 
struct status 
{ 
long hr; 
long min; 
long sec; 
} ; 
////////////////////////////////////////////////////////////  
struct status startTimer() 
{ 
time_t begin,end; 
long totsec; 
long v; 
struct status ob; 
 
begin= time(NULL); 
 
signal(SIGINT, &stopTimer); 
 
while(timer_running) 
{ 
end = time(NULL); 
totsec=difftime(end, begin); 
ob.hr=totsec/3600; 
v=totsec%3600; 
ob.min=v/60; 
ob.sec=v%60; 
printf(" %ld : %ld: %ld\n\n " ,ob.hr, ob.min, ob.sec); 
} 
return ob; 
} 
 
void stopTimer(int signum) 
{ 
if (signum == SIGINT) 
timer_running = 0; 
} 
 
/////////////////////////////////////////////////////////////  
int main() 
{ 
struct status ob = startTimer(); 
printf(" Completed- %ld : %ld : %ld\n\n " ,ob.hr, ob.min, ob.sec); 
system("pause"); 
return 0; 
} 
