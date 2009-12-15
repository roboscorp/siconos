/* Siconos-Example version 3.0.0, Copyright INRIA 2005-2008.
 * Siconos is a program dedicated to modeling, simulation and control
 * of non smooth dynamical systems.
 * Siconos is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Siconos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Siconos; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth FLOOR, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY vincent.acary@inrialpes.fr
 *
 */

#include "Sphere.hpp"

static double _2PI = 2 * M_PI;


void normalize(SP::SiconosVector q, unsigned int i)
{

  q->setValue(i, fmod(q->getValue(i), _2PI));

  assert(fabs(q->getValue(i)) - std::numeric_limits<double>::epsilon() >= 0.);
  assert(fabs(q->getValue(i)) < _2PI);

}

void Sphere::computeMass()
{

  SP::SiconosVector qold;


  if (qMemory())
    qold = qMemory()->getSiconosVector(0);

  normalize(q(), 3);
  normalize(q(), 4);
  normalize(q(), 5);

  if (qold)
  {
    normalize(qold, 3);
    normalize(qold, 4);
    normalize(qold, 5);
  }

  double theta = q()->getValue(3);

  assert(fabs(theta) - std::numeric_limits<double>::epsilon() >= 0.);
  //assert (fabs(theta) - _2PI < 0.);

  (*_mass)(4, 5) = (*_mass)(5, 4) = I * cos(theta);

}

void Sphere::computeNNL()
{
  Sphere::computeNNL(q(), velocity());
}

void Sphere::computeNNL(SP::SiconosVector q, SP::SiconosVector v)
{

  assert(q->size() == 6);
  assert(v->size() == 6);

  //  normalize(q,3);
  //normalize(q,4);
  //normalize(q,5);

  double theta    = q->getValue(3);
  double phi      = q->getValue(4);
  double psi      = q->getValue(5);

  double thetadot = v->getValue(3);
  double phidot   = v->getValue(4);
  double psidot   = v->getValue(5);

  double sintheta   = sin(theta);

  (*_NNL)(0) = (*_NNL)(1) = (*_NNL)(2) = 0;

  (*_NNL)(3) = I * psidot * phidot * sintheta;
  (*_NNL)(4) = -I * psidot * thetadot * sintheta;
  (*_NNL)(5) = -I * phidot * thetadot * sintheta;
}



void Sphere::computeJacobianqNNL()
{

  Sphere::computeJacobianqNNL(q(), velocity());
}
void Sphere::computeJacobianqDotNNL()
{

  Sphere::computeJacobianqDotNNL(q(), velocity());
}

void Sphere::computeJacobianqNNL(SP::SiconosVector q, SP::SiconosVector v)
{
  double theta    = q->getValue(3);
  double phi      = q->getValue(4);
  double psi      = q->getValue(5);

  double thetadot = v->getValue(3);
  double phidot   = v->getValue(4);
  double psidot   = v->getValue(5);

  double costheta = cos(theta);

  _jacobianqNNL->zero();

  (*_jacobianqNNL)(3, 3) = -I * psidot * phidot * costheta;
  (*_jacobianqNNL)(4, 3) = I * psidot * thetadot * costheta;
  (*_jacobianqNNL)(5, 3) = I * psidot * thetadot * costheta;


}
void Sphere::computeJacobianqDotNNL(SP::SiconosVector q, SP::SiconosVector v)
{
  double theta    = q->getValue(3);
  double phi      = q->getValue(4);
  double psi      = q->getValue(5);

  double thetadot = v->getValue(3);
  double phidot   = v->getValue(4);
  double psidot   = v->getValue(5);

  double sintheta   = sin(theta);

  _jacobianqDotNNL->zero();


  (*_jacobianqDotNNL)(3, 3) = 0;
  (*_jacobianqDotNNL)(3, 4) = I * psidot * sintheta;
  (*_jacobianqDotNNL)(3, 5) = I * phidot * sintheta;

  (*_jacobianqDotNNL)(4, 3) = -I * psidot * sintheta;
  (*_jacobianqDotNNL)(4, 4) = 0;
  (*_jacobianqDotNNL)(4, 5) = -I * thetadot * sintheta;

  (*_jacobianqDotNNL)(5, 3) =  -I * phidot * sintheta;
  (*_jacobianqDotNNL)(5, 4) =  -I * thetadot * sintheta;
  (*_jacobianqDotNNL)(5, 5) = 0;

}


Sphere::Sphere(double r, double m,
               SP::SiconosVector qinit,
               SP::SiconosVector vinit)
  : LagrangianDS(qinit, vinit), radius(r), massValue(m)
{

  normalize(q(), 3);
  normalize(q(), 4);
  normalize(q(), 5);
  _ndof = 6;

  assert(qinit->size() == _ndof);
  assert(vinit->size() == _ndof);

  double theta    = qinit->getValue(3);
  double phi      = qinit->getValue(4);
  double psi      = qinit->getValue(5);

  double thetadot = vinit->getValue(3);
  double phidot   = vinit->getValue(4);
  double psidot   = vinit->getValue(5);


  _mass.reset(new SimpleMatrix(_ndof, _ndof));
  _mass->zero();
  I = massValue * radius * radius * 2. / 5.;
  (*_mass)(0, 0) = (*_mass)(1, 1) = (*_mass)(2, 2) = massValue;    ;
  (*_mass)(3, 3) = (*_mass)(4, 4) = (*_mass)(5, 5) = I;

  computeMass();

  _jacobianqNNL.reset(new SimpleMatrix(_ndof, _ndof));
  _jacobianqDotNNL.reset(new SimpleMatrix(_ndof, _ndof));

  _NNL.reset(new SimpleVector(_ndof));
  _NNL->zero();

  computeNNL();


}

Sphere::~Sphere()
{}
