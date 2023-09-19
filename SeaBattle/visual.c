#include <glad/glad.h>
#include <math.h>
#include "visual.h"
#include "game.h"

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

#pragma comment(lib, "opengl32.lib")

float CELL_SIZE = 2.0f / (float)FIELD_SIZE;
float HALF_CELL_SIZE = 1.0f / (float)FIELD_SIZE;

void DrawCellGrid(Cell[FIELD_SIZE][FIELD_SIZE]);
void DrawCell(Cell*);
void DrawDot(int);
void DrawCross();
void DrawSquare(float);

void InitializeVisual()
{
	
}

void DrawMain()
{
	glColor3f(0.3f, 0.3f, 1.0f);
	glPushMatrix();

		glTranslatef(-0.5f, 0.0f, 0.0f);
		glScalef(0.5f, 0.5f, 0.0f);
		DrawCellGrid(playerMatrix);

	glPopMatrix();
	
	glPushMatrix();

		glTranslatef(0.5f, 0.0f, 0.0f);
		glScalef(0.5f, 0.5f, 0.0f);

		glColor3f(1.0f, 0.3f, 0.3f);
		DrawCellGrid(computerMatrix);

	glPopMatrix();

	/*glColor3f(0.3f, 1.0f, 0.3f);
	glBegin(GL_LINES);

		glVertex2f(0.0f, 0.5f); glVertex2f(0.0f, -0.5f);

	glEnd();*/
}

void DrawCellGrid(Cell matrix[FIELD_SIZE][FIELD_SIZE])
{
	glLineWidth(0.01f);
	glBegin(GL_LINES);

		for (int i = 0; i <= FIELD_SIZE; ++i)
		{
			float x = -1.0f + HALF_CELL_SIZE * i * 2;
			glVertex2f(x, -1.0f); glVertex2f(x, 1.0f);
		}

		for (int j = 0; j <= FIELD_SIZE; ++j)
		{
			float y = -1.0f + HALF_CELL_SIZE * j * 2;
			glVertex2f(-1.0f, y); glVertex2f(1.0f, y);
		}

	glEnd();

	for(int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			glPushMatrix();

				glTranslatef(-1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * i * 2.0f, -1.0f + HALF_CELL_SIZE + HALF_CELL_SIZE * j * 2.0f, 0.0f);
				glScalef(HALF_CELL_SIZE, HALF_CELL_SIZE, HALF_CELL_SIZE);

				DrawCell(&matrix[i][j]);

			glPopMatrix();
		}
}

void DrawCell(Cell* cell)
{
	/*if (!cell->isOpen)
		return;*/

	if (cell->hasShip)
	{
		DrawSquare(0.1f);

		glEnable(GL_LINE_SMOOTH);
		glPushMatrix();

			glLineWidth(0.5f);
			glScalef(0.7f, 0.7f, 0.0f);
			DrawCross();

		glPopMatrix();
		glDisable(GL_LINE_SMOOTH);
	}
	else
	{
		glPushMatrix();

			glScalef(0.2f, 0.2f, 0.0f);
			DrawDot(20);

		glPopMatrix();
	}
}

void DrawDot(int segments)
{
	glBegin(GL_TRIANGLE_FAN);

		glVertex2f(0.0f, 0.0f);

		for (int i = 0; i <= segments; ++i)
		{
			float theta = 2.0f * M_PI * (float)i / (float)segments;

			float x = cosf(theta);
			float y = sinf(theta);

			glVertex2f(x, y);
		}

	glEnd();
}

void DrawCross()
{
	glBegin(GL_LINES);

		glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
		glVertex2f(-1.0f, -1.0f); glVertex2f(1.0f, 1.0f);

	glEnd();
}

void DrawSquare(float width)
{
	float hf = width / 2.0f;

	float hfNegMin = -1.0f - hf;
	float hfNegMax = -1.0f + hf;

	float hfPosMin = 1.0f - hf;
	float hfPosMax = 1.0f + hf;

	for (int i = 0; i < 4; ++i)
	{
		glPushMatrix();

			glRotatef(90.0f * i, 0.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLE_STRIP);

				glVertex2f(hfNegMin, hfNegMin); glVertex2f(hfNegMin, hfPosMax);
				glVertex2f(hfNegMax, hfNegMin); glVertex2f(hfNegMax, hfPosMax);

			glEnd();

		glPopMatrix();
	}
}

void Rescale(int width, int height)
{
	int size = width > height * 2 ? height * 2 : width;
	glViewport((width - size) / 2, (height - size) / 2, size, size);
}