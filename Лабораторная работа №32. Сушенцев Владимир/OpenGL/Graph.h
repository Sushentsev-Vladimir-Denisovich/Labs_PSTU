#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <freeglut.h>
#include <string>

using namespace std;

const int maxSize = 20;

int R;
int WinW;
int WinH;

template <class T>
class Graph
{
public:
	int n;
	int adjMatrix[20][20];
	int Redukcia[20][20];
	int minstrok[20];
	int minstolb[20];
	int Ocenka[20][20];
	///
	struct vertCoord
	{
		int x, y;
	};
	vertCoord vertC[20];
public:

	Graph()
	{
		//перебор строк и столбцов матрицы смежности и заполнение её нулями
		for (int i = 0; i < maxSize; ++i)
		{
			for (int j = 0; j < maxSize; ++j)
			{
				this->adjMatrix[i][j] = 0;
			}
		}
	}

	~Graph() {}

	void REDUCIROVANIE(int goroda[20][20], int n) // редукция по строкам, затем по столбцам
	{
		this->MinStrok(goroda, n);

		this->RedukciyaStrok(goroda, n, this->minstrok);

		this->MinStolb(this->Redukcia, n);

		this->RedukciyaStolbcov(this->Redukcia, n, this->minstolb);
	}

	void Ocenivanie(int n, int Redukcia[20][20]) // Выполняет оценку нулевых клеток
	{
		int M;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Redukcia[i][j] == 0)
				{
					int min = 999, miin = 999;
					for (int p = 0; p < j; p++)
					{
						if (Redukcia[i][p] != -1 && Redukcia[i][p] < min) min = Redukcia[i][p];
					}
					for (int p = j + 1; p < n; p++)
					{
						if (Redukcia[i][p] != -1 && Redukcia[i][p] < min) min = Redukcia[i][p];
					}
					if (min == 999) min = 0;

					for (int k = 0; k < i; k++)
					{
						if (Redukcia[k][j] != -1 && Redukcia[k][j] < miin) miin = Redukcia[k][j];
					}
					for (int k = i + 1; k < n; k++)
					{
						if (Redukcia[k][j] != -1 && Redukcia[k][j] < miin) miin = Redukcia[k][j];
					}
					if (miin == 999) miin = 0;

					this->Ocenka[i][j] = min + miin;
				}
				else this->Ocenka[i][j] = -1;
			}
		}
	}

	void RedukciaMatrici(int Redukcia[20][20], int n, int Marshrut[20][20], int Ocenka[20][20]) // Удаление из рассмотрения дороги с наибольшим нулем, обратной дороги и столбца со строкой
	{
		int M = -1, k, p;
		// Находим 0 матрицы с наибольшей оценкой
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (Ocenka[i][j] > M)
				{
					M = Ocenka[i][j];
					k = i;
					p = j;
				}
			}

			for (int j = i + 1; j < n; j++)
			{
				if (Ocenka[i][j] > M)
				{
					M = Ocenka[i][j];
					k = i;
					p = j;
				}
			}
		}
		// Присвоили клетке матрицы с наибольшей оценкой М, и клетке с обратным маршрутом
		Redukcia[k][p] = -1;
		Redukcia[p][k] = -1;
		// Исключаем строку и столбец с двумя М    
		for (int j = 0; j < n; j++)
			Redukcia[k][j] = -1;
		for (int i = 0; i < n; i++)
			Redukcia[i][p] = -1;
		// Запомнили готовый маршрут
		Marshrut[k][p] = 1;
	}

	void DrawGraph()
	{
		int n = this->n;
		for (int i = 0; i < n; i++)
		{
			setCoord(i, n);
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (adjMatrix[i][j] != -1)
				{
					if (j > i)
					{
						int a = adjMatrix[i][j];
						if (a != 0)
						{
							drawLineGreen(a, vertC[i].x, vertC[i].y - 20, vertC[j].x, vertC[j].y - 20);
						}
					}
					else
					{
						int a = adjMatrix[i][j];
						if (a != 0)
						{
							drawLineRed(a, vertC[i].x, vertC[i].y + 20, vertC[j].x, vertC[j].y + 20);
						}
					}

				}
			}
		}
		drawVertex(n);
		//drawButtons();
	}

	int GetVertPos(const T& vertex)
	{
		for (int i = 0; i < this->vertList.size(); ++i)
		{
			if (this->vertList[i] == vertex)
				return i;
		}
		return -1;
	}

	void setCoord(int i, int n)
	{
		int R1;
		int x0 = WinW / 2;
		int y0 = WinH / 2;
		if (WinW > WinH)
		{
			R = 5 * (WinH / 13) / n;
			R1 = WinH / 2 - R - 10;
		}
		else {
			R = 5 * (WinW / 13) / n;
			R1 = WinW / 2 - R - 10;
		}
		float theta = 2.0f * 3.1415926f * float(i) / float(n);
		float y1 = R1 * cos(theta) + y0;
		float x1 = R1 * sin(theta) + x0;

		vertC[i].x = x1;
		vertC[i].y = y1;
	}

	void drawCircle(int x, int y, int R) //рисуем круг в заданных координатах
	{
		glColor3f(1.0, 1.0, 1.0);
		float x1, y1;
		glBegin(GL_POLYGON);
		for (int i = 0; i < 360; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(360);
			y1 = R * cos(theta) + y;
			x1 = R * sin(theta) + x;;
			glVertex2f(x1, y1);
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		float x2, y2;
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 360; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(360);
			y2 = R * cos(theta) + y;
			x2 = R * sin(theta) + x;
			glVertex2f(x2, y2);
		}
		glEnd();
	}

	void drawText(int nom, int x1, int y1)
	{
		GLvoid* font = GLUT_BITMAP_HELVETICA_18;
		string s = to_string(nom);
		glRasterPos2i(x1 - 5, y1 - 5);
		for (int j = 0; j < s.length(); j++)
			glutBitmapCharacter(font, s[j]);
	}

	void drawVertex(int n)
	{
		for (int i = 0; i < n; i++) {
			drawCircle(vertC[i].x, vertC[i].y, R);
			drawText(i + 1, vertC[i].x, vertC[i].y);
		}
	}

	void drawLineGreen(int text, int x0, int y0, int x1, int y1) //ребро неориентированный взвешенный граф
	{
		glColor3f(0.15f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2i(x0, y0);
		glVertex2i(x1, y1);
		glEnd();

		drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
	}
	void drawLineRed(int text, int x0, int y0, int x1, int y1) //ребро неориентированный взвешенный граф
	{
		glColor3f(1.0f, 0.35f, 0.0f);
		glBegin(GL_LINES);
		glVertex2i(x0, y0);
		glVertex2i(x1, y1);
		glEnd();

		drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
	}

	

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void MinStrok(int adjMatrix[20][20], int n)
	{
		for (int i = 0; i < n; i++)
		{
			this->minstrok[i] = 999;

			for (int j = 0; j < i; j++)
			{
				if (adjMatrix[i][j] < this->minstrok[i] && adjMatrix[i][j] != -1)
				{
					this->minstrok[i] = adjMatrix[i][j];
				}
			}

			for (int j = i + 1; j < n; j++)
			{
				if (adjMatrix[i][j] < this->minstrok[i] && adjMatrix[i][j] != -1)
				{
					this->minstrok[i] = adjMatrix[i][j];
				}
			}

			if (this->minstrok[i] == 999) this->minstrok[i] = 0;
		}
	}

	void MinStolb(int adjMatrix[20][20], int n)
	{
		for (int i = 0; i < n; i++)
		{
			this->minstolb[i] = 999;

			for (int j = 0; j < i; j++)
			{
				if (adjMatrix[j][i] < this->minstolb[i] && adjMatrix[j][i] != -1)
				{
					this->minstolb[i] = adjMatrix[j][i];
				}
			}

			for (int j = i + 1; j < n; j++)
			{
				if (adjMatrix[j][i] < this->minstolb[i] && adjMatrix[j][i] != -1)
				{
					this->minstolb[i] = adjMatrix[j][i];
				}
			}

			if (this->minstolb[i] == 999) this->minstolb[i] = 0;
		}
	}

	void RedukciyaStrok(int adjMatrix[20][20], int n, int* minstrok)
	{
		// Создаем новый массив, хранящий значения расстояний в матрице после редукции строк
		
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				this->Redukcia[i][j] = adjMatrix[i][j];
			}
		}
		// Выполняем редукцию строк
		for (int i = 0; i < n; i++)
		{
			if (minstrok[i] != 0)
			{
				for (int j = 0; j < n; j++)
				{
					if (adjMatrix[i][j] != -1 && this->Redukcia[i][j] != -1)
						this->Redukcia[i][j] = adjMatrix[i][j] - minstrok[i];
				}
			}
			this->Redukcia[i][i] = -1;
		}
	}

	void RedukciyaStolbcov(int adjMatrix[20][20], int n, int* minstolb)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				this->Redukcia[i][j] = adjMatrix[i][j];
			}
		}
		// Выполняем редукцию строк
		for (int i = 0; i < n; i++)
		{
			if (minstolb[i] != 0)
			{
				for (int j = 0; j < n; j++)
				{
					if (adjMatrix[j][i] != -1 && this->Redukcia[j][i] != -1)
						this->Redukcia[j][i] = adjMatrix[j][i] - minstolb[i];
				}
			}
			this->Redukcia[i][i] = -1;
		}
	}

	void ObnulenieOtric(int Redukcia[20][20], int n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Redukcia[i][j] < 0 && this->adjMatrix[i][j] != -1)
					Redukcia[i][j] = 0;
			}
			Redukcia[i][i] = -1;
		}

	}

	void GRADOSTROENIE(int n)
	{
		
		// Вводим расстояния между городами в матрицу смежности
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				cout << "В-те расстояние от " << i + 1 << " до " << j + 1 << ": "; cin >> this->adjMatrix[i][j];
			}
			this->adjMatrix[i][i] = -1;
			for (int j = i + 1; j < n; j++)
			{
				cout << "В-те расстояние от " << i + 1 << " до " << j + 1 << ": "; cin >> this->adjMatrix[i][j];
			}
		}
		cout << "\n";

	}

	

	void VIVOD(int Redukcia[20][20], int n)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << Redukcia[i][j] << "\t";
			}
			cout << "\n";
		}
	}
	void NULEVAYA(int Redukcia[20][20], int n)
	{
		this->Ocenivanie(n, Redukcia);
	}

	int Vivod_Marshrut(int Marshrut[20][20], int n, int start, int goroda[20][20])
	{
		cout << start + 1;
		int finish = start;
		int k = 0, j = 0, I = 0;
		bool P = false;
		while (k != n-1)
		{
			if (Marshrut[start][j] == 1)
			{
				I += goroda[start][j];
				cout << "--->" << j + 1;
				start = j;
				j = 0;
				k++;
				P = true;
			}
			j++;
			if (P == true)
			{
				j = 0;
				P = false;
			}
		}
		return I;
	}
};
