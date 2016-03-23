#include <glew.h> // glew.h must be included before gl.h/glu.h/freeglut.h
#include <freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
static int aa = 0;
static float ss = 0.5f;

void myDisplay(void)
{

	GLint i, j, k, v;
	static GLubyte Mask[128];
	FILE *fp;

	// �������������Ķ�����������
	static GLfloat vertex_list[][3] = {
		-0.25,0.5,-0.433013,
		0.25,0.5,-0.433013,
		0.5,0.5,0,
		0.25,0.5,0.433013,
		-0.25,0.5,0.433013,
		-0.5,0.5,0,
		-0.5,-0.5,0,
		-0.25,-0.5,-0.433013,
		0.25,-0.5,-0.433013,
		0.5,-0.5,0,
		0.25,-0.5,0.433013,
		-0.25,-0.5,0.433013,
	};

	//���¶���Ϊ�������Ķ�����������
	static GLfloat vertex3_list[][3] = {
		-0.25,0.5,0,
		0,0.5,-0.433013,
		0.25,0.5,0,
		0.25,-0.5,0,
		0,-0.5,-0.433013,
		-0.25,-0.5,0
	};

	//����Ϊ�������Ĳ��涥����������
	static GLint index_list[][4] = {
		5,6,11,4,
		4,11,10,3,
		3,10,9,2,
		1,8,9,2,
		0,7,8,1,
		5,6,7,0,
	};

	//����Ϊ�����������µ��涥����������
	static GLint index1_list[][6] = {
		0,5,4,3,2,1,
		6,7,8,9,10,11,
	};
	//����Ϊ�������Ĳ��涥����������
	static GLint index3_list[][4] = {
		0,1,4,5,
		1,2,3,4,
		0,5,3,2,
	};

	//��ȡ��VR���ַ���������
	//fp = fopen("mask.bmp", "rb");
	///if (!fp)
	//	exit(0);
	//if (fseek(fp, -(int)sizeof(Mask), SEEK_END))
	//	exit(0);
	//if (!fread(Mask, sizeof(Mask), 1, fp))
	//	exit(0);
	//fclose(fp);

	//
	glEnable(GL_DEPTH_TEST);  //������Ȳ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();	// ����ģ�͹۲����
	glPushMatrix();
	glTranslatef(0, 0.45f, 0.5f);
	glTranslatef(ss, 0.0f, 0.0f);  //ͨ���ı����ss��ֵ��ʵ����������ƽ��
	glRotatef(-45, 1.0f, 0.5f, -0.5f);
	glScalef(0.4f, 0.6f, 0.4f);

	//�����ǻ����������Ĳ������
	glBegin(GL_QUADS);
	for (i = 0; i<6; ++i)       // �������棬ѭ������
		for (j = 0; j<4; ++j)     // ÿ�������ĸ����㣬ѭ���Ĵ�
		{
			if (index_list[i][j] % 3 == 0)
				glColor3f(1.0f, 0.0f, 0.0f);
			if (index_list[i][j] % 3 == 1)
				glColor3f(0.0f, 1.0f, 0.0f);
			if (index_list[i][j] % 3 == 2)
				glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3fv(vertex_list[index_list[i][j]]);
			glDisable(GL_POLYGON_STIPPLE);
		}
	glEnd();

	//�����ǻ����������ϵ��沢���̻�
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(Mask);
	glBegin(GL_POLYGON);
	for (k = 0; k<6; k++)
	{
		glColor3f(0.9804f, 0.9882f, 0.0f);
		glVertex3fv(vertex_list[index1_list[0][k]]);
	}
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);

	//�����������µ���
	glBegin(GL_POLYGON);
	for (v = 0; v<6; v++)
	{
		glColor3f(0.6275f, 0.1255f, 0.9412f);
		glVertex3fv(vertex_list[index1_list[1][v]]);
	}
	glEnd();

	//�����￪ʼ������������������������˼�뼸������������ȫһ��
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.45f, -0.45f, -0.5f);
	glRotatef(aa / 15, 1.0f, -0.5f, -0.3f);//�Ա���aa���иı䣬ʵ������������ת
	glScalef(1.0f, 0.6f, 1.0f);
	glBegin(GL_QUADS);
	for (i = 0; i<3; ++i)      // �������棬ѭ������
		for (j = 0; j<4; ++j)     // ÿ�������ĸ����㣬ѭ���Ĵ�
		{
			if (i == 0)
				glColor3f(1.0f, 0.0f, 0.0f);
			if (i == 1)
				glColor3f(0.0f, 1.0f, 0.0f);
			if (i == 2)
				glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3fv(vertex3_list[index3_list[i][j]]);
		}
	glEnd();

	glBegin(GL_TRIANGLES);
	{ glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertex3_list[0]);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertex3_list[2]);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertex3_list[1]); }
	glEnd();

	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3fv(vertex3_list[3]);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3fv(vertex3_list[5]);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3fv(vertex3_list[4]);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glDisable(GL_DEPTH_TEST);//������Ȳ���
	glEnable(GL_BLEND);  //�������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //���û������

	glColor4f(0.4863, 0.9882, 0, 0.5);
	glTranslatef(-0.55, -0.55, 0.0);
	glRectf(-0.25, -0.25, 0.25, 0.25);
	glPopMatrix();
	glColor4f(0.6, 0.2, 0.9804, 0.5);
	glTranslatef(-0.35, -0.35, 0.0);
	glRectf(-0.25, -0.25, 0.25, 0.25);

	glutSwapBuffers();
	glFlush();// 
			  //glPopMatrix();
}
void myIdle(void)
{
	/* �µĺ������ڿ���ʱ���ã�������ʵ����������ƽ�ƺ�����������ת*/
	++aa;
	if (aa >= 5400) //����һ����ֵ�����ã�ʵ��������ת
		aa = 0;
	ss = ss + 0.0003;
	if (ss >= 0.8)    //����һ����ֵ�����ã�ʵ�ִӴ��������ƽ��
		ss = -ss;
	myDisplay();
}



int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("������ʵ����");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
	return 0;
}

