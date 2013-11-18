/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <GLES/gl.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "chk"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Vertex3D;
typedef struct {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} Color3D;



static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}
static const GLfloat light0Position[] = {0.0, 0.0, 2.0, 0.0};
static const GLfloat light0Ambient[] = {0.4, 0.4, 0.4, 1.0};
static const GLfloat light0Diffuse[] = {0.7, 0.7, 0.7, 1.0};
static const GLfloat light0Specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat scale = 1.0f;

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}
GLuint texture[1];
bool setupGraphics(JNIEnv * env, int w, int h, jobject bitmap) {
//    printGLString("Version", GL_VERSION);
//    printGLString("Vendor", GL_VENDOR);
//    printGLString("Renderer", GL_RENDERER);
//    printGLString("Extensions", GL_EXTENSIONS);
//    glEnable(GL_COLOR_MATERIAL);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
//
//    LOGI("setupGraphics(%d, %d)", w, h);
//    gProgram = createProgram(gVertexShader, gFragmentShader);
//    if (!gProgram) {
//        LOGE("Could not create program.");
//        return false;
//    }
//    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
//    checkGlError("glGetAttribLocation");
//    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
//            gvPositionHandle);
//
//	glOrthof(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//    glViewport(0, 0, w, h);
    //scale = (GLfloat)w/(GLfloat)h;
    //    checkGlError("glViewport");

    GLuint textureWidth = 0;
    GLuint textureHeight = 0;
    GLvoid* pixel_source = NULL;

	AndroidBitmapInfo *info = (AndroidBitmapInfo *) malloc(sizeof(AndroidBitmapInfo));
	AndroidBitmap_getInfo(env, bitmap, info);
    if (info != NULL) {
    	textureWidth = info->width;
    	textureHeight = info->height;
    	if(info->format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
    		LOGI("Bitmap format is RGBA_8888!");
    	}
    	free(info);
    }
    LOGI("GL width = %d", textureWidth);
    LOGI("GL height = %d", textureHeight);

	AndroidBitmap_lockPixels(env, bitmap, &pixel_source);
	if (pixel_source != NULL) {
	    LOGI("not NULL");
	}

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_COLOR, GL_ZERO);
    glBlendFunc(GL_ONE, GL_SRC_COLOR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    glGenTextures(1, &texture[0]);
    checkGlError("glGenTextures");
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    checkGlError("glBindTexture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_source);
    checkGlError("glTexImage2D");
//    free(pixel_source);
//    AndroidBitmap_unlockPixels(env, bitmap);

//    LOGI("GL w = %d", w);
//    LOGI("GL h = %d", h);
//    LOGI("GL scale = %f", scale);
    return true;
}
static GLfloat rotation = 0.0;
static inline void makeVertex(Vertex3D *vertex, GLfloat x, GLfloat y, GLfloat z) {
	vertex->x = x;
	vertex->y = y;
	vertex->z = z;
}

static inline void makeColor(Color3D *color, GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

//static const Vertex3D vertices[] = {
//		{-0.2, 0.2, 0.2},
//		{-0.2, -0.2, 0.2},
//		{0.2, 0.2, 0.2},
//		{0.2, -0.2, 0.2},
//		{-0.2, 0.2, -0.2},
//		{-0.2, -0.2, -0.2},
//		{0.2, 0.2, -0.2},
//		{0.2, -0.2, -0.2}};
static const Vertex3D vertices_4[] = {
		{-0.5, 0.5, 0.0},
		{-0.5, -0.5, 0.0},
		{0.5, 0.5, 0.0},
		{0.5, -0.5, 0.0},
};
static const GLubyte icosahedronFaces_4[] = {
		0, 1, 2,
		2, 1, 3,
};

static const GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
    };
static const Color3D colors_4[] = {
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },};
static const Vertex3D vertices[] = {
		{-0.2, 0.2*scale, 0.2*scale},
		{-0.2, -0.2*scale, 0.2*scale},
		{0.2, 0.2*scale, 0.2*scale},
		{0.2, -0.2*scale, 0.2*scale},
		{-0.2, 0.2*scale, -0.2*scale},
		{-0.2, -0.2*scale, -0.2*scale},
		{0.2, 0.2*scale, -0.2*scale},
		{0.2, -0.2*scale, -0.2*scale}};
static const Color3D colors[] = {
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },
		{ 1.0, 0.0, 1.0, 1.0 },
		{ 0.0, 1.0, 1.0, 1.0 },
		{ 0.0, 0.0, 0.0, 1.0 },
		{ 1, 1, 1, 1.0 }};

static const GLubyte icosahedronFaces[] = {
		0, 1, 2,
		2, 1, 3,
		4, 5, 6,
		6, 5, 7,

		4, 0, 6,
		6, 0, 2,
		5, 1, 7,
		7, 1, 3,

		2, 3, 6,
		6, 3, 7,
		4, 5, 0,
		0, 5, 1};

static const Vertex3D normals[] = {
 {0.000000, -0.417775, 0.675974},
 {0.675973, 0.000000, 0.417775},
 {0.675973, -0.000000, -0.417775},
 {-0.675973, 0.000000, -0.417775},
 {-0.675973, -0.000000, 0.417775},
 {-0.417775, 0.675974, 0.000000},
 {0.417775, 0.675973, -0.000000},
 {0.417775, -0.675974, 0.000000},
};

