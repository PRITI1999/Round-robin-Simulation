#include<stdio.h>
#include<string.h>
#include<GL/glut.h>
#include<stdlib.h>
int df = 0;
char ready_queue[500];
char gantt_chart[500];
void read_file()
{
	FILE *fp;
	char ch;
	int i=0;
	fp = fopen("output.txt", "r");
	if (fp == NULL)
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
	while((ch = fgetc(fp)) != '\n'){
      		ready_queue[i++] = ch;
	}
	ready_queue[i] = ' ';
	i=0;
	while((ch = fgetc(fp)) != EOF){
		gantt_chart[i++] = ch;
	}
	gantt_chart[i] = ' ';
   	fclose(fp);
}
void framed_rectangle(int x, int y)
{
	glColor3f(0.5f, 1.0f, 0.50f);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x+10, y);
	glVertex2i(x+10, y+10);
	glVertex2i(x,y+10);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f); // Let it be yellow.
	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y);
        glVertex2i(x+10, y);
        glVertex2i(x+10, y+10);
        glVertex2i(x,y+10);
	glEnd();
	sleep(1);
	glFlush();
}
void drawstring(int x, int y, char *string,void *font)
{
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font,string[i]);
	}
}
void output(int x, int y, char *string){
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
}
void frontscreen(void)
{

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(0,0,0);
	output(120,5," Press key `n` to go to next screen");
    	glColor3f(0,0,0);
        output(5,160," PES INSTITUTE OF TECHNOLOGY");
        glColor3f(0,0,0);
        output(10.0,150,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
        glColor3f(0,0,0);
        output(60,130,"A Mini Project On:-");
        glColor3f(0,0,0);
        output(38,120,"\"ROUND ROBIN SIMULATION USING OPENGL\"");
        glColor3f(0,0,0);
        output(40,100,"By :");
        glBegin(GL_LINES);
        glVertex2f(40,98);
        glVertex2f(50,98);
        glEnd();
        glColor3f(0,0,0);
        output(40,90,"Rashmi(1PE17CS119), Priti(1PE17CS115) and Loganyaa(1PE17CS126)");
        output(40,80,"");
        glColor3f(0,0,0);
        output(40,60,"Under the Guidence of :");
        glBegin(GL_LINES);
        glVertex2f(40,58);
        glVertex2f(98,58);
        glEnd();
        glColor3f(0,0,0);
        output(72,30,"(B.E.)");
        output(70,20,"Assistant Professor,Dept. of CSE");
        glFlush();

}
void infoscreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	output(25,140,"WELCOME TO ROUND ROBIN SIMULATION");
	output(50,100,"1");
	output(50,80,"2.");
	output(50,60,"3.");
	glFlush();
}
void simulation_screen()
{
	read_file();
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 20;
	int y = 50;
	int x1 = 20;
	int y1 = 100;
	int i = 2;
	int j = 0;
	char ch;
	glColor3f(0,0,0);
	output(x, y-5, "0");
	while(gantt_chart[i] != '\0')
	{
		char time[3];
		char process[3];
		int k = 0;
		while(ready_queue[j] != '|' && ready_queue[j] != '\0')
		{
			char q_process[3];
			q_process[k++] = 'P';
			while((ch=ready_queue[j++]) != ' ')
			{
				q_process[k++] = ch;
			}
			q_process[k] = '\0';
			if(q_process[1] != '\0')
			{
				framed_rectangle(x1,y1);
				output(x1+2, y1+4, q_process);
				x1 = x1+10;
			}
			k = 0;
		}
		if(ready_queue[j] != '\0')
			j+=2;
		k=0;
		while((ch = gantt_chart[i++]) != ' ')
		{
			process[k++] = ch;
		}
		process[k] = '\0';
		k = 0;
		while((ch = gantt_chart[i++]) != ' ')
		{
			time[k++] = ch;
		}
		framed_rectangle(x, y);
		glColor3f(0,0,0);
		output(x+2, y+4, process);
		glColor3f(0,0,0);
		time[k] = '\0';
		output(x+8, y-5, time);
		x = x+10;
	}
	glFlush();
}
void myreshape(int w, int h)
{
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(w<=h)
                gluOrtho2D(45.0,135.0,-2.0*(GLfloat)h/(GLfloat)w,180.0*(GLfloat)h/(GLfloat)w);
        else
                gluOrtho2D(-45.0*(GLfloat)w/(GLfloat)h,135.0*(GLfloat)w/(GLfloat)h,-2.0,180.0);
  	glMatrixMode(GL_MODELVIEW);
  	glutPostRedisplay();
 }
void myinit()
{
	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	glMatrixMode(GL_MODELVIEW);
  	glClearColor(1.0,1.0,1.0,0.0);

}
void display()
{
   	glClear(GL_COLOR_BUFFER_BIT);
	if(df==10)
		infoscreen();
	if(df == 0)
		frontscreen();
	if(df==2)
		simulation_screen();
}
void keyboard(unsigned char key,int x,int y)
{
	if(key=='n')
		df=2;
	if(key =='t')
		df =10;
	display();
}
int main(int argc,char **argv)
{
	system("java SchedulingImp < input.txt > output.txt");
  	df = 0;
  	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  	glutCreateWindow("Round robin");
	glutFullScreen();
  	glutReshapeFunc(myreshape);
  	glutDisplayFunc(display);
  	glutKeyboardFunc(keyboard);
  	myinit();
 	glutMainLoop();
  	return 0;
}
