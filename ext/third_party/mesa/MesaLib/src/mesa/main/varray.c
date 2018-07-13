/*
 * Mesa 3-D graphics library
 * Version:  7.6
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
 * Copyright (C) 2009  VMware, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#include "glheader.h"
#include "imports.h"
#include "bufferobj.h"
#include "context.h"
#include "enable.h"
#include "enums.h"
#include "hash.h"
#include "macros.h"
#include "mtypes.h"
#include "varray.h"
#include "arrayobj.h"
#include "main/dispatch.h"


/**
 * Set the fields of a vertex array.
 * Also do an error check for GL_ARB_vertex_array_object: check that
 * all arrays reside in VBOs when using a vertex array object.
 *
 * \param array  the array to update
 * \param dirtyBit  which bit to set in ctx->Array.NewState for this array
 * \param elementSize  size of each array element, in bytes
 * \param size  components per element (1, 2, 3 or 4)
 * \param type  datatype of each component (GL_FLOAT, GL_INT, etc)
 * \param format  either GL_RGBA or GL_BGRA
 * \param stride  stride between elements, in elements
 * \param normalized  are integer types converted to floats in [-1, 1]?
 * \param ptr  the address (or offset inside VBO) of the array data
 */
static void
update_array(GLcontext *ctx, struct gl_client_array *array,
             GLbitfield dirtyBit, GLsizei elementSize,
             GLint size, GLenum type, GLenum format,
             GLsizei stride, GLboolean normalized, const GLvoid *ptr)
{
   ASSERT(format == GL_RGBA || format == GL_BGRA);

   if (ctx->Array.ArrayObj->VBOonly &&
       ctx->Array.ArrayBufferObj->Name == 0) {
      /* GL_ARB_vertex_array_object requires that all arrays reside in VBOs.
       * Generate GL_INVALID_OPERATION if that's not true.
       */
      _mesa_error(ctx, GL_INVALID_OPERATION,
                  "glVertex/Normal/EtcPointer(non-VBO array)");
      return;
   }

   array->Size = size;
   array->Type = type;
   array->Format = format;
   array->Stride = stride;
   array->StrideB = stride ? stride : elementSize;
   array->Normalized = normalized;
   array->Ptr = (const GLubyte *) ptr;
   array->_ElementSize = elementSize;

   _mesa_reference_buffer_object(ctx, &array->BufferObj,
                                 ctx->Array.ArrayBufferObj);

   ctx->NewState |= _NEW_ARRAY;
   ctx->Array.NewState |= dirtyBit;
}


void GLAPIENTRY
_mesa_VertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (size < 2 || size > 4) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glVertexPointer(size)" );
      return;
   }
   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glVertexPointer(stride)" );
      return;
   }

   if (MESA_VERBOSE&(VERBOSE_VARRAY|VERBOSE_API))
      _mesa_debug(ctx, "glVertexPointer( sz %d type %s stride %d )\n", size,
                  _mesa_lookup_enum_by_nr( type ), stride);

   /* always need to check that <type> is legal */
   switch (type) {
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_INT:
         elementSize = size * sizeof(GLint);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = size * sizeof(GLhalfARB);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = size * sizeof(GLfixed);
         break;
#endif
#if FEATURE_vertex_array_byte
      case GL_BYTE:
         elementSize = size * sizeof(GLbyte);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glVertexPointer(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->Vertex, _NEW_ARRAY_VERTEX,
                elementSize, size, type, GL_RGBA, stride, GL_FALSE, ptr);
}


void GLAPIENTRY
_mesa_NormalPointer(GLenum type, GLsizei stride, const GLvoid *ptr )
{
   GLsizei elementSize;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glNormalPointer(stride)" );
      return;
   }

   if (MESA_VERBOSE&(VERBOSE_VARRAY|VERBOSE_API))
      _mesa_debug(ctx, "glNormalPointer( type %s stride %d )\n",
                  _mesa_lookup_enum_by_nr( type ), stride);

   switch (type) {
      case GL_BYTE:
         elementSize = 3 * sizeof(GLbyte);
         break;
      case GL_SHORT:
         elementSize = 3 * sizeof(GLshort);
         break;
      case GL_INT:
         elementSize = 3 * sizeof(GLint);
         break;
      case GL_FLOAT:
         elementSize = 3 * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = 3 * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = 3 * sizeof(GLhalfARB);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = 3 * sizeof(GLfixed);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glNormalPointer(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->Normal, _NEW_ARRAY_NORMAL,
                elementSize, 3, type, GL_RGBA, stride, GL_TRUE, ptr);
}


