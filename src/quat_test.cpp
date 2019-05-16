//
//  quat_test.cpp
//  
//
//  Created by Matthew Baptist on 5/9/19.
//
//

#include "gtest/gtest.h"
#include "quat.hpp"

TEST(vec3test, constructorNoArgs) {
  vec3 a;
  
  EXPECT_DOUBLE_EQ(a[0], 0);
  EXPECT_DOUBLE_EQ(a[1], 0);
  EXPECT_DOUBLE_EQ(a[2], 0);
  
}

TEST(vec3test, constructorWArgs) {
  vec3 a(1.000005, 4.3, 9.5);
  
  EXPECT_DOUBLE_EQ(a[0], 1.000005);
  EXPECT_DOUBLE_EQ(a[1], 4.3);
  EXPECT_DOUBLE_EQ(a[2], 9.5);
  
}

TEST(vec3test, assignment) {
  vec3 a;
  
  a[0] = 5.0;
  a[1] = 10.0;
  a[2] = 15.0;
  
  EXPECT_DOUBLE_EQ(a[0], 5.0);
  EXPECT_DOUBLE_EQ(a[1], 10.0);
  EXPECT_DOUBLE_EQ(a[2], 15.0);
}

TEST(vec3test, dot) {
  vec3 a(0, 1.0, 2.0);
  vec3 b(1.0, 1.0, 1.0);
  
  double dot = a.dot(b);
  
  EXPECT_DOUBLE_EQ(dot, 3.0);
  
  vec3 c(1.0, 0, 2.0);
  vec3 d(1.0, 1.0, 1.0);
  
  dot = c.dot(d);
  
  EXPECT_DOUBLE_EQ(dot, 3.0);
  
  vec3 e(1.0, 2.0, 0);
  vec3 f(1.0, 1.0, 1.0);
  
  dot = e.dot(f);
  
  EXPECT_DOUBLE_EQ(dot, 3.0);
  
  vec3 g(2.0, 1.0, 2.0);
  vec3 h(1.0, 1.0, 1.0);
  
  dot = g.dot(h);
  
  EXPECT_DOUBLE_EQ(dot, 5.0);
}

TEST(vec3test, sum) {
  vec3 a(0, 1.0, 2.0);
  vec3 b(1.0, 4.0, 9.0);
  
  vec3 c = a + b;
  
  EXPECT_DOUBLE_EQ(c[0], 1.0);
  EXPECT_DOUBLE_EQ(c[1], 5.0);
  EXPECT_DOUBLE_EQ(c[2], 11.0);
}

TEST(vec3test, difference) {
  vec3 a(0, 1.0, 2.0);
  vec3 b(1.0, 4.0, 9.0);
  
  vec3 c = b - a;
  
  EXPECT_DOUBLE_EQ(c[0], 1.0);
  EXPECT_DOUBLE_EQ(c[1], 3.0);
  EXPECT_DOUBLE_EQ(c[2], 7.0);
}

TEST(vec3test, scale) {
  vec3 a(1.0, 2.0, 3.0);
  double s = 10.0;
  
  vec3 b = a * s;
  
  EXPECT_DOUBLE_EQ(b[0], 10.0);
  EXPECT_DOUBLE_EQ(b[1], 20.0);
  EXPECT_DOUBLE_EQ(b[2], 30.0);
  
  vec3 c(0.0, 0.0, 0.0);
  double t = 10.0;
  
  vec3 d = c * t;
  
  EXPECT_DOUBLE_EQ(d[0], 0.0);
  EXPECT_DOUBLE_EQ(d[1], 0.0);
  EXPECT_DOUBLE_EQ(d[2], 0.0);
}

TEST(vec3test, magnitude) {
  
  vec3 a(1.0, 2.0, 2.0);
  vec3 b(2.0, 10.0, 11.0);
  
  EXPECT_DOUBLE_EQ(a.mag(), 3.0);
  EXPECT_DOUBLE_EQ(b.mag(), 15.0);
}

TEST(vec3test, unit) {
  
  vec3 a(1.0, 2.0, 2.0);
  vec3 b = a.unit();
  
  EXPECT_DOUBLE_EQ(b[0], 1.0/3.0);
  EXPECT_DOUBLE_EQ(b[1], 2.0/3.0);
  EXPECT_DOUBLE_EQ(b[2], 2.0/3.0);
}

TEST(vec3test, normalize) {
  
  vec3 a(1.0, 2.0, 2.0);
  a.normalize();
  
  EXPECT_DOUBLE_EQ(a[0], 1.0/3.0);
  EXPECT_DOUBLE_EQ(a[1], 2.0/3.0);
  EXPECT_DOUBLE_EQ(a[2], 2.0/3.0);
}

TEST(vec3test, cross) {
  
  vec3 a(3.0, 2.0, 1.0);
  vec3 b(1.0, 0.0, 1.0);

  vec3 c = a.cross(b);
  vec3 d = b.cross(a);
  
  EXPECT_DOUBLE_EQ(c[0], 2.0);
  EXPECT_DOUBLE_EQ(c[1], -2.0);
  EXPECT_DOUBLE_EQ(c[2], -2.0);
  
  EXPECT_DOUBLE_EQ(d[0], -2.0);
  EXPECT_DOUBLE_EQ(d[1], 2.0);
  EXPECT_DOUBLE_EQ(d[2], 2.0);
  
  vec3 e(1.0, 0.0, 1.0);
  vec3 f(0.0, 1.0, 0.0);
  
  vec3 g = e.cross(f);
  vec3 h = f.cross(e);
  
  EXPECT_DOUBLE_EQ(g[0], -1.0);
  EXPECT_DOUBLE_EQ(g[1], 0.0);
  EXPECT_DOUBLE_EQ(g[2], 1.0);
  
  EXPECT_DOUBLE_EQ(h[0], 1.0);
  EXPECT_DOUBLE_EQ(h[1], 0.0);
  EXPECT_DOUBLE_EQ(h[2], -1.0);
}

