#include <Windows.h> 
#include <stdio.h>


main() 
{ 
	while(1) 
	{ 
		short a = ::GetAsyncKeyState(VK_LSHIFT);
		printf( "0x%x",a);
	} 
}
