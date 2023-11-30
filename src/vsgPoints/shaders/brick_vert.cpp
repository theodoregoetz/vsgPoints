#include <vsg/io/VSG.h>
#include <vsg/io/mem_stream.h>
static auto brick_vert = []() {
static const char str[] = 
R"(#vsga 1.1.0
Root id=1 vsg::ShaderStage
{
  userObjects 0
  mask 18446744073709551615
  stage 1
  entryPointName "main"
  module id=2 vsg::ShaderModule
  {
    userObjects 0
    hints id=0
    source "#version 450
#extension GL_ARB_separate_shader_objects : enable
#pragma import_defines (VSG_POSITION_SCALE)

#define VIEW_DESCRIPTOR_SET 0
#define MATERIAL_DESCRIPTOR_SET 1

layout(push_constant) uniform PushConstants {
    mat4 projection;
    mat4 modelView;
} pc;


layout(location = 0) in vec3 vsg_Vertex;
layout(location = 1) in vec3 vsg_Normal;
layout(location = 2) in vec4 vsg_Color;

#ifdef VSG_POSITION_SCALE
layout(location = 3) in vec4 vsg_PositionScale;
#endif

layout(location = 4) in vec2 vsg_PointSize;

layout(location = 0) out vec3 eyePos;
layout(location = 1) out vec3 normalDir;
layout(location = 2) out vec4 vertexColor;

layout(location = 5) out vec3 viewDir;

layout(set = VIEW_DESCRIPTOR_SET, binding = 1) uniform ViewportData
{
    vec4 values[1];
} viewportData;

out gl_PerVertex{
    vec4 gl_Position;
    float gl_PointSize;
};

void main()
{

    #ifdef VSG_POSITION_SCALE
    vec4 vertex = vec4(vsg_PositionScale.xyz + vsg_Vertex * vsg_PositionScale.w, 1.0);
    #else
    vec4 vertex = vec4(vsg_Vertex, 1.0);
    #endif

    vec4 normal = vec4(vsg_Normal, 0.0);

    gl_Position = (pc.projection * pc.modelView) * vertex;

    eyePos = vec4(pc.modelView * vertex).xyz;
    viewDir = -eyePos;//normalize(-eyePos);
    normalDir = (pc.modelView * normal).xyz;
    vertexColor = vsg_Color;

    float dist = max(vsg_PointSize[1], abs(eyePos.z));
    vec4 viewport = viewportData.values[0];
    gl_PointSize = viewport[3] * (vsg_PointSize[0] / dist);
}

"
    code 750
     119734787 65536 524299 106 0 131089 1 393227 1 1280527431 1685353262 808793134
     0 196622 0 1 917519 0 4 1852399981 0 12 20 29
     48 59 62 68 70 76 196611 2 450 589828 1096764487 1935622738
     1918988389 1600484449 1684105331 1868526181 1667590754 29556 262149 4 1852399981 0 262149 9
     1953654134 30821 327685 12 1600615286 1953654102 30821 262149 19 1836216174 27745 327685
     20 1600615286 1836216142 27745 393221 27 1348430951 1700164197 2019914866 0 393222 27
     0 1348430951 1953067887 7237481 458758 27 1 1348430951 1953393007 1702521171 0 196613
     29 0 393221 33 1752397136 1936617283 1953390964 115 393222 33 0 1785688688
     1769235301 28271 393222 33 1 1701080941 1701402220 119 196613 35 25456 262149
     48 1348827493 29551 262149 59 2003134838 7498052 327685 62 1836216174 1766091873 114
     327685 68 1953654134 1866692709 7499628 327685 70 1600615286 1869377347 114 262149 73
     1953720676 0 393221 76 1600615286 1852403536 2053722996 101 327685 88 2003134838 1953656688
     0 393221 90 2003134806 1953656688 1635017028 0 327686 90 0 1970037110 29541
     393221 92 2003134838 1953656688 1635017028 0 262215 12 30 0 262215 20
     30 1 327752 27 0 11 0 327752 27 1 11 1
     196679 27 2 262216 33 0 5 327752 33 0 35 0
     327752 33 0 7 16 262216 33 1 5 327752 33 1
     35 64 327752 33 1 7 16 196679 33 2 262215 48
     30 0 262215 59 30 5 262215 62 30 1 262215 68
     30 2 262215 70 30 2 262215 76 30 4 262215 89
     6 16 327752 90 0 35 0 196679 90 2 262215 92
     34 0 262215 92 33 1 131091 2 196641 3 2 196630
     6 32 262167 7 6 4 262176 8 7 7 262167 10
     6 3 262176 11 1 10 262203 11 12 1 262187 6
     14 1065353216 262203 11 20 1 262187 6 22 0 262174 27
     7 6 262176 28 3 27 262203 28 29 3 262165 30
     32 1 262187 30 31 0 262168 32 7 4 262174 33
     32 32 262176 34 9 33 262203 34 35 9 262176 36
     9 32 262187 30 39 1 262176 45 3 7 262176 47
     3 10 262203 47 48 3 262203 47 59 3 262203 47
     62 3 262203 45 68 3 262176 69 1 7 262203 69
     70 1 262176 72 7 6 262167 74 6 2 262176 75
     1 74 262203 75 76 1 262165 77 32 0 262187 77
     78 1 262176 79 1 6 262187 77 82 2 262176 83
     3 6 262172 89 7 78 196638 90 89 262176 91 2
     90 262203 91 92 2 262176 93 2 7 262187 77 96
     3 262187 77 99 0 327734 2 4 0 3 131320 5
     262203 8 9 7 262203 8 19 7 262203 72 73 7
     262203 8 88 7 262205 10 13 12 327761 6 15 13
     0 327761 6 16 13 1 327761 6 17 13 2 458832
     7 18 15 16 17 14 196670 9 18 262205 10 21
     20 327761 6 23 21 0 327761 6 24 21 1 327761
     6 25 21 2 458832 7 26 23 24 25 22 196670
     19 26 327745 36 37 35 31 262205 32 38 37 327745
     36 40 35 39 262205 32 41 40 327826 32 42 38
     41 262205 7 43 9 327825 7 44 42 43 327745 45
     46 29 31 196670 46 44 327745 36 49 35 39 262205
     32 50 49 262205 7 51 9 327825 7 52 50 51
     327761 6 53 52 0 327761 6 54 52 1 327761 6
     55 52 2 327761 6 56 52 3 458832 7 57 53
     54 55 56 524367 10 58 57 57 0 1 2 196670
     48 58 262205 10 60 48 262271 10 61 60 196670 59
     61 327745 36 63 35 39 262205 32 64 63 262205 7
     65 19 327825 7 66 64 65 524367 10 67 66 66
     0 1 2 196670 62 67 262205 7 71 70 196670 68
     71 327745 79 80 76 78 262205 6 81 80 327745 83
     84 48 82 262205 6 85 84 393228 6 86 1 4
     85 458764 6 87 1 40 81 86 196670 73 87 393281
     93 94 92 31 31 262205 7 95 94 196670 88 95
     327745 72 97 88 96 262205 6 98 97 327745 79 100
     76 99 262205 6 101 100 262205 6 102 73 327816 6
     103 101 102 327813 6 104 98 103 327745 83 105 29
     39 196670 105 104 65789 65592
  }
  NumSpecializationConstants 0
}
)";
vsg::VSG io;
return io.read_cast<vsg::ShaderStage>(reinterpret_cast<const uint8_t*>(str), sizeof(str));
};
