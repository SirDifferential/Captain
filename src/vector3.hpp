/*
Everything by abax
I haven't really studied this much yet. All I know is that this class is
a three float vector class with all the tools we ever need.
Cool guy, that apaksi. You should really play this game, "Bottles"
*/

#ifndef _VECTOR3_H
#define _VECTOR3_H

#ifndef M_PI
#define M_PI 3.14159
#endif

#include <iostream>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <boost/numeric/ublas/matrix.hpp>

using namespace std;
using namespace boost::numeric;

// 3-dimensional floating point vector.

class Vector3
{
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(const float* v) : x(v[0]), y(v[1]), z(v[2]) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(float xyz) : x(xyz), y(xyz), z(xyz) {}
/*
	Vector3 min(const Vector3& b) const
	{
		return Vector3(
			(x < b.x) ? x : b.x,
			(y < b.y) ? y : b.y,
			(z < b.z) ? z : b.z);
	}

	Vector3 max(const Vector3& b) const
	{
		return Vector3(
			(x > b.x) ? x : b.x,
			(y > b.y) ? y : b.y,
			(z > b.z) ? z : b.z);
	}
*/
	float dot(const Vector3& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	friend float dot(const Vector3& a, const Vector3& b)
        {
 		return a.dot(b);
        }

	float length() const
	{
		return sqrtf(dot(*this));
	}

	float length2() const
	{
		return dot(*this);
	}

	Vector3 normalize() const
	{
		float m = 1.0f / length();
		return Vector3(x * m, y * m, z * m);
	}

	Vector3 cross(const Vector3& b) const
	{
		return Vector3(
			y * b.z - z * b.y,
			z * b.x - x * b.z,
			x * b.y - y * b.x);
	}

	Vector3& self_scale(const Vector3& s)
	{
		x *= s.x;
		y *= s.y;
		z *= s.z;
		return *this;
	}

	Vector3& self_pow(float p)
	{
		x = powf(x, p);
		y = powf(y, p);
		z = powf(z, p);
		return *this;
	}

	float luminance() const
	{
		return 0.299 * x + 0.587 * y + 0.114 * z;
	}

	Vector3 operator+(const Vector3& b) const
	{
		return Vector3(
			x + b.x,
			y + b.y,
			z + b.z);
	}

	Vector3 operator-(const Vector3& b) const
	{
		return Vector3(
			x - b.x,
			y - b.y,
			z - b.z);
	}

	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 operator*(float s) const
	{
		return Vector3(x * s, y * s, z * s);
	}

	friend Vector3 operator*(const float s, const Vector3& v)
	{
		return v * s;
	}

  float operator*(const Vector3 &v) const
  {
    return dot(v);
  }

	Vector3 operator/(float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	Vector3& operator=(const Vector3& b)
	{
		x = b.x;
		y = b.y;
		z = b.z;
		return *this;
	}

	Vector3& operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	Vector3& operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	const float& operator[](int n) const
	{
		assert(n >= 0 && n < 3);
		return (&x)[n];
	}

	float& operator[](int n)
	{
		assert(n >= 0 && n < 3);
		return (&x)[n];
	}

	static inline Vector3 zero()
	{
		return Vector3(0.0f, 0.0f, 0.0f);
	}

	operator float *()
	{
		return &x;
	}

	bool operator==(const Vector3 &a) const
	{
	  return x == a.x && y == a.y && z == a.z;
	}

	bool operator!=(const Vector3 &a) const
	{
	  return !operator==(a);
	}

  bool operator<(const Vector3 &a) const
  {
    return length() < a.length();
  }

public:
	float x, y, z;
};

inline ostream &operator <<(ostream &s, const Vector3 &v)
{
  s << '[' << v.x << ", " << v.y << ", " << v.z << ']' << std::endl;
  return s;
}

inline Vector3 scale(const Vector3& a, float s)
{
	return Vector3(a.x * s, a.y * s, a.z * s);
}

inline Vector3 scale(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline Vector3 normalize(const Vector3& v)
{
	float m = 1.0f / v.length();
	return Vector3(v.x * m, v.y * m, v.z * m);
}

inline Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

/*
inline Vector3 min(const Vector3& a, const Vector3& b)
{
	return Vector3((a.x < b.x) ? a.x : b.x,
	               (a.y < b.y) ? a.y : b.y,
	               (a.z < b.z) ? a.z : b.z);
}

inline Vector3 max(const Vector3& a, const Vector3& b)
{
	return Vector3((a.x >= b.x) ? a.x : b.x,
	               (a.y >= b.y) ? a.y : b.y,
	               (a.z >= b.z) ? a.z : b.z);
}
*/
// Intersect axis-aligned bounding box.

inline bool aaboxIntersect(const Vector3& p, const Vector3& d,
                           const Vector3& min, const Vector3& max,
                           float &a, float &b)
{
	float t1;
	float t2;
	float t3;
	float t4;
	bool hit1 = false;
	bool hit2 = false;

	assert(d.x != 0.0f || d.y != 0.0f || d.z != 0.0f);

	/* TODO: branch probabilities? */

	if (d.x == 0.0f)
	{
		if (p.x < min.x || p.x > max.x)
			return false;
	}
	else if (d.x > 0.0f)
	{
		t1 = (min.x - p.x) / d.x;
		t2 = (max.x - p.x) / d.x;
		hit1 = true;
	}
	else
	{
		t1 = (max.x - p.x) / d.x;
		t2 = (min.x - p.x) / d.x;
		hit1 = true;
	}
	assert(!hit1 || t1 <= t2);

	if (d.y == 0.0f)
	{
		if (p.y < min.y || p.y > max.y)
			return false;
	}
	else if (d.y > 0.0f)
	{
		t3 = (min.y - p.y) / d.y;
		t4 = (max.y - p.y) / d.y;
		hit2 = true;
	}
	else
	{
		t3 = (max.y - p.y) / d.y;
		t4 = (min.y - p.y) / d.y;
		hit2 = true;
	}
	assert(!hit2 || t3 <= t4);

	if (hit1 && hit2)
	{
		if (t2 < t3 || t4 < t1)
			return false;

		if (t1 < t3)
			t1 = t3;
		if (t2 > t4)
			t2 = t4;

		assert(t1 <= t2);
	}

	if (!hit1 && hit2)
	{
		t1 = t3;
		t2 = t4;
		hit1 = true;
	}

	if (d.z == 0.0f)
	{
		if (p.z < min.z || p.z > max.z)
			return false;
		hit2 = false;
	}
	else if (d.z > 0.0f)
	{
		t3 = (min.z - p.z) / d.z;
		t4 = (max.z - p.z) / d.z;
		hit2 = true;
	}
	else
	{
		t3 = (max.z - p.z) / d.z;
		t4 = (min.z - p.z) / d.z;
		hit2 = true;
	}

	if (!hit1 && !hit2)
		return false;

	assert(!hit2 || t3 <= t4);

	if (hit1 && hit2)
	{
		if (t2 < t3 || t4 < t1)
			return false;

		if (t1 < t3)
			t1 = t3;
		if (t2 > t4)
			t2 = t4;

		assert(t1 <= t2);
	}

	if (!hit1 && hit2)
	{
		a = t3;
		b = t4;
	}
	else
	{
		a = t1;
		b = t2;
	}

	return true;
}

// Intersect a triangle.

/*
static inline bool triangleIntersect(const Vector3& O, const Vector3& D,
				     const Vector3& V0, const Vector3& V1,
				     const Vector3& V2,
				     float &_t, float &_u, float &_v)
{
	const Vector3 E1 = V1 - V0;
	const Vector3 E2 = V2 - V0;
	const Vector3 P = D.cross(E2);

	float det = E1.dot(P);

	if (fabs(det) < 0.00001f)
		return false;

	const Vector3 T = O - V0;

	float u = T.dot(P);

	if (u < 0.0f || u > det)
		return false;

	const Vector3 Q = T.cross(E1);

	float v = D.dot(Q);
	if (v < 0.0f || u + v > det)
		return false;

	float t = E2.dot(Q);
	if (t < 0.0f)
		return false;

	float invDet = 1.0f / det;

	_t = t * invDet;
	_u = u * invDet;
	_v = v * invDet;

	return true;
}
*/

static inline bool triangleIntersect(const Vector3& O, const Vector3& D,
				     const Vector3& V0, const Vector3& V1,
				     const Vector3& V2,
				     float &_t, float &_u, float &_v)
{
  const Vector3 E1 = V1 - V0;
  const Vector3 E2 = V2 - V0;
  const Vector3 P = cross(D, E2);

  float det = E1.dot(P);
  float inv_det = 1.0f / det;

  // Epsilon test goes here.

  const Vector3 T = O - V0;

  float u = T.dot(P) * inv_det;

  if (u < 0.0f || u > 1.0f)
    return false;

  const Vector3 Q = cross(T, E1);

  float v = D.dot(Q) * inv_det;
  if (v < 0.0f || u + v > 1.0f)
    return false;

  float t = E2.dot(Q) * inv_det;
  if (t < 0.0f)
    return false;

  _t = t;
  _u = u;
  _v = v;

  return true;
}





// Gives an uniformly mapped point on a sphere from two floats between 0..1.

inline Vector3 pointOnSphere(float sx, float sy)
{
#if 0
	// Rejection sampling
	Vector3 v;
	do {
		v.x = randomFloat() * 2.0f - 1.0f;
		v.y = randomFloat() * 2.0f - 1.0f;
		v.z = randomFloat() * 2.0f - 1.0f;
	} while (v.length2() > 1.0f);
	return v;
#else
	sx = sx * 3.14159265f * 2.0f;
	sy = sy * 2.0f - 1.0f;
	float r = sqrtf(1.0f - sy * sy);
	return Vector3(cosf(sx) * r, sy, sinf(sx) * r);
#endif
}

// Gives an uniformly mapped hemisphere.
// TODO: check this!

inline Vector3 pointOnHemisphere(const Vector3& n, float theta, float phi)
{
	Vector3 ref = (fabs(n.x) < 0.5f) ?
		Vector3(1.0f, 0.0f, 0.0f) : Vector3(0.0f, 1.0f, 0.0f);

	Vector3 u = n.cross(ref).normalize();
	Vector3 v = u.cross(n);

	return
		u * sinf(theta) * cosf(phi) +
		v * sinf(theta) * sinf(phi) +
		n * cosf(theta);
}

// Gives a cosine weighted point on a hemisphere.

inline Vector3 pointOnHemisphereCosine(const Vector3& n, float x, float y)
{
	Vector3 ref = (fabs(n.x) < 0.5f) ?
		Vector3(1.0f, 0.0f, 0.0f) : Vector3(0.0f, 1.0f, 0.0f);

	Vector3 u = n.cross(ref).normalize();
	Vector3 v = u.cross(n);

	x *= 2.0f * 3.14159265f;
	y = sqrt(y);

	float xx = cosf(x) * y;
	float yy = sinf(x) * y;
	float zz = xx * xx + yy * yy;
	zz = (zz >= 1.0f) ? 0.0f : sqrtf(1.0f - zz);

	return
		u * xx + v * yy + n * zz;
}

// Reflects a ray.

inline Vector3 reflectRay(const Vector3& d, const Vector3& n)
{
	return n - n * (2.0f * d.dot(n));
}

// Refracts a ray.
// TODO: give only eta1 / eta2

inline Vector3 refractRay(const Vector3& d_, const Vector3& n,
                         float eta1, float eta2)
{
	Vector3 d = -d_;
	float dot1 = d.dot(n);
	float eta = eta1 / eta2;

	Vector3 v1 = (d - n * dot1) * -eta;
	Vector3 v2 = n * -sqrtf(1 - eta*eta * (1 - dot1*dot1));

	return v1 + v2;
}

class Vector2
{
public:
  float x, y;

  Vector2() :
    x(0.0f),
    y(0.0f)
  {
  }
  Vector2(float x, float y) :
    x(x),
    y(y)
  {
  }
  Vector2(float xy) :
    x(xy),
    y(xy)
  {
  }
  Vector2 operator-(const Vector2& b) const
  {
    return Vector2(x - b.x,
		   y - b.y);
  }
};

static inline Vector2 point_on_sphere_to_angles(const Vector3 &v)
{
  Vector2 t;
  t.y = acosf(v.y) / 3.14159265;
  t.x = ((atan2f(v.x, v.z) / 3.14159265) + 1.0) / 2.0;
  return t;
}

class Vector4
{
public:
  float r, g, b, a;

  Vector4() :
    r(0.0f),
    g(0.0f),
    b(0.0f),
    a(1.0f)
  {
  }
  Vector4(float r, float g, float b) :
    r(r),
    g(g),
    b(b),
    a(1.0f)
  {
  }
  Vector4(float r, float g, float b, float a) :
    r(r),
    g(g),
    b(b),
    a(a)
  {
  }
  Vector4(float rgb) :
    r(rgb),
    g(rgb),
    b(rgb),
    a(1.0f)
  {
  }
  Vector4(const Vector3 &x) :
    r(x.x),
    g(x.y),
    b(x.z),
    a(1.0f)
  {
  }
  float dot(const Vector4 &x) const
  {
    return r*x.r + g*x.g + b*x.b + a*x.a;
  }
  operator Vector3() const
  {
    return Vector3(r, g, b) / a;
  }

  Vector4 operator *(float s) const
  {
    return Vector4(r * s, g * s, b * s, a * s);
  }

  friend Vector4 operator*(const float s, const Vector4 &v)
  {
    return v * s;
  }

  Vector4 &operator +=(const Vector4 &x)
  {
    r += x.r;
    g += x.g;
    b += x.b;
    a += x.a;
    return *this;
  }

  Vector4 operator +(const Vector4 &x) const
  {
    return Vector4(r + x.r,
		   g + x.g,
		   b + x.b,
		   a + x.a);
  }
};

static inline void sodGetNormalOfPlane(float *normal, const float *pvector1, const float *pvector2)
{
  normal[0]=(pvector1[1]*pvector2[2])-(pvector1[2]*pvector2[1]);
  normal[1]=(pvector1[2]*pvector2[0])-(pvector1[0]*pvector2[2]);
  normal[2]=(pvector1[0]*pvector2[1])-(pvector1[1]*pvector2[0]);
}

class Matrix4
{
public:
  float m[16];

  Matrix4()
  {
  }

  Matrix4(const Matrix4 &a)
  {
    (*this) = a;
  }

  Matrix4 &operator =(const Matrix4 &a)
  {
    memcpy(m, a.m, sizeof(m));
    return *this;
  }

  float &operator [](int i)
  {
    assert(0 <= i && i < 16);
    return m[i];
  }

  Matrix4 &identity()
  {
    m[0 ] = 1; m[1 ] = 0; m[2 ] = 0; m[3 ] = 0;
    m[4 ] = 0; m[5 ] = 1; m[6 ] = 0; m[7 ] = 0;
    m[8 ] = 0; m[9 ] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
    return *this;
  }

  void scale(float x, float y, float z)
  {
    m[0 ] *= x; m[1 ] *= x; m[2 ] *= x; m[3 ] *= x;
    m[4 ] *= y; m[5 ] *= y; m[6 ] *= y; m[7 ] *= y;
    m[8 ] *= z; m[9 ] *= z; m[10] *= z; m[11] *= z;
  }

  void translate(float x, float y, float z)
  {
    m[3*4+0] += m[0*4+0] * x + m[1*4+0] * y + m[2*4+0] * z;
    m[3*4+1] += m[0*4+1] * x + m[1*4+1] * y + m[2*4+1] * z;
    m[3*4+2] += m[0*4+2] * x + m[1*4+2] * y + m[2*4+2] * z;
    m[3*4+3] += m[0*4+3] * x + m[1*4+3] * y + m[2*4+3] * z;
  }

  void rotate(float angle, float x, float y, float z)
  {
    float l = sqrtf(x*x + y*y + z*z);
    if (l != 0.0f) {
      x /= l;
      y /= l;
      z /= l;
    }

    float c, s, ic;
    c = cosf(angle * M_PI / 180.0);
    s = sinf(angle * M_PI / 180.0);
    ic = 1.0f - c;

    float rot[16];
    rot[0 * 4 + 0] = x * x * ic + c;
    rot[1 * 4 + 0] = x * y * ic - z * s;
    rot[2 * 4 + 0] = x * z * ic + y * s;
    rot[3 * 4 + 0] = 0.0f;
    rot[0 * 4 + 1] = y * x * ic + z * s;
    rot[1 * 4 + 1] = y * y * ic + c;
    rot[2 * 4 + 1] = y * z * ic - x * s;
    rot[3 * 4 + 1] = 0.0f;
    rot[0 * 4 + 2] = x * z * ic - y * s;
    rot[1 * 4 + 2] = y * z * ic + x * s;
    rot[2 * 4 + 2] = z * z * ic + c;
    rot[3 * 4 + 2] = 0.0f;
    rot[0 * 4 + 3] = 0.0f;
    rot[1 * 4 + 3] = 0.0f;
    rot[2 * 4 + 3] = 0.0f;
    rot[3 * 4 + 3] = 1.0f;

    float temp[16];
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
	temp[j * 4 + i] = 0.0f;
	for (int k = 0; k < 4; ++k) {
	  temp[j * 4 + i] += m[k * 4 + i] * rot[j * 4 + k];
	}
      }
    }
    memcpy(m, temp, sizeof(temp));
  }

  void multiply(const float *m2)
  {
    ublas::matrix<float> u1(4, 4), u2(4, 4);
    for (unsigned int i=0; i<16; i++) {
      u1(i/4, i%4) = m[i];
      u2(i/4, i%4) = m2[i];
    }
    ublas::matrix<float> p = ublas::prod(u1, u2);
    for (unsigned int i=0; i<16; i++) {
      m[i] = p(i/4, i%4);
    }
  }

  void multiply(const Matrix4 &m)
  {
    multiply(m.m);
  }

  Matrix4 operator *(const Matrix4 &b) const
  {
    Matrix4 a(*this);
    a.multiply(b);
    return a;
  }

  operator float *()
  {
    return m;
  }

  void look_at(Vector3 eye, Vector3 center, Vector3 uup)
  {
    Matrix4 &matrix = *this;
    Vector3 forward, side, up;
    /*GL*/float matrix2[16];

    forward[0] = center[0] - eye[0];
    forward[1] = center[1] - eye[1];
    forward[2] = center[2] - eye[2];
    forward = forward.normalize();

    //Side = forward x up
    sodGetNormalOfPlane(side, forward, uup);
    side = side.normalize();

    //Recompute up as: up = side x forward
    sodGetNormalOfPlane(up, side, forward);

    matrix2[0] = side[0];
    matrix2[4] = side[1];
    matrix2[8] = side[2];
    matrix2[12] = 0.0;

    matrix2[1] = up[0];
    matrix2[5] = up[1];
    matrix2[9] = up[2];
    matrix2[13] = 0.0;

    matrix2[2] = -forward[0];
    matrix2[6] = -forward[1];
    matrix2[10] = -forward[2];
    matrix2[14] = 0.0;

    matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
    matrix2[15] = 1.0;

    matrix.multiply(matrix2);
    matrix.translate(-eye[0], -eye[1], -eye[2]);
  }

  void perspective(float fovy, float aspect, float nearNonMS, float farNonMS)
  {
    Matrix4 &matrix = *this;
    const float f = 1.0f / tan(fovy / 180.0f * M_PI / 2.0f);
    matrix[0 ] = f / aspect;
    matrix[1 ] = 0;
    matrix[2 ] = 0;
    matrix[3 ] = 0;

    matrix[4 ] = 0;
    matrix[5 ] = f;
    matrix[6 ] = 0;
    matrix[7 ] = 0;

    matrix[8 ] = 0;
    matrix[9 ] = 0;
    matrix[10] = (farNonMS + nearNonMS) / (nearNonMS - farNonMS);
    matrix[11] = -1;

    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = (2 * farNonMS * nearNonMS) / (nearNonMS - farNonMS);
    matrix[15] = 0;
  }


};


static inline Vector4 multiply(const Matrix4 &m, const Vector4 &v)
{
  const float a = v.dot(Vector4(m.m[0], m.m[4], m.m[8], m.m[12]));
  const float b = v.dot(Vector4(m.m[1], m.m[5], m.m[9], m.m[13]));
  const float c = v.dot(Vector4(m.m[2], m.m[6], m.m[10], m.m[14]));
  const float d = v.dot(Vector4(m.m[3], m.m[7], m.m[11], m.m[15]));
  return Vector4(a, b, c, d);
}


#endif