void GLAPIENTRY
_mesa_ColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GLenum format;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (size < 3 || size > 4) {
      if (!ctx->Extensions.EXT_vertex_array_bgra || size != GL_BGRA) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glColorPointer(size)");
         return;
      }
   }
   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glColorPointer(stride)" );
      return;
   }

   if (MESA_VERBOSE&(VERBOSE_VARRAY|VERBOSE_API))
      _mesa_debug(ctx, "glColorPointer( sz %d type %s stride %d )\n", size,
                  _mesa_lookup_enum_by_nr( type ), stride);

   if (size == GL_BGRA) {
      if (type != GL_UNSIGNED_BYTE) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glColorPointer(GL_BGRA/GLubyte)");
         return;
      }
      format = GL_BGRA;
      size = 4;
   }
   else {
      format = GL_RGBA;
   }

   switch (type) {
      case GL_BYTE:
         elementSize = size * sizeof(GLbyte);
         break;
      case GL_UNSIGNED_BYTE:
         elementSize = size * sizeof(GLubyte);
         break;
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_UNSIGNED_SHORT:
         elementSize = size * sizeof(GLushort);
         break;
      case GL_INT:
         elementSize = size * sizeof(GLint);
         break;
      case GL_UNSIGNED_INT:
         elementSize = size * sizeof(GLuint);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = size * sizeof(GLhalfARB);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = size * sizeof(GLfixed);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glColorPointer(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->Color, _NEW_ARRAY_COLOR0,
                elementSize, size, type, format, stride, GL_TRUE, ptr);
}


void GLAPIENTRY
_mesa_FogCoordPointerEXT(GLenum type, GLsizei stride, const GLvoid *ptr)
{
   GLint elementSize;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glFogCoordPointer(stride)" );
      return;
   }

   switch (type) {
      case GL_FLOAT:
         elementSize = sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = sizeof(GLhalfARB);
         break;
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glFogCoordPointer(type)" );
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->FogCoord, _NEW_ARRAY_FOGCOORD,
                elementSize, 1, type, GL_RGBA, stride, GL_FALSE, ptr);
}


void GLAPIENTRY
_mesa_IndexPointer(GLenum type, GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glIndexPointer(stride)" );
      return;
   }

   switch (type) {
      case GL_UNSIGNED_BYTE:
         elementSize = sizeof(GLubyte);
         break;
      case GL_SHORT:
         elementSize = sizeof(GLshort);
         break;
      case GL_INT:
         elementSize = sizeof(GLint);
         break;
      case GL_FLOAT:
         elementSize = sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = sizeof(GLdouble);
         break;
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glIndexPointer(type)" );
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->Index, _NEW_ARRAY_INDEX,
                elementSize, 1, type, GL_RGBA, stride, GL_FALSE, ptr);
}


void GLAPIENTRY
_mesa_SecondaryColorPointerEXT(GLint size, GLenum type,
			       GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GLenum format;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (size != 3 && size != 4) {
      if (!ctx->Extensions.EXT_vertex_array_bgra || size != GL_BGRA) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glSecondaryColorPointer(size)");
         return;
      }
   }
   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glSecondaryColorPointer(stride)" );
      return;
   }

   if (MESA_VERBOSE&(VERBOSE_VARRAY|VERBOSE_API))
      _mesa_debug(ctx, "glSecondaryColorPointer( sz %d type %s stride %d )\n",
                  size, _mesa_lookup_enum_by_nr( type ), stride);

   if (size == GL_BGRA) {
      if (type != GL_UNSIGNED_BYTE) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glColorPointer(GL_BGRA/GLubyte)");
         return;
      }
      format = GL_BGRA;
      size = 4;
   }
   else {
      format = GL_RGBA;
   }

   switch (type) {
      case GL_BYTE:
         elementSize = size * sizeof(GLbyte);
         break;
      case GL_UNSIGNED_BYTE:
         elementSize = size * sizeof(GLubyte);
         break;
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_UNSIGNED_SHORT:
         elementSize = size * sizeof(GLushort);
         break;
      case GL_INT:
         elementSize = size * sizeof(GLint);
         break;
      case GL_UNSIGNED_INT:
         elementSize = size * sizeof(GLuint);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = size * sizeof(GLhalfARB);
         break;
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glSecondaryColorPointer(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->SecondaryColor, _NEW_ARRAY_COLOR1,
                elementSize, size, type, format, stride, GL_TRUE, ptr);
}


void GLAPIENTRY
_mesa_TexCoordPointer(GLint size, GLenum type, GLsizei stride,
                      const GLvoid *ptr)
{
   GLint elementSize;
   GET_CURRENT_CONTEXT(ctx);
   const GLuint unit = ctx->Array.ActiveTexture;
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (size < 1 || size > 4) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glTexCoordPointer(size)" );
      return;
   }
   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glTexCoordPointer(stride)" );
      return;
   }

   if (MESA_VERBOSE&(VERBOSE_VARRAY|VERBOSE_API))
      _mesa_debug(ctx, "glTexCoordPointer(unit %u sz %d type %s stride %d)\n",
                  unit, size, _mesa_lookup_enum_by_nr( type ), stride);

   /* always need to check that <type> is legal */
   switch (type) {
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_INT:
         elementSize = size * sizeof(GLint);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = size * sizeof(GLhalfARB);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = size * sizeof(GLfixed);
         break;
#endif
#if FEATURE_vertex_array_byte
      case GL_BYTE:
         elementSize = size * sizeof(GLbyte);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glTexCoordPointer(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   ASSERT(unit < Elements(ctx->Array.ArrayObj->TexCoord));

   update_array(ctx, &ctx->Array.ArrayObj->TexCoord[unit],
                _NEW_ARRAY_TEXCOORD(unit),
                elementSize, size, type, GL_RGBA, stride, GL_FALSE, ptr);
}


void GLAPIENTRY
_mesa_EdgeFlagPointer(GLsizei stride, const GLvoid *ptr)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glEdgeFlagPointer(stride)" );
      return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->EdgeFlag, _NEW_ARRAY_EDGEFLAG,
                sizeof(GLboolean), 1, GL_UNSIGNED_BYTE, GL_RGBA,
                stride, GL_FALSE, ptr);
}


