#include "Dialog.h"

int main() {
	Exercises ex;
	int rc;
	const char* msgs[] = { "0. Quit", "1. Show info", "2. Commanders", "3. Location", "4. Duration", "5. Soldiers" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(Exercises&) = { NULL, D_Show, D_Commander, D_Map, D_Duration, D_Soldiers };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](ex))
			break;
	printf("That's all.\n");
	return 0;
}