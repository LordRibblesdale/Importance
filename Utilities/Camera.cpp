#include "Camera.h"

Camera::Camera(Float3&  eye, Float3&  lookAt) : eye(std::move(eye)), lootAt(std::move(lookAt)),  up(std::move(Float3(0, 0, 1))) {}

SquareMatrix Camera::world2ViewMatrix() {
   Float3 zView(eye - lootAt);
   Float3 xView(std::move(up.cross_product(zView)));
   Float3 yView(std::move(zView.cross_product(xView)));
   SquareMatrix view2WorldMatrix(4, {});

   for (int i = 0; i < xView.get_size(); ++i) {
      view2WorldMatrix.get_array()[i*view2WorldMatrix.get_dimension()] = xView.get_vector().get()[i];
      view2WorldMatrix.get_array()[i*view2WorldMatrix.get_dimension() + 1] = yView.get_vector().get()[i];
      view2WorldMatrix.get_array()[i*view2WorldMatrix.get_dimension() + 2] = zView.get_vector().get()[i];
   }

   view2WorldMatrix.get_array()[view2WorldMatrix.get_dimension()*view2WorldMatrix.get_dimension()-1] = 1;

   return SquareMatrix::calculate_inverse(view2WorldMatrix);
}