void GLAPIENTRY
_mesa_PointSizePointer(GLenum type, GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glPointSizePointer(stride)" );
      return;
   }

   switch (type) {
      case GL_FLOAT:
         elementSize = sizeof(GLfloat);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = sizeof(GLfixed);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glPointSizePointer(type)" );
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->PointSize, _NEW_ARRAY_POINT_SIZE,
                elementSize, 1, type, GL_RGBA, stride, GL_FALSE, ptr);
}


#if FEATURE_NV_vertex_program
/**
 * Set a vertex attribute array.
 * Note that these arrays DO alias the conventional GL vertex arrays
 * (position, normal, color, fog, texcoord, etc).
 * The generic attribute slots at #16 and above are not touched.
 */
void GLAPIENTRY
_mesa_VertexAttribPointerNV(GLuint index, GLint size, GLenum type,
                            GLsizei stride, const GLvoid *ptr)
{
   GLboolean normalized = GL_FALSE;
   GLsizei elementSize;
   GLenum format;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (index >= MAX_NV_VERTEX_PROGRAM_INPUTS) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerNV(index)");
      return;
   }

   if (size < 1 || size > 4) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerNV(size)");
      return;
   }

   if (stride < 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerNV(stride)");
      return;
   }

   if (type == GL_UNSIGNED_BYTE && size != 4) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerNV(size!=4)");
      return;
   }

   if (size == GL_BGRA) {
      if (type != GL_UNSIGNED_BYTE) {
         _mesa_error(ctx, GL_INVALID_VALUE,
                     "glVertexAttribPointerNV(GL_BGRA/type)");
         return;
      }

      format = GL_BGRA;
      size = 4;
      normalized = GL_TRUE;
   }
   else {
      format = GL_RGBA;
   }

   /* check for valid 'type' and compute StrideB right away */
   switch (type) {
      case GL_UNSIGNED_BYTE:
         normalized = GL_TRUE;
         elementSize = size * sizeof(GLubyte);
         break;
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glVertexAttribPointerNV(type=%s)",
                      _mesa_lookup_enum_by_nr(type));
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->VertexAttrib[index],
                _NEW_ARRAY_ATTRIB(index),
                elementSize, size, type, format, stride, normalized, ptr);
}
#endif


#if FEATURE_ARB_vertex_program
/**
 * Set a generic vertex attribute array.
 * Note that these arrays DO NOT alias the conventional GL vertex arrays
 * (position, normal, color, fog, texcoord, etc).
 */
void GLAPIENTRY
_mesa_VertexAttribPointerARB(GLuint index, GLint size, GLenum type,
                             GLboolean normalized,
                             GLsizei stride, const GLvoid *ptr)
{
   GLsizei elementSize;
   GLenum format;
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (index >= ctx->Const.VertexProgram.MaxAttribs) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerARB(index)");
      return;
   }

   if (size < 1 || size > 4) {
      if (!ctx->Extensions.EXT_vertex_array_bgra || size != GL_BGRA) {
         _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerARB(size)");
         return;
      }
   }

   if (stride < 0) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glVertexAttribPointerARB(stride)");
      return;
   }

   if (size == GL_BGRA) {
      if (type != GL_UNSIGNED_BYTE) {
         _mesa_error(ctx, GL_INVALID_VALUE,
                     "glVertexAttribPointerARB(GL_BGRA/type)");
         return;
      }
      if (normalized != GL_TRUE) {
         _mesa_error(ctx, GL_INVALID_VALUE,
                     "glVertexAttribPointerARB(GL_BGRA/normalized)");
         return;
      }

      format = GL_BGRA;
      size = 4;
   }
   else {
      format = GL_RGBA;
   }

   /* check for valid 'type' and compute StrideB right away */
   /* NOTE: more types are supported here than in the NV extension */
   switch (type) {
      case GL_BYTE:
         elementSize = size * sizeof(GLbyte);
         break;
      case GL_UNSIGNED_BYTE:
         elementSize = size * sizeof(GLubyte);
         break;
      case GL_SHORT:
         elementSize = size * sizeof(GLshort);
         break;
      case GL_UNSIGNED_SHORT:
         elementSize = size * sizeof(GLushort);
         break;
      case GL_INT:
         elementSize = size * sizeof(GLint);
         break;
      case GL_UNSIGNED_INT:
         elementSize = size * sizeof(GLuint);
         break;
      case GL_FLOAT:
         elementSize = size * sizeof(GLfloat);
         break;
      case GL_DOUBLE:
         elementSize = size * sizeof(GLdouble);
         break;
      case GL_HALF_FLOAT:
         elementSize = size * sizeof(GLhalfARB);
         break;
#if FEATURE_fixedpt
      case GL_FIXED:
         elementSize = size * sizeof(GLfixed);
         break;
#endif
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glVertexAttribPointerARB(type)" );
         return;
   }

   update_array(ctx, &ctx->Array.ArrayObj->VertexAttrib[index],
                _NEW_ARRAY_ATTRIB(index),
                elementSize, size, type, format, stride, normalized, ptr);
}
#endif


