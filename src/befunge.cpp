////  Includes
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include "befunge.h"

////  Befunge methods implementations
Befunge::Befunge(std::ifstream *file)
{
	srand(time(NULL));
	bool end_of_line = false;
	char c;
	int status;

	for(int i = 0; i < 25; i++)
	{
		for(int j = 0; j < 80; j++)
		{
			if(!end_of_line)
			{
				file->read(&c, 1);
				if(c != '\n' && !file->eof())
				{
					this->program[i][j] = c;
				}
				else
				{
					end_of_line = true;
					this->program[i][j] = ' ';
				}
			}
			else
			{
				this->program[i][j] = ' ';
			}
		}
		end_of_line = false;
	}
}

int Befunge::extend()
{
	int new_capacity = this->capacity*2;
	int *new_stack = (int *)realloc(stack, sizeof(int)*new_capacity);
	if(new_stack != NULL)
	{
		this->capacity = new_capacity;
		this->stack = new_stack;
		return 0;
	}
	return 1;
}

int Befunge::stack_is_full()
{
	if(this->used >= this->capacity-1) return 1;
	else return 0;
}

int Befunge::get_current()
{
	int current = this->program[this->pc_position[0]][this->pc_position[1]];
	return current;
}

int Befunge::get_at(int x, int y)
{
	if(x*y < 0 || x > 79 || y > 24) return 0;
	int v = this->program[y][x];
	return v;
}

void Befunge::put_at(int v, int x, int y)
{
	if(x*y < 0 || x > 79 || y > 24) return;
	this->program[y][x] = v;
}

void Befunge::push(int value)
{
	if(this->stack_is_full())
	while(this->extend());
	this->stack[this->used] = value;
	this->used += 1;
}

int Befunge::pop()
{
	if(this->used-1 < 0) return 0;
	this->used -= 1;
	this->stack[this->used+1] = 0;
	return this->stack[this->used];
}

void Befunge::move()
{
	if(direction == up)
	{
		this->pc_position[0] -= 1;
		if(this->pc_position[0] < 0) this->pc_position[0] = 24;
	}
	else if(direction == down)
	{
		this->pc_position[0] += 1;
		if(this->pc_position[0] > 24) this->pc_position[0] = 0;
	}
	else if(direction == left)
	{
		this->pc_position[1] -= 1;
		if(this->pc_position[1] < 0) this->pc_position[1] = 79;
	}
	else if(direction == right)
	{
		this->pc_position[1] += 1;
		if(this->pc_position[1] > 79) this->pc_position[1] = 0;
	}
}

void Befunge::execute()
{
	int c = this->get_current();

	switch(c)
	{
		case '+':
			this->add();
			break;
		case '-':
			this->subtract();
			break;
		case '*':
			this->multiply();
			break;
		case '/':
			this->divide();
			break;
		case '%':
			this->modulo();
			break;
		case '!':
			this->negate();
			break;
		case '`':
			this->greater_than();
			break;
		case '>':
			this->dir_right();
			break;
		case '<':
			this->dir_left();
			break;
		case '^':
			this->dir_up();
			break;
		case 'v':
			this->dir_down();
			break;
		case '?':
			this->dir_random();
			break;
		case '_':
			this->horizontal_if();
			break;
		case '|':
			this->vertical_if();
			break;
		case '"':
			this->string_mode();
			break;
		case ':':
			this->duplicate();
			break;
		case '\\':
			this->swap();
			break;
		case '$':
			this->pop();
			break;
		case '.':
			this->out_int();
			break;
		case ',':
			this->out_char();
			break;
		case '#':
			this->bridge();
			break;
		case 'g':
			this->get();
			break;
		case 'p':
			this->put();
			break;
		case '&':
			this->in_int();
			break;
		case '~':
			this->in_char();
			break;
		case '@':
			this->end();
			break;
		case 48 ... 57:
			this->push(c-48);
			break;
		case 97 ... 102:
			this->push(c-87);
			break;
		default:
			break;
	}
}

void Befunge::add()
{
	int a = this->pop();
	int b = this->pop();
	int c = b+a;
	this->push(c);
}

void Befunge::subtract()
{
	int a = this->pop();
	int b = this->pop();
	int c = b-a;
	this->push(c);
}

void Befunge::multiply()
{
	int a = this->pop();
	int b = this->pop();
	int c = b*a;
	this->push(c);
}

void Befunge::divide()
{
	int a = this->pop();
	int b = this->pop();
	int c = b/a;
	this->push(c);
}

void Befunge::modulo()
{
	int a = this->pop();
	int b = this->pop();
	int c = b%a;
	this->push(c);
}

void Befunge::negate()
{
	int a = this->pop();
	push(a == 0 ? 1 : 0);
}

void Befunge::greater_than()
{
	int a = this->pop();
	int b = this->pop();
	int c = b > a ? 1 : 0;
	this->push(c);
}

void Befunge::dir_down()
{
	this->direction = down;
}

void Befunge::dir_up()
{
	this->direction = up;
}

void Befunge::dir_right()
{
	this->direction = right;
}

void Befunge::dir_left()
{
	this->direction = left;
}

void Befunge::dir_random()
{
	int d = rand() % 4;
	switch(d)
	{
		case 0:
			this->dir_left();
			break;
		case 1:
			this->dir_right();
			break;
		case 2:
			this->dir_up();
			break;
		case 3:
			this->dir_down();
			break;
	}

}

void Befunge::horizontal_if()
{
	int v = this->pop();
	v == 0 ? this->dir_right() : this->dir_left();
}

void Befunge::vertical_if()
{
	int v = this->pop();
	v == 0 ? this->dir_down() : this->dir_up();
}

void Befunge::string_mode()
{
	char in;

	this->move();
	in = this->get_current();
	
	while(in != '"')
	{
		this->push(in);
		this->move();
		in = this->get_current();
	}
}

void Befunge::duplicate()
{
	int v = this->pop();
	this->push(v);
	this->push(v);
}

void Befunge::swap()
{
	int a = this->pop();
	int b = this->pop();
	this->push(a);
	this->push(b);
}

void Befunge::out_int()
{
	int v = this->pop();
	std::cout << v;
}

void Befunge::out_char()
{
	char v = this->pop();
	std::cout << v;
}

void Befunge::bridge()
{
	this->move();
}

void Befunge::get()
{
	int y = this->pop();
	int x = this->pop();
	int v = this->get_at(x, y);
	this->push(v);
}

void Befunge::put()
{
	int y = this->pop();
	int x = this->pop();
	int v = this->pop();
	this->put_at(v, x, y);
}

void Befunge::in_int()
{
	int v;
	std::cin >> v;
	this->push(v);
}

void Befunge::in_char()
{
	char v;
	std::cin >> v;
	this->push(v);
}

void Befunge::end()
{
	exit(0);
}