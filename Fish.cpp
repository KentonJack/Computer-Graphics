// mysecond.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "time.h"
#include "iostream"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "gl/glew.h"
#include "GL/glut.h"
#include "GL/glaux.h"
#include "atlimage.h"
#define Maxnum 50
using namespace::std;
const GLfloat R = 0.40f;
const GLfloat Pi = 3.1415926536f;
int x = clock();
int num = 6;
int iPointNum = 2;
float x1 = 0.0, y = 0.0, x2 = 0.75, y2 = 0, x3 = 0.75, y3 = 0.75, x4 = 0.0, y4 = 0.75;
float myX = 0.0, myY = 0.0;
int wid = 400, hei = 300;
struct My
{						//自己
	float myX, myY;
	float myR;
	float speed;
	My()
	{
		myX = 0.0;
		myY = 0.0;
		myR = 0.03;
	}
};
My my;
struct Enemy
{					
	float enemyX, enemyY;
	float enemyR;
	float speed;
	Enemy()
	{
		enemyX = -1.1;
		enemyY = 0.9;
		enemyR = (rand() % (70 - 10) + 10) / 1000.0;
		speed = rand() % (10 - 1) + 1;
	}
};
Enemy enemy[Maxnum];		//初始化
/* 定义三个光源（红色 绿色和蓝色）的位置 */
static float lightPositionR[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionG[] = { 0.0f, 0.0f, 5.0f, 1.0f };
static float lightPositionB[] = { 0.0f, 0.0f, 5.0f, 1.0f };
/* 定义三个光源的漫射光 */
static float diffuseLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float diffuseLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float diffuseLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
/* 定义三个光源的镜面光 */
static float specularLightR[] = { 1.0f, 0.0f, 0.0f, 1.0f };
static float specularLightG[] = { 0.0f, 1.0f, 0.0f, 1.0f };
static float specularLightB[] = { 0.0f, 0.0f, 1.0f, 1.0f };
/* 再定义一个默认的光源 */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static float lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };
bool LightInit()
{
	/* 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	/* 设置0号光源 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	/* 设置1号红色光源 */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightR);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightR);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPositionR);
	/* 设置2号绿色光源 */
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightG);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightG);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPositionG);
	/* 设置3号蓝色光源 */
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightB);
	glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightB);
	glLightfv(GL_LIGHT3, GL_POSITION, lightPositionB);
	glEnable(GL_LIGHT0);                                     /*< 启用0号灰色光源,让物体可见 */
	return 1;												/*< 成功返回 */
}
/*
void MaterialDraw()
{
	// 用户自定义的绘制过程
	///定义材质属性值
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 }; // 无材质颜色
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 }; // 环境颜色
	GLfloat mat_ambient_color[] = { 0.8, 0.6, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.2, 0.5, 0.8, 1.0 };// 散射颜色
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };// 镜面反射颜色
	GLfloat no_shininess[] = { 0.0 };              // 镜面反射指数为0
	GLfloat low_shininess[] = { 5.0 };             // 镜面反射指数为5.0
	GLfloat high_shininess[] = { 100.0 };          // 镜面反射指数为100.0
	GLfloat mat_emission[] = { 0.3, 0.2, 0.3, 0.0 }; // 发射光颜色
	//清除缓存并重置单位矩阵
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.75, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.0, 1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.75, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2, 0.0, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.75, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	auxSolidSphere(0.5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2, -1.75, -6.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	auxSolidSphere(0.5);
	glPopMatrix();
	glFlush();													//强制执行所有的OpenGL命令
}*/
GLuint ATLLoadTexture(const char *fileName)
{
	BITMAP bm;
	GLuint idTexture = 0;
	CImage img;             //需要头文件atlimage.h  
	LPCTSTR ptr;
	ptr = (LPCTSTR)fileName;
	HRESULT hr = img.Load(ptr);
	if (!SUCCEEDED(hr))   //文件加载失败  
	{
		MessageBox(NULL, L"文件加载失败", L"ERROR", 0);
		return NULL;
	}
	HBITMAP hbmp = img;
	if (!GetObject(hbmp, sizeof(bm), &bm))
		return 0;
	glGenTextures(1, &idTexture);
	if (idTexture)
	{
		glBindTexture(GL_TEXTURE_2D, idTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bm.bmBits);
	}
	return idTexture;
}
GLuint LoadTexture(const char * filename, int width, int height)
{
	GLuint texture;
	unsigned char * data;
	FILE * file;
	//读文件  
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	data = (unsigned char *)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);
	fclose(file);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//线性滤图  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//生成纹理  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	//释放纹理 
	free(data); 
	return texture;
}
void Background(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
	glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
	glEnd();
}
void myDisplay(void)
{
	int i;
	int j;
	int n = 1000;
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	//导入纹理  
	GLuint texture = LoadTexture("sea.bmp", 400, 300);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
	/*	glBegin(GL_POLYGON);				//画矩形
	glVertex2f(x1,y);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();*/
	//glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);				//画yuan
	for (j = 0; j < n; ++j)
	{
		glVertex2f(my.myX + my.myR*cos(2 * Pi / n*j), my.myY + my.myR*sin(2 * Pi / n*j));
	}
	glEnd();
	//glColor3f(1.0, 0.0, 0.0);				//画其他yuan
	for (i = 0; i < num; i++)
	{
		//enemy[i].enemyX = -1.0;
		//enemy[i].enemyY = 0.7 - i*0.3;
		//enemy[i].enemyR = 0.1;
		glBegin(GL_POLYGON);				//画yuan
		for (j = 0; j < n; ++j)
		{
			glVertex2f(enemy[i].enemyX + enemy[i].enemyR*cos(2 * Pi / n*j), enemy[i].enemyY + enemy[i].enemyR*sin(2 * Pi / n*j));
		}
		glEnd();
	}
	glutSwapBuffers();
	glFlush();
}
bool crash(My M, Enemy E)					//判断是否碰撞
{
	if ((M.myX - E.enemyX)*(M.myX - E.enemyX) + (M.myY - E.enemyY)*(M.myY - E.enemyY) <= (M.myR + E.enemyR)*(M.myR + E.enemyR))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PrintText(char *string, float x, float y)
{
	unsigned int listBase = glGenLists(96);
	///错误检查.如果listBase为0或string为NULL则不用绘制直接返回
	if (listBase == 0 || string == NULL)
		return;
	HFONT hFont = CreateFont(60,					/**< 字体高度 */
		0,						/**< 字体宽度 */
		0,						/**< 字体的旋转角度 Angle Of Escapement */
		0,						/**< 字体底线的旋转角度Orientation Angle */
		FW_BOLD,				/**< 字体的重量 */
		FALSE,					/**< 是否使用斜体 */
		FALSE,					/**< 是否使用下划线 */
		FALSE,					/**< 是否使用删除线 */
		ANSI_CHARSET,			/**< 设置字符集 */
		OUT_TT_PRECIS,			/**< 输出精度 */
		CLIP_DEFAULT_PRECIS,	/**< 裁剪精度 */
		ANTIALIASED_QUALITY,	/**< 输出质量 */
		FF_DONTCARE | DEFAULT_PITCH,		/**< Family And Pitch */
		L"Arial");				/**< 字体名称 */
	if (!hFont)
		exit(0);  /**< 创建字体失败则返回 */
	HFONT oldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont); /**< 选择我们需要的字体 */
	wglUseFontBitmaps(wglGetCurrentDC(), 32, 96, listBase);
	glPushMatrix();
	glDisable(GL_DEPTH_TEST); /**< 关闭深度测试 */
	glDisable(GL_LIGHTING); /**< 关闭光照 */
	glRasterPos2f(x, y); /**< 将光栅位置移动到指定点 */
						 ///将字符串输出到屏幕上
	glPushAttrib(GL_LIST_BIT); /**< 把显示列表属性压入属性堆栈 */
	glListBase(listBase - 32); /**< 设置显示列表的基值 */
	glCallLists(strlen(string), GL_UNSIGNED_BYTE, string); /**< 执行多个显示列表输出字符串 */
	glPopAttrib();  /**< 把显示列表属性弹出属性堆栈 */
					///恢复原来状态
	glEnable(GL_LIGHTING); /**< 启用光照 */
	glEnable(GL_DEPTH_TEST); /**< 启用深度测试 */
	glPopMatrix();
}
void fun(int value)
{
	int i;
	for (i = 0; i<num; i++)
	{
		if (crash(my, enemy[i]) == false)		//没有碰撞
		{
			enemy[i].enemyX = enemy[i].enemyX + enemy[i].speed*0.01;
			enemy[i].enemyY = 0.9 - (i % 7)*0.3;
			if (enemy[i].enemyX>1.0)
			{
				enemy[i].enemyX = -1.1;
				enemy[i].speed++;
				num++;
			}
		}
		else
		{						//碰撞
			if (my.myR>enemy[i].enemyR)
			{			//如果能吃掉它
				enemy[i].enemyR = 0.0;
				enemy[i].enemyX = 0;
				enemy[i].enemyY = 0;
				enemy[i].speed = 0;
				if (my.myR < 0.07)
					my.myR = my.myR + 0.002;
				else
				{
					int y = clock();
					printf("Win\n");
					printf("Score :%d", (y - x));
					Sleep(1000);
					exit(0);
				}
			}
			else
			{
				int y = clock();
				my.myR = 0.0;
				glClear(GL_COLOR_BUFFER_BIT);
				glLoadIdentity();
				///绘制字符过程
				glTranslatef(0.0f, 0.0f, -10.0f); /**< 移入屏幕 */
				glColor3f(0, 0, 0); /**< 指定颜色 */
				PrintText("DIE", 100, 100); /**< 调用方法输出字符串 */
				glFlush();
				printf("DIE\n");
				printf("Score: %d", (y - x));
				Sleep(1000);
				exit(0);
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(200, fun, 1);
}
void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a':
			my.myX = my.myX - 0.1;
			glutPostRedisplay();
			break;
		case 'w':
			my.myY = my.myY + 0.1;
			glutPostRedisplay();
			break;
		case 's':
			my.myY = my.myY - 0.1;
			glutPostRedisplay();
			break;
		case 'd':
			my.myX = my.myX + 0.1;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}
void init()
{
	glClearColor(-1.0f, 1.0f, 1.0f, 1.0f);
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 400);
	glutCreateWindow("大鱼吃小鱼");
	glutDisplayFunc(&myDisplay);
	glutKeyboardFunc(Key);
	//glutMouseFunc(plot);
	//fun();
	glutTimerFunc(200, fun, 1);
	init();
	glutMainLoop();
	return 0;
}

