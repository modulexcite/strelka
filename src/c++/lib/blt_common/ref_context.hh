// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Strelka - Small Variant Caller
// Copyright (c) 2009-2017 Illumina, Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//

///
/// \author Chris Saunders
///

#pragma once

#include "blt_util/blt_types.hh"
#include "blt_util/reference_contig_segment.hh"


/// get size of hpol from the current position, given that this
/// is the left-most position in the hpol, otherwise, return 1
unsigned
get_left_shifted_hpol_size(
    const pos_t pos,
    const reference_contig_segment& ref);

/// checks whether the current position is the left end of an STR track
/// includes shorter repeat sizes which have valid [patternSize] repetitions
bool
isLeftEndOfSTR(
    const unsigned patternSize,
    const pos_t pos,
    const reference_contig_segment& ref);

/// get repeat count of the STR from the current position, given that this
/// is the left-most position in the STR track, otherwise, return 1
/// includes shorter repeat sizes which have valid [patternSize] repetitions
unsigned
getLeftShiftedSTRRepeatCount(
    const unsigned patternSize,
    const pos_t startPosition,
    const reference_contig_segment& ref);

/// compare repeatPatternSize number of bases between two positions in the ref
bool
compareRepeatPattern(
    const unsigned repeatPatternSize,
    const unsigned pos1,
    const unsigned pos2,
    const reference_contig_segment& ref);

/// searches for an STR track around the base
void searchForSTR(
    const unsigned patternSize,
    const unsigned pos,
    bool& isBaseInStr,
    bool& isBaseLeftEndOfStr,
    const reference_contig_segment& ref);

/// Get the length of the longest homopolymer containing the current
/// position if this position can be treated as any base.
///
unsigned
get_snp_hpol_size(const pos_t pos,
                  const reference_contig_segment& ref);

/// find the largest homopolymer extending from pos where one
/// occurrence of an alternate base is allowed
///
unsigned
get_interrupted_hpol_size(
    const pos_t pos,
    const reference_contig_segment& ref);
