#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>

typedef float point[3];

point v[] = {{0.0,0.0,1.0},
              {0.0, 0.942809, -0.3333},
              {-0.816497, -0.471405, -0.333333},
              {0.816497, -0.471405, -0.333333}};

static GLfloat theta[] = {0.0, 0.0, 0.0};
int n;

void triangle(point a, point b, point c){
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

void divide_triangle(point a, point b, point c, int m){
    point v1,v2,v3;
    int j;
    if(m>0){
        for(j=0;j<3;j++) v1[j] = (a[j]+b[j])/2;
        for(j=0;j<3;j++) v2[j] = (a[j]+c[j])/2;
        for(j=0;j<3;j++) v3[j] = (b[j]+c[j])/2;

        divide_triangle(a,v1,v2,m-1);
        divide_triangle(c,v2,v3,m-1);
        divide_triangle(b,v3,v1,m-1);
    }
    else (triangle(a,b,c));
}

void tetrahedron(int m){
    glColor3f(1.0, 0.0, 0.0);
    divide_triangle(v[0],v[1],v[2],m);
    glColor3f(0.0, 1.0, 0.0);
    divide_triangle(v[3],v[2],v[1],m);
    glColor3f(0.0, 0.0, 1.0);
    divide_triangle(v[0],v[3],v[1],m);
    glColor3f(0.0, 0.0, 0.0);
    divide_triangle(v[0],v[2],v[3],m);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tetrahedron(n);
    glFlush();
}

void myinit(){
    glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv){
    printf("Number of divisions: ");
    scanf("%d",&n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Gasket");
    glutDisplayFunc(display);
    myinit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
