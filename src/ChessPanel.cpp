/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
 */

#include "ChessPanel.h"
#include <cstdio>

JNIEXPORT void JNICALL Java_ChessPanel_printClick(JNIEnv *env, jobject obj, jint x, jint y)
{
	printf("Click! (%d, %d)\n", (int)x, (int)y);
}
