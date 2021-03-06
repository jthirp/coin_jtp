/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

/*!
  \class SoSFBox3s SoSFBox3s.h Inventor/fields/SoSFBox3s.h
  \brief The SoSFBox3s class is a container for an SbBox3s vector.

  \ingroup fields

  This field is used where nodes, engines or other field containers
  need to store a box.

  \COIN_CLASS_EXTENSION

  \since Coin 2.0
*/

// *************************************************************************

#include <Inventor/fields/SoSFBox3s.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>

#include "fields/SoSubFieldP.h"

// *************************************************************************

SO_SFIELD_SOURCE(SoSFBox3s, SbBox3s, const SbBox3s &);

// *************************************************************************

// Override from parent class.
void
SoSFBox3s::initClass(void)
{
  SO_SFIELD_INTERNAL_INIT_CLASS(SoSFBox3s);
}

// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS


SbBool
SoSFBox3s::readValue(SoInput * in)
{
  short min[3];
  short max[3];
  if (!in->read(min[0]) ||
      !in->read(min[1]) ||
      !in->read(min[2]) ||
      !in->read(max[0]) ||
      !in->read(max[1]) ||
      !in->read(max[2])) {
    SoReadError::post(in, "Couldn't read SoSFBox3s");
    return FALSE;
  }
  this->setValue(min[0], min[1], min[2], max[0], max[1], max[2]);
  return TRUE;
}

void
SoSFBox3s::writeValue(SoOutput * out) const
{
  short min[3];
  short max[3];
  SbBox3s b = this->getValue();
  b.getBounds(min[0], min[1], min[2], max[0], max[1], max[2]);

  out->write(min[0]);
  if (!out->isBinary()) out->write(' ');
  out->write(min[1]);
  if (!out->isBinary()) out->write(' ');
  out->write(min[2]);
  if (!out->isBinary()) out->write(' ');
  out->write(max[0]);
  if (!out->isBinary()) out->write(' ');
  out->write(max[1]);
  if (!out->isBinary()) out->write(' ');
  out->write(max[2]);
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

/*!
  Set value of vector.
*/
void
SoSFBox3s::setValue(short xmin,
                    short ymin,
                    short zmin,
                    short xmax,
                    short ymax,
                    short zmax)
{
  this->setValue(SbBox3s(xmin, ymin, zmin, xmax, ymax, zmax));
}


/*!
  Set value of vector.
*/
void
SoSFBox3s::setValue(const SbVec3s & minvec, const SbVec3s & maxvec)
{
  this->setValue(SbBox3s(minvec, maxvec));
}


/*!
  Set value of vector.
*/
void
SoSFBox3s::getValue(SbBox3s & box) const
{
  box = value;
}

// *************************************************************************

#ifdef COIN_TEST_SUITE

BOOST_AUTO_TEST_CASE(initialized)
{
  SoSFBox3s field;
  BOOST_CHECK_MESSAGE(SoSFBox3s::getClassTypeId() != SoType::badType(),
                      "SoSFBox3s class not initialized");
  BOOST_CHECK_MESSAGE(field.getTypeId() != SoType::badType(),
                      "missing class initialization");
}

#endif // COIN_TEST_SUITE