/**
 * New in GL3:
 * Set an integer-valued vertex attribute array.
 * Note that these arrays DO NOT alias the conventional GL vertex arrays
 * (position, normal, color, fog, texcoord, etc).
 */
void GLAPIENTRY
_mesa_VertexAttribIPointer(GLuint index, GLint size, GLenum type,
                           GLboolean normalized,
                           GLsizei stride, const GLvoid *ptr)
{
   /* NOTE: until we have integer-valued vertex attributes, just
    * route this through the regular glVertexAttribPointer() function.
    */
   _mesa_VertexAttribPointerARB(index, size, type, normalized, stride, ptr);
}



void GLAPIENTRY
_mesa_EnableVertexAttribArrayARB(GLuint index)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (index >= ctx->Const.VertexProgram.MaxAttribs) {
      _mesa_error(ctx, GL_INVALID_VALUE,
                  "glEnableVertexAttribArrayARB(index)");
      return;
   }

   ASSERT(index < Elements(ctx->Array.ArrayObj->VertexAttrib));

   FLUSH_VERTICES(ctx, _NEW_ARRAY);
   ctx->Array.ArrayObj->VertexAttrib[index].Enabled = GL_TRUE;
   ctx->Array.ArrayObj->_Enabled |= _NEW_ARRAY_ATTRIB(index);
   ctx->Array.NewState |= _NEW_ARRAY_ATTRIB(index);
}


void GLAPIENTRY
_mesa_DisableVertexAttribArrayARB(GLuint index)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (index >= ctx->Const.VertexProgram.MaxAttribs) {
      _mesa_error(ctx, GL_INVALID_VALUE,
                  "glEnableVertexAttribArrayARB(index)");
      return;
   }

   ASSERT(index < Elements(ctx->Array.ArrayObj->VertexAttrib));

   FLUSH_VERTICES(ctx, _NEW_ARRAY);
   ctx->Array.ArrayObj->VertexAttrib[index].Enabled = GL_FALSE;
   ctx->Array.ArrayObj->_Enabled &= ~_NEW_ARRAY_ATTRIB(index);
   ctx->Array.NewState |= _NEW_ARRAY_ATTRIB(index);
}


/**
 * Return info for a vertex attribute array (no alias with legacy
 * vertex attributes (pos, normal, color, etc)).  This function does
 * not handle the 4-element GL_CURRENT_VERTEX_ATTRIB_ARB query.
 */
static GLuint
get_vertex_array_attrib(GLcontext *ctx, GLuint index, GLenum pname,
                  const char *caller)
{
   const struct gl_client_array *array;

   if (index >= MAX_VERTEX_GENERIC_ATTRIBS) {
      _mesa_error(ctx, GL_INVALID_VALUE, "%s(index=%u)", caller, index);
      return 0;
   }

   ASSERT(index < Elements(ctx->Array.ArrayObj->VertexAttrib));

   array = &ctx->Array.ArrayObj->VertexAttrib[index];

   switch (pname) {
   case GL_VERTEX_ATTRIB_ARRAY_ENABLED_ARB:
      return array->Enabled;
   case GL_VERTEX_ATTRIB_ARRAY_SIZE_ARB:
      return array->Size;
   case GL_VERTEX_ATTRIB_ARRAY_STRIDE_ARB:
      return array->Stride;
   case GL_VERTEX_ATTRIB_ARRAY_TYPE_ARB:
      return array->Type;
   case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED_ARB:
      return array->Normalized;
   case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB:
      return array->BufferObj->Name;
   default:
      _mesa_error(ctx, GL_INVALID_ENUM, "%s(pname=0x%x)", caller, pname);
      return 0;
   }
}


void GLAPIENTRY
_mesa_GetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat *params)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      if (index == 0) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetVertexAttribfv(index==0)");
      }
      else {
         const GLfloat *v = ctx->Current.Attrib[VERT_ATTRIB_GENERIC0 + index];
         FLUSH_CURRENT(ctx, 0);
         COPY_4V(params, v);
      }
   }
   else {
      params[0] = (GLfloat) get_vertex_array_attrib(ctx, index, pname,
                                                    "glGetVertexAttribfv");
   }
}


