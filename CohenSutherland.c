#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>

#define outcode int
#define true 1
#define false 0

double xmin=50, ymin=50, xmax=100, ymax=100;
double xvmin=200, yvmin=200, xvmax=300, yvmax=300;

float x0[4],yo[4],x1[4],yl[4];
int n;
const int RIGHT=2;
const int LEFT=1;
const int TOP=8;
const int BOTTOM=4;

outcode computeoutcode(double x, double y);

void cohensutherland(double x0, double yo, double x1, double yl){
    outcode outcode0, outcode1, outcodeout;
    bool accept = false;
    bool done = false;

    outcode0 = computeoutcode(x0,yo);
    outcode1 = computeoutcode(x1,yl);

    do{
        if(!(outcode0 | outcode1)){
            accept = true;
            done = true;
        }
        else if(outcode0 & outcode1){
            done = true;
        }
        else{
            double x,y;
            outcodeout = outcode0?outcode0:outcode1;

            if(outcodeout & TOP){
                x = x0 + (x1-x0)*(ymax-yo)/(yl-yo);
                y = ymax;
            }
            else if(outcodeout & BOTTOM){
                x = x0 + (x1-x0)*(ymin-yo)/(yl-yo);
                y = ymin;
            }
            else if(outcodeout & RIGHT){
                y = yo + (yl-yo)*(xmax-x0)/(x1-x0);
                x = xmax;
            }
            else{
                y = yo + (yl-yo)*(xmin-x0)/(x1-x0);
                x = xmin;
            }

            if(outcodeout==outcode0){
                x0=x;
                yo=y;
                outcode0 = computeoutcode(x0,yo);
            }
            else{
                x1=x;
                yl=y;
                outcode1 = computeoutcode(x1,yl);
            }
        }
    }

    while(!done);

    if(accept){
        double sx = (xvmax-xvmin)/(xmax-xmin);
        double sy = (yvmax-yvmin)/(ymax-ymin);
        double vx0 = xvmin + (x0-xmin)*sx;
        double vy0 = yvmin + (yo-ymin)*sy;
        double vx1 = xvmin + (x1-xmin)*sx;
        double vy1 = yvmin + (yl-ymin)*sy;

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin, yvmin);
        glVertex2f(xvmax, yvmin);
        glVertex2f(xvmax, yvmax);
        glVertex2f(xvmin, yvmax);
        glEnd();

        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
    }
}

outcode computeoutcode(double x, double y){
    outcode code =0;
    if(y>ymax) code|=TOP;
    else if(y<ymin) code|=BOTTOM;
    else{
        if(x>xmax) code|=RIGHT;
        else if(x<xmin) code|=LEFT;
    }
    return code;
}

void display(){
    int j,k;
    glClear(GL_COLOR_BUFFER_BIT);
    for(k=0;k<n;k++){
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(x0[k], yo[k]);
        glVertex2d(x1[k], yl[k]);
        glEnd();
    }

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    for(j=0; j<n; j++){
        cohensutherland(x0[j], yo[j], x1[j], yl[j]);
	glFlush();
    }
}

void myinit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){
    printf("\nNumber of lines: ");
    scanf("%d",&n);
    printf("\nEnter x0,y0,x1,y1 for each: \n");

    for(int i=0; i<n; i++){
        scanf("%f%f%f%f",&x0[i],&yo[i],&x1[i],&yl[i]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen Sutherland clipping algorithm");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}
