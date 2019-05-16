//
//  quat.cpp
//  
//
//  Created by Matthew Baptist on 4/15/19.
//
//

#include "quat.hpp"
#include <math.h>

vec3::vec3(double x, double y, double z) {
  (*this)[0] = x;
  (*this)[1] = y;
  (*this)[2] = z;
}

vec3::vec3() {
  (*this)[0] = 0;
  (*this)[1] = 0;
  (*this)[2] = 0;
}

double vec3::dot(const vec3 &u) const {
  return (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]);
}

vec3 vec3::cross(const vec3 &u) const {
  vec3 temp;
  temp[0] = (v[1] * u[2] - v[2] * u[1]);
  temp[1] = -(v[0] * u[2] - v[2] * u[0]);
  temp[2] = (v[0] * u[1] - v[1] * u[0]);
  return temp;
}

double vec3::mag() const {
  return sqrt(dot(*this));
}

vec3 vec3::unit() const {
  double m = mag();
  vec3 temp(v[0] / m, v[1] / m, v[2] / m);
  return temp;
}

void vec3::normalize() {
  double m = mag();
  v[0] = v[0] / m;
  v[1] = v[1] / m;
  v[2] = v[2] / m;
}

vec3 vec3::operator+(const vec3 &u) const {
  vec3 temp;
  temp[0] = v[0] + u[0];
  temp[1] = v[1] + u[1];
  temp[2] = v[2] + u[2];
  return temp;
}

vec3 vec3::operator-(const vec3 &u) const {
  vec3 temp;
  temp[0] = v[0] - u[0];
  temp[1] = v[1] - u[1];
  temp[2] = v[2] - u[2];
  return temp;
}

vec3 vec3::operator*(const double s) const {
  vec3 temp;
  temp[0] = s * v[0];
  temp[1] = s * v[1];
  temp[2] = s * v[2];
  return temp;
}

/* Quaternion Code Here */
quat::quat() {
  s = 0;
}

quat::quat(double s, vec3 v) {
  this->s = s;
  this->v = v;
}

quat::quat(vec3 v) {
  this->s = 0;
  this->v = v;
}

quat quat::unit() const {
  double m = mag();
  quat u = (*this);
  u = u * (1.0 / m);
  return u;
}

void quat::normalize() {
  double m = mag();
  s = s / m;
  v[0] = v[0] / m;
  v[1] = v[1] / m;
  v[2] = v[2] / m;
}

double quat::mag() const {
  return sqrt(s*s + v.dot(v));
}

double quat::mag_sq() const {
  return s*s + v.dot(v);
}

quat quat::operator*(const quat &u) const {
  const quat& v = *this;
  quat r;
  r.s = v.s * u.s - v.v.dot(u.v);
  r.v = u.v * v.s + v.v * u.s + v.v.cross(u.v);
  return r;
}

quat quat::operator*(const double s) const {
  quat u;
  u.s = this->s * s;
  u.v[0] = this->v[0] * s;
  u.v[1] = this->v[1] * s;
  u.v[2] = this->v[2] * s;
  return u;
}

quat quat::inv() const {
  const quat& v = *this;
  double m = v.mag_sq();
  quat u = v * (1 / m);
  u.v = u.v * (-1);
  return u;
}

vec3 quat::rot(const vec3 &u) const {
  const quat& v = *this;
  quat w(u);
  quat vinv = this->inv();
  quat r = vinv * w * v;
  return r.v;
}

void quat::toEulerAngles(double& Z,
                         double& Y,
                         double& X) {
  /* Potential Stability Issues */
  Z = atan2(2(s * v[0] + v[1] * v[2]), 1 - 2(v[0]*v[0] + v[1]*v[1]));
  Y = asin(2(s * v[1] - v[2] * v[0]));
  X = atan2(2(s * v[2] + v[0] * v[1]), 1 - 2(v[1]*v[1] + v[2]*v[2]));
}

void quat::fromEulerAngles(const double Z,
                           const double Y,
                           const double X) {
  double cz = cos(Z / 2.0);
  double sz = sin(Z / 2.0);
  double cy = cos(Y / 2.0);
  double sy = sin(Y / 2.0);
  double cx = cos(X / 2.0);
  double sx = sin(X / 2.0);
  
  s = (cz * cy * cx) + (sz * sy * sx);
  v[0] = (cz * cy * sx) - (sz * sy * cx);
  v[1] = (sz * cy * sx) + (cz * sy * cx);
  v[2] = (sz * cy * cx) - (cz * sy * sx);
}

void quat::toRotMatrix(double rot[3][3]) {
  double ss = s*s;
  double xx = v[0] * v[0];
  double yy = v[1] * v[1];
  double zz = v[2] * v[2];
  double sx = s * v[0];
  double sy = s * v[1];
  double sz = s * v[2];
  double xy = v[0] * v[1];
  double xz = v[0] * v[2];
  double yz = v[1] * v[2];
  
  rot[0][0] = ss + xx + yy + zz;
  rot[0][1] = 2 * (xy - sz);
  rot[0][2] = 2 * (sy + xz);
  rot[1][0] = 2 * (xy + sz);
  rot[1][1] = ss - xx + yy - zz;
  rot[1][2] = 2 * (yz - sx);
  rot[2][0] = 2 * (xz - sy);
  rot[2][1] = 2 * (sx + yz);
  rot[2][2] = ss - xx - yy + zz;
}

void quat::fromRotMatrix(double rot[3][3]) {
  double tr = rot[0][0] + rot[1][1] + rot[2][2] + 1;
  /* Potential Stability issues here */
  s = .5 * sqrt(tr);
  double S = .25 * (1 / s);
  v[0] = (rot[2][1] - rot[1][2]) * S;
  v[1] = (rot[0][2] - rot[2][0]) * S;
  v[2] = (rot[1][0] - rot[0][1]) * S;
}
