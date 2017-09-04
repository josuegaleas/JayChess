/*
 * Author: Josue Galeas
 * Last Edit: September 4, 2017
 */

#include "ChessBoard.h"
#include "ChessBoard_Board.h"
#include "ChessBoard_FilesBar.h"
#include "ChessBoard_RanksBar.h"
#include "Board.hpp"
#include <cstdio>

static Board *b;

JNIEXPORT void JNICALL Java_ChessBoard_createBoard(JNIEnv *env, jobject obj)
{
	b = new Board();
}

JNIEXPORT void JNICALL Java_ChessBoard_updateBoard(JNIEnv *env, jobject obj, jobject game)
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

JNIEXPORT void JNICALL Java_ChessBoard_deleteBoard(JNIEnv *env, jobject obj)
{
	delete b;
}
