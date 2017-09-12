/*
 * Author: Josue Galeas
 * Last Edit: September 12, 2017
 */

#include "Board.h"
#include "Verification.hpp"

static Game *g;

JNIEXPORT void JNICALL
Java_Board_createBoard(JNIEnv *env, jobject obj)
{
	g = new Game();
}

JNIEXPORT void JNICALL
Java_Board_updateBoard(JNIEnv *env, jobject obj)
{
	jclass clazz = env->GetObjectClass(obj);
	jmethodID mid = env->GetMethodID(clazz, "updateLabelOf", "(IILjava/lang/String;)V");

	std::string symbol;
	jstring label;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			symbol = g->getBoard()->getPiece(x, y)->getSymbol();
			label = env->NewStringUTF(symbol.c_str());
			env->CallVoidMethod(obj, mid, x, y, label);
		}
	}
}

JNIEXPORT void JNICALL
Java_Board_deleteBoard(JNIEnv *env, jobject obj)
{
	delete g;
}

JNIEXPORT jchar JNICALL
Java_Board_getColorOf(JNIEnv *env, jobject obj, jint x, jint y)
{
	return (jchar)g->getBoard()->getPiece(x, y)->getColor();
}

JNIEXPORT jboolean JNICALL
Java_Board_verifyMove(JNIEnv *env, jobject obj, jint ix, jint iy, jint fx, jint fy)
{
	Move *m = new Move(ix, iy, fx, fy);

	if (verifyCapture(m, g))
	{
		if (verifyMove(m, g))
		{
			updatePieces(m, g);

			delete m;
			return JNI_TRUE;
		}
	}

	delete m;
	return JNI_FALSE;
}
