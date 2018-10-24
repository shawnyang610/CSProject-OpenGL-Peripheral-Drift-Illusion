//  CS718 Computer Graphics
//  project2_Peripheral_Drift_Illusion
//  Author: Shawn Yang
//  10/13/2018

#include <iostream>
#include <GLUT/glut.h>
#include <cmath>

static GLfloat SHIELD[4][3]={{-5,10,0},{5,10,0},{5,-10,0},{-5,-10,0}};
static GLfloat COLOR[3] ={0.15,0.39,0.77};
GLfloat frame[4][3];

void set_frame(){
  // calculates frame size using SHIELD size
  frame[0][0] = SHIELD[0][0]+(fabs(SHIELD[1][0]-SHIELD[0][0])/2.0);
  frame[0][1] = SHIELD[0][1]+2.0;
  frame[0][2] = SHIELD[0][2];
  frame[1][0] = SHIELD[1][0]+2.0;
  frame[1][1] = SHIELD[1][1]+2.0;
  frame[1][2] = SHIELD[1][2];
  frame[2][0] = SHIELD[2][0]+2.0;
  frame[2][1] = SHIELD[2][1]-2.0;
  frame[2][2] = SHIELD[2][2];
  frame[3][0] = SHIELD[3][0]+(fabs(SHIELD[2][0]-SHIELD[3][0])/2.0);
  frame[3][1] = SHIELD[3][1]-2.0;
  frame[3][2] = SHIELD[3][2];
}

void draw_shield(void){
  glColor3fv(COLOR);
  glBegin(GL_POLYGON);
    for (int i=0; i<4; i++)
      glVertex3fv(SHIELD[i]);
  glEnd();
}

void draw_frame(bool flipped_color){
  if (flipped_color)
    glColor3f(0,0, 0);
  else
    glColor3f(1,1,1);
  
  glBegin(GL_POLYGON);
  for (int i=0; i<4; i++)
    glVertex3fv(frame[i]);
  glEnd();
}

void draw_frame_and_shield(bool isFlipped){
  draw_shield();
  draw_frame(!isFlipped);
  glRotated(180, 0, 1, 0);
  draw_frame(isFlipped);
}

void draw_ring(bool isFlipped){
  for (int i=0; i<360; i+=45){
    glPushMatrix();
    glScaled(1.6, 1.6, 1);
    glRotated(i, 0, 0, 1);
    glTranslated(0, 35, 0);
    draw_frame_and_shield(isFlipped);
    glPopMatrix();
  }
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // calculates and set the size of frame for given shield size
  set_frame();
  // draw the shield ring for 8 times
  for (int i=0; i<8; i++){
    glPushMatrix();
    glTranslated(-300 + (i%4)*200, 100-(i/4)*200, 0);
    // if.. else sets opposite border pattern for up-down neighbors.
    if (i<4)
      draw_ring(i%2); // upper 4 rings
    else
      draw_ring((i+1)%2); //lower 4 rings
    glPopMatrix();
  }
  glFlush();
}

int main(int argc, char * argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(800, 400);
  glutInitWindowPosition(200, 100);
  glutCreateWindow("Shawn Yang's Proj.2");
  glClearColor(0.77, 0.76, 0.15, 0.1);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-400, 400, -200, 200, 0, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
