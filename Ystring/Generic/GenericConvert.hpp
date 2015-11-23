//****************************************************************************
// Copyright © 2015 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2015-06-02.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include "../Encoded/DecoderStringFunctions.hpp"
#include "../Encoded/ForwardDecoder.hpp"
#include "StringReference.hpp"
#include "StringTypeTraits.hpp"

namespace Ystring { namespace Generic {
    namespace Detail {
        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendImpl(StringReference <Str> dst, Range <It> src,
                        Enc1 dstEncoding, Enc2 srcEncoding,
                        std::true_type);

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendImpl(StringReference <Str> dst, Range <It> src,
                        Enc1 dstEncoding, Enc2 srcEncoding,
                        std::false_type);

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendWithEncoder(StringReference <Str> dst, Range <It> src,
                               Enc1 dstEncoding, Enc2 srcEncoding,
                               std::true_type);

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendWithEncoder(StringReference <Str> dst, Range <It> src,
                               Enc1 dstEncoding, Enc2 srcEncoding,
                               std::false_type);
    }


    template<typename Str, typename It, typename Enc1, typename Enc2>
    void append(StringReference<Str> dst, Range<It> src,
                Enc1 dstEncoding, Enc2 srcEncoding)
    {
        Detail::appendImpl(
                dst, src, dstEncoding, srcEncoding,
                CanCopyRawValues<
                        typename StringReference<Str>::ValueType,
                        Enc1,
                        typename Range<It>::ValueType, Enc2>());
    }

    template<typename Str, typename It, typename Enc1, typename Enc2>
    Str convert(Range<It> str, Enc1 fromEncoding, Enc2 toEncoding)
    {
        auto result = Str();
        append(makeStringReference(result), str, toEncoding, fromEncoding);
        return result;
    }

    namespace Detail {
        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendImpl(StringReference<Str> dst, Range<It> src,
                        Enc1 dstEncoding, Enc2 srcEncoding,
                        std::true_type)
        {
            auto appender = dst.getAppender();
            appender.append(src);
            dst.terminate();
        }

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendImpl(StringReference<Str> dst, Range<It> src,
                        Enc1 dstEncoding, Enc2 srcEncoding,
                        std::false_type)
        {
            appendWithEncoder(dst, src, dstEncoding, srcEncoding,
                              IsByteString<Str>());
            dst.terminate();
        }

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                               Enc1 dstEncoding, Enc2 srcEncoding,
                               std::true_type)
        {
            appendBytes(dst.getEncoder(dstEncoding),
                        Encoded::makeForwardDecoder(src, srcEncoding));
            dst.terminate();
        }

        template<typename Str, typename It, typename Enc1, typename Enc2>
        void appendWithEncoder(StringReference<Str> dst, Range<It> src,
                               Enc1 dstEncoding, Enc2 srcEncoding,
                               std::false_type)
        {
            append(dst.getEncoder(dstEncoding),
                   Encoded::makeForwardDecoder(src, srcEncoding));
            dst.terminate();
        }
    }
}}
