#pragma once

#include "Logical.h"
#include "Operations.h"
#include "../String.h"

namespace Math {


	template<typename T = float>
	class Vec2 {
	public:
		typedef T Type;

		MATH_FUNC_QUALIFIER Vec2( void );
		MATH_FUNC_QUALIFIER Vec2( const T & v );
		MATH_FUNC_QUALIFIER Vec2( const T & x, const T & y );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2( const U( &v )[2] ); 


		template<typename U = char>
		MATH_FUNC_QUALIFIER operator BasicString<U>() const;

		MATH_FUNC_QUALIFIER T & operator[]( unsigned int index );
		MATH_FUNC_QUALIFIER const T & operator[]( unsigned int index ) const;


		/************************************************************************/
		/* Arithmetic                                                           */
		/************************************************************************/
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator*=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator*=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator/=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator/=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator+=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator+=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator-=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator-=( const T & v );

		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator>>=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator>>=( const T & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator<<=( const Vec2<U> & v );
		MATH_FUNC_QUALIFIER Vec2<T> & operator<<=( const T & v );

		MATH_FUNC_QUALIFIER Vec2<T> & operator++();
		MATH_FUNC_QUALIFIER Vec2<T> & operator--();
		MATH_FUNC_QUALIFIER Vec2<T> operator-() const;

		/************************************************************************/
		/* Assignments                                                          */
		/************************************************************************/
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const T & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const Vec2<U> & v );
		template<typename U>
		MATH_FUNC_QUALIFIER Vec2<T> & operator=( const U( &v )[2] );

		MATH_FUNC_QUALIFIER void inverse();

		template<typename U = char>
		MATH_FUNC_QUALIFIER BasicString<U> toString() const;


		union {
			struct { T r, g; };
			struct { T x, y; };
			struct { T values[2]; };
		};

		static const Vec2<T> null;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare & func, const Vec2<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorAND( Compare & func, const T & v ) const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare & func, const Vec2<T> & v ) const;
		template<typename Compare>
		MATH_FUNC_QUALIFIER bool _logicalOperatorOR( Compare & func, const T & v )const;

		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec2<T> & _MathOperator( Compare & func, const Vec2<T> & v );
		template<typename Compare>
		MATH_FUNC_QUALIFIER Vec2<T> & _MathOperator( Compare & func, const T & v );
	};


	/************************************************************************/
	/* Logical                                                              */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator==( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator!=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<=( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator>( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER bool operator<( const Vec2<T> & v1, const T & v2 );


	/************************************************************************/
	/* Arithmetic                                                           */
	/************************************************************************/
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const T & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator+( const Vec2<T> & v1, const T & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator-( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator*( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator/( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator >> ( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator<<( const T & v1, const Vec2<T> & v2 );

	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const Vec2<T> & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const Vec2<T> & v1, const T & v2 );
	template<typename T>
	MATH_FUNC_QUALIFIER Vec2<T> operator%( const T & v1, const Vec2<T> & v2 );


	template<typename T>
	MATH_FUNC_QUALIFIER std::ostream & operator<<( std::ostream & stream, const Vec2<T> & v );
	template<typename T, typename U = char>
	MATH_FUNC_QUALIFIER BasicString<U> & operator<<( BasicString<U> & string, const Vec2<T> & v );


	typedef Vec2<MATH_FLOAT_DEFAULT> vec2;
	typedef Vec2<float> vec2f;
	typedef Vec2<double> vec2d;
	typedef Vec2<char> vec2c;
	typedef Vec2<unsigned char> vec2uc;
	typedef Vec2<int> vec2i;
	typedef Vec2<unsigned int> vec2ui;
	typedef Vec2<long> vec2l;
	typedef Vec2<unsigned long> vec2ul;


}




#include "Vec2.hpp"