void renderFrame() {

//	Vertex3D *vertices = (Vertex3D *) malloc(sizeof(Vertex3D) * 6);
//	makeVertex(&vertices[0], -0.5, 0.5, 0.0);
//	makeVertex(&vertices[1], -0.5, -0.5, 0.0);
//	makeVertex(&vertices[2], 0.5, 0.5, 0.0);
//	makeVertex(&vertices[3], 0.5, -0.5, 0.0);
//	makeVertex(&vertices[5], -0.5, -0.5, 0.0);

//	Color3D *colors = (Color3D *) malloc(sizeof(Color3D) * 4);
//	makeColor(&colors[0], 1.0, 0.0, 0.0, 0.0);
//	makeColor(&colors[1], 0.0, 1.0, 0.0, 0.0);
//	makeColor(&colors[2], 0.0, 0.0, 1.0, 0.0);
//	makeColor(&colors[3], 0.0, 0.0, 0.0, 0.0);

	glLoadIdentity();
	glClearColor(0.7, 0.7, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glOrthof(-100, 100, 100, -100, -1.0, 1.0);
	//glOrthof(-1.0, 1.0, -1.0, 1.0, 0.01, 1000.0);
	//glViewport(0, 0, 1280.0, 720.0);
//	glMatrixMode(GL_PROJECTION);
	//glFrustumf(-0.5, -0.5, 0.5, 0.5, 1.0, 1000);

	//glColor4f(1.0, 0.0, 0.0, 1.0);
	//glColorPointer(4, GL_FLOAT, 0, colors);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
	glVertexPointer(3, GL_FLOAT, 0, vertices_4);
	glColorPointer(4, GL_FLOAT, 0, colors_4);
	glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
//	GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);
//
//    GLfloat specular[] = {0.3, 0.3, 0.3, 1.0};
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0);

	glRotatef(rotation, 0.0, 1.0, 0.0);
	rotation += 1;
//    glNormalPointer(GL_FLOAT, 0, normals);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, icosahedronFaces);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, icosahedronFaces_4);
//	for (int i = 0; i < 10; i++) {
//		glLoadIdentity();
//	    glRotatef(rotation, 1.0, 1.0, 1.0);
//		glTranslatef(0.0, 0.0, -0.1 * (GLfloat)i);
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, icosahedronFaces);
//	}

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);



//	if (rotation >= 450.0) {
//		rotation = 90.0;
//	}
//	if (vertices != NULL) {
//		free(vertices);
//	}
//	if (colors != NULL) {
//		free(colors);
//	}
	/*
//    static float grey;
//    grey += 0.01f;
//    if (grey > 1.0f) {
//        grey = 0.0f;
//    }
//    glClearColor(grey, grey, grey, 1.0f);
//    checkGlError("glClearColor");
//    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//    checkGlError("glClear");
//
//    glUseProgram(gProgram);
//    checkGlError("glUseProgram");
//
//    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
//    checkGlError("glVertexAttribPointer");
//    glEnableVertexAttribArray(gvPositionHandle);
//    checkGlError("glEnableVertexAttribArray");
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    checkGlError("glDrawArrays");
 */
}
//
//
//static const char gVertexShader[] =
//    "attribute vec4 vPosition;\n"
//    "void main() {\n"
//    "  gl_Position = vPosition;\n"
//    "}\n";
//
//static const char gFragmentShader[] =
//    "precision mediump float;\n"
//    "void main() {\n"
//    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
//    "}\n";
//
//GLuint loadShader(GLenum shaderType, const char* pSource) {
//    GLuint shader = glCreateShader(shaderType);
//    if (shader) {
//        glShaderSource(shader, 1, &pSource, NULL);
//        glCompileShader(shader);
//        GLint compiled = 0;
//        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//        if (!compiled) {
//            GLint infoLen = 0;
//            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
//            if (infoLen) {
//                char* buf = (char*) malloc(infoLen);
//                if (buf) {
//                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
//                    LOGE("Could not compile shader %d:\n%s\n",
//                            shaderType, buf);
//                    free(buf);
//                }
//                glDeleteShader(shader);
//                shader = 0;
//            }
//        }
//    }
//    return shader;
//}
//
//GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
//    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
//    if (!vertexShader) {
//        return 0;
//    }
//
//    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
//    if (!pixelShader) {
//        return 0;
//    }
//
//    GLuint program = glCreateProgram();
//    if (program) {
//        glAttachShader(program, vertexShader);
//        checkGlError("glAttachShader");
//        glAttachShader(program, pixelShader);
//        checkGlError("glAttachShader");
//        glLinkProgram(program);
//        GLint linkStatus = GL_FALSE;
//        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
//        if (linkStatus != GL_TRUE) {
//            GLint bufLength = 0;
//            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
//            if (bufLength) {
//                char* buf = (char*) malloc(bufLength);
//                if (buf) {
//                    glGetProgramInfoLog(program, bufLength, NULL, buf);
//                    LOGE("Could not link program:\n%s\n", buf);
//                    free(buf);
//                }
//            }
//            glDeleteProgram(program);
//            program = 0;
//        }
//    }
//    return program;
//}
//
//GLuint gProgram;
//GLuint gvPositionHandle;
//
//
//const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f };
//


extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jobject bitmap);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height, jobject bitmap)
{
    setupGraphics(env, width, height, bitmap);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}