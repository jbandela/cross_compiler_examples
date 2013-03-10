#include "../cross_compiler_call/cross_compiler_interface/interface_unknown.hpp"


using cross_compiler_interface::cross_function;
using cross_compiler_interface::define_interface_unknown;
using cross_compiler_interface::use_unknown;

// {C90C5D9D-80B7-43C3-AA21-7DCA210D2AD7}
typedef cross_compiler_interface::uuid< 
0xc90c5d9d, 0x80b7, 0x43c3, 0xaa, 0x21, 0x7d, 0xca, 0x21, 0xd, 0x2a, 0xd7> Attribute_uuid_t;

template<class T>
struct IAttribute:public define_interface_unknown<T,Attribute_uuid_t>
{


	IAttribute(){}
};




// {FB83D912-B130-4D01-9520-36CFB3CB75DB}
typedef cross_compiler_interface::uuid< 
0xfb83d912, 0xb130, 0x4d01, 0x95, 0x20, 0x36, 0xcf, 0xb3, 0xcb, 0x75, 0xdb> Point_uuid_t;

template<class T>
struct IPoint:public define_interface_unknown<T,Point_uuid_t>
{

	cross_function<IPoint,0,std::int32_t()> getX;
	cross_function<IPoint,1,std::int32_t()> getY;
	cross_function<IPoint,2,use_unknown<IAttribute>(std::int32_t)> getAttribute;
	cross_function<IPoint,3,void(use_unknown<IAttribute>)> addAttribute;

	IPoint():getX(this),getY(this),getAttribute(this), addAttribute(this){}
};


// {CF875930-6E04-46FB-AB29-13651DE982CB}
typedef cross_compiler_interface::uuid<
0xcf875930, 0x6e04, 0x46fb, 0xab, 0x29, 0x13, 0x65, 0x1d, 0xe9, 0x82, 0xcb> Point2D_uuid_t;
template<class T>
struct IPoint2D:public define_interface_unknown<T,Point2D_uuid_t,IPoint>
{

	IPoint2D(){}
};

// {13CAE1F0-5DE6-4100-8FC1-CD9B98E448BD}
typedef cross_compiler_interface::uuid<
	0x13cae1f0, 0x5de6, 0x4100, 0x8f, 0xc1, 0xcd, 0x9b, 0x98, 0xe4, 0x48, 0xbd> Point3D_uuid_t;
template<class T>
struct IPoint3D:public define_interface_unknown<T,Point3D_uuid_t,IPoint>{
	cross_function<IPoint3D,0,std::int32_t()> getZ;

	IPoint3D():getZ(this){}
};


// {0946F613-DA11-473F-855F-B0DCA25E5246}
typedef cross_compiler_interface::uuid<
0x946f613, 0xda11, 0x473f, 0x85, 0x5f, 0xb0, 0xdc, 0xa2, 0x5e, 0x52, 0x46> Line_uuid_t;
template<class T>
struct ILine:public define_interface_unknown<T,Line_uuid_t>
{
	
	cross_function<ILine,0,use_unknown<IPoint>(std::int32_t)> getPoint;
	cross_function<ILine,1,void(use_unknown<IPoint>)> addPoint;
	cross_function<ILine,2,use_unknown<IAttribute>(std::int32_t)> getAttribute;
	cross_function<ILine,3,void(use_unknown<IAttribute>)> addAttribute;

	ILine():getPoint(this),addPoint(this),getAttribute(this),addAttribute(this){}


};

// {723691EF-6039-47EF-B6C6-B2F6B49FFE35}
typedef cross_compiler_interface::uuid<
0x723691ef, 0x6039, 0x47ef, 0xb6, 0xc6, 0xb2, 0xf6, 0xb4, 0x9f, 0xfe, 0x35> StringAttribute_uuid_t;
template<class T>
struct IStringAttribute:public define_interface_unknown<T,StringAttribute_uuid_t,IAttribute>
{
	cross_function<IStringAttribute,0,std::string()> getValue;
	cross_function<IStringAttribute,1,void(std::string)> setValue;

	IStringAttribute():getValue(this),setValue(this){}
};


// {8A7E2EA6-BC73-43AD-8922-012F48125FD3}
typedef cross_compiler_interface::uuid<
0x8a7e2ea6, 0xbc73, 0x43ad, 0x89, 0x22, 0x1, 0x2f, 0x48, 0x12, 0x5f, 0xd3> IntegerAttribute_uuid_t;
template<class T>
struct IIntegerAttribute:public define_interface_unknown<T,IntegerAttribute_uuid_t,IAttribute>
{
	cross_function<IIntegerAttribute,0,std::int32_t()> getValue;
	cross_function<IIntegerAttribute,1,void(std::int32_t)> setValue;

	IIntegerAttribute():getValue(this),setValue(this){}
};


// A class to create stuff

template<class T>
struct ICreator:public cross_compiler_interface::define_interface<T>
{
	
	cross_function<ICreator,0, use_unknown<IAttribute>(std::int32_t)> createIntAttribute;
	cross_function<ICreator,1,use_unknown<IAttribute>(std::string)> createStringAttribute;
	cross_function<ICreator,2, use_unknown<IPoint>(std::int32_t,std::int32_t)> createPoint2D;
	cross_function<ICreator,3, use_unknown<IPoint>(std::int32_t,std::int32_t,std::int32_t)> createPoint3D;
	cross_function<ICreator,4, use_unknown<ILine>()> createLine;

	ICreator():createIntAttribute(this),createStringAttribute(this),createPoint2D(this),createPoint3D(this),createLine(this){}
};