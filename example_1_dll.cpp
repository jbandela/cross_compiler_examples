#include "example_1_interface.h"
#include <vector>
using namespace cross_compiler_interface;


// A lot of classes need attribute implementation
// so factor out the code into 1 class

struct AttributeImplementation{
	std::vector<use_unknown<IAttribute>> attributes_;

	void addAttribute(use_unknown<IAttribute> a){
		attributes_.push_back(a);
	}

	use_unknown<IAttribute> getAttribute(std::int32_t i){
		return attributes_.at(i);
	}

	template<class Imp>
	void set_implementation(Imp* imp){

		// In addition to using a lambda for a cross_function, you can also use a member function
		imp->addAttribute.template set_mem_fn<AttributeImplementation,&AttributeImplementation::addAttribute>(this);
		imp->getAttribute. template set_mem_fn<AttributeImplementation,&AttributeImplementation::getAttribute>(this);

	}
};


struct Point2D:cross_compiler_interface::implement_unknown_interfaces<Point2D,IPoint2D>{


	std::int32_t x_;
	std::int32_t y_;

	// This will implement the getAttribute and addAttribute
	AttributeImplementation attribute_imp;


	Point2D(std::int32_t x,std::int32_t y):x_(x),y_(y){

		auto imp = get_implementation<IPoint2D>();

		// Set the attribute implementation
		attribute_imp.set_implementation(imp);

		// Define the implementation for the rest of the cross_functions
		imp->getX = [this]{return x_;};
		imp->getY = [this]{return y_;};
	}


};



struct Point3D:implement_unknown_interfaces<Point3D,IPoint3D>{


	std::int32_t x_;
	std::int32_t y_;
	std::int32_t z_;


	AttributeImplementation attribute_imp;

	Point3D(std::int32_t x,std::int32_t y,std::int32_t z):x_(x),y_(y),z_(z){
		auto imp = get_implementation<IPoint3D>();

		attribute_imp.set_implementation(imp);

		imp->getX = [this]{return x_;};
		imp->getY = [this]{return y_;};
		imp->getZ = [this]{return z_;};
	}


};

struct Line:public implement_unknown_interfaces<Line,ILine>{

	std::vector<use_unknown<IPoint>> points_;

	AttributeImplementation attribute_imp;

	Line(){
		auto imp = get_implementation<ILine>();
		
		attribute_imp.set_implementation(imp);

		imp->addPoint = [this](use_unknown<IPoint> p){
			points_.push_back(p);
		};

		imp->getPoint = [this](std::int32_t i){
			return points_.at(i);
		};

		
	}


};


struct IntegerAttribute:public implement_unknown_interfaces<IntegerAttribute,IIntegerAttribute>{

	std::int32_t val_;

	IntegerAttribute(std::int32_t v):val_(v){
		auto imp = get_implementation<IIntegerAttribute>();
		imp->getValue = [this](){return val_;};

		imp->setValue = [this](std::int32_t v){
			val_ = v;
		};

	}

};


struct StringAttribute:public implement_unknown_interfaces<StringAttribute,IStringAttribute>{
	std::string val_;


	StringAttribute(std::string v):val_(v){
		auto imp = get_implementation<IStringAttribute>();
		imp->getValue = [this](){return val_;};

		imp->setValue = [this](std::string v){
			val_ = v;
		};

	}

};
struct Creator{
	
	implement_interface<ICreator> imp;


	Creator(){

		imp.createIntAttribute = [](std::int32_t i){
			return IntegerAttribute::create(i).QueryInterface<IAttribute>();
		};
		imp.createStringAttribute = [](std::string s){
			return StringAttribute::create(s).QueryInterface<IAttribute>();
		};
		imp.createLine = [](){
			return Line::create().QueryInterface<ILine>();
		};
		imp.createPoint2D = [](std::int32_t x, std::int32_t y){
			return Point2D::create(x,y).QueryInterface<IPoint>();
		};
		imp.createPoint3D = [](std::int32_t x, std::int32_t y,std::int32_t z){
			return Point3D::create(x,y,z).QueryInterface<IPoint>();
		};

	};


};


extern "C"{

 cross_compiler_interface::portable_base* CROSS_CALL_CALLING_CONVENTION CreateCreator(){
	static Creator c;
	return c.imp.get_portable_base();
}
}