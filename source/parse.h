/****************************************************************************
 *                  parse.h
 *
 * This header file is included by all all language parsing C modules in
 * POV-Ray.
 *
 * from Persistence of Vision(tm) Ray Tracer version 3.6.
 * Copyright 1991-2003 Persistence of Vision Team
 * Copyright 2003-2004 Persistence of Vision Raytracer Pty. Ltd.
 *---------------------------------------------------------------------------
 * NOTICE: This source code file is provided so that users may experiment
 * with enhancements to POV-Ray and to port the software to platforms other
 * than those supported by the POV-Ray developers. There are strict rules
 * regarding how you are permitted to use this file. These rules are contained
 * in the distribution and derivative versions licenses which should have been
 * provided with this file.
 *
 * These licences may be found online, linked from the end-user license
 * agreement that is located at http://www.povray.org/povlegal.html
 *---------------------------------------------------------------------------
 * This program is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 *---------------------------------------------------------------------------
 * $File: //depot/povray/3.6-release/source/parse.h $
 * $Revision: #2 $
 * $Change: 2939 $
 * $DateTime: 2004/07/05 03:43:26 $
 * $Author: root $
 * $Log$
 *****************************************************************************/

#ifndef PARSE_H
#define PARSE_H

#include "frame.h"
#include "camera.h"

BEGIN_POV_NAMESPACE

/*****************************************************************************
* Global preprocessor defines
******************************************************************************/

/* Here we create our own little language for doing the parsing.  It
  makes the code easier to read. */

