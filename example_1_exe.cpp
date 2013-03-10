#include "example_1_interface.h"
#include <iostream>

using namespace std;

int main(){
	auto creator = cross_compiler_interface::create<ICreator>("cross_compiler_example1_dll","CreateCreator");

	auto line = creator.createLine();
	line.addPoint(creator.createPoint2D(5,10));
	line.addPoint(creator.createPoint3D(5,10,15));
	
	auto point1 = line.getPoint(0);
	cout << point1.QueryInterface<IPoint2D>().getX() << endl;
	point1.addAttribute(creator.createStringAttribute("Hello"));
}