#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

int a=0,aa=0,b=0,bb=0,fw=0;//fish movement
float x0=100,y2=0,r=0.5,y11=0,y21=0,y31=0,y41=0,y51=0,y61=0,y71=0,y81=0,y91=0,y10=0,y12=0,y13=0,y14=0, angle=0.0, pi=3.142;
float radius,twicePi;
int triangleAmount =40;
bool man_mov=true;
bool throw_down=false;
GLfloat menPosition2=0;
int y_mov=0,screen_off=0,next=0,next1=0,next2=0;;
bool break_down=false;
bool into_two=false;
bool into_four=false;
int y_mov_1=0,lag=0;






void drawCloud(int x0, int y2){
    int radius = 20;

    // Draw the main circle for the cloud
    glColor3f(1.0, 1.0, 1.0);  // White color for the cloud
    glBegin(GL_TRIANGLE_FAN);
    for (float angle = 0; angle < 360.0; angle += 5) {
        float cloudX = x0 + radius * cos(angle * (pi / 180));
        float cloudY = y2 + radius * sin(angle * (pi / 180));
        glVertex2f(cloudX, cloudY);
    }
    glEnd();

    // Draw smaller circles to give a cloud-like appearance
    for (int j = 0; j < 3; j++) {
        int offsetX = rand() % (2 * radius) - radius;  // Random offset within the main circle
        int offsetY = rand() % (2 * radius) - radius;
        glBegin(GL_TRIANGLE_FAN);
        for (float angle = 0; angle < 360.0; angle += 5) {
            float cloudX = x0 + offsetX + radius * cos(angle * (pi / 180));
            float cloudY = y2 + offsetY + radius * sin(angle * (pi / 180));
            glVertex2f(cloudX, cloudY);
        }
        glEnd();
    }
}
void init()
{
	glClearColor(0.0,0.6,0.9,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(h>w)
		gluOrtho2D(0, 500, ((float)h/(float)w)*(0), ((float)h/(float)w)*500);
	else
        gluOrtho2D(((float)w/(float)h)*(0), ((float)w/(float)h)*(520), 0, 500);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}




void circleFunc(float yc,int d,int x1,int y1){
    for(angle=0; angle<360.0; angle+=.1)
	{
        y2 =yc+(sin(angle*pi/180)*d);
        x0 =(cos(angle*pi/180)*d);
        glVertex2f(x0+x1,y2-y1);
	}
}

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int j = 0; j <= 360; j++)
    {
        float angle = j * 3.1416 / 180;
        float x0 = rx * cos(angle);
        float y2 = ry * sin(angle);
        glVertex2f((x0 + cx), (y2 + cy));
    }
    glEnd();
}


