
#include "utils.c"

static const Vertex3D vertices[] = {
		{-0.5, 0.5, 0.0},
		{-0.5, -0.5, 0.0},
		{0.5, 0.5, 0.0},
		{0.5, -0.5, 0.0},
};
static const GLubyte icosahedronFaces[] = {
		0, 1, 2,
		2, 1, 3,
};
static const Vertex3D normals[] = {
 {0.000000, -0.417775, 0.675974},
 {0.675973, 0.000000, 0.417775},
 {0.675973, -0.000000, -0.417775},
 {-0.675973, 0.000000, -0.417775},
};
static const GLfloat texCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
    };
static const Color3D colors[] = {
		{ 1.0, 0.0, 0.0, 1.0 },
		{ 0.0, 1.0, 0.0, 1.0 },
		{ 0.0, 0.0, 1.0, 1.0 },
		{ 1.0, 1.0, 0.0, 1.0 },};
