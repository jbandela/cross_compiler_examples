#include "example_1_interface.h"
#include <vector>
using namespace cross_compiler_interface;


// A lot of classes need attribute implementation
// so factor out the code into 1 class

template<class Imp>
struct AttributeImplementation{
	std::vector<use_unknown<IAttribute>> attributes_;

	void addAttribute(use_unknown<IAttribute> a){
		attributes_.push_back(a);
	}

	use_unknown<IAttribute> getAttribute(std::int32_t i){
		return attributes_.at(i);
	}

	AttributeImplementation(Imp& imp){

		// In addition to using a lambda for a cross_function, you can also use a member function
		imp.addAttribute.template set_mem_fn<AttributeImplementation,&AttributeImplementation::addAttribute>(this);
		imp.getAttribute. template set_mem_fn<AttributeImplementation,&AttributeImplementation::getAttribute>(this);

	}
};


struct Point2D{
	implement_interface<IPoint2D> imp;


	std::int32_t x_;
	std::int32_t y_;

	// This will implement the getAttribute and addAttribute
	AttributeImplementation<decltype(imp)> attribute_imp;

	// This will implement IUknown
	implement_iunknown<Point2D,decltype(imp)> unknow_imp;

	Point2D(std::int32_t x,std::int32_t y):x_(x),y_(y),attribute_imp(imp),unknow_imp(this,imp){
		// Define the remaining functions in IPoint2D
		imp.getX = [this]{return x_;};
		imp.getY = [this]{return y_;};
	}


};



struct Point3D{
	implement_interface<IPoint3D> imp;


	std::int32_t x_;
	std::int32_t y_;
	std::int32_t z_;


	AttributeImplementation<decltype(imp)> attribute_imp;
	implement_iunknown<Point3D,decltype(imp)>unknown_imp;
	Point3D(std::int32_t x,std::int32_t y,std::int32_t z):x_(x),y_(y),z_(z),attribute_imp(imp),unknown_imp(this,imp){
		imp.getX = [this]{return x_;};
		imp.getY = [this]{return y_;};
		imp.getZ = [this]{return z_;};
	}


};

struct Line{
	implement_interface<ILine> imp;

	std::vector<use_unknown<IPoint>> points_;
	AttributeImplementation<decltype(imp)> attribute_imp;
	implement_iunknown<Line,decltype(imp)> unknown_imp;

	Line():attribute_imp(imp),unknown_imp(this,imp){
		imp.addPoint = [this](use_unknown<IPoint> p){
			points_.push_back(p);
		};

		imp.getPoint = [this](std::int32_t i){
			return points_.at(i);
		};

		
	}


};


struct IntegerAttribute{
	implement_interface<IIntegerAttribute> imp;
	std::int32_t val_;

	implement_iunknown<IntegerAttribute,decltype(imp)> unknown_imp;

	IntegerAttribute(std::int32_t v):val_(v),unknown_imp(this,imp){
		imp.getValue = [this](){return val_;};

		imp.setValue = [this](std::int32_t v){
			val_ = v;
		};

	}

};


struct StringAttribute{
	implement_interface<IStringAttribute> imp;
	std::string val_;

	implement_iunknown<StringAttribute,decltype(imp)> unknown_imp;

	StringAttribute(std::string v):val_(v),unknown_imp(this,imp){
		imp.getValue = [this](){return val_;};

		imp.setValue = [this](std::string v){
			val_ = v;
		};

	}

};
struct Creator{
	
	implement_interface<ICreator> imp;


	Creator(){

		imp.createIntAttribute = [](std::int32_t i)->use_unknown<IAttribute> {
			auto r = new IntegerAttribute(i);
			use_unknown<IIntegerAttribute> ret(r->imp);
			r->imp.Release();
			return ret.QueryInterface<IAttribute>();
		};
		imp.createStringAttribute = [](std::string i)->use_unknown<IAttribute> {
			auto r = new StringAttribute(i);
			use_unknown<IStringAttribute> ret(r->imp);
			r->imp.Release();
			return ret.QueryInterface<IAttribute>();
		};
		imp.createLine = []()->use_unknown<ILine>{
			auto r = new Line;
			use_unknown<ILine> ret(r->imp);
			r->imp.Release();
			return ret;
		};
		imp.createPoint2D = [](std::int32_t x, std::int32_t y)->use_unknown<IPoint> {
			auto r = new Point2D(x,y);
			use_unknown<IPoint2D> ret(r->imp);
			r->imp.Release();
			return ret.QueryInterface<IPoint>();
		};
		imp.createPoint3D = [](std::int32_t x, std::int32_t y,std::int32_t z)->use_unknown<IPoint> {
			auto r = new Point3D(x,y,z);
			use_unknown<IPoint3D> ret(r->imp);
			r->imp.Release();
			return ret.QueryInterface<IPoint>();
		};

	};


};


extern "C"{

 cross_compiler_interface::portable_base* CROSS_CALL_CALLING_CONVENTION CreateCreator(){
	static Creator c;
	return c.imp.get_portable_base();
}
}