#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
//
// Buffer Definitions: 
//
// cbuffer Material
// {
//
//   float3 Kd;                         // Offset:    0 Size:    12
//   float dissolve;                    // Offset:   12 Size:     4
//   float3 Ks;                         // Offset:   16 Size:    12 [unused]
//   float Ns;                          // Offset:   28 Size:     4 [unused]
//   float material_param1;             // Offset:   32 Size:     4 [unused]
//   float material_param2;             // Offset:   36 Size:     4 [unused]
//   float material_param3;             // Offset:   40 Size:     4 [unused]
//   float material_param4;             // Offset:   44 Size:     4 [unused]
//
// }
//
// cbuffer LightData
// {
//
//   float3 Ia;                         // Offset:    0 Size:    12
//   uint nb_omnilights;                // Offset:   12 Size:     4
//   float3 Id;                         // Offset:   16 Size:    12
//   uint nb_spotlights;                // Offset:   28 Size:     4
//   float3 d;                          // Offset:   32 Size:    12
//   uint padding;                      // Offset:   44 Size:     4 [unused]
//
// }
//
// Resource bind info for omni_lights
// {
//
//   struct OmniLight
//   {
//       
//       float4 p;                      // Offset:    0
//       float3 I;                      // Offset:   16
//       float distance_falloff_start;  // Offset:   28
//       float distance_falloff_end;    // Offset:   32
//       uint padding[3];               // Offset:   36
//
//   } $Element;                        // Offset:    0 Size:    48
//
// }
//
// Resource bind info for spot_lights
// {
//
//   struct SpotLight
//   {
//       
//       float4 p;                      // Offset:    0
//       float3 I;                      // Offset:   16
//       float exponent_property;       // Offset:   28
//       float3 d;                      // Offset:   32
//       float distance_falloff_start;  // Offset:   44
//       float distance_falloff_end;    // Offset:   48
//       float cos_penumbra;            // Offset:   52
//       float cos_umbra;               // Offset:   56
//       uint padding;                  // Offset:   60
//
//   } $Element;                        // Offset:    0 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// texture_sampler                   sampler      NA          NA    0        1
// diffuse_texture_map               texture  float4          2d    0        1
// omni_lights                       texture  struct         r/o    1        1
// spot_lights                       texture  struct         r/o    2        1
// normal_texture_map                texture  float4          2d    4        1
// Material                          cbuffer      NA          NA    1        1
// LightData                         cbuffer      NA          NA    2        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float       
// POSITION                 0   xyzw        1     NONE   float   xyz 
// NORMAL                   0   xyz         2     NONE   float   xyz 
// TEXCOORD                 0   xy          3     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb1[1], immediateIndexed
dcl_constantbuffer cb2[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_structured t1, 48 
dcl_resource_structured t2, 64 
dcl_resource_texture2d (float,float,float,float) t4
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xyz
dcl_input_ps linear v3.xy
dcl_output o0.xyzw
dcl_temps 7
dp3 r0.x, v2.xyzx, v2.xyzx
rsq r0.x, r0.x
mul r0.xyz, r0.xxxx, v2.xyzx
deriv_rtx_coarse r1.xyz, v1.yzxy
deriv_rty_coarse r2.xyz, v1.zxyz
deriv_rtx_coarse r3.xy, v3.xyxx
deriv_rty_coarse r3.zw, v3.xxxy
mul r4.xyz, r0.yzxy, r2.xyzx
mad r2.xyz, r2.zxyz, r0.zxyz, -r4.xyzx
mul r4.xyz, r0.zxyz, r1.xyzx
mad r1.xyz, r0.yzxy, r1.yzxy, -r4.xyzx
mul r4.xyz, r1.xyzx, r3.zzzz
mad r4.xyz, r3.xxxx, r2.xyzx, r4.xyzx
mul r1.xyz, r1.xyzx, r3.wwww
mad r1.xyz, r3.yyyy, r2.xyzx, r1.xyzx
dp3 r0.w, r4.xyzx, r4.xyzx
dp3 r1.w, r1.xyzx, r1.xyzx
max r0.w, r0.w, r1.w
rsq r0.w, r0.w
mul r2.xyz, r0.wwww, r4.xyzx
mul r1.xyz, r0.wwww, r1.xyzx
sample_indexable(texture2d)(float,float,float,float) r3.xyz, v3.xyxx, t4.xyzw, s0
mad r3.xyz, r3.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), l(-1.000000, -1.000000, -1.000000, 0.000000)
mul r1.xyz, r1.xyzx, r3.yyyy
mad r1.xyz, r3.xxxx, r2.xyzx, r1.xyzx
mad r0.xyz, r3.zzzz, r0.xyzx, r1.xyzx
dp3 r0.w, r0.xyzx, r0.xyzx
rsq r0.w, r0.w
mul r0.xyz, r0.wwww, r0.xyzx
dp3 r0.w, r0.xyzx, -cb2[2].xyzx
max r0.w, r0.w, l(0.000000)
mad r1.xyz, r0.wwww, cb2[1].xyzx, cb2[0].xyzx
mov r2.xyz, r1.xyzx
mov r0.w, l(0)
loop 
  uge r1.w, r0.w, cb2[0].w
  breakc_nz r1.w
  ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r3.xyz, r0.w, l(0), t1.xyzx
  ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r4.xyzw, r0.w, l(16), t1.xyzw
  ld_structured_indexable(structured_buffer, stride=48)(mixed,mixed,mixed,mixed) r1.w, r0.w, l(32), t1.xxxx
  add r3.xyz, r3.xyzx, -v1.xyzx
  dp3 r2.w, r3.xyzx, r3.xyzx
  rsq r3.w, r2.w
  mul r3.xyz, r3.wwww, r3.xyzx
  sqrt r2.w, r2.w
  add r2.w, r1.w, -r2.w
  add r1.w, -r4.w, r1.w
  div_sat r1.w, r2.w, r1.w
  mul r4.xyz, r4.xyzx, r1.wwww
  dp3 r1.w, r0.xyzx, r3.xyzx
  max r1.w, r1.w, l(0.000000)
  mad r2.xyz, r1.wwww, r4.xyzx, r2.xyzx
  iadd r0.w, r0.w, l(1)
