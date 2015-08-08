//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-03
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../FindFlags.hpp"

namespace Ystring { namespace Encoded {

template <typename Decoder>
bool advanceCharacter(Decoder& it);

template <typename Decoder>
size_t advanceCharacters(Decoder& it, size_t n);

template <typename Encoder, typename Decoder>
void appendLower(Encoder&& dst, Decoder&& src);

template <typename Encoder, typename Decoder>
void appendTitle(Encoder&& dst, Decoder&& src);

template <typename Encoder, typename Decoder>
void appendUpper(Encoder&& dst, Decoder&& src);

template <typename Decoder1, typename Decoder2>
int32_t caseInsensitiveCompare(Decoder1 str, Decoder2 cmp);

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveEqual(Decoder1 str, Decoder2 cmp);

template <typename Decoder1, typename Decoder2>
bool caseInsensitiveLess(Decoder1 str, Decoder2 cmp);

template <typename Decoder1, typename Decoder2>
Decoder1 find(Decoder1& str, Decoder2 sub,
              FindFlags_t flags = FindFlags::DEFAULTS);

template <typename Decoder>
bool isAlphaNumeric(Decoder dec);

template <typename Decoder>
Decoder nextLine(Decoder& str);

template <typename Decoder>
Decoder nextNewline(Decoder& str);

template <typename Decoder, typename UnaryPredicate>
Decoder nextToken(Decoder& str, UnaryPredicate predicate);

template <typename Decoder1, typename Decoder2>
Decoder1 nextToken(Decoder1& str, Decoder2 cmp, FindFlags_t flags);

template <typename Decoder1, typename Decoder2>
bool startsWith(Decoder1&& str, Decoder2&& sub,
                FindFlags_t flags = FindFlags::DEFAULTS);

}}

#include "DecoderStringFunctions-impl.hpp"
