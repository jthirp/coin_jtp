#ifndef COIN_SBSPHEREPROJECTOR_H
#define COIN_SBSPHEREPROJECTOR_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion.  All rights reserved.
 *  
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.  See the
 *  file LICENSE.GPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you desire to use Coin with software that is incompatible
 *  licensewise with the GPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

#include <Inventor/projectors/SbProjector.h>
#include <Inventor/SbSphere.h>
#include <Inventor/SbRotation.h>

class COIN_DLL_API SbSphereProjector : public SbProjector {
  typedef SbProjector inherited;

public:
  SbVec3f projectAndGetRotation(const SbVec2f & point, SbRotation & rot);
  virtual SbRotation getRotation(const SbVec3f & point1,
                                 const SbVec3f & point2) = 0;

  void setSphere(const SbSphere & sph);
  const SbSphere & getSphere(void) const;
  void setOrientToEye(const SbBool orienttoeye);
  SbBool isOrientToEye(void) const;
  void setFront(const SbBool infront);
  SbBool isFront(void) const;
  SbBool isPointInFront(const SbVec3f & point) const;
  virtual void setWorkingSpace(const SbMatrix & space);

protected:
  SbSphereProjector(const SbBool orienttoeye);
  SbSphereProjector(const SbSphere & s, const SbBool orienttoeye);

  SbBool intersectSphereFront(const SbLine & l, SbVec3f & result);

  SbBool intersectFront;
  SbSphere sphere;
  SbBool orientToEye;
  SbBool needSetup;
  SbVec3f lastPoint;
};

#endif // !COIN_SBSPHEREPROJECTOR_H
