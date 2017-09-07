/*
 * Author: Josue Galeas
 * Last Edit: September 7, 2017
 */

#include "Board.h"
#include "Board.hpp"
#include "Verification.hpp"
#include <cstdio>

static Board *b;

JNIEXPORT void JNICALL
Java_Board_createBoard(JNIEnv *env, jobject obj)
{
	b = new Board();
}

JNIEXPORT void JNICALL
Java_Board_updateBoard(JNIEnv *env, jobject obj, jobject game)
{
	jclass clazz = env->GetObjectClass(game);
	std::string symbol;
	jstring label;
	jmethodID mid;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			symbol = b->getPiece(x, y)->getSymbol();
			label = env->NewStringUTF(symbol.c_str());
			mid = env->GetMethodID(clazz, "updateLabelOf", "(IILjava/lang/String;)V");
			env->CallVoidMethod(game, mid, (jint)x, (jint)y, label);
		}
	}
}

JNIEXPORT void JNICALL
Java_Board_deleteBoard(JNIEnv *env, jobject obj)
{
	delete b;
}

JNIEXPORT jboolean JNICALL
Java_Board_verifyMove(JNIEnv *env, jobject obj, jintArray i, jintArray f)
{
	jboolean isCopy;
	jint *init = env->GetIntArrayElements(i, &isCopy);
	jint *fin = env->GetIntArrayElements(f, &isCopy);

	Move *m = new Move(init, fin);

	if (verifyCapture(m, b))
	{
		if (verifyMove(m, b))
		{
			updatePieces(m, b);

			delete m;
			return JNI_TRUE;
		}
	}

	delete m;
	return JNI_FALSE;
}
