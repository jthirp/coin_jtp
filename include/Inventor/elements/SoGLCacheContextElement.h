/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2000 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

#ifndef COIN_SOGLCACHECONTEXTELEMENT_H
#define COIN_SOGLCACHECONTEXTELEMENT_H

#include <Inventor/elements/SoSubElement.h>

class COIN_DLL_EXPORT SoGLCacheContextElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoGLCacheContextElement);
public:
  static void initClass(void);
protected:
  virtual ~SoGLCacheContextElement();

public:
  virtual void init(SoState * state);

  virtual SbBool matches(const SoElement * elt) const;
  virtual SoElement * copyMatchInfo(void) const;
  static void set(SoState * state, int context,
                  SbBool twopasstransparency,
                  SbBool remoterendering);
  static int get(SoState * state);
  static int getExtID(const char * str);
  static void getOpenGLVersion(SoState * state, int & major, int & minor);
  static SbBool extSupported(SoState * state, int extid);
  static SbBool areMipMapsFast(SoState * state);
  enum {
    DO_AUTO_CACHE,
    DONT_AUTO_CACHE
  };
  static void shouldAutoCache(SoState * state, int bits);
  static void setAutoCacheBits(SoState * state, int bits);
  static int resetAutoCacheBits(SoState * state);
  static SbBool getIsRemoteRendering(SoState * state);

private:
  friend class SoGLDisplayList;
  static void scheduleDelete(SoState * state, class SoGLDisplayList * dl);

private:
  int context;
  SbBool twopass;
  SbBool remote;
};

// implementation in Coin/src/elements/SoGLDisplayList.cpp
class COIN_DLL_EXPORT SoGLDisplayList {
  friend class SoGLCacheContextElement;
  ~SoGLDisplayList();
public:
  enum Type {
    DISPLAY_LIST,
    TEXTURE_OBJECT
  };
  SoGLDisplayList(SoState * state, Type type, int allocnum = 1,
                  SbBool mipmaptexobj = FALSE);
  void ref(void);
  void unref(SoState * state = NULL);

  void open(SoState *state, int index = 0);
  void close(SoState *state);

  void call(SoState * state, int index = 0);
  void addDependency(SoState * state);

  SbBool isMipMapTextureObject(void) const;
  Type getType(void) const;
  int getNumAllocated(void) const;
  // this returns GLuint in Inventor, but we try to avoid including
  // gl.h in the header files so we just return unsigned int.
  unsigned int getFirstIndex(void) const;
  int getContext(void) const;

private:
  Type type;
  int numalloc;
  unsigned int firstindex;
  int context;
  int refcount;
  SbBool mipmap;
};


#endif // COIN_SOGLCACHECONTEXTELEMENT_H
