#include <assert.h>
#include <string.h>

#include "json.hpp"
#include "scoped_allocator.hpp"
#include "glproc.hpp"
#include "glsize.hpp"
#include "glstate.hpp"
#include "glstate_internal.hpp"

namespace glstate {

static void
flushErrors(void) {
    while (glGetError() != GL_NO_ERROR) {}
}

void
dumpBoolean(JSONWriter &json, GLboolean value)
{
    switch (value) {
    case GL_FALSE:
        json.writeString("GL_FALSE");
        break;
    case GL_TRUE:
        json.writeString("GL_TRUE");
        break;
    default:
        json.writeInt(static_cast<GLint>(value));
        break;
    }
}

const char *
enumToString(GLenum pname)
{
    switch (pname) {
    case GL_ZERO:
        return "GL_ZERO";
    case GL_ONE:
        return "GL_ONE";
    case GL_ACCUM:
        return "GL_ACCUM";
    case GL_LOAD:
        return "GL_LOAD";
    case GL_RETURN:
        return "GL_RETURN";
    case GL_MULT:
        return "GL_MULT";
    case GL_ADD:
        return "GL_ADD";
    case GL_NEVER:
        return "GL_NEVER";
    case GL_LESS:
        return "GL_LESS";
    case GL_EQUAL:
        return "GL_EQUAL";
    case GL_LEQUAL:
        return "GL_LEQUAL";
    case GL_GREATER:
        return "GL_GREATER";
    case GL_NOTEQUAL:
        return "GL_NOTEQUAL";
    case GL_GEQUAL:
        return "GL_GEQUAL";
    case GL_ALWAYS:
        return "GL_ALWAYS";
    case GL_SRC_COLOR:
        return "GL_SRC_COLOR";
    case GL_ONE_MINUS_SRC_COLOR:
        return "GL_ONE_MINUS_SRC_COLOR";
    case GL_SRC_ALPHA:
        return "GL_SRC_ALPHA";
    case GL_ONE_MINUS_SRC_ALPHA:
        return "GL_ONE_MINUS_SRC_ALPHA";
    case GL_DST_ALPHA:
        return "GL_DST_ALPHA";
    case GL_ONE_MINUS_DST_ALPHA:
        return "GL_ONE_MINUS_DST_ALPHA";
    case GL_DST_COLOR:
        return "GL_DST_COLOR";
    case GL_ONE_MINUS_DST_COLOR:
        return "GL_ONE_MINUS_DST_COLOR";
    case GL_SRC_ALPHA_SATURATE:
        return "GL_SRC_ALPHA_SATURATE";
    case GL_FRONT_LEFT:
        return "GL_FRONT_LEFT";
    case GL_FRONT_RIGHT:
        return "GL_FRONT_RIGHT";
    case GL_BACK_LEFT:
        return "GL_BACK_LEFT";
    case GL_BACK_RIGHT:
        return "GL_BACK_RIGHT";
    case GL_FRONT:
        return "GL_FRONT";
    case GL_BACK:
        return "GL_BACK";
    case GL_LEFT:
        return "GL_LEFT";
    case GL_RIGHT:
        return "GL_RIGHT";
    case GL_FRONT_AND_BACK:
        return "GL_FRONT_AND_BACK";
    case GL_AUX0:
        return "GL_AUX0";
    case GL_AUX1:
        return "GL_AUX1";
    case GL_AUX2:
        return "GL_AUX2";
    case GL_AUX3:
        return "GL_AUX3";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_2D:
        return "GL_2D";
    case GL_3D:
        return "GL_3D";
    case GL_3D_COLOR:
        return "GL_3D_COLOR";
    case GL_3D_COLOR_TEXTURE:
        return "GL_3D_COLOR_TEXTURE";
    case GL_4D_COLOR_TEXTURE:
        return "GL_4D_COLOR_TEXTURE";
    case GL_PASS_THROUGH_TOKEN:
        return "GL_PASS_THROUGH_TOKEN";
    case GL_POINT_TOKEN:
        return "GL_POINT_TOKEN";
    case GL_LINE_TOKEN:
        return "GL_LINE_TOKEN";
    case GL_POLYGON_TOKEN:
        return "GL_POLYGON_TOKEN";
    case GL_BITMAP_TOKEN:
        return "GL_BITMAP_TOKEN";
    case GL_DRAW_PIXEL_TOKEN:
        return "GL_DRAW_PIXEL_TOKEN";
    case GL_COPY_PIXEL_TOKEN:
        return "GL_COPY_PIXEL_TOKEN";
    case GL_LINE_RESET_TOKEN:
        return "GL_LINE_RESET_TOKEN";
    case GL_EXP:
        return "GL_EXP";
    case GL_EXP2:
        return "GL_EXP2";
    case GL_CW:
        return "GL_CW";
    case GL_CCW:
        return "GL_CCW";
    case GL_COEFF:
        return "GL_COEFF";
    case GL_ORDER:
        return "GL_ORDER";
    case GL_DOMAIN:
        return "GL_DOMAIN";
    case GL_CURRENT_COLOR:
        return "GL_CURRENT_COLOR";
    case GL_CURRENT_INDEX:
        return "GL_CURRENT_INDEX";
    case GL_CURRENT_NORMAL:
        return "GL_CURRENT_NORMAL";
    case GL_CURRENT_TEXTURE_COORDS:
        return "GL_CURRENT_TEXTURE_COORDS";
    case GL_CURRENT_RASTER_COLOR:
        return "GL_CURRENT_RASTER_COLOR";
    case GL_CURRENT_RASTER_INDEX:
        return "GL_CURRENT_RASTER_INDEX";
    case GL_CURRENT_RASTER_TEXTURE_COORDS:
        return "GL_CURRENT_RASTER_TEXTURE_COORDS";
    case GL_CURRENT_RASTER_POSITION:
        return "GL_CURRENT_RASTER_POSITION";
    case GL_CURRENT_RASTER_POSITION_VALID:
        return "GL_CURRENT_RASTER_POSITION_VALID";
    case GL_CURRENT_RASTER_DISTANCE:
        return "GL_CURRENT_RASTER_DISTANCE";
    case GL_POINT_SMOOTH:
        return "GL_POINT_SMOOTH";
    case GL_POINT_SIZE:
        return "GL_POINT_SIZE";
    case GL_POINT_SIZE_RANGE:
        return "GL_POINT_SIZE_RANGE";
    case GL_POINT_SIZE_GRANULARITY:
        return "GL_POINT_SIZE_GRANULARITY";
    case GL_LINE_SMOOTH:
        return "GL_LINE_SMOOTH";
    case GL_LINE_WIDTH:
        return "GL_LINE_WIDTH";
    case GL_LINE_WIDTH_RANGE:
        return "GL_LINE_WIDTH_RANGE";
    case GL_LINE_WIDTH_GRANULARITY:
        return "GL_LINE_WIDTH_GRANULARITY";
    case GL_LINE_STIPPLE:
        return "GL_LINE_STIPPLE";
    case GL_LINE_STIPPLE_PATTERN:
        return "GL_LINE_STIPPLE_PATTERN";
    case GL_LINE_STIPPLE_REPEAT:
        return "GL_LINE_STIPPLE_REPEAT";
    case GL_LIST_MODE:
        return "GL_LIST_MODE";
    case GL_MAX_LIST_NESTING:
        return "GL_MAX_LIST_NESTING";
    case GL_LIST_BASE:
        return "GL_LIST_BASE";
    case GL_LIST_INDEX:
        return "GL_LIST_INDEX";
    case GL_POLYGON_MODE:
        return "GL_POLYGON_MODE";
    case GL_POLYGON_SMOOTH:
        return "GL_POLYGON_SMOOTH";
    case GL_POLYGON_STIPPLE:
        return "GL_POLYGON_STIPPLE";
    case GL_EDGE_FLAG:
        return "GL_EDGE_FLAG";
    case GL_CULL_FACE:
        return "GL_CULL_FACE";
    case GL_CULL_FACE_MODE:
        return "GL_CULL_FACE_MODE";
    case GL_FRONT_FACE:
        return "GL_FRONT_FACE";
    case GL_LIGHTING:
        return "GL_LIGHTING";
    case GL_LIGHT_MODEL_LOCAL_VIEWER:
        return "GL_LIGHT_MODEL_LOCAL_VIEWER";
    case GL_LIGHT_MODEL_TWO_SIDE:
        return "GL_LIGHT_MODEL_TWO_SIDE";
    case GL_LIGHT_MODEL_AMBIENT:
        return "GL_LIGHT_MODEL_AMBIENT";
    case GL_SHADE_MODEL:
        return "GL_SHADE_MODEL";
    case GL_COLOR_MATERIAL_FACE:
        return "GL_COLOR_MATERIAL_FACE";
    case GL_COLOR_MATERIAL_PARAMETER:
        return "GL_COLOR_MATERIAL_PARAMETER";
    case GL_COLOR_MATERIAL:
        return "GL_COLOR_MATERIAL";
    case GL_FOG:
        return "GL_FOG";
    case GL_FOG_INDEX:
        return "GL_FOG_INDEX";
    case GL_FOG_DENSITY:
        return "GL_FOG_DENSITY";
    case GL_FOG_START:
        return "GL_FOG_START";
    case GL_FOG_END:
        return "GL_FOG_END";
    case GL_FOG_MODE:
        return "GL_FOG_MODE";
    case GL_FOG_COLOR:
        return "GL_FOG_COLOR";
    case GL_DEPTH_RANGE:
        return "GL_DEPTH_RANGE";
    case GL_DEPTH_TEST:
        return "GL_DEPTH_TEST";
    case GL_DEPTH_WRITEMASK:
        return "GL_DEPTH_WRITEMASK";
    case GL_DEPTH_CLEAR_VALUE:
        return "GL_DEPTH_CLEAR_VALUE";
    case GL_DEPTH_FUNC:
        return "GL_DEPTH_FUNC";
    case GL_ACCUM_CLEAR_VALUE:
        return "GL_ACCUM_CLEAR_VALUE";
    case GL_STENCIL_TEST:
        return "GL_STENCIL_TEST";
    case GL_STENCIL_CLEAR_VALUE:
        return "GL_STENCIL_CLEAR_VALUE";
    case GL_STENCIL_FUNC:
        return "GL_STENCIL_FUNC";
    case GL_STENCIL_VALUE_MASK:
        return "GL_STENCIL_VALUE_MASK";
    case GL_STENCIL_FAIL:
        return "GL_STENCIL_FAIL";
    case GL_STENCIL_PASS_DEPTH_FAIL:
        return "GL_STENCIL_PASS_DEPTH_FAIL";
    case GL_STENCIL_PASS_DEPTH_PASS:
        return "GL_STENCIL_PASS_DEPTH_PASS";
    case GL_STENCIL_REF:
        return "GL_STENCIL_REF";
    case GL_STENCIL_WRITEMASK:
        return "GL_STENCIL_WRITEMASK";
    case GL_MATRIX_MODE:
        return "GL_MATRIX_MODE";
    case GL_NORMALIZE:
        return "GL_NORMALIZE";
    case GL_VIEWPORT:
        return "GL_VIEWPORT";
    case GL_MODELVIEW_STACK_DEPTH:
        return "GL_MODELVIEW_STACK_DEPTH";
    case GL_PROJECTION_STACK_DEPTH:
        return "GL_PROJECTION_STACK_DEPTH";
    case GL_TEXTURE_STACK_DEPTH:
        return "GL_TEXTURE_STACK_DEPTH";
    case GL_MODELVIEW_MATRIX:
        return "GL_MODELVIEW_MATRIX";
    case GL_PROJECTION_MATRIX:
        return "GL_PROJECTION_MATRIX";
    case GL_TEXTURE_MATRIX:
        return "GL_TEXTURE_MATRIX";
    case GL_ATTRIB_STACK_DEPTH:
        return "GL_ATTRIB_STACK_DEPTH";
    case GL_CLIENT_ATTRIB_STACK_DEPTH:
        return "GL_CLIENT_ATTRIB_STACK_DEPTH";
    case GL_ALPHA_TEST:
        return "GL_ALPHA_TEST";
    case GL_ALPHA_TEST_FUNC:
        return "GL_ALPHA_TEST_FUNC";
    case GL_ALPHA_TEST_REF:
        return "GL_ALPHA_TEST_REF";
    case GL_DITHER:
        return "GL_DITHER";
    case GL_BLEND_DST:
        return "GL_BLEND_DST";
    case GL_BLEND_SRC:
        return "GL_BLEND_SRC";
    case GL_BLEND:
        return "GL_BLEND";
    case GL_LOGIC_OP_MODE:
        return "GL_LOGIC_OP_MODE";
    case GL_INDEX_LOGIC_OP:
        return "GL_INDEX_LOGIC_OP";
    case GL_COLOR_LOGIC_OP:
        return "GL_COLOR_LOGIC_OP";
    case GL_AUX_BUFFERS:
        return "GL_AUX_BUFFERS";
    case GL_DRAW_BUFFER:
        return "GL_DRAW_BUFFER";
    case GL_READ_BUFFER:
        return "GL_READ_BUFFER";
    case GL_SCISSOR_BOX:
        return "GL_SCISSOR_BOX";
    case GL_SCISSOR_TEST:
        return "GL_SCISSOR_TEST";
    case GL_INDEX_CLEAR_VALUE:
        return "GL_INDEX_CLEAR_VALUE";
    case GL_INDEX_WRITEMASK:
        return "GL_INDEX_WRITEMASK";
    case GL_COLOR_CLEAR_VALUE:
        return "GL_COLOR_CLEAR_VALUE";
    case GL_COLOR_WRITEMASK:
        return "GL_COLOR_WRITEMASK";
    case GL_INDEX_MODE:
        return "GL_INDEX_MODE";
    case GL_RGBA_MODE:
        return "GL_RGBA_MODE";
    case GL_DOUBLEBUFFER:
        return "GL_DOUBLEBUFFER";
    case GL_STEREO:
        return "GL_STEREO";
    case GL_RENDER_MODE:
        return "GL_RENDER_MODE";
    case GL_PERSPECTIVE_CORRECTION_HINT:
        return "GL_PERSPECTIVE_CORRECTION_HINT";
    case GL_POINT_SMOOTH_HINT:
        return "GL_POINT_SMOOTH_HINT";
    case GL_LINE_SMOOTH_HINT:
        return "GL_LINE_SMOOTH_HINT";
    case GL_POLYGON_SMOOTH_HINT:
        return "GL_POLYGON_SMOOTH_HINT";
    case GL_FOG_HINT:
        return "GL_FOG_HINT";
    case GL_TEXTURE_GEN_S:
        return "GL_TEXTURE_GEN_S";
    case GL_TEXTURE_GEN_T:
        return "GL_TEXTURE_GEN_T";
    case GL_TEXTURE_GEN_R:
        return "GL_TEXTURE_GEN_R";
    case GL_TEXTURE_GEN_Q:
        return "GL_TEXTURE_GEN_Q";
    case GL_PIXEL_MAP_I_TO_I:
        return "GL_PIXEL_MAP_I_TO_I";
    case GL_PIXEL_MAP_S_TO_S:
        return "GL_PIXEL_MAP_S_TO_S";
    case GL_PIXEL_MAP_I_TO_R:
        return "GL_PIXEL_MAP_I_TO_R";
    case GL_PIXEL_MAP_I_TO_G:
        return "GL_PIXEL_MAP_I_TO_G";
    case GL_PIXEL_MAP_I_TO_B:
        return "GL_PIXEL_MAP_I_TO_B";
    case GL_PIXEL_MAP_I_TO_A:
        return "GL_PIXEL_MAP_I_TO_A";
    case GL_PIXEL_MAP_R_TO_R:
        return "GL_PIXEL_MAP_R_TO_R";
    case GL_PIXEL_MAP_G_TO_G:
        return "GL_PIXEL_MAP_G_TO_G";
    case GL_PIXEL_MAP_B_TO_B:
        return "GL_PIXEL_MAP_B_TO_B";
    case GL_PIXEL_MAP_A_TO_A:
        return "GL_PIXEL_MAP_A_TO_A";
    case GL_PIXEL_MAP_I_TO_I_SIZE:
        return "GL_PIXEL_MAP_I_TO_I_SIZE";
    case GL_PIXEL_MAP_S_TO_S_SIZE:
        return "GL_PIXEL_MAP_S_TO_S_SIZE";
    case GL_PIXEL_MAP_I_TO_R_SIZE:
        return "GL_PIXEL_MAP_I_TO_R_SIZE";
    case GL_PIXEL_MAP_I_TO_G_SIZE:
        return "GL_PIXEL_MAP_I_TO_G_SIZE";
    case GL_PIXEL_MAP_I_TO_B_SIZE:
        return "GL_PIXEL_MAP_I_TO_B_SIZE";
    case GL_PIXEL_MAP_I_TO_A_SIZE:
        return "GL_PIXEL_MAP_I_TO_A_SIZE";
    case GL_PIXEL_MAP_R_TO_R_SIZE:
        return "GL_PIXEL_MAP_R_TO_R_SIZE";
    case GL_PIXEL_MAP_G_TO_G_SIZE:
        return "GL_PIXEL_MAP_G_TO_G_SIZE";
    case GL_PIXEL_MAP_B_TO_B_SIZE:
        return "GL_PIXEL_MAP_B_TO_B_SIZE";
    case GL_PIXEL_MAP_A_TO_A_SIZE:
        return "GL_PIXEL_MAP_A_TO_A_SIZE";
    case GL_UNPACK_SWAP_BYTES:
        return "GL_UNPACK_SWAP_BYTES";
    case GL_UNPACK_LSB_FIRST:
        return "GL_UNPACK_LSB_FIRST";
    case GL_UNPACK_ROW_LENGTH:
        return "GL_UNPACK_ROW_LENGTH";
    case GL_UNPACK_SKIP_ROWS:
        return "GL_UNPACK_SKIP_ROWS";
    case GL_UNPACK_SKIP_PIXELS:
        return "GL_UNPACK_SKIP_PIXELS";
    case GL_UNPACK_ALIGNMENT:
        return "GL_UNPACK_ALIGNMENT";
    case GL_PACK_SWAP_BYTES:
        return "GL_PACK_SWAP_BYTES";
    case GL_PACK_LSB_FIRST:
        return "GL_PACK_LSB_FIRST";
    case GL_PACK_ROW_LENGTH:
        return "GL_PACK_ROW_LENGTH";
    case GL_PACK_SKIP_ROWS:
        return "GL_PACK_SKIP_ROWS";
    case GL_PACK_SKIP_PIXELS:
        return "GL_PACK_SKIP_PIXELS";
    case GL_PACK_ALIGNMENT:
        return "GL_PACK_ALIGNMENT";
    case GL_MAP_COLOR:
        return "GL_MAP_COLOR";
    case GL_MAP_STENCIL:
        return "GL_MAP_STENCIL";
    case GL_INDEX_SHIFT:
        return "GL_INDEX_SHIFT";
    case GL_INDEX_OFFSET:
        return "GL_INDEX_OFFSET";
    case GL_RED_SCALE:
        return "GL_RED_SCALE";
    case GL_RED_BIAS:
        return "GL_RED_BIAS";
    case GL_ZOOM_X:
        return "GL_ZOOM_X";
    case GL_ZOOM_Y:
        return "GL_ZOOM_Y";
    case GL_GREEN_SCALE:
        return "GL_GREEN_SCALE";
    case GL_GREEN_BIAS:
        return "GL_GREEN_BIAS";
    case GL_BLUE_SCALE:
        return "GL_BLUE_SCALE";
    case GL_BLUE_BIAS:
        return "GL_BLUE_BIAS";
    case GL_ALPHA_SCALE:
        return "GL_ALPHA_SCALE";
    case GL_ALPHA_BIAS:
        return "GL_ALPHA_BIAS";
    case GL_DEPTH_SCALE:
        return "GL_DEPTH_SCALE";
    case GL_DEPTH_BIAS:
        return "GL_DEPTH_BIAS";
    case GL_MAX_EVAL_ORDER:
        return "GL_MAX_EVAL_ORDER";
    case GL_MAX_LIGHTS:
        return "GL_MAX_LIGHTS";
    case GL_MAX_CLIP_DISTANCES:
        return "GL_MAX_CLIP_DISTANCES";
    case GL_MAX_TEXTURE_SIZE:
        return "GL_MAX_TEXTURE_SIZE";
    case GL_MAX_PIXEL_MAP_TABLE:
        return "GL_MAX_PIXEL_MAP_TABLE";
    case GL_MAX_ATTRIB_STACK_DEPTH:
        return "GL_MAX_ATTRIB_STACK_DEPTH";
    case GL_MAX_MODELVIEW_STACK_DEPTH:
        return "GL_MAX_MODELVIEW_STACK_DEPTH";
    case GL_MAX_NAME_STACK_DEPTH:
        return "GL_MAX_NAME_STACK_DEPTH";
    case GL_MAX_PROJECTION_STACK_DEPTH:
        return "GL_MAX_PROJECTION_STACK_DEPTH";
    case GL_MAX_TEXTURE_STACK_DEPTH:
        return "GL_MAX_TEXTURE_STACK_DEPTH";
    case GL_MAX_VIEWPORT_DIMS:
        return "GL_MAX_VIEWPORT_DIMS";
    case GL_MAX_CLIENT_ATTRIB_STACK_DEPTH:
        return "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH";
    case GL_SUBPIXEL_BITS:
        return "GL_SUBPIXEL_BITS";
    case GL_INDEX_BITS:
        return "GL_INDEX_BITS";
    case GL_RED_BITS:
        return "GL_RED_BITS";
    case GL_GREEN_BITS:
        return "GL_GREEN_BITS";
    case GL_BLUE_BITS:
        return "GL_BLUE_BITS";
    case GL_ALPHA_BITS:
        return "GL_ALPHA_BITS";
    case GL_DEPTH_BITS:
        return "GL_DEPTH_BITS";
    case GL_STENCIL_BITS:
        return "GL_STENCIL_BITS";
    case GL_ACCUM_RED_BITS:
        return "GL_ACCUM_RED_BITS";
    case GL_ACCUM_GREEN_BITS:
        return "GL_ACCUM_GREEN_BITS";
    case GL_ACCUM_BLUE_BITS:
        return "GL_ACCUM_BLUE_BITS";
    case GL_ACCUM_ALPHA_BITS:
        return "GL_ACCUM_ALPHA_BITS";
    case GL_NAME_STACK_DEPTH:
        return "GL_NAME_STACK_DEPTH";
    case GL_AUTO_NORMAL:
        return "GL_AUTO_NORMAL";
    case GL_MAP1_COLOR_4:
        return "GL_MAP1_COLOR_4";
    case GL_MAP1_INDEX:
        return "GL_MAP1_INDEX";
    case GL_MAP1_NORMAL:
        return "GL_MAP1_NORMAL";
    case GL_MAP1_TEXTURE_COORD_1:
        return "GL_MAP1_TEXTURE_COORD_1";
    case GL_MAP1_TEXTURE_COORD_2:
        return "GL_MAP1_TEXTURE_COORD_2";
    case GL_MAP1_TEXTURE_COORD_3:
        return "GL_MAP1_TEXTURE_COORD_3";
    case GL_MAP1_TEXTURE_COORD_4:
        return "GL_MAP1_TEXTURE_COORD_4";
    case GL_MAP1_VERTEX_3:
        return "GL_MAP1_VERTEX_3";
    case GL_MAP1_VERTEX_4:
        return "GL_MAP1_VERTEX_4";
    case GL_MAP2_COLOR_4:
        return "GL_MAP2_COLOR_4";
    case GL_MAP2_INDEX:
        return "GL_MAP2_INDEX";
    case GL_MAP2_NORMAL:
        return "GL_MAP2_NORMAL";
    case GL_MAP2_TEXTURE_COORD_1:
        return "GL_MAP2_TEXTURE_COORD_1";
    case GL_MAP2_TEXTURE_COORD_2:
        return "GL_MAP2_TEXTURE_COORD_2";
    case GL_MAP2_TEXTURE_COORD_3:
        return "GL_MAP2_TEXTURE_COORD_3";
    case GL_MAP2_TEXTURE_COORD_4:
        return "GL_MAP2_TEXTURE_COORD_4";
    case GL_MAP2_VERTEX_3:
        return "GL_MAP2_VERTEX_3";
    case GL_MAP2_VERTEX_4:
        return "GL_MAP2_VERTEX_4";
    case GL_MAP1_GRID_DOMAIN:
        return "GL_MAP1_GRID_DOMAIN";
    case GL_MAP1_GRID_SEGMENTS:
        return "GL_MAP1_GRID_SEGMENTS";
    case GL_MAP2_GRID_DOMAIN:
        return "GL_MAP2_GRID_DOMAIN";
    case GL_MAP2_GRID_SEGMENTS:
        return "GL_MAP2_GRID_SEGMENTS";
    case GL_TEXTURE_1D:
        return "GL_TEXTURE_1D";
    case GL_TEXTURE_2D:
        return "GL_TEXTURE_2D";
    case GL_FEEDBACK_BUFFER_POINTER:
        return "GL_FEEDBACK_BUFFER_POINTER";
    case GL_FEEDBACK_BUFFER_SIZE:
        return "GL_FEEDBACK_BUFFER_SIZE";
    case GL_FEEDBACK_BUFFER_TYPE:
        return "GL_FEEDBACK_BUFFER_TYPE";
    case GL_SELECTION_BUFFER_POINTER:
        return "GL_SELECTION_BUFFER_POINTER";
    case GL_SELECTION_BUFFER_SIZE:
        return "GL_SELECTION_BUFFER_SIZE";
    case GL_TEXTURE_WIDTH:
        return "GL_TEXTURE_WIDTH";
    case GL_TEXTURE_HEIGHT:
        return "GL_TEXTURE_HEIGHT";
    case GL_TEXTURE_INTERNAL_FORMAT:
        return "GL_TEXTURE_INTERNAL_FORMAT";
    case GL_TEXTURE_BORDER_COLOR:
        return "GL_TEXTURE_BORDER_COLOR";
    case GL_TEXTURE_BORDER:
        return "GL_TEXTURE_BORDER";
    case GL_DONT_CARE:
        return "GL_DONT_CARE";
    case GL_FASTEST:
        return "GL_FASTEST";
    case GL_NICEST:
        return "GL_NICEST";
    case GL_AMBIENT:
        return "GL_AMBIENT";
    case GL_DIFFUSE:
        return "GL_DIFFUSE";
    case GL_SPECULAR:
        return "GL_SPECULAR";
    case GL_POSITION:
        return "GL_POSITION";
    case GL_SPOT_DIRECTION:
        return "GL_SPOT_DIRECTION";
    case GL_SPOT_EXPONENT:
        return "GL_SPOT_EXPONENT";
    case GL_SPOT_CUTOFF:
        return "GL_SPOT_CUTOFF";
    case GL_CONSTANT_ATTENUATION:
        return "GL_CONSTANT_ATTENUATION";
    case GL_LINEAR_ATTENUATION:
        return "GL_LINEAR_ATTENUATION";
    case GL_QUADRATIC_ATTENUATION:
        return "GL_QUADRATIC_ATTENUATION";
    case GL_COMPILE:
        return "GL_COMPILE";
    case GL_COMPILE_AND_EXECUTE:
        return "GL_COMPILE_AND_EXECUTE";
    case GL_BYTE:
        return "GL_BYTE";
    case GL_UNSIGNED_BYTE:
        return "GL_UNSIGNED_BYTE";
    case GL_SHORT:
        return "GL_SHORT";
    case GL_UNSIGNED_SHORT:
        return "GL_UNSIGNED_SHORT";
    case GL_INT:
        return "GL_INT";
    case GL_UNSIGNED_INT:
        return "GL_UNSIGNED_INT";
    case GL_FLOAT:
        return "GL_FLOAT";
    case GL_2_BYTES:
        return "GL_2_BYTES";
    case GL_3_BYTES:
        return "GL_3_BYTES";
    case GL_4_BYTES:
        return "GL_4_BYTES";
    case GL_DOUBLE:
        return "GL_DOUBLE";
    case GL_HALF_FLOAT:
        return "GL_HALF_FLOAT";
    case GL_FIXED:
        return "GL_FIXED";
    case GL_INT64_NV:
        return "GL_INT64_NV";
    case GL_UNSIGNED_INT64_NV:
        return "GL_UNSIGNED_INT64_NV";
    case GL_CLEAR:
        return "GL_CLEAR";
    case GL_AND:
        return "GL_AND";
    case GL_AND_REVERSE:
        return "GL_AND_REVERSE";
    case GL_COPY:
        return "GL_COPY";
    case GL_AND_INVERTED:
        return "GL_AND_INVERTED";
    case GL_NOOP:
        return "GL_NOOP";
    case GL_XOR:
        return "GL_XOR";
    case GL_OR:
        return "GL_OR";
    case GL_NOR:
        return "GL_NOR";
    case GL_EQUIV:
        return "GL_EQUIV";
    case GL_INVERT:
        return "GL_INVERT";
    case GL_OR_REVERSE:
        return "GL_OR_REVERSE";
    case GL_COPY_INVERTED:
        return "GL_COPY_INVERTED";
    case GL_OR_INVERTED:
        return "GL_OR_INVERTED";
    case GL_NAND:
        return "GL_NAND";
    case GL_SET:
        return "GL_SET";
    case GL_EMISSION:
        return "GL_EMISSION";
    case GL_SHININESS:
        return "GL_SHININESS";
    case GL_AMBIENT_AND_DIFFUSE:
        return "GL_AMBIENT_AND_DIFFUSE";
    case GL_COLOR_INDEXES:
        return "GL_COLOR_INDEXES";
    case GL_MODELVIEW:
        return "GL_MODELVIEW";
    case GL_PROJECTION:
        return "GL_PROJECTION";
    case GL_TEXTURE:
        return "GL_TEXTURE";
    case GL_COLOR:
        return "GL_COLOR";
    case GL_DEPTH:
        return "GL_DEPTH";
    case GL_STENCIL:
        return "GL_STENCIL";
    case GL_COLOR_INDEX:
        return "GL_COLOR_INDEX";
    case GL_STENCIL_INDEX:
        return "GL_STENCIL_INDEX";
    case GL_DEPTH_COMPONENT:
        return "GL_DEPTH_COMPONENT";
    case GL_RED:
        return "GL_RED";
    case GL_GREEN:
        return "GL_GREEN";
    case GL_BLUE:
        return "GL_BLUE";
    case GL_ALPHA:
        return "GL_ALPHA";
    case GL_RGB:
        return "GL_RGB";
    case GL_RGBA:
        return "GL_RGBA";
    case GL_LUMINANCE:
        return "GL_LUMINANCE";
    case GL_LUMINANCE_ALPHA:
        return "GL_LUMINANCE_ALPHA";
    case GL_RASTER_POSITION_UNCLIPPED_IBM:
        return "GL_RASTER_POSITION_UNCLIPPED_IBM";
    case GL_BITMAP:
        return "GL_BITMAP";
    case GL_PREFER_DOUBLEBUFFER_HINT_PGI:
        return "GL_PREFER_DOUBLEBUFFER_HINT_PGI";
    case GL_CONSERVE_MEMORY_HINT_PGI:
        return "GL_CONSERVE_MEMORY_HINT_PGI";
    case GL_RECLAIM_MEMORY_HINT_PGI:
        return "GL_RECLAIM_MEMORY_HINT_PGI";
    case GL_NATIVE_GRAPHICS_HANDLE_PGI:
        return "GL_NATIVE_GRAPHICS_HANDLE_PGI";
    case GL_NATIVE_GRAPHICS_BEGIN_HINT_PGI:
        return "GL_NATIVE_GRAPHICS_BEGIN_HINT_PGI";
    case GL_NATIVE_GRAPHICS_END_HINT_PGI:
        return "GL_NATIVE_GRAPHICS_END_HINT_PGI";
    case GL_ALWAYS_FAST_HINT_PGI:
        return "GL_ALWAYS_FAST_HINT_PGI";
    case GL_ALWAYS_SOFT_HINT_PGI:
        return "GL_ALWAYS_SOFT_HINT_PGI";
    case GL_ALLOW_DRAW_OBJ_HINT_PGI:
        return "GL_ALLOW_DRAW_OBJ_HINT_PGI";
    case GL_ALLOW_DRAW_WIN_HINT_PGI:
        return "GL_ALLOW_DRAW_WIN_HINT_PGI";
    case GL_ALLOW_DRAW_FRG_HINT_PGI:
        return "GL_ALLOW_DRAW_FRG_HINT_PGI";
    case GL_ALLOW_DRAW_MEM_HINT_PGI:
        return "GL_ALLOW_DRAW_MEM_HINT_PGI";
    case GL_STRICT_DEPTHFUNC_HINT_PGI:
        return "GL_STRICT_DEPTHFUNC_HINT_PGI";
    case GL_STRICT_LIGHTING_HINT_PGI:
        return "GL_STRICT_LIGHTING_HINT_PGI";
    case GL_STRICT_SCISSOR_HINT_PGI:
        return "GL_STRICT_SCISSOR_HINT_PGI";
    case GL_FULL_STIPPLE_HINT_PGI:
        return "GL_FULL_STIPPLE_HINT_PGI";
    case GL_CLIP_NEAR_HINT_PGI:
        return "GL_CLIP_NEAR_HINT_PGI";
    case GL_CLIP_FAR_HINT_PGI:
        return "GL_CLIP_FAR_HINT_PGI";
    case GL_WIDE_LINE_HINT_PGI:
        return "GL_WIDE_LINE_HINT_PGI";
    case GL_BACK_NORMALS_HINT_PGI:
        return "GL_BACK_NORMALS_HINT_PGI";
    case GL_VERTEX_DATA_HINT_PGI:
        return "GL_VERTEX_DATA_HINT_PGI";
    case GL_VERTEX_CONSISTENT_HINT_PGI:
        return "GL_VERTEX_CONSISTENT_HINT_PGI";
    case GL_MATERIAL_SIDE_HINT_PGI:
        return "GL_MATERIAL_SIDE_HINT_PGI";
    case GL_MAX_VERTEX_HINT_PGI:
        return "GL_MAX_VERTEX_HINT_PGI";
    case GL_POINT:
        return "GL_POINT";
    case GL_LINE:
        return "GL_LINE";
    case GL_FILL:
        return "GL_FILL";
    case GL_RENDER:
        return "GL_RENDER";
    case GL_FEEDBACK:
        return "GL_FEEDBACK";
    case GL_SELECT:
        return "GL_SELECT";
    case GL_FLAT:
        return "GL_FLAT";
    case GL_SMOOTH:
        return "GL_SMOOTH";
    case GL_KEEP:
        return "GL_KEEP";
    case GL_REPLACE:
        return "GL_REPLACE";
    case GL_INCR:
        return "GL_INCR";
    case GL_DECR:
        return "GL_DECR";
    case GL_VENDOR:
        return "GL_VENDOR";
    case GL_RENDERER:
        return "GL_RENDERER";
    case GL_VERSION:
        return "GL_VERSION";
    case GL_EXTENSIONS:
        return "GL_EXTENSIONS";
    case GL_S:
        return "GL_S";
    case GL_T:
        return "GL_T";
    case GL_R:
        return "GL_R";
    case GL_Q:
        return "GL_Q";
    case GL_MODULATE:
        return "GL_MODULATE";
    case GL_DECAL:
        return "GL_DECAL";
    case GL_TEXTURE_ENV_MODE:
        return "GL_TEXTURE_ENV_MODE";
    case GL_TEXTURE_ENV_COLOR:
        return "GL_TEXTURE_ENV_COLOR";
    case GL_TEXTURE_ENV:
        return "GL_TEXTURE_ENV";
    case GL_EYE_LINEAR:
        return "GL_EYE_LINEAR";
    case GL_OBJECT_LINEAR:
        return "GL_OBJECT_LINEAR";
    case GL_SPHERE_MAP:
        return "GL_SPHERE_MAP";
    case GL_TEXTURE_GEN_MODE:
        return "GL_TEXTURE_GEN_MODE";
    case GL_OBJECT_PLANE:
        return "GL_OBJECT_PLANE";
    case GL_EYE_PLANE:
        return "GL_EYE_PLANE";
    case GL_NEAREST:
        return "GL_NEAREST";
    case GL_LINEAR:
        return "GL_LINEAR";
    case GL_NEAREST_MIPMAP_NEAREST:
        return "GL_NEAREST_MIPMAP_NEAREST";
    case GL_LINEAR_MIPMAP_NEAREST:
        return "GL_LINEAR_MIPMAP_NEAREST";
    case GL_NEAREST_MIPMAP_LINEAR:
        return "GL_NEAREST_MIPMAP_LINEAR";
    case GL_LINEAR_MIPMAP_LINEAR:
        return "GL_LINEAR_MIPMAP_LINEAR";
    case GL_TEXTURE_MAG_FILTER:
        return "GL_TEXTURE_MAG_FILTER";
    case GL_TEXTURE_MIN_FILTER:
        return "GL_TEXTURE_MIN_FILTER";
    case GL_TEXTURE_WRAP_S:
        return "GL_TEXTURE_WRAP_S";
    case GL_TEXTURE_WRAP_T:
        return "GL_TEXTURE_WRAP_T";
    case GL_CLAMP:
        return "GL_CLAMP";
    case GL_REPEAT:
        return "GL_REPEAT";
    case GL_POLYGON_OFFSET_UNITS:
        return "GL_POLYGON_OFFSET_UNITS";
    case GL_POLYGON_OFFSET_POINT:
        return "GL_POLYGON_OFFSET_POINT";
    case GL_POLYGON_OFFSET_LINE:
        return "GL_POLYGON_OFFSET_LINE";
    case GL_R3_G3_B2:
        return "GL_R3_G3_B2";
    case GL_V2F:
        return "GL_V2F";
    case GL_V3F:
        return "GL_V3F";
    case GL_C4UB_V2F:
        return "GL_C4UB_V2F";
    case GL_C4UB_V3F:
        return "GL_C4UB_V3F";
    case GL_C3F_V3F:
        return "GL_C3F_V3F";
    case GL_N3F_V3F:
        return "GL_N3F_V3F";
    case GL_C4F_N3F_V3F:
        return "GL_C4F_N3F_V3F";
    case GL_T2F_V3F:
        return "GL_T2F_V3F";
    case GL_T4F_V4F:
        return "GL_T4F_V4F";
    case GL_T2F_C4UB_V3F:
        return "GL_T2F_C4UB_V3F";
    case GL_T2F_C3F_V3F:
        return "GL_T2F_C3F_V3F";
    case GL_T2F_N3F_V3F:
        return "GL_T2F_N3F_V3F";
    case GL_T2F_C4F_N3F_V3F:
        return "GL_T2F_C4F_N3F_V3F";
    case GL_T4F_C4F_N3F_V4F:
        return "GL_T4F_C4F_N3F_V4F";
    case GL_CLIP_DISTANCE0:
        return "GL_CLIP_DISTANCE0";
    case GL_CLIP_DISTANCE1:
        return "GL_CLIP_DISTANCE1";
    case GL_CLIP_DISTANCE2:
        return "GL_CLIP_DISTANCE2";
    case GL_CLIP_DISTANCE3:
        return "GL_CLIP_DISTANCE3";
    case GL_CLIP_DISTANCE4:
        return "GL_CLIP_DISTANCE4";
    case GL_CLIP_DISTANCE5:
        return "GL_CLIP_DISTANCE5";
    case GL_CLIP_DISTANCE6:
        return "GL_CLIP_DISTANCE6";
    case GL_CLIP_DISTANCE7:
        return "GL_CLIP_DISTANCE7";
    case GL_LIGHT0:
        return "GL_LIGHT0";
    case GL_LIGHT1:
        return "GL_LIGHT1";
    case GL_LIGHT2:
        return "GL_LIGHT2";
    case GL_LIGHT3:
        return "GL_LIGHT3";
    case GL_LIGHT4:
        return "GL_LIGHT4";
    case GL_LIGHT5:
        return "GL_LIGHT5";
    case GL_LIGHT6:
        return "GL_LIGHT6";
    case GL_LIGHT7:
        return "GL_LIGHT7";
    case GL_ABGR_EXT:
        return "GL_ABGR_EXT";
    case GL_CONSTANT_COLOR:
        return "GL_CONSTANT_COLOR";
    case GL_ONE_MINUS_CONSTANT_COLOR:
        return "GL_ONE_MINUS_CONSTANT_COLOR";
    case GL_CONSTANT_ALPHA:
        return "GL_CONSTANT_ALPHA";
    case GL_ONE_MINUS_CONSTANT_ALPHA:
        return "GL_ONE_MINUS_CONSTANT_ALPHA";
    case GL_BLEND_COLOR:
        return "GL_BLEND_COLOR";
    case GL_FUNC_ADD:
        return "GL_FUNC_ADD";
    case GL_MIN:
        return "GL_MIN";
    case GL_MAX:
        return "GL_MAX";
    case GL_BLEND_EQUATION:
        return "GL_BLEND_EQUATION";
    case GL_FUNC_SUBTRACT:
        return "GL_FUNC_SUBTRACT";
    case GL_FUNC_REVERSE_SUBTRACT:
        return "GL_FUNC_REVERSE_SUBTRACT";
    case GL_CMYK_EXT:
        return "GL_CMYK_EXT";
    case GL_CMYKA_EXT:
        return "GL_CMYKA_EXT";
    case GL_PACK_CMYK_HINT_EXT:
        return "GL_PACK_CMYK_HINT_EXT";
    case GL_UNPACK_CMYK_HINT_EXT:
        return "GL_UNPACK_CMYK_HINT_EXT";
    case GL_CONVOLUTION_1D:
        return "GL_CONVOLUTION_1D";
    case GL_CONVOLUTION_2D:
        return "GL_CONVOLUTION_2D";
    case GL_SEPARABLE_2D:
        return "GL_SEPARABLE_2D";
    case GL_CONVOLUTION_BORDER_MODE:
        return "GL_CONVOLUTION_BORDER_MODE";
    case GL_CONVOLUTION_FILTER_SCALE:
        return "GL_CONVOLUTION_FILTER_SCALE";
    case GL_CONVOLUTION_FILTER_BIAS:
        return "GL_CONVOLUTION_FILTER_BIAS";
    case GL_REDUCE:
        return "GL_REDUCE";
    case GL_CONVOLUTION_FORMAT:
        return "GL_CONVOLUTION_FORMAT";
    case GL_CONVOLUTION_WIDTH:
        return "GL_CONVOLUTION_WIDTH";
    case GL_CONVOLUTION_HEIGHT:
        return "GL_CONVOLUTION_HEIGHT";
    case GL_MAX_CONVOLUTION_WIDTH:
        return "GL_MAX_CONVOLUTION_WIDTH";
    case GL_MAX_CONVOLUTION_HEIGHT:
        return "GL_MAX_CONVOLUTION_HEIGHT";
    case GL_POST_CONVOLUTION_RED_SCALE:
        return "GL_POST_CONVOLUTION_RED_SCALE";
    case GL_POST_CONVOLUTION_GREEN_SCALE:
        return "GL_POST_CONVOLUTION_GREEN_SCALE";
    case GL_POST_CONVOLUTION_BLUE_SCALE:
        return "GL_POST_CONVOLUTION_BLUE_SCALE";
    case GL_POST_CONVOLUTION_ALPHA_SCALE:
        return "GL_POST_CONVOLUTION_ALPHA_SCALE";
    case GL_POST_CONVOLUTION_RED_BIAS:
        return "GL_POST_CONVOLUTION_RED_BIAS";
    case GL_POST_CONVOLUTION_GREEN_BIAS:
        return "GL_POST_CONVOLUTION_GREEN_BIAS";
    case GL_POST_CONVOLUTION_BLUE_BIAS:
        return "GL_POST_CONVOLUTION_BLUE_BIAS";
    case GL_POST_CONVOLUTION_ALPHA_BIAS:
        return "GL_POST_CONVOLUTION_ALPHA_BIAS";
    case GL_HISTOGRAM:
        return "GL_HISTOGRAM";
    case GL_PROXY_HISTOGRAM:
        return "GL_PROXY_HISTOGRAM";
    case GL_HISTOGRAM_WIDTH:
        return "GL_HISTOGRAM_WIDTH";
    case GL_HISTOGRAM_FORMAT:
        return "GL_HISTOGRAM_FORMAT";
    case GL_HISTOGRAM_RED_SIZE:
        return "GL_HISTOGRAM_RED_SIZE";
    case GL_HISTOGRAM_GREEN_SIZE:
        return "GL_HISTOGRAM_GREEN_SIZE";
    case GL_HISTOGRAM_BLUE_SIZE:
        return "GL_HISTOGRAM_BLUE_SIZE";
    case GL_HISTOGRAM_ALPHA_SIZE:
        return "GL_HISTOGRAM_ALPHA_SIZE";
    case GL_HISTOGRAM_LUMINANCE_SIZE:
        return "GL_HISTOGRAM_LUMINANCE_SIZE";
    case GL_HISTOGRAM_SINK:
        return "GL_HISTOGRAM_SINK";
    case GL_MINMAX:
        return "GL_MINMAX";
    case GL_MINMAX_FORMAT:
        return "GL_MINMAX_FORMAT";
    case GL_MINMAX_SINK:
        return "GL_MINMAX_SINK";
    case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";
    case GL_UNSIGNED_BYTE_3_3_2:
        return "GL_UNSIGNED_BYTE_3_3_2";
    case GL_UNSIGNED_SHORT_4_4_4_4:
        return "GL_UNSIGNED_SHORT_4_4_4_4";
    case GL_UNSIGNED_SHORT_5_5_5_1:
        return "GL_UNSIGNED_SHORT_5_5_5_1";
    case GL_UNSIGNED_INT_8_8_8_8:
        return "GL_UNSIGNED_INT_8_8_8_8";
    case GL_UNSIGNED_INT_10_10_10_2:
        return "GL_UNSIGNED_INT_10_10_10_2";
    case GL_POLYGON_OFFSET_FILL:
        return "GL_POLYGON_OFFSET_FILL";
    case GL_POLYGON_OFFSET_FACTOR:
        return "GL_POLYGON_OFFSET_FACTOR";
    case GL_POLYGON_OFFSET_BIAS_EXT:
        return "GL_POLYGON_OFFSET_BIAS_EXT";
    case GL_RESCALE_NORMAL:
        return "GL_RESCALE_NORMAL";
    case GL_ALPHA4:
        return "GL_ALPHA4";
    case GL_ALPHA8:
        return "GL_ALPHA8";
    case GL_ALPHA12:
        return "GL_ALPHA12";
    case GL_ALPHA16:
        return "GL_ALPHA16";
    case GL_LUMINANCE4:
        return "GL_LUMINANCE4";
    case GL_LUMINANCE8:
        return "GL_LUMINANCE8";
    case GL_LUMINANCE12:
        return "GL_LUMINANCE12";
    case GL_LUMINANCE16:
        return "GL_LUMINANCE16";
    case GL_LUMINANCE4_ALPHA4:
        return "GL_LUMINANCE4_ALPHA4";
    case GL_LUMINANCE6_ALPHA2:
        return "GL_LUMINANCE6_ALPHA2";
    case GL_LUMINANCE8_ALPHA8:
        return "GL_LUMINANCE8_ALPHA8";
    case GL_LUMINANCE12_ALPHA4:
        return "GL_LUMINANCE12_ALPHA4";
    case GL_LUMINANCE12_ALPHA12:
        return "GL_LUMINANCE12_ALPHA12";
    case GL_LUMINANCE16_ALPHA16:
        return "GL_LUMINANCE16_ALPHA16";
    case GL_INTENSITY:
        return "GL_INTENSITY";
    case GL_INTENSITY4:
        return "GL_INTENSITY4";
    case GL_INTENSITY8:
        return "GL_INTENSITY8";
    case GL_INTENSITY12:
        return "GL_INTENSITY12";
    case GL_INTENSITY16:
        return "GL_INTENSITY16";
    case GL_RGB2_EXT:
        return "GL_RGB2_EXT";
    case GL_RGB4:
        return "GL_RGB4";
    case GL_RGB5:
        return "GL_RGB5";
    case GL_RGB8:
        return "GL_RGB8";
    case GL_RGB10:
        return "GL_RGB10";
    case GL_RGB12:
        return "GL_RGB12";
    case GL_RGB16:
        return "GL_RGB16";
    case GL_RGBA2:
        return "GL_RGBA2";
    case GL_RGBA4:
        return "GL_RGBA4";
    case GL_RGB5_A1:
        return "GL_RGB5_A1";
    case GL_RGBA8:
        return "GL_RGBA8";
    case GL_RGB10_A2:
        return "GL_RGB10_A2";
    case GL_RGBA12:
        return "GL_RGBA12";
    case GL_RGBA16:
        return "GL_RGBA16";
    case GL_TEXTURE_RED_SIZE:
        return "GL_TEXTURE_RED_SIZE";
    case GL_TEXTURE_GREEN_SIZE:
        return "GL_TEXTURE_GREEN_SIZE";
    case GL_TEXTURE_BLUE_SIZE:
        return "GL_TEXTURE_BLUE_SIZE";
    case GL_TEXTURE_ALPHA_SIZE:
        return "GL_TEXTURE_ALPHA_SIZE";
    case GL_TEXTURE_LUMINANCE_SIZE:
        return "GL_TEXTURE_LUMINANCE_SIZE";
    case GL_TEXTURE_INTENSITY_SIZE:
        return "GL_TEXTURE_INTENSITY_SIZE";
    case GL_REPLACE_EXT:
        return "GL_REPLACE_EXT";
    case GL_PROXY_TEXTURE_1D:
        return "GL_PROXY_TEXTURE_1D";
    case GL_PROXY_TEXTURE_2D:
        return "GL_PROXY_TEXTURE_2D";
    case GL_TEXTURE_TOO_LARGE_EXT:
        return "GL_TEXTURE_TOO_LARGE_EXT";
    case GL_TEXTURE_PRIORITY:
        return "GL_TEXTURE_PRIORITY";
    case GL_TEXTURE_RESIDENT:
        return "GL_TEXTURE_RESIDENT";
    case GL_TEXTURE_BINDING_1D:
        return "GL_TEXTURE_BINDING_1D";
    case GL_TEXTURE_BINDING_2D:
        return "GL_TEXTURE_BINDING_2D";
    case GL_TEXTURE_BINDING_3D:
        return "GL_TEXTURE_BINDING_3D";
    case GL_PACK_SKIP_IMAGES:
        return "GL_PACK_SKIP_IMAGES";
    case GL_PACK_IMAGE_HEIGHT:
        return "GL_PACK_IMAGE_HEIGHT";
    case GL_UNPACK_SKIP_IMAGES:
        return "GL_UNPACK_SKIP_IMAGES";
    case GL_UNPACK_IMAGE_HEIGHT:
        return "GL_UNPACK_IMAGE_HEIGHT";
    case GL_TEXTURE_3D:
        return "GL_TEXTURE_3D";
    case GL_PROXY_TEXTURE_3D:
        return "GL_PROXY_TEXTURE_3D";
    case GL_TEXTURE_DEPTH:
        return "GL_TEXTURE_DEPTH";
    case GL_TEXTURE_WRAP_R:
        return "GL_TEXTURE_WRAP_R";
    case GL_MAX_3D_TEXTURE_SIZE:
        return "GL_MAX_3D_TEXTURE_SIZE";
    case GL_VERTEX_ARRAY:
        return "GL_VERTEX_ARRAY";
    case GL_NORMAL_ARRAY:
        return "GL_NORMAL_ARRAY";
    case GL_COLOR_ARRAY:
        return "GL_COLOR_ARRAY";
    case GL_INDEX_ARRAY:
        return "GL_INDEX_ARRAY";
    case GL_TEXTURE_COORD_ARRAY:
        return "GL_TEXTURE_COORD_ARRAY";
    case GL_EDGE_FLAG_ARRAY:
        return "GL_EDGE_FLAG_ARRAY";
    case GL_VERTEX_ARRAY_SIZE:
        return "GL_VERTEX_ARRAY_SIZE";
    case GL_VERTEX_ARRAY_TYPE:
        return "GL_VERTEX_ARRAY_TYPE";
    case GL_VERTEX_ARRAY_STRIDE:
        return "GL_VERTEX_ARRAY_STRIDE";
    case GL_VERTEX_ARRAY_COUNT_EXT:
        return "GL_VERTEX_ARRAY_COUNT_EXT";
    case GL_NORMAL_ARRAY_TYPE:
        return "GL_NORMAL_ARRAY_TYPE";
    case GL_NORMAL_ARRAY_STRIDE:
        return "GL_NORMAL_ARRAY_STRIDE";
    case GL_NORMAL_ARRAY_COUNT_EXT:
        return "GL_NORMAL_ARRAY_COUNT_EXT";
    case GL_COLOR_ARRAY_SIZE:
        return "GL_COLOR_ARRAY_SIZE";
    case GL_COLOR_ARRAY_TYPE:
        return "GL_COLOR_ARRAY_TYPE";
    case GL_COLOR_ARRAY_STRIDE:
        return "GL_COLOR_ARRAY_STRIDE";
    case GL_COLOR_ARRAY_COUNT_EXT:
        return "GL_COLOR_ARRAY_COUNT_EXT";
    case GL_INDEX_ARRAY_TYPE:
        return "GL_INDEX_ARRAY_TYPE";
    case GL_INDEX_ARRAY_STRIDE:
        return "GL_INDEX_ARRAY_STRIDE";
    case GL_INDEX_ARRAY_COUNT_EXT:
        return "GL_INDEX_ARRAY_COUNT_EXT";
    case GL_TEXTURE_COORD_ARRAY_SIZE:
        return "GL_TEXTURE_COORD_ARRAY_SIZE";
    case GL_TEXTURE_COORD_ARRAY_TYPE:
        return "GL_TEXTURE_COORD_ARRAY_TYPE";
    case GL_TEXTURE_COORD_ARRAY_STRIDE:
        return "GL_TEXTURE_COORD_ARRAY_STRIDE";
    case GL_TEXTURE_COORD_ARRAY_COUNT_EXT:
        return "GL_TEXTURE_COORD_ARRAY_COUNT_EXT";
    case GL_EDGE_FLAG_ARRAY_STRIDE:
        return "GL_EDGE_FLAG_ARRAY_STRIDE";
    case GL_EDGE_FLAG_ARRAY_COUNT_EXT:
        return "GL_EDGE_FLAG_ARRAY_COUNT_EXT";
    case GL_VERTEX_ARRAY_POINTER:
        return "GL_VERTEX_ARRAY_POINTER";
    case GL_NORMAL_ARRAY_POINTER:
        return "GL_NORMAL_ARRAY_POINTER";
    case GL_COLOR_ARRAY_POINTER:
        return "GL_COLOR_ARRAY_POINTER";
    case GL_INDEX_ARRAY_POINTER:
        return "GL_INDEX_ARRAY_POINTER";
    case GL_TEXTURE_COORD_ARRAY_POINTER:
        return "GL_TEXTURE_COORD_ARRAY_POINTER";
    case GL_EDGE_FLAG_ARRAY_POINTER:
        return "GL_EDGE_FLAG_ARRAY_POINTER";
    case GL_INTERLACE_SGIX:
        return "GL_INTERLACE_SGIX";
    case GL_DETAIL_TEXTURE_2D_SGIS:
        return "GL_DETAIL_TEXTURE_2D_SGIS";
    case GL_DETAIL_TEXTURE_2D_BINDING_SGIS:
        return "GL_DETAIL_TEXTURE_2D_BINDING_SGIS";
    case GL_LINEAR_DETAIL_SGIS:
        return "GL_LINEAR_DETAIL_SGIS";
    case GL_LINEAR_DETAIL_ALPHA_SGIS:
        return "GL_LINEAR_DETAIL_ALPHA_SGIS";
    case GL_LINEAR_DETAIL_COLOR_SGIS:
        return "GL_LINEAR_DETAIL_COLOR_SGIS";
    case GL_DETAIL_TEXTURE_LEVEL_SGIS:
        return "GL_DETAIL_TEXTURE_LEVEL_SGIS";
    case GL_DETAIL_TEXTURE_MODE_SGIS:
        return "GL_DETAIL_TEXTURE_MODE_SGIS";
    case GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS:
        return "GL_DETAIL_TEXTURE_FUNC_POINTS_SGIS";
    case GL_MULTISAMPLE:
        return "GL_MULTISAMPLE";
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        return "GL_SAMPLE_ALPHA_TO_COVERAGE";
    case GL_SAMPLE_ALPHA_TO_ONE:
        return "GL_SAMPLE_ALPHA_TO_ONE";
    case GL_SAMPLE_COVERAGE:
        return "GL_SAMPLE_COVERAGE";
    case GL_1PASS_EXT:
        return "GL_1PASS_EXT";
    case GL_2PASS_0_EXT:
        return "GL_2PASS_0_EXT";
    case GL_2PASS_1_EXT:
        return "GL_2PASS_1_EXT";
    case GL_4PASS_0_EXT:
        return "GL_4PASS_0_EXT";
    case GL_4PASS_1_EXT:
        return "GL_4PASS_1_EXT";
    case GL_4PASS_2_EXT:
        return "GL_4PASS_2_EXT";
    case GL_4PASS_3_EXT:
        return "GL_4PASS_3_EXT";
    case GL_SAMPLE_BUFFERS:
        return "GL_SAMPLE_BUFFERS";
    case GL_SAMPLES:
        return "GL_SAMPLES";
    case GL_SAMPLE_COVERAGE_VALUE:
        return "GL_SAMPLE_COVERAGE_VALUE";
    case GL_SAMPLE_COVERAGE_INVERT:
        return "GL_SAMPLE_COVERAGE_INVERT";
    case GL_SAMPLE_PATTERN_EXT:
        return "GL_SAMPLE_PATTERN_EXT";
    case GL_LINEAR_SHARPEN_SGIS:
        return "GL_LINEAR_SHARPEN_SGIS";
    case GL_LINEAR_SHARPEN_ALPHA_SGIS:
        return "GL_LINEAR_SHARPEN_ALPHA_SGIS";
    case GL_LINEAR_SHARPEN_COLOR_SGIS:
        return "GL_LINEAR_SHARPEN_COLOR_SGIS";
    case GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS:
        return "GL_SHARPEN_TEXTURE_FUNC_POINTS_SGIS";
    case GL_COLOR_MATRIX:
        return "GL_COLOR_MATRIX";
    case GL_COLOR_MATRIX_STACK_DEPTH:
        return "GL_COLOR_MATRIX_STACK_DEPTH";
    case GL_MAX_COLOR_MATRIX_STACK_DEPTH:
        return "GL_MAX_COLOR_MATRIX_STACK_DEPTH";
    case GL_POST_COLOR_MATRIX_RED_SCALE:
        return "GL_POST_COLOR_MATRIX_RED_SCALE";
    case GL_POST_COLOR_MATRIX_GREEN_SCALE:
        return "GL_POST_COLOR_MATRIX_GREEN_SCALE";
    case GL_POST_COLOR_MATRIX_BLUE_SCALE:
        return "GL_POST_COLOR_MATRIX_BLUE_SCALE";
    case GL_POST_COLOR_MATRIX_ALPHA_SCALE:
        return "GL_POST_COLOR_MATRIX_ALPHA_SCALE";
    case GL_POST_COLOR_MATRIX_RED_BIAS:
        return "GL_POST_COLOR_MATRIX_RED_BIAS";
    case GL_POST_COLOR_MATRIX_GREEN_BIAS:
        return "GL_POST_COLOR_MATRIX_GREEN_BIAS";
    case GL_POST_COLOR_MATRIX_BLUE_BIAS:
        return "GL_POST_COLOR_MATRIX_BLUE_BIAS";
    case GL_POST_COLOR_MATRIX_ALPHA_BIAS:
        return "GL_POST_COLOR_MATRIX_ALPHA_BIAS";
    case GL_TEXTURE_COLOR_TABLE_SGI:
        return "GL_TEXTURE_COLOR_TABLE_SGI";
    case GL_PROXY_TEXTURE_COLOR_TABLE_SGI:
        return "GL_PROXY_TEXTURE_COLOR_TABLE_SGI";
    case GL_TEXTURE_ENV_BIAS_SGIX:
        return "GL_TEXTURE_ENV_BIAS_SGIX";
    case GL_TEXTURE_COMPARE_FAIL_VALUE_ARB:
        return "GL_TEXTURE_COMPARE_FAIL_VALUE_ARB";
    case GL_BLEND_DST_RGB:
        return "GL_BLEND_DST_RGB";
    case GL_BLEND_SRC_RGB:
        return "GL_BLEND_SRC_RGB";
    case GL_BLEND_DST_ALPHA:
        return "GL_BLEND_DST_ALPHA";
    case GL_BLEND_SRC_ALPHA:
        return "GL_BLEND_SRC_ALPHA";
    case GL_422_EXT:
        return "GL_422_EXT";
    case GL_422_REV_EXT:
        return "GL_422_REV_EXT";
    case GL_422_AVERAGE_EXT:
        return "GL_422_AVERAGE_EXT";
    case GL_422_REV_AVERAGE_EXT:
        return "GL_422_REV_AVERAGE_EXT";
    case GL_COLOR_TABLE:
        return "GL_COLOR_TABLE";
    case GL_POST_CONVOLUTION_COLOR_TABLE:
        return "GL_POST_CONVOLUTION_COLOR_TABLE";
    case GL_POST_COLOR_MATRIX_COLOR_TABLE:
        return "GL_POST_COLOR_MATRIX_COLOR_TABLE";
    case GL_PROXY_COLOR_TABLE:
        return "GL_PROXY_COLOR_TABLE";
    case GL_PROXY_POST_CONVOLUTION_COLOR_TABLE:
        return "GL_PROXY_POST_CONVOLUTION_COLOR_TABLE";
    case GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE:
        return "GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE";
    case GL_COLOR_TABLE_SCALE:
        return "GL_COLOR_TABLE_SCALE";
    case GL_COLOR_TABLE_BIAS:
        return "GL_COLOR_TABLE_BIAS";
    case GL_COLOR_TABLE_FORMAT:
        return "GL_COLOR_TABLE_FORMAT";
    case GL_COLOR_TABLE_WIDTH:
        return "GL_COLOR_TABLE_WIDTH";
    case GL_COLOR_TABLE_RED_SIZE:
        return "GL_COLOR_TABLE_RED_SIZE";
    case GL_COLOR_TABLE_GREEN_SIZE:
        return "GL_COLOR_TABLE_GREEN_SIZE";
    case GL_COLOR_TABLE_BLUE_SIZE:
        return "GL_COLOR_TABLE_BLUE_SIZE";
    case GL_COLOR_TABLE_ALPHA_SIZE:
        return "GL_COLOR_TABLE_ALPHA_SIZE";
    case GL_COLOR_TABLE_LUMINANCE_SIZE:
        return "GL_COLOR_TABLE_LUMINANCE_SIZE";
    case GL_COLOR_TABLE_INTENSITY_SIZE:
        return "GL_COLOR_TABLE_INTENSITY_SIZE";
    case GL_BGR:
        return "GL_BGR";
    case GL_BGRA:
        return "GL_BGRA";
    case GL_COLOR_INDEX1_EXT:
        return "GL_COLOR_INDEX1_EXT";
    case GL_COLOR_INDEX2_EXT:
        return "GL_COLOR_INDEX2_EXT";
    case GL_COLOR_INDEX4_EXT:
        return "GL_COLOR_INDEX4_EXT";
    case GL_COLOR_INDEX8_EXT:
        return "GL_COLOR_INDEX8_EXT";
    case GL_COLOR_INDEX12_EXT:
        return "GL_COLOR_INDEX12_EXT";
    case GL_COLOR_INDEX16_EXT:
        return "GL_COLOR_INDEX16_EXT";
    case GL_MAX_ELEMENTS_VERTICES:
        return "GL_MAX_ELEMENTS_VERTICES";
    case GL_MAX_ELEMENTS_INDICES:
        return "GL_MAX_ELEMENTS_INDICES";
    case GL_PHONG_WIN:
        return "GL_PHONG_WIN";
    case GL_PHONG_HINT_WIN:
        return "GL_PHONG_HINT_WIN";
    case GL_FOG_SPECULAR_TEXTURE_WIN:
        return "GL_FOG_SPECULAR_TEXTURE_WIN";
    case GL_TEXTURE_INDEX_SIZE_EXT:
        return "GL_TEXTURE_INDEX_SIZE_EXT";
    case GL_CLIP_VOLUME_CLIPPING_HINT_EXT:
        return "GL_CLIP_VOLUME_CLIPPING_HINT_EXT";
    case GL_DUAL_ALPHA4_SGIS:
        return "GL_DUAL_ALPHA4_SGIS";
    case GL_DUAL_ALPHA8_SGIS:
        return "GL_DUAL_ALPHA8_SGIS";
    case GL_DUAL_ALPHA12_SGIS:
        return "GL_DUAL_ALPHA12_SGIS";
    case GL_DUAL_ALPHA16_SGIS:
        return "GL_DUAL_ALPHA16_SGIS";
    case GL_DUAL_LUMINANCE4_SGIS:
        return "GL_DUAL_LUMINANCE4_SGIS";
    case GL_DUAL_LUMINANCE8_SGIS:
        return "GL_DUAL_LUMINANCE8_SGIS";
    case GL_DUAL_LUMINANCE12_SGIS:
        return "GL_DUAL_LUMINANCE12_SGIS";
    case GL_DUAL_LUMINANCE16_SGIS:
        return "GL_DUAL_LUMINANCE16_SGIS";
    case GL_DUAL_INTENSITY4_SGIS:
        return "GL_DUAL_INTENSITY4_SGIS";
    case GL_DUAL_INTENSITY8_SGIS:
        return "GL_DUAL_INTENSITY8_SGIS";
    case GL_DUAL_INTENSITY12_SGIS:
        return "GL_DUAL_INTENSITY12_SGIS";
    case GL_DUAL_INTENSITY16_SGIS:
        return "GL_DUAL_INTENSITY16_SGIS";
    case GL_DUAL_LUMINANCE_ALPHA4_SGIS:
        return "GL_DUAL_LUMINANCE_ALPHA4_SGIS";
    case GL_DUAL_LUMINANCE_ALPHA8_SGIS:
        return "GL_DUAL_LUMINANCE_ALPHA8_SGIS";
    case GL_QUAD_ALPHA4_SGIS:
        return "GL_QUAD_ALPHA4_SGIS";
    case GL_QUAD_ALPHA8_SGIS:
        return "GL_QUAD_ALPHA8_SGIS";
    case GL_QUAD_LUMINANCE4_SGIS:
        return "GL_QUAD_LUMINANCE4_SGIS";
    case GL_QUAD_LUMINANCE8_SGIS:
        return "GL_QUAD_LUMINANCE8_SGIS";
    case GL_QUAD_INTENSITY4_SGIS:
        return "GL_QUAD_INTENSITY4_SGIS";
    case GL_QUAD_INTENSITY8_SGIS:
        return "GL_QUAD_INTENSITY8_SGIS";
    case GL_DUAL_TEXTURE_SELECT_SGIS:
        return "GL_DUAL_TEXTURE_SELECT_SGIS";
    case GL_QUAD_TEXTURE_SELECT_SGIS:
        return "GL_QUAD_TEXTURE_SELECT_SGIS";
    case GL_POINT_SIZE_MIN:
        return "GL_POINT_SIZE_MIN";
    case GL_POINT_SIZE_MAX:
        return "GL_POINT_SIZE_MAX";
    case GL_POINT_FADE_THRESHOLD_SIZE:
        return "GL_POINT_FADE_THRESHOLD_SIZE";
    case GL_POINT_DISTANCE_ATTENUATION:
        return "GL_POINT_DISTANCE_ATTENUATION";
    case GL_FOG_FUNC_SGIS:
        return "GL_FOG_FUNC_SGIS";
    case GL_FOG_FUNC_POINTS_SGIS:
        return "GL_FOG_FUNC_POINTS_SGIS";
    case GL_MAX_FOG_FUNC_POINTS_SGIS:
        return "GL_MAX_FOG_FUNC_POINTS_SGIS";
    case GL_CLAMP_TO_BORDER:
        return "GL_CLAMP_TO_BORDER";
    case GL_TEXTURE_MULTI_BUFFER_HINT_SGIX:
        return "GL_TEXTURE_MULTI_BUFFER_HINT_SGIX";
    case GL_CLAMP_TO_EDGE:
        return "GL_CLAMP_TO_EDGE";
    case GL_PACK_SKIP_VOLUMES_SGIS:
        return "GL_PACK_SKIP_VOLUMES_SGIS";
    case GL_PACK_IMAGE_DEPTH_SGIS:
        return "GL_PACK_IMAGE_DEPTH_SGIS";
    case GL_UNPACK_SKIP_VOLUMES_SGIS:
        return "GL_UNPACK_SKIP_VOLUMES_SGIS";
    case GL_UNPACK_IMAGE_DEPTH_SGIS:
        return "GL_UNPACK_IMAGE_DEPTH_SGIS";
    case GL_TEXTURE_4D_SGIS:
        return "GL_TEXTURE_4D_SGIS";
    case GL_PROXY_TEXTURE_4D_SGIS:
        return "GL_PROXY_TEXTURE_4D_SGIS";
    case GL_TEXTURE_4DSIZE_SGIS:
        return "GL_TEXTURE_4DSIZE_SGIS";
    case GL_TEXTURE_WRAP_Q_SGIS:
        return "GL_TEXTURE_WRAP_Q_SGIS";
    case GL_MAX_4D_TEXTURE_SIZE_SGIS:
        return "GL_MAX_4D_TEXTURE_SIZE_SGIS";
    case GL_PIXEL_TEX_GEN_SGIX:
        return "GL_PIXEL_TEX_GEN_SGIX";
    case GL_TEXTURE_MIN_LOD:
        return "GL_TEXTURE_MIN_LOD";
    case GL_TEXTURE_MAX_LOD:
        return "GL_TEXTURE_MAX_LOD";
    case GL_TEXTURE_BASE_LEVEL:
        return "GL_TEXTURE_BASE_LEVEL";
    case GL_TEXTURE_MAX_LEVEL:
        return "GL_TEXTURE_MAX_LEVEL";
    case GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX:
        return "GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX";
    case GL_PIXEL_TILE_CACHE_INCREMENT_SGIX:
        return "GL_PIXEL_TILE_CACHE_INCREMENT_SGIX";
    case GL_PIXEL_TILE_WIDTH_SGIX:
        return "GL_PIXEL_TILE_WIDTH_SGIX";
    case GL_PIXEL_TILE_HEIGHT_SGIX:
        return "GL_PIXEL_TILE_HEIGHT_SGIX";
    case GL_PIXEL_TILE_GRID_WIDTH_SGIX:
        return "GL_PIXEL_TILE_GRID_WIDTH_SGIX";
    case GL_PIXEL_TILE_GRID_HEIGHT_SGIX:
        return "GL_PIXEL_TILE_GRID_HEIGHT_SGIX";
    case GL_PIXEL_TILE_GRID_DEPTH_SGIX:
        return "GL_PIXEL_TILE_GRID_DEPTH_SGIX";
    case GL_PIXEL_TILE_CACHE_SIZE_SGIX:
        return "GL_PIXEL_TILE_CACHE_SIZE_SGIX";
    case GL_FILTER4_SGIS:
        return "GL_FILTER4_SGIS";
    case GL_TEXTURE_FILTER4_SIZE_SGIS:
        return "GL_TEXTURE_FILTER4_SIZE_SGIS";
    case GL_SPRITE_SGIX:
        return "GL_SPRITE_SGIX";
    case GL_SPRITE_MODE_SGIX:
        return "GL_SPRITE_MODE_SGIX";
    case GL_SPRITE_AXIS_SGIX:
        return "GL_SPRITE_AXIS_SGIX";
    case GL_SPRITE_TRANSLATION_SGIX:
        return "GL_SPRITE_TRANSLATION_SGIX";
    case GL_SPRITE_AXIAL_SGIX:
        return "GL_SPRITE_AXIAL_SGIX";
    case GL_SPRITE_OBJECT_ALIGNED_SGIX:
        return "GL_SPRITE_OBJECT_ALIGNED_SGIX";
    case GL_SPRITE_EYE_ALIGNED_SGIX:
        return "GL_SPRITE_EYE_ALIGNED_SGIX";
    case GL_TEXTURE_4D_BINDING_SGIS:
        return "GL_TEXTURE_4D_BINDING_SGIS";
    case GL_IGNORE_BORDER_HP:
        return "GL_IGNORE_BORDER_HP";
    case GL_CONSTANT_BORDER:
        return "GL_CONSTANT_BORDER";
    case GL_REPLICATE_BORDER:
        return "GL_REPLICATE_BORDER";
    case GL_CONVOLUTION_BORDER_COLOR:
        return "GL_CONVOLUTION_BORDER_COLOR";
    case GL_IMAGE_SCALE_X_HP:
        return "GL_IMAGE_SCALE_X_HP";
    case GL_IMAGE_SCALE_Y_HP:
        return "GL_IMAGE_SCALE_Y_HP";
    case GL_IMAGE_TRANSLATE_X_HP:
        return "GL_IMAGE_TRANSLATE_X_HP";
    case GL_IMAGE_TRANSLATE_Y_HP:
        return "GL_IMAGE_TRANSLATE_Y_HP";
    case GL_IMAGE_ROTATE_ANGLE_HP:
        return "GL_IMAGE_ROTATE_ANGLE_HP";
    case GL_IMAGE_ROTATE_ORIGIN_X_HP:
        return "GL_IMAGE_ROTATE_ORIGIN_X_HP";
    case GL_IMAGE_ROTATE_ORIGIN_Y_HP:
        return "GL_IMAGE_ROTATE_ORIGIN_Y_HP";
    case GL_IMAGE_MAG_FILTER_HP:
        return "GL_IMAGE_MAG_FILTER_HP";
    case GL_IMAGE_MIN_FILTER_HP:
        return "GL_IMAGE_MIN_FILTER_HP";
    case GL_IMAGE_CUBIC_WEIGHT_HP:
        return "GL_IMAGE_CUBIC_WEIGHT_HP";
    case GL_CUBIC_HP:
        return "GL_CUBIC_HP";
    case GL_AVERAGE_HP:
        return "GL_AVERAGE_HP";
    case GL_IMAGE_TRANSFORM_2D_HP:
        return "GL_IMAGE_TRANSFORM_2D_HP";
    case GL_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP:
        return "GL_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP";
    case GL_PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP:
        return "GL_PROXY_POST_IMAGE_TRANSFORM_COLOR_TABLE_HP";
    case GL_OCCLUSION_TEST_HP:
        return "GL_OCCLUSION_TEST_HP";
    case GL_OCCLUSION_TEST_RESULT_HP:
        return "GL_OCCLUSION_TEST_RESULT_HP";
    case GL_TEXTURE_LIGHTING_MODE_HP:
        return "GL_TEXTURE_LIGHTING_MODE_HP";
    case GL_TEXTURE_POST_SPECULAR_HP:
        return "GL_TEXTURE_POST_SPECULAR_HP";
    case GL_TEXTURE_PRE_SPECULAR_HP:
        return "GL_TEXTURE_PRE_SPECULAR_HP";
    case GL_LINEAR_CLIPMAP_LINEAR_SGIX:
        return "GL_LINEAR_CLIPMAP_LINEAR_SGIX";
    case GL_TEXTURE_CLIPMAP_CENTER_SGIX:
        return "GL_TEXTURE_CLIPMAP_CENTER_SGIX";
    case GL_TEXTURE_CLIPMAP_FRAME_SGIX:
        return "GL_TEXTURE_CLIPMAP_FRAME_SGIX";
    case GL_TEXTURE_CLIPMAP_OFFSET_SGIX:
        return "GL_TEXTURE_CLIPMAP_OFFSET_SGIX";
    case GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX:
        return "GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX";
    case GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX:
        return "GL_TEXTURE_CLIPMAP_LOD_OFFSET_SGIX";
    case GL_TEXTURE_CLIPMAP_DEPTH_SGIX:
        return "GL_TEXTURE_CLIPMAP_DEPTH_SGIX";
    case GL_MAX_CLIPMAP_DEPTH_SGIX:
        return "GL_MAX_CLIPMAP_DEPTH_SGIX";
    case GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX:
        return "GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX";
    case GL_POST_TEXTURE_FILTER_BIAS_SGIX:
        return "GL_POST_TEXTURE_FILTER_BIAS_SGIX";
    case GL_POST_TEXTURE_FILTER_SCALE_SGIX:
        return "GL_POST_TEXTURE_FILTER_SCALE_SGIX";
    case GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX:
        return "GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX";
    case GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX:
        return "GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX";
    case GL_REFERENCE_PLANE_SGIX:
        return "GL_REFERENCE_PLANE_SGIX";
    case GL_REFERENCE_PLANE_EQUATION_SGIX:
        return "GL_REFERENCE_PLANE_EQUATION_SGIX";
    case GL_IR_INSTRUMENT1_SGIX:
        return "GL_IR_INSTRUMENT1_SGIX";
    case GL_INSTRUMENT_BUFFER_POINTER_SGIX:
        return "GL_INSTRUMENT_BUFFER_POINTER_SGIX";
    case GL_INSTRUMENT_MEASUREMENTS_SGIX:
        return "GL_INSTRUMENT_MEASUREMENTS_SGIX";
    case GL_LIST_PRIORITY_SGIX:
        return "GL_LIST_PRIORITY_SGIX";
    case GL_CALLIGRAPHIC_FRAGMENT_SGIX:
        return "GL_CALLIGRAPHIC_FRAGMENT_SGIX";
    case GL_PIXEL_TEX_GEN_Q_CEILING_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_CEILING_SGIX";
    case GL_PIXEL_TEX_GEN_Q_ROUND_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_ROUND_SGIX";
    case GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX:
        return "GL_PIXEL_TEX_GEN_Q_FLOOR_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_REPLACE_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_NO_REPLACE_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_LS_SGIX";
    case GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX:
        return "GL_PIXEL_TEX_GEN_ALPHA_MS_SGIX";
    case GL_FRAMEZOOM_SGIX:
        return "GL_FRAMEZOOM_SGIX";
    case GL_FRAMEZOOM_FACTOR_SGIX:
        return "GL_FRAMEZOOM_FACTOR_SGIX";
    case GL_MAX_FRAMEZOOM_FACTOR_SGIX:
        return "GL_MAX_FRAMEZOOM_FACTOR_SGIX";
    case GL_TEXTURE_LOD_BIAS_S_SGIX:
        return "GL_TEXTURE_LOD_BIAS_S_SGIX";
    case GL_TEXTURE_LOD_BIAS_T_SGIX:
        return "GL_TEXTURE_LOD_BIAS_T_SGIX";
    case GL_TEXTURE_LOD_BIAS_R_SGIX:
        return "GL_TEXTURE_LOD_BIAS_R_SGIX";
    case GL_GENERATE_MIPMAP:
        return "GL_GENERATE_MIPMAP";
    case GL_GENERATE_MIPMAP_HINT:
        return "GL_GENERATE_MIPMAP_HINT";
    case GL_GEOMETRY_DEFORMATION_SGIX:
        return "GL_GEOMETRY_DEFORMATION_SGIX";
    case GL_TEXTURE_DEFORMATION_SGIX:
        return "GL_TEXTURE_DEFORMATION_SGIX";
    case GL_DEFORMATIONS_MASK_SGIX:
        return "GL_DEFORMATIONS_MASK_SGIX";
    case GL_MAX_DEFORMATION_ORDER_SGIX:
        return "GL_MAX_DEFORMATION_ORDER_SGIX";
    case GL_FOG_OFFSET_SGIX:
        return "GL_FOG_OFFSET_SGIX";
    case GL_FOG_OFFSET_VALUE_SGIX:
        return "GL_FOG_OFFSET_VALUE_SGIX";
    case GL_TEXTURE_COMPARE_SGIX:
        return "GL_TEXTURE_COMPARE_SGIX";
    case GL_TEXTURE_COMPARE_OPERATOR_SGIX:
        return "GL_TEXTURE_COMPARE_OPERATOR_SGIX";
    case GL_TEXTURE_LEQUAL_R_SGIX:
        return "GL_TEXTURE_LEQUAL_R_SGIX";
    case GL_TEXTURE_GEQUAL_R_SGIX:
        return "GL_TEXTURE_GEQUAL_R_SGIX";
    case GL_DEPTH_COMPONENT16:
        return "GL_DEPTH_COMPONENT16";
    case GL_DEPTH_COMPONENT24:
        return "GL_DEPTH_COMPONENT24";
    case GL_DEPTH_COMPONENT32:
        return "GL_DEPTH_COMPONENT32";
    case GL_ARRAY_ELEMENT_LOCK_FIRST_EXT:
        return "GL_ARRAY_ELEMENT_LOCK_FIRST_EXT";
    case GL_ARRAY_ELEMENT_LOCK_COUNT_EXT:
        return "GL_ARRAY_ELEMENT_LOCK_COUNT_EXT";
    case GL_CULL_VERTEX_EXT:
        return "GL_CULL_VERTEX_EXT";
    case GL_CULL_VERTEX_EYE_POSITION_EXT:
        return "GL_CULL_VERTEX_EYE_POSITION_EXT";
    case GL_CULL_VERTEX_OBJECT_POSITION_EXT:
        return "GL_CULL_VERTEX_OBJECT_POSITION_EXT";
    case GL_IUI_V2F_EXT:
        return "GL_IUI_V2F_EXT";
    case GL_IUI_V3F_EXT:
        return "GL_IUI_V3F_EXT";
    case GL_IUI_N3F_V2F_EXT:
        return "GL_IUI_N3F_V2F_EXT";
    case GL_IUI_N3F_V3F_EXT:
        return "GL_IUI_N3F_V3F_EXT";
    case GL_T2F_IUI_V2F_EXT:
        return "GL_T2F_IUI_V2F_EXT";
    case GL_T2F_IUI_V3F_EXT:
        return "GL_T2F_IUI_V3F_EXT";
    case GL_T2F_IUI_N3F_V2F_EXT:
        return "GL_T2F_IUI_N3F_V2F_EXT";
    case GL_T2F_IUI_N3F_V3F_EXT:
        return "GL_T2F_IUI_N3F_V3F_EXT";
    case GL_INDEX_TEST_EXT:
        return "GL_INDEX_TEST_EXT";
    case GL_INDEX_TEST_FUNC_EXT:
        return "GL_INDEX_TEST_FUNC_EXT";
    case GL_INDEX_TEST_REF_EXT:
        return "GL_INDEX_TEST_REF_EXT";
    case GL_INDEX_MATERIAL_EXT:
        return "GL_INDEX_MATERIAL_EXT";
    case GL_INDEX_MATERIAL_PARAMETER_EXT:
        return "GL_INDEX_MATERIAL_PARAMETER_EXT";
    case GL_INDEX_MATERIAL_FACE_EXT:
        return "GL_INDEX_MATERIAL_FACE_EXT";
    case GL_YCRCB_422_SGIX:
        return "GL_YCRCB_422_SGIX";
    case GL_YCRCB_444_SGIX:
        return "GL_YCRCB_444_SGIX";
    case GL_WRAP_BORDER_SUN:
        return "GL_WRAP_BORDER_SUN";
    case GL_UNPACK_CONSTANT_DATA_SUNX:
        return "GL_UNPACK_CONSTANT_DATA_SUNX";
    case GL_TEXTURE_CONSTANT_DATA_SUNX:
        return "GL_TEXTURE_CONSTANT_DATA_SUNX";
    case GL_TRIANGLE_LIST_SUN:
        return "GL_TRIANGLE_LIST_SUN";
    case GL_REPLACEMENT_CODE_SUN:
        return "GL_REPLACEMENT_CODE_SUN";
    case GL_GLOBAL_ALPHA_SUN:
        return "GL_GLOBAL_ALPHA_SUN";
    case GL_GLOBAL_ALPHA_FACTOR_SUN:
        return "GL_GLOBAL_ALPHA_FACTOR_SUN";
    case GL_TEXTURE_COLOR_WRITEMASK_SGIS:
        return "GL_TEXTURE_COLOR_WRITEMASK_SGIS";
    case GL_EYE_DISTANCE_TO_POINT_SGIS:
        return "GL_EYE_DISTANCE_TO_POINT_SGIS";
    case GL_OBJECT_DISTANCE_TO_POINT_SGIS:
        return "GL_OBJECT_DISTANCE_TO_POINT_SGIS";
    case GL_EYE_DISTANCE_TO_LINE_SGIS:
        return "GL_EYE_DISTANCE_TO_LINE_SGIS";
    case GL_OBJECT_DISTANCE_TO_LINE_SGIS:
        return "GL_OBJECT_DISTANCE_TO_LINE_SGIS";
    case GL_EYE_POINT_SGIS:
        return "GL_EYE_POINT_SGIS";
    case GL_OBJECT_POINT_SGIS:
        return "GL_OBJECT_POINT_SGIS";
    case GL_EYE_LINE_SGIS:
        return "GL_EYE_LINE_SGIS";
    case GL_OBJECT_LINE_SGIS:
        return "GL_OBJECT_LINE_SGIS";
    case GL_LIGHT_MODEL_COLOR_CONTROL:
        return "GL_LIGHT_MODEL_COLOR_CONTROL";
    case GL_SINGLE_COLOR:
        return "GL_SINGLE_COLOR";
    case GL_SEPARATE_SPECULAR_COLOR:
        return "GL_SEPARATE_SPECULAR_COLOR";
    case GL_SHARED_TEXTURE_PALETTE_EXT:
        return "GL_SHARED_TEXTURE_PALETTE_EXT";
    case GL_FOG_SCALE_SGIX:
        return "GL_FOG_SCALE_SGIX";
    case GL_FOG_SCALE_VALUE_SGIX:
        return "GL_FOG_SCALE_VALUE_SGIX";
    case GL_TEXT_FRAGMENT_SHADER_ATI:
        return "GL_TEXT_FRAGMENT_SHADER_ATI";
    case GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING:
        return "GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING";
    case GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE:
        return "GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE";
    case GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE";
    case GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE:
        return "GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE";
    case GL_FRAMEBUFFER_DEFAULT:
        return "GL_FRAMEBUFFER_DEFAULT";
    case GL_FRAMEBUFFER_UNDEFINED:
        return "GL_FRAMEBUFFER_UNDEFINED";
    case GL_DEPTH_STENCIL_ATTACHMENT:
        return "GL_DEPTH_STENCIL_ATTACHMENT";
    case GL_MAJOR_VERSION:
        return "GL_MAJOR_VERSION";
    case GL_MINOR_VERSION:
        return "GL_MINOR_VERSION";
    case GL_NUM_EXTENSIONS:
        return "GL_NUM_EXTENSIONS";
    case GL_CONTEXT_FLAGS:
        return "GL_CONTEXT_FLAGS";
    case GL_INDEX:
        return "GL_INDEX";
    case GL_COMPRESSED_RED:
        return "GL_COMPRESSED_RED";
    case GL_COMPRESSED_RG:
        return "GL_COMPRESSED_RG";
    case GL_RG:
        return "GL_RG";
    case GL_RG_INTEGER:
        return "GL_RG_INTEGER";
    case GL_R8:
        return "GL_R8";
    case GL_R16:
        return "GL_R16";
    case GL_RG8:
        return "GL_RG8";
    case GL_RG16:
        return "GL_RG16";
    case GL_R16F:
        return "GL_R16F";
    case GL_R32F:
        return "GL_R32F";
    case GL_RG16F:
        return "GL_RG16F";
    case GL_RG32F:
        return "GL_RG32F";
    case GL_R8I:
        return "GL_R8I";
    case GL_R8UI:
        return "GL_R8UI";
    case GL_R16I:
        return "GL_R16I";
    case GL_R16UI:
        return "GL_R16UI";
    case GL_R32I:
        return "GL_R32I";
    case GL_R32UI:
        return "GL_R32UI";
    case GL_RG8I:
        return "GL_RG8I";
    case GL_RG8UI:
        return "GL_RG8UI";
    case GL_RG16I:
        return "GL_RG16I";
    case GL_RG16UI:
        return "GL_RG16UI";
    case GL_RG32I:
        return "GL_RG32I";
    case GL_RG32UI:
        return "GL_RG32UI";
    case GL_SYNC_CL_EVENT_ARB:
        return "GL_SYNC_CL_EVENT_ARB";
    case GL_SYNC_CL_EVENT_COMPLETE_ARB:
        return "GL_SYNC_CL_EVENT_COMPLETE_ARB";
    case GL_DEBUG_OUTPUT_SYNCHRONOUS:
        return "GL_DEBUG_OUTPUT_SYNCHRONOUS";
    case GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH:
        return "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH";
    case GL_DEBUG_CALLBACK_FUNCTION:
        return "GL_DEBUG_CALLBACK_FUNCTION";
    case GL_DEBUG_CALLBACK_USER_PARAM:
        return "GL_DEBUG_CALLBACK_USER_PARAM";
    case GL_DEBUG_SOURCE_API:
        return "GL_DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "GL_DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "GL_DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER:
        return "GL_DEBUG_SOURCE_OTHER";
    case GL_DEBUG_TYPE_ERROR:
        return "GL_DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "GL_DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "GL_DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_OTHER:
        return "GL_DEBUG_TYPE_OTHER";
    case GL_LOSE_CONTEXT_ON_RESET_ARB:
        return "GL_LOSE_CONTEXT_ON_RESET_ARB";
    case GL_GUILTY_CONTEXT_RESET_ARB:
        return "GL_GUILTY_CONTEXT_RESET_ARB";
    case GL_INNOCENT_CONTEXT_RESET_ARB:
        return "GL_INNOCENT_CONTEXT_RESET_ARB";
    case GL_UNKNOWN_CONTEXT_RESET_ARB:
        return "GL_UNKNOWN_CONTEXT_RESET_ARB";
    case GL_RESET_NOTIFICATION_STRATEGY_ARB:
        return "GL_RESET_NOTIFICATION_STRATEGY_ARB";
    case GL_PROGRAM_BINARY_RETRIEVABLE_HINT:
        return "GL_PROGRAM_BINARY_RETRIEVABLE_HINT";
    case GL_PROGRAM_SEPARABLE:
        return "GL_PROGRAM_SEPARABLE";
    case GL_ACTIVE_PROGRAM:
        return "GL_ACTIVE_PROGRAM";
    case GL_PROGRAM_PIPELINE_BINDING:
        return "GL_PROGRAM_PIPELINE_BINDING";
    case GL_MAX_VIEWPORTS:
        return "GL_MAX_VIEWPORTS";
    case GL_VIEWPORT_SUBPIXEL_BITS:
        return "GL_VIEWPORT_SUBPIXEL_BITS";
    case GL_VIEWPORT_BOUNDS_RANGE:
        return "GL_VIEWPORT_BOUNDS_RANGE";
    case GL_LAYER_PROVOKING_VERTEX:
        return "GL_LAYER_PROVOKING_VERTEX";
    case GL_VIEWPORT_INDEX_PROVOKING_VERTEX:
        return "GL_VIEWPORT_INDEX_PROVOKING_VERTEX";
    case GL_UNDEFINED_VERTEX:
        return "GL_UNDEFINED_VERTEX";
    case GL_NO_RESET_NOTIFICATION_ARB:
        return "GL_NO_RESET_NOTIFICATION_ARB";
    case GL_MAX_COMPUTE_SHARED_MEMORY_SIZE:
        return "GL_MAX_COMPUTE_SHARED_MEMORY_SIZE";
    case GL_MAX_COMPUTE_UNIFORM_COMPONENTS:
        return "GL_MAX_COMPUTE_UNIFORM_COMPONENTS";
    case GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_COMPUTE_ATOMIC_COUNTERS:
        return "GL_MAX_COMPUTE_ATOMIC_COUNTERS";
    case GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS";
    case GL_COMPUTE_LOCAL_WORK_SIZE:
        return "GL_COMPUTE_LOCAL_WORK_SIZE";
    case GL_DEBUG_TYPE_MARKER:
        return "GL_DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "GL_DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "GL_DEBUG_TYPE_POP_GROUP";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        return "GL_DEBUG_SEVERITY_NOTIFICATION";
    case GL_MAX_DEBUG_GROUP_STACK_DEPTH:
        return "GL_MAX_DEBUG_GROUP_STACK_DEPTH";
    case GL_DEBUG_GROUP_STACK_DEPTH:
        return "GL_DEBUG_GROUP_STACK_DEPTH";
    case GL_MAX_UNIFORM_LOCATIONS:
        return "GL_MAX_UNIFORM_LOCATIONS";
    case GL_INTERNALFORMAT_SUPPORTED:
        return "GL_INTERNALFORMAT_SUPPORTED";
    case GL_INTERNALFORMAT_PREFERRED:
        return "GL_INTERNALFORMAT_PREFERRED";
    case GL_INTERNALFORMAT_RED_SIZE:
        return "GL_INTERNALFORMAT_RED_SIZE";
    case GL_INTERNALFORMAT_GREEN_SIZE:
        return "GL_INTERNALFORMAT_GREEN_SIZE";
    case GL_INTERNALFORMAT_BLUE_SIZE:
        return "GL_INTERNALFORMAT_BLUE_SIZE";
    case GL_INTERNALFORMAT_ALPHA_SIZE:
        return "GL_INTERNALFORMAT_ALPHA_SIZE";
    case GL_INTERNALFORMAT_DEPTH_SIZE:
        return "GL_INTERNALFORMAT_DEPTH_SIZE";
    case GL_INTERNALFORMAT_STENCIL_SIZE:
        return "GL_INTERNALFORMAT_STENCIL_SIZE";
    case GL_INTERNALFORMAT_SHARED_SIZE:
        return "GL_INTERNALFORMAT_SHARED_SIZE";
    case GL_INTERNALFORMAT_RED_TYPE:
        return "GL_INTERNALFORMAT_RED_TYPE";
    case GL_INTERNALFORMAT_GREEN_TYPE:
        return "GL_INTERNALFORMAT_GREEN_TYPE";
    case GL_INTERNALFORMAT_BLUE_TYPE:
        return "GL_INTERNALFORMAT_BLUE_TYPE";
    case GL_INTERNALFORMAT_ALPHA_TYPE:
        return "GL_INTERNALFORMAT_ALPHA_TYPE";
    case GL_INTERNALFORMAT_DEPTH_TYPE:
        return "GL_INTERNALFORMAT_DEPTH_TYPE";
    case GL_INTERNALFORMAT_STENCIL_TYPE:
        return "GL_INTERNALFORMAT_STENCIL_TYPE";
    case GL_MAX_WIDTH:
        return "GL_MAX_WIDTH";
    case GL_MAX_HEIGHT:
        return "GL_MAX_HEIGHT";
    case GL_MAX_DEPTH:
        return "GL_MAX_DEPTH";
    case GL_MAX_LAYERS:
        return "GL_MAX_LAYERS";
    case GL_MAX_COMBINED_DIMENSIONS:
        return "GL_MAX_COMBINED_DIMENSIONS";
    case GL_COLOR_COMPONENTS:
        return "GL_COLOR_COMPONENTS";
    case GL_DEPTH_COMPONENTS:
        return "GL_DEPTH_COMPONENTS";
    case GL_STENCIL_COMPONENTS:
        return "GL_STENCIL_COMPONENTS";
    case GL_COLOR_RENDERABLE:
        return "GL_COLOR_RENDERABLE";
    case GL_DEPTH_RENDERABLE:
        return "GL_DEPTH_RENDERABLE";
    case GL_STENCIL_RENDERABLE:
        return "GL_STENCIL_RENDERABLE";
    case GL_FRAMEBUFFER_RENDERABLE:
        return "GL_FRAMEBUFFER_RENDERABLE";
    case GL_FRAMEBUFFER_RENDERABLE_LAYERED:
        return "GL_FRAMEBUFFER_RENDERABLE_LAYERED";
    case GL_FRAMEBUFFER_BLEND:
        return "GL_FRAMEBUFFER_BLEND";
    case GL_READ_PIXELS:
        return "GL_READ_PIXELS";
    case GL_READ_PIXELS_FORMAT:
        return "GL_READ_PIXELS_FORMAT";
    case GL_READ_PIXELS_TYPE:
        return "GL_READ_PIXELS_TYPE";
    case GL_TEXTURE_IMAGE_FORMAT:
        return "GL_TEXTURE_IMAGE_FORMAT";
    case GL_TEXTURE_IMAGE_TYPE:
        return "GL_TEXTURE_IMAGE_TYPE";
    case GL_GET_TEXTURE_IMAGE_FORMAT:
        return "GL_GET_TEXTURE_IMAGE_FORMAT";
    case GL_GET_TEXTURE_IMAGE_TYPE:
        return "GL_GET_TEXTURE_IMAGE_TYPE";
    case GL_MIPMAP:
        return "GL_MIPMAP";
    case GL_MANUAL_GENERATE_MIPMAP:
        return "GL_MANUAL_GENERATE_MIPMAP";
    case GL_AUTO_GENERATE_MIPMAP:
        return "GL_AUTO_GENERATE_MIPMAP";
    case GL_COLOR_ENCODING:
        return "GL_COLOR_ENCODING";
    case GL_SRGB_READ:
        return "GL_SRGB_READ";
    case GL_SRGB_WRITE:
        return "GL_SRGB_WRITE";
    case GL_SRGB_DECODE_ARB:
        return "GL_SRGB_DECODE_ARB";
    case GL_FILTER:
        return "GL_FILTER";
    case GL_VERTEX_TEXTURE:
        return "GL_VERTEX_TEXTURE";
    case GL_TESS_CONTROL_TEXTURE:
        return "GL_TESS_CONTROL_TEXTURE";
    case GL_TESS_EVALUATION_TEXTURE:
        return "GL_TESS_EVALUATION_TEXTURE";
    case GL_GEOMETRY_TEXTURE:
        return "GL_GEOMETRY_TEXTURE";
    case GL_FRAGMENT_TEXTURE:
        return "GL_FRAGMENT_TEXTURE";
    case GL_COMPUTE_TEXTURE:
        return "GL_COMPUTE_TEXTURE";
    case GL_TEXTURE_SHADOW:
        return "GL_TEXTURE_SHADOW";
    case GL_TEXTURE_GATHER:
        return "GL_TEXTURE_GATHER";
    case GL_TEXTURE_GATHER_SHADOW:
        return "GL_TEXTURE_GATHER_SHADOW";
    case GL_SHADER_IMAGE_LOAD:
        return "GL_SHADER_IMAGE_LOAD";
    case GL_SHADER_IMAGE_STORE:
        return "GL_SHADER_IMAGE_STORE";
    case GL_SHADER_IMAGE_ATOMIC:
        return "GL_SHADER_IMAGE_ATOMIC";
    case GL_IMAGE_TEXEL_SIZE:
        return "GL_IMAGE_TEXEL_SIZE";
    case GL_IMAGE_COMPATIBILITY_CLASS:
        return "GL_IMAGE_COMPATIBILITY_CLASS";
    case GL_IMAGE_PIXEL_FORMAT:
        return "GL_IMAGE_PIXEL_FORMAT";
    case GL_IMAGE_PIXEL_TYPE:
        return "GL_IMAGE_PIXEL_TYPE";
    case GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST:
        return "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST";
    case GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST:
        return "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST";
    case GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE:
        return "GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE";
    case GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE:
        return "GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE";
    case GL_TEXTURE_COMPRESSED_BLOCK_WIDTH:
        return "GL_TEXTURE_COMPRESSED_BLOCK_WIDTH";
    case GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT:
        return "GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT";
    case GL_TEXTURE_COMPRESSED_BLOCK_SIZE:
        return "GL_TEXTURE_COMPRESSED_BLOCK_SIZE";
    case GL_CLEAR_BUFFER:
        return "GL_CLEAR_BUFFER";
    case GL_TEXTURE_VIEW:
        return "GL_TEXTURE_VIEW";
    case GL_VIEW_COMPATIBILITY_CLASS:
        return "GL_VIEW_COMPATIBILITY_CLASS";
    case GL_FULL_SUPPORT:
        return "GL_FULL_SUPPORT";
    case GL_CAVEAT_SUPPORT:
        return "GL_CAVEAT_SUPPORT";
    case GL_IMAGE_CLASS_4_X_32:
        return "GL_IMAGE_CLASS_4_X_32";
    case GL_IMAGE_CLASS_2_X_32:
        return "GL_IMAGE_CLASS_2_X_32";
    case GL_IMAGE_CLASS_1_X_32:
        return "GL_IMAGE_CLASS_1_X_32";
    case GL_IMAGE_CLASS_4_X_16:
        return "GL_IMAGE_CLASS_4_X_16";
    case GL_IMAGE_CLASS_2_X_16:
        return "GL_IMAGE_CLASS_2_X_16";
    case GL_IMAGE_CLASS_1_X_16:
        return "GL_IMAGE_CLASS_1_X_16";
    case GL_IMAGE_CLASS_4_X_8:
        return "GL_IMAGE_CLASS_4_X_8";
    case GL_IMAGE_CLASS_2_X_8:
        return "GL_IMAGE_CLASS_2_X_8";
    case GL_IMAGE_CLASS_1_X_8:
        return "GL_IMAGE_CLASS_1_X_8";
    case GL_IMAGE_CLASS_11_11_10:
        return "GL_IMAGE_CLASS_11_11_10";
    case GL_IMAGE_CLASS_10_10_10_2:
        return "GL_IMAGE_CLASS_10_10_10_2";
    case GL_VIEW_CLASS_128_BITS:
        return "GL_VIEW_CLASS_128_BITS";
    case GL_VIEW_CLASS_96_BITS:
        return "GL_VIEW_CLASS_96_BITS";
    case GL_VIEW_CLASS_64_BITS:
        return "GL_VIEW_CLASS_64_BITS";
    case GL_VIEW_CLASS_48_BITS:
        return "GL_VIEW_CLASS_48_BITS";
    case GL_VIEW_CLASS_32_BITS:
        return "GL_VIEW_CLASS_32_BITS";
    case GL_VIEW_CLASS_24_BITS:
        return "GL_VIEW_CLASS_24_BITS";
    case GL_VIEW_CLASS_16_BITS:
        return "GL_VIEW_CLASS_16_BITS";
    case GL_VIEW_CLASS_8_BITS:
        return "GL_VIEW_CLASS_8_BITS";
    case GL_VIEW_CLASS_S3TC_DXT1_RGB:
        return "GL_VIEW_CLASS_S3TC_DXT1_RGB";
    case GL_VIEW_CLASS_S3TC_DXT1_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT1_RGBA";
    case GL_VIEW_CLASS_S3TC_DXT3_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT3_RGBA";
    case GL_VIEW_CLASS_S3TC_DXT5_RGBA:
        return "GL_VIEW_CLASS_S3TC_DXT5_RGBA";
    case GL_VIEW_CLASS_RGTC1_RED:
        return "GL_VIEW_CLASS_RGTC1_RED";
    case GL_VIEW_CLASS_RGTC2_RG:
        return "GL_VIEW_CLASS_RGTC2_RG";
    case GL_VIEW_CLASS_BPTC_UNORM:
        return "GL_VIEW_CLASS_BPTC_UNORM";
    case GL_VIEW_CLASS_BPTC_FLOAT:
        return "GL_VIEW_CLASS_BPTC_FLOAT";
    case GL_VERTEX_ATTRIB_BINDING:
        return "GL_VERTEX_ATTRIB_BINDING";
    case GL_VERTEX_ATTRIB_RELATIVE_OFFSET:
        return "GL_VERTEX_ATTRIB_RELATIVE_OFFSET";
    case GL_VERTEX_BINDING_DIVISOR:
        return "GL_VERTEX_BINDING_DIVISOR";
    case GL_VERTEX_BINDING_OFFSET:
        return "GL_VERTEX_BINDING_OFFSET";
    case GL_VERTEX_BINDING_STRIDE:
        return "GL_VERTEX_BINDING_STRIDE";
    case GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET:
        return "GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET";
    case GL_MAX_VERTEX_ATTRIB_BINDINGS:
        return "GL_MAX_VERTEX_ATTRIB_BINDINGS";
    case GL_TEXTURE_VIEW_MIN_LEVEL:
        return "GL_TEXTURE_VIEW_MIN_LEVEL";
    case GL_TEXTURE_VIEW_NUM_LEVELS:
        return "GL_TEXTURE_VIEW_NUM_LEVELS";
    case GL_TEXTURE_VIEW_MIN_LAYER:
        return "GL_TEXTURE_VIEW_MIN_LAYER";
    case GL_TEXTURE_VIEW_NUM_LAYERS:
        return "GL_TEXTURE_VIEW_NUM_LAYERS";
    case GL_TEXTURE_IMMUTABLE_LEVELS:
        return "GL_TEXTURE_IMMUTABLE_LEVELS";
    case GL_BUFFER:
        return "GL_BUFFER";
    case GL_SHADER:
        return "GL_SHADER";
    case GL_PROGRAM:
        return "GL_PROGRAM";
    case GL_QUERY:
        return "GL_QUERY";
    case GL_PROGRAM_PIPELINE:
        return "GL_PROGRAM_PIPELINE";
    case GL_SAMPLER:
        return "GL_SAMPLER";
    case GL_DISPLAY_LIST:
        return "GL_DISPLAY_LIST";
    case GL_MAX_LABEL_LENGTH:
        return "GL_MAX_LABEL_LENGTH";
    case GL_NUM_SHADING_LANGUAGE_VERSIONS:
        return "GL_NUM_SHADING_LANGUAGE_VERSIONS";
    case GL_DEPTH_PASS_INSTRUMENT_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_SGIX";
    case GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_COUNTERS_SGIX";
    case GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX:
        return "GL_DEPTH_PASS_INSTRUMENT_MAX_SGIX";
    case GL_CONVOLUTION_HINT_SGIX:
        return "GL_CONVOLUTION_HINT_SGIX";
    case GL_YCRCB_SGIX:
        return "GL_YCRCB_SGIX";
    case GL_YCRCBA_SGIX:
        return "GL_YCRCBA_SGIX";
    case GL_ALPHA_MIN_SGIX:
        return "GL_ALPHA_MIN_SGIX";
    case GL_ALPHA_MAX_SGIX:
        return "GL_ALPHA_MAX_SGIX";
    case GL_SCALEBIAS_HINT_SGIX:
        return "GL_SCALEBIAS_HINT_SGIX";
    case GL_ASYNC_MARKER_SGIX:
        return "GL_ASYNC_MARKER_SGIX";
    case GL_PIXEL_TEX_GEN_MODE_SGIX:
        return "GL_PIXEL_TEX_GEN_MODE_SGIX";
    case GL_ASYNC_HISTOGRAM_SGIX:
        return "GL_ASYNC_HISTOGRAM_SGIX";
    case GL_MAX_ASYNC_HISTOGRAM_SGIX:
        return "GL_MAX_ASYNC_HISTOGRAM_SGIX";
    case GL_PIXEL_TRANSFORM_2D_EXT:
        return "GL_PIXEL_TRANSFORM_2D_EXT";
    case GL_PIXEL_MAG_FILTER_EXT:
        return "GL_PIXEL_MAG_FILTER_EXT";
    case GL_PIXEL_MIN_FILTER_EXT:
        return "GL_PIXEL_MIN_FILTER_EXT";
    case GL_PIXEL_CUBIC_WEIGHT_EXT:
        return "GL_PIXEL_CUBIC_WEIGHT_EXT";
    case GL_CUBIC_EXT:
        return "GL_CUBIC_EXT";
    case GL_AVERAGE_EXT:
        return "GL_AVERAGE_EXT";
    case GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT:
        return "GL_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT";
    case GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT:
        return "GL_MAX_PIXEL_TRANSFORM_2D_STACK_DEPTH_EXT";
    case GL_PIXEL_TRANSFORM_2D_MATRIX_EXT:
        return "GL_PIXEL_TRANSFORM_2D_MATRIX_EXT";
    case GL_FRAGMENT_MATERIAL_EXT:
        return "GL_FRAGMENT_MATERIAL_EXT";
    case GL_FRAGMENT_NORMAL_EXT:
        return "GL_FRAGMENT_NORMAL_EXT";
    case GL_FRAGMENT_COLOR_EXT:
        return "GL_FRAGMENT_COLOR_EXT";
    case GL_ATTENUATION_EXT:
        return "GL_ATTENUATION_EXT";
    case GL_SHADOW_ATTENUATION_EXT:
        return "GL_SHADOW_ATTENUATION_EXT";
    case GL_TEXTURE_APPLICATION_MODE_EXT:
        return "GL_TEXTURE_APPLICATION_MODE_EXT";
    case GL_TEXTURE_LIGHT_EXT:
        return "GL_TEXTURE_LIGHT_EXT";
    case GL_TEXTURE_MATERIAL_FACE_EXT:
        return "GL_TEXTURE_MATERIAL_FACE_EXT";
    case GL_TEXTURE_MATERIAL_PARAMETER_EXT:
        return "GL_TEXTURE_MATERIAL_PARAMETER_EXT";
    case GL_PIXEL_TEXTURE_SGIS:
        return "GL_PIXEL_TEXTURE_SGIS";
    case GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS:
        return "GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS";
    case GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS:
        return "GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS";
    case GL_PIXEL_GROUP_COLOR_SGIS:
        return "GL_PIXEL_GROUP_COLOR_SGIS";
    case GL_ASYNC_TEX_IMAGE_SGIX:
        return "GL_ASYNC_TEX_IMAGE_SGIX";
    case GL_ASYNC_DRAW_PIXELS_SGIX:
        return "GL_ASYNC_DRAW_PIXELS_SGIX";
    case GL_ASYNC_READ_PIXELS_SGIX:
        return "GL_ASYNC_READ_PIXELS_SGIX";
    case GL_MAX_ASYNC_TEX_IMAGE_SGIX:
        return "GL_MAX_ASYNC_TEX_IMAGE_SGIX";
    case GL_MAX_ASYNC_DRAW_PIXELS_SGIX:
        return "GL_MAX_ASYNC_DRAW_PIXELS_SGIX";
    case GL_MAX_ASYNC_READ_PIXELS_SGIX:
        return "GL_MAX_ASYNC_READ_PIXELS_SGIX";
    case GL_UNSIGNED_BYTE_2_3_3_REV:
        return "GL_UNSIGNED_BYTE_2_3_3_REV";
    case GL_UNSIGNED_SHORT_5_6_5:
        return "GL_UNSIGNED_SHORT_5_6_5";
    case GL_UNSIGNED_SHORT_5_6_5_REV:
        return "GL_UNSIGNED_SHORT_5_6_5_REV";
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        return "GL_UNSIGNED_SHORT_4_4_4_4_REV";
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
        return "GL_UNSIGNED_SHORT_1_5_5_5_REV";
    case GL_UNSIGNED_INT_8_8_8_8_REV:
        return "GL_UNSIGNED_INT_8_8_8_8_REV";
    case GL_UNSIGNED_INT_2_10_10_10_REV:
        return "GL_UNSIGNED_INT_2_10_10_10_REV";
    case GL_TEXTURE_MAX_CLAMP_S_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_S_SGIX";
    case GL_TEXTURE_MAX_CLAMP_T_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_T_SGIX";
    case GL_TEXTURE_MAX_CLAMP_R_SGIX:
        return "GL_TEXTURE_MAX_CLAMP_R_SGIX";
    case GL_MIRRORED_REPEAT:
        return "GL_MIRRORED_REPEAT";
    case GL_RGB_S3TC:
        return "GL_RGB_S3TC";
    case GL_RGB4_S3TC:
        return "GL_RGB4_S3TC";
    case GL_RGBA_S3TC:
        return "GL_RGBA_S3TC";
    case GL_RGBA4_S3TC:
        return "GL_RGBA4_S3TC";
    case GL_VERTEX_PRECLIP_SGIX:
        return "GL_VERTEX_PRECLIP_SGIX";
    case GL_VERTEX_PRECLIP_HINT_SGIX:
        return "GL_VERTEX_PRECLIP_HINT_SGIX";
    case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_RGB_S3TC_DXT1_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT3_EXT";
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
        return "GL_COMPRESSED_RGBA_S3TC_DXT5_EXT";
    case GL_PARALLEL_ARRAYS_INTEL:
        return "GL_PARALLEL_ARRAYS_INTEL";
    case GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_VERTEX_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_NORMAL_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_COLOR_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL:
        return "GL_TEXTURE_COORD_ARRAY_PARALLEL_POINTERS_INTEL";
    case GL_FRAGMENT_LIGHTING_SGIX:
        return "GL_FRAGMENT_LIGHTING_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX";
    case GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX:
        return "GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX";
    case GL_MAX_FRAGMENT_LIGHTS_SGIX:
        return "GL_MAX_FRAGMENT_LIGHTS_SGIX";
    case GL_MAX_ACTIVE_LIGHTS_SGIX:
        return "GL_MAX_ACTIVE_LIGHTS_SGIX";
    case GL_CURRENT_RASTER_NORMAL_SGIX:
        return "GL_CURRENT_RASTER_NORMAL_SGIX";
    case GL_LIGHT_ENV_MODE_SGIX:
        return "GL_LIGHT_ENV_MODE_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX";
    case GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX:
        return "GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX";
    case GL_FRAGMENT_LIGHT0_SGIX:
        return "GL_FRAGMENT_LIGHT0_SGIX";
    case GL_FRAGMENT_LIGHT1_SGIX:
        return "GL_FRAGMENT_LIGHT1_SGIX";
    case GL_FRAGMENT_LIGHT2_SGIX:
        return "GL_FRAGMENT_LIGHT2_SGIX";
    case GL_FRAGMENT_LIGHT3_SGIX:
        return "GL_FRAGMENT_LIGHT3_SGIX";
    case GL_FRAGMENT_LIGHT4_SGIX:
        return "GL_FRAGMENT_LIGHT4_SGIX";
    case GL_FRAGMENT_LIGHT5_SGIX:
        return "GL_FRAGMENT_LIGHT5_SGIX";
    case GL_FRAGMENT_LIGHT6_SGIX:
        return "GL_FRAGMENT_LIGHT6_SGIX";
    case GL_FRAGMENT_LIGHT7_SGIX:
        return "GL_FRAGMENT_LIGHT7_SGIX";
    case GL_PACK_RESAMPLE_SGIX:
        return "GL_PACK_RESAMPLE_SGIX";
    case GL_UNPACK_RESAMPLE_SGIX:
        return "GL_UNPACK_RESAMPLE_SGIX";
    case GL_RESAMPLE_REPLICATE_SGIX:
        return "GL_RESAMPLE_REPLICATE_SGIX";
    case GL_RESAMPLE_ZERO_FILL_SGIX:
        return "GL_RESAMPLE_ZERO_FILL_SGIX";
    case GL_RESAMPLE_DECIMATE_SGIX:
        return "GL_RESAMPLE_DECIMATE_SGIX";
    case GL_TANGENT_ARRAY_EXT:
        return "GL_TANGENT_ARRAY_EXT";
    case GL_BINORMAL_ARRAY_EXT:
        return "GL_BINORMAL_ARRAY_EXT";
    case GL_CURRENT_TANGENT_EXT:
        return "GL_CURRENT_TANGENT_EXT";
    case GL_CURRENT_BINORMAL_EXT:
        return "GL_CURRENT_BINORMAL_EXT";
    case GL_TANGENT_ARRAY_TYPE_EXT:
        return "GL_TANGENT_ARRAY_TYPE_EXT";
    case GL_TANGENT_ARRAY_STRIDE_EXT:
        return "GL_TANGENT_ARRAY_STRIDE_EXT";
    case GL_BINORMAL_ARRAY_TYPE_EXT:
        return "GL_BINORMAL_ARRAY_TYPE_EXT";
    case GL_BINORMAL_ARRAY_STRIDE_EXT:
        return "GL_BINORMAL_ARRAY_STRIDE_EXT";
    case GL_TANGENT_ARRAY_POINTER_EXT:
        return "GL_TANGENT_ARRAY_POINTER_EXT";
    case GL_BINORMAL_ARRAY_POINTER_EXT:
        return "GL_BINORMAL_ARRAY_POINTER_EXT";
    case GL_MAP1_TANGENT_EXT:
        return "GL_MAP1_TANGENT_EXT";
    case GL_MAP2_TANGENT_EXT:
        return "GL_MAP2_TANGENT_EXT";
    case GL_MAP1_BINORMAL_EXT:
        return "GL_MAP1_BINORMAL_EXT";
    case GL_MAP2_BINORMAL_EXT:
        return "GL_MAP2_BINORMAL_EXT";
    case GL_NEAREST_CLIPMAP_NEAREST_SGIX:
        return "GL_NEAREST_CLIPMAP_NEAREST_SGIX";
    case GL_NEAREST_CLIPMAP_LINEAR_SGIX:
        return "GL_NEAREST_CLIPMAP_LINEAR_SGIX";
    case GL_LINEAR_CLIPMAP_NEAREST_SGIX:
        return "GL_LINEAR_CLIPMAP_NEAREST_SGIX";
    case GL_FOG_COORD_SRC:
        return "GL_FOG_COORD_SRC";
    case GL_FOG_COORD:
        return "GL_FOG_COORD";
    case GL_FRAGMENT_DEPTH:
        return "GL_FRAGMENT_DEPTH";
    case GL_CURRENT_FOG_COORD:
        return "GL_CURRENT_FOG_COORD";
    case GL_FOG_COORD_ARRAY_TYPE:
        return "GL_FOG_COORD_ARRAY_TYPE";
    case GL_FOG_COORD_ARRAY_STRIDE:
        return "GL_FOG_COORD_ARRAY_STRIDE";
    case GL_FOG_COORD_ARRAY_POINTER:
        return "GL_FOG_COORD_ARRAY_POINTER";
    case GL_FOG_COORD_ARRAY:
        return "GL_FOG_COORD_ARRAY";
    case GL_COLOR_SUM:
        return "GL_COLOR_SUM";
    case GL_CURRENT_SECONDARY_COLOR:
        return "GL_CURRENT_SECONDARY_COLOR";
    case GL_SECONDARY_COLOR_ARRAY_SIZE:
        return "GL_SECONDARY_COLOR_ARRAY_SIZE";
    case GL_SECONDARY_COLOR_ARRAY_TYPE:
        return "GL_SECONDARY_COLOR_ARRAY_TYPE";
    case GL_SECONDARY_COLOR_ARRAY_STRIDE:
        return "GL_SECONDARY_COLOR_ARRAY_STRIDE";
    case GL_SECONDARY_COLOR_ARRAY_POINTER:
        return "GL_SECONDARY_COLOR_ARRAY_POINTER";
    case GL_SECONDARY_COLOR_ARRAY:
        return "GL_SECONDARY_COLOR_ARRAY";
    case GL_CURRENT_RASTER_SECONDARY_COLOR:
        return "GL_CURRENT_RASTER_SECONDARY_COLOR";
    case GL_ALIASED_POINT_SIZE_RANGE:
        return "GL_ALIASED_POINT_SIZE_RANGE";
    case GL_ALIASED_LINE_WIDTH_RANGE:
        return "GL_ALIASED_LINE_WIDTH_RANGE";
    case GL_SCREEN_COORDINATES_REND:
        return "GL_SCREEN_COORDINATES_REND";
    case GL_INVERTED_SCREEN_W_REND:
        return "GL_INVERTED_SCREEN_W_REND";
    case GL_TEXTURE0:
        return "GL_TEXTURE0";
    case GL_TEXTURE1:
        return "GL_TEXTURE1";
    case GL_TEXTURE2:
        return "GL_TEXTURE2";
    case GL_TEXTURE3:
        return "GL_TEXTURE3";
    case GL_TEXTURE4:
        return "GL_TEXTURE4";
    case GL_TEXTURE5:
        return "GL_TEXTURE5";
    case GL_TEXTURE6:
        return "GL_TEXTURE6";
    case GL_TEXTURE7:
        return "GL_TEXTURE7";
    case GL_TEXTURE8:
        return "GL_TEXTURE8";
    case GL_TEXTURE9:
        return "GL_TEXTURE9";
    case GL_TEXTURE10:
        return "GL_TEXTURE10";
    case GL_TEXTURE11:
        return "GL_TEXTURE11";
    case GL_TEXTURE12:
        return "GL_TEXTURE12";
    case GL_TEXTURE13:
        return "GL_TEXTURE13";
    case GL_TEXTURE14:
        return "GL_TEXTURE14";
    case GL_TEXTURE15:
        return "GL_TEXTURE15";
    case GL_TEXTURE16:
        return "GL_TEXTURE16";
    case GL_TEXTURE17:
        return "GL_TEXTURE17";
    case GL_TEXTURE18:
        return "GL_TEXTURE18";
    case GL_TEXTURE19:
        return "GL_TEXTURE19";
    case GL_TEXTURE20:
        return "GL_TEXTURE20";
    case GL_TEXTURE21:
        return "GL_TEXTURE21";
    case GL_TEXTURE22:
        return "GL_TEXTURE22";
    case GL_TEXTURE23:
        return "GL_TEXTURE23";
    case GL_TEXTURE24:
        return "GL_TEXTURE24";
    case GL_TEXTURE25:
        return "GL_TEXTURE25";
    case GL_TEXTURE26:
        return "GL_TEXTURE26";
    case GL_TEXTURE27:
        return "GL_TEXTURE27";
    case GL_TEXTURE28:
        return "GL_TEXTURE28";
    case GL_TEXTURE29:
        return "GL_TEXTURE29";
    case GL_TEXTURE30:
        return "GL_TEXTURE30";
    case GL_TEXTURE31:
        return "GL_TEXTURE31";
    case GL_ACTIVE_TEXTURE:
        return "GL_ACTIVE_TEXTURE";
    case GL_CLIENT_ACTIVE_TEXTURE:
        return "GL_CLIENT_ACTIVE_TEXTURE";
    case GL_MAX_TEXTURE_UNITS:
        return "GL_MAX_TEXTURE_UNITS";
    case GL_TRANSPOSE_MODELVIEW_MATRIX:
        return "GL_TRANSPOSE_MODELVIEW_MATRIX";
    case GL_TRANSPOSE_PROJECTION_MATRIX:
        return "GL_TRANSPOSE_PROJECTION_MATRIX";
    case GL_TRANSPOSE_TEXTURE_MATRIX:
        return "GL_TRANSPOSE_TEXTURE_MATRIX";
    case GL_TRANSPOSE_COLOR_MATRIX:
        return "GL_TRANSPOSE_COLOR_MATRIX";
    case GL_SUBTRACT:
        return "GL_SUBTRACT";
    case GL_MAX_RENDERBUFFER_SIZE:
        return "GL_MAX_RENDERBUFFER_SIZE";
    case GL_COMPRESSED_ALPHA:
        return "GL_COMPRESSED_ALPHA";
    case GL_COMPRESSED_LUMINANCE:
        return "GL_COMPRESSED_LUMINANCE";
    case GL_COMPRESSED_LUMINANCE_ALPHA:
        return "GL_COMPRESSED_LUMINANCE_ALPHA";
    case GL_COMPRESSED_INTENSITY:
        return "GL_COMPRESSED_INTENSITY";
    case GL_COMPRESSED_RGB:
        return "GL_COMPRESSED_RGB";
    case GL_COMPRESSED_RGBA:
        return "GL_COMPRESSED_RGBA";
    case GL_TEXTURE_COMPRESSION_HINT:
        return "GL_TEXTURE_COMPRESSION_HINT";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER";
    case GL_ALL_COMPLETED_NV:
        return "GL_ALL_COMPLETED_NV";
    case GL_FENCE_STATUS_NV:
        return "GL_FENCE_STATUS_NV";
    case GL_FENCE_CONDITION_NV:
        return "GL_FENCE_CONDITION_NV";
    case GL_TEXTURE_RECTANGLE:
        return "GL_TEXTURE_RECTANGLE";
    case GL_TEXTURE_BINDING_RECTANGLE:
        return "GL_TEXTURE_BINDING_RECTANGLE";
    case GL_PROXY_TEXTURE_RECTANGLE:
        return "GL_PROXY_TEXTURE_RECTANGLE";
    case GL_MAX_RECTANGLE_TEXTURE_SIZE:
        return "GL_MAX_RECTANGLE_TEXTURE_SIZE";
    case GL_DEPTH_STENCIL:
        return "GL_DEPTH_STENCIL";
    case GL_UNSIGNED_INT_24_8:
        return "GL_UNSIGNED_INT_24_8";
    case GL_MAX_TEXTURE_LOD_BIAS:
        return "GL_MAX_TEXTURE_LOD_BIAS";
    case GL_TEXTURE_MAX_ANISOTROPY_EXT:
        return "GL_TEXTURE_MAX_ANISOTROPY_EXT";
    case GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT:
        return "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT";
    case GL_TEXTURE_FILTER_CONTROL:
        return "GL_TEXTURE_FILTER_CONTROL";
    case GL_TEXTURE_LOD_BIAS:
        return "GL_TEXTURE_LOD_BIAS";
    case GL_MODELVIEW1_STACK_DEPTH_EXT:
        return "GL_MODELVIEW1_STACK_DEPTH_EXT";
    case GL_COMBINE4_NV:
        return "GL_COMBINE4_NV";
    case GL_MAX_SHININESS_NV:
        return "GL_MAX_SHININESS_NV";
    case GL_MAX_SPOT_EXPONENT_NV:
        return "GL_MAX_SPOT_EXPONENT_NV";
    case GL_MODELVIEW1_MATRIX_EXT:
        return "GL_MODELVIEW1_MATRIX_EXT";
    case GL_INCR_WRAP:
        return "GL_INCR_WRAP";
    case GL_DECR_WRAP:
        return "GL_DECR_WRAP";
    case GL_VERTEX_WEIGHTING_EXT:
        return "GL_VERTEX_WEIGHTING_EXT";
    case GL_MODELVIEW1_ARB:
        return "GL_MODELVIEW1_ARB";
    case GL_CURRENT_VERTEX_WEIGHT_EXT:
        return "GL_CURRENT_VERTEX_WEIGHT_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_SIZE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT";
    case GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT:
        return "GL_VERTEX_WEIGHT_ARRAY_POINTER_EXT";
    case GL_NORMAL_MAP:
        return "GL_NORMAL_MAP";
    case GL_REFLECTION_MAP:
        return "GL_REFLECTION_MAP";
    case GL_TEXTURE_CUBE_MAP:
        return "GL_TEXTURE_CUBE_MAP";
    case GL_TEXTURE_BINDING_CUBE_MAP:
        return "GL_TEXTURE_BINDING_CUBE_MAP";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_X";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_X";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_Y";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y";
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
        return "GL_TEXTURE_CUBE_MAP_POSITIVE_Z";
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        return "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z";
    case GL_PROXY_TEXTURE_CUBE_MAP:
        return "GL_PROXY_TEXTURE_CUBE_MAP";
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
        return "GL_MAX_CUBE_MAP_TEXTURE_SIZE";
    case GL_VERTEX_ARRAY_RANGE_NV:
        return "GL_VERTEX_ARRAY_RANGE_NV";
    case GL_VERTEX_ARRAY_RANGE_LENGTH_NV:
        return "GL_VERTEX_ARRAY_RANGE_LENGTH_NV";
    case GL_VERTEX_ARRAY_RANGE_VALID_NV:
        return "GL_VERTEX_ARRAY_RANGE_VALID_NV";
    case GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV:
        return "GL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV";
    case GL_VERTEX_ARRAY_RANGE_POINTER_NV:
        return "GL_VERTEX_ARRAY_RANGE_POINTER_NV";
    case GL_REGISTER_COMBINERS_NV:
        return "GL_REGISTER_COMBINERS_NV";
    case GL_VARIABLE_A_NV:
        return "GL_VARIABLE_A_NV";
    case GL_VARIABLE_B_NV:
        return "GL_VARIABLE_B_NV";
    case GL_VARIABLE_C_NV:
        return "GL_VARIABLE_C_NV";
    case GL_VARIABLE_D_NV:
        return "GL_VARIABLE_D_NV";
    case GL_VARIABLE_E_NV:
        return "GL_VARIABLE_E_NV";
    case GL_VARIABLE_F_NV:
        return "GL_VARIABLE_F_NV";
    case GL_VARIABLE_G_NV:
        return "GL_VARIABLE_G_NV";
    case GL_CONSTANT_COLOR0_NV:
        return "GL_CONSTANT_COLOR0_NV";
    case GL_CONSTANT_COLOR1_NV:
        return "GL_CONSTANT_COLOR1_NV";
    case GL_PRIMARY_COLOR_NV:
        return "GL_PRIMARY_COLOR_NV";
    case GL_SECONDARY_COLOR_NV:
        return "GL_SECONDARY_COLOR_NV";
    case GL_SPARE0_NV:
        return "GL_SPARE0_NV";
    case GL_SPARE1_NV:
        return "GL_SPARE1_NV";
    case GL_DISCARD_NV:
        return "GL_DISCARD_NV";
    case GL_E_TIMES_F_NV:
        return "GL_E_TIMES_F_NV";
    case GL_SPARE0_PLUS_SECONDARY_COLOR_NV:
        return "GL_SPARE0_PLUS_SECONDARY_COLOR_NV";
    case GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV:
        return "GL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV";
    case GL_MULTISAMPLE_FILTER_HINT_NV:
        return "GL_MULTISAMPLE_FILTER_HINT_NV";
    case GL_PER_STAGE_CONSTANTS_NV:
        return "GL_PER_STAGE_CONSTANTS_NV";
    case GL_UNSIGNED_IDENTITY_NV:
        return "GL_UNSIGNED_IDENTITY_NV";
    case GL_UNSIGNED_INVERT_NV:
        return "GL_UNSIGNED_INVERT_NV";
    case GL_EXPAND_NORMAL_NV:
        return "GL_EXPAND_NORMAL_NV";
    case GL_EXPAND_NEGATE_NV:
        return "GL_EXPAND_NEGATE_NV";
    case GL_HALF_BIAS_NORMAL_NV:
        return "GL_HALF_BIAS_NORMAL_NV";
    case GL_HALF_BIAS_NEGATE_NV:
        return "GL_HALF_BIAS_NEGATE_NV";
    case GL_SIGNED_IDENTITY_NV:
        return "GL_SIGNED_IDENTITY_NV";
    case GL_SIGNED_NEGATE_NV:
        return "GL_SIGNED_NEGATE_NV";
    case GL_SCALE_BY_TWO_NV:
        return "GL_SCALE_BY_TWO_NV";
    case GL_SCALE_BY_FOUR_NV:
        return "GL_SCALE_BY_FOUR_NV";
    case GL_SCALE_BY_ONE_HALF_NV:
        return "GL_SCALE_BY_ONE_HALF_NV";
    case GL_BIAS_BY_NEGATIVE_ONE_HALF_NV:
        return "GL_BIAS_BY_NEGATIVE_ONE_HALF_NV";
    case GL_COMBINER_INPUT_NV:
        return "GL_COMBINER_INPUT_NV";
    case GL_COMBINER_MAPPING_NV:
        return "GL_COMBINER_MAPPING_NV";
    case GL_COMBINER_COMPONENT_USAGE_NV:
        return "GL_COMBINER_COMPONENT_USAGE_NV";
    case GL_COMBINER_AB_DOT_PRODUCT_NV:
        return "GL_COMBINER_AB_DOT_PRODUCT_NV";
    case GL_COMBINER_CD_DOT_PRODUCT_NV:
        return "GL_COMBINER_CD_DOT_PRODUCT_NV";
    case GL_COMBINER_MUX_SUM_NV:
        return "GL_COMBINER_MUX_SUM_NV";
    case GL_COMBINER_SCALE_NV:
        return "GL_COMBINER_SCALE_NV";
    case GL_COMBINER_BIAS_NV:
        return "GL_COMBINER_BIAS_NV";
    case GL_COMBINER_AB_OUTPUT_NV:
        return "GL_COMBINER_AB_OUTPUT_NV";
    case GL_COMBINER_CD_OUTPUT_NV:
        return "GL_COMBINER_CD_OUTPUT_NV";
    case GL_COMBINER_SUM_OUTPUT_NV:
        return "GL_COMBINER_SUM_OUTPUT_NV";
    case GL_MAX_GENERAL_COMBINERS_NV:
        return "GL_MAX_GENERAL_COMBINERS_NV";
    case GL_NUM_GENERAL_COMBINERS_NV:
        return "GL_NUM_GENERAL_COMBINERS_NV";
    case GL_COLOR_SUM_CLAMP_NV:
        return "GL_COLOR_SUM_CLAMP_NV";
    case GL_COMBINER0_NV:
        return "GL_COMBINER0_NV";
    case GL_COMBINER1_NV:
        return "GL_COMBINER1_NV";
    case GL_COMBINER2_NV:
        return "GL_COMBINER2_NV";
    case GL_COMBINER3_NV:
        return "GL_COMBINER3_NV";
    case GL_COMBINER4_NV:
        return "GL_COMBINER4_NV";
    case GL_COMBINER5_NV:
        return "GL_COMBINER5_NV";
    case GL_COMBINER6_NV:
        return "GL_COMBINER6_NV";
    case GL_COMBINER7_NV:
        return "GL_COMBINER7_NV";
    case GL_PRIMITIVE_RESTART_NV:
        return "GL_PRIMITIVE_RESTART_NV";
    case GL_PRIMITIVE_RESTART_INDEX_NV:
        return "GL_PRIMITIVE_RESTART_INDEX_NV";
    case GL_FOG_DISTANCE_MODE_NV:
        return "GL_FOG_DISTANCE_MODE_NV";
    case GL_EYE_RADIAL_NV:
        return "GL_EYE_RADIAL_NV";
    case GL_EYE_PLANE_ABSOLUTE_NV:
        return "GL_EYE_PLANE_ABSOLUTE_NV";
    case GL_EMBOSS_LIGHT_NV:
        return "GL_EMBOSS_LIGHT_NV";
    case GL_EMBOSS_CONSTANT_NV:
        return "GL_EMBOSS_CONSTANT_NV";
    case GL_EMBOSS_MAP_NV:
        return "GL_EMBOSS_MAP_NV";
    case GL_RED_MIN_CLAMP_INGR:
        return "GL_RED_MIN_CLAMP_INGR";
    case GL_GREEN_MIN_CLAMP_INGR:
        return "GL_GREEN_MIN_CLAMP_INGR";
    case GL_BLUE_MIN_CLAMP_INGR:
        return "GL_BLUE_MIN_CLAMP_INGR";
    case GL_ALPHA_MIN_CLAMP_INGR:
        return "GL_ALPHA_MIN_CLAMP_INGR";
    case GL_RED_MAX_CLAMP_INGR:
        return "GL_RED_MAX_CLAMP_INGR";
    case GL_GREEN_MAX_CLAMP_INGR:
        return "GL_GREEN_MAX_CLAMP_INGR";
    case GL_BLUE_MAX_CLAMP_INGR:
        return "GL_BLUE_MAX_CLAMP_INGR";
    case GL_ALPHA_MAX_CLAMP_INGR:
        return "GL_ALPHA_MAX_CLAMP_INGR";
    case GL_INTERLACE_READ_INGR:
        return "GL_INTERLACE_READ_INGR";
    case GL_COMBINE:
        return "GL_COMBINE";
    case GL_COMBINE_RGB:
        return "GL_COMBINE_RGB";
    case GL_COMBINE_ALPHA:
        return "GL_COMBINE_ALPHA";
    case GL_RGB_SCALE:
        return "GL_RGB_SCALE";
    case GL_ADD_SIGNED:
        return "GL_ADD_SIGNED";
    case GL_INTERPOLATE:
        return "GL_INTERPOLATE";
    case GL_CONSTANT:
        return "GL_CONSTANT";
    case GL_PRIMARY_COLOR:
        return "GL_PRIMARY_COLOR";
    case GL_PREVIOUS:
        return "GL_PREVIOUS";
    case GL_SRC0_RGB:
        return "GL_SRC0_RGB";
    case GL_SRC1_RGB:
        return "GL_SRC1_RGB";
    case GL_SRC2_RGB:
        return "GL_SRC2_RGB";
    case GL_SOURCE3_RGB_NV:
        return "GL_SOURCE3_RGB_NV";
    case GL_SRC0_ALPHA:
        return "GL_SRC0_ALPHA";
    case GL_SRC1_ALPHA:
        return "GL_SRC1_ALPHA";
    case GL_SRC2_ALPHA:
        return "GL_SRC2_ALPHA";
    case GL_SOURCE3_ALPHA_NV:
        return "GL_SOURCE3_ALPHA_NV";
    case GL_OPERAND0_RGB:
        return "GL_OPERAND0_RGB";
    case GL_OPERAND1_RGB:
        return "GL_OPERAND1_RGB";
    case GL_OPERAND2_RGB:
        return "GL_OPERAND2_RGB";
    case GL_OPERAND3_RGB_NV:
        return "GL_OPERAND3_RGB_NV";
    case GL_OPERAND0_ALPHA:
        return "GL_OPERAND0_ALPHA";
    case GL_OPERAND1_ALPHA:
        return "GL_OPERAND1_ALPHA";
    case GL_OPERAND2_ALPHA:
        return "GL_OPERAND2_ALPHA";
    case GL_OPERAND3_ALPHA_NV:
        return "GL_OPERAND3_ALPHA_NV";
    case GL_PACK_SUBSAMPLE_RATE_SGIX:
        return "GL_PACK_SUBSAMPLE_RATE_SGIX";
    case GL_UNPACK_SUBSAMPLE_RATE_SGIX:
        return "GL_UNPACK_SUBSAMPLE_RATE_SGIX";
    case GL_PIXEL_SUBSAMPLE_4444_SGIX:
        return "GL_PIXEL_SUBSAMPLE_4444_SGIX";
    case GL_PIXEL_SUBSAMPLE_2424_SGIX:
        return "GL_PIXEL_SUBSAMPLE_2424_SGIX";
    case GL_PIXEL_SUBSAMPLE_4242_SGIX:
        return "GL_PIXEL_SUBSAMPLE_4242_SGIX";
    case GL_PERTURB_EXT:
        return "GL_PERTURB_EXT";
    case GL_TEXTURE_NORMAL_EXT:
        return "GL_TEXTURE_NORMAL_EXT";
    case GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE:
        return "GL_LIGHT_MODEL_SPECULAR_VECTOR_APPLE";
    case GL_TRANSFORM_HINT_APPLE:
        return "GL_TRANSFORM_HINT_APPLE";
    case GL_UNPACK_CLIENT_STORAGE_APPLE:
        return "GL_UNPACK_CLIENT_STORAGE_APPLE";
    case GL_BUFFER_OBJECT_APPLE:
        return "GL_BUFFER_OBJECT_APPLE";
    case GL_STORAGE_CLIENT_APPLE:
        return "GL_STORAGE_CLIENT_APPLE";
    case GL_VERTEX_ARRAY_BINDING:
        return "GL_VERTEX_ARRAY_BINDING";
    case GL_TEXTURE_RANGE_LENGTH_APPLE:
        return "GL_TEXTURE_RANGE_LENGTH_APPLE";
    case GL_TEXTURE_RANGE_POINTER_APPLE:
        return "GL_TEXTURE_RANGE_POINTER_APPLE";
    case GL_YCBCR_422_APPLE:
        return "GL_YCBCR_422_APPLE";
    case GL_UNSIGNED_SHORT_8_8_MESA:
        return "GL_UNSIGNED_SHORT_8_8_MESA";
    case GL_UNSIGNED_SHORT_8_8_REV_MESA:
        return "GL_UNSIGNED_SHORT_8_8_REV_MESA";
    case GL_TEXTURE_STORAGE_HINT_APPLE:
        return "GL_TEXTURE_STORAGE_HINT_APPLE";
    case GL_STORAGE_PRIVATE_APPLE:
        return "GL_STORAGE_PRIVATE_APPLE";
    case GL_STORAGE_CACHED_APPLE:
        return "GL_STORAGE_CACHED_APPLE";
    case GL_STORAGE_SHARED_APPLE:
        return "GL_STORAGE_SHARED_APPLE";
    case GL_REPLACEMENT_CODE_ARRAY_SUN:
        return "GL_REPLACEMENT_CODE_ARRAY_SUN";
    case GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN:
        return "GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN";
    case GL_REPLACEMENT_CODE_ARRAY_STRIDE_SUN:
        return "GL_REPLACEMENT_CODE_ARRAY_STRIDE_SUN";
    case GL_REPLACEMENT_CODE_ARRAY_POINTER_SUN:
        return "GL_REPLACEMENT_CODE_ARRAY_POINTER_SUN";
    case GL_R1UI_V3F_SUN:
        return "GL_R1UI_V3F_SUN";
    case GL_R1UI_C4UB_V3F_SUN:
        return "GL_R1UI_C4UB_V3F_SUN";
    case GL_R1UI_C3F_V3F_SUN:
        return "GL_R1UI_C3F_V3F_SUN";
    case GL_R1UI_N3F_V3F_SUN:
        return "GL_R1UI_N3F_V3F_SUN";
    case GL_R1UI_C4F_N3F_V3F_SUN:
        return "GL_R1UI_C4F_N3F_V3F_SUN";
    case GL_R1UI_T2F_V3F_SUN:
        return "GL_R1UI_T2F_V3F_SUN";
    case GL_R1UI_T2F_N3F_V3F_SUN:
        return "GL_R1UI_T2F_N3F_V3F_SUN";
    case GL_R1UI_T2F_C4F_N3F_V3F_SUN:
        return "GL_R1UI_T2F_C4F_N3F_V3F_SUN";
    case GL_SLICE_ACCUM_SUN:
        return "GL_SLICE_ACCUM_SUN";
    case GL_QUAD_MESH_SUN:
        return "GL_QUAD_MESH_SUN";
    case GL_TRIANGLE_MESH_SUN:
        return "GL_TRIANGLE_MESH_SUN";
    case GL_VERTEX_PROGRAM_ARB:
        return "GL_VERTEX_PROGRAM_ARB";
    case GL_VERTEX_STATE_PROGRAM_NV:
        return "GL_VERTEX_STATE_PROGRAM_NV";
    case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
        return "GL_VERTEX_ATTRIB_ARRAY_ENABLED";
    case GL_VERTEX_ATTRIB_ARRAY_SIZE:
        return "GL_VERTEX_ATTRIB_ARRAY_SIZE";
    case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
        return "GL_VERTEX_ATTRIB_ARRAY_STRIDE";
    case GL_VERTEX_ATTRIB_ARRAY_TYPE:
        return "GL_VERTEX_ATTRIB_ARRAY_TYPE";
    case GL_CURRENT_VERTEX_ATTRIB:
        return "GL_CURRENT_VERTEX_ATTRIB";
    case GL_PROGRAM_LENGTH_ARB:
        return "GL_PROGRAM_LENGTH_ARB";
    case GL_PROGRAM_STRING_ARB:
        return "GL_PROGRAM_STRING_ARB";
    case GL_MODELVIEW_PROJECTION_NV:
        return "GL_MODELVIEW_PROJECTION_NV";
    case GL_IDENTITY_NV:
        return "GL_IDENTITY_NV";
    case GL_INVERSE_NV:
        return "GL_INVERSE_NV";
    case GL_TRANSPOSE_NV:
        return "GL_TRANSPOSE_NV";
    case GL_INVERSE_TRANSPOSE_NV:
        return "GL_INVERSE_TRANSPOSE_NV";
    case GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB:
        return "GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB";
    case GL_MAX_PROGRAM_MATRICES_ARB:
        return "GL_MAX_PROGRAM_MATRICES_ARB";
    case GL_MATRIX0_NV:
        return "GL_MATRIX0_NV";
    case GL_MATRIX1_NV:
        return "GL_MATRIX1_NV";
    case GL_MATRIX2_NV:
        return "GL_MATRIX2_NV";
    case GL_MATRIX3_NV:
        return "GL_MATRIX3_NV";
    case GL_MATRIX4_NV:
        return "GL_MATRIX4_NV";
    case GL_MATRIX5_NV:
        return "GL_MATRIX5_NV";
    case GL_MATRIX6_NV:
        return "GL_MATRIX6_NV";
    case GL_MATRIX7_NV:
        return "GL_MATRIX7_NV";
    case GL_CURRENT_MATRIX_STACK_DEPTH_ARB:
        return "GL_CURRENT_MATRIX_STACK_DEPTH_ARB";
    case GL_CURRENT_MATRIX_ARB:
        return "GL_CURRENT_MATRIX_ARB";
    case GL_PROGRAM_POINT_SIZE:
        return "GL_PROGRAM_POINT_SIZE";
    case GL_VERTEX_PROGRAM_TWO_SIDE:
        return "GL_VERTEX_PROGRAM_TWO_SIDE";
    case GL_PROGRAM_PARAMETER_NV:
        return "GL_PROGRAM_PARAMETER_NV";
    case GL_VERTEX_ATTRIB_ARRAY_POINTER:
        return "GL_VERTEX_ATTRIB_ARRAY_POINTER";
    case GL_PROGRAM_TARGET_NV:
        return "GL_PROGRAM_TARGET_NV";
    case GL_PROGRAM_RESIDENT_NV:
        return "GL_PROGRAM_RESIDENT_NV";
    case GL_TRACK_MATRIX_NV:
        return "GL_TRACK_MATRIX_NV";
    case GL_TRACK_MATRIX_TRANSFORM_NV:
        return "GL_TRACK_MATRIX_TRANSFORM_NV";
    case GL_VERTEX_PROGRAM_BINDING_NV:
        return "GL_VERTEX_PROGRAM_BINDING_NV";
    case GL_PROGRAM_ERROR_POSITION_ARB:
        return "GL_PROGRAM_ERROR_POSITION_ARB";
    case GL_OFFSET_TEXTURE_RECTANGLE_NV:
        return "GL_OFFSET_TEXTURE_RECTANGLE_NV";
    case GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV:
        return "GL_OFFSET_TEXTURE_RECTANGLE_SCALE_NV";
    case GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV:
        return "GL_DOT_PRODUCT_TEXTURE_RECTANGLE_NV";
    case GL_DEPTH_CLAMP:
        return "GL_DEPTH_CLAMP";
    case GL_VERTEX_ATTRIB_ARRAY0_NV:
        return "GL_VERTEX_ATTRIB_ARRAY0_NV";
    case GL_VERTEX_ATTRIB_ARRAY1_NV:
        return "GL_VERTEX_ATTRIB_ARRAY1_NV";
    case GL_VERTEX_ATTRIB_ARRAY2_NV:
        return "GL_VERTEX_ATTRIB_ARRAY2_NV";
    case GL_VERTEX_ATTRIB_ARRAY3_NV:
        return "GL_VERTEX_ATTRIB_ARRAY3_NV";
    case GL_VERTEX_ATTRIB_ARRAY4_NV:
        return "GL_VERTEX_ATTRIB_ARRAY4_NV";
    case GL_VERTEX_ATTRIB_ARRAY5_NV:
        return "GL_VERTEX_ATTRIB_ARRAY5_NV";
    case GL_VERTEX_ATTRIB_ARRAY6_NV:
        return "GL_VERTEX_ATTRIB_ARRAY6_NV";
    case GL_VERTEX_ATTRIB_ARRAY7_NV:
        return "GL_VERTEX_ATTRIB_ARRAY7_NV";
    case GL_VERTEX_ATTRIB_ARRAY8_NV:
        return "GL_VERTEX_ATTRIB_ARRAY8_NV";
    case GL_VERTEX_ATTRIB_ARRAY9_NV:
        return "GL_VERTEX_ATTRIB_ARRAY9_NV";
    case GL_VERTEX_ATTRIB_ARRAY10_NV:
        return "GL_VERTEX_ATTRIB_ARRAY10_NV";
    case GL_VERTEX_ATTRIB_ARRAY11_NV:
        return "GL_VERTEX_ATTRIB_ARRAY11_NV";
    case GL_VERTEX_ATTRIB_ARRAY12_NV:
        return "GL_VERTEX_ATTRIB_ARRAY12_NV";
    case GL_VERTEX_ATTRIB_ARRAY13_NV:
        return "GL_VERTEX_ATTRIB_ARRAY13_NV";
    case GL_VERTEX_ATTRIB_ARRAY14_NV:
        return "GL_VERTEX_ATTRIB_ARRAY14_NV";
    case GL_VERTEX_ATTRIB_ARRAY15_NV:
        return "GL_VERTEX_ATTRIB_ARRAY15_NV";
    case GL_MAP1_VERTEX_ATTRIB0_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB0_4_NV";
    case GL_MAP1_VERTEX_ATTRIB1_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB1_4_NV";
    case GL_MAP1_VERTEX_ATTRIB2_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB2_4_NV";
    case GL_MAP1_VERTEX_ATTRIB3_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB3_4_NV";
    case GL_MAP1_VERTEX_ATTRIB4_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB4_4_NV";
    case GL_MAP1_VERTEX_ATTRIB5_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB5_4_NV";
    case GL_MAP1_VERTEX_ATTRIB6_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB6_4_NV";
    case GL_MAP1_VERTEX_ATTRIB7_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB7_4_NV";
    case GL_MAP1_VERTEX_ATTRIB8_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB8_4_NV";
    case GL_MAP1_VERTEX_ATTRIB9_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB9_4_NV";
    case GL_MAP1_VERTEX_ATTRIB10_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB10_4_NV";
    case GL_MAP1_VERTEX_ATTRIB11_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB11_4_NV";
    case GL_MAP1_VERTEX_ATTRIB12_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB12_4_NV";
    case GL_MAP1_VERTEX_ATTRIB13_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB13_4_NV";
    case GL_MAP1_VERTEX_ATTRIB14_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB14_4_NV";
    case GL_MAP1_VERTEX_ATTRIB15_4_NV:
        return "GL_MAP1_VERTEX_ATTRIB15_4_NV";
    case GL_MAP2_VERTEX_ATTRIB0_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB0_4_NV";
    case GL_MAP2_VERTEX_ATTRIB1_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB1_4_NV";
    case GL_MAP2_VERTEX_ATTRIB2_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB2_4_NV";
    case GL_MAP2_VERTEX_ATTRIB3_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB3_4_NV";
    case GL_MAP2_VERTEX_ATTRIB4_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB4_4_NV";
    case GL_MAP2_VERTEX_ATTRIB5_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB5_4_NV";
    case GL_MAP2_VERTEX_ATTRIB6_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB6_4_NV";
    case GL_PROGRAM_BINDING_ARB:
        return "GL_PROGRAM_BINDING_ARB";
    case GL_MAP2_VERTEX_ATTRIB8_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB8_4_NV";
    case GL_MAP2_VERTEX_ATTRIB9_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB9_4_NV";
    case GL_MAP2_VERTEX_ATTRIB10_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB10_4_NV";
    case GL_MAP2_VERTEX_ATTRIB11_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB11_4_NV";
    case GL_MAP2_VERTEX_ATTRIB12_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB12_4_NV";
    case GL_MAP2_VERTEX_ATTRIB13_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB13_4_NV";
    case GL_MAP2_VERTEX_ATTRIB14_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB14_4_NV";
    case GL_MAP2_VERTEX_ATTRIB15_4_NV:
        return "GL_MAP2_VERTEX_ATTRIB15_4_NV";
    case GL_TEXTURE_COMPRESSED_IMAGE_SIZE:
        return "GL_TEXTURE_COMPRESSED_IMAGE_SIZE";
    case GL_TEXTURE_COMPRESSED:
        return "GL_TEXTURE_COMPRESSED";
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
        return "GL_NUM_COMPRESSED_TEXTURE_FORMATS";
    case GL_COMPRESSED_TEXTURE_FORMATS:
        return "GL_COMPRESSED_TEXTURE_FORMATS";
    case GL_MAX_VERTEX_UNITS_ARB:
        return "GL_MAX_VERTEX_UNITS_ARB";
    case GL_ACTIVE_VERTEX_UNITS_ARB:
        return "GL_ACTIVE_VERTEX_UNITS_ARB";
    case GL_WEIGHT_SUM_UNITY_ARB:
        return "GL_WEIGHT_SUM_UNITY_ARB";
    case GL_VERTEX_BLEND_ARB:
        return "GL_VERTEX_BLEND_ARB";
    case GL_CURRENT_WEIGHT_ARB:
        return "GL_CURRENT_WEIGHT_ARB";
    case GL_WEIGHT_ARRAY_TYPE_ARB:
        return "GL_WEIGHT_ARRAY_TYPE_ARB";
    case GL_WEIGHT_ARRAY_STRIDE_ARB:
        return "GL_WEIGHT_ARRAY_STRIDE_ARB";
    case GL_WEIGHT_ARRAY_SIZE_ARB:
        return "GL_WEIGHT_ARRAY_SIZE_ARB";
    case GL_WEIGHT_ARRAY_POINTER_ARB:
        return "GL_WEIGHT_ARRAY_POINTER_ARB";
    case GL_WEIGHT_ARRAY_ARB:
        return "GL_WEIGHT_ARRAY_ARB";
    case GL_DOT3_RGB:
        return "GL_DOT3_RGB";
    case GL_DOT3_RGBA:
        return "GL_DOT3_RGBA";
    case GL_COMPRESSED_RGB_FXT1_3DFX:
        return "GL_COMPRESSED_RGB_FXT1_3DFX";
    case GL_COMPRESSED_RGBA_FXT1_3DFX:
        return "GL_COMPRESSED_RGBA_FXT1_3DFX";
    case GL_MULTISAMPLE_3DFX:
        return "GL_MULTISAMPLE_3DFX";
    case GL_SAMPLE_BUFFERS_3DFX:
        return "GL_SAMPLE_BUFFERS_3DFX";
    case GL_SAMPLES_3DFX:
        return "GL_SAMPLES_3DFX";
    case GL_EVAL_2D_NV:
        return "GL_EVAL_2D_NV";
    case GL_EVAL_TRIANGULAR_2D_NV:
        return "GL_EVAL_TRIANGULAR_2D_NV";
    case GL_MAP_TESSELLATION_NV:
        return "GL_MAP_TESSELLATION_NV";
    case GL_MAP_ATTRIB_U_ORDER_NV:
        return "GL_MAP_ATTRIB_U_ORDER_NV";
    case GL_MAP_ATTRIB_V_ORDER_NV:
        return "GL_MAP_ATTRIB_V_ORDER_NV";
    case GL_EVAL_FRACTIONAL_TESSELLATION_NV:
        return "GL_EVAL_FRACTIONAL_TESSELLATION_NV";
    case GL_EVAL_VERTEX_ATTRIB0_NV:
        return "GL_EVAL_VERTEX_ATTRIB0_NV";
    case GL_EVAL_VERTEX_ATTRIB1_NV:
        return "GL_EVAL_VERTEX_ATTRIB1_NV";
    case GL_EVAL_VERTEX_ATTRIB2_NV:
        return "GL_EVAL_VERTEX_ATTRIB2_NV";
    case GL_EVAL_VERTEX_ATTRIB3_NV:
        return "GL_EVAL_VERTEX_ATTRIB3_NV";
    case GL_EVAL_VERTEX_ATTRIB4_NV:
        return "GL_EVAL_VERTEX_ATTRIB4_NV";
    case GL_EVAL_VERTEX_ATTRIB5_NV:
        return "GL_EVAL_VERTEX_ATTRIB5_NV";
    case GL_EVAL_VERTEX_ATTRIB6_NV:
        return "GL_EVAL_VERTEX_ATTRIB6_NV";
    case GL_EVAL_VERTEX_ATTRIB7_NV:
        return "GL_EVAL_VERTEX_ATTRIB7_NV";
    case GL_EVAL_VERTEX_ATTRIB8_NV:
        return "GL_EVAL_VERTEX_ATTRIB8_NV";
    case GL_EVAL_VERTEX_ATTRIB9_NV:
        return "GL_EVAL_VERTEX_ATTRIB9_NV";
    case GL_EVAL_VERTEX_ATTRIB10_NV:
        return "GL_EVAL_VERTEX_ATTRIB10_NV";
    case GL_EVAL_VERTEX_ATTRIB11_NV:
        return "GL_EVAL_VERTEX_ATTRIB11_NV";
    case GL_EVAL_VERTEX_ATTRIB12_NV:
        return "GL_EVAL_VERTEX_ATTRIB12_NV";
    case GL_EVAL_VERTEX_ATTRIB13_NV:
        return "GL_EVAL_VERTEX_ATTRIB13_NV";
    case GL_EVAL_VERTEX_ATTRIB14_NV:
        return "GL_EVAL_VERTEX_ATTRIB14_NV";
    case GL_EVAL_VERTEX_ATTRIB15_NV:
        return "GL_EVAL_VERTEX_ATTRIB15_NV";
    case GL_MAX_MAP_TESSELLATION_NV:
        return "GL_MAX_MAP_TESSELLATION_NV";
    case GL_MAX_RATIONAL_EVAL_ORDER_NV:
        return "GL_MAX_RATIONAL_EVAL_ORDER_NV";
    case GL_MAX_PROGRAM_PATCH_ATTRIBS_NV:
        return "GL_MAX_PROGRAM_PATCH_ATTRIBS_NV";
    case GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV:
        return "GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV";
    case GL_UNSIGNED_INT_S8_S8_8_8_NV:
        return "GL_UNSIGNED_INT_S8_S8_8_8_NV";
    case GL_UNSIGNED_INT_8_8_S8_S8_REV_NV:
        return "GL_UNSIGNED_INT_8_8_S8_S8_REV_NV";
    case GL_DSDT_MAG_INTENSITY_NV:
        return "GL_DSDT_MAG_INTENSITY_NV";
    case GL_SHADER_CONSISTENT_NV:
        return "GL_SHADER_CONSISTENT_NV";
    case GL_TEXTURE_SHADER_NV:
        return "GL_TEXTURE_SHADER_NV";
    case GL_SHADER_OPERATION_NV:
        return "GL_SHADER_OPERATION_NV";
    case GL_CULL_MODES_NV:
        return "GL_CULL_MODES_NV";
    case GL_OFFSET_TEXTURE_MATRIX_NV:
        return "GL_OFFSET_TEXTURE_MATRIX_NV";
    case GL_OFFSET_TEXTURE_SCALE_NV:
        return "GL_OFFSET_TEXTURE_SCALE_NV";
    case GL_OFFSET_TEXTURE_BIAS_NV:
        return "GL_OFFSET_TEXTURE_BIAS_NV";
    case GL_PREVIOUS_TEXTURE_INPUT_NV:
        return "GL_PREVIOUS_TEXTURE_INPUT_NV";
    case GL_CONST_EYE_NV:
        return "GL_CONST_EYE_NV";
    case GL_PASS_THROUGH_NV:
        return "GL_PASS_THROUGH_NV";
    case GL_CULL_FRAGMENT_NV:
        return "GL_CULL_FRAGMENT_NV";
    case GL_OFFSET_TEXTURE_2D_NV:
        return "GL_OFFSET_TEXTURE_2D_NV";
    case GL_DEPENDENT_AR_TEXTURE_2D_NV:
        return "GL_DEPENDENT_AR_TEXTURE_2D_NV";
    case GL_DEPENDENT_GB_TEXTURE_2D_NV:
        return "GL_DEPENDENT_GB_TEXTURE_2D_NV";
    case GL_SURFACE_STATE_NV:
        return "GL_SURFACE_STATE_NV";
    case GL_DOT_PRODUCT_NV:
        return "GL_DOT_PRODUCT_NV";
    case GL_DOT_PRODUCT_DEPTH_REPLACE_NV:
        return "GL_DOT_PRODUCT_DEPTH_REPLACE_NV";
    case GL_DOT_PRODUCT_TEXTURE_2D_NV:
        return "GL_DOT_PRODUCT_TEXTURE_2D_NV";
    case GL_DOT_PRODUCT_TEXTURE_3D_NV:
        return "GL_DOT_PRODUCT_TEXTURE_3D_NV";
    case GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV:
        return "GL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV";
    case GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV:
        return "GL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV";
    case GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV:
        return "GL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV";
    case GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV:
        return "GL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV";
    case GL_HILO_NV:
        return "GL_HILO_NV";
    case GL_DSDT_NV:
        return "GL_DSDT_NV";
    case GL_DSDT_MAG_NV:
        return "GL_DSDT_MAG_NV";
    case GL_DSDT_MAG_VIB_NV:
        return "GL_DSDT_MAG_VIB_NV";
    case GL_HILO16_NV:
        return "GL_HILO16_NV";
    case GL_SIGNED_HILO_NV:
        return "GL_SIGNED_HILO_NV";
    case GL_SIGNED_HILO16_NV:
        return "GL_SIGNED_HILO16_NV";
    case GL_SIGNED_RGBA_NV:
        return "GL_SIGNED_RGBA_NV";
    case GL_SIGNED_RGBA8_NV:
        return "GL_SIGNED_RGBA8_NV";
    case GL_SURFACE_REGISTERED_NV:
        return "GL_SURFACE_REGISTERED_NV";
    case GL_SIGNED_RGB_NV:
        return "GL_SIGNED_RGB_NV";
    case GL_SIGNED_RGB8_NV:
        return "GL_SIGNED_RGB8_NV";
    case GL_SURFACE_MAPPED_NV:
        return "GL_SURFACE_MAPPED_NV";
    case GL_SIGNED_LUMINANCE_NV:
        return "GL_SIGNED_LUMINANCE_NV";
    case GL_SIGNED_LUMINANCE8_NV:
        return "GL_SIGNED_LUMINANCE8_NV";
    case GL_SIGNED_LUMINANCE_ALPHA_NV:
        return "GL_SIGNED_LUMINANCE_ALPHA_NV";
    case GL_SIGNED_LUMINANCE8_ALPHA8_NV:
        return "GL_SIGNED_LUMINANCE8_ALPHA8_NV";
    case GL_SIGNED_ALPHA_NV:
        return "GL_SIGNED_ALPHA_NV";
    case GL_SIGNED_ALPHA8_NV:
        return "GL_SIGNED_ALPHA8_NV";
    case GL_SIGNED_INTENSITY_NV:
        return "GL_SIGNED_INTENSITY_NV";
    case GL_SIGNED_INTENSITY8_NV:
        return "GL_SIGNED_INTENSITY8_NV";
    case GL_DSDT8_NV:
        return "GL_DSDT8_NV";
    case GL_DSDT8_MAG8_NV:
        return "GL_DSDT8_MAG8_NV";
    case GL_DSDT8_MAG8_INTENSITY8_NV:
        return "GL_DSDT8_MAG8_INTENSITY8_NV";
    case GL_SIGNED_RGB_UNSIGNED_ALPHA_NV:
        return "GL_SIGNED_RGB_UNSIGNED_ALPHA_NV";
    case GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV:
        return "GL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV";
    case GL_HI_SCALE_NV:
        return "GL_HI_SCALE_NV";
    case GL_LO_SCALE_NV:
        return "GL_LO_SCALE_NV";
    case GL_DS_SCALE_NV:
        return "GL_DS_SCALE_NV";
    case GL_DT_SCALE_NV:
        return "GL_DT_SCALE_NV";
    case GL_MAGNITUDE_SCALE_NV:
        return "GL_MAGNITUDE_SCALE_NV";
    case GL_VIBRANCE_SCALE_NV:
        return "GL_VIBRANCE_SCALE_NV";
    case GL_HI_BIAS_NV:
        return "GL_HI_BIAS_NV";
    case GL_LO_BIAS_NV:
        return "GL_LO_BIAS_NV";
    case GL_DS_BIAS_NV:
        return "GL_DS_BIAS_NV";
    case GL_DT_BIAS_NV:
        return "GL_DT_BIAS_NV";
    case GL_MAGNITUDE_BIAS_NV:
        return "GL_MAGNITUDE_BIAS_NV";
    case GL_VIBRANCE_BIAS_NV:
        return "GL_VIBRANCE_BIAS_NV";
    case GL_TEXTURE_BORDER_VALUES_NV:
        return "GL_TEXTURE_BORDER_VALUES_NV";
    case GL_TEXTURE_HI_SIZE_NV:
        return "GL_TEXTURE_HI_SIZE_NV";
    case GL_TEXTURE_LO_SIZE_NV:
        return "GL_TEXTURE_LO_SIZE_NV";
    case GL_TEXTURE_DS_SIZE_NV:
        return "GL_TEXTURE_DS_SIZE_NV";
    case GL_TEXTURE_DT_SIZE_NV:
        return "GL_TEXTURE_DT_SIZE_NV";
    case GL_TEXTURE_MAG_SIZE_NV:
        return "GL_TEXTURE_MAG_SIZE_NV";
    case GL_MODELVIEW2_ARB:
        return "GL_MODELVIEW2_ARB";
    case GL_MODELVIEW3_ARB:
        return "GL_MODELVIEW3_ARB";
    case GL_MODELVIEW4_ARB:
        return "GL_MODELVIEW4_ARB";
    case GL_MODELVIEW5_ARB:
        return "GL_MODELVIEW5_ARB";
    case GL_MODELVIEW6_ARB:
        return "GL_MODELVIEW6_ARB";
    case GL_MODELVIEW7_ARB:
        return "GL_MODELVIEW7_ARB";
    case GL_MODELVIEW8_ARB:
        return "GL_MODELVIEW8_ARB";
    case GL_MODELVIEW9_ARB:
        return "GL_MODELVIEW9_ARB";
    case GL_MODELVIEW10_ARB:
        return "GL_MODELVIEW10_ARB";
    case GL_MODELVIEW11_ARB:
        return "GL_MODELVIEW11_ARB";
    case GL_MODELVIEW12_ARB:
        return "GL_MODELVIEW12_ARB";
    case GL_MODELVIEW13_ARB:
        return "GL_MODELVIEW13_ARB";
    case GL_MODELVIEW14_ARB:
        return "GL_MODELVIEW14_ARB";
    case GL_MODELVIEW15_ARB:
        return "GL_MODELVIEW15_ARB";
    case GL_MODELVIEW16_ARB:
        return "GL_MODELVIEW16_ARB";
    case GL_MODELVIEW17_ARB:
        return "GL_MODELVIEW17_ARB";
    case GL_MODELVIEW18_ARB:
        return "GL_MODELVIEW18_ARB";
    case GL_MODELVIEW19_ARB:
        return "GL_MODELVIEW19_ARB";
    case GL_MODELVIEW20_ARB:
        return "GL_MODELVIEW20_ARB";
    case GL_MODELVIEW21_ARB:
        return "GL_MODELVIEW21_ARB";
    case GL_MODELVIEW22_ARB:
        return "GL_MODELVIEW22_ARB";
    case GL_MODELVIEW23_ARB:
        return "GL_MODELVIEW23_ARB";
    case GL_MODELVIEW24_ARB:
        return "GL_MODELVIEW24_ARB";
    case GL_MODELVIEW25_ARB:
        return "GL_MODELVIEW25_ARB";
    case GL_MODELVIEW26_ARB:
        return "GL_MODELVIEW26_ARB";
    case GL_MODELVIEW27_ARB:
        return "GL_MODELVIEW27_ARB";
    case GL_MODELVIEW28_ARB:
        return "GL_MODELVIEW28_ARB";
    case GL_MODELVIEW29_ARB:
        return "GL_MODELVIEW29_ARB";
    case GL_MODELVIEW30_ARB:
        return "GL_MODELVIEW30_ARB";
    case GL_MODELVIEW31_ARB:
        return "GL_MODELVIEW31_ARB";
    case GL_DOT3_RGB_EXT:
        return "GL_DOT3_RGB_EXT";
    case GL_PROGRAM_BINARY_LENGTH:
        return "GL_PROGRAM_BINARY_LENGTH";
    case GL_MIRROR_CLAMP_ATI:
        return "GL_MIRROR_CLAMP_ATI";
    case GL_MIRROR_CLAMP_TO_EDGE_ATI:
        return "GL_MIRROR_CLAMP_TO_EDGE_ATI";
    case GL_MODULATE_ADD_ATI:
        return "GL_MODULATE_ADD_ATI";
    case GL_MODULATE_SIGNED_ADD_ATI:
        return "GL_MODULATE_SIGNED_ADD_ATI";
    case GL_MODULATE_SUBTRACT_ATI:
        return "GL_MODULATE_SUBTRACT_ATI";
    case GL_YCBCR_MESA:
        return "GL_YCBCR_MESA";
    case GL_PACK_INVERT_MESA:
        return "GL_PACK_INVERT_MESA";
    case GL_TEXTURE_1D_STACK_MESAX:
        return "GL_TEXTURE_1D_STACK_MESAX";
    case GL_TEXTURE_2D_STACK_MESAX:
        return "GL_TEXTURE_2D_STACK_MESAX";
    case GL_PROXY_TEXTURE_1D_STACK_MESAX:
        return "GL_PROXY_TEXTURE_1D_STACK_MESAX";
    case GL_PROXY_TEXTURE_2D_STACK_MESAX:
        return "GL_PROXY_TEXTURE_2D_STACK_MESAX";
    case GL_TEXTURE_1D_STACK_BINDING_MESAX:
        return "GL_TEXTURE_1D_STACK_BINDING_MESAX";
    case GL_TEXTURE_2D_STACK_BINDING_MESAX:
        return "GL_TEXTURE_2D_STACK_BINDING_MESAX";
    case GL_STATIC_ATI:
        return "GL_STATIC_ATI";
    case GL_DYNAMIC_ATI:
        return "GL_DYNAMIC_ATI";
    case GL_PRESERVE_ATI:
        return "GL_PRESERVE_ATI";
    case GL_DISCARD_ATI:
        return "GL_DISCARD_ATI";
    case GL_BUFFER_SIZE:
        return "GL_BUFFER_SIZE";
    case GL_BUFFER_USAGE:
        return "GL_BUFFER_USAGE";
    case GL_ARRAY_OBJECT_BUFFER_ATI:
        return "GL_ARRAY_OBJECT_BUFFER_ATI";
    case GL_ARRAY_OBJECT_OFFSET_ATI:
        return "GL_ARRAY_OBJECT_OFFSET_ATI";
    case GL_ELEMENT_ARRAY_ATI:
        return "GL_ELEMENT_ARRAY_ATI";
    case GL_ELEMENT_ARRAY_TYPE_ATI:
        return "GL_ELEMENT_ARRAY_TYPE_ATI";
    case GL_ELEMENT_ARRAY_POINTER_ATI:
        return "GL_ELEMENT_ARRAY_POINTER_ATI";
    case GL_MAX_VERTEX_STREAMS_ATI:
        return "GL_MAX_VERTEX_STREAMS_ATI";
    case GL_VERTEX_STREAM0_ATI:
        return "GL_VERTEX_STREAM0_ATI";
    case GL_VERTEX_STREAM1_ATI:
        return "GL_VERTEX_STREAM1_ATI";
    case GL_VERTEX_STREAM2_ATI:
        return "GL_VERTEX_STREAM2_ATI";
    case GL_VERTEX_STREAM3_ATI:
        return "GL_VERTEX_STREAM3_ATI";
    case GL_VERTEX_STREAM4_ATI:
        return "GL_VERTEX_STREAM4_ATI";
    case GL_VERTEX_STREAM5_ATI:
        return "GL_VERTEX_STREAM5_ATI";
    case GL_VERTEX_STREAM6_ATI:
        return "GL_VERTEX_STREAM6_ATI";
    case GL_VERTEX_STREAM7_ATI:
        return "GL_VERTEX_STREAM7_ATI";
    case GL_VERTEX_SOURCE_ATI:
        return "GL_VERTEX_SOURCE_ATI";
    case GL_BUMP_ROT_MATRIX_ATI:
        return "GL_BUMP_ROT_MATRIX_ATI";
    case GL_BUMP_ROT_MATRIX_SIZE_ATI:
        return "GL_BUMP_ROT_MATRIX_SIZE_ATI";
    case GL_BUMP_NUM_TEX_UNITS_ATI:
        return "GL_BUMP_NUM_TEX_UNITS_ATI";
    case GL_BUMP_TEX_UNITS_ATI:
        return "GL_BUMP_TEX_UNITS_ATI";
    case GL_DUDV_ATI:
        return "GL_DUDV_ATI";
    case GL_DU8DV8_ATI:
        return "GL_DU8DV8_ATI";
    case GL_BUMP_ENVMAP_ATI:
        return "GL_BUMP_ENVMAP_ATI";
    case GL_BUMP_TARGET_ATI:
        return "GL_BUMP_TARGET_ATI";
    case GL_VERTEX_SHADER_EXT:
        return "GL_VERTEX_SHADER_EXT";
    case GL_VERTEX_SHADER_BINDING_EXT:
        return "GL_VERTEX_SHADER_BINDING_EXT";
    case GL_OP_INDEX_EXT:
        return "GL_OP_INDEX_EXT";
    case GL_OP_NEGATE_EXT:
        return "GL_OP_NEGATE_EXT";
    case GL_OP_DOT3_EXT:
        return "GL_OP_DOT3_EXT";
    case GL_OP_DOT4_EXT:
        return "GL_OP_DOT4_EXT";
    case GL_OP_MUL_EXT:
        return "GL_OP_MUL_EXT";
    case GL_OP_ADD_EXT:
        return "GL_OP_ADD_EXT";
    case GL_OP_MADD_EXT:
        return "GL_OP_MADD_EXT";
    case GL_OP_FRAC_EXT:
        return "GL_OP_FRAC_EXT";
    case GL_OP_MAX_EXT:
        return "GL_OP_MAX_EXT";
    case GL_OP_MIN_EXT:
        return "GL_OP_MIN_EXT";
    case GL_OP_SET_GE_EXT:
        return "GL_OP_SET_GE_EXT";
    case GL_OP_SET_LT_EXT:
        return "GL_OP_SET_LT_EXT";
    case GL_OP_CLAMP_EXT:
        return "GL_OP_CLAMP_EXT";
    case GL_OP_FLOOR_EXT:
        return "GL_OP_FLOOR_EXT";
    case GL_OP_ROUND_EXT:
        return "GL_OP_ROUND_EXT";
    case GL_OP_EXP_BASE_2_EXT:
        return "GL_OP_EXP_BASE_2_EXT";
    case GL_OP_LOG_BASE_2_EXT:
        return "GL_OP_LOG_BASE_2_EXT";
    case GL_OP_POWER_EXT:
        return "GL_OP_POWER_EXT";
    case GL_OP_RECIP_EXT:
        return "GL_OP_RECIP_EXT";
    case GL_OP_RECIP_SQRT_EXT:
        return "GL_OP_RECIP_SQRT_EXT";
    case GL_OP_SUB_EXT:
        return "GL_OP_SUB_EXT";
    case GL_OP_CROSS_PRODUCT_EXT:
        return "GL_OP_CROSS_PRODUCT_EXT";
    case GL_OP_MULTIPLY_MATRIX_EXT:
        return "GL_OP_MULTIPLY_MATRIX_EXT";
    case GL_OP_MOV_EXT:
        return "GL_OP_MOV_EXT";
    case GL_OUTPUT_VERTEX_EXT:
        return "GL_OUTPUT_VERTEX_EXT";
    case GL_OUTPUT_COLOR0_EXT:
        return "GL_OUTPUT_COLOR0_EXT";
    case GL_OUTPUT_COLOR1_EXT:
        return "GL_OUTPUT_COLOR1_EXT";
    case GL_OUTPUT_TEXTURE_COORD0_EXT:
        return "GL_OUTPUT_TEXTURE_COORD0_EXT";
    case GL_OUTPUT_TEXTURE_COORD1_EXT:
        return "GL_OUTPUT_TEXTURE_COORD1_EXT";
    case GL_OUTPUT_TEXTURE_COORD2_EXT:
        return "GL_OUTPUT_TEXTURE_COORD2_EXT";
    case GL_OUTPUT_TEXTURE_COORD3_EXT:
        return "GL_OUTPUT_TEXTURE_COORD3_EXT";
    case GL_OUTPUT_TEXTURE_COORD4_EXT:
        return "GL_OUTPUT_TEXTURE_COORD4_EXT";
    case GL_OUTPUT_TEXTURE_COORD5_EXT:
        return "GL_OUTPUT_TEXTURE_COORD5_EXT";
    case GL_OUTPUT_TEXTURE_COORD6_EXT:
        return "GL_OUTPUT_TEXTURE_COORD6_EXT";
    case GL_OUTPUT_TEXTURE_COORD7_EXT:
        return "GL_OUTPUT_TEXTURE_COORD7_EXT";
    case GL_OUTPUT_TEXTURE_COORD8_EXT:
        return "GL_OUTPUT_TEXTURE_COORD8_EXT";
    case GL_OUTPUT_TEXTURE_COORD9_EXT:
        return "GL_OUTPUT_TEXTURE_COORD9_EXT";
    case GL_OUTPUT_TEXTURE_COORD10_EXT:
        return "GL_OUTPUT_TEXTURE_COORD10_EXT";
    case GL_OUTPUT_TEXTURE_COORD11_EXT:
        return "GL_OUTPUT_TEXTURE_COORD11_EXT";
    case GL_OUTPUT_TEXTURE_COORD12_EXT:
        return "GL_OUTPUT_TEXTURE_COORD12_EXT";
    case GL_OUTPUT_TEXTURE_COORD13_EXT:
        return "GL_OUTPUT_TEXTURE_COORD13_EXT";
    case GL_OUTPUT_TEXTURE_COORD14_EXT:
        return "GL_OUTPUT_TEXTURE_COORD14_EXT";
    case GL_OUTPUT_TEXTURE_COORD15_EXT:
        return "GL_OUTPUT_TEXTURE_COORD15_EXT";
    case GL_OUTPUT_TEXTURE_COORD16_EXT:
        return "GL_OUTPUT_TEXTURE_COORD16_EXT";
    case GL_OUTPUT_TEXTURE_COORD17_EXT:
        return "GL_OUTPUT_TEXTURE_COORD17_EXT";
    case GL_OUTPUT_TEXTURE_COORD18_EXT:
        return "GL_OUTPUT_TEXTURE_COORD18_EXT";
    case GL_OUTPUT_TEXTURE_COORD19_EXT:
        return "GL_OUTPUT_TEXTURE_COORD19_EXT";
    case GL_OUTPUT_TEXTURE_COORD20_EXT:
        return "GL_OUTPUT_TEXTURE_COORD20_EXT";
    case GL_OUTPUT_TEXTURE_COORD21_EXT:
        return "GL_OUTPUT_TEXTURE_COORD21_EXT";
    case GL_OUTPUT_TEXTURE_COORD22_EXT:
        return "GL_OUTPUT_TEXTURE_COORD22_EXT";
    case GL_OUTPUT_TEXTURE_COORD23_EXT:
        return "GL_OUTPUT_TEXTURE_COORD23_EXT";
    case GL_OUTPUT_TEXTURE_COORD24_EXT:
        return "GL_OUTPUT_TEXTURE_COORD24_EXT";
    case GL_OUTPUT_TEXTURE_COORD25_EXT:
        return "GL_OUTPUT_TEXTURE_COORD25_EXT";
    case GL_OUTPUT_TEXTURE_COORD26_EXT:
        return "GL_OUTPUT_TEXTURE_COORD26_EXT";
    case GL_OUTPUT_TEXTURE_COORD27_EXT:
        return "GL_OUTPUT_TEXTURE_COORD27_EXT";
    case GL_OUTPUT_TEXTURE_COORD28_EXT:
        return "GL_OUTPUT_TEXTURE_COORD28_EXT";
    case GL_OUTPUT_TEXTURE_COORD29_EXT:
        return "GL_OUTPUT_TEXTURE_COORD29_EXT";
    case GL_OUTPUT_TEXTURE_COORD30_EXT:
        return "GL_OUTPUT_TEXTURE_COORD30_EXT";
    case GL_OUTPUT_TEXTURE_COORD31_EXT:
        return "GL_OUTPUT_TEXTURE_COORD31_EXT";
    case GL_OUTPUT_FOG_EXT:
        return "GL_OUTPUT_FOG_EXT";
    case GL_SCALAR_EXT:
        return "GL_SCALAR_EXT";
    case GL_VECTOR_EXT:
        return "GL_VECTOR_EXT";
    case GL_MATRIX_EXT:
        return "GL_MATRIX_EXT";
    case GL_VARIANT_EXT:
        return "GL_VARIANT_EXT";
    case GL_INVARIANT_EXT:
        return "GL_INVARIANT_EXT";
    case GL_LOCAL_CONSTANT_EXT:
        return "GL_LOCAL_CONSTANT_EXT";
    case GL_LOCAL_EXT:
        return "GL_LOCAL_EXT";
    case GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT:
        return "GL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT";
    case GL_MAX_VERTEX_SHADER_VARIANTS_EXT:
        return "GL_MAX_VERTEX_SHADER_VARIANTS_EXT";
    case GL_MAX_VERTEX_SHADER_INVARIANTS_EXT:
        return "GL_MAX_VERTEX_SHADER_INVARIANTS_EXT";
    case GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT:
        return "GL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT";
    case GL_MAX_VERTEX_SHADER_LOCALS_EXT:
        return "GL_MAX_VERTEX_SHADER_LOCALS_EXT";
    case GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT:
        return "GL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT";
    case GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT:
        return "GL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT";
    case GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT:
        return "GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT";
    case GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT:
        return "GL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT";
    case GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT:
        return "GL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT";
    case GL_VERTEX_SHADER_INSTRUCTIONS_EXT:
        return "GL_VERTEX_SHADER_INSTRUCTIONS_EXT";
    case GL_VERTEX_SHADER_VARIANTS_EXT:
        return "GL_VERTEX_SHADER_VARIANTS_EXT";
    case GL_VERTEX_SHADER_INVARIANTS_EXT:
        return "GL_VERTEX_SHADER_INVARIANTS_EXT";
    case GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT:
        return "GL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT";
    case GL_VERTEX_SHADER_LOCALS_EXT:
        return "GL_VERTEX_SHADER_LOCALS_EXT";
    case GL_VERTEX_SHADER_OPTIMIZED_EXT:
        return "GL_VERTEX_SHADER_OPTIMIZED_EXT";
    case GL_X_EXT:
        return "GL_X_EXT";
    case GL_Y_EXT:
        return "GL_Y_EXT";
    case GL_Z_EXT:
        return "GL_Z_EXT";
    case GL_W_EXT:
        return "GL_W_EXT";
    case GL_NEGATIVE_X_EXT:
        return "GL_NEGATIVE_X_EXT";
    case GL_NEGATIVE_Y_EXT:
        return "GL_NEGATIVE_Y_EXT";
    case GL_NEGATIVE_Z_EXT:
        return "GL_NEGATIVE_Z_EXT";
    case GL_NEGATIVE_W_EXT:
        return "GL_NEGATIVE_W_EXT";
    case GL_ZERO_EXT:
        return "GL_ZERO_EXT";
    case GL_ONE_EXT:
        return "GL_ONE_EXT";
    case GL_NEGATIVE_ONE_EXT:
        return "GL_NEGATIVE_ONE_EXT";
    case GL_NORMALIZED_RANGE_EXT:
        return "GL_NORMALIZED_RANGE_EXT";
    case GL_FULL_RANGE_EXT:
        return "GL_FULL_RANGE_EXT";
    case GL_CURRENT_VERTEX_EXT:
        return "GL_CURRENT_VERTEX_EXT";
    case GL_MVP_MATRIX_EXT:
        return "GL_MVP_MATRIX_EXT";
    case GL_VARIANT_VALUE_EXT:
        return "GL_VARIANT_VALUE_EXT";
    case GL_VARIANT_DATATYPE_EXT:
        return "GL_VARIANT_DATATYPE_EXT";
    case GL_VARIANT_ARRAY_STRIDE_EXT:
        return "GL_VARIANT_ARRAY_STRIDE_EXT";
    case GL_VARIANT_ARRAY_TYPE_EXT:
        return "GL_VARIANT_ARRAY_TYPE_EXT";
    case GL_VARIANT_ARRAY_EXT:
        return "GL_VARIANT_ARRAY_EXT";
    case GL_VARIANT_ARRAY_POINTER_EXT:
        return "GL_VARIANT_ARRAY_POINTER_EXT";
    case GL_INVARIANT_VALUE_EXT:
        return "GL_INVARIANT_VALUE_EXT";
    case GL_INVARIANT_DATATYPE_EXT:
        return "GL_INVARIANT_DATATYPE_EXT";
    case GL_LOCAL_CONSTANT_VALUE_EXT:
        return "GL_LOCAL_CONSTANT_VALUE_EXT";
    case GL_LOCAL_CONSTANT_DATATYPE_EXT:
        return "GL_LOCAL_CONSTANT_DATATYPE_EXT";
    case GL_PN_TRIANGLES_ATI:
        return "GL_PN_TRIANGLES_ATI";
    case GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI:
        return "GL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI";
    case GL_PN_TRIANGLES_POINT_MODE_ATI:
        return "GL_PN_TRIANGLES_POINT_MODE_ATI";
    case GL_PN_TRIANGLES_NORMAL_MODE_ATI:
        return "GL_PN_TRIANGLES_NORMAL_MODE_ATI";
    case GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI:
        return "GL_PN_TRIANGLES_TESSELATION_LEVEL_ATI";
    case GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI:
        return "GL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI";
    case GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI:
        return "GL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI";
    case GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI:
        return "GL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI";
    case GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI:
        return "GL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI";
    case GL_VBO_FREE_MEMORY_ATI:
        return "GL_VBO_FREE_MEMORY_ATI";
    case GL_TEXTURE_FREE_MEMORY_ATI:
        return "GL_TEXTURE_FREE_MEMORY_ATI";
    case GL_RENDERBUFFER_FREE_MEMORY_ATI:
        return "GL_RENDERBUFFER_FREE_MEMORY_ATI";
    case GL_NUM_PROGRAM_BINARY_FORMATS:
        return "GL_NUM_PROGRAM_BINARY_FORMATS";
    case GL_PROGRAM_BINARY_FORMATS:
        return "GL_PROGRAM_BINARY_FORMATS";
    case GL_STENCIL_BACK_FUNC:
        return "GL_STENCIL_BACK_FUNC";
    case GL_STENCIL_BACK_FAIL:
        return "GL_STENCIL_BACK_FAIL";
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
        return "GL_STENCIL_BACK_PASS_DEPTH_FAIL";
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:
        return "GL_STENCIL_BACK_PASS_DEPTH_PASS";
    case GL_FRAGMENT_PROGRAM_ARB:
        return "GL_FRAGMENT_PROGRAM_ARB";
    case GL_PROGRAM_ALU_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_ALU_INSTRUCTIONS_ARB";
    case GL_PROGRAM_TEX_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_TEX_INSTRUCTIONS_ARB";
    case GL_PROGRAM_TEX_INDIRECTIONS_ARB:
        return "GL_PROGRAM_TEX_INDIRECTIONS_ARB";
    case GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB";
    case GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB";
    case GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB:
        return "GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB";
    case GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB:
        return "GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB";
    case GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB";
    case GL_RGBA32F:
        return "GL_RGBA32F";
    case GL_RGB32F:
        return "GL_RGB32F";
    case GL_ALPHA32F_ARB:
        return "GL_ALPHA32F_ARB";
    case GL_INTENSITY32F_ARB:
        return "GL_INTENSITY32F_ARB";
    case GL_LUMINANCE32F_ARB:
        return "GL_LUMINANCE32F_ARB";
    case GL_LUMINANCE_ALPHA32F_ARB:
        return "GL_LUMINANCE_ALPHA32F_ARB";
    case GL_RGBA16F:
        return "GL_RGBA16F";
    case GL_RGB16F:
        return "GL_RGB16F";
    case GL_ALPHA16F_ARB:
        return "GL_ALPHA16F_ARB";
    case GL_INTENSITY16F_ARB:
        return "GL_INTENSITY16F_ARB";
    case GL_LUMINANCE16F_ARB:
        return "GL_LUMINANCE16F_ARB";
    case GL_LUMINANCE_ALPHA16F_ARB:
        return "GL_LUMINANCE_ALPHA16F_ARB";
    case GL_RGBA_FLOAT_MODE_ARB:
        return "GL_RGBA_FLOAT_MODE_ARB";
    case GL_MAX_DRAW_BUFFERS:
        return "GL_MAX_DRAW_BUFFERS";
    case GL_DRAW_BUFFER0:
        return "GL_DRAW_BUFFER0";
    case GL_DRAW_BUFFER1:
        return "GL_DRAW_BUFFER1";
    case GL_DRAW_BUFFER2:
        return "GL_DRAW_BUFFER2";
    case GL_DRAW_BUFFER3:
        return "GL_DRAW_BUFFER3";
    case GL_DRAW_BUFFER4:
        return "GL_DRAW_BUFFER4";
    case GL_DRAW_BUFFER5:
        return "GL_DRAW_BUFFER5";
    case GL_DRAW_BUFFER6:
        return "GL_DRAW_BUFFER6";
    case GL_DRAW_BUFFER7:
        return "GL_DRAW_BUFFER7";
    case GL_DRAW_BUFFER8:
        return "GL_DRAW_BUFFER8";
    case GL_DRAW_BUFFER9:
        return "GL_DRAW_BUFFER9";
    case GL_DRAW_BUFFER10:
        return "GL_DRAW_BUFFER10";
    case GL_DRAW_BUFFER11:
        return "GL_DRAW_BUFFER11";
    case GL_DRAW_BUFFER12:
        return "GL_DRAW_BUFFER12";
    case GL_DRAW_BUFFER13:
        return "GL_DRAW_BUFFER13";
    case GL_DRAW_BUFFER14:
        return "GL_DRAW_BUFFER14";
    case GL_DRAW_BUFFER15:
        return "GL_DRAW_BUFFER15";
    case GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI:
        return "GL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI";
    case GL_BLEND_EQUATION_ALPHA:
        return "GL_BLEND_EQUATION_ALPHA";
    case GL_MATRIX_PALETTE_ARB:
        return "GL_MATRIX_PALETTE_ARB";
    case GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB:
        return "GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB";
    case GL_MAX_PALETTE_MATRICES_ARB:
        return "GL_MAX_PALETTE_MATRICES_ARB";
    case GL_CURRENT_PALETTE_MATRIX_ARB:
        return "GL_CURRENT_PALETTE_MATRIX_ARB";
    case GL_MATRIX_INDEX_ARRAY_ARB:
        return "GL_MATRIX_INDEX_ARRAY_ARB";
    case GL_CURRENT_MATRIX_INDEX_ARB:
        return "GL_CURRENT_MATRIX_INDEX_ARB";
    case GL_MATRIX_INDEX_ARRAY_SIZE_ARB:
        return "GL_MATRIX_INDEX_ARRAY_SIZE_ARB";
    case GL_MATRIX_INDEX_ARRAY_TYPE_ARB:
        return "GL_MATRIX_INDEX_ARRAY_TYPE_ARB";
    case GL_MATRIX_INDEX_ARRAY_STRIDE_ARB:
        return "GL_MATRIX_INDEX_ARRAY_STRIDE_ARB";
    case GL_MATRIX_INDEX_ARRAY_POINTER_ARB:
        return "GL_MATRIX_INDEX_ARRAY_POINTER_ARB";
    case GL_TEXTURE_DEPTH_SIZE:
        return "GL_TEXTURE_DEPTH_SIZE";
    case GL_DEPTH_TEXTURE_MODE:
        return "GL_DEPTH_TEXTURE_MODE";
    case GL_TEXTURE_COMPARE_MODE:
        return "GL_TEXTURE_COMPARE_MODE";
    case GL_TEXTURE_COMPARE_FUNC:
        return "GL_TEXTURE_COMPARE_FUNC";
    case GL_COMPARE_REF_TO_TEXTURE:
        return "GL_COMPARE_REF_TO_TEXTURE";
    case GL_TEXTURE_CUBE_MAP_SEAMLESS:
        return "GL_TEXTURE_CUBE_MAP_SEAMLESS";
    case GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV:
        return "GL_OFFSET_PROJECTIVE_TEXTURE_2D_NV";
    case GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV:
        return "GL_OFFSET_PROJECTIVE_TEXTURE_2D_SCALE_NV";
    case GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV:
        return "GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_NV";
    case GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV:
        return "GL_OFFSET_PROJECTIVE_TEXTURE_RECTANGLE_SCALE_NV";
    case GL_OFFSET_HILO_TEXTURE_2D_NV:
        return "GL_OFFSET_HILO_TEXTURE_2D_NV";
    case GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV:
        return "GL_OFFSET_HILO_TEXTURE_RECTANGLE_NV";
    case GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV:
        return "GL_OFFSET_HILO_PROJECTIVE_TEXTURE_2D_NV";
    case GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV:
        return "GL_OFFSET_HILO_PROJECTIVE_TEXTURE_RECTANGLE_NV";
    case GL_DEPENDENT_HILO_TEXTURE_2D_NV:
        return "GL_DEPENDENT_HILO_TEXTURE_2D_NV";
    case GL_DEPENDENT_RGB_TEXTURE_3D_NV:
        return "GL_DEPENDENT_RGB_TEXTURE_3D_NV";
    case GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV:
        return "GL_DEPENDENT_RGB_TEXTURE_CUBE_MAP_NV";
    case GL_DOT_PRODUCT_PASS_THROUGH_NV:
        return "GL_DOT_PRODUCT_PASS_THROUGH_NV";
    case GL_DOT_PRODUCT_TEXTURE_1D_NV:
        return "GL_DOT_PRODUCT_TEXTURE_1D_NV";
    case GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV:
        return "GL_DOT_PRODUCT_AFFINE_DEPTH_REPLACE_NV";
    case GL_HILO8_NV:
        return "GL_HILO8_NV";
    case GL_SIGNED_HILO8_NV:
        return "GL_SIGNED_HILO8_NV";
    case GL_FORCE_BLUE_TO_ONE_NV:
        return "GL_FORCE_BLUE_TO_ONE_NV";
    case GL_POINT_SPRITE:
        return "GL_POINT_SPRITE";
    case GL_COORD_REPLACE:
        return "GL_COORD_REPLACE";
    case GL_POINT_SPRITE_R_MODE_NV:
        return "GL_POINT_SPRITE_R_MODE_NV";
    case GL_QUERY_COUNTER_BITS:
        return "GL_QUERY_COUNTER_BITS";
    case GL_CURRENT_QUERY:
        return "GL_CURRENT_QUERY";
    case GL_QUERY_RESULT:
        return "GL_QUERY_RESULT";
    case GL_QUERY_RESULT_AVAILABLE:
        return "GL_QUERY_RESULT_AVAILABLE";
    case GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV:
        return "GL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV";
    case GL_MAX_VERTEX_ATTRIBS:
        return "GL_MAX_VERTEX_ATTRIBS";
    case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
        return "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED";
    case GL_MAX_TESS_CONTROL_INPUT_COMPONENTS:
        return "GL_MAX_TESS_CONTROL_INPUT_COMPONENTS";
    case GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS:
        return "GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS";
    case GL_DEPTH_STENCIL_TO_RGBA_NV:
        return "GL_DEPTH_STENCIL_TO_RGBA_NV";
    case GL_DEPTH_STENCIL_TO_BGRA_NV:
        return "GL_DEPTH_STENCIL_TO_BGRA_NV";
    case GL_FRAGMENT_PROGRAM_NV:
        return "GL_FRAGMENT_PROGRAM_NV";
    case GL_MAX_TEXTURE_COORDS:
        return "GL_MAX_TEXTURE_COORDS";
    case GL_MAX_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_TEXTURE_IMAGE_UNITS";
    case GL_FRAGMENT_PROGRAM_BINDING_NV:
        return "GL_FRAGMENT_PROGRAM_BINDING_NV";
    case GL_PROGRAM_ERROR_STRING_ARB:
        return "GL_PROGRAM_ERROR_STRING_ARB";
    case GL_PROGRAM_FORMAT_ASCII_ARB:
        return "GL_PROGRAM_FORMAT_ASCII_ARB";
    case GL_PROGRAM_FORMAT_ARB:
        return "GL_PROGRAM_FORMAT_ARB";
    case GL_WRITE_PIXEL_DATA_RANGE_NV:
        return "GL_WRITE_PIXEL_DATA_RANGE_NV";
    case GL_READ_PIXEL_DATA_RANGE_NV:
        return "GL_READ_PIXEL_DATA_RANGE_NV";
    case GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV:
        return "GL_WRITE_PIXEL_DATA_RANGE_LENGTH_NV";
    case GL_READ_PIXEL_DATA_RANGE_LENGTH_NV:
        return "GL_READ_PIXEL_DATA_RANGE_LENGTH_NV";
    case GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV:
        return "GL_WRITE_PIXEL_DATA_RANGE_POINTER_NV";
    case GL_READ_PIXEL_DATA_RANGE_POINTER_NV:
        return "GL_READ_PIXEL_DATA_RANGE_POINTER_NV";
    case GL_GEOMETRY_SHADER_INVOCATIONS:
        return "GL_GEOMETRY_SHADER_INVOCATIONS";
    case GL_FLOAT_R_NV:
        return "GL_FLOAT_R_NV";
    case GL_FLOAT_RG_NV:
        return "GL_FLOAT_RG_NV";
    case GL_FLOAT_RGB_NV:
        return "GL_FLOAT_RGB_NV";
    case GL_FLOAT_RGBA_NV:
        return "GL_FLOAT_RGBA_NV";
    case GL_FLOAT_R16_NV:
        return "GL_FLOAT_R16_NV";
    case GL_FLOAT_R32_NV:
        return "GL_FLOAT_R32_NV";
    case GL_FLOAT_RG16_NV:
        return "GL_FLOAT_RG16_NV";
    case GL_FLOAT_RG32_NV:
        return "GL_FLOAT_RG32_NV";
    case GL_FLOAT_RGB16_NV:
        return "GL_FLOAT_RGB16_NV";
    case GL_FLOAT_RGB32_NV:
        return "GL_FLOAT_RGB32_NV";
    case GL_FLOAT_RGBA16_NV:
        return "GL_FLOAT_RGBA16_NV";
    case GL_FLOAT_RGBA32_NV:
        return "GL_FLOAT_RGBA32_NV";
    case GL_TEXTURE_FLOAT_COMPONENTS_NV:
        return "GL_TEXTURE_FLOAT_COMPONENTS_NV";
    case GL_FLOAT_CLEAR_COLOR_VALUE_NV:
        return "GL_FLOAT_CLEAR_COLOR_VALUE_NV";
    case GL_FLOAT_RGBA_MODE_NV:
        return "GL_FLOAT_RGBA_MODE_NV";
    case GL_TEXTURE_UNSIGNED_REMAP_MODE_NV:
        return "GL_TEXTURE_UNSIGNED_REMAP_MODE_NV";
    case GL_DEPTH_BOUNDS_TEST_EXT:
        return "GL_DEPTH_BOUNDS_TEST_EXT";
    case GL_DEPTH_BOUNDS_EXT:
        return "GL_DEPTH_BOUNDS_EXT";
    case GL_ARRAY_BUFFER:
        return "GL_ARRAY_BUFFER";
    case GL_ELEMENT_ARRAY_BUFFER:
        return "GL_ELEMENT_ARRAY_BUFFER";
    case GL_ARRAY_BUFFER_BINDING:
        return "GL_ARRAY_BUFFER_BINDING";
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:
        return "GL_ELEMENT_ARRAY_BUFFER_BINDING";
    case GL_VERTEX_ARRAY_BUFFER_BINDING:
        return "GL_VERTEX_ARRAY_BUFFER_BINDING";
    case GL_NORMAL_ARRAY_BUFFER_BINDING:
        return "GL_NORMAL_ARRAY_BUFFER_BINDING";
    case GL_COLOR_ARRAY_BUFFER_BINDING:
        return "GL_COLOR_ARRAY_BUFFER_BINDING";
    case GL_INDEX_ARRAY_BUFFER_BINDING:
        return "GL_INDEX_ARRAY_BUFFER_BINDING";
    case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
        return "GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING";
    case GL_EDGE_FLAG_ARRAY_BUFFER_BINDING:
        return "GL_EDGE_FLAG_ARRAY_BUFFER_BINDING";
    case GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING:
        return "GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING";
    case GL_FOG_COORD_ARRAY_BUFFER_BINDING:
        return "GL_FOG_COORD_ARRAY_BUFFER_BINDING";
    case GL_WEIGHT_ARRAY_BUFFER_BINDING:
        return "GL_WEIGHT_ARRAY_BUFFER_BINDING";
    case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
        return "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING";
    case GL_PROGRAM_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_INSTRUCTIONS_ARB";
    case GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB:
        return "GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB";
    case GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB";
    case GL_PROGRAM_TEMPORARIES_ARB:
        return "GL_PROGRAM_TEMPORARIES_ARB";
    case GL_MAX_PROGRAM_TEMPORARIES_ARB:
        return "GL_MAX_PROGRAM_TEMPORARIES_ARB";
    case GL_PROGRAM_NATIVE_TEMPORARIES_ARB:
        return "GL_PROGRAM_NATIVE_TEMPORARIES_ARB";
    case GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB:
        return "GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB";
    case GL_PROGRAM_PARAMETERS_ARB:
        return "GL_PROGRAM_PARAMETERS_ARB";
    case GL_MAX_PROGRAM_PARAMETERS_ARB:
        return "GL_MAX_PROGRAM_PARAMETERS_ARB";
    case GL_PROGRAM_NATIVE_PARAMETERS_ARB:
        return "GL_PROGRAM_NATIVE_PARAMETERS_ARB";
    case GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB";
    case GL_PROGRAM_ATTRIBS_ARB:
        return "GL_PROGRAM_ATTRIBS_ARB";
    case GL_MAX_PROGRAM_ATTRIBS_ARB:
        return "GL_MAX_PROGRAM_ATTRIBS_ARB";
    case GL_PROGRAM_NATIVE_ATTRIBS_ARB:
        return "GL_PROGRAM_NATIVE_ATTRIBS_ARB";
    case GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB";
    case GL_PROGRAM_ADDRESS_REGISTERS_ARB:
        return "GL_PROGRAM_ADDRESS_REGISTERS_ARB";
    case GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB:
        return "GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB";
    case GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB:
        return "GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB";
    case GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB:
        return "GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB";
    case GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB:
        return "GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB";
    case GL_MAX_PROGRAM_ENV_PARAMETERS_ARB:
        return "GL_MAX_PROGRAM_ENV_PARAMETERS_ARB";
    case GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB:
        return "GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB";
    case GL_TRANSPOSE_CURRENT_MATRIX_ARB:
        return "GL_TRANSPOSE_CURRENT_MATRIX_ARB";
    case GL_READ_ONLY:
        return "GL_READ_ONLY";
    case GL_WRITE_ONLY:
        return "GL_WRITE_ONLY";
    case GL_READ_WRITE:
        return "GL_READ_WRITE";
    case GL_BUFFER_ACCESS:
        return "GL_BUFFER_ACCESS";
    case GL_BUFFER_MAPPED:
        return "GL_BUFFER_MAPPED";
    case GL_BUFFER_MAP_POINTER:
        return "GL_BUFFER_MAP_POINTER";
    case GL_WRITE_DISCARD_NV:
        return "GL_WRITE_DISCARD_NV";
    case GL_TIME_ELAPSED:
        return "GL_TIME_ELAPSED";
    case GL_MATRIX0_ARB:
        return "GL_MATRIX0_ARB";
    case GL_MATRIX1_ARB:
        return "GL_MATRIX1_ARB";
    case GL_MATRIX2_ARB:
        return "GL_MATRIX2_ARB";
    case GL_MATRIX3_ARB:
        return "GL_MATRIX3_ARB";
    case GL_MATRIX4_ARB:
        return "GL_MATRIX4_ARB";
    case GL_MATRIX5_ARB:
        return "GL_MATRIX5_ARB";
    case GL_MATRIX6_ARB:
        return "GL_MATRIX6_ARB";
    case GL_MATRIX7_ARB:
        return "GL_MATRIX7_ARB";
    case GL_MATRIX8_ARB:
        return "GL_MATRIX8_ARB";
    case GL_MATRIX9_ARB:
        return "GL_MATRIX9_ARB";
    case GL_MATRIX10_ARB:
        return "GL_MATRIX10_ARB";
    case GL_MATRIX11_ARB:
        return "GL_MATRIX11_ARB";
    case GL_MATRIX12_ARB:
        return "GL_MATRIX12_ARB";
    case GL_MATRIX13_ARB:
        return "GL_MATRIX13_ARB";
    case GL_MATRIX14_ARB:
        return "GL_MATRIX14_ARB";
    case GL_MATRIX15_ARB:
        return "GL_MATRIX15_ARB";
    case GL_MATRIX16_ARB:
        return "GL_MATRIX16_ARB";
    case GL_MATRIX17_ARB:
        return "GL_MATRIX17_ARB";
    case GL_MATRIX18_ARB:
        return "GL_MATRIX18_ARB";
    case GL_MATRIX19_ARB:
        return "GL_MATRIX19_ARB";
    case GL_MATRIX20_ARB:
        return "GL_MATRIX20_ARB";
    case GL_MATRIX21_ARB:
        return "GL_MATRIX21_ARB";
    case GL_MATRIX22_ARB:
        return "GL_MATRIX22_ARB";
    case GL_MATRIX23_ARB:
        return "GL_MATRIX23_ARB";
    case GL_MATRIX24_ARB:
        return "GL_MATRIX24_ARB";
    case GL_MATRIX25_ARB:
        return "GL_MATRIX25_ARB";
    case GL_MATRIX26_ARB:
        return "GL_MATRIX26_ARB";
    case GL_MATRIX27_ARB:
        return "GL_MATRIX27_ARB";
    case GL_MATRIX28_ARB:
        return "GL_MATRIX28_ARB";
    case GL_MATRIX29_ARB:
        return "GL_MATRIX29_ARB";
    case GL_MATRIX30_ARB:
        return "GL_MATRIX30_ARB";
    case GL_MATRIX31_ARB:
        return "GL_MATRIX31_ARB";
    case GL_STREAM_DRAW:
        return "GL_STREAM_DRAW";
    case GL_STREAM_READ:
        return "GL_STREAM_READ";
    case GL_STREAM_COPY:
        return "GL_STREAM_COPY";
    case GL_STATIC_DRAW:
        return "GL_STATIC_DRAW";
    case GL_STATIC_READ:
        return "GL_STATIC_READ";
    case GL_STATIC_COPY:
        return "GL_STATIC_COPY";
    case GL_DYNAMIC_DRAW:
        return "GL_DYNAMIC_DRAW";
    case GL_DYNAMIC_READ:
        return "GL_DYNAMIC_READ";
    case GL_DYNAMIC_COPY:
        return "GL_DYNAMIC_COPY";
    case GL_PIXEL_PACK_BUFFER:
        return "GL_PIXEL_PACK_BUFFER";
    case GL_PIXEL_UNPACK_BUFFER:
        return "GL_PIXEL_UNPACK_BUFFER";
    case GL_PIXEL_PACK_BUFFER_BINDING:
        return "GL_PIXEL_PACK_BUFFER_BINDING";
    case GL_PIXEL_UNPACK_BUFFER_BINDING:
        return "GL_PIXEL_UNPACK_BUFFER_BINDING";
    case GL_DEPTH24_STENCIL8:
        return "GL_DEPTH24_STENCIL8";
    case GL_TEXTURE_STENCIL_SIZE:
        return "GL_TEXTURE_STENCIL_SIZE";
    case GL_STENCIL_TAG_BITS_EXT:
        return "GL_STENCIL_TAG_BITS_EXT";
    case GL_STENCIL_CLEAR_TAG_VALUE_EXT:
        return "GL_STENCIL_CLEAR_TAG_VALUE_EXT";
    case GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV:
        return "GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV";
    case GL_MAX_PROGRAM_CALL_DEPTH_NV:
        return "GL_MAX_PROGRAM_CALL_DEPTH_NV";
    case GL_MAX_PROGRAM_IF_DEPTH_NV:
        return "GL_MAX_PROGRAM_IF_DEPTH_NV";
    case GL_MAX_PROGRAM_LOOP_DEPTH_NV:
        return "GL_MAX_PROGRAM_LOOP_DEPTH_NV";
    case GL_MAX_PROGRAM_LOOP_COUNT_NV:
        return "GL_MAX_PROGRAM_LOOP_COUNT_NV";
    case GL_SRC1_COLOR:
        return "GL_SRC1_COLOR";
    case GL_ONE_MINUS_SRC1_COLOR:
        return "GL_ONE_MINUS_SRC1_COLOR";
    case GL_ONE_MINUS_SRC1_ALPHA:
        return "GL_ONE_MINUS_SRC1_ALPHA";
    case GL_MAX_DUAL_SOURCE_DRAW_BUFFERS:
        return "GL_MAX_DUAL_SOURCE_DRAW_BUFFERS";
    case GL_VERTEX_ATTRIB_ARRAY_INTEGER:
        return "GL_VERTEX_ATTRIB_ARRAY_INTEGER";
    case GL_VERTEX_ATTRIB_ARRAY_DIVISOR:
        return "GL_VERTEX_ATTRIB_ARRAY_DIVISOR";
    case GL_MAX_ARRAY_TEXTURE_LAYERS:
        return "GL_MAX_ARRAY_TEXTURE_LAYERS";
    case GL_MIN_PROGRAM_TEXEL_OFFSET:
        return "GL_MIN_PROGRAM_TEXEL_OFFSET";
    case GL_MAX_PROGRAM_TEXEL_OFFSET:
        return "GL_MAX_PROGRAM_TEXEL_OFFSET";
    case GL_PROGRAM_ATTRIB_COMPONENTS_NV:
        return "GL_PROGRAM_ATTRIB_COMPONENTS_NV";
    case GL_PROGRAM_RESULT_COMPONENTS_NV:
        return "GL_PROGRAM_RESULT_COMPONENTS_NV";
    case GL_MAX_PROGRAM_ATTRIB_COMPONENTS_NV:
        return "GL_MAX_PROGRAM_ATTRIB_COMPONENTS_NV";
    case GL_MAX_PROGRAM_RESULT_COMPONENTS_NV:
        return "GL_MAX_PROGRAM_RESULT_COMPONENTS_NV";
    case GL_STENCIL_TEST_TWO_SIDE_EXT:
        return "GL_STENCIL_TEST_TWO_SIDE_EXT";
    case GL_ACTIVE_STENCIL_FACE_EXT:
        return "GL_ACTIVE_STENCIL_FACE_EXT";
    case GL_MIRROR_CLAMP_TO_BORDER_EXT:
        return "GL_MIRROR_CLAMP_TO_BORDER_EXT";
    case GL_SAMPLES_PASSED:
        return "GL_SAMPLES_PASSED";
    case GL_GEOMETRY_VERTICES_OUT:
        return "GL_GEOMETRY_VERTICES_OUT";
    case GL_GEOMETRY_INPUT_TYPE:
        return "GL_GEOMETRY_INPUT_TYPE";
    case GL_GEOMETRY_OUTPUT_TYPE:
        return "GL_GEOMETRY_OUTPUT_TYPE";
    case GL_SAMPLER_BINDING:
        return "GL_SAMPLER_BINDING";
    case GL_CLAMP_VERTEX_COLOR:
        return "GL_CLAMP_VERTEX_COLOR";
    case GL_CLAMP_FRAGMENT_COLOR:
        return "GL_CLAMP_FRAGMENT_COLOR";
    case GL_CLAMP_READ_COLOR:
        return "GL_CLAMP_READ_COLOR";
    case GL_FIXED_ONLY:
        return "GL_FIXED_ONLY";
    case GL_TESS_CONTROL_PROGRAM_NV:
        return "GL_TESS_CONTROL_PROGRAM_NV";
    case GL_TESS_EVALUATION_PROGRAM_NV:
        return "GL_TESS_EVALUATION_PROGRAM_NV";
    case GL_FRAGMENT_SHADER_ATI:
        return "GL_FRAGMENT_SHADER_ATI";
    case GL_REG_0_ATI:
        return "GL_REG_0_ATI";
    case GL_REG_1_ATI:
        return "GL_REG_1_ATI";
    case GL_REG_2_ATI:
        return "GL_REG_2_ATI";
    case GL_REG_3_ATI:
        return "GL_REG_3_ATI";
    case GL_REG_4_ATI:
        return "GL_REG_4_ATI";
    case GL_REG_5_ATI:
        return "GL_REG_5_ATI";
    case GL_REG_6_ATI:
        return "GL_REG_6_ATI";
    case GL_REG_7_ATI:
        return "GL_REG_7_ATI";
    case GL_REG_8_ATI:
        return "GL_REG_8_ATI";
    case GL_REG_9_ATI:
        return "GL_REG_9_ATI";
    case GL_REG_10_ATI:
        return "GL_REG_10_ATI";
    case GL_REG_11_ATI:
        return "GL_REG_11_ATI";
    case GL_REG_12_ATI:
        return "GL_REG_12_ATI";
    case GL_REG_13_ATI:
        return "GL_REG_13_ATI";
    case GL_REG_14_ATI:
        return "GL_REG_14_ATI";
    case GL_REG_15_ATI:
        return "GL_REG_15_ATI";
    case GL_REG_16_ATI:
        return "GL_REG_16_ATI";
    case GL_REG_17_ATI:
        return "GL_REG_17_ATI";
    case GL_REG_18_ATI:
        return "GL_REG_18_ATI";
    case GL_REG_19_ATI:
        return "GL_REG_19_ATI";
    case GL_REG_20_ATI:
        return "GL_REG_20_ATI";
    case GL_REG_21_ATI:
        return "GL_REG_21_ATI";
    case GL_REG_22_ATI:
        return "GL_REG_22_ATI";
    case GL_REG_23_ATI:
        return "GL_REG_23_ATI";
    case GL_REG_24_ATI:
        return "GL_REG_24_ATI";
    case GL_REG_25_ATI:
        return "GL_REG_25_ATI";
    case GL_REG_26_ATI:
        return "GL_REG_26_ATI";
    case GL_REG_27_ATI:
        return "GL_REG_27_ATI";
    case GL_REG_28_ATI:
        return "GL_REG_28_ATI";
    case GL_REG_29_ATI:
        return "GL_REG_29_ATI";
    case GL_REG_30_ATI:
        return "GL_REG_30_ATI";
    case GL_REG_31_ATI:
        return "GL_REG_31_ATI";
    case GL_CON_0_ATI:
        return "GL_CON_0_ATI";
    case GL_CON_1_ATI:
        return "GL_CON_1_ATI";
    case GL_CON_2_ATI:
        return "GL_CON_2_ATI";
    case GL_CON_3_ATI:
        return "GL_CON_3_ATI";
    case GL_CON_4_ATI:
        return "GL_CON_4_ATI";
    case GL_CON_5_ATI:
        return "GL_CON_5_ATI";
    case GL_CON_6_ATI:
        return "GL_CON_6_ATI";
    case GL_CON_7_ATI:
        return "GL_CON_7_ATI";
    case GL_CON_8_ATI:
        return "GL_CON_8_ATI";
    case GL_CON_9_ATI:
        return "GL_CON_9_ATI";
    case GL_CON_10_ATI:
        return "GL_CON_10_ATI";
    case GL_CON_11_ATI:
        return "GL_CON_11_ATI";
    case GL_CON_12_ATI:
        return "GL_CON_12_ATI";
    case GL_CON_13_ATI:
        return "GL_CON_13_ATI";
    case GL_CON_14_ATI:
        return "GL_CON_14_ATI";
    case GL_CON_15_ATI:
        return "GL_CON_15_ATI";
    case GL_CON_16_ATI:
        return "GL_CON_16_ATI";
    case GL_CON_17_ATI:
        return "GL_CON_17_ATI";
    case GL_CON_18_ATI:
        return "GL_CON_18_ATI";
    case GL_CON_19_ATI:
        return "GL_CON_19_ATI";
    case GL_CON_20_ATI:
        return "GL_CON_20_ATI";
    case GL_CON_21_ATI:
        return "GL_CON_21_ATI";
    case GL_CON_22_ATI:
        return "GL_CON_22_ATI";
    case GL_CON_23_ATI:
        return "GL_CON_23_ATI";
    case GL_CON_24_ATI:
        return "GL_CON_24_ATI";
    case GL_CON_25_ATI:
        return "GL_CON_25_ATI";
    case GL_CON_26_ATI:
        return "GL_CON_26_ATI";
    case GL_CON_27_ATI:
        return "GL_CON_27_ATI";
    case GL_CON_28_ATI:
        return "GL_CON_28_ATI";
    case GL_CON_29_ATI:
        return "GL_CON_29_ATI";
    case GL_CON_30_ATI:
        return "GL_CON_30_ATI";
    case GL_CON_31_ATI:
        return "GL_CON_31_ATI";
    case GL_MOV_ATI:
        return "GL_MOV_ATI";
    case GL_ADD_ATI:
        return "GL_ADD_ATI";
    case GL_MUL_ATI:
        return "GL_MUL_ATI";
    case GL_SUB_ATI:
        return "GL_SUB_ATI";
    case GL_DOT3_ATI:
        return "GL_DOT3_ATI";
    case GL_DOT4_ATI:
        return "GL_DOT4_ATI";
    case GL_MAD_ATI:
        return "GL_MAD_ATI";
    case GL_LERP_ATI:
        return "GL_LERP_ATI";
    case GL_CND_ATI:
        return "GL_CND_ATI";
    case GL_CND0_ATI:
        return "GL_CND0_ATI";
    case GL_DOT2_ADD_ATI:
        return "GL_DOT2_ADD_ATI";
    case GL_SECONDARY_INTERPOLATOR_ATI:
        return "GL_SECONDARY_INTERPOLATOR_ATI";
    case GL_NUM_FRAGMENT_REGISTERS_ATI:
        return "GL_NUM_FRAGMENT_REGISTERS_ATI";
    case GL_NUM_FRAGMENT_CONSTANTS_ATI:
        return "GL_NUM_FRAGMENT_CONSTANTS_ATI";
    case GL_NUM_PASSES_ATI:
        return "GL_NUM_PASSES_ATI";
    case GL_NUM_INSTRUCTIONS_PER_PASS_ATI:
        return "GL_NUM_INSTRUCTIONS_PER_PASS_ATI";
    case GL_NUM_INSTRUCTIONS_TOTAL_ATI:
        return "GL_NUM_INSTRUCTIONS_TOTAL_ATI";
    case GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI:
        return "GL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI";
    case GL_NUM_LOOPBACK_COMPONENTS_ATI:
        return "GL_NUM_LOOPBACK_COMPONENTS_ATI";
    case GL_COLOR_ALPHA_PAIRING_ATI:
        return "GL_COLOR_ALPHA_PAIRING_ATI";
    case GL_SWIZZLE_STR_ATI:
        return "GL_SWIZZLE_STR_ATI";
    case GL_SWIZZLE_STQ_ATI:
        return "GL_SWIZZLE_STQ_ATI";
    case GL_SWIZZLE_STR_DR_ATI:
        return "GL_SWIZZLE_STR_DR_ATI";
    case GL_SWIZZLE_STQ_DQ_ATI:
        return "GL_SWIZZLE_STQ_DQ_ATI";
    case GL_SWIZZLE_STRQ_ATI:
        return "GL_SWIZZLE_STRQ_ATI";
    case GL_SWIZZLE_STRQ_DQ_ATI:
        return "GL_SWIZZLE_STRQ_DQ_ATI";
    case GL_INTERLACE_OML:
        return "GL_INTERLACE_OML";
    case GL_INTERLACE_READ_OML:
        return "GL_INTERLACE_READ_OML";
    case GL_FORMAT_SUBSAMPLE_24_24_OML:
        return "GL_FORMAT_SUBSAMPLE_24_24_OML";
    case GL_FORMAT_SUBSAMPLE_244_244_OML:
        return "GL_FORMAT_SUBSAMPLE_244_244_OML";
    case GL_PACK_RESAMPLE_OML:
        return "GL_PACK_RESAMPLE_OML";
    case GL_UNPACK_RESAMPLE_OML:
        return "GL_UNPACK_RESAMPLE_OML";
    case GL_RESAMPLE_REPLICATE_OML:
        return "GL_RESAMPLE_REPLICATE_OML";
    case GL_RESAMPLE_ZERO_FILL_OML:
        return "GL_RESAMPLE_ZERO_FILL_OML";
    case GL_RESAMPLE_AVERAGE_OML:
        return "GL_RESAMPLE_AVERAGE_OML";
    case GL_RESAMPLE_DECIMATE_OML:
        return "GL_RESAMPLE_DECIMATE_OML";
    case GL_POINT_SIZE_ARRAY_TYPE_OES:
        return "GL_POINT_SIZE_ARRAY_TYPE_OES";
    case GL_POINT_SIZE_ARRAY_STRIDE_OES:
        return "GL_POINT_SIZE_ARRAY_STRIDE_OES";
    case GL_POINT_SIZE_ARRAY_POINTER_OES:
        return "GL_POINT_SIZE_ARRAY_POINTER_OES";
    case GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES:
        return "GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES";
    case GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES:
        return "GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES";
    case GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES:
        return "GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES";
    case GL_VERTEX_ATTRIB_MAP1_APPLE:
        return "GL_VERTEX_ATTRIB_MAP1_APPLE";
    case GL_VERTEX_ATTRIB_MAP2_APPLE:
        return "GL_VERTEX_ATTRIB_MAP2_APPLE";
    case GL_VERTEX_ATTRIB_MAP1_SIZE_APPLE:
        return "GL_VERTEX_ATTRIB_MAP1_SIZE_APPLE";
    case GL_VERTEX_ATTRIB_MAP1_COEFF_APPLE:
        return "GL_VERTEX_ATTRIB_MAP1_COEFF_APPLE";
    case GL_VERTEX_ATTRIB_MAP1_ORDER_APPLE:
        return "GL_VERTEX_ATTRIB_MAP1_ORDER_APPLE";
    case GL_VERTEX_ATTRIB_MAP1_DOMAIN_APPLE:
        return "GL_VERTEX_ATTRIB_MAP1_DOMAIN_APPLE";
    case GL_VERTEX_ATTRIB_MAP2_SIZE_APPLE:
        return "GL_VERTEX_ATTRIB_MAP2_SIZE_APPLE";
    case GL_VERTEX_ATTRIB_MAP2_COEFF_APPLE:
        return "GL_VERTEX_ATTRIB_MAP2_COEFF_APPLE";
    case GL_VERTEX_ATTRIB_MAP2_ORDER_APPLE:
        return "GL_VERTEX_ATTRIB_MAP2_ORDER_APPLE";
    case GL_VERTEX_ATTRIB_MAP2_DOMAIN_APPLE:
        return "GL_VERTEX_ATTRIB_MAP2_DOMAIN_APPLE";
    case GL_DRAW_PIXELS_APPLE:
        return "GL_DRAW_PIXELS_APPLE";
    case GL_FENCE_APPLE:
        return "GL_FENCE_APPLE";
    case GL_ELEMENT_ARRAY_APPLE:
        return "GL_ELEMENT_ARRAY_APPLE";
    case GL_ELEMENT_ARRAY_TYPE_APPLE:
        return "GL_ELEMENT_ARRAY_TYPE_APPLE";
    case GL_ELEMENT_ARRAY_POINTER_APPLE:
        return "GL_ELEMENT_ARRAY_POINTER_APPLE";
    case GL_COLOR_FLOAT_APPLE:
        return "GL_COLOR_FLOAT_APPLE";
    case GL_UNIFORM_BUFFER:
        return "GL_UNIFORM_BUFFER";
    case GL_BUFFER_SERIALIZED_MODIFY_APPLE:
        return "GL_BUFFER_SERIALIZED_MODIFY_APPLE";
    case GL_BUFFER_FLUSHING_UNMAP_APPLE:
        return "GL_BUFFER_FLUSHING_UNMAP_APPLE";
    case GL_AUX_DEPTH_STENCIL_APPLE:
        return "GL_AUX_DEPTH_STENCIL_APPLE";
    case GL_PACK_ROW_BYTES_APPLE:
        return "GL_PACK_ROW_BYTES_APPLE";
    case GL_UNPACK_ROW_BYTES_APPLE:
        return "GL_UNPACK_ROW_BYTES_APPLE";
    case GL_RELEASED_APPLE:
        return "GL_RELEASED_APPLE";
    case GL_VOLATILE_APPLE:
        return "GL_VOLATILE_APPLE";
    case GL_RETAINED_APPLE:
        return "GL_RETAINED_APPLE";
    case GL_UNDEFINED_APPLE:
        return "GL_UNDEFINED_APPLE";
    case GL_PURGEABLE_APPLE:
        return "GL_PURGEABLE_APPLE";
    case GL_RGB_422_APPLE:
        return "GL_RGB_422_APPLE";
    case GL_UNIFORM_BUFFER_BINDING:
        return "GL_UNIFORM_BUFFER_BINDING";
    case GL_UNIFORM_BUFFER_START:
        return "GL_UNIFORM_BUFFER_START";
    case GL_UNIFORM_BUFFER_SIZE:
        return "GL_UNIFORM_BUFFER_SIZE";
    case GL_MAX_VERTEX_UNIFORM_BLOCKS:
        return "GL_MAX_VERTEX_UNIFORM_BLOCKS";
    case GL_MAX_GEOMETRY_UNIFORM_BLOCKS:
        return "GL_MAX_GEOMETRY_UNIFORM_BLOCKS";
    case GL_MAX_FRAGMENT_UNIFORM_BLOCKS:
        return "GL_MAX_FRAGMENT_UNIFORM_BLOCKS";
    case GL_MAX_COMBINED_UNIFORM_BLOCKS:
        return "GL_MAX_COMBINED_UNIFORM_BLOCKS";
    case GL_MAX_UNIFORM_BUFFER_BINDINGS:
        return "GL_MAX_UNIFORM_BUFFER_BINDINGS";
    case GL_MAX_UNIFORM_BLOCK_SIZE:
        return "GL_MAX_UNIFORM_BLOCK_SIZE";
    case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS";
    case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS";
    case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS";
    case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT:
        return "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT";
    case GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH:
        return "GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH";
    case GL_ACTIVE_UNIFORM_BLOCKS:
        return "GL_ACTIVE_UNIFORM_BLOCKS";
    case GL_UNIFORM_TYPE:
        return "GL_UNIFORM_TYPE";
    case GL_UNIFORM_SIZE:
        return "GL_UNIFORM_SIZE";
    case GL_UNIFORM_NAME_LENGTH:
        return "GL_UNIFORM_NAME_LENGTH";
    case GL_UNIFORM_BLOCK_INDEX:
        return "GL_UNIFORM_BLOCK_INDEX";
    case GL_UNIFORM_OFFSET:
        return "GL_UNIFORM_OFFSET";
    case GL_UNIFORM_ARRAY_STRIDE:
        return "GL_UNIFORM_ARRAY_STRIDE";
    case GL_UNIFORM_MATRIX_STRIDE:
        return "GL_UNIFORM_MATRIX_STRIDE";
    case GL_UNIFORM_IS_ROW_MAJOR:
        return "GL_UNIFORM_IS_ROW_MAJOR";
    case GL_UNIFORM_BLOCK_BINDING:
        return "GL_UNIFORM_BLOCK_BINDING";
    case GL_UNIFORM_BLOCK_DATA_SIZE:
        return "GL_UNIFORM_BLOCK_DATA_SIZE";
    case GL_UNIFORM_BLOCK_NAME_LENGTH:
        return "GL_UNIFORM_BLOCK_NAME_LENGTH";
    case GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS:
        return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS";
    case GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES:
        return "GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER";
    case GL_TEXTURE_SRGB_DECODE_EXT:
        return "GL_TEXTURE_SRGB_DECODE_EXT";
    case GL_DECODE_EXT:
        return "GL_DECODE_EXT";
    case GL_SKIP_DECODE_EXT:
        return "GL_SKIP_DECODE_EXT";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_PROGRAM_OBJECT_ARB:
        return "GL_PROGRAM_OBJECT_ARB";
    case GL_SHADER_OBJECT_ARB:
        return "GL_SHADER_OBJECT_ARB";
    case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS:
        return "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS";
    case GL_MAX_VERTEX_UNIFORM_COMPONENTS:
        return "GL_MAX_VERTEX_UNIFORM_COMPONENTS";
    case GL_MAX_VARYING_COMPONENTS:
        return "GL_MAX_VARYING_COMPONENTS";
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS";
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS";
    case GL_OBJECT_TYPE_ARB:
        return "GL_OBJECT_TYPE_ARB";
    case GL_SHADER_TYPE:
        return "GL_SHADER_TYPE";
    case GL_FLOAT_VEC2:
        return "GL_FLOAT_VEC2";
    case GL_FLOAT_VEC3:
        return "GL_FLOAT_VEC3";
    case GL_FLOAT_VEC4:
        return "GL_FLOAT_VEC4";
    case GL_INT_VEC2:
        return "GL_INT_VEC2";
    case GL_INT_VEC3:
        return "GL_INT_VEC3";
    case GL_INT_VEC4:
        return "GL_INT_VEC4";
    case GL_BOOL:
        return "GL_BOOL";
    case GL_BOOL_VEC2:
        return "GL_BOOL_VEC2";
    case GL_BOOL_VEC3:
        return "GL_BOOL_VEC3";
    case GL_BOOL_VEC4:
        return "GL_BOOL_VEC4";
    case GL_FLOAT_MAT2:
        return "GL_FLOAT_MAT2";
    case GL_FLOAT_MAT3:
        return "GL_FLOAT_MAT3";
    case GL_FLOAT_MAT4:
        return "GL_FLOAT_MAT4";
    case GL_SAMPLER_1D:
        return "GL_SAMPLER_1D";
    case GL_SAMPLER_2D:
        return "GL_SAMPLER_2D";
    case GL_SAMPLER_3D:
        return "GL_SAMPLER_3D";
    case GL_SAMPLER_CUBE:
        return "GL_SAMPLER_CUBE";
    case GL_SAMPLER_1D_SHADOW:
        return "GL_SAMPLER_1D_SHADOW";
    case GL_SAMPLER_2D_SHADOW:
        return "GL_SAMPLER_2D_SHADOW";
    case GL_SAMPLER_2D_RECT:
        return "GL_SAMPLER_2D_RECT";
    case GL_SAMPLER_2D_RECT_SHADOW:
        return "GL_SAMPLER_2D_RECT_SHADOW";
    case GL_FLOAT_MAT2x3:
        return "GL_FLOAT_MAT2x3";
    case GL_FLOAT_MAT2x4:
        return "GL_FLOAT_MAT2x4";
    case GL_FLOAT_MAT3x2:
        return "GL_FLOAT_MAT3x2";
    case GL_FLOAT_MAT3x4:
        return "GL_FLOAT_MAT3x4";
    case GL_FLOAT_MAT4x2:
        return "GL_FLOAT_MAT4x2";
    case GL_FLOAT_MAT4x3:
        return "GL_FLOAT_MAT4x3";
    case GL_DELETE_STATUS:
        return "GL_DELETE_STATUS";
    case GL_COMPILE_STATUS:
        return "GL_COMPILE_STATUS";
    case GL_LINK_STATUS:
        return "GL_LINK_STATUS";
    case GL_VALIDATE_STATUS:
        return "GL_VALIDATE_STATUS";
    case GL_INFO_LOG_LENGTH:
        return "GL_INFO_LOG_LENGTH";
    case GL_ATTACHED_SHADERS:
        return "GL_ATTACHED_SHADERS";
    case GL_ACTIVE_UNIFORMS:
        return "GL_ACTIVE_UNIFORMS";
    case GL_ACTIVE_UNIFORM_MAX_LENGTH:
        return "GL_ACTIVE_UNIFORM_MAX_LENGTH";
    case GL_SHADER_SOURCE_LENGTH:
        return "GL_SHADER_SOURCE_LENGTH";
    case GL_ACTIVE_ATTRIBUTES:
        return "GL_ACTIVE_ATTRIBUTES";
    case GL_ACTIVE_ATTRIBUTE_MAX_LENGTH:
        return "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH";
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:
        return "GL_FRAGMENT_SHADER_DERIVATIVE_HINT";
    case GL_SHADING_LANGUAGE_VERSION:
        return "GL_SHADING_LANGUAGE_VERSION";
    case GL_CURRENT_PROGRAM:
        return "GL_CURRENT_PROGRAM";
    case GL_PALETTE4_RGB8_OES:
        return "GL_PALETTE4_RGB8_OES";
    case GL_PALETTE4_RGBA8_OES:
        return "GL_PALETTE4_RGBA8_OES";
    case GL_PALETTE4_R5_G6_B5_OES:
        return "GL_PALETTE4_R5_G6_B5_OES";
    case GL_PALETTE4_RGBA4_OES:
        return "GL_PALETTE4_RGBA4_OES";
    case GL_PALETTE4_RGB5_A1_OES:
        return "GL_PALETTE4_RGB5_A1_OES";
    case GL_PALETTE8_RGB8_OES:
        return "GL_PALETTE8_RGB8_OES";
    case GL_PALETTE8_RGBA8_OES:
        return "GL_PALETTE8_RGBA8_OES";
    case GL_PALETTE8_R5_G6_B5_OES:
        return "GL_PALETTE8_R5_G6_B5_OES";
    case GL_PALETTE8_RGBA4_OES:
        return "GL_PALETTE8_RGBA4_OES";
    case GL_PALETTE8_RGB5_A1_OES:
        return "GL_PALETTE8_RGB5_A1_OES";
    case GL_IMPLEMENTATION_COLOR_READ_TYPE:
        return "GL_IMPLEMENTATION_COLOR_READ_TYPE";
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
        return "GL_IMPLEMENTATION_COLOR_READ_FORMAT";
    case GL_POINT_SIZE_ARRAY_OES:
        return "GL_POINT_SIZE_ARRAY_OES";
    case GL_TEXTURE_CROP_RECT_OES:
        return "GL_TEXTURE_CROP_RECT_OES";
    case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
        return "GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES";
    case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
        return "GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES";
    case GL_COUNTER_TYPE_AMD:
        return "GL_COUNTER_TYPE_AMD";
    case GL_COUNTER_RANGE_AMD:
        return "GL_COUNTER_RANGE_AMD";
    case GL_UNSIGNED_INT64_AMD:
        return "GL_UNSIGNED_INT64_AMD";
    case GL_PERCENTAGE_AMD:
        return "GL_PERCENTAGE_AMD";
    case GL_PERFMON_RESULT_AVAILABLE_AMD:
        return "GL_PERFMON_RESULT_AVAILABLE_AMD";
    case GL_PERFMON_RESULT_SIZE_AMD:
        return "GL_PERFMON_RESULT_SIZE_AMD";
    case GL_PERFMON_RESULT_AMD:
        return "GL_PERFMON_RESULT_AMD";
    case GL_TEXTURE_RED_TYPE:
        return "GL_TEXTURE_RED_TYPE";
    case GL_TEXTURE_GREEN_TYPE:
        return "GL_TEXTURE_GREEN_TYPE";
    case GL_TEXTURE_BLUE_TYPE:
        return "GL_TEXTURE_BLUE_TYPE";
    case GL_TEXTURE_ALPHA_TYPE:
        return "GL_TEXTURE_ALPHA_TYPE";
    case GL_TEXTURE_LUMINANCE_TYPE:
        return "GL_TEXTURE_LUMINANCE_TYPE";
    case GL_TEXTURE_INTENSITY_TYPE:
        return "GL_TEXTURE_INTENSITY_TYPE";
    case GL_TEXTURE_DEPTH_TYPE:
        return "GL_TEXTURE_DEPTH_TYPE";
    case GL_UNSIGNED_NORMALIZED:
        return "GL_UNSIGNED_NORMALIZED";
    case GL_TEXTURE_1D_ARRAY:
        return "GL_TEXTURE_1D_ARRAY";
    case GL_PROXY_TEXTURE_1D_ARRAY:
        return "GL_PROXY_TEXTURE_1D_ARRAY";
    case GL_TEXTURE_2D_ARRAY:
        return "GL_TEXTURE_2D_ARRAY";
    case GL_PROXY_TEXTURE_2D_ARRAY:
        return "GL_PROXY_TEXTURE_2D_ARRAY";
    case GL_TEXTURE_BINDING_1D_ARRAY:
        return "GL_TEXTURE_BINDING_1D_ARRAY";
    case GL_TEXTURE_BINDING_2D_ARRAY:
        return "GL_TEXTURE_BINDING_2D_ARRAY";
    case GL_GEOMETRY_PROGRAM_NV:
        return "GL_GEOMETRY_PROGRAM_NV";
    case GL_MAX_PROGRAM_OUTPUT_VERTICES_NV:
        return "GL_MAX_PROGRAM_OUTPUT_VERTICES_NV";
    case GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV:
        return "GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV";
    case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS";
    case GL_TEXTURE_BUFFER:
        return "GL_TEXTURE_BUFFER";
    case GL_MAX_TEXTURE_BUFFER_SIZE:
        return "GL_MAX_TEXTURE_BUFFER_SIZE";
    case GL_TEXTURE_BINDING_BUFFER:
        return "GL_TEXTURE_BINDING_BUFFER";
    case GL_TEXTURE_BUFFER_DATA_STORE_BINDING:
        return "GL_TEXTURE_BUFFER_DATA_STORE_BINDING";
    case GL_TEXTURE_BUFFER_FORMAT:
        return "GL_TEXTURE_BUFFER_FORMAT";
    case GL_ANY_SAMPLES_PASSED:
        return "GL_ANY_SAMPLES_PASSED";
    case GL_SAMPLE_SHADING:
        return "GL_SAMPLE_SHADING";
    case GL_MIN_SAMPLE_SHADING_VALUE:
        return "GL_MIN_SAMPLE_SHADING_VALUE";
    case GL_R11F_G11F_B10F:
        return "GL_R11F_G11F_B10F";
    case GL_UNSIGNED_INT_10F_11F_11F_REV:
        return "GL_UNSIGNED_INT_10F_11F_11F_REV";
    case GL_RGBA_SIGNED_COMPONENTS_EXT:
        return "GL_RGBA_SIGNED_COMPONENTS_EXT";
    case GL_RGB9_E5:
        return "GL_RGB9_E5";
    case GL_UNSIGNED_INT_5_9_9_9_REV:
        return "GL_UNSIGNED_INT_5_9_9_9_REV";
    case GL_TEXTURE_SHARED_SIZE:
        return "GL_TEXTURE_SHARED_SIZE";
    case GL_SRGB:
        return "GL_SRGB";
    case GL_SRGB8:
        return "GL_SRGB8";
    case GL_SRGB_ALPHA:
        return "GL_SRGB_ALPHA";
    case GL_SRGB8_ALPHA8:
        return "GL_SRGB8_ALPHA8";
    case GL_SLUMINANCE_ALPHA:
        return "GL_SLUMINANCE_ALPHA";
    case GL_SLUMINANCE8_ALPHA8:
        return "GL_SLUMINANCE8_ALPHA8";
    case GL_SLUMINANCE:
        return "GL_SLUMINANCE";
    case GL_SLUMINANCE8:
        return "GL_SLUMINANCE8";
    case GL_COMPRESSED_SRGB:
        return "GL_COMPRESSED_SRGB";
    case GL_COMPRESSED_SRGB_ALPHA:
        return "GL_COMPRESSED_SRGB_ALPHA";
    case GL_COMPRESSED_SLUMINANCE:
        return "GL_COMPRESSED_SLUMINANCE";
    case GL_COMPRESSED_SLUMINANCE_ALPHA:
        return "GL_COMPRESSED_SLUMINANCE_ALPHA";
    case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_SRGB_S3TC_DXT1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT";
    case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
        return "GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT";
    case GL_COMPRESSED_LUMINANCE_LATC1_EXT:
        return "GL_COMPRESSED_LUMINANCE_LATC1_EXT";
    case GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT:
        return "GL_COMPRESSED_SIGNED_LUMINANCE_LATC1_EXT";
    case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
        return "GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT";
    case GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT:
        return "GL_COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2_EXT";
    case GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV:
        return "GL_TESS_CONTROL_PROGRAM_PARAMETER_BUFFER_NV";
    case GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV:
        return "GL_TESS_EVALUATION_PROGRAM_PARAMETER_BUFFER_NV";
    case GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH:
        return "GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH";
    case GL_BACK_PRIMARY_COLOR_NV:
        return "GL_BACK_PRIMARY_COLOR_NV";
    case GL_BACK_SECONDARY_COLOR_NV:
        return "GL_BACK_SECONDARY_COLOR_NV";
    case GL_TEXTURE_COORD_NV:
        return "GL_TEXTURE_COORD_NV";
    case GL_CLIP_DISTANCE_NV:
        return "GL_CLIP_DISTANCE_NV";
    case GL_VERTEX_ID_NV:
        return "GL_VERTEX_ID_NV";
    case GL_PRIMITIVE_ID_NV:
        return "GL_PRIMITIVE_ID_NV";
    case GL_GENERIC_ATTRIB_NV:
        return "GL_GENERIC_ATTRIB_NV";
    case GL_TRANSFORM_FEEDBACK_ATTRIBS_NV:
        return "GL_TRANSFORM_FEEDBACK_ATTRIBS_NV";
    case GL_TRANSFORM_FEEDBACK_BUFFER_MODE:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_MODE";
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS:
        return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS";
    case GL_ACTIVE_VARYINGS_NV:
        return "GL_ACTIVE_VARYINGS_NV";
    case GL_ACTIVE_VARYING_MAX_LENGTH_NV:
        return "GL_ACTIVE_VARYING_MAX_LENGTH_NV";
    case GL_TRANSFORM_FEEDBACK_VARYINGS:
        return "GL_TRANSFORM_FEEDBACK_VARYINGS";
    case GL_TRANSFORM_FEEDBACK_BUFFER_START:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_START";
    case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_SIZE";
    case GL_TRANSFORM_FEEDBACK_RECORD_NV:
        return "GL_TRANSFORM_FEEDBACK_RECORD_NV";
    case GL_PRIMITIVES_GENERATED:
        return "GL_PRIMITIVES_GENERATED";
    case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
        return "GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN";
    case GL_RASTERIZER_DISCARD:
        return "GL_RASTERIZER_DISCARD";
    case GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS:
        return "GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS";
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS:
        return "GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS";
    case GL_INTERLEAVED_ATTRIBS:
        return "GL_INTERLEAVED_ATTRIBS";
    case GL_SEPARATE_ATTRIBS:
        return "GL_SEPARATE_ATTRIBS";
    case GL_TRANSFORM_FEEDBACK_BUFFER:
        return "GL_TRANSFORM_FEEDBACK_BUFFER";
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_BINDING";
    case GL_ATC_RGB_AMD:
        return "GL_ATC_RGB_AMD";
    case GL_ATC_RGBA_EXPLICIT_ALPHA_AMD:
        return "GL_ATC_RGBA_EXPLICIT_ALPHA_AMD";
    case GL_POINT_SPRITE_COORD_ORIGIN:
        return "GL_POINT_SPRITE_COORD_ORIGIN";
    case GL_LOWER_LEFT:
        return "GL_LOWER_LEFT";
    case GL_UPPER_LEFT:
        return "GL_UPPER_LEFT";
    case GL_STENCIL_BACK_REF:
        return "GL_STENCIL_BACK_REF";
    case GL_STENCIL_BACK_VALUE_MASK:
        return "GL_STENCIL_BACK_VALUE_MASK";
    case GL_STENCIL_BACK_WRITEMASK:
        return "GL_STENCIL_BACK_WRITEMASK";
    case GL_DRAW_FRAMEBUFFER_BINDING:
        return "GL_DRAW_FRAMEBUFFER_BINDING";
    case GL_RENDERBUFFER_BINDING:
        return "GL_RENDERBUFFER_BINDING";
    case GL_READ_FRAMEBUFFER:
        return "GL_READ_FRAMEBUFFER";
    case GL_DRAW_FRAMEBUFFER:
        return "GL_DRAW_FRAMEBUFFER";
    case GL_READ_FRAMEBUFFER_BINDING:
        return "GL_READ_FRAMEBUFFER_BINDING";
    case GL_RENDERBUFFER_SAMPLES:
        return "GL_RENDERBUFFER_SAMPLES";
    case GL_DEPTH_COMPONENT32F:
        return "GL_DEPTH_COMPONENT32F";
    case GL_DEPTH32F_STENCIL8:
        return "GL_DEPTH32F_STENCIL8";
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
        return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE";
    case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME:
        return "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER";
    case GL_FRAMEBUFFER_COMPLETE:
        return "GL_FRAMEBUFFER_COMPLETE";
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        return "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT";
    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        return "GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT";
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
    case GL_FRAMEBUFFER_UNSUPPORTED:
        return "GL_FRAMEBUFFER_UNSUPPORTED";
    case GL_MAX_COLOR_ATTACHMENTS:
        return "GL_MAX_COLOR_ATTACHMENTS";
    case GL_COLOR_ATTACHMENT0:
        return "GL_COLOR_ATTACHMENT0";
    case GL_COLOR_ATTACHMENT1:
        return "GL_COLOR_ATTACHMENT1";
    case GL_COLOR_ATTACHMENT2:
        return "GL_COLOR_ATTACHMENT2";
    case GL_COLOR_ATTACHMENT3:
        return "GL_COLOR_ATTACHMENT3";
    case GL_COLOR_ATTACHMENT4:
        return "GL_COLOR_ATTACHMENT4";
    case GL_COLOR_ATTACHMENT5:
        return "GL_COLOR_ATTACHMENT5";
    case GL_COLOR_ATTACHMENT6:
        return "GL_COLOR_ATTACHMENT6";
    case GL_COLOR_ATTACHMENT7:
        return "GL_COLOR_ATTACHMENT7";
    case GL_COLOR_ATTACHMENT8:
        return "GL_COLOR_ATTACHMENT8";
    case GL_COLOR_ATTACHMENT9:
        return "GL_COLOR_ATTACHMENT9";
    case GL_COLOR_ATTACHMENT10:
        return "GL_COLOR_ATTACHMENT10";
    case GL_COLOR_ATTACHMENT11:
        return "GL_COLOR_ATTACHMENT11";
    case GL_COLOR_ATTACHMENT12:
        return "GL_COLOR_ATTACHMENT12";
    case GL_COLOR_ATTACHMENT13:
        return "GL_COLOR_ATTACHMENT13";
    case GL_COLOR_ATTACHMENT14:
        return "GL_COLOR_ATTACHMENT14";
    case GL_COLOR_ATTACHMENT15:
        return "GL_COLOR_ATTACHMENT15";
    case GL_DEPTH_ATTACHMENT:
        return "GL_DEPTH_ATTACHMENT";
    case GL_STENCIL_ATTACHMENT:
        return "GL_STENCIL_ATTACHMENT";
    case GL_FRAMEBUFFER:
        return "GL_FRAMEBUFFER";
    case GL_RENDERBUFFER:
        return "GL_RENDERBUFFER";
    case GL_RENDERBUFFER_WIDTH:
        return "GL_RENDERBUFFER_WIDTH";
    case GL_RENDERBUFFER_HEIGHT:
        return "GL_RENDERBUFFER_HEIGHT";
    case GL_RENDERBUFFER_INTERNAL_FORMAT:
        return "GL_RENDERBUFFER_INTERNAL_FORMAT";
    case GL_STENCIL_INDEX1:
        return "GL_STENCIL_INDEX1";
    case GL_STENCIL_INDEX4:
        return "GL_STENCIL_INDEX4";
    case GL_STENCIL_INDEX8:
        return "GL_STENCIL_INDEX8";
    case GL_STENCIL_INDEX16:
        return "GL_STENCIL_INDEX16";
    case GL_RENDERBUFFER_RED_SIZE:
        return "GL_RENDERBUFFER_RED_SIZE";
    case GL_RENDERBUFFER_GREEN_SIZE:
        return "GL_RENDERBUFFER_GREEN_SIZE";
    case GL_RENDERBUFFER_BLUE_SIZE:
        return "GL_RENDERBUFFER_BLUE_SIZE";
    case GL_RENDERBUFFER_ALPHA_SIZE:
        return "GL_RENDERBUFFER_ALPHA_SIZE";
    case GL_RENDERBUFFER_DEPTH_SIZE:
        return "GL_RENDERBUFFER_DEPTH_SIZE";
    case GL_RENDERBUFFER_STENCIL_SIZE:
        return "GL_RENDERBUFFER_STENCIL_SIZE";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
    case GL_MAX_SAMPLES:
        return "GL_MAX_SAMPLES";
    case GL_TEXTURE_GEN_STR_OES:
        return "GL_TEXTURE_GEN_STR_OES";
    case GL_HALF_FLOAT_OES:
        return "GL_HALF_FLOAT_OES";
    case GL_RGB565_OES:
        return "GL_RGB565_OES";
    case GL_ETC1_RGB8_OES:
        return "GL_ETC1_RGB8_OES";
    case GL_TEXTURE_EXTERNAL_OES:
        return "GL_TEXTURE_EXTERNAL_OES";
    case GL_SAMPLER_EXTERNAL_OES:
        return "GL_SAMPLER_EXTERNAL_OES";
    case GL_TEXTURE_BINDING_EXTERNAL_OES:
        return "GL_TEXTURE_BINDING_EXTERNAL_OES";
    case GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES:
        return "GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES";
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        return "GL_PRIMITIVE_RESTART_FIXED_INDEX";
    case GL_ANY_SAMPLES_PASSED_CONSERVATIVE:
        return "GL_ANY_SAMPLES_PASSED_CONSERVATIVE";
    case GL_MAX_ELEMENT_INDEX:
        return "GL_MAX_ELEMENT_INDEX";
    case GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT:
        return "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT";
    case GL_RGBA32UI:
        return "GL_RGBA32UI";
    case GL_RGB32UI:
        return "GL_RGB32UI";
    case GL_ALPHA32UI_EXT:
        return "GL_ALPHA32UI_EXT";
    case GL_INTENSITY32UI_EXT:
        return "GL_INTENSITY32UI_EXT";
    case GL_LUMINANCE32UI_EXT:
        return "GL_LUMINANCE32UI_EXT";
    case GL_LUMINANCE_ALPHA32UI_EXT:
        return "GL_LUMINANCE_ALPHA32UI_EXT";
    case GL_RGBA16UI:
        return "GL_RGBA16UI";
    case GL_RGB16UI:
        return "GL_RGB16UI";
    case GL_ALPHA16UI_EXT:
        return "GL_ALPHA16UI_EXT";
    case GL_INTENSITY16UI_EXT:
        return "GL_INTENSITY16UI_EXT";
    case GL_LUMINANCE16UI_EXT:
        return "GL_LUMINANCE16UI_EXT";
    case GL_LUMINANCE_ALPHA16UI_EXT:
        return "GL_LUMINANCE_ALPHA16UI_EXT";
    case GL_RGBA8UI:
        return "GL_RGBA8UI";
    case GL_RGB8UI:
        return "GL_RGB8UI";
    case GL_ALPHA8UI_EXT:
        return "GL_ALPHA8UI_EXT";
    case GL_INTENSITY8UI_EXT:
        return "GL_INTENSITY8UI_EXT";
    case GL_LUMINANCE8UI_EXT:
        return "GL_LUMINANCE8UI_EXT";
    case GL_LUMINANCE_ALPHA8UI_EXT:
        return "GL_LUMINANCE_ALPHA8UI_EXT";
    case GL_RGBA32I:
        return "GL_RGBA32I";
    case GL_RGB32I:
        return "GL_RGB32I";
    case GL_ALPHA32I_EXT:
        return "GL_ALPHA32I_EXT";
    case GL_INTENSITY32I_EXT:
        return "GL_INTENSITY32I_EXT";
    case GL_LUMINANCE32I_EXT:
        return "GL_LUMINANCE32I_EXT";
    case GL_LUMINANCE_ALPHA32I_EXT:
        return "GL_LUMINANCE_ALPHA32I_EXT";
    case GL_RGBA16I:
        return "GL_RGBA16I";
    case GL_RGB16I:
        return "GL_RGB16I";
    case GL_ALPHA16I_EXT:
        return "GL_ALPHA16I_EXT";
    case GL_INTENSITY16I_EXT:
        return "GL_INTENSITY16I_EXT";
    case GL_LUMINANCE16I_EXT:
        return "GL_LUMINANCE16I_EXT";
    case GL_LUMINANCE_ALPHA16I_EXT:
        return "GL_LUMINANCE_ALPHA16I_EXT";
    case GL_RGBA8I:
        return "GL_RGBA8I";
    case GL_RGB8I:
        return "GL_RGB8I";
    case GL_ALPHA8I_EXT:
        return "GL_ALPHA8I_EXT";
    case GL_INTENSITY8I_EXT:
        return "GL_INTENSITY8I_EXT";
    case GL_LUMINANCE8I_EXT:
        return "GL_LUMINANCE8I_EXT";
    case GL_LUMINANCE_ALPHA8I_EXT:
        return "GL_LUMINANCE_ALPHA8I_EXT";
    case GL_RED_INTEGER:
        return "GL_RED_INTEGER";
    case GL_GREEN_INTEGER:
        return "GL_GREEN_INTEGER";
    case GL_BLUE_INTEGER:
        return "GL_BLUE_INTEGER";
    case GL_ALPHA_INTEGER:
        return "GL_ALPHA_INTEGER";
    case GL_RGB_INTEGER:
        return "GL_RGB_INTEGER";
    case GL_RGBA_INTEGER:
        return "GL_RGBA_INTEGER";
    case GL_BGR_INTEGER:
        return "GL_BGR_INTEGER";
    case GL_BGRA_INTEGER:
        return "GL_BGRA_INTEGER";
    case GL_LUMINANCE_INTEGER_EXT:
        return "GL_LUMINANCE_INTEGER_EXT";
    case GL_LUMINANCE_ALPHA_INTEGER_EXT:
        return "GL_LUMINANCE_ALPHA_INTEGER_EXT";
    case GL_RGBA_INTEGER_MODE_EXT:
        return "GL_RGBA_INTEGER_MODE_EXT";
    case GL_INT_2_10_10_10_REV:
        return "GL_INT_2_10_10_10_REV";
    case GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV:
        return "GL_MAX_PROGRAM_PARAMETER_BUFFER_BINDINGS_NV";
    case GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV:
        return "GL_MAX_PROGRAM_PARAMETER_BUFFER_SIZE_NV";
    case GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV:
        return "GL_VERTEX_PROGRAM_PARAMETER_BUFFER_NV";
    case GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV:
        return "GL_GEOMETRY_PROGRAM_PARAMETER_BUFFER_NV";
    case GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV:
        return "GL_FRAGMENT_PROGRAM_PARAMETER_BUFFER_NV";
    case GL_MAX_PROGRAM_GENERIC_ATTRIBS_NV:
        return "GL_MAX_PROGRAM_GENERIC_ATTRIBS_NV";
    case GL_MAX_PROGRAM_GENERIC_RESULTS_NV:
        return "GL_MAX_PROGRAM_GENERIC_RESULTS_NV";
    case GL_FRAMEBUFFER_ATTACHMENT_LAYERED:
        return "GL_FRAMEBUFFER_ATTACHMENT_LAYERED";
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB:
        return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_COUNT_ARB";
    case GL_LAYER_NV:
        return "GL_LAYER_NV";
    case GL_DEPTH_COMPONENT32F_NV:
        return "GL_DEPTH_COMPONENT32F_NV";
    case GL_DEPTH32F_STENCIL8_NV:
        return "GL_DEPTH32F_STENCIL8_NV";
    case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
        return "GL_FLOAT_32_UNSIGNED_INT_24_8_REV";
    case GL_SHADER_INCLUDE_ARB:
        return "GL_SHADER_INCLUDE_ARB";
    case GL_DEPTH_BUFFER_FLOAT_MODE_NV:
        return "GL_DEPTH_BUFFER_FLOAT_MODE_NV";
    case GL_FRAMEBUFFER_SRGB:
        return "GL_FRAMEBUFFER_SRGB";
    case GL_FRAMEBUFFER_SRGB_CAPABLE_EXT:
        return "GL_FRAMEBUFFER_SRGB_CAPABLE_EXT";
    case GL_COMPRESSED_RED_RGTC1:
        return "GL_COMPRESSED_RED_RGTC1";
    case GL_COMPRESSED_SIGNED_RED_RGTC1:
        return "GL_COMPRESSED_SIGNED_RED_RGTC1";
    case GL_COMPRESSED_RG_RGTC2:
        return "GL_COMPRESSED_RG_RGTC2";
    case GL_COMPRESSED_SIGNED_RG_RGTC2:
        return "GL_COMPRESSED_SIGNED_RG_RGTC2";
    case GL_SAMPLER_1D_ARRAY:
        return "GL_SAMPLER_1D_ARRAY";
    case GL_SAMPLER_2D_ARRAY:
        return "GL_SAMPLER_2D_ARRAY";
    case GL_SAMPLER_BUFFER:
        return "GL_SAMPLER_BUFFER";
    case GL_SAMPLER_1D_ARRAY_SHADOW:
        return "GL_SAMPLER_1D_ARRAY_SHADOW";
    case GL_SAMPLER_2D_ARRAY_SHADOW:
        return "GL_SAMPLER_2D_ARRAY_SHADOW";
    case GL_SAMPLER_CUBE_SHADOW:
        return "GL_SAMPLER_CUBE_SHADOW";
    case GL_UNSIGNED_INT_VEC2:
        return "GL_UNSIGNED_INT_VEC2";
    case GL_UNSIGNED_INT_VEC3:
        return "GL_UNSIGNED_INT_VEC3";
    case GL_UNSIGNED_INT_VEC4:
        return "GL_UNSIGNED_INT_VEC4";
    case GL_INT_SAMPLER_1D:
        return "GL_INT_SAMPLER_1D";
    case GL_INT_SAMPLER_2D:
        return "GL_INT_SAMPLER_2D";
    case GL_INT_SAMPLER_3D:
        return "GL_INT_SAMPLER_3D";
    case GL_INT_SAMPLER_CUBE:
        return "GL_INT_SAMPLER_CUBE";
    case GL_INT_SAMPLER_2D_RECT:
        return "GL_INT_SAMPLER_2D_RECT";
    case GL_INT_SAMPLER_1D_ARRAY:
        return "GL_INT_SAMPLER_1D_ARRAY";
    case GL_INT_SAMPLER_2D_ARRAY:
        return "GL_INT_SAMPLER_2D_ARRAY";
    case GL_INT_SAMPLER_BUFFER:
        return "GL_INT_SAMPLER_BUFFER";
    case GL_UNSIGNED_INT_SAMPLER_1D:
        return "GL_UNSIGNED_INT_SAMPLER_1D";
    case GL_UNSIGNED_INT_SAMPLER_2D:
        return "GL_UNSIGNED_INT_SAMPLER_2D";
    case GL_UNSIGNED_INT_SAMPLER_3D:
        return "GL_UNSIGNED_INT_SAMPLER_3D";
    case GL_UNSIGNED_INT_SAMPLER_CUBE:
        return "GL_UNSIGNED_INT_SAMPLER_CUBE";
    case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
        return "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
    case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
        return "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
        return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_BUFFER:
        return "GL_UNSIGNED_INT_SAMPLER_BUFFER";
    case GL_GEOMETRY_SHADER:
        return "GL_GEOMETRY_SHADER";
    case GL_GEOMETRY_VERTICES_OUT_ARB:
        return "GL_GEOMETRY_VERTICES_OUT_ARB";
    case GL_GEOMETRY_INPUT_TYPE_ARB:
        return "GL_GEOMETRY_INPUT_TYPE_ARB";
    case GL_GEOMETRY_OUTPUT_TYPE_ARB:
        return "GL_GEOMETRY_OUTPUT_TYPE_ARB";
    case GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB:
        return "GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB";
    case GL_MAX_VERTEX_VARYING_COMPONENTS_ARB:
        return "GL_MAX_VERTEX_VARYING_COMPONENTS_ARB";
    case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS:
        return "GL_MAX_GEOMETRY_UNIFORM_COMPONENTS";
    case GL_MAX_GEOMETRY_OUTPUT_VERTICES:
        return "GL_MAX_GEOMETRY_OUTPUT_VERTICES";
    case GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS:
        return "GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS";
    case GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT:
        return "GL_MAX_VERTEX_BINDABLE_UNIFORMS_EXT";
    case GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT:
        return "GL_MAX_FRAGMENT_BINDABLE_UNIFORMS_EXT";
    case GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT:
        return "GL_MAX_GEOMETRY_BINDABLE_UNIFORMS_EXT";
    case GL_ACTIVE_SUBROUTINES:
        return "GL_ACTIVE_SUBROUTINES";
    case GL_ACTIVE_SUBROUTINE_UNIFORMS:
        return "GL_ACTIVE_SUBROUTINE_UNIFORMS";
    case GL_MAX_SUBROUTINES:
        return "GL_MAX_SUBROUTINES";
    case GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS:
        return "GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS";
    case GL_NAMED_STRING_LENGTH_ARB:
        return "GL_NAMED_STRING_LENGTH_ARB";
    case GL_NAMED_STRING_TYPE_ARB:
        return "GL_NAMED_STRING_TYPE_ARB";
    case GL_MAX_BINDABLE_UNIFORM_SIZE_EXT:
        return "GL_MAX_BINDABLE_UNIFORM_SIZE_EXT";
    case GL_UNIFORM_BUFFER_EXT:
        return "GL_UNIFORM_BUFFER_EXT";
    case GL_UNIFORM_BUFFER_BINDING_EXT:
        return "GL_UNIFORM_BUFFER_BINDING_EXT";
    case GL_LOW_FLOAT:
        return "GL_LOW_FLOAT";
    case GL_MEDIUM_FLOAT:
        return "GL_MEDIUM_FLOAT";
    case GL_HIGH_FLOAT:
        return "GL_HIGH_FLOAT";
    case GL_LOW_INT:
        return "GL_LOW_INT";
    case GL_MEDIUM_INT:
        return "GL_MEDIUM_INT";
    case GL_HIGH_INT:
        return "GL_HIGH_INT";
    case GL_NUM_SHADER_BINARY_FORMATS:
        return "GL_NUM_SHADER_BINARY_FORMATS";
    case GL_SHADER_COMPILER:
        return "GL_SHADER_COMPILER";
    case GL_MAX_VERTEX_UNIFORM_VECTORS:
        return "GL_MAX_VERTEX_UNIFORM_VECTORS";
    case GL_MAX_VARYING_VECTORS:
        return "GL_MAX_VARYING_VECTORS";
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
        return "GL_MAX_FRAGMENT_UNIFORM_VECTORS";
    case GL_RENDERBUFFER_COLOR_SAMPLES_NV:
        return "GL_RENDERBUFFER_COLOR_SAMPLES_NV";
    case GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV:
        return "GL_MAX_MULTISAMPLE_COVERAGE_MODES_NV";
    case GL_MULTISAMPLE_COVERAGE_MODES_NV:
        return "GL_MULTISAMPLE_COVERAGE_MODES_NV";
    case GL_QUERY_WAIT:
        return "GL_QUERY_WAIT";
    case GL_QUERY_NO_WAIT:
        return "GL_QUERY_NO_WAIT";
    case GL_QUERY_BY_REGION_WAIT:
        return "GL_QUERY_BY_REGION_WAIT";
    case GL_QUERY_BY_REGION_NO_WAIT:
        return "GL_QUERY_BY_REGION_NO_WAIT";
    case GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS";
    case GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS:
        return "GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS";
    case GL_COLOR_SAMPLES_NV:
        return "GL_COLOR_SAMPLES_NV";
    case GL_TRANSFORM_FEEDBACK:
        return "GL_TRANSFORM_FEEDBACK";
    case GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED";
    case GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE:
        return "GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE";
    case GL_TRANSFORM_FEEDBACK_BINDING:
        return "GL_TRANSFORM_FEEDBACK_BINDING";
    case GL_FRAME_NV:
        return "GL_FRAME_NV";
    case GL_FIELDS_NV:
        return "GL_FIELDS_NV";
    case GL_TIMESTAMP:
        return "GL_TIMESTAMP";
    case GL_NUM_FILL_STREAMS_NV:
        return "GL_NUM_FILL_STREAMS_NV";
    case GL_PRESENT_TIME_NV:
        return "GL_PRESENT_TIME_NV";
    case GL_PRESENT_DURATION_NV:
        return "GL_PRESENT_DURATION_NV";
    case GL_PROGRAM_MATRIX_EXT:
        return "GL_PROGRAM_MATRIX_EXT";
    case GL_TRANSPOSE_PROGRAM_MATRIX_EXT:
        return "GL_TRANSPOSE_PROGRAM_MATRIX_EXT";
    case GL_PROGRAM_MATRIX_STACK_DEPTH_EXT:
        return "GL_PROGRAM_MATRIX_STACK_DEPTH_EXT";
    case GL_TEXTURE_SWIZZLE_R:
        return "GL_TEXTURE_SWIZZLE_R";
    case GL_TEXTURE_SWIZZLE_G:
        return "GL_TEXTURE_SWIZZLE_G";
    case GL_TEXTURE_SWIZZLE_B:
        return "GL_TEXTURE_SWIZZLE_B";
    case GL_TEXTURE_SWIZZLE_A:
        return "GL_TEXTURE_SWIZZLE_A";
    case GL_TEXTURE_SWIZZLE_RGBA:
        return "GL_TEXTURE_SWIZZLE_RGBA";
    case GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS:
        return "GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS";
    case GL_ACTIVE_SUBROUTINE_MAX_LENGTH:
        return "GL_ACTIVE_SUBROUTINE_MAX_LENGTH";
    case GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH:
        return "GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH";
    case GL_NUM_COMPATIBLE_SUBROUTINES:
        return "GL_NUM_COMPATIBLE_SUBROUTINES";
    case GL_COMPATIBLE_SUBROUTINES:
        return "GL_COMPATIBLE_SUBROUTINES";
    case GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION:
        return "GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION";
    case GL_FIRST_VERTEX_CONVENTION:
        return "GL_FIRST_VERTEX_CONVENTION";
    case GL_LAST_VERTEX_CONVENTION:
        return "GL_LAST_VERTEX_CONVENTION";
    case GL_PROVOKING_VERTEX:
        return "GL_PROVOKING_VERTEX";
    case GL_SAMPLE_POSITION:
        return "GL_SAMPLE_POSITION";
    case GL_SAMPLE_MASK:
        return "GL_SAMPLE_MASK";
    case GL_SAMPLE_MASK_VALUE:
        return "GL_SAMPLE_MASK_VALUE";
    case GL_TEXTURE_BINDING_RENDERBUFFER_NV:
        return "GL_TEXTURE_BINDING_RENDERBUFFER_NV";
    case GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV:
        return "GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV";
    case GL_TEXTURE_RENDERBUFFER_NV:
        return "GL_TEXTURE_RENDERBUFFER_NV";
    case GL_SAMPLER_RENDERBUFFER_NV:
        return "GL_SAMPLER_RENDERBUFFER_NV";
    case GL_INT_SAMPLER_RENDERBUFFER_NV:
        return "GL_INT_SAMPLER_RENDERBUFFER_NV";
    case GL_UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV:
        return "GL_UNSIGNED_INT_SAMPLER_RENDERBUFFER_NV";
    case GL_MAX_SAMPLE_MASK_WORDS:
        return "GL_MAX_SAMPLE_MASK_WORDS";
    case GL_MAX_GEOMETRY_SHADER_INVOCATIONS:
        return "GL_MAX_GEOMETRY_SHADER_INVOCATIONS";
    case GL_MIN_FRAGMENT_INTERPOLATION_OFFSET:
        return "GL_MIN_FRAGMENT_INTERPOLATION_OFFSET";
    case GL_MAX_FRAGMENT_INTERPOLATION_OFFSET:
        return "GL_MAX_FRAGMENT_INTERPOLATION_OFFSET";
    case GL_FRAGMENT_INTERPOLATION_OFFSET_BITS:
        return "GL_FRAGMENT_INTERPOLATION_OFFSET_BITS";
    case GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET:
        return "GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET";
    case GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET:
        return "GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET";
    case GL_MAX_TRANSFORM_FEEDBACK_BUFFERS:
        return "GL_MAX_TRANSFORM_FEEDBACK_BUFFERS";
    case GL_MAX_VERTEX_STREAMS:
        return "GL_MAX_VERTEX_STREAMS";
    case GL_PATCH_VERTICES:
        return "GL_PATCH_VERTICES";
    case GL_PATCH_DEFAULT_INNER_LEVEL:
        return "GL_PATCH_DEFAULT_INNER_LEVEL";
    case GL_PATCH_DEFAULT_OUTER_LEVEL:
        return "GL_PATCH_DEFAULT_OUTER_LEVEL";
    case GL_TESS_CONTROL_OUTPUT_VERTICES:
        return "GL_TESS_CONTROL_OUTPUT_VERTICES";
    case GL_TESS_GEN_MODE:
        return "GL_TESS_GEN_MODE";
    case GL_TESS_GEN_SPACING:
        return "GL_TESS_GEN_SPACING";
    case GL_TESS_GEN_VERTEX_ORDER:
        return "GL_TESS_GEN_VERTEX_ORDER";
    case GL_TESS_GEN_POINT_MODE:
        return "GL_TESS_GEN_POINT_MODE";
    case GL_ISOLINES:
        return "GL_ISOLINES";
    case GL_FRACTIONAL_ODD:
        return "GL_FRACTIONAL_ODD";
    case GL_FRACTIONAL_EVEN:
        return "GL_FRACTIONAL_EVEN";
    case GL_MAX_PATCH_VERTICES:
        return "GL_MAX_PATCH_VERTICES";
    case GL_MAX_TESS_GEN_LEVEL:
        return "GL_MAX_TESS_GEN_LEVEL";
    case GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS:
        return "GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS";
    case GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS:
        return "GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS";
    case GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS";
    case GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS";
    case GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS:
        return "GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS";
    case GL_MAX_TESS_PATCH_COMPONENTS:
        return "GL_MAX_TESS_PATCH_COMPONENTS";
    case GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS:
        return "GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS";
    case GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS:
        return "GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS";
    case GL_TESS_EVALUATION_SHADER:
        return "GL_TESS_EVALUATION_SHADER";
    case GL_TESS_CONTROL_SHADER:
        return "GL_TESS_CONTROL_SHADER";
    case GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS:
        return "GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS";
    case GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS:
        return "GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS";
    case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB:
        return "GL_COMPRESSED_RGBA_BPTC_UNORM_ARB";
    case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB:
        return "GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB";
    case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB:
        return "GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB";
    case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB:
        return "GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB";
    case GL_BUFFER_GPU_ADDRESS_NV:
        return "GL_BUFFER_GPU_ADDRESS_NV";
    case GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV:
        return "GL_VERTEX_ATTRIB_ARRAY_UNIFIED_NV";
    case GL_ELEMENT_ARRAY_UNIFIED_NV:
        return "GL_ELEMENT_ARRAY_UNIFIED_NV";
    case GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV:
        return "GL_VERTEX_ATTRIB_ARRAY_ADDRESS_NV";
    case GL_VERTEX_ARRAY_ADDRESS_NV:
        return "GL_VERTEX_ARRAY_ADDRESS_NV";
    case GL_NORMAL_ARRAY_ADDRESS_NV:
        return "GL_NORMAL_ARRAY_ADDRESS_NV";
    case GL_COLOR_ARRAY_ADDRESS_NV:
        return "GL_COLOR_ARRAY_ADDRESS_NV";
    case GL_INDEX_ARRAY_ADDRESS_NV:
        return "GL_INDEX_ARRAY_ADDRESS_NV";
    case GL_TEXTURE_COORD_ARRAY_ADDRESS_NV:
        return "GL_TEXTURE_COORD_ARRAY_ADDRESS_NV";
    case GL_EDGE_FLAG_ARRAY_ADDRESS_NV:
        return "GL_EDGE_FLAG_ARRAY_ADDRESS_NV";
    case GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV:
        return "GL_SECONDARY_COLOR_ARRAY_ADDRESS_NV";
    case GL_FOG_COORD_ARRAY_ADDRESS_NV:
        return "GL_FOG_COORD_ARRAY_ADDRESS_NV";
    case GL_ELEMENT_ARRAY_ADDRESS_NV:
        return "GL_ELEMENT_ARRAY_ADDRESS_NV";
    case GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV:
        return "GL_VERTEX_ATTRIB_ARRAY_LENGTH_NV";
    case GL_VERTEX_ARRAY_LENGTH_NV:
        return "GL_VERTEX_ARRAY_LENGTH_NV";
    case GL_NORMAL_ARRAY_LENGTH_NV:
        return "GL_NORMAL_ARRAY_LENGTH_NV";
    case GL_COLOR_ARRAY_LENGTH_NV:
        return "GL_COLOR_ARRAY_LENGTH_NV";
    case GL_INDEX_ARRAY_LENGTH_NV:
        return "GL_INDEX_ARRAY_LENGTH_NV";
    case GL_TEXTURE_COORD_ARRAY_LENGTH_NV:
        return "GL_TEXTURE_COORD_ARRAY_LENGTH_NV";
    case GL_EDGE_FLAG_ARRAY_LENGTH_NV:
        return "GL_EDGE_FLAG_ARRAY_LENGTH_NV";
    case GL_SECONDARY_COLOR_ARRAY_LENGTH_NV:
        return "GL_SECONDARY_COLOR_ARRAY_LENGTH_NV";
    case GL_FOG_COORD_ARRAY_LENGTH_NV:
        return "GL_FOG_COORD_ARRAY_LENGTH_NV";
    case GL_ELEMENT_ARRAY_LENGTH_NV:
        return "GL_ELEMENT_ARRAY_LENGTH_NV";
    case GL_GPU_ADDRESS_NV:
        return "GL_GPU_ADDRESS_NV";
    case GL_MAX_SHADER_BUFFER_ADDRESS_NV:
        return "GL_MAX_SHADER_BUFFER_ADDRESS_NV";
    case GL_COPY_READ_BUFFER:
        return "GL_COPY_READ_BUFFER";
    case GL_COPY_WRITE_BUFFER:
        return "GL_COPY_WRITE_BUFFER";
    case GL_MAX_IMAGE_UNITS:
        return "GL_MAX_IMAGE_UNITS";
    case GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS:
        return "GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS";
    case GL_IMAGE_BINDING_NAME:
        return "GL_IMAGE_BINDING_NAME";
    case GL_IMAGE_BINDING_LEVEL:
        return "GL_IMAGE_BINDING_LEVEL";
    case GL_IMAGE_BINDING_LAYERED:
        return "GL_IMAGE_BINDING_LAYERED";
    case GL_IMAGE_BINDING_LAYER:
        return "GL_IMAGE_BINDING_LAYER";
    case GL_IMAGE_BINDING_ACCESS:
        return "GL_IMAGE_BINDING_ACCESS";
    case GL_DRAW_INDIRECT_BUFFER:
        return "GL_DRAW_INDIRECT_BUFFER";
    case GL_DRAW_INDIRECT_UNIFIED_NV:
        return "GL_DRAW_INDIRECT_UNIFIED_NV";
    case GL_DRAW_INDIRECT_ADDRESS_NV:
        return "GL_DRAW_INDIRECT_ADDRESS_NV";
    case GL_DRAW_INDIRECT_LENGTH_NV:
        return "GL_DRAW_INDIRECT_LENGTH_NV";
    case GL_DRAW_INDIRECT_BUFFER_BINDING:
        return "GL_DRAW_INDIRECT_BUFFER_BINDING";
    case GL_MAX_PROGRAM_SUBROUTINE_PARAMETERS_NV:
        return "GL_MAX_PROGRAM_SUBROUTINE_PARAMETERS_NV";
    case GL_MAX_PROGRAM_SUBROUTINE_NUM_NV:
        return "GL_MAX_PROGRAM_SUBROUTINE_NUM_NV";
    case GL_DOUBLE_MAT2:
        return "GL_DOUBLE_MAT2";
    case GL_DOUBLE_MAT3:
        return "GL_DOUBLE_MAT3";
    case GL_DOUBLE_MAT4:
        return "GL_DOUBLE_MAT4";
    case GL_DOUBLE_MAT2x3:
        return "GL_DOUBLE_MAT2x3";
    case GL_DOUBLE_MAT2x4:
        return "GL_DOUBLE_MAT2x4";
    case GL_DOUBLE_MAT3x2:
        return "GL_DOUBLE_MAT3x2";
    case GL_DOUBLE_MAT3x4:
        return "GL_DOUBLE_MAT3x4";
    case GL_DOUBLE_MAT4x2:
        return "GL_DOUBLE_MAT4x2";
    case GL_DOUBLE_MAT4x3:
        return "GL_DOUBLE_MAT4x3";
    case GL_MALI_SHADER_BINARY_ARM:
        return "GL_MALI_SHADER_BINARY_ARM";
    case GL_RED_SNORM:
        return "GL_RED_SNORM";
    case GL_RG_SNORM:
        return "GL_RG_SNORM";
    case GL_RGB_SNORM:
        return "GL_RGB_SNORM";
    case GL_RGBA_SNORM:
        return "GL_RGBA_SNORM";
    case GL_R8_SNORM:
        return "GL_R8_SNORM";
    case GL_RG8_SNORM:
        return "GL_RG8_SNORM";
    case GL_RGB8_SNORM:
        return "GL_RGB8_SNORM";
    case GL_RGBA8_SNORM:
        return "GL_RGBA8_SNORM";
    case GL_R16_SNORM:
        return "GL_R16_SNORM";
    case GL_RG16_SNORM:
        return "GL_RG16_SNORM";
    case GL_RGB16_SNORM:
        return "GL_RGB16_SNORM";
    case GL_RGBA16_SNORM:
        return "GL_RGBA16_SNORM";
    case GL_SIGNED_NORMALIZED:
        return "GL_SIGNED_NORMALIZED";
    case GL_PRIMITIVE_RESTART:
        return "GL_PRIMITIVE_RESTART";
    case GL_PRIMITIVE_RESTART_INDEX:
        return "GL_PRIMITIVE_RESTART_INDEX";
    case GL_PERFMON_GLOBAL_MODE_QCOM:
        return "GL_PERFMON_GLOBAL_MODE_QCOM";
    case GL_SHADER_BINARY_VIV:
        return "GL_SHADER_BINARY_VIV";
    case GL_INT8_NV:
        return "GL_INT8_NV";
    case GL_INT8_VEC2_NV:
        return "GL_INT8_VEC2_NV";
    case GL_INT8_VEC3_NV:
        return "GL_INT8_VEC3_NV";
    case GL_INT8_VEC4_NV:
        return "GL_INT8_VEC4_NV";
    case GL_INT16_NV:
        return "GL_INT16_NV";
    case GL_INT16_VEC2_NV:
        return "GL_INT16_VEC2_NV";
    case GL_INT16_VEC3_NV:
        return "GL_INT16_VEC3_NV";
    case GL_INT16_VEC4_NV:
        return "GL_INT16_VEC4_NV";
    case GL_INT64_VEC2_NV:
        return "GL_INT64_VEC2_NV";
    case GL_INT64_VEC3_NV:
        return "GL_INT64_VEC3_NV";
    case GL_INT64_VEC4_NV:
        return "GL_INT64_VEC4_NV";
    case GL_UNSIGNED_INT8_NV:
        return "GL_UNSIGNED_INT8_NV";
    case GL_UNSIGNED_INT8_VEC2_NV:
        return "GL_UNSIGNED_INT8_VEC2_NV";
    case GL_UNSIGNED_INT8_VEC3_NV:
        return "GL_UNSIGNED_INT8_VEC3_NV";
    case GL_UNSIGNED_INT8_VEC4_NV:
        return "GL_UNSIGNED_INT8_VEC4_NV";
    case GL_UNSIGNED_INT16_NV:
        return "GL_UNSIGNED_INT16_NV";
    case GL_UNSIGNED_INT16_VEC2_NV:
        return "GL_UNSIGNED_INT16_VEC2_NV";
    case GL_UNSIGNED_INT16_VEC3_NV:
        return "GL_UNSIGNED_INT16_VEC3_NV";
    case GL_UNSIGNED_INT16_VEC4_NV:
        return "GL_UNSIGNED_INT16_VEC4_NV";
    case GL_UNSIGNED_INT64_VEC2_NV:
        return "GL_UNSIGNED_INT64_VEC2_NV";
    case GL_UNSIGNED_INT64_VEC3_NV:
        return "GL_UNSIGNED_INT64_VEC3_NV";
    case GL_UNSIGNED_INT64_VEC4_NV:
        return "GL_UNSIGNED_INT64_VEC4_NV";
    case GL_FLOAT16_NV:
        return "GL_FLOAT16_NV";
    case GL_FLOAT16_VEC2_NV:
        return "GL_FLOAT16_VEC2_NV";
    case GL_FLOAT16_VEC3_NV:
        return "GL_FLOAT16_VEC3_NV";
    case GL_FLOAT16_VEC4_NV:
        return "GL_FLOAT16_VEC4_NV";
    case GL_DOUBLE_VEC2:
        return "GL_DOUBLE_VEC2";
    case GL_DOUBLE_VEC3:
        return "GL_DOUBLE_VEC3";
    case GL_DOUBLE_VEC4:
        return "GL_DOUBLE_VEC4";
    case GL_SAMPLER_BUFFER_AMD:
        return "GL_SAMPLER_BUFFER_AMD";
    case GL_INT_SAMPLER_BUFFER_AMD:
        return "GL_INT_SAMPLER_BUFFER_AMD";
    case GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD:
        return "GL_UNSIGNED_INT_SAMPLER_BUFFER_AMD";
    case GL_TESSELLATION_MODE_AMD:
        return "GL_TESSELLATION_MODE_AMD";
    case GL_TESSELLATION_FACTOR_AMD:
        return "GL_TESSELLATION_FACTOR_AMD";
    case GL_DISCRETE_AMD:
        return "GL_DISCRETE_AMD";
    case GL_CONTINUOUS_AMD:
        return "GL_CONTINUOUS_AMD";
    case GL_TEXTURE_CUBE_MAP_ARRAY:
        return "GL_TEXTURE_CUBE_MAP_ARRAY";
    case GL_TEXTURE_BINDING_CUBE_MAP_ARRAY:
        return "GL_TEXTURE_BINDING_CUBE_MAP_ARRAY";
    case GL_PROXY_TEXTURE_CUBE_MAP_ARRAY:
        return "GL_PROXY_TEXTURE_CUBE_MAP_ARRAY";
    case GL_SAMPLER_CUBE_MAP_ARRAY:
        return "GL_SAMPLER_CUBE_MAP_ARRAY";
    case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW:
        return "GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW";
    case GL_INT_SAMPLER_CUBE_MAP_ARRAY:
        return "GL_INT_SAMPLER_CUBE_MAP_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY:
        return "GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY";
    case GL_ALPHA_SNORM:
        return "GL_ALPHA_SNORM";
    case GL_LUMINANCE_SNORM:
        return "GL_LUMINANCE_SNORM";
    case GL_LUMINANCE_ALPHA_SNORM:
        return "GL_LUMINANCE_ALPHA_SNORM";
    case GL_INTENSITY_SNORM:
        return "GL_INTENSITY_SNORM";
    case GL_ALPHA8_SNORM:
        return "GL_ALPHA8_SNORM";
    case GL_LUMINANCE8_SNORM:
        return "GL_LUMINANCE8_SNORM";
    case GL_LUMINANCE8_ALPHA8_SNORM:
        return "GL_LUMINANCE8_ALPHA8_SNORM";
    case GL_INTENSITY8_SNORM:
        return "GL_INTENSITY8_SNORM";
    case GL_ALPHA16_SNORM:
        return "GL_ALPHA16_SNORM";
    case GL_LUMINANCE16_SNORM:
        return "GL_LUMINANCE16_SNORM";
    case GL_LUMINANCE16_ALPHA16_SNORM:
        return "GL_LUMINANCE16_ALPHA16_SNORM";
    case GL_INTENSITY16_SNORM:
        return "GL_INTENSITY16_SNORM";
    case GL_FACTOR_MIN_AMD:
        return "GL_FACTOR_MIN_AMD";
    case GL_FACTOR_MAX_AMD:
        return "GL_FACTOR_MAX_AMD";
    case GL_DEPTH_CLAMP_NEAR_AMD:
        return "GL_DEPTH_CLAMP_NEAR_AMD";
    case GL_DEPTH_CLAMP_FAR_AMD:
        return "GL_DEPTH_CLAMP_FAR_AMD";
    case GL_VIDEO_BUFFER_NV:
        return "GL_VIDEO_BUFFER_NV";
    case GL_VIDEO_BUFFER_BINDING_NV:
        return "GL_VIDEO_BUFFER_BINDING_NV";
    case GL_FIELD_UPPER_NV:
        return "GL_FIELD_UPPER_NV";
    case GL_FIELD_LOWER_NV:
        return "GL_FIELD_LOWER_NV";
    case GL_NUM_VIDEO_CAPTURE_STREAMS_NV:
        return "GL_NUM_VIDEO_CAPTURE_STREAMS_NV";
    case GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV:
        return "GL_NEXT_VIDEO_CAPTURE_BUFFER_STATUS_NV";
    case GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV:
        return "GL_VIDEO_CAPTURE_TO_422_SUPPORTED_NV";
    case GL_LAST_VIDEO_CAPTURE_STATUS_NV:
        return "GL_LAST_VIDEO_CAPTURE_STATUS_NV";
    case GL_VIDEO_BUFFER_PITCH_NV:
        return "GL_VIDEO_BUFFER_PITCH_NV";
    case GL_VIDEO_COLOR_CONVERSION_MATRIX_NV:
        return "GL_VIDEO_COLOR_CONVERSION_MATRIX_NV";
    case GL_VIDEO_COLOR_CONVERSION_MAX_NV:
        return "GL_VIDEO_COLOR_CONVERSION_MAX_NV";
    case GL_VIDEO_COLOR_CONVERSION_MIN_NV:
        return "GL_VIDEO_COLOR_CONVERSION_MIN_NV";
    case GL_VIDEO_COLOR_CONVERSION_OFFSET_NV:
        return "GL_VIDEO_COLOR_CONVERSION_OFFSET_NV";
    case GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV:
        return "GL_VIDEO_BUFFER_INTERNAL_FORMAT_NV";
    case GL_PARTIAL_SUCCESS_NV:
        return "GL_PARTIAL_SUCCESS_NV";
    case GL_SUCCESS_NV:
        return "GL_SUCCESS_NV";
    case GL_FAILURE_NV:
        return "GL_FAILURE_NV";
    case GL_YCBYCR8_422_NV:
        return "GL_YCBYCR8_422_NV";
    case GL_YCBAYCR8A_4224_NV:
        return "GL_YCBAYCR8A_4224_NV";
    case GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV:
        return "GL_Z6Y10Z6CB10Z6Y10Z6CR10_422_NV";
    case GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV:
        return "GL_Z6Y10Z6CB10Z6A10Z6Y10Z6CR10Z6A10_4224_NV";
    case GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV:
        return "GL_Z4Y12Z4CB12Z4Y12Z4CR12_422_NV";
    case GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV:
        return "GL_Z4Y12Z4CB12Z4A12Z4Y12Z4CR12Z4A12_4224_NV";
    case GL_Z4Y12Z4CB12Z4CR12_444_NV:
        return "GL_Z4Y12Z4CB12Z4CR12_444_NV";
    case GL_VIDEO_CAPTURE_FRAME_WIDTH_NV:
        return "GL_VIDEO_CAPTURE_FRAME_WIDTH_NV";
    case GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV:
        return "GL_VIDEO_CAPTURE_FRAME_HEIGHT_NV";
    case GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV:
        return "GL_VIDEO_CAPTURE_FIELD_UPPER_HEIGHT_NV";
    case GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV:
        return "GL_VIDEO_CAPTURE_FIELD_LOWER_HEIGHT_NV";
    case GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV:
        return "GL_VIDEO_CAPTURE_SURFACE_ORIGIN_NV";
    case GL_TEXTURE_COVERAGE_SAMPLES_NV:
        return "GL_TEXTURE_COVERAGE_SAMPLES_NV";
    case GL_TEXTURE_COLOR_SAMPLES_NV:
        return "GL_TEXTURE_COLOR_SAMPLES_NV";
    case GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX:
        return "GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX";
    case GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX:
        return "GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX";
    case GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX:
        return "GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX";
    case GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX:
        return "GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX";
    case GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX:
        return "GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX";
    case GL_IMAGE_1D:
        return "GL_IMAGE_1D";
    case GL_IMAGE_2D:
        return "GL_IMAGE_2D";
    case GL_IMAGE_3D:
        return "GL_IMAGE_3D";
    case GL_IMAGE_2D_RECT:
        return "GL_IMAGE_2D_RECT";
    case GL_IMAGE_CUBE:
        return "GL_IMAGE_CUBE";
    case GL_IMAGE_BUFFER:
        return "GL_IMAGE_BUFFER";
    case GL_IMAGE_1D_ARRAY:
        return "GL_IMAGE_1D_ARRAY";
    case GL_IMAGE_2D_ARRAY:
        return "GL_IMAGE_2D_ARRAY";
    case GL_IMAGE_CUBE_MAP_ARRAY:
        return "GL_IMAGE_CUBE_MAP_ARRAY";
    case GL_IMAGE_2D_MULTISAMPLE:
        return "GL_IMAGE_2D_MULTISAMPLE";
    case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
        return "GL_IMAGE_2D_MULTISAMPLE_ARRAY";
    case GL_INT_IMAGE_1D:
        return "GL_INT_IMAGE_1D";
    case GL_INT_IMAGE_2D:
        return "GL_INT_IMAGE_2D";
    case GL_INT_IMAGE_3D:
        return "GL_INT_IMAGE_3D";
    case GL_INT_IMAGE_2D_RECT:
        return "GL_INT_IMAGE_2D_RECT";
    case GL_INT_IMAGE_CUBE:
        return "GL_INT_IMAGE_CUBE";
    case GL_INT_IMAGE_BUFFER:
        return "GL_INT_IMAGE_BUFFER";
    case GL_INT_IMAGE_1D_ARRAY:
        return "GL_INT_IMAGE_1D_ARRAY";
    case GL_INT_IMAGE_2D_ARRAY:
        return "GL_INT_IMAGE_2D_ARRAY";
    case GL_INT_IMAGE_CUBE_MAP_ARRAY:
        return "GL_INT_IMAGE_CUBE_MAP_ARRAY";
    case GL_INT_IMAGE_2D_MULTISAMPLE:
        return "GL_INT_IMAGE_2D_MULTISAMPLE";
    case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
        return "GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY";
    case GL_UNSIGNED_INT_IMAGE_1D:
        return "GL_UNSIGNED_INT_IMAGE_1D";
    case GL_UNSIGNED_INT_IMAGE_2D:
        return "GL_UNSIGNED_INT_IMAGE_2D";
    case GL_UNSIGNED_INT_IMAGE_3D:
        return "GL_UNSIGNED_INT_IMAGE_3D";
    case GL_UNSIGNED_INT_IMAGE_2D_RECT:
        return "GL_UNSIGNED_INT_IMAGE_2D_RECT";
    case GL_UNSIGNED_INT_IMAGE_CUBE:
        return "GL_UNSIGNED_INT_IMAGE_CUBE";
    case GL_UNSIGNED_INT_IMAGE_BUFFER:
        return "GL_UNSIGNED_INT_IMAGE_BUFFER";
    case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
        return "GL_UNSIGNED_INT_IMAGE_1D_ARRAY";
    case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
        return "GL_UNSIGNED_INT_IMAGE_2D_ARRAY";
    case GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY:
        return "GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY";
    case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
        return "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE";
    case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
        return "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY";
    case GL_MAX_IMAGE_SAMPLES:
        return "GL_MAX_IMAGE_SAMPLES";
    case GL_IMAGE_BINDING_FORMAT:
        return "GL_IMAGE_BINDING_FORMAT";
    case GL_RGB10_A2UI:
        return "GL_RGB10_A2UI";
    case GL_PATH_FORMAT_SVG_NV:
        return "GL_PATH_FORMAT_SVG_NV";
    case GL_PATH_FORMAT_PS_NV:
        return "GL_PATH_FORMAT_PS_NV";
    case GL_STANDARD_FONT_NAME_NV:
        return "GL_STANDARD_FONT_NAME_NV";
    case GL_SYSTEM_FONT_NAME_NV:
        return "GL_SYSTEM_FONT_NAME_NV";
    case GL_FILE_NAME_NV:
        return "GL_FILE_NAME_NV";
    case GL_PATH_STROKE_WIDTH_NV:
        return "GL_PATH_STROKE_WIDTH_NV";
    case GL_PATH_END_CAPS_NV:
        return "GL_PATH_END_CAPS_NV";
    case GL_PATH_INITIAL_END_CAP_NV:
        return "GL_PATH_INITIAL_END_CAP_NV";
    case GL_PATH_TERMINAL_END_CAP_NV:
        return "GL_PATH_TERMINAL_END_CAP_NV";
    case GL_PATH_JOIN_STYLE_NV:
        return "GL_PATH_JOIN_STYLE_NV";
    case GL_PATH_MITER_LIMIT_NV:
        return "GL_PATH_MITER_LIMIT_NV";
    case GL_PATH_DASH_CAPS_NV:
        return "GL_PATH_DASH_CAPS_NV";
    case GL_PATH_INITIAL_DASH_CAP_NV:
        return "GL_PATH_INITIAL_DASH_CAP_NV";
    case GL_PATH_TERMINAL_DASH_CAP_NV:
        return "GL_PATH_TERMINAL_DASH_CAP_NV";
    case GL_PATH_DASH_OFFSET_NV:
        return "GL_PATH_DASH_OFFSET_NV";
    case GL_PATH_CLIENT_LENGTH_NV:
        return "GL_PATH_CLIENT_LENGTH_NV";
    case GL_PATH_FILL_MODE_NV:
        return "GL_PATH_FILL_MODE_NV";
    case GL_PATH_FILL_MASK_NV:
        return "GL_PATH_FILL_MASK_NV";
    case GL_PATH_FILL_COVER_MODE_NV:
        return "GL_PATH_FILL_COVER_MODE_NV";
    case GL_PATH_STROKE_COVER_MODE_NV:
        return "GL_PATH_STROKE_COVER_MODE_NV";
    case GL_PATH_STROKE_MASK_NV:
        return "GL_PATH_STROKE_MASK_NV";
    case GL_PATH_SAMPLE_QUALITY_NV:
        return "GL_PATH_SAMPLE_QUALITY_NV";
    case GL_PATH_STROKE_BOUND_NV:
        return "GL_PATH_STROKE_BOUND_NV";
    case GL_PATH_STROKE_OVERSAMPLE_COUNT_NV:
        return "GL_PATH_STROKE_OVERSAMPLE_COUNT_NV";
    case GL_COUNT_UP_NV:
        return "GL_COUNT_UP_NV";
    case GL_COUNT_DOWN_NV:
        return "GL_COUNT_DOWN_NV";
    case GL_PATH_OBJECT_BOUNDING_BOX_NV:
        return "GL_PATH_OBJECT_BOUNDING_BOX_NV";
    case GL_CONVEX_HULL_NV:
        return "GL_CONVEX_HULL_NV";
    case GL_MULTI_HULLS_NV:
        return "GL_MULTI_HULLS_NV";
    case GL_BOUNDING_BOX_NV:
        return "GL_BOUNDING_BOX_NV";
    case GL_TRANSLATE_X_NV:
        return "GL_TRANSLATE_X_NV";
    case GL_TRANSLATE_Y_NV:
        return "GL_TRANSLATE_Y_NV";
    case GL_TRANSLATE_2D_NV:
        return "GL_TRANSLATE_2D_NV";
    case GL_TRANSLATE_3D_NV:
        return "GL_TRANSLATE_3D_NV";
    case GL_AFFINE_2D_NV:
        return "GL_AFFINE_2D_NV";
    case GL_PROJECTIVE_2D_NV:
        return "GL_PROJECTIVE_2D_NV";
    case GL_AFFINE_3D_NV:
        return "GL_AFFINE_3D_NV";
    case GL_PROJECTIVE_3D_NV:
        return "GL_PROJECTIVE_3D_NV";
    case GL_TRANSPOSE_AFFINE_2D_NV:
        return "GL_TRANSPOSE_AFFINE_2D_NV";
    case GL_TRANSPOSE_PROJECTIVE_2D_NV:
        return "GL_TRANSPOSE_PROJECTIVE_2D_NV";
    case GL_TRANSPOSE_AFFINE_3D_NV:
        return "GL_TRANSPOSE_AFFINE_3D_NV";
    case GL_TRANSPOSE_PROJECTIVE_3D_NV:
        return "GL_TRANSPOSE_PROJECTIVE_3D_NV";
    case GL_UTF8_NV:
        return "GL_UTF8_NV";
    case GL_UTF16_NV:
        return "GL_UTF16_NV";
    case GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV:
        return "GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV";
    case GL_PATH_COMMAND_COUNT_NV:
        return "GL_PATH_COMMAND_COUNT_NV";
    case GL_PATH_COORD_COUNT_NV:
        return "GL_PATH_COORD_COUNT_NV";
    case GL_PATH_DASH_ARRAY_COUNT_NV:
        return "GL_PATH_DASH_ARRAY_COUNT_NV";
    case GL_PATH_COMPUTED_LENGTH_NV:
        return "GL_PATH_COMPUTED_LENGTH_NV";
    case GL_PATH_FILL_BOUNDING_BOX_NV:
        return "GL_PATH_FILL_BOUNDING_BOX_NV";
    case GL_PATH_STROKE_BOUNDING_BOX_NV:
        return "GL_PATH_STROKE_BOUNDING_BOX_NV";
    case GL_SQUARE_NV:
        return "GL_SQUARE_NV";
    case GL_ROUND_NV:
        return "GL_ROUND_NV";
    case GL_TRIANGULAR_NV:
        return "GL_TRIANGULAR_NV";
    case GL_BEVEL_NV:
        return "GL_BEVEL_NV";
    case GL_MITER_REVERT_NV:
        return "GL_MITER_REVERT_NV";
    case GL_MITER_TRUNCATE_NV:
        return "GL_MITER_TRUNCATE_NV";
    case GL_SKIP_MISSING_GLYPH_NV:
        return "GL_SKIP_MISSING_GLYPH_NV";
    case GL_USE_MISSING_GLYPH_NV:
        return "GL_USE_MISSING_GLYPH_NV";
    case GL_PATH_ERROR_POSITION_NV:
        return "GL_PATH_ERROR_POSITION_NV";
    case GL_PATH_FOG_GEN_MODE_NV:
        return "GL_PATH_FOG_GEN_MODE_NV";
    case GL_ACCUM_ADJACENT_PAIRS_NV:
        return "GL_ACCUM_ADJACENT_PAIRS_NV";
    case GL_ADJACENT_PAIRS_NV:
        return "GL_ADJACENT_PAIRS_NV";
    case GL_FIRST_TO_REST_NV:
        return "GL_FIRST_TO_REST_NV";
    case GL_PATH_GEN_MODE_NV:
        return "GL_PATH_GEN_MODE_NV";
    case GL_PATH_GEN_COEFF_NV:
        return "GL_PATH_GEN_COEFF_NV";
    case GL_PATH_GEN_COLOR_FORMAT_NV:
        return "GL_PATH_GEN_COLOR_FORMAT_NV";
    case GL_PATH_GEN_COMPONENTS_NV:
        return "GL_PATH_GEN_COMPONENTS_NV";
    case GL_PATH_DASH_OFFSET_RESET_NV:
        return "GL_PATH_DASH_OFFSET_RESET_NV";
    case GL_MOVE_TO_RESETS_NV:
        return "GL_MOVE_TO_RESETS_NV";
    case GL_MOVE_TO_CONTINUES_NV:
        return "GL_MOVE_TO_CONTINUES_NV";
    case GL_PATH_STENCIL_FUNC_NV:
        return "GL_PATH_STENCIL_FUNC_NV";
    case GL_PATH_STENCIL_REF_NV:
        return "GL_PATH_STENCIL_REF_NV";
    case GL_PATH_STENCIL_VALUE_MASK_NV:
        return "GL_PATH_STENCIL_VALUE_MASK_NV";
    case GL_SCALED_RESOLVE_FASTEST_EXT:
        return "GL_SCALED_RESOLVE_FASTEST_EXT";
    case GL_SCALED_RESOLVE_NICEST_EXT:
        return "GL_SCALED_RESOLVE_NICEST_EXT";
    case GL_MIN_MAP_BUFFER_ALIGNMENT:
        return "GL_MIN_MAP_BUFFER_ALIGNMENT";
    case GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV:
        return "GL_PATH_STENCIL_DEPTH_OFFSET_FACTOR_NV";
    case GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV:
        return "GL_PATH_STENCIL_DEPTH_OFFSET_UNITS_NV";
    case GL_PATH_COVER_DEPTH_FUNC_NV:
        return "GL_PATH_COVER_DEPTH_FUNC_NV";
    case GL_IMAGE_FORMAT_COMPATIBILITY_TYPE:
        return "GL_IMAGE_FORMAT_COMPATIBILITY_TYPE";
    case GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE:
        return "GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE";
    case GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS:
        return "GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS";
    case GL_MAX_VERTEX_IMAGE_UNIFORMS:
        return "GL_MAX_VERTEX_IMAGE_UNIFORMS";
    case GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS:
        return "GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS";
    case GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS:
        return "GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS";
    case GL_MAX_GEOMETRY_IMAGE_UNIFORMS:
        return "GL_MAX_GEOMETRY_IMAGE_UNIFORMS";
    case GL_MAX_FRAGMENT_IMAGE_UNIFORMS:
        return "GL_MAX_FRAGMENT_IMAGE_UNIFORMS";
    case GL_MAX_COMBINED_IMAGE_UNIFORMS:
        return "GL_MAX_COMBINED_IMAGE_UNIFORMS";
    case GL_SHADER_STORAGE_BUFFER:
        return "GL_SHADER_STORAGE_BUFFER";
    case GL_SHADER_STORAGE_BUFFER_BINDING:
        return "GL_SHADER_STORAGE_BUFFER_BINDING";
    case GL_SHADER_STORAGE_BUFFER_START:
        return "GL_SHADER_STORAGE_BUFFER_START";
    case GL_SHADER_STORAGE_BUFFER_SIZE:
        return "GL_SHADER_STORAGE_BUFFER_SIZE";
    case GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS";
    case GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS";
    case GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS";
    case GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS";
    case GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS";
    case GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS";
    case GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS:
        return "GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS";
    case GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS:
        return "GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS";
    case GL_MAX_SHADER_STORAGE_BLOCK_SIZE:
        return "GL_MAX_SHADER_STORAGE_BLOCK_SIZE";
    case GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT:
        return "GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT";
    case GL_SYNC_X11_FENCE_EXT:
        return "GL_SYNC_X11_FENCE_EXT";
    case GL_DEPTH_STENCIL_TEXTURE_MODE:
        return "GL_DEPTH_STENCIL_TEXTURE_MODE";
    case GL_MAX_COMPUTE_LOCAL_INVOCATIONS:
        return "GL_MAX_COMPUTE_LOCAL_INVOCATIONS";
    case GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER:
        return "GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER";
    case GL_DISPATCH_INDIRECT_BUFFER:
        return "GL_DISPATCH_INDIRECT_BUFFER";
    case GL_DISPATCH_INDIRECT_BUFFER_BINDING:
        return "GL_DISPATCH_INDIRECT_BUFFER_BINDING";
    case GL_TEXTURE_2D_MULTISAMPLE:
        return "GL_TEXTURE_2D_MULTISAMPLE";
    case GL_PROXY_TEXTURE_2D_MULTISAMPLE:
        return "GL_PROXY_TEXTURE_2D_MULTISAMPLE";
    case GL_TEXTURE_2D_MULTISAMPLE_ARRAY:
        return "GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
    case GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY:
        return "GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE:
        return "GL_TEXTURE_BINDING_2D_MULTISAMPLE";
    case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY:
        return "GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY";
    case GL_TEXTURE_SAMPLES:
        return "GL_TEXTURE_SAMPLES";
    case GL_TEXTURE_FIXED_SAMPLE_LOCATIONS:
        return "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS";
    case GL_SAMPLER_2D_MULTISAMPLE:
        return "GL_SAMPLER_2D_MULTISAMPLE";
    case GL_INT_SAMPLER_2D_MULTISAMPLE:
        return "GL_INT_SAMPLER_2D_MULTISAMPLE";
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
        return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
    case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
        return "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
    case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
        return "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
    case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
        return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
    case GL_MAX_COLOR_TEXTURE_SAMPLES:
        return "GL_MAX_COLOR_TEXTURE_SAMPLES";
    case GL_MAX_DEPTH_TEXTURE_SAMPLES:
        return "GL_MAX_DEPTH_TEXTURE_SAMPLES";
    case GL_MAX_INTEGER_SAMPLES:
        return "GL_MAX_INTEGER_SAMPLES";
    case GL_MAX_SERVER_WAIT_TIMEOUT:
        return "GL_MAX_SERVER_WAIT_TIMEOUT";
    case GL_OBJECT_TYPE:
        return "GL_OBJECT_TYPE";
    case GL_SYNC_CONDITION:
        return "GL_SYNC_CONDITION";
    case GL_SYNC_STATUS:
        return "GL_SYNC_STATUS";
    case GL_SYNC_FLAGS:
        return "GL_SYNC_FLAGS";
    case GL_SYNC_FENCE:
        return "GL_SYNC_FENCE";
    case GL_SYNC_GPU_COMMANDS_COMPLETE:
        return "GL_SYNC_GPU_COMMANDS_COMPLETE";
    case GL_UNSIGNALED:
        return "GL_UNSIGNALED";
    case GL_SIGNALED:
        return "GL_SIGNALED";
    case GL_ALREADY_SIGNALED:
        return "GL_ALREADY_SIGNALED";
    case GL_TIMEOUT_EXPIRED:
        return "GL_TIMEOUT_EXPIRED";
    case GL_CONDITION_SATISFIED:
        return "GL_CONDITION_SATISFIED";
    case GL_WAIT_FAILED:
        return "GL_WAIT_FAILED";
    case GL_BUFFER_ACCESS_FLAGS:
        return "GL_BUFFER_ACCESS_FLAGS";
    case GL_BUFFER_MAP_LENGTH:
        return "GL_BUFFER_MAP_LENGTH";
    case GL_BUFFER_MAP_OFFSET:
        return "GL_BUFFER_MAP_OFFSET";
    case GL_MAX_VERTEX_OUTPUT_COMPONENTS:
        return "GL_MAX_VERTEX_OUTPUT_COMPONENTS";
    case GL_MAX_GEOMETRY_INPUT_COMPONENTS:
        return "GL_MAX_GEOMETRY_INPUT_COMPONENTS";
    case GL_MAX_GEOMETRY_OUTPUT_COMPONENTS:
        return "GL_MAX_GEOMETRY_OUTPUT_COMPONENTS";
    case GL_MAX_FRAGMENT_INPUT_COMPONENTS:
        return "GL_MAX_FRAGMENT_INPUT_COMPONENTS";
    case GL_CONTEXT_PROFILE_MASK:
        return "GL_CONTEXT_PROFILE_MASK";
    case GL_UNPACK_COMPRESSED_BLOCK_WIDTH:
        return "GL_UNPACK_COMPRESSED_BLOCK_WIDTH";
    case GL_UNPACK_COMPRESSED_BLOCK_HEIGHT:
        return "GL_UNPACK_COMPRESSED_BLOCK_HEIGHT";
    case GL_UNPACK_COMPRESSED_BLOCK_DEPTH:
        return "GL_UNPACK_COMPRESSED_BLOCK_DEPTH";
    case GL_UNPACK_COMPRESSED_BLOCK_SIZE:
        return "GL_UNPACK_COMPRESSED_BLOCK_SIZE";
    case GL_PACK_COMPRESSED_BLOCK_WIDTH:
        return "GL_PACK_COMPRESSED_BLOCK_WIDTH";
    case GL_PACK_COMPRESSED_BLOCK_HEIGHT:
        return "GL_PACK_COMPRESSED_BLOCK_HEIGHT";
    case GL_PACK_COMPRESSED_BLOCK_DEPTH:
        return "GL_PACK_COMPRESSED_BLOCK_DEPTH";
    case GL_PACK_COMPRESSED_BLOCK_SIZE:
        return "GL_PACK_COMPRESSED_BLOCK_SIZE";
    case GL_TEXTURE_IMMUTABLE_FORMAT:
        return "GL_TEXTURE_IMMUTABLE_FORMAT";
    case GL_SGX_PROGRAM_BINARY_IMG:
        return "GL_SGX_PROGRAM_BINARY_IMG";
    case GL_RENDERBUFFER_SAMPLES_IMG:
        return "GL_RENDERBUFFER_SAMPLES_IMG";
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG:
        return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG";
    case GL_MAX_SAMPLES_IMG:
        return "GL_MAX_SAMPLES_IMG";
    case GL_TEXTURE_SAMPLES_IMG:
        return "GL_TEXTURE_SAMPLES_IMG";
    case GL_MAX_DEBUG_MESSAGE_LENGTH:
        return "GL_MAX_DEBUG_MESSAGE_LENGTH";
    case GL_MAX_DEBUG_LOGGED_MESSAGES:
        return "GL_MAX_DEBUG_LOGGED_MESSAGES";
    case GL_DEBUG_LOGGED_MESSAGES:
        return "GL_DEBUG_LOGGED_MESSAGES";
    case GL_DEBUG_SEVERITY_HIGH:
        return "GL_DEBUG_SEVERITY_HIGH";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "GL_DEBUG_SEVERITY_MEDIUM";
    case GL_DEBUG_SEVERITY_LOW:
        return "GL_DEBUG_SEVERITY_LOW";
    case GL_DEBUG_CATEGORY_API_ERROR_AMD:
        return "GL_DEBUG_CATEGORY_API_ERROR_AMD";
    case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
        return "GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD";
    case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
        return "GL_DEBUG_CATEGORY_DEPRECATION_AMD";
    case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
        return "GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD";
    case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
        return "GL_DEBUG_CATEGORY_PERFORMANCE_AMD";
    case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
        return "GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD";
    case GL_DEBUG_CATEGORY_APPLICATION_AMD:
        return "GL_DEBUG_CATEGORY_APPLICATION_AMD";
    case GL_DEBUG_CATEGORY_OTHER_AMD:
        return "GL_DEBUG_CATEGORY_OTHER_AMD";
    case GL_BUFFER_OBJECT_EXT:
        return "GL_BUFFER_OBJECT_EXT";
    case GL_PERFORMANCE_MONITOR_AMD:
        return "GL_PERFORMANCE_MONITOR_AMD";
    case GL_QUERY_OBJECT_EXT:
        return "GL_QUERY_OBJECT_EXT";
    case GL_VERTEX_ARRAY_OBJECT_EXT:
        return "GL_VERTEX_ARRAY_OBJECT_EXT";
    case GL_SAMPLER_OBJECT_AMD:
        return "GL_SAMPLER_OBJECT_AMD";
    case GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD:
        return "GL_EXTERNAL_VIRTUAL_MEMORY_BUFFER_AMD";
    case GL_QUERY_BUFFER_AMD:
        return "GL_QUERY_BUFFER_AMD";
    case GL_QUERY_BUFFER_BINDING_AMD:
        return "GL_QUERY_BUFFER_BINDING_AMD";
    case GL_QUERY_RESULT_NO_WAIT_AMD:
        return "GL_QUERY_RESULT_NO_WAIT_AMD";
    case GL_TEXTURE_BUFFER_OFFSET:
        return "GL_TEXTURE_BUFFER_OFFSET";
    case GL_TEXTURE_BUFFER_SIZE:
        return "GL_TEXTURE_BUFFER_SIZE";
    case GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT:
        return "GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT";
    case GL_COMPUTE_SHADER:
        return "GL_COMPUTE_SHADER";
    case GL_MAX_COMPUTE_UNIFORM_BLOCKS:
        return "GL_MAX_COMPUTE_UNIFORM_BLOCKS";
    case GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS:
        return "GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS";
    case GL_MAX_COMPUTE_IMAGE_UNIFORMS:
        return "GL_MAX_COMPUTE_IMAGE_UNIFORMS";
    case GL_MAX_COMPUTE_WORK_GROUP_COUNT:
        return "GL_MAX_COMPUTE_WORK_GROUP_COUNT";
    case GL_MAX_COMPUTE_WORK_GROUP_SIZE:
        return "GL_MAX_COMPUTE_WORK_GROUP_SIZE";
    case GL_SHADER_BINARY_DMP:
        return "GL_SHADER_BINARY_DMP";
    case GL_COMPRESSED_R11_EAC:
        return "GL_COMPRESSED_R11_EAC";
    case GL_COMPRESSED_SIGNED_R11_EAC:
        return "GL_COMPRESSED_SIGNED_R11_EAC";
    case GL_COMPRESSED_RG11_EAC:
        return "GL_COMPRESSED_RG11_EAC";
    case GL_COMPRESSED_SIGNED_RG11_EAC:
        return "GL_COMPRESSED_SIGNED_RG11_EAC";
    case GL_COMPRESSED_RGB8_ETC2:
        return "GL_COMPRESSED_RGB8_ETC2";
    case GL_COMPRESSED_SRGB8_ETC2:
        return "GL_COMPRESSED_SRGB8_ETC2";
    case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
        return "GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2";
    case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
        return "GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2";
    case GL_COMPRESSED_RGBA8_ETC2_EAC:
        return "GL_COMPRESSED_RGBA8_ETC2_EAC";
    case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC";
    case GL_ATOMIC_COUNTER_BUFFER:
        return "GL_ATOMIC_COUNTER_BUFFER";
    case GL_ATOMIC_COUNTER_BUFFER_BINDING:
        return "GL_ATOMIC_COUNTER_BUFFER_BINDING";
    case GL_ATOMIC_COUNTER_BUFFER_START:
        return "GL_ATOMIC_COUNTER_BUFFER_START";
    case GL_ATOMIC_COUNTER_BUFFER_SIZE:
        return "GL_ATOMIC_COUNTER_BUFFER_SIZE";
    case GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE:
        return "GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE";
    case GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS:
        return "GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS";
    case GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES:
        return "GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER";
    case GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER:
        return "GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER";
    case GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS:
        return "GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS";
    case GL_MAX_VERTEX_ATOMIC_COUNTERS:
        return "GL_MAX_VERTEX_ATOMIC_COUNTERS";
    case GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS:
        return "GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS";
    case GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS:
        return "GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS";
    case GL_MAX_GEOMETRY_ATOMIC_COUNTERS:
        return "GL_MAX_GEOMETRY_ATOMIC_COUNTERS";
    case GL_MAX_FRAGMENT_ATOMIC_COUNTERS:
        return "GL_MAX_FRAGMENT_ATOMIC_COUNTERS";
    case GL_MAX_COMBINED_ATOMIC_COUNTERS:
        return "GL_MAX_COMBINED_ATOMIC_COUNTERS";
    case GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE:
        return "GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE";
    case GL_ACTIVE_ATOMIC_COUNTER_BUFFERS:
        return "GL_ACTIVE_ATOMIC_COUNTER_BUFFERS";
    case GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX:
        return "GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX";
    case GL_UNSIGNED_INT_ATOMIC_COUNTER:
        return "GL_UNSIGNED_INT_ATOMIC_COUNTER";
    case GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS:
        return "GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS";
    case GL_DEBUG_OUTPUT:
        return "GL_DEBUG_OUTPUT";
    case GL_UNIFORM:
        return "GL_UNIFORM";
    case GL_UNIFORM_BLOCK:
        return "GL_UNIFORM_BLOCK";
    case GL_PROGRAM_INPUT:
        return "GL_PROGRAM_INPUT";
    case GL_PROGRAM_OUTPUT:
        return "GL_PROGRAM_OUTPUT";
    case GL_BUFFER_VARIABLE:
        return "GL_BUFFER_VARIABLE";
    case GL_SHADER_STORAGE_BLOCK:
        return "GL_SHADER_STORAGE_BLOCK";
    case GL_IS_PER_PATCH:
        return "GL_IS_PER_PATCH";
    case GL_VERTEX_SUBROUTINE:
        return "GL_VERTEX_SUBROUTINE";
    case GL_TESS_CONTROL_SUBROUTINE:
        return "GL_TESS_CONTROL_SUBROUTINE";
    case GL_TESS_EVALUATION_SUBROUTINE:
        return "GL_TESS_EVALUATION_SUBROUTINE";
    case GL_GEOMETRY_SUBROUTINE:
        return "GL_GEOMETRY_SUBROUTINE";
    case GL_FRAGMENT_SUBROUTINE:
        return "GL_FRAGMENT_SUBROUTINE";
    case GL_COMPUTE_SUBROUTINE:
        return "GL_COMPUTE_SUBROUTINE";
    case GL_VERTEX_SUBROUTINE_UNIFORM:
        return "GL_VERTEX_SUBROUTINE_UNIFORM";
    case GL_TESS_CONTROL_SUBROUTINE_UNIFORM:
        return "GL_TESS_CONTROL_SUBROUTINE_UNIFORM";
    case GL_TESS_EVALUATION_SUBROUTINE_UNIFORM:
        return "GL_TESS_EVALUATION_SUBROUTINE_UNIFORM";
    case GL_GEOMETRY_SUBROUTINE_UNIFORM:
        return "GL_GEOMETRY_SUBROUTINE_UNIFORM";
    case GL_FRAGMENT_SUBROUTINE_UNIFORM:
        return "GL_FRAGMENT_SUBROUTINE_UNIFORM";
    case GL_COMPUTE_SUBROUTINE_UNIFORM:
        return "GL_COMPUTE_SUBROUTINE_UNIFORM";
    case GL_TRANSFORM_FEEDBACK_VARYING:
        return "GL_TRANSFORM_FEEDBACK_VARYING";
    case GL_ACTIVE_RESOURCES:
        return "GL_ACTIVE_RESOURCES";
    case GL_MAX_NAME_LENGTH:
        return "GL_MAX_NAME_LENGTH";
    case GL_MAX_NUM_ACTIVE_VARIABLES:
        return "GL_MAX_NUM_ACTIVE_VARIABLES";
    case GL_MAX_NUM_COMPATIBLE_SUBROUTINES:
        return "GL_MAX_NUM_COMPATIBLE_SUBROUTINES";
    case GL_NAME_LENGTH:
        return "GL_NAME_LENGTH";
    case GL_TYPE:
        return "GL_TYPE";
    case GL_ARRAY_SIZE:
        return "GL_ARRAY_SIZE";
    case GL_OFFSET:
        return "GL_OFFSET";
    case GL_BLOCK_INDEX:
        return "GL_BLOCK_INDEX";
    case GL_ARRAY_STRIDE:
        return "GL_ARRAY_STRIDE";
    case GL_MATRIX_STRIDE:
        return "GL_MATRIX_STRIDE";
    case GL_IS_ROW_MAJOR:
        return "GL_IS_ROW_MAJOR";
    case GL_ATOMIC_COUNTER_BUFFER_INDEX:
        return "GL_ATOMIC_COUNTER_BUFFER_INDEX";
    case GL_BUFFER_BINDING:
        return "GL_BUFFER_BINDING";
    case GL_BUFFER_DATA_SIZE:
        return "GL_BUFFER_DATA_SIZE";
    case GL_NUM_ACTIVE_VARIABLES:
        return "GL_NUM_ACTIVE_VARIABLES";
    case GL_ACTIVE_VARIABLES:
        return "GL_ACTIVE_VARIABLES";
    case GL_REFERENCED_BY_VERTEX_SHADER:
        return "GL_REFERENCED_BY_VERTEX_SHADER";
    case GL_REFERENCED_BY_TESS_CONTROL_SHADER:
        return "GL_REFERENCED_BY_TESS_CONTROL_SHADER";
    case GL_REFERENCED_BY_TESS_EVALUATION_SHADER:
        return "GL_REFERENCED_BY_TESS_EVALUATION_SHADER";
    case GL_REFERENCED_BY_GEOMETRY_SHADER:
        return "GL_REFERENCED_BY_GEOMETRY_SHADER";
    case GL_REFERENCED_BY_FRAGMENT_SHADER:
        return "GL_REFERENCED_BY_FRAGMENT_SHADER";
    case GL_REFERENCED_BY_COMPUTE_SHADER:
        return "GL_REFERENCED_BY_COMPUTE_SHADER";
    case GL_TOP_LEVEL_ARRAY_SIZE:
        return "GL_TOP_LEVEL_ARRAY_SIZE";
    case GL_TOP_LEVEL_ARRAY_STRIDE:
        return "GL_TOP_LEVEL_ARRAY_STRIDE";
    case GL_LOCATION:
        return "GL_LOCATION";
    case GL_LOCATION_INDEX:
        return "GL_LOCATION_INDEX";
    case GL_FRAMEBUFFER_DEFAULT_WIDTH:
        return "GL_FRAMEBUFFER_DEFAULT_WIDTH";
    case GL_FRAMEBUFFER_DEFAULT_HEIGHT:
        return "GL_FRAMEBUFFER_DEFAULT_HEIGHT";
    case GL_FRAMEBUFFER_DEFAULT_LAYERS:
        return "GL_FRAMEBUFFER_DEFAULT_LAYERS";
    case GL_FRAMEBUFFER_DEFAULT_SAMPLES:
        return "GL_FRAMEBUFFER_DEFAULT_SAMPLES";
    case GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS:
        return "GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS";
    case GL_MAX_FRAMEBUFFER_WIDTH:
        return "GL_MAX_FRAMEBUFFER_WIDTH";
    case GL_MAX_FRAMEBUFFER_HEIGHT:
        return "GL_MAX_FRAMEBUFFER_HEIGHT";
    case GL_MAX_FRAMEBUFFER_LAYERS:
        return "GL_MAX_FRAMEBUFFER_LAYERS";
    case GL_MAX_FRAMEBUFFER_SAMPLES:
        return "GL_MAX_FRAMEBUFFER_SAMPLES";
    case GL_NUM_SAMPLE_COUNTS:
        return "GL_NUM_SAMPLE_COUNTS";
    case GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE:
        return "GL_TRANSLATED_SHADER_SOURCE_LENGTH_ANGLE";
    case GL_TEXTURE_USAGE_ANGLE:
        return "GL_TEXTURE_USAGE_ANGLE";
    case GL_FRAMEBUFFER_ATTACHMENT_ANGLE:
        return "GL_FRAMEBUFFER_ATTACHMENT_ANGLE";
    case GL_PACK_REVERSE_ROW_ORDER_ANGLE:
        return "GL_PACK_REVERSE_ROW_ORDER_ANGLE";
    case GL_COMPRESSED_RGBA_ASTC_4x4_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_4x4_KHR";
    case GL_COMPRESSED_RGBA_ASTC_5x4_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_5x4_KHR";
    case GL_COMPRESSED_RGBA_ASTC_5x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_5x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_6x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_6x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_6x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_6x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_8x8_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_8x8_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x5_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x5_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x6_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x6_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x8_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x8_KHR";
    case GL_COMPRESSED_RGBA_ASTC_10x10_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_10x10_KHR";
    case GL_COMPRESSED_RGBA_ASTC_12x10_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_12x10_KHR";
    case GL_COMPRESSED_RGBA_ASTC_12x12_KHR:
        return "GL_COMPRESSED_RGBA_ASTC_12x12_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR";
    case GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR:
        return "GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR";
    case GL_RESTART_PATH_NV:
        return "GL_RESTART_PATH_NV";
    case GL_DUP_FIRST_CUBIC_CURVE_TO_NV:
        return "GL_DUP_FIRST_CUBIC_CURVE_TO_NV";
    case GL_DUP_LAST_CUBIC_CURVE_TO_NV:
        return "GL_DUP_LAST_CUBIC_CURVE_TO_NV";
    case GL_RECT_NV:
        return "GL_RECT_NV";
    case GL_CIRCULAR_CCW_ARC_TO_NV:
        return "GL_CIRCULAR_CCW_ARC_TO_NV";
    case GL_CIRCULAR_CW_ARC_TO_NV:
        return "GL_CIRCULAR_CW_ARC_TO_NV";
    case GL_CIRCULAR_TANGENT_ARC_TO_NV:
        return "GL_CIRCULAR_TANGENT_ARC_TO_NV";
    case GL_ARC_TO_NV:
        return "GL_ARC_TO_NV";
    case GL_INVALID_INDEX:
        return "GL_INVALID_INDEX";
    default:
        return NULL;
    }
}

void
dumpEnum(JSONWriter &json, GLenum pname)
{
    const char *s = enumToString(pname);
    if (s) {
        json.writeString(s);
    } else {
        json.writeInt(pname);
    }
}

static void
dumpTextureTargetParameters(JSONWriter &json, Context &context, GLenum target, GLenum binding_param)
{
    GLboolean enabled = GL_FALSE;
    GLint binding = 0;
    glGetBooleanv(target, &enabled);
    json.beginMember(enumToString(target));
    dumpBoolean(json, enabled);
    json.endMember();
    glGetIntegerv(binding_param, &binding);
    json.writeIntMember(enumToString(binding_param), binding);
    if (enabled || binding) {
        json.beginMember(enumToString(target));
        json.beginObject();
        dumpObjectLabel(json, context, GL_TEXTURE, binding, "GL_TEXTURE_LABEL");
        // GL_TEXTURE_BORDER_COLOR
        {
            flushErrors();
    GLfloat texture_border_color[4 + 1];
    memset(texture_border_color, 0, 4 * sizeof *texture_border_color);
    texture_border_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, texture_border_color);
    }
    assert(texture_border_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BORDER_COLOR");
    json.beginArray();
    for (unsigned _i0 = 0; _i0 < 4; ++_i0) {
    json.writeFloat(texture_border_color[_i0]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_MAG_FILTER
        {
            flushErrors();
    GLint texture_mag_filter = 0;
    glGetTexParameteriv(target, GL_TEXTURE_MAG_FILTER, &texture_mag_filter);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAG_FILTER");
    dumpEnum(json, texture_mag_filter);
                json.endMember();
            }
        }

        // GL_TEXTURE_MIN_FILTER
        {
            flushErrors();
    GLint texture_min_filter = 0;
    glGetTexParameteriv(target, GL_TEXTURE_MIN_FILTER, &texture_min_filter);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MIN_FILTER");
    dumpEnum(json, texture_min_filter);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_S
        {
            flushErrors();
    GLint texture_wrap_s = 0;
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_S, &texture_wrap_s);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_S");
    dumpEnum(json, texture_wrap_s);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_T
        {
            flushErrors();
    GLint texture_wrap_t = 0;
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_T, &texture_wrap_t);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_T");
    dumpEnum(json, texture_wrap_t);
                json.endMember();
            }
        }

        // GL_TEXTURE_PRIORITY
        {
            flushErrors();
    GLfloat texture_priority = 0;
    glGetTexParameterfv(target, GL_TEXTURE_PRIORITY, &texture_priority);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_PRIORITY");
    json.writeFloat(texture_priority);
                json.endMember();
            }
        }

        // GL_TEXTURE_RESIDENT
        {
            flushErrors();
    GLint texture_resident = 0;
    glGetTexParameteriv(target, GL_TEXTURE_RESIDENT, &texture_resident);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_RESIDENT");
    dumpBoolean(json, texture_resident);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_R
        {
            flushErrors();
    GLint texture_wrap_r = 0;
    glGetTexParameteriv(target, GL_TEXTURE_WRAP_R, &texture_wrap_r);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_R");
    dumpEnum(json, texture_wrap_r);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_FAIL_VALUE_ARB
        {
            flushErrors();
    GLfloat texture_compare_fail_value_arb = 0;
    glGetTexParameterfv(target, GL_TEXTURE_COMPARE_FAIL_VALUE_ARB, &texture_compare_fail_value_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_FAIL_VALUE_ARB");
    json.writeFloat(texture_compare_fail_value_arb);
                json.endMember();
            }
        }

        // GL_TEXTURE_MIN_LOD
        {
            flushErrors();
    GLfloat texture_min_lod = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MIN_LOD, &texture_min_lod);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MIN_LOD");
    json.writeFloat(texture_min_lod);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_LOD
        {
            flushErrors();
    GLfloat texture_max_lod = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_LOD, &texture_max_lod);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_LOD");
    json.writeFloat(texture_max_lod);
                json.endMember();
            }
        }

        // GL_TEXTURE_BASE_LEVEL
        {
            flushErrors();
    GLfloat texture_base_level = 0;
    glGetTexParameterfv(target, GL_TEXTURE_BASE_LEVEL, &texture_base_level);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BASE_LEVEL");
    json.writeFloat(texture_base_level);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_LEVEL
        {
            flushErrors();
    GLfloat texture_max_level = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_LEVEL, &texture_max_level);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_LEVEL");
    json.writeFloat(texture_max_level);
                json.endMember();
            }
        }

        // GL_TEXTURE_CLIPMAP_CENTER_SGIX
        {
            flushErrors();
    GLint texture_clipmap_center_sgix[2 + 1];
    memset(texture_clipmap_center_sgix, 0, 2 * sizeof *texture_clipmap_center_sgix);
    texture_clipmap_center_sgix[2] = (GLint)0xdeadc0de;
    if (2) {
        glGetTexParameteriv(target, GL_TEXTURE_CLIPMAP_CENTER_SGIX, texture_clipmap_center_sgix);
    }
    assert(texture_clipmap_center_sgix[2] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CLIPMAP_CENTER_SGIX");
    json.beginArray();
    for (unsigned _i1 = 0; _i1 < 2; ++_i1) {
    json.writeInt(texture_clipmap_center_sgix[_i1]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_CLIPMAP_FRAME_SGIX
        {
            flushErrors();
    GLfloat texture_clipmap_frame_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_CLIPMAP_FRAME_SGIX, &texture_clipmap_frame_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CLIPMAP_FRAME_SGIX");
    json.writeFloat(texture_clipmap_frame_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_CLIPMAP_OFFSET_SGIX
        {
            flushErrors();
    GLint texture_clipmap_offset_sgix[2 + 1];
    memset(texture_clipmap_offset_sgix, 0, 2 * sizeof *texture_clipmap_offset_sgix);
    texture_clipmap_offset_sgix[2] = (GLint)0xdeadc0de;
    if (2) {
        glGetTexParameteriv(target, GL_TEXTURE_CLIPMAP_OFFSET_SGIX, texture_clipmap_offset_sgix);
    }
    assert(texture_clipmap_offset_sgix[2] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CLIPMAP_OFFSET_SGIX");
    json.beginArray();
    for (unsigned _i2 = 0; _i2 < 2; ++_i2) {
    json.writeInt(texture_clipmap_offset_sgix[_i2]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX
        {
            flushErrors();
    GLint texture_clipmap_virtual_depth_sgix[3 + 1];
    memset(texture_clipmap_virtual_depth_sgix, 0, 3 * sizeof *texture_clipmap_virtual_depth_sgix);
    texture_clipmap_virtual_depth_sgix[3] = (GLint)0xdeadc0de;
    if (3) {
        glGetTexParameteriv(target, GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX, texture_clipmap_virtual_depth_sgix);
    }
    assert(texture_clipmap_virtual_depth_sgix[3] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CLIPMAP_VIRTUAL_DEPTH_SGIX");
    json.beginArray();
    for (unsigned _i3 = 0; _i3 < 3; ++_i3) {
    json.writeInt(texture_clipmap_virtual_depth_sgix[_i3]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_POST_TEXTURE_FILTER_BIAS_SGIX
        {
            flushErrors();
    GLfloat post_texture_filter_bias_sgix = 0;
    glGetTexParameterfv(target, GL_POST_TEXTURE_FILTER_BIAS_SGIX, &post_texture_filter_bias_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_TEXTURE_FILTER_BIAS_SGIX");
    json.writeFloat(post_texture_filter_bias_sgix);
                json.endMember();
            }
        }

        // GL_POST_TEXTURE_FILTER_SCALE_SGIX
        {
            flushErrors();
    GLfloat post_texture_filter_scale_sgix = 0;
    glGetTexParameterfv(target, GL_POST_TEXTURE_FILTER_SCALE_SGIX, &post_texture_filter_scale_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_TEXTURE_FILTER_SCALE_SGIX");
    json.writeFloat(post_texture_filter_scale_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_LOD_BIAS_S_SGIX
        {
            flushErrors();
    GLfloat texture_lod_bias_s_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_LOD_BIAS_S_SGIX, &texture_lod_bias_s_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LOD_BIAS_S_SGIX");
    json.writeFloat(texture_lod_bias_s_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_LOD_BIAS_T_SGIX
        {
            flushErrors();
    GLfloat texture_lod_bias_t_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_LOD_BIAS_T_SGIX, &texture_lod_bias_t_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LOD_BIAS_T_SGIX");
    json.writeFloat(texture_lod_bias_t_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_LOD_BIAS_R_SGIX
        {
            flushErrors();
    GLfloat texture_lod_bias_r_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_LOD_BIAS_R_SGIX, &texture_lod_bias_r_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LOD_BIAS_R_SGIX");
    json.writeFloat(texture_lod_bias_r_sgix);
                json.endMember();
            }
        }

        // GL_GENERATE_MIPMAP
        {
            flushErrors();
    GLint generate_mipmap = 0;
    glGetTexParameteriv(target, GL_GENERATE_MIPMAP, &generate_mipmap);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GENERATE_MIPMAP");
    dumpBoolean(json, generate_mipmap);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_SGIX
        {
            flushErrors();
    GLint texture_compare_sgix = 0;
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_SGIX, &texture_compare_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_SGIX");
    dumpBoolean(json, texture_compare_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_OPERATOR_SGIX
        {
            flushErrors();
    GLint texture_compare_operator_sgix = 0;
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_OPERATOR_SGIX, &texture_compare_operator_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_OPERATOR_SGIX");
    dumpEnum(json, texture_compare_operator_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_VIEW_MIN_LEVEL
        {
            flushErrors();
    GLint texture_view_min_level = 0;
    glGetTexParameteriv(target, GL_TEXTURE_VIEW_MIN_LEVEL, &texture_view_min_level);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_VIEW_MIN_LEVEL");
    json.writeInt(texture_view_min_level);
                json.endMember();
            }
        }

        // GL_TEXTURE_VIEW_NUM_LEVELS
        {
            flushErrors();
    GLint texture_view_num_levels = 0;
    glGetTexParameteriv(target, GL_TEXTURE_VIEW_NUM_LEVELS, &texture_view_num_levels);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_VIEW_NUM_LEVELS");
    json.writeInt(texture_view_num_levels);
                json.endMember();
            }
        }

        // GL_TEXTURE_VIEW_MIN_LAYER
        {
            flushErrors();
    GLint texture_view_min_layer = 0;
    glGetTexParameteriv(target, GL_TEXTURE_VIEW_MIN_LAYER, &texture_view_min_layer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_VIEW_MIN_LAYER");
    json.writeInt(texture_view_min_layer);
                json.endMember();
            }
        }

        // GL_TEXTURE_VIEW_NUM_LAYERS
        {
            flushErrors();
    GLint texture_view_num_layers = 0;
    glGetTexParameteriv(target, GL_TEXTURE_VIEW_NUM_LAYERS, &texture_view_num_layers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_VIEW_NUM_LAYERS");
    json.writeInt(texture_view_num_layers);
                json.endMember();
            }
        }

        // GL_TEXTURE_IMMUTABLE_LEVELS
        {
            flushErrors();
    GLint texture_immutable_levels = 0;
    glGetTexParameteriv(target, GL_TEXTURE_IMMUTABLE_LEVELS, &texture_immutable_levels);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_IMMUTABLE_LEVELS");
    json.writeInt(texture_immutable_levels);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_CLAMP_S_SGIX
        {
            flushErrors();
    GLfloat texture_max_clamp_s_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_CLAMP_S_SGIX, &texture_max_clamp_s_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_CLAMP_S_SGIX");
    json.writeFloat(texture_max_clamp_s_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_CLAMP_T_SGIX
        {
            flushErrors();
    GLfloat texture_max_clamp_t_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_CLAMP_T_SGIX, &texture_max_clamp_t_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_CLAMP_T_SGIX");
    json.writeFloat(texture_max_clamp_t_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_CLAMP_R_SGIX
        {
            flushErrors();
    GLfloat texture_max_clamp_r_sgix = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_CLAMP_R_SGIX, &texture_max_clamp_r_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_CLAMP_R_SGIX");
    json.writeFloat(texture_max_clamp_r_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_ANISOTROPY_EXT
        {
            flushErrors();
    GLfloat texture_max_anisotropy_ext = 0;
    glGetTexParameterfv(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, &texture_max_anisotropy_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_ANISOTROPY_EXT");
    json.writeFloat(texture_max_anisotropy_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_LOD_BIAS
        {
            flushErrors();
    GLfloat texture_lod_bias = 0;
    glGetTexParameterfv(target, GL_TEXTURE_LOD_BIAS, &texture_lod_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LOD_BIAS");
    json.writeFloat(texture_lod_bias);
                json.endMember();
            }
        }

        // GL_TEXTURE_STORAGE_HINT_APPLE
        {
            flushErrors();
    GLint texture_storage_hint_apple = 0;
    glGetTexParameteriv(target, GL_TEXTURE_STORAGE_HINT_APPLE, &texture_storage_hint_apple);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_STORAGE_HINT_APPLE");
    dumpEnum(json, texture_storage_hint_apple);
                json.endMember();
            }
        }

        // GL_DEPTH_TEXTURE_MODE
        {
            flushErrors();
    GLint depth_texture_mode = 0;
    glGetTexParameteriv(target, GL_DEPTH_TEXTURE_MODE, &depth_texture_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_TEXTURE_MODE");
    dumpEnum(json, depth_texture_mode);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_MODE
        {
            flushErrors();
    GLint texture_compare_mode = 0;
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_MODE, &texture_compare_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_MODE");
    dumpEnum(json, texture_compare_mode);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_FUNC
        {
            flushErrors();
    GLint texture_compare_func = 0;
    glGetTexParameteriv(target, GL_TEXTURE_COMPARE_FUNC, &texture_compare_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_FUNC");
    dumpEnum(json, texture_compare_func);
                json.endMember();
            }
        }

        // GL_TEXTURE_UNSIGNED_REMAP_MODE_NV
        {
            flushErrors();
    GLint texture_unsigned_remap_mode_nv = 0;
    glGetTexParameteriv(target, GL_TEXTURE_UNSIGNED_REMAP_MODE_NV, &texture_unsigned_remap_mode_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_UNSIGNED_REMAP_MODE_NV");
    dumpEnum(json, texture_unsigned_remap_mode_nv);
                json.endMember();
            }
        }

        // GL_TEXTURE_SRGB_DECODE_EXT
        {
            flushErrors();
    GLint texture_srgb_decode_ext = 0;
    glGetTexParameteriv(target, GL_TEXTURE_SRGB_DECODE_EXT, &texture_srgb_decode_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SRGB_DECODE_EXT");
    dumpEnum(json, texture_srgb_decode_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_CROP_RECT_OES
        {
            flushErrors();
    GLint texture_crop_rect_oes[4 + 1];
    memset(texture_crop_rect_oes, 0, 4 * sizeof *texture_crop_rect_oes);
    texture_crop_rect_oes[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetTexParameteriv(target, GL_TEXTURE_CROP_RECT_OES, texture_crop_rect_oes);
    }
    assert(texture_crop_rect_oes[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CROP_RECT_OES");
    json.beginArray();
    for (unsigned _i4 = 0; _i4 < 4; ++_i4) {
    json.writeInt(texture_crop_rect_oes[_i4]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_R
        {
            flushErrors();
    GLint texture_swizzle_r = 0;
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_R, &texture_swizzle_r);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SWIZZLE_R");
    dumpEnum(json, texture_swizzle_r);
                json.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_G
        {
            flushErrors();
    GLint texture_swizzle_g = 0;
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_G, &texture_swizzle_g);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SWIZZLE_G");
    dumpEnum(json, texture_swizzle_g);
                json.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_B
        {
            flushErrors();
    GLint texture_swizzle_b = 0;
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_B, &texture_swizzle_b);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SWIZZLE_B");
    dumpEnum(json, texture_swizzle_b);
                json.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_A
        {
            flushErrors();
    GLint texture_swizzle_a = 0;
    glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_A, &texture_swizzle_a);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SWIZZLE_A");
    dumpEnum(json, texture_swizzle_a);
                json.endMember();
            }
        }

        // GL_TEXTURE_SWIZZLE_RGBA
        {
            flushErrors();
    GLint texture_swizzle_rgba[4 + 1];
    memset(texture_swizzle_rgba, 0, 4 * sizeof *texture_swizzle_rgba);
    texture_swizzle_rgba[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, texture_swizzle_rgba);
    }
    assert(texture_swizzle_rgba[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SWIZZLE_RGBA");
    json.beginArray();
    for (unsigned _i5 = 0; _i5 < 4; ++_i5) {
    dumpEnum(json, texture_swizzle_rgba[_i5]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DEPTH_STENCIL_TEXTURE_MODE
        {
            flushErrors();
    GLint depth_stencil_texture_mode = 0;
    glGetTexParameteriv(target, GL_DEPTH_STENCIL_TEXTURE_MODE, &depth_stencil_texture_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_STENCIL_TEXTURE_MODE");
    dumpEnum(json, depth_stencil_texture_mode);
                json.endMember();
            }
        }

        // GL_TEXTURE_IMMUTABLE_FORMAT
        {
            flushErrors();
    GLint texture_immutable_format = 0;
    glGetTexParameteriv(target, GL_TEXTURE_IMMUTABLE_FORMAT, &texture_immutable_format);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_IMMUTABLE_FORMAT");
    dumpBoolean(json, texture_immutable_format);
                json.endMember();
            }
        }

        if (!context.ES) {
            GLenum levelTarget;
            if (target == GL_TEXTURE_CUBE_MAP ||
                target == GL_TEXTURE_CUBE_MAP_ARRAY) {
                // Must pick a face
                levelTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
            } else {
                levelTarget = target;
            }
        // GL_TEXTURE_WIDTH
        {
            flushErrors();
    GLint texture_width = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_WIDTH, &texture_width);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WIDTH");
    json.writeInt(texture_width);
                json.endMember();
            }
        }

        // GL_TEXTURE_HEIGHT
        {
            flushErrors();
    GLint texture_height = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_HEIGHT, &texture_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_HEIGHT");
    json.writeInt(texture_height);
                json.endMember();
            }
        }

        // GL_TEXTURE_INTERNAL_FORMAT
        {
            flushErrors();
    GLint texture_internal_format = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_INTERNAL_FORMAT, &texture_internal_format);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_INTERNAL_FORMAT");
    dumpEnum(json, texture_internal_format);
                json.endMember();
            }
        }

        // GL_TEXTURE_BORDER
        {
            flushErrors();
    GLint texture_border = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_BORDER, &texture_border);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BORDER");
    json.writeInt(texture_border);
                json.endMember();
            }
        }

        // GL_TEXTURE_RED_SIZE
        {
            flushErrors();
    GLint texture_red_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_RED_SIZE, &texture_red_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_RED_SIZE");
    json.writeInt(texture_red_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_GREEN_SIZE
        {
            flushErrors();
    GLint texture_green_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_GREEN_SIZE, &texture_green_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GREEN_SIZE");
    json.writeInt(texture_green_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_BLUE_SIZE
        {
            flushErrors();
    GLint texture_blue_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_BLUE_SIZE, &texture_blue_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BLUE_SIZE");
    json.writeInt(texture_blue_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_ALPHA_SIZE
        {
            flushErrors();
    GLint texture_alpha_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_ALPHA_SIZE, &texture_alpha_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_ALPHA_SIZE");
    json.writeInt(texture_alpha_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_LUMINANCE_SIZE
        {
            flushErrors();
    GLint texture_luminance_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_LUMINANCE_SIZE, &texture_luminance_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LUMINANCE_SIZE");
    json.writeInt(texture_luminance_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_INTENSITY_SIZE
        {
            flushErrors();
    GLint texture_intensity_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_INTENSITY_SIZE, &texture_intensity_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_INTENSITY_SIZE");
    json.writeInt(texture_intensity_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_DEPTH
        {
            flushErrors();
    GLint texture_depth = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_DEPTH, &texture_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_DEPTH");
    json.writeInt(texture_depth);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPRESSED_IMAGE_SIZE
        {
            flushErrors();
    GLint texture_compressed_image_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &texture_compressed_image_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPRESSED_IMAGE_SIZE");
    json.writeInt(texture_compressed_image_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPRESSED
        {
            flushErrors();
    GLint texture_compressed = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_COMPRESSED, &texture_compressed);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPRESSED");
    dumpBoolean(json, texture_compressed);
                json.endMember();
            }
        }

        // GL_TEXTURE_DEPTH_SIZE
        {
            flushErrors();
    GLint texture_depth_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_DEPTH_SIZE, &texture_depth_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_DEPTH_SIZE");
    json.writeInt(texture_depth_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_STENCIL_SIZE
        {
            flushErrors();
    GLint texture_stencil_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_STENCIL_SIZE, &texture_stencil_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_STENCIL_SIZE");
    json.writeInt(texture_stencil_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_RED_TYPE
        {
            flushErrors();
    GLint texture_red_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_RED_TYPE, &texture_red_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_RED_TYPE");
    dumpEnum(json, texture_red_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_GREEN_TYPE
        {
            flushErrors();
    GLint texture_green_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_GREEN_TYPE, &texture_green_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GREEN_TYPE");
    dumpEnum(json, texture_green_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_BLUE_TYPE
        {
            flushErrors();
    GLint texture_blue_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_BLUE_TYPE, &texture_blue_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BLUE_TYPE");
    dumpEnum(json, texture_blue_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_ALPHA_TYPE
        {
            flushErrors();
    GLint texture_alpha_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_ALPHA_TYPE, &texture_alpha_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_ALPHA_TYPE");
    dumpEnum(json, texture_alpha_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_LUMINANCE_TYPE
        {
            flushErrors();
    GLint texture_luminance_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_LUMINANCE_TYPE, &texture_luminance_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LUMINANCE_TYPE");
    dumpEnum(json, texture_luminance_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_INTENSITY_TYPE
        {
            flushErrors();
    GLint texture_intensity_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_INTENSITY_TYPE, &texture_intensity_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_INTENSITY_TYPE");
    dumpEnum(json, texture_intensity_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_DEPTH_TYPE
        {
            flushErrors();
    GLint texture_depth_type = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_DEPTH_TYPE, &texture_depth_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_DEPTH_TYPE");
    dumpEnum(json, texture_depth_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_SAMPLES
        {
            flushErrors();
    GLint texture_samples = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_SAMPLES, &texture_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_SAMPLES");
    json.writeInt(texture_samples);
                json.endMember();
            }
        }

        // GL_TEXTURE_FIXED_SAMPLE_LOCATIONS
        {
            flushErrors();
    GLint texture_fixed_sample_locations = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_FIXED_SAMPLE_LOCATIONS, &texture_fixed_sample_locations);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_FIXED_SAMPLE_LOCATIONS");
    dumpBoolean(json, texture_fixed_sample_locations);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER_OFFSET
        {
            flushErrors();
    GLint texture_buffer_offset = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_BUFFER_OFFSET, &texture_buffer_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER_OFFSET");
    json.writeInt(texture_buffer_offset);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER_SIZE
        {
            flushErrors();
    GLint texture_buffer_size = 0;
    glGetTexLevelParameteriv(levelTarget, 0, GL_TEXTURE_BUFFER_SIZE, &texture_buffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER_SIZE");
    json.writeInt(texture_buffer_size);
                json.endMember();
            }
        }

        }
        json.endObject();
        json.endMember(); // target
    }
}

static void
dumpFramebufferAttachementParameters(JSONWriter &json, Context &context, GLenum target, GLenum attachment)
{
            {
                GLint object_type = GL_NONE;
                glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &object_type);
                if (object_type != GL_NONE) {
                    json.beginMember(enumToString(attachment));
                    json.beginObject();
        // GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING
        {
            flushErrors();
    GLint framebuffer_attachment_color_encoding = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, &framebuffer_attachment_color_encoding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING");
    dumpEnum(json, framebuffer_attachment_color_encoding);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE
        {
            flushErrors();
    GLint framebuffer_attachment_component_type = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE, &framebuffer_attachment_component_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE");
    dumpEnum(json, framebuffer_attachment_component_type);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_red_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &framebuffer_attachment_red_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE");
    json.writeInt(framebuffer_attachment_red_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_green_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &framebuffer_attachment_green_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE");
    json.writeInt(framebuffer_attachment_green_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_blue_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &framebuffer_attachment_blue_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE");
    json.writeInt(framebuffer_attachment_blue_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_alpha_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &framebuffer_attachment_alpha_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE");
    json.writeInt(framebuffer_attachment_alpha_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_depth_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &framebuffer_attachment_depth_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE");
    json.writeInt(framebuffer_attachment_depth_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE
        {
            flushErrors();
    GLint framebuffer_attachment_stencil_size = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &framebuffer_attachment_stencil_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE");
    json.writeInt(framebuffer_attachment_stencil_size);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
        {
            flushErrors();
    GLint framebuffer_attachment_object_type = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &framebuffer_attachment_object_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE");
    dumpEnum(json, framebuffer_attachment_object_type);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
        {
            flushErrors();
    GLint framebuffer_attachment_object_name = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &framebuffer_attachment_object_name);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME");
    json.writeInt(framebuffer_attachment_object_name);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL
        {
            flushErrors();
    GLint framebuffer_attachment_texture_level = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, &framebuffer_attachment_texture_level);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL");
    json.writeInt(framebuffer_attachment_texture_level);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE
        {
            flushErrors();
    GLint framebuffer_attachment_texture_cube_map_face = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, &framebuffer_attachment_texture_cube_map_face);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE");
    dumpEnum(json, framebuffer_attachment_texture_cube_map_face);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER
        {
            flushErrors();
    GLint framebuffer_attachment_texture_layer = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &framebuffer_attachment_texture_layer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER");
    json.writeInt(framebuffer_attachment_texture_layer);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_ATTACHMENT_LAYERED
        {
            flushErrors();
    GLint framebuffer_attachment_layered = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_LAYERED, &framebuffer_attachment_layered);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_ATTACHMENT_LAYERED");
    dumpBoolean(json, framebuffer_attachment_layered);
                json.endMember();
            }
        }

                    GLint object_name = 0;
                    glGetFramebufferAttachmentParameteriv(target, attachment, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &object_name);
                    dumpObjectLabel(json, context, object_type, object_name, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_LABEL");
                    json.endObject();
                    json.endMember(); // GL_x_ATTACHMENT
                }
            }
}

void dumpParameters(JSONWriter &json, Context &context)
{
    ScopedAllocator _allocator;
    (void)_allocator;

    json.beginMember("parameters");
    json.beginObject();
        // GL_CURRENT_COLOR
        {
            flushErrors();
    GLfloat current_color[4 + 1];
    memset(current_color, 0, 4 * sizeof *current_color);
    current_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_COLOR, current_color);
    }
    assert(current_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_COLOR");
    json.beginArray();
    for (unsigned _i6 = 0; _i6 < 4; ++_i6) {
    json.writeFloat(current_color[_i6]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_INDEX
        {
            flushErrors();
    GLfloat current_index = 0;
    glGetFloatv(GL_CURRENT_INDEX, &current_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_INDEX");
    json.writeFloat(current_index);
                json.endMember();
            }
        }

        // GL_CURRENT_NORMAL
        {
            flushErrors();
    GLfloat current_normal[3 + 1];
    memset(current_normal, 0, 3 * sizeof *current_normal);
    current_normal[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetFloatv(GL_CURRENT_NORMAL, current_normal);
    }
    assert(current_normal[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_NORMAL");
    json.beginArray();
    for (unsigned _i7 = 0; _i7 < 3; ++_i7) {
    json.writeFloat(current_normal[_i7]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_TEXTURE_COORDS
        {
            flushErrors();
    GLfloat current_texture_coords[4 + 1];
    memset(current_texture_coords, 0, 4 * sizeof *current_texture_coords);
    current_texture_coords[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_TEXTURE_COORDS, current_texture_coords);
    }
    assert(current_texture_coords[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_TEXTURE_COORDS");
    json.beginArray();
    for (unsigned _i8 = 0; _i8 < 4; ++_i8) {
    json.writeFloat(current_texture_coords[_i8]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_COLOR
        {
            flushErrors();
    GLfloat current_raster_color[4 + 1];
    memset(current_raster_color, 0, 4 * sizeof *current_raster_color);
    current_raster_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_RASTER_COLOR, current_raster_color);
    }
    assert(current_raster_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_COLOR");
    json.beginArray();
    for (unsigned _i9 = 0; _i9 < 4; ++_i9) {
    json.writeFloat(current_raster_color[_i9]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_INDEX
        {
            flushErrors();
    GLfloat current_raster_index = 0;
    glGetFloatv(GL_CURRENT_RASTER_INDEX, &current_raster_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_INDEX");
    json.writeFloat(current_raster_index);
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_TEXTURE_COORDS
        {
            flushErrors();
    GLfloat current_raster_texture_coords[4 + 1];
    memset(current_raster_texture_coords, 0, 4 * sizeof *current_raster_texture_coords);
    current_raster_texture_coords[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_RASTER_TEXTURE_COORDS, current_raster_texture_coords);
    }
    assert(current_raster_texture_coords[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_TEXTURE_COORDS");
    json.beginArray();
    for (unsigned _i10 = 0; _i10 < 4; ++_i10) {
    json.writeFloat(current_raster_texture_coords[_i10]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_POSITION
        {
            flushErrors();
    GLfloat current_raster_position[4 + 1];
    memset(current_raster_position, 0, 4 * sizeof *current_raster_position);
    current_raster_position[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_RASTER_POSITION, current_raster_position);
    }
    assert(current_raster_position[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_POSITION");
    json.beginArray();
    for (unsigned _i11 = 0; _i11 < 4; ++_i11) {
    json.writeFloat(current_raster_position[_i11]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_POSITION_VALID
        {
            flushErrors();
    GLint current_raster_position_valid = 0;
    glGetIntegerv(GL_CURRENT_RASTER_POSITION_VALID, &current_raster_position_valid);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_POSITION_VALID");
    json.writeInt(current_raster_position_valid);
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_DISTANCE
        {
            flushErrors();
    GLfloat current_raster_distance = 0;
    glGetFloatv(GL_CURRENT_RASTER_DISTANCE, &current_raster_distance);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_DISTANCE");
    json.writeFloat(current_raster_distance);
                json.endMember();
            }
        }

        // GL_POINT_SMOOTH
        {
            flushErrors();
    GLboolean point_smooth = 0;
    glGetBooleanv(GL_POINT_SMOOTH, &point_smooth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SMOOTH");
    dumpBoolean(json, point_smooth);
                json.endMember();
            }
        }

        // GL_POINT_SIZE
        {
            flushErrors();
    GLfloat point_size = 0;
    glGetFloatv(GL_POINT_SIZE, &point_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SIZE");
    json.writeFloat(point_size);
                json.endMember();
            }
        }

        // GL_POINT_SIZE_RANGE
        {
            flushErrors();
    GLfloat point_size_range[2 + 1];
    memset(point_size_range, 0, 2 * sizeof *point_size_range);
    point_size_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_POINT_SIZE_RANGE, point_size_range);
    }
    assert(point_size_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SIZE_RANGE");
    json.beginArray();
    for (unsigned _i12 = 0; _i12 < 2; ++_i12) {
    json.writeFloat(point_size_range[_i12]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_POINT_SIZE_GRANULARITY
        {
            flushErrors();
    GLfloat point_size_granularity = 0;
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &point_size_granularity);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SIZE_GRANULARITY");
    json.writeFloat(point_size_granularity);
                json.endMember();
            }
        }

        // GL_LINE_SMOOTH
        {
            flushErrors();
    GLboolean line_smooth = 0;
    glGetBooleanv(GL_LINE_SMOOTH, &line_smooth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_SMOOTH");
    dumpBoolean(json, line_smooth);
                json.endMember();
            }
        }

        // GL_LINE_WIDTH
        {
            flushErrors();
    GLfloat line_width = 0;
    glGetFloatv(GL_LINE_WIDTH, &line_width);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_WIDTH");
    json.writeFloat(line_width);
                json.endMember();
            }
        }

        // GL_LINE_WIDTH_RANGE
        {
            flushErrors();
    GLfloat line_width_range[2 + 1];
    memset(line_width_range, 0, 2 * sizeof *line_width_range);
    line_width_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_LINE_WIDTH_RANGE, line_width_range);
    }
    assert(line_width_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_WIDTH_RANGE");
    json.beginArray();
    for (unsigned _i13 = 0; _i13 < 2; ++_i13) {
    json.writeFloat(line_width_range[_i13]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_LINE_WIDTH_GRANULARITY
        {
            flushErrors();
    GLfloat line_width_granularity = 0;
    glGetFloatv(GL_LINE_WIDTH_GRANULARITY, &line_width_granularity);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_WIDTH_GRANULARITY");
    json.writeFloat(line_width_granularity);
                json.endMember();
            }
        }

        // GL_LINE_STIPPLE
        {
            flushErrors();
    GLboolean line_stipple = 0;
    glGetBooleanv(GL_LINE_STIPPLE, &line_stipple);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_STIPPLE");
    dumpBoolean(json, line_stipple);
                json.endMember();
            }
        }

        // GL_LINE_STIPPLE_PATTERN
        {
            flushErrors();
    GLint line_stipple_pattern = 0;
    glGetIntegerv(GL_LINE_STIPPLE_PATTERN, &line_stipple_pattern);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_STIPPLE_PATTERN");
    json.writeInt(line_stipple_pattern);
                json.endMember();
            }
        }

        // GL_LINE_STIPPLE_REPEAT
        {
            flushErrors();
    GLint line_stipple_repeat = 0;
    glGetIntegerv(GL_LINE_STIPPLE_REPEAT, &line_stipple_repeat);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_STIPPLE_REPEAT");
    json.writeInt(line_stipple_repeat);
                json.endMember();
            }
        }

        // GL_LIST_MODE
        {
            flushErrors();
    GLint list_mode = 0;
    glGetIntegerv(GL_LIST_MODE, &list_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIST_MODE");
    dumpEnum(json, list_mode);
                json.endMember();
            }
        }

        // GL_MAX_LIST_NESTING
        {
            flushErrors();
    GLint max_list_nesting = 0;
    glGetIntegerv(GL_MAX_LIST_NESTING, &max_list_nesting);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_LIST_NESTING");
    json.writeInt(max_list_nesting);
                json.endMember();
            }
        }

        // GL_LIST_BASE
        {
            flushErrors();
    GLint list_base = 0;
    glGetIntegerv(GL_LIST_BASE, &list_base);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIST_BASE");
    json.writeInt(list_base);
                json.endMember();
            }
        }

        // GL_LIST_INDEX
        {
            flushErrors();
    GLint list_index = 0;
    glGetIntegerv(GL_LIST_INDEX, &list_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIST_INDEX");
    json.writeInt(list_index);
                json.endMember();
            }
        }

        // GL_POLYGON_MODE
        {
            flushErrors();
    GLint polygon_mode[2 + 1];
    memset(polygon_mode, 0, 2 * sizeof *polygon_mode);
    polygon_mode[2] = (GLint)0xdeadc0de;
    if (2) {
        glGetIntegerv(GL_POLYGON_MODE, polygon_mode);
    }
    assert(polygon_mode[2] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_MODE");
    json.beginArray();
    for (unsigned _i14 = 0; _i14 < 2; ++_i14) {
    dumpEnum(json, polygon_mode[_i14]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_POLYGON_SMOOTH
        {
            flushErrors();
    GLboolean polygon_smooth = 0;
    glGetBooleanv(GL_POLYGON_SMOOTH, &polygon_smooth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_SMOOTH");
    dumpBoolean(json, polygon_smooth);
                json.endMember();
            }
        }

        // GL_POLYGON_STIPPLE
        {
            flushErrors();
    GLboolean polygon_stipple = 0;
    glGetBooleanv(GL_POLYGON_STIPPLE, &polygon_stipple);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_STIPPLE");
    dumpBoolean(json, polygon_stipple);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG
        {
            flushErrors();
    GLboolean edge_flag = 0;
    glGetBooleanv(GL_EDGE_FLAG, &edge_flag);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG");
    dumpBoolean(json, edge_flag);
                json.endMember();
            }
        }

        // GL_CULL_FACE
        {
            flushErrors();
    GLboolean cull_face = 0;
    glGetBooleanv(GL_CULL_FACE, &cull_face);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_FACE");
    dumpBoolean(json, cull_face);
                json.endMember();
            }
        }

        // GL_CULL_FACE_MODE
        {
            flushErrors();
    GLint cull_face_mode = 0;
    glGetIntegerv(GL_CULL_FACE_MODE, &cull_face_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_FACE_MODE");
    dumpEnum(json, cull_face_mode);
                json.endMember();
            }
        }

        // GL_FRONT_FACE
        {
            flushErrors();
    GLint front_face = 0;
    glGetIntegerv(GL_FRONT_FACE, &front_face);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRONT_FACE");
    dumpEnum(json, front_face);
                json.endMember();
            }
        }

        // GL_LIGHTING
        {
            flushErrors();
    GLboolean lighting = 0;
    glGetBooleanv(GL_LIGHTING, &lighting);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHTING");
    dumpBoolean(json, lighting);
                json.endMember();
            }
        }

        // GL_LIGHT_MODEL_LOCAL_VIEWER
        {
            flushErrors();
    GLboolean light_model_local_viewer = 0;
    glGetBooleanv(GL_LIGHT_MODEL_LOCAL_VIEWER, &light_model_local_viewer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHT_MODEL_LOCAL_VIEWER");
    dumpBoolean(json, light_model_local_viewer);
                json.endMember();
            }
        }

        // GL_LIGHT_MODEL_TWO_SIDE
        {
            flushErrors();
    GLboolean light_model_two_side = 0;
    glGetBooleanv(GL_LIGHT_MODEL_TWO_SIDE, &light_model_two_side);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHT_MODEL_TWO_SIDE");
    dumpBoolean(json, light_model_two_side);
                json.endMember();
            }
        }

        // GL_LIGHT_MODEL_AMBIENT
        {
            flushErrors();
    GLfloat light_model_ambient[4 + 1];
    memset(light_model_ambient, 0, 4 * sizeof *light_model_ambient);
    light_model_ambient[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);
    }
    assert(light_model_ambient[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHT_MODEL_AMBIENT");
    json.beginArray();
    for (unsigned _i15 = 0; _i15 < 4; ++_i15) {
    json.writeFloat(light_model_ambient[_i15]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SHADE_MODEL
        {
            flushErrors();
    GLint shade_model = 0;
    glGetIntegerv(GL_SHADE_MODEL, &shade_model);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHADE_MODEL");
    dumpEnum(json, shade_model);
                json.endMember();
            }
        }

        // GL_COLOR_MATERIAL_FACE
        {
            flushErrors();
    GLint color_material_face = 0;
    glGetIntegerv(GL_COLOR_MATERIAL_FACE, &color_material_face);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_MATERIAL_FACE");
    dumpEnum(json, color_material_face);
                json.endMember();
            }
        }

        // GL_COLOR_MATERIAL_PARAMETER
        {
            flushErrors();
    GLint color_material_parameter = 0;
    glGetIntegerv(GL_COLOR_MATERIAL_PARAMETER, &color_material_parameter);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_MATERIAL_PARAMETER");
    dumpEnum(json, color_material_parameter);
                json.endMember();
            }
        }

        // GL_COLOR_MATERIAL
        {
            flushErrors();
    GLboolean color_material = 0;
    glGetBooleanv(GL_COLOR_MATERIAL, &color_material);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_MATERIAL");
    dumpBoolean(json, color_material);
                json.endMember();
            }
        }

        // GL_FOG
        {
            flushErrors();
    GLboolean fog = 0;
    glGetBooleanv(GL_FOG, &fog);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG");
    dumpBoolean(json, fog);
                json.endMember();
            }
        }

        // GL_FOG_INDEX
        {
            flushErrors();
    GLint fog_index = 0;
    glGetIntegerv(GL_FOG_INDEX, &fog_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_INDEX");
    json.writeInt(fog_index);
                json.endMember();
            }
        }

        // GL_FOG_DENSITY
        {
            flushErrors();
    GLfloat fog_density = 0;
    glGetFloatv(GL_FOG_DENSITY, &fog_density);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_DENSITY");
    json.writeFloat(fog_density);
                json.endMember();
            }
        }

        // GL_FOG_START
        {
            flushErrors();
    GLfloat fog_start = 0;
    glGetFloatv(GL_FOG_START, &fog_start);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_START");
    json.writeFloat(fog_start);
                json.endMember();
            }
        }

        // GL_FOG_END
        {
            flushErrors();
    GLfloat fog_end = 0;
    glGetFloatv(GL_FOG_END, &fog_end);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_END");
    json.writeFloat(fog_end);
                json.endMember();
            }
        }

        // GL_FOG_MODE
        {
            flushErrors();
    GLint fog_mode = 0;
    glGetIntegerv(GL_FOG_MODE, &fog_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_MODE");
    dumpEnum(json, fog_mode);
                json.endMember();
            }
        }

        // GL_FOG_COLOR
        {
            flushErrors();
    GLfloat fog_color[4 + 1];
    memset(fog_color, 0, 4 * sizeof *fog_color);
    fog_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_FOG_COLOR, fog_color);
    }
    assert(fog_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COLOR");
    json.beginArray();
    for (unsigned _i16 = 0; _i16 < 4; ++_i16) {
    json.writeFloat(fog_color[_i16]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DEPTH_RANGE
        {
            flushErrors();
    GLfloat depth_range[2 + 1];
    memset(depth_range, 0, 2 * sizeof *depth_range);
    depth_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_DEPTH_RANGE, depth_range);
    }
    assert(depth_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_RANGE");
    json.beginArray();
    for (unsigned _i17 = 0; _i17 < 2; ++_i17) {
    json.writeFloat(depth_range[_i17]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DEPTH_TEST
        {
            flushErrors();
    GLboolean depth_test = 0;
    glGetBooleanv(GL_DEPTH_TEST, &depth_test);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_TEST");
    dumpBoolean(json, depth_test);
                json.endMember();
            }
        }

        // GL_DEPTH_WRITEMASK
        {
            flushErrors();
    GLboolean depth_writemask = 0;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &depth_writemask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_WRITEMASK");
    dumpBoolean(json, depth_writemask);
                json.endMember();
            }
        }

        // GL_DEPTH_CLEAR_VALUE
        {
            flushErrors();
    GLfloat depth_clear_value = 0;
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depth_clear_value);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_CLEAR_VALUE");
    json.writeFloat(depth_clear_value);
                json.endMember();
            }
        }

        // GL_DEPTH_FUNC
        {
            flushErrors();
    GLint depth_func = 0;
    glGetIntegerv(GL_DEPTH_FUNC, &depth_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_FUNC");
    dumpEnum(json, depth_func);
                json.endMember();
            }
        }

        // GL_ACCUM_CLEAR_VALUE
        {
            flushErrors();
    GLfloat accum_clear_value[4 + 1];
    memset(accum_clear_value, 0, 4 * sizeof *accum_clear_value);
    accum_clear_value[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_ACCUM_CLEAR_VALUE, accum_clear_value);
    }
    assert(accum_clear_value[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACCUM_CLEAR_VALUE");
    json.beginArray();
    for (unsigned _i18 = 0; _i18 < 4; ++_i18) {
    json.writeFloat(accum_clear_value[_i18]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_STENCIL_TEST
        {
            flushErrors();
    GLboolean stencil_test = 0;
    glGetBooleanv(GL_STENCIL_TEST, &stencil_test);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_TEST");
    dumpBoolean(json, stencil_test);
                json.endMember();
            }
        }

        // GL_STENCIL_CLEAR_VALUE
        {
            flushErrors();
    GLint stencil_clear_value = 0;
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencil_clear_value);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_CLEAR_VALUE");
    json.writeInt(stencil_clear_value);
                json.endMember();
            }
        }

        // GL_STENCIL_FUNC
        {
            flushErrors();
    GLint stencil_func = 0;
    glGetIntegerv(GL_STENCIL_FUNC, &stencil_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_FUNC");
    dumpEnum(json, stencil_func);
                json.endMember();
            }
        }

        // GL_STENCIL_VALUE_MASK
        {
            flushErrors();
    GLint stencil_value_mask = 0;
    glGetIntegerv(GL_STENCIL_VALUE_MASK, &stencil_value_mask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_VALUE_MASK");
    json.writeInt(stencil_value_mask);
                json.endMember();
            }
        }

        // GL_STENCIL_FAIL
        {
            flushErrors();
    GLint stencil_fail = 0;
    glGetIntegerv(GL_STENCIL_FAIL, &stencil_fail);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_FAIL");
    dumpEnum(json, stencil_fail);
                json.endMember();
            }
        }

        // GL_STENCIL_PASS_DEPTH_FAIL
        {
            flushErrors();
    GLint stencil_pass_depth_fail = 0;
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &stencil_pass_depth_fail);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_PASS_DEPTH_FAIL");
    dumpEnum(json, stencil_pass_depth_fail);
                json.endMember();
            }
        }

        // GL_STENCIL_PASS_DEPTH_PASS
        {
            flushErrors();
    GLint stencil_pass_depth_pass = 0;
    glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &stencil_pass_depth_pass);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_PASS_DEPTH_PASS");
    dumpEnum(json, stencil_pass_depth_pass);
                json.endMember();
            }
        }

        // GL_STENCIL_REF
        {
            flushErrors();
    GLint stencil_ref = 0;
    glGetIntegerv(GL_STENCIL_REF, &stencil_ref);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_REF");
    json.writeInt(stencil_ref);
                json.endMember();
            }
        }

        // GL_STENCIL_WRITEMASK
        {
            flushErrors();
    GLint stencil_writemask = 0;
    glGetIntegerv(GL_STENCIL_WRITEMASK, &stencil_writemask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_WRITEMASK");
    json.writeInt(stencil_writemask);
                json.endMember();
            }
        }

        // GL_MATRIX_MODE
        {
            flushErrors();
    GLint matrix_mode = 0;
    glGetIntegerv(GL_MATRIX_MODE, &matrix_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_MODE");
    dumpEnum(json, matrix_mode);
                json.endMember();
            }
        }

        // GL_NORMALIZE
        {
            flushErrors();
    GLboolean normalize = 0;
    glGetBooleanv(GL_NORMALIZE, &normalize);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMALIZE");
    dumpBoolean(json, normalize);
                json.endMember();
            }
        }

        // GL_VIEWPORT
        {
            flushErrors();
    GLint viewport[4 + 1];
    memset(viewport, 0, 4 * sizeof *viewport);
    viewport[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetIntegerv(GL_VIEWPORT, viewport);
    }
    assert(viewport[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VIEWPORT");
    json.beginArray();
    for (unsigned _i19 = 0; _i19 < 4; ++_i19) {
    json.writeInt(viewport[_i19]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MODELVIEW_STACK_DEPTH
        {
            flushErrors();
    GLint modelview_stack_depth = 0;
    glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &modelview_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MODELVIEW_STACK_DEPTH");
    json.writeInt(modelview_stack_depth);
                json.endMember();
            }
        }

        // GL_PROJECTION_STACK_DEPTH
        {
            flushErrors();
    GLint projection_stack_depth = 0;
    glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &projection_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROJECTION_STACK_DEPTH");
    json.writeInt(projection_stack_depth);
                json.endMember();
            }
        }

        // GL_TEXTURE_STACK_DEPTH
        {
            flushErrors();
    GLint texture_stack_depth = 0;
    glGetIntegerv(GL_TEXTURE_STACK_DEPTH, &texture_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_STACK_DEPTH");
    json.writeInt(texture_stack_depth);
                json.endMember();
            }
        }

        // GL_MODELVIEW_MATRIX
        {
            flushErrors();
    GLfloat modelview_matrix[16 + 1];
    memset(modelview_matrix, 0, 16 * sizeof *modelview_matrix);
    modelview_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
    }
    assert(modelview_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MODELVIEW_MATRIX");
    json.beginArray();
    for (unsigned _i20 = 0; _i20 < 16; ++_i20) {
    json.writeFloat(modelview_matrix[_i20]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_PROJECTION_MATRIX
        {
            flushErrors();
    GLfloat projection_matrix[16 + 1];
    memset(projection_matrix, 0, 16 * sizeof *projection_matrix);
    projection_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);
    }
    assert(projection_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROJECTION_MATRIX");
    json.beginArray();
    for (unsigned _i21 = 0; _i21 < 16; ++_i21) {
    json.writeFloat(projection_matrix[_i21]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_MATRIX
        {
            flushErrors();
    GLfloat texture_matrix[16 + 1];
    memset(texture_matrix, 0, 16 * sizeof *texture_matrix);
    texture_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TEXTURE_MATRIX, texture_matrix);
    }
    assert(texture_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MATRIX");
    json.beginArray();
    for (unsigned _i22 = 0; _i22 < 16; ++_i22) {
    json.writeFloat(texture_matrix[_i22]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_ATTRIB_STACK_DEPTH
        {
            flushErrors();
    GLint attrib_stack_depth = 0;
    glGetIntegerv(GL_ATTRIB_STACK_DEPTH, &attrib_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ATTRIB_STACK_DEPTH");
    json.writeInt(attrib_stack_depth);
                json.endMember();
            }
        }

        // GL_CLIENT_ATTRIB_STACK_DEPTH
        {
            flushErrors();
    GLint client_attrib_stack_depth = 0;
    glGetIntegerv(GL_CLIENT_ATTRIB_STACK_DEPTH, &client_attrib_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIENT_ATTRIB_STACK_DEPTH");
    json.writeInt(client_attrib_stack_depth);
                json.endMember();
            }
        }

        // GL_ALPHA_TEST
        {
            flushErrors();
    GLboolean alpha_test = 0;
    glGetBooleanv(GL_ALPHA_TEST, &alpha_test);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_TEST");
    dumpBoolean(json, alpha_test);
                json.endMember();
            }
        }

        // GL_ALPHA_TEST_FUNC
        {
            flushErrors();
    GLint alpha_test_func = 0;
    glGetIntegerv(GL_ALPHA_TEST_FUNC, &alpha_test_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_TEST_FUNC");
    dumpEnum(json, alpha_test_func);
                json.endMember();
            }
        }

        // GL_ALPHA_TEST_REF
        {
            flushErrors();
    GLfloat alpha_test_ref = 0;
    glGetFloatv(GL_ALPHA_TEST_REF, &alpha_test_ref);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_TEST_REF");
    json.writeFloat(alpha_test_ref);
                json.endMember();
            }
        }

        // GL_DITHER
        {
            flushErrors();
    GLboolean dither = 0;
    glGetBooleanv(GL_DITHER, &dither);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DITHER");
    dumpBoolean(json, dither);
                json.endMember();
            }
        }

        // GL_BLEND_DST
        {
            flushErrors();
    GLint blend_dst = 0;
    glGetIntegerv(GL_BLEND_DST, &blend_dst);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_DST");
    dumpEnum(json, blend_dst);
                json.endMember();
            }
        }

        // GL_BLEND_SRC
        {
            flushErrors();
    GLint blend_src = 0;
    glGetIntegerv(GL_BLEND_SRC, &blend_src);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_SRC");
    dumpEnum(json, blend_src);
                json.endMember();
            }
        }

        // GL_BLEND
        {
            flushErrors();
    GLboolean blend = 0;
    glGetBooleanv(GL_BLEND, &blend);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND");
    dumpBoolean(json, blend);
                json.endMember();
            }
        }

        // GL_LOGIC_OP_MODE
        {
            flushErrors();
    GLint logic_op_mode = 0;
    glGetIntegerv(GL_LOGIC_OP_MODE, &logic_op_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LOGIC_OP_MODE");
    dumpEnum(json, logic_op_mode);
                json.endMember();
            }
        }

        // GL_INDEX_LOGIC_OP
        {
            flushErrors();
    GLboolean index_logic_op = 0;
    glGetBooleanv(GL_INDEX_LOGIC_OP, &index_logic_op);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_LOGIC_OP");
    dumpBoolean(json, index_logic_op);
                json.endMember();
            }
        }

        // GL_COLOR_LOGIC_OP
        {
            flushErrors();
    GLboolean color_logic_op = 0;
    glGetBooleanv(GL_COLOR_LOGIC_OP, &color_logic_op);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_LOGIC_OP");
    dumpBoolean(json, color_logic_op);
                json.endMember();
            }
        }

        // GL_AUX_BUFFERS
        {
            flushErrors();
    GLint aux_buffers = 0;
    glGetIntegerv(GL_AUX_BUFFERS, &aux_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_AUX_BUFFERS");
    json.writeInt(aux_buffers);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER
        {
            flushErrors();
    GLint draw_buffer = 0;
    glGetIntegerv(GL_DRAW_BUFFER, &draw_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER");
    dumpEnum(json, draw_buffer);
                json.endMember();
            }
        }

        // GL_READ_BUFFER
        {
            flushErrors();
    GLint read_buffer = 0;
    glGetIntegerv(GL_READ_BUFFER, &read_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_READ_BUFFER");
    dumpEnum(json, read_buffer);
                json.endMember();
            }
        }

        // GL_SCISSOR_BOX
        {
            flushErrors();
    GLint scissor_box[4 + 1];
    memset(scissor_box, 0, 4 * sizeof *scissor_box);
    scissor_box[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetIntegerv(GL_SCISSOR_BOX, scissor_box);
    }
    assert(scissor_box[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SCISSOR_BOX");
    json.beginArray();
    for (unsigned _i23 = 0; _i23 < 4; ++_i23) {
    json.writeInt(scissor_box[_i23]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SCISSOR_TEST
        {
            flushErrors();
    GLboolean scissor_test = 0;
    glGetBooleanv(GL_SCISSOR_TEST, &scissor_test);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SCISSOR_TEST");
    dumpBoolean(json, scissor_test);
                json.endMember();
            }
        }

        // GL_INDEX_CLEAR_VALUE
        {
            flushErrors();
    GLint index_clear_value = 0;
    glGetIntegerv(GL_INDEX_CLEAR_VALUE, &index_clear_value);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_CLEAR_VALUE");
    json.writeInt(index_clear_value);
                json.endMember();
            }
        }

        // GL_INDEX_WRITEMASK
        {
            flushErrors();
    GLint index_writemask = 0;
    glGetIntegerv(GL_INDEX_WRITEMASK, &index_writemask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_WRITEMASK");
    json.writeInt(index_writemask);
                json.endMember();
            }
        }

        // GL_COLOR_CLEAR_VALUE
        {
            flushErrors();
    GLfloat color_clear_value[4 + 1];
    memset(color_clear_value, 0, 4 * sizeof *color_clear_value);
    color_clear_value[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_COLOR_CLEAR_VALUE, color_clear_value);
    }
    assert(color_clear_value[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_CLEAR_VALUE");
    json.beginArray();
    for (unsigned _i24 = 0; _i24 < 4; ++_i24) {
    json.writeFloat(color_clear_value[_i24]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_COLOR_WRITEMASK
        {
            flushErrors();
    GLboolean color_writemask[4 + 1];
    memset(color_writemask, 0, 4 * sizeof *color_writemask);
    color_writemask[4] = (GLboolean)0xdeadc0de;
    if (4) {
        glGetBooleanv(GL_COLOR_WRITEMASK, color_writemask);
    }
    assert(color_writemask[4] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_WRITEMASK");
    json.beginArray();
    for (unsigned _i25 = 0; _i25 < 4; ++_i25) {
    dumpBoolean(json, color_writemask[_i25]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_INDEX_MODE
        {
            flushErrors();
    GLboolean index_mode = 0;
    glGetBooleanv(GL_INDEX_MODE, &index_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_MODE");
    dumpBoolean(json, index_mode);
                json.endMember();
            }
        }

        // GL_RGBA_MODE
        {
            flushErrors();
    GLboolean rgba_mode = 0;
    glGetBooleanv(GL_RGBA_MODE, &rgba_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RGBA_MODE");
    dumpBoolean(json, rgba_mode);
                json.endMember();
            }
        }

        // GL_DOUBLEBUFFER
        {
            flushErrors();
    GLboolean doublebuffer = 0;
    glGetBooleanv(GL_DOUBLEBUFFER, &doublebuffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DOUBLEBUFFER");
    dumpBoolean(json, doublebuffer);
                json.endMember();
            }
        }

        // GL_STEREO
        {
            flushErrors();
    GLboolean stereo = 0;
    glGetBooleanv(GL_STEREO, &stereo);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STEREO");
    dumpBoolean(json, stereo);
                json.endMember();
            }
        }

        // GL_RENDER_MODE
        {
            flushErrors();
    GLint render_mode = 0;
    glGetIntegerv(GL_RENDER_MODE, &render_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RENDER_MODE");
    dumpEnum(json, render_mode);
                json.endMember();
            }
        }

        // GL_PERSPECTIVE_CORRECTION_HINT
        {
            flushErrors();
    GLint perspective_correction_hint = 0;
    glGetIntegerv(GL_PERSPECTIVE_CORRECTION_HINT, &perspective_correction_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PERSPECTIVE_CORRECTION_HINT");
    dumpEnum(json, perspective_correction_hint);
                json.endMember();
            }
        }

        // GL_POINT_SMOOTH_HINT
        {
            flushErrors();
    GLint point_smooth_hint = 0;
    glGetIntegerv(GL_POINT_SMOOTH_HINT, &point_smooth_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SMOOTH_HINT");
    dumpEnum(json, point_smooth_hint);
                json.endMember();
            }
        }

        // GL_LINE_SMOOTH_HINT
        {
            flushErrors();
    GLint line_smooth_hint = 0;
    glGetIntegerv(GL_LINE_SMOOTH_HINT, &line_smooth_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINE_SMOOTH_HINT");
    dumpEnum(json, line_smooth_hint);
                json.endMember();
            }
        }

        // GL_POLYGON_SMOOTH_HINT
        {
            flushErrors();
    GLint polygon_smooth_hint = 0;
    glGetIntegerv(GL_POLYGON_SMOOTH_HINT, &polygon_smooth_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_SMOOTH_HINT");
    dumpEnum(json, polygon_smooth_hint);
                json.endMember();
            }
        }

        // GL_FOG_HINT
        {
            flushErrors();
    GLint fog_hint = 0;
    glGetIntegerv(GL_FOG_HINT, &fog_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_HINT");
    dumpEnum(json, fog_hint);
                json.endMember();
            }
        }

        // GL_TEXTURE_GEN_S
        {
            flushErrors();
    GLboolean texture_gen_s = 0;
    glGetBooleanv(GL_TEXTURE_GEN_S, &texture_gen_s);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GEN_S");
    dumpBoolean(json, texture_gen_s);
                json.endMember();
            }
        }

        // GL_TEXTURE_GEN_T
        {
            flushErrors();
    GLboolean texture_gen_t = 0;
    glGetBooleanv(GL_TEXTURE_GEN_T, &texture_gen_t);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GEN_T");
    dumpBoolean(json, texture_gen_t);
                json.endMember();
            }
        }

        // GL_TEXTURE_GEN_R
        {
            flushErrors();
    GLboolean texture_gen_r = 0;
    glGetBooleanv(GL_TEXTURE_GEN_R, &texture_gen_r);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GEN_R");
    dumpBoolean(json, texture_gen_r);
                json.endMember();
            }
        }

        // GL_TEXTURE_GEN_Q
        {
            flushErrors();
    GLboolean texture_gen_q = 0;
    glGetBooleanv(GL_TEXTURE_GEN_Q, &texture_gen_q);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_GEN_Q");
    dumpBoolean(json, texture_gen_q);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_I_TO_I_SIZE
        {
            flushErrors();
    GLint pixel_map_i_to_i_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_I_TO_I_SIZE, &pixel_map_i_to_i_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_I_TO_I_SIZE");
    json.writeInt(pixel_map_i_to_i_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_S_TO_S_SIZE
        {
            flushErrors();
    GLint pixel_map_s_to_s_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_S_TO_S_SIZE, &pixel_map_s_to_s_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_S_TO_S_SIZE");
    json.writeInt(pixel_map_s_to_s_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_I_TO_R_SIZE
        {
            flushErrors();
    GLint pixel_map_i_to_r_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_I_TO_R_SIZE, &pixel_map_i_to_r_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_I_TO_R_SIZE");
    json.writeInt(pixel_map_i_to_r_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_I_TO_G_SIZE
        {
            flushErrors();
    GLint pixel_map_i_to_g_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_I_TO_G_SIZE, &pixel_map_i_to_g_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_I_TO_G_SIZE");
    json.writeInt(pixel_map_i_to_g_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_I_TO_B_SIZE
        {
            flushErrors();
    GLint pixel_map_i_to_b_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_I_TO_B_SIZE, &pixel_map_i_to_b_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_I_TO_B_SIZE");
    json.writeInt(pixel_map_i_to_b_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_I_TO_A_SIZE
        {
            flushErrors();
    GLint pixel_map_i_to_a_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_I_TO_A_SIZE, &pixel_map_i_to_a_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_I_TO_A_SIZE");
    json.writeInt(pixel_map_i_to_a_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_R_TO_R_SIZE
        {
            flushErrors();
    GLint pixel_map_r_to_r_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_R_TO_R_SIZE, &pixel_map_r_to_r_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_R_TO_R_SIZE");
    json.writeInt(pixel_map_r_to_r_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_G_TO_G_SIZE
        {
            flushErrors();
    GLint pixel_map_g_to_g_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_G_TO_G_SIZE, &pixel_map_g_to_g_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_G_TO_G_SIZE");
    json.writeInt(pixel_map_g_to_g_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_B_TO_B_SIZE
        {
            flushErrors();
    GLint pixel_map_b_to_b_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_B_TO_B_SIZE, &pixel_map_b_to_b_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_B_TO_B_SIZE");
    json.writeInt(pixel_map_b_to_b_size);
                json.endMember();
            }
        }

        // GL_PIXEL_MAP_A_TO_A_SIZE
        {
            flushErrors();
    GLint pixel_map_a_to_a_size = 0;
    glGetIntegerv(GL_PIXEL_MAP_A_TO_A_SIZE, &pixel_map_a_to_a_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_MAP_A_TO_A_SIZE");
    json.writeInt(pixel_map_a_to_a_size);
                json.endMember();
            }
        }

        // GL_UNPACK_SWAP_BYTES
        {
            flushErrors();
    GLboolean unpack_swap_bytes = 0;
    glGetBooleanv(GL_UNPACK_SWAP_BYTES, &unpack_swap_bytes);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_SWAP_BYTES");
    dumpBoolean(json, unpack_swap_bytes);
                json.endMember();
            }
        }

        // GL_UNPACK_LSB_FIRST
        {
            flushErrors();
    GLboolean unpack_lsb_first = 0;
    glGetBooleanv(GL_UNPACK_LSB_FIRST, &unpack_lsb_first);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_LSB_FIRST");
    dumpBoolean(json, unpack_lsb_first);
                json.endMember();
            }
        }

        // GL_UNPACK_ROW_LENGTH
        {
            flushErrors();
    GLint unpack_row_length = 0;
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &unpack_row_length);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_ROW_LENGTH");
    json.writeInt(unpack_row_length);
                json.endMember();
            }
        }

        // GL_UNPACK_SKIP_ROWS
        {
            flushErrors();
    GLint unpack_skip_rows = 0;
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &unpack_skip_rows);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_SKIP_ROWS");
    json.writeInt(unpack_skip_rows);
                json.endMember();
            }
        }

        // GL_UNPACK_SKIP_PIXELS
        {
            flushErrors();
    GLint unpack_skip_pixels = 0;
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &unpack_skip_pixels);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_SKIP_PIXELS");
    json.writeInt(unpack_skip_pixels);
                json.endMember();
            }
        }

        // GL_UNPACK_ALIGNMENT
        {
            flushErrors();
    GLint unpack_alignment = 0;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &unpack_alignment);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_ALIGNMENT");
    json.writeInt(unpack_alignment);
                json.endMember();
            }
        }

        // GL_PACK_SWAP_BYTES
        {
            flushErrors();
    GLboolean pack_swap_bytes = 0;
    glGetBooleanv(GL_PACK_SWAP_BYTES, &pack_swap_bytes);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_SWAP_BYTES");
    dumpBoolean(json, pack_swap_bytes);
                json.endMember();
            }
        }

        // GL_PACK_LSB_FIRST
        {
            flushErrors();
    GLboolean pack_lsb_first = 0;
    glGetBooleanv(GL_PACK_LSB_FIRST, &pack_lsb_first);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_LSB_FIRST");
    dumpBoolean(json, pack_lsb_first);
                json.endMember();
            }
        }

        // GL_PACK_ROW_LENGTH
        {
            flushErrors();
    GLint pack_row_length = 0;
    glGetIntegerv(GL_PACK_ROW_LENGTH, &pack_row_length);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_ROW_LENGTH");
    json.writeInt(pack_row_length);
                json.endMember();
            }
        }

        // GL_PACK_SKIP_ROWS
        {
            flushErrors();
    GLint pack_skip_rows = 0;
    glGetIntegerv(GL_PACK_SKIP_ROWS, &pack_skip_rows);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_SKIP_ROWS");
    json.writeInt(pack_skip_rows);
                json.endMember();
            }
        }

        // GL_PACK_SKIP_PIXELS
        {
            flushErrors();
    GLint pack_skip_pixels = 0;
    glGetIntegerv(GL_PACK_SKIP_PIXELS, &pack_skip_pixels);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_SKIP_PIXELS");
    json.writeInt(pack_skip_pixels);
                json.endMember();
            }
        }

        // GL_PACK_ALIGNMENT
        {
            flushErrors();
    GLint pack_alignment = 0;
    glGetIntegerv(GL_PACK_ALIGNMENT, &pack_alignment);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_ALIGNMENT");
    json.writeInt(pack_alignment);
                json.endMember();
            }
        }

        // GL_MAP_COLOR
        {
            flushErrors();
    GLboolean map_color = 0;
    glGetBooleanv(GL_MAP_COLOR, &map_color);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP_COLOR");
    dumpBoolean(json, map_color);
                json.endMember();
            }
        }

        // GL_MAP_STENCIL
        {
            flushErrors();
    GLboolean map_stencil = 0;
    glGetBooleanv(GL_MAP_STENCIL, &map_stencil);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP_STENCIL");
    dumpBoolean(json, map_stencil);
                json.endMember();
            }
        }

        // GL_INDEX_SHIFT
        {
            flushErrors();
    GLint index_shift = 0;
    glGetIntegerv(GL_INDEX_SHIFT, &index_shift);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_SHIFT");
    json.writeInt(index_shift);
                json.endMember();
            }
        }

        // GL_INDEX_OFFSET
        {
            flushErrors();
    GLint index_offset = 0;
    glGetIntegerv(GL_INDEX_OFFSET, &index_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_OFFSET");
    json.writeInt(index_offset);
                json.endMember();
            }
        }

        // GL_RED_SCALE
        {
            flushErrors();
    GLfloat red_scale = 0;
    glGetFloatv(GL_RED_SCALE, &red_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RED_SCALE");
    json.writeFloat(red_scale);
                json.endMember();
            }
        }

        // GL_RED_BIAS
        {
            flushErrors();
    GLfloat red_bias = 0;
    glGetFloatv(GL_RED_BIAS, &red_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RED_BIAS");
    json.writeFloat(red_bias);
                json.endMember();
            }
        }

        // GL_ZOOM_X
        {
            flushErrors();
    GLfloat zoom_x = 0;
    glGetFloatv(GL_ZOOM_X, &zoom_x);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ZOOM_X");
    json.writeFloat(zoom_x);
                json.endMember();
            }
        }

        // GL_ZOOM_Y
        {
            flushErrors();
    GLfloat zoom_y = 0;
    glGetFloatv(GL_ZOOM_Y, &zoom_y);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ZOOM_Y");
    json.writeFloat(zoom_y);
                json.endMember();
            }
        }

        // GL_GREEN_SCALE
        {
            flushErrors();
    GLfloat green_scale = 0;
    glGetFloatv(GL_GREEN_SCALE, &green_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GREEN_SCALE");
    json.writeFloat(green_scale);
                json.endMember();
            }
        }

        // GL_GREEN_BIAS
        {
            flushErrors();
    GLfloat green_bias = 0;
    glGetFloatv(GL_GREEN_BIAS, &green_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GREEN_BIAS");
    json.writeFloat(green_bias);
                json.endMember();
            }
        }

        // GL_BLUE_SCALE
        {
            flushErrors();
    GLfloat blue_scale = 0;
    glGetFloatv(GL_BLUE_SCALE, &blue_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLUE_SCALE");
    json.writeFloat(blue_scale);
                json.endMember();
            }
        }

        // GL_BLUE_BIAS
        {
            flushErrors();
    GLfloat blue_bias = 0;
    glGetFloatv(GL_BLUE_BIAS, &blue_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLUE_BIAS");
    json.writeFloat(blue_bias);
                json.endMember();
            }
        }

        // GL_ALPHA_SCALE
        {
            flushErrors();
    GLfloat alpha_scale = 0;
    glGetFloatv(GL_ALPHA_SCALE, &alpha_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_SCALE");
    json.writeFloat(alpha_scale);
                json.endMember();
            }
        }

        // GL_ALPHA_BIAS
        {
            flushErrors();
    GLfloat alpha_bias = 0;
    glGetFloatv(GL_ALPHA_BIAS, &alpha_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_BIAS");
    json.writeFloat(alpha_bias);
                json.endMember();
            }
        }

        // GL_DEPTH_SCALE
        {
            flushErrors();
    GLfloat depth_scale = 0;
    glGetFloatv(GL_DEPTH_SCALE, &depth_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_SCALE");
    json.writeFloat(depth_scale);
                json.endMember();
            }
        }

        // GL_DEPTH_BIAS
        {
            flushErrors();
    GLfloat depth_bias = 0;
    glGetFloatv(GL_DEPTH_BIAS, &depth_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_BIAS");
    json.writeFloat(depth_bias);
                json.endMember();
            }
        }

        // GL_MAX_EVAL_ORDER
        {
            flushErrors();
    GLint max_eval_order = 0;
    glGetIntegerv(GL_MAX_EVAL_ORDER, &max_eval_order);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_EVAL_ORDER");
    json.writeInt(max_eval_order);
                json.endMember();
            }
        }

        // GL_MAX_LIGHTS
        {
            flushErrors();
    GLint max_lights = 0;
    glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_LIGHTS");
    json.writeInt(max_lights);
                json.endMember();
            }
        }

        // GL_MAX_CLIP_DISTANCES
        {
            flushErrors();
    GLint max_clip_distances = 0;
    glGetIntegerv(GL_MAX_CLIP_DISTANCES, &max_clip_distances);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_CLIP_DISTANCES");
    json.writeInt(max_clip_distances);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_texture_size = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_SIZE");
    json.writeInt(max_texture_size);
                json.endMember();
            }
        }

        // GL_MAX_PIXEL_MAP_TABLE
        {
            flushErrors();
    GLint max_pixel_map_table = 0;
    glGetIntegerv(GL_MAX_PIXEL_MAP_TABLE, &max_pixel_map_table);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PIXEL_MAP_TABLE");
    json.writeInt(max_pixel_map_table);
                json.endMember();
            }
        }

        // GL_MAX_ATTRIB_STACK_DEPTH
        {
            flushErrors();
    GLint max_attrib_stack_depth = 0;
    glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &max_attrib_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ATTRIB_STACK_DEPTH");
    json.writeInt(max_attrib_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_MODELVIEW_STACK_DEPTH
        {
            flushErrors();
    GLint max_modelview_stack_depth = 0;
    glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &max_modelview_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_MODELVIEW_STACK_DEPTH");
    json.writeInt(max_modelview_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_NAME_STACK_DEPTH
        {
            flushErrors();
    GLint max_name_stack_depth = 0;
    glGetIntegerv(GL_MAX_NAME_STACK_DEPTH, &max_name_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_NAME_STACK_DEPTH");
    json.writeInt(max_name_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_PROJECTION_STACK_DEPTH
        {
            flushErrors();
    GLint max_projection_stack_depth = 0;
    glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &max_projection_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROJECTION_STACK_DEPTH");
    json.writeInt(max_projection_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_STACK_DEPTH
        {
            flushErrors();
    GLint max_texture_stack_depth = 0;
    glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &max_texture_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_STACK_DEPTH");
    json.writeInt(max_texture_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_VIEWPORT_DIMS
        {
            flushErrors();
    GLfloat max_viewport_dims[2 + 1];
    memset(max_viewport_dims, 0, 2 * sizeof *max_viewport_dims);
    max_viewport_dims[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_MAX_VIEWPORT_DIMS, max_viewport_dims);
    }
    assert(max_viewport_dims[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VIEWPORT_DIMS");
    json.beginArray();
    for (unsigned _i26 = 0; _i26 < 2; ++_i26) {
    json.writeFloat(max_viewport_dims[_i26]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAX_CLIENT_ATTRIB_STACK_DEPTH
        {
            flushErrors();
    GLint max_client_attrib_stack_depth = 0;
    glGetIntegerv(GL_MAX_CLIENT_ATTRIB_STACK_DEPTH, &max_client_attrib_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_CLIENT_ATTRIB_STACK_DEPTH");
    json.writeInt(max_client_attrib_stack_depth);
                json.endMember();
            }
        }

        // GL_SUBPIXEL_BITS
        {
            flushErrors();
    GLint subpixel_bits = 0;
    glGetIntegerv(GL_SUBPIXEL_BITS, &subpixel_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SUBPIXEL_BITS");
    json.writeInt(subpixel_bits);
                json.endMember();
            }
        }

        // GL_INDEX_BITS
        {
            flushErrors();
    GLint index_bits = 0;
    glGetIntegerv(GL_INDEX_BITS, &index_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_BITS");
    json.writeInt(index_bits);
                json.endMember();
            }
        }

        // GL_RED_BITS
        {
            flushErrors();
    GLint red_bits = 0;
    glGetIntegerv(GL_RED_BITS, &red_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RED_BITS");
    json.writeInt(red_bits);
                json.endMember();
            }
        }

        // GL_GREEN_BITS
        {
            flushErrors();
    GLint green_bits = 0;
    glGetIntegerv(GL_GREEN_BITS, &green_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GREEN_BITS");
    json.writeInt(green_bits);
                json.endMember();
            }
        }

        // GL_BLUE_BITS
        {
            flushErrors();
    GLint blue_bits = 0;
    glGetIntegerv(GL_BLUE_BITS, &blue_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLUE_BITS");
    json.writeInt(blue_bits);
                json.endMember();
            }
        }

        // GL_ALPHA_BITS
        {
            flushErrors();
    GLint alpha_bits = 0;
    glGetIntegerv(GL_ALPHA_BITS, &alpha_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_BITS");
    json.writeInt(alpha_bits);
                json.endMember();
            }
        }

        // GL_DEPTH_BITS
        {
            flushErrors();
    GLint depth_bits = 0;
    glGetIntegerv(GL_DEPTH_BITS, &depth_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_BITS");
    json.writeInt(depth_bits);
                json.endMember();
            }
        }

        // GL_STENCIL_BITS
        {
            flushErrors();
    GLint stencil_bits = 0;
    glGetIntegerv(GL_STENCIL_BITS, &stencil_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_BITS");
    json.writeInt(stencil_bits);
                json.endMember();
            }
        }

        // GL_ACCUM_RED_BITS
        {
            flushErrors();
    GLint accum_red_bits = 0;
    glGetIntegerv(GL_ACCUM_RED_BITS, &accum_red_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACCUM_RED_BITS");
    json.writeInt(accum_red_bits);
                json.endMember();
            }
        }

        // GL_ACCUM_GREEN_BITS
        {
            flushErrors();
    GLint accum_green_bits = 0;
    glGetIntegerv(GL_ACCUM_GREEN_BITS, &accum_green_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACCUM_GREEN_BITS");
    json.writeInt(accum_green_bits);
                json.endMember();
            }
        }

        // GL_ACCUM_BLUE_BITS
        {
            flushErrors();
    GLint accum_blue_bits = 0;
    glGetIntegerv(GL_ACCUM_BLUE_BITS, &accum_blue_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACCUM_BLUE_BITS");
    json.writeInt(accum_blue_bits);
                json.endMember();
            }
        }

        // GL_ACCUM_ALPHA_BITS
        {
            flushErrors();
    GLint accum_alpha_bits = 0;
    glGetIntegerv(GL_ACCUM_ALPHA_BITS, &accum_alpha_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACCUM_ALPHA_BITS");
    json.writeInt(accum_alpha_bits);
                json.endMember();
            }
        }

        // GL_NAME_STACK_DEPTH
        {
            flushErrors();
    GLint name_stack_depth = 0;
    glGetIntegerv(GL_NAME_STACK_DEPTH, &name_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NAME_STACK_DEPTH");
    json.writeInt(name_stack_depth);
                json.endMember();
            }
        }

        // GL_AUTO_NORMAL
        {
            flushErrors();
    GLboolean auto_normal = 0;
    glGetBooleanv(GL_AUTO_NORMAL, &auto_normal);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_AUTO_NORMAL");
    dumpBoolean(json, auto_normal);
                json.endMember();
            }
        }

        // GL_MAP1_COLOR_4
        {
            flushErrors();
    GLboolean map1_color_4 = 0;
    glGetBooleanv(GL_MAP1_COLOR_4, &map1_color_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_COLOR_4");
    dumpBoolean(json, map1_color_4);
                json.endMember();
            }
        }

        // GL_MAP1_INDEX
        {
            flushErrors();
    GLboolean map1_index = 0;
    glGetBooleanv(GL_MAP1_INDEX, &map1_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_INDEX");
    dumpBoolean(json, map1_index);
                json.endMember();
            }
        }

        // GL_MAP1_NORMAL
        {
            flushErrors();
    GLboolean map1_normal = 0;
    glGetBooleanv(GL_MAP1_NORMAL, &map1_normal);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_NORMAL");
    dumpBoolean(json, map1_normal);
                json.endMember();
            }
        }

        // GL_MAP1_TEXTURE_COORD_1
        {
            flushErrors();
    GLboolean map1_texture_coord_1 = 0;
    glGetBooleanv(GL_MAP1_TEXTURE_COORD_1, &map1_texture_coord_1);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_TEXTURE_COORD_1");
    dumpBoolean(json, map1_texture_coord_1);
                json.endMember();
            }
        }

        // GL_MAP1_TEXTURE_COORD_2
        {
            flushErrors();
    GLboolean map1_texture_coord_2 = 0;
    glGetBooleanv(GL_MAP1_TEXTURE_COORD_2, &map1_texture_coord_2);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_TEXTURE_COORD_2");
    dumpBoolean(json, map1_texture_coord_2);
                json.endMember();
            }
        }

        // GL_MAP1_TEXTURE_COORD_3
        {
            flushErrors();
    GLboolean map1_texture_coord_3 = 0;
    glGetBooleanv(GL_MAP1_TEXTURE_COORD_3, &map1_texture_coord_3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_TEXTURE_COORD_3");
    dumpBoolean(json, map1_texture_coord_3);
                json.endMember();
            }
        }

        // GL_MAP1_TEXTURE_COORD_4
        {
            flushErrors();
    GLboolean map1_texture_coord_4 = 0;
    glGetBooleanv(GL_MAP1_TEXTURE_COORD_4, &map1_texture_coord_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_TEXTURE_COORD_4");
    dumpBoolean(json, map1_texture_coord_4);
                json.endMember();
            }
        }

        // GL_MAP1_VERTEX_3
        {
            flushErrors();
    GLboolean map1_vertex_3 = 0;
    glGetBooleanv(GL_MAP1_VERTEX_3, &map1_vertex_3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_VERTEX_3");
    dumpBoolean(json, map1_vertex_3);
                json.endMember();
            }
        }

        // GL_MAP1_VERTEX_4
        {
            flushErrors();
    GLboolean map1_vertex_4 = 0;
    glGetBooleanv(GL_MAP1_VERTEX_4, &map1_vertex_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_VERTEX_4");
    dumpBoolean(json, map1_vertex_4);
                json.endMember();
            }
        }

        // GL_MAP2_COLOR_4
        {
            flushErrors();
    GLboolean map2_color_4 = 0;
    glGetBooleanv(GL_MAP2_COLOR_4, &map2_color_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_COLOR_4");
    dumpBoolean(json, map2_color_4);
                json.endMember();
            }
        }

        // GL_MAP2_INDEX
        {
            flushErrors();
    GLboolean map2_index = 0;
    glGetBooleanv(GL_MAP2_INDEX, &map2_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_INDEX");
    dumpBoolean(json, map2_index);
                json.endMember();
            }
        }

        // GL_MAP2_NORMAL
        {
            flushErrors();
    GLboolean map2_normal = 0;
    glGetBooleanv(GL_MAP2_NORMAL, &map2_normal);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_NORMAL");
    dumpBoolean(json, map2_normal);
                json.endMember();
            }
        }

        // GL_MAP2_TEXTURE_COORD_1
        {
            flushErrors();
    GLboolean map2_texture_coord_1 = 0;
    glGetBooleanv(GL_MAP2_TEXTURE_COORD_1, &map2_texture_coord_1);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_TEXTURE_COORD_1");
    dumpBoolean(json, map2_texture_coord_1);
                json.endMember();
            }
        }

        // GL_MAP2_TEXTURE_COORD_2
        {
            flushErrors();
    GLboolean map2_texture_coord_2 = 0;
    glGetBooleanv(GL_MAP2_TEXTURE_COORD_2, &map2_texture_coord_2);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_TEXTURE_COORD_2");
    dumpBoolean(json, map2_texture_coord_2);
                json.endMember();
            }
        }

        // GL_MAP2_TEXTURE_COORD_3
        {
            flushErrors();
    GLboolean map2_texture_coord_3 = 0;
    glGetBooleanv(GL_MAP2_TEXTURE_COORD_3, &map2_texture_coord_3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_TEXTURE_COORD_3");
    dumpBoolean(json, map2_texture_coord_3);
                json.endMember();
            }
        }

        // GL_MAP2_TEXTURE_COORD_4
        {
            flushErrors();
    GLboolean map2_texture_coord_4 = 0;
    glGetBooleanv(GL_MAP2_TEXTURE_COORD_4, &map2_texture_coord_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_TEXTURE_COORD_4");
    dumpBoolean(json, map2_texture_coord_4);
                json.endMember();
            }
        }

        // GL_MAP2_VERTEX_3
        {
            flushErrors();
    GLboolean map2_vertex_3 = 0;
    glGetBooleanv(GL_MAP2_VERTEX_3, &map2_vertex_3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_VERTEX_3");
    dumpBoolean(json, map2_vertex_3);
                json.endMember();
            }
        }

        // GL_MAP2_VERTEX_4
        {
            flushErrors();
    GLboolean map2_vertex_4 = 0;
    glGetBooleanv(GL_MAP2_VERTEX_4, &map2_vertex_4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_VERTEX_4");
    dumpBoolean(json, map2_vertex_4);
                json.endMember();
            }
        }

        // GL_MAP1_GRID_DOMAIN
        {
            flushErrors();
    GLfloat map1_grid_domain[2 + 1];
    memset(map1_grid_domain, 0, 2 * sizeof *map1_grid_domain);
    map1_grid_domain[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_MAP1_GRID_DOMAIN, map1_grid_domain);
    }
    assert(map1_grid_domain[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_GRID_DOMAIN");
    json.beginArray();
    for (unsigned _i27 = 0; _i27 < 2; ++_i27) {
    json.writeFloat(map1_grid_domain[_i27]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAP1_GRID_SEGMENTS
        {
            flushErrors();
    GLint map1_grid_segments = 0;
    glGetIntegerv(GL_MAP1_GRID_SEGMENTS, &map1_grid_segments);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP1_GRID_SEGMENTS");
    json.writeInt(map1_grid_segments);
                json.endMember();
            }
        }

        // GL_MAP2_GRID_DOMAIN
        {
            flushErrors();
    GLfloat map2_grid_domain[4 + 1];
    memset(map2_grid_domain, 0, 4 * sizeof *map2_grid_domain);
    map2_grid_domain[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_MAP2_GRID_DOMAIN, map2_grid_domain);
    }
    assert(map2_grid_domain[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_GRID_DOMAIN");
    json.beginArray();
    for (unsigned _i28 = 0; _i28 < 4; ++_i28) {
    json.writeFloat(map2_grid_domain[_i28]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAP2_GRID_SEGMENTS
        {
            flushErrors();
    GLint map2_grid_segments[2 + 1];
    memset(map2_grid_segments, 0, 2 * sizeof *map2_grid_segments);
    map2_grid_segments[2] = (GLint)0xdeadc0de;
    if (2) {
        glGetIntegerv(GL_MAP2_GRID_SEGMENTS, map2_grid_segments);
    }
    assert(map2_grid_segments[2] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAP2_GRID_SEGMENTS");
    json.beginArray();
    for (unsigned _i29 = 0; _i29 < 2; ++_i29) {
    json.writeInt(map2_grid_segments[_i29]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_FEEDBACK_BUFFER_POINTER
        {
            flushErrors();
    GLvoid *feedback_buffer_pointer;
    glGetPointerv(GL_FEEDBACK_BUFFER_POINTER, &feedback_buffer_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FEEDBACK_BUFFER_POINTER");
    json.writeInt((size_t)feedback_buffer_pointer);
                json.endMember();
            }
        }

        // GL_FEEDBACK_BUFFER_SIZE
        {
            flushErrors();
    GLint feedback_buffer_size = 0;
    glGetIntegerv(GL_FEEDBACK_BUFFER_SIZE, &feedback_buffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FEEDBACK_BUFFER_SIZE");
    json.writeInt(feedback_buffer_size);
                json.endMember();
            }
        }

        // GL_FEEDBACK_BUFFER_TYPE
        {
            flushErrors();
    GLint feedback_buffer_type = 0;
    glGetIntegerv(GL_FEEDBACK_BUFFER_TYPE, &feedback_buffer_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FEEDBACK_BUFFER_TYPE");
    dumpEnum(json, feedback_buffer_type);
                json.endMember();
            }
        }

        // GL_SELECTION_BUFFER_POINTER
        {
            flushErrors();
    GLvoid *selection_buffer_pointer;
    glGetPointerv(GL_SELECTION_BUFFER_POINTER, &selection_buffer_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SELECTION_BUFFER_POINTER");
    json.writeInt((size_t)selection_buffer_pointer);
                json.endMember();
            }
        }

        // GL_SELECTION_BUFFER_SIZE
        {
            flushErrors();
    GLint selection_buffer_size = 0;
    glGetIntegerv(GL_SELECTION_BUFFER_SIZE, &selection_buffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SELECTION_BUFFER_SIZE");
    json.writeInt(selection_buffer_size);
                json.endMember();
            }
        }

        // GL_VENDOR
        {
            flushErrors();
    char * vendor = (char *)glGetString(GL_VENDOR);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VENDOR");
    json.writeString((const char *)vendor);
                json.endMember();
            }
        }

        // GL_RENDERER
        {
            flushErrors();
    char * renderer = (char *)glGetString(GL_RENDERER);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RENDERER");
    json.writeString((const char *)renderer);
                json.endMember();
            }
        }

        // GL_VERSION
        {
            flushErrors();
    char * version = (char *)glGetString(GL_VERSION);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERSION");
    json.writeString((const char *)version);
                json.endMember();
            }
        }

        // GL_EXTENSIONS
        {
            flushErrors();
    char * extensions = (char *)glGetString(GL_EXTENSIONS);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EXTENSIONS");
    json.writeString((const char *)extensions);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_UNITS
        {
            flushErrors();
    GLfloat polygon_offset_units = 0;
    glGetFloatv(GL_POLYGON_OFFSET_UNITS, &polygon_offset_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_UNITS");
    json.writeFloat(polygon_offset_units);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_POINT
        {
            flushErrors();
    GLboolean polygon_offset_point = 0;
    glGetBooleanv(GL_POLYGON_OFFSET_POINT, &polygon_offset_point);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_POINT");
    dumpBoolean(json, polygon_offset_point);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_LINE
        {
            flushErrors();
    GLboolean polygon_offset_line = 0;
    glGetBooleanv(GL_POLYGON_OFFSET_LINE, &polygon_offset_line);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_LINE");
    dumpBoolean(json, polygon_offset_line);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE0
        {
            flushErrors();
    GLboolean clip_distance0 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE0, &clip_distance0);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE0");
    dumpBoolean(json, clip_distance0);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE1
        {
            flushErrors();
    GLboolean clip_distance1 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE1, &clip_distance1);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE1");
    dumpBoolean(json, clip_distance1);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE2
        {
            flushErrors();
    GLboolean clip_distance2 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE2, &clip_distance2);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE2");
    dumpBoolean(json, clip_distance2);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE3
        {
            flushErrors();
    GLboolean clip_distance3 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE3, &clip_distance3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE3");
    dumpBoolean(json, clip_distance3);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE4
        {
            flushErrors();
    GLboolean clip_distance4 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE4, &clip_distance4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE4");
    dumpBoolean(json, clip_distance4);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE5
        {
            flushErrors();
    GLboolean clip_distance5 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE5, &clip_distance5);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE5");
    dumpBoolean(json, clip_distance5);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE6
        {
            flushErrors();
    GLboolean clip_distance6 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE6, &clip_distance6);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE6");
    dumpBoolean(json, clip_distance6);
                json.endMember();
            }
        }

        // GL_CLIP_DISTANCE7
        {
            flushErrors();
    GLboolean clip_distance7 = 0;
    glGetBooleanv(GL_CLIP_DISTANCE7, &clip_distance7);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_DISTANCE7");
    dumpBoolean(json, clip_distance7);
                json.endMember();
            }
        }

        // GL_BLEND_COLOR
        {
            flushErrors();
    GLfloat blend_color[4 + 1];
    memset(blend_color, 0, 4 * sizeof *blend_color);
    blend_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_BLEND_COLOR, blend_color);
    }
    assert(blend_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_COLOR");
    json.beginArray();
    for (unsigned _i30 = 0; _i30 < 4; ++_i30) {
    json.writeFloat(blend_color[_i30]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_BLEND_EQUATION
        {
            flushErrors();
    GLint blend_equation = 0;
    glGetIntegerv(GL_BLEND_EQUATION, &blend_equation);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_EQUATION");
    dumpEnum(json, blend_equation);
                json.endMember();
            }
        }

        // GL_PACK_CMYK_HINT_EXT
        {
            flushErrors();
    GLint pack_cmyk_hint_ext = 0;
    glGetIntegerv(GL_PACK_CMYK_HINT_EXT, &pack_cmyk_hint_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_CMYK_HINT_EXT");
    json.writeInt(pack_cmyk_hint_ext);
                json.endMember();
            }
        }

        // GL_UNPACK_CMYK_HINT_EXT
        {
            flushErrors();
    GLint unpack_cmyk_hint_ext = 0;
    glGetIntegerv(GL_UNPACK_CMYK_HINT_EXT, &unpack_cmyk_hint_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_CMYK_HINT_EXT");
    json.writeInt(unpack_cmyk_hint_ext);
                json.endMember();
            }
        }

        // GL_CONVOLUTION_1D
        {
            flushErrors();
    GLboolean convolution_1d = 0;
    glGetBooleanv(GL_CONVOLUTION_1D, &convolution_1d);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONVOLUTION_1D");
    dumpBoolean(json, convolution_1d);
                json.endMember();
            }
        }

        // GL_CONVOLUTION_2D
        {
            flushErrors();
    GLboolean convolution_2d = 0;
    glGetBooleanv(GL_CONVOLUTION_2D, &convolution_2d);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONVOLUTION_2D");
    dumpBoolean(json, convolution_2d);
                json.endMember();
            }
        }

        // GL_SEPARABLE_2D
        {
            flushErrors();
    GLboolean separable_2d = 0;
    glGetBooleanv(GL_SEPARABLE_2D, &separable_2d);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SEPARABLE_2D");
    dumpBoolean(json, separable_2d);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_RED_SCALE
        {
            flushErrors();
    GLfloat post_convolution_red_scale = 0;
    glGetFloatv(GL_POST_CONVOLUTION_RED_SCALE, &post_convolution_red_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_RED_SCALE");
    json.writeFloat(post_convolution_red_scale);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_GREEN_SCALE
        {
            flushErrors();
    GLfloat post_convolution_green_scale = 0;
    glGetFloatv(GL_POST_CONVOLUTION_GREEN_SCALE, &post_convolution_green_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_GREEN_SCALE");
    json.writeFloat(post_convolution_green_scale);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_BLUE_SCALE
        {
            flushErrors();
    GLfloat post_convolution_blue_scale = 0;
    glGetFloatv(GL_POST_CONVOLUTION_BLUE_SCALE, &post_convolution_blue_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_BLUE_SCALE");
    json.writeFloat(post_convolution_blue_scale);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_ALPHA_SCALE
        {
            flushErrors();
    GLfloat post_convolution_alpha_scale = 0;
    glGetFloatv(GL_POST_CONVOLUTION_ALPHA_SCALE, &post_convolution_alpha_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_ALPHA_SCALE");
    json.writeFloat(post_convolution_alpha_scale);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_RED_BIAS
        {
            flushErrors();
    GLfloat post_convolution_red_bias = 0;
    glGetFloatv(GL_POST_CONVOLUTION_RED_BIAS, &post_convolution_red_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_RED_BIAS");
    json.writeFloat(post_convolution_red_bias);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_GREEN_BIAS
        {
            flushErrors();
    GLfloat post_convolution_green_bias = 0;
    glGetFloatv(GL_POST_CONVOLUTION_GREEN_BIAS, &post_convolution_green_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_GREEN_BIAS");
    json.writeFloat(post_convolution_green_bias);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_BLUE_BIAS
        {
            flushErrors();
    GLfloat post_convolution_blue_bias = 0;
    glGetFloatv(GL_POST_CONVOLUTION_BLUE_BIAS, &post_convolution_blue_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_BLUE_BIAS");
    json.writeFloat(post_convolution_blue_bias);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_ALPHA_BIAS
        {
            flushErrors();
    GLfloat post_convolution_alpha_bias = 0;
    glGetFloatv(GL_POST_CONVOLUTION_ALPHA_BIAS, &post_convolution_alpha_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_ALPHA_BIAS");
    json.writeFloat(post_convolution_alpha_bias);
                json.endMember();
            }
        }

        // GL_HISTOGRAM
        {
            flushErrors();
    GLboolean histogram = 0;
    glGetBooleanv(GL_HISTOGRAM, &histogram);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_HISTOGRAM");
    dumpBoolean(json, histogram);
                json.endMember();
            }
        }

        // GL_MINMAX
        {
            flushErrors();
    GLboolean minmax = 0;
    glGetBooleanv(GL_MINMAX, &minmax);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MINMAX");
    dumpBoolean(json, minmax);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_FILL
        {
            flushErrors();
    GLboolean polygon_offset_fill = 0;
    glGetBooleanv(GL_POLYGON_OFFSET_FILL, &polygon_offset_fill);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_FILL");
    dumpBoolean(json, polygon_offset_fill);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_FACTOR
        {
            flushErrors();
    GLfloat polygon_offset_factor = 0;
    glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &polygon_offset_factor);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_FACTOR");
    json.writeFloat(polygon_offset_factor);
                json.endMember();
            }
        }

        // GL_POLYGON_OFFSET_BIAS_EXT
        {
            flushErrors();
    GLfloat polygon_offset_bias_ext = 0;
    glGetFloatv(GL_POLYGON_OFFSET_BIAS_EXT, &polygon_offset_bias_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POLYGON_OFFSET_BIAS_EXT");
    json.writeFloat(polygon_offset_bias_ext);
                json.endMember();
            }
        }

        // GL_RESCALE_NORMAL
        {
            flushErrors();
    GLboolean rescale_normal = 0;
    glGetBooleanv(GL_RESCALE_NORMAL, &rescale_normal);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RESCALE_NORMAL");
    dumpBoolean(json, rescale_normal);
                json.endMember();
            }
        }

        // GL_PACK_SKIP_IMAGES
        {
            flushErrors();
    GLint pack_skip_images = 0;
    glGetIntegerv(GL_PACK_SKIP_IMAGES, &pack_skip_images);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_SKIP_IMAGES");
    json.writeInt(pack_skip_images);
                json.endMember();
            }
        }

        // GL_PACK_IMAGE_HEIGHT
        {
            flushErrors();
    GLfloat pack_image_height = 0;
    glGetFloatv(GL_PACK_IMAGE_HEIGHT, &pack_image_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_IMAGE_HEIGHT");
    json.writeFloat(pack_image_height);
                json.endMember();
            }
        }

        // GL_UNPACK_SKIP_IMAGES
        {
            flushErrors();
    GLint unpack_skip_images = 0;
    glGetIntegerv(GL_UNPACK_SKIP_IMAGES, &unpack_skip_images);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_SKIP_IMAGES");
    json.writeInt(unpack_skip_images);
                json.endMember();
            }
        }

        // GL_UNPACK_IMAGE_HEIGHT
        {
            flushErrors();
    GLfloat unpack_image_height = 0;
    glGetFloatv(GL_UNPACK_IMAGE_HEIGHT, &unpack_image_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_IMAGE_HEIGHT");
    json.writeFloat(unpack_image_height);
                json.endMember();
            }
        }

        // GL_TEXTURE_3D
        {
            flushErrors();
    GLboolean texture_3d = 0;
    glGetBooleanv(GL_TEXTURE_3D, &texture_3d);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_3D");
    dumpBoolean(json, texture_3d);
                json.endMember();
            }
        }

        // GL_MAX_3D_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_3d_texture_size = 0;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_3d_texture_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_3D_TEXTURE_SIZE");
    json.writeInt(max_3d_texture_size);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY
        {
            flushErrors();
    GLboolean vertex_array = 0;
    glGetBooleanv(GL_VERTEX_ARRAY, &vertex_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY");
    dumpBoolean(json, vertex_array);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY
        {
            flushErrors();
    GLboolean normal_array = 0;
    glGetBooleanv(GL_NORMAL_ARRAY, &normal_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY");
    dumpBoolean(json, normal_array);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY
        {
            flushErrors();
    GLboolean color_array = 0;
    glGetBooleanv(GL_COLOR_ARRAY, &color_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY");
    dumpBoolean(json, color_array);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY
        {
            flushErrors();
    GLboolean index_array = 0;
    glGetBooleanv(GL_INDEX_ARRAY, &index_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY");
    dumpBoolean(json, index_array);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY
        {
            flushErrors();
    GLboolean texture_coord_array = 0;
    glGetBooleanv(GL_TEXTURE_COORD_ARRAY, &texture_coord_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY");
    dumpBoolean(json, texture_coord_array);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG_ARRAY
        {
            flushErrors();
    GLboolean edge_flag_array = 0;
    glGetBooleanv(GL_EDGE_FLAG_ARRAY, &edge_flag_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG_ARRAY");
    dumpBoolean(json, edge_flag_array);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_SIZE
        {
            flushErrors();
    GLint vertex_array_size = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_SIZE, &vertex_array_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_SIZE");
    json.writeInt(vertex_array_size);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_TYPE
        {
            flushErrors();
    GLint vertex_array_type = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_TYPE, &vertex_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_TYPE");
    dumpEnum(json, vertex_array_type);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_STRIDE
        {
            flushErrors();
    GLint vertex_array_stride = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_STRIDE, &vertex_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_STRIDE");
    json.writeInt(vertex_array_stride);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint vertex_array_count_ext = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_COUNT_EXT, &vertex_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_COUNT_EXT");
    json.writeInt(vertex_array_count_ext);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY_TYPE
        {
            flushErrors();
    GLint normal_array_type = 0;
    glGetIntegerv(GL_NORMAL_ARRAY_TYPE, &normal_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY_TYPE");
    dumpEnum(json, normal_array_type);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY_STRIDE
        {
            flushErrors();
    GLint normal_array_stride = 0;
    glGetIntegerv(GL_NORMAL_ARRAY_STRIDE, &normal_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY_STRIDE");
    json.writeInt(normal_array_stride);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint normal_array_count_ext = 0;
    glGetIntegerv(GL_NORMAL_ARRAY_COUNT_EXT, &normal_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY_COUNT_EXT");
    json.writeInt(normal_array_count_ext);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_SIZE
        {
            flushErrors();
    GLint color_array_size = 0;
    glGetIntegerv(GL_COLOR_ARRAY_SIZE, &color_array_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_SIZE");
    json.writeInt(color_array_size);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_TYPE
        {
            flushErrors();
    GLint color_array_type = 0;
    glGetIntegerv(GL_COLOR_ARRAY_TYPE, &color_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_TYPE");
    dumpEnum(json, color_array_type);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_STRIDE
        {
            flushErrors();
    GLint color_array_stride = 0;
    glGetIntegerv(GL_COLOR_ARRAY_STRIDE, &color_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_STRIDE");
    json.writeInt(color_array_stride);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint color_array_count_ext = 0;
    glGetIntegerv(GL_COLOR_ARRAY_COUNT_EXT, &color_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_COUNT_EXT");
    json.writeInt(color_array_count_ext);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY_TYPE
        {
            flushErrors();
    GLint index_array_type = 0;
    glGetIntegerv(GL_INDEX_ARRAY_TYPE, &index_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY_TYPE");
    dumpEnum(json, index_array_type);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY_STRIDE
        {
            flushErrors();
    GLint index_array_stride = 0;
    glGetIntegerv(GL_INDEX_ARRAY_STRIDE, &index_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY_STRIDE");
    json.writeInt(index_array_stride);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint index_array_count_ext = 0;
    glGetIntegerv(GL_INDEX_ARRAY_COUNT_EXT, &index_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY_COUNT_EXT");
    json.writeInt(index_array_count_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_SIZE
        {
            flushErrors();
    GLint texture_coord_array_size = 0;
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_SIZE, &texture_coord_array_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_SIZE");
    json.writeInt(texture_coord_array_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_TYPE
        {
            flushErrors();
    GLint texture_coord_array_type = 0;
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_TYPE, &texture_coord_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_TYPE");
    dumpEnum(json, texture_coord_array_type);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_STRIDE
        {
            flushErrors();
    GLint texture_coord_array_stride = 0;
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_STRIDE, &texture_coord_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_STRIDE");
    json.writeInt(texture_coord_array_stride);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint texture_coord_array_count_ext = 0;
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_COUNT_EXT, &texture_coord_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_COUNT_EXT");
    json.writeInt(texture_coord_array_count_ext);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG_ARRAY_STRIDE
        {
            flushErrors();
    GLint edge_flag_array_stride = 0;
    glGetIntegerv(GL_EDGE_FLAG_ARRAY_STRIDE, &edge_flag_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG_ARRAY_STRIDE");
    json.writeInt(edge_flag_array_stride);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG_ARRAY_COUNT_EXT
        {
            flushErrors();
    GLint edge_flag_array_count_ext = 0;
    glGetIntegerv(GL_EDGE_FLAG_ARRAY_COUNT_EXT, &edge_flag_array_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG_ARRAY_COUNT_EXT");
    json.writeInt(edge_flag_array_count_ext);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *vertex_array_pointer;
    glGetPointerv(GL_VERTEX_ARRAY_POINTER, &vertex_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_POINTER");
    json.writeInt((size_t)vertex_array_pointer);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *normal_array_pointer;
    glGetPointerv(GL_NORMAL_ARRAY_POINTER, &normal_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY_POINTER");
    json.writeInt((size_t)normal_array_pointer);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *color_array_pointer;
    glGetPointerv(GL_COLOR_ARRAY_POINTER, &color_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_POINTER");
    json.writeInt((size_t)color_array_pointer);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *index_array_pointer;
    glGetPointerv(GL_INDEX_ARRAY_POINTER, &index_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY_POINTER");
    json.writeInt((size_t)index_array_pointer);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *texture_coord_array_pointer;
    glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER, &texture_coord_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_POINTER");
    json.writeInt((size_t)texture_coord_array_pointer);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *edge_flag_array_pointer;
    glGetPointerv(GL_EDGE_FLAG_ARRAY_POINTER, &edge_flag_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG_ARRAY_POINTER");
    json.writeInt((size_t)edge_flag_array_pointer);
                json.endMember();
            }
        }

        // GL_INTERLACE_SGIX
        {
            flushErrors();
    GLint interlace_sgix = 0;
    glGetIntegerv(GL_INTERLACE_SGIX, &interlace_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INTERLACE_SGIX");
    json.writeInt(interlace_sgix);
                json.endMember();
            }
        }

        // GL_DETAIL_TEXTURE_2D_BINDING_SGIS
        {
            flushErrors();
    GLint detail_texture_2d_binding_sgis = 0;
    glGetIntegerv(GL_DETAIL_TEXTURE_2D_BINDING_SGIS, &detail_texture_2d_binding_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DETAIL_TEXTURE_2D_BINDING_SGIS");
    json.writeInt(detail_texture_2d_binding_sgis);
                json.endMember();
            }
        }

        // GL_MULTISAMPLE
        {
            flushErrors();
    GLint multisample = 0;
    glGetIntegerv(GL_MULTISAMPLE, &multisample);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MULTISAMPLE");
    json.writeInt(multisample);
                json.endMember();
            }
        }

        // GL_SAMPLE_ALPHA_TO_COVERAGE
        {
            flushErrors();
    GLint sample_alpha_to_coverage = 0;
    glGetIntegerv(GL_SAMPLE_ALPHA_TO_COVERAGE, &sample_alpha_to_coverage);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_ALPHA_TO_COVERAGE");
    json.writeInt(sample_alpha_to_coverage);
                json.endMember();
            }
        }

        // GL_SAMPLE_ALPHA_TO_ONE
        {
            flushErrors();
    GLint sample_alpha_to_one = 0;
    glGetIntegerv(GL_SAMPLE_ALPHA_TO_ONE, &sample_alpha_to_one);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_ALPHA_TO_ONE");
    json.writeInt(sample_alpha_to_one);
                json.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE
        {
            flushErrors();
    GLint sample_coverage = 0;
    glGetIntegerv(GL_SAMPLE_COVERAGE, &sample_coverage);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_COVERAGE");
    json.writeInt(sample_coverage);
                json.endMember();
            }
        }

        // GL_SAMPLE_BUFFERS
        {
            flushErrors();
    GLint sample_buffers = 0;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &sample_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_BUFFERS");
    json.writeInt(sample_buffers);
                json.endMember();
            }
        }

        // GL_SAMPLES
        {
            flushErrors();
    GLint samples = 0;
    glGetIntegerv(GL_SAMPLES, &samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLES");
    json.writeInt(samples);
                json.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE_VALUE
        {
            flushErrors();
    GLfloat sample_coverage_value = 0;
    glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, &sample_coverage_value);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_COVERAGE_VALUE");
    json.writeFloat(sample_coverage_value);
                json.endMember();
            }
        }

        // GL_SAMPLE_COVERAGE_INVERT
        {
            flushErrors();
    GLint sample_coverage_invert = 0;
    glGetIntegerv(GL_SAMPLE_COVERAGE_INVERT, &sample_coverage_invert);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_COVERAGE_INVERT");
    json.writeInt(sample_coverage_invert);
                json.endMember();
            }
        }

        // GL_SAMPLE_PATTERN_EXT
        {
            flushErrors();
    GLint sample_pattern_ext = 0;
    glGetIntegerv(GL_SAMPLE_PATTERN_EXT, &sample_pattern_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_PATTERN_EXT");
    json.writeInt(sample_pattern_ext);
                json.endMember();
            }
        }

        // GL_COLOR_MATRIX
        {
            flushErrors();
    GLfloat color_matrix[16 + 1];
    memset(color_matrix, 0, 16 * sizeof *color_matrix);
    color_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_COLOR_MATRIX, color_matrix);
    }
    assert(color_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_MATRIX");
    json.beginArray();
    for (unsigned _i31 = 0; _i31 < 16; ++_i31) {
    json.writeFloat(color_matrix[_i31]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_COLOR_MATRIX_STACK_DEPTH
        {
            flushErrors();
    GLint color_matrix_stack_depth = 0;
    glGetIntegerv(GL_COLOR_MATRIX_STACK_DEPTH, &color_matrix_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_MATRIX_STACK_DEPTH");
    json.writeInt(color_matrix_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_COLOR_MATRIX_STACK_DEPTH
        {
            flushErrors();
    GLint max_color_matrix_stack_depth = 0;
    glGetIntegerv(GL_MAX_COLOR_MATRIX_STACK_DEPTH, &max_color_matrix_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COLOR_MATRIX_STACK_DEPTH");
    json.writeInt(max_color_matrix_stack_depth);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_RED_SCALE
        {
            flushErrors();
    GLfloat post_color_matrix_red_scale = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_RED_SCALE, &post_color_matrix_red_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_RED_SCALE");
    json.writeFloat(post_color_matrix_red_scale);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_GREEN_SCALE
        {
            flushErrors();
    GLfloat post_color_matrix_green_scale = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_GREEN_SCALE, &post_color_matrix_green_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_GREEN_SCALE");
    json.writeFloat(post_color_matrix_green_scale);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_BLUE_SCALE
        {
            flushErrors();
    GLfloat post_color_matrix_blue_scale = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_BLUE_SCALE, &post_color_matrix_blue_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_BLUE_SCALE");
    json.writeFloat(post_color_matrix_blue_scale);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_ALPHA_SCALE
        {
            flushErrors();
    GLfloat post_color_matrix_alpha_scale = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_ALPHA_SCALE, &post_color_matrix_alpha_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_ALPHA_SCALE");
    json.writeFloat(post_color_matrix_alpha_scale);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_RED_BIAS
        {
            flushErrors();
    GLfloat post_color_matrix_red_bias = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_RED_BIAS, &post_color_matrix_red_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_RED_BIAS");
    json.writeFloat(post_color_matrix_red_bias);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_GREEN_BIAS
        {
            flushErrors();
    GLfloat post_color_matrix_green_bias = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_GREEN_BIAS, &post_color_matrix_green_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_GREEN_BIAS");
    json.writeFloat(post_color_matrix_green_bias);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_BLUE_BIAS
        {
            flushErrors();
    GLfloat post_color_matrix_blue_bias = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_BLUE_BIAS, &post_color_matrix_blue_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_BLUE_BIAS");
    json.writeFloat(post_color_matrix_blue_bias);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_ALPHA_BIAS
        {
            flushErrors();
    GLfloat post_color_matrix_alpha_bias = 0;
    glGetFloatv(GL_POST_COLOR_MATRIX_ALPHA_BIAS, &post_color_matrix_alpha_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_ALPHA_BIAS");
    json.writeFloat(post_color_matrix_alpha_bias);
                json.endMember();
            }
        }

        // GL_TEXTURE_COLOR_TABLE_SGI
        {
            flushErrors();
    GLint texture_color_table_sgi = 0;
    glGetIntegerv(GL_TEXTURE_COLOR_TABLE_SGI, &texture_color_table_sgi);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COLOR_TABLE_SGI");
    json.writeInt(texture_color_table_sgi);
                json.endMember();
            }
        }

        // GL_BLEND_DST_RGB
        {
            flushErrors();
    GLint blend_dst_rgb = 0;
    glGetIntegerv(GL_BLEND_DST_RGB, &blend_dst_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_DST_RGB");
    dumpEnum(json, blend_dst_rgb);
                json.endMember();
            }
        }

        // GL_BLEND_SRC_RGB
        {
            flushErrors();
    GLint blend_src_rgb = 0;
    glGetIntegerv(GL_BLEND_SRC_RGB, &blend_src_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_SRC_RGB");
    dumpEnum(json, blend_src_rgb);
                json.endMember();
            }
        }

        // GL_BLEND_DST_ALPHA
        {
            flushErrors();
    GLint blend_dst_alpha = 0;
    glGetIntegerv(GL_BLEND_DST_ALPHA, &blend_dst_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_DST_ALPHA");
    dumpEnum(json, blend_dst_alpha);
                json.endMember();
            }
        }

        // GL_BLEND_SRC_ALPHA
        {
            flushErrors();
    GLint blend_src_alpha = 0;
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &blend_src_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_SRC_ALPHA");
    dumpEnum(json, blend_src_alpha);
                json.endMember();
            }
        }

        // GL_COLOR_TABLE
        {
            flushErrors();
    GLboolean color_table = 0;
    glGetBooleanv(GL_COLOR_TABLE, &color_table);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_TABLE");
    dumpBoolean(json, color_table);
                json.endMember();
            }
        }

        // GL_POST_CONVOLUTION_COLOR_TABLE
        {
            flushErrors();
    GLint post_convolution_color_table = 0;
    glGetIntegerv(GL_POST_CONVOLUTION_COLOR_TABLE, &post_convolution_color_table);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_CONVOLUTION_COLOR_TABLE");
    json.writeInt(post_convolution_color_table);
                json.endMember();
            }
        }

        // GL_POST_COLOR_MATRIX_COLOR_TABLE
        {
            flushErrors();
    GLint post_color_matrix_color_table = 0;
    glGetIntegerv(GL_POST_COLOR_MATRIX_COLOR_TABLE, &post_color_matrix_color_table);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_COLOR_MATRIX_COLOR_TABLE");
    json.writeInt(post_color_matrix_color_table);
                json.endMember();
            }
        }

        // GL_MAX_ELEMENTS_VERTICES
        {
            flushErrors();
    GLint max_elements_vertices = 0;
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max_elements_vertices);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ELEMENTS_VERTICES");
    json.writeInt(max_elements_vertices);
                json.endMember();
            }
        }

        // GL_MAX_ELEMENTS_INDICES
        {
            flushErrors();
    GLint max_elements_indices = 0;
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &max_elements_indices);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ELEMENTS_INDICES");
    json.writeInt(max_elements_indices);
                json.endMember();
            }
        }

        // GL_CLIP_VOLUME_CLIPPING_HINT_EXT
        {
            flushErrors();
    GLint clip_volume_clipping_hint_ext = 0;
    glGetIntegerv(GL_CLIP_VOLUME_CLIPPING_HINT_EXT, &clip_volume_clipping_hint_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIP_VOLUME_CLIPPING_HINT_EXT");
    dumpEnum(json, clip_volume_clipping_hint_ext);
                json.endMember();
            }
        }

        // GL_POINT_SIZE_MIN
        {
            flushErrors();
    GLfloat point_size_min = 0;
    glGetFloatv(GL_POINT_SIZE_MIN, &point_size_min);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SIZE_MIN");
    json.writeFloat(point_size_min);
                json.endMember();
            }
        }

        // GL_POINT_SIZE_MAX
        {
            flushErrors();
    GLfloat point_size_max = 0;
    glGetFloatv(GL_POINT_SIZE_MAX, &point_size_max);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SIZE_MAX");
    json.writeFloat(point_size_max);
                json.endMember();
            }
        }

        // GL_POINT_FADE_THRESHOLD_SIZE
        {
            flushErrors();
    GLfloat point_fade_threshold_size = 0;
    glGetFloatv(GL_POINT_FADE_THRESHOLD_SIZE, &point_fade_threshold_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_FADE_THRESHOLD_SIZE");
    json.writeFloat(point_fade_threshold_size);
                json.endMember();
            }
        }

        // GL_POINT_DISTANCE_ATTENUATION
        {
            flushErrors();
    GLfloat point_distance_attenuation[3 + 1];
    memset(point_distance_attenuation, 0, 3 * sizeof *point_distance_attenuation);
    point_distance_attenuation[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetFloatv(GL_POINT_DISTANCE_ATTENUATION, point_distance_attenuation);
    }
    assert(point_distance_attenuation[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_DISTANCE_ATTENUATION");
    json.beginArray();
    for (unsigned _i32 = 0; _i32 < 3; ++_i32) {
    json.writeFloat(point_distance_attenuation[_i32]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_FOG_FUNC_POINTS_SGIS
        {
            flushErrors();
    GLint fog_func_points_sgis = 0;
    glGetIntegerv(GL_FOG_FUNC_POINTS_SGIS, &fog_func_points_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_FUNC_POINTS_SGIS");
    json.writeInt(fog_func_points_sgis);
                json.endMember();
            }
        }

        // GL_MAX_FOG_FUNC_POINTS_SGIS
        {
            flushErrors();
    GLint max_fog_func_points_sgis = 0;
    glGetIntegerv(GL_MAX_FOG_FUNC_POINTS_SGIS, &max_fog_func_points_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FOG_FUNC_POINTS_SGIS");
    json.writeInt(max_fog_func_points_sgis);
                json.endMember();
            }
        }

        // GL_PACK_SKIP_VOLUMES_SGIS
        {
            flushErrors();
    GLint pack_skip_volumes_sgis = 0;
    glGetIntegerv(GL_PACK_SKIP_VOLUMES_SGIS, &pack_skip_volumes_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_SKIP_VOLUMES_SGIS");
    json.writeInt(pack_skip_volumes_sgis);
                json.endMember();
            }
        }

        // GL_PACK_IMAGE_DEPTH_SGIS
        {
            flushErrors();
    GLint pack_image_depth_sgis = 0;
    glGetIntegerv(GL_PACK_IMAGE_DEPTH_SGIS, &pack_image_depth_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_IMAGE_DEPTH_SGIS");
    json.writeInt(pack_image_depth_sgis);
                json.endMember();
            }
        }

        // GL_UNPACK_SKIP_VOLUMES_SGIS
        {
            flushErrors();
    GLint unpack_skip_volumes_sgis = 0;
    glGetIntegerv(GL_UNPACK_SKIP_VOLUMES_SGIS, &unpack_skip_volumes_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_SKIP_VOLUMES_SGIS");
    json.writeInt(unpack_skip_volumes_sgis);
                json.endMember();
            }
        }

        // GL_UNPACK_IMAGE_DEPTH_SGIS
        {
            flushErrors();
    GLint unpack_image_depth_sgis = 0;
    glGetIntegerv(GL_UNPACK_IMAGE_DEPTH_SGIS, &unpack_image_depth_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_IMAGE_DEPTH_SGIS");
    json.writeInt(unpack_image_depth_sgis);
                json.endMember();
            }
        }

        // GL_TEXTURE_4D_SGIS
        {
            flushErrors();
    GLint texture_4d_sgis = 0;
    glGetIntegerv(GL_TEXTURE_4D_SGIS, &texture_4d_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_4D_SGIS");
    json.writeInt(texture_4d_sgis);
                json.endMember();
            }
        }

        // GL_MAX_4D_TEXTURE_SIZE_SGIS
        {
            flushErrors();
    GLint max_4d_texture_size_sgis = 0;
    glGetIntegerv(GL_MAX_4D_TEXTURE_SIZE_SGIS, &max_4d_texture_size_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_4D_TEXTURE_SIZE_SGIS");
    json.writeInt(max_4d_texture_size_sgis);
                json.endMember();
            }
        }

        // GL_PIXEL_TEX_GEN_SGIX
        {
            flushErrors();
    GLint pixel_tex_gen_sgix = 0;
    glGetIntegerv(GL_PIXEL_TEX_GEN_SGIX, &pixel_tex_gen_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TEX_GEN_SGIX");
    json.writeInt(pixel_tex_gen_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX
        {
            flushErrors();
    GLint pixel_tile_best_alignment_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX, &pixel_tile_best_alignment_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_BEST_ALIGNMENT_SGIX");
    json.writeInt(pixel_tile_best_alignment_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_CACHE_INCREMENT_SGIX
        {
            flushErrors();
    GLint pixel_tile_cache_increment_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_CACHE_INCREMENT_SGIX, &pixel_tile_cache_increment_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_CACHE_INCREMENT_SGIX");
    json.writeInt(pixel_tile_cache_increment_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_WIDTH_SGIX
        {
            flushErrors();
    GLint pixel_tile_width_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_WIDTH_SGIX, &pixel_tile_width_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_WIDTH_SGIX");
    json.writeInt(pixel_tile_width_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_HEIGHT_SGIX
        {
            flushErrors();
    GLint pixel_tile_height_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_HEIGHT_SGIX, &pixel_tile_height_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_HEIGHT_SGIX");
    json.writeInt(pixel_tile_height_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_GRID_WIDTH_SGIX
        {
            flushErrors();
    GLint pixel_tile_grid_width_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_GRID_WIDTH_SGIX, &pixel_tile_grid_width_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_GRID_WIDTH_SGIX");
    json.writeInt(pixel_tile_grid_width_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_GRID_HEIGHT_SGIX
        {
            flushErrors();
    GLint pixel_tile_grid_height_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_GRID_HEIGHT_SGIX, &pixel_tile_grid_height_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_GRID_HEIGHT_SGIX");
    json.writeInt(pixel_tile_grid_height_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_GRID_DEPTH_SGIX
        {
            flushErrors();
    GLint pixel_tile_grid_depth_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_GRID_DEPTH_SGIX, &pixel_tile_grid_depth_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_GRID_DEPTH_SGIX");
    json.writeInt(pixel_tile_grid_depth_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TILE_CACHE_SIZE_SGIX
        {
            flushErrors();
    GLint pixel_tile_cache_size_sgix = 0;
    glGetIntegerv(GL_PIXEL_TILE_CACHE_SIZE_SGIX, &pixel_tile_cache_size_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TILE_CACHE_SIZE_SGIX");
    json.writeInt(pixel_tile_cache_size_sgix);
                json.endMember();
            }
        }

        // GL_SPRITE_SGIX
        {
            flushErrors();
    GLint sprite_sgix = 0;
    glGetIntegerv(GL_SPRITE_SGIX, &sprite_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPRITE_SGIX");
    json.writeInt(sprite_sgix);
                json.endMember();
            }
        }

        // GL_SPRITE_MODE_SGIX
        {
            flushErrors();
    GLint sprite_mode_sgix = 0;
    glGetIntegerv(GL_SPRITE_MODE_SGIX, &sprite_mode_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPRITE_MODE_SGIX");
    json.writeInt(sprite_mode_sgix);
                json.endMember();
            }
        }

        // GL_SPRITE_AXIS_SGIX
        {
            flushErrors();
    GLfloat sprite_axis_sgix[3 + 1];
    memset(sprite_axis_sgix, 0, 3 * sizeof *sprite_axis_sgix);
    sprite_axis_sgix[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetFloatv(GL_SPRITE_AXIS_SGIX, sprite_axis_sgix);
    }
    assert(sprite_axis_sgix[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPRITE_AXIS_SGIX");
    json.beginArray();
    for (unsigned _i33 = 0; _i33 < 3; ++_i33) {
    json.writeFloat(sprite_axis_sgix[_i33]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPRITE_TRANSLATION_SGIX
        {
            flushErrors();
    GLfloat sprite_translation_sgix[3 + 1];
    memset(sprite_translation_sgix, 0, 3 * sizeof *sprite_translation_sgix);
    sprite_translation_sgix[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetFloatv(GL_SPRITE_TRANSLATION_SGIX, sprite_translation_sgix);
    }
    assert(sprite_translation_sgix[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPRITE_TRANSLATION_SGIX");
    json.beginArray();
    for (unsigned _i34 = 0; _i34 < 3; ++_i34) {
    json.writeFloat(sprite_translation_sgix[_i34]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_4D_BINDING_SGIS
        {
            flushErrors();
    GLint texture_4d_binding_sgis = 0;
    glGetIntegerv(GL_TEXTURE_4D_BINDING_SGIS, &texture_4d_binding_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_4D_BINDING_SGIS");
    json.writeInt(texture_4d_binding_sgis);
                json.endMember();
            }
        }

        // GL_MAX_CLIPMAP_DEPTH_SGIX
        {
            flushErrors();
    GLint max_clipmap_depth_sgix = 0;
    glGetIntegerv(GL_MAX_CLIPMAP_DEPTH_SGIX, &max_clipmap_depth_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_CLIPMAP_DEPTH_SGIX");
    json.writeInt(max_clipmap_depth_sgix);
                json.endMember();
            }
        }

        // GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX
        {
            flushErrors();
    GLint max_clipmap_virtual_depth_sgix = 0;
    glGetIntegerv(GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX, &max_clipmap_virtual_depth_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_CLIPMAP_VIRTUAL_DEPTH_SGIX");
    json.writeInt(max_clipmap_virtual_depth_sgix);
                json.endMember();
            }
        }

        // GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX
        {
            flushErrors();
    GLfloat post_texture_filter_bias_range_sgix[2 + 1];
    memset(post_texture_filter_bias_range_sgix, 0, 2 * sizeof *post_texture_filter_bias_range_sgix);
    post_texture_filter_bias_range_sgix[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX, post_texture_filter_bias_range_sgix);
    }
    assert(post_texture_filter_bias_range_sgix[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_TEXTURE_FILTER_BIAS_RANGE_SGIX");
    json.beginArray();
    for (unsigned _i35 = 0; _i35 < 2; ++_i35) {
    json.writeFloat(post_texture_filter_bias_range_sgix[_i35]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX
        {
            flushErrors();
    GLfloat post_texture_filter_scale_range_sgix[2 + 1];
    memset(post_texture_filter_scale_range_sgix, 0, 2 * sizeof *post_texture_filter_scale_range_sgix);
    post_texture_filter_scale_range_sgix[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX, post_texture_filter_scale_range_sgix);
    }
    assert(post_texture_filter_scale_range_sgix[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POST_TEXTURE_FILTER_SCALE_RANGE_SGIX");
    json.beginArray();
    for (unsigned _i36 = 0; _i36 < 2; ++_i36) {
    json.writeFloat(post_texture_filter_scale_range_sgix[_i36]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_REFERENCE_PLANE_SGIX
        {
            flushErrors();
    GLint reference_plane_sgix = 0;
    glGetIntegerv(GL_REFERENCE_PLANE_SGIX, &reference_plane_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_REFERENCE_PLANE_SGIX");
    json.writeInt(reference_plane_sgix);
                json.endMember();
            }
        }

        // GL_REFERENCE_PLANE_EQUATION_SGIX
        {
            flushErrors();
    GLfloat reference_plane_equation_sgix[4 + 1];
    memset(reference_plane_equation_sgix, 0, 4 * sizeof *reference_plane_equation_sgix);
    reference_plane_equation_sgix[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_REFERENCE_PLANE_EQUATION_SGIX, reference_plane_equation_sgix);
    }
    assert(reference_plane_equation_sgix[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_REFERENCE_PLANE_EQUATION_SGIX");
    json.beginArray();
    for (unsigned _i37 = 0; _i37 < 4; ++_i37) {
    json.writeFloat(reference_plane_equation_sgix[_i37]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_IR_INSTRUMENT1_SGIX
        {
            flushErrors();
    GLint ir_instrument1_sgix = 0;
    glGetIntegerv(GL_IR_INSTRUMENT1_SGIX, &ir_instrument1_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_IR_INSTRUMENT1_SGIX");
    json.writeInt(ir_instrument1_sgix);
                json.endMember();
            }
        }

        // GL_INSTRUMENT_MEASUREMENTS_SGIX
        {
            flushErrors();
    GLint instrument_measurements_sgix = 0;
    glGetIntegerv(GL_INSTRUMENT_MEASUREMENTS_SGIX, &instrument_measurements_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INSTRUMENT_MEASUREMENTS_SGIX");
    json.writeInt(instrument_measurements_sgix);
                json.endMember();
            }
        }

        // GL_CALLIGRAPHIC_FRAGMENT_SGIX
        {
            flushErrors();
    GLint calligraphic_fragment_sgix = 0;
    glGetIntegerv(GL_CALLIGRAPHIC_FRAGMENT_SGIX, &calligraphic_fragment_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CALLIGRAPHIC_FRAGMENT_SGIX");
    json.writeInt(calligraphic_fragment_sgix);
                json.endMember();
            }
        }

        // GL_FRAMEZOOM_SGIX
        {
            flushErrors();
    GLint framezoom_sgix = 0;
    glGetIntegerv(GL_FRAMEZOOM_SGIX, &framezoom_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEZOOM_SGIX");
    json.writeInt(framezoom_sgix);
                json.endMember();
            }
        }

        // GL_FRAMEZOOM_FACTOR_SGIX
        {
            flushErrors();
    GLint framezoom_factor_sgix = 0;
    glGetIntegerv(GL_FRAMEZOOM_FACTOR_SGIX, &framezoom_factor_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEZOOM_FACTOR_SGIX");
    json.writeInt(framezoom_factor_sgix);
                json.endMember();
            }
        }

        // GL_MAX_FRAMEZOOM_FACTOR_SGIX
        {
            flushErrors();
    GLint max_framezoom_factor_sgix = 0;
    glGetIntegerv(GL_MAX_FRAMEZOOM_FACTOR_SGIX, &max_framezoom_factor_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAMEZOOM_FACTOR_SGIX");
    json.writeInt(max_framezoom_factor_sgix);
                json.endMember();
            }
        }

        // GL_GENERATE_MIPMAP_HINT
        {
            flushErrors();
    GLint generate_mipmap_hint = 0;
    glGetIntegerv(GL_GENERATE_MIPMAP_HINT, &generate_mipmap_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GENERATE_MIPMAP_HINT");
    dumpEnum(json, generate_mipmap_hint);
                json.endMember();
            }
        }

        // GL_DEFORMATIONS_MASK_SGIX
        {
            flushErrors();
    GLint deformations_mask_sgix = 0;
    glGetIntegerv(GL_DEFORMATIONS_MASK_SGIX, &deformations_mask_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEFORMATIONS_MASK_SGIX");
    json.writeInt(deformations_mask_sgix);
                json.endMember();
            }
        }

        // GL_FOG_OFFSET_SGIX
        {
            flushErrors();
    GLint fog_offset_sgix = 0;
    glGetIntegerv(GL_FOG_OFFSET_SGIX, &fog_offset_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_OFFSET_SGIX");
    json.writeInt(fog_offset_sgix);
                json.endMember();
            }
        }

        // GL_FOG_OFFSET_VALUE_SGIX
        {
            flushErrors();
    GLfloat fog_offset_value_sgix[4 + 1];
    memset(fog_offset_value_sgix, 0, 4 * sizeof *fog_offset_value_sgix);
    fog_offset_value_sgix[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_FOG_OFFSET_VALUE_SGIX, fog_offset_value_sgix);
    }
    assert(fog_offset_value_sgix[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_OFFSET_VALUE_SGIX");
    json.beginArray();
    for (unsigned _i38 = 0; _i38 < 4; ++_i38) {
    json.writeFloat(fog_offset_value_sgix[_i38]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_ARRAY_ELEMENT_LOCK_FIRST_EXT
        {
            flushErrors();
    GLint array_element_lock_first_ext = 0;
    glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_FIRST_EXT, &array_element_lock_first_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ARRAY_ELEMENT_LOCK_FIRST_EXT");
    json.writeInt(array_element_lock_first_ext);
                json.endMember();
            }
        }

        // GL_ARRAY_ELEMENT_LOCK_COUNT_EXT
        {
            flushErrors();
    GLint array_element_lock_count_ext = 0;
    glGetIntegerv(GL_ARRAY_ELEMENT_LOCK_COUNT_EXT, &array_element_lock_count_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ARRAY_ELEMENT_LOCK_COUNT_EXT");
    json.writeInt(array_element_lock_count_ext);
                json.endMember();
            }
        }

        // GL_CULL_VERTEX_EXT
        {
            flushErrors();
    GLboolean cull_vertex_ext = 0;
    glGetBooleanv(GL_CULL_VERTEX_EXT, &cull_vertex_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_VERTEX_EXT");
    dumpBoolean(json, cull_vertex_ext);
                json.endMember();
            }
        }

        // GL_CULL_VERTEX_EYE_POSITION_EXT
        {
            flushErrors();
    GLfloat cull_vertex_eye_position_ext[4 + 1];
    memset(cull_vertex_eye_position_ext, 0, 4 * sizeof *cull_vertex_eye_position_ext);
    cull_vertex_eye_position_ext[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CULL_VERTEX_EYE_POSITION_EXT, cull_vertex_eye_position_ext);
    }
    assert(cull_vertex_eye_position_ext[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_VERTEX_EYE_POSITION_EXT");
    json.beginArray();
    for (unsigned _i39 = 0; _i39 < 4; ++_i39) {
    json.writeFloat(cull_vertex_eye_position_ext[_i39]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CULL_VERTEX_OBJECT_POSITION_EXT
        {
            flushErrors();
    GLfloat cull_vertex_object_position_ext[4 + 1];
    memset(cull_vertex_object_position_ext, 0, 4 * sizeof *cull_vertex_object_position_ext);
    cull_vertex_object_position_ext[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CULL_VERTEX_OBJECT_POSITION_EXT, cull_vertex_object_position_ext);
    }
    assert(cull_vertex_object_position_ext[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_VERTEX_OBJECT_POSITION_EXT");
    json.beginArray();
    for (unsigned _i40 = 0; _i40 < 4; ++_i40) {
    json.writeFloat(cull_vertex_object_position_ext[_i40]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_COLOR_WRITEMASK_SGIS
        {
            flushErrors();
    GLboolean texture_color_writemask_sgis[4 + 1];
    memset(texture_color_writemask_sgis, 0, 4 * sizeof *texture_color_writemask_sgis);
    texture_color_writemask_sgis[4] = (GLboolean)0xdeadc0de;
    if (4) {
        glGetBooleanv(GL_TEXTURE_COLOR_WRITEMASK_SGIS, texture_color_writemask_sgis);
    }
    assert(texture_color_writemask_sgis[4] == (GLboolean)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COLOR_WRITEMASK_SGIS");
    json.beginArray();
    for (unsigned _i41 = 0; _i41 < 4; ++_i41) {
    dumpBoolean(json, texture_color_writemask_sgis[_i41]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_LIGHT_MODEL_COLOR_CONTROL
        {
            flushErrors();
    GLint light_model_color_control = 0;
    glGetIntegerv(GL_LIGHT_MODEL_COLOR_CONTROL, &light_model_color_control);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHT_MODEL_COLOR_CONTROL");
    dumpEnum(json, light_model_color_control);
                json.endMember();
            }
        }

        // GL_MAJOR_VERSION
        {
            flushErrors();
    GLint major_version = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAJOR_VERSION");
    json.writeInt(major_version);
                json.endMember();
            }
        }

        // GL_MINOR_VERSION
        {
            flushErrors();
    GLint minor_version = 0;
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MINOR_VERSION");
    json.writeInt(minor_version);
                json.endMember();
            }
        }

        // GL_NUM_EXTENSIONS
        {
            flushErrors();
    GLint num_extensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NUM_EXTENSIONS");
    json.writeInt(num_extensions);
                json.endMember();
            }
        }

        // GL_CONTEXT_FLAGS
        {
            flushErrors();
    GLint context_flags = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONTEXT_FLAGS");
    json.writeInt(context_flags);
                json.endMember();
            }
        }

        // GL_DEBUG_OUTPUT_SYNCHRONOUS
        {
            flushErrors();
    GLboolean debug_output_synchronous = 0;
    glGetBooleanv(GL_DEBUG_OUTPUT_SYNCHRONOUS, &debug_output_synchronous);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_OUTPUT_SYNCHRONOUS");
    dumpBoolean(json, debug_output_synchronous);
                json.endMember();
            }
        }

        // GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH
        {
            flushErrors();
    GLint debug_next_logged_message_length = 0;
    glGetIntegerv(GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH, &debug_next_logged_message_length);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH");
    json.writeInt(debug_next_logged_message_length);
                json.endMember();
            }
        }

        // GL_DEBUG_CALLBACK_FUNCTION
        {
            flushErrors();
    GLvoid *debug_callback_function;
    glGetPointerv(GL_DEBUG_CALLBACK_FUNCTION, &debug_callback_function);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_CALLBACK_FUNCTION");
    json.writeInt((size_t)debug_callback_function);
                json.endMember();
            }
        }

        // GL_DEBUG_CALLBACK_USER_PARAM
        {
            flushErrors();
    GLvoid *debug_callback_user_param;
    glGetPointerv(GL_DEBUG_CALLBACK_USER_PARAM, &debug_callback_user_param);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_CALLBACK_USER_PARAM");
    json.writeInt((size_t)debug_callback_user_param);
                json.endMember();
            }
        }

        // GL_RESET_NOTIFICATION_STRATEGY_ARB
        {
            flushErrors();
    GLint reset_notification_strategy_arb = 0;
    glGetIntegerv(GL_RESET_NOTIFICATION_STRATEGY_ARB, &reset_notification_strategy_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RESET_NOTIFICATION_STRATEGY_ARB");
    dumpEnum(json, reset_notification_strategy_arb);
                json.endMember();
            }
        }

        // GL_ACTIVE_PROGRAM
        {
            flushErrors();
    GLint active_program = 0;
    glGetIntegerv(GL_ACTIVE_PROGRAM, &active_program);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACTIVE_PROGRAM");
    json.writeInt(active_program);
                json.endMember();
            }
        }

        // GL_PROGRAM_PIPELINE_BINDING
        {
            flushErrors();
    GLint program_pipeline_binding = 0;
    glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING, &program_pipeline_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_PIPELINE_BINDING");
    json.writeInt(program_pipeline_binding);
                json.endMember();
            }
        }

        // GL_MAX_VIEWPORTS
        {
            flushErrors();
    GLint max_viewports = 0;
    glGetIntegerv(GL_MAX_VIEWPORTS, &max_viewports);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VIEWPORTS");
    json.writeInt(max_viewports);
                json.endMember();
            }
        }

        // GL_VIEWPORT_SUBPIXEL_BITS
        {
            flushErrors();
    GLint viewport_subpixel_bits = 0;
    glGetIntegerv(GL_VIEWPORT_SUBPIXEL_BITS, &viewport_subpixel_bits);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VIEWPORT_SUBPIXEL_BITS");
    json.writeInt(viewport_subpixel_bits);
                json.endMember();
            }
        }

        // GL_VIEWPORT_BOUNDS_RANGE
        {
            flushErrors();
    GLfloat viewport_bounds_range[2 + 1];
    memset(viewport_bounds_range, 0, 2 * sizeof *viewport_bounds_range);
    viewport_bounds_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_VIEWPORT_BOUNDS_RANGE, viewport_bounds_range);
    }
    assert(viewport_bounds_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VIEWPORT_BOUNDS_RANGE");
    json.beginArray();
    for (unsigned _i42 = 0; _i42 < 2; ++_i42) {
    json.writeFloat(viewport_bounds_range[_i42]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_LAYER_PROVOKING_VERTEX
        {
            flushErrors();
    GLint layer_provoking_vertex = 0;
    glGetIntegerv(GL_LAYER_PROVOKING_VERTEX, &layer_provoking_vertex);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LAYER_PROVOKING_VERTEX");
    dumpEnum(json, layer_provoking_vertex);
                json.endMember();
            }
        }

        // GL_VIEWPORT_INDEX_PROVOKING_VERTEX
        {
            flushErrors();
    GLint viewport_index_provoking_vertex = 0;
    glGetIntegerv(GL_VIEWPORT_INDEX_PROVOKING_VERTEX, &viewport_index_provoking_vertex);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VIEWPORT_INDEX_PROVOKING_VERTEX");
    dumpEnum(json, viewport_index_provoking_vertex);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_SHARED_MEMORY_SIZE
        {
            flushErrors();
    GLint max_compute_shared_memory_size = 0;
    glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &max_compute_shared_memory_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_SHARED_MEMORY_SIZE");
    json.writeInt(max_compute_shared_memory_size);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_compute_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &max_compute_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_UNIFORM_COMPONENTS");
    json.writeInt(max_compute_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS
        {
            flushErrors();
    GLint max_compute_atomic_counter_buffers = 0;
    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, &max_compute_atomic_counter_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS");
    json.writeInt(max_compute_atomic_counter_buffers);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_ATOMIC_COUNTERS
        {
            flushErrors();
    GLint max_compute_atomic_counters = 0;
    glGetIntegerv(GL_MAX_COMPUTE_ATOMIC_COUNTERS, &max_compute_atomic_counters);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_ATOMIC_COUNTERS");
    json.writeInt(max_compute_atomic_counters);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_compute_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, &max_combined_compute_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_compute_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_DEBUG_GROUP_STACK_DEPTH
        {
            flushErrors();
    GLint max_debug_group_stack_depth = 0;
    glGetIntegerv(GL_MAX_DEBUG_GROUP_STACK_DEPTH, &max_debug_group_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DEBUG_GROUP_STACK_DEPTH");
    json.writeInt(max_debug_group_stack_depth);
                json.endMember();
            }
        }

        // GL_DEBUG_GROUP_STACK_DEPTH
        {
            flushErrors();
    GLint debug_group_stack_depth = 0;
    glGetIntegerv(GL_DEBUG_GROUP_STACK_DEPTH, &debug_group_stack_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_GROUP_STACK_DEPTH");
    json.writeInt(debug_group_stack_depth);
                json.endMember();
            }
        }

        // GL_MAX_UNIFORM_LOCATIONS
        {
            flushErrors();
    GLint max_uniform_locations = 0;
    glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &max_uniform_locations);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_UNIFORM_LOCATIONS");
    json.writeInt(max_uniform_locations);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET
        {
            flushErrors();
    GLint max_vertex_attrib_relative_offset = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, &max_vertex_attrib_relative_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET");
    json.writeInt(max_vertex_attrib_relative_offset);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_ATTRIB_BINDINGS
        {
            flushErrors();
    GLint max_vertex_attrib_bindings = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_vertex_attrib_bindings);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_ATTRIB_BINDINGS");
    json.writeInt(max_vertex_attrib_bindings);
                json.endMember();
            }
        }

        // GL_MAX_LABEL_LENGTH
        {
            flushErrors();
    GLint max_label_length = 0;
    glGetIntegerv(GL_MAX_LABEL_LENGTH, &max_label_length);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_LABEL_LENGTH");
    json.writeInt(max_label_length);
                json.endMember();
            }
        }

        // GL_CONVOLUTION_HINT_SGIX
        {
            flushErrors();
    GLint convolution_hint_sgix = 0;
    glGetIntegerv(GL_CONVOLUTION_HINT_SGIX, &convolution_hint_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONVOLUTION_HINT_SGIX");
    json.writeInt(convolution_hint_sgix);
                json.endMember();
            }
        }

        // GL_PIXEL_TEX_GEN_MODE_SGIX
        {
            flushErrors();
    GLint pixel_tex_gen_mode_sgix = 0;
    glGetIntegerv(GL_PIXEL_TEX_GEN_MODE_SGIX, &pixel_tex_gen_mode_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TEX_GEN_MODE_SGIX");
    json.writeInt(pixel_tex_gen_mode_sgix);
                json.endMember();
            }
        }

        // GL_TEXTURE_APPLICATION_MODE_EXT
        {
            flushErrors();
    GLint texture_application_mode_ext = 0;
    glGetIntegerv(GL_TEXTURE_APPLICATION_MODE_EXT, &texture_application_mode_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_APPLICATION_MODE_EXT");
    json.writeInt(texture_application_mode_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_LIGHT_EXT
        {
            flushErrors();
    GLint texture_light_ext = 0;
    glGetIntegerv(GL_TEXTURE_LIGHT_EXT, &texture_light_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LIGHT_EXT");
    json.writeInt(texture_light_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_MATERIAL_FACE_EXT
        {
            flushErrors();
    GLint texture_material_face_ext = 0;
    glGetIntegerv(GL_TEXTURE_MATERIAL_FACE_EXT, &texture_material_face_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MATERIAL_FACE_EXT");
    json.writeInt(texture_material_face_ext);
                json.endMember();
            }
        }

        // GL_TEXTURE_MATERIAL_PARAMETER_EXT
        {
            flushErrors();
    GLint texture_material_parameter_ext = 0;
    glGetIntegerv(GL_TEXTURE_MATERIAL_PARAMETER_EXT, &texture_material_parameter_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MATERIAL_PARAMETER_EXT");
    json.writeInt(texture_material_parameter_ext);
                json.endMember();
            }
        }

        // GL_PIXEL_TEXTURE_SGIS
        {
            flushErrors();
    GLint pixel_texture_sgis = 0;
    glGetIntegerv(GL_PIXEL_TEXTURE_SGIS, &pixel_texture_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_TEXTURE_SGIS");
    json.writeInt(pixel_texture_sgis);
                json.endMember();
            }
        }

        // GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS
        {
            flushErrors();
    GLint pixel_fragment_rgb_source_sgis = 0;
    glGetIntegerv(GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS, &pixel_fragment_rgb_source_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_FRAGMENT_RGB_SOURCE_SGIS");
    json.writeInt(pixel_fragment_rgb_source_sgis);
                json.endMember();
            }
        }

        // GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS
        {
            flushErrors();
    GLint pixel_fragment_alpha_source_sgis = 0;
    glGetIntegerv(GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS, &pixel_fragment_alpha_source_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_FRAGMENT_ALPHA_SOURCE_SGIS");
    json.writeInt(pixel_fragment_alpha_source_sgis);
                json.endMember();
            }
        }

        // GL_PIXEL_GROUP_COLOR_SGIS
        {
            flushErrors();
    GLint pixel_group_color_sgis = 0;
    glGetIntegerv(GL_PIXEL_GROUP_COLOR_SGIS, &pixel_group_color_sgis);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_GROUP_COLOR_SGIS");
    json.writeInt(pixel_group_color_sgis);
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHTING_SGIX
        {
            flushErrors();
    GLint fragment_lighting_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_LIGHTING_SGIX, &fragment_lighting_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHTING_SGIX");
    json.writeInt(fragment_lighting_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_COLOR_MATERIAL_SGIX
        {
            flushErrors();
    GLint fragment_color_material_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_COLOR_MATERIAL_SGIX, &fragment_color_material_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_COLOR_MATERIAL_SGIX");
    json.writeInt(fragment_color_material_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX
        {
            flushErrors();
    GLint fragment_color_material_face_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX, &fragment_color_material_face_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_COLOR_MATERIAL_FACE_SGIX");
    json.writeInt(fragment_color_material_face_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX
        {
            flushErrors();
    GLint fragment_color_material_parameter_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX, &fragment_color_material_parameter_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_COLOR_MATERIAL_PARAMETER_SGIX");
    json.writeInt(fragment_color_material_parameter_sgix);
                json.endMember();
            }
        }

        // GL_MAX_FRAGMENT_LIGHTS_SGIX
        {
            flushErrors();
    GLint max_fragment_lights_sgix = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_LIGHTS_SGIX, &max_fragment_lights_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAGMENT_LIGHTS_SGIX");
    json.writeInt(max_fragment_lights_sgix);
                json.endMember();
            }
        }

        // GL_MAX_ACTIVE_LIGHTS_SGIX
        {
            flushErrors();
    GLint max_active_lights_sgix = 0;
    glGetIntegerv(GL_MAX_ACTIVE_LIGHTS_SGIX, &max_active_lights_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ACTIVE_LIGHTS_SGIX");
    json.writeInt(max_active_lights_sgix);
                json.endMember();
            }
        }

        // GL_CURRENT_RASTER_NORMAL_SGIX
        {
            flushErrors();
    GLint current_raster_normal_sgix = 0;
    glGetIntegerv(GL_CURRENT_RASTER_NORMAL_SGIX, &current_raster_normal_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_RASTER_NORMAL_SGIX");
    json.writeInt(current_raster_normal_sgix);
                json.endMember();
            }
        }

        // GL_LIGHT_ENV_MODE_SGIX
        {
            flushErrors();
    GLint light_env_mode_sgix = 0;
    glGetIntegerv(GL_LIGHT_ENV_MODE_SGIX, &light_env_mode_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LIGHT_ENV_MODE_SGIX");
    json.writeInt(light_env_mode_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX
        {
            flushErrors();
    GLint fragment_light_model_local_viewer_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX, &fragment_light_model_local_viewer_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHT_MODEL_LOCAL_VIEWER_SGIX");
    json.writeInt(fragment_light_model_local_viewer_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX
        {
            flushErrors();
    GLint fragment_light_model_two_side_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX, &fragment_light_model_two_side_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHT_MODEL_TWO_SIDE_SGIX");
    json.writeInt(fragment_light_model_two_side_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX
        {
            flushErrors();
    GLfloat fragment_light_model_ambient_sgix[4 + 1];
    memset(fragment_light_model_ambient_sgix, 0, 4 * sizeof *fragment_light_model_ambient_sgix);
    fragment_light_model_ambient_sgix[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX, fragment_light_model_ambient_sgix);
    }
    assert(fragment_light_model_ambient_sgix[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHT_MODEL_AMBIENT_SGIX");
    json.beginArray();
    for (unsigned _i43 = 0; _i43 < 4; ++_i43) {
    json.writeFloat(fragment_light_model_ambient_sgix[_i43]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX
        {
            flushErrors();
    GLint fragment_light_model_normal_interpolation_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX, &fragment_light_model_normal_interpolation_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHT_MODEL_NORMAL_INTERPOLATION_SGIX");
    json.writeInt(fragment_light_model_normal_interpolation_sgix);
                json.endMember();
            }
        }

        // GL_FRAGMENT_LIGHT0_SGIX
        {
            flushErrors();
    GLint fragment_light0_sgix = 0;
    glGetIntegerv(GL_FRAGMENT_LIGHT0_SGIX, &fragment_light0_sgix);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_LIGHT0_SGIX");
    json.writeInt(fragment_light0_sgix);
                json.endMember();
            }
        }

        // GL_TANGENT_ARRAY_TYPE_EXT
        {
            flushErrors();
    GLint tangent_array_type_ext = 0;
    glGetIntegerv(GL_TANGENT_ARRAY_TYPE_EXT, &tangent_array_type_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TANGENT_ARRAY_TYPE_EXT");
    dumpEnum(json, tangent_array_type_ext);
                json.endMember();
            }
        }

        // GL_BINORMAL_ARRAY_TYPE_EXT
        {
            flushErrors();
    GLint binormal_array_type_ext = 0;
    glGetIntegerv(GL_BINORMAL_ARRAY_TYPE_EXT, &binormal_array_type_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BINORMAL_ARRAY_TYPE_EXT");
    dumpEnum(json, binormal_array_type_ext);
                json.endMember();
            }
        }

        // GL_TANGENT_ARRAY_POINTER_EXT
        {
            flushErrors();
    GLvoid *tangent_array_pointer_ext;
    glGetPointerv(GL_TANGENT_ARRAY_POINTER_EXT, &tangent_array_pointer_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TANGENT_ARRAY_POINTER_EXT");
    json.writeInt((size_t)tangent_array_pointer_ext);
                json.endMember();
            }
        }

        // GL_BINORMAL_ARRAY_POINTER_EXT
        {
            flushErrors();
    GLvoid *binormal_array_pointer_ext;
    glGetPointerv(GL_BINORMAL_ARRAY_POINTER_EXT, &binormal_array_pointer_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BINORMAL_ARRAY_POINTER_EXT");
    json.writeInt((size_t)binormal_array_pointer_ext);
                json.endMember();
            }
        }

        // GL_FOG_COORD_SRC
        {
            flushErrors();
    GLint fog_coord_src = 0;
    glGetIntegerv(GL_FOG_COORD_SRC, &fog_coord_src);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COORD_SRC");
    dumpEnum(json, fog_coord_src);
                json.endMember();
            }
        }

        // GL_CURRENT_FOG_COORD
        {
            flushErrors();
    GLfloat current_fog_coord = 0;
    glGetFloatv(GL_CURRENT_FOG_COORD, &current_fog_coord);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_FOG_COORD");
    json.writeFloat(current_fog_coord);
                json.endMember();
            }
        }

        // GL_FOG_COORD_ARRAY_TYPE
        {
            flushErrors();
    GLint fog_coord_array_type = 0;
    glGetIntegerv(GL_FOG_COORD_ARRAY_TYPE, &fog_coord_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COORD_ARRAY_TYPE");
    dumpEnum(json, fog_coord_array_type);
                json.endMember();
            }
        }

        // GL_FOG_COORD_ARRAY_STRIDE
        {
            flushErrors();
    GLint fog_coord_array_stride = 0;
    glGetIntegerv(GL_FOG_COORD_ARRAY_STRIDE, &fog_coord_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COORD_ARRAY_STRIDE");
    json.writeInt(fog_coord_array_stride);
                json.endMember();
            }
        }

        // GL_FOG_COORD_ARRAY
        {
            flushErrors();
    GLboolean fog_coord_array = 0;
    glGetBooleanv(GL_FOG_COORD_ARRAY, &fog_coord_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COORD_ARRAY");
    dumpBoolean(json, fog_coord_array);
                json.endMember();
            }
        }

        // GL_COLOR_SUM
        {
            flushErrors();
    GLboolean color_sum = 0;
    glGetBooleanv(GL_COLOR_SUM, &color_sum);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_SUM");
    dumpBoolean(json, color_sum);
                json.endMember();
            }
        }

        // GL_CURRENT_SECONDARY_COLOR
        {
            flushErrors();
    GLfloat current_secondary_color[4 + 1];
    memset(current_secondary_color, 0, 4 * sizeof *current_secondary_color);
    current_secondary_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CURRENT_SECONDARY_COLOR, current_secondary_color);
    }
    assert(current_secondary_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_SECONDARY_COLOR");
    json.beginArray();
    for (unsigned _i44 = 0; _i44 < 4; ++_i44) {
    json.writeFloat(current_secondary_color[_i44]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SECONDARY_COLOR_ARRAY_SIZE
        {
            flushErrors();
    GLint secondary_color_array_size = 0;
    glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_SIZE, &secondary_color_array_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SECONDARY_COLOR_ARRAY_SIZE");
    json.writeInt(secondary_color_array_size);
                json.endMember();
            }
        }

        // GL_SECONDARY_COLOR_ARRAY_TYPE
        {
            flushErrors();
    GLint secondary_color_array_type = 0;
    glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_TYPE, &secondary_color_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SECONDARY_COLOR_ARRAY_TYPE");
    dumpEnum(json, secondary_color_array_type);
                json.endMember();
            }
        }

        // GL_SECONDARY_COLOR_ARRAY_STRIDE
        {
            flushErrors();
    GLint secondary_color_array_stride = 0;
    glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_STRIDE, &secondary_color_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SECONDARY_COLOR_ARRAY_STRIDE");
    json.writeInt(secondary_color_array_stride);
                json.endMember();
            }
        }

        // GL_SECONDARY_COLOR_ARRAY
        {
            flushErrors();
    GLboolean secondary_color_array = 0;
    glGetBooleanv(GL_SECONDARY_COLOR_ARRAY, &secondary_color_array);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SECONDARY_COLOR_ARRAY");
    dumpBoolean(json, secondary_color_array);
                json.endMember();
            }
        }

        // GL_ALIASED_POINT_SIZE_RANGE
        {
            flushErrors();
    GLfloat aliased_point_size_range[2 + 1];
    memset(aliased_point_size_range, 0, 2 * sizeof *aliased_point_size_range);
    aliased_point_size_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, aliased_point_size_range);
    }
    assert(aliased_point_size_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALIASED_POINT_SIZE_RANGE");
    json.beginArray();
    for (unsigned _i45 = 0; _i45 < 2; ++_i45) {
    json.writeFloat(aliased_point_size_range[_i45]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_ALIASED_LINE_WIDTH_RANGE
        {
            flushErrors();
    GLfloat aliased_line_width_range[2 + 1];
    memset(aliased_line_width_range, 0, 2 * sizeof *aliased_line_width_range);
    aliased_line_width_range[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, aliased_line_width_range);
    }
    assert(aliased_line_width_range[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALIASED_LINE_WIDTH_RANGE");
    json.beginArray();
    for (unsigned _i46 = 0; _i46 < 2; ++_i46) {
    json.writeFloat(aliased_line_width_range[_i46]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_ACTIVE_TEXTURE
        {
            flushErrors();
    GLint active_texture = 0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACTIVE_TEXTURE");
    dumpEnum(json, active_texture);
                json.endMember();
            }
        }

        // GL_CLIENT_ACTIVE_TEXTURE
        {
            flushErrors();
    GLint client_active_texture = 0;
    glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE, &client_active_texture);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLIENT_ACTIVE_TEXTURE");
    dumpEnum(json, client_active_texture);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_UNITS
        {
            flushErrors();
    GLint max_texture_units = 0;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS, &max_texture_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_UNITS");
    json.writeInt(max_texture_units);
                json.endMember();
            }
        }

        // GL_TRANSPOSE_MODELVIEW_MATRIX
        {
            flushErrors();
    GLfloat transpose_modelview_matrix[16 + 1];
    memset(transpose_modelview_matrix, 0, 16 * sizeof *transpose_modelview_matrix);
    transpose_modelview_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TRANSPOSE_MODELVIEW_MATRIX, transpose_modelview_matrix);
    }
    assert(transpose_modelview_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSPOSE_MODELVIEW_MATRIX");
    json.beginArray();
    for (unsigned _i47 = 0; _i47 < 16; ++_i47) {
    json.writeFloat(transpose_modelview_matrix[_i47]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TRANSPOSE_PROJECTION_MATRIX
        {
            flushErrors();
    GLfloat transpose_projection_matrix[16 + 1];
    memset(transpose_projection_matrix, 0, 16 * sizeof *transpose_projection_matrix);
    transpose_projection_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TRANSPOSE_PROJECTION_MATRIX, transpose_projection_matrix);
    }
    assert(transpose_projection_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSPOSE_PROJECTION_MATRIX");
    json.beginArray();
    for (unsigned _i48 = 0; _i48 < 16; ++_i48) {
    json.writeFloat(transpose_projection_matrix[_i48]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TRANSPOSE_TEXTURE_MATRIX
        {
            flushErrors();
    GLfloat transpose_texture_matrix[16 + 1];
    memset(transpose_texture_matrix, 0, 16 * sizeof *transpose_texture_matrix);
    transpose_texture_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TRANSPOSE_TEXTURE_MATRIX, transpose_texture_matrix);
    }
    assert(transpose_texture_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSPOSE_TEXTURE_MATRIX");
    json.beginArray();
    for (unsigned _i49 = 0; _i49 < 16; ++_i49) {
    json.writeFloat(transpose_texture_matrix[_i49]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TRANSPOSE_COLOR_MATRIX
        {
            flushErrors();
    GLfloat transpose_color_matrix[16 + 1];
    memset(transpose_color_matrix, 0, 16 * sizeof *transpose_color_matrix);
    transpose_color_matrix[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TRANSPOSE_COLOR_MATRIX, transpose_color_matrix);
    }
    assert(transpose_color_matrix[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSPOSE_COLOR_MATRIX");
    json.beginArray();
    for (unsigned _i50 = 0; _i50 < 16; ++_i50) {
    json.writeFloat(transpose_color_matrix[_i50]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAX_RENDERBUFFER_SIZE
        {
            flushErrors();
    GLint max_renderbuffer_size = 0;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &max_renderbuffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_RENDERBUFFER_SIZE");
    json.writeInt(max_renderbuffer_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPRESSION_HINT
        {
            flushErrors();
    GLint texture_compression_hint = 0;
    glGetIntegerv(GL_TEXTURE_COMPRESSION_HINT, &texture_compression_hint);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPRESSION_HINT");
    dumpEnum(json, texture_compression_hint);
                json.endMember();
            }
        }

        // GL_MAX_RECTANGLE_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_rectangle_texture_size = 0;
    glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE, &max_rectangle_texture_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_RECTANGLE_TEXTURE_SIZE");
    json.writeInt(max_rectangle_texture_size);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_LOD_BIAS
        {
            flushErrors();
    GLfloat max_texture_lod_bias = 0;
    glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS, &max_texture_lod_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_LOD_BIAS");
    json.writeFloat(max_texture_lod_bias);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
        {
            flushErrors();
    GLfloat max_texture_max_anisotropy_ext = 0;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_texture_max_anisotropy_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT");
    json.writeFloat(max_texture_max_anisotropy_ext);
                json.endMember();
            }
        }

        // GL_MAX_SHININESS_NV
        {
            flushErrors();
    GLfloat max_shininess_nv = 0;
    glGetFloatv(GL_MAX_SHININESS_NV, &max_shininess_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SHININESS_NV");
    json.writeFloat(max_shininess_nv);
                json.endMember();
            }
        }

        // GL_MAX_SPOT_EXPONENT_NV
        {
            flushErrors();
    GLfloat max_spot_exponent_nv = 0;
    glGetFloatv(GL_MAX_SPOT_EXPONENT_NV, &max_spot_exponent_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SPOT_EXPONENT_NV");
    json.writeFloat(max_spot_exponent_nv);
                json.endMember();
            }
        }

        // GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT
        {
            flushErrors();
    GLint vertex_weight_array_type_ext = 0;
    glGetIntegerv(GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT, &vertex_weight_array_type_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_WEIGHT_ARRAY_TYPE_EXT");
    dumpEnum(json, vertex_weight_array_type_ext);
                json.endMember();
            }
        }

        // GL_MAX_CUBE_MAP_TEXTURE_SIZE
        {
            flushErrors();
    GLint max_cube_map_texture_size = 0;
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &max_cube_map_texture_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_CUBE_MAP_TEXTURE_SIZE");
    json.writeInt(max_cube_map_texture_size);
                json.endMember();
            }
        }

        // GL_CONSTANT_COLOR0_NV
        {
            flushErrors();
    GLfloat constant_color0_nv[4 + 1];
    memset(constant_color0_nv, 0, 4 * sizeof *constant_color0_nv);
    constant_color0_nv[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CONSTANT_COLOR0_NV, constant_color0_nv);
    }
    assert(constant_color0_nv[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONSTANT_COLOR0_NV");
    json.beginArray();
    for (unsigned _i51 = 0; _i51 < 4; ++_i51) {
    json.writeFloat(constant_color0_nv[_i51]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_CONSTANT_COLOR1_NV
        {
            flushErrors();
    GLfloat constant_color1_nv[4 + 1];
    memset(constant_color1_nv, 0, 4 * sizeof *constant_color1_nv);
    constant_color1_nv[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_CONSTANT_COLOR1_NV, constant_color1_nv);
    }
    assert(constant_color1_nv[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONSTANT_COLOR1_NV");
    json.beginArray();
    for (unsigned _i52 = 0; _i52 < 4; ++_i52) {
    json.writeFloat(constant_color1_nv[_i52]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MULTISAMPLE_FILTER_HINT_NV
        {
            flushErrors();
    GLint multisample_filter_hint_nv = 0;
    glGetIntegerv(GL_MULTISAMPLE_FILTER_HINT_NV, &multisample_filter_hint_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MULTISAMPLE_FILTER_HINT_NV");
    dumpEnum(json, multisample_filter_hint_nv);
                json.endMember();
            }
        }

        // GL_MAX_GENERAL_COMBINERS_NV
        {
            flushErrors();
    GLint max_general_combiners_nv = 0;
    glGetIntegerv(GL_MAX_GENERAL_COMBINERS_NV, &max_general_combiners_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GENERAL_COMBINERS_NV");
    json.writeInt(max_general_combiners_nv);
                json.endMember();
            }
        }

        // GL_NUM_GENERAL_COMBINERS_NV
        {
            flushErrors();
    GLint num_general_combiners_nv = 0;
    glGetIntegerv(GL_NUM_GENERAL_COMBINERS_NV, &num_general_combiners_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NUM_GENERAL_COMBINERS_NV");
    json.writeInt(num_general_combiners_nv);
                json.endMember();
            }
        }

        // GL_COLOR_SUM_CLAMP_NV
        {
            flushErrors();
    GLboolean color_sum_clamp_nv = 0;
    glGetBooleanv(GL_COLOR_SUM_CLAMP_NV, &color_sum_clamp_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_SUM_CLAMP_NV");
    dumpBoolean(json, color_sum_clamp_nv);
                json.endMember();
            }
        }

        // GL_FOG_DISTANCE_MODE_NV
        {
            flushErrors();
    GLint fog_distance_mode_nv = 0;
    glGetIntegerv(GL_FOG_DISTANCE_MODE_NV, &fog_distance_mode_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_DISTANCE_MODE_NV");
    dumpEnum(json, fog_distance_mode_nv);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_BINDING
        {
            flushErrors();
    GLint vertex_array_binding = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vertex_array_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_BINDING");
    json.writeInt(vertex_array_binding);
                json.endMember();
            }
        }

        // GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN
        {
            flushErrors();
    GLint replacement_code_array_type_sun = 0;
    glGetIntegerv(GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN, &replacement_code_array_type_sun);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_REPLACEMENT_CODE_ARRAY_TYPE_SUN");
    dumpEnum(json, replacement_code_array_type_sun);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB
        {
            flushErrors();
    GLint max_program_matrix_stack_depth_arb = 0;
    glGetIntegerv(GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB, &max_program_matrix_stack_depth_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB");
    json.writeInt(max_program_matrix_stack_depth_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_MATRICES_ARB
        {
            flushErrors();
    GLint max_program_matrices_arb = 0;
    glGetIntegerv(GL_MAX_PROGRAM_MATRICES_ARB, &max_program_matrices_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_MATRICES_ARB");
    json.writeInt(max_program_matrices_arb);
                json.endMember();
            }
        }

        // GL_CURRENT_MATRIX_STACK_DEPTH_ARB
        {
            flushErrors();
    GLint current_matrix_stack_depth_arb = 0;
    glGetIntegerv(GL_CURRENT_MATRIX_STACK_DEPTH_ARB, &current_matrix_stack_depth_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_MATRIX_STACK_DEPTH_ARB");
    json.writeInt(current_matrix_stack_depth_arb);
                json.endMember();
            }
        }

        // GL_CURRENT_MATRIX_ARB
        {
            flushErrors();
    GLfloat current_matrix_arb[16 + 1];
    memset(current_matrix_arb, 0, 16 * sizeof *current_matrix_arb);
    current_matrix_arb[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_CURRENT_MATRIX_ARB, current_matrix_arb);
    }
    assert(current_matrix_arb[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_MATRIX_ARB");
    json.beginArray();
    for (unsigned _i53 = 0; _i53 < 16; ++_i53) {
    json.writeFloat(current_matrix_arb[_i53]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_PROGRAM_POINT_SIZE
        {
            flushErrors();
    GLboolean program_point_size = 0;
    glGetBooleanv(GL_PROGRAM_POINT_SIZE, &program_point_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_POINT_SIZE");
    dumpBoolean(json, program_point_size);
                json.endMember();
            }
        }

        // GL_VERTEX_PROGRAM_TWO_SIDE
        {
            flushErrors();
    GLboolean vertex_program_two_side = 0;
    glGetBooleanv(GL_VERTEX_PROGRAM_TWO_SIDE, &vertex_program_two_side);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_PROGRAM_TWO_SIDE");
    dumpBoolean(json, vertex_program_two_side);
                json.endMember();
            }
        }

        // GL_VERTEX_PROGRAM_BINDING_NV
        {
            flushErrors();
    GLint vertex_program_binding_nv = 0;
    glGetIntegerv(GL_VERTEX_PROGRAM_BINDING_NV, &vertex_program_binding_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_PROGRAM_BINDING_NV");
    json.writeInt(vertex_program_binding_nv);
                json.endMember();
            }
        }

        // GL_PROGRAM_ERROR_POSITION_ARB
        {
            flushErrors();
    GLint program_error_position_arb = 0;
    glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &program_error_position_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ERROR_POSITION_ARB");
    json.writeInt(program_error_position_arb);
                json.endMember();
            }
        }

        // GL_DEPTH_CLAMP
        {
            flushErrors();
    GLboolean depth_clamp = 0;
    glGetBooleanv(GL_DEPTH_CLAMP, &depth_clamp);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_CLAMP");
    dumpBoolean(json, depth_clamp);
                json.endMember();
            }
        }

        // GL_NUM_COMPRESSED_TEXTURE_FORMATS
        {
            flushErrors();
    GLint num_compressed_texture_formats = 0;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &num_compressed_texture_formats);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NUM_COMPRESSED_TEXTURE_FORMATS");
    json.writeInt(num_compressed_texture_formats);
                json.endMember();
            }
        }

        // GL_COMPRESSED_TEXTURE_FORMATS
        {
            flushErrors();
    size_t _compressed_texture_formats_length = _glGetInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS);
    GLint *compressed_texture_formats = _allocator.alloc<GLint>(_compressed_texture_formats_length + 1);
    memset(compressed_texture_formats, 0, _compressed_texture_formats_length * sizeof *compressed_texture_formats);
    compressed_texture_formats[_compressed_texture_formats_length] = (GLint)0xdeadc0de;
    if (_compressed_texture_formats_length) {
        glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, compressed_texture_formats);
    }
    assert(compressed_texture_formats[_compressed_texture_formats_length] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COMPRESSED_TEXTURE_FORMATS");
    json.beginArray();
    for (unsigned _i54 = 0; _i54 < _glGetInteger(GL_NUM_COMPRESSED_TEXTURE_FORMATS); ++_i54) {
    dumpEnum(json, compressed_texture_formats[_i54]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_UNITS_ARB
        {
            flushErrors();
    GLint max_vertex_units_arb = 0;
    glGetIntegerv(GL_MAX_VERTEX_UNITS_ARB, &max_vertex_units_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_UNITS_ARB");
    json.writeInt(max_vertex_units_arb);
                json.endMember();
            }
        }

        // GL_ACTIVE_VERTEX_UNITS_ARB
        {
            flushErrors();
    GLint active_vertex_units_arb = 0;
    glGetIntegerv(GL_ACTIVE_VERTEX_UNITS_ARB, &active_vertex_units_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACTIVE_VERTEX_UNITS_ARB");
    json.writeInt(active_vertex_units_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_SUM_UNITY_ARB
        {
            flushErrors();
    GLboolean weight_sum_unity_arb = 0;
    glGetBooleanv(GL_WEIGHT_SUM_UNITY_ARB, &weight_sum_unity_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_SUM_UNITY_ARB");
    dumpBoolean(json, weight_sum_unity_arb);
                json.endMember();
            }
        }

        // GL_VERTEX_BLEND_ARB
        {
            flushErrors();
    GLboolean vertex_blend_arb = 0;
    glGetBooleanv(GL_VERTEX_BLEND_ARB, &vertex_blend_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_BLEND_ARB");
    dumpBoolean(json, vertex_blend_arb);
                json.endMember();
            }
        }

        // GL_CURRENT_WEIGHT_ARB
        {
            flushErrors();
    GLfloat current_weight_arb = 0;
    glGetFloatv(GL_CURRENT_WEIGHT_ARB, &current_weight_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_WEIGHT_ARB");
    json.writeFloat(current_weight_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_TYPE_ARB
        {
            flushErrors();
    GLint weight_array_type_arb = 0;
    glGetIntegerv(GL_WEIGHT_ARRAY_TYPE_ARB, &weight_array_type_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_TYPE_ARB");
    dumpEnum(json, weight_array_type_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_STRIDE_ARB
        {
            flushErrors();
    GLint weight_array_stride_arb = 0;
    glGetIntegerv(GL_WEIGHT_ARRAY_STRIDE_ARB, &weight_array_stride_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_STRIDE_ARB");
    json.writeInt(weight_array_stride_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_SIZE_ARB
        {
            flushErrors();
    GLint weight_array_size_arb = 0;
    glGetIntegerv(GL_WEIGHT_ARRAY_SIZE_ARB, &weight_array_size_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_SIZE_ARB");
    json.writeInt(weight_array_size_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_POINTER_ARB
        {
            flushErrors();
    GLvoid *weight_array_pointer_arb;
    glGetPointerv(GL_WEIGHT_ARRAY_POINTER_ARB, &weight_array_pointer_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_POINTER_ARB");
    json.writeInt((size_t)weight_array_pointer_arb);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_ARB
        {
            flushErrors();
    GLboolean weight_array_arb = 0;
    glGetBooleanv(GL_WEIGHT_ARRAY_ARB, &weight_array_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_ARB");
    dumpBoolean(json, weight_array_arb);
                json.endMember();
            }
        }

        // GL_PACK_INVERT_MESA
        {
            flushErrors();
    GLboolean pack_invert_mesa = 0;
    glGetBooleanv(GL_PACK_INVERT_MESA, &pack_invert_mesa);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_INVERT_MESA");
    dumpBoolean(json, pack_invert_mesa);
                json.endMember();
            }
        }

        // GL_ELEMENT_ARRAY_TYPE_ATI
        {
            flushErrors();
    GLint element_array_type_ati = 0;
    glGetIntegerv(GL_ELEMENT_ARRAY_TYPE_ATI, &element_array_type_ati);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ELEMENT_ARRAY_TYPE_ATI");
    dumpEnum(json, element_array_type_ati);
                json.endMember();
            }
        }

        // GL_VERTEX_SHADER_BINDING_EXT
        {
            flushErrors();
    GLint vertex_shader_binding_ext = 0;
    glGetIntegerv(GL_VERTEX_SHADER_BINDING_EXT, &vertex_shader_binding_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_SHADER_BINDING_EXT");
    json.writeInt(vertex_shader_binding_ext);
                json.endMember();
            }
        }

        // GL_VARIANT_ARRAY_TYPE_EXT
        {
            flushErrors();
    GLint variant_array_type_ext = 0;
    glGetIntegerv(GL_VARIANT_ARRAY_TYPE_EXT, &variant_array_type_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VARIANT_ARRAY_TYPE_EXT");
    dumpEnum(json, variant_array_type_ext);
                json.endMember();
            }
        }

        // GL_NUM_PROGRAM_BINARY_FORMATS
        {
            flushErrors();
    GLint num_program_binary_formats = 0;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &num_program_binary_formats);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NUM_PROGRAM_BINARY_FORMATS");
    json.writeInt(num_program_binary_formats);
                json.endMember();
            }
        }

        // GL_PROGRAM_BINARY_FORMATS
        {
            flushErrors();
    size_t _program_binary_formats_length = _glGetInteger(GL_NUM_PROGRAM_BINARY_FORMATS);
    GLint *program_binary_formats = _allocator.alloc<GLint>(_program_binary_formats_length + 1);
    memset(program_binary_formats, 0, _program_binary_formats_length * sizeof *program_binary_formats);
    program_binary_formats[_program_binary_formats_length] = (GLint)0xdeadc0de;
    if (_program_binary_formats_length) {
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, program_binary_formats);
    }
    assert(program_binary_formats[_program_binary_formats_length] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_BINARY_FORMATS");
    json.beginArray();
    for (unsigned _i55 = 0; _i55 < _glGetInteger(GL_NUM_PROGRAM_BINARY_FORMATS); ++_i55) {
    dumpEnum(json, program_binary_formats[_i55]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_STENCIL_BACK_FUNC
        {
            flushErrors();
    GLint stencil_back_func = 0;
    glGetIntegerv(GL_STENCIL_BACK_FUNC, &stencil_back_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_BACK_FUNC");
    dumpEnum(json, stencil_back_func);
                json.endMember();
            }
        }

        // GL_STENCIL_BACK_FAIL
        {
            flushErrors();
    GLint stencil_back_fail = 0;
    glGetIntegerv(GL_STENCIL_BACK_FAIL, &stencil_back_fail);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_BACK_FAIL");
    dumpEnum(json, stencil_back_fail);
                json.endMember();
            }
        }

        // GL_STENCIL_BACK_PASS_DEPTH_FAIL
        {
            flushErrors();
    GLint stencil_back_pass_depth_fail = 0;
    glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_FAIL, &stencil_back_pass_depth_fail);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_BACK_PASS_DEPTH_FAIL");
    dumpEnum(json, stencil_back_pass_depth_fail);
                json.endMember();
            }
        }

        // GL_STENCIL_BACK_PASS_DEPTH_PASS
        {
            flushErrors();
    GLint stencil_back_pass_depth_pass = 0;
    glGetIntegerv(GL_STENCIL_BACK_PASS_DEPTH_PASS, &stencil_back_pass_depth_pass);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_BACK_PASS_DEPTH_PASS");
    dumpEnum(json, stencil_back_pass_depth_pass);
                json.endMember();
            }
        }

        // GL_RGBA_FLOAT_MODE_ARB
        {
            flushErrors();
    GLboolean rgba_float_mode_arb = 0;
    glGetBooleanv(GL_RGBA_FLOAT_MODE_ARB, &rgba_float_mode_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RGBA_FLOAT_MODE_ARB");
    dumpBoolean(json, rgba_float_mode_arb);
                json.endMember();
            }
        }

        // GL_MAX_DRAW_BUFFERS
        {
            flushErrors();
    GLint max_draw_buffers = 0;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &max_draw_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DRAW_BUFFERS");
    json.writeInt(max_draw_buffers);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER0
        {
            flushErrors();
    GLint draw_buffer0 = 0;
    glGetIntegerv(GL_DRAW_BUFFER0, &draw_buffer0);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER0");
    dumpEnum(json, draw_buffer0);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER1
        {
            flushErrors();
    GLint draw_buffer1 = 0;
    glGetIntegerv(GL_DRAW_BUFFER1, &draw_buffer1);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER1");
    dumpEnum(json, draw_buffer1);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER2
        {
            flushErrors();
    GLint draw_buffer2 = 0;
    glGetIntegerv(GL_DRAW_BUFFER2, &draw_buffer2);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER2");
    dumpEnum(json, draw_buffer2);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER3
        {
            flushErrors();
    GLint draw_buffer3 = 0;
    glGetIntegerv(GL_DRAW_BUFFER3, &draw_buffer3);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER3");
    dumpEnum(json, draw_buffer3);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER4
        {
            flushErrors();
    GLint draw_buffer4 = 0;
    glGetIntegerv(GL_DRAW_BUFFER4, &draw_buffer4);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER4");
    dumpEnum(json, draw_buffer4);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER5
        {
            flushErrors();
    GLint draw_buffer5 = 0;
    glGetIntegerv(GL_DRAW_BUFFER5, &draw_buffer5);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER5");
    dumpEnum(json, draw_buffer5);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER6
        {
            flushErrors();
    GLint draw_buffer6 = 0;
    glGetIntegerv(GL_DRAW_BUFFER6, &draw_buffer6);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER6");
    dumpEnum(json, draw_buffer6);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER7
        {
            flushErrors();
    GLint draw_buffer7 = 0;
    glGetIntegerv(GL_DRAW_BUFFER7, &draw_buffer7);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER7");
    dumpEnum(json, draw_buffer7);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER8
        {
            flushErrors();
    GLint draw_buffer8 = 0;
    glGetIntegerv(GL_DRAW_BUFFER8, &draw_buffer8);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER8");
    dumpEnum(json, draw_buffer8);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER9
        {
            flushErrors();
    GLint draw_buffer9 = 0;
    glGetIntegerv(GL_DRAW_BUFFER9, &draw_buffer9);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER9");
    dumpEnum(json, draw_buffer9);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER10
        {
            flushErrors();
    GLint draw_buffer10 = 0;
    glGetIntegerv(GL_DRAW_BUFFER10, &draw_buffer10);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER10");
    dumpEnum(json, draw_buffer10);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER11
        {
            flushErrors();
    GLint draw_buffer11 = 0;
    glGetIntegerv(GL_DRAW_BUFFER11, &draw_buffer11);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER11");
    dumpEnum(json, draw_buffer11);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER12
        {
            flushErrors();
    GLint draw_buffer12 = 0;
    glGetIntegerv(GL_DRAW_BUFFER12, &draw_buffer12);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER12");
    dumpEnum(json, draw_buffer12);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER13
        {
            flushErrors();
    GLint draw_buffer13 = 0;
    glGetIntegerv(GL_DRAW_BUFFER13, &draw_buffer13);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER13");
    dumpEnum(json, draw_buffer13);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER14
        {
            flushErrors();
    GLint draw_buffer14 = 0;
    glGetIntegerv(GL_DRAW_BUFFER14, &draw_buffer14);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER14");
    dumpEnum(json, draw_buffer14);
                json.endMember();
            }
        }

        // GL_DRAW_BUFFER15
        {
            flushErrors();
    GLint draw_buffer15 = 0;
    glGetIntegerv(GL_DRAW_BUFFER15, &draw_buffer15);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_BUFFER15");
    dumpEnum(json, draw_buffer15);
                json.endMember();
            }
        }

        // GL_BLEND_EQUATION_ALPHA
        {
            flushErrors();
    GLint blend_equation_alpha = 0;
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &blend_equation_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BLEND_EQUATION_ALPHA");
    dumpEnum(json, blend_equation_alpha);
                json.endMember();
            }
        }

        // GL_MATRIX_PALETTE_ARB
        {
            flushErrors();
    GLboolean matrix_palette_arb = 0;
    glGetBooleanv(GL_MATRIX_PALETTE_ARB, &matrix_palette_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_PALETTE_ARB");
    dumpBoolean(json, matrix_palette_arb);
                json.endMember();
            }
        }

        // GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB
        {
            flushErrors();
    GLint max_matrix_palette_stack_depth_arb = 0;
    glGetIntegerv(GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB, &max_matrix_palette_stack_depth_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_MATRIX_PALETTE_STACK_DEPTH_ARB");
    json.writeInt(max_matrix_palette_stack_depth_arb);
                json.endMember();
            }
        }

        // GL_MAX_PALETTE_MATRICES_ARB
        {
            flushErrors();
    GLint max_palette_matrices_arb = 0;
    glGetIntegerv(GL_MAX_PALETTE_MATRICES_ARB, &max_palette_matrices_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PALETTE_MATRICES_ARB");
    json.writeInt(max_palette_matrices_arb);
                json.endMember();
            }
        }

        // GL_CURRENT_PALETTE_MATRIX_ARB
        {
            flushErrors();
    GLint current_palette_matrix_arb = 0;
    glGetIntegerv(GL_CURRENT_PALETTE_MATRIX_ARB, &current_palette_matrix_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_PALETTE_MATRIX_ARB");
    json.writeInt(current_palette_matrix_arb);
                json.endMember();
            }
        }

        // GL_MATRIX_INDEX_ARRAY_ARB
        {
            flushErrors();
    GLboolean matrix_index_array_arb = 0;
    glGetBooleanv(GL_MATRIX_INDEX_ARRAY_ARB, &matrix_index_array_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_INDEX_ARRAY_ARB");
    dumpBoolean(json, matrix_index_array_arb);
                json.endMember();
            }
        }

        // GL_CURRENT_MATRIX_INDEX_ARB
        {
            flushErrors();
    GLint current_matrix_index_arb = 0;
    glGetIntegerv(GL_CURRENT_MATRIX_INDEX_ARB, &current_matrix_index_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_MATRIX_INDEX_ARB");
    json.writeInt(current_matrix_index_arb);
                json.endMember();
            }
        }

        // GL_MATRIX_INDEX_ARRAY_SIZE_ARB
        {
            flushErrors();
    GLint matrix_index_array_size_arb = 0;
    glGetIntegerv(GL_MATRIX_INDEX_ARRAY_SIZE_ARB, &matrix_index_array_size_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_INDEX_ARRAY_SIZE_ARB");
    json.writeInt(matrix_index_array_size_arb);
                json.endMember();
            }
        }

        // GL_MATRIX_INDEX_ARRAY_TYPE_ARB
        {
            flushErrors();
    GLint matrix_index_array_type_arb = 0;
    glGetIntegerv(GL_MATRIX_INDEX_ARRAY_TYPE_ARB, &matrix_index_array_type_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_INDEX_ARRAY_TYPE_ARB");
    dumpEnum(json, matrix_index_array_type_arb);
                json.endMember();
            }
        }

        // GL_MATRIX_INDEX_ARRAY_STRIDE_ARB
        {
            flushErrors();
    GLint matrix_index_array_stride_arb = 0;
    glGetIntegerv(GL_MATRIX_INDEX_ARRAY_STRIDE_ARB, &matrix_index_array_stride_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_INDEX_ARRAY_STRIDE_ARB");
    json.writeInt(matrix_index_array_stride_arb);
                json.endMember();
            }
        }

        // GL_MATRIX_INDEX_ARRAY_POINTER_ARB
        {
            flushErrors();
    GLvoid *matrix_index_array_pointer_arb;
    glGetPointerv(GL_MATRIX_INDEX_ARRAY_POINTER_ARB, &matrix_index_array_pointer_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MATRIX_INDEX_ARRAY_POINTER_ARB");
    json.writeInt((size_t)matrix_index_array_pointer_arb);
                json.endMember();
            }
        }

        // GL_TEXTURE_CUBE_MAP_SEAMLESS
        {
            flushErrors();
    GLboolean texture_cube_map_seamless = 0;
    glGetBooleanv(GL_TEXTURE_CUBE_MAP_SEAMLESS, &texture_cube_map_seamless);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_CUBE_MAP_SEAMLESS");
    dumpBoolean(json, texture_cube_map_seamless);
                json.endMember();
            }
        }

        // GL_POINT_SPRITE
        {
            flushErrors();
    GLboolean point_sprite = 0;
    glGetBooleanv(GL_POINT_SPRITE, &point_sprite);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SPRITE");
    dumpBoolean(json, point_sprite);
                json.endMember();
            }
        }

        // GL_POINT_SPRITE_R_MODE_NV
        {
            flushErrors();
    GLint point_sprite_r_mode_nv = 0;
    glGetIntegerv(GL_POINT_SPRITE_R_MODE_NV, &point_sprite_r_mode_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SPRITE_R_MODE_NV");
    dumpEnum(json, point_sprite_r_mode_nv);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_ATTRIBS
        {
            flushErrors();
    GLint max_vertex_attribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attribs);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_ATTRIBS");
    json.writeInt(max_vertex_attribs);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_COORDS
        {
            flushErrors();
    GLint max_texture_coords = 0;
    glGetIntegerv(GL_MAX_TEXTURE_COORDS, &max_texture_coords);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_COORDS");
    json.writeInt(max_texture_coords);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_texture_image_units = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_texture_image_units);
                json.endMember();
            }
        }

        // GL_FRAGMENT_PROGRAM_BINDING_NV
        {
            flushErrors();
    GLint fragment_program_binding_nv = 0;
    glGetIntegerv(GL_FRAGMENT_PROGRAM_BINDING_NV, &fragment_program_binding_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAGMENT_PROGRAM_BINDING_NV");
    json.writeInt(fragment_program_binding_nv);
                json.endMember();
            }
        }

        // GL_PROGRAM_ERROR_STRING_ARB
        {
            flushErrors();
    char * program_error_string_arb = (char *)glGetString(GL_PROGRAM_ERROR_STRING_ARB);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ERROR_STRING_ARB");
    json.writeString((const char *)program_error_string_arb);
                json.endMember();
            }
        }

        // GL_DEPTH_BOUNDS_TEST_EXT
        {
            flushErrors();
    GLboolean depth_bounds_test_ext = 0;
    glGetBooleanv(GL_DEPTH_BOUNDS_TEST_EXT, &depth_bounds_test_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_BOUNDS_TEST_EXT");
    dumpBoolean(json, depth_bounds_test_ext);
                json.endMember();
            }
        }

        // GL_DEPTH_BOUNDS_EXT
        {
            flushErrors();
    GLfloat depth_bounds_ext[2 + 1];
    memset(depth_bounds_ext, 0, 2 * sizeof *depth_bounds_ext);
    depth_bounds_ext[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_DEPTH_BOUNDS_EXT, depth_bounds_ext);
    }
    assert(depth_bounds_ext[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEPTH_BOUNDS_EXT");
    json.beginArray();
    for (unsigned _i56 = 0; _i56 < 2; ++_i56) {
    json.writeFloat(depth_bounds_ext[_i56]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint array_buffer_binding = 0;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ARRAY_BUFFER_BINDING");
    json.writeInt(array_buffer_binding);
                json.endMember();
            }
        }

        // GL_ELEMENT_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint element_array_buffer_binding = 0;
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &element_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ELEMENT_ARRAY_BUFFER_BINDING");
    json.writeInt(element_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_VERTEX_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint vertex_array_buffer_binding = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &vertex_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ARRAY_BUFFER_BINDING");
    json.writeInt(vertex_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_NORMAL_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint normal_array_buffer_binding = 0;
    glGetIntegerv(GL_NORMAL_ARRAY_BUFFER_BINDING, &normal_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NORMAL_ARRAY_BUFFER_BINDING");
    json.writeInt(normal_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_COLOR_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint color_array_buffer_binding = 0;
    glGetIntegerv(GL_COLOR_ARRAY_BUFFER_BINDING, &color_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_ARRAY_BUFFER_BINDING");
    json.writeInt(color_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_INDEX_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint index_array_buffer_binding = 0;
    glGetIntegerv(GL_INDEX_ARRAY_BUFFER_BINDING, &index_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_INDEX_ARRAY_BUFFER_BINDING");
    json.writeInt(index_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint texture_coord_array_buffer_binding = 0;
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING, &texture_coord_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING");
    json.writeInt(texture_coord_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_EDGE_FLAG_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint edge_flag_array_buffer_binding = 0;
    glGetIntegerv(GL_EDGE_FLAG_ARRAY_BUFFER_BINDING, &edge_flag_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EDGE_FLAG_ARRAY_BUFFER_BINDING");
    json.writeInt(edge_flag_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint secondary_color_array_buffer_binding = 0;
    glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING, &secondary_color_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING");
    json.writeInt(secondary_color_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_FOG_COORD_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint fog_coord_array_buffer_binding = 0;
    glGetIntegerv(GL_FOG_COORD_ARRAY_BUFFER_BINDING, &fog_coord_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FOG_COORD_ARRAY_BUFFER_BINDING");
    json.writeInt(fog_coord_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_WEIGHT_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint weight_array_buffer_binding = 0;
    glGetIntegerv(GL_WEIGHT_ARRAY_BUFFER_BINDING, &weight_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_WEIGHT_ARRAY_BUFFER_BINDING");
    json.writeInt(weight_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_TRANSPOSE_CURRENT_MATRIX_ARB
        {
            flushErrors();
    GLfloat transpose_current_matrix_arb[16 + 1];
    memset(transpose_current_matrix_arb, 0, 16 * sizeof *transpose_current_matrix_arb);
    transpose_current_matrix_arb[16] = (GLfloat)0xdeadc0de;
    if (16) {
        glGetFloatv(GL_TRANSPOSE_CURRENT_MATRIX_ARB, transpose_current_matrix_arb);
    }
    assert(transpose_current_matrix_arb[16] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSPOSE_CURRENT_MATRIX_ARB");
    json.beginArray();
    for (unsigned _i57 = 0; _i57 < 16; ++_i57) {
    json.writeFloat(transpose_current_matrix_arb[_i57]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_PIXEL_PACK_BUFFER_BINDING
        {
            flushErrors();
    GLint pixel_pack_buffer_binding = 0;
    glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &pixel_pack_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_PACK_BUFFER_BINDING");
    json.writeInt(pixel_pack_buffer_binding);
                json.endMember();
            }
        }

        // GL_PIXEL_UNPACK_BUFFER_BINDING
        {
            flushErrors();
    GLint pixel_unpack_buffer_binding = 0;
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &pixel_unpack_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PIXEL_UNPACK_BUFFER_BINDING");
    json.writeInt(pixel_unpack_buffer_binding);
                json.endMember();
            }
        }

        // GL_MAX_DUAL_SOURCE_DRAW_BUFFERS
        {
            flushErrors();
    GLint max_dual_source_draw_buffers = 0;
    glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, &max_dual_source_draw_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DUAL_SOURCE_DRAW_BUFFERS");
    json.writeInt(max_dual_source_draw_buffers);
                json.endMember();
            }
        }

        // GL_MAX_ARRAY_TEXTURE_LAYERS
        {
            flushErrors();
    GLint max_array_texture_layers = 0;
    glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &max_array_texture_layers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ARRAY_TEXTURE_LAYERS");
    json.writeInt(max_array_texture_layers);
                json.endMember();
            }
        }

        // GL_MIN_PROGRAM_TEXEL_OFFSET
        {
            flushErrors();
    GLfloat min_program_texel_offset = 0;
    glGetFloatv(GL_MIN_PROGRAM_TEXEL_OFFSET, &min_program_texel_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MIN_PROGRAM_TEXEL_OFFSET");
    json.writeFloat(min_program_texel_offset);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEXEL_OFFSET
        {
            flushErrors();
    GLfloat max_program_texel_offset = 0;
    glGetFloatv(GL_MAX_PROGRAM_TEXEL_OFFSET, &max_program_texel_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEXEL_OFFSET");
    json.writeFloat(max_program_texel_offset);
                json.endMember();
            }
        }

        // GL_STENCIL_TEST_TWO_SIDE_EXT
        {
            flushErrors();
    GLboolean stencil_test_two_side_ext = 0;
    glGetBooleanv(GL_STENCIL_TEST_TWO_SIDE_EXT, &stencil_test_two_side_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_STENCIL_TEST_TWO_SIDE_EXT");
    dumpBoolean(json, stencil_test_two_side_ext);
                json.endMember();
            }
        }

        // GL_ACTIVE_STENCIL_FACE_EXT
        {
            flushErrors();
    GLint active_stencil_face_ext = 0;
    glGetIntegerv(GL_ACTIVE_STENCIL_FACE_EXT, &active_stencil_face_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ACTIVE_STENCIL_FACE_EXT");
    dumpEnum(json, active_stencil_face_ext);
                json.endMember();
            }
        }

        // GL_CLAMP_VERTEX_COLOR
        {
            flushErrors();
    GLboolean clamp_vertex_color = 0;
    glGetBooleanv(GL_CLAMP_VERTEX_COLOR, &clamp_vertex_color);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLAMP_VERTEX_COLOR");
    dumpBoolean(json, clamp_vertex_color);
                json.endMember();
            }
        }

        // GL_CLAMP_FRAGMENT_COLOR
        {
            flushErrors();
    GLboolean clamp_fragment_color = 0;
    glGetBooleanv(GL_CLAMP_FRAGMENT_COLOR, &clamp_fragment_color);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLAMP_FRAGMENT_COLOR");
    dumpBoolean(json, clamp_fragment_color);
                json.endMember();
            }
        }

        // GL_CLAMP_READ_COLOR
        {
            flushErrors();
    GLboolean clamp_read_color = 0;
    glGetBooleanv(GL_CLAMP_READ_COLOR, &clamp_read_color);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CLAMP_READ_COLOR");
    dumpBoolean(json, clamp_read_color);
                json.endMember();
            }
        }

        // GL_ELEMENT_ARRAY_TYPE_APPLE
        {
            flushErrors();
    GLint element_array_type_apple = 0;
    glGetIntegerv(GL_ELEMENT_ARRAY_TYPE_APPLE, &element_array_type_apple);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ELEMENT_ARRAY_TYPE_APPLE");
    dumpEnum(json, element_array_type_apple);
                json.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_BINDING
        {
            flushErrors();
    GLint uniform_buffer_binding = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_BINDING, &uniform_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNIFORM_BUFFER_BINDING");
    json.writeInt(uniform_buffer_binding);
                json.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_START
        {
            flushErrors();
    GLint uniform_buffer_start = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_START, &uniform_buffer_start);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNIFORM_BUFFER_START");
    json.writeInt(uniform_buffer_start);
                json.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_SIZE
        {
            flushErrors();
    GLint uniform_buffer_size = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_SIZE, &uniform_buffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNIFORM_BUFFER_SIZE");
    json.writeInt(uniform_buffer_size);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_vertex_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &max_vertex_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_UNIFORM_BLOCKS");
    json.writeInt(max_vertex_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_geometry_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &max_geometry_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_UNIFORM_BLOCKS");
    json.writeInt(max_geometry_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_fragment_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &max_fragment_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAGMENT_UNIFORM_BLOCKS");
    json.writeInt(max_fragment_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_combined_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS, &max_combined_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_UNIFORM_BLOCKS");
    json.writeInt(max_combined_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_UNIFORM_BUFFER_BINDINGS
        {
            flushErrors();
    GLint max_uniform_buffer_bindings = 0;
    glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &max_uniform_buffer_bindings);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_UNIFORM_BUFFER_BINDINGS");
    json.writeInt(max_uniform_buffer_bindings);
                json.endMember();
            }
        }

        // GL_MAX_UNIFORM_BLOCK_SIZE
        {
            flushErrors();
    GLint max_uniform_block_size = 0;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_uniform_block_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_UNIFORM_BLOCK_SIZE");
    json.writeInt(max_uniform_block_size);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_vertex_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, &max_combined_vertex_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_vertex_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_geometry_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, &max_combined_geometry_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_geometry_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_fragment_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, &max_combined_fragment_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_fragment_uniform_components);
                json.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT
        {
            flushErrors();
    GLint uniform_buffer_offset_alignment = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &uniform_buffer_offset_alignment);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT");
    json.writeInt(uniform_buffer_offset_alignment);
                json.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_fragment_uniform_components = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &max_fragment_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS");
    json.writeInt(max_fragment_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_vertex_uniform_components = 0;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max_vertex_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_UNIFORM_COMPONENTS");
    json.writeInt(max_vertex_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_VARYING_COMPONENTS
        {
            flushErrors();
    GLint max_varying_components = 0;
    glGetIntegerv(GL_MAX_VARYING_COMPONENTS, &max_varying_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VARYING_COMPONENTS");
    json.writeInt(max_varying_components);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_vertex_texture_image_units = 0;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &max_vertex_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_vertex_texture_image_units);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_combined_texture_image_units = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_combined_texture_image_units);
                json.endMember();
            }
        }

        // GL_SHADING_LANGUAGE_VERSION
        {
            flushErrors();
    char * shading_language_version = (char *)glGetString(GL_SHADING_LANGUAGE_VERSION);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHADING_LANGUAGE_VERSION");
    json.writeString((const char *)shading_language_version);
                json.endMember();
            }
        }

        // GL_CURRENT_PROGRAM
        {
            flushErrors();
    GLint current_program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_PROGRAM");
    json.writeInt(current_program);
                json.endMember();
            }
        }

        // GL_IMPLEMENTATION_COLOR_READ_TYPE
        {
            flushErrors();
    GLint implementation_color_read_type = 0;
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &implementation_color_read_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_IMPLEMENTATION_COLOR_READ_TYPE");
    dumpEnum(json, implementation_color_read_type);
                json.endMember();
            }
        }

        // GL_IMPLEMENTATION_COLOR_READ_FORMAT
        {
            flushErrors();
    GLint implementation_color_read_format = 0;
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &implementation_color_read_format);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_IMPLEMENTATION_COLOR_READ_FORMAT");
    dumpEnum(json, implementation_color_read_format);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_geometry_texture_image_units = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &max_geometry_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_geometry_texture_image_units);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER
        {
            flushErrors();
    GLint texture_buffer = 0;
    glGetIntegerv(GL_TEXTURE_BUFFER, &texture_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER");
    json.writeInt(texture_buffer);
                json.endMember();
            }
        }

        // GL_MAX_TEXTURE_BUFFER_SIZE
        {
            flushErrors();
    GLint max_texture_buffer_size = 0;
    glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &max_texture_buffer_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TEXTURE_BUFFER_SIZE");
    json.writeInt(max_texture_buffer_size);
                json.endMember();
            }
        }

        // GL_TEXTURE_BINDING_BUFFER
        {
            flushErrors();
    GLint texture_binding_buffer = 0;
    glGetIntegerv(GL_TEXTURE_BINDING_BUFFER, &texture_binding_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BINDING_BUFFER");
    json.writeInt(texture_binding_buffer);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER_DATA_STORE_BINDING
        {
            flushErrors();
    GLint texture_buffer_data_store_binding = 0;
    glGetIntegerv(GL_TEXTURE_BUFFER_DATA_STORE_BINDING, &texture_buffer_data_store_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER_DATA_STORE_BINDING");
    json.writeInt(texture_buffer_data_store_binding);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER_FORMAT
        {
            flushErrors();
    GLint texture_buffer_format = 0;
    glGetIntegerv(GL_TEXTURE_BUFFER_FORMAT, &texture_buffer_format);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER_FORMAT");
    dumpEnum(json, texture_buffer_format);
                json.endMember();
            }
        }

        // GL_RASTERIZER_DISCARD
        {
            flushErrors();
    GLboolean rasterizer_discard = 0;
    glGetBooleanv(GL_RASTERIZER_DISCARD, &rasterizer_discard);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RASTERIZER_DISCARD");
    dumpBoolean(json, rasterizer_discard);
                json.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_BINDING
        {
            flushErrors();
    GLint transform_feedback_buffer_binding = 0;
    glGetIntegerv(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, &transform_feedback_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_BINDING");
    json.writeInt(transform_feedback_buffer_binding);
                json.endMember();
            }
        }

        // GL_POINT_SPRITE_COORD_ORIGIN
        {
            flushErrors();
    GLint point_sprite_coord_origin = 0;
    glGetIntegerv(GL_POINT_SPRITE_COORD_ORIGIN, &point_sprite_coord_origin);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POINT_SPRITE_COORD_ORIGIN");
    dumpEnum(json, point_sprite_coord_origin);
                json.endMember();
            }
        }

        // GL_DRAW_FRAMEBUFFER_BINDING
        {
            flushErrors();
    GLint draw_framebuffer_binding = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw_framebuffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_FRAMEBUFFER_BINDING");
    json.writeInt(draw_framebuffer_binding);
                json.endMember();
            }
        }

        // GL_RENDERBUFFER_BINDING
        {
            flushErrors();
    GLint renderbuffer_binding = 0;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &renderbuffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RENDERBUFFER_BINDING");
    json.writeInt(renderbuffer_binding);
                json.endMember();
            }
        }

        // GL_READ_FRAMEBUFFER_BINDING
        {
            flushErrors();
    GLint read_framebuffer_binding = 0;
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read_framebuffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_READ_FRAMEBUFFER_BINDING");
    json.writeInt(read_framebuffer_binding);
                json.endMember();
            }
        }

        // GL_MAX_COLOR_ATTACHMENTS
        {
            flushErrors();
    GLint max_color_attachments = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COLOR_ATTACHMENTS");
    json.writeInt(max_color_attachments);
                json.endMember();
            }
        }

        // GL_MAX_SAMPLES
        {
            flushErrors();
    GLint max_samples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SAMPLES");
    json.writeInt(max_samples);
                json.endMember();
            }
        }

        // GL_PRIMITIVE_RESTART_FIXED_INDEX
        {
            flushErrors();
    GLboolean primitive_restart_fixed_index = 0;
    glGetBooleanv(GL_PRIMITIVE_RESTART_FIXED_INDEX, &primitive_restart_fixed_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PRIMITIVE_RESTART_FIXED_INDEX");
    dumpBoolean(json, primitive_restart_fixed_index);
                json.endMember();
            }
        }

        // GL_MAX_ELEMENT_INDEX
        {
            flushErrors();
    GLint max_element_index = 0;
    glGetIntegerv(GL_MAX_ELEMENT_INDEX, &max_element_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_ELEMENT_INDEX");
    json.writeInt(max_element_index);
                json.endMember();
            }
        }

        // GL_RGBA_INTEGER_MODE_EXT
        {
            flushErrors();
    GLboolean rgba_integer_mode_ext = 0;
    glGetBooleanv(GL_RGBA_INTEGER_MODE_EXT, &rgba_integer_mode_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RGBA_INTEGER_MODE_EXT");
    dumpBoolean(json, rgba_integer_mode_ext);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_SRGB
        {
            flushErrors();
    GLboolean framebuffer_srgb = 0;
    glGetBooleanv(GL_FRAMEBUFFER_SRGB, &framebuffer_srgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_SRGB");
    dumpBoolean(json, framebuffer_srgb);
                json.endMember();
            }
        }

        // GL_FRAMEBUFFER_SRGB_CAPABLE_EXT
        {
            flushErrors();
    GLboolean framebuffer_srgb_capable_ext = 0;
    glGetBooleanv(GL_FRAMEBUFFER_SRGB_CAPABLE_EXT, &framebuffer_srgb_capable_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_FRAMEBUFFER_SRGB_CAPABLE_EXT");
    dumpBoolean(json, framebuffer_srgb_capable_ext);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB
        {
            flushErrors();
    GLint max_geometry_varying_components_arb = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB, &max_geometry_varying_components_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB");
    json.writeInt(max_geometry_varying_components_arb);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_VARYING_COMPONENTS_ARB
        {
            flushErrors();
    GLint max_vertex_varying_components_arb = 0;
    glGetIntegerv(GL_MAX_VERTEX_VARYING_COMPONENTS_ARB, &max_vertex_varying_components_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_VARYING_COMPONENTS_ARB");
    json.writeInt(max_vertex_varying_components_arb);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_geometry_uniform_components = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &max_geometry_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS");
    json.writeInt(max_geometry_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_OUTPUT_VERTICES
        {
            flushErrors();
    GLint max_geometry_output_vertices = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &max_geometry_output_vertices);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_OUTPUT_VERTICES");
    json.writeInt(max_geometry_output_vertices);
                json.endMember();
            }
        }

        // GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS
        {
            flushErrors();
    GLint max_geometry_total_output_components = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &max_geometry_total_output_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS");
    json.writeInt(max_geometry_total_output_components);
                json.endMember();
            }
        }

        // GL_MAX_SUBROUTINES
        {
            flushErrors();
    GLint max_subroutines = 0;
    glGetIntegerv(GL_MAX_SUBROUTINES, &max_subroutines);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SUBROUTINES");
    json.writeInt(max_subroutines);
                json.endMember();
            }
        }

        // GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS
        {
            flushErrors();
    GLint max_subroutine_uniform_locations = 0;
    glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &max_subroutine_uniform_locations);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS");
    json.writeInt(max_subroutine_uniform_locations);
                json.endMember();
            }
        }

        // GL_MAX_BINDABLE_UNIFORM_SIZE_EXT
        {
            flushErrors();
    GLint max_bindable_uniform_size_ext = 0;
    glGetIntegerv(GL_MAX_BINDABLE_UNIFORM_SIZE_EXT, &max_bindable_uniform_size_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_BINDABLE_UNIFORM_SIZE_EXT");
    json.writeInt(max_bindable_uniform_size_ext);
                json.endMember();
            }
        }

        // GL_UNIFORM_BUFFER_BINDING_EXT
        {
            flushErrors();
    GLint uniform_buffer_binding_ext = 0;
    glGetIntegerv(GL_UNIFORM_BUFFER_BINDING_EXT, &uniform_buffer_binding_ext);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNIFORM_BUFFER_BINDING_EXT");
    json.writeInt(uniform_buffer_binding_ext);
                json.endMember();
            }
        }

        // GL_NUM_SHADER_BINARY_FORMATS
        {
            flushErrors();
    GLint num_shader_binary_formats = 0;
    glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &num_shader_binary_formats);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_NUM_SHADER_BINARY_FORMATS");
    json.writeInt(num_shader_binary_formats);
                json.endMember();
            }
        }

        // GL_SHADER_COMPILER
        {
            flushErrors();
    GLboolean shader_compiler = 0;
    glGetBooleanv(GL_SHADER_COMPILER, &shader_compiler);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHADER_COMPILER");
    dumpBoolean(json, shader_compiler);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_UNIFORM_VECTORS
        {
            flushErrors();
    GLint max_vertex_uniform_vectors = 0;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &max_vertex_uniform_vectors);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_UNIFORM_VECTORS");
    json.writeInt(max_vertex_uniform_vectors);
                json.endMember();
            }
        }

        // GL_MAX_VARYING_VECTORS
        {
            flushErrors();
    GLint max_varying_vectors = 0;
    glGetIntegerv(GL_MAX_VARYING_VECTORS, &max_varying_vectors);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VARYING_VECTORS");
    json.writeInt(max_varying_vectors);
                json.endMember();
            }
        }

        // GL_MAX_FRAGMENT_UNIFORM_VECTORS
        {
            flushErrors();
    GLint max_fragment_uniform_vectors = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &max_fragment_uniform_vectors);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAGMENT_UNIFORM_VECTORS");
    json.writeInt(max_fragment_uniform_vectors);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_tess_control_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS, &max_combined_tess_control_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_tess_control_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_combined_tess_evaluation_uniform_components = 0;
    glGetIntegerv(GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS, &max_combined_tess_evaluation_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS");
    json.writeInt(max_combined_tess_evaluation_uniform_components);
                json.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED
        {
            flushErrors();
    GLboolean transform_feedback_buffer_paused = 0;
    glGetBooleanv(GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED, &transform_feedback_buffer_paused);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED");
    dumpBoolean(json, transform_feedback_buffer_paused);
                json.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE
        {
            flushErrors();
    GLboolean transform_feedback_buffer_active = 0;
    glGetBooleanv(GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE, &transform_feedback_buffer_active);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE");
    dumpBoolean(json, transform_feedback_buffer_active);
                json.endMember();
            }
        }

        // GL_TRANSFORM_FEEDBACK_BINDING
        {
            flushErrors();
    GLint transform_feedback_binding = 0;
    glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &transform_feedback_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TRANSFORM_FEEDBACK_BINDING");
    json.writeInt(transform_feedback_binding);
                json.endMember();
            }
        }

        // GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION
        {
            flushErrors();
    GLboolean quads_follow_provoking_vertex_convention = 0;
    glGetBooleanv(GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION, &quads_follow_provoking_vertex_convention);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION");
    dumpBoolean(json, quads_follow_provoking_vertex_convention);
                json.endMember();
            }
        }

        // GL_PROVOKING_VERTEX
        {
            flushErrors();
    GLint provoking_vertex = 0;
    glGetIntegerv(GL_PROVOKING_VERTEX, &provoking_vertex);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROVOKING_VERTEX");
    dumpEnum(json, provoking_vertex);
                json.endMember();
            }
        }

        // GL_SAMPLE_MASK
        {
            flushErrors();
    GLboolean sample_mask = 0;
    glGetBooleanv(GL_SAMPLE_MASK, &sample_mask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_MASK");
    dumpBoolean(json, sample_mask);
                json.endMember();
            }
        }

        // GL_SAMPLE_MASK_VALUE
        {
            flushErrors();
    GLint sample_mask_value = 0;
    glGetIntegerv(GL_SAMPLE_MASK_VALUE, &sample_mask_value);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SAMPLE_MASK_VALUE");
    json.writeInt(sample_mask_value);
                json.endMember();
            }
        }

        // GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV
        {
            flushErrors();
    GLint texture_renderbuffer_data_store_binding_nv = 0;
    glGetIntegerv(GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV, &texture_renderbuffer_data_store_binding_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_RENDERBUFFER_DATA_STORE_BINDING_NV");
    json.writeInt(texture_renderbuffer_data_store_binding_nv);
                json.endMember();
            }
        }

        // GL_MAX_SAMPLE_MASK_WORDS
        {
            flushErrors();
    GLint max_sample_mask_words = 0;
    glGetIntegerv(GL_MAX_SAMPLE_MASK_WORDS, &max_sample_mask_words);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_SAMPLE_MASK_WORDS");
    json.writeInt(max_sample_mask_words);
                json.endMember();
            }
        }

        // GL_MAX_TRANSFORM_FEEDBACK_BUFFERS
        {
            flushErrors();
    GLint max_transform_feedback_buffers = 0;
    glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_BUFFERS, &max_transform_feedback_buffers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TRANSFORM_FEEDBACK_BUFFERS");
    json.writeInt(max_transform_feedback_buffers);
                json.endMember();
            }
        }

        // GL_MAX_VERTEX_STREAMS
        {
            flushErrors();
    GLint max_vertex_streams = 0;
    glGetIntegerv(GL_MAX_VERTEX_STREAMS, &max_vertex_streams);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_VERTEX_STREAMS");
    json.writeInt(max_vertex_streams);
                json.endMember();
            }
        }

        // GL_PATCH_VERTICES
        {
            flushErrors();
    GLint patch_vertices = 0;
    glGetIntegerv(GL_PATCH_VERTICES, &patch_vertices);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PATCH_VERTICES");
    json.writeInt(patch_vertices);
                json.endMember();
            }
        }

        // GL_PATCH_DEFAULT_INNER_LEVEL
        {
            flushErrors();
    GLfloat patch_default_inner_level[2 + 1];
    memset(patch_default_inner_level, 0, 2 * sizeof *patch_default_inner_level);
    patch_default_inner_level[2] = (GLfloat)0xdeadc0de;
    if (2) {
        glGetFloatv(GL_PATCH_DEFAULT_INNER_LEVEL, patch_default_inner_level);
    }
    assert(patch_default_inner_level[2] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PATCH_DEFAULT_INNER_LEVEL");
    json.beginArray();
    for (unsigned _i58 = 0; _i58 < 2; ++_i58) {
    json.writeFloat(patch_default_inner_level[_i58]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_PATCH_DEFAULT_OUTER_LEVEL
        {
            flushErrors();
    GLfloat patch_default_outer_level[4 + 1];
    memset(patch_default_outer_level, 0, 4 * sizeof *patch_default_outer_level);
    patch_default_outer_level[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetFloatv(GL_PATCH_DEFAULT_OUTER_LEVEL, patch_default_outer_level);
    }
    assert(patch_default_outer_level[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PATCH_DEFAULT_OUTER_LEVEL");
    json.beginArray();
    for (unsigned _i59 = 0; _i59 < 4; ++_i59) {
    json.writeFloat(patch_default_outer_level[_i59]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TESS_GEN_MODE
        {
            flushErrors();
    GLint tess_gen_mode = 0;
    glGetIntegerv(GL_TESS_GEN_MODE, &tess_gen_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TESS_GEN_MODE");
    dumpEnum(json, tess_gen_mode);
                json.endMember();
            }
        }

        // GL_TESS_GEN_SPACING
        {
            flushErrors();
    GLint tess_gen_spacing = 0;
    glGetIntegerv(GL_TESS_GEN_SPACING, &tess_gen_spacing);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TESS_GEN_SPACING");
    dumpEnum(json, tess_gen_spacing);
                json.endMember();
            }
        }

        // GL_TESS_GEN_VERTEX_ORDER
        {
            flushErrors();
    GLint tess_gen_vertex_order = 0;
    glGetIntegerv(GL_TESS_GEN_VERTEX_ORDER, &tess_gen_vertex_order);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TESS_GEN_VERTEX_ORDER");
    dumpEnum(json, tess_gen_vertex_order);
                json.endMember();
            }
        }

        // GL_TESS_GEN_POINT_MODE
        {
            flushErrors();
    GLint tess_gen_point_mode = 0;
    glGetIntegerv(GL_TESS_GEN_POINT_MODE, &tess_gen_point_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TESS_GEN_POINT_MODE");
    dumpEnum(json, tess_gen_point_mode);
                json.endMember();
            }
        }

        // GL_MAX_PATCH_VERTICES
        {
            flushErrors();
    GLint max_patch_vertices = 0;
    glGetIntegerv(GL_MAX_PATCH_VERTICES, &max_patch_vertices);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PATCH_VERTICES");
    json.writeInt(max_patch_vertices);
                json.endMember();
            }
        }

        // GL_MAX_TESS_GEN_LEVEL
        {
            flushErrors();
    GLint max_tess_gen_level = 0;
    glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &max_tess_gen_level);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_GEN_LEVEL");
    json.writeInt(max_tess_gen_level);
                json.endMember();
            }
        }

        // GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_tess_control_uniform_components = 0;
    glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &max_tess_control_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS");
    json.writeInt(max_tess_control_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS
        {
            flushErrors();
    GLint max_tess_evaluation_uniform_components = 0;
    glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, &max_tess_evaluation_uniform_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS");
    json.writeInt(max_tess_evaluation_uniform_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_tess_control_texture_image_units = 0;
    glGetIntegerv(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, &max_tess_control_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_tess_control_texture_image_units);
                json.endMember();
            }
        }

        // GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_tess_evaluation_texture_image_units = 0;
    glGetIntegerv(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, &max_tess_evaluation_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_tess_evaluation_texture_image_units);
                json.endMember();
            }
        }

        // GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS
        {
            flushErrors();
    GLint max_tess_control_output_components = 0;
    glGetIntegerv(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, &max_tess_control_output_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS");
    json.writeInt(max_tess_control_output_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_PATCH_COMPONENTS
        {
            flushErrors();
    GLint max_tess_patch_components = 0;
    glGetIntegerv(GL_MAX_TESS_PATCH_COMPONENTS, &max_tess_patch_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_PATCH_COMPONENTS");
    json.writeInt(max_tess_patch_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS
        {
            flushErrors();
    GLint max_tess_control_total_output_components = 0;
    glGetIntegerv(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, &max_tess_control_total_output_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS");
    json.writeInt(max_tess_control_total_output_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS
        {
            flushErrors();
    GLint max_tess_evaluation_output_components = 0;
    glGetIntegerv(GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS, &max_tess_evaluation_output_components);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS");
    json.writeInt(max_tess_evaluation_output_components);
                json.endMember();
            }
        }

        // GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_tess_control_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, &max_tess_control_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS");
    json.writeInt(max_tess_control_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_tess_evaluation_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, &max_tess_evaluation_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS");
    json.writeInt(max_tess_evaluation_uniform_blocks);
                json.endMember();
            }
        }

        // GL_COPY_READ_BUFFER
        {
            flushErrors();
    GLint copy_read_buffer = 0;
    glGetIntegerv(GL_COPY_READ_BUFFER, &copy_read_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COPY_READ_BUFFER");
    json.writeInt(copy_read_buffer);
                json.endMember();
            }
        }

        // GL_COPY_WRITE_BUFFER
        {
            flushErrors();
    GLint copy_write_buffer = 0;
    glGetIntegerv(GL_COPY_WRITE_BUFFER, &copy_write_buffer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COPY_WRITE_BUFFER");
    json.writeInt(copy_write_buffer);
                json.endMember();
            }
        }

        // GL_DRAW_INDIRECT_BUFFER_BINDING
        {
            flushErrors();
    GLint draw_indirect_buffer_binding = 0;
    glGetIntegerv(GL_DRAW_INDIRECT_BUFFER_BINDING, &draw_indirect_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DRAW_INDIRECT_BUFFER_BINDING");
    json.writeInt(draw_indirect_buffer_binding);
                json.endMember();
            }
        }

        // GL_PRIMITIVE_RESTART
        {
            flushErrors();
    GLboolean primitive_restart = 0;
    glGetBooleanv(GL_PRIMITIVE_RESTART, &primitive_restart);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PRIMITIVE_RESTART");
    dumpBoolean(json, primitive_restart);
                json.endMember();
            }
        }

        // GL_PRIMITIVE_RESTART_INDEX
        {
            flushErrors();
    GLint primitive_restart_index = 0;
    glGetIntegerv(GL_PRIMITIVE_RESTART_INDEX, &primitive_restart_index);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PRIMITIVE_RESTART_INDEX");
    json.writeInt(primitive_restart_index);
                json.endMember();
            }
        }

        // GL_VIDEO_BUFFER_BINDING_NV
        {
            flushErrors();
    GLint video_buffer_binding_nv = 0;
    glGetIntegerv(GL_VIDEO_BUFFER_BINDING_NV, &video_buffer_binding_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VIDEO_BUFFER_BINDING_NV");
    json.writeInt(video_buffer_binding_nv);
                json.endMember();
            }
        }

        // GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX
        {
            flushErrors();
    GLint gpu_memory_info_dedicated_vidmem_nvx = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &gpu_memory_info_dedicated_vidmem_nvx);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX");
    json.writeInt(gpu_memory_info_dedicated_vidmem_nvx);
                json.endMember();
            }
        }

        // GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX
        {
            flushErrors();
    GLint gpu_memory_info_total_available_memory_nvx = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &gpu_memory_info_total_available_memory_nvx);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX");
    json.writeInt(gpu_memory_info_total_available_memory_nvx);
                json.endMember();
            }
        }

        // GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX
        {
            flushErrors();
    GLint gpu_memory_info_current_available_vidmem_nvx = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &gpu_memory_info_current_available_vidmem_nvx);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX");
    json.writeInt(gpu_memory_info_current_available_vidmem_nvx);
                json.endMember();
            }
        }

        // GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX
        {
            flushErrors();
    GLint gpu_memory_info_eviction_count_nvx = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &gpu_memory_info_eviction_count_nvx);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX");
    json.writeInt(gpu_memory_info_eviction_count_nvx);
                json.endMember();
            }
        }

        // GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX
        {
            flushErrors();
    GLint gpu_memory_info_evicted_memory_nvx = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &gpu_memory_info_evicted_memory_nvx);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX");
    json.writeInt(gpu_memory_info_evicted_memory_nvx);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS
        {
            flushErrors();
    GLint max_compute_shader_storage_blocks = 0;
    glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &max_compute_shader_storage_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS");
    json.writeInt(max_compute_shader_storage_blocks);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_LOCAL_INVOCATIONS
        {
            flushErrors();
    GLint max_compute_local_invocations = 0;
    glGetIntegerv(GL_MAX_COMPUTE_LOCAL_INVOCATIONS, &max_compute_local_invocations);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_LOCAL_INVOCATIONS");
    json.writeInt(max_compute_local_invocations);
                json.endMember();
            }
        }

        // GL_DISPATCH_INDIRECT_BUFFER_BINDING
        {
            flushErrors();
    GLint dispatch_indirect_buffer_binding = 0;
    glGetIntegerv(GL_DISPATCH_INDIRECT_BUFFER_BINDING, &dispatch_indirect_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DISPATCH_INDIRECT_BUFFER_BINDING");
    json.writeInt(dispatch_indirect_buffer_binding);
                json.endMember();
            }
        }

        // GL_MAX_COLOR_TEXTURE_SAMPLES
        {
            flushErrors();
    GLint max_color_texture_samples = 0;
    glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &max_color_texture_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COLOR_TEXTURE_SAMPLES");
    json.writeInt(max_color_texture_samples);
                json.endMember();
            }
        }

        // GL_MAX_DEPTH_TEXTURE_SAMPLES
        {
            flushErrors();
    GLint max_depth_texture_samples = 0;
    glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES, &max_depth_texture_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DEPTH_TEXTURE_SAMPLES");
    json.writeInt(max_depth_texture_samples);
                json.endMember();
            }
        }

        // GL_MAX_INTEGER_SAMPLES
        {
            flushErrors();
    GLint max_integer_samples = 0;
    glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &max_integer_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_INTEGER_SAMPLES");
    json.writeInt(max_integer_samples);
                json.endMember();
            }
        }

        // GL_CONTEXT_PROFILE_MASK
        {
            flushErrors();
    GLint context_profile_mask = 0;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &context_profile_mask);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONTEXT_PROFILE_MASK");
    json.writeInt(context_profile_mask);
                json.endMember();
            }
        }

        // GL_UNPACK_COMPRESSED_BLOCK_WIDTH
        {
            flushErrors();
    GLint unpack_compressed_block_width = 0;
    glGetIntegerv(GL_UNPACK_COMPRESSED_BLOCK_WIDTH, &unpack_compressed_block_width);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_COMPRESSED_BLOCK_WIDTH");
    json.writeInt(unpack_compressed_block_width);
                json.endMember();
            }
        }

        // GL_UNPACK_COMPRESSED_BLOCK_HEIGHT
        {
            flushErrors();
    GLint unpack_compressed_block_height = 0;
    glGetIntegerv(GL_UNPACK_COMPRESSED_BLOCK_HEIGHT, &unpack_compressed_block_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_COMPRESSED_BLOCK_HEIGHT");
    json.writeInt(unpack_compressed_block_height);
                json.endMember();
            }
        }

        // GL_UNPACK_COMPRESSED_BLOCK_DEPTH
        {
            flushErrors();
    GLint unpack_compressed_block_depth = 0;
    glGetIntegerv(GL_UNPACK_COMPRESSED_BLOCK_DEPTH, &unpack_compressed_block_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_COMPRESSED_BLOCK_DEPTH");
    json.writeInt(unpack_compressed_block_depth);
                json.endMember();
            }
        }

        // GL_UNPACK_COMPRESSED_BLOCK_SIZE
        {
            flushErrors();
    GLint unpack_compressed_block_size = 0;
    glGetIntegerv(GL_UNPACK_COMPRESSED_BLOCK_SIZE, &unpack_compressed_block_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_UNPACK_COMPRESSED_BLOCK_SIZE");
    json.writeInt(unpack_compressed_block_size);
                json.endMember();
            }
        }

        // GL_PACK_COMPRESSED_BLOCK_WIDTH
        {
            flushErrors();
    GLint pack_compressed_block_width = 0;
    glGetIntegerv(GL_PACK_COMPRESSED_BLOCK_WIDTH, &pack_compressed_block_width);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_COMPRESSED_BLOCK_WIDTH");
    json.writeInt(pack_compressed_block_width);
                json.endMember();
            }
        }

        // GL_PACK_COMPRESSED_BLOCK_HEIGHT
        {
            flushErrors();
    GLint pack_compressed_block_height = 0;
    glGetIntegerv(GL_PACK_COMPRESSED_BLOCK_HEIGHT, &pack_compressed_block_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_COMPRESSED_BLOCK_HEIGHT");
    json.writeInt(pack_compressed_block_height);
                json.endMember();
            }
        }

        // GL_PACK_COMPRESSED_BLOCK_DEPTH
        {
            flushErrors();
    GLint pack_compressed_block_depth = 0;
    glGetIntegerv(GL_PACK_COMPRESSED_BLOCK_DEPTH, &pack_compressed_block_depth);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_COMPRESSED_BLOCK_DEPTH");
    json.writeInt(pack_compressed_block_depth);
                json.endMember();
            }
        }

        // GL_PACK_COMPRESSED_BLOCK_SIZE
        {
            flushErrors();
    GLint pack_compressed_block_size = 0;
    glGetIntegerv(GL_PACK_COMPRESSED_BLOCK_SIZE, &pack_compressed_block_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PACK_COMPRESSED_BLOCK_SIZE");
    json.writeInt(pack_compressed_block_size);
                json.endMember();
            }
        }

        // GL_MAX_DEBUG_MESSAGE_LENGTH
        {
            flushErrors();
    GLint max_debug_message_length = 0;
    glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &max_debug_message_length);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DEBUG_MESSAGE_LENGTH");
    json.writeInt(max_debug_message_length);
                json.endMember();
            }
        }

        // GL_MAX_DEBUG_LOGGED_MESSAGES
        {
            flushErrors();
    GLint max_debug_logged_messages = 0;
    glGetIntegerv(GL_MAX_DEBUG_LOGGED_MESSAGES, &max_debug_logged_messages);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_DEBUG_LOGGED_MESSAGES");
    json.writeInt(max_debug_logged_messages);
                json.endMember();
            }
        }

        // GL_DEBUG_LOGGED_MESSAGES
        {
            flushErrors();
    GLint debug_logged_messages = 0;
    glGetIntegerv(GL_DEBUG_LOGGED_MESSAGES, &debug_logged_messages);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_LOGGED_MESSAGES");
    json.writeInt(debug_logged_messages);
                json.endMember();
            }
        }

        // GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT
        {
            flushErrors();
    GLint texture_buffer_offset_alignment = 0;
    glGetIntegerv(GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, &texture_buffer_offset_alignment);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT");
    json.writeInt(texture_buffer_offset_alignment);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_UNIFORM_BLOCKS
        {
            flushErrors();
    GLint max_compute_uniform_blocks = 0;
    glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_BLOCKS, &max_compute_uniform_blocks);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_UNIFORM_BLOCKS");
    json.writeInt(max_compute_uniform_blocks);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS
        {
            flushErrors();
    GLint max_compute_texture_image_units = 0;
    glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &max_compute_texture_image_units);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS");
    json.writeInt(max_compute_texture_image_units);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_IMAGE_UNIFORMS
        {
            flushErrors();
    GLint max_compute_image_uniforms = 0;
    glGetIntegerv(GL_MAX_COMPUTE_IMAGE_UNIFORMS, &max_compute_image_uniforms);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_IMAGE_UNIFORMS");
    json.writeInt(max_compute_image_uniforms);
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_WORK_GROUP_COUNT
        {
            flushErrors();
    GLint max_compute_work_group_count[3 + 1];
    memset(max_compute_work_group_count, 0, 3 * sizeof *max_compute_work_group_count);
    max_compute_work_group_count[3] = (GLint)0xdeadc0de;
    if (3) {
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_COUNT, max_compute_work_group_count);
    }
    assert(max_compute_work_group_count[3] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_WORK_GROUP_COUNT");
    json.beginArray();
    for (unsigned _i60 = 0; _i60 < 3; ++_i60) {
    json.writeInt(max_compute_work_group_count[_i60]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_MAX_COMPUTE_WORK_GROUP_SIZE
        {
            flushErrors();
    GLint max_compute_work_group_size[3 + 1];
    memset(max_compute_work_group_size, 0, 3 * sizeof *max_compute_work_group_size);
    max_compute_work_group_size[3] = (GLint)0xdeadc0de;
    if (3) {
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_SIZE, max_compute_work_group_size);
    }
    assert(max_compute_work_group_size[3] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_COMPUTE_WORK_GROUP_SIZE");
    json.beginArray();
    for (unsigned _i61 = 0; _i61 < 3; ++_i61) {
    json.writeInt(max_compute_work_group_size[_i61]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DEBUG_OUTPUT
        {
            flushErrors();
    GLboolean debug_output = 0;
    glGetBooleanv(GL_DEBUG_OUTPUT, &debug_output);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DEBUG_OUTPUT");
    dumpBoolean(json, debug_output);
                json.endMember();
            }
        }

        // GL_MAX_FRAMEBUFFER_WIDTH
        {
            flushErrors();
    GLint max_framebuffer_width = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &max_framebuffer_width);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAMEBUFFER_WIDTH");
    json.writeInt(max_framebuffer_width);
                json.endMember();
            }
        }

        // GL_MAX_FRAMEBUFFER_HEIGHT
        {
            flushErrors();
    GLint max_framebuffer_height = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &max_framebuffer_height);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAMEBUFFER_HEIGHT");
    json.writeInt(max_framebuffer_height);
                json.endMember();
            }
        }

        // GL_MAX_FRAMEBUFFER_LAYERS
        {
            flushErrors();
    GLint max_framebuffer_layers = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS, &max_framebuffer_layers);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAMEBUFFER_LAYERS");
    json.writeInt(max_framebuffer_layers);
                json.endMember();
            }
        }

        // GL_MAX_FRAMEBUFFER_SAMPLES
        {
            flushErrors();
    GLint max_framebuffer_samples = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES, &max_framebuffer_samples);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_FRAMEBUFFER_SAMPLES");
    json.writeInt(max_framebuffer_samples);
                json.endMember();
            }
        }

    if (!context.ES) {
    json.beginMember("GL_FRONT");
    json.beginObject();
        // GL_AMBIENT
        {
            flushErrors();
    GLfloat ambient[4 + 1];
    memset(ambient, 0, 4 * sizeof *ambient);
    ambient[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    }
    assert(ambient[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_AMBIENT");
    json.beginArray();
    for (unsigned _i62 = 0; _i62 < 4; ++_i62) {
    json.writeFloat(ambient[_i62]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DIFFUSE
        {
            flushErrors();
    GLfloat diffuse[4 + 1];
    memset(diffuse, 0, 4 * sizeof *diffuse);
    diffuse[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    }
    assert(diffuse[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DIFFUSE");
    json.beginArray();
    for (unsigned _i63 = 0; _i63 < 4; ++_i63) {
    json.writeFloat(diffuse[_i63]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPECULAR
        {
            flushErrors();
    GLfloat specular[4 + 1];
    memset(specular, 0, 4 * sizeof *specular);
    specular[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    }
    assert(specular[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPECULAR");
    json.beginArray();
    for (unsigned _i64 = 0; _i64 < 4; ++_i64) {
    json.writeFloat(specular[_i64]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_EMISSION
        {
            flushErrors();
    GLfloat emission[4 + 1];
    memset(emission, 0, 4 * sizeof *emission);
    emission[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_FRONT, GL_EMISSION, emission);
    }
    assert(emission[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EMISSION");
    json.beginArray();
    for (unsigned _i65 = 0; _i65 < 4; ++_i65) {
    json.writeFloat(emission[_i65]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SHININESS
        {
            flushErrors();
    GLfloat shininess = 0;
    glGetMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHININESS");
    json.writeFloat(shininess);
                json.endMember();
            }
        }

        // GL_COLOR_INDEXES
        {
            flushErrors();
    GLfloat color_indexes[3 + 1];
    memset(color_indexes, 0, 3 * sizeof *color_indexes);
    color_indexes[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetMaterialfv(GL_FRONT, GL_COLOR_INDEXES, color_indexes);
    }
    assert(color_indexes[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_INDEXES");
    json.beginArray();
    for (unsigned _i66 = 0; _i66 < 3; ++_i66) {
    json.writeFloat(color_indexes[_i66]);
    }
    json.endArray();
                json.endMember();
            }
        }

    json.endObject();
    json.beginMember("GL_BACK");
    json.beginObject();
        // GL_AMBIENT
        {
            flushErrors();
    GLfloat ambient[4 + 1];
    memset(ambient, 0, 4 * sizeof *ambient);
    ambient[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_BACK, GL_AMBIENT, ambient);
    }
    assert(ambient[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_AMBIENT");
    json.beginArray();
    for (unsigned _i67 = 0; _i67 < 4; ++_i67) {
    json.writeFloat(ambient[_i67]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DIFFUSE
        {
            flushErrors();
    GLfloat diffuse[4 + 1];
    memset(diffuse, 0, 4 * sizeof *diffuse);
    diffuse[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_BACK, GL_DIFFUSE, diffuse);
    }
    assert(diffuse[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DIFFUSE");
    json.beginArray();
    for (unsigned _i68 = 0; _i68 < 4; ++_i68) {
    json.writeFloat(diffuse[_i68]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPECULAR
        {
            flushErrors();
    GLfloat specular[4 + 1];
    memset(specular, 0, 4 * sizeof *specular);
    specular[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_BACK, GL_SPECULAR, specular);
    }
    assert(specular[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPECULAR");
    json.beginArray();
    for (unsigned _i69 = 0; _i69 < 4; ++_i69) {
    json.writeFloat(specular[_i69]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_EMISSION
        {
            flushErrors();
    GLfloat emission[4 + 1];
    memset(emission, 0, 4 * sizeof *emission);
    emission[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetMaterialfv(GL_BACK, GL_EMISSION, emission);
    }
    assert(emission[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_EMISSION");
    json.beginArray();
    for (unsigned _i70 = 0; _i70 < 4; ++_i70) {
    json.writeFloat(emission[_i70]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SHININESS
        {
            flushErrors();
    GLfloat shininess = 0;
    glGetMaterialfv(GL_BACK, GL_SHININESS, &shininess);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHININESS");
    json.writeFloat(shininess);
                json.endMember();
            }
        }

        // GL_COLOR_INDEXES
        {
            flushErrors();
    GLfloat color_indexes[3 + 1];
    memset(color_indexes, 0, 3 * sizeof *color_indexes);
    color_indexes[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetMaterialfv(GL_BACK, GL_COLOR_INDEXES, color_indexes);
    }
    assert(color_indexes[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COLOR_INDEXES");
    json.beginArray();
    for (unsigned _i71 = 0; _i71 < 3; ++_i71) {
    json.writeFloat(color_indexes[_i71]);
    }
    json.endArray();
                json.endMember();
            }
        }

    json.endObject();
    }

    GLint max_lights = 0;
    _glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
    for (GLint index = 0; index < max_lights; ++index) {
        GLenum light = GL_LIGHT0 + index;
        if (glIsEnabled(light)) {
            char name[32];
            snprintf(name, sizeof name, "GL_LIGHT%i", index);
            json.beginMember(name);
            json.beginObject();
        // GL_AMBIENT
        {
            flushErrors();
    GLfloat ambient[4 + 1];
    memset(ambient, 0, 4 * sizeof *ambient);
    ambient[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetLightfv(    GL_LIGHT0 + index, GL_AMBIENT, ambient);
    }
    assert(ambient[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_AMBIENT");
    json.beginArray();
    for (unsigned _i72 = 0; _i72 < 4; ++_i72) {
    json.writeFloat(ambient[_i72]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_DIFFUSE
        {
            flushErrors();
    GLfloat diffuse[4 + 1];
    memset(diffuse, 0, 4 * sizeof *diffuse);
    diffuse[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetLightfv(    GL_LIGHT0 + index, GL_DIFFUSE, diffuse);
    }
    assert(diffuse[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_DIFFUSE");
    json.beginArray();
    for (unsigned _i73 = 0; _i73 < 4; ++_i73) {
    json.writeFloat(diffuse[_i73]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPECULAR
        {
            flushErrors();
    GLfloat specular[4 + 1];
    memset(specular, 0, 4 * sizeof *specular);
    specular[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetLightfv(    GL_LIGHT0 + index, GL_SPECULAR, specular);
    }
    assert(specular[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPECULAR");
    json.beginArray();
    for (unsigned _i74 = 0; _i74 < 4; ++_i74) {
    json.writeFloat(specular[_i74]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_POSITION
        {
            flushErrors();
    GLfloat position[4 + 1];
    memset(position, 0, 4 * sizeof *position);
    position[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetLightfv(    GL_LIGHT0 + index, GL_POSITION, position);
    }
    assert(position[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_POSITION");
    json.beginArray();
    for (unsigned _i75 = 0; _i75 < 4; ++_i75) {
    json.writeFloat(position[_i75]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPOT_DIRECTION
        {
            flushErrors();
    GLfloat spot_direction[3 + 1];
    memset(spot_direction, 0, 3 * sizeof *spot_direction);
    spot_direction[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetLightfv(    GL_LIGHT0 + index, GL_SPOT_DIRECTION, spot_direction);
    }
    assert(spot_direction[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPOT_DIRECTION");
    json.beginArray();
    for (unsigned _i76 = 0; _i76 < 3; ++_i76) {
    json.writeFloat(spot_direction[_i76]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_SPOT_EXPONENT
        {
            flushErrors();
    GLfloat spot_exponent = 0;
    glGetLightfv(    GL_LIGHT0 + index, GL_SPOT_EXPONENT, &spot_exponent);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPOT_EXPONENT");
    json.writeFloat(spot_exponent);
                json.endMember();
            }
        }

        // GL_SPOT_CUTOFF
        {
            flushErrors();
    GLfloat spot_cutoff = 0;
    glGetLightfv(    GL_LIGHT0 + index, GL_SPOT_CUTOFF, &spot_cutoff);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SPOT_CUTOFF");
    json.writeFloat(spot_cutoff);
                json.endMember();
            }
        }

        // GL_CONSTANT_ATTENUATION
        {
            flushErrors();
    GLfloat constant_attenuation = 0;
    glGetLightfv(    GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION, &constant_attenuation);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONSTANT_ATTENUATION");
    json.writeFloat(constant_attenuation);
                json.endMember();
            }
        }

        // GL_LINEAR_ATTENUATION
        {
            flushErrors();
    GLfloat linear_attenuation = 0;
    glGetLightfv(    GL_LIGHT0 + index, GL_LINEAR_ATTENUATION, &linear_attenuation);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_LINEAR_ATTENUATION");
    json.writeFloat(linear_attenuation);
                json.endMember();
            }
        }

        // GL_QUADRATIC_ATTENUATION
        {
            flushErrors();
    GLfloat quadratic_attenuation = 0;
    glGetLightfv(    GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_QUADRATIC_ATTENUATION");
    json.writeFloat(quadratic_attenuation);
                json.endMember();
            }
        }

            json.endObject();
            json.endMember(); // GL_LIGHTi
        }
    }

    GLint max_vertex_attribs = 0;
    _glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attribs);
    for (GLint index = 0; index < max_vertex_attribs; ++index) {
        char name[32];
        snprintf(name, sizeof name, "GL_VERTEX_ATTRIB_ARRAY%i", index);
        json.beginMember(name);
        json.beginObject();
        // GL_VERTEX_ATTRIB_BINDING
        {
            flushErrors();
    GLint vertex_attrib_binding = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_BINDING, &vertex_attrib_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_BINDING");
    json.writeInt(vertex_attrib_binding);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_RELATIVE_OFFSET
        {
            flushErrors();
    GLint vertex_attrib_relative_offset = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_RELATIVE_OFFSET, &vertex_attrib_relative_offset);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_RELATIVE_OFFSET");
    json.writeInt(vertex_attrib_relative_offset);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_ENABLED
        {
            flushErrors();
    GLint vertex_attrib_array_enabled = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &vertex_attrib_array_enabled);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_ENABLED");
    dumpBoolean(json, vertex_attrib_array_enabled);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_SIZE
        {
            flushErrors();
    GLint vertex_attrib_array_size = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &vertex_attrib_array_size);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_SIZE");
    json.writeInt(vertex_attrib_array_size);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_STRIDE
        {
            flushErrors();
    GLint vertex_attrib_array_stride = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &vertex_attrib_array_stride);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_STRIDE");
    json.writeInt(vertex_attrib_array_stride);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_TYPE
        {
            flushErrors();
    GLint vertex_attrib_array_type = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &vertex_attrib_array_type);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_TYPE");
    dumpEnum(json, vertex_attrib_array_type);
                json.endMember();
            }
        }

        // GL_CURRENT_VERTEX_ATTRIB
        {
            flushErrors();
    GLdouble current_vertex_attrib[4 + 1];
    memset(current_vertex_attrib, 0, 4 * sizeof *current_vertex_attrib);
    current_vertex_attrib[4] = (GLdouble)0xdeadc0de;
    if (4) {
        glGetVertexAttribdv(index, GL_CURRENT_VERTEX_ATTRIB, current_vertex_attrib);
    }
    assert(current_vertex_attrib[4] == (GLdouble)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CURRENT_VERTEX_ATTRIB");
    json.beginArray();
    for (unsigned _i77 = 0; _i77 < 4; ++_i77) {
    json.writeFloat(current_vertex_attrib[_i77]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_POINTER
        {
            flushErrors();
    GLvoid *vertex_attrib_array_pointer;
    glGetVertexAttribPointerv(index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &vertex_attrib_array_pointer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_POINTER");
    json.writeInt((size_t)vertex_attrib_array_pointer);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_NORMALIZED
        {
            flushErrors();
    GLint vertex_attrib_array_normalized = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &vertex_attrib_array_normalized);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED");
    dumpBoolean(json, vertex_attrib_array_normalized);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING
        {
            flushErrors();
    GLint vertex_attrib_array_buffer_binding = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vertex_attrib_array_buffer_binding);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING");
    json.writeInt(vertex_attrib_array_buffer_binding);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_INTEGER
        {
            flushErrors();
    GLint vertex_attrib_array_integer = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_INTEGER, &vertex_attrib_array_integer);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_INTEGER");
    dumpBoolean(json, vertex_attrib_array_integer);
                json.endMember();
            }
        }

        // GL_VERTEX_ATTRIB_ARRAY_DIVISOR
        {
            flushErrors();
    GLint vertex_attrib_array_divisor = 0;
    glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &vertex_attrib_array_divisor);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_VERTEX_ATTRIB_ARRAY_DIVISOR");
    json.writeInt(vertex_attrib_array_divisor);
                json.endMember();
            }
        }

        GLint buffer_binding = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &buffer_binding);
        dumpObjectLabel(json, context, GL_BUFFER, buffer_binding, "GL_VERTEX_ATTRIB_ARRAY_BUFFER_LABEL");
        json.endObject();
        json.endMember(); // GL_VERTEX_ATTRIB_ARRAYi
    }

    if (glIsEnabled(GL_FRAGMENT_PROGRAM_ARB)) {
        json.beginMember("GL_FRAGMENT_PROGRAM_ARB");
        json.beginObject();
        // GL_PROGRAM_LENGTH_ARB
        {
            flushErrors();
    GLint program_length_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_LENGTH_ARB, &program_length_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_LENGTH_ARB");
    json.writeInt(program_length_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_BINDING_ARB
        {
            flushErrors();
    GLint program_binding_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB, &program_binding_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_BINDING_ARB");
    json.writeInt(program_binding_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_alu_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_ALU_INSTRUCTIONS_ARB, &program_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ALU_INSTRUCTIONS_ARB");
    json.writeInt(program_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_tex_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_TEX_INSTRUCTIONS_ARB, &program_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEX_INSTRUCTIONS_ARB");
    json.writeInt(program_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint program_tex_indirections_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_TEX_INDIRECTIONS_ARB, &program_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEX_INDIRECTIONS_ARB");
    json.writeInt(program_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_alu_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, &program_native_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB");
    json.writeInt(program_native_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_tex_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, &program_native_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB");
    json.writeInt(program_native_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint program_native_tex_indirections_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, &program_native_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB");
    json.writeInt(program_native_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_alu_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB, &max_program_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB");
    json.writeInt(max_program_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_tex_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB, &max_program_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB");
    json.writeInt(max_program_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint max_program_tex_indirections_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB, &max_program_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB");
    json.writeInt(max_program_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_alu_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, &max_program_native_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_tex_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, &max_program_native_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_tex_indirections_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, &max_program_native_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB");
    json.writeInt(max_program_native_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_FORMAT_ARB
        {
            flushErrors();
    GLint program_format_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ARB, &program_format_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_FORMAT_ARB");
    dumpEnum(json, program_format_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_INSTRUCTIONS_ARB, &program_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_INSTRUCTIONS_ARB");
    json.writeInt(program_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_INSTRUCTIONS_ARB, &max_program_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_INSTRUCTIONS_ARB");
    json.writeInt(max_program_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &program_native_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB");
    json.writeInt(program_native_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_instructions_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &max_program_native_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEMPORARIES_ARB
        {
            flushErrors();
    GLint program_temporaries_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_TEMPORARIES_ARB, &program_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEMPORARIES_ARB");
    json.writeInt(program_temporaries_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEMPORARIES_ARB
        {
            flushErrors();
    GLint max_program_temporaries_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_TEMPORARIES_ARB, &max_program_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEMPORARIES_ARB");
    json.writeInt(max_program_temporaries_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEMPORARIES_ARB
        {
            flushErrors();
    GLint program_native_temporaries_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEMPORARIES_ARB, &program_native_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEMPORARIES_ARB");
    json.writeInt(program_native_temporaries_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB
        {
            flushErrors();
    GLint max_program_native_temporaries_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB, &max_program_native_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB");
    json.writeInt(max_program_native_temporaries_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_PARAMETERS_ARB
        {
            flushErrors();
    GLint program_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_PARAMETERS_ARB, &program_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_PARAMETERS_ARB");
    json.writeInt(program_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_PARAMETERS_ARB, &max_program_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_PARAMETERS_ARB");
    json.writeInt(max_program_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_PARAMETERS_ARB
        {
            flushErrors();
    GLint program_native_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_PARAMETERS_ARB, &program_native_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_PARAMETERS_ARB");
    json.writeInt(program_native_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_native_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB, &max_program_native_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB");
    json.writeInt(max_program_native_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ATTRIBS_ARB
        {
            flushErrors();
    GLint program_attribs_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_ATTRIBS_ARB, &program_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ATTRIBS_ARB");
    json.writeInt(program_attribs_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ATTRIBS_ARB
        {
            flushErrors();
    GLint max_program_attribs_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_ATTRIBS_ARB, &max_program_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ATTRIBS_ARB");
    json.writeInt(max_program_attribs_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ATTRIBS_ARB
        {
            flushErrors();
    GLint program_native_attribs_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_ATTRIBS_ARB, &program_native_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ATTRIBS_ARB");
    json.writeInt(program_native_attribs_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB
        {
            flushErrors();
    GLint max_program_native_attribs_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB, &max_program_native_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB");
    json.writeInt(max_program_native_attribs_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint program_address_registers_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_ADDRESS_REGISTERS_ARB, &program_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ADDRESS_REGISTERS_ARB");
    json.writeInt(program_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint max_program_address_registers_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB, &max_program_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB");
    json.writeInt(max_program_address_registers_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint program_native_address_registers_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, &program_native_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB");
    json.writeInt(program_native_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint max_program_native_address_registers_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, &max_program_native_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB");
    json.writeInt(max_program_native_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_local_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB, &max_program_local_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB");
    json.writeInt(max_program_local_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ENV_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_env_parameters_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_ENV_PARAMETERS_ARB, &max_program_env_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ENV_PARAMETERS_ARB");
    json.writeInt(max_program_env_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB
        {
            flushErrors();
    GLint program_under_native_limits_arb = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB, &program_under_native_limits_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB");
    dumpBoolean(json, program_under_native_limits_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV
        {
            flushErrors();
    GLint max_program_exec_instructions_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV, &max_program_exec_instructions_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV");
    json.writeInt(max_program_exec_instructions_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_CALL_DEPTH_NV
        {
            flushErrors();
    GLint max_program_call_depth_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_CALL_DEPTH_NV, &max_program_call_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_CALL_DEPTH_NV");
    json.writeInt(max_program_call_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_IF_DEPTH_NV
        {
            flushErrors();
    GLint max_program_if_depth_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_IF_DEPTH_NV, &max_program_if_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_IF_DEPTH_NV");
    json.writeInt(max_program_if_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOOP_DEPTH_NV
        {
            flushErrors();
    GLint max_program_loop_depth_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_LOOP_DEPTH_NV, &max_program_loop_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOOP_DEPTH_NV");
    json.writeInt(max_program_loop_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOOP_COUNT_NV
        {
            flushErrors();
    GLint max_program_loop_count_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_LOOP_COUNT_NV, &max_program_loop_count_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOOP_COUNT_NV");
    json.writeInt(max_program_loop_count_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_OUTPUT_VERTICES_NV
        {
            flushErrors();
    GLint max_program_output_vertices_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_OUTPUT_VERTICES_NV, &max_program_output_vertices_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_OUTPUT_VERTICES_NV");
    json.writeInt(max_program_output_vertices_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV
        {
            flushErrors();
    GLint max_program_total_output_components_nv = 0;
    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV, &max_program_total_output_components_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV");
    json.writeInt(max_program_total_output_components_nv);
                json.endMember();
            }
        }

        json.endObject();
    }
    if (glIsEnabled(GL_VERTEX_PROGRAM_ARB)) {
        json.beginMember("GL_VERTEX_PROGRAM_ARB");
        json.beginObject();
        // GL_PROGRAM_LENGTH_ARB
        {
            flushErrors();
    GLint program_length_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_LENGTH_ARB, &program_length_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_LENGTH_ARB");
    json.writeInt(program_length_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_BINDING_ARB
        {
            flushErrors();
    GLint program_binding_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB, &program_binding_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_BINDING_ARB");
    json.writeInt(program_binding_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_alu_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_ALU_INSTRUCTIONS_ARB, &program_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ALU_INSTRUCTIONS_ARB");
    json.writeInt(program_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_tex_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_TEX_INSTRUCTIONS_ARB, &program_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEX_INSTRUCTIONS_ARB");
    json.writeInt(program_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint program_tex_indirections_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_TEX_INDIRECTIONS_ARB, &program_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEX_INDIRECTIONS_ARB");
    json.writeInt(program_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_alu_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, &program_native_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB");
    json.writeInt(program_native_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_tex_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, &program_native_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB");
    json.writeInt(program_native_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint program_native_tex_indirections_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, &program_native_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB");
    json.writeInt(program_native_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_alu_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB, &max_program_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB");
    json.writeInt(max_program_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_tex_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB, &max_program_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB");
    json.writeInt(max_program_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint max_program_tex_indirections_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB, &max_program_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB");
    json.writeInt(max_program_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_alu_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB, &max_program_native_alu_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_alu_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_tex_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB, &max_program_native_tex_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_tex_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_tex_indirections_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB, &max_program_native_tex_indirections_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB");
    json.writeInt(max_program_native_tex_indirections_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_FORMAT_ARB
        {
            flushErrors();
    GLint program_format_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ARB, &program_format_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_FORMAT_ARB");
    dumpEnum(json, program_format_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_INSTRUCTIONS_ARB, &program_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_INSTRUCTIONS_ARB");
    json.writeInt(program_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_INSTRUCTIONS_ARB, &max_program_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_INSTRUCTIONS_ARB");
    json.writeInt(max_program_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint program_native_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &program_native_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_INSTRUCTIONS_ARB");
    json.writeInt(program_native_instructions_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB
        {
            flushErrors();
    GLint max_program_native_instructions_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB, &max_program_native_instructions_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_INSTRUCTIONS_ARB");
    json.writeInt(max_program_native_instructions_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_TEMPORARIES_ARB
        {
            flushErrors();
    GLint program_temporaries_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_TEMPORARIES_ARB, &program_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_TEMPORARIES_ARB");
    json.writeInt(program_temporaries_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TEMPORARIES_ARB
        {
            flushErrors();
    GLint max_program_temporaries_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_TEMPORARIES_ARB, &max_program_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TEMPORARIES_ARB");
    json.writeInt(max_program_temporaries_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_TEMPORARIES_ARB
        {
            flushErrors();
    GLint program_native_temporaries_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_TEMPORARIES_ARB, &program_native_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_TEMPORARIES_ARB");
    json.writeInt(program_native_temporaries_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB
        {
            flushErrors();
    GLint max_program_native_temporaries_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB, &max_program_native_temporaries_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_TEMPORARIES_ARB");
    json.writeInt(max_program_native_temporaries_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_PARAMETERS_ARB
        {
            flushErrors();
    GLint program_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_PARAMETERS_ARB, &program_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_PARAMETERS_ARB");
    json.writeInt(program_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_PARAMETERS_ARB, &max_program_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_PARAMETERS_ARB");
    json.writeInt(max_program_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_PARAMETERS_ARB
        {
            flushErrors();
    GLint program_native_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_PARAMETERS_ARB, &program_native_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_PARAMETERS_ARB");
    json.writeInt(program_native_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_native_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB, &max_program_native_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_PARAMETERS_ARB");
    json.writeInt(max_program_native_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ATTRIBS_ARB
        {
            flushErrors();
    GLint program_attribs_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_ATTRIBS_ARB, &program_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ATTRIBS_ARB");
    json.writeInt(program_attribs_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ATTRIBS_ARB
        {
            flushErrors();
    GLint max_program_attribs_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_ATTRIBS_ARB, &max_program_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ATTRIBS_ARB");
    json.writeInt(max_program_attribs_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ATTRIBS_ARB
        {
            flushErrors();
    GLint program_native_attribs_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_ATTRIBS_ARB, &program_native_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ATTRIBS_ARB");
    json.writeInt(program_native_attribs_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB
        {
            flushErrors();
    GLint max_program_native_attribs_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB, &max_program_native_attribs_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ATTRIBS_ARB");
    json.writeInt(max_program_native_attribs_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint program_address_registers_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_ADDRESS_REGISTERS_ARB, &program_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_ADDRESS_REGISTERS_ARB");
    json.writeInt(program_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint max_program_address_registers_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB, &max_program_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ADDRESS_REGISTERS_ARB");
    json.writeInt(max_program_address_registers_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint program_native_address_registers_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, &program_native_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB");
    json.writeInt(program_native_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB
        {
            flushErrors();
    GLint max_program_native_address_registers_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB, &max_program_native_address_registers_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS_ARB");
    json.writeInt(max_program_native_address_registers_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_local_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB, &max_program_local_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOCAL_PARAMETERS_ARB");
    json.writeInt(max_program_local_parameters_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_ENV_PARAMETERS_ARB
        {
            flushErrors();
    GLint max_program_env_parameters_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_ENV_PARAMETERS_ARB, &max_program_env_parameters_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_ENV_PARAMETERS_ARB");
    json.writeInt(max_program_env_parameters_arb);
                json.endMember();
            }
        }

        // GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB
        {
            flushErrors();
    GLint program_under_native_limits_arb = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB, &program_under_native_limits_arb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PROGRAM_UNDER_NATIVE_LIMITS_ARB");
    dumpBoolean(json, program_under_native_limits_arb);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV
        {
            flushErrors();
    GLint max_program_exec_instructions_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV, &max_program_exec_instructions_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_EXEC_INSTRUCTIONS_NV");
    json.writeInt(max_program_exec_instructions_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_CALL_DEPTH_NV
        {
            flushErrors();
    GLint max_program_call_depth_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_CALL_DEPTH_NV, &max_program_call_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_CALL_DEPTH_NV");
    json.writeInt(max_program_call_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_IF_DEPTH_NV
        {
            flushErrors();
    GLint max_program_if_depth_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_IF_DEPTH_NV, &max_program_if_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_IF_DEPTH_NV");
    json.writeInt(max_program_if_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOOP_DEPTH_NV
        {
            flushErrors();
    GLint max_program_loop_depth_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_LOOP_DEPTH_NV, &max_program_loop_depth_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOOP_DEPTH_NV");
    json.writeInt(max_program_loop_depth_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_LOOP_COUNT_NV
        {
            flushErrors();
    GLint max_program_loop_count_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_LOOP_COUNT_NV, &max_program_loop_count_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_LOOP_COUNT_NV");
    json.writeInt(max_program_loop_count_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_OUTPUT_VERTICES_NV
        {
            flushErrors();
    GLint max_program_output_vertices_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_OUTPUT_VERTICES_NV, &max_program_output_vertices_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_OUTPUT_VERTICES_NV");
    json.writeInt(max_program_output_vertices_nv);
                json.endMember();
            }
        }

        // GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV
        {
            flushErrors();
    GLint max_program_total_output_components_nv = 0;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV, &max_program_total_output_components_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_MAX_PROGRAM_TOTAL_OUTPUT_COMPONENTS_NV");
    json.writeInt(max_program_total_output_components_nv);
                json.endMember();
            }
        }

        json.endObject();
    }
    {
        GLint active_texture = GL_TEXTURE0;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
        GLint max_texture_coords = 0;
        glGetIntegerv(GL_MAX_TEXTURE_COORDS, &max_texture_coords);
        GLint max_combined_texture_image_units = 0;
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_units);
        GLint max_units = std::max(std::max(max_combined_texture_image_units, max_texture_coords), 2);
        for (GLint unit = 0; unit < max_units; ++unit) {
            char name[32];
            snprintf(name, sizeof name, "GL_TEXTURE%i", unit);
            json.beginMember(name);
            glActiveTexture(GL_TEXTURE0 + unit);
            json.beginObject();

            dumpTextureTargetParameters(json, context, GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_BINDING_1D_ARRAY);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BINDING_2D_ARRAY);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_BINDING_2D_MULTISAMPLE);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BINDING_CUBE_MAP);
            dumpTextureTargetParameters(json, context, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BINDING_CUBE_MAP_ARRAY);
            if (unit < max_texture_coords) {
    // GL_SAMPLER_BINDING
    if (context.ARB_sampler_objects) {
        GLint sampler_binding = 0;
        glGetIntegerv(GL_SAMPLER_BINDING, &sampler_binding);
        json.beginMember("GL_SAMPLER_BINDING");
        json.writeInt(sampler_binding);
        json.endMember();
        if (sampler_binding) {
            json.beginMember("GL_SAMPLER");
            json.beginObject();
            dumpObjectLabel(json, context, GL_SAMPLER, sampler_binding, "GL_SAMPLER_LABEL");
        // GL_TEXTURE_BORDER_COLOR
        {
            flushErrors();
    GLfloat texture_border_color[4 + 1];
    memset(texture_border_color, 0, 4 * sizeof *texture_border_color);
    texture_border_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_BORDER_COLOR, texture_border_color);
    }
    assert(texture_border_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_BORDER_COLOR");
    json.beginArray();
    for (unsigned _i78 = 0; _i78 < 4; ++_i78) {
    json.writeFloat(texture_border_color[_i78]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_TEXTURE_MAG_FILTER
        {
            flushErrors();
    GLint texture_mag_filter = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_MAG_FILTER, &texture_mag_filter);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAG_FILTER");
    dumpEnum(json, texture_mag_filter);
                json.endMember();
            }
        }

        // GL_TEXTURE_MIN_FILTER
        {
            flushErrors();
    GLint texture_min_filter = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_MIN_FILTER, &texture_min_filter);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MIN_FILTER");
    dumpEnum(json, texture_min_filter);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_S
        {
            flushErrors();
    GLint texture_wrap_s = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_S, &texture_wrap_s);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_S");
    dumpEnum(json, texture_wrap_s);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_T
        {
            flushErrors();
    GLint texture_wrap_t = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_T, &texture_wrap_t);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_T");
    dumpEnum(json, texture_wrap_t);
                json.endMember();
            }
        }

        // GL_TEXTURE_WRAP_R
        {
            flushErrors();
    GLint texture_wrap_r = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_WRAP_R, &texture_wrap_r);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_WRAP_R");
    dumpEnum(json, texture_wrap_r);
                json.endMember();
            }
        }

        // GL_TEXTURE_MIN_LOD
        {
            flushErrors();
    GLfloat texture_min_lod = 0;
    glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_MIN_LOD, &texture_min_lod);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MIN_LOD");
    json.writeFloat(texture_min_lod);
                json.endMember();
            }
        }

        // GL_TEXTURE_MAX_LOD
        {
            flushErrors();
    GLfloat texture_max_lod = 0;
    glGetSamplerParameterfv(sampler_binding, GL_TEXTURE_MAX_LOD, &texture_max_lod);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_MAX_LOD");
    json.writeFloat(texture_max_lod);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_MODE
        {
            flushErrors();
    GLint texture_compare_mode = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_COMPARE_MODE, &texture_compare_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_MODE");
    dumpEnum(json, texture_compare_mode);
                json.endMember();
            }
        }

        // GL_TEXTURE_COMPARE_FUNC
        {
            flushErrors();
    GLint texture_compare_func = 0;
    glGetSamplerParameteriv(sampler_binding, GL_TEXTURE_COMPARE_FUNC, &texture_compare_func);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_COMPARE_FUNC");
    dumpEnum(json, texture_compare_func);
                json.endMember();
            }
        }

           json.endObject();
           json.endMember(); // GL_SAMPLER
       }
    }
    if (!context.ES) {
        json.beginMember("GL_TEXTURE_ENV");
        json.beginObject();
        // GL_ALPHA_SCALE
        {
            flushErrors();
    GLfloat alpha_scale = 0;
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_ALPHA_SCALE, &alpha_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_ALPHA_SCALE");
    json.writeFloat(alpha_scale);
                json.endMember();
            }
        }

        // GL_TEXTURE_ENV_MODE
        {
            flushErrors();
    GLint texture_env_mode = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &texture_env_mode);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_ENV_MODE");
    dumpEnum(json, texture_env_mode);
                json.endMember();
            }
        }

        // GL_TEXTURE_ENV_COLOR
        {
            flushErrors();
    GLfloat texture_env_color[4 + 1];
    memset(texture_env_color, 0, 4 * sizeof *texture_env_color);
    texture_env_color[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, texture_env_color);
    }
    assert(texture_env_color[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_ENV_COLOR");
    json.beginArray();
    for (unsigned _i79 = 0; _i79 < 4; ++_i79) {
    json.writeFloat(texture_env_color[_i79]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_COMBINE_RGB
        {
            flushErrors();
    GLint combine_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_COMBINE_RGB, &combine_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COMBINE_RGB");
    dumpEnum(json, combine_rgb);
                json.endMember();
            }
        }

        // GL_COMBINE_ALPHA
        {
            flushErrors();
    GLint combine_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, &combine_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COMBINE_ALPHA");
    dumpEnum(json, combine_alpha);
                json.endMember();
            }
        }

        // GL_RGB_SCALE
        {
            flushErrors();
    GLfloat rgb_scale = 0;
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_RGB_SCALE, &rgb_scale);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RGB_SCALE");
    json.writeFloat(rgb_scale);
                json.endMember();
            }
        }

        // GL_SRC0_RGB
        {
            flushErrors();
    GLint src0_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC0_RGB, &src0_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC0_RGB");
    dumpEnum(json, src0_rgb);
                json.endMember();
            }
        }

        // GL_SRC1_RGB
        {
            flushErrors();
    GLint src1_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC1_RGB, &src1_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC1_RGB");
    dumpEnum(json, src1_rgb);
                json.endMember();
            }
        }

        // GL_SRC2_RGB
        {
            flushErrors();
    GLint src2_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC2_RGB, &src2_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC2_RGB");
    dumpEnum(json, src2_rgb);
                json.endMember();
            }
        }

        // GL_SOURCE3_RGB_NV
        {
            flushErrors();
    GLint source3_rgb_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SOURCE3_RGB_NV, &source3_rgb_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SOURCE3_RGB_NV");
    dumpEnum(json, source3_rgb_nv);
                json.endMember();
            }
        }

        // GL_SRC0_ALPHA
        {
            flushErrors();
    GLint src0_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC0_ALPHA, &src0_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC0_ALPHA");
    dumpEnum(json, src0_alpha);
                json.endMember();
            }
        }

        // GL_SRC1_ALPHA
        {
            flushErrors();
    GLint src1_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC1_ALPHA, &src1_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC1_ALPHA");
    dumpEnum(json, src1_alpha);
                json.endMember();
            }
        }

        // GL_SRC2_ALPHA
        {
            flushErrors();
    GLint src2_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SRC2_ALPHA, &src2_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SRC2_ALPHA");
    dumpEnum(json, src2_alpha);
                json.endMember();
            }
        }

        // GL_SOURCE3_ALPHA_NV
        {
            flushErrors();
    GLint source3_alpha_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SOURCE3_ALPHA_NV, &source3_alpha_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SOURCE3_ALPHA_NV");
    dumpEnum(json, source3_alpha_nv);
                json.endMember();
            }
        }

        // GL_OPERAND0_RGB
        {
            flushErrors();
    GLint operand0_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND0_RGB, &operand0_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND0_RGB");
    dumpEnum(json, operand0_rgb);
                json.endMember();
            }
        }

        // GL_OPERAND1_RGB
        {
            flushErrors();
    GLint operand1_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND1_RGB, &operand1_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND1_RGB");
    dumpEnum(json, operand1_rgb);
                json.endMember();
            }
        }

        // GL_OPERAND2_RGB
        {
            flushErrors();
    GLint operand2_rgb = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND2_RGB, &operand2_rgb);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND2_RGB");
    dumpEnum(json, operand2_rgb);
                json.endMember();
            }
        }

        // GL_OPERAND3_RGB_NV
        {
            flushErrors();
    GLint operand3_rgb_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND3_RGB_NV, &operand3_rgb_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND3_RGB_NV");
    dumpEnum(json, operand3_rgb_nv);
                json.endMember();
            }
        }

        // GL_OPERAND0_ALPHA
        {
            flushErrors();
    GLint operand0_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, &operand0_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND0_ALPHA");
    dumpEnum(json, operand0_alpha);
                json.endMember();
            }
        }

        // GL_OPERAND1_ALPHA
        {
            flushErrors();
    GLint operand1_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, &operand1_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND1_ALPHA");
    dumpEnum(json, operand1_alpha);
                json.endMember();
            }
        }

        // GL_OPERAND2_ALPHA
        {
            flushErrors();
    GLint operand2_alpha = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, &operand2_alpha);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND2_ALPHA");
    dumpEnum(json, operand2_alpha);
                json.endMember();
            }
        }

        // GL_OPERAND3_ALPHA_NV
        {
            flushErrors();
    GLint operand3_alpha_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_OPERAND3_ALPHA_NV, &operand3_alpha_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OPERAND3_ALPHA_NV");
    dumpEnum(json, operand3_alpha_nv);
                json.endMember();
            }
        }

        // GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV
        {
            flushErrors();
    GLint rgba_unsigned_dot_product_mapping_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV, &rgba_unsigned_dot_product_mapping_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV");
    dumpEnum(json, rgba_unsigned_dot_product_mapping_nv);
                json.endMember();
            }
        }

        // GL_SHADER_OPERATION_NV
        {
            flushErrors();
    GLint shader_operation_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_SHADER_OPERATION_NV, &shader_operation_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_SHADER_OPERATION_NV");
    dumpEnum(json, shader_operation_nv);
                json.endMember();
            }
        }

        // GL_CULL_MODES_NV
        {
            flushErrors();
    GLint cull_modes_nv[4 + 1];
    memset(cull_modes_nv, 0, 4 * sizeof *cull_modes_nv);
    cull_modes_nv[4] = (GLint)0xdeadc0de;
    if (4) {
        glGetTexEnviv(GL_TEXTURE_ENV, GL_CULL_MODES_NV, cull_modes_nv);
    }
    assert(cull_modes_nv[4] == (GLint)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CULL_MODES_NV");
    json.beginArray();
    for (unsigned _i80 = 0; _i80 < 4; ++_i80) {
    dumpEnum(json, cull_modes_nv[_i80]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_OFFSET_TEXTURE_MATRIX_NV
        {
            flushErrors();
    GLfloat offset_texture_matrix_nv[4 + 1];
    memset(offset_texture_matrix_nv, 0, 4 * sizeof *offset_texture_matrix_nv);
    offset_texture_matrix_nv[4] = (GLfloat)0xdeadc0de;
    if (4) {
        glGetTexEnvfv(GL_TEXTURE_ENV, GL_OFFSET_TEXTURE_MATRIX_NV, offset_texture_matrix_nv);
    }
    assert(offset_texture_matrix_nv[4] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OFFSET_TEXTURE_MATRIX_NV");
    json.beginArray();
    for (unsigned _i81 = 0; _i81 < 4; ++_i81) {
    json.writeFloat(offset_texture_matrix_nv[_i81]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_OFFSET_TEXTURE_SCALE_NV
        {
            flushErrors();
    GLfloat offset_texture_scale_nv = 0;
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_OFFSET_TEXTURE_SCALE_NV, &offset_texture_scale_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OFFSET_TEXTURE_SCALE_NV");
    json.writeFloat(offset_texture_scale_nv);
                json.endMember();
            }
        }

        // GL_OFFSET_TEXTURE_BIAS_NV
        {
            flushErrors();
    GLfloat offset_texture_bias_nv = 0;
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_OFFSET_TEXTURE_BIAS_NV, &offset_texture_bias_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_OFFSET_TEXTURE_BIAS_NV");
    json.writeFloat(offset_texture_bias_nv);
                json.endMember();
            }
        }

        // GL_PREVIOUS_TEXTURE_INPUT_NV
        {
            flushErrors();
    GLint previous_texture_input_nv = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_PREVIOUS_TEXTURE_INPUT_NV, &previous_texture_input_nv);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_PREVIOUS_TEXTURE_INPUT_NV");
    dumpEnum(json, previous_texture_input_nv);
                json.endMember();
            }
        }

        // GL_CONST_EYE_NV
        {
            flushErrors();
    GLfloat const_eye_nv[3 + 1];
    memset(const_eye_nv, 0, 3 * sizeof *const_eye_nv);
    const_eye_nv[3] = (GLfloat)0xdeadc0de;
    if (3) {
        glGetTexEnvfv(GL_TEXTURE_ENV, GL_CONST_EYE_NV, const_eye_nv);
    }
    assert(const_eye_nv[3] == (GLfloat)0xdeadc0de);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_CONST_EYE_NV");
    json.beginArray();
    for (unsigned _i82 = 0; _i82 < 3; ++_i82) {
    json.writeFloat(const_eye_nv[_i82]);
    }
    json.endArray();
                json.endMember();
            }
        }

        // GL_BUMP_TARGET_ATI
        {
            flushErrors();
    GLint bump_target_ati = 0;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_BUMP_TARGET_ATI, &bump_target_ati);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_BUMP_TARGET_ATI");
    dumpEnum(json, bump_target_ati);
                json.endMember();
            }
        }

        json.endObject();
    }
    if (!context.ES) {
        json.beginMember("GL_TEXTURE_FILTER_CONTROL");
        json.beginObject();
        // GL_TEXTURE_LOD_BIAS
        {
            flushErrors();
    GLfloat texture_lod_bias = 0;
    glGetTexEnvfv(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, &texture_lod_bias);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_TEXTURE_LOD_BIAS");
    json.writeFloat(texture_lod_bias);
                json.endMember();
            }
        }

        json.endObject();
    }
    if (!context.ES) {
        json.beginMember("GL_POINT_SPRITE");
        json.beginObject();
        // GL_COORD_REPLACE
        {
            flushErrors();
    GLint coord_replace = 0;
    glGetTexEnviv(GL_POINT_SPRITE, GL_COORD_REPLACE, &coord_replace);
            if (glGetError() != GL_NO_ERROR) {
                flushErrors();
            } else {
                json.beginMember("GL_COORD_REPLACE");
    dumpBoolean(json, coord_replace);
                json.endMember();
            }
        }

        json.endObject();
    }
            }
            json.endObject();
            json.endMember(); // GL_TEXTUREi
        }
        glActiveTexture(active_texture);
    }

    {
        GLint max_color_attachments = 0;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);
        GLint framebuffer;
            // GL_DRAW_FRAMEBUFFER
            framebuffer = 0;
            glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &framebuffer);
            if (framebuffer) {
                json.beginMember("GL_DRAW_FRAMEBUFFER");
                json.beginObject();
                dumpObjectLabel(json, context, GL_FRAMEBUFFER, framebuffer, "GL_FRAMEBUFFER_LABEL");
                for (GLint i = 0; i < max_color_attachments; ++i) {
                    GLint color_attachment = GL_COLOR_ATTACHMENT0 + i;
                    dumpFramebufferAttachementParameters(json, context, GL_DRAW_FRAMEBUFFER, color_attachment);
                }
                dumpFramebufferAttachementParameters(json, context, GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);
                dumpFramebufferAttachementParameters(json, context, GL_DRAW_FRAMEBUFFER, GL_STENCIL_ATTACHMENT);
                json.endObject();
                json.endMember(); // GL_DRAW_FRAMEBUFFER
            }

            // GL_READ_FRAMEBUFFER
            framebuffer = 0;
            glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &framebuffer);
            if (framebuffer) {
                json.beginMember("GL_READ_FRAMEBUFFER");
                json.beginObject();
                dumpObjectLabel(json, context, GL_FRAMEBUFFER, framebuffer, "GL_FRAMEBUFFER_LABEL");
                for (GLint i = 0; i < max_color_attachments; ++i) {
                    GLint color_attachment = GL_COLOR_ATTACHMENT0 + i;
                    dumpFramebufferAttachementParameters(json, context, GL_READ_FRAMEBUFFER, color_attachment);
                }
                dumpFramebufferAttachementParameters(json, context, GL_READ_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);
                dumpFramebufferAttachementParameters(json, context, GL_READ_FRAMEBUFFER, GL_STENCIL_ATTACHMENT);
                json.endObject();
                json.endMember(); // GL_READ_FRAMEBUFFER
            }

    }

    {
        GLint binding = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_COLOR_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_COLOR_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_EDGE_FLAG_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_EDGE_FLAG_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_ELEMENT_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_FOG_COORDINATE_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_INDEX_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_INDEX_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_NORMAL_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_NORMAL_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_SECONDARY_COLOR_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_TEXTURE_COORD_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_TRANSFORM_FEEDBACK_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_VERTEX_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_WEIGHT_ARRAY_BUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_BUFFER, binding, "GL_WEIGHT_ARRAY_BUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_FRAMEBUFFER, binding, "GL_DRAW_FRAMEBUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_FRAMEBUFFER, binding, "GL_READ_FRAMEBUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &binding);
        dumpObjectLabel(json, context, GL_PROGRAM, binding, "GL_CURRENT_PROGRAM_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_PROGRAM_PIPELINE_BINDING, &binding);
        dumpObjectLabel(json, context, GL_PROGRAM_PIPELINE, binding, "GL_PROGRAM_PIPELINE_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &binding);
        dumpObjectLabel(json, context, GL_RENDERBUFFER, binding, "GL_RENDERBUFFER_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_TRANSFORM_FEEDBACK_BINDING, &binding);
        dumpObjectLabel(json, context, GL_TRANSFORM_FEEDBACK, binding, "GL_TRANSFORM_FEEDBACK_LABEL");
    }
    {
        GLint binding = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding);
        dumpObjectLabel(json, context, GL_VERTEX_ARRAY, binding, "GL_VERTEX_ARRAY_LABEL");
    }
    json.endObject();
    json.endMember(); // parameters
}

} /*namespace glstate */