void GLAPIENTRY
_mesa_GetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble *params)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      if (index == 0) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetVertexAttribdv(index==0)");
      }
      else {
         const GLfloat *v = ctx->Current.Attrib[VERT_ATTRIB_GENERIC0 + index];
         FLUSH_CURRENT(ctx, 0);
         params[0] = (GLdouble) v[0];
         params[1] = (GLdouble) v[1];
         params[2] = (GLdouble) v[2];
         params[3] = (GLdouble) v[3];
      }
   }
   else {
      params[0] = (GLdouble) get_vertex_array_attrib(ctx, index, pname,
                                                     "glGetVertexAttribdv");
   }
}


void GLAPIENTRY
_mesa_GetVertexAttribivARB(GLuint index, GLenum pname, GLint *params)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      if (index == 0) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetVertexAttribiv(index==0)");
      }
      else {
         const GLfloat *v = ctx->Current.Attrib[VERT_ATTRIB_GENERIC0 + index];
         FLUSH_CURRENT(ctx, 0);
         /* XXX should floats in[0,1] be scaled to full int range? */
         params[0] = (GLint) v[0];
         params[1] = (GLint) v[1];
         params[2] = (GLint) v[2];
         params[3] = (GLint) v[3];
      }
   }
   else {
      params[0] = (GLint) get_vertex_array_attrib(ctx, index, pname,
                                                  "glGetVertexAttribiv");
   }
}


/** GL 3.0 */
void GLAPIENTRY
_mesa_GetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      if (index == 0) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetVertexAttribIiv(index==0)");
      }
      else {
         const GLfloat *v = ctx->Current.Attrib[VERT_ATTRIB_GENERIC0 + index];
         FLUSH_CURRENT(ctx, 0);
         /* XXX we don't have true integer-valued vertex attribs yet */
         params[0] = (GLint) v[0];
         params[1] = (GLint) v[1];
         params[2] = (GLint) v[2];
         params[3] = (GLint) v[3];
      }
   }
   else {
      params[0] = (GLint) get_vertex_array_attrib(ctx, index, pname,
                                                  "glGetVertexAttribIiv");
   }
}


/** GL 3.0 */
void GLAPIENTRY
_mesa_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (pname == GL_CURRENT_VERTEX_ATTRIB_ARB) {
      if (index == 0) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetVertexAttribIuiv(index==0)");
      }
      else {
         const GLfloat *v = ctx->Current.Attrib[VERT_ATTRIB_GENERIC0 + index];
         FLUSH_CURRENT(ctx, 0);
         /* XXX we don't have true integer-valued vertex attribs yet */
         params[0] = (GLuint) v[0];
         params[1] = (GLuint) v[1];
         params[2] = (GLuint) v[2];
         params[3] = (GLuint) v[3];
      }
   }
   else {
      params[0] = get_vertex_array_attrib(ctx, index, pname,
                                          "glGetVertexAttribIuiv");
   }
}


void GLAPIENTRY
_mesa_GetVertexAttribPointervARB(GLuint index, GLenum pname, GLvoid **pointer)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END(ctx);

   if (index >= ctx->Const.VertexProgram.MaxAttribs) {
      _mesa_error(ctx, GL_INVALID_VALUE, "glGetVertexAttribPointerARB(index)");
      return;
   }

   if (pname != GL_VERTEX_ATTRIB_ARRAY_POINTER_ARB) {
      _mesa_error(ctx, GL_INVALID_ENUM, "glGetVertexAttribPointerARB(pname)");
      return;
   }

   ASSERT(index < Elements(ctx->Array.ArrayObj->VertexAttrib));

   *pointer = (GLvoid *) ctx->Array.ArrayObj->VertexAttrib[index].Ptr;
}


void GLAPIENTRY
_mesa_VertexPointerEXT(GLint size, GLenum type, GLsizei stride,
                       GLsizei count, const GLvoid *ptr)
{
   (void) count;
   _mesa_VertexPointer(size, type, stride, ptr);
}


void GLAPIENTRY
_mesa_NormalPointerEXT(GLenum type, GLsizei stride, GLsizei count,
                       const GLvoid *ptr)
{
   (void) count;
   _mesa_NormalPointer(type, stride, ptr);
}


void GLAPIENTRY
_mesa_ColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count,
                      const GLvoid *ptr)
{
   (void) count;
   _mesa_ColorPointer(size, type, stride, ptr);
}


void GLAPIENTRY
_mesa_IndexPointerEXT(GLenum type, GLsizei stride, GLsizei count,
                      const GLvoid *ptr)
{
   (void) count;
   _mesa_IndexPointer(type, stride, ptr);
}