endloop 
mov r1.xyz, r2.xyzx
mov r0.w, l(0)
loop 
  uge r1.w, r0.w, cb2[1].w
  breakc_nz r1.w
  ld_structured_indexable(structured_buffer, stride=64)(mixed,mixed,mixed,mixed) r3.xyz, r0.w, l(0), t2.xyzx
  ld_structured_indexable(structured_buffer, stride=64)(mixed,mixed,mixed,mixed) r4.xyzw, r0.w, l(16), t2.xyzw
  ld_structured_indexable(structured_buffer, stride=64)(mixed,mixed,mixed,mixed) r5.xyzw, r0.w, l(32), t2.xyzw
  ld_structured_indexable(structured_buffer, stride=64)(mixed,mixed,mixed,mixed) r6.xyz, r0.w, l(48), t2.xyzx
  add r3.xyz, r3.xyzx, -v1.xyzx
  dp3 r1.w, r3.xyzx, r3.xyzx
  rsq r2.w, r1.w
  mul r3.xyz, r2.wwww, r3.xyzx
  sqrt r1.w, r1.w
  dp3 r2.w, r5.xyzx, -r3.xyzx
  add r1.w, -r1.w, r6.x
  add r3.w, -r5.w, r6.x
  div_sat r1.w, r1.w, r3.w
  add r2.w, -r6.z, r2.w
  add r3.w, -r6.z, r6.y
  div_sat r2.w, r2.w, r3.w
  log r2.w, r2.w
  mul r2.w, r2.w, r4.w
  exp r2.w, r2.w
  mul r1.w, r1.w, r2.w
  mul r4.xyz, r4.xyzx, r1.wwww
  dp3 r1.w, r0.xyzx, r3.xyzx
  max r1.w, r1.w, l(0.000000)
  mad r1.xyz, r1.wwww, r4.xyzx, r1.xyzx
  iadd r0.w, r0.w, l(1)
