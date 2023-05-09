#include <iostream>
#include <string>
#include <sstream>
#include "Set.h"

int main()
{
	Set<int> universum, a, b, c, d, e;
	for(int i = 1;i<=7; i++) universum.insert(i);
	for(int i = 4;i<=7; i++) a.insert(i);

	b.insert(2);
	b.insert(4);
	b.insert(5);
	b.insert(6);

	c.insert(1);
	c.insert(3);
	c.insert(5);
	c.insert(6);

	d.insert(2);
	d.insert(3);
	d.insert(5);
	d.insert(7);

	e.insert(1);
	e.insert(2);
	e.insert(6);
	e.insert(7);

	(c ^ (b & a)).print();
	std::cout << "\n\n";

	((c & d) | (universum - e)).print();
	std::cout << "\n";
	(e & (universum - d)).print();
	std::cout << "\n\n";

	(d&c).print();
	std::cout << "\n";
	(b&c).print();
	std::cout << "\n";

	system("Pause");
}
