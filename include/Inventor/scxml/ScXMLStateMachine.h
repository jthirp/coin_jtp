#ifndef COIN_SCXMLSTATEMACHINE_H
#define COIN_SCXMLSTATEMACHINE_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2008 by Kongsberg SIM.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg SIM about acquiring
 *  a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg SIM, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/scxml/ScXMLObject.h>

#include <Inventor/SbName.h>
#include <Inventor/tools/SbPimplPtr.h>

class ScXMLEvent;
class ScXMLDocument;
class ScXMLStateBase;
class ScXMLStateMachine;
class ScXMLStateMachineP;

typedef void ScXMLStateMachineDeleteCB(void * data, const ScXMLStateMachine * sm);

class COIN_DLL_API ScXMLStateMachine : public ScXMLObject {
  typedef ScXMLObject inherited;
  SCXML_OBJECT_HEADER(ScXMLStateMachine);

public:
  static void initClass(void);

  ScXMLStateMachine(void);
  virtual ~ScXMLStateMachine(void);

  virtual void setName(const SbName & name);
  const SbName & getName(void) const { return this->name; }

  virtual void setDescription(ScXMLDocument * document);
  const ScXMLDocument * getDescription(void) const { return this->description; }

  virtual void initialize(void);

  virtual void queueEvent(const ScXMLEvent * event, SbBool dealloc = FALSE);
  virtual void queueEvent(const SbName & eventid);
  virtual SbBool processEventQueue(void);

  virtual SbBool isActive(void) const;
  virtual SbBool isFinished(void) const;



  virtual const ScXMLEvent * getCurrentEvent(void) const;

  virtual int getNumActiveStates(void) const;
  virtual const ScXMLObject * getActiveState(int idx) const;

  virtual void addDeleteCallback(ScXMLStateMachineDeleteCB * cb, void * userdata);
  virtual void removeDeleteCallback(ScXMLStateMachineDeleteCB * cb, void * userdata);

protected:
  virtual SbBool processOneEvent(const ScXMLEvent * event);

  virtual void setCurrentEvent(const ScXMLEvent * event);

protected:
  SbName name;

  ScXMLDocument * description;

  SbBool active;
  SbBool finished;

private:
  ScXMLStateMachine(const ScXMLStateMachine & rhs); // N/A
  ScXMLStateMachine & operator = (const ScXMLStateMachine & rhs); // N/A

  SbPimplPtr<ScXMLStateMachineP> pimpl;

}; // ScXMLStateMachine

#endif // !COIN_SCXMLSTATEMACHINE_H