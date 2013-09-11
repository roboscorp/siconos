/* Siconos-Kernel, Copyright INRIA 2005-2012.
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact: Vincent ACARY, siconos-team@lists.gforge.inria.fr
*/

/*! \file Circle.hpp
 */
/** \class Circle
 * \brief Definition of a 2D Circle - Inherits from CircularDS
*/

#ifndef Circle_H
#define Circle_H

#include "CircularDS.hpp"

class Circle : public CircularDS, public std11::enable_shared_from_this<Circle>
{
private:
  /** serialization hooks
  */
  ACCEPT_SERIALIZATION(Circle);


  void MassSetup();


protected:

  Circle() : CircularDS() {};

public:

  /** Constructor
      \param radius
      \param mass
      \param postion vector
      \param velocity vector
  */

  Circle(double, double, SP::SiconosVector, SP::SiconosVector);

  /** destructor
   */
  ~Circle();

  /** visitors hook */
  ACCEPT_SP_VISITORS();

};
#endif /* Circle_H */

