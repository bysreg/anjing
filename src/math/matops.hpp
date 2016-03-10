#pragma once

#include "math/tmat4.hpp"
#include "math/tvec3.hpp"
#include "math/vecops.hpp"

namespace anjing
{
	namespace math
	{

		template<typename T>
		inline TMat4<T> LookAt(TVec3<T> const & eye, TVec3<T> const & center, TVec3<T> const & up)
		{
			TVec3<T> w = Normalize(center - eye);
			TVec3<T> u = Normalize(Cross(w, up));
			TVec3<T> v = Cross(u, w); // don't need to normalize this, bcos cross product of base unit vector is another base unit vector

			TMat4<T> ret;
			ret.SetAsIdentity();

			ret[0][0] = u.x;
			ret[1][0] = u.y;
			ret[2][0] = u.z;
			ret[3][0] = -Dot(eye, u);
			ret[0][1] = v.x;
			ret[1][1] = v.y;
			ret[2][1] = v.z;
			ret[3][1] = -Dot(eye, v);
			ret[0][2] = -w.x;
			ret[1][2] = -w.y;
			ret[2][2] = -w.z;
			ret[3][2] = Dot(eye, w);

			return ret;
		}

	}
}
