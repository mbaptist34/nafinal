//
//  physics.cpp
//  
//
//  Created by Matthew Baptist on 5/16/19.
//
//

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "quat.hpp"

int main(int argc, char **argv) {
  
  vec3 p(1.0, 0.0, 0.0);
  
  quat q[4] = { quat(0, vec3(0, 0, 1)),
                quat(-1, vec3(0, 0, 0)),
                quat(0, vec3(0, 0, -1)),
                quat(1, vec3(0, 0, 0))};
  
  vec3 scoords[12];
  vec3 lcoords[12];
  
  int ind = 0;
  
  for (int i = 0; i < 4; i++) {
    int k = (i + 1) % 4;
    
    lcoords[ind] = q[i].rot(p);
    scoords[ind++] = q[i].rot(p);
    
    for (int j = 1; j < 3; j++) {
      double t = 1 / 3.0;
      
      quat temp = q[i].slerp(q[k], j * t);
      quat ltemp;
      ltemp.s = q[i].s * (1 - j * t) + q[k].s * (j * t);
      ltemp.v[0] = q[i].v[0] * (1 - j * t) + q[k].v[0] * (j * t);
      ltemp.v[1] = q[i].v[1] * (1 - j * t) + q[k].v[1] * (j * t);
      ltemp.v[2] = q[i].v[2] * (1 - j * t) + q[k].v[2] * (j * t);
      
      lcoords[ind] = ltemp.rot(p);
      scoords[ind++] = temp.rot(p);
    }
    
  }
  std::cout << "Slerp points: " << std::endl;
  for (int i = 0; i < 12; i++) {
    
    std::cout << scoords[i][0] << ", " << scoords[i][1]
              << ", " << scoords[i][2] << std::endl;
    
  }
  std::cout << "Lerp points: " << std::endl;
  for (int i = 0; i < 12; i++) {
    
    std::cout << lcoords[i][0] << ", " << lcoords[i][1]
    << ", " << lcoords[i][2] << std::endl;
    
  }
  
  double sum = 0;
  for (int i = 0; i < 12; i++) {
    double term = (scoords[i] - lcoords[i]).mag();
    term = term * term;
    sum += term;
  }
  std::cout << "Error of Lerp" << std::endl;
  std::cout << sqrt(sum) << std::endl;
}
