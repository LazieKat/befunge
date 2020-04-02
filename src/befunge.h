#ifndef BEFUNGE_98_CPP
#define BEFUNGE_98_CPP

////  Includes
#include <fstream>

////  Defines
#define INIT 10

////  Befunge class declarationaaa
class Befunge
{
	private:
		enum Directions {up, down, left, right};
		Directions direction = right;
		int capacity = INIT;
		int used = 0;
		int *stack = (int *)calloc(INIT, sizeof(int));
		int pc_position[2] = {0, 0};
		char program[25][80];

		int extend();
		int stack_is_full();
		int get_current();
		int get_at(int x, int y);
		void put_at(int v, int x, int y);

	public:
		Befunge(std::ifstream *file);
		void push(int value);
		int pop();
		void move();
		void execute();

		void add();
		void subtract();
		void multiply();
		void divide();
		void modulo();
		void negate();
		void greater_than();
		void dir_down();
		void dir_up();
		void dir_right();
		void dir_left();
		void dir_random();
		void horizontal_if();
		void vertical_if();
		void string_mode();
		void duplicate();
		void swap();
		void out_int();
		void out_char();
		void bridge();
		void get();
		void put();
		void in_int();
		void in_char();
		void end();
};

#endif