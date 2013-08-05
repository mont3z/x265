/*****************************************************************************
 * Copyright (C) 2013 x265 project
 *
 * Authors: Gopu Govindaswamy <gopu@multicorewareinc.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@multicorewareinc.com.
 *****************************************************************************/

#include "x265.h"
#include "common.h"
#include "mv.h"

namespace x265 {
class ReferencePlanes;

#define X265_BFRAME_MAX 16

struct LookaheadFrame : public ReferencePlanes
{
    /* lowres buffers, sizes and strides */
    pixel *buffer[4];
    int    stride;
    int    width;
    int    lines;

    /* lookahead output data */
    int       costEst[X265_BFRAME_MAX + 2][X265_BFRAME_MAX + 2];
    int      *rowSatds[X265_BFRAME_MAX + 2][X265_BFRAME_MAX + 2];
    int       intraMbs[X265_BFRAME_MAX + 2];
    uint16_t(*lowresCosts[X265_BFRAME_MAX + 2][X265_BFRAME_MAX + 2]);
    int      *lowresMvCosts[2][X265_BFRAME_MAX + 1];
    MV       *lowresMvs[2][X265_BFRAME_MAX + 1];
};

struct Lookahead
{
    LookaheadFrame *frames;
    int             bframes;            // from param->bframes
    int             frameQueueSize;     // from param->rcLookahead (--rc-lookahead)
    int             bAdaptMode;         // from param->bAdaptMode (--b-adapt 0-none, 1-simple, 2-trellis)

    TComList<TComPic*> inputQueue;      // input pictures in order received
    TComList<TComPic*> outputQueue;     // pictures to be encoded, in encode order
};

}