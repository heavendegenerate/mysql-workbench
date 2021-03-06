/*
 * Copyright (c) 2009, 2018, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2.0,
 * as published by the Free Software Foundation.
 *
 * This program is also distributed with certain software (including
 * but not limited to OpenSSL) that is licensed under separate terms, as
 * designated in a particular file or component or in included license
 * documentation.  The authors of MySQL hereby grant you an additional
 * permission to link the program and your derivative works with the
 * separately licensed software that they have included with MySQL.
 * This program is distributed in the hope that it will be useful,  but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 * the GNU General Public License, version 2.0, for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA 
 */

#pragma once

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "grt.h"
#include "grtpp_util.h"
#include "grtdb/db_object_helpers.h"
#include "grts/structs.db.mysql.h"
#include "grts/structs.workbench.physical.h"

#include <fstream>

#include "grt/common.h"
#include "grt/grt_manager.h"
#include "grtdb/db_object_helpers.h"

#include "ILexer.h"

/**
 * For in-memory styling of SQL text we need a mockup-backend we can feed to the lexer accessor
 * (which does the actual styling). It holds the styles the lexer determined for the given text.
 */
class LexerDocument : public Scintilla::IDocument {
private:
  const std::string& _text;
  std::vector<std::pair<std::size_t, std::size_t> > _lines;

  char* _style_buffer;
  std::vector<int> _level_cache;
  int _style_position;
  char _styling_mask;

public:
  LexerDocument(const std::string& text);
  virtual ~LexerDocument();

  // IDocument implementation.
  virtual int SCI_METHOD Version() const;
  virtual void SCI_METHOD SetErrorStatus(int status);
  virtual int SCI_METHOD Length() const;
  virtual void SCI_METHOD GetCharRange(char* buffer, int position, int lengthRetrieve) const;
  virtual char SCI_METHOD StyleAt(int position) const;
  virtual int SCI_METHOD LineFromPosition(int position) const;
  virtual int SCI_METHOD LineStart(int line) const;
  virtual int SCI_METHOD GetLevel(int line) const;
  virtual int SCI_METHOD SetLevel(int line, int level);
  virtual int SCI_METHOD GetLineState(int line) const;
  virtual int SCI_METHOD SetLineState(int line, int state);
  virtual void SCI_METHOD StartStyling(int position, char mask);
  virtual bool SCI_METHOD SetStyleFor(int length, char style);
  virtual bool SCI_METHOD SetStyles(int length, const char* styles);
  virtual void SCI_METHOD DecorationSetCurrentIndicator(int indicator);
  virtual void SCI_METHOD DecorationFillRange(int position, int value, int fillLength);
  virtual void SCI_METHOD ChangeLexerState(int start, int end);
  virtual int SCI_METHOD CodePage() const;
  virtual bool SCI_METHOD IsDBCSLeadByte(char ch) const;
  virtual const char* SCI_METHOD BufferPointer();
  virtual int SCI_METHOD GetLineIndentation(int line);
};
