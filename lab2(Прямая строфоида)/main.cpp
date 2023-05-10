#include "Header.h"

int main() { 
	strophoid* object = new strophoid;
	int rc;
	const char* msgs[] = { "0. Quit", "1. Show", "2. Change", "3. Y coordinate", "4. Distance", "5. Radius", "6. Square", "7. Volume", "8. Asymptote" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(strophoid*) = { NULL, D_Show, D_Change, D_Coord, D_Dist, D_Rad, D_Square, D_Volume, D_Asympt };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](object))
			break;
	delete object;
	printf("That's all.\n");
	return 0;
}