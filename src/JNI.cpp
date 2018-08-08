/*
 * Author: Josue Galeas
 * Last Edit: 2018.08.08
 */

#include "Board.h"
#include "Verification.hpp"
#include "JNIHelper.hpp"
#include <cassert>

static Board *board;

JNIEXPORT void JNICALL Java_Board_createBoard(JNIEnv *, jobject)
{
	board = new Board();
}

JNIEXPORT void JNICALL Java_Board_deleteBoard(JNIEnv *, jobject)
{
	delete board;
}

JNIEXPORT jchar JNICALL Java_Board_getColor(JNIEnv *, jobject, jint x, jint y)
{
	return static_cast<jchar>(board->getPiece(x, y)->getColor());
}

JNIEXPORT jchar JNICALL Java_Board_getType(JNIEnv *, jobject, jint x, jint y)
{
	return static_cast<jchar>(board->getPiece(x, y)->getType());
}

JNIEXPORT jboolean JNICALL Java_Board_verifyMove(JNIEnv *env, jobject obj, jintArray i, jintArray f)
{
	jboolean isCopy;
	jint *init = env->GetIntArrayElements(i, &isCopy);
	jint *fin = env->GetIntArrayElements(f, &isCopy);

	Move m(init, fin);

	if (verifyCapture(&m, board) && verifyMove(&m, board))
	{
		jclass clazz = env->GetObjectClass(obj);
		jfieldID fid = env->GetFieldID(clazz, "an", "Ljava/lang/String;");

		std::string AN = getAN(&m, board);
		updatePieces(&m, board);
		getANCheck(AN, board);
		// FIXME: Testing
		int *pawn = board->getPawn();
		printf("pawnMovedTwo: %d\n", board->getPawnMovedTwo());
		printf("pawnPos: (%d, %d)\n\n", pawn[0], pawn[1]);

		jstring an = env->NewStringUTF(AN.c_str());
		env->SetObjectField(obj, fid, an);

		return JNI_TRUE;
	}

	return JNI_FALSE;
}
