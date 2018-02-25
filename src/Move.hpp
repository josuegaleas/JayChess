/*
 * Author: Josue Galeas
 * Last Edit: 2018.02.20
 */

#ifndef MOVE_HPP
#define MOVE_HPP

class Move
{
	private:
		int *init = new int[2];
		int *fin = new int[2];

	public:
		Move(int *, int *);
		~Move() {delete[] init; delete[] fin;};
		int *getInit() const {return init;};
		int *getFin() const {return fin;};
};

#endif /* MOVE_HPP */
