/*
 * Copyright (c) 2002 Light Weight Java Game Library Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of 'Light Weight Java Game Library' nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * $Id$
 *
 * Win32 math library.
 *
 * @author cix_foo <cix_foo@users.sourceforge.net>
 * @version $Revision$
 */

#include <windows.h>
#include "org_lwjgl_Math_MatrixOpSubtract_MatrixOpSafe.h"
#include "MatrixOpCommon.h"
#include <cmath>

using namespace std;

/*
 * Class:     org_lwjgl_Math_MatrixOpNormalise_MatrixOpSafe
 * Method:    execute
 * Signature: (IIIIIZIIZ)V
 */
JNIEXPORT void JNICALL Java_org_lwjgl_Math_00024MatrixOpNormalise_00024MatrixOpSafe_execute
  (
	JNIEnv * env,
	jobject obj,
	jint sourceAddress,
	jint sourceStride,
	jint numElements,
	jint sourceWidth,
	jint sourceHeight,
	jboolean transposeSource,
	jint destAddress,
	jint destStride,
	jboolean transposeDest
  )
{
        SrcMatrix source  (sourceAddress, sourceStride, sourceWidth,  sourceHeight, numElements,    transposeSource);
        DstMatrix dest  (destAddress,     destStride,   source.width, source.height, source.elements, transposeDest);
        
        float * sourceRecord, * destRecord;
        float magnitude, magnitude_squared;
        
        int i;
        register int j;
        
        for (i = 0; i < source.elements; i++)
        {
        
            magnitude_squared = 0;
            sourceRecord = source.nextRecord();
            destRecord = dest.nextRecord();
            
            for (j = 0 ; j < sourceWidth*sourceHeight; i++)
                magnitude_squared += sourceRecord[j] * sourceRecord[j];
                
            magnitude = (float) sqrt((double) magnitude_squared);
                
            for (j = 0; j < sourceWidth*sourceHeight; i++)
                destRecord[j] = sourceRecord[j] / magnitude;
            
            dest.writeRecord();
        }
}
