/**
 * @file   main.cpp
 * @brief  PurPose's main file
 * @author Maeda Takumi
 */
#include "main.h"
#include "PurPose.h"

KShader* NoneShading(NULL);
KShader* PhongShading(NULL);
KShader* CthulhuXShading(NULL);
KShader* CthulhuYShading(NULL);
KShader* CthulhuZShading(NULL);

static const char* SHADER_VERTEX[]{
    "#version 120\n",
    "",
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "",
    "void main(void) {",
    "    vGLPosition = gl_Vertex;",
    "    vPosition   =           gl_ModelViewMatrix * gl_Vertex;",
    "    vNormal     = normalize(gl_NormalMatrix    * gl_Normal);",
    "",
    "    gl_Position    = ftransform();",
    "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;",
    "}\n",
};
static const char* SHADER_FRAGMENT_NONE[]{
    "#version 120\n",
    ""
    "uniform sampler2D texture;",
    "",
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "",
    "void main(void) {",
    "    gl_FragColor = texture2DProj(texture, gl_TexCoord[0]);" // テクスチャの色そのまま
    "}\n",
};
static const char* SHADER_FRAGMENT_PHONG[]{
    "#version 120\n",
    ""
    "uniform sampler2D texture;",
    "",
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "",
    "void main(void) {",
    "    vec4 color   = texture2DProj(texture, gl_TexCoord[0]);", // テクスチャの色
    "",
    "", // 光線ベクトル・視線ベクトル
    "    vec3 light  = (gl_LightSource[0].position * vPosition.w - gl_LightSource[0].position.w * vPosition).xyz;",
    "    vec3 nLight = normalize(light);",
    "    vec3 view   = -vPosition.xyz;",
    "    vec3 nView  = normalize(view);",
    "    vec3 nHalf  = normalize(nLight + nView);",
    "",
    "", // 距離での減衰
    "    float distance    = length(light);",
    "    float attenuation = min(1.0 / ",
    "                      ( gl_LightSource[0].constantAttenuation",
    "                      + gl_LightSource[0].linearAttenuation    * distance",
    "                      + gl_LightSource[0].quadraticAttenuation * distance * distance)"
    "                      , 1.0);",
    "",
    "", // 角度での減衰
    "    float angle = acos(dot(nLight, nView));",
    "    float LS = dot(-nLight, normalize(gl_LightSource[0].spotDirection));",
    "    if (LS < gl_LightSource[0].spotCosCutoff) attenuation = 0.0;", //スポットライトの外側
    "    else attenuation *= pow(LS, gl_LightSource[0].spotExponent);",
    "",
    "", // 拡散反射率と鏡面反射率
    "    float diffuse  = max(dot(vNormal, nLight), 0.0);",
    "    float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "", // 計算結果(フラグメントの色)
    "    gl_FragColor = color * gl_LightSource[0].diffuse  * diffuse",
    "                 +   gl_FrontLightProduct[0].specular * specular",
    "                 + color * gl_LightSource[0].ambient;",
    "    gl_FragColor = vec4((gl_FragColor * attenuation).xyz, color.w);" // 透過値は変更しない
    "}\n",
};
static const char* SHADER_FRAGMENT_CTHULHUX[]{// 法線がx軸と平行の時のシェーダ
    "#version 120\n",
    ""
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "varying vec3 vGLNormal;", //   法線ベクトル(無変換)
    "",
    "const float PI = 3.141592653589793;",
    "",
    "float interpolate(float a, float b, float x) {",
    "    float  f = (1.0 - cos(x * PI)) * 0.5;",
    "    return mix(a, b, f);", // 線形補間
    "}",
    "",
    "float rand(vec2 p) {",
    "    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);",
    "}",
    "",
    "float irand(vec2 p) {",
    "    vec2 i = floor(p);", // 整数部
    "    vec2 f = fract(p);", // 小数部
    "", // 対応点を囲む矩形
    "    vec4 v = vec4(rand(i),",
    "                  rand(vec2(i.x + 1.0, i.y)),",
    "                  rand(vec2(i.x      , i.y + 1.0)),",
    "                  rand(vec2(i.x + 1.0, i.y + 1.0))",
    "             );",
    "    return interpolate(interpolate(v.x, v.y, f.x), interpolate(v.z, v.w, f.x), f.y);",
    "}",
    "",
    "float noise(vec2 p) {",
    "    return irand(p     ) * 0.00390625",
    "         + irand(p * 0.5) * 0.0078125",
    "         + irand(p * 0.25) * 0.015625",
    "         + irand(p * 0.125) * 0.03125",
    "         + irand(p * 0.0625) * 0.0625",
    "         + irand(p * 0.03125) * 0.125",
    "         + irand(p * 0.015625) * 0.25",
    "         + irand(p * 0.0078125) * 0.5;",
    "}",
    "",
    "void main(void) {",
    "    float n    = noise(vec2(vGLPosition.y, vGLPosition.z) * 255);",
    "    vec4 color = vec4(0.0, n, 0.0, 1.0);",
    "",
    "", // 光線ベクトル・視線ベクトル
    "    vec3 light  = (gl_LightSource[0].position * vPosition.w - gl_LightSource[0].position.w * vPosition).xyz;",
    "    vec3 nLight = normalize(light);",
    "    vec3 view   = -vPosition.xyz;",
    "    vec3 nView  = normalize(view);",
    "    vec3 nHalf  = normalize(nLight + nView);",
    "",
    "", // 距離での減衰
    "    float distance    = length(light);",
    "    float attenuation = min(1.0 / ",
    "                      ( gl_LightSource[0].constantAttenuation",
    "                      + gl_LightSource[0].linearAttenuation    * distance",
    "                      + gl_LightSource[0].quadraticAttenuation * distance * distance)"
    "                      , 1.0);",
    "",
    "", // 角度での減衰
    "    float angle = acos(dot(nLight, nView));",
    "    float LS = dot(-nLight, normalize(gl_LightSource[0].spotDirection));",
    "    if (LS < gl_LightSource[0].spotCosCutoff) attenuation = 0.0;", //スポットライトの外側
    "    else attenuation *= pow(LS, gl_LightSource[0].spotExponent);",
    "",
    "", // 拡散反射率と鏡面反射率
    "    float diffuse  = max(dot(vNormal, nLight), 0.0);",
    "    float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "", // 計算結果(フラグメントの色)
    "    gl_FragColor = color * gl_LightSource[0].diffuse  * diffuse",
    "                 +   gl_FrontLightProduct[0].specular * specular",
    "                 + color * gl_LightSource[0].ambient;",
    "    gl_FragColor = vec4((gl_FragColor * attenuation).xyz, color.w);" // 透過値は変更しない
    "}\n",
};
static const char* SHADER_FRAGMENT_CTHULHUY[]{// 法線がy軸と平行の時のシェーダ
    "#version 120\n",
    ""
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "varying vec3 vGLNormal;", //   法線ベクトル(無変換)
    "",
    "const float PI = 3.141592653589793;",
    "",
    "float interpolate(float a, float b, float x) {",
    "    float  f = (1.0 - cos(x * PI)) * 0.5;",
    "    return mix(a, b, f);", // 線形補間
    "}",
    "",
    "float rand(vec2 p) {",
    "    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);",
    "}",
    "",
    "float irand(vec2 p) {",
    "    vec2 i = floor(p);", // 整数部
    "    vec2 f = fract(p);", // 小数部
    "", // 対応点を囲む矩形
    "    vec4 v = vec4(rand(i),",
    "                  rand(vec2(i.x + 1.0, i.y)),",
    "                  rand(vec2(i.x      , i.y + 1.0)),",
    "                  rand(vec2(i.x + 1.0, i.y + 1.0))",
    "             );",
    "    return interpolate(interpolate(v.x, v.y, f.x), interpolate(v.z, v.w, f.x), f.y);",
    "}",
    "",
    "float noise(vec2 p) {",
    "    return irand(p     ) * 0.00390625",
    "         + irand(p * 0.5) * 0.0078125",
    "         + irand(p * 0.25) * 0.015625",
    "         + irand(p * 0.125) * 0.03125",
    "         + irand(p * 0.0625) * 0.0625",
    "         + irand(p * 0.03125) * 0.125",
    "         + irand(p * 0.015625) * 0.25",
    "         + irand(p * 0.0078125) * 0.5;",
    "}",
    "",
    "void main(void) {",
    "    float n    = noise(vec2(vGLPosition.z, vGLPosition.x) * 255);",
    "    vec4 color = vec4(0.0, n, 0.0, 1.0);",
    "",
    "", // 光線ベクトル・視線ベクトル
    "    vec3 light  = (gl_LightSource[0].position * vPosition.w - gl_LightSource[0].position.w * vPosition).xyz;",
    "    vec3 nLight = normalize(light);",
    "    vec3 view   = -vPosition.xyz;",
    "    vec3 nView  = normalize(view);",
    "    vec3 nHalf  = normalize(nLight + nView);",
    "",
    "", // 距離での減衰
    "    float distance    = length(light);",
    "    float attenuation = min(1.0 / ",
    "                      ( gl_LightSource[0].constantAttenuation",
    "                      + gl_LightSource[0].linearAttenuation    * distance",
    "                      + gl_LightSource[0].quadraticAttenuation * distance * distance)"
    "                      , 1.0);",
    "",
    "", // 角度での減衰
    "    float angle = acos(dot(nLight, nView));",
    "    float LS = dot(-nLight, normalize(gl_LightSource[0].spotDirection));",
    "    if (LS < gl_LightSource[0].spotCosCutoff) attenuation = 0.0;", //スポットライトの外側
    "    else attenuation *= pow(LS, gl_LightSource[0].spotExponent);",
    "",
    "", // 拡散反射率と鏡面反射率
    "    float diffuse  = max(dot(vNormal, nLight), 0.0);",
    "    float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "", // 計算結果(フラグメントの色)
    "    gl_FragColor = color * gl_LightSource[0].diffuse  * diffuse",
    "                 +   gl_FrontLightProduct[0].specular * specular",
    "                 + color * gl_LightSource[0].ambient;",
    "    gl_FragColor = vec4((gl_FragColor * attenuation).xyz, color.w);" // 透過値は変更しない
    "}\n",
};
static const char* SHADER_FRAGMENT_CTHULHUZ[]{// 法線がz軸と平行の時のシェーダ
    "#version 120\n",
    ""
    "varying vec4 vPosition;", //   頂点座標
    "varying vec4 vGLPosition;", // 頂点座標(無変換)
    "varying vec3 vNormal;", //     法線ベクトル
    "varying vec3 vGLNormal;", //   法線ベクトル(無変換)
    "",
    "const float PI = 3.141592653589793;",
    "",
    "float interpolate(float a, float b, float x) {",
    "    float  f = (1.0 - cos(x * PI)) * 0.5;",
    "    return mix(a, b, f);", // 線形補間
    "}",
    "",
    "float rand(vec2 p) {",
    "    return fract(sin(dot(p, vec2(12.9898, 78.233))) * 43758.5453);",
    "}",
    "",
    "float irand(vec2 p) {",
    "    vec2 i = floor(p);", // 整数部
    "    vec2 f = fract(p);", // 小数部
    "", // 対応点を囲む矩形
    "    vec4 v = vec4(rand(i),",
    "                  rand(vec2(i.x + 1.0, i.y)),",
    "                  rand(vec2(i.x      , i.y + 1.0)),",
    "                  rand(vec2(i.x + 1.0, i.y + 1.0))",
    "             );",
    "    return interpolate(interpolate(v.x, v.y, f.x), interpolate(v.z, v.w, f.x), f.y);",
    "}",
    "",
    "float noise(vec2 p) {",
    "    return irand(p     ) * 0.00390625",
    "         + irand(p * 0.5) * 0.0078125",
    "         + irand(p * 0.25) * 0.015625",
    "         + irand(p * 0.125) * 0.03125",
    "         + irand(p * 0.0625) * 0.0625",
    "         + irand(p * 0.03125) * 0.125",
    "         + irand(p * 0.015625) * 0.25",
    "         + irand(p * 0.0078125) * 0.5;",
    "}",
    "",
    "void main(void) {",
    "    float n    = noise(vec2(vGLPosition.x, vGLPosition.y) * 255);",
    "    vec4 color = vec4(0.0, n, 0.0, 1.0);",
    "",
    "", // 光線ベクトル・視線ベクトル
    "    vec3 light  = (gl_LightSource[0].position * vPosition.w - gl_LightSource[0].position.w * vPosition).xyz;",
    "    vec3 nLight = normalize(light);",
    "    vec3 view   = -vPosition.xyz;",
    "    vec3 nView  = normalize(view);",
    "    vec3 nHalf  = normalize(nLight + nView);",
    "",
    "", // 距離での減衰
    "    float distance    = length(light);",
    "    float attenuation = min(1.0 / ",
    "                      ( gl_LightSource[0].constantAttenuation",
    "                      + gl_LightSource[0].linearAttenuation    * distance",
    "                      + gl_LightSource[0].quadraticAttenuation * distance * distance)"
    "                      , 1.0);",
    "",
    "", // 角度での減衰
    "    float angle = acos(dot(nLight, nView));",
    "    float LS = dot(-nLight, normalize(gl_LightSource[0].spotDirection));",
    "    if (LS < gl_LightSource[0].spotCosCutoff) attenuation = 0.0;", //スポットライトの外側
    "    else attenuation *= pow(LS, gl_LightSource[0].spotExponent);",
    "",
    "", // 拡散反射率と鏡面反射率
    "    float diffuse  = max(dot(vNormal, nLight), 0.0);",
    "    float specular = pow(max(dot(vNormal, nHalf), 0.0), gl_FrontMaterial.shininess);",
    "", // 計算結果(フラグメントの色)
    "    gl_FragColor = color * gl_LightSource[0].diffuse  * diffuse",
    "                 +   gl_FrontLightProduct[0].specular * specular",
    "                 + color * gl_LightSource[0].ambient;",
    "    gl_FragColor = vec4((gl_FragColor * attenuation).xyz, color.w);" // 透過値は変更しない
    "}\n",
};

