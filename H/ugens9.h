/*  
    ugens9.h:

    Copyright (C) 1996 Greg Sullivan

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

/*                                                              UGENS9.H    */

#include "fft.h"

typedef struct {
    OPDS    h;
    MYFLT   *ar1,*ar2,*ar3,*ar4,*ain,*ifilno,*channel;
    MEMFIL  *mfp;
    long    Hlen, Hlenpadded,incount,outcnt,obufsiz;
    int     nchanls; /* number of channels we are actually processing */
    MYFLT   *H,*cvlut,*outhead,*outail,*obufend;
    AUXCH   auxch;    /* use AUXDS to manage the following buffer spaces */
    MYFLT   *fftbuf;  /* [Hlenpadded + 2] (general FFT working buffer) */
    MYFLT   *olap;    /* [(Hlen - 1) * nchnls] (samples to overlap on next run) */
    MYFLT   *outbuf;  /* (to store output audio if
                        ((Hlen > ksmps) && !(multiple of ksmps)), or
                        ((Hlen < ksmps) && !(submultiple of ksmps)) */
    MYFLT   *X;       /* [Hlenpadded + 2] (holds transform of input audio -
                         only required for multi-channel output)   */
} CONVOLVE;

typedef struct {
    OPDS    h;
    MYFLT   *ar1, *ar2, *ar3, *ar4, *ain,*ifilno,*partitionSize,*channel;
    long    numPartitions;
    long    Hlen, Hlenpadded;
    int     nchanls;    /* number of channels we are actually processing */
    complex *cvlut;             /* lookup table used for fft */

    AUXCH   H;                  /* array of Impulse Responses */

    AUXCH   savedInput; /* the last Hlen input samps for overlap-save method */
    long    inCount;    /* index to write to savedInput */

    AUXCH   workBuf;    /* work buf for current partion convolution */
    MYFLT   *workWrite; /* current index for writing input samps */

    AUXCH   convBuf;    /* circular buf accumulating partitioned convolutions */
    long    curPart;    /* "current" segment in convBuf */

    AUXCH   output;             /* circular buf accumulating output samples */
    long    outBufSiz;  /* hlenpadded or 2*ksmps, whichever is greater */
    MYFLT   *outWrite, *outRead; /* i/o pointers to the output buf */
    long    outCount;   /* number of valid samples in the outbuf */
} PCONVOLVE;
