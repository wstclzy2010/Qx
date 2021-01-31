/* FPRESET.C: This program uses signal to set up a
* routine for handling floating-point errors.
*/

＃include <stdio.h>
＃include <signal.h>
＃include <setjmp.h>
＃include <stdlib.h>
＃include <float.h>
＃include <math.h>
＃include <string.h>

jmp_buf mark; /* Address for long jump to jump to */
int fperr; /* Global error number */

void __cdecl fphandler( int sig, int num ); /* Prototypes */
void fpcheck( void );

void main( void )
{
double n1, n2, r;
int jmpret;
/* Unmask all floating-point exceptions. */
_control87( 0, _MCW_EM );
/* Set up floating-point error handler. The compiler
* will generate a warning because it expects
* signal-handling functions to take only one argument.
*/
if( signal( SIGFPE, fphandler ) == SIG_ERR )

{
fprintf( stderr, "Couldnt set SIGFPEn" );
abort(); }

/* Save stack environment for return in case of error. First 
* time through, jmpret is 0, so true conditional is executed. 
* If an error occurs, jmpret will be set to -1 and false 
* conditional will be executed.
*/

// 注意，下面这条语句的作用是，保存程序当前运行的状态
jmpret = setjmp( mark );
if( jmpret == 0 )
{
printf( "Test for invalid operation - " );
printf( "enter two numbers: " );
scanf( "%lf %lf", &n1, &n2 );

// 注意，下面这条语句可能出现异常，
// 如果从终端输入的第2个变量是0值的话
r = n1 / n2;
/* This won"t be reached if error occurs. */
printf( "nn%4.3g / %4.3g = %4.3gn", n1, n2, r );

r = n1 * n2;
/* This won"t be reached if error occurs. */
printf( "nn%4.3g * %4.3g = %4.3gn", n1, n2, r );
}
else
fpcheck();
}
/* fphandler handles SIGFPE (floating-point error) interrupt. Note
* that this prototype accepts two arguments and that the 
* prototype for signal in the run-time library expects a signal 
* handler to have only one argument.
*
* The second argument in this signal handler allows processing of
* _FPE_INVALID, _FPE_OVERFLOW, _FPE_UNDERFLOW, and 
* _FPE_ZERODIVIDE, all of which are Microsoft-specific symbols 
* that augment the information provided by SIGFPE. The compiler 
* will generate a warning, which is harmless and expected.

*/
void fphandler( int sig, int num )
{
/* Set global for outside check since we don"t want
* to do I/O in the handler.
*/
fperr = num;
/* Initialize floating-point package. */
_fpreset();
/* Restore calling environment and jump back to setjmp. Return 
* -1 so that setjmp will return false for conditional test.
*/
// 注意，下面这条语句的作用是，恢复先前setjmp所保存的程序状态
longjmp(mark, -1 );
}
void fpcheck( void )
{
char fpstr[30];
switch( fperr )
{
case _FPE_INVALID:
strcpy( fpstr, "Invalid number" );
break;
case _FPE_OVERFLOW:
strcpy( fpstr, "Overflow" );

break;
case _FPE_UNDERFLOW:
strcpy( fpstr, "Underflow" );
break;
case _FPE_ZERODIVIDE:
strcpy( fpstr, "Divide by zero" );
break;
default:
strcpy( fpstr, "Other floating point error" );
break;
}
printf( "Error %d: %sn", fperr, fpstr );
}