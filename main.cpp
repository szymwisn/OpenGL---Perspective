#include <iostream>
#include <GL/glut.h>
#include <cmath>

typedef float point3[3];
static GLfloat viewer[] = {0.0, 0.0, 10.0};
static GLfloat object[] = {0.0, 0.0, 0.0};
static GLfloat up[] = {0.0, 1.0, 0.0};

static GLfloat theta_x = 0.0;
static GLfloat theta_y = 0.0;

static GLfloat pix2angle;

static GLint status = 0;

static int x_pos_old = 0;
static int y_pos_old = 0;
static int z_pos_old = 0;

static int delta_x = 0;
static int delta_y = 0;
static int delta_z = 0;

static float theta = 0.0;
static float phi = 0.0;

static float R = 10.0;

void Axes(void)
{
    point3 x_min = { -5.0, 0.0, 0.0 };
    point3 x_max = { 5.0, 0.0, 0.0 };

    point3 y_min = {0.0, -5.0, 0.0};
    point3 y_max = {0.0, 5.0, 0.0};

    point3 z_min = {0.0, 0.0, -5.0};
    point3 z_max = {0.0, 0.0, 5.0};

    glColor3f(1.0f,0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3fv(x_min);
        glVertex3fv(x_max);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3fv(y_min);
        glVertex3fv(y_max);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3fv(z_min);
        glVertex3fv(z_max);
    glEnd();
}

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(viewer[0], viewer[1], viewer[2], object[0], object[1], object[2], up[0], up[1], up[2]);

    Axes();

    glColor3f(1.0f, 1.0f, 0.0f);

    if(status == 1) {
        // theta_x += delta_x * pix2angle;
        // theta_y += delta_y * pix2angle;

        theta += delta_x * pix2angle * 0.1;
        phi += delta_y * pix2angle * 0.1;
    } if(status == 2) {
        // viewer[2] += delta_y * pix2angle;

        // if(viewer[2] <= 6.0) {
        //     viewer[2] = 6.0;
        // } else if(viewer[2] >= 25.0) {
        //     viewer[2] = 25.0;
        // }

        R += delta_y * pix2angle;

        if(R <= 6.0) {
            R = 6.0;
        } else if(R >= 25.0) {
            R = 25.0;
        }
    }

    // glRotatef(theta_x, 0.0, 1.0, 0.0);
    // glRotatef(theta_y, 1.0, 0.0, 0.0);

    viewer[0] = R * cos(theta) * cos(phi);
    viewer[1] = R * sin(phi);
    viewer[2] = R * sin(theta) * cos(phi);

    glutWireTeapot(3.0);

    glFlush();

    glutSwapBuffers();
}

void MyInit(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x_pos_old = x;
        y_pos_old = y;
        status = 1;
    } else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        y_pos_old = y;
        status = 2;
    } else
        status = 0;
}

void Motion(GLsizei x, GLsizei y) {
    delta_x = x - x_pos_old;
    x_pos_old = x;

    delta_y = y - y_pos_old;
    y_pos_old = y;

    glutPostRedisplay();
}

void ChangeSize(GLsizei horizontal, GLsizei vertical) {
    pix2angle = 360.0/(float)horizontal;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(70, 1.0, 1.0, 30.0);

    if(horizontal <= vertical)
        glViewport(0, (vertical-horizontal)/2, horizontal, horizontal);
    else 
        glViewport((horizontal-vertical)/2, 0, vertical, vertical);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(800, 800);

    glutCreateWindow("Grafika Komputerowa - 241269");

    glutDisplayFunc(RenderScene);

    glutReshapeFunc(ChangeSize);

    glutMouseFunc(Mouse);

    glutMotionFunc(Motion);

    MyInit();

    glutMainLoop();

    return 0;
}
