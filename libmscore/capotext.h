//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id: capotext.h 5500 2013-01-19 01:46:26Z acollier $
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __CAPOTEXT_H__
#define __CAPOTEXT_H__

#include "text.h"

//-------------------------------------------------------------------
//   @@ CapoText
///   Capo marker which determines the capo display for
///   Chord Name (harmony) elements
//
//    @P position unsigned 	capo position (in semitones, or 0 for no display)
//    @P displayInline bool show capo chordname inline with harmony
//    @P brackets bool      show capo chordname in brackets
//    @P simplify bool		show a simplified chord, e.g. Asus2(G)
//-------------------------------------------------------------------

class CapoText : public Text  {
      Q_OBJECT
      Q_PROPERTY(unsigned position      READ position   	WRITE undoSetPosition)
      Q_PROPERTY(bool     displayInline READ displayInline  WRITE undoSetDisplayInline)
      Q_PROPERTY(bool     brackets      READ brackets 		WRITE undoSetBrackets)
      Q_PROPERTY(bool     simplify      READ simplify 		WRITE undoSetSimplify)

      unsigned	_position;		// fret position in semitones
      bool _displayInline; 	    // display the capo chord name inline with harmony
      bool _brackets;			// display brackets around the capo chord name
      bool _simplify;			// display simplified version of capo chord name
   public:
      CapoText(Score*);
      virtual CapoText* clone() const { return new CapoText(*this); }
      virtual ElementType type() const { return CAPO_TEXT; }
      virtual void write(Xml& xml) const;
      virtual void read(XmlReader&);
      Segment* segment() const   { return (Segment*)parent(); }
      Measure* measure() const   { return (Measure*)parent()->parent(); }

      unsigned position() const  { return _position;   }
      void setPosition(unsigned v)  { _position = v;         }
      void undoSetPosition(unsigned v);

      bool displayInline() const    { return _displayInline; }
      void setDisplayInline(bool v) { _displayInline = v;    }
      void undoSetDisplayInline(bool v);

      bool brackets() const    { return _brackets; }
      void setBrackets(bool v) { _brackets = v;    }
      void undoSetBrackets(bool v);

      bool simplify() const    { return _simplify; }
      void setSimplify(bool v) { _simplify = v;    }
      void undoSetSimplify(bool v);

      virtual void textChanged();
      virtual void layout();

      QVariant getProperty(P_ID propertyId) const;
      bool setProperty(P_ID propertyId, const QVariant&);
      QVariant propertyDefault(P_ID id) const;
      };

#endif
