#include"plane.h"

//����ͼƬ����
IMAGE background;//����ͼ
IMAGE plane_back;//�ɻ�����ͼ
IMAGE plane_mask;//�ɻ�����ͼ
IMAGE fplane_back;//�л�����ͼ
IMAGE fplane_mask;//�л�����ͼ
IMAGE bullte_back;//�ӵ�����ͼ
IMAGE bullte_mask;//�ӵ�����ͼ

//����ȫ�ֱ���
mem plane;//�ɻ��ṹ��
mem bullte[MAX];//�ӵ��ṹ������
mem fplane[FMAX];//�л��ṹ��

DWORD time_start, time_last; //ʱ��仯��

void Load()//ͼƬ����
{
	loadimage(&background, "background.jpg", SIZE, SIZE);
	loadimage(&plane_back, "plane_back.jpg", PSIZE, PSIZE);
	loadimage(&plane_mask, "plane_mask.jpg", PSIZE, PSIZE);
	loadimage(&fplane_back, "fplane_back.jpg", PSIZE, PSIZE);
	loadimage(&fplane_mask, "fplane_mask.jpg", PSIZE, PSIZE);
	loadimage(&bullte_back, "bullte_back.jpg", BSIZE, BSIZE);
	loadimage(&bullte_mask, "bullte_mask.jpg", BSIZE, BSIZE);
}
void DataInit()//���ݳ�ʼ��
{
	//�ɻ������ݳ�ʼ��
	plane.x = SIZE / 2 - PSIZE / 2; //�ɻ���ʼλ���ڱ���ͼ������
	plane.y = SIZE - PSIZE;
	plane.lable = true; //�ɻ������Ǵ���

	//�ӵ���ʼ��
	for (int i = 0; i < MAX; i++)
	{
		bullte[i].lable = false;//�ӵ�û���ռ�ǰ�ǲ����ڵ�
	}

	time_start = time_last = GetTickCount();//���������ڵĺ�����

	//�л���ʼ��
	for (int i = 0; i>FMAX; i++)
	{
		fplane[i].lable = false;
	}

}

void PlaneCtr()//ͨ�����������������ı�ɻ�������
{
	if (GetAsyncKeyState(VK_UP))//�����ƶ�
	{
		if (plane.y>0)//����Խ��
		plane.y-=0.8;
	}
	if (GetAsyncKeyState(VK_DOWN))//�����ƶ�
	{
		if (plane.y<SIZE-PSIZE)//y���ֵ600���ɻ�ͼƬ��СΪ80
		plane.y+=0.8;
	}
	if (GetAsyncKeyState(VK_LEFT))//�����ƶ�
	{
		if (plane.x>-PSIZE/2)//��������ǽ��һ�����
		plane.x-=0.8;
	}
	if (GetAsyncKeyState(VK_RIGHT))//�����ƶ�
	{
		if (plane.x<SIZE-PSIZE/2)
		plane.x+=0.8;
	}
	if (GetAsyncKeyState(VK_SPACE) &&time_last - time_start>80)//�����ӵ���ÿ���ӵ����Ϊ80����
	{
		BullterCre();//�ո����ӵ�
		time_start = time_last;
	}
	time_last = GetTickCount();
}

void Show()//�������
{	
	BeginBatchDraw();//˫�����ͼ������˸

	putimage(0, 0, &background);
	if (plane.lable)//�ɻ����ʹ�ӡ�ɻ�
	{
		putimage((int)plane.x, (int)plane.y, &plane_mask, SRCAND);
		putimage((int)plane.x, (int)plane.y, &plane_back, SRCPAINT);
	}
	for (int i = 0; i < MAX; i++)//ѭ���ж��ӵ�
	{
		if (bullte[i].lable)//�ӵ����ھʹ�ӡ�ӵ�
		{
			putimage((int)bullte[i].x, (int)bullte[i].y, &bullte_mask, SRCAND);
			putimage((int)bullte[i].x, (int)bullte[i].y, &bullte_back, SRCPAINT);
		}
	}
	for (int i = 0; i < FMAX; i++)
	{
		if (fplane[i].lable)//��ӡ�л�
		{
			putimage((int)fplane[i].x, (int)fplane[i].y, &fplane_mask, SRCAND);
			putimage((int)fplane[i].x, (int)fplane[i].y, &fplane_back, SRCPAINT);
		}
	}

	EndBatchDraw();
}

void BullterCre()//���˿ո񣬵��ú����������ӵ�
{
	for (int i = 0; i < MAX; i++)
	{
		if (!bullte[i].lable)//�ӵ������ھʹ����ӵ�
		{
			//�ӷɻ�����ǰ������ȥ
			bullte[i].x = plane.x + PSIZE / 2 - BSIZE / 2;
			bullte[i].y = plane.y - BSIZE;
			bullte[i].lable = true;
			break;//һ�οո����һ���ӵ�
		}
	}
}
void BullterMove()//�ӵ��ƶ�
{
	for (int i = 0; i < MAX; i++)
	{
		if (bullte[i].lable)//�ӵ����ڣ�����y����ͼ���
		{
			bullte[i].y--;//������������ƶ�

			if (bullte[i].y < 0)//�ӵ����գ������´�ȫ�Ƿ����ȥ���ӵ�
			{
				bullte[i].lable = false;
			}
		}
	}
}
void FplaneCre()//�л�����
{
	for (int i = 0; i < FMAX; i++)
	{
		if (!fplane[i].lable&&time_last-time_start>100)//û�ел��ͽ��й�������ʱ�亯�����Ʋ����ٶ�
		{
			fplane[i].lable = true;
			fplane[i].x = rand() % SIZE - PSIZE;//���õг����ڴ�����
			fplane[i].y = 0;
			time_start = time_last;
			break;//ÿ��һ��
		}
		time_last = GetTickCount();//��ȡ�µ�ʱ��
	}
}
void FplaneMove()//�л��ƶ�
{
	for (int i = 0; i < FMAX; i++)
	{
		if (fplane[i].lable)
		{
			fplane[i].y+=0.3;//�л�������

			if (fplane[i].y>SIZE)//�л�����
				fplane[i].lable = false;
		}
	}
}
void Hit()//����л�
{
	for (int i = 0; i < FMAX; i++)
	{
		if (!fplane[i].lable)//����������һ���ж�
			continue;

		for (int j = 0; j < MAX; j++)
		{
			if (!bullte[j].lable)
				continue;//�ӵ�������Ҳ����һ���ж�

			if (bullte[j].x>fplane[i].x&&  //�ӵ��͵л��н�������ʧ
				bullte[j].x<fplane[i].x + PSIZE
				&&bullte[j].y>fplane[i].y&&
				bullte[j].y <fplane[i].y + PSIZE) 
			{
				bullte[j].lable = false;
				fplane[i].lable = false;
			}
		}
	}
}


void Game()
{
	//����ͼƬ���ͳ�ʼ������
	Load();
	DataInit();
	srand((unsigned)time(NULL));//�������������

	while (1)
	{
		Show();//ͼ����ʾ
		PlaneCtr();//�ٿ�
		BullterMove();//�ӵ��ƶ�
		FplaneCre();//�л�����		
		Hit();//�ж��Ƿ���ел�
		FplaneMove();//�л�������
	}





}


