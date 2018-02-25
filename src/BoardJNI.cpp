/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.24
 */

#include "Board.h"
#include "Verification.hpp"
#include "AN.hpp"

static Board *b;

JNIEXPORT void JNICALL
Java_Board_createBoard(JNIEnv *, jobject)
{
	b = new Board();
}

JNIEXPORT void JNICALL
Java_Board_updateBoard(JNIEnv *env, jobject obj)
{
	jclass clazz = env->GetObjectClass(obj);
	jmethodID mid = env->GetMethodID(clazz, "setLabel", "(IILjava/lang/String;)V");

	std::string symbol;
	jstring label;

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			symbol = b->getPiece(x, y)->getSymbol();
			label = env->NewStringUTF(symbol.c_str());
			env->CallVoidMethod(obj, mid, x, y, label);
		}
	}
}

JNIEXPORT void JNICALL
Java_Board_deleteBoard(JNIEnv *, jobject)
{
	delete b;
}

JNIEXPORT jchar JNICALL
Java_Board_getColor(JNIEnv *, jobject, jint x, jint y)
{
	return (jchar)b->getPiece(x, y)->getColor();
}

JNIEXPORT jboolean JNICALL
Java_Board_verifyMove(JNIEnv *env, jobject obj, jintArray i, jintArray f)
{
	jboolean isCopy;
	jint *init = env->GetIntArrayElements(i, &isCopy);
	jint *fin = env->GetIntArrayElements(f, &isCopy);

	Move m(init, fin);

	if (verifyCapture(&m, b))
	{
		if (verifyMove(&m, b))
		{
			jclass clazz = env->GetObjectClass(obj);
			jfieldID fid = env->GetFieldID(clazz, "an", "Ljava/lang/String;");
			std::string AN = getAN(&m, b);
			updatePieces(&m, b);
			jstring an = env->NewStringUTF(getANCheck(AN, b).c_str());
			env->SetObjectField(obj, fid, an);

			return JNI_TRUE;
		}
	}

	return JNI_FALSE;
}
