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
void output(int x, int y, char *string){
	int len, i;
	glRasterPos2f(x,y);
	len=(int) strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	}
}
void framed_rectangle(int x, int y, char *process)
{
	glColor3f(0.43, 0.85, 0.85);
	glLineWidth(5);
	glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x+10, y);
		glVertex2i(x+10, y+10);
		glVertex2i(x,y+10);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
        	glVertex2i(x+10, y);
        	glVertex2i(x+10, y+10);
		glVertex2i(x,y+10);
	glEnd();
	output(x+2, y+4, process);
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
void frontscreen(void)
{

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(0.57,0.43,0.87);
		output(0,5," Press: Key `t` to go to next screen, Key 'x' to exit");
    	glColor3f(0.13,0.55,0.41);
        	output(0,160," PES INSTITUTE OF TECHNOLOGY");
        glColor3f(0.13,0.55,0.41);
        	output(1,150,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
        glColor3f(0.13,0.55,0.41);
        	output(0,130,"A Mini Project On:-");
        glColor3f(0.13,0.13,0.55);
        	output(8,120,"\"ROUND ROBIN SIMULATION USING OPENGL\"");
        glColor3f(0.65,0.49,0.24);
        	output(4,100,"By :");
        glBegin(GL_LINES);
        	glVertex2f(4,98);
        	glVertex2f(10,98);
        glEnd();
        glColor3f(0.65,0.49,0.24);
        	output(4,90,"1. Priti(1PE17CS115)");
		output(4,82,"2. Rashmi(1PE17CS119)");
		output(4,74,"3. Loganyaa(1PE17CS126)");
        	output(4,80,"");
        glColor3f(0.53,0.12,0.47);
        	output(4,50,"Under the Guidence of :");
        glBegin(GL_LINES);
        	glVertex2f(4,48);
        	glVertex2f(50,48);
        glEnd();
        glColor3f(0.53,0.12,0.47);
        	output(7,38,"Mrs. Shubha Raj K.B");
        	output(7,30,"Assistant Professor,Dept. of CSE");
        glFlush();

}
void infoscreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.13,0.13,0.55);
		output(0,120,"WELCOME TO ROUND ROBIN SIMULATION");
		output(5,100,"1. Provide input to the program in <input.txt> in the following format:");
		output(5,90,"   {Process i} {ith Arrival Time} {ith Burst time}... {Quantum time}");
		output(5,80,"2. The program calls the Java file to run and execute the round robin algorithm");
		output(5,70,"   and stores the resulting answer in <output.txt>");
		output(5,60,"3. Press 'n' to go to simulation screen to understand how the proccesses");
		output(5,50,"   enter the Ready Queue and how the Gantt Chart is formed.");
	glFlush();
}
void cross_process(int x, int y)
{
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex2i(x,y);
	glVertex2i(x+10,y+10);
	glEnd();
	glFlush();
}
void translatePoint(int x, int y)
{
	glColor3f(0.43, 0.85, 0.85);
	glPointSize(20);
	glBegin(GL_POINTS);
	glVertex2i(x+5,y);
	glEnd();
	sleep(1);
	glFlush();
}
void simulation_screen()
{
	read_file();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.13,0.13,0.55);
		output(50,65,"Gantt simulation:");
	glColor3f(0.13,0.13,0.55);
		output(50,120,"Ready Queue simulation:");
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
				framed_rectangle(x1,y1, q_process);
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
		glPushMatrix();
		for(int l = 0; l < y1-y-20; l+=10)
		{
		glTranslatef(0,-10,0);
		translatePoint(x,y1);
		}
		glPopMatrix();
		framed_rectangle(x, y,process);
		glColor3f(0,0,0);
		time[k] = '\0';
			output(x+8, y-5, time);
		cross_process(x,y1);
		x = x+10;
	}
	glColor3f(0.57,0.43,0.87);
		output(0,5," Press: Key 'x' to exit");
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
	glClearColor(0.94,0.81,0.99,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void display()
{
   	glClear(GL_COLOR_BUFFER_BIT);
	if(df==10)
		infoscreen();
	if(df==0)
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
	if(key == 'x')
		exit(0);
	display();
}
int main(int argc,char **argv)
{
	system("java SchedulingImp < input.txt > output.txt");
  	df = 0;
  	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(120,0);
  	glutCreateWindow("Round robin");
	glutFullScreen();
  	glutReshapeFunc(myreshape);
  	glutDisplayFunc(display);
  	glutKeyboardFunc(keyboard);
  	myinit();
 	glutMainLoop();
  	return 0;
}
