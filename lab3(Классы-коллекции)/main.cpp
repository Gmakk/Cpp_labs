#include "Dialog.h"

int main() {
	Plate plate;
	int rc;
	const char* msgs[] = { "0. Quit", "1. Add contact", "2. Add link", "3. Check correctness", "4. Show group", "5. Show all", "6. Find length" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(Plate&) = { NULL, D_AddContact, D_AddLink, D_Correct, D_Group, D_Info, D_Length };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](plate))
			break;
	printf("That's all.\n");
	return 0;
}