void GLAPIENTRY
_mesa_TexCoordPointerEXT(GLint size, GLenum type, GLsizei stride,
                         GLsizei count, const GLvoid *ptr)
{
   (void) count;
   _mesa_TexCoordPointer(size, type, stride, ptr);
}


void GLAPIENTRY
_mesa_EdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean *ptr)
{
   (void) count;
   _mesa_EdgeFlagPointer(stride, ptr);
}


void GLAPIENTRY
_mesa_InterleavedArrays(GLenum format, GLsizei stride, const GLvoid *pointer)
{
   GET_CURRENT_CONTEXT(ctx);
   GLboolean tflag, cflag, nflag;  /* enable/disable flags */
   GLint tcomps, ccomps, vcomps;   /* components per texcoord, color, vertex */
   GLenum ctype = 0;               /* color type */
   GLint coffset = 0, noffset = 0, voffset;/* color, normal, vertex offsets */
   const GLint toffset = 0;        /* always zero */
   GLint defstride;                /* default stride */
   GLint c, f;

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   f = sizeof(GLfloat);
   c = f * ((4 * sizeof(GLubyte) + (f - 1)) / f);

   if (stride < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glInterleavedArrays(stride)" );
      return;
   }

   switch (format) {
      case GL_V2F:
         tflag = GL_FALSE;  cflag = GL_FALSE;  nflag = GL_FALSE;
         tcomps = 0;  ccomps = 0;  vcomps = 2;
         voffset = 0;
         defstride = 2*f;
         break;
      case GL_V3F:
         tflag = GL_FALSE;  cflag = GL_FALSE;  nflag = GL_FALSE;
         tcomps = 0;  ccomps = 0;  vcomps = 3;
         voffset = 0;
         defstride = 3*f;
         break;
      case GL_C4UB_V2F:
         tflag = GL_FALSE;  cflag = GL_TRUE;  nflag = GL_FALSE;
         tcomps = 0;  ccomps = 4;  vcomps = 2;
         ctype = GL_UNSIGNED_BYTE;
         coffset = 0;
         voffset = c;
         defstride = c + 2*f;
         break;
      case GL_C4UB_V3F:
         tflag = GL_FALSE;  cflag = GL_TRUE;  nflag = GL_FALSE;
         tcomps = 0;  ccomps = 4;  vcomps = 3;
         ctype = GL_UNSIGNED_BYTE;
         coffset = 0;
         voffset = c;
         defstride = c + 3*f;
         break;
      case GL_C3F_V3F:
         tflag = GL_FALSE;  cflag = GL_TRUE;  nflag = GL_FALSE;
         tcomps = 0;  ccomps = 3;  vcomps = 3;
         ctype = GL_FLOAT;
         coffset = 0;
         voffset = 3*f;
         defstride = 6*f;
         break;
      case GL_N3F_V3F:
         tflag = GL_FALSE;  cflag = GL_FALSE;  nflag = GL_TRUE;
         tcomps = 0;  ccomps = 0;  vcomps = 3;
         noffset = 0;
         voffset = 3*f;
         defstride = 6*f;
         break;
      case GL_C4F_N3F_V3F:
         tflag = GL_FALSE;  cflag = GL_TRUE;  nflag = GL_TRUE;
         tcomps = 0;  ccomps = 4;  vcomps = 3;
         ctype = GL_FLOAT;
         coffset = 0;
         noffset = 4*f;
         voffset = 7*f;
         defstride = 10*f;
         break;
      case GL_T2F_V3F:
         tflag = GL_TRUE;  cflag = GL_FALSE;  nflag = GL_FALSE;
         tcomps = 2;  ccomps = 0;  vcomps = 3;
         voffset = 2*f;
         defstride = 5*f;
         break;
      case GL_T4F_V4F:
         tflag = GL_TRUE;  cflag = GL_FALSE;  nflag = GL_FALSE;
         tcomps = 4;  ccomps = 0;  vcomps = 4;
         voffset = 4*f;
         defstride = 8*f;
         break;
      case GL_T2F_C4UB_V3F:
         tflag = GL_TRUE;  cflag = GL_TRUE;  nflag = GL_FALSE;
         tcomps = 2;  ccomps = 4;  vcomps = 3;
         ctype = GL_UNSIGNED_BYTE;
         coffset = 2*f;
         voffset = c+2*f;
         defstride = c+5*f;
         break;
      case GL_T2F_C3F_V3F:
         tflag = GL_TRUE;  cflag = GL_TRUE;  nflag = GL_FALSE;
         tcomps = 2;  ccomps = 3;  vcomps = 3;
         ctype = GL_FLOAT;
         coffset = 2*f;
         voffset = 5*f;
         defstride = 8*f;
         break;
      case GL_T2F_N3F_V3F:
         tflag = GL_TRUE;  cflag = GL_FALSE;  nflag = GL_TRUE;
         tcomps = 2;  ccomps = 0;  vcomps = 3;
         noffset = 2*f;
         voffset = 5*f;
         defstride = 8*f;
         break;
      case GL_T2F_C4F_N3F_V3F:
         tflag = GL_TRUE;  cflag = GL_TRUE;  nflag = GL_TRUE;
         tcomps = 2;  ccomps = 4;  vcomps = 3;
         ctype = GL_FLOAT;
         coffset = 2*f;
         noffset = 6*f;
         voffset = 9*f;
         defstride = 12*f;
         break;
      case GL_T4F_C4F_N3F_V4F:
         tflag = GL_TRUE;  cflag = GL_TRUE;  nflag = GL_TRUE;
         tcomps = 4;  ccomps = 4;  vcomps = 4;
         ctype = GL_FLOAT;
         coffset = 4*f;
         noffset = 8*f;
         voffset = 11*f;
         defstride = 15*f;
         break;
      default:
         _mesa_error( ctx, GL_INVALID_ENUM, "glInterleavedArrays(format)" );
         return;
   }

   if (stride==0) {
      stride = defstride;
   }

   _mesa_DisableClientState( GL_EDGE_FLAG_ARRAY );
   _mesa_DisableClientState( GL_INDEX_ARRAY );
   /* XXX also disable secondary color and generic arrays? */

   /* Texcoords */
   if (tflag) {
      _mesa_EnableClientState( GL_TEXTURE_COORD_ARRAY );
      _mesa_TexCoordPointer( tcomps, GL_FLOAT, stride,
                             (GLubyte *) pointer + toffset );
   }
   else {
      _mesa_DisableClientState( GL_TEXTURE_COORD_ARRAY );
   }

   /* Color */
   if (cflag) {
      _mesa_EnableClientState( GL_COLOR_ARRAY );
      _mesa_ColorPointer( ccomps, ctype, stride,
			  (GLubyte *) pointer + coffset );
   }
   else {
      _mesa_DisableClientState( GL_COLOR_ARRAY );
   }


   /* Normals */
   if (nflag) {
      _mesa_EnableClientState( GL_NORMAL_ARRAY );
      _mesa_NormalPointer( GL_FLOAT, stride, (GLubyte *) pointer + noffset );
   }
   else {
      _mesa_DisableClientState( GL_NORMAL_ARRAY );
   }

   /* Vertices */
   _mesa_EnableClientState( GL_VERTEX_ARRAY );
   _mesa_VertexPointer( vcomps, GL_FLOAT, stride,
			(GLubyte *) pointer + voffset );
}


