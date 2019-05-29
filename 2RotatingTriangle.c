#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat triangle[3][3] = {{100.0,175.0,250.0},{100.0,250.0,100.0},{1.0,1.0,1.0}};
GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat res[3][3] = {{0},{0},{0}};
GLfloat h=100.0;
GLfloat k=100.0;
GLfloat theta;
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}

void multiply()
{
    int i,j,l;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            res[i][j]=0;
            for(l=0;l<3;l++)
            {
                res[i][j]=res[i][j]+rot_mat[i][l]*triangle[l][j];
            }
        }
    }
}
void rotated()
{
    GLfloat m,n;
    m=h*(1-cos(theta))+k*sin(theta);
    n=k*(1-cos(theta))-h*sin(theta);
    rot_mat[0][0]=cos(theta);
    rot_mat[0][1]=-sin(theta);
    rot_mat[0][2]=m;
    rot_mat[1][0]=sin(theta);
    rot_mat[1][1]=cos(theta);
    rot_mat[1][2]=n;
    rot_mat[2][0]=0;
    rot_mat[2][1]=0;
    rot_mat[2][2]=1;
    multiply();
}
void drawTriangle()
{
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(triangle[0][0],triangle[1][0]);
    glVertex2f(triangle[0][1],triangle[1][1]);
    glVertex2f(triangle[0][2],triangle[1][2]);
    glEnd();
}
void drawRotatedTriangle()
{
    glColor3f(0,0,1);
    //glColor3f(0.5,0.0,1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(res[0][0],res[1][0]);
    glVertex2f(res[0][1],res[1][1]);
    glVertex2f(res[0][2],res[1][2]);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle();
    rotated();
    drawRotatedTriangle();
    glFlush();
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    printf("Enter h,k and theta: ");
    scanf("%f%f%f",&h,&k,&theta);
    theta=(theta*3.14)/180;
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Rotated Triangle ");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}

