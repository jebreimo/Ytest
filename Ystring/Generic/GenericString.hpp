//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02
//
// This file is distributed under the Simplified BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <vector>
#include "../FindFlags.hpp"
#include "../SplitFlags.hpp"
#include "RangeAlgorithms.hpp"
#include "StringReference.hpp"

namespace Ystring { namespace Generic {

template <typename Str, typename Enc>
void append(StringReference<Str>& dst, uint32_t chr, Enc encoding);

template <typename Str, typename Enc>
void append(StringReference<Str>&& dst, uint32_t chr, Enc encoding);

template <typename Str, typename It, typename Enc1, typename Enc2>
void append(StringReference<Str> dst, Range<It> src,
            Enc1 dstEncoding, Enc2 srcEncoding);

template <typename Str, typename It1, typename It2>
void appendJoin(StringReference<Str>& dst, It1 first, It1 last,
                Range<It2> delimiter);

template <typename Str, typename It>
void appendJoin(StringReference<Str>& dst, It first, It last);

template <typename Str, typename It, typename Enc1, typename Enc2>
Str convert(Range<It> str, Enc1 fromEncoding, Enc2 toEncoding);

template <typename It, typename Enc>
size_t countCharacters(Range<It> str, Enc encoding);

template <typename It1, typename It2, typename Enc>
bool endsWith(Range<It1> str,
              Range<It2> cmp,
              Enc encoding,
              FindFlags_t flags = FindFlags::DEFAULTS);

template <typename It, typename Enc>
uint32_t getCodePoint(Range<It> str, ptrdiff_t pos, Enc encoding);

template <typename Str, typename It1, typename It2>
Str join(It1 first, It1 last, Range<It2> delimiter);

template <typename Str, typename It>
Str join(It first, It last);

template <typename Str, typename It1, typename It2, typename Enc>
std::vector<Str> split(
        Range<It1> str,
        Range<It2> cmp,
        Enc encoding,
        ptrdiff_t maxSplits = 0,
        SplitFlags_t flags = SplitFlags::IGNORE_EMPTY);

template <typename Str, typename It, typename Enc, typename Predicate>
std::vector<Str> splitIf(
        Range<It> str,
        Enc encoding,
        Predicate predicate,
        ptrdiff_t maxSplits,
        SplitFlags_t flags);

template <typename It, typename Enc, typename UnaryPred>
Range<It> trim(Range<It> str,
               Enc encoding,
               UnaryPred trimChar);

template <typename It, typename Enc, typename UnaryPred>
Range<It> trimEnd(Range<It> str,
                  Enc encoding,
                  UnaryPred trimChar);

template <typename It, typename Enc, typename UnaryPred>
Range<It> trimStart(Range<It> str,
                    Enc encoding,
                    UnaryPred trimChar);

}}

#include "GenericString-impl.hpp"