void GLAPIENTRY
_mesa_LockArraysEXT(GLint first, GLsizei count)
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glLockArrays %d %d\n", first, count);

   if (first < 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glLockArraysEXT(first)" );
      return;
   }
   if (count <= 0) {
      _mesa_error( ctx, GL_INVALID_VALUE, "glLockArraysEXT(count)" );
      return;
   }
   if (ctx->Array.LockCount != 0) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glLockArraysEXT(reentry)" );
      return;
   }

   ctx->Array.LockFirst = first;
   ctx->Array.LockCount = count;

   ctx->NewState |= _NEW_ARRAY;
   ctx->Array.NewState |= _NEW_ARRAY_ALL;
}


void GLAPIENTRY
_mesa_UnlockArraysEXT( void )
{
   GET_CURRENT_CONTEXT(ctx);
   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glUnlockArrays\n");

   if (ctx->Array.LockCount == 0) {
      _mesa_error( ctx, GL_INVALID_OPERATION, "glUnlockArraysEXT(reexit)" );
      return;
   }

   ctx->Array.LockFirst = 0;
   ctx->Array.LockCount = 0;
   ctx->NewState |= _NEW_ARRAY;
   ctx->Array.NewState |= _NEW_ARRAY_ALL;
}


/* GL_EXT_multi_draw_arrays */
/* Somebody forgot to spec the first and count parameters as const! <sigh> */
void GLAPIENTRY
_mesa_MultiDrawArraysEXT( GLenum mode, const GLint *first,
                          const GLsizei *count, GLsizei primcount )
{
   GET_CURRENT_CONTEXT(ctx);
   GLint i;

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   for (i = 0; i < primcount; i++) {
      if (count[i] > 0) {
         CALL_DrawArrays(ctx->Exec, (mode, first[i], count[i]));
      }
   }
}


/* GL_IBM_multimode_draw_arrays */
void GLAPIENTRY
_mesa_MultiModeDrawArraysIBM( const GLenum * mode, const GLint * first,
			      const GLsizei * count,
			      GLsizei primcount, GLint modestride )
{
   GET_CURRENT_CONTEXT(ctx);
   GLint i;

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   for ( i = 0 ; i < primcount ; i++ ) {
      if ( count[i] > 0 ) {
         GLenum m = *((GLenum *) ((GLubyte *) mode + i * modestride));
	 CALL_DrawArrays(ctx->Exec, ( m, first[i], count[i] ));
      }
   }
}


