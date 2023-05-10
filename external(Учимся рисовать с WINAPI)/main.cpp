#include "Dialog.h"

int main() {
	laba3::Polygon polygon;
	int rc;
	const char* msgs[] = { "0. Quit", "1. Set a circle", "2. Set a square", "3. Set a triangle", "4. Show all points", "5. Draw a bear", "6. Draw a rabbit", "7. tic tac toe" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	int(*fptr[])(laba3::Polygon&) = { NULL, D_Circle, D_Square, D_Triangle, D_Show, D_Bear, D_Rabbit, D_Tic_Tac };
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](polygon))
			break;
	printf("That's all.\n");
}