float bx = 10;
void clouds()
{
    glPushMatrix();
    glTranslatef(bx, 0, 0);
    // 1st cloud
    glColor3ub(255, 255, 255);

    circle(50, 30, 360, 400);

    circle(55, 20, 345, 400);

    circle(55, 20, 375, 400);

    // 2nd cloud

    circle(50, 30, 310, 320);

    circle(55, 20, 295, 320);

    circle(55, 20, 365, 320);

    glPopMatrix();
     bx +=.5;
    if (bx >600)
        bx = -1200;
    glutPostRedisplay();

}
void sky(){
        // Draw sky
    glColor3f(0.5, 0.8, 1.0);  // Light blue color for the sky
    glBegin(GL_POLYGON);
    glVertex2f(0, 500);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 500);
    glEnd();
}
void sun(){
     // Sun design
    glColor3ub(255, 215, 0);
    circle(35, 45, 100, 400);
}
void river(){
 // River Color
    glColor3ub(0, 191, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(1200, 0);
    glVertex2d(1200, 200);
    glVertex2d(0, 200);
    glEnd();
}
void side(){
    glColor3f(0.0, 0.5, 0.0); // Set color to deep green
   // circle(0, 0, 400, 200);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0); // Center point
    for (int angle = 0; angle <= 180; angle++) {
        float x0 = 400 * cos(angle * 3.14159 / 180);
        float y2 = 200 * sin(angle * 3.14159 / 180);
        glVertex2f(x0, y2);
    }
    glEnd();
}

void wooden(){
    // Draw the stand
    glColor3f(0.65, 0.5, 0.39); // Set color to wooden brown
    glBegin(GL_POLYGON);

    glVertex2d(250, 20);
    glVertex2d(550, 20); // Lower right corner
    glVertex2d(450, 120); // Upper right corner
    glVertex2d(150, 120);

    glVertex2d(250, 20); // Lower left corner
    glVertex2d(550, 20); // Lower right corner
    glVertex2d(450, 120); // Upper right corner
    glVertex2d(150, 120); // Upper left corner
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(530,20);
    glVertex2d(510,20);
    glVertex2d(510,0);
    glVertex2d(530,0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(270,20);
    glVertex2d(290,20);
    glVertex2d(290,0);
    glVertex2d(270,0);
    glEnd();
}


int x_mov=0;
void man(){

     glPushMatrix();
     glLoadIdentity();
     if(man_mov){
        x_mov+=1;
     }


    glTranslated(x_mov,0, 0.0);
	//Man 1 Draw
	//Left Leg
	glBegin(GL_QUADS);
	glColor3ub(44, 80, 197);
	glVertex2d(300,50);
	glVertex2d(325,50);
	glVertex2d(315,100);
	glVertex2d(310,100);

	//Right leg
    glVertex2d(330,50);
	glVertex2d(355,50);
	glVertex2d(345,100);
	glVertex2d(340,100);
	glEnd();

	//Body
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0 );
	glVertex2d(300,90);
	glVertex2d(350,90);
	glVertex2d(350,140);
	glVertex2d(300,140);
	glEnd();

	//Left hand
	glBegin(GL_POLYGON);
	glColor3ub(44, 80, 197);
	glVertex2d(330,120);
	glVertex2d(320,120);
	glVertex2d(320,100);
	glVertex2d(380,100);
    glVertex2d(380,105);
	glVertex2d(330,105);
	glEnd();


	//Shoe
	glBegin(GL_TRIANGLES);
	glColor3ub(0,0,0);
	glVertex2d(300,50);
	glVertex2d(325,50);
	glVertex2d(315,60);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(0,0,0);
	glVertex2d(330,50);
	glVertex2d(355,50);
	glVertex2d(345,60);
	glEnd();

    //neck
    glLineWidth(6);
	glBegin(GL_LINES);
	glColor3ub(249, 231, 159);
	glVertex2i(325, 140);
	glVertex2i(325,150);

	glEnd();
    //head
	 glBegin(GL_TRIANGLE_FAN);
    glColor3ub(250, 222, 157 );
    x0=325; y2=165; radius =20;

    twicePi = 2.0f * pi;


    glVertex2f(x0, y2); // center of circle
    for(int j = 0; j <= triangleAmount;j++) {
    glVertex2f(
    x0 + (radius * cos(j *  twicePi / triangleAmount)),
    y2 + (radius * sin(j * twicePi / triangleAmount))
        );
        }
    glEnd();
//hair
	 glBegin(GL_TRIANGLE_FAN);
    glColor3ub(0,0,0 );
    x0=325; y2=165; radius =20;

   // twicePi = 2.0f * pi;


    glVertex2f(x0, y2); // center of circle
    for(int j = 0; j <= triangleAmount;j++) {
    glVertex2f(
    x0 + (radius * cos(j *  pi / triangleAmount)),
    y2 + (radius * sin(j * pi / triangleAmount))
        );
        }
    glEnd();

glPopMatrix();

}
bool bottle_floating=false;
float b_angle=12;
int x_mov_float=180;
int y_mov_float=0;

void plastic_bottle(){
     glPushMatrix();
     glLoadIdentity();

    if(throw_down){
    if(y_mov>=-20){
    glTranslatef(x_mov_float+25,0, 0.0);
    glRotatef(b_angle,0,0,-1);
    b_angle+=0.01;
    y_mov_float=y_mov;
    y_mov-=1;
    }
    else{
    glTranslatef(x_mov_float,y_mov_float, 0.0);
    glRotatef(b_angle,0,0,-1);
    b_angle+=0.01;
    x_mov_float+=1;
    }

    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.5); //light blue
	glVertex2d(365,140);
	glVertex2d(360,140);
	glVertex2d(360,130);
    glVertex2d(355,130);
    glVertex2d(355,95);
	glVertex2d(370,95);
	glVertex2d(370,130);
	glVertex2d(365,130);
	glVertex2d(365,135);
	glEnd();
	//cap
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2d(368,140);
	glVertex2d(360,140);
	glVertex2d(360,135);
	glVertex2d(368,135);
	glEnd();


    }
    else glTranslated(x_mov, 0, 0.0);

    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.5); //light blue
	glVertex2d(365,140);
	glVertex2d(360,140);
	glVertex2d(360,130);
	glVertex2d(355,130);
    glVertex2d(355,95);
	glVertex2d(370,95);
	glVertex2d(370,130);
	glVertex2d(365,130);
	glVertex2d(365,135);
	glEnd();
	//cap
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2d(368,140);
	glVertex2d(360,140);
	glVertex2d(360,135);
	glVertex2d(368,135);
	glEnd();



    if(x_mov>=170){
        man_mov=false;
        throw_down=true;
    }
    glPopMatrix();
    glutPostRedisplay();



}
void drawstring(float x0,float y2,float z,char *string, int f)
{
    char *c;
    glRasterPos3f(x0,y2,z);
    for(c=string;*c!='\0';c++){
        if(f==0)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);
        else
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
    }
}
void screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0,1.0,1.0);
	drawstring(210,425,0.0,"American International University Bangladesh",1);
		glColor3f(1.0,1.0,1.0);
	drawstring(210,385,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING",1);
		glColor3f(1.0,1.0,1.0);
	drawstring(210,350,0.0,"A PROJECT ON DISSEMINATION OF MICROPLASTIC IN HUMAN FOOD",1);
	 	glColor3f(1.0,1.0,1.0);
	  drawstring(135,205,0.0," STUDENT NAME",0);
	  	glColor3f(0.0,0.0,0.0);
	drawstring(140,170,0.0,"JARIATUN ISLAM",0);
	drawstring(140,150,0.0,"SHUVA SAHA ",0);
	drawstring(140,130,0.0,"SHAORIN SHAMIMA ",0);
	drawstring(140,110,0.0,"FARHINA PARVIN SWARNA ",0);
	drawstring(140,90,0.0,"TOUHIDUL ISLAM SAAD",0);
		glColor3f(1.0,1.0,1.0);
	drawstring(710,205,0.0,"Under the Guidance of",0);
		glColor3f(0.0,0.0,0.0);
	drawstring(720,170,0.0," MAHFUZUR RAHMAN",0);
    glColor3f(1.0,1.0,1.0);
	drawstring(406,95,0.0,"Academic Year 2023-24",0);
    glColor3f(1.0,1.0,1.0);
	drawstring(406,70,0.0,"Press 's' to start",0);

glFlush();
 glutSwapBuffers();
}
void fish1()
{

     glPushMatrix();
    glTranslatef(a, aa, 0);
    //body
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(270,350);
    glVertex2f(300,325);
    glVertex2f(370,350);
    glVertex2f(300,375);
  glEnd();



 glBegin(GL_POLYGON);

    glVertex2f(360,350);
    glColor3ub(1.0,0.0,0.0);
    glVertex2f(405,370);
    glVertex2f(395,350);
    glVertex2f(405,327);
  glEnd();

  glBegin(GL_TRIANGLES);

   glColor3ub(1.0,0.0,0.0);
  glVertex2f(302,373);
   glColor3f(1.0,0.0,0.0);
	glVertex2f(340,409);
	glVertex2f(320,360);
  glEnd();

glBegin(GL_TRIANGLES);

 glColor3ub(1.0,0.0,0.0);
    glVertex2f(302,328);
glColor3f(1.0,0.0,0.0);
	glVertex2f(340,300);
	glVertex2f(320,340);
  glEnd();


 glColor3f(0.0,0.0,0.0);
  glPointSize(4.0);
  glBegin(GL_POINTS);
  glVertex2f(280,355);
  glEnd();

    if(a>=-500)
        a=a-1;
    else
        a=700;

    if(a<-500){
        aa=aa-100;
    }

    if(aa<-251){
        aa=100;
    }
      glPopMatrix();
    glutPostRedisplay();
}
void fish2()
{
       glPushMatrix();
    glTranslatef(b, bb, 0);
	glColor3f(1.0,0.0,0.0);

  glBegin(GL_POLYGON);
  glVertex2f(70,145);
  glColor3ub(1.0,0.0,0.0);
  glVertex2f(20,120);
  glVertex2f(30,145);
    glVertex2f(20,170);


  glEnd();

  glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
   glVertex2f(65,145);

   glVertex2f(125,170);

   glVertex2f(165,145);
   glVertex2f(125,120);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3ub(1.0,0.0,0.0);
    glVertex2f(126,168);
   glColor3f(1.0,0.0,0.0);
   glVertex2f(110,155);
    glVertex2f(85,195);
 glEnd();

 glBegin(GL_TRIANGLES);
  glColor3ub(1.0,0.0,0.0);
    glVertex2f(126,122);
   glColor3f(1.0,0.0,0.0);
	glVertex2f(110,136);
	glVertex2f(85,95);
  glEnd();




 glColor3f(0.0,0.0,0.0);
  glPointSize(4.0);
  glBegin(GL_POINTS);
  glVertex2f(150,149);
  glEnd();

       if(b<=1000)
        b=b+1;
    else
        b=-500;

    if(b>1000){
        bb=bb+150;
    }
    if(bb>251){
        bb=5;
    }
    glPopMatrix();
    glutPostRedisplay();

}
void plastic_bottle_1(){

    if(!break_down){
   glPushMatrix();
     glLoadIdentity();
     glTranslated(0, y_mov_1, 0.0);

    //body
    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.5); //ligt green
    glVertex2d(600,600);
	glVertex2d(595,600);
    glVertex2d(595,590);
    glVertex2d(590,590);
    glVertex2d(590,545);
    glVertex2d(605,545);
    glVertex2d(605,590);
    glVertex2d(600,590);
    glVertex2d(600,600);
	glEnd();
	//cap
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2d(601,600);
	glVertex2d(593,600);
    glVertex2d(593,595);
    glVertex2d(601,595);
	glEnd();


    glPopMatrix();


     if(y_mov_1>=-300){
        y_mov_1-=1;
    }
    else {
         y_mov_1+=1;
         break_down=true;
         into_two=true;
    }



    glutPostRedisplay();

    }

}
void break_process(){
    lag++;
    if(break_down){
    if(into_two){
       //two pieces
    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.5); //ligt green
    glVertex2d(600,300);
	glVertex2d(595,300);
    glVertex2d(595,290);
    glVertex2d(590,290);
    glVertex2d(590,270);
    glVertex2d(605,270);
    glVertex2d(605,290);
    glVertex2d(600,290);
    glEnd();
    //second
    glBegin(GL_QUADS);
    glVertex2d(590,260);
    glVertex2d(590,235);
    glVertex2d(605,235);
    glVertex2d(605,260);


	glEnd();
	//cap
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2d(601,300);
	glVertex2d(593,300);
    glVertex2d(593,295);
    glVertex2d(601,295);
	glEnd();

    }
    if(lag>=500){
    into_two=false;
    into_four=true;
    }
    //four pieces
    if(into_four){
   //1st
    glBegin(GL_POLYGON);
    glColor3f(0, 0.2, 0.5);

    glVertex2d(600,300);
    glVertex2d(605,300);
    glVertex2d(605,290);
    glVertex2d(610,290);
    glVertex2d(610,270);
    glVertex2d(600,270);
     glEnd();
 glBegin(GL_POLYGON);
    //2nd
    glVertex2d(590,300);
    glVertex2d(585,300);
    glVertex2d(585,290);
    glVertex2d(580,290);
    glVertex2d(580,270);
    glVertex2d(590,270);
     glEnd();
    //3rd
    glBegin(GL_QUADS);
    glVertex2d(590,260);
    glVertex2d(585,260);
    glVertex2d(585,235);
    glVertex2d(590,235);
    //4th
    glVertex2d(610,235);
    glVertex2d(605,235);
    glVertex2d(605,260);
    glVertex2d(610,260);

	glEnd();
	//cap
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2d(601,310);
	glVertex2d(593,310);
    glVertex2d(593,305);
    glVertex2d(601,305);
	glEnd();
    }

        //8 pieces
        // 16 circles


    }
}
void sky1(){
        // Draw sky
    glColor3f(0.5, 0.8, 1.0);  // Light blue color for the sky
    glBegin(GL_POLYGON);
    glVertex2f(0, 500);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 500);
    glEnd();
}
void river2(){
    // River Color
    glColor3ub(0, 191, 255);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(1200, 0);
    glVertex2d(1200, 230);
    glVertex2d(0, 230);
    glEnd();

}
void boat(){
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(665 , 220);
    glVertex2d(860 , 220);
    glVertex2d(885 , 250);
    glVertex2d(640 , 250);
    glEnd();

    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2d(705 , 250);
    glVertex2d(820 , 250);
    glVertex2d(810 , 280);
    glVertex2d(705 , 280);
    glEnd();

}
void man_1(){
    glColor3ub(0, 0, 255); // Blue color for the body (square)
    glBegin(GL_POLYGON);
    glVertex2d(850 , 270);
    glVertex2d(850 , 250);
    glVertex2d(870 , 250);
    glVertex2d(870 , 270);
    glEnd();
     glColor3ub(255, 255, 255); // white color for the head (circle)
    circle(5, 5, 860, 270);


}
void hook(){
    glColor3ub(192, 192, 192);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2d(850, 250);
    glVertex2d(850, 150);
    glEnd();
}
void microplastic(){

   //reduced
    if(fw>300){
        glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2f(400,150);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(405,155);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(410,120);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(415,125);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(420,120);
    glEnd();glBegin(GL_POINTS);
    glVertex2f(400,120);
    glEnd();
     glBegin(GL_POINTS);
    glVertex2f(420,130);
    glBegin(GL_POINTS);
    glVertex2f(420,130);
    glBegin(GL_POINTS);
    glVertex2f(220,130);
    glBegin(GL_POINTS);
    glVertex2f(720,130);
    glEnd();
     glBegin(GL_POINTS);
    glVertex2f(725,130);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(600,135);
    glEnd();

    }
 else{
    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2f(400,150);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(405,155);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(410,120);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(415,125);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(420,120);
    glEnd();glBegin(GL_POINTS);
    glVertex2f(400,120);
    glEnd();
     glBegin(GL_POINTS);
    glVertex2f(420,130);
    glEnd();glBegin(GL_POINTS);
    glVertex2f(400,135);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(420,130);
    glEnd();glBegin(GL_POINTS);
    glVertex2f(200,135);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(220,130);
    glEnd();glBegin(GL_POINTS);
    glVertex2f(300,135);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(720,130);
    glEnd();
     glBegin(GL_POINTS);
    glVertex2f(725,130);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(600,135);
    glEnd();
}

}


