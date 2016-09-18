xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 56;
 -0.73460;0.78463;-1.02509;,
 -0.10889;0.83274;-1.29735;,
 -0.18927;0.27501;-1.33600;,
 -0.82655;0.26397;-1.09241;,
 0.59295;0.75839;-1.36461;,
 0.56226;0.22096;-1.39630;,
 1.20168;0.54194;-1.19959;,
 1.19075;0.09682;-1.26270;,
 -0.20282;-0.35965;-1.18595;,
 -0.77934;-0.22742;-0.99421;,
 0.47891;-0.39413;-1.24328;,
 1.05683;-0.35658;-1.17339;,
 -0.13991;-0.86371;-0.94718;,
 -0.62408;-0.73613;-0.77630;,
 0.36036;-0.87572;-1.01979;,
 0.91804;-0.75066;-0.97401;,
 1.50144;0.72530;-0.55472;,
 1.46442;0.18294;-0.57133;,
 1.54870;0.75774;0.22390;,
 1.53129;0.20056;0.28930;,
 1.34186;0.63433;0.92576;,
 1.36554;0.14738;1.02846;,
 1.26342;-0.44623;-0.50888;,
 1.33212;-0.44716;0.29375;,
 0.97336;-0.25875;0.96128;,
 0.94821;-0.89019;-0.40657;,
 0.87227;-0.85831;0.23177;,
 0.70742;-0.66325;0.82875;,
 0.64665;0.96471;1.18175;,
 0.60203;0.32793;1.28063;,
 -0.20416;1.03995;1.22299;,
 -0.36504;0.40133;1.34569;,
 -0.84688;1.15178;1.08827;,
 -1.17789;0.34197;1.17622;,
 0.48046;-0.45282;1.20516;,
 -0.43885;-0.46174;1.29573;,
 -1.20017;-0.37217;1.17765;,
 0.33258;-1.04585;1.03420;,
 -0.37223;-1.12996;1.09684;,
 -0.99246;-0.76973;0.95244;,
 -1.01208;1.41836;0.34974;,
 -1.18190;0.74225;0.44877;,
 -1.00546;1.27811;-0.41916;,
 -1.12452;0.59490;-0.42348;,
 -1.17833;-0.19924;0.47014;,
 -1.05398;-0.24385;-0.34425;,
 -1.02328;-0.95904;0.37818;,
 -0.88445;-0.90802;-0.23460;,
 -0.14193;1.43382;0.43023;,
 0.87770;1.12268;0.39811;,
 -0.11278;1.21007;-0.53614;,
 1.00177;0.95882;-0.55215;,
 -0.33031;-1.04580;-0.33212;,
 0.34786;-1.03952;-0.39198;,
 -0.45756;-1.10981;0.41107;,
 0.23467;-1.05334;0.34665;;
 
 54;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;2,5,10,8;,
 4;5,7,11,10;,
 4;9,8,12,13;,
 4;8,10,14,12;,
 4;10,11,15,14;,
 4;6,16,17,7;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;7,17,22,11;,
 4;17,19,23,22;,
 4;19,21,24,23;,
 4;11,22,25,15;,
 4;22,23,26,25;,
 4;23,24,27,26;,
 4;20,28,29,21;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;21,29,34,24;,
 4;29,31,35,34;,
 4;31,33,36,35;,
 4;24,34,37,27;,
 4;34,35,38,37;,
 4;35,36,39,38;,
 4;32,40,41,33;,
 4;40,42,43,41;,
 4;42,0,3,43;,
 4;33,41,44,36;,
 4;41,43,45,44;,
 4;43,3,9,45;,
 4;36,44,46,39;,
 4;44,45,47,46;,
 4;45,9,13,47;,
 4;32,30,48,40;,
 4;30,28,49,48;,
 4;28,20,18,49;,
 4;40,48,50,42;,
 4;48,49,51,50;,
 4;49,18,16,51;,
 4;42,50,1,0;,
 4;50,51,4,1;,
 4;51,16,6,4;,
 4;13,12,52,47;,
 4;12,14,53,52;,
 4;14,15,25,53;,
 4;47,52,54,46;,
 4;52,53,55,54;,
 4;53,25,26,55;,
 4;46,54,38,39;,
 4;54,55,37,38;,
 4;55,26,27,37;;
 
 MeshMaterialList {
  1;
  54;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Data/Mesh/asteroid.png";
   }
  }
 }
 MeshNormals {
  65;
  -0.517225;0.438447;-0.735012;,
  -0.135945;0.563993;-0.814513;,
  0.087210;0.079994;-0.992973;,
  0.620554;0.356441;-0.698471;,
  -0.679757;-0.004634;-0.733423;,
  -0.231306;-0.055609;-0.971290;,
  0.057183;-0.080893;-0.995081;,
  0.637192;-0.141406;-0.757622;,
  -0.667808;-0.308615;-0.677339;,
  -0.240538;-0.331545;-0.912261;,
  0.022210;-0.344978;-0.938348;,
  0.572764;-0.447174;-0.687006;,
  -0.552764;-0.595986;-0.582455;,
  -0.234562;-0.729717;-0.642257;,
  0.063068;-0.772229;-0.632207;,
  0.449525;-0.729708;-0.515222;,
  0.972148;-0.031997;-0.232172;,
  0.857256;0.500465;0.121025;,
  0.717788;0.396580;0.572280;,
  0.960366;-0.175158;-0.216834;,
  0.970428;-0.207601;0.123171;,
  0.708155;-0.153256;0.689224;,
  0.869048;-0.468196;-0.159836;,
  0.809365;-0.552832;0.198256;,
  0.624044;-0.486319;0.611607;,
  0.546533;-0.829800;-0.112848;,
  0.559299;-0.810145;0.175642;,
  0.609441;-0.669250;0.425072;,
  0.329726;0.587809;0.738757;,
  0.024212;0.629676;0.776480;,
  -0.102477;0.634286;0.766277;,
  0.225391;-0.006887;0.974244;,
  -0.054945;0.067450;0.996209;,
  -0.183656;0.096690;0.978224;,
  0.304573;-0.285867;0.908579;,
  -0.071974;-0.211497;0.974725;,
  -0.238647;-0.231046;0.943221;,
  0.474558;-0.592232;0.651196;,
  -0.143758;-0.791531;0.593980;,
  -0.373442;-0.733812;0.567505;,
  -0.957246;0.272793;0.096252;,
  -0.936275;0.197872;-0.290235;,
  -0.991627;0.127726;0.019008;,
  -0.961885;0.050656;-0.268722;,
  -0.986826;-0.143062;-0.075544;,
  -0.941502;-0.192852;-0.276375;,
  -0.729933;-0.682420;-0.038754;,
  -0.667097;-0.673574;-0.318243;,
  0.124019;0.987073;0.101522;,
  0.361192;0.926310;0.107188;,
  0.065765;0.940248;-0.334080;,
  0.307980;0.913076;-0.267285;,
  -0.146369;-0.965867;-0.213720;,
  0.127923;-0.983372;-0.128903;,
  -0.130449;-0.991442;-0.005057;,
  0.241544;-0.969783;0.034300;,
  -0.906070;0.332426;0.261785;,
  -0.975690;0.177198;0.128953;,
  -0.988531;-0.150897;-0.006084;,
  -0.950277;-0.311400;-0.002117;,
  0.014804;0.994498;0.103703;,
  -0.060924;0.923170;-0.379532;,
  0.422518;0.871989;-0.247212;,
  0.263155;0.876732;-0.402604;,
  0.097842;-0.994948;-0.022464;;
  54;
  4;0,1,5,4;,
  4;1,2,6,5;,
  4;2,3,7,6;,
  4;4,5,9,8;,
  4;5,6,10,9;,
  4;6,7,11,10;,
  4;8,9,13,12;,
  4;9,10,14,13;,
  4;10,11,15,14;,
  4;3,16,19,7;,
  4;16,17,20,19;,
  4;17,18,21,20;,
  4;7,19,22,11;,
  4;19,20,23,22;,
  4;20,21,24,23;,
  4;11,22,25,15;,
  4;22,23,26,25;,
  4;23,24,27,26;,
  4;18,28,31,21;,
  4;28,29,32,31;,
  4;29,30,33,32;,
  4;21,31,34,24;,
  4;31,32,35,34;,
  4;32,33,36,35;,
  4;24,34,37,27;,
  4;34,35,38,37;,
  4;35,36,39,38;,
  4;56,40,42,57;,
  4;40,41,43,42;,
  4;41,0,4,43;,
  4;57,42,44,58;,
  4;42,43,45,44;,
  4;43,4,8,45;,
  4;58,44,46,59;,
  4;44,45,47,46;,
  4;45,8,12,47;,
  4;30,29,48,60;,
  4;29,28,49,48;,
  4;28,18,17,49;,
  4;60,48,50,61;,
  4;48,49,51,50;,
  4;49,17,62,51;,
  4;61,50,1,0;,
  4;50,51,63,1;,
  4;51,62,3,63;,
  4;12,13,52,47;,
  4;13,14,53,52;,
  4;14,15,25,53;,
  4;47,52,54,46;,
  4;52,53,55,54;,
  4;53,25,26,55;,
  4;46,54,38,39;,
  4;54,55,64,38;,
  4;55,26,27,37;;
 }
 MeshTextureCoords {
  56;
  -0.156180;0.084940;,
  0.353880;0.045720;,
  0.288360;0.500360;,
  -0.231130;0.509360;,
  1.089090;0.191420;,
  0.900980;0.544420;,
  1.422210;0.282770;,
  1.413300;0.645610;,
  0.277320;1.017710;,
  -0.192640;0.909920;,
  0.833040;1.045820;,
  1.304140;1.015210;,
  0.328590;1.428600;,
  -0.066080;1.324600;,
  0.736400;1.438390;,
  1.191000;1.336450;,
  1.666560;0.133300;,
  1.749850;0.412320;,
  1.910730;-0.588080;,
  1.896540;0.518500;,
  1.536480;0.207460;,
  1.555790;0.604400;,
  1.862560;1.492490;,
  2.010740;1.365600;,
  1.236090;0.935460;,
  1.711970;1.882750;,
  1.153690;1.424200;,
  1.019310;1.265200;,
  0.969770;-0.061850;,
  0.933400;0.457220;,
  0.276230;-0.123190;,
  0.145080;0.397390;,
  -0.176780;-0.625640;,
  -0.517520;0.445770;,
  0.834300;1.093660;,
  0.084910;1.100930;,
  -0.890250;1.893040;,
  0.763390;1.860720;,
  0.217220;1.844200;,
  -0.302550;1.890920;,
  -0.914200;-0.920950;,
  -0.889530;0.183310;,
  -0.376970;-0.317330;,
  -0.729310;0.069410;,
  -0.872440;0.879860;,
  -0.416520;0.923320;,
  -0.391490;1.506320;,
  -0.278320;1.464720;,
  0.553860;-0.883910;,
  1.633230;-0.864290;,
  0.762000;-0.609330;,
  1.259250;-0.057060;,
  0.173390;1.577040;,
  1.016950;1.876840;,
  0.069660;1.629210;,
  0.633940;1.583190;;
 }
 MeshVertexColors {
  56;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;;
 }
}