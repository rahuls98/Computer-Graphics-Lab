#include <iostream>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416

GLsizei winWd = 600, winHt = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;
int choice = 0;

struct w{
    GLfloat x,y,z;
};

//calc nCr
void bino(GLint n, GLint *c){
    GLint k,j;
    for(k=0; k<=n; k++){
        c[k]=1;
        for(j=n; j>=k+1; j--) c[k] *= j;
        for(j=n-k; j>=2; j--) c[k] /= j;
    }
}

//to compute bezier points
void compute(GLfloat u, w *bezPt, GLint ncp, w *ctrl, GLint *c){
    GLint k, n=ncp-1;
    GLfloat bezBlend;

    bezPt->x = bezPt->y = bezPt->z = 0.0;

    for(k=0; k<ncp; k++){
        bezBlend = c[k] * pow(u,k) * pow(1-u, n-k);
        bezPt->x += ctrl[k].x * bezBlend;
        bezPt->y += ctrl[k].y * bezBlend;
        bezPt->z += ctrl[k].z * bezBlend;
    }
}

//to generate one bezier curve
void bezier(w *ctrl, GLint ncp, GLint nbcp){
    w bcp;
    GLfloat u;
    GLint *c, k;
    c = new GLint[ncp];

    bino(ncp-1, c);

    glBegin(GL_LINE_STRIP);
    for(k=0; k<nbcp; k++){
        u = GLfloat(k)/GLfloat(nbcp);
        compute(u, &bcp, ncp, ctrl, c);
        glVertex2f(bcp.x, bcp.y);
    }
    glEnd();
    delete[] c;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(choice==2||choice==3){
        GLint ncp=4, nbcp=20;
        static float theta = 0;
        w ctrl[4] = {{20,100,0}, {30,110,0}, {50,90,0}, {60,100,0}};
        ctrl[1].x += 10*sin(theta*PI/180.0);
        ctrl[1].y += 5*sin(theta*PI/180.0);
        ctrl[2].x -= 10*sin((theta+30)*PI/180.0);
        ctrl[2].y -= 10*sin((theta+30)*PI/180.0);
        ctrl[3].x -= 4*sin(theta*PI/180.0);
        ctrl[4].y += sin((theta-30)*PI/180.0);

        if(choice==3) theta+=1.0;

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 1.0, 1.0);
        glPointSize(5);

        glPushMatrix();
            glLineWidth(5);
            glColor3f(255/255, 153/255.0, 51/255.0);
            for(int i=0; i<8; i++){
                glTranslatef(0, -0.8, 0);
                bezier(ctrl, ncp, nbcp);
            }
            glColor3f(1.0, 1.0, 1.0);
            for(int i=0; i<8; i++){
                glTranslatef(0, -0.8, 0);
                bezier(ctrl, ncp, nbcp);
            }
            glColor3f(19/255.0, 136/255.0, 8/255.0);
            for(int i=0; i<8; i++){
                glTranslatef(0, -0.8, 0);
                bezier(ctrl, ncp, nbcp);
            }
        glPopMatrix();

        glColor3f(0.7, 0.5, 0.3);
        glLineWidth(5);
        glBegin(GL_LINES);
            glVertex2f(20,100);
            glVertex2f(20,40);
        glEnd();

        glFlush();
        glutPostRedisplay();
    }
    glutSwapBuffers();
}

void menu(int id){
    switch(id){
        case 1:exit(0);
                break;
        case 2:choice = 2;
                break;
        case 3:choice = 3;
                break;
    }
    glutPostRedisplay();
}

void reshape(GLint newWid, GLint newHt){
    glViewport(0, 0, newWid, newHt);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWd, winHt);
    glutCreateWindow("Bezier Curve");

    int sub_menu = glutCreateMenu(menu);
    glutAddMenuEntry("Draw Flag",2);
    glutAddMenuEntry("Start Animation",3);
    glutAddMenuEntry("Stop Animation", 2);

    glutCreateMenu(menu);
    glutAddMenuEntry("Exit",1);
    glutAddSubMenu("Flag",sub_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
}