endloop 
mul r0.xyz, r1.xyzx, cb1[0].xyzx
sample_indexable(texture2d)(float,float,float,float) r1.xyzw, v3.xyxx, t0.xyzw, s0
mul o0.xyz, r0.xyzx, r1.xyzx
mul o0.w, r1.w, cb1[0].w
ret 
// Approximately 90 instruction slots used
#endif

const BYTE g_tsnm_lambertian_ps[] =
{
     68,  88,  66,  67, 117, 185, 
     59,  55, 206,  79, 174, 106, 
    131, 210, 145, 185, 254, 191, 
     87, 111,   1,   0,   0,   0, 
     24,  20,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    252,   7,   0,   0, 148,   8, 
      0,   0, 200,   8,   0,   0, 
    124,  19,   0,   0,  82,  68, 
     69,  70, 192,   7,   0,   0, 
      4,   0,   0,   0, 128,   1, 
      0,   0,   7,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    255, 255,   0,   1,   0,   0, 
    140,   7,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     28,   1,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  44,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  64,   1, 
      0,   0,   5,   0,   0,   0, 
      6,   0,   0,   0,   1,   0, 
      0,   0,  48,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     76,   1,   0,   0,   5,   0, 
      0,   0,   6,   0,   0,   0, 
      1,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  88,   1,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   4,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 107,   1, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    116,   1,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 116, 101, 120, 116, 
    117, 114, 101,  95, 115,  97, 
    109, 112, 108, 101, 114,   0, 
    100, 105, 102, 102, 117, 115, 
    101,  95, 116, 101, 120, 116, 
    117, 114, 101,  95, 109,  97, 
    112,   0, 111, 109, 110, 105, 
     95, 108, 105, 103, 104, 116, 
    115,   0, 115, 112, 111, 116, 
     95, 108, 105, 103, 104, 116, 
    115,   0, 110, 111, 114, 109, 
     97, 108,  95, 116, 101, 120, 
    116, 117, 114, 101,  95, 109, 
     97, 112,   0,  77,  97, 116, 
    101, 114, 105,  97, 108,   0, 
     76, 105, 103, 104, 116,  68, 
     97, 116,  97,   0, 171, 171, 
    107,   1,   0,   0,   8,   0, 
      0,   0, 224,   1,   0,   0, 
     48,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    116,   1,   0,   0,   6,   0, 
      0,   0, 204,   3,   0,   0, 
     48,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     64,   1,   0,   0,   1,   0, 
      0,   0,  20,   5,   0,   0, 
     48,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     76,   1,   0,   0,   1,   0, 
      0,   0, 124,   6,   0,   0, 
     64,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
     32,   3,   0,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
      2,   0,   0,   0,  44,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  80,   3, 
      0,   0,  12,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0,  96,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 132,   3,   0,   0, 
     16,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
     44,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    135,   3,   0,   0,  28,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,  96,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 138,   3, 
      0,   0,  32,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  96,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 154,   3,   0,   0, 
     36,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
     96,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    170,   3,   0,   0,  40,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,  96,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 186,   3, 
      0,   0,  44,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,  96,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  75, 100,   0, 102, 
    108, 111,  97, 116,  51,   0, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  35,   3, 
      0,   0, 100, 105, 115, 115, 
    111, 108, 118, 101,   0, 102, 
    108, 111,  97, 116,   0, 171, 
      0,   0,   3,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  89,   3,   0,   0, 
     75, 115,   0,  78, 115,   0, 
    109,  97, 116, 101, 114, 105, 
     97, 108,  95, 112,  97, 114, 
     97, 109,  49,   0, 109,  97, 
    116, 101, 114, 105,  97, 108, 
     95, 112,  97, 114,  97, 109, 
     50,   0, 109,  97, 116, 101, 
    114, 105,  97, 108,  95, 112, 
     97, 114,  97, 109,  51,   0, 
    109,  97, 116, 101, 114, 105, 
     97, 108,  95, 112,  97, 114, 
     97, 109,  52,   0, 171, 171, 
    188,   4,   0,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
      2,   0,   0,   0,  44,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 191,   4, 
      0,   0,  12,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 212,   4,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 248,   4,   0,   0, 
     16,   0,   0,   0,  12,   0, 
      0,   0,   2,   0,   0,   0, 
     44,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    251,   4,   0,   0,  28,   0, 
      0,   0,   4,   0,   0,   0, 
      2,   0,   0,   0, 212,   4, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,   9,   5, 
      0,   0,  32,   0,   0,   0, 
     12,   0,   0,   0,   2,   0, 
      0,   0,  44,   3,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  11,   5,   0,   0, 
     44,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
    212,   4,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     73,  97,   0, 110,  98,  95, 
    111, 109, 110, 105, 108, 105, 
    103, 104, 116, 115,   0, 100, 
    119, 111, 114, 100,   0, 171, 
      0,   0,  19,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 205,   4,   0,   0, 
     73, 100,   0, 110,  98,  95, 
    115, 112, 111, 116, 108, 105, 
    103, 104, 116, 115,   0, 100, 
      0, 112,  97, 100, 100, 105, 
    110, 103,   0, 171,  60,   5, 
      0,   0,   0,   0,   0,   0, 
     48,   0,   0,   0,   2,   0, 
      0,   0,  88,   6,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  36,  69, 108, 101, 
    109, 101, 110, 116,   0,  79, 
    109, 110, 105,  76, 105, 103, 
    104, 116,   0, 112,   0, 102, 
    108, 111,  97, 116,  52,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  81,   5,   0,   0, 
     73,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     35,   3,   0,   0, 100, 105, 
    115, 116,  97, 110,  99, 101, 
     95, 102,  97, 108, 108, 111, 
    102, 102,  95, 115, 116,  97, 
    114, 116,   0, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     89,   3,   0,   0, 100, 105, 
    115, 116,  97, 110,  99, 101, 
     95, 102,  97, 108, 108, 111, 
    102, 102,  95, 101, 110, 100, 
      0, 171, 171, 171,   0,   0, 
     19,   0,   1,   0,   1,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    205,   4,   0,   0,  79,   5, 
      0,   0,  88,   5,   0,   0, 
      0,   0,   0,   0, 124,   5, 
      0,   0, 128,   5,   0,   0, 
     16,   0,   0,   0, 164,   5, 
      0,   0, 188,   5,   0,   0, 
     28,   0,   0,   0, 224,   5, 
      0,   0, 188,   5,   0,   0, 
     32,   0,   0,   0,  11,   5, 
      0,   0, 248,   5,   0,   0, 
     36,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,  12,   0, 
      0,   0,   5,   0,  28,   6, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     69,   5,   0,   0,  60,   5, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0, 104,   7,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  83, 112, 111, 116, 
     76, 105, 103, 104, 116,   0, 
    101, 120, 112, 111, 110, 101, 
    110, 116,  95, 112, 114, 111, 
    112, 101, 114, 116, 121,   0, 
     99, 111, 115,  95, 112, 101, 
    110, 117, 109,  98, 114,  97, 
      0,  99, 111, 115,  95, 117, 
    109,  98, 114,  97,   0, 171, 
      0,   0,  19,   0,   1,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 205,   4,   0,   0, 
     79,   5,   0,   0,  88,   5, 
      0,   0,   0,   0,   0,   0, 
    124,   5,   0,   0, 128,   5, 
      0,   0,  16,   0,   0,   0, 
    174,   6,   0,   0, 188,   5, 
      0,   0,  28,   0,   0,   0, 
      9,   5,   0,   0, 128,   5, 
      0,   0,  32,   0,   0,   0, 
    164,   5,   0,   0, 188,   5, 
      0,   0,  44,   0,   0,   0, 
    224,   5,   0,   0, 188,   5, 
      0,   0,  48,   0,   0,   0, 
    192,   6,   0,   0, 188,   5, 
      0,   0,  52,   0,   0,   0, 
    205,   6,   0,   0, 188,   5, 
      0,   0,  56,   0,   0,   0, 
     11,   5,   0,   0, 216,   6, 
      0,   0,  60,   0,   0,   0, 
      5,   0,   0,   0,   1,   0, 
     16,   0,   0,   0,   9,   0, 
    252,   6,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 164,   6,   0,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  54, 
     46,  51,  46,  57,  54,  48, 
     48,  46,  49,  54,  51,  56, 
     52,   0, 171, 171,  73,  83, 
     71,  78, 144,   0,   0,   0, 
      4,   0,   0,   0,   8,   0, 
      0,   0, 104,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0, 116,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,  15,   7, 
      0,   0, 125,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   7, 
      0,   0, 132,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   3,   3, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0,  78, 
     79,  82,  77,  65,  76,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0, 171, 171, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     69,  88, 172,  10,   0,   0, 
     80,   0,   0,   0, 171,   2, 
      0,   0, 106,   8,   0,   1, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,  89,   0, 
      0,   4,  70, 142,  32,   0, 
      2,   0,   0,   0,   3,   0, 
      0,   0,  90,   0,   0,   3, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   0,   0, 
      0,   0,  85,  85,   0,   0, 
    162,   0,   0,   4,   0, 112, 
     16,   0,   1,   0,   0,   0, 
     48,   0,   0,   0, 162,   0, 
      0,   4,   0, 112,  16,   0, 
      2,   0,   0,   0,  64,   0, 
      0,   0,  88,  24,   0,   4, 
      0, 112,  16,   0,   4,   0, 
      0,   0,  85,  85,   0,   0, 
     98,  16,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     98,  16,   0,   3, 114,  16, 
     16,   0,   2,   0,   0,   0, 
     98,  16,   0,   3,  50,  16, 
     16,   0,   3,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    104,   0,   0,   2,   7,   0, 
      0,   0,  16,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      2,   0,   0,   0,  70,  18, 
     16,   0,   2,   0,   0,   0, 
     68,   0,   0,   5,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   0,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,  70,  18, 
     16,   0,   2,   0,   0,   0, 
    122,   0,   0,   5, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    150,  20,  16,   0,   1,   0, 
      0,   0, 124,   0,   0,   5, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  38,  25,  16,   0, 
      1,   0,   0,   0, 122,   0, 
      0,   5,  50,   0,  16,   0, 
      3,   0,   0,   0,  70,  16, 
     16,   0,   3,   0,   0,   0, 
    124,   0,   0,   5, 194,   0, 
     16,   0,   3,   0,   0,   0, 
      6,  20,  16,   0,   3,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   4,   0, 
      0,   0, 150,   4,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     38,   9,  16,   0,   2,   0, 
      0,   0,  38,   9,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      4,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      4,   0,   0,   0,  38,   9, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 150,   4,  16,   0, 
      0,   0,   0,   0, 150,   4, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      4,   0,   0,   0,   6,   0, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
    246,  15,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  52,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  68,   0,   0,   5, 
    130,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0, 139, 194,   0, 
      0, 128,  67,  85,  21,   0, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,  16,  16,   0, 
      3,   0,   0,   0,  70, 126, 
     16,   0,   4,   0,   0,   0, 
      0,  96,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  15, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,  64, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128, 191,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    166,  10,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  68,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   9, 130,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,  52,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  50,   0,   0,  11, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   2,   0,   0,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,  54,   0, 
      0,   5, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     54,   0,   0,   5, 130,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  48,   0,   0,   1, 
     80,   0,   0,   8, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  58, 128,  32,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   4,   3, 
     58,   0,  16,   0,   1,   0, 
      0,   0, 167,   0,   0, 139, 
      2, 131,   1, 128, 131, 153, 
     25,   0, 114,   0,  16,   0, 
      3,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,  70, 114,  16,   0, 
      1,   0,   0,   0, 167,   0, 
      0, 139,   2, 131,   1, 128, 
    131, 153,  25,   0, 242,   0, 
     16,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
     16,   0,   0,   0,  70, 126, 
     16,   0,   1,   0,   0,   0, 
    167,   0,   0, 139,   2, 131, 
      1, 128, 131, 153,  25,   0, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,  32,   0,   0,   0, 
      6, 112,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,   8, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,  18, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  68,   0,   0,   5, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      3,   0,   0,   0, 246,  15, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  75,   0,   0,   5, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   8, 130,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   8, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   4,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  14,  32,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0, 246,  15,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  52,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   2,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     30,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      1,   0,   0,   0,  22,   0, 
      0,   1,  54,   0,   0,   5, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      2,   0,   0,   0,  54,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     48,   0,   0,   1,  80,   0, 
      0,   8, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     58, 128,  32,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   4,   3,  58,   0, 
     16,   0,   1,   0,   0,   0, 
    167,   0,   0, 139,   2,   3, 
      2, 128, 131, 153,  25,   0, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,   0, 
     70, 114,  16,   0,   2,   0, 
      0,   0, 167,   0,   0, 139, 
      2,   3,   2, 128, 131, 153, 
     25,   0, 242,   0,  16,   0, 
      4,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,  16,   0, 
      0,   0,  70, 126,  16,   0, 
      2,   0,   0,   0, 167,   0, 
      0, 139,   2,   3,   2, 128, 
    131, 153,  25,   0, 242,   0, 
     16,   0,   5,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
     32,   0,   0,   0,  70, 126, 
     16,   0,   2,   0,   0,   0, 
    167,   0,   0, 139,   2,   3, 
      2, 128, 131, 153,  25,   0, 
    114,   0,  16,   0,   6,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,   1,  64, 
      0,   0,  48,   0,   0,   0, 
     70, 114,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,   8, 
    114,   0,  16,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  70,  18, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  68,   0,   0,   5, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      3,   0,   0,   0, 246,  15, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  75,   0,   0,   5, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   8, 130,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   5,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   8, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   6,   0, 
      0,   0,   0,   0,   0,   8, 
    130,   0,  16,   0,   3,   0, 
      0,   0,  58,   0,  16, 128, 
     65,   0,   0,   0,   5,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,  14,  32, 
      0,   7, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   3,   0, 
      0,   0,   0,   0,   0,   8, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  42,   0,  16, 128, 
     65,   0,   0,   0,   6,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   8, 130,   0,  16,   0, 
      3,   0,   0,   0,  42,   0, 
     16, 128,  65,   0,   0,   0, 
      6,   0,   0,   0,  26,   0, 
     16,   0,   6,   0,   0,   0, 
     14,  32,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      3,   0,   0,   0,  47,   0, 
      0,   5, 130,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      4,   0,   0,   0,  25,   0, 
      0,   5, 130,   0,  16,   0, 
      2,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  58,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  16,   0,   0,   7, 
    130,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     52,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      1,   0,   0,   0, 246,  15, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  30,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   1,   0, 
      0,   0,  22,   0,   0,   1, 
     56,   0,   0,   8, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  69,   0,   0, 139, 
    194,   0,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   3,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 114,  32,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   8, 
    130,  32,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      1,   0,   0,   0,  58, 128, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  62,   0, 
      0,   1,  83,  84,  65,  84, 
    148,   0,   0,   0,  90,   0, 
      0,   0,   7,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,  66,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,   1,   0,   0,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,   7,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};
