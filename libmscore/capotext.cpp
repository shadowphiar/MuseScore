//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id: tempotext.cpp 5427 2012-03-07 12:41:34Z wschweer $
//
//  Copyright (C) 2008-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include "score.h"
#include "capotext.h"
#include "tempo.h"
#include "system.h"
#include "measure.h"

//---------------------------------------------------------
//   CapoText
//---------------------------------------------------------

CapoText::CapoText(Score* s)
   : Text(s)
      {
      _position = 0;
      _displayInline = true;
      _brackets = true;
      _simplify = true;
      setPlacement(ABOVE);
      setTextStyle(s->textStyle(TEXT_STYLE_TEMPO));
      }

//---------------------------------------------------------
//   write
//---------------------------------------------------------

void CapoText::write(Xml& xml) const
      {
      xml.stag("CapoText");
      xml.tag("position", _position);
      if (_displayInline)
            xml.tag("displayInline", _displayInline);
      if (_brackets)
            xml.tag("brackets", _brackets);
      if (_simplify)
            xml.tag("brackets", _simplify);
      Text::writeProperties(xml);
      xml.etag();
      }

//---------------------------------------------------------
//   read
//---------------------------------------------------------

void CapoText::read(XmlReader& e)
      {
      while (e.readNextStartElement()) {
            const QStringRef& tag(e.name());
            if (tag == "position")
                  _position = e.readInt();
            else if (tag == "displayInline")
                  _displayInline = e.readInt();
            else if (tag == "brackets")
                  _brackets = e.readInt();
            else if (tag == "simplify")
                  _simplify = e.readInt();
            else if (!Text::readProperties(e))
                  e.unknown();
            }
      }

//---------------------------------------------------------
//   undoSetPosition
//---------------------------------------------------------

void CapoText::undoSetPosition(unsigned v)
      {
      score()->undoChangeProperty(this, P_CAPO_POSITION, v);
      }

//---------------------------------------------------------
//   undoSetDisplayInline
//---------------------------------------------------------

void CapoText::undoSetDisplayInline(bool v)
      {
      score()->undoChangeProperty(this, P_CAPO_DISPLAY_INLINE, v);
      }

//---------------------------------------------------------
//   undoSetBrackets
//---------------------------------------------------------

void CapoText::undoSetBrackets(bool v)
      {
      score()->undoChangeProperty(this, P_CAPO_BRACKETS, v);
      }

//---------------------------------------------------------
//   undoSetSimplify
//---------------------------------------------------------

void CapoText::undoSetSimplify(bool v)
      {
      score()->undoChangeProperty(this, P_CAPO_SIMPLIFY, v);
      }

//---------------------------------------------------------
//   getProperty
//---------------------------------------------------------

QVariant CapoText::getProperty(P_ID propertyId) const
      {
      switch(propertyId) {
            case P_CAPO_POSITION:     	return _position;
            case P_CAPO_DISPLAY_INLINE: return _displayInline;
            case P_CAPO_BRACKETS:       return _brackets;
            case P_CAPO_SIMPLIFY:       return _simplify;
            default:
                  return Text::getProperty(propertyId);
            }
      }

//---------------------------------------------------------
//   setProperty
//---------------------------------------------------------

bool CapoText::setProperty(P_ID propertyId, const QVariant& v)
      {
      switch(propertyId) {
            case P_CAPO_POSITION:
                  _position = v.toUInt();
                  break;
            case P_CAPO_DISPLAY_INLINE:
            	_displayInline = v.toBool();
                  break;
            case P_CAPO_BRACKETS:
            	_brackets = v.toBool();
                  break;
            case P_CAPO_SIMPLIFY:
            	_simplify = v.toBool();
                  break;
            default:
                  if (!Text::setProperty(propertyId, v))
                        return false;
                  break;
            }
      score()->setLayoutAll(true);
      return true;
      }

//---------------------------------------------------------
//   propertyDefault
//---------------------------------------------------------

QVariant CapoText::propertyDefault(P_ID id) const
      {
      switch(id) {
      	    case P_CAPO_POSITION:	  	return 0;
      	    case P_CAPO_DISPLAY_INLINE:	return true;
      	    case P_CAPO_BRACKETS:	    return true;
      	    case P_CAPO_SIMPLIFY:	    return true;
            case P_PLACEMENT:         return ABOVE;
            default:                  return Text::propertyDefault(id);
            }
      }

//---------------------------------------------------------
//   layout
//---------------------------------------------------------

void CapoText::layout()
      {
      Text::layout();
      if (placement() == BELOW) {
            rypos() = -rypos() + 4 * spatium();
            // rUserYoffset() *= -1;
            // text height ?
            }
      }


