/*
 * Author: Josue Galeas
 * Last Edit: September 22, 2017
 */

#ifndef MOVE_H
#define MOVE_H

class Move
{
	private:
		int *init;
		int *fin;

	public:
		Move(int *, int *);
		~Move() {delete[] init; delete[] fin;};
		int *getInit() const {return init;};
		int *getFin() const {return fin;};
};

#endif