TEST(quatTest, constructor) {
  
  quat a;
  
  EXPECT_DOUBLE_EQ(a.s, 0.0);
  EXPECT_DOUBLE_EQ(a.v[0], 0.0);
  EXPECT_DOUBLE_EQ(a.v[1], 0.0);
  EXPECT_DOUBLE_EQ(a.v[2], 0.0);

  quat b(1.0, vec3(0.0, 1.0, 0.0));
  
  EXPECT_DOUBLE_EQ(b.s, 1.0);
  EXPECT_DOUBLE_EQ(b.v[0], 0.0);
  EXPECT_DOUBLE_EQ(b.v[1], 1.0);
  EXPECT_DOUBLE_EQ(b.v[2], 0.0);
  
  quat c(vec3(1.0, 2.0, 3.0));
  
  EXPECT_DOUBLE_EQ(c.s, 0.0);
  EXPECT_DOUBLE_EQ(c.v[0], 1.0);
  EXPECT_DOUBLE_EQ(c.v[1], 2.0);
  EXPECT_DOUBLE_EQ(c.v[2], 3.0);
}

TEST(quatTest, magsq) {
  quat a(1.0, vec3(2.0, 2.0, 0.0));
  
  double m = a.mag_sq();
  
  EXPECT_DOUBLE_EQ(m, 9.0);
}

TEST(quatTest, mag) {
  quat a(1.0, vec3(2.0, 2.0, 0.0));
  
  double m = a.mag();
  
  EXPECT_DOUBLE_EQ(m, 3.0);
}

TEST(quatTest, unit) {
  quat a(1.0, vec3(2.0, 2.0, 0.0));
  quat b = a.unit();
  
  double m = a.mag();
  
  EXPECT_DOUBLE_EQ(m, 3.0);
  
  EXPECT_DOUBLE_EQ(b.s, 1.0/m);
  EXPECT_DOUBLE_EQ(b.v[0], 2.0/m);
  EXPECT_DOUBLE_EQ(b.v[1], 2.0/m);
  EXPECT_DOUBLE_EQ(b.v[2], 0.0/m);
}

TEST(quatTest, normalize) {
  quat a(1.0, vec3(2.0, 2.0, 0.0));
  double m = a.mag();
  a.normalize();
  
  EXPECT_DOUBLE_EQ(m, 3.0);
  
  EXPECT_DOUBLE_EQ(a.s, 1.0/m);
  EXPECT_DOUBLE_EQ(a.v[0], 2.0/m);
  EXPECT_DOUBLE_EQ(a.v[1], 2.0/m);
  EXPECT_DOUBLE_EQ(a.v[2], 0.0/m);
}

TEST(quatTest, scaling) {
  quat a(1.0, vec3(2.0, 3.0, 4.0));
  a = a * 5;
  
  EXPECT_DOUBLE_EQ(a.s, 5.0);
  EXPECT_DOUBLE_EQ(a.v[0], 10.0);
  EXPECT_DOUBLE_EQ(a.v[1], 15.0);
  EXPECT_DOUBLE_EQ(a.v[2], 20.0);
}

TEST(quatTest, inv) {
  quat a(1.0, vec3(2.0, 2.0, 0.0));
  quat b = a.inv();
  
  EXPECT_DOUBLE_EQ(b.s, 1.0/9.0);
  EXPECT_DOUBLE_EQ(b.v[0], -2.0/9.0);
  EXPECT_DOUBLE_EQ(b.v[1], -2.0/9.0);
  EXPECT_DOUBLE_EQ(b.v[2], 0.0/9.0);
}

TEST(quatTest, quatMultiplication) {
  /* Case 1: s1 = s2 = 0 */
  vec3 x(1.0, 1.0, 1.0);
  vec3 y(1.0, 4.0, 9.0);
  vec3 z = x.cross(y);
  
  quat a(0.0, x);
  quat b(0.0, y);
  
  quat c = a * b;
  
  EXPECT_DOUBLE_EQ(c.s, -x.dot(y));
  EXPECT_DOUBLE_EQ(c.v[0], z[0]);
  EXPECT_DOUBLE_EQ(c.v[1], z[1]);
  EXPECT_DOUBLE_EQ(c.v[2], z[2]);
  
  /* Case 2: x1 = c, v1 = 0 */
  x[0] = 0;
  x[1] = 0;
  x[2] = 0;
  
  quat d(2.0, x);
  quat e(1.0, y);
  
  quat f = d * e;
  
  EXPECT_DOUBLE_EQ(f.s, 2.0);
  EXPECT_DOUBLE_EQ(f.v[0], 2.0 * y[0]);
  EXPECT_DOUBLE_EQ(f.v[1], 2.0 * y[1]);
  EXPECT_DOUBLE_EQ(f.v[2], 2.0 * y[2]);
  
  /* Case 3: General Case*/
  quat g(1.0, vec3(2.0, 2.0, 0.0));
  quat h(1.0/9.0, vec3(-2.0/9.0, -2.0/9.0, 0.0));
  
  quat i = g * h;
  
  EXPECT_DOUBLE_EQ(i.s, 1.0);
  EXPECT_DOUBLE_EQ(i.v[0], 0);
  EXPECT_DOUBLE_EQ(i.v[1], 0);
  EXPECT_DOUBLE_EQ(i.v[2], 0);
  
}

int main(int argc, char **argv) {
  
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}