void fish3()
{


    if(fw<=700){
        fw++;
    }

    glPushMatrix();
    glTranslatef(fw, 0, 0);
	glColor3f(1.0,0.0,0.0);

    glBegin(GL_POLYGON);
    glVertex2f(70,145);
    glColor3ub(1.0,0.0,0.0);
    glVertex2f(20,120);
    glVertex2f(30,145);
    glVertex2f(20,170);
    glEnd();

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(65,145);
    glVertex2f(125,170);
    glVertex2f(165,145);
    glVertex2f(125,120);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(1.0,0.0,0.0);
    glVertex2f(126,168);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(110,155);
    glVertex2f(85,195);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(1.0,0.0,0.0);
    glVertex2f(126,122);
    glColor3f(1.0,0.0,0.0);
	glVertex2f(110,136);
	glVertex2f(85,95);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(150,149);
    glEnd();

     if(fw>300){
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(100,149);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(105,140);
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(102,145);
    glEnd();
    }


    glPopMatrix();
    glutPostRedisplay();

}
void handleKeypress(unsigned char k,int x0,int y2)
{

	if(k=='s'||k=='S'){
        screen_off=1;
	}

}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(screen_off==1 && (next<500)){
    sky();
    sun();
    clouds();
    river();
    side();
    wooden();
    plastic_bottle();
    man();}
   // next+=1;
   /* }
    else if((next>=500) && (next1<=1200)){
    sky();
     fish1();
     fish2();
     plastic_bottle_1();
     break_process();

    next1+=1;

    }
    else if((next1>1200)&&(next2<1200)){
    sky1();
    sun();
    clouds();
    river2();
    boat();
    man_1();
    hook();
    //plant();
    fish3();
    microplastic();
    next2++;
    }*/
    else screen();

    glFlush();
    glutSwapBuffers();



}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Microplastic");
    init();
    glutReshapeFunc(reshape);
     glutKeyboardFunc(handleKeypress);
    glutDisplayFunc(display);
    glutMainLoop();
}



