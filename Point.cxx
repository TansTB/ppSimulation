#include "Point.h"

Point::Point(Double_t x, Double_t y, Double_t z){
  this->x = x;
  this->y = y;
  this->z = z;
}

void Point::SetX(Double_t x){this->x = x;}
void Point::SetY(Double_t y){this->y = y;}
void Point::SetZ(Double_t z){this->z = z;}
// void Point::Print(){std::cout<<"x: " << x << "\ny: " << y << "\nz: " << z << std::endl;}