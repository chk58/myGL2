
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


typedef GLfloat Matrix3D[16];

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

static inline void Matrix3DMultiply(Matrix3D m1, Matrix3D m2, Matrix3D result)
{
    result[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
    result[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
    result[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
    result[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

    result[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
    result[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
    result[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
    result[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

    result[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
    result[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
    result[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
    result[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

    result[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
    result[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
    result[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    result[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
}

static inline void Matrix3DSetTranslation(Matrix3D matrix, GLfloat xTranslate,
		GLfloat yTranslate, GLfloat zTranslate) {
	matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0;
	matrix[1] = matrix[2] = matrix[3] = matrix[4] = 0.0;
	matrix[6] = matrix[7] = matrix[8] = matrix[9] = 0.0;
	matrix[11] = 0.0;
	matrix[12] = xTranslate;
	matrix[13] = yTranslate;
	matrix[14] = zTranslate;
}