#define EXPECT { int Exit_Flag; Exit_Flag = false; \
 while (!Exit_Flag) {Get_Token();  switch (Token.Token_Id) {
#define EXPECT_ONE { int Exit_Flag; Exit_Flag = false; \
 {Get_Token();  switch (Token.Token_Id) {
#define CASE(x) case x:
#define CASE2(x, y) case x: case y:
#define CASE3(x, y, z) case x: case y: case z:
#define CASE4(w, x, y, z) case w: case x: case y: case z:
#define CASE5(v, w, x, y, z) case v: case w: case x: case y: case z:
#define CASE6(u, v, w, x, y, z) case u: case v: case w: case x: case y: case z:
#define END_CASE break;
#define EXIT Exit_Flag = true;
#define OTHERWISE default:
#define END_EXPECT } } }
#define GET(x) Get_Token(); if (Token.Token_Id != x) Parse_Error (x);
#define ALLOW(x) Get_Token(); if (Token.Token_Id != x) Unget_Token();
#define UNGET Unget_Token();

#define CASE_FLOAT CASE2 (LEFT_PAREN_TOKEN,FLOAT_FUNCT_TOKEN)\
 CASE4 (PLUS_TOKEN,DASH_TOKEN,FUNCT_ID_TOKEN,EXCLAMATION_TOKEN) \
 UNGET

#define CASE_VECTOR CASE3 (VECTFUNCT_ID_TOKEN,VECTOR_FUNCT_TOKEN,LEFT_ANGLE_TOKEN) \
 CASE5 (U_TOKEN,V_TOKEN,UV_ID_TOKEN,VECTOR_4D_ID_TOKEN,SPLINE_ID_TOKEN) \
 CASE_FLOAT /* NOTE this has an UNGET in it! */

#define CASE_COLOUR CASE3 (COLOUR_TOKEN,COLOUR_KEY_TOKEN,COLOUR_ID_TOKEN) \
 UNGET

/*
CASE_EXPRESS is a CASE_COLOUR w/o an UNGET and a CASE_VECTOR (w/unget)

   NOTE: you cannot use CASE_VECTOR followed by CASE_COLOUR or vice-versa, because
         they both contain an UNGET which will cause problems!
*/
#define CASE_EXPRESS CASE3 (COLOUR_TOKEN,COLOUR_KEY_TOKEN,COLOUR_ID_TOKEN) \
  CASE_VECTOR /* NOTE this has an UNGET in it! */

#define MAX_BRACES 200

/* Token Definitions for Parser */

enum TOKEN_IDS
{
  ABS_TOKEN = 0,
  ATAN_TOKEN,
  ATAN2_TOKEN,
  CEIL_TOKEN,
  CLOCK_ON_TOKEN,
  CLOCK_TOKEN,
  COS_TOKEN,
  DEGREES_TOKEN,
  DIV_TOKEN,
  EXP_TOKEN,
  FLOAT_ID_TOKEN,
  FLOAT_TOKEN,
  FLOOR_TOKEN,
  FINALCLOCK_TOKEN,
  FINALFRAME_TOKEN,
  FRAMENUMBER_TOKEN,
  IMAGE_WIDTH_TOKEN,
  IMAGE_HEIGHT_TOKEN,
  INITIALFRAME_TOKEN,
  INITIALCLOCK_TOKEN,
  INSIDE_TOKEN,
  INT_TOKEN,
  LN_TOKEN,
  LOG_TOKEN,
  MAX_TOKEN,
  MIN_TOKEN,
  MOD_TOKEN,
  PI_TOKEN,
  POW_TOKEN,
  RADIANS_TOKEN,
  SELECT_TOKEN,
  SIN_TOKEN,
  SQRT_TOKEN,
  VDOT_TOKEN,
  VLENGTH_TOKEN,
  VERSION_TOKEN,
  ON_TOKEN,
  OFF_TOKEN,
  TRUE_TOKEN,
  FALSE_TOKEN,
  YES_TOKEN,
  NO_TOKEN,
  ACOS_TOKEN,
  ASIN_TOKEN,
  TAN_TOKEN,
  ASC_TOKEN,
  STRLEN_TOKEN,
  VAL_TOKEN,
  FILE_EXISTS_TOKEN,
  STRCMP_TOKEN,
  SEED_TOKEN,
  RAND_TOKEN,
  CLOCK_DELTA_TOKEN,
  DIMENSIONS_TOKEN,
  DIMENSION_SIZE_TOKEN,
  DEFINED_TOKEN,
  COSH_TOKEN,
  SINH_TOKEN,
  TANH_TOKEN,
  ATANH_TOKEN,
  ACOSH_TOKEN,
  ASINH_TOKEN,
  SUM_TOKEN,
  PROD_TOKEN,
  FLOAT_FUNCT_TOKEN,/*WARNING: All new functions returning a float value must be placed before FLOAT_FUNCT_TOKEN or the parser won't work right. */
  VAXIS_ROTATE_TOKEN,
  VCROSS_TOKEN,
  VECTOR_ID_TOKEN,
  VNORMALIZE_TOKEN,
  VROTATE_TOKEN,
  VTURBULENCE_TOKEN,
  X_TOKEN,
  Y_TOKEN,
  Z_TOKEN,
  TRACE_TOKEN,
  MIN_EXTENT_TOKEN,
  MAX_EXTENT_TOKEN,
  VECTOR_FUNCT_TOKEN, /*WARNING: All new functions returning a vector value must be placed before VECTOR_FUNCT_TOKEN or the parser won't work right. */
  ALPHA_TOKEN,
  BLUE_TOKEN,
  FILTER_TOKEN,
  TRANSMIT_TOKEN,
  GRAY_TOKEN,
  GREEN_TOKEN,
  RED_TOKEN,
  RGBF_TOKEN,
  RGBFT_TOKEN,
  RGBT_TOKEN,
  RGB_TOKEN,
  COLOUR_KEY_TOKEN, /*WARNING: All new keywords which may preceed a COLOUR must be placed  before COLOUR_KEY_TOKEN or the parser won't work right. */
  COLOR_TOKEN,   
  COLOUR_TOKEN,
  COLOUR_ID_TOKEN, /*Note: Not 100% sure about the above tokens.  May move them up later. */
  CHARSET_TOKEN,
  ASCII_TOKEN,
  UTF8_TOKEN,
  ADAPTIVE_TOKEN,
  AGATE_TOKEN,
  ALL_TOKEN,
  ALTITUDE_TOKEN,
  AMBIENT_TOKEN,
  AMPERSAND_TOKEN,
  AREA_LIGHT_TOKEN,
  AT_TOKEN,
  BACK_QUOTE_TOKEN,
  BACK_SLASH_TOKEN,
  BAR_TOKEN,
  BICUBIC_PATCH_TOKEN,
  BLOB_TOKEN,
  BOUNDED_BY_TOKEN,
  BOX_TOKEN,
  BOZO_TOKEN,
  BRICK_TOKEN,
  BRILLIANCE_TOKEN,
  BUMPS_TOKEN,
  BUMP_MAP_TOKEN,
  BUMP_SIZE_TOKEN,
  CAMERA_ID_TOKEN,
  CAMERA_TOKEN,
  CELLS_TOKEN,
  CHECKER_TOKEN,
  CLIPPED_BY_TOKEN,
  COLON_TOKEN,
  COLOR_MAP_TOKEN,
  COLOUR_MAP_ID_TOKEN,
  COLOUR_MAP_TOKEN,
  COMMA_TOKEN,
  COMPONENT_TOKEN,
  COMPOSITE_TOKEN,
  CONE_TOKEN,
  CRAND_TOKEN,
  CUBIC_TOKEN,
  CYLINDER_TOKEN,
  DASH_TOKEN,
  DECLARE_TOKEN,
  DEFAULT_TOKEN,
  DENTS_TOKEN,
  DIFFERENCE_TOKEN,
  DIFFUSE_TOKEN,
  DIRECTION_TOKEN,
  DISC_TOKEN,
  DISTANCE_TOKEN,
  DOLLAR_TOKEN,
  END_OF_FILE_TOKEN,
  EQUALS_TOKEN,
  EXCLAMATION_TOKEN,
  EXPONENT_TOKEN,
  FALLOFF_TOKEN,
  FINISH_ID_TOKEN,
  FINISH_TOKEN,
  FLATNESS_TOKEN,
  FOG_TOKEN,
  FREQUENCY_TOKEN,
  FRESNEL_TOKEN,
  GIF_TOKEN,
  GRADIENT_TOKEN,
  GRANITE_TOKEN,
  HASH_TOKEN,
  HAT_TOKEN,
  HEIGHT_FIELD_TOKEN,
  HEXAGON_TOKEN,
  IDENTIFIER_TOKEN,
  IFF_TOKEN,
  IMAGE_MAP_TOKEN,
  INCLUDE_TOKEN,
  INTERPOLATE_TOKEN,
  INTERSECTION_TOKEN,
  INVERSE_TOKEN,
  IOR_TOKEN,
  JITTER_TOKEN,
  LAMBDA_TOKEN,
  LEFT_ANGLE_TOKEN,
  LEFT_CURLY_TOKEN,
  LEFT_PAREN_TOKEN,
  LEFT_SQUARE_TOKEN,
  LEOPARD_TOKEN,
  LIGHT_SOURCE_TOKEN,
  LOCATION_TOKEN,
  LOOKS_LIKE_TOKEN,
  LOOK_AT_TOKEN,
  MANDEL_TOKEN,
  MAP_TYPE_TOKEN,
  MARBLE_TOKEN,
  MATERIAL_MAP_TOKEN,
  MAX_INTERSECTIONS,
  MAX_TRACE_LEVEL_TOKEN,
  MERGE_TOKEN,
  METALLIC_TOKEN,
  MORTAR_TOKEN,
  NO_SHADOW_TOKEN,
  OBJECT_ID_TOKEN,
  OBJECT_TOKEN,
  OCTAVES_TOKEN,
  OMEGA_TOKEN,
  ONCE_TOKEN,
  ONION_TOKEN,
  PERCENT_TOKEN,
  PHASE_TOKEN,
  PHONG_SIZE_TOKEN,
  PHONG_TOKEN,
  PIGMENT_ID_TOKEN,
  PIGMENT_TOKEN,
  PLANE_TOKEN,
  PLUS_TOKEN,
  POINT_AT_TOKEN,
  POLY_TOKEN,
  POT_TOKEN,
  QUADRIC_TOKEN,
  QUARTIC_TOKEN,
  QUESTION_TOKEN,
  QUICK_COLOR_TOKEN,
  QUICK_COLOUR_TOKEN,
  RADIAL_TOKEN,
  RADIUS_TOKEN,
  BRICK_SIZE_TOKEN,
  REFLECTION_TOKEN,
  REFRACTION_TOKEN,
  RIGHT_ANGLE_TOKEN,
  RIGHT_CURLY_TOKEN,
  RIGHT_PAREN_TOKEN,
  RIGHT_SQUARE_TOKEN,
  RIGHT_TOKEN,
  RIPPLES_TOKEN,
  ROTATE_TOKEN,
  ROUGHNESS_TOKEN,
  SCALE_TOKEN,
  SEMI_COLON_TOKEN,
  SINGLE_QUOTE_TOKEN,
  SKY_TOKEN,
  SLASH_TOKEN,
  SMOOTH_TOKEN,
  SMOOTH_TRIANGLE_TOKEN,
  SPECULAR_TOKEN,
  SPHERE_TOKEN,
  SPOTLIGHT_TOKEN,
  SPOTTED_TOKEN,
  STAR_TOKEN,
  STRING_LITERAL_TOKEN,
  STURM_TOKEN,
  TEXTURE_ID_TOKEN,
  TEXTURE_TOKEN,
  INTERIOR_TEXTURE_TOKEN,
  TGA_TOKEN,
  THRESHOLD_TOKEN,
  TIFF_TOKEN,
  TIGHTNESS_TOKEN,
  TILDE_TOKEN,
  TILE2_TOKEN,
  TILES_TOKEN,
  TNORMAL_ID_TOKEN,
  TNORMAL_TOKEN,
  TORUS_TOKEN,
  TRANSFORM_ID_TOKEN,
  TRANSFORM_TOKEN,
  TRANSLATE_TOKEN,
  TRIANGLE_TOKEN,
  TURBULENCE_TOKEN,
  TYPE_TOKEN,
  UNION_TOKEN,
  UP_TOKEN,
  USE_COLOR_TOKEN,
  USE_COLOUR_TOKEN,
  USE_INDEX_TOKEN,
  U_STEPS_TOKEN,
  V_STEPS_TOKEN,
  WATER_LEVEL_TOKEN,
  WAVES_TOKEN,
  WOOD_TOKEN,
  WRINKLES_TOKEN,
  BACKGROUND_TOKEN,
  OPEN_TOKEN,
  AGATE_TURB_TOKEN,
  IRID_TOKEN,
  THICKNESS_TOKEN,
  IRID_WAVELENGTH_TOKEN,
  CRACKLE_TOKEN,
  ADC_BAILOUT_TOKEN,
  FILL_LIGHT_TOKEN,
  NUMBER_OF_WAVES_TOKEN,
  FOG_TYPE_TOKEN,
  FOG_ALT_TOKEN,
  FOG_OFFSET_TOKEN,
  TEXT_TOKEN,
  TTF_TOKEN,
  REL_GE_TOKEN,
  REL_LE_TOKEN,
  REL_NE_TOKEN,
  APERTURE_TOKEN,
  BLUR_SAMPLES_TOKEN,
  FOCAL_POINT_TOKEN,
  QUILTED_TOKEN,
  CONTROL0_TOKEN,
  CONTROL1_TOKEN,
  RAINBOW_TOKEN,
  SKYSPHERE_TOKEN,
  ANGLE_TOKEN,
  WIDTH_TOKEN,
  ARC_ANGLE_TOKEN,
  PERSPECTIVE_TOKEN,
  ORTHOGRAPHIC_TOKEN,
  FISHEYE_TOKEN,
  ULTRA_WIDE_ANGLE_TOKEN,
  OMNIMAX_TOKEN,
  PANORAMIC_TOKEN,
  LATHE_TOKEN,
  LINEAR_SPLINE_TOKEN,
  QUADRATIC_SPLINE_TOKEN,
  CUBIC_SPLINE_TOKEN,
  BEZIER_SPLINE_TOKEN,
  POLYGON_TOKEN,
  PRISM_TOKEN,
  LINEAR_SWEEP_TOKEN,
  CONIC_SWEEP_TOKEN,
  SOR_TOKEN,
  SPIRAL1_TOKEN,
  SPIRAL2_TOKEN,
  STRENGTH_TOKEN,
  HIERARCHY_TOKEN,
  RAMP_WAVE_TOKEN,
  TRIANGLE_WAVE_TOKEN,
  SINE_WAVE_TOKEN,
  SCALLOP_WAVE_TOKEN,
  PIGMENT_MAP_TOKEN,
  NORMAL_MAP_TOKEN,
  SLOPE_MAP_TOKEN,
  TEXTURE_MAP_TOKEN,
  PIGMENT_MAP_ID_TOKEN,
  NORMAL_MAP_ID_TOKEN,
  SLOPE_MAP_ID_TOKEN,
  TEXTURE_MAP_ID_TOKEN,
  SUPERELLIPSOID_TOKEN,
  QUATERNION_TOKEN,
  CUBE_TOKEN,
  MAX_ITERATION_TOKEN,
  HYPERCOMPLEX_TOKEN,
  RAINBOW_ID_TOKEN,
  FOG_ID_TOKEN,
  SKYSPHERE_ID_TOKEN,
  FADE_POWER_TOKEN,
  FADE_COLOUR_TOKEN,
  FADE_COLOR_TOKEN,
  FADE_DISTANCE_TOKEN,
  TURB_DEPTH_TOKEN,
  PPM_TOKEN,
  PGM_TOKEN,
  AVERAGE_TOKEN,
  MESH_TOKEN,
  WARP_TOKEN,
  OFFSET_TOKEN,
  REPEAT_TOKEN,
  BLACK_HOLE_TOKEN,
  FLIP_TOKEN,
  AMBIENT_LIGHT_TOKEN,
  IF_TOKEN,
  ELSE_TOKEN,
  END_TOKEN,
  SWITCH_TOKEN,
  CASE_TOKEN,
  RANGE_TOKEN,
  WHILE_TOKEN,
  BREAK_TOKEN,
  FALLOFF_ANGLE_TOKEN,
  CAUSTICS_TOKEN,
  JULIA_FRACTAL_TOKEN,
  SQR_TOKEN,
  RECIPROCAL_TOKEN,
  STR_TOKEN,
  VSTR_TOKEN,
  CONCAT_TOKEN,
  CHR_TOKEN,
  SUBSTR_TOKEN,
  STRING_ID_TOKEN,
  WARNING_TOKEN,
  ERROR_TOKEN,
  RENDER_TOKEN,
  STATISTICS_TOKEN,
  DEBUG_TOKEN,
  VARIANCE_TOKEN,
  CONFIDENCE_TOKEN,
  RADIOSITY_TOKEN,
  BRIGHTNESS_TOKEN,
  COUNT_TOKEN,
  DISTANCE_MAXIMUM_TOKEN,
  ERROR_BOUND_TOKEN,
  GRAY_THRESHOLD_TOKEN,
  LOW_ERROR_FACTOR_TOKEN,
  MINIMUM_REUSE_TOKEN,
  NEAREST_COUNT_TOKEN,
  RECURSION_LIMIT_TOKEN,
  HF_GRAY_16_TOKEN,
  GLOBAL_SETTINGS_TOKEN,
  ECCENTRICITY_TOKEN,
  HOLLOW_TOKEN,
  MEDIA_ATTENUATION_TOKEN,
  MEDIA_INTERACTION_TOKEN,
  MATRIX_TOKEN,
  PERIOD_TOKEN,
  SYS_TOKEN,
  STRUPR_TOKEN,
  STRLWR_TOKEN,
  U_TOKEN,
  V_TOKEN,
  IFDEF_TOKEN,
  PNG_TOKEN,
  PRECISION_TOKEN,
  SLICE_TOKEN,
  ASSUMED_GAMMA_TOKEN,
  PWR_TOKEN,
  T_TOKEN,
  IFNDEF_TOKEN,
  MEDIA_TOKEN, /* Media stuff. */
  MEDIA_ID_TOKEN,
  DENSITY_ID_TOKEN,
  DENSITY_TOKEN,
  DENSITY_FILE_TOKEN,
  RATIO_TOKEN,
  SCATTERING_TOKEN,
  EMISSION_TOKEN,
  ABSORPTION_TOKEN,
  SAMPLES_TOKEN,
  INTERVALS_TOKEN,
  INTERIOR_TOKEN,
  INTERIOR_ID_TOKEN,
  EXTERIOR_TOKEN,
  LOCAL_TOKEN,
  UNDEF_TOKEN,
  MACRO_TOKEN,
  MACRO_ID_TOKEN, 
  TEMPORARY_MACRO_ID_TOKEN,
  PARAMETER_ID_TOKEN, 
  ARRAY_TOKEN, 
  ARRAY_ID_TOKEN, 
  EMPTY_ARRAY_TOKEN, 
  FILE_ID_TOKEN,
  FOPEN_TOKEN,
  FCLOSE_TOKEN,
  WRITE_TOKEN,
  READ_TOKEN,
  APPEND_TOKEN,
  PLANAR_TOKEN,
  SPHERICAL_TOKEN,
  BOXED_TOKEN,
  CYLINDRICAL_TOKEN,
  CUBIC_WAVE_TOKEN,
  POLY_WAVE_TOKEN,
  DENSITY_MAP_TOKEN,
  DENSITY_MAP_ID_TOKEN,
  REFLECTION_EXPONENT_TOKEN,
  DF3_TOKEN,
  EXTINCTION_TOKEN,
  MATERIAL_TOKEN,
  MATERIAL_ID_TOKEN,
  UV_ID_TOKEN,
  VECTOR_4D_ID_TOKEN,
  UV_MAPPING_TOKEN,
  UV_VECTORS_TOKEN,
  MESH2_TOKEN,
  VERTEX_VECTORS_TOKEN,
  NORMAL_VECTORS_TOKEN,
  FACE_INDICES_TOKEN,
  NORMAL_INDICES_TOKEN,
  UV_INDICES_TOKEN,
  TEXTURE_LIST_TOKEN,
  IMAGE_PATTERN_TOKEN,
  USE_ALPHA_TOKEN,
  DOUBLE_ILLUMINATE_TOKEN,
  INSIDE_VECTOR_TOKEN,
  PHOTONS_TOKEN,
  STEPS_TOKEN,
  PASS_THROUGH_TOKEN,
  COLLECT_TOKEN,
  AUTOSTOP_TOKEN,
  GATHER_TOKEN,
  SPLIT_UNION_TOKEN,
  EXPAND_THRESHOLDS_TOKEN,
  SPACING_TOKEN,
  TARGET_TOKEN,
  PARAMETRIC_TOKEN,
  PRECOMPUTE_TOKEN,
  CONTAINED_BY_TOKEN,
  ISOSURFACE_TOKEN,
  METHOD_TOKEN,
  ACCURACY_TOKEN,
  MAX_GRADIENT_TOKEN,
  MAX_TRACE_TOKEN,
  FUNCTION_TOKEN,
  EVALUATE_TOKEN,
  FUNCT_ID_TOKEN,
  VECTFUNCT_ID_TOKEN,
  ALL_INTERSECTIONS_TOKEN,
  DISPERSION_TOKEN,
  DISPERSION_SAMPLES_TOKEN,
  ORIENT_TOKEN,
  CIRCULAR_TOKEN,
  NO_IMAGE_TOKEN,
  NO_REFLECTION_TOKEN,
  LIGHT_GROUP_TOKEN,
  NATURAL_SPLINE_TOKEN,
  B_SPLINE_TOKEN, 
  TOLERANCE_TOKEN, 
  PROJECTED_THROUGH_TOKEN, 
  PARALLEL_TOKEN, 
  SPHERE_SWEEP_TOKEN, 
  SPLINE_TOKEN,
  SPLINE_ID_TOKEN,
  PATTERN_TOKEN,
  FACETS_TOKEN, 
  SLOPE_TOKEN, 
  SOLID_TOKEN, 
  COORDS_TOKEN, 
  SIZE_TOKEN, 
  METRIC_TOKEN, 
  FORM_TOKEN, 
  ORIENTATION_TOKEN, 
  TOROIDAL_TOKEN,
  DIST_EXP_TOKEN,
  MAJOR_RADIUS_TOKEN,
  JPEG_TOKEN,
  AA_THRESHOLD_TOKEN,
  AA_LEVEL_TOKEN,
  LOAD_FILE_TOKEN,
  SAVE_FILE_TOKEN,
  ALWAYS_SAMPLE_TOKEN,
  PRETRACE_START_TOKEN,
  PRETRACE_END_TOKEN,
  MAX_SAMPLE_TOKEN,
  GLOBAL_LIGHTS_TOKEN,
  CUTAWAY_TEXTURES_TOKEN,
  NO_BUMP_SCALE_TOKEN,
  CONSERVE_ENERGY_TOKEN,
  PIGMENT_PATTERN_TOKEN,
  INTERNAL_TOKEN,
  NOISE_GENERATOR_TOKEN,
  JULIA_TOKEN,
  MAGNET_TOKEN,

  // !!!! New for SAR simulator
  // added by Stefan Auer, May 2009
  
  SAR_OUTPUT_DATA_TOKEN,
  SAR_INTERSECTION_TOKEN,

  // !!!! New for SAR simulator

  LAST_TOKEN

#ifdef GLOBAL_PHOTONS
  GLOBAL_TOKEN,
#endif
#if 0
  TRIMMED_BY_ID_TOKEN,
  RATIONAL_TOKEN,
  FIRST_TOKEN, 
  PREVIOUS_TOKEN, 
  TRIMMED_BY_TOKEN,
#endif 
#if 0
  BEZIER_PATCH_TOKEN, 
#endif
};


/*****************************************************************************
* Global typedefs
******************************************************************************/


/*****************************************************************************
* Global variables
******************************************************************************/

extern short Not_In_Default;
extern short Ok_To_Declare;
extern short LValue_Ok;

extern CAMERA *Default_Camera;

// !!!! New for SAR simulator
  // added by Stefan Auer, May 2009

extern DBL SAR_Output_Data_Flag;
extern DBL SAR_Intersection_Flag;

// !!!

/*****************************************************************************
* Global functions
******************************************************************************/

void Parse_Error (TOKEN Token_Id);
void Found_Instead_Error (const char *exstr, const char *extokstr);
void Parse_Begin (void);
void Parse_End (void);
void Parse_Comma (void);
void Parse_Semi_Colon (bool force_semicolon);
void Destroy_Frame (void);
void Parse (void);
void MAError (const char *str, long size);
void Warn_State (TOKEN Token_Id, TOKEN Type);
void Only_In (const char *s1,const char *s2);
void Not_With (const char *s1,const char *s2);
void Warn_Compat (int f, const char *sym);
void Link_Textures (TEXTURE **Old_Texture, TEXTURE *New_Texture);

void Parse_Object_Mods (OBJECT *Object);
OBJECT *Parse_Object (void);
OBJECT *Parse_Bound_Clip (void);
void Parse_Default (void);
void Parse_Declare (bool is_local, bool after_hash);
void Parse_Matrix (MATRIX Matrix);
void Destroy_Ident_Data (void *Data, int Type);
int Parse_RValue (int Previous, int *NumberPtr, void **DataPtr, SYM_ENTRY *sym, bool ParFlag, bool SemiFlag, bool is_local, bool allow_redefine, int old_table_index);
char *Get_Token_String (TOKEN Token_Id);
void Test_Redefine(TOKEN Previous, TOKEN *NumberPtr, void *Data, bool allow_redefine = true);
void Expectation_Error(const char *);
void *Copy_Identifier(void *Data, int Type);
TRANSFORM *Parse_Transform(TRANSFORM *Trans = NULL);
TRANSFORM *Parse_Transform_Block(TRANSFORM *New = NULL);
char *Get_Reserved_Words (const char *additional_words) ;

END_POV_NAMESPACE

#endif
  

