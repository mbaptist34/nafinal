
#ifndef quat_hpp
#define quat_hpp

#include <stdio.h>
#include <iostream>

class vec3 {
  
  double v[3];
  
public:
  
  vec3(double x, double y, double z);
  vec3();
  
  inline double &operator[](std::size_t idx) { return v[idx]; }
  
  inline double operator[](std::size_t idx) const { return v[idx]; }
  
  double dot(const vec3 &u) const;
  
  vec3 cross(const vec3 &u) const;
  
  double mag() const;
  
  vec3 unit() const;
  
  void normalize();
  
  vec3 operator+(const vec3 &u) const;
  
  vec3 operator-(const vec3 &b) const;
  
  vec3 operator*(const double u) const;
};

class quat {
  
public:

  double s;
  vec3 v;
  
  quat();
  quat(double s, vec3 v);
  quat(vec3 v);
  
  quat unit() const;
  
  void normalize();
  
  double mag_sq() const;
  
  double mag() const;
  
  quat operator*(const quat &u) const;
  
  quat operator*(const double s) const;
  
  quat inv() const;
  
  vec3 rot(const vec3 &u) const;
  
  void toEulerAngles(double& Z,
                     double& Y,
                     double& X);
  void fromEulerAngles(const double Z,
                       const double Y,
                       const double X);
  
  void toRotMatrix(double rot[3][3]);
  void fromRotMatrix(double rot[3][3]);
};

#endif /* quat_hpp */