void newFailed() {
    message(_T("メモリの確保に失敗しました。"), _T("実行時エラー"));
    exit(1);
}

/**
 * @brief windows main function
 * @param  aInst     
 * @param  aPrevInst 
 * @param  aCmdLine   
 * @param  aCmdShow  
 * @return result of main function
 */
int WINAPI _tWinMain(
        HINSTANCE aInst,
        HINSTANCE aPrevInst,
        LPSTR aCmdLine,
        int aCmdShow
        ) {
    std::set_new_handler(newFailed);

    KWindow::MainArgs args{aInst, aPrevInst, aCmdLine, aCmdShow};

    KWindow window(&args, KWindow::SIZE, "PurPose");

    KOpenGL _(window);
    NoneShading = new KShader(
            sizeof SHADER_VERTEX / sizeof SHADER_VERTEX[0],
            SHADER_VERTEX,
            sizeof SHADER_FRAGMENT_NONE / sizeof SHADER_FRAGMENT_NONE[0],
            SHADER_FRAGMENT_NONE
            );
    NoneShading->ON();
    glUniform1i(glGetUniformLocation(NoneShading->program(), "texture"), 0);
    PhongShading = new KShader(
            sizeof SHADER_VERTEX / sizeof SHADER_VERTEX[0],
            SHADER_VERTEX,
            sizeof SHADER_FRAGMENT_PHONG / sizeof SHADER_FRAGMENT_PHONG[0],
            SHADER_FRAGMENT_PHONG
            );
    PhongShading->ON();
    glUniform1i(glGetUniformLocation(PhongShading->program(), "texture"), 0);
    CthulhuXShading = new KShader(
            sizeof SHADER_VERTEX / sizeof SHADER_VERTEX[0],
            SHADER_VERTEX,
            sizeof SHADER_FRAGMENT_CTHULHUX / sizeof SHADER_FRAGMENT_CTHULHUX[0],
            SHADER_FRAGMENT_CTHULHUX
            );
    CthulhuYShading = new KShader(
            sizeof SHADER_VERTEX / sizeof SHADER_VERTEX[0],
            SHADER_VERTEX,
            sizeof SHADER_FRAGMENT_CTHULHUY / sizeof SHADER_FRAGMENT_CTHULHUY[0],
            SHADER_FRAGMENT_CTHULHUY
            );
    CthulhuZShading = new KShader(
            sizeof SHADER_VERTEX / sizeof SHADER_VERTEX[0],
            SHADER_VERTEX,
            sizeof SHADER_FRAGMENT_CTHULHUZ / sizeof SHADER_FRAGMENT_CTHULHUZ[0],
            SHADER_FRAGMENT_CTHULHUZ
            );
    PhongShading->ON(); // デフォルトシェーダ

    PurPose game(window);
    window.setListener(&game);
    try {
        window.show();
    } catch (Error& e) {
        message(e.what(), "初期化エラー");
        return 0;
    }
    game.start(FPS);

    delete NoneShading;
    delete PhongShading;
    delete CthulhuXShading;
    delete CthulhuYShading;
    delete CthulhuZShading;

    return 0;
}
