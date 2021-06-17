/** \file object.h
 ** \brief Defines Object and declares its member functions.
 **/
#ifndef OBJECT_H
	#define OBJECT_H

	typedef union ObjectBody {
		char asChr;
		unsigned char asUChr;
		short asShort;
		unsigned short asUShort;
		int asInt;
		unsigned int asUInt;
		long asLong;
		unsigned long asULong;
		float asFloat;
		double asDbl;
		const void* asPtr;
	} Object;

	#ifdef DECLARE_OBJ_FROM
		#undef DECLARE_OBJ_FROM
	#endif
	#define DECLARE_OBJ_FROM(type,name)	Object from##name##_obj(const type)

	DECLARE_OBJ_FROM(char,Char);
	DECLARE_OBJ_FROM(unsigned char,UChar);
	DECLARE_OBJ_FROM(short,Short);
	DECLARE_OBJ_FROM(unsigned short,UShort);
	DECLARE_OBJ_FROM(int,Int);
	DECLARE_OBJ_FROM(unsigned int,UInt);
	DECLARE_OBJ_FROM(long,Long);
	DECLARE_OBJ_FROM(unsigned long,ULong);
	DECLARE_OBJ_FROM(float,Float);
	DECLARE_OBJ_FROM(double,Dbl);
	DECLARE_OBJ_FROM(void*,Ptr);

	#undef DECLARE_OBJ_FROM
#endif
