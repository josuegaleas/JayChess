/*
 * Author: Josue Galeas
 * Last Edit: September 6, 2017
 */

#include "Board.h"
#include "Board.hpp"
#include <cstdio>

static Board *b;

JNIEXPORT void JNICALL Java_Board_createBoard(JNIEnv *env, jobject obj)
{
	b = new Board();
}

JNIEXPORT void JNICALL Java_Board_updateBoard(JNIEnv *env, jobject obj, jobject game)
{
	jclass clazz = env->GetObjectClass(game);
	jmethodID mid;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			std::string symbol = b->getPiece(x, y)->getSymbol();
			jstring label = env->NewStringUTF(symbol.c_str());
			mid = env->GetMethodID(clazz, "updateLabelOf", "(IILjava/lang/String;)V");
			env->CallVoidMethod(game, mid, (jint)x, (jint)y, label);
		}
	}
}

JNIEXPORT void JNICALL Java_Board_deleteBoard(JNIEnv *env, jobject obj)
{
	delete b;
}
