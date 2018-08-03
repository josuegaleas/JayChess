/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.24
 */

#include "Board.h"
#include "Verification.hpp"
#include "AN.hpp"
#include <cassert>

static Board *board;
void updatePieces(Move *, Board *);

void updatePieces(Move *m, Board *b)
{
	assert(m);
	assert(b);

	Piece *initPiece = b->getPiece(m->getInit());
	Piece *finPiece = b->getPiece(m->getFin());

	initPiece->setMoved(true);
	finPiece->setPiece(initPiece);
	initPiece->setPiece('E', 'E', false);

	if (b->getCastling())
	{
		int *rookPos = b->getRook();
		Piece *rookInit = b->getPiece(rookPos);
		Piece *rookFin;

		if (rookPos[1] == 0)
			rookFin = b->getPiece(rookPos[0], 3);
		else if (rookPos[1] == 7)
			rookFin = b->getPiece(rookPos[0], 5);
		else
			return;

		rookInit->setMoved(true);
		rookFin->setPiece(rookInit);
		rookInit->setPiece('E', 'E', false);

		b->setCastling();
		b->setRook();
	}

	if (b->getPawnPromotion())
	{
		// TODO: Need to ask user what piece they want!
		// However, in almost all cases, they pick queen.
		finPiece->setType('Q');
		b->setPawnPromotion();
	}
}

JNIEXPORT void JNICALL
Java_Board_createBoard(JNIEnv *, jobject)
{
	board = new Board();
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
			symbol = "LOL";
			label = env->NewStringUTF(symbol.c_str());
			env->CallVoidMethod(obj, mid, x, y, label);
		}
	}
}

JNIEXPORT void JNICALL
Java_Board_deleteBoard(JNIEnv *, jobject)
{
	delete board;
}

JNIEXPORT jchar JNICALL
Java_Board_getColor(JNIEnv *, jobject, jint x, jint y)
{
	return static_cast<jchar>(board->getPiece(x, y)->getColor());
}

JNIEXPORT jboolean JNICALL
Java_Board_verifyMove(JNIEnv *env, jobject obj, jintArray i, jintArray f)
{
	jboolean isCopy;
	jint *init = env->GetIntArrayElements(i, &isCopy);
	jint *fin = env->GetIntArrayElements(f, &isCopy);

	Move m(init, fin);

	if (verifyCapture(&m, board))
	{
		if (verifyMove(&m, board))
		{
			jclass clazz = env->GetObjectClass(obj);
			jfieldID fid = env->GetFieldID(clazz, "an", "Ljava/lang/String;");
			std::string AN = getAN(&m, board);
			updatePieces(&m, board);
			jstring an = env->NewStringUTF(getANCheck(AN, board).c_str());
			env->SetObjectField(obj, fid, an);

			return JNI_TRUE;
		}
	}

	return JNI_FALSE;
}