/* GL_IBM_multimode_draw_arrays */
void GLAPIENTRY
_mesa_MultiModeDrawElementsIBM( const GLenum * mode, const GLsizei * count,
				GLenum type, const GLvoid * const * indices,
				GLsizei primcount, GLint modestride )
{
   GET_CURRENT_CONTEXT(ctx);
   GLint i;

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   /* XXX not sure about ARB_vertex_buffer_object handling here */

   for ( i = 0 ; i < primcount ; i++ ) {
      if ( count[i] > 0 ) {
         GLenum m = *((GLenum *) ((GLubyte *) mode + i * modestride));
	 CALL_DrawElements(ctx->Exec, ( m, count[i], type, indices[i] ));
      }
   }
}


/**
 * GL 3.1 glPrimitiveRestartIndex().
 */
void GLAPIENTRY
_mesa_PrimitiveRestartIndex(GLuint index)
{
   GET_CURRENT_CONTEXT(ctx);

   if (ctx->VersionMajor * 10 + ctx->VersionMinor < 31) {
      _mesa_error(ctx, GL_INVALID_OPERATION, "glPrimitiveRestartIndex()");
      return;
   }

   ASSERT_OUTSIDE_BEGIN_END_AND_FLUSH(ctx);

   FLUSH_VERTICES(ctx, _NEW_TRANSFORM);

   ctx->Array.RestartIndex = index;
}


/**
 * Copy one client vertex array to another.
 */
void
_mesa_copy_client_array(GLcontext *ctx,
                        struct gl_client_array *dst,
                        struct gl_client_array *src)
{
   dst->Size = src->Size;
   dst->Type = src->Type;
   dst->Format = src->Format;
   dst->Stride = src->Stride;
   dst->StrideB = src->StrideB;
   dst->Ptr = src->Ptr;
   dst->Enabled = src->Enabled;
   dst->Normalized = src->Normalized;
   dst->_ElementSize = src->_ElementSize;
   _mesa_reference_buffer_object(ctx, &dst->BufferObj, src->BufferObj);
   dst->_MaxElement = src->_MaxElement;
}



/**
 * Print vertex array's fields.
 */
static void
print_array(const char *name, GLint index, const struct gl_client_array *array)
{
   if (index >= 0)
      printf("  %s[%d]: ", name, index);
   else
      printf("  %s: ", name);
   printf("Ptr=%p, Type=0x%x, Size=%d, ElemSize=%u, Stride=%d, Buffer=%u(Size %lu), MaxElem=%u\n",
	  array->Ptr, array->Type, array->Size,
	  array->_ElementSize, array->StrideB,
	  array->BufferObj->Name, (unsigned long) array->BufferObj->Size,
	  array->_MaxElement);
}


/**
 * Print current vertex object/array info.  For debug.
 */
void
_mesa_print_arrays(GLcontext *ctx)
{
   struct gl_array_object *arrayObj = ctx->Array.ArrayObj;
   GLuint i;

   _mesa_update_array_object_max_element(ctx, arrayObj);

   printf("Array Object %u\n", arrayObj->Name);
   if (arrayObj->Vertex.Enabled)
      print_array("Vertex", -1, &arrayObj->Vertex);
   if (arrayObj->Normal.Enabled)
      print_array("Normal", -1, &arrayObj->Normal);
   if (arrayObj->Color.Enabled)
      print_array("Color", -1, &arrayObj->Color);
   for (i = 0; i < Elements(arrayObj->TexCoord); i++)
      if (arrayObj->TexCoord[i].Enabled)
         print_array("TexCoord", i, &arrayObj->TexCoord[i]);
   for (i = 0; i < Elements(arrayObj->VertexAttrib); i++)
      if (arrayObj->VertexAttrib[i].Enabled)
         print_array("Attrib", i, &arrayObj->VertexAttrib[i]);
   printf("  _MaxElement = %u\n", arrayObj->_MaxElement);
}


/**
 * Initialize vertex array state for given context.
 */
void 
_mesa_init_varray(GLcontext *ctx)
{
   ctx->Array.DefaultArrayObj = _mesa_new_array_object(ctx, 0);
   _mesa_reference_array_object(ctx, &ctx->Array.ArrayObj,
                                ctx->Array.DefaultArrayObj);
   ctx->Array.ActiveTexture = 0;   /* GL_ARB_multitexture */

   ctx->Array.Objects = _mesa_NewHashTable();
}


/**
 * Callback for deleting an array object.  Called by _mesa_HashDeleteAll().
 */
static void
delete_arrayobj_cb(GLuint id, void *data, void *userData)
{
   struct gl_array_object *arrayObj = (struct gl_array_object *) data;
   GLcontext *ctx = (GLcontext *) userData;
   _mesa_delete_array_object(ctx, arrayObj);
}


/**
 * Free vertex array state for given context.
 */
void 
_mesa_free_varray_data(GLcontext *ctx)
{
   _mesa_HashDeleteAll(ctx->Array.Objects, delete_arrayobj_cb, ctx);
   _mesa_DeleteHashTable(ctx->Array.Objects);
}
