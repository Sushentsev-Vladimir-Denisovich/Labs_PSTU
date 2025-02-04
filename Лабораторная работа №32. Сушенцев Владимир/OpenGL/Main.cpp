#define _CRT_SECURE_NO_WARNINGS

#include "Graph.h"
#include <conio.h>
#include <locale>
#include <glut.h>

using namespace std;

Graph<int> graph;

void display()
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH); //������ ������ ��������� � ����� ������ ����
	glViewport(0, 0, WinW, WinH);
	glClearColor(0.55, 0.45, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.DrawGraph(); // �������� ���, �� VERTLIST.SIZE()==0

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	/*WinW = w;
	WinH = h;*/
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

static void mouseClick(int btn, int stat, int x, int y)
{
	Graph<int> graph1 = graph;

	if (stat == GLUT_DOWN)
	{
		int j;
		int i;
		int t;

		if (x > 10 && x < 90 && y > 15 && y < 40)
		{
			//cout << "���������� ������\n";
			//cout << "�-�� �����, ������ ���� ������: "; cin >> i;
			//cout << "�-�� �����, ���� ���� ������: "; cin >> j;
			//cout << "�-�� ����������: "; cin >> t;
			//grap�.adjMatrix[i][j] = t;
			
		}
		if (x > 410 && x < 480 && y > 15 && y < 40)
		{
			cout << "�������� ������\n";
			int i; cout << "�-�� �����, ������ ���� ������: "; cin >> i;
			int j; cout << "�-�� �����, ���� ���� ������: "; cin >> j;
			graph.adjMatrix[i][j] = -1;
		}
	}
	
	glutPostRedisplay();
	//glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouseClick);
	//glutMainLoop();

	//graph.drawButtons();
}

Graph<int> makeGraph()
{
	setlocale(LC_ALL, "Russian");
	Graph<int> graph; // �������� �����, ����������� ������� � �������� ������ ����

	cout << "���-�� �������: "; cin >> graph.n;
	graph.GRADOSTROENIE(graph.n);
	//������� ������ ��� �������� �������
	int Marshrut[20][20];
	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			Marshrut[i][j] = 0;
		}
	}
	//������� ���������� ����� �������� �� ������� ���������
	graph.VIVOD(graph.adjMatrix, graph.n);
	//���������� � �������
	graph.REDUCIROVANIE(graph.adjMatrix, graph.n);
	graph.ObnulenieOtric(graph.Redukcia, graph.n);
	cout << "������� ������� � ������������������ �������� � ���������\n";
	graph.VIVOD(graph.Redukcia, graph.n);
	cout << "\n";
	//��������� ������ ������� �������� ��� ������� �������� �������, ������� ����, ����� ���� [i][i]
	cout << "������� ������� �������\n";
	graph.NULEVAYA(graph.Redukcia, graph.n);
	graph.VIVOD(graph.Ocenka, graph.n);
	cout << "\n";
	//���������� �������, �������� ������� � �������������� ������
	graph.RedukciaMatrici(graph.Redukcia, graph.n, Marshrut, graph.Ocenka);
	cout << "������� ����������������� �������\n";
	graph.VIVOD(graph.Redukcia, graph.n);
	cout << "\n";
	///
	bool T = true;
	for (int i = 0; i < graph.n; i++)
	{
		for (int j = 0; j < graph.n; j++)
		{
			if (graph.Redukcia[i][j] != -1)
				T = false;
		}
	}
	while (T == false)
	{
		graph.REDUCIROVANIE(graph.Redukcia, graph.n);
		cout << "������� ������� � ������������������ �������� � ���������\n";
		graph.VIVOD(graph.Redukcia, graph.n);
		cout << "\n";
		cout << "������� ������� �������\n";
		graph.NULEVAYA(graph.Redukcia, graph.n);
		graph.VIVOD(graph.Ocenka, graph.n);
		cout << "\n";
		graph.RedukciaMatrici(graph.Redukcia, graph.n, Marshrut, graph.Ocenka);
		cout << "������� ����������������� �������\n";
		graph.VIVOD(graph.Redukcia, graph.n);
		cout << "\n";
		T = true;
		for (int i = 0; i < graph.n; i++)
		{
			for (int j = 0; j < graph.n; j++)
			{
				if (graph.Redukcia[i][j] != -1)
					T = false;
			}
		}
	}
	int start; cout << "�-�� ����� ������ ��������: "; cin >> start;
	cout << "�������: ";
	cout << "\n\n����� ��������: " << graph.Vivod_Marshrut(Marshrut, graph.n, start - 1, graph.adjMatrix);
	cout << "\n\n������� ���� ���������� ������ �������\n\n";
	cout << "������� ���� ���������� ��������";
	cout << endl;
	return graph;
}



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	glutInit(&argc, argv);

	graph = makeGraph();

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(750, 250);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutCreateWindow("�����������");

	WinW = glutGet(GLUT_WINDOW_WIDTH);
	WinH = glutGet(GLUT_WINDOW_HEIGHT);
	
	
	glutPostRedisplay();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	
	return 0;